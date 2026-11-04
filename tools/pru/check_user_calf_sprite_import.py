#!/usr/bin/env python3
"""Verify the approved user Mootiny/Miltitan artwork and icon integration."""
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
GFX = ROOT / "graphics/pokemon"
SOURCE = ROOT / "assets/pru_user_calf_sprites"
PALETTES = {"miltitan": 0, "mootiny": 5}

for name, palette_id in PALETTES.items():
    source = SOURCE / name
    installed = GFX / "prl_authoritative" / name
    assert (installed / "front.png").read_bytes() == (source / "front.png").read_bytes(), name
    assert (installed / "normal.pal").read_bytes() == (source / "normal.pal").read_bytes(), name
    assert (installed / "shiny.pal").read_bytes() == (source / "normal.pal").read_bytes(), name
    with Image.open(installed / "front.png") as front, Image.open(installed / "back.png") as back:
        assert front.mode == back.mode == "P" and front.size == back.size == (64, 64)
        assert front.info.get("transparency") == back.info.get("transparency") == 0
        assert front.getpixel((0, 0)) == front.getpixel((63, 63)) == 0
        assert back.getpixel((0, 0)) == back.getpixel((63, 63)) == 0
        source_palette = [tuple(front.getpalette()[3*i:3*i+3]) for i in range(16)]
        output_palette = [tuple(back.getpalette()[3*i:3*i+3]) for i in range(16)]
        assert source_palette == output_palette, name
        assert max(front.getdata()) < 16 and max(back.getdata()) < 16
    icon_path = installed / "icon.png"
    with Image.open(icon_path) as icon:
        expected = [tuple(map(int, line.split())) for line in (GFX / "icon_palettes" / f"pal{palette_id}.pal").read_text().splitlines()[3:19]]
        actual = [tuple(icon.getpalette()[3*i:3*i+3]) for i in range(16)]
        assert icon.mode == "P" and icon.size == (32, 64)
        assert icon.info.get("transparency") == 0 and actual == expected
        assert list(icon.crop((0, 0, 32, 32)).getdata()) == list(icon.crop((0, 32, 32, 64)).getdata())
        assert any(icon.getdata()) and max(icon.getdata()) < 16
    print(f"PASS: {name} approved front/palette, retained back, and derived icon palette #{palette_id}")

print("PASS: shiny palettes are explicitly neutral copies until authentic art is supplied")
