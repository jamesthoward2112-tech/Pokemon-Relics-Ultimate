#!/usr/bin/env python3
"""Focused source regression for Job 4A: False Swipe and Max Revive replacements."""

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


# TM54 keeps its original save ID, move mapping, price, field use and non-KO effect.
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

# TM54 remains in both Cherrygrove phases and the two department-store counters.
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

# Rope remains the original reusable Key Item; Elm grants it and recovers missing copies.
config = read("include/config/item.h")
rope_data = tm_data.split("[ITEM_ESCAPE_ROPE] =", 1)[1].split("\n    },", 1)[0]
require("#define I_KEY_ESCAPE_ROPE               GEN_8" in config, "Escape Rope ceased being a Key Item")
require("ITEM_ESCAPE_ROPE = 120" in items and ".pocket = POCKET_KEY_ITEMS" in rope_data
        and "ItemUseOutOfBattle_EscapeRope" in rope_data, "Reusable Escape Rope identity/use changed")
lab = read("data/maps/NewBarkTown_Lab_hns/scripts.inc")
require(lab.count("giveitem ITEM_ESCAPE_ROPE") == 2, "Initial grant and older-save recovery missing")
require(re.search(r"setflag FLAG_RECEIVED_FIRST_BALLS\s+(?:@[^\n]*\n\s*)?giveitem ITEM_ESCAPE_ROPE", lab) is not None,
        "Initial reusable Rope must follow the Poké Ball progression event")
require("checkitem ITEM_ESCAPE_ROPE, 1" in lab
        and "goto_if_eq VAR_RESULT, TRUE, PRU_Elm_RopeCheckDone" in lab,
        "Elm recovery must avoid duplicate Key Items")

# All obsolete visible/hidden Rope pickups resolve to one Max Revive, HNS only.
header = read("include/item_ball.h")
balls = read("src/item_ball.c")
hidden = read("src/field_control_avatar.c")
require("GetPruEscapeRopePickupTm" not in header + balls + hidden,
        "Obsolete badge-tier TM helper/declaration remains")
id_conversion = balls.split("static u32 GetItemBallIdFromTemplate(u32 itemBallId)", 1)[1].split("\n}", 1)[0]
require("#if IS_HNS" in id_conversion and "if (itemId == ITEM_ESCAPE_ROPE)" in id_conversion
        and "return ITEM_MAX_REVIVE;" in id_conversion,
        "Visible HNS Rope item balls must convert directly to a Max Revive")
require("gMapHeader.events->objectEvents[itemBallId].trainerRange_berryTreeId == ITEM_ESCAPE_ROPE" in balls
        and "gSpecialVar_0x8009 = 1;" in balls,
        "Visible converted pickups must award quantity one")
hidden_conversion = hidden.split("gSpecialVar_0x8005 = bgEvent->bgUnion.hiddenItem.item;", 1)[1].split(
    "if (FlagGet(gSpecialVar_0x8004)", 1)[0]
require("#if IS_HNS" in hidden_conversion and "gSpecialVar_0x8005 == ITEM_ESCAPE_ROPE" in hidden_conversion
        and "gSpecialVar_0x8005 = ITEM_MAX_REVIVE;" in hidden_conversion
        and "gSpecialVar_0x8009 = 1;" in hidden_conversion,
        "Hidden HNS Rope pickups must convert to exactly one Max Revive")
require("FLAG_HIDDEN_ITEMS_START" in hidden and "FlagGet(gSpecialVar_0x8004)" in hidden
        and hidden.index("FlagGet(gSpecialVar_0x8004)") > hidden.index("ITEM_MAX_REVIVE;", hidden.index("BG_EVENT_HIDDEN_ITEM")),
        "Hidden-item collection flags/normal receipt path must remain intact")
require("FLAG_BADGE01_GET" not in id_conversion and "ITEM_TM_" not in id_conversion,
        "Visible Rope rewards must not use badge tiers or TMs")
require("ITEM_TM_" not in hidden_conversion, "Hidden Rope rewards must not use TMs")

# Keep each old item-ball script, object coordinate, collection flag and graphics.
scripted = (
    ("MtMortar_1F_North_hns", "MtMortar_1F_North_hns", "MtMortar_1F_North_EventScript_Item_EscapeRope",
     "FLAG_ITEM_MTMORTAR2_ESCAPE_ROPE", (52, 22), "OBJ_EVENT_GFX_POKE_BALL"),
    ("WhirlIslands_B1F_hns", "WhirlIslands_B1F_hns", "WhirlIslands_B1F_EventScript_Item_Escape_Rope",
     "FLAG_ITEM_WHIRL_ISLANDS_B2F_ESCAPE_ROPE", (57, 9), "OBJ_EVENT_GFX_ITEM_BALL_HNS"),
    ("SproutTower_3F_hns", "SproutTower_3F_hns", "SproutTower_3F_EventScript_EscapeRope",
     "FLAG_ITEM_SPROUT_TOWER_ESCAPE_ROPE", (16, 3), "OBJ_EVENT_GFX_POKE_BALL"),
    ("TinTower_3F_hns", "TinTower_4F_hns", "TinTower_4F_EventScript_Item_EscapeRope",
     "FLAG_ITEM_TIN_TOWER_4F_ESCAPE_ROPE", (15, 17), "OBJ_EVENT_GFX_POKE_BALL"),
)
for script_map, event_map, label, flag, coords, graphics in scripted:
    scripts = read(f"data/maps/{script_map}/scripts.inc")
    body = scripts.split(label + "::", 1)[1].split("\n\n", 1)[0]
    require(body.count("finditem ITEM_MAX_REVIVE") == 1 and "ITEM_TM_" not in body
            and "ITEM_ESCAPE_ROPE" not in body,
            f"{script_map}: explicit former Rope pickup must give one Max Revive")
    events = json.loads((MAPS / event_map / "map.json").read_text(encoding="utf-8"))["object_events"]
    matching = [event for event in events if event.get("script") == label]
    require(len(matching) == 1, f"{event_map}: original item ball is missing/duplicated")
    event = matching[0]
    require((event["x"], event["y"]) == coords and event["flag"] == flag
            and event["graphics_id"] == graphics,
            f"{event_map}: original location, pickup flag or graphics changed")

# Full HNS script audit: only the legitimate lab Key Item gift/check may remain.
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
require(not remaining, "Obsolete direct HNS Escape Rope loot remains:\n" + "\n".join(remaining))
require("ITEM_ESCAPE_ROPE" not in shop, "Obsolete Escape Rope shop stock remains")

# This patch must not alter existing TM consumption/reusability settings.
require("#define I_REUSABLE_TMS          FALSE" in config,
        "Existing TM consumption/reusability setting changed")

print("PASS: TM54 identity, purchase paths, teachability and non-KO effect retained")
print("PASS: Escape Rope Key Item grants/recovery retained; visible, hidden and scripted loot gives one Max Revive")
print("PASS: original map item flags/locations/graphics retained; HNS loot audit clear")
print("NOTE: source regression only; Max Revive gameplay pickup remains a separate emulator/player check")
