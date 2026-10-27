#!/usr/bin/env python3
"""Guard the party-menu gate that must agree with PRU tutor eligibility."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
party = (ROOT / "src/party_menu.c").read_text(encoding="utf-8")
choosebox = (ROOT / "src/chooseboxmon.c").read_text(encoding="utf-8")
party_header = (ROOT / "include/party_menu.h").read_text(encoding="utf-8")

match = re.search(
    r"static enum CanMoveBeLearned CanTeachMove\(struct Pokemon \*mon, enum Move move\)\n\{(.*?)\n\}",
    party,
    re.S,
)
assert match, "party-menu move eligibility function missing"
gate = match.group(0)
assert "CanLearnTeachableMove(species, move)" in gate, (
    "ordinary TM/tutor compatibility was not preserved"
)
assert "CanSpeciesLearnPruTutorMoveForParty(species, move," in gate, (
    "party menu still uses the fragile PC-selection-state gate"
)
assert "gPartyMenu.action == PARTY_ACTION_MOVE_TUTOR" in gate, (
    "PRU-only eligibility could leak into TM teaching"
)
assert "CanSpeciesLearnPruTutorMoveForParty" in party_header
assert "sSelectionType != SELECT_PC_MON_PJR_CONTROL_TUTOR" in choosebox
assert "sSelectionType != SELECT_PC_MON_PRU_DOUBLE_TUTOR" in choosebox
assert "CanSpeciesLearnSelectedPruTutorMove" in party_header
print("PASS: party tutor eligibility matches its PC selector; TM compatibility stays standard")
