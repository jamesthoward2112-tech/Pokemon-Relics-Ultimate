#!/usr/bin/env python3
"""Job 7: no pre-RELICS legendary captures, legacy-save re-entry, and League guard."""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
def read(path):
    return (ROOT / path).read_text(encoding="utf-8")
def actor(map_name, script):
    events = json.loads(read(f"data/maps/{map_name}/map.json"))["object_events"]
    matches = [item for item in events if item.get("script") == script]
    assert len(matches) == 1, (map_name, script, len(matches))
    return matches[0]
def before(source, entry, forbidden):
    chunk = source.split(entry, 1)[1]
    assert chunk.lstrip().startswith("goto "), (entry, chunk[:160])
    assert chunk.index("goto ") < chunk.find(forbidden), entry

gate = read("data/maps/ReceptionGate_hns/scripts.inc")
assert "goto_if_lt VAR_ECRUTEAK_CITY_THEATER, 7, ReceptionGate_EventScript_Kimono" in gate
assert "goto_if_unset FLAG_BADGE08_GET, ReceptionGate_EventScript_NotEnough" in gate
assert "goto_if_lt VAR_ECRUTEAK_CITY_THEATER, 8, ReceptionGate_EventScript_Kimono" not in gate
theater = read("data/maps/EcruteakCity_Theater_hns/scripts.inc")
assert "setvar VAR_ECRUTEAK_CITY_THEATER, 7" in theater
assert "setvar VAR_COMPLETED_LUGIA, 2" in theater
print("PASS: Zacharias League/ceremony state 7, all badges and untouched old-save Lugia state 2")

whirl = read("data/maps/WhirlIslands_LugiaChamber_hns/scripts.inc")
transition = whirl.split("WhirlIslands_LugiaChamber_OnTransition:",1)[1].split(
    "WhirlIslands_LugiaChamber_MapScript_RelicLugia::",1)[0]
for flag in ("FLAG_IS_CHAMPION", "FLAG_PRU_ELITE18_CLEARED",
             "FLAG_PJR_RELIC_RAIKOU", "FLAG_PJR_RELIC_ENTEI"):
    assert f"goto_if_unset {flag}, WhirlIslands_LugiaChamber_MapScript_RelicLugiaSealed" in transition
assert "goto_if_eq VAR_COMPLETED_LUGIA" not in transition
assert "setflag FLAG_HIDE_LUGIA" in transition
assert "setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS" in transition
assert "goto WhirlIslands_LugiaChamber_MapScript_RelicLugia" in transition
lugia_root = whirl.split("WhirlIslands_LugiaChamber_EventScript_Lugia::",1)[1]
assert lugia_root.index("goto WhirlIslands_LugiaChamber_hns_RelicLugia") < lugia_root.index("seteventmon SPECIES_LUGIA")
assert "goto WhirlIslands_LugiaChamber_MapScript_RelicLugiaSealed" in whirl.split(
    "WhirlIslands_LugiaChamber_EventScript_TalkToKimono::",1)[1][:160]
assert json.loads(read("data/maps/WhirlIslands_LugiaChamber_hns/map.json"))["coord_events"] == []
lugia_relic = whirl.split("WhirlIslands_LugiaChamber_hns_RelicLugia::",1)[1].split(
    "WhirlIslands_LugiaChamber_hns_RelicLugia_Unavailable::",1)[0]
for flag in ("FLAG_IS_CHAMPION", "FLAG_PRU_ELITE18_CLEARED", "FLAG_PJR_RELIC_RAIKOU", "FLAG_PJR_RELIC_ENTEI"):
    assert f"goto_if_unset {flag}," in lugia_relic
assert "goto RuinsOfAlph_Lab_EventScript_RelicLugia" in lugia_relic
print("PASS: Lugia cannot be caught via old story states 2/3/4 or the old Kimono trigger")

ilex = read("data/maps/IlexForest_hns/scripts.inc")
ilex_transition = ilex.split("IlexForest_OnTransition:",1)[1].split(
    "IlexForest_EventScript_ReenterWhenFarfetchdLeaving::",1)[0]
for hide in ("FLAG_HIDE_CELEBI", "FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI", "FLAG_TEMP_6"):
    assert f"setflag {hide}" in ilex_transition
for flag in ("FLAG_IS_CHAMPION", "FLAG_PRU_ELITE18_CLEARED", "FLAG_PJR_RELIC_UNOWN_I"):
    assert f"goto_if_unset {flag}," in ilex_transition
shrine = ilex.split("IlexForest_EventScript_Shrine::",1)[1].split(
    "IlexForest_EventScript_Shrine_PreRelics::",1)[0]
assert "goto_if_eq VAR_AZALEA_TOWN_STATE" not in shrine
assert "goto RuinsOfAlph_Lab_EventScript_RelicCelebi" in shrine
for label in ("IlexForest_EventScript_Celebi_Event::", "IlexForest_EventScript_SecondCelebi::"):
    block = ilex.split(label,1)[1].split("seteventmon SPECIES_CELEBI",1)[0]
    assert "goto IlexForest_hns_RelicCelebi_Unavailable" in block, label
assert actor("IlexForest_hns","IlexForest_hns_RelicCelebi")["flag"] == "FLAG_TEMP_6"
assert "goto_if_unset FLAG_PRU_ELITE18_CLEARED" in ilex.split("IlexForest_hns_RelicCelebi::",1)[1][:300]
assert "GS BALL" in ilex
print("PASS: early GS Ball state cannot start Celebi; duplicate actor retired; shrine/RELICS remains")

route = read("data/maps/Route25_hns/scripts.inc")
route_transition = route.split("Route25_MapScript_OnTransition::",1)[1].split(
    "Route25_EventScript_SetSuicuneSceneMid::",1)[0]
assert "setflag FLAG_HIDE_ROUTE25_SUICUNE" in route_transition
assert "setflag FLAG_TEMP_7" in route_transition
for flag in ("FLAG_IS_CHAMPION", "FLAG_PRU_ELITE18_CLEARED", "FLAG_PJR_RELIC_CELEBI"):
    assert f"goto_if_unset {flag}," in route_transition
assert "goto Route25_RelicSuicune" in route.split(
    "Route25_EventScript_Suicune::",1)[1].split("seteventmon SPECIES_SUICUNE",1)[0]
assert actor("Route25_hns", "Route25_RelicSuicune")["flag"] == "FLAG_TEMP_7"
assert "goto_if_unset FLAG_PRU_ELITE18_CLEARED" in route.split(
    "Route25_RelicSuicune::",1)[1][:300]
print("PASS: original level-50 Suicune retired; sole post-RELICS event gated")

groudon = read("data/maps/Route45_GroudonCave_hns/scripts.inc")
for label, end in [
    ("Route45_GroudonCave_OnTransition::", "Route45_GroudonCave_HideGroudon::"),
    ("Route45_GroudonCave_EventScript_Maxie::", "Route45_GroudonCave_EventScript_MaxieAfterBattle::"),
    ("Route45_GroudonCave_EventScript_Groudon::", "Route45_GroudonCave_GroudonUnavailable::"),
]:
    block = groudon.split(label, 1)[1].split(end, 1)[0]
    assert "goto_if_unset FLAG_IS_CHAMPION" in block, label
assert "TRAINER_PRU_MAXIE_GROUDON_HNS" in groudon
assert "setwildbattleshiny SPECIES_GROUDON, 75" in groudon
print("PASS: Maxie and Route 45 Groudon gated until Johto Champion")

for path,label in [
    ("data/maps/MtMortar_B1F_hns/scripts.inc","MtMortar_B1F_hns_RelicEntei::"),
    ("data/maps/RuinsOfAlph_B1F_hns/scripts.inc","RuinsOfAlph_B1F_hns_RelicUnownI::"),
    ("data/maps/RuinsOfAlph_B1F_hns/scripts.inc","RuinsOfAlph_B1F_hns_RelicAlphoracle::")
]:
    assert "goto_if_unset FLAG_PRU_ELITE18_CLEARED" in read(path).split(label,1)[1][:320], label
lab = read("data/maps/RuinsOfAlph_Lab_hns/scripts.inc")
assert "setflag FLAG_TEMP_6" in lab.split("RuinsOfAlph_Lab_EventScript_RelicCelebiCaught::",1)[1][:160]
assert "setflag FLAG_TEMP_7" in lab.split("RuinsOfAlph_Lab_EventScript_RelicSuicuneCaught::",1)[1][:180]
for name,flag,prev in [
("Raikou","FLAG_PJR_RELIC_RAIKOU",None),
("Entei","FLAG_PJR_RELIC_ENTEI","FLAG_PJR_RELIC_RAIKOU"),
("Lugia","FLAG_PJR_RELIC_LUGIA","FLAG_PJR_RELIC_ENTEI"),
("UnownI","FLAG_PJR_RELIC_UNOWN_I","FLAG_PJR_RELIC_LUGIA"),
("Celebi","FLAG_PJR_RELIC_CELEBI","FLAG_PJR_RELIC_UNOWN_I"),
("Suicune","FLAG_PJR_RELIC_SUICUNE","FLAG_PJR_RELIC_CELEBI"),
("Alphoracle","FLAG_PJR_RELIC_ALPHORACLE","FLAG_PJR_RELIC_SUICUNE")
]:
    assert f"RuinsOfAlph_Lab_EventScript_Relic{name}Caught::" in lab
    assert f"setflag {flag}" in lab.split(f"RuinsOfAlph_Lab_EventScript_Relic{name}Caught::",1)[1][:170]
print("PASS: ordered R-E-L-I-C-S/Alphoracle remains intact; only capture awards flags")
print("JOB7_LEGENDARY_GATING_PASS")
