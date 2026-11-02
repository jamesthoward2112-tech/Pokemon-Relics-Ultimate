#!/usr/bin/env python3
"""Guard Dark Void's I-Unown learnability and preserve its battle behavior."""

from pathlib import Path
import re


ROOT = Path(__file__).resolve().parents[2]
RR_V41_MOVE_ADDITIONS = (
    "ALLURING_VOICE", "BARB_BARRAGE", "BURNING_BULWARK", "ELECTRO_SHOT",
    "FICKLE_BEAM", "FLIP_TURN", "GRASSY_GLIDE", "HEAT_CRASH", "JET_PUNCH",
    "LUNGE", "MIGHTY_CLEAVE", "PSYCHIC_NOISE", "SHED_TAIL", "TIDY_UP",
    "THUNDERCLAP", "UPPER_HAND", "VACUUM_WAVE",
)


def section(source: str, start: str, end: str) -> str:
    begin = source.index(start)
    finish = source.index(end, begin)
    return source[begin:finish]


learnsets = (ROOT / "src/data/pokemon/level_up_learnsets/pjr.h").read_text()
i_unown = section(learnsets, "sUnownEyeLevelUpLearnset[]", "sDrakeonLevelUpLearnset[]")
assert "LEVEL_UP_MOVE(1, MOVE_DARK_VOID)" in i_unown, "I-Unown must learn Dark Void at level 1"

move_data = (ROOT / "src/data/moves_info.h").read_text()
move_constants = (ROOT / "include/constants/moves.h").read_text()
for name in RR_V41_MOVE_ADDITIONS:
    move = f"MOVE_{name}"
    assert move in move_constants, f"Radical Red v4.1 move ID missing: {move}"
    assert len(re.findall(rf"\[{move}\]\s*=", move_data)) == 1, f"Move data missing/duplicated: {move}"

supercell_slam = section(move_data, "[MOVE_SUPERCELL_SLAM]", "[MOVE_PSYCHIC_NOISE]")
assert ".power = 120" in supercell_slam, "Radical Red v4.1 raises Supercell Slam to 120 BP"

flash = section(move_data, "[MOVE_FLASH]", "[MOVE_PSYWAVE]")
assert ".magicCoatAffected = FALSE" in flash, "Radical Red v4.1 fixes Flash being affected by Magic Coat"

tidy_up_script = section(
    (ROOT / "data/battle_scripts_1.s").read_text(),
    "BattleScript_EffectTidyUp::",
    "BattleScript_EffectTidyUpDoMoveAnimation::",
)
assert "trytidyup FALSE" in tidy_up_script, "Tidy Up must clear hazards before its stat changes"
tidy_up_clear = section(
    (ROOT / "src/battle_script_commands.c").read_text(),
    "static bool32 TryTidyUpClear(",
    "u32 IsFlowerVeilProtected(",
)
assert "DefogClearHazards(saveBattler, i, clear)" in tidy_up_clear

multi_hit = (ROOT / "src/battle_move_resolution.c").read_text()
assert "RandomUniform(RNG_LOADED_DICE, 4, 5)" in multi_hit
assert "GetMoveEffect(ctx->move) == EFFECT_POPULATION_BOMB" in multi_hit

dragon_tail = section(move_data, "[MOVE_DRAGON_TAIL]", "[MOVE_WORK_UP]")
assert re.search(r"\.pp\s*=\s*10\s*,", dragon_tail)

dark_void = section(move_data, "[MOVE_DARK_VOID]", "[MOVE_SEED_FLARE]")
assert ".type = TYPE_DARK" in dark_void
assert ".accuracy = B_UPDATED_MOVE_DATA >= GEN_7 ? 50 : 80" in dark_void
assert re.search(r"\.pp\s*=\s*10\s*,", dark_void), "Dark Void must retain 10 PP"
assert ".target = TARGET_BOTH" in dark_void, "Dark Void must target both opposing Pokémon"
assert ".argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP }" in dark_void
assert ".battleAnimScript = gBattleAnimMove_DarkVoid" in dark_void

effect_script = (ROOT / "data/battle_scripts_1.s").read_text()
dark_void_script = section(effect_script, "BattleScript_EffectDarkVoid::", "BattleScript_EffectNonVolatileStatus::")
assert "jumpifspecies SPECIES_DARKRAI, BattleScript_EffectNonVolatileStatus" in dark_void_script
assert "jumpifspecies SPECIES_UNOWN_I, BattleScript_EffectNonVolatileStatus" in dark_void_script
assert "BattleScript_PokemonCantUseTheMove" in dark_void_script, "Keep the restriction for other non-Darkrai users"

ai = (ROOT / "src/battle_ai_main.c").read_text()
dark_void_ai = section(ai, "case EFFECT_DARK_VOID:", "case EFFECT_HYPERSPACE_FURY:")
assert "SPECIES_DARKRAI" in dark_void_ai and "SPECIES_UNOWN_I" in dark_void_ai

omen_eye = section(move_data, "[MOVE_OMEN_EYE]", "[MOVE_MINDWAVE]")
for expected in (
    ".effect = EFFECT_HIT",
    ".power = 95",
    ".type = TYPE_GHOST",
    ".accuracy = 100",
    ".pp = 10",
    ".target = TARGET_SELECTED",
    ".moveEffect = MOVE_EFFECT_FEAR, .chance = 20",
    ".battleAnimScript = gBattleAnimMove_MeanLook",
):
    assert expected in omen_eye, f"Omen Eye changed: missing {expected}"

print("Dark Void / I-Unown source regression: PASS")
