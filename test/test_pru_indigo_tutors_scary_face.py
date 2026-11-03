#!/usr/bin/env python3
"""Focused source regression for the Indigo tutor additions and Scary Face Fear."""
from pathlib import Path
import json
import re

ROOT = Path(__file__).resolve().parents[1]


def read(path):
    return (ROOT / path).read_text(encoding="utf-8")


def move_block(source, move):
    return source.split(f"[{move}] =", 1)[1].split("\n    },", 1)[0]


def menu_choices(section):
    match = re.search(r"dynmultichoice[^\n]*DYN_MULTICHOICE_CB_NONE, ([^\n]+)", section)
    assert match, "Tutor choice menu missing"
    return [entry.strip() for entry in match.group(1).split(",")]


maps = read("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
objects = json.loads(read("data/maps/IndigoPlateau_PokemonCenter_hns/map.json"))["object_events"]
scripts = {obj["script"] for obj in objects}
for service in (
    "IndigoPlateau_EventScript_HazardTutor",
    "IndigoPlateau_EventScript_CleanupTutor",
    "PRU_DoublesTutor",
    "PRU_SetupTutor",
    "PRU_TrainingHub_EggTutor",
    "PRU_TrainingHub_Relearner",
    "PRU_TrainingHub_MoveDeleter",
    "PRU_TrainingHub_AbilityNature",
    "PRU_TrainingHub_EvIv",
):
    assert service in scripts, f"Existing Indigo tutor/service NPC missing: {service}"

# Retain the four hazard choices, the existing long-scroll menu, and add both
# new options without shifting any old index or the cancel result.
hazard = maps.split("IndigoPlateau_EventScript_HazardTutor::", 1)[1].split(
    "IndigoPlateau_EventScript_CleanupTutor::", 1
)[0]
choices = menu_choices(hazard)
assert choices[:4] == [
    "IndigoPlateau_Text_TutorMove_StealthRock",
    "IndigoPlateau_Text_TutorMove_Spikes",
    "IndigoPlateau_Text_TutorMove_ToxicSpikes",
    "IndigoPlateau_Text_TutorMove_StickyWeb",
]
assert choices[-3:] == [
    "IndigoPlateau_Text_TutorMove_EerieFog",
    "IndigoPlateau_Text_TutorMove_ScaryFace",
    "IndigoPlateau_Text_TutorMove_Cancel",
]
assert len(choices) == len(set(choices))
for index, move in ((22, "EerieFog"), (23, "ScaryFace")):
    assert f"case {index}, IndigoPlateau_EventScript_TutorTeach_{move}" in hazard
assert "case 24, IndigoPlateau_EventScript_TutorDecline" in hazard
for move in ("EerieFog", "ScaryFace"):
    assert f"IndigoPlateau_EventScript_TutorTeach_{move}::" in maps
assert "setvar VAR_0x8005, MOVE_EERIE_FOG" in maps
assert "setvar VAR_0x8005, MOVE_SCARY_FACE" in maps
assert "chooseboxmon SELECT_PC_MON_PJR_CONTROL_TUTOR" in maps
cleanup = maps.split("IndigoPlateau_EventScript_CleanupTutor::", 1)[1].split(
    "IndigoPlateau_EventScript_TutorTeach_StealthRock::", 1
)[0]
assert "IndigoPlateau_Text_TutorMove_Snarl" in cleanup
assert "case 16, IndigoPlateau_EventScript_TutorTeach_Snarl" in cleanup
assert "setvar VAR_0x8005, MOVE_SNARL" in maps

doubles = maps.split("PRU_DoublesTutor::", 1)[1].split("PRU_DoublesTutor_Teach::", 1)[0]
double_choices = menu_choices(doubles)
assert double_choices[:5] == [
    "PRU_DoublesTutor_Text_ShockwaveFist", "PRU_DoublesTutor_Text_Faultline",
    "PRU_DoublesTutor_Text_WraithCry", "PRU_DoublesTutor_Text_MetalBarrage",
    "PRU_DoublesTutor_Text_Mindwave",
]
assert double_choices[5:] == ["PRU_DoublesTutor_Text_Electroweb", "IndigoPlateau_Text_TutorMove_Cancel"]
assert "PRU_DoublesTutor_Text_Electroweb" in doubles
assert "case 5, PRU_DoublesTutor_Electroweb" in doubles
assert "case 6, PRU_Elite18_Exit" in doubles
assert "setvar VAR_0x8005, MOVE_ELECTROWEB" in doubles

setup = maps.split("PRU_SetupTutor::", 1)[1].split("PRU_SetupTutor_Text_Intro:", 1)[0]
setup_choices = menu_choices(setup)
assert setup_choices[:7] == [
    "PRU_SetupTutor_Text_SwordsDance", "PRU_SetupTutor_Text_NastyPlot",
    "PRU_SetupTutor_Text_DragonDance", "PRU_SetupTutor_Text_CalmMind",
    "PRU_SetupTutor_Text_BulkUp", "PRU_SetupTutor_Text_Agility",
    "PRU_SetupTutor_Text_Protect",
]
assert setup_choices[7:] == [
    "PRU_SetupTutor_Text_FollowMe", "PRU_SetupTutor_Text_Reflect",
    "PRU_SetupTutor_Text_DoubleHit", "PRU_SetupTutor_Text_BatonPass",
    "IndigoPlateau_Text_TutorMove_Cancel",
]
assert "case 11, IndigoPlateau_EventScript_TutorDecline" in setup
for move in ("FollowMe", "Reflect", "DoubleHit", "BatonPass"):
    assert f"PRU_SetupTutor_Text_{move}" in setup
    assert f"PRU_SetupTutor_{move}" in setup
    assert f"PRU_SetupTutor_Text_{move}:" in maps
    assert f"setvar VAR_0x8005, MOVE_{re.sub(r'(?<!^)(?=[A-Z])', '_', move).upper()}" in maps

# The existing species-aware tutor gate stays selective. Sticky Web's Bug
# rule remains intact, including Shuckle; Grass remains the only extra type.
chooser = read("src/chooseboxmon.c")
move_gate = chooser.split("static bool32 IsPjrControlTutorMove", 1)[1].split(
    "static bool32 CanSpeciesLearnPjrControlTutorMove", 1
)[0]
eligibility = chooser.split("static bool32 CanSpeciesLearnPjrControlTutorMove", 1)[1].split(
    "static bool32 CanMonLearnPjrControlMove", 1
)[0]
for move in ("EERIE_FOG", "SCARY_FACE"):
    assert f"case MOVE_{move}:" in move_gate
    assert f"case MOVE_{move}:" in eligibility
for move in ("FOLLOW_ME", "REFLECT", "DOUBLE_HIT", "BATON_PASS"):
    assert f"case MOVE_{move}:" in move_gate
    assert f"case MOVE_{move}:" in eligibility
assert "IsSpeciesOfType(species, TYPE_GHOST)" in eligibility
assert "IsSpeciesOfType(species, TYPE_DARK)" in eligibility
assert "IsSpeciesOfType(species, TYPE_PSYCHIC)" in eligibility
assert "IsSpeciesOfType(species, TYPE_POISON)" in eligibility
assert "IsSpeciesOfType(species, TYPE_DRAGON)" in eligibility
sticky = eligibility.split("case MOVE_STICKY_WEB:", 1)[1].split("case MOVE_STONE_AXE:", 1)[0]
assert "IsSpeciesOfType(species, TYPE_BUG)" in sticky
assert "IsSpeciesOfType(species, TYPE_GRASS)" in sticky
double_gate = chooser.split("static bool32 IsPruDoubleTutorMove", 1)[1].split(
    "static bool32 CanSpeciesLearnPruDoubleTutorMove", 1
)[0]
double_eligibility = chooser.split("static bool32 CanSpeciesLearnPruDoubleTutorMove", 1)[1].split(
    "bool32 CanSpeciesLearnPruTutorMove", 1
)[0]
assert "case MOVE_ELECTROWEB:" in double_gate
assert "case MOVE_ELECTROWEB:" in double_eligibility
assert "case MOVE_FOLLOW_ME:" in eligibility
assert "case MOVE_REFLECT:" in eligibility
assert "case MOVE_DOUBLE_HIT:" in eligibility
assert "case MOVE_BATON_PASS:" in eligibility

# Preserve Eerie Fog's existing eight-turn field-weather move data and Scary
# Face's original status signature, Speed reduction, and animation.
moves = read("src/data/moves_info.h")
fog = move_block(moves, "MOVE_EERIE_FOG")
assert ".effect = EFFECT_WEATHER" in fog
assert ".type = TYPE_GHOST" in fog and ".accuracy = 0" in fog and ".pp = 5" in fog
assert ".target = TARGET_FIELD" in fog and ".weatherType = BATTLE_WEATHER_FOG" in fog
scary = move_block(moves, "MOVE_SCARY_FACE")
assert ".effect = EFFECT_SPEED_DOWN_2" in scary
assert ".type = TYPE_NORMAL" in scary and ".accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 100 : 90" in scary
assert ".pp = 10" in scary and ".target = TARGET_SELECTED" in scary
assert ".battleAnimScript = gBattleAnimMove_ScaryFace" in scary
assert ".magicCoatAffected = TRUE" in scary
electroweb = move_block(moves, "MOVE_ELECTROWEB")
assert ".target = TARGET_BOTH" in electroweb

battle = read("data/battle_scripts_1.s")
stat_down = battle.split("BattleScript_EffectStatDown:\n", 1)[1].split(
    "BattleScript_MirrorArmorReflect::", 1
)[0]
assert "attackcanceler" in stat_down
assert "jumpifsubstituteblocks BattleScript_ButItFailed" in stat_down
assert "accuracycheck BattleScript_MoveMissedPause" in stat_down
assert "jumpifhalfword CMP_EQUAL, gCurrentMove, MOVE_SCARY_FACE, BattleScript_PRU_ScaryFaceFear" in stat_down
fear = stat_down.split("BattleScript_PRU_ScaryFaceFear::", 1)[1]
assert "jumpifmoveresultflags MOVE_RESULT_NO_EFFECT, BattleScript_MoveEnd" in fear
assert "seteffectprimary BS_ATTACKER, BS_TARGET, MOVE_EFFECT_FEAR" in fear

handler = read("src/battle_script_commands.c").split("case MOVE_EFFECT_FEAR:", 1)[1].split("case MOVE_EFFECT_PRU_INFATUATION:", 1)[0]
assert "fearTimer == 0" in handler and "fearTimer = 2" in handler
assert "status1" not in handler, "Fear must remain a volatile and not overwrite major status"

print("PASS: all existing Indigo tutor/service NPCs and original hazard choices remain")
print("PASS: Eerie Fog and Scary Face are in the existing tutor with aligned cancel paths")
print("PASS: both moves use selective species compatibility; Shuckle retains Sticky Web")
print("PASS: Eerie Fog data and Scary Face -2 Speed/Fear effect are preserved")
print("NOTE: source-only checks; no battle or menu gameplay is implied")
