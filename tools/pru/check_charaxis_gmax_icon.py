#!/usr/bin/env python3
"""Ensure Charaxis uses Mega Charizard X icon pixels recoloured black/orange."""
from pathlib import Path
import re
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
info = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
row = re.search(r"PJR_RED_SPECIES\(SPECIES_CHARAXIS,(.*?)\),", info, re.S)
assert row and row.group(1).strip().endswith("600, 0, 1, 6"), "Charaxis icon must use palette #6"
code = (ROOT / "src/pokemon_icon.c").read_text()
match = re.search(r"static const u16 sPRLNoxichuIconPalette\[16\]\s*=\s*\{(.*?)\};", code, re.S)
assert match and "{ sPRLNoxichuIconPalette, POKE_ICON_BASE_PAL_TAG + 6 }" in code
palette = [tuple(map(int, item)) for item in re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", match.group(1))]
assert len(palette) == 16
with Image.open(ROOT / "graphics/pokemon/prl_authoritative/charaxis/icon.png") as icon:
    assert icon.mode == "P" and icon.size == (32, 64) and icon.info.get("transparency") == 0
    indices = set(icon.getdata())
    assert indices <= set(range(16)) and 0 in indices and len(indices & set(range(1, 16))) >= 5
    actual = list(icon.getdata())
with Image.open(ROOT / "graphics/pokemon/charizard/mega_x/icon.png") as source:
    source_indices = list(source.getdata())
mapping = {0: 0, 1: 5, 2: 4, 3: 13, 6: 12, 8: 8, 9: 7, 12: 10, 14: 3, 15: 1}
assert set(source_indices) <= set(mapping)
assert actual == [mapping[index] for index in source_indices], "Charaxis party icon must retain Mega X silhouette/pixels"
colors_used = {palette[i] for i in indices if i}
assert any(max(c) <= 15 for c in colors_used), "Charaxis icon is missing near-black pixels"
assert any(c[0] >= 20 and c[1] >= 8 for c in colors_used), "Charaxis icon is missing ember pixels"
print("PASS: Charaxis party icon uses exact Mega Charizard X pixels, recoloured black/orange with palette #6")
