#!/usr/bin/env python3
"""Regression contract for the save-compatible Saffron Dojo Elite 20."""

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
read = lambda path: (ROOT / path).read_text()

constants = read("include/constants/opponents_hns.h")
parties = read("src/data/trainers_hns.party")
scripts = read("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
dojo = json.loads(read("data/maps/SaffronCity_FightingDojoVIP_hns/map.json"))
indigo = json.loads(read("data/maps/IndigoPlateau_PokemonCenter_hns/map.json"))
backgrounds = read("src/battle_bg.c")
setup = read("src/battle_setup.c")
transitions = read("src/battle_transition.c")
transition_ids = read("include/battle_transition.h")

# Old save-indexed pair IDs keep their numeric meanings.
for name, value in {
    "TRAINER_PRU_E18_17_A_HNS": 733,
    "TRAINER_PRU_E18_17_B_HNS": 734,
    "TRAINER_PRU_E18_18_A_HNS": 735,
    "TRAINER_PRU_E18_18_B_HNS": 736,
    "TRAINER_PRU_E18_17_A_MASTER_HNS": 769,
    "TRAINER_PRU_E18_17_B_MASTER_HNS": 770,
    "TRAINER_PRU_E18_18_A_MASTER_HNS": 771,
    "TRAINER_PRU_E18_18_B_MASTER_HNS": 772,
}.items():
    assert f"#define {name}" in constants and re.search(rf"#define {name}\s+{value}\b", constants)

new_ids = (
    "TRAINER_PRU_E20_JASMINE_HNS", "TRAINER_PRU_E20_CLAIR_HNS",
    "TRAINER_PRU_E20_STEVEN_HNS", "TRAINER_PRU_E20_MAY_HNS",
    "TRAINER_PRU_E20_RIVAL_HNS", "TRAINER_PRU_E20_GIOVANNI_HNS",
    "TRAINER_PRU_E20_JASMINE_MASTER_HNS", "TRAINER_PRU_E20_CLAIR_MASTER_HNS",
    "TRAINER_PRU_E20_STEVEN_MASTER_HNS", "TRAINER_PRU_E20_MAY_MASTER_HNS",
    "TRAINER_PRU_E20_RIVAL_MASTER_HNS", "TRAINER_PRU_E20_GIOVANNI_MASTER_HNS",
)
for name in new_ids:
    assert re.search(rf"#define {name}\s+(\d+)\b", constants), name

# The only attendant is physically in Saffron Dojo.
assert sum(o.get("script") == "PRU_Elite18_Steward" for o in dojo["object_events"]) == 1
assert all(o.get("script") != "PRU_Elite18_Steward" for o in indigo["object_events"])

round_pairs = [
    ("TRAINER_PRU_E18_01_A_HNS", "TRAINER_PRU_E18_01_B_HNS"),
    ("TRAINER_PRU_E18_02_A_HNS", "TRAINER_PRU_E18_02_B_HNS"),
    ("TRAINER_PRU_E18_03_A_HNS", "TRAINER_PRU_E18_03_B_HNS"),
    ("TRAINER_PRU_E18_04_A_HNS", "TRAINER_PRU_E18_04_B_HNS"),
    ("TRAINER_PRU_E18_05_A_HNS", "TRAINER_PRU_E18_05_B_HNS"),
    ("TRAINER_PRU_E18_06_A_HNS", "TRAINER_PRU_E18_06_B_HNS"),
    ("TRAINER_PRU_E18_07_A_HNS", "TRAINER_PRU_E18_07_B_HNS"),
    ("TRAINER_PRU_E20_JASMINE_HNS", "TRAINER_PRU_E20_CLAIR_HNS"),
    ("TRAINER_PRU_E18_09_A_HNS", "TRAINER_PRU_E18_09_B_HNS"),
    ("TRAINER_PRU_E18_10_A_HNS", "TRAINER_PRU_E18_10_B_HNS"),
    ("TRAINER_PRU_E18_11_A_HNS", "TRAINER_PRU_E18_11_B_HNS"),
    ("TRAINER_PRU_E18_12_A_HNS", "TRAINER_PRU_E18_12_B_HNS"),
    ("TRAINER_PRU_E18_13_A_HNS", "TRAINER_PRU_E18_13_B_HNS"),
    ("TRAINER_PRU_E18_14_A_HNS", "TRAINER_PRU_E18_14_B_HNS"),
    ("TRAINER_PRU_E18_15_A_HNS", "TRAINER_PRU_E18_15_B_HNS"),
    ("TRAINER_PRU_E18_08_A_HNS", "TRAINER_PRU_E18_08_B_HNS"),
    ("TRAINER_PRU_E20_STEVEN_HNS", "TRAINER_PRU_E20_MAY_HNS"),
    ("TRAINER_PRU_E20_RIVAL_HNS", "TRAINER_PRU_E20_GIOVANNI_HNS"),
    ("TRAINER_PRU_E18_17_A_HNS", "TRAINER_PRU_E18_17_B_HNS"),
    ("TRAINER_PRU_E18_18_A_HNS", "TRAINER_PRU_E18_18_B_HNS"),
]
for index, pair in enumerate(round_pairs, 1):
    block = scripts.split(f"PRU_Elite18_Round_{index:02d}::", 1)[1].split("\n\n", 1)[0]
    assert f"trainerbattle_two_trainers {pair[0]}" in block, (index, pair)
    assert pair[1] in block, (index, pair)

gauntlet = scripts.split("PRU_Elite18_Gauntlet::", 1)[1].split("PRU_Elite18_ChoosePair::", 1)[0]
assert [int(x) for x in re.findall(r"call PRU_Elite18_Round_(\d+)", gauntlet)] == list(range(1, 21))
assert "ELITE 20" in scripts and "SILVER and MAY" not in scripts

# New teams contain exactly three Pokémon; masters are all level 100.
def party_block(name):
    return parties.split(f"=== {name} ===", 1)[1].split("\n=== ", 1)[0]

for name in new_ids:
    block = party_block(name)
    assert len(re.findall(r"^Level:", block, re.M)) == 3, name
    if "MASTER" in name:
        assert set(re.findall(r"^Level: (\d+)$", block, re.M)) == {"100"}, name

assert "Steelix" in party_block("TRAINER_PRU_E20_JASMINE_HNS")
assert "Kingdra" in party_block("TRAINER_PRU_E20_CLAIR_HNS")
assert "Metagross" in party_block("TRAINER_PRU_E20_STEVEN_HNS")
assert "Name: {B_RIVAL_NAME}" in party_block("TRAINER_PRU_E20_RIVAL_HNS")
assert "Rhyperior" in party_block("TRAINER_PRU_E20_GIOVANNI_HNS")
assert "Mewtwo" not in party_block("TRAINER_PRU_E20_GIOVANNI_HNS")

assert "sPruElite20RhythmScenes[20]" in backgrounds
assert "{35, 48, 46, 34, 39, 19, 16, 45, 14, 8, 18, 38, 30, 42, 49, 54, 41, 36, 13, 0}" in backgrounds
assert "BATTLE_TYPE_TWO_OPPONENTS" in backgrounds

for token in ("B_TRANSITION_STEVEN_MAY", "B_TRANSITION_SILVER_GIOVANNI"):
    assert token in transition_ids and token in setup and token in transitions
for stem in ("steven_may", "silver_giovanni"):
    for ext in ("4bpp", "bin", "gbapal"):
        path = ROOT / f"graphics/battle_transitions/prl/{stem}.{ext}"
        assert path.is_file() and path.stat().st_size > 0, path

print("PASS: Saffron Dojo Elite 20 order, teams, master variants, scenes and entrances")
