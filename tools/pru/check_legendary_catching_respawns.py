#!/usr/bin/env python3
"""PRU legendary capture/respawn safeguards. Run before every canonical ROM build."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
read = lambda name: (ROOT / name).read_text(encoding="utf-8")

battle = read("src/battle_script_commands.c")
overworld = read("src/overworld.c")
assert re.search(
    r"if \(IS_HNS && \(gBattleTypeFlags & \(BATTLE_TYPE_LEGENDARY \| BATTLE_TYPE_ROAMER\)\)"
    r"\s*&& catchRate < 20\)\s*catchRate = 20;", battle
), "HNS legendary/roamer catch rate minimum must stay at 20 (not guaranteed)"
assert battle.index("catchRate = gSpeciesInfo[battleMon->species].catchRate;") < battle.index("catchRate = 20;") < battle.index("catchRate += ball.flatBonus;")

# The mechanism must run on BOTH camera-connected map changes and warps.
assert overworld.count("RestorePruDefeatedLegendariesOnMapEntry();") == 2
assert "if (!IS_HNS)" in overworld
for species, hide_flag in {
    "HO_OH": "HO_OH", "LUGIA": "LUGIA", "ARTICUNO": "ARTICUNO",
    "ZAPDOS": "ZAPDOS", "MOLTRES": "MOLTRES", "MEWTWO": "MEWTWO",
    "GROUDON": "GROUDON", "KYOGRE": "KYOGRE", "RAYQUAZA": "RAYQUAZA",
    "LATIAS": "LATIAS", "LATIOS": "LATIOS",
    "REGICE": "SINJOHRUINS_REGICE", "REGIROCK": "SINJOHRUINS_REGIROCK",
    "REGISTEEL": "SINJOHRUINS_REGISTEEL", "MEW": "MEW",
}.items():
    assert re.search(rf"SPECIES_{species},\s+FLAG_HIDE_{hide_flag}\b", overworld), species

assert "FLAG_GET_SEEN" in overworld and "FLAG_GET_CAUGHT" in overworld
assert "FLAG_SUMMONED_MTMOON_JIRACHI" in overworld
assert "FlagClear(FLAG_HIDE_MTMOON_JIRACHI)" in overworld
assert "VarGet(VAR_SUICUNE_ENCOUNTERS) >= 8" in overworld
assert "FlagClear(FLAG_HIDE_ROUTE25_SUICUNE)" in overworld
assert "RestorePruDefeatedRoamers();" in overworld
roamer = read("src/roamer.c")
battle_main = read("src/battle_main.c")
assert "if (IS_HNS && gBattleOutcome == B_OUTCOME_WON)" in roamer
assert "ROAMER(gEncounteredRoamerIndex)->hp = GetMonData(mon, MON_DATA_MAX_HP)" in roamer
assert "void RestorePruDefeatedRoamers(void)" in roamer
assert "ROAMER_LOC_TABLE_KANTO" in roamer and "FLAG_GET_CAUGHT" in roamer
assert "(!IS_HNS && gBattleOutcome == B_OUTCOME_WON)" in battle_main
assert "VarGet(VAR_AZALEA_TOWN_STATE) >= 10" in overworld
assert "FlagClear(FLAG_DEFEATED_MEW)" in overworld
assert "FlagClear(FLAG_DEFEATED_DEOXYS)" in overworld

lugia = read("data/maps/WhirlIslands_LugiaChamber_hns/scripts.inc")
assert "goto_if_set FLAG_CAUGHT_LUGIA, WhirlIslands_LugiaChamber_MapScript_LugiaCaught" in lugia
assert re.search(r"WhirlIslands_LugiaChamber_MapScript_LugiaPostStoryGone::[\s\S]*?setvar VAR_COMPLETED_LUGIA, 4", lugia)
hooh = read("data/maps/TinTower_RoofDay_hns/scripts.inc")
assert "goto_if_set FLAG_CAUGHT_HO_OH, TinTower_RoofDay_MapScript_HoohCaught" in hooh
assert "goto_if_eq VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_HoOhRetry" in hooh
assert "seteventmon SPECIES_HO_OH, 50" in hooh
ilex = read("data/maps/IlexForest_hns/scripts.inc")
assert "call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, IlexForest_EventScript_SecondCelebiCaught" in ilex

jirachi = read("src/data/pokemon/species_info/gen_3_families.h")
assert "[SPECIES_JIRACHI]" in jirachi and ".frontPic = gMonFrontPic_Jirachi" in jirachi
assert "SPECIES_JIRACHI, 50" in read("data/maps/MtMoon_Outside_hns/scripts.inc")

print("PASS: legends use rate floor 20 only in HNS legendary/roamer encounters")
print("PASS: 15 static legendary hide flags restore only for seen, uncaught species")
print("PASS: Jirachi and Celebi story gates; Mew and Deoxys defeat markers reset")
print("PASS: Lugia, Ho-Oh, Suicune and second Celebi retries preserve captured/story states")
print("PASS: Latias/Latios roamers recover on knockout; capture remains permanent")
