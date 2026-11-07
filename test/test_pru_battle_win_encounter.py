"""PRU alpha: battle Win Encounter shortcut is compiled out, normal controls preserved."""
from pathlib import Path
import re

cfg = Path("include/config/debug.h").read_text()
globals = Path("include/constants/global.h").read_text()
controller = Path("src/battle_controller_player.c").read_text()
debug_menu = Path("src/battle_debug.c").read_text()
battle = Path("src/battle_main.c").read_text()
ci = Path(".github/workflows/pru-clean-build.yml").read_text()

assert re.search(r"^#define\s+DEBUG_BATTLE_MENU\s+FALSE\b", cfg, re.M)
assert re.search(r"^#define\s+DEBUG_OVERWORLD_MENU\s+FALSE\b", cfg, re.M)
assert "#define DISABLED_ON_RELEASE FALSE" in globals
assert "#define DISABLED_ON_RELEASE TRUE" in globals

# Shortcut is restricted to the action menu; battle move-selection START gimmicks remain untouched.
start = controller.index("void HandleInputChooseAction(")
end = controller.index("void HandleInputChooseTarget(", start)
actions = controller[start:end]
assert "DEBUG_BATTLE_MENU == TRUE && JOY_NEW(START_BUTTON)" in actions
assert "BtlController_EmitTwoReturnValues(battler, B_COMM_TO_ENGINE, B_ACTION_DEBUG, 0);" in actions
assert "JOY_NEW(START_BUTTON) || (DEBUG_BATTLE_MENU == TRUE && JOY_NEW(SELECT_BUTTON))" in actions
assert "SwapHpBarsWithHpText();" in actions

# In-battle menu entry resolves as a victory, not a player forfeit.
assert '{COMPOUND_STRING("Win Encounter"), LIST_ITEM_INSTANT_WIN}' in debug_menu
assert "listItemId == LIST_ITEM_INSTANT_WIN && JOY_NEW(A_BUTTON)" in debug_menu
assert "BattleDebug_WonBattle();" in debug_menu
assert "gBattleOutcome |= B_OUTCOME_WON;" in battle
assert "DidPlayerForfeitNormalTrainerBattle(void)" in battle
assert "gBattleStruct->gimmick.playerSelect ^= 1;" in controller

assert "python3 test/test_pru_battle_win_encounter.py" in ci
assert "make hns -j2 -O" in ci
print("PRU_ALPHA_BATTLE_DEBUG_PASS: Win Encounter entry exists only in unreachable debug code; disabled in every alpha build")
