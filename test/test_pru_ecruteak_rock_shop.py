#!/usr/bin/env python3
"""Focused source regression for the Ecruteak Rock Shop."""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def source(path):
    return (ROOT / path).read_text(encoding="utf-8")

def require(condition, reason):
    if not condition:
        raise AssertionError(reason)

shop = source("data/maps/EcruteakCity_RockShop_hns/scripts.inc")
code = source("src/shop.c")
items = source("include/constants/items.h")
evolutions = source("src/data/pokemon/species_info/gen_1_families.h") + source(
    "src/data/pokemon/species_info/gen_2_families.h") + source(
    "src/data/pokemon/species_info/gen_3_families.h")

def inventory(name):
    body = shop.split(name + ":", 1)[1].split("pokemartlistend", 1)[0]
    return re.findall(r"\.2byte\s+(ITEM_[A-Z0-9_]+)", body)

basic = [
    "ITEM_FIRE_STONE", "ITEM_WATER_STONE", "ITEM_THUNDER_STONE",
    "ITEM_LEAF_STONE", "ITEM_ICE_STONE", "ITEM_MOON_STONE",
    "ITEM_SUN_STONE", "ITEM_OVAL_STONE", "ITEM_EVERSTONE",
    "ITEM_ANCIENT_STONE",
]
advanced = basic + ["ITEM_SHINY_STONE", "ITEM_DUSK_STONE", "ITEM_DAWN_STONE"]
require(inventory("EcruteakCity_RockShop_Basic") == basic,
        "Immediate stock must contain the approved ten items in order")
require(inventory("EcruteakCity_RockShop_Advanced") == advanced,
        "Fog Badge stock must contain all thirteen approved items in order")
require("goto_if_set FLAG_BADGE04_GET, EcruteakCity_RockShop_EventScript_ClerkAdvanced" in shop,
        "Advanced stock must retain Fog Badge progression")
require(shop.count("ITEM_ANCIENT_STONE") == 2,
        "Ancient Stone must be stocked in both tiers")

helper_match = re.search(
    r"static u32 GetShopPurchasePrice\(u32 itemId\)\s*\{(?P<body>.*?)\n\}",
    code, re.S)
require(helper_match is not None, "Isolated purchase-price helper is missing")
helper = helper_match.group("body")
require("GetItemPrice(itemId)" in helper and "MAP_ECRUTEAK_CITY_ROCK_SHOP_HNS" in helper,
        "Discount must use base item price and be scoped to Ecruteak Rock Shop")
require(re.search(r"return\s+price\s*>\s*1\s*\?\s*\(price\s*\+\s*1\)\s*/\s*2\s*:\s*price", helper) is not None,
        "Odd prices must round upward")
require(helper.index("MAP_ECRUTEAK_CITY_ROCK_SHOP_HNS") < helper.index("IsPokeNewsActive"),
        "Rock Shop price must be derived before other marts' Slateport adjustment")
require("return GetItemPrice(itemId) >> IsPokeNewsActive(POKENEWS_SLATEPORT);" in helper,
        "Other mart pricing must preserve Slateport news behavior")
for regular, discounted in ((3000, 1500), (2100, 1050), (2001, 1001), (1, 1)):
    calculated = (regular + 1) // 2 if regular > 1 else regular
    require(calculated == discounted, f"Incorrect half-price rounding for {regular}")

require(code.count("GetShopPurchasePrice(itemId)") >= 2
        and code.count("GetShopPurchasePrice(tItemId)") >= 2,
        "Displayed price, initial total, confirmation and quantity total must use helper")
require("IsEnoughMoney(&gSaveBlock1Ptr->money, sShopData->totalCost)" in code
        and "RemoveMoney(&gSaveBlock1Ptr->money, sShopData->totalCost)" in code,
        "Existing funds validation and exact-total deduction must remain active")
require(code.count("GetShopPurchasePrice(") == 5,
        "The price helper must only be used at its definition and four buy-price callsites")
require("ITEM_ANCIENT_STONE" in items and "ITEM_OVAL_STONE" in items
        and "ITEM_EVERSTONE" in items,
        "Use existing item IDs")
require("ITEM_ANCIENT_STONE, SPECIES_" in evolutions
        and "CONDITIONS({IF_MIN_LEVEL, 45})" in evolutions,
        "Ancient Stone level-45 evolution rules must remain present")

print("Ecruteak Rock Shop source regression passed (inventory, tier, local pricing, purchase paths, sell path, Ancient Stone).")
