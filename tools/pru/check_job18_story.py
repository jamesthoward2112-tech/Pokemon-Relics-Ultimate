#!/usr/bin/env python3
"""Source-level progression regression for the Job 18 storyline."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]

def read(path: str) -> str:
    return (ROOT / path).read_text()

lab = read("data/maps/RuinsOfAlph_Lab_hns/scripts.inc")
assert "FLAG_PRU_ELITE18_CLEARED" in lab
assert "FLAG_PJR_RELIC_ALPHORACLE" in lab
assert "summit of MT. SILVER" in lab
assert "ITEM_ANCIENT_RAINBOW_CREST" not in lab
assert "goto_if_unset FLAG_PRU_ELITE18_CLEARED" in lab
assert "goto_if_set FLAG_PJR_RELIC_HO_OH" in lab
unlock = lab.split("RuinsOfAlph_Lab_EventScript_UnlockRelicHoOh::", 1)[1].split("RuinsOfAlph_Lab_EventScript_RelicRecorded::", 1)[0]
assert "VAR_COMPLETED_HO_OH" not in unlock
assert "FLAG_HIDE_TIN_TOWER_GUARDIAN" not in unlock

oak_lab = read("data/maps/PalletTown_Lab_hns/scripts.inc")
reveal = oak_lab.split("PalletTown_Lab_Text_OakRelicsExplain:", 1)[1].split("PalletTown_Lab_Text_OakRelicsStart:", 1)[0]
assert "ULTIMATE ANCIENT" in reveal and "RELIC" in reveal
assert "MT. SILVER" not in reveal and "TIN TOWER" not in reveal

summit = read("data/maps/MtSilver_SummitDay_hns/scripts.inc")
oak_event = summit.split("MtSilver_SummitDay_EventScript_RelicOak::", 1)[1].split("MtSilver_SummitDay_Text_OakChallenge:", 1)[0]
assert "trainerbattle" not in oak_event.lower()
assert "ITEM_ANCIENT_RAINBOW_CREST" not in oak_event
assert "seteventmon SPECIES_RELIC_HO_OH, 100" in oak_event
assert "MtSilver_SummitDay_EventScript_OakRelicCaught" in oak_event
assert "MtSilver_SummitDay_EventScript_OakRetry" not in oak_event
assert "Gollum" not in summit and "One Ring" not in summit
assert '"Shortcut to Top$"' in read("data/maps/MtSilver_Outside_hns/scripts.inc")

tin = read("data/maps/TinTower_RoofDay_hns/scripts.inc")
assert "TRAINER_PRU_ANCIENT_GUARDIAN_DRAGONITE" in tin
assert "SPECIES_HO_OH, CRY_MODE_ENCOUNTER" not in tin

for name in ("TinTower_RoofDay_hns", "TinTower_RoofNight_hns"):
    source = read(f"data/maps/{name}/map.json")
    assert "SPECIES_DRAGONITE" in source
    assert "FLAG_HIDE_TIN_TOWER_GUARDIAN" in source

party = read("src/data/trainers_hns.party")
guardian = party.split("=== TRAINER_PRU_ANCIENT_GUARDIAN_DRAGONITE ===", 1)[1].split("===", 1)[0]
for line in (
    "Ancient Guardian Dragonite @ Weakness Policy", "Level: 60", "Ability: Multiscale",
    "Nature: Adamant", "252 HP / 252 Atk / 0 Def / 0 SpA / 0 SpD / 4 Spe", "IVs: 31",
    "Dragon Dance", "Dual Wingbeat", "Dragon Claw", "Roost",
):
    assert line in guardian, line
assert "Earthquake" not in guardian
assert "SPECIES_ANCIENT_GUARDIAN_DRAGONITE" not in read("src/data/pokemon/pru_dex_order.h")

credits = read("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
assert "FLAG_PRU_HOOH_FINALE_COMPLETE" in credits
assert "FLAG_PRU_E20_CREDITS_PENDING" in credits

theater = read("data/maps/EcruteakCity_Theater_hns/scripts.inc")
hooh_hint = theater.split("EcruteakCity_Theater_Text_GirlHooh:", 1)[1].split("EcruteakCity_Theater_Text_GirlLugia:", 1)[0]
hooh_direction = theater.split("EcruteakCity_Theater_Text_ZukiHooh:", 1)[1].split("EcruteakCity_Theater_Text_ZukiLugia:", 1)[0]
assert "blue-crystal" in hooh_hint and "guardian" in hooh_hint
assert "TIN TOWER summit" in hooh_direction and "guardian" in hooh_direction

dialogue = {
    "data/maps/MtSilver_SummitDay_hns/scripts.inc": [
        "MtSilver_SummitDay_Text_OakObsessed", "MtSilver_SummitDay_Text_OakReluctant",
        "MtSilver_SummitDay_Text_OakSummon", "MtSilver_SummitDay_Text_OakNeedElite20",
        "MtSilver_SummitDay_Text_OakNeedRelics", "MtSilver_SummitDay_Text_OakRetry",
        "MtSilver_SummitDay_Text_OakEpilogue",
    ],
    "data/maps/TinTower_RoofDay_hns/scripts.inc": [
        "TinTower_RoofDay_Text_GuardianRumour", "TinTower_RoofDay_Text_GuardianChallenge",
        "TinTower_RoofDay_Text_GuardianVictory", "TinTower_RoofDay_Text_GuardianFarewell",
        "TinTower_RoofDay_Text_Kimono_Opening", "TinTower_RoofDay_Text_Kimono_Closing1",
    ],
    "data/maps/EcruteakCity_Theater_hns/scripts.inc": [
        "EcruteakCity_Theater_Text_GirlHooh", "EcruteakCity_Theater_Text_ZukiHooh",
    ],
    "data/maps/RuinsOfAlph_Lab_hns/scripts.inc": [
        "RuinsOfAlph_Lab_Text_NeedElite20", "RuinsOfAlph_Lab_Text_MtSilverSummit",
        "RuinsOfAlph_Lab_Text_RelicsComplete",
    ],
    "data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc": [
        "PRU_Elite20_Text_OakRelics", "PRU_Elite20_Text_RuinsDirections",
        "PRU_Elite20_Text_FinalCelebration", "PRU_Elite20_Text_GoldenSky",
    ],
    "data/maps/PalletTown_Lab_hns/scripts.inc": [
        "PalletTown_Lab_Text_OakRelicsExplain", "PalletTown_Lab_Text_OakRelicsCrest",
        "PalletTown_Lab_Text_OakRelicsHoOh",
    ],
}
for path, labels in dialogue.items():
    lines = read(path).splitlines()
    for index, line in enumerate(lines):
        if not any(line.startswith(label + ":") for label in labels):
            continue
        label = line.split(":", 1)[0]
        for body in lines[index + 1:]:
            if re.match(r"^\w+::?$", body):
                break
            if ".string" not in body:
                continue
            value = body.split(".string", 1)[1]
            for text_line in re.split(r"\\[nlp]", value):
                text_line = text_line.strip().strip('"')
                assert len(text_line) <= 29, f"{path}:{label}: text line too wide: {text_line}"

print("PASS: Job 18 dialogue, gates, summit, retry and Tin Tower source progression")
