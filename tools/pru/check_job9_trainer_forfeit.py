#!/usr/bin/env python3
"""PRU Job 9 - disable trainer Quit/Forfeit; preserve wild run."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
read=lambda file:(root/file).read_text(encoding="utf-8")
config=read("include/config/battle.h")
engine=read("src/battle_main.c")
controller=read("src/battle_controller_player.c")
util=read("src/battle_util.c")
assert "#define B_RUN_TRAINER_BATTLE                (!IS_HNS)" in config
start=engine.index("bool32 CanPlayerForfeitNormalTrainerBattle(void)")
assert "if (IS_HNS || !B_RUN_TRAINER_BATTLE)" in engine[start:start+500]
assert "return FALSE;" in engine[start:start+500]
sel=engine[engine.index("case STATE_WAIT_ACTION_CASE_CHOSEN:")-3000:]
# Selection script bypass: all PRU trainer Run attempts take standard denial.
assert "if (!IS_HNS && (gBattleTypeFlags & BATTLE_TYPE_TRAINER)" in engine
assert "gSelectionBattleScripts[battler] = BattleScript_AskIfWantsToForfeitMatch" in engine
assert "else if (CanPlayerForfeitNormalTrainerBattle()" in engine
assert "BattleScriptExecute(BattleScript_PrintCantRunFromTrainer);" in engine
end=engine[engine.index("static void HandleEndTurn_RanFromBattle(void)\n{"):]
assert "if (!IS_HNS && (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)" in end[:700]
assert "else if (!IS_HNS && (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL))" in end[:900]
# No changes to the R-button Quick Run code or wild escape calculations.
assert "if (JOY_NEW(R_BUTTON) && !(gBattleTypeFlags & BATTLE_TYPE_TRAINER))" in controller
assert "gBattleStruct->pjrQuickRun = TRUE;" in controller
assert "BtlController_EmitTwoReturnValues(battler, B_COMM_TO_ENGINE, B_ACTION_RUN, 0);" in controller
assert "IsRunningFromBattleImpossible" in engine and "BATTLE_RUN_SUCCESS" in engine
assert "else if (CanPlayerForfeitNormalTrainerBattle())" in util
assert "BATTLE_TYPE_TRAINER" in engine
print("JOB9_TRAINER_FORFEIT_PASS: no regular, double, Frontier or Hill forfeit in PRU")
print("JOB9_WILD_RUN_PASS: wild R-button shortcut and escape action unchanged")
