#!/usr/bin/env python3
"""Regression contract for Indigo Plateau's compact postgame support row."""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
data = json.loads((ROOT / "data/maps/IndigoPlateau_PokemonCenter_hns/map.json").read_text())
scripts = (ROOT / "data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc").read_text()
specials = (ROOT / "data/specials.inc").read_text()
field = (ROOT / "src/field_specials.c").read_text()

services = [
    "PRU_TrainingHub_Relearner",
    "PRU_SetupTutor",
    "PRU_DoublesTutor",
    "IndigoPlateau_EventScript_HazardTutor",
    "IndigoPlateau_EventScript_CleanupTutor",
    "PRU_TrainingHub_MoveDeleter",
    "PRU_TrainingHub_AbilityNature",
    "PRU_TrainingHub_EvIv",
]
objects = data["object_events"]
row = [o for o in objects if o.get("script") in services]
assert len(row) == len(services)
assert sorted(o["x"] for o in row) == [2, 4, 6, 8, 10, 12, 14, 16]
assert {o["y"] for o in row} == {15}
assert {o["movement_type"] for o in row} == {"MOVEMENT_TYPE_FACE_UP"}
assert len({o["graphics_id"] for o in row}) == len(row)
for service in services:
    assert sum(o.get("script") == service for o in objects) == 1, service
assert all(o.get("script") != "PRU_Elite18_Steward" for o in objects)

# Healing, Mart, BP/legitimate NPCs and the user-requested two Lv100 Chansey remain.
assert any(o.get("script") == "OldaleTown_PokemonCenter_1F_EventScript_Nurse" for o in objects)
assert any(o.get("script") == "BattleFrontier_Mart_EventScript_Clerk" for o in objects)
chansey = [o for o in objects if o.get("graphics_id") == "OBJ_EVENT_GFX_NURSE_CHANSEY_HNS"]
assert len(chansey) == 1 and chansey[0]["script"] == "PRU_ChanseyTrainer_Lv100"

# Every advertised service routes to a real implementation.
for label in ("PRU_TrainingHub_Relearner::", "PRU_SetupTutor::", "PRU_TrainingHub_MoveDeleter::", "PRU_TrainingHub_AbilityNature::", "PRU_TrainingHub_EvIv::"):
    assert label in scripts
assert "Common_EventScript_MoveRelearner" in scripts
assert "SELECT_PC_MON_PJR_CONTROL_TUTOR" in scripts
assert "special SwitchMonAbility" in scripts
assert "special SetHiddenNature" in scripts
for name in ("PRU_SetSelectedMonPerfectIVs", "PRU_SetSelectedMonPhysicalEVs", "PRU_SetSelectedMonSpecialEVs", "PRU_SetSelectedMonBulkyEVs", "PRU_ResetSelectedMonEVs"):
    assert f"def_special {name}" in specials
    assert f"void {name}(void)" in field

print("PASS: Indigo support services form one stationary row; Lv100 Chansey and core facilities remain")
