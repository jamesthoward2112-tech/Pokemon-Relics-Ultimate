#!/usr/bin/env python3
"""Guard the custom Gold/cream Ho-Oh PC and party icon palette."""
from pathlib import Path
import re
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
code = (ROOT / "src/pokemon_icon.c").read_text()
species = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
assert re.search(r"if \(species == SPECIES_RELIC_HO_OH\)\s*return 6;", code)
assert "{ sPRLNoxichuIconPalette, POKE_ICON_BASE_PAL_TAG + 6 }" in code
block = species.split("[SPECIES_RELIC_HO_OH] =", 1)[1].split("[SPECIES_", 1)[0]
assert ".iconSprite = gMonIcon_HoOhRelic" in block and ".iconPalIndex = 1" in block
palette_match = re.search(r"static const u16 sPRLNoxichuIconPalette\[16\]\s*=\s*\{(.*?)\};", code, re.S)
assert palette_match
palette = [tuple(map(int, row)) for row in re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", palette_match.group(1))]
assert len(palette) == 16
with Image.open(ROOT / "graphics/pokemon/ho_oh_relic/icon.png") as icon:
    assert icon.mode == "P" and icon.size == (32, 64) and icon.info.get("transparency") == 0
    used = set(icon.getdata())
    assert 0 in used and used <= {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13}, used
    colors = [palette[index] for index in used - {0}]
    assert any(r >= 25 and g >= 15 and b <= 12 for r, g, b in colors), "missing gold feather colours"
    assert all(not (g > r + 2 and g > b + 2) for r, g, b in colors), "green tint remains"
    assert all(not (r > g + 14 and r > b + 10) for r, g, b in colors), "red tint remains"
print("PASS: Golden Ho-Oh keeps the custom silhouette and uses only gold, cream and charcoal icon colours")
