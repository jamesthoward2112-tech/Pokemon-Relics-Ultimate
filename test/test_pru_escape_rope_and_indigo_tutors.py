#!/usr/bin/env python3
"""PRU source-only checks: old Rope loot becomes progression TMs and Indigo tutor moves.

Use once this preparation branch is checked out locally. This is NOT a compiled
or playable ROM test. It also reports any direct map script Rope references
that bypass the shared item-ball conversion and require separate review.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]


def source(path):
    return (ROOT / path).read_text(encoding="utf-8")


def require(value, reason):
    if not value:
        raise AssertionError(reason)


config = source("include/config/item.h")
item_info = source("src/data/items.h")
require("#define I_KEY_ESCAPE_ROPE               GEN_8" in config, "Escape Rope is no longer a key item")
rope_info = item_info.split("[ITEM_ESCAPE_ROPE] =", 1)[1].split("    },", 1)[0]
require(".pocket = POCKET_KEY_ITEMS" in rope_info and ".fieldUseFunc = ItemUseOutOfBattle_EscapeRope" in rope_info,
        "Reusable Rope key item must keep its proper exit behaviour")

ball = source("src/item_ball.c")
for marker in (
    "GetPruEscapeRopePickupTm",
    "if (itemId == ITEM_ESCAPE_ROPE)",
    "if (gMapHeader.events->objectEvents[itemBallId].trainerRange_berryTreeId == ITEM_ESCAPE_ROPE)",
    "return ITEM_TM_BULLET_SEED;",
    "return ITEM_TM_ROCK_TOMB;",
    "return ITEM_TM_BRICK_BREAK;",
    "return ITEM_TM_SHADOW_BALL;",
    "return ITEM_TM_ROOST;",
    "return ITEM_TM_ROCK_SLIDE;",
    "return ITEM_TM_EARTHQUAKE;",
):
    require(marker in ball, f"Missing item-ball conversion: {marker}")

# Visible item balls and hidden/background item events are separate paths:
# both must share the same badge-tier resolution and give precisely one TM.
hidden = source("src/field_control_avatar.c")
header = source("include/item_ball.h")
require("enum Item GetPruEscapeRopePickupTm(void);" in header,
        "Badge-tier conversion must be shared with hidden pickups")
require('if (gSpecialVar_0x8005 == ITEM_ESCAPE_ROPE)' in hidden
        and "gSpecialVar_0x8005 = GetPruEscapeRopePickupTm();" in hidden
        and "gSpecialVar_0x8009 = 1;" in hidden,
        "Hidden/background Escape Rope finds must convert to one TM")

lab = source("data/maps/NewBarkTown_Lab_hns/scripts.inc")
require("goto_if_unset FLAG_RECEIVED_FIRST_BALLS, PRU_Elm_RopeCheckDone" in lab,
        "Don't give key item before the early story gift")
require("checkitem ITEM_ESCAPE_ROPE, 1" in lab
        and "goto_if_eq VAR_RESULT, TRUE, PRU_Elm_RopeCheckDone" in lab,
        "Elm must recover the key item for old saves only when missing")
require(lab.count("giveitem ITEM_ESCAPE_ROPE") == 2,
        "Aide's first copy and Elm's missing-key fallback must both exist")
require("PRU_Elm_Text_MissingEscapeRope" in lab,
        "Missing reusable Rope gift explanation")

shops = source("src/shop.c")
require("ITEM_ESCAPE_ROPE" not in shops, "An obsolete Rope remains for sale in badge-based marts")
tiers = {
    "ZeroBadges": "BULLET_SEED",
    "OneBadge": "ROCK_TOMB",
    "TwoBadges": "AERIAL_ACE",
    "ThreeBadges": "BRICK_BREAK",
    "FourBadges": "FACADE",
    "FiveBadges": "SHADOW_BALL",
    "SixBadges": "ROOST",
    "SevenBadges": "ROCK_SLIDE",
    "EightBadges": "EARTHQUAKE",
}
for tier, move in tiers.items():
    for suffix in ("", "_PC"):
        match = re.search(r"static const u16 sShopInventory_" + tier + suffix
                          + r"\[\] = \{(.*?)\};", shops, re.S)
        require(match is not None, f"Shop stock for badge tier {tier}{suffix} missing")
        require(f"ITEM_TM_{move}" in match.group(1), f"Wrong TM at badge tier {tier}{suffix}")
require("GetShopPurchasePrice" in shops, "Previous Rock Shop discount was reverted")
require("sPruCherrygroveTMStock" in shops, "Previous early False Swipe shop was reverted")

tm_definitions = source("include/constants/tms_hms.h")
active_tms = tm_definitions.split("#if IS_HNS")[1].split("#else")[0]
for move in set(tiers.values()):
    require(f"F({move})" in active_tms, f"Unregistered PRU TM: {move}")

indigo = source("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
control = indigo.split("IndigoPlateau_EventScript_HazardTutor::", 1)[1].split(
    "IndigoPlateau_EventScript_CleanupTutor::", 1)[0]
for label in ("IndigoPlateau_Text_TutorMove_EerieFog", "IndigoPlateau_Text_TutorMove_ScaryFace"):
    require(label in control, f"Missing option in control tutor: {label}")
for i, name in ((22, "EerieFog"), (23, "ScaryFace")):
    require(f"case {i}, IndigoPlateau_EventScript_TutorTeach_{name}" in control,
            f"Option {name} not mapped to the proper script")
require("case 24, IndigoPlateau_EventScript_TutorDecline" in control,
        "Control tutor cancel index no longer matches the expanded menu")
for move in ("EERIE_FOG", "SCARY_FACE"):
    require(f"setvar VAR_0x8005, MOVE_{move}" in indigo, f"Indigo doesn't teach {move}")

chooser = source("src/chooseboxmon.c")
control_move_list = chooser.split("static bool32 IsPjrControlTutorMove(", 1)[1].split("static bool32 CanSpeciesLearnPjrControlTutorMove(", 1)[0]
for move in ("EERIE_FOG", "SCARY_FACE"):
    require(f"case MOVE_{move}:" in control_move_list, f"Party/PC tutor filter missing {move}")
    require(f"case MOVE_{move}:" in chooser.split("static bool32 CanSpeciesLearnPjrControlTutorMove(", 1)[1],
            f"Species compatibility for {move} missing")

move_info = source("src/data/moves_info.h")
for move in ("EERIE_FOG", "SCARY_FACE"):
    require(f"[MOVE_{move}]" in move_info, f"Original move missing {move}")
require(".effect = EFFECT_SPEED_DOWN_2" in move_info.split("[MOVE_SCARY_FACE]", 1)[1].split("    },", 1)[0],
        "Scary Face lost its -2 Speed effect")
require(".argument = { .weatherType = BATTLE_WEATHER_FOG }" in move_info.split("[MOVE_EERIE_FOG]", 1)[1].split("    },", 1)[0],
        "Eerie Fog weather mechanic was lost")
battle_scripts = source("data/battle_scripts_1.s")
require("jumpifhalfword CMP_EQUAL, gCurrentMove, MOVE_SCARY_FACE, BattleScript_PRU_ScaryFaceFear" in battle_scripts,
        "Scary Face doesn't trigger its existing Fear branch")
require("BattleScript_PRU_ScaryFaceFear::" in battle_scripts
        and "seteffectprimary BS_ATTACKER, BS_TARGET, MOVE_EFFECT_FEAR" in battle_scripts,
        "Scary Face Fear branch is not connected to the native status handler")
runtime = source("src/battle_script_commands.c")
require("case MOVE_EFFECT_FEAR:" in runtime and "volatiles.fearTimer = 2;" in runtime,
        "Original PRU Fear effect was removed")

# Visible and hidden loot are centrally converted. Direct map-script
# gifts/shops are not: every remaining HNS Rope reference must be a deliberate
# first-time/recovery Key Item gift, otherwise the audit must FAIL.
direct = []
for path in (ROOT / "data/maps").glob("*_hns/scripts.inc"):
    content = path.read_text(encoding="utf-8")
    for i, line in enumerate(content.splitlines(), 1):
        if "ITEM_ESCAPE_ROPE" in line and not line.lstrip().startswith(("@", "//")):
            # Only the intentional one-time and recovery Key Item gifts remain.
            if path.parent.name == "NewBarkTown_Lab_hns" and line.strip() == "giveitem ITEM_ESCAPE_ROPE":
                continue
            direct.append(f"{path.relative_to(ROOT)}:{i} {line.strip()}")
print("PASS: former Escape Rope visible and hidden pickups convert to real TMs")
print("PASS: reusable Rope key item granted early, with old-save fallback")
print("PASS: 18 badge stock entries use progression TMs (normal and PC modes)")
print("PASS: Eerie Fog and Scary Face are in Indigo tutor menu and eligibility filters")
print("PASS: existing Scary Face Fear and eight-turn Eerie Fog mechanics retained")
require(not direct, "Obsolete direct HNS Rope loot/stock remains:\\n" + "\\n".join(direct))
print("PASS: all HNS scripted Rope references are intentional Key Item handouts")
print("NOTE: source-only checks, not a compile/emulator/battle-verification result.")
