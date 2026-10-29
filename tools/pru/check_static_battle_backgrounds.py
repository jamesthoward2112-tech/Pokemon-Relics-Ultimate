#!/usr/bin/env python3
"""The 55 Rhythm scenes must render completely without entry overlays."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
bg = (ROOT / "src/battle_bg.c").read_text()
intro = (ROOT / "src/battle_intro.c").read_text()
header = (ROOT / "include/battle_bg.h").read_text()

draw = bg.split("void DrawBattleEntryBackground(void)\n{", 1)[1].split(
    "bool8 LoadChosenBattleElement", 1)[0]
assert "if (IsPruCrystalBattleBgActive())" in draw
assert "LoadPruCrystalBattleEntry" not in bg
assert "sPruCrystalEntryActive" not in bg
assert "IsPruCrystalBattleEntryActive" not in header
assert "EndPruCrystalBattleEntry" not in header

static = intro.split("static void BattleIntroCrystalStatic(u8 taskId)\n{", 1)[1].split(
    "static void BattleIntroNoSlide", 1)[0]
assert "ScanlineEffect_Stop();" in static
assert "BattleIntroSlideEnd(taskId);" in static
for forbidden in (
    "gBattle_BG1_Y -=", "gBattle_BG1_X +=", "BLDALPHA_BLEND(",
    "EndPruCrystalBattleEntry", "IsPruCrystalBattleEntryActive", "gTasks[taskId].tState",
):
    assert forbidden not in static, f"Unexpected entry animation: {forbidden}"

print("PASS: Rhythm backdrops are static from the first frame; no extra BG1 layer")
