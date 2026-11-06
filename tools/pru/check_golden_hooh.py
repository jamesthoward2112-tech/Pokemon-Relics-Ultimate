#!/usr/bin/env python3
"""Source regressions for Job 6 Golden Ho-Oh signatures and sole encounter."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

def read(path):
    return (ROOT / path).read_text()

def section(source, start, end):
    return source.split(start, 1)[1].split(end, 1)[0]

constants = read("include/constants/abilities.h")
assert constants.index("ABILITY_GOLDEN_SOVEREIGN,") < constants.index("ABILITY_PHOENIX_SOUL,") < constants.index("ABILITIES_COUNT,")
assert "[ABILITY_PHOENIX_SOUL]" in read("src/data/abilities.h")
assert '_("PHOENIX SOUL")' in read("src/data/abilities.h")

moves = read("include/constants/moves.h")
assert moves.index("MOVE_OMEN_EYE,") < moves.index("MOVE_GOLDEN_REIGN,") < moves.index("MOVES_COUNT,")
golden_move = section(read("src/data/moves_info.h"), "[MOVE_GOLDEN_REIGN] =", "\n    },")
for expected in (
    '.power = 110', '.type = TYPE_FIRE', '.accuracy = 100', '.pp = 5',
    '.target = TARGET_BOTH', '.category = DAMAGE_CATEGORY_SPECIAL',
    '.metronomeBanned = TRUE', '.instructBanned = TRUE', '.mimicBanned = TRUE',
    '.copycatBanned = TRUE', '.sketchBanned = TRUE', '.mirrorMoveBanned = TRUE',
    '.moveEffect = MOVE_EFFECT_BURN', '.chance = 20',
    '.moveEffect = MOVE_EFFECT_SUN', '.chance = 100',
    '.battleAnimScript = gBattleAnimMove_MakeItRain',
):
    assert expected in golden_move, expected
assert "MOVE_EFFECT_PAYDAY" not in golden_move
assert "MOVE_EFFECT_SP_ATK_MINUS_1" not in golden_move

species = read("src/data/pokemon/species_info/pjr_families.h")
relic = section(species, "[SPECIES_RELIC_HO_OH] =", "[SPECIES_")
for stat in ("baseHP = 106", "baseAttack = 100", "baseDefense = 100", "baseSpAttack = 140", "baseSpDefense = 140", "baseSpeed = 114"):
    assert stat in relic, stat
assert ".abilities = { ABILITY_PHOENIX_SOUL, ABILITY_PHOENIX_SOUL, ABILITY_PHOENIX_SOUL }" in relic
for sprite in ("gMonFrontPic_HoOhRelic", "gMonBackPic_HoOhRelic", "gMonPalette_HoOhRelic", "gMonIcon_HoOhRelic"):
    assert sprite in relic

learnset = read("src/data/pokemon/level_up_learnsets/pjr.h")
hooh_learnset = section(learnset, "static const struct LevelUpMove sRelicHoOhLevelUpLearnset[]", "static const struct LevelUpMove sHeracurionLevelUpLearnset[]")
assert "LEVEL_UP_MOVE(100, MOVE_GOLDEN_REIGN)" in hooh_learnset
assert "MOVE_GOLDEN_REIGN" not in read("src/data/pokemon/all_learnables.json")
relearner = read("src/move_relearner.c")
assert "GetRelearnerLevelUpMoves(boxmon" in relearner

pokemon = read("src/pokemon.c")
event_mon = section(pokemon, "void CreateEnemyEventMon(void)", "static u16 CalculateBoxMonChecksum")
assert "species == SPECIES_RELIC_HO_OH && level == 100" in event_mon
assert "SetMonMoveSlot(&gEnemyParty[0], MOVE_GOLDEN_REIGN, 0);" in event_mon
assert "SetMonMoveSlot(&gEnemyParty[0], MOVE_PHOENIX_HYMN, 2);" in event_mon
assert "ABILITY_NUM" not in event_mon

battle = read("src/battle_util.c")
phoenix = section(battle, "else if (ctx->abilityDef == ABILITY_PHOENIX_SOUL", "else if (GetConfig(B_STURDY)")
assert "pjrPhoenixSoulUsed[ctx->battlerDef]" in phoenix
assert "pjrPhoenixSoulPending[ctx->battlerDef]" in phoenix
assert "GetMovePower(ctx->move) != 0" in phoenix
assert "enduredHit = TRUE;" in phoenix
assert "gBattleMons[ctx->battlerDef].hp > 0" in phoenix
assert "MOVE_RESULT_STURDIED" in phoenix
assert "RecordAbilityBattle(ctx->battlerDef, ABILITY_PHOENIX_SOUL)" in phoenix
apply_damage = read("src/battle_script_commands.c")
phoenix_heal = section(apply_damage, "if (gBattleStruct->pjrPhoenixSoulPending[battler]", "if (gCurrentMove == MOVE_PHOENIX_HYMN")
assert "max(1, gBattleMons[battler].maxHP / 4)" in phoenix_heal
assert "pjrPhoenixSoulPending[battler] = FALSE" in phoenix_heal
assert "pjrPhoenixSoulUsed[MAX_BATTLERS_COUNT]" in read("include/battle.h")

oak = read("data/maps/MtSilver_SummitDay_hns/scripts.inc")
oak_event = section(oak, "MtSilver_SummitDay_EventScript_OakSummon::", "MtSilver_SummitDay_EventScript_OakRelicCaught::")
assert "FLAG_PJR_GOT_RAINBOW_CREST" not in oak_event
assert "ITEM_ANCIENT_RAINBOW_CREST" not in oak_event
assert "seteventmon SPECIES_RELIC_HO_OH, 100" in oak_event
assert "setweather WEATHER_SUNNY" in oak_event
assert "MtSilver_SummitDay_Text_OakRetry" in oak_event
caught = section(oak, "MtSilver_SummitDay_EventScript_OakRelicCaught::", "MtSilver_SummitDay_EventScript_OakEpilogue::")
assert "setflag FLAG_PJR_RELIC_HO_OH" in caught and "setflag FLAG_HIDE_HO_OH" in caught
assert "PRU_Elite20_StartFinale" in caught

for path in ("data/maps/TinTower_RoofDay_hns/scripts.inc", "data/maps/NavelRock_Summit_Frlg/scripts.inc", "data/maps/NavelRock_Top/scripts.inc"):
    source = read(path)
    assert "seteventmon SPECIES_HO_OH" not in source, path
    assert "BattleSetup_StartLegendaryBattle" not in source, path
all_scripts = "\n".join(p.read_text(errors="ignore") for p in (ROOT / "data/maps").rglob("*.inc"))
assert all_scripts.count("seteventmon SPECIES_RELIC_HO_OH,") == 1
print("PASS: Golden Ho-Oh stats/moves, Phoenix Soul, sole gated Lv100 encounter and retry story")

