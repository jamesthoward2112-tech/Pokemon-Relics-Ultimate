#!/usr/bin/env python3
"""Validate the original Crystal Redux entry artwork and its PRU integration."""
from pathlib import Path
from struct import unpack
import re


def decompress_gba_lz77(data):
    assert data[0] == 0x10
    size = int.from_bytes(data[1:4], "little")
    output = bytearray()
    cursor = 4
    while len(output) < size:
        flags = data[cursor]
        cursor += 1
        for bit in range(7, -1, -1):
            if len(output) >= size:
                break
            if flags & (1 << bit):
                pair = int.from_bytes(data[cursor:cursor + 2], "big")
                cursor += 2
                length = (pair >> 12) + 3
                distance = (pair & 0xFFF) + 1
                for _ in range(length):
                    output.append(output[-distance])
            else:
                output.append(data[cursor])
                cursor += 1
    return bytes(output)


# Independently inspected original donor art: all other entries are blank or
# flat single-tile placeholders and must never cover the settled BG3 scene.
expected_animated = {0, 1, 3, 4, 5, 7, 14, 15, 19, 22, 23, 24, 25, 36}
animated = set()
base = Path("graphics/battle_environment/crystal_redux")
for index in range(38):
    path = base / f"{index:02d}"
    tiles = decompress_gba_lz77((path / "entry_tiles.4bpp.lz").read_bytes())
    tilemap = decompress_gba_lz77((path / "entry_tilemap.bin.lz").read_bytes())
    assert len(tilemap) == 32 * 14 * 2
    entries = unpack("<448H", tilemap)
    used = {entry & 0x3FF for entry in entries}
    if len(used) > 1:
        animated.add(index)
        assert max(used) < len(tiles) // 32, index
        assert {entry >> 12 for entry in entries if entry & 0x3FF} <= {2, 3, 4}, index
assert animated == expected_animated, (animated, expected_animated)

table = Path("src/data/pru_crystal_bg_table.h").read_text()
bg = Path("src/battle_bg.c").read_text()
intro = Path("src/battle_intro.c").read_text()
header = Path("include/battle_bg.h").read_text()
workflow = Path(".github/workflows/pru-clean-build.yml").read_text()

assert "entryTiles" in table and "entryTilemap" in table
assert "static void LoadPruCrystalBattleEntry(void)" in bg
assert "sPruCrystalBattleBgs[entryIndex].entryTiles" in bg
assert "sPruCrystalBattleBgs[entryIndex].entryTilemap" in bg
assert "BGCNT_CHARBASE(1)" in bg and "BGCNT_SCREENBASE(28)" in bg
assert "BG_CHAR_ADDR(1)" in bg and "BG_SCREEN_ADDR(28)" in bg
assert "IsPruCrystalBattleEntryActive" in bg and "EndPruCrystalBattleEntry" in bg
assert "bool8 IsPruCrystalBattleEntryActive(void);" in header
assert "void EndPruCrystalBattleEntry(void);" in header
assert "LoadPruCrystalBattleEntry();" in bg
assert "BATTLE_TYPE_LEGENDARY" in bg
mask = bg.split("static const bool8 sPruCrystalEntryHasArt[38] =", 1)[1].split("};", 1)[0]
enabled = {int(index) for index in re.findall(r"\[(\d+)\] = TRUE", mask)}
assert enabled == expected_animated, (enabled, expected_animated)

# The donor art must be used without replacing the still BG3 scene, and BG1
# must leave before its VRAM is cleared or reused by later battle animations.
start = intro.index("static void BattleIntroCrystalStatic(u8 taskId)\n{")
end = intro.index("\nstatic void BattleIntroNoSlide", start)
entry_intro = intro[start:end]
assert "IsPruCrystalBattleEntryActive()" in entry_intro
assert "EndPruCrystalBattleEntry();" in entry_intro
assert "gBattle_BG3_X" not in entry_intro and "gBattle_BG3_Y" not in entry_intro
assert "gScanlineEffectRegBuffers" not in entry_intro
assert "gBattle_BG1_Y" in entry_intro
assert "gBattle_BG1_Y -= 2;" in entry_intro, "entry art must descend, never fly upwards"
assert "gBattle_BG1_Y +=" not in entry_intro
assert entry_intro.index("BLDALPHA_BLEND(16, 0)") < entry_intro.index("EndPruCrystalBattleEntry();")
assert "python3 tools/pru/check_crystal_entry_transitions.py" in workflow
assert "python3 tools/pru/check_emerald_foregrounds.py" not in workflow
print("PRU_CRYSTAL_ENTRIES_PASS: 14 real donor entries, 24 static placeholders, BG3 stationary")
