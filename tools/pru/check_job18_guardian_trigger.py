#!/usr/bin/env python3
"""Guard against the Tin Tower pre-event reveal and dead-end NPC dialogue."""
from pathlib import Path
import json

ROOT = Path(__file__).resolve().parents[2]
map_dir = ROOT / "data/maps/TinTower_RoofDay_hns"
scripts = (map_dir / "scripts.inc").read_text()
map_data = json.loads((map_dir / "map.json").read_text())

transition = scripts.split("TinTower_RoofDay_OnTransition:", 1)[1].split("\n\n", 1)[0]
assert "VAR_COMPLETED_HO_OH, 2, TinTower_RoofDay_MapScript_GuardianReady" in transition
assert "VAR_COMPLETED_HO_OH, 2, TinTower_RoofDay_MapScript_HoohStory" not in transition
ready = scripts.split("TinTower_RoofDay_MapScript_GuardianReady::", 1)[1].split("\n\n", 1)[0]
assert "setflag FLAG_HIDE_HO_OH" in ready

talk = scripts.split("TinTower_RoofDay_EventScript_TalkToKimono::", 1)[1].split("TinTower_RoofDay_EventScript_GuardianDefeated::", 1)[0]
assert talk.index("clearflag FLAG_HIDE_HO_OH") < talk.index("applymovement LOCALID_HO_OH")
assert talk.index("TinTower_RoofDay_Text_GuardianChallenge") > talk.index("playmoncry SPECIES_DRAGONITE_GUARDIAN")

trigger = next(event for event in map_data["coord_events"] if event["type"] == "trigger")
assert trigger["var"] == "VAR_COMPLETED_HO_OH" and trigger["var_value"] == "2"
assert trigger["script"] == "TinTower_RoofDay_EventScript_TalkToKimono"
print("PASS: Guardian stays hidden on map entry and the armed coordinate trigger runs the ceremony")
