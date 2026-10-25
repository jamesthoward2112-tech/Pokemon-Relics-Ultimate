#!/usr/bin/env python3
"""PRU Kyogre cave: overworld, weather, scripted handoff, and boss roster."""
import json
import re
from pathlib import Path

root = Path(__file__).resolve().parents[2]
def read(path):
    return (root / path).read_text(encoding="utf-8")

map_data = json.loads(read("data/maps/SeafoamIslands_SecretCave_hns/map.json"))
events = map_data["object_events"]
kyogre = next(obj for obj in events if obj["script"] == "SeafoamIslands_SecretCave_EventScript_Kyogre")
archie = next(obj for obj in events if obj["script"] == "SeafoamIslands_SecretCave_EventScript_Archie")

assert map_data["weather"] == "WEATHER_RAIN", "rain must be visible on the cave map"
assert map_data["layout"] == "LAYOUT_SEAFOAM_ISLANDS_SECRET_CAVE_HNS", "restore the previously working Seafoam cave artwork"
assert (kyogre["x"], kyogre["y"], kyogre["elevation"]) == (16, 11, 0)
assert (archie["x"], archie["y"], archie["elevation"]) == (16, 12, 0)
assert map_data["warp_events"][0]["dest_map"] == "MAP_SEAFOAM_ISLANDS_GYM_HNS"
assert (map_data["warp_events"][0]["x"], map_data["warp_events"][0]["y"]) == (16, 17)
assert map_data["coord_events"] == [], "the original compact room uses Kyogre's visible NPC event, not a distant pool trigger"

assert kyogre["graphics_id"] == "OBJ_EVENT_GFX_PRU_SHINY_PRIMAL_KYOGRE_HNS", "use the approved shiny Primal overworld asset"
assert kyogre["flag"] == "FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE"
assert archie["flag"] == "FLAG_PRU_ARCHIE_KYOGRE_DEFEATED"
assert archie["trainer_sight_or_berry_tree_id"] == "4"

script = read("data/maps/SeafoamIslands_SecretCave_hns/scripts.inc")
post = script.split("SeafoamIslands_SecretCave_EventScript_Archie::", 1)[1].split("SeafoamIslands_SecretCave_EventScript_Kyogre::", 1)[0]
assert "trainerbattle_single TRAINER_PRU_ARCHIE_KYOGRE_HNS" in post
assert post.index("lockall") < post.index("msgbox SeafoamIslands_SecretCave_Text_ArchieAfter")
assert post.index("closemessage") < post.index("releaseall")
assert "removeobject LOCALID_PRU_ARCHIE" in post
assert "setflag FLAG_PRU_ARCHIE_KYOGRE_DEFEATED" in post

encounter = script.split("SeafoamIslands_SecretCave_EventScript_Kyogre::", 1)[1].split("SeafoamIslands_SecretCave_Text_ArchieIntro:", 1)[0]
assert "setwildbattleshiny SPECIES_KYOGRE, 75, ITEM_BLUE_ORB" in encounter
assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT" in encounter
assert "goto_if_set FLAG_PRU_KYOGRE_CAUGHT, SeafoamIslands_SecretCave_EventScript_KyogreUnavailable" in encounter, "capture must keep Kyogre permanently unavailable"
before_capture, after_capture = encounter.split("SeafoamIslands_SecretCave_EventScript_KyogreCaught::", 1)
assert "setflag FLAG_PRU_KYOGRE_CAUGHT" not in before_capture, "KO and fleeing must allow re-encounter"
assert "setflag FLAG_PRU_KYOGRE_CAUGHT" in after_capture

party_file = read("src/data/trainers_hns.party")
boss = party_file.split("=== TRAINER_PRU_ARCHIE_KYOGRE_HNS ===", 1)[1].split("=== TRAINER_PRU_MAXIE_GROUDON_HNS ===", 1)[0]
actual_species = re.findall(r"^([A-Za-z]+) @ ", boss, flags=re.MULTILINE)
assert actual_species == ["Pelipper", "Skulberus", "Sharpedo", "Feralodon", "Swamplith", "Kyogre"], actual_species
assert len(re.findall(r"^Level: ", boss, flags=re.MULTILINE)) == 6
assert "Ability: Drizzle" in boss
assert "Ability: Moxie" in boss
assert "Ability: Tidal Roar" in boss
assert "Ability: Tidal Bastion" in boss
assert "AI: Smart Trainer / Prediction" in boss
assert "Kyogre @ Blue Orb" in boss
assert boss.index("Swamplith @") < boss.index("Kyogre @ Blue Orb")
assert "Level: 80" in boss

print("PRU_KYOGRE_CAVE_PASS: original Seafoam room, native Kyogre, rain, dialogue lock, capture-only removal, custom rain team")
