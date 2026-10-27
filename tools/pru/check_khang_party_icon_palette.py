#!/usr/bin/env python3
"""Verify Khang's party icon uses the exact indexed PRL donor palette."""

from pathlib import Path
import re

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
png = ROOT / "graphics/pokemon/prl_authoritative/khang/icon.png"
icon_code = (ROOT / "src/pokemon_icon.c").read_text()
species_code = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()

with Image.open(png) as icon:
    assert icon.mode == "P" and icon.size == (32, 64)
    png_palette = icon.getpalette()[:48]

block = re.search(r"sPRUArticunoPIconPalette\[16\]\s*=\s*\{(.*?)\};", icon_code, re.S)
assert block, "The existing PRU indexed icon palette must remain available"
actual = [tuple(map(int, rgb)) for rgb in re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", block.group(1))]
expected = [tuple(round(value * 31 / 255) for value in png_palette[i:i + 3]) for i in range(0, 48, 3)]
assert actual == expected, "Khang palette differs from the approved PRL icon PNG"
assert "{ sPRUArticunoPIconPalette, POKE_ICON_BASE_PAL_TAG + 11 }" in icon_code
assert re.search(r"if \(species == SPECIES_KHANG\)\s*return 11;", icon_code)
assert "gMonIcon_Khang" in species_code
print("PASS: Khang icon keeps original PRL sprite and exact 16-colour party palette without another OBJ palette slot")
