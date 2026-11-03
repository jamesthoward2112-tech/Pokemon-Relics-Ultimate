#!/usr/bin/env python3
"""Source regression for the Rock Shop Eeveelution Expert and Eevee."""
import json
import re
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def read(path):
    return (ROOT / path).read_bytes().decode("latin-1")

def require(ok, message):
    if not ok:
        raise AssertionError(message)

map_path = "data/maps/EcruteakCity_RockShop_hns/map.json"
map_data = json.loads(read(map_path))
scripts = read("data/maps/EcruteakCity_RockShop_hns/scripts.inc")
evolutions = read("src/data/pokemon/species_info/gen_1_families.h")
dex = read("src/data/pokemon/pru_dex_order.h")
layout = (ROOT / "data/layouts/EcruteakCity_RockShop_hns/map.bin").read_bytes()

objects = map_data["object_events"]
expert = [o for o in objects if o.get("script") == "EcruteakCity_RockShop_EventScript_EeveelutionExpert"]
eevees = [o for o in objects if o.get("script") == "EcruteakCity_RockShop_EventScript_ExpertEevee"]
require(len(expert) == 1 and len(eevees) == 1, "Need exactly one expert and one companion Eevee")
expert, eevee = expert[0], eevees[0]
require(expert["graphics_id"] == "OBJ_EVENT_GFX_LASS_HNS", "Expert must use an existing human sprite")
require(eevee["graphics_id"] == "OBJ_EVENT_GFX_MON_BASE+SPECIES_EEVEE", "Companion must use Eevee's real overworld graphics")
require(expert["script"] in scripts and eevee["script"] in scripts, "Both object scripts must be defined")
require(abs(expert["x"] - eevee["x"]) + abs(expert["y"] - eevee["y"]) == 1,
        "Expert and Eevee must occupy adjacent distinct tiles")
for obj in (expert, eevee):
    x, y = obj["x"], obj["y"]
    require(0 <= x < 14 and 0 <= y < 9, "NPC must remain inside the 14x9 shop layout")
    tile = struct.unpack_from("<H", layout, (y * 14 + x) * 2)[0]
    require(tile == 0x32E3, "NPC object must stand on the open shop floor")
approaches = [(expert["x"] + dx, expert["y"] + dy) for dx,dy in ((0,1),(1,0),(-1,0),(0,-1))]
require(any(0 <= x < 14 and 0 <= y < 9 and struct.unpack_from("<H",layout,(y*14+x)*2)[0] == 0x32E3
            and not any(o["x"] == x and o["y"] == y for o in objects)
            for x,y in approaches), "Expert must have an adjacent open approach tile")
require(any(w["x"] == 4 and w["y"] == 7 for w in map_data["warp_events"]), "Original entrance warp must remain")
clerk = next((o for o in objects if o.get("script") == "EcruteakCity_RockShop_EventScript_Clerk"), None)
collector = next((o for o in objects if o.get("script") == "EcruteakCity_RockShop_EventScript_Collector"), None)
require(clerk is not None and (clerk["x"],clerk["y"]) == (2,3), "Original clerk must remain in place")
require(collector is not None and (collector["x"],collector["y"]) == (7,5), "Original collector must remain in place")
warp = next((w for w in map_data["warp_events"] if (w["x"],w["y"]) == (4,7)), None)
require(warp is not None and warp["dest_map"] == "MAP_ECRUTEAK_CITY_HNS" and warp["dest_warp_id"] == "14",
        "Original entrance connection must remain unchanged")

expected = {
    "SPECIES_VAPOREON": "ITEM_WATER_STONE", "SPECIES_JOLTEON": "ITEM_THUNDER_STONE",
    "SPECIES_FLAREON": "ITEM_FIRE_STONE", "SPECIES_ESPEON": "ITEM_SUN_STONE",
    "SPECIES_UMBREON": "ITEM_MOON_STONE", "SPECIES_LEAFEON": "ITEM_LEAF_STONE",
    "SPECIES_GLACEON": "ITEM_ICE_STONE", "SPECIES_EEVEEON": "ITEM_ANCIENT_STONE",
    "SPECIES_NIMBEON": "ITEM_SHINY_STONE", "SPECIES_OMEON": "ITEM_DUSK_STONE",
    "SPECIES_CHAMPEON": "ITEM_EXPERT_BELT", "SPECIES_LEPIDEON": "ITEM_SILVER_POWDER",
    "SPECIES_SPHYNXEON": "ITEM_SOFT_SAND", "SPECIES_GUARDEON": "ITEM_METAL_COAT",
    "SPECIES_OBSIDEON": "ITEM_HARD_STONE", "SPECIES_TOXEON": "ITEM_POISON_BARB",
    "SPECIES_DRAKEON": "ITEM_DRAGON_FANG",
    "SPECIES_SYLVEON": "ITEM_DAWN_STONE",
}
hns = evolutions.split("#if IS_HNS", 1)[1].split("#else", 1)[0]
actual = dict(re.findall(r"\{EVO_ITEM,\s*(ITEM_[A-Z0-9_]+),\s*(SPECIES_[A-Z0-9_]+)\}", hns))
actual = {species:item for item,species in actual.items()}
require(actual == expected, "HNS direct-use evolution items must match all 18 approved methods")
for species in expected:
    require(species in dex, f"{species} must be in the approved PRU Dex")

guide = scripts.split("EcruteakCity_RockShop_Text_ExpertGreeting:", 1)[1].split("EcruteakCity_RockShop_Text_Collector:",1)[0]
for species, item in expected.items():
    require(species.removeprefix("SPECIES_") in guide, f"Guide is missing {species}")
    require(item.removeprefix("ITEM_").replace("_", " ") in guide, f"Guide is missing {item}")
require("SYLVEON" in guide and "DAWN STONE" in guide, "Guide must describe Sylveon's Dawn Stone evolution")
require("DAWN STONE is sold here after the\\n" in guide and "FOG BADGE" in guide,
        "Guide must state Dawn Stone unlock timing")
require("all 18 of" in guide and "17" not in guide, "Guide greeting must report 18 approved Eeveelutions")
for symbol in ("Classic", "Relic", "Unusual", "Goodbye"):
    require(f"EcruteakCity_RockShop_Text_ExpertOption{symbol}" in scripts, f"Missing {symbol} menu choice")
menu = scripts.split("EcruteakCity_RockShop_EventScript_EeveelutionExpertMenu::",1)[1].split("EcruteakCity_RockShop_EventScript_ExpertClassic::",1)[0]
for target in ("ExpertClassic", "ExpertRelic", "ExpertUnusual", "ExpertGoodbye"):
    require(f"EcruteakCity_RockShop_EventScript_{target}" in menu, f"Menu branch missing {target}")
for label, body in re.findall(r"(EcruteakCity_RockShop_EventScript_Expert(?:Classic|Relic|Unusual|Goodbye))::(.*?)(?=\nEcruteakCity_RockShop_)", scripts, re.S):
    require("end" in body, f"Script branch {label} must terminate")
require("playmoncry SPECIES_EEVEE, CRY_MODE_NORMAL" in scripts, "Companion Eevee should have a friendly cry interaction")
expert_scripts = scripts.split("EcruteakCity_RockShop_EventScript_EeveelutionExpert::",1)[1].split("EcruteakCity_RockShop_EventScript_ExpertEevee::",1)[0]
require(not re.search(r"\b(?:setflag|clearflag|setvar|addvar)\b", expert_scripts),
        "Expert must not create persistent flags or save variables")
for line in re.findall(r'\.string "([^"$]*)', guide):
    require(len(line.replace("\\n", "")) <= 36, "Guide line may overflow a GBA text window")

print("Eeveelution Expert source regression passed (objects, access, exact HNS methods, menu branches and approved species).")
