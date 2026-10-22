#!/usr/bin/env python3
"""Guard the 22 Oct PRU native-Primal, unique Electrode and Aurora Ticket events."""
import json
from pathlib import Path

root = Path(__file__).resolve().parents[2]
def read(path):
    return (root / path).read_text(encoding="utf-8")

for map_name, mon, orb, boss, caught, defeated in (
    ("SeafoamIslands_SecretCave_hns", "KYOGRE", "BLUE", "ARCHIE",
     "FLAG_PRU_KYOGRE_CAUGHT", "FLAG_PRU_ARCHIE_KYOGRE_DEFEATED"),
    ("MtSilver_1F_MoltresRoom_hns", "GROUDON", "RED", "MAXIE",
     "FLAG_PRU_GROUDON_CAUGHT", "FLAG_PRU_MAXIE_GROUDON_DEFEATED"),
):
    script = read(f"data/maps/{map_name}/scripts.inc")
    data = json.loads(read(f"data/maps/{map_name}/map.json"))
    assert f"seteventmon SPECIES_{mon}, 75, ITEM_{orb}_ORB" in script, mon
    assert f"seteventmon SPECIES_{mon}_PRIMAL" not in script, mon
    assert f"playmoncry SPECIES_{mon}, CRY_MODE_ENCOUNTER" in script, mon
    assert f"goto_if_unset {defeated}" in script, mon
    assert f"setflag {caught}" in script, mon
    assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT" in script, mon
    assert any(o.get("graphics_id") == f"OBJ_EVENT_GFX_SPECIES({mon}_PRIMAL)"
               and o.get("flag") == caught for o in data["object_events"]), mon
    assert any(o.get("graphics_id") == f"OBJ_EVENT_GFX_{boss}"
               and o.get("trainer_sight_or_berry_tree_id") == "4"
               and o.get("flag") == defeated for o in data["object_events"]), boss

electrode = read("data/maps/Route10_hns/scripts.inc")
route = json.loads(read("data/maps/Route10_hns/map.json"))
pokemon = read("src/pokemon.c")
util = read("src/script_pokemon_util.c")
assert "setwildbattleshiny SPECIES_ELECTRODE, 80" in electrode
assert "special PruPrepareChargedElectrode" in electrode
assert "setflag FLAG_PRU_POWER_PLANT_ELECTRODE_CAUGHT" in electrode
assert any(o.get("graphics_id") == "OBJ_EVENT_GFX_SPECIES_SHINY(ELECTRODE)"
           and o.get("flag") == "FLAG_PRU_POWER_PLANT_ELECTRODE_CAUGHT"
           for o in route["object_events"])
assert "MON_DATA_MODERN_FATEFUL_ENCOUNTER" in util
assert "return ABILITY_LEVITATE;" in pokemon and "IsPruChargedElectrode" in pokemon
for stat, amount in (("HP",100), ("ATK",100), ("DEF",115), ("SPATK",150),
                     ("SPDEF",125), ("SPEED",175)):
    assert f"[STAT_{stat}] = {amount}" in pokemon

oak = read("data/maps/PalletTown_Lab_hns/scripts.inc")
olivine = read("data/maps/OlivineCity_PortInside_hns/scripts.inc")
assert "goto_if_ge VAR_NUM_BADGES, 12" in oak
assert "giveitem ITEM_AURORA_TICKET" in oak
assert "goto_if_eq VAR_RESULT, FALSE, PalletTown_Lab_EventScript_OakPRUAuroraBagFull" in oak
assert "setflag FLAG_PRU_OAK_AURORA_TICKET_RECEIVED" in oak
assert "checkitem ITEM_AURORA_TICKET" in olivine
assert "warpsilent MAP_BIRTH_ISLAND_EXTERIOR_HNS" in olivine
print("PRU_LEGENDARY_20261022_PASS: canonical Primal Orb encounters, boss gates, unique Electrode, Aurora Ticket")
