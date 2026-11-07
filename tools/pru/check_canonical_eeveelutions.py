#!/usr/bin/env python3
"""PRU/HNS whitelist evolution and easy-to-use Eeveelution source checks.

The underlying multi-generation engine keeps species declarations for donors and
approved special cases. Only canonical 450 targets may evolve in PRU/HNS.
No other game variant may gain these PRU-only Eevee/item behavior changes.
"""
from pathlib import Path
import csv
import re

root = Path(__file__).resolve().parents[2]
read = lambda p: (root / p).read_text(encoding="utf-8")
rows = list(csv.DictReader(open(root / "data/pru/PRU_National_Pokedex_2026-10-16.csv", encoding="utf-8-sig", newline="")))
assert len(rows) == 450
canonical = {row["Species_Constant"] for row in rows}
dex = read("src/data/pokemon/pru_dex_order.h")
assert "#define PRU_DEX_COUNT 450" in dex
assert len(re.findall(r"^\s*SPECIES_[A-Z0-9_]+,\s*//\s*\d{3}\s", dex, re.M)) == 450
assert "SPECIES_LUVDISC" not in canonical and "SPECIES_SYLVEON" in canonical

pokemon = read("src/pokemon.c")
assert '#include "data/pokemon/pru_dex_order.h"' in pokemon
assert "static bool32 IsPruApprovedEvolutionTarget(u32 species)" in pokemon
helper = pokemon.split("static bool32 IsPruApprovedEvolutionTarget(u32 species)", 1)[1].split("\n}",1)[0]
assert "if (!IS_HNS)" in helper and "sPruDexSpecies[i] == species" in helper
method = pokemon.split("u32 GetEvolutionTargetSpecies(struct Pokemon *mon,",1)[1].split("\n}\n",1)[0]
guard = "!IsPruApprovedEvolutionTarget(evolutions[i].targetSpecies)"
assert method.count(guard) == 6, f"Only {method.count(guard)}/6 modes block non-canon evolutions"
assert "if (targetSpecies != SPECIES_NONE && !IsPruApprovedEvolutionTarget(targetSpecies))" in method

source = read("src/data/pokemon/species_info/gen_1_families.h")
eevee = source.split("[SPECIES_EEVEE] =", 1)[1].split("\n    },",1)[0]
assert "#if IS_HNS" in eevee and "#else" in eevee
hns = eevee.split("#if IS_HNS",1)[1].split("#else",1)[0]
legacy = eevee.split("#else",1)[1].split("#endif",1)[0]
assert "FRIENDSHIP" not in hns and "EVO_LEVEL" not in hns
assert "EVO_LEVEL" in legacy, "Legacy/other game variants must keep donor Evo paths"
routes = re.findall(r"\{\s*EVO_ITEM,\s*(ITEM_[A-Z0-9_]+),\s*(SPECIES_[A-Z0-9_]+)\s*\}", hns)
expected = [
    ("ITEM_WATER_STONE", "SPECIES_VAPOREON"),
    ("ITEM_THUNDER_STONE", "SPECIES_JOLTEON"),
    ("ITEM_FIRE_STONE", "SPECIES_FLAREON"),
    ("ITEM_SUN_STONE", "SPECIES_ESPEON"),
    ("ITEM_MOON_STONE", "SPECIES_UMBREON"),
    ("ITEM_ANCIENT_STONE", "SPECIES_EEVEEON"),
    ("ITEM_SHINY_STONE", "SPECIES_NIMBEON"),
    ("ITEM_LEAF_STONE", "SPECIES_LEAFEON"),
    ("ITEM_ICE_STONE", "SPECIES_GLACEON"),
    ("ITEM_DAWN_STONE", "SPECIES_SYLVEON"),
    ("ITEM_DUSK_STONE", "SPECIES_OMEON"),
    ("ITEM_EXPERT_BELT", "SPECIES_CHAMPEON"),
    ("ITEM_SILVER_POWDER", "SPECIES_LEPIDEON"),
    ("ITEM_SOFT_SAND", "SPECIES_SPHYNXEON"),
    ("ITEM_METAL_COAT", "SPECIES_GUARDEON"),
    ("ITEM_HARD_STONE", "SPECIES_OBSIDEON"),
    ("ITEM_POISON_BARB", "SPECIES_TOXEON"),
    ("ITEM_DRAGON_FANG", "SPECIES_DRAKEON"),
]
assert routes == expected, f"PRU Eevee routes differ: {routes}"
assert len(set(item for item, _ in routes)) == len(routes)
assert all(species in canonical for _, species in routes)

items = read("src/data/items.h")
shop = read("data/maps/GoldenrodCity_DepartmentStore_2F_hns/scripts.inc")
for item, species in routes:
    if item == "ITEM_DAWN_STONE":
        ecruteak = read("data/maps/EcruteakCity_RockShop_hns/scripts.inc")
        advanced = ecruteak.split("EcruteakCity_RockShop_Advanced:", 1)[1].split("pokemartlistend", 1)[0]
        assert f".2byte {item}" in advanced, f"{item} unavailable after Fog Badge"
    else:
        assert f".2byte {item}" in shop, f"{item} unavailable at Goldenrod"
    row = items.split(f"[{item}] =",1)[1].split("\n    },",1)[0]
    assert "ItemUseOutOfBattle_EvolutionStone" in row, (item, "not directly usable")
    assert ".effect = gItemEffect_EvoItem" in row, (item, "missing use effect")
for item, _ in routes[11:]:
    row = items.split(f"[{item}] =",1)[1].split("\n    },",1)[0]
    assert "#if IS_HNS" in row, f"{item} must remain unchanged in non-PRU games"
    assert ".holdEffect =" in row, f"{item} lost its original held-item effect"

# Noxichu and the established relic split must not be affected by the Eevee simplification.
assert "{EVO_ITEM, ITEM_MOON_STONE, SPECIES_NOXICHU}" in source
assert "{EVO_ITEM, ITEM_THUNDER_STONE, SPECIES_RAICHU" in source
assert "{EVO_ITEM, ITEM_ANCIENT_STONE, SPECIES_CHARAXIS" in source

# Keep public names separate from stable internal species constants, evolutions and sprites.
# PRU's selected Infinity-era artwork remains unchanged (these are DISPLAY names only).
public_names = {
    "SPECIES_NIMBEON": "Aereon",
    "SPECIES_TOXEON": "Toxeon",
    "SPECIES_OMEON": "Obliveon",
    "SPECIES_OBSIDEON": "Pebleon",
    "SPECIES_EEVEEON": "Eeveeon",
    "SPECIES_SPHYNXEON": "Eartheon",
    "SPECIES_CHAMPEON": "Champeon",
    "SPECIES_GUARDEON": "Galveon",
    "SPECIES_LEPIDEON": "Moffeon",
    "SPECIES_DRAKEON": "Mytheon",
}
pjr_species = read("src/data/pokemon/species_info/pjr_families.h")
pru_species = read("src/data/pokemon/species_info/pru_custom.h")
expert = read("data/maps/EcruteakCity_RockShop_hns/scripts.inc")
dex_order = read("src/data/pokemon/pru_dex_order.h")
for species, public_name in public_names.items():
    species_constant = species.removeprefix("SPECIES_")
    if species in ("SPECIES_NIMBEON", "SPECIES_EEVEEON"):
        block = pru_species.split(f"[{species}] =", 1)[1].split("\\n},", 1)[0]
        assert f'.speciesName = _("{public_name}")' in block, (species, public_name)
    elif species == "SPECIES_DRAKEON":
        block = pjr_species.split(f"PJR_RED_SPECIES({species},", 1)[1].split("),", 1)[0]
        assert f'"{public_name}"' in block, (species, public_name)
    else:
        block = pjr_species.split(f"[{species}] =", 1)[1].split("\\n},", 1)[0]
        assert f'.speciesName = _("{public_name}")' in block, (species, public_name)
    dex_line = re.search(rf"^\\s*{species},\\s*//\\s*\\d{{3}}\\s+(.+)$", dex_order, re.M)
    assert dex_line and dex_line.group(1) == public_name, (species, "Dex display label")
    assert public_name.upper() in expert, (species, "Ecruteak Eeveelution Expert")
# Khang / Nolax typings were already present on PR75; prevent future regressions.
assert "PJR_RED_SPECIES(SPECIES_KHANG, 105, 105, 95, 50, 90, 110, TYPE_NORMAL, TYPE_FIGHTING," in pjr_species
assert "PJR_RED_SPECIES(SPECIES_NOLAX, 100, 130, 80, 45, 90, 130, TYPE_NORMAL, TYPE_DARK," in pjr_species
print("PASS: all ten public Eeveelution display names, Dex order and Expert dialogue agree")
print("PASS: Khang Normal/Fighting and Nolax Normal/Dark retained")

print("PASS: all 450 canonical evolution targets are whitelisted in 6 active evolution modes")
print("PASS: all 18 approved Eeveelutions use exactly one direct-use item")
print("PASS: all seven alternate-item catalysts retain their original held effects and non-PRU behavior")
print("PASS: Pikachu Moon/Thunder and Charaxis/Ancient Stone evolutions preserved")
