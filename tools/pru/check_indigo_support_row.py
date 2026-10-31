#!/usr/bin/env python3
"""Regression contract for Indigo Plateau's compact postgame support row."""
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
data = json.loads((ROOT / "data/maps/IndigoPlateau_PokemonCenter_hns/map.json").read_text())
scripts = (ROOT / "data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc").read_text()
specials = (ROOT / "data/specials.inc").read_text()
field = (ROOT / "src/field_specials.c").read_text()

services = [
    "PRU_TrainingHub_Relearner",
    "PRU_TrainingHub_EggTutor",
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
assert sorted(o["x"] for o in row) == list(range(6, 15)), "all nine NPCs must stand together on the open floor"
assert {o["y"] for o in row} == {15}
assert {o["movement_type"] for o in row} == {"MOVEMENT_TYPE_FACE_UP"}
assert len({o["graphics_id"] for o in row}) == len(row)
assert [o["script"] for o in sorted(row, key=lambda o: o["x"])] == services

# Characterization regression: this particular 35x18 GBA map has VOID at
# x=2..4 and an occupied wall/statue at x=5. The previous source-only test
# accepted nine coordinates even though only six NPCs rendered in-game.
layout_path = ROOT / "data/layouts/IndigoPlateau_PokemonCenter_hns/map.bin"
tiles = struct.unpack("<630H", layout_path.read_bytes())
floor_metatiles = {641, 665, 666, 667}
for npc in row:
    tile = tiles[npc["y"] * 35 + npc["x"]] & 0x3FF
    assert tile in floor_metatiles, f'{npc["script"]} is standing on a wall, statue or outside the room: ({npc["x"]}, {npc["y"]}), tile={tile}'
for service in services:
    assert sum(o.get("script") == service for o in objects) == 1, service
    section = scripts.split(f"{service}::", 1)[1].split("\n\n", 1)[0]
    assert "MSGBOX_YESNO" in section, f"{service} must introduce its service and ask first"
    assert "goto_if_eq VAR_RESULT, NO" in section, f"{service} must permit declining"
assert all(o.get("script") != "PRU_Elite18_Steward" for o in objects)

# Healing, Mart, BP/legitimate NPCs and the user-requested two Lv100 Chansey remain.
assert any(o.get("script") == "OldaleTown_PokemonCenter_1F_EventScript_Nurse" for o in objects)
assert any(o.get("script") == "PRU_IndigoPlateau_HeldItemsClerk" for o in objects)
assert "pokemart PRU_IndigoPlateau_HeldItemMart" in scripts
assert "ITEM_WEAKNESS_POLICY" in scripts and "ITEM_THROAT_SPRAY" in scripts
chansey = [o for o in objects if o.get("graphics_id") == "OBJ_EVENT_GFX_NURSE_CHANSEY_HNS"]
assert len(chansey) == 1 and chansey[0]["script"] == "PRU_ChanseyTrainer_Lv100"

# Every advertised service routes to a real implementation.
for label in ("PRU_TrainingHub_Relearner::", "PRU_TrainingHub_EggTutor::", "PRU_SetupTutor::", "PRU_TrainingHub_MoveDeleter::", "PRU_TrainingHub_AbilityNature::", "PRU_TrainingHub_EvIv::"):
    assert label in scripts
assert "setmoverelearnerstate MOVE_RELEARNER_LEVEL_UP_MOVES" in scripts
assert "setmoverelearnerstate MOVE_RELEARNER_EGG_MOVES" in scripts
assert "SELECT_PC_MON_PJR_CONTROL_TUTOR" in scripts
assert "special SwitchMonAbility" in scripts
assert "special SetHiddenNature" in scripts
for name in ("PRU_SetSelectedMonPerfectIVs", "PRU_SetSelectedMonPhysicalEVs", "PRU_SetSelectedMonSpecialEVs", "PRU_SetSelectedMonBulkyEVs", "PRU_ResetSelectedMonEVs"):
    assert f"def_special {name}" in specials
    assert f"void {name}(void)" in field

print("PASS: nine adjacent Indigo support services introduce themselves; Lv100 Chansey and core facilities remain")
