#!/usr/bin/env python3
"""Ensure PRU's Rocket heist rematches get their own fixed Rhythm scenes."""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
source = (ROOT / "src/battle_bg.c").read_text()
manifest = json.loads((ROOT / "assets/pru_rhythm/background_manifest.json").read_text())
dojo = 45  # Already approved martial-arts hall used by Chuck.
giovanni = 51  # Already approved final-challenge hall used by Blue.

assert manifest["entries"][dojo]["visible_sha256"] != manifest["entries"][giovanni]["visible_sha256"]
assert "TestRunner_Battle_GetForcedEnvironment()" in source
section = source.split("// Rocket badge-heist story battles", 1)[1].split(
    "// Distinct Gym Leader arenas", 1
)[0]
for leader in ("BROCK", "MISTY", "SURGE", "ERIKA", "JANINE", "SABRINA", "BLAINE"):
    assert f"case TRAINER_PRU_HEIST_{leader}_HNS:" in section
dojo_block, finale_block = section.split("case TRAINER_PRU_HEIST_GIOVANNI_HNS:")
assert "return 45;" in dojo_block
assert "return 51;" in finale_block
assert "return 45;" not in finale_block
assert source.index("// Rocket badge-heist story battles") < source.index("// Distinct Gym Leader arenas")

# Guard against accidentally overriding each leader's ordinary Gym scenery.
regular = source.split("// Distinct Gym Leader arenas", 1)[1].split(
    "// Wild and regular trainer fights", 1
)[0]
for token, expected in (
    ("TRAINER_BROCK_HNS", 35),
    ("TRAINER_MISTY_HNS", 48),
    ("TRAINER_LTSURGE_HNS", 46),
    ("TRAINER_ERIKA_HNS", 9),
    ("TRAINER_JANINE_HNS", 31),
    ("TRAINER_SABRINA_HNS", 19),
    ("TRAINER_BLAINE_HNS", 16),
    ("TRAINER_BLUE_HNS", 51),
):
    assert re.search(rf"case {token}:.*?return {expected};", regular, flags=re.S), token
print("PRU_DOJO_GIOVANNI_BACKGROUNDS_PASS: 7 indoor dojo rematches, separate final arena, original Gym scenery retained")
