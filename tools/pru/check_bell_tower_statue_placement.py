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
    "OBJ_EVENT_GFX_JESSIE_HNS": (9, 5),
    "OBJ_EVENT_GFX_JAMES_HNS": (11, 5),
    "OBJ_EVENT_GFX_MON_BASE+SPECIES_MEOWTH": (10, 5),
}
found = {o["graphics_id"]: (o["x"], o["y"]) for o in nine["object_events"] if o.get("flag") == flag}
assert found == expected, f"Final trio misplaced on 9F: {found}"
assert all(o["script"] == "TinTower_9F_EventScript_JessieJamesInteract" for o in nine["object_events"] if o.get("flag") == flag)
warps = {(w["x"], w["y"]) for w in nine["warp_events"]}
# The legacy map defines a warp EVENT at (9,5). That does not establish that a
# visible staircase is at Jessie's sprite. Check for unexpected overlaps without
# making a claim about physical stairs or in-game encounter behaviour.
assert warps.intersection(expected.values()) == {(9, 5)}, "Unexpected map warp overlap"
assert any(w["x"] == 9 and w["y"] == 5 and w["dest_map"] == "MAP_TIN_TOWER_8F_HNS" for w in nine["warp_events"]), "Legacy map warp changed"
assert all(o.get("flag") == flag for o in nine["object_events"] if o["graphics_id"] in expected), "Finale objects must disappear after battle"
# 9F (NOT 8F): 9 and 16 are the two statues seen in the user's final video frames.
layout = Path("data/layouts/TinTower_9F_hns/map.bin").read_bytes()
width = 21
tiles = struct.unpack("<" + "H" * (len(layout) // 2), layout)
tile = lambda x, y: tiles[y * width + x] & 0x3FF
assert tile(9, 3) == tile(16, 3) == 0x249, "This is not the two-statue 9F corridor"
assert all(tile(x, y) in (0x2E0, 0x23D) for x, y in expected.values()), "Trio is not in the intended corridor"
script9 = (maps / "TinTower_9F_hns/scripts.inc").read_text()
script8 = (maps / "TinTower_8F_hns/scripts.inc").read_text()
assert "trainerbattle_double TRAINER_JESSIE_JAMES_TINTOWER_HNS" in script9
assert "map_script MAP_SCRIPT_ON_FRAME_TABLE, TinTower_9F_OnFrame" in script9
assert script9.count("removeobject 6") == 2
assert "setflag FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED" in script9
assert "removeobject 4" in script9 and "removeobject 5" in script9
assert "TinTower_9F_EventScript_JessieJamesBattle" in script9
assert "JessieJamesBattle" not in script8
print("PASS: Bell Tower 9F trio at 9/10/11, with declared map-warp overlap; gameplay still needs testing")
