#!/usr/bin/env python3
"""Check that the Rhythm assets are wired into every ordinary PRU battle."""

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
code = (ROOT / "src/battle_bg.c").read_text()
art = (ROOT / "src/graphics.c").read_text()
gfx = (ROOT / "src/data/pru_rhythm_gfx.h").read_text()
table = (ROOT / "src/data/pru_rhythm_bg_table.h").read_text()
manifest = json.loads((ROOT / "assets/pru_rhythm/background_manifest.json").read_text())

assert '#include "data/pru_rhythm_gfx.h"' in art
assert '#include "data/pru_rhythm_bg_table.h"' in code
assert '#include "data/pru_crystal_gfx.h"' not in art
assert '#include "data/pru_crystal_bg_table.h"' not in code
assert "sPruRhythmBattleBgs[55]" in table
assert "const struct PruRhythmBattleBg *bg = &sPruRhythmBattleBgs[pruRhythmBg]" in code

# Every entry must remain selectable, even when two indices share an image.
reachable = set()
for group in ("Grass", "Water", "Cave", "Rock", "Ice", "Urban", "Volcano", "Burial"):
    pool = re.search(r"sPruRhythm" + group + r"\[\] = \{([^}]*)\}", code)
    assert pool is not None, group
    choices = [int(x) for x in re.findall(r"\d+", pool.group(1))]
    assert choices and all(0 <= index < 55 for index in choices), group
    if group == "Grass":
        assert not {13, 23, 18, 27}.intersection(choices), "Snow or graveyard scene on warm grass routes"
    reachable.update(choices)
assert reachable == set(range(55)), sorted(set(range(55)) - reachable)

# Each Gym Leader, including all rematches, must use that same leader's
# dedicated backdrop; the 16 leaders must have different backgrounds.
leaders = (
    "FALKNER", "BUGSY", "WHITNEY", "MORTY", "CHUCK", "JASMINE",
    "PRYCE", "CLAIR", "BROCK", "MISTY", "LTSURGE", "ERIKA",
    "JANINE", "SABRINA", "BLAINE", "BLUE",
)
gym_indices = []
for leader in leaders:
    rematch_cases = re.findall(
        r"case TRAINER_" + leader + r"(?:_\w+)?_HNS:", code
    )
    assert len(rematch_cases) >= 2, leader
    match = re.search(
        r"case TRAINER_" + leader + r"(?:_\w+)?_HNS:(?:\s*case TRAINER_\w+_HNS:)*\s*return (\d+);",
        code,
    )
    assert match is not None, leader
    gym_indices.append(int(match.group(1)))
assert len(set(gym_indices)) == 16

assert "case MAP_SEAFOAM_ISLANDS_SECRET_CAVE_HNS:\n        return 48;" in code
assert "case MAP_MT_SILVER_1F_MOLTRES_ROOM_HNS:\n        return 16;" in code
assert "case MAP_LAVENDER_SPIRIT_TOWER_7F_HNS:\n        return 44;" in code
assert "TestRunner_Battle_GetForcedEnvironment()" in code
for flag in ("BATTLE_TYPE_LINK", "BATTLE_TYPE_FRONTIER", "BATTLE_TYPE_RECORDED_LINK"):
    assert flag in code
assert "return 0xFF;" in code

# Check table pointers resolve to 44 canonical sets instead of emitting 55
# identical blocks, and that each alias really has the same image pixels.
entries = re.findall(
    r"\{gPruRhythmTiles_(\d{2}), gPruRhythmMap_(\d{2}), gPruRhythmPal_(\d{2})\}", table
)
assert len(entries) == 55, len(entries)
by_source = {}
for i, pointers in enumerate(entries):
    assert len(set(pointers)) == 1, (i, pointers)
    index = int(pointers[0])
    assert 0 <= index < 55
    assert f"gPruRhythmTiles_{index:02d}[] = INCBIN_U32(" in gfx
    assert f"gPruRhythmMap_{index:02d}[] = INCBIN_U32(" in gfx
    assert f"gPruRhythmPal_{index:02d}[] = INCBIN_U16(" in gfx
    by_source.setdefault(index, []).append(i)
    assert manifest["entries"][i]["visible_sha256"] == manifest["entries"][index]["visible_sha256"]
assert len(by_source) == 44, len(by_source)

for accessor in ("bg->tiles", "bg->tilemap", "bg->palette"):
    assert accessor in code
for stage in ("tiles", "tilemap", "palette"):
    assert f"sPruRhythmBattleBgs[pruBg].{stage}" in code

assert "bool8 IsPruCrystalBattleBgActive(void)" in code  # Legacy static-viewport hook
print("PASS: 55 Rhythm entries are reachable, 16 unique Gyms and static/fallback loading intact")
