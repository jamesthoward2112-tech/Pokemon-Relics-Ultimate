#!/usr/bin/env python3
"""Verify Khang/Alphoracle PC icon indexed palettes and final ability."""

from pathlib import Path
import re
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
code = (ROOT / "src/pokemon_icon.c").read_text()
species = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()

def palette(symbol):
    found = re.search(r"static const u16 " + symbol + r"\[16\]\s*=\s*\{(.*?)\};", code, re.S)
    assert found, symbol
    return [tuple(map(int, rgb)) for rgb in re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", found.group(1))]

def donor_palette(name):
    with Image.open(ROOT / "graphics/pokemon/prl_authoritative" / name / "icon.png") as im:
        assert im.mode == "P" and im.size == (32, 64)
        src = im.getpalette()[:48]
    return [tuple(round(v * 31 / 255) for v in src[i:i + 3]) for i in range(0, 48, 3)]

# Khang can reuse Articuno-P's slot because these two exact 4bpp palettes are identical.
assert palette("sPRUArticunoPIconPalette") == donor_palette("khang")
assert "{ sPRUArticunoPIconPalette, POKE_ICON_BASE_PAL_TAG + 11 }" in code
assert re.search(r"if \(species == SPECIES_KHANG\)\s*return 11;", code)
assert "gMonIcon_Khang" in species

# Alphoracle uses its genuine PRL sprite and its own colours; not shared palette zero.
with Image.open(ROOT / "graphics/pokemon/alphoracle/icon.png") as icon, Image.open(ROOT / "graphics/pokemon/prl_authoritative/alphoracle/icon.png") as donor:
    assert icon.mode == donor.mode == "P" and icon.size == donor.size == (32, 64)
    assert icon.tobytes() == donor.tobytes()
assert palette("sPRUAlphoracleIconPalette") == donor_palette("alphoracle")
assert "{ sPRUAlphoracleIconPalette, POKE_ICON_BASE_PAL_TAG + 14 }" in code
assert re.search(r"if \(species == SPECIES_ALPHORACLE\)\s*return 14;", code)
block = species.split("[SPECIES_ALPHORACLE] =", 1)[1].split("[SPECIES_PINSIREX]", 1)[0]
assert "ABILITY_MAGIC_BOUNCE" in block
assert "ABILITY_FULL_METAL_BODY" not in block
print("PASS: Khang and Alphoracle use correct PRL PC icon palettes; Alphoracle uses Magic Bounce")
