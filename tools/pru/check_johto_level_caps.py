#!/usr/bin/env python3
"""Check PRU challenge caps against the eight HnS Johto Gym Leader teams."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
caps_source = (root / "src/caps.c").read_text()
party_source = (root / "src/data/trainers_hns.party").read_text()
leader_order = ("FALKNER", "BUGSY", "WHITNEY", "MORTY", "CHUCK", "JASMINE", "PRYCE", "CLAIR")
expected_normal = (16, 22, 27, 33, 39, 43, 38, 52)
expected_hard = (12, 18, 23, 29, 35, 39, 34, 48)

# Preserve each explicit index rather than relying on source order.
def indexed_caps(name: str) -> dict[int, int]:
    section = caps_source.split(f"static const u8 sLevelCapTable_{name}[] =", 1)[1].split("};", 1)[0]
    return {int(index): int(value) for index, value in re.findall(r"\[(\d+)\]\s*=\s*(\d+)", section)}

def ace_level(trainer: str) -> int:
    marker = f"=== TRAINER_{trainer}_1_HNS ==="
    section = party_source.split(marker, 1)[1].split("=== ", 1)[0]
    levels = [int(value) for value in re.findall(r"^Level:\s*(\d+)\s*$", section, re.MULTILINE)]
    assert levels, f"No levels found for {trainer}"
    return max(levels)

normal = indexed_caps("Normal")
hard = indexed_caps("Hard")
for index, trainer in enumerate(leader_order):
    ace = ace_level(trainer)
    assert ace == expected_normal[index], f"{trainer} ace changed: expected {expected_normal[index]}, found {ace}"
    assert normal[index] == ace, f"Normal cap before {trainer} must be {ace}; got {normal[index]}"
    assert hard[index] == ace - 4, f"Hard cap before {trainer} must be {ace - 4}; got {hard[index]}"
assert normal[8] == 56 and hard[8] == 54, "Post-eighth-badge caps should remain unchanged"
assert "challengeSettings.tx_Challenges_LevelCap" in caps_source
assert "return sLevelCapTable_Normal[badgeCount]" in caps_source
assert "return sLevelCapTable_Hard[badgeCount]" in caps_source
print("JOHTO_LEVEL_CAPS_PASS: Normal and Hard caps match all 8 Gym Leaders")
