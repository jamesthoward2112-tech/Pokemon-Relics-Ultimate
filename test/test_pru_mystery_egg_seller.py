#!/usr/bin/env python3
"""PRU Day-Care Mystery Egg source regression; no ROM build required.

Run in a full repository checkout:
    python3 test/test_pru_mystery_egg_seller.py

This is source validation only; all purchase paths, sprite reachability and
actual hatching still need mGBA gameplay verification before release.
"""
import json
import re
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def source(path):
    return (ROOT / path).read_text(encoding="utf-8")

def require(condition, reason):
    if not condition:
        raise AssertionError(reason)

daycare = source("src/daycare.c")
script = source("data/maps/Route34_DayCare_hns/scripts.inc")
map_data = json.loads(source("data/maps/Route34_DayCare_hns/map.json"))
registry = source("data/specials.inc")
dex = source("src/data/pokemon/pru_dex_order.h")
species_info = source("src/data/pokemon/species_info/pjr_families.h")
relic_species_info = source("src/data/pokemon/species_info/pru_custom.h")
layout = json.loads(source("data/layouts/layouts.json"))

require('#include "money.h"' in daycare, "Money API header must be included")
require("def_special PruBuyDaycareMysteryEgg" in registry,
        "Mystery Egg C special must be callable from scripts")

fn_start = daycare.index("u16 PruBuyDaycareMysteryEgg(void)")
fn_end = daycare.index("\n#else", fn_start)
func = daycare[fn_start:fn_end]
require("#define PRU_MYSTERY_EGG_PRICE 5000" in daycare,
        "Egg sale must cost exactly 5000")
require("CalculatePlayerPartyCount()" in func and "count >= GetMaxPartySize()" in func,
        "Seller must refuse a full or challenge-capped party")
require("IsEnoughMoney(&gSaveBlock1Ptr->money, PRU_MYSTERY_EGG_PRICE)" in func,
        "Money must be checked before Egg creation")
require("CreateEgg(&egg, species, FALSE)" in func
        and "MON_DATA_IS_EGG" in func and "gSpeciesInfo[species].eggCycles" in func,
        "Seller must produce and validate an actual hatchable Egg")
require("RemoveMoney(&gSaveBlock1Ptr->money, PRU_MYSTERY_EGG_PRICE)" in func,
        "Seller must charge exactly the price")

ordered = [
    "count >= GetMaxPartySize()",
    "IsEnoughMoney(&gSaveBlock1Ptr->money, PRU_MYSTERY_EGG_PRICE)",
    "species = sPruMysteryEggSpecies[",
    "CreateEgg(&egg, species, FALSE)",
    "gPlayerParty[GetMaxPartySize() - 1] = egg;",
    "CompactPartySlots();",
    "RemoveMoney(&gSaveBlock1Ptr->money, PRU_MYSTERY_EGG_PRICE)",
    "return 0;",
]
require(all(func.find(step) >= 0 for step in ordered), "Transaction missing a required step")
positions = [func.index(step) for step in ordered]
require(positions == sorted(positions),
        "Party/funds validation and valid delivery must precede deduction")
require(func.index("CalculatePlayerPartyCount();", func.index("CompactPartySlots();"))
        < func.index("RemoveMoney(&gSaveBlock1Ptr->money, PRU_MYSTERY_EGG_PRICE)"),
        "Party count must update after compaction and before payment")

pool_src = daycare.split("static const u16 sPruMysteryEggSpecies[] =", 1)[1].split("};", 1)[0]
pool = re.findall(r"\bSPECIES_[A-Z0-9_]+\b", pool_src)
expected = [
    "SPECIES_BULBASAUR", "SPECIES_CHARMANDER", "SPECIES_SQUIRTLE",
    "SPECIES_CHIKORITA", "SPECIES_CYNDAQUIL", "SPECIES_TOTODILE",
    "SPECIES_TREECKO", "SPECIES_TORCHIC", "SPECIES_MUDKIP",
    "SPECIES_SCARABUB", "SPECIES_SKARMET", "SPECIES_MOOTINY",
    "SPECIES_GEMLIN",
]
require(pool == expected, "Missing, duplicate or unauthorized Mystery Egg species")
require("static u16 GetUniformPruMysteryEggIndex(void)" in daycare,
        "13-species selection must use unbiased rejection sampling")
selector = daycare.split("static u16 GetUniformPruMysteryEggIndex(void)", 1)[1].split("\n}", 1)[0]
require("randomRange = (u32)USHRT_MAX + 1;" in selector
        and "limit = randomRange - (randomRange % poolSize);" in selector
        and "while (randomValue >= limit)" in selector
        and "randomValue % poolSize" in selector,
        "Every Mystery Egg species must have exactly equal selection probability")
pool_size = len(pool)
random_range = 1 << 16
limit = random_range - (random_range % pool_size)
outcomes = [0] * pool_size
for random_value in range(limit):
    outcomes[random_value % pool_size] += 1
require(len(set(outcomes)) == 1,
        "Rejection sampling must map accepted 16-bit rolls uniformly")
dex_entries = set(re.findall(r"\bSPECIES_[A-Z0-9_]+\b", dex.split("sPruDexSpecies", 1)[1]))
require(set(pool).issubset(dex_entries), "Every Mystery Egg species must belong to canonical PRU 450")

for species in ("SCARABUB", "SKARMET", "MOOTINY", "GEMLIN"):
    active_info = relic_species_info if species == "GEMLIN" else species_info
    record = active_info.split("[SPECIES_" + species + "] =", 1)[1].split("\n},", 1)[0]
    require(re.search(r"\.eggCycles\s*=\s*[1-9]\d*", record) is not None,
            "Relic baby must have nonzero hatch cycles: " + species)
    for asset in (".frontPic =", ".backPic =", ".iconSprite ="):
        require(asset in record, "Relic baby lacks image mapping: " + species)

require("Route34_DayCare_EventScript_MysteryEggSeller::" in script,
        "Separate repeatable vendor script is missing")
vendor = script.split("@ PRU Mystery Egg seller.", 1)[1].split(
    "Route34_DayCare_EventScript_Clerk::", 1)[0]
require("specialvar VAR_RESULT, PruBuyDaycareMysteryEgg" in vendor,
        "Purchase must use the transactional special")
for index, branch in (
    ("0", "MysteryEggSuccess"),
    ("1", "MysteryEggPartyFull"),
    ("2", "MysteryEggNoMoney"),
):
    require(f"case {index}, Route34_DayCare_EventScript_{branch}" in vendor,
            "Vendor response path missing: " + branch)
require("goto_if_eq VAR_RESULT, NO, Route34_DayCare_EventScript_MysteryEggDecline" in vendor,
        "Declined purchases must terminate safely")
require("FLAG_RECEIVED_ODD_EGG" not in vendor
        and "removemoney" not in vendor
        and "giveoddegg" not in vendor,
        "Seller must not affect existing Odd Egg event or double-charge")
for phrase in ("MysteryEggReceived", "MysteryEggPartyFull", "MysteryEggNoMoney",
               "MysteryEggDecline", "MysteryEggUnavailable"):
    require("Route34_DayCare_Text_" + phrase in vendor,
            "Missing useful NPC dialogue: " + phrase)
require("\\\\n" not in vendor and "\\\\p" not in vendor,
        "String control escapes must not be doubled in source")

required_original_scripts = (
    "Route34_DayCare_EventScript_Clerk::",
    "Route34_DayCare_EventScript_Clerk_GaveEgg::",
    "Route34_DayCare_EventScript_PRUMoveExpert::",
    "Route34_DayCare_EventScript_DaycareWoman::",
)
for label in required_original_scripts:
    require(label in script, "Existing Day-Care service lost: " + label)
require("giveoddegg 1" in script and "setflag FLAG_RECEIVED_ODD_EGG" in script,
        "The original free one-off Odd Egg must remain intact")

vendors = [obj for obj in map_data["object_events"]
           if obj["script"] == "Route34_DayCare_EventScript_MysteryEggSeller"]
require(len(vendors) == 1, "There must be one and only one Mystery Egg NPC")
vendor_npc = vendors[0]
layout_def = next(x for x in layout["layouts"]
                  if x["id"] == map_data["layout"])
require(0 <= vendor_npc["x"] < layout_def["width"]
        and 0 <= vendor_npc["y"] < layout_def["height"],
        "Mystery Egg NPC position must be inside the map")
require(not any(other is not vendor_npc and
                other["x"] == vendor_npc["x"] and
                other["y"] == vendor_npc["y"]
                for other in map_data["object_events"]),
        "Mystery Egg seller must not overlap another fixed NPC")
require(vendor_npc["flag"] == "0", "Vendor should be permanently repeatable")
require("OBJ_EVENT_GFX_LASS_HNS" == vendor_npc["graphics_id"],
        "Vendor graphics must be a valid existing map asset")

# Confirm the vendor's tile and a neighboring approach tile are walkable.
map_bytes = (ROOT / layout_def["blockdata_filepath"]).read_bytes()
primary_attrs = (ROOT / "data/tilesets/primary/johto_building_hns/metatile_attributes.bin").read_bytes()
secondary_attrs = (ROOT / "data/tilesets/secondary/pokemon_day_care_hns/metatile_attributes.bin").read_bytes()
def map_tile_is_open(x, y):
    word = struct.unpack_from("<H", map_bytes, (y * layout_def["width"] + x) * 2)[0]
    metatile_id = word & 0x03FF
    primary_count = len(primary_attrs) // 2
    attr_bytes = primary_attrs if metatile_id < primary_count else secondary_attrs
    attr_id = metatile_id if metatile_id < primary_count else metatile_id - primary_count
    behavior = struct.unpack_from("<H", attr_bytes, attr_id * 2)[0] & 0x00FF
    collision = word & 0x0C00
    return behavior == 0 and collision == 0

vx, vy = vendor_npc["x"], vendor_npc["y"]
require(map_tile_is_open(vx, vy), "Mystery Egg NPC must stand on a walkable tile")
approaches = [(vx + 1, vy), (vx - 1, vy), (vx, vy + 1), (vx, vy - 1)]
require(any(0 <= x < layout_def["width"] and 0 <= y < layout_def["height"]
            and map_tile_is_open(x, y) for x, y in approaches),
        "Player must be able to approach and interact with the vendor")

print("PASS: 13 species: Kanto/Johto/Hoenn starters plus Scarabub, Skarmet, Mootiny and Gemlin")
print("PASS: save-compatible, single-charge Egg creation after capacity/funds checks")
print("PASS: dedicated seller, original Odd Egg event and Move Expert retained")
print("PASS: NPC inside layout bounds and not on another object event")
print("PASS: vendor tile and an adjacent approach tile are walkable")
print("NOTE: source only; purchase UI, hatching, challenge modes and save/reload are not emulator-tested")
