#!/usr/bin/env python3
"""PRU source regression: do not allow quitting local trainer battles.

Run manually from the repository root (no ROM build required):
    python3 test/test_pru_trainer_battle_no_quit.py
This source audit is NOT a substitute for mGBA gameplay testing.
"""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def source(path):
    return (ROOT / path).read_text(encoding="utf-8")

def require(value, message):
    if not value:
        raise AssertionError(message)

controller = source("src/battle_controller_player.c")
main = source("src/battle_main.c")
script = source("data/battle_scripts_1.s")
header = source("include/battle_scripts.h")

# The A-button handler refuses the Run tile for local trainer battles,
# without issuing B_ACTION_RUN or completing the controller action.
action_start = controller.index("else if (JOY_NEW(A_BUTTON))", controller.index("static void HandleInputChooseAction"))
action_end = controller.index("else if (JOY_NEW(DPAD_LEFT))", action_start)
action = controller[action_start:action_end]
deny_at = action.index("gActionSelectionCursor[battler] == 3")
emit_at = action.index("BtlController_EmitTwoReturnValues", deny_at)
require("gBattleTypeFlags & BATTLE_TYPE_TRAINER" in action[deny_at:emit_at],
        "Run option must be blocked in trainer battles")
require("BATTLE_TYPE_LINK" in action[deny_at:emit_at]
        and "BATTLE_TYPE_RECORDED_LINK" in action[deny_at:emit_at],
        "Preserve link/recorded-link escape handling")
require("PlaySE(SE_BOO);" in action[deny_at:emit_at]
        and "return;" in action[deny_at:emit_at],
        "Rejected Run must stay in the action-selection controller")
require("BtlController_Complete" not in action[deny_at:action.index("#endif", deny_at)],
        "Rejected Run must not complete a controller action")

# The R shortcut remains exclusively non-trainer; wild battles still submit
# their original RUN action, and the D-pad/fight/item/switch handling remains.
shortcut = controller[controller.index("// PJR/PHR shortcut:"):
                      controller.index("else if (JOY_NEW(A_BUTTON))", controller.index("// PJR/PHR shortcut:"))]
require("JOY_NEW(R_BUTTON) && !(gBattleTypeFlags & BATTLE_TYPE_TRAINER)" in shortcut,
        "Wild quick-run shortcut was changed")
for selection in ("B_ACTION_USE_MOVE", "B_ACTION_USE_ITEM", "B_ACTION_SWITCH", "B_ACTION_RUN"):
    require(selection in action, f"Battle action entry missing: {selection}")

# A late/local synthetic RUN command cannot reach normal or Frontier forfeits.
engine_start = main.index("// PRU: reject an unexpected trainer RUN action")
engine_end = main.index("if (gBattleTypeFlags & BATTLE_TYPE_TRAINER", engine_start)
engine = main[engine_start:engine_end]
require("gBattleResources->bufferB[battler][1] == B_ACTION_RUN" in engine
        and "BattleScript_PRU_CantQuitTrainer" in engine,
        "Engine fallback must intercept B_ACTION_RUN for PRU trainers")
require("BATTLE_TYPE_LINK" in engine and "BATTLE_TYPE_RECORDED_LINK" in engine,
        "The fallback must leave link battles alone")
require("STATE_SELECTION_SCRIPT" in engine
        and "STATE_BEFORE_ACTION_CHOSEN" in engine
        and "return;" in engine,
        "Engine fallback must return to action selection, not end the battle")

defn = main[main.index("bool32 CanPlayerForfeitNormalTrainerBattle(void)"):
            main.index("bool32 DidPlayerForfeitNormalTrainerBattle(void)")]
require("#if IS_HNS" in defn and "return FALSE;" in defn.split("#else", 1)[0],
        "PRU normal trainer battle forfeiting was not disabled")
require("B_RUN_TRAINER_BATTLE" in defn.split("#else", 1)[1],
        "Other ROM variants must preserve original trainer-forfeit logic")

require("extern const u8 BattleScript_PRU_CantQuitTrainer[];" in header,
        "New battle selection script symbol must be declared")
safe_script = script.split("BattleScript_PRU_CantQuitTrainer::", 1)[1].split("#endif", 1)[0]
require("printselectionstring STRINGID_NORUNNINGFROMTRAINERS" in safe_script
        and "endselectionscript" in safe_script,
        "Fallback must print existing can't-run text and end as a SELECTION script")

print("PASS: trainer RUN blocked without controller completion")
print("PASS: secondary engine guard returns to action selection")
print("PASS: original wild, Safari, link and non-HNS code paths preserved")
print("NOTE: source-only; trainer doubles, defeat and victory need emulator tests.")
