#!/usr/bin/env python3
"""The Primal Groudon finale belongs on Route 45, not in Seafoam/Mt Silver."""
import json
from pathlib import Path

root = Path(__file__).resolve().parents[2]
read = lambda p: (root / p).read_text()
group = json.loads(read("data/maps/map_groups.json"))
route = json.loads(read("data/maps/Route45_hns/map.json"))
cave = json.loads(read("data/maps/Route45_GroudonCave_hns/map.json"))
layouts = json.loads(read("data/layouts/layouts.json"))

assert "Route45_GroudonCave_hns" in group["gMapGroup_Dungeons_Hns"]
assert any(w["dest_map"] == "MAP_ROUTE45_GROUDON_CAVE_HNS" for w in route["warp_events"])
assert cave["layout"] == "LAYOUT_ROUTE45_GROUDON_CAVE_HNS"
assert any(x["id"] == cave["layout"] and x["secondary_tileset"] == "gTileset_BlackthornGym_Hns"
           for x in layouts["layouts"]), "Red magma tileset must replace Seafoam blue"
assert cave["region"] == "REGION_JOHTO"
assert any(o["script"] == "Route45_GroudonCave_EventScript_Maxie" for o in cave["object_events"])
assert any(o["script"] == "Route45_GroudonCave_EventScript_Groudon" for o in cave["object_events"])
assert not any(o["script"].endswith(("EventScript_Maxie", "EventScript_Groudon"))
               for o in json.loads(read("data/maps/MtSilver_1F_MoltresRoom_hns/map.json"))["object_events"])
scene = read("data/maps/Route45_GroudonCave_hns/scripts.inc")
assert '.include "data/maps/Route45_GroudonCave_hns/scripts.inc"' in read("data/event_scripts.s")
maxie_party = read("src/data/trainers_hns.party").split("=== TRAINER_PRU_MAXIE_GROUDON_HNS ===", 1)[1].split("=== TRAINER_", 1)[0]
assert "AI: Smart Trainer / Prediction / Ace Pokemon" in maxie_party
assert maxie_party.rfind("Groudon @ Red Orb") > maxie_party.rfind("Houndoom @ Wise Glasses")
assert "FLAG_PRU_MAXIE_GROUDON_DEFEATED" in scene
assert "FLAG_PRU_GROUDON_CAUGHT" in scene
assert "setwildbattleshiny SPECIES_GROUDON, 75, ITEM_RED_ORB" in scene
assert "B_OUTCOME_CAUGHT" in scene
src = read("src/script_pokemon_util.c")
for move in ("HONE_CLAWS", "PRECIPICE_BLADES", "FIRE_PUNCH", "DRAGON_CLAW"):
    assert f"MOVE_{move}" in src

print("PASS: Route 45 magma cave, Maxie, shiny Primal Groudon and moves")
