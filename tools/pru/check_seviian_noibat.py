#!/usr/bin/env python3
"""Verify the slot-preserving Radical Red Seviian Noibat family replacement."""
from __future__ import annotations

import csv
import hashlib
import json
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSETS = ROOT / "assets/pru_final_polish/seviian_noibat"

EXPECTED = {
    "noibat/front.png": "1aaf027cf0531936d8bf1ea908af78789dca6301d7013c4e24ecf2793478f36e",
    "noibat/back.png": "4db62e88e2e31e8f34ec4f5aa235914a14ef9837e9d461bd9d10a3ba58c62fe2",
    "noibat/icon.png": "856169e2b6d1efd0912dfdef4645be9ac41c327e94b1f7ddb6593bdce6a36989",
    "noibat/normal.pal": "0c5a9bcb934693b125b8197d0fe867f277f0aaf0a01538285f7113c2b0517c99",
    "noibat/shiny.pal": "ca28a2c16ea95b43e7eb53f54e8cfa509fcc58cb7acd0f6ef20f75efa2deed5b",
    "noivern/front.png": "3fa148fe5c3b051020866a9654126e91c8be8fc83e0298868ae8f07f0f90a01f",
    "noivern/back.png": "ed7f3c47b0726b37089f0ae857794304cd1bdd91837899a38f76ccb2f9c4e288",
    "noivern/icon.png": "3fbc534080d2e0ecf0e923c46be39dd274be7079c1640d304eec371722803ec5",
    "noivern/normal.pal": "08fc98961f2d31a137ce6b08e79c81b72bcb33eedb1d4d89f306b61a46727f82",
    "noivern/shiny.pal": "e6bd800fcd1a728ec5366afa2b25aba4d4d199226d3914e2490e96060beb9768",
}
for relative, expected in EXPECTED.items():
    path = ASSETS / relative
    assert path.is_file(), f"missing authentic Radical Red donor: {relative}"
    assert hashlib.sha256(path.read_bytes()).hexdigest() == expected, relative

for species in ("noibat", "noivern"):
    folder = ROOT / "graphics/pokemon" / species
    for name, size in (("anim_front.png", (64, 128)), ("back.png", (64, 64)), ("icon.png", (32, 64))):
        with Image.open(folder / name) as image:
            image.load()
            assert image.mode == "P" and image.size == size, (species, name, image.mode, image.size)
            assert max(image.getdata()) < 16, (species, name)

info = (ROOT / "src/data/pokemon/species_info/gen_6_families.h").read_text()
noibat = info[info.index("[SPECIES_NOIBAT] ="):info.index("[SPECIES_NOIVERN] =")]
noivern = info[info.index("[SPECIES_NOIVERN] ="):info.index("#endif //P_FAMILY_NOIBAT")]
for block in (noibat, noivern):
    assert ".types = MON_TYPES(TYPE_ROCK, TYPE_GHOST)" in block
    assert ".abilities = { ABILITY_LEVITATE, ABILITY_ROCK_HEAD, ABILITY_STURDY }" in block
    assert ".iconPalIndex = 1" in block
assert all(value in noibat for value in (".baseHP        = 40", ".baseAttack    = 45", ".baseSpAttack  = 30"))
assert all(value in noivern for value in (".baseHP        = 85", ".baseAttack    = 102", ".baseSpAttack  = 70"))
assert "{EVO_LEVEL, 36, SPECIES_NOIVERN}" in noibat

learnsets = (ROOT / "src/data/pokemon/level_up_learnsets/gen_3.h").read_text()
assert "LEVEL_UP_MOVE(16, MOVE_SHADOW_SNEAK)" in learnsets
assert "LEVEL_UP_MOVE(23, MOVE_ROCK_BLAST)" in learnsets
assert "LEVEL_UP_MOVE(58, MOVE_POLTERGEIST)" in learnsets
assert "LEVEL_UP_MOVE(64, MOVE_HEAD_SMASH)" in learnsets

encounters = json.loads((ROOT / "src/data/wild_encounters.json").read_text())
south = [
    header for group in encounters["wild_encounter_groups"]
    for header in group["encounters"]
    if header.get("map") == "MAP_DARK_CAVE_SOUTH_SIDE_HNS"
]
assert south and any(
    mon["species"] == "SPECIES_NOIBAT"
    for header in south for mon in header["land_mons"]["mons"]
), "Seviian Noibat must be catchable in Dark Cave South Side"

with (ROOT / "data/pru/PRU_National_Pokedex_2026-10-16.csv").open(newline="") as handle:
    assert len(list(csv.DictReader(handle))) == 450
constants = (ROOT / "include/constants/species.h").read_text()
assert "SPECIES_NOIBAT_SEVII" not in constants and "SPECIES_NOIVERN_SEVII" not in constants

print("PASS: authentic RR 4.1 Seviian Noibat/Noivern front, back, icon and palettes")
print("PASS: Rock/Ghost family uses existing IDs, Lv36 evolution and Dark Cave South Side encounter")
