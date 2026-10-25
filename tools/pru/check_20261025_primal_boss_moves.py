#!/usr/bin/env python3
"""Check both shiny Primal finale battles and Water Spout on existing Kyogre."""
from pathlib import Path
import json
import re

root = Path(__file__).resolve().parents[2]


def read(path):
    return (root / path).read_text(encoding="utf-8")


def kyogre_moves(path):
    source = read(path)
    block = source.split("static const struct LevelUpMove sKyogreLevelUpLearnset[] = {", 1)[1].split("LEVEL_UP_END", 1)[0]
    return [(int(level), move) for level, move in re.findall(
        r"LEVEL_UP_MOVE\(\s*(\d+),\s*MOVE_([A-Z_]+)\)", block
    )]


# Modern Gen 7 and classic Gen 3 modes both allow a captured Lv75 Kyogre
# to relearn Water Spout in a continuing save.
assert "#define P_LVL_UP_LEARNSETS          GEN_7" in read("include/config/pokemon.h")
for gen in (3, 7):
    learnset = kyogre_moves(f"src/data/pokemon/level_up_learnsets/gen_{gen}.h")
    assert any(level <= 75 and move == "WATER_SPOUT" for level, move in learnset), gen

parties = read("src/data/trainers_hns.party")
archie = parties.split("=== TRAINER_PRU_ARCHIE_KYOGRE_HNS ===", 1)[1].split("=== TRAINER_PRU_MAXIE_GROUDON_HNS ===", 1)[0]
maxie = parties.split("=== TRAINER_PRU_MAXIE_GROUDON_HNS ===", 1)[1].split("=== TRAINER_STEEVE_NEEVEE_CELADON_HNS ===", 1)[0]
expected = {
    "KYOGRE": ("Water Spout", "Origin Pulse", "Thunder", "Ice Beam"),
    "GROUDON": ("Hone Claws", "Precipice Blades", "Fire Punch", "Dragon Claw"),
}
for name, party, held_item in (
    ("KYOGRE", archie, "Blue Orb"),
    ("GROUDON", maxie, "Red Orb"),
):
    assert "AI: Smart Trainer / Prediction / Ace Pokemon" in party
    assert len(re.findall(r"^Level: ", party, re.M)) == 6, name
    ace = party.split(f"{name.title()} @ {held_item}", 1)[1].split("===", 1)[0]
    assert "Level: 80" in ace and "Shiny: Yes" in ace
    moves = tuple(re.findall(r"^- (.+)$", ace, re.M))
    assert moves == expected[name], (name, moves)

util = read("src/script_pokemon_util.c")
func = util.split("void PruPreparePrimalLegendMoves(void)", 1)[1].split("\n}", 1)[0]
for mon, moves in expected.items():
    segment = func.split(f"species == SPECIES_{mon}", 1)[1].split("\n    }", 1)[0]
    for slot, move in enumerate(moves):
        constant = "MOVE_" + move.upper().replace(" ", "_")
        assert f"SetMonMoveSlot(mon, {constant}, {slot});" in segment
assert "\tdef_special PruPreparePrimalLegendMoves" in read("data/specials.inc")

for place, mon, boss, caught, hide in (
    ("SeafoamIslands_SecretCave_hns", "KYOGRE", "Archie", "FLAG_PRU_KYOGRE_CAUGHT", "FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE"),
    ("MtSilver_1F_MoltresRoom_hns", "GROUDON", "Maxie", "FLAG_PRU_GROUDON_CAUGHT", "FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE"),
):
    script = read(f"data/maps/{place}/scripts.inc")
    map_data = json.loads(read(f"data/maps/{place}/map.json"))
    assert f"setwildbattleshiny SPECIES_{mon}, 75, ITEM_{'BLUE' if mon == 'KYOGRE' else 'RED'}_ORB" in script
    encounter = script.split(f"EventScript_{mon.title()}::", 1)[1]
    assert encounter.index("special PruPreparePrimalLegendMoves") < encounter.index("special BattleSetup_StartLegendaryBattle")
    assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT" in encounter
    assert f"setflag {caught}" in encounter.split(f"EventScript_{mon.title()}Caught::", 1)[1]
    obj = next(o for o in map_data["object_events"] if o["local_id"] == f"LOCALID_PRU_{mon}")
    assert obj["flag"] == hide
    assert obj["graphics_id"] == f"OBJ_EVENT_GFX_PRU_SHINY_PRIMAL_{mon}_HNS"
    boss_script = script.split(f"EventScript_{boss}::", 1)[1].split(f"EventScript_{boss}AfterBattle:", 1)[0]
    assert f"EventScript_{boss}AfterBattle" in boss_script
    reveal = script.split(f"EventScript_{boss}AfterBattle:", 1)[1].split(f"EventScript_{mon.title()}::", 1)[0]
    assert reveal.index(f"setflag FLAG_PRU_{boss.upper()}_{mon}_DEFEATED") < reveal.index(f"addobject LOCALID_PRU_{mon}")
    assert reveal.index(f"addobject LOCALID_PRU_{mon}") < reveal.index(f"removeobject LOCALID_PRU_{boss.upper()}")

flags = read("include/constants/flags_hns.h")
assert "#define FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE             0x4FF" in flags
palette = read("graphics/pokemon/groudon/primal/shiny.pal")
colors = [tuple(map(int, line.split())) for line in palette.splitlines()[3:]]
assert colors[1] == (0, 0, 0) and max(colors[2]) < 70

print("PRU_PRIMAL_BOSSES_PASS: exact trainer and catch moves, hidden reveal, black shiny Primals, Kyogre relearn")
