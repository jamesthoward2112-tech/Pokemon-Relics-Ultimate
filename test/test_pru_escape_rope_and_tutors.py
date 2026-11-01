#!/usr/bin/env python3
"""PRU pickup and Indigo source regression (no build required).

Run from the repo root: python3 test/test_pru_escape_rope_and_tutors.py
Do not promote the stage while the remaining pickup audit fails.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
maps = ROOT / "data" / "maps"
remaining = []
for file in sorted(maps.glob("*_hns/scripts.inc")):
    for lineno, line in enumerate(file.read_text(encoding="utf-8").splitlines(), 1):
        if re.search(r"^\s*(?:finditem|giveitem|additem|checkitem|itemball)\s+ITEM_ESCAPE_ROPE\b", line):
            remaining.append(f"{file.relative_to(ROOT)}:{lineno}: {line.strip()}")
for path in sorted(maps.glob("*_hns/map.json")):
    text = path.read_text(encoding="utf-8")
    if '"ITEM_ESCAPE_ROPE"' in text:
        remaining.append(f"{path.relative_to(ROOT)}: map JSON has Escape Rope")

assert not remaining, "Unreplaced PRU Escape Rope placements:\n  " + "\n  ".join(remaining)
config = (ROOT / "include/config/item.h").read_text()
assert "#define I_KEY_ESCAPE_ROPE               GEN_8" in config
scripts = (maps / "IndigoPlateau_PokemonCenter_hns/scripts.inc").read_text()
for suffix, move in (("EerieFog", "EERIE_FOG"), ("ScaryFace", "SCARY_FACE")):
    assert f"IndigoPlateau_EventScript_TutorTeach_{suffix}::" in scripts
    assert f"setvar VAR_0x8005, MOVE_{move}" in scripts
    assert f"IndigoPlateau_Text_TutorMove_{suffix}" in scripts
moves = (ROOT / "src/data/moves_info.h").read_text()
scary = moves.split("[MOVE_SCARY_FACE] =", 1)[1].split("\n    [MOVE_", 1)[0]
assert ".effect = EFFECT_SPEED_DOWN_2" in scary
assert "MOVE_EFFECT_FEAR, .chance = 100" in scary
print("PASS: no collectible Escape Rope in any HNS map scripts or JSON")
print("PASS: original Escape Rope item remains a Key Item")
print("PASS: Indigo tutors select Eerie Fog and Scary Face")
print("PASS: Scary Face retains Speed-down and adds Fear (runtime still needs testing)")
