#!/usr/bin/env python3
"""Focused source regression for Sylveon and the canonical PRU Pokédex."""
import csv
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def read(path):
    return (ROOT / path).read_text(encoding="utf-8")

with (ROOT / "data/pru/PRU_National_Pokedex_2026-10-16.csv").open(encoding="utf-8-sig", newline="") as f:
    rows = list(csv.DictReader(f))
assert len(rows) == 450
assert [int(row["PRU_No"]) for row in rows] == list(range(1, 451))
species = [row["Species_Constant"] for row in rows]
assert len(set(species)) == 450
assert species.count("SPECIES_SYLVEON") == 1
assert "SPECIES_LUVDISC" not in species
names = [row["Name"] for row in rows]
assert names[166:187] == [
    "Eevee", "Eeveeon", "Aereon", "Champeon", "Moffeon", "Eartheon",
    "Galveon", "Pebleon", "Toxeon", "Obliveon", "Mytheon", "Vaporeon",
    "Jolteon", "Flareon", "Espeon", "Umbreon", "Leafeon", "Glaceon",
    "Sylveon", "Porygon", "Porygon2",
]

order = read("src/data/pokemon/pru_dex_order.h")
listed = [(m.group(1), int(m.group(2))) for m in re.finditer(r"^\s*(SPECIES_[A-Z0-9_]+),\s*//\s*(\d{3})\b", order, re.M)]
assert len(listed) == 450 and listed == list(zip(species, range(1, 451)))
assert order.count("SPECIES_SYLVEON") == 1 and "SPECIES_LUVDISC" not in order

# Keep both internal IDs stable; display numbers never become species IDs.
constants = read("include/constants/species.h")
assert re.search(r"^#define SPECIES_LUVDISC\s+370\s*$", constants, re.M)
assert re.search(r"^#define SPECIES_SYLVEON\s+700\s*$", constants, re.M)

families = read("src/data/pokemon/species_info/gen_1_families.h")
eevee = families.split("[SPECIES_EEVEE] =", 1)[1].split("\n    },", 1)[0]
hns = eevee.split("#if IS_HNS", 1)[1].split("#else", 1)[0]
routes = re.findall(r"\{EVO_ITEM,\s*(ITEM_[A-Z0-9_]+),\s*(SPECIES_[A-Z0-9_]+)\}", hns)
assert len(routes) == 18 and len(set(routes)) == 18
assert ("ITEM_DAWN_STONE", "SPECIES_SYLVEON") in routes
assert all(target in set(species) for _, target in routes)
assert {target for _, target in routes} <= set(species)
assert "ITEM_SHINY_STONE, SPECIES_SYLVEON" not in hns

shop = read("data/maps/EcruteakCity_RockShop_hns/scripts.inc")
assert ".2byte ITEM_DAWN_STONE" in shop
assert "goto_if_set FLAG_BADGE04_GET, EcruteakCity_RockShop_EventScript_ClerkAdvanced" in shop
advanced = shop.split("EcruteakCity_RockShop_Advanced:", 1)[1].split("pokemartlistend", 1)[0]
assert ".2byte ITEM_DAWN_STONE" in advanced
guide = shop.split("EcruteakCity_RockShop_Text_ExpertGreeting:", 1)[1].split("EcruteakCity_RockShop_Text_Collector:", 1)[0]
assert "all 18 of" in guide
assert "DAWN STONE: SYLVEON" in guide
assert "after the FOG BADGE" in guide
for line in re.findall(r'\.string "([^"$]*)', guide):
    assert len(line.replace("\\n", "")) <= 36, line

# Save flags are based on immutable species National Dex values, not PRU rows.
pokedex = read("src/pokedex.c")
pokemon = read("src/pokemon.c")
assert "return gSpeciesInfo[species].natDexNum;" in pokemon.split("enum NationalDexOrder SpeciesToNationalPokedexNum", 1)[1].split("\n}", 1)[0]
flag_fn = pokedex.split("s8 GetSetPokedexFlag(enum NationalDexOrder nationalDexNo", 1)[1].split("\nu16 GetNationalPokedexCount", 1)[0]
assert "nationalDexNo--;" in flag_fn and "gSaveBlock1Ptr->dexSeen[index]" in flag_fn
assert "gSaveBlock1Ptr->dexCaught[index]" in flag_fn

# HNS species acquisition surfaces do not offer Luvdisc. Vanilla encounter data
# and species/egg records remain for existing saves and other game variants.
wild = json.loads(read("src/data/wild_encounters.json"))
for group in wild["wild_encounter_groups"]:
    for encounter in group.get("encounters", []):
        if encounter.get("map", "").endswith("_HNS"):
            assert all(mon["species"] != "SPECIES_LUVDISC"
                       for area in encounter.values() if isinstance(area, dict)
                       for mon in area.get("mons", [])), encounter.get("map")
for path in (ROOT / "data/maps").glob("*_hns/map.json"):
    assert "SPECIES_LUVDISC" not in path.read_text(encoding="utf-8"), path

randomizer = read("src/randomizer.c")
permitted = randomizer.split("static bool32 IsSpeciesPermitted(u16 species)", 1)[1].split("\n}", 1)[0]
assert "SpeciesToPokedexNum(species)" in permitted and "0xFFFF" in permitted
daycare = read("src/daycare.c")
compat = daycare.split("u8 GetDaycareCompatibilityScore(struct DayCare *daycare)", 1)[1].split("\n}", 1)[0]
assert "IS_HNS && SpeciesToPokedexNum(species[i]) == 0xFFFF" in compat
obtainable = read("include/constants/pokedex.h")
obtainable = obtainable.split("enum ObtainableDexOrder", 1)[1].split("#else", 1)[0]
assert "OBTAINABLE_DEX_LUVDISC" not in obtainable and "OBTAINABLE_DEX_SYLVEON" in obtainable
lookup = read("src/pokemon.c")
lookup = lookup.split("static const enum NationalDexOrder sObtainableToNationalOrder", 1)[1].split("#endif", 1)[0]
assert "OBTAINABLE_TO_NATIONAL(LUVDISC)" not in lookup

expert_test = read("test/test_pru_eeveelution_expert.py")
assert '"SPECIES_SYLVEON": "ITEM_DAWN_STONE"' in expert_test
assert "all 18 approved methods" in expert_test
print("Sylveon/450 PRU Dex source regression passed (roster, IDs, evolution, saves, expert and HNS availability).")
