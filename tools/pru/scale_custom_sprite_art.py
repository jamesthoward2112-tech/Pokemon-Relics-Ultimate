#!/usr/bin/env python3
"""Reduce custom Eeveelution art and normalize the reported party icon palettes.

Only existing indexed pixels are resampled; no artwork or shiny colours are
invented. Battle sprites remain 64x64 and animated icons remain 32x64.
"""
from __future__ import annotations

from pathlib import Path
from PIL import Image, PngImagePlugin
import json
import re

ROOT = Path(__file__).resolve().parents[2]
GFX = ROOT / "graphics/pokemon"
EEVEELUTIONS = (
    "champeon", "lepideon", "guardeon", "obsideon", "toxeon",
    "sphynxeon", "omeon", "drakeon", "eeveeon", "nimbeon",
)
ICON_REDUCE = EEVEELUTIONS


def palette(path: Path) -> list[tuple[int, int, int]]:
    lines = path.read_text().splitlines()
    assert lines[:3] == ["JASC-PAL", "0100", "16"], path
    result = [tuple(map(int, line.split())) for line in lines[3:19]]
    assert len(result) == 16
    return result


def save_indexed(path: Path, image: Image.Image, colors: list[tuple[int, int, int]], *, tags: dict[str, str] | None = None) -> None:
    image.putpalette([c for rgb in colors for c in rgb] + [0] * (768 - 3 * len(colors)))
    image.info["transparency"] = 0
    meta = PngImagePlugin.PngInfo()
    for key, value in (tags or {}).items():
        meta.add_text(key, value)
    image.save(path, optimize=False, pnginfo=meta)


def scale_frames(path: Path, *, frame_height: int, scale: float = 0.8) -> None:
    with Image.open(path) as source:
        assert source.mode == "P" and source.info.get("transparency") in (None, 0), (path, source.mode, source.info)
        width, height = source.size
        assert height % frame_height == 0, (path, source.size, frame_height)
        if source.info.get("PRU_SPRITE_SCALE") == "80%":
            return
        colors = [tuple(source.getpalette()[3*i:3*i+3]) for i in range(16)]
        frames = [source.crop((0, y, width, y + frame_height)) for y in range(0, height, frame_height)]
        marker = {key: str(value) for key, value in source.info.items() if key.startswith("PRU_")}
    out = Image.new("P", (width, height), 0)
    out.putpalette([c for rgb in colors for c in rgb] + [0] * (768 - 3 * len(colors)))
    pixels = [0] * (width * height)
    scaled_w = round(width * scale)
    scaled_h = round(frame_height * scale)
    for frame_index, frame in enumerate(frames):
        resized = frame.resize((scaled_w, scaled_h), Image.Resampling.NEAREST)
        xoff = (width - scaled_w) // 2
        yoff = (frame_height - scaled_h) // 2
        values = list(resized.getdata())
        for y in range(scaled_h):
            for x in range(scaled_w):
                value = values[y * scaled_w + x]
                if value:
                    pixels[(frame_index * frame_height + yoff + y) * width + xoff + x] = value
    out.putdata(pixels)
    save_indexed(path, out, colors, tags={**marker, "PRU_SPRITE_SCALE": "80%"})


def normalize_nimbeon_icon() -> None:
    path = GFX / "nimbeon/icon.png"
    target = palette(GFX / "icon_palettes/pal3.pal")
    with Image.open(path) as source:
        if source.info.get("PRU_ICON_PALETTE") == "3":
            return
        assert source.mode == "P" and source.size == (32, 64) and source.info.get("transparency") == 0
        old_palette = source.getpalette()
        assert old_palette and len(old_palette) >= 48
        old_colors = [tuple(old_palette[3*i:3*i+3]) for i in range(16)]
        pixels = list(source.getdata())
    lookup = {0: 0}
    for index in range(1, 16):
        rgb = old_colors[index]
        lookup[index] = min(range(1, 16), key=lambda k: sum((rgb[c] - target[k][c]) ** 2 for c in range(3)))
    icon = Image.new("P", (32, 64), 0)
    icon.putdata([lookup[i] if i else 0 for i in pixels])
    save_indexed(path, icon, target, tags={"PRU_ICON_PALETTE": "3"})


def rebuild_nimbeon_icon_from_front() -> None:
    """Use Nimbeon's approved front art for its party icon at the same 80% scale."""
    front_path = GFX / "prl_authoritative/nimbeon/front.png"
    icon_path = GFX / "nimbeon/icon.png"
    target = palette(GFX / "icon_palettes/pal3.pal")
    with Image.open(front_path) as source:
        assert source.mode == "P" and source.size == (64, 64) and source.info.get("transparency") == 0
        source.load()
        colors = [tuple(source.getpalette()[3*i:3*i+3]) for i in range(16)]
        pix = list(source.getdata())
    bbox = Image.frombytes("L", (64, 64), bytes(255 if value else 0 for value in pix)).getbbox()
    assert bbox is not None
    crop = Image.new("P", (64, 64), 0)
    crop.putpalette([c for rgb in colors for c in rgb] + [0] * (768 - 3 * len(colors)))
    crop.putdata(pix)
    crop = crop.crop(bbox)
    max_size = round(32 * 0.8)
    scale = min(max_size / crop.width, max_size / crop.height)
    size = (max(1, round(crop.width * scale)), max(1, round(crop.height * scale)))
    crop = crop.resize(size, Image.Resampling.NEAREST)
    lookup = {0: 0}
    for index in range(1, 16):
        rgb = colors[index]
        lookup[index] = min(
            range(1, 16),
            key=lambda candidate: sum((rgb[c] - target[candidate][c]) ** 2 for c in range(3)),
        )
    mapped = [lookup[value] if value else 0 for value in crop.getdata()]
    frame = Image.new("P", (32, 32), 0)
    frame.putpalette([c for rgb in target for c in rgb] + [0] * (768 - 3 * len(target)))
    layer = Image.new("P", size, 0)
    layer.putpalette(frame.getpalette())
    layer.putdata(mapped)
    frame.paste(layer, ((32 - size[0]) // 2, 31 - size[1]))
    sheet = Image.new("P", (32, 64), 0)
    sheet.putpalette(frame.getpalette())
    sheet.paste(frame, (0, 0))
    sheet.paste(frame, (0, 32))
    save_indexed(icon_path, sheet, target, tags={
        "PRU_ICON_PALETTE": "3", "PRU_ICON_SOURCE": "approved-front-80%",
        "PRU_SPRITE_SCALE": "80%",
    })


def main() -> None:
    normalize_nimbeon_icon()
    # The headers point battle sprites at the pinned PRL-authoritative folders.
    for name in EEVEELUTIONS:
        folder = GFX / "prl_authoritative" / name
        for side in ("front", "back"):
            scale_frames(folder / f"{side}.png", frame_height=64)
        # These party icon PNGs are the normalized assets referenced by the
        # graphics headers. Scale each 32x32 animation frame independently.
        scale_frames(GFX / name / "icon.png", frame_height=32)

    rebuild_nimbeon_icon_from_front()
    # Document the intentional, compatible palette choices at the species data.
    family = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
    pru = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()
    assert re.search(r'iconPalIndex = 5, // PRU Mootiny icon is indexed for the warm palette #5', family)
    assert re.search(r'gMonIcon_Miltitan, 0, sMiltitanLevelUpLearnset', family)
    nimbeon = pru.split("[SPECIES_NIMBEON] =", 1)[1].split("\n},", 1)[0]
    assert ".iconPalIndex = 3," in nimbeon
    audit_path = ROOT / "PRU-QA/infinity-sprite-cleanup.json"
    if audit_path.is_file():
        audit = json.loads(audit_path.read_text())
        audit["eeveelution_art_scale"] = "80% of the original canvas, centered, nearest-neighbour"
        audit["preserved"] = [item for item in audit.get("preserved", []) if item != "original sprite scale"]
        audit["preserved"].append("original approved indexed pixels, transparency, and palettes")
        audit_path.write_text(json.dumps(audit, indent=2) + "\n")
    print("SPRITE_SCALE: 10 custom Eeveelutions front/back and icons at 80%")
    print("ICON_PALETTES: Nimbeon #3; Miltitan #0, Mootiny #5")


if __name__ == "__main__":
    main()
