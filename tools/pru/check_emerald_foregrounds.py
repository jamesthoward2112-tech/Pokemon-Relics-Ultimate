#!/usr/bin/env python3
"""PRU BG1-only Emerald battle foreground regression (no artwork regeneration)."""
from pathlib import Path
import struct

root = Path("graphics/battle_environment")
assets = ("tall_grass", "long_grass", "water", "pond_water", "sand", "rock", "cave", "underwater")
for name in assets:
    d = root / name
    assert (d / "anim_tiles.png").is_file(), name
    raw = (d / "anim_map.bin").read_bytes()
    assert len(raw) == 2048, name
    tiles = struct.unpack("<1024H", raw)
    assert any(t & 0x3FF for t in tiles), name
    assert all((t >> 12) in (0, 4) for t in tiles), name
    # Emerald anim foregrounds use palette 4; the Crystal background uses BG2-4.
    assert 4 in {t >> 12 for t in tiles}, name
    # At BG1 scroll Y=160 every nontransparent tile is off the top edge.
    occupied_rows = [idx // 32 for idx, tile in enumerate(tiles) if tile & 0x3FF]
    assert occupied_rows and max(occupied_rows) < 20, name

bg = Path("src/battle_bg.c").read_text()
intro = Path("src/battle_intro.c").read_text()
header = Path("include/battle_bg.h").read_text()
workflow = Path(".github/workflows/pru-clean-build.yml").read_text()
for required in (
    "IsPruEmeraldEnvironment", "LoadPruEmeraldBattleForeground",
    "EndPruEmeraldBattleForeground", "BGCNT_CHARBASE(1)",
    "BGCNT_SCREENBASE(28)", "BGCNT_TXT256x512",
    "BG_PLTT_ID(8)", "BG_SCREEN_ADDR(29)",
    "gBattleEnvironmentInfo[environment].entry.tileset",
    "gBattleEnvironmentInfo[environment].entry.tilemap",
    "IsPruCrystalBattleBgActive()", "BATTLE_TYPE_LEGENDARY",
):
    assert required in bg, required
assert "bool8 IsPruEmeraldForegroundActive(void);" in header
assert "EndPruEmeraldBattleForeground();" in intro
static = intro.split("static void BattleIntroCrystalStatic(u8 taskId)\n{", 1)[1].split("\nstatic void BattleIntroNoSlide", 1)[0]
# The foreground stops at the bottom of the screen (never sweeps up
# through the scenery), remains briefly visible, then blends back to BG3.
assert "gBattle_BG1_Y += 8;" in static
assert "gBattle_BG1_Y < -48" in static
assert "gBattle_BG1_Y = (u16)-48;" in static
assert "gBattle_BG1_Y = 160;" not in static
assert "gTasks[taskId].data[2] = 8;" in static
assert "BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG3" in static
assert "BLDALPHA_BLEND(16, 0)" in static
assert "16 - gTasks[taskId].data[2]" in static
assert static.index("BLDALPHA_BLEND(16, 0)") < static.index("gBattle_BG1_Y += 8;") < static.index("EndPruEmeraldBattleForeground();")
assert "gBattle_BG3_X" not in static and "gBattle_BG3_Y" not in static
assert "gScanlineEffectRegBuffers" not in static
assert "gIntroSlideFlags &= ~1;" in static
assert "BattleIntroSlideEnd(taskId);" in static
assert "python3 tools/pru/check_crystal_battle_backgrounds.py" in workflow
assert "python3 tools/pru/check_emerald_foregrounds.py" in workflow
print("PRU_EMERALD_FOREGROUNDS_PASS: authentic Emerald art rises to lower screen and crossfades, Crystal BG3 static")
