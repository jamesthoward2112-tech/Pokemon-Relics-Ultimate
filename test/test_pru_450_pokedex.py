#!/usr/bin/env python3
"""PRU source regression: canonical HGSS 450-Dex, distinct flags, old saves.

Run manually in a complete repository checkout:
    python3 test/test_pru_450_pokedex.py

No ROM build is initiated. This is NOT gameplay or migration testing.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]

def source(path):
    return (ROOT / path).read_text(encoding="utf-8")

def require(value, message):
    if not value:
        raise AssertionError(message)

dex = source("src/data/pokemon/pru_dex_order.h")
hgss = source("src/pokedex_plus_hgss.c")
flags = source("src/pokedex.c")
pokemon = source("src/pokemon.c")
battle = source("src/battle_script_commands.c")
global_h = source("include/global.h")
interface = source("include/pokedex.h")
species_constants = source("include/constants/species.h")

entries = [
    (species, int(num))
    for species, num in re.findall(
        r"^\s*(SPECIES_[A-Z0-9_]+),\s*//\s*(\d{3})", dex, re.M
    )
]
require("#define PRU_DEX_COUNT 450" in dex, "Canonical Dex size changed")
require(len(entries) == 450, f"Expected 450 entries, got {len(entries)}")
require([num for _, num in entries] == list(range(1, 451)),
        "Canonical numbering has omissions, gaps or out-of-order indices")
require(len({species for species, _ in entries}) == 450,
        "Canonical Dex contains duplicate species")
require(all(re.search(r"^#define\s+" + re.escape(species) + r"\s+", species_constants, re.M)
            for species, _ in entries),
        "A canonical species constant does not exist")
orders = dict(entries)
for species, number in {
    "SPECIES_EDENSAUR": 4,
    "SPECIES_CHARIZARD": 7,
    "SPECIES_CHARAXIS": 8,
    "SPECIES_FORTOTOISE": 12,
    "SPECIES_LUGIA": 435,
    "SPECIES_ALPHORACLE": 437,
    "SPECIES_DEOXYS": 450,
}.items():
    require(orders.get(species) == number,
            f"Wrong PRU Dex position for {species}: {orders.get(species)}")

for name in ("PruDexNumToSpecies", "PruSpeciesToDexNum",
             "GetSetPruDexFlag", "GetPruDexCount"):
    require(name in interface and name in flags,
            f"PRU Dex public API missing: {name}")
require("PRU_DEX_FLAG_BYTES ((PRU_DEX_COUNT + 7) / 8)" in flags,
        "New save flag storage must use 450 bits")
require("gSaveBlock1Ptr->dexPadding1" in flags
        and "gSaveBlock1Ptr->dexPadding2" in flags,
        "Store independently in existing SaveBlock1 Dex padding")
require("STATIC_ASSERT(sizeof(((struct SaveBlock1 *)0)->dexPadding1)" in flags
        and "STATIC_ASSERT(sizeof(((struct SaveBlock1 *)0)->dexPadding2)" in flags,
        "Storage must be guarded against size/config changes")
require("u8 dexPadding1[0xBF - NUM_DEX_FLAG_BYTES]" in global_h
        and "u8 dexPadding2[0xBF - NUM_DEX_FLAG_BYTES]" in global_h,
        "Do not change save layout and offsets")
require("PruEnsureDexFlagsInitialized" in flags
        and "NationalPokedexNumToSpecies(nativeNum) == species" in flags,
        "Legacy migration must not blindly copy shared National IDs")
require("GetBoxMonDataAt(i, j, MON_DATA_SPECIES)" in flags
        and "GetMonData(&gPlayerParty[i], MON_DATA_SPECIES)" in flags,
        "Migration should recover species actually held in party and PC")
require("GetSetPokedexFlag(nativeNum, FLAG_GET_SEEN)" in flags
        and "GetSetPokedexFlag(nativeNum, FLAG_GET_CAUGHT)" in flags,
        "Existing native flag bits must be preserved through migration")
require("memset(gSaveBlock1Ptr->dexPadding1" in flags
        and "memset(gSaveBlock1Ptr->dexPadding2" in flags,
        "Resetting Pokédex must also clear PRU records")

require("GetSetPruDexFlag(PruSpeciesToDexNum(species), caseId)" in pokemon,
        "Wild encounter/party/gift seen and caught hooks missing")
require("GetSetPruDexFlag(PruSpeciesToDexNum(species), FLAG_GET_CAUGHT)" in battle
        and "GetSetPruDexFlag(PruSpeciesToDexNum(species), FLAG_SET_CAUGHT)" in battle,
        "Wild capture flow must not treat ancestor's caught record as its Relic's")

require("#define HGSS_LIST_CAPACITY (IS_HNS ? PRU_DEX_COUNT : OBTAINABLE_DEX_COUNT)" in hgss,
        "HGSS must allocate exactly PRU's 450 display slots in HNS")
require("pokedexList[HGSS_LIST_CAPACITY + 1]" in hgss,
        "No out-of-bounds cursor sentinel or row array")
require("if (IS_HNS)" in hgss and "i < PRU_DEX_COUNT" in hgss,
        "PRU canonical 450 loop missing")
require("sPokedexView->pokedexList[j].dexNum = dexNum;" in hgss,
        "List entries must store PRU ordinal, not National ID")
require("sPokedexView->pokemonListCount++" in hgss,
        "All rows must have an independent list entry")
require("GetPruDexCount(FLAG_GET_SEEN)" in hgss
        and "GetPruDexCount(FLAG_GET_CAUGHT)" in hgss,
        "The PRU main screen must count canonical independent flags")
require("HgssGetDexFlag" in hgss and "HgssSpeciesToDexNum" in hgss
        and "HgssDexNumToSpecies" in hgss,
        "Info/search/evolution screens must resolve canonical mappings")
require(hgss.count("GetSetPokedexFlag(") == 1
        and hgss.count("NationalPokedexNumToSpecies(") == 1
        and hgss.count("SpeciesToNationalPokedexNum(") == 1,
        "Direct National ID operations must only remain in non-HNS wrappers")
require("dexNum = sPokedexView->pokedexList[entryNum].dexNum;" in hgss,
        "Visible list numbering must use 1–450 ordinals")
require(hgss.count("if (IS_HNS)\n        value = num;") >= 2,
        "Information and stats pages must show PRU numeric IDs")
require("if (species >= HGSS_LIST_CAPACITY" in hgss,
        "Scrolling sprite access must be bounded by the PRU array")
require("if (sPokedexView->selectedPokemon >= sPokedexView->pokemonListCount)" in hgss,
        "Sorted-list cursor must be clamped safely")
require("if (sPokedexView->pokemonListCount == 0 && order != ORDER_NUMERICAL)" in hgss,
        "Empty sorts must not underflow the list")
require("GetSpeciesName(species)" in hgss and "gSpeciesInfo[species].weight" in hgss,
        "Sorts must use the actual canonical species data")
require("HgssGetDexFlag(HgssSpeciesToDexNum(targetSpecies), FLAG_GET_SEEN)" in hgss,
        "Evolutions must not leak a base species' seen flag")

print("PASS: 450 unique and complete family-grouped canonical species numbers")
print("PASS: independent legacy-save-compatible seen/caught records and exact-species battle hooks")
print("PASS: HGSS list, search, detail, stats, sprites, evolutions and counters use PRU IDs")
print("PASS: bounds, zero-result sort, reset and legacy migration safeguards")
print("NOTE: still requires full source test run, compilation (when approved) and in-game save checks.")
