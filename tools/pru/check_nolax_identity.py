#!/usr/bin/env python3
"""Regression guard: Nolax is light, quick and never inherits Snorlax's food/sleep moves."""
from __future__ import annotations
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
species = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
level = (ROOT / "src/data/pokemon/level_up_learnsets/prl_evolution_overrides.h").read_text()
teachable = (ROOT / "src/data/pokemon/teachable_learnsets/pru.h").read_text()
moves = (ROOT / "include/constants/moves.h").read_text()

# New weight argument is in tenths of kg; other Red Relics remain unchanged.
macro = species.split("#define PJR_RED_SPECIES", 1)[1].split("#undef PJR_RED_SPECIES", 1)[0]
assert ".weight = weightKgTenths" in macro, "Nolax weight still shared with other Red Relics"
nolax = macro.split("PJR_RED_SPECIES(SPECIES_NOLAX,", 1)[1].split("),", 1)[0]
assert re.search(r"^\s*100, 130, 80, 45, 90, 130,", nolax), "Nolax speed/attack changed"
assert "ABILITY_INSOMNIA" in nolax
assert "sNolaxLevelUpLearnset, sNolaxTeachableLearnset, 280, 0, 8, 3" in nolax
assert "sSnorlaxTeachableLearnset" not in nolax
for name in ("Edensaur", "Charaxis", "Fortotoise", "Khang", "Noxichu"):
    block = macro.split(f"PJR_RED_SPECIES(SPECIES_{name.upper()},", 1)[1].split("),", 1)[0]
    assert re.search(r", 600, [^,]+, [^,]+, [^,]+\s*$", block), name

def moves_in_block(source: str, symbol: str) -> list[str]:
    hit = re.search(r"static const (?:struct LevelUpMove|u16)\s+" +
                    re.escape(symbol) + r"\[\]\s*=\s*\{([^}]+)\};", source, re.S)
    assert hit, f"Missing moveset: {symbol}"
    return re.findall(r"\bMOVE_[A-Z0-9_]+", hit.group(1))

levels = moves_in_block(level, "sNolaxLevelUpLearnset")
tms = moves_in_block(teachable, "sNolaxTeachableLearnset")
assert "MOVE_EXTREME_SPEED" in levels and "MOVE_AGILITY" in levels
assert "MOVE_U_TURN" in levels and "MOVE_ACROBATICS" in levels
assert "MOVE_UNAVAILABLE" == tms[-1]
assert len(set(tms)) == len(tms), "Duplicate Nolax teachable move"

banned = {
    "MOVE_HEAVY_SLAM", "MOVE_HEAT_CRASH", "MOVE_BODY_SLAM", "MOVE_GIGA_IMPACT",
    "MOVE_REST", "MOVE_SLEEP_TALK", "MOVE_SNORE", "MOVE_YAWN", "MOVE_RECYCLE",
    "MOVE_SWALLOW", "MOVE_SPIT_UP", "MOVE_STOCKPILE", "MOVE_STUFF_CHEEKS",
    "MOVE_BELCH", "MOVE_TEATIME", "MOVE_TEA_TIME", "MOVE_SLACK_OFF",
    "MOVE_COVET", "MOVE_FLING",
}
assert not (banned & set(levels + tms)), sorted(banned & set(levels + tms))
assert all(name in moves for name in set(levels + tms) - {"MOVE_UNAVAILABLE"}), "Undefined move"
assert len(levels) >= 13 and len(tms) >= 30
print("PASS: Nolax 28.0 kg, base Speed 130, Insomnia, agile level/TM sets, no heavy/sleep/berry moves")
