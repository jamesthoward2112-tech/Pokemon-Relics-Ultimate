#!/usr/bin/env python3
"""Second Kanto League flow and small story/UX regression checks."""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(relative):
    return (ROOT / relative).read_text(encoding="utf-8")


rooms = [
    ("WillsRoom", "Will", "Lorelei", "WILL_HNS", "LORELEI"),
    ("KogasRoom", "Koga", "Bruno", "KOGA_HNS", "BRUNO_HNS"),
    ("BrunosRoom", "Bruno", "Agatha", "BRUNO_HNS", "AGATHA"),
    ("KarensRoom", "Karen", "Lance", "KAREN_HNS", "LANCE_HNS"),
    ("ChampionsRoom", "Lance", "Red", "LANCE_HNS", "RED_NORMAL_HNS"),
]
for folder, johto, kanto, johto_gfx, kanto_gfx in rooms:
    prefix = f"data/maps/PokemonLeague_{folder}_hns"
    game_map = json.loads(read(f"{prefix}/map.json"))
    trainer_npcs = [o for o in game_map["object_events"] if (o["x"], o["y"]) in {(6, 6), (6, 8)}]
    assert len(trainer_npcs) == 1, (folder, "single always-visible trainer required")
    actor = trainer_npcs[0]
    assert actor["flag"] == "0" and actor["graphics_id"] == "OBJ_EVENT_GFX_VAR_0"
    assert actor["script"] == f"PRU_KantoE4_{johto}Or{kanto}"
    script = read(f"{prefix}/scripts.inc")
    assert f"setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_{johto_gfx}" in script
    assert f"setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_{kanto_gfx}" in script
    assert f"PRU_KantoE4_{johto}Or{kanto}::" in script
    assert "call PRU_KantoE4_CheckActive" in script
    assert f"goto_if_eq VAR_RESULT, TRUE, PRU_KantoE4_{kanto}" in script

common = read("data/maps/PokemonLeague_WillsRoom_hns/scripts.inc")
for flag in ["FLAG_IS_CHAMPION", "FLAG_BADGE16_GET", "FLAG_PRU_HEIST_COMPLETED",
             "FLAG_PRU_HEIST_GIOVANNI", "FLAG_PRU_KANTO_LEAGUE_CLEARED"]:
    assert flag in common
assert "PRU_KantoE4_CheckActive::" in common

champion = read("data/maps/PokemonLeague_ChampionsRoom_hns/scripts.inc")
red = champion.split("PRU_KantoE4_Red::", 1)[1].split("PokemonLeague_ChampionsRoom_OnResume::", 1)[0]
for phrase in ["addobject LOCALID_LEAGUE_OAK", "PRU_KantoE4_OakCongratulations",
               "setflag FLAG_PRU_KANTO_LEAGUE_CLEARED", "warpsilent MAP_POKEMON_LEAGUE_HALL_OF_FAME_HNS"]:
    assert phrase in red or phrase in champion, phrase
assert red.index("addobject LOCALID_LEAGUE_OAK") < red.index("warpsilent")

indigo = json.loads(read("data/maps/IndigoPlateau_PokemonCenter_hns/map.json"))
assert not any(o["script"] == "PRU_Elite18_Steward" for o in indigo["object_events"])
center_script = read("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
assert "PRU_LeagueEntrance_Seal::" in center_script
assert "SAFFRON" in center_script
assert "PRU_Elite18_Steward::" in center_script

dojo = json.loads(read("data/maps/SaffronCity_FightingDojoVIP_hns/map.json"))
elite = [o for o in dojo["object_events"] if o["script"] == "PRU_Elite18_Steward"]
assert len(elite) == 1 and elite[0]["flag"] == "0"
chansey = [o for o in dojo["object_events"] if o["script"] == "PRU_ChanseyTrainer_Lv100"]
assert len(chansey) == 1
assert (chansey[0]["x"], chansey[0]["y"]) == (39, 5)
assert chansey[0]["flag"] == "0"
assert not any(o["script"] != "PRU_ChanseyTrainer_Lv100" and
               (o["x"], o["y"]) == (39, 5) for o in dojo["object_events"])

new_bark = read("data/maps/NewBarkTown_hns/scripts.inc")
hof = read("data/maps/PokemonLeague_HallOfFame_hns/scripts.inc")
items = read("src/data/items.h")
assert "giveitem ITEM_RELIC_CANDY" in new_bark
assert "ANCIENT CANDY" in new_bark and '.name = ITEM_NAME("ANCIENT CANDY")' in items
assert "setvar VAR_NEWBARK_TOWN_STATE, 8" in hof

sinjoh = read("data/maps/SinjohRuins_hns/scripts.inc")
battle = sinjoh.split("SinjohRuins_EventScript_StevenBattle::", 1)[1].split("SinjohRuins_Text_HealParty::", 1)[0]
assert "setflag FLAG_HIDE_SINJOHRUINS_STEVEN" in battle
assert "removeobject LOCALID_SINJOHRUINS_STEVEN" in battle
assert "call_if_ge VAR_SINJOH_STORYLINE, 10, SinjohRuins_HideStevenAfterBattle" in sinjoh
assert "FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_STEVEN" in read("data/maps/SinjohRuins_ArceusRoom_hns/map.json")

moves = read("src/data/moves_info.h")
fog = moves.split("[MOVE_EERIE_FOG]", 1)[1].split(".effect", 1)[0]
assert re.search(r"\.description\s*=\s*COMPOUND_STRING\([^)]*\\n", fog), fog
print("PASS: visible E4 roster, Oak/Elm finale, Dojo Elite18/Chansey, Steven, Eerie Fog")
