#!/usr/bin/env python3
"""Check contextual Rhythm scene routing for both PRU championships."""

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
source = (ROOT / "src/battle_bg.c").read_text()
start = source.index("static u8 GetPruRhythmBattleBgIndex")
end = source.index("static void LoadBattleEnvironmentGfx", start)
body = source[start:end]

expected = {
    "TRAINER_WILL_1_HNS": 19,
    "TRAINER_WILL_2_HNS": 19,
    "TRAINER_WILL_POSTOBC_HNS": 19,
    "TRAINER_KOGA_1_HNS": 39,
    "TRAINER_KOGA_2_HNS": 39,
    "TRAINER_KOGA_POSTOBC_HNS": 39,
    "TRAINER_BRUNO_1_HNS": 8,
    "TRAINER_BRUNO_2_HNS": 8,
    "TRAINER_BRUNO_POSTOBC_HNS": 8,
    "TRAINER_KAREN_1_HNS": 38,
    "TRAINER_KAREN_2_HNS": 38,
    "TRAINER_KAREN_POSTOBC_HNS": 38,
    "TRAINER_LANCE_1_HNS": 30,
    "TRAINER_LANCE_2_HNS": 30,
    "TRAINER_LANCE_3_HNS": 30,
    "TRAINER_LANCE_POSTOBC_HNS": 30,
    "TRAINER_PRU_KANTO_E4_LORELEI_HNS": 14,
    "TRAINER_PRU_KANTO_E4_BRUNO_HNS": 8,
    "TRAINER_PRU_KANTO_E4_AGATHA_HNS": 18,
    "TRAINER_PRU_KANTO_E4_LANCE_HNS": 30,
    "TRAINER_PRU_KANTO_E4_RED_HNS": 13,
    "TRAINER_RED_POSTOBC_HNS": 13,
}

for trainer, scene in expected.items():
    match = re.search(
        rf"case {trainer}:((?:\s*case [A-Z0-9_]+:)*)\s*return (\d+);",
        body,
    )
    assert match and int(match.group(2)) == scene, (trainer, scene)

assert "GetPruRhythmBattleBgIndex(GetBattleEnvironmentOverride())" in source
assert "BATTLE_TYPE_FRONTIER | BATTLE_TYPE_LINK" in source
print("PASS: both League rosters route to the 10 approved Rhythm scenes by trainer ID")
