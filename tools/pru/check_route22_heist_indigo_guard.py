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
field_engine = read("src/field_control_avatar.c")

# The Kanto Route 22 reception entrance is the heist location, not Route 26.
assert route22["region"] == "REGION_KANTO"
assert any(w["x"] == 12 and w["y"] == 9 and w["dest_map"] == "MAP_RECEPTION_GATE_HNS"
           for w in route22["warp_events"])
for gfx in ("OBJ_EVENT_GFX_JESSIE_HNS", "OBJ_EVENT_GFX_JAMES_HNS",
            "OBJ_EVENT_GFX_MON_BASE+SPECIES_MEOWTH", "OBJ_EVENT_GFX_PRU_MEOWTH_BALLOON_HNS"):
    assert any(o["graphics_id"] == gfx for o in route22["object_events"]), gfx
    assert not any(o["graphics_id"] == gfx for o in reception["object_events"]), gfx
assert not any(e["script"] == "Route22_EventScript_PRUHeistTrigger"
               for e in route22["coord_events"]), "theft must not auto-trigger from a tile"
rocket_npcs = [o for o in route22["object_events"] if o["graphics_id"] in (
    "OBJ_EVENT_GFX_JESSIE_HNS", "OBJ_EVENT_GFX_JAMES_HNS", "OBJ_EVENT_GFX_MON_BASE+SPECIES_MEOWTH")]
assert len(rocket_npcs) == 3
assert all(o["script"] == "Route22_EventScript_PRUHeistTrigger" for o in rocket_npcs)
assert [(o["x"], o["y"]) for o in rocket_npcs] == [(11, 11), (13, 11), (12, 11)]
assert "call Route22_EventScript_PRUSyncRocket" in scripts22
assert "goto_if_unset FLAG_BADGE16_GET, Route22_EventScript_PRUHeistNoop" in scripts22
assert "goto_if_set FLAG_PRU_HEIST_STARTED, Route22_EventScript_PRUHeistNoop" in scripts22
assert "setflag FLAG_PRU_HEIST_STARTED" in scripts22
# The original regression used local ID 14 (Meowth) for the balloon (ID 15).
assert "clearflag FLAG_PRU_HIDE_MEOWTH_BALLOON" in scripts22
assert "addobject 15" in scripts22
assert "applymovement 15, Route22_Movement_PRUBalloonDepart" in scripts22
# In mapjson, LOCALIDs are one-based positions in object_events, NOT names or guesses.
route22_ids = {o["graphics_id"]: index + 1 for index, o in enumerate(route22["object_events"])}
assert route22_ids["OBJ_EVENT_GFX_JESSIE_HNS"] == 12
assert route22_ids["OBJ_EVENT_GFX_JAMES_HNS"] == 13
assert route22_ids["OBJ_EVENT_GFX_MON_BASE+SPECIES_MEOWTH"] == 14
assert route22_ids["OBJ_EVENT_GFX_PRU_MEOWTH_BALLOON_HNS"] == 15
assert route22["object_events"][10]["graphics_id"] == "OBJ_EVENT_GFX_SMALL_LIGHT_HNS"
balloon22 = next(o for o in route22["object_events"] if o["graphics_id"] == "OBJ_EVENT_GFX_PRU_MEOWTH_BALLOON_HNS")
assert (balloon22["x"], balloon22["y"]) == (20, 12), "balloon must enter beside the courtyard, not over the gate roof"
assert balloon22["flag"] == "FLAG_PRU_HIDE_MEOWTH_BALLOON"
heist = scripts22.split("Route22_EventScript_PRUHeistTrigger::", 1)[1].split("Route22_EventScript_PRUHeistNoop::", 1)[0]
assert heist.index("applymovement 12, Route22_Movement_PRUJessieGather") < heist.index("addobject 15")
assert heist.index("applymovement 13, Route22_Movement_PRUJamesGather") < heist.index("addobject 15")
assert heist.index("applymovement 14, Route22_Movement_PRUMeowthReady") < heist.index("addobject 15")
assert heist.index("addobject 15") < heist.index("applymovement 15, Route22_Movement_PRUBalloonArrive")
assert heist.index("waitmovement 15") < heist.index("applymovement 12, Route22_Movement_PRUJessieBoard")
assert "applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark" in heist
assert "applymovement 11, Common_Movement_ExclamationMark" not in heist
assert heist.index("applymovement 12, Route22_Movement_PRUJessieBoard") < heist.index("waitmovement 12", heist.index("applymovement 12, Route22_Movement_PRUJessieBoard")) < heist.index("removeobject 12")
assert heist.index("removeobject 12") < heist.index("applymovement 13, Route22_Movement_PRUJamesBoard")
assert heist.index("applymovement 13, Route22_Movement_PRUJamesBoard") < heist.index("removeobject 13")
assert heist.index("removeobject 13") < heist.index("applymovement 14, Route22_Movement_PRUMeowthBoard")
assert heist.index("applymovement 14, Route22_Movement_PRUMeowthBoard") < heist.index("removeobject 14")
assert "removeobject 11" not in heist, "do not delete the unrelated Route 22 light"
assert heist.index("removeobject 14") < heist.index("applymovement 15, Route22_Movement_PRUBalloonDepart")
assert "applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark" in heist
assert "waitmovement VAR_LAST_TALKED" in heist
assert "applymovement 12, Common_Movement_ExclamationMark" not in heist
assert "addobject 14" not in heist and "removeobject 15" in heist
assert heist.index("applymovement 15") < heist.index("removeobject 15")
# Model tile movement from actual source commands to catch missing or reversed approach/flight.
def movement_delta(scripts, label):
    script = scripts.split(f"{label}:\n", 1)[1].split("\tstep_end", 1)[0]
    steps = [line.strip() for line in script.splitlines()]
    assert steps, f"{label}: no movement commands"
    dx = steps.count("walk_fast_right") - steps.count("walk_fast_left")
    dy = steps.count("walk_fast_down") - steps.count("walk_fast_up")
    return dx, dy

assert movement_delta(scripts22, "Route22_Movement_PRUJessieGather") == (0, 0)
assert movement_delta(scripts22, "Route22_Movement_PRUJamesGather") == (0, 0)
assert movement_delta(scripts22, "Route22_Movement_PRUBalloonArrive") == (-8, 0)
assert movement_delta(scripts22, "Route22_Movement_PRUBalloonDepart") == (8, 0)
for name in ("JessieBoard", "JamesBoard", "MeowthBoard"):
    assert movement_delta(scripts22, f"Route22_Movement_PRU{name}") == (0, 1)
assert "playse SE_M_FLY" in heist
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
# Walking onto the League warp must run a blocking script BEFORE warp handling.
# NPC collision alone is not sufficient, as shown by gameplay video.
assert any(e["x"] == door["x"] and e["y"] == door["y"]
           and e["script"] == "IndigoPlateau_EventScript_PRUDoorGate" 
           for e in indigo["coord_events"]), "missing scripted League entrance guard"
gate = scripts_indigo.split("IndigoPlateau_EventScript_PRUDoorGate::", 1)[1].split(
    "IndigoPlateau_Text_PRUGuard:", 1)[0]
assert "ShouldBlockIndigoPlateauRocketDoor" in field_engine, "field engine must intercept auto door warps"
door_func = field_engine.split("static bool8 TryDoorWarp(struct MapPosition *position", 1)[1].split("static s8 GetWarpEventAtPosition", 1)[0]
assert door_func.index("ShouldBlockIndigoPlateauRocketDoor(position)") < door_func.index("DoDoorWarp()"), "must check lock before door auto-warp"
assert "goto_if_unset FLAG_PRU_HEIST_STARTED" in gate
assert "goto_if_set FLAG_PRU_HEIST_COMPLETED" in gate
assert "msgbox IndigoPlateau_Text_PRUGuard" in gate
assert "warp MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS, 19, 15" in gate
assert gate.index("msgbox IndigoPlateau_Text_PRUGuard") < gate.index("warp MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS")
balloon_indigo = next(o for o in indigo["object_events"] if o["graphics_id"] == "OBJ_EVENT_GFX_PRU_MEOWTH_BALLOON_HNS")
assert (balloon_indigo["x"], balloon_indigo["y"]) == (19, 10)
assert balloon_indigo["flag"] == "FLAG_PRU_HIDE_MEOWTH_BALLOON"
assert "clearflag FLAG_PRU_HIDE_MEOWTH_BALLOON" in scripts_indigo
assert "addobject 4" in scripts_indigo

sync = scripts_indigo.split("IndigoPlateau_EventScript_PRUSyncRocket::", 1)[1].split(
    "IndigoPlateau_EventScript_PRUSyncDone::", 1)[0]
assert "goto_if_unset FLAG_PRU_HEIST_STARTED" in sync
assert "goto_if_set FLAG_PRU_HEIST_COMPLETED" in sync
assert sync.index("clearflag FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD") < sync.index(
    "goto_if_unset FLAG_PRU_HEIST_GIOVANNI")
finale = scripts_indigo.split("IndigoPlateau_EventScript_PRUEscape::", 1)[1].split(
    "IndigoPlateau_Text_PRURocketIntro:", 1)[0]
assert finale.index("addobject 4") < finale.index("applymovement 4, IndigoPlateau_Movement_PRUBalloonArrive")
assert finale.index("applymovement 4, IndigoPlateau_Movement_PRUBalloonArrive") < finale.index("applymovement 1, IndigoPlateau_Movement_PRUJessieBoard")
assert finale.index("applymovement 1, IndigoPlateau_Movement_PRUJessieBoard") < finale.index("removeobject 1")
assert finale.index("removeobject 1") < finale.index("applymovement 2, IndigoPlateau_Movement_PRUJamesBoard")
assert finale.index("applymovement 2, IndigoPlateau_Movement_PRUJamesBoard") < finale.index("removeobject 2")
assert finale.index("removeobject 2") < finale.index("applymovement 3, IndigoPlateau_Movement_PRUMeowthBoard")
assert finale.index("applymovement 3, IndigoPlateau_Movement_PRUMeowthBoard") < finale.index("removeobject 3")
assert finale.index("removeobject 3") < finale.index("applymovement 4, IndigoPlateau_Movement_PRUBalloonDepart")
assert "removeobject 4" in finale
assert finale.index("applymovement 4, IndigoPlateau_Movement_PRUBalloonDepart") < finale.index("removeobject 4")
assert movement_delta(scripts_indigo, "IndigoPlateau_Movement_PRUBalloonArrive") == (-8, 0)
assert movement_delta(scripts_indigo, "IndigoPlateau_Movement_PRUBalloonDepart") == (8, 0)
for name in ("JessieBoard", "JamesBoard", "MeowthBoard"):
    assert movement_delta(scripts_indigo, f"IndigoPlateau_Movement_PRU{name}") == (0, 1)
assert finale.index("setflag FLAG_PRU_HEIST_COMPLETED") < finale.index(
    "setflag FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD") < finale.index("removeobject 5")
assert "#define FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD              0x4FF" in flags

print("PRU_ROUTE22_HEIST_INDIGO_GUARD_PASS: Route 22 theft, original badge flags retained, Indigo door locked until Rocket finale")
