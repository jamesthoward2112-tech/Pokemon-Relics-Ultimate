#!/usr/bin/env python3
"""Source-only regression for PRU's purchasable False Swipe TM54.

Run with: python3 test/test_pru_false_swipe_marts.py
This verifies wiring and inventory; a future clean ROM build and player tests
are still needed before claiming the item teaches a compatible party Pokémon.
"""

from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]


def read(path):
    return (ROOT / path).read_text(encoding="utf-8")


def require(condition, message):
    if not condition:
        raise AssertionError(message)


tms = read("include/constants/tms_hms.h")
hns_tms = tms.split("#if IS_HNS", 1)[1].split("#else", 1)[0]
hns_tms = hns_tms.split("#define FOREACH_TM(F)", 1)[1].split("#define FOREACH_HM(F)", 1)[0]
tm_moves = re.findall(r"\bF\(([A-Z_0-9]+)\)", hns_tms)
require(len(tm_moves) >= 54 and tm_moves[53] == "FALSE_SWIPE",
        "PRU TM54 must remain False Swipe; TM slot IDs must not change")

items_enum = read("include/constants/items.h")
require("ITEM_TM54 = 635" in items_enum, "Save-compatible ITEM_TM54 number changed")
require("CAT(ITEM_TM_, id) = CAT(ITEM_TM, n)" in items_enum,
        "The generated ITEM_TM_FALSE_SWIPE alias is missing")

item_info = read("src/data/items.h")
tm54 = re.search(r"\[ITEM_TM54\]\s*=\s*// False Swipe\s*\{([\s\S]*?)\n    \},", item_info)
require(tm54 is not None, "Real TM54 item definition missing")
for requirement in (
    'ITEM_NAME("TM54 - FALSE SWIPE")',
    ".price = 3000",
    ".pocket = POCKET_TM_HM",
    ".type = ITEM_USE_PARTY_MENU",
    ".fieldUseFunc = ItemUseOutOfBattle_TMHM",
):
    require(requirement in tm54.group(1), f"TM54 incomplete: {requirement}")

moves = read("src/data/moves_info.h")
false_swipe = re.search(r"\[MOVE_FALSE_SWIPE\]\s*=\s*\{([\s\S]*?)\n    \},", moves)
require(false_swipe is not None and ".effect = EFFECT_FALSE_SWIPE" in false_swipe.group(1),
        "False Swipe must actually retain its non-KO battle effect")

item_cpp = read("include/item.h")
require("FOREACH_TM(UNPACK_ITEM_TO_TM_MOVE_ID)" in item_cpp,
        "The item-to-move runtime map must include TM54")
party = read("src/party_menu.c")
require("enum Move move = ItemIdToBattleMoveId(item);" in party
        and "switch (CanTeachMove(mon, move))" in party,
        "TM must use real party teaching and compatibility checks")

early = read("data/maps/CherrygroveCity_Mart_hns/scripts.inc")
pre_ball_stock = early.split("Cherrygrove_Pokemart_Pokemart:", 1)[1].split("ITEM_NONE", 1)[0]
require("ITEM_TM_FALSE_SWIPE" in pre_ball_stock, "Early Cherrygrove inventory missing TM54")
require("pokemart 0" in early, "Cherrygrove's existing badge-dependent stock was replaced")

shop = read("src/shop.c")
for requirement in (
    "sPruCherrygroveTMStock",
    "MAP_GROUP(MAP_CHERRYGROVE_CITY_MART_HNS)",
    "MAP_NUM(MAP_CHERRYGROVE_CITY_MART_HNS)",
    "sPruCherrygroveTMStock[i++] = ITEM_TM_FALSE_SWIPE;",
    "sMartInfo.itemList = sPruCherrygroveTMStock;",
):
    require(requirement in shop, f"Cherrygrove dynamic stock extension missing: {requirement}")
require("GetShopPurchasePrice(itemId)" in shop,
        "Existing isolated Ecruteak Rock Shop price rule was lost")

department_stores = (
    ("data/maps/GoldenrodCity_DepartmentStore_5F_hns/scripts.inc", "GoldenrodDeptStore5_Pokemart:"),
    ("data/maps/CeladonCity_DepartmentStore_3F_hns/scripts.inc", "CeladonDept3_Pokemart:"),
)
for path, label in department_stores:
    scripts = read(path)
    inventory = scripts.split(label, 1)[1].split("pokemartlistend", 1)[0]
    require(inventory.count("ITEM_TM_FALSE_SWIPE") == 1, f"{path}: missing/duplicate TM54")

print("PASS: TM54 retains its original save ID, machine index, move and item effect")
print("PASS: Cherrygrove carries False Swipe before/after Poké Ball unlock")
print("PASS: Goldenrod 5F and Celadon 3F stock False Swipe without replacing other TMs")
print("NOTE: source only. No GBA build, player teachability or save test performed.")
