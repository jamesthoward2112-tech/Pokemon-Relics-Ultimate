#!/usr/bin/env python3
"""Guard the 80% custom Eeveelution sizing and corrected icon palettes."""
from pathlib import Path
import re
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
GFX = ROOT / "graphics/pokemon"
EEVEELUTIONS = (
    "champeon", "lepideon", "guardeon", "obsideon", "toxeon",
    "sphynxeon", "omeon", "drakeon", "eeveeon", "nimbeon",
)

def check(path: Path, expected_size: tuple[int, int]) -> None:
    with Image.open(path) as im:
        assert im.mode == "P" and im.size == expected_size, (path, im.mode, im.size)
        assert im.info.get("transparency") == 0, (path, "index 0 must remain transparent")
        assert im.info.get("PRU_SPRITE_SCALE") == "80%", (path, im.info)
        pixels = list(im.getdata())
        assert any(pixels), (path, "empty sprite")
        xs = [i % expected_size[0] for i, value in enumerate(pixels) if value]
        assert min(xs) >= (3 if expected_size[0] == 32 else 6)
        assert max(xs) <= (expected_size[0] - 4 if expected_size[0] == 32 else 57)

for name in EEVEELUTIONS:
    for side in ("front", "back"):
        check(GFX / "prl_authoritative" / name / f"{side}.png", (64, 64))
    check(GFX / name / "icon.png", (32, 64))
with Image.open(GFX / "nimbeon/icon.png") as icon:
    expected = [tuple(map(int, line.split())) for line in (GFX / "icon_palettes/pal3.pal").read_text().splitlines()[3:19]]
    actual = [tuple(icon.getpalette()[3*i:3*i+3]) for i in range(16)]
    assert icon.info.get("PRU_ICON_PALETTE") == "3"
    assert icon.info.get("PRU_ICON_SOURCE") == "approved-front-80%"
    assert actual == expected, "Nimbeon icon must be indexed against the shared sky/white icon palette"
pru = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()
nimbeon = pru.split("[SPECIES_NIMBEON] =", 1)[1].split("\n},", 1)[0]
assert ".iconPalIndex = 3," in nimbeon
family = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
mootiny = family.split("[SPECIES_MOOTINY] =", 1)[1].split("\n},", 1)[0]
assert ".iconPalIndex = 5, // PRU Mootiny icon is indexed for the warm palette #5." in mootiny
assert re.search(r'gMonIcon_Miltitan, 0, sMiltitanLevelUpLearnset', family)
print("PASS: custom Eeveelution battle sprites and icons are 80%; Nimbeon, Mootiny and Miltitan use aligned icon palettes")
