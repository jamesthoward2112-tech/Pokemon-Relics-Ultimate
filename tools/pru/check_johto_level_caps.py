#!/usr/bin/env python3
"""Check PRU challenge caps against the eight HnS Johto Gym Leader teams."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
caps_source = (root / "src/caps.c").read_text()
party_source = (root / "src/data/trainers_hns.party").read_text()
leader_order = ("FALKNER", "BUGSY", "WHITNEY", "MORTY", "CHUCK", "JASMINE", "PRYCE", "CLAIR")
expected_aces = (16, 22, 27, 33, 39, 43, 38, 52)
expected_normal = (16, 22, 27, 33, 39, 43, 43, 52, 56)
expected_hard = (12, 18, 23, 29, 35, 39, 39, 48, 54)

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
    assert ace == expected_aces[index], f"{trainer} ace changed: expected {expected_aces[index]}, found {ace}"
    assert normal[index] == expected_normal[index], (trainer, "Normal", normal[index])
    assert hard[index] == expected_hard[index], (trainer, "Hard", hard[index])
assert [normal[i] for i in range(9)] == list(expected_normal)
assert [hard[i] for i in range(9)] == list(expected_hard)
assert all(normal[i] >= normal[i - 1] for i in range(1, 9)), "Normal caps must never decrease after a badge"
assert all(hard[i] >= hard[i - 1] for i in range(1, 9)), "Hard caps must never decrease after a badge"
# Chuck/Jasmine/Pryce may be beaten in different orders: badge-count
# progression must stay playable even when the next leader has a lower ace.
assert normal[6] >= normal[5] >= ace_level("PRYCE")
assert hard[6] >= hard[5], "Hard cap must not drop from 39 to 34"
assert "challengeSettings.tx_Challenges_LevelCap" in caps_source
assert "return sLevelCapTable_Normal[badgeCount]" in caps_source
assert "return sLevelCapTable_Hard[badgeCount]" in caps_source
print("JOHTO_LEVEL_CAPS_PASS: all 8 leader aces verified and Normal/Hard caps never decrease")
