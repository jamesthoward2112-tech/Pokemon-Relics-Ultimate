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
layout_data = json.loads(read("data/layouts/layouts.json"))
chamber = next(x for x in layout_data["layouts"] if x["id"] == "LAYOUT_PRU_KYOGRE_CHAMBER_HNS")
assert chamber["game_version"] == "hns" and chamber["layout_version"] == "hns", "pool layout must link into the HNS ROM"
assert chamber["blockdata_filepath"] == "data/layouts/MarineCave_End/map.bin", "pool must reuse original collision and tiles"
assert chamber["border_filepath"] == "data/layouts/MarineCave_End/border.bin"
assert chamber["secondary_tileset"] == "gTileset_Cave"
assert map_data["layout"] == "LAYOUT_PRU_KYOGRE_CHAMBER_HNS", "reuse the original Kyogre pool as a compiled HNS layout"
assert (kyogre["x"], kyogre["y"], kyogre["elevation"]) == (9, 22, 1)
assert (archie["x"], archie["y"]) == (9, 27)
assert map_data["warp_events"][0]["dest_map"] == "MAP_SEAFOAM_ISLANDS_GYM_HNS"
assert (map_data["warp_events"][0]["x"], map_data["warp_events"][0]["y"]) == (20, 4)
assert any(event["x"] == 9 and event["y"] == 26
           and event["script"] == "SeafoamIslands_SecretCave_EventScript_Kyogre"
           and event["var"] == "VAR_TEMP_1" and event["var_value"] == "1"
           for event in map_data["coord_events"]), "pool-side approach must trigger Kyogre"

assert kyogre["graphics_id"] == "OBJ_EVENT_GFX_KYOGRE_FRONT", "use the tested native Kyogre overworld asset"
assert kyogre["flag"] == "FLAG_PRU_KYOGRE_CAUGHT"
assert archie["flag"] == "FLAG_PRU_ARCHIE_KYOGRE_DEFEATED"
assert archie["trainer_sight_or_berry_tree_id"] == "4"

script = read("data/maps/SeafoamIslands_SecretCave_hns/scripts.inc")
post = script.split("SeafoamIslands_SecretCave_EventScript_Archie::", 1)[1].split("SeafoamIslands_SecretCave_EventScript_Kyogre::", 1)[0]
assert "trainerbattle_single TRAINER_PRU_ARCHIE_KYOGRE_HNS" in post
assert "map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_SecretCave_OnTransition" in script
assert "setvar VAR_TEMP_1, 1" in script
assert "setvar VAR_TEMP_1, 0" in script
assert post.index("lockall") < post.index("msgbox SeafoamIslands_SecretCave_Text_ArchieAfter")
assert post.index("closemessage") < post.index("releaseall")
assert "removeobject LOCALID_PRU_ARCHIE" in post
assert "setflag FLAG_PRU_ARCHIE_KYOGRE_DEFEATED" in post

encounter = script.split("SeafoamIslands_SecretCave_EventScript_Kyogre::", 1)[1].split("SeafoamIslands_SecretCave_Text_ArchieIntro:", 1)[0]
assert "seteventmon SPECIES_KYOGRE, 75, ITEM_BLUE_ORB" in encounter
assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT" in encounter
assert "goto_if_set FLAG_PRU_KYOGRE_CAUGHT, SeafoamIslands_SecretCave_EventScript_KyogreUnavailable" in encounter, "captured Kyogre must not respawn from the coordinate event"
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
assert "Level: 75" in boss

# The Emerald Cave tileset is normally excluded by HNS preprocessor guards.
# Its exact donor pixels/collision metadata must therefore be explicitly linked.
metatiles_source = read("src/data/tilesets/metatiles.h")
headers_source = read("src/data/tilesets/headers.h")
assert '#if IS_HNS\n// Exact Emerald Cave metatiles' in metatiles_source
assert 'const u16 gMetatiles_Cave[] = INCBIN_U16("data/tilesets/secondary/cave/metatiles.bin");' in metatiles_source
assert '#if IS_HNS\n// Exact Emerald cave tileset' in headers_source
assert 'const struct Tileset gTileset_Cave =' in headers_source

print("PRU_KYOGRE_CAVE_PASS: native overworld, field rain, locked post-battle, preserved respawn, rain-themed custom team")
