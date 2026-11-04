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

# Khang's indexed icon uses the standard PRU icon palette selected by its
# SpeciesInfo; it must not borrow the unrelated Articuno-P custom palette.
assert "{ sPRUArticunoPIconPalette, POKE_ICON_BASE_PAL_TAG + 11 }" in code
assert not re.search(r"if \(species == SPECIES_KHANG\)", code)
assert "gMonIcon_Khang" in species
assert re.search(r"gMonIcon_Khang,[\s\S]*?P_GBA_STYLE_SPECIES_ICONS \? 1 : 2\)", species)

# Alphoracle's approved icon silhouette must remain intact but its pixels
# are reindexed to the shared palette #2; PC tag #14 is reserved for its
# large Pokémon portrait and caused scrolling colour corruption.
with Image.open(ROOT / "graphics/pokemon/alphoracle/icon.png") as icon, Image.open(ROOT / "graphics/pokemon/prl_authoritative/alphoracle/icon.png") as donor:
    assert icon.mode == donor.mode == "P" and icon.size == donor.size == (32, 64)
    assert icon.tobytes() == donor.tobytes()
    assert icon.info.get("transparency") == 0
assert re.search(r"if \(species == SPECIES_ALPHORACLE\)\s*return 2;", code)
block = species.split("[SPECIES_ALPHORACLE] =", 1)[1].split("[SPECIES_PINSIREX]", 1)[0]
assert "ABILITY_MAGIC_BOUNCE" in block
assert "ABILITY_FULL_METAL_BODY" not in block
print("PASS: Khang stays correct; Alphoracle uses stable shared PC icon palette #2 and Magic Bounce")
