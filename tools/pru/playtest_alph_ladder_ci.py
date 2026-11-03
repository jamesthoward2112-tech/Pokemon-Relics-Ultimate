#!/usr/bin/env python3
"""mGBA test of real Ruins of Alph ladder transitions using EWRAM probes.

Builds a throwaway ROM that starts outside the B1F entrance. A temporary
probe records the engine's loaded map group/number and player coordinates each
time WarpIntoMap runs. The harness enters B1F, walks off and back onto its
original ladder warp to exit, then re-enters. Temporary source edits and the
canonical ROM are restored even when the test fails.
"""
import re
import shutil
import struct
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TITLE = ROOT / "src/title_screen.c"
NEWGAME = ROOT / "src/new_game.c"
OVERWORLD = ROOT / "src/overworld.c"
ROM = ROOT / "pokehns.gba"
CANONICAL = ROOT / "pru-canonical-before-playtest.gba"
TEST_ROM = ROOT / "pru-alph-traversal-only.gba"
LOG = ROOT / "pru-mgba-ladder.log"


def main():
    shutil.copy2(ROM, CANONICAL)
    original = {p: p.read_text() for p in (TITLE, NEWGAME, OVERWORLD)}
    try:
        title = original[TITLE]
        include = '#include "battle.h"'
        target = "#if IS_HNS\n    CB2_InitPruTitleScreen();\n    return;"
        assert title.count(include) == 1 and title.count(target) == 1
        TITLE.write_text(title.replace(include, include + '\n#include "overworld.h"', 1)
                         .replace(target, "#if IS_HNS\n    CB2_NewGame();\n    return;", 1))

        newgame = original[NEWGAME]
        spawn = "SetWarpDestination(MAP_GROUP(MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F_HNS), MAP_NUM(MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F_HNS), 1, 0, 0);"
        assert newgame.count(spawn) == 1
        outside_spawn = "SetWarpDestination(MAP_GROUP(MAP_RUINS_OF_ALPH_OUTSIDE_HNS), MAP_NUM(MAP_RUINS_OF_ALPH_OUTSIDE_HNS), WARP_ID_NONE, 21, 22);"
        NEWGAME.write_text(newgame.replace(spawn, outside_spawn, 1))

        overworld = original[OVERWORLD]
        function = """void WarpIntoMap(void)
{
    ApplyCurrentWarp();
    LoadCurrentMapData();
    SetPlayerCoordsFromWarp();
}"""
        probe = """EWRAM_DATA volatile u16 gPruAlphMapProbe[4] = {0};

void WarpIntoMap(void)
{
    ApplyCurrentWarp();
    LoadCurrentMapData();
    SetPlayerCoordsFromWarp();
    gPruAlphMapProbe[0] = (u8)gSaveBlock1Ptr->location.mapGroup;
    gPruAlphMapProbe[1] = (u8)gSaveBlock1Ptr->location.mapNum;
    gPruAlphMapProbe[2] = (u16)gSaveBlock1Ptr->pos.x;
    gPruAlphMapProbe[3] = (u16)gSaveBlock1Ptr->pos.y;
}"""
        assert overworld.count(function) == 1
        OVERWORLD.write_text(overworld.replace(function, probe, 1))

        with (ROOT / "pru-mgba-test-build.log").open("w") as log:
            subprocess.run(["make", "hns", "-j2", "-O"], cwd=ROOT,
                           stdout=log, stderr=subprocess.STDOUT,
                           timeout=720, check=True)
        shutil.copy2(ROM, TEST_ROM)
        symbols = subprocess.check_output(["arm-none-eabi-nm", "-n", "pokehns.elf"],
                                          cwd=ROOT, text=True)
        match = re.search(r"^([0-9a-fA-F]+) [bBdD] gPruAlphMapProbe$", symbols, re.M)
        assert match, "mGBA probe symbol missing from temporary ROM ELF"
        probe_addr = int(match.group(1), 16)
    finally:
        for path, content in original.items():
            path.write_text(content)
        shutil.copy2(CANONICAL, ROM)

    # The source table is generated during make hns and supplies the real map IDs.
    maps_header = ROOT / "include/constants/map_groups.h"
    maps_text = maps_header.read_text()

    def map_id(name):
        found = re.search(rf"^\s*{re.escape(name)}\s*=\s*\((\d+)\s*\|\s*\((\d+)\s*<<\s*8\)\)", maps_text, re.M)
        if not found:
            # mapjson may emit the equivalent folded integer for unused maps.
            found = re.search(rf"^#define\s+{re.escape(name)}\s+(\d+)\s*$", maps_text, re.M)
            assert found, f"map constant {name} missing"
            return int(found.group(1)) >> 8, int(found.group(1)) & 0xFF
        return int(found.group(2)), int(found.group(1))

    outside = map_id("MAP_RUINS_OF_ALPH_OUTSIDE_HNS")
    interior = map_id("MAP_RUINS_OF_ALPH_B1F_HNS")
    if not (0x02000000 <= probe_addr < 0x02040000):
        raise AssertionError(f"probe is not in EWRAM: {probe_addr:#x}")
    probe_offset = probe_addr - 0x02000000

    debugger = Path("/tmp/pru-gba-rom-debugger")
    if debugger.exists():
        shutil.rmtree(debugger)
    subprocess.run(["git", "clone", "-q", "--depth=1",
                    "https://github.com/JohnnySun/gba-rom-debugger.git",
                    str(debugger)], check=True, timeout=60)
    with LOG.open("w") as log:
        subprocess.run(["make", "bin/gba-dump", "MGBA_PREFIX=/usr",
                        "LIBPNG_PREFIX=/usr"], cwd=debugger, check=True,
                       stdout=log, stderr=subprocess.STDOUT, timeout=60)
        subprocess.run([str(debugger / "bin/gba-dump"), str(TEST_ROM), str(ROOT),
                        "run:2200", "dump:alph-outside-start",
                        "press:UP:1", "run:50", "dump:alph-entered-b1f",
                        "press:DOWN:1", "run:50", "press:UP:1", "run:50",
                        "dump:alph-exited-outside",
                        "press:DOWN:1", "run:50", "press:UP:1", "run:50",
                        "dump:alph-reentered-b1f"],
                       check=True, cwd=ROOT, stdout=log, stderr=log, timeout=120)

    def observation(name):
        raw = (ROOT / f"{name}.ewram.bin").read_bytes()
        return struct.unpack_from("<4H", raw, probe_offset)

    expected = {
        "alph-outside-start": (*outside, 21, 22),
        "alph-entered-b1f": (*interior, 15, 16),
        "alph-exited-outside": (*outside, 21, 21),
        "alph-reentered-b1f": (*interior, 15, 16),
    }
    for name, wanted in expected.items():
        got = observation(name)
        print(f"mGBA {name}: map=({got[0]},{got[1]}) pos=({got[2]},{got[3]})")
        assert got == wanted, f"{name}: expected map/position {wanted}, got {got}"

    print("PASS: actual mGBA map loads verify outside -> B1F -> outside -> B1F")
    for path in ROOT.glob("alph-*.ewram.bin"):
        path.unlink(missing_ok=True)
    TEST_ROM.unlink(missing_ok=True)
    CANONICAL.unlink(missing_ok=True)
