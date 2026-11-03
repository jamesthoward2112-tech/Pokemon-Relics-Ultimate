#!/usr/bin/env python3
"""Focused source regression for Job 4: TM54 and reusable Escape Rope loot conversion."""

from pathlib import Path
import json
import re

ROOT = Path(__file__).resolve().parents[1]
MAPS = ROOT / "data/maps"


def read(path):
    return (ROOT / path).read_text(encoding="utf-8")


def require(ok, message):
    if not ok:
        raise AssertionError(message)


# TM54 keeps its old save ID, move mapping, price, field use and non-KO effect.
tms = read("include/constants/tms_hms.h").split("#if IS_HNS", 1)[1].split("#else", 1)[0]
tm_list = tms.split("#define FOREACH_TM(F)", 1)[1].split("#define FOREACH_HM(F)", 1)[0]
require(re.findall(r"\bF\(([A-Z_0-9]+)\)", tm_list)[53] == "FALSE_SWIPE", "TM54 must stay False Swipe")
items = read("include/constants/items.h")
require("ITEM_TM54 = 635" in items, "TM54 save ID changed")
require("CAT(ITEM_TM_, id) = CAT(ITEM_TM, n)" in items, "Generated TM54 alias missing")
tm_data = read("src/data/items.h")
tm54 = re.search(r"\[ITEM_TM54\]\s*=\s*// False Swipe\s*\{([\s\S]*?)\n    \},", tm_data)
require(tm54 is not None, "TM54 data entry missing")
for text in (".price = 3000", ".pocket = POCKET_TM_HM", ".type = ITEM_USE_PARTY_MENU",
             ".fieldUseFunc = ItemUseOutOfBattle_TMHM"):
    require(text in tm54.group(1), f"TM54 data changed: {text}")
move_data = read("src/data/moves_info.h")
false_swipe = move_data.split("[MOVE_FALSE_SWIPE]", 1)[1].split("\n    [MOVE_", 1)[0]
require(".effect = EFFECT_FALSE_SWIPE" in false_swipe, "False Swipe no longer prevents KOs")
require("FOREACH_TM(UNPACK_ITEM_TO_TM_MOVE_ID)" in read("include/item.h"), "TM move mapping missing")
require("CanTeachMove(mon, move)" in read("src/party_menu.c"), "TM teachability check missing")

# TM54 is in the early scripted list, the later badge stock, and both requested TM counters.
cherry = read("data/maps/CherrygroveCity_Mart_hns/scripts.inc")
early = cherry.split("Cherrygrove_Pokemart_Pokemart:", 1)[1].split("ITEM_NONE", 1)[0]
require("ITEM_TM_FALSE_SWIPE" in early, "Pre-Poké Ball Cherrygrove list lacks TM54")
require("pokemart 0" in cherry, "Later badge-dependent stock path was removed")
shop = read("src/shop.c")
for fragment in ("sPruCherrygroveTMStock", "MAP_GROUP(MAP_CHERRYGROVE_CITY_MART_HNS)",
                 "MAP_NUM(MAP_CHERRYGROVE_CITY_MART_HNS)",
                 "sPruCherrygroveTMStock[i++] = ITEM_TM_FALSE_SWIPE;",
                 "sMartInfo.itemList = sPruCherrygroveTMStock;"):
    require(fragment in shop, f"Later Cherrygrove stock extension missing: {fragment}")
for path, label in (
    ("data/maps/GoldenrodCity_DepartmentStore_5F_hns/scripts.inc", "GoldenrodDeptStore5_Pokemart:"),
    ("data/maps/CeladonCity_DepartmentStore_3F_hns/scripts.inc", "CeladonDept3_Pokemart:"),
):
    stock = read(path).split(label, 1)[1].split("pokemartlistend", 1)[0]
    require(stock.count("ITEM_TM_FALSE_SWIPE") == 1, f"{path} must stock TM54 exactly once")

# Escape Rope itself retains ID, reusable Key Item placement and field-use handler.
config = read("include/config/item.h")
rope_data = tm_data.split("[ITEM_ESCAPE_ROPE] =", 1)[1].split("\n    },", 1)[0]
require("#define I_KEY_ESCAPE_ROPE               GEN_8" in config, "Escape Rope ceased being a Key Item")
require("ITEM_ESCAPE_ROPE = 120" in items and ".pocket = POCKET_KEY_ITEMS" in rope_data
        and "ItemUseOutOfBattle_EscapeRope" in rope_data, "Reusable Escape Rope identity/use changed")

lab = read("data/maps/NewBarkTown_Lab_hns/scripts.inc")
require(lab.count("giveitem ITEM_ESCAPE_ROPE") == 2, "Initial grant and old-save recovery missing")
require(re.search(r"setflag FLAG_RECEIVED_FIRST_BALLS\s+(?:@[^\n]*\n\s*)?giveitem ITEM_ESCAPE_ROPE", lab) is not None,
        "Initial reusable Rope must follow the Poké Ball progression event")
require("checkitem ITEM_ESCAPE_ROPE, 1" in lab
        and "goto_if_eq VAR_RESULT, TRUE, PRU_Elm_RopeCheckDone" in lab,
        "Elm recovery must avoid duplicate Key Items")

# Shared badge-tier resolution handles all 16 HNS badges; both separate pickup paths use it.
header = read("include/item_ball.h")
balls = read("src/item_ball.c")
hidden = read("src/field_control_avatar.c")
require("enum Item GetPruEscapeRopePickupTm(void);" in header, "Shared helper declaration missing")
require("enum Item GetPruEscapeRopePickupTm(void)" in balls and "FLAG_BADGE01_GET + NUM_BADGES" in balls,
        "Badge count helper missing or not sized for HNS")
for tm in ("BULLET_SEED", "ROCK_TOMB", "BRICK_BREAK", "SHADOW_BALL", "ROOST", "ROCK_SLIDE", "EARTHQUAKE"):
    require(f"return ITEM_TM_{tm};" in balls, f"Badge pickup reward TM {tm} missing")
require("return GetPruEscapeRopePickupTm();" in balls
        and "gSpecialVar_0x8009 = 1;" in balls, "Visible balls must convert and award exactly one TM")
require("gSpecialVar_0x8005 = GetPruEscapeRopePickupTm();" in hidden
        and "gSpecialVar_0x8009 = 1;" in hidden, "Hidden pickups must convert and award exactly one TM")

# Keep the original object/script labels and flags while replacing direct static scripted rewards.
scripted = (
    ("MtMortar_1F_North_hns", "MtMortar_1F_North_hns", "MtMortar_1F_North_EventScript_Item_EscapeRope",
     "ITEM_TM_BRICK_BREAK", "FLAG_ITEM_MTMORTAR2_ESCAPE_ROPE", (52, 22), "OBJ_EVENT_GFX_POKE_BALL"),
    ("WhirlIslands_B1F_hns", "WhirlIslands_B1F_hns", "WhirlIslands_B1F_EventScript_Item_Escape_Rope",
     "ITEM_TM_SWORDS_DANCE", "FLAG_ITEM_WHIRL_ISLANDS_B2F_ESCAPE_ROPE", (57, 9), "OBJ_EVENT_GFX_ITEM_BALL_HNS"),
    ("SproutTower_3F_hns", "SproutTower_3F_hns", "SproutTower_3F_EventScript_EscapeRope",
     "ITEM_TM_BULLET_SEED", "FLAG_ITEM_SPROUT_TOWER_ESCAPE_ROPE", (16, 3), "OBJ_EVENT_GFX_POKE_BALL"),
    ("TinTower_3F_hns", "TinTower_4F_hns", "TinTower_4F_EventScript_Item_EscapeRope",
     "ITEM_TM_ROCK_SLIDE", "FLAG_ITEM_TIN_TOWER_4F_ESCAPE_ROPE", (15, 17), "OBJ_EVENT_GFX_POKE_BALL"),
)
for script_map, event_map, label, tm, flag, coords, graphics in scripted:
    scripts = read(f"data/maps/{script_map}/scripts.inc")
    body = scripts.split(label + "::", 1)[1].split("\n\n", 1)[0]
    require(tm in body and "ITEM_ESCAPE_ROPE" not in body, f"{script_map}: static Rope reward not replaced")
    events = json.loads((MAPS / event_map / "map.json").read_text(encoding="utf-8"))["object_events"]
    matching = [event for event in events if event.get("script") == label]
    require(len(matching) == 1, f"{event_map}: original item ball is missing/duplicated")
    event = matching[0]
    require((event["x"], event["y"]) == coords and event["flag"] == flag
            and event["graphics_id"] == graphics,
            f"{event_map}: item ball location, pickup flag or graphics changed")

# No ordinary HNS map script or shop can still sell/give Escape Rope.
remaining = []
for path in sorted(MAPS.glob("*_hns/scripts.inc")):
    for line_no, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        stripped = line.strip()
        if "ITEM_ESCAPE_ROPE" in stripped and not stripped.startswith(("@", "//")):
            if path.parent.name == "NewBarkTown_Lab_hns" and stripped in (
                "giveitem ITEM_ESCAPE_ROPE", "checkitem ITEM_ESCAPE_ROPE, 1"
            ):
                continue
            remaining.append(f"{path.relative_to(ROOT)}:{line_no}: {stripped}")
require(not remaining, "Ordinary HNS Escape Rope reward remains:\n" + "\n".join(remaining))

expected_shop = {
    "ZeroBadges": "BULLET_SEED", "OneBadge": "ROCK_TOMB", "TwoBadges": "AERIAL_ACE",
    "ThreeBadges": "BRICK_BREAK", "FourBadges": "FACADE", "FiveBadges": "SHADOW_BALL",
    "SixBadges": "ROOST", "SevenBadges": "ROCK_SLIDE", "EightBadges": "EARTHQUAKE",
}
for tier, tm in expected_shop.items():
    for suffix in ("", "_PC"):
        stock = re.search(r"static const u16 sShopInventory_" + tier + suffix + r"\[\] = \{(.*?)\};", shop, re.S)
        require(stock is not None and f"ITEM_TM_{tm}" in stock.group(1),
                f"Badge tier {tier}{suffix} missing its progressive replacement")
        require("ITEM_ESCAPE_ROPE" not in stock.group(1), f"Badge tier {tier}{suffix} still sells Escape Rope")
require("ITEM_ESCAPE_ROPE" not in shop, "Obsolete Escape Rope stock remains in HNS shop arrays")
require("GetShopPurchasePrice" in shop, "Ecruteak Rock Shop pricing function was lost")

# All replacement TM constants exist only in HNS tables; generic engine data remains unchanged.
active_tm_defs = read("include/constants/tms_hms.h").split("#if IS_HNS", 1)[1].split("#else", 1)[0]
for tm in {"BULLET_SEED", "ROCK_TOMB", "AERIAL_ACE", "BRICK_BREAK", "FACADE", "SHADOW_BALL",
           "ROOST", "ROCK_SLIDE", "EARTHQUAKE", "SWORDS_DANCE"}:
    require(f"F({tm})" in active_tm_defs, f"Replacement TM {tm} is not an active HNS TM")

print("PASS: TM54 ID, price, False Swipe effect and teaching path retained; all three mart paths stock it")
print("PASS: Escape Rope remains reusable; Elm grants it once and recovers it for older saves")
print("PASS: visible/hidden Rope pickups award one badge-tier TM; all direct HNS loot and shop stock audited")
print("NOTE: source regression only; ROM build and gameplay/emulator interactions remain separate checks")
