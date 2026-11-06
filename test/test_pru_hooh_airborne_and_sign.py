"""PRU Golden Ho-Oh must resist Ground through Phoenix Soul and the sign must stay evergreen."""
from pathlib import Path
import re

u = Path("src/battle_util.c").read_text()
sign = Path("data/maps/MtSilver_Outside_hns/scripts.inc").read_text()
info = Path("src/data/pokemon/species_info/pjr_families.h").read_text()
ci = Path(".github/workflows/pru-clean-build.yml").read_text()

assert 'ability == ABILITY_LEVITATE || ability == ABILITY_PHOENIX_SOUL' in u
assert 'ctx->abilityDef == ABILITY_LEVITATE || ctx->abilityDef == ABILITY_PHOENIX_SOUL' in u
assert 'gLastUsedAbility = ctx->abilityDef;' in u
assert 'RecordAbilityBattle(ctx->battlerDef, ctx->abilityDef);' in u
assert "IsBattlerGroundedInverseCheck" in u
relic = info.split("[SPECIES_RELIC_HO_OH] =", 1)[1].split("\n[SPECIES_", 1)[0]
assert "TYPE_FIRE, TYPE_FAIRY" in relic
assert "ABILITY_PHOENIX_SOUL" in relic
assert 'Shortcut to the top?$' in sign
assert 'shortcut to RED' not in sign
assert 'warp MAP_MT_SILVER_SUMMIT_DAY_HNS, 10, 8' in sign
assert "python3 test/test_pru_hooh_airborne_and_sign.py" in ci
print("PRU_HOOH_GROUND_IMMUNITY_AND_SIGN_PASS")
