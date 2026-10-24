#!/usr/bin/env python3
"""PRU Kyogre ace reveal and both Orb legendaries as genuine shiny Primals."""
from pathlib import Path
import json

root = Path(__file__).resolve().parents[2]

def read(path):
    return (root / path).read_text(encoding="utf-8")

party = read("src/data/trainers_hns.party")
archie = party.split("=== TRAINER_PRU_ARCHIE_KYOGRE_HNS ===", 1)[1].split("=== TRAINER_PRU_MAXIE_GROUDON_HNS ===", 1)[0]
assert "AI: Smart Trainer / Prediction / Ace Pokemon" in archie, "AI must reserve Kyogre for last"
ace = archie.split("Kyogre @ Blue Orb", 1)[1]
assert ace.count("Shiny: Yes") == 1, "trainer Kyogre should be actually shiny"
assert ace.index("Shiny: Yes") > ace.index("Level: ")
assert "Kyogre @ Blue Orb" in archie

# Native AI code, not just party ordering, must honour the ace and avoid
# choosing it when other usable party members remain.
ai = read("src/battle_ai_switch.c")
assert "AI_FLAG_ACE_POKEMON" in ai
assert "monPartyId == CalculateEnemyPartyCountInSide(battler)-1" in ai
assert "CountUsablePartyMons(battler) <= aceMonCount" in ai

map_data = json.loads(read("data/maps/SeafoamIslands_SecretCave_hns/map.json"))
assert map_data["layout"] == "LAYOUT_SEAFOAM_ISLANDS_SECRET_CAVE_HNS"
assert map_data["weather"] == "WEATHER_RAIN"
kyogre = next(o for o in map_data["object_events"] if o["script"] == "SeafoamIslands_SecretCave_EventScript_Kyogre")
archie_obj = next(o for o in map_data["object_events"] if o["script"] == "SeafoamIslands_SecretCave_EventScript_Archie")
assert kyogre["graphics_id"] == "OBJ_EVENT_GFX_KYOGRE_FRONT"
assert kyogre["local_id"] == "LOCALID_PRU_KYOGRE"
assert kyogre["flag"] == "FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE"
assert archie_obj["y"] == 12, "Archie should stand closer to the hidden legend"
flags = read("include/constants/flags_hns.h")
assert "#define FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE" in flags

script = read("data/maps/SeafoamIslands_SecretCave_hns/scripts.inc")
assert "map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_SecretCave_OnTransition" in script
assert "goto_if_set FLAG_PRU_KYOGRE_CAUGHT" in script
assert "goto_if_set FLAG_PRU_ARCHIE_KYOGRE_DEFEATED" in script
assert "setflag FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE" in script
assert "clearflag FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE" in script
post = script.split("SeafoamIslands_SecretCave_EventScript_Archie::", 1)[1].split("SeafoamIslands_SecretCave_EventScript_Kyogre::", 1)[0]
assert post.index("setflag FLAG_PRU_ARCHIE_KYOGRE_DEFEATED") < post.index("addobject LOCALID_PRU_KYOGRE")
assert post.index("addobject LOCALID_PRU_KYOGRE") < post.index("removeobject LOCALID_PRU_ARCHIE")
assert "ancient RELIC" in script
assert "setwildbattleshiny SPECIES_KYOGRE, 75, ITEM_BLUE_ORB" in script
assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT" in script
caught = script.split("SeafoamIslands_SecretCave_EventScript_KyogreCaught::", 1)[1]
assert "setflag FLAG_PRU_KYOGRE_CAUGHT" in caught
assert "setflag FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE" in caught

groudon = read("data/maps/MtSilver_1F_MoltresRoom_hns/scripts.inc")
assert "setwildbattleshiny SPECIES_GROUDON, 75, ITEM_RED_ORB" in groudon
assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT" in groudon
util = read("src/script_pokemon_util.c")
shiny = util.split("void CreateShinyScriptedMon(", 1)[1].split("void PruPrepareChargedElectrode(", 1)[0]
assert "MON_DATA_MODERN_FATEFUL_ENCOUNTER" in shiny
assert "SPECIES_KYOGRE" in shiny and "ITEM_BLUE_ORB" in shiny
assert "SPECIES_GROUDON" in shiny and "ITEM_RED_ORB" in shiny

for name in ("kyogre", "groudon"):
    art = root / "graphics" / "pokemon" / name / "primal"
    assert (art / "front.png").is_file() and (art / "back.png").is_file()
    assert (art / "shiny.pal").is_file()
    assert (art / "shiny.pal").read_bytes() != (art / "normal.pal").read_bytes()
print("PRU_PRIMAL_ACE_PASS: true shiny Primals, native ace AI, hidden Kyogre reveal, original cave, capture-only respawns")
