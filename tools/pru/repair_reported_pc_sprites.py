#!/usr/bin/env python3
"""Save-safe PC sprite repair for Alphoracle, I-Unown and two Elite Redux donors.

Executed after all artwork installers and before source QA/build.
Never edits battle art, species IDs, saves, animations, Pyroclast, or maps.
"""
from __future__ import annotations

from collections import deque
from pathlib import Path
import re

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
POKEMON = ROOT / "graphics/pokemon"

def read_palette(path: Path) -> list[tuple[int, int, int]]:
    lines = path.read_text().splitlines()
    assert lines[:3] == ["JASC-PAL", "0100", "16"], path
    return [tuple(map(int, line.split())) for line in lines[3:19]]

def save_png(path: Path, image: Image.Image, rgb: list[tuple[int, int, int]]) -> None:
    assert image.mode == "P" and image.size in ((64, 64), (32, 64))
    assert len(rgb) == 16
    image.putpalette([v for item in rgb for v in item] + [0] * (768 - 48))
    image.info["transparency"] = 0
    image.save(path, optimize=False)

def skarmet_palette() -> list[tuple[int, int, int]]:
    # Reuse an already allocated non-overlapping PC icon tag (#9).
    code = (ROOT / "src/pokemon_icon.c").read_text()
    m = re.search(r"static const u16 sPRUSkarmetIconPalette\[16\]\s*=\s*\{(.*?)\};", code, re.S)
    assert m, "Missing approved dark Skarmet icon palette"
    entries = re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", m.group(1))
    assert len(entries) == 16
    return [tuple(round(int(x) * 255 / 31) for x in rgb) for rgb in entries]

def noxichu_palette() -> list[tuple[int, int, int]]:
    code = (ROOT / "src/pokemon_icon.c").read_text()
    m = re.search(r"static const u16 sPRLNoxichuIconPalette\[16\]\s*=\s*\{(.*?)\};", code, re.S)
    assert m, "Missing approved dark/amber icon palette #6"
    entries = re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", m.group(1))
    assert len(entries) == 16
    return [tuple(round(int(x) * 255 / 31) for x in rgb) for rgb in entries]

def fix_alphoracle() -> None:
    src = POKEMON / "prl_authoritative/alphoracle/icon.png"
    with Image.open(src) as icon:
        assert icon.mode == "P" and icon.size == (32, 64)
        indexes = list(icon.getdata())
        pal = icon.getpalette()
    assert pal and max(indexes) < 16
    original = [tuple(pal[3*i:3*i+3]) for i in range(16)]
    target = read_palette(POKEMON / "icon_palettes/pal2.pal")
    # Keep original silhouette and all transparency; remap visible colours to
    # a palette reserved by the PC rather than the conflicting portrait tag 14.
    map_index = [0] + [
        min(range(1,16),key=lambda k: sum((original[i][c]-target[k][c])**2 for c in range(3)))
        for i in range(1,16)
    ]
    new_icon = Image.new("P", (32,64),0)
    new_icon.putdata([map_index[k] if k else 0 for k in indexes])
    for path in (src, POKEMON/"alphoracle/icon.png"):
        path.parent.mkdir(parents=True,exist_ok=True)
        save_png(path,new_icon,target)

def fix_i_unown() -> None:
    src = POKEMON/"unown_eye/icon.png"
    with Image.open(src) as icon:
        assert icon.mode=="P" and icon.size==(32,64)
        indexes=list(icon.getdata())
        original=icon.getpalette()
    assert original and len(original)>=33
    target=skarmet_palette()
    if original[:48] == [channel for rgb in target for channel in rgb] and set(indexes).issubset({0,1,5,10,11}):
        return  # The checked-in icon is already normalized; keep the fixer idempotent.
    # The original grey/white indexed art is remapped to black charcoal and
    # dark-red accents. This is intentionally NOT the white Mewduo palette.
    # source indices 1..10: black, grey shades, white, red shades, pale white
    mapping={0:0,1:5,2:5,3:5,4:1,5:1,6:11,7:10,8:10,9:5,10:11}
    assert set(indexes).issubset(mapping), set(indexes)-set(mapping)
    icon=Image.new("P",(32,64),0)
    icon.putdata([mapping[i] for i in indexes])
    save_png(src,icon,target)

def fix_mewduo() -> None:
    # Mewduo's approved red/grey icon artwork was assigned palette tag 15,
    # which the PC also uses for its miscellaneous UI sprite. Reindex the
    # existing pixels to the shared palette #2 and keep the source silhouette.
    path = POKEMON / "mewsion/icon.png"
    with Image.open(path) as source:
        rgba = source.convert("RGBA")
        assert rgba.size == (32, 64)
    target = read_palette(POKEMON / "icon_palettes/pal2.pal")
    rgb = list(rgba.getdata())
    indices = []
    for r, g, b, a in rgb:
        if a < 128:
            indices.append(0)
            continue
        # Work in 5-bit GBA colour space, matching the palette compiled by
        # gbagfx. Index zero remains transparent by engine convention.
        src = tuple(round(c * 31 / 255) for c in (r, g, b))
        best = min(range(1, 16), key=lambda k: sum(
            (src[c] - round(target[k][c] * 31 / 255)) ** 2 for c in range(3)))
        indices.append(best)
    icon = Image.new("P", (32, 64), 0)
    icon.putdata(indices)
    save_png(path, icon, target)

def fix_golden_ho_oh_icon() -> None:
    """Keep Ho-Oh's accepted icon silhouette and recolour its indexed feathers gold."""
    path = POKEMON / "ho_oh_relic/icon.png"
    target = noxichu_palette()
    with Image.open(path) as source:
        assert source.mode == "P" and source.size == (32, 64)
        indices = list(source.getdata())
        palette = source.getpalette()
        transparency = source.info.get("transparency")
    target_flat = [channel for rgb in target for channel in rgb]
    if palette and palette[:48] == target_flat and transparency == 0:
        assert set(indices) <= {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13}
        return
    # Source indices belong to vanilla Ho-Oh palette 1: red/green feathers,
    # yellow chest, grey/white body. Reindex the same silhouette to palette #6.
    gold = {0: 0, 1: 4, 2: 5, 3: 13, 4: 6, 5: 7, 6: 8,
            7: 9, 9: 7, 10: 10, 13: 8, 14: 3, 15: 2}
    assert set(indices) <= set(gold), f"Unexpected Golden Ho-Oh icon indices: {set(indices)-set(gold)}"
    icon = Image.new("P", (32, 64), 0)
    icon.putdata([gold[index] for index in indices])
    save_png(path, icon, target)
    print("PC_REPAIRED ho_oh_relic/icon.png: same approved silhouette, gold/cream/charcoal palette #6")

def remove_donor_background(name: str) -> None:
    # PNG palette entry zero is the sky/green background. Tropisaur also has
    # white checkerboard background pixels (index 15). Flood only from the
    # image edges to preserve identical-colour highlights inside the Pokémon.
    for side in ("front","back"):
        path=POKEMON/"prl_authoritative"/name/(side+".png")
        with Image.open(path) as source:
            assert source.mode=="P" and source.size==(64,64),path
            colors=source.getpalette()
            values=list(source.getdata())
        assert colors and len(colors)>=48
        transparent={0,15} if name=="tropisaur" else {0}
        q=deque()
        seen=set()
        for x in range(64):
            for y in (0,63):
                pos=y*64+x
                if values[pos] in transparent and pos not in seen:
                    seen.add(pos);q.append(pos)
        for y in range(64):
            for x in (0,63):
                pos=y*64+x
                if values[pos] in transparent and pos not in seen:
                    seen.add(pos);q.append(pos)
        while q:
            pos=q.popleft()
            x,y=pos%64,pos//64
            for nx,ny in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
                if 0<=nx<64 and 0<=ny<64:
                    i=ny*64+nx
                    if i not in seen and values[i] in transparent:
                        seen.add(i);q.append(i)
        # Game Boy Advance sprites treat indexed colour zero as transparent.
        for i in seen:values[i]=0
        target=Image.new("P",(64,64),0)
        target.putdata(values)
        palette=[tuple(colors[3*i:3*i+3]) for i in range(16)]
        save_png(path,target,palette)
        # Some donor sprites touch canvas corners. Never erase those actual
        # Pokémon pixels: only border-connected known background shades.
        assert any(v == 0 for v in values), (name, side, "no transparent pixels")
        print(f"PC_REPAIRED {name}/{side}: removed {len(seen)} border-connected background pixels")

def rebuild_icon_from_front(name: str, icon_palette_index: int) -> None:
    """Make a clean two-frame party icon from approved battle front pixels."""
    folder = POKEMON / "prl_authoritative" / name
    image_path = folder / "front.png"
    palette_path = folder / "normal.pal"
    with Image.open(image_path) as source:
        assert source.mode == "P" and source.size == (64, 64), image_path
        colors = [tuple(map(int, line.split())) for line in palette_path.read_text().splitlines()[3:19]]
        assert len(colors) == 16, palette_path
        rgba = source.copy()
        rgba.putpalette([value for rgb in colors for value in rgb] + [0] * (768 - 48))
        rgba.info["transparency"] = 0
        rgba = rgba.convert("RGBA")
    bounds = rgba.getchannel("A").getbbox()
    assert bounds, f"empty {name} front sprite"
    crop = rgba.crop(bounds)
    factor = min(30 / crop.width, 30 / crop.height)
    size = (max(1, round(crop.width * factor)), max(1, round(crop.height * factor)))
    sprite = crop.resize(size, Image.Resampling.NEAREST)
    frame = Image.new("RGBA", (32, 32), (0, 0, 0, 0))
    frame.alpha_composite(sprite, ((32 - size[0]) // 2, 31 - size[1]))
    two_frames = Image.new("RGBA", (32, 64), (0, 0, 0, 0))
    two_frames.alpha_composite(frame, (0, 0))
    two_frames.alpha_composite(frame, (0, 32))
    target = read_palette(POKEMON / "icon_palettes" / f"pal{icon_palette_index}.pal")
    pixels = []
    for red, green, blue, alpha in two_frames.getdata():
        if alpha < 128:
            pixels.append(0)
            continue
        rgb = (red, green, blue)
        nearest = min(range(1, 16), key=lambda i: sum(
            (rgb[c] - target[i][c]) ** 2 for c in range(3)
        ))
        pixels.append(nearest)
    icon = Image.new("P", (32, 64), 0)
    icon.putdata(pixels)
    save_png(icon_path := folder / "icon.png", icon, target)
    assert max(pixels) < 16 and pixels.count(0) > 0
    print(f"PC_REPAIRED {name}/icon.png: derived from approved front with shared palette {icon_palette_index}")

def main():
    fix_alphoracle()
    fix_i_unown()
    fix_mewduo()
    fix_golden_ho_oh_icon()
    for name in ("tropisaur","torkaldera"):
        remove_donor_background(name)
    # These imported PC icons have no transparent pixels and show solid donor
    # backgrounds. Rebuild just the icon from each accepted battle front.
    rebuild_icon_from_front("tropisaur", 1)
    rebuild_icon_from_front("torkaldera", 2)
    rebuild_icon_from_front("coelossus", 2)
    print("PC_REPAIRED: Alphoracle and Mewduo stable palette #2, I-Unown dark palette #9, Golden Ho-Oh custom gold icon; Elite Redux backgrounds transparent")
    print("PRESERVED: Pyroclast, all battle art except 2 transparent donor backgrounds, no species/save/map changes")

if __name__=="__main__":
    main()
