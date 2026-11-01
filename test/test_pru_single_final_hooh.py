#!/usr/bin/env python3
"""PRU staged Ho-Oh story regression (source-only; no ROM build).

Ensure that the only catchable Ho-Oh is the level-100 RELIC on Tin Tower roof,
and that ALL other RELICS and Ancient Rainbow Crest are required first.
"""
from pathlib import Path
import json
import re

ROOT = Path(__file__).resolve().parents[1]
def read(path):
    return (ROOT / path).read_text(encoding="utf-8")
def require(value, reason):
    if not value:
        raise AssertionError(reason)

roof = read("data/maps/TinTower_RoofDay_hns/scripts.inc")
roof_map = json.loads(read("data/maps/TinTower_RoofDay_hns/map.json"))
silver = read("data/maps/MtSilver_SummitDay_hns/scripts.inc")
theater = read("data/maps/EcruteakCity_Theater_hns/scripts.inc")
lab = read("data/maps/RuinsOfAlph_Lab_hns/scripts.inc")
tower = read("data/maps/TinTower_1F_hns/scripts.inc")
policy = read("test/test_pru_legendary_encounter_levels.py")

def section(content, start, end):
    require(start in content and end in content, f"Missing required labels: {start}, {end}")
    return content.split(start, 1)[1].split(end, 1)[0]

on_transition = section(roof, "TinTower_RoofDay_OnTransition:", "TinTower_RoofDay_EventScript_SyncRelicHoOhState::")
sync = section(roof, "TinTower_RoofDay_EventScript_SyncRelicHoOhState::",
               "TinTower_RoofDay_EventScript_SyncLegacyHoOhCaught::")
encounter = section(roof, "TinTower_RoofDay_EventScript_HoOhPostgame::",
                    "TinTower_RoofDay_EventScript_HoOhLocked::")
required_flags = (
    "FLAG_PJR_RELIC_RAIKOU", "FLAG_PJR_RELIC_ENTEI",
    "FLAG_PJR_RELIC_LUGIA", "FLAG_PJR_RELIC_UNOWN_I",
    "FLAG_PJR_RELIC_CELEBI", "FLAG_PJR_RELIC_SUICUNE",
    "FLAG_PJR_RELIC_ALPHORACLE",
)
require("call TinTower_RoofDay_EventScript_SyncRelicHoOhState" in on_transition,
        "Ho-Oh availability must always be recalculated on roof entry")
require("goto_if_eq VAR_COMPLETED_HO_OH, 2" not in on_transition,
        "Old story state must not reveal Ho-Oh before finishing RELICS")
require("setflag FLAG_HIDE_HO_OH" in sync
        and "setflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS" in sync,
        "Hide early Ho-Oh and Kimono Girls before performing unlock check")
for flag in required_flags:
    require("goto_if_unset " + flag in sync,
            "Missing arrival-stage Relic gate: " + flag)
    require("goto_if_unset " + flag in encounter,
            "Missing encounter-stage Relic gate: " + flag)
require("goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST" in sync
        and "checkitem ITEM_ANCIENT_RAINBOW_CREST" in sync,
        "Roof visibility requires the unlocked and owned Ancient Crest")
require("goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST" in encounter
        and "checkitem ITEM_ANCIENT_RAINBOW_CREST" in encounter,
        "Ho-Oh battle must require Crest flag and physical item")
require("seteventmon SPECIES_RELIC_HO_OH, 100" in encounter
        and encounter.count("seteventmon ") == 1,
        "Exactly one level-100 Relic Ho-Oh battle must exist")
require("goto_if_set FLAG_PJR_RELIC_HO_OH" in roof
        and "goto_if_set FLAG_CAUGHT_HO_OH" in roof,
        "Repeat catches and older-save ordinary Ho-Oh must stay hidden")
require("TinTower_RoofDay_EventScript_SyncLegacyHoOhCaught::" in roof
        and "setflag FLAG_PJR_RELIC_HO_OH" in roof,
        "Older saves cannot get a second Ho-Oh after an original catch")
require("setflag FLAG_CAUGHT_HO_OH" in section(
    roof, "TinTower_RoofDay_EventScript_CaughtRelicHoOh::",
    "TinTower_RoofDay_EventScript_HoohFlewAway::"),
    "Catch must set legacy and final flags to lock reencounters")
require("seteventmon SPECIES_HO_OH," not in roof,
        "Retired ordinary Ho-Oh battle setter still exists")

require(not any(evt.get("script") == "TinTower_RoofDay_EventScript_TalkToKimono"
                for evt in roof_map["coord_events"]),
        "Old story Kimono scene trigger must be retired")
rooftop_hooh = [evt for evt in roof_map["object_events"]
               if "SPECIES_HO_OH" in evt.get("graphics_id", "")]
require(len(rooftop_hooh) == 1 and rooftop_hooh[0]["flag"] == "FLAG_HIDE_HO_OH",
        "Only one hidden/revealed Ho-Oh overworld object should remain")

require("seteventmon SPECIES_HO_OH," not in silver
        and "seteventmon SPECIES_RELIC_HO_OH," not in silver,
        "Oak must not summon a second catchable Ho-Oh")
oak = section(silver, "MtSilver_SummitDay_EventScript_OakSummon::",
              "MtSilver_SummitDay_EventScript_OakRelicCaught::")
require("special BattleSetup_StartLegendaryBattle" not in oak,
        "Old Oak summon label must no longer start legendary combat")
require("trainerbattle_no_intro TRAINER_PRU_E18_18_A_MASTER_HNS" in silver,
        "Oak's trainer challenge must remain")
crest = section(silver, "MtSilver_SummitDay_EventScript_UnlockRelicHoOh::",
                "MtSilver_SummitDay_Text_RedBeaten:")
require("clearflag FLAG_HIDE_HO_OH" not in crest
        and "setvar VAR_COMPLETED_HO_OH, 4" not in crest,
        "Red's Crest must not directly reveal Ho-Oh")
alph_unlock = section(lab, "RuinsOfAlph_Lab_EventScript_UnlockRelicHoOh::",
                      "RuinsOfAlph_Lab_EventScript_RelicDecline::")
require("clearflag FLAG_HIDE_HO_OH" not in alph_unlock
        and "setvar VAR_COMPLETED_HO_OH, 4" not in alph_unlock,
        "Alph Lab may inform but never directly reveal Ho-Oh")
theater_old = section(theater, "EcruteakCity_Theater_EventScript_Hooh::",
                      "EcruteakCity_Theater_Movement_Sister:")
require("setvar VAR_COMPLETED_HO_OH, 2" not in theater_old
        and "clearflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS" not in theater_old,
        "Kimono gauntlet must not schedule a pre-quest Ho-Oh visit")
require("setvar VAR_ECRUTEAK_CITY_THEATER, 8" in theater_old
        and "clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI" in theater_old
        and "clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS" in theater_old
        and "clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS" in theater_old,
        "Kimono gauntlet must complete normally without an early Ho-Oh battle")

require("rumour" in theater and "rumour" in tower,
        "Early NPCs should give rumours, not guaranteed Ho-Oh sightings")
require('("TinTower_RoofDay_hns", "RELIC_HO_OH"): 1' in policy,
        "Legendary level audit must enforce one Ho-Oh setter")
print("PASS: one catchable level-100 Relic Ho-Oh at Tin Tower")
print("PASS: all seven RELICS and the Ancient Rainbow Crest gated twice")
print("PASS: early roof trigger, Oak summon, Red/Alph bypasses retired")
print("PASS: Kimono Theater story completes without a Ho-Oh appearance")
print("PASS: legendary catch and legacy-save flags block additional Ho-Oh")
print("NOTE: source only. Compile and exercise new/existing saves in mGBA before release.")
