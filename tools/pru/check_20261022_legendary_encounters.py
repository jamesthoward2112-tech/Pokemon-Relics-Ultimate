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
    ("Route45_GroudonCave_hns", "GROUDON", "RED", "MAXIE",
     "FLAG_PRU_GROUDON_CAUGHT", "FLAG_PRU_MAXIE_GROUDON_DEFEATED"),
):
    script = read(f"data/maps/{map_name}/scripts.inc")
    data = json.loads(read(f"data/maps/{map_name}/map.json"))
    assert f"setwildbattleshiny SPECIES_{mon}, 75, ITEM_{orb}_ORB" in script, mon
    assert f"seteventmon SPECIES_{mon}_PRIMAL" not in script, mon
    assert f"playmoncry SPECIES_{mon}, CRY_MODE_ENCOUNTER" in script, mon
    assert f"goto_if_unset {defeated}" in script, mon
    assert f"setflag {caught}" in script, mon
    assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT" in script, mon
    expected_sprite = f"OBJ_EVENT_GFX_PRU_SHINY_PRIMAL_{mon}_HNS"
    assert any(o.get("graphics_id") == expected_sprite
               and o.get("flag") == ("FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE" if mon == "KYOGRE" else "FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE") for o in data["object_events"]), mon
    assert any(o.get("graphics_id") == f"OBJ_EVENT_GFX_{boss}"
               and o.get("trainer_sight_or_berry_tree_id") == "4"
               and o.get("flag") == defeated for o in data["object_events"]), boss

electrode = read("data/maps/Route10_hns/scripts.inc")
route = json.loads(read("data/maps/Route10_hns/map.json"))
pokemon = read("src/pokemon.c")
util = read("src/script_pokemon_util.c")
assert "setwildbattleshiny SPECIES_ELECTRODE, 80" in electrode
assert "special PruPrepareChargedElectrode" in electrode
# The Power Plant Electrode stays visible after Kaboom! self-KO, any other
# knockout, fleeing or whiteout. Capture is the *only* permanent removal.
encounter, caught_block = electrode.split("Route10_EventScript_PRU_ElectrodeCaught::", 1)
encounter = encounter.split("Route10_EventScript_PRU_ShinyElectrode::", 1)[1]
caught_block = caught_block.split("Route10_Text_PRU_ShinyElectrode:", 1)[0]
assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route10_EventScript_PRU_ElectrodeCaught" in encounter
assert "removeobject LOCALID_ROUTE10_PRU_ELECTRODE" not in encounter
assert "setflag FLAG_PRU_POWER_PLANT_ELECTRODE_CAUGHT" not in encounter
assert "setflag FLAG_PRU_POWER_PLANT_ELECTRODE_CAUGHT" in caught_block
assert "removeobject LOCALID_ROUTE10_PRU_ELECTRODE" in caught_block
assert any(o.get("graphics_id") == "OBJ_EVENT_GFX_SPECIES_SHINY(ELECTRODE)"
           and o.get("flag") == "FLAG_PRU_POWER_PLANT_ELECTRODE_CAUGHT"
           for o in route["object_events"])
assert "MON_DATA_MODERN_FATEFUL_ENCOUNTER" in util
assert "return ABILITY_LEVITATE;" in pokemon and "IsPruChargedElectrode" in pokemon
# Ability must survive initial battle setup and display in party/PC summaries.
assert "dst->ability = GetMonAbility(src);" in pokemon
battle_main = read("src/battle_main.c")
# Initial battle and switch-in must use the actual Pokémon's ability,
# never the species default (Static/Soundproof for Electrode).
intro = battle_main.split("case BATTLE_INTRO_STATE_DRAW_SPRITES:", 1)[1].split("case BATTLE_INTRO_STATE_", 1)[0]
ability_source = "gBattleMons[battler].ability = GetMonAbility(&GetSideParty(side)[gBattlerPartyIndexes[battler]]);"
assert ability_source in intro
assert "GetAbilityBySpecies(gBattleMons[battler].species" not in intro
summary = read("src/pokemon_summary_screen.c")
assert "GetBoxMonData(GetCurrentBoxmon(), MON_DATA_MODERN_FATEFUL_ENCOUNTER)" in summary
assert summary.count("enum Ability ability = GetSummaryMonAbility();") == 2
# The new encounter knows Kablow; a caught old Electrode gets the move if
# its fourth slot is still the original Electro Ball.
assert "SetMonMoveSlot(mon, MOVE_KABOOM, 3);" in util
assert "GetMonData(mon, MON_DATA_MOVE4) == MOVE_ELECTRO_BALL" in pokemon
assert "GetMonData(mon, MON_DATA_MOVE4) == MOVE_KABLOW" in pokemon
assert "SetMonMoveSlot(mon, MOVE_KABOOM, 3);" in pokemon
# Kaboom is a new signature move, not a rewrite of Kablowfish's Kablow!
moves = read("include/constants/moves.h")
infos = read("src/data/moves_info.h")
resolution = read("src/battle_move_resolution.c")
switching = read("src/battle_script_commands.c")
assert moves.index("MOVE_KABLOW,") < moves.index("MOVE_KABOOM,") < moves.index("MOVES_COUNT,")
assert "[MOVE_KABLOW]" in infos and ".power = 170" in infos.split("[MOVE_KABLOW]", 1)[1].split("},", 1)[0]
kaboom = infos.split("[MOVE_KABOOM]", 1)[1].split("    [MOVE_", 1)[0]
for expected in ('.power = 200', '.type = TYPE_ELECTRIC',
                 '.explosion = TRUE', '.chance = 100',
                 '.moveEffect = MOVE_EFFECT_PARALYSIS',
                 'Paralyzes survivors.'):
    assert expected in kaboom, expected
assert "gCurrentMove == MOVE_KABOOM" in resolution
kb = resolution.split("gCurrentMove == MOVE_KABOOM", 1)[1].split("else if", 1)[0]
assert "HAZARDS_SPIKES" in kb and "HAZARDS_STEALTH_ROCK" in kb
assert "HAZARDS_TOXIC_SPIKES" not in kb
assert "GetMonAbility(&GetSideParty(side)[gBattlerPartyIndexes[battler]])" in switching
# Siege Tusk itself is a standard Ground damaging move without ability bypass.
siege = infos.split("[MOVE_SIEGE_TUSK]", 1)[1].split("    [MOVE_", 1)[0]
assert ".type = TYPE_GROUND" in siege
assert "ignoresTargetAbility = TRUE" not in siege
assert "ABILITY_LEVITATE" in read("src/battle_util.c")

assert "MOVE_KABLOW" in read("src/data/pokemon/level_up_learnsets/pjr.h")
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
