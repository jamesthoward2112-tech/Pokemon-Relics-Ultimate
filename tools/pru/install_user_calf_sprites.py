#!/usr/bin/env python3
"""Install the user's approved Mootiny and Miltitan redraws after donor sync."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import shutil

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
GFX = ROOT / "graphics/pokemon"
SOURCE = ROOT / "assets/pru_user_calf_sprites"
ICON_PALETTE_IDS = {"miltitan": 0, "mootiny": 5}


def jasc(path: Path) -> list[tuple[int, int, int]]:
    lines = path.read_text().splitlines()
    assert lines[:3] == ["JASC-PAL", "0100", "16"], path
    colors = [tuple(map(int, line.split())) for line in lines[3:19]]
    assert len(colors) == 16 and all(len(c) == 3 for c in colors), path
    return colors


def save_indexed(path: Path, image: Image.Image, colors: list[tuple[int, int, int]]) -> None:
    image.putpalette([v for color in colors for v in color] + [0] * (768 - 3 * len(colors)))
    image.info["transparency"] = 0
    image.save(path, optimize=False)


def remap_back(back: Image.Image, old_palette: list[tuple[int, int, int]], new_palette: list[tuple[int, int, int]]) -> Image.Image:
    """Keep the existing back drawing legible with the new shared species palette."""
    pixels = list(back.getdata())
    lookup = {0: 0}
    for old_index in set(pixels) - {0}:
        rgb = old_palette[old_index]
        lookup[old_index] = min(
            range(1, 16),
            key=lambda index: sum((rgb[channel] - new_palette[index][channel]) ** 2 for channel in range(3)),
        )
    out = Image.new("P", back.size, 0)
    out.putdata([lookup.get(pixel, 0) for pixel in pixels])
    return out


def make_icon(front: Image.Image, front_palette: list[tuple[int, int, int]], icon_palette: list[tuple[int, int, int]]) -> Image.Image:
    """Build a faithful two-frame icon from the approved new front artwork."""
    bbox = front.getbbox()
    assert bbox is not None
    crop = front.crop(bbox)
    scale = min(30 / crop.width, 30 / crop.height)
    size = (max(1, round(crop.width * scale)), max(1, round(crop.height * scale)))
    crop = crop.resize(size, Image.Resampling.NEAREST)
    mapped = Image.new("P", crop.size, 0)
    mapped.putpalette([v for color in icon_palette for v in color] + [0] * (768 - 3 * len(icon_palette)))
    lookup = {0: 0}
    for index in range(1, 16):
        rgb = front_palette[index]
        lookup[index] = min(
            range(1, 16),
            key=lambda candidate: sum((rgb[channel] - icon_palette[candidate][channel]) ** 2 for channel in range(3)),
        )
    mapped.putdata([lookup.get(pixel, 0) for pixel in crop.getdata()])
    icon_frame = Image.new("P", (32, 32), 0)
    icon_frame.putpalette(mapped.getpalette())
    icon_frame.paste(mapped, ((32 - size[0]) // 2, 31 - size[1]))
    sheet = Image.new("P", (32, 64), 0)
    sheet.putpalette(icon_frame.getpalette())
    sheet.paste(icon_frame, (0, 0))
    sheet.paste(icon_frame, (0, 32))
    return sheet


def install(name: str) -> dict:
    source = SOURCE / name
    dest = GFX / "prl_authoritative" / name
    front_path, normal_path = source / "front.png", source / "normal.pal"
    with Image.open(front_path) as opened:
        assert opened.mode == "P" and opened.size == (64, 64), (name, opened.mode, opened.size)
        assert opened.info.get("transparency") == 0, (name, "front must use index 0 transparency")
        front = opened.copy()
        front_palette = [tuple(opened.getpalette()[3*i:3*i+3]) for i in range(16)]
    colors = jasc(normal_path)
    assert colors == front_palette, (name, "approved palette must exactly match the indexed front PNG")
    assert front.getpixel((0, 0)) == 0 and front.getpixel((63, 63)) == 0

    back_path = dest / "back.png"
    with Image.open(back_path) as old_back:
        assert old_back.mode == "P" and old_back.size == (64, 64)
        old_palette = jasc(dest / "normal.pal")
        back = remap_back(old_back.copy(), old_palette, colors)

    dest.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(front_path, dest / "front.png")
    save_indexed(back_path, back, colors)
    shutil.copyfile(normal_path, dest / "normal.pal")
    # The user provided no shiny art/palette. Identical colors avoid applying
    # the old drawing's palette to new index meanings or inventing a shiny.
    shutil.copyfile(normal_path, dest / "shiny.pal")

    icon_id = ICON_PALETTE_IDS[name]
    icon_colors = jasc(GFX / "icon_palettes" / f"pal{icon_id}.pal")
    icon = make_icon(front, front_palette, icon_colors)
    save_indexed(dest / "icon.png", icon, icon_colors)
    return {
        "species": name,
        "source": "user-provided GBA-ready artwork, 2026-11-04",
        "front_sha256": hashlib.sha256((dest / "front.png").read_bytes()).hexdigest(),
        "front_source_sha256": hashlib.sha256(front_path.read_bytes()).hexdigest(),
        "palette_sha256": hashlib.sha256(normal_path.read_bytes()).hexdigest(),
        "back": "existing approved drawing, remapped to new shared species palette by nearest RGB",
        "shiny": "no shiny supplied; normal palette reused without invented shiny colors",
        "icon": f"derived from approved front, shared party palette #{icon_id}",
    }


def main() -> None:
    entries = [install(name) for name in ("miltitan", "mootiny")]
    report = ROOT / "PRU-QA/user-calf-sprite-import.json"
    report.parent.mkdir(parents=True, exist_ok=True)
    report.write_text(json.dumps({"sprites": entries}, indent=2) + "\n")
    print("USER_CALF_ART: installed new Miltitan and Mootiny fronts; regenerated palette-matched icons")
    print("USER_CALF_ART: kept and recolored existing back views; shiny palette is neutral until source art is supplied")


if __name__ == "__main__":
    main()
