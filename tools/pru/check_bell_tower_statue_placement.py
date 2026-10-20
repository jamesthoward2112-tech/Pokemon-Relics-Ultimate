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
    "OBJ_EVENT_GFX_JESSIE_HNS": (11, 5),
    "OBJ_EVENT_GFX_JAMES_HNS": (14, 5),
    "OBJ_EVENT_GFX_MON_BASE+SPECIES_MEOWTH": (12, 5),
}
found = {o["graphics_id"]: (o["x"], o["y"]) for o in nine["object_events"] if o.get("flag") == flag}
assert found == expected, f"Final trio misplaced on 9F: {found}"
assert all(o["script"] == "TinTower_9F_EventScript_JessieJamesInteract" for o in nine["object_events"] if o.get("flag") == flag)
warps = {(w["x"], w["y"]) for w in nine["warp_events"]}
assert not warps.intersection(expected.values()), "Finale sprite overlaps a warp"
# 9F (NOT 8F): 9 and 16 are the two statues seen in the user's final video frames.
layout = Path("data/layouts/TinTower_9F_hns/map.bin").read_bytes()
width = 21
tiles = struct.unpack("<" + "H" * (len(layout) // 2), layout)
tile = lambda x, y: tiles[y * width + x] & 0x3FF
assert tile(9, 3) == tile(16, 3) == 0x249, "This is not the two-statue 9F corridor"
assert all(tile(x, y) == 0x23D for x, y in expected.values()), "Trio is not on the upper wall corridor"
script9 = (maps / "TinTower_9F_hns/scripts.inc").read_text()
script8 = (maps / "TinTower_8F_hns/scripts.inc").read_text()
assert "trainerbattle_double TRAINER_JESSIE_JAMES_TINTOWER_HNS" in script9
assert "map_script MAP_SCRIPT_ON_FRAME_TABLE, TinTower_9F_OnFrame" in script9
assert script9.count("removeobject 6") == 2
assert "JessieJamesBattle" not in script8
print("PASS: Bell Tower 9F right-hand statue gap, trio positions, original double battle and no 8F duplicates")
