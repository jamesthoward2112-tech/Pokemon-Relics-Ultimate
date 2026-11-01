#!/usr/bin/env python3
"""PRU Johto/Kanto Escape Rope pickup and Indigo tutor source audit.

Run from the repo root: python3 test/test_pru_escape_rope_and_tutors.py
Source validation only: a compiled ROM and actual battle/overworld tests
are required separately before claiming this patch is playable.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
MAPS = ROOT / "data" / "maps"


def load(path):
    return (ROOT / path).read_text(encoding="utf-8")


# Never repurpose the actual reusable Escape Rope item or its save ID.
config = load("include/config/item.h")
item_info = load("src/data/items.h")
assert "#define I_KEY_ESCAPE_ROPE               GEN_8" in config
rope = item_info.split("[ITEM_ESCAPE_ROPE] =", 1)[1].split("    },", 1)[0]
assert ".pocket = POCKET_KEY_ITEMS" in rope
assert "ItemUseOutOfBattle_EscapeRope" in rope

lab = load("data/maps/NewBarkTown_Lab_hns/scripts.inc")
assert lab.count("giveitem ITEM_ESCAPE_ROPE") == 2, "First and old-save recovery Key Items missing"
assert "checkitem ITEM_ESCAPE_ROPE, 1" in lab

# Physical item balls and hidden/background pickups have DIFFERENT entry
# points. Existing Escape Rope map data can safely remain unchanged because
# these award-time paths substitute the TM before the receipt text/bag add.
ball = load("src/item_ball.c")
hidden = load("src/field_control_avatar.c")
header = load("include/item_ball.h")
assert "enum Item GetPruEscapeRopePickupTm(void)" in ball
assert "enum Item GetPruEscapeRopePickupTm(void);" in header
assert "if (itemId == ITEM_ESCAPE_ROPE)" in ball
assert "return GetPruEscapeRopePickupTm();" in ball
assert "if (gSpecialVar_0x8005 == ITEM_ESCAPE_ROPE)" in hidden
assert "gSpecialVar_0x8005 = GetPruEscapeRopePickupTm();" in hidden
assert "gSpecialVar_0x8009 = 1;" in hidden and "gSpecialVar_0x8009 = 1;" in ball

# All directly scripted HNS pickups/rewards (which bypass the central
# conversion), and specialty mart stock, need manual replacement. The only
# legitimate Rope in an HNS script is Elm's early/recovery key-item handout
# and its ownership check. Other game modes are intentionally unaffected.
remaining = []
for path in sorted(MAPS.glob("*_hns/scripts.inc")):
    for lineno, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        stripped = line.strip()
        if "ITEM_ESCAPE_ROPE" not in stripped or stripped.startswith(("@", "//")):
            continue
        if path.parent.name == "NewBarkTown_Lab_hns" and stripped in (
            "giveitem ITEM_ESCAPE_ROPE", "checkitem ITEM_ESCAPE_ROPE, 1"
        ):
            continue
        remaining.append(f"{path.relative_to(ROOT)}:{lineno}: {stripped}")

# The two explicitly converted scripted rewards retain their original
# local object flags and labels, and teach valid TMs rather than Rope.
replacements = (
    ("MtMortar_1F_North_hns", "MtMortar_1F_North_EventScript_Item_EscapeRope", "ITEM_TM_BRICK_BREAK"),
    ("WhirlIslands_B1F_hns", "WhirlIslands_B1F_EventScript_Item_Escape_Rope", "ITEM_TM_SWORDS_DANCE"),
)
for map_name, label, item in replacements:
    script = load(f"data/maps/{map_name}/scripts.inc")
    assert label in script and item in script, f"{map_name} replacement missing"

assert not remaining, "HNS scripted Rope loot remains:\n  " + "\n  ".join(remaining)

shops = load("src/shop.c")
assert "ITEM_ESCAPE_ROPE" not in shops, "Obsolete shop Escape Rope stock remains"
assert "sPruCherrygroveTMStock" in shops and "GetShopPurchasePrice" in shops

plateau = load("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
chooser = load("src/chooseboxmon.c")
for suffix, move in (("EerieFog", "EERIE_FOG"), ("ScaryFace", "SCARY_FACE")):
    assert f"IndigoPlateau_EventScript_TutorTeach_{suffix}::" in plateau
    assert f"setvar VAR_0x8005, MOVE_{move}" in plateau
    assert f"IndigoPlateau_Text_TutorMove_{suffix}" in plateau
    assert f"case MOVE_{move}:" in chooser

moves = load("src/data/moves_info.h")
scary = moves.split("[MOVE_SCARY_FACE] =", 1)[1].split("\n    [MOVE_", 1)[0]
assert ".effect = EFFECT_SPEED_DOWN_2" in scary
assert ".additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_FEAR" not in scary, (
    "Scary Face must not fire a duplicate Fear via generic secondary effects"
)
battle = load("data/battle_scripts_1.s")
assert "BattleScript_PRU_ScaryFaceFear::" in battle
assert "seteffectprimary BS_ATTACKER, BS_TARGET, MOVE_EFFECT_FEAR" in battle
assert "jumpifword CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_NO_EFFECT" in battle
assert "volatiles.fearTimer = 2;" in load("src/battle_script_commands.c")

print("PASS: reusable key Escape Rope preserved; both pickup types convert to badge-scaled TMs")
print("PASS: no direct scripted HNS Escape Rope loot remains apart from deliberate Key Item handouts")
print("PASS: existing item rewards, marts and Indigo tutors are source-wired")
print("PASS: Scary Face Speed drop + single guarded Fear effect are source-wired")
print("NOTE: source audit only; compilation and emulator tests have NOT been run")
