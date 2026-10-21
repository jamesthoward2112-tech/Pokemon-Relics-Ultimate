#!/usr/bin/env python3
"""Guard the Bell Tower 9F statue-corridor finale against accidental floor/coordinate regressions."""
import json
import struct
from pathlib import Path

maps = Path("data/maps")
eight = json.loads((maps / "TinTower_8F_hns/map.json").read_text())
nine = json.loads((maps / "TinTower_9F_hns/map.json").read_text())
flag = "FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED"
assert not any(o.get("flag") == flag for o in eight["object_events"]), "Jessie and James still on 8F"

expected = {
    "OBJ_EVENT_GFX_JESSIE_HNS": (11, 3),
    "OBJ_EVENT_GFX_JAMES_HNS": (13, 3),
    "OBJ_EVENT_GFX_MON_BASE+SPECIES_MEOWTH": (12, 3),
}
found = {o["graphics_id"]: (o["x"], o["y"]) for o in nine["object_events"] if o.get("flag") == flag}
assert found == expected, f"Final trio misplaced on 9F: {found}"
assert all(o["script"] == "TinTower_9F_EventScript_JessieJamesInteract" for o in nine["object_events"] if o.get("flag") == flag)
warps = {(w["x"], w["y"]) for w in nine["warp_events"]}
# Nearest unobstructed floor row against the upper statue wall. Existing warp
# tiles must stay free, and the trio must form an adjacent, unbroken line.
assert not warps.intersection(expected.values()), "Finale NPC blocks a warp"
assert any(w["x"] == 9 and w["y"] == 5 and w["dest_map"] == "MAP_TIN_TOWER_8F_HNS" for w in nine["warp_events"]), "Legacy warp changed"
assert sorted(expected.values()) == [(11, 3), (12, 3), (13, 3)], "Trio not adjacent at the saved player location"
assert all(o.get("flag") == flag for o in nine["object_events"] if o["graphics_id"] in expected), "Finale objects must disappear after battle"
# 9F (NOT 8F): 9 and 16 are the two statues seen in the user's final video frames.
layout = Path("data/layouts/TinTower_9F_hns/map.bin").read_bytes()
width = 21
tiles = struct.unpack("<" + "H" * (len(layout) // 2), layout)
tile = lambda x, y: tiles[y * width + x] & 0x3FF
assert tile(9, 3) == tile(16, 3) == 0x249, "This is not the two-statue 9F corridor"
assert all(tile(x, y) == 0x324 for x, y in expected.values()), "Trio not on saved upper wall row"
script9 = (maps / "TinTower_9F_hns/scripts.inc").read_text()
script8 = (maps / "TinTower_8F_hns/scripts.inc").read_text()
assert "trainerbattle_double TRAINER_JESSIE_JAMES_TINTOWER_HNS" in script9
assert "map_script MAP_SCRIPT_ON_FRAME_TABLE, TinTower_9F_OnFrame" in script9
expected_triggers = {(15, 6), (16, 6), (10, 5), (15, 5), (16, 5)}
actual_triggers = {(v["x"],v["y"]) for v in nine["coord_events"] if v["script"]=="TinTower_9F_EventScript_JessieJamesTrigger"}
assert actual_triggers == expected_triggers, f"Mandatory approach triggers missing: {actual_triggers}"
assert all(v["var"] == "VAR_TEMP_0" and v["var_value"] == "1" for v in nine["coord_events"]), "Approach must respect one-time story gate"
assert script9.count("removeobject 6") == 2
assert "setflag FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED" in script9
# Verify the battle does not immediately erase the trio: all three physically
# depart to the right and down before removal.
aftermath = script9.split("TinTower_9F_EventScript_JessieJamesBattle::", 1)[1].split("TinTower_9F_EventScript_NoFinalRocket::", 1)[0]
assert aftermath.index("msgbox TinTower_9F_Text_JessieJamesFinalAfter") < aftermath.index("applymovement 5, TinTower_9F_Movement_JamesExit")
exit_start = aftermath.index("applymovement 5, TinTower_9F_Movement_JamesExit")
exit_wait = aftermath.index("waitmovement 0", exit_start)
assert exit_start < exit_wait < aftermath.index("removeobject 4"), "Objects removed before completed walk-off"
for name in ("JamesExit", "MeowthExit", "JessieExit"):
    segment = script9.split("TinTower_9F_Movement_" + name + ":", 1)[1].split("step_end", 1)[0]
    assert "walk_right" in segment and "walk_down" in segment, "Missing east then south exit for " + name
    assert segment.index("walk_right") < segment.index("walk_down"), "Incorrect exit route for " + name
assert "removeobject 4" in script9 and "removeobject 5" in script9
assert "delay 32" in aftermath
assert "TinTower_9F_EventScript_JessieJamesBattle" in script9
assert "JessieJamesBattle" not in script8
print("PASS: Bell Tower 9F trio at save coordinate (12,3), flanked by Jessie and James, forced approach triggers and staggered walk-off scripts")
