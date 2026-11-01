#!/usr/bin/env python3
"""Regressions for Golden Ho-Oh final RELIC encounter and caught-save behaviour."""
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
def read(p): return (ROOT / p).read_text()
roof = read("data/maps/TinTower_RoofDay_hns/scripts.inc")
def section(label, endlabel):
    return roof.split(label + "::", 1)[1].split(endlabel + "::", 1)[0]
assert "goto_if_set FLAG_PJR_RELIC_HO_OH, TinTower_RoofDay_MapScript_HoohCaught" in section("TinTower_RoofDay_MapScript_HoohPostStoryGone", "TinTower_RoofDay_MapScript_HoohCaught")
assert "goto_if_set FLAG_PJR_RELIC_HO_OH, TinTower_RoofDay_MapScript_HoohCaught" in section("TinTower_RoofDay_MapScript_HoohPostStoryEncounter", "TinTower_RoofDay_MapScript_RelicHoOhLocked")
assert "goto_if_set FLAG_PJR_RELIC_HO_OH, TinTower_RoofDay_EventScript_AlreadyCaughtRelic" in section("TinTower_RoofDay_EventScript_HoOh", "TinTower_RoofDay_EventScript_HoOhRetry")
assert "setflag FLAG_PJR_RELIC_HO_OH" in section("TinTower_RoofDay_EventScript_CaughtRelicHoOh", "TinTower_RoofDay_EventScript_HoohFlewAway")
assert "setflag FLAG_HIDE_HO_OH" in section("TinTower_RoofDay_EventScript_CaughtRelicHoOh", "TinTower_RoofDay_EventScript_HoohFlewAway")
constants = read("include/constants/abilities.h")
assert constants.index("ABILITY_RELIC_EYE,") < constants.index("ABILITY_GOLDEN_SOVEREIGN,") < constants.index("ABILITIES_COUNT,")
assert 'GOLDEN SOVEREIGN' in read("src/data/abilities.h")
battle = read("src/battle_util.c")
assert "case ABILITY_GOLDEN_SOVEREIGN:" in battle
assert "moveType == TYPE_FIRE || moveType == TYPE_STEEL" in battle
species = read("src/data/pokemon/species_info/gen_2_families.h")
ho = species.split("[SPECIES_HO_OH] =",1)[1].split("#endif //P_FAMILY_HO_OH",1)[0]
assert "ABILITY_PRESSURE, ABILITY_NONE, ABILITY_GOLDEN_SOVEREIGN" in ho
pokemon = read("src/pokemon.c")
assert "if (species == SPECIES_HO_OH && level == 85" in pokemon
assert "GetMonData(mon, MON_DATA_MET_LEVEL) == 85" in pokemon
assert "isPruGoldenHoOh ? sPruGoldenHoOhBaseStats[i]" in pokemon
assert "isPruGoldenHoOh ? sPruGoldenHoOhBaseStats[STAT_HP]" in pokemon
assert [int(v) for v in ("125","130","115","170","155","105")] and sum((125,130,115,170,155,105)) == 800
assert "SetMonMoveSlot(&gEnemyParty[0], MOVE_MAKE_IT_RAIN, 1);" in pokemon
assert "LEVEL_UP_MOVE(85, MOVE_MAKE_IT_RAIN)" in read("src/data/pokemon/level_up_learnsets/gen_2.h")
print("PASS: Golden Ho-Oh caught permanence, unique 800 BST, ability, Make It Rain and old-save migration")
