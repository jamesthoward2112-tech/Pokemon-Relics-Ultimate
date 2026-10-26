#!/usr/bin/env python3
"""Regression check for Battle Frontier's repeatable Chansey XP station."""

import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
MAP = ROOT / "data/maps/BattleFrontier_ExchangeServiceCorner_hns/map.json"
PARTIES = ROOT / "src/data/trainers_hns.party"
TRAINING_SCRIPT = ROOT / "data/maps/CherrygroveCity_PokemonCenter_hns/scripts.inc"


def check() -> None:
    events = json.loads(MAP.read_text())["object_events"]
    exchange_clerks = sorted(
        e["x"] for e in events
        if e["graphics_id"] == "OBJ_EVENT_GFX_WORKER_F_HNS"
        and e["y"] == 5 and e["script"] in (
            "BattleFrontier_ExchangeServiceCorner_EventScript_DecorClerk2_hns",
            "BattleFrontier_ExchangeServiceCorner_EventScript_PokeBallClerk_hns",
            "BattleFrontier_ExchangeServiceCorner_EventScript_VitaminClerk_hns",
        )
    )
    assert exchange_clerks == [5, 7, 9], exchange_clerks

    trainers = [e for e in events if e["script"] == "PRU_ChanseyTrainer_Lv100"]
    assert len(trainers) == 1, "expected one Chansey XP desk attendant"
    trainer = trainers[0]
    assert (trainer["x"], trainer["y"]) == (11, 5)
    assert trainer["graphics_id"] == "OBJ_EVENT_GFX_MON_BASE+SPECIES_CHANSEY"
    assert trainer["movement_type"] == "MOVEMENT_TYPE_FACE_DOWN"
    assert trainer["flag"] == "0"

    text = PARTIES.read_text()
    team = text.split("=== TRAINER_PRU_CHANSEY_100_HNS ===", 1)[1].split("===", 1)[0]
    assert "Double Battle: Yes" in team
    assert team.count("Chansey\nLevel: 100") == 2
    assert team.count("- Memento") == 2
    assert team.count("- Heal Pulse") == 2

    scripts = TRAINING_SCRIPT.read_text()
    assert "PRU_ChanseyTrainer_Lv100::" in scripts
    assert "cleartrainerflag TRAINER_PRU_CHANSEY_100_HNS" in scripts
    assert "trainerbattle_double TRAINER_PRU_CHANSEY_100_HNS" in scripts
    assert "PRU_ChanseyTrainer_Text_Offer, MSGBOX_YESNO" in scripts


if __name__ == "__main__":
    check()
    print("Battle Frontier Chansey XP station validated")
