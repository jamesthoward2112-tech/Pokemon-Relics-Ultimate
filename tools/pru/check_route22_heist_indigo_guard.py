#!/usr/bin/env python3
"""Route 22 Badge Heist staging and Indigo Plateau Rocket door blockade."""
from pathlib import Path
import json
import re

ROOT = Path(__file__).resolve().parents[2]


def read(path):
    return (ROOT / path).read_text(encoding="utf-8")


def map_data(name):
    return json.loads(read(f"data/maps/{name}/map.json"))


route22 = map_data("Route22_hns")
reception = map_data("ReceptionGate_hns")
indigo = map_data("IndigoPlateau_hns")
scripts22 = read("data/maps/Route22_hns/scripts.inc")
scripts_indigo = read("data/maps/IndigoPlateau_hns/scripts.inc")
scripts_reception = read("data/maps/ReceptionGate_hns/scripts.inc")
flags = read("include/constants/flags_hns.h")

# The Kanto Route 22 reception entrance is the heist location, not Route 26.
assert route22["region"] == "REGION_KANTO"
assert any(w["x"] == 12 and w["y"] == 9 and w["dest_map"] == "MAP_RECEPTION_GATE_HNS"
           for w in route22["warp_events"])
for gfx in ("OBJ_EVENT_GFX_JESSIE_HNS", "OBJ_EVENT_GFX_JAMES_HNS",
            "OBJ_EVENT_GFX_MON_BASE+SPECIES_MEOWTH", "OBJ_EVENT_GFX_PRU_MEOWTH_BALLOON_HNS"):
    assert any(o["graphics_id"] == gfx for o in route22["object_events"]), gfx
    assert not any(o["graphics_id"] == gfx for o in reception["object_events"]), gfx
assert any(e["script"] == "Route22_EventScript_PRUHeistTrigger"
           and e["x"] == 12 and e["y"] == 13 for e in route22["coord_events"])
assert "call Route22_EventScript_PRUSyncRocket" in scripts22
assert "goto_if_unset FLAG_BADGE16_GET, Route22_EventScript_PRUHeistNoop" in scripts22
assert "goto_if_set FLAG_PRU_HEIST_STARTED, Route22_EventScript_PRUHeistNoop" in scripts22
assert "setflag FLAG_PRU_HEIST_STARTED" in scripts22
assert "addobject 14" in scripts22 and "applymovement 14, Route22_Movement_PRUBalloonRise" in scripts22
assert "Route22_EventScript_Scene::" in scripts22, "existing Giovanni/Silver scene changed"
assert "ReceptionGate_EventScript_PRUHeistTrigger" not in scripts_reception
assert not re.search(r"\b(?:setflag|clearflag)\s+FLAG_BADGE\d+_GET", 
                     scripts22.split("Route22_EventScript_PRUSyncRocket::", 1)[1]), "real badge flags changed"

# The actual Indigo Plateau League doorway must remain blocked after theft
# (even after Giovanni) until Jessie and James return the badge case.
door = next(w for w in indigo["warp_events"]
            if w["dest_map"] == "MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS")
assert (door["x"], door["y"]) == (11, 6)
guard = next(o for o in indigo["object_events"]
             if o["graphics_id"] == "OBJ_EVENT_GFX_ROCKET_M_HNS")
assert (guard["x"], guard["y"]) == (11, 6), "Rocket guard must occupy the actual door"
assert guard["flag"] == "FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD"
sync = scripts_indigo.split("IndigoPlateau_EventScript_PRUSyncRocket::", 1)[1].split(
    "IndigoPlateau_EventScript_PRUSyncDone::", 1)[0]
assert "goto_if_unset FLAG_PRU_HEIST_STARTED" in sync
assert "goto_if_set FLAG_PRU_HEIST_COMPLETED" in sync
assert sync.index("clearflag FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD") < sync.index(
    "goto_if_unset FLAG_PRU_HEIST_GIOVANNI")
finale = scripts_indigo.split("IndigoPlateau_EventScript_PRUEscape::", 1)[1].split(
    "IndigoPlateau_Text_PRURocketIntro:", 1)[0]
assert finale.index("setflag FLAG_PRU_HEIST_COMPLETED") < finale.index(
    "setflag FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD") < finale.index("removeobject 5")
assert "#define FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD              0x4FF" in flags

print("PRU_ROUTE22_HEIST_INDIGO_GUARD_PASS: Route 22 theft, original badge flags retained, Indigo door locked until Rocket finale")
