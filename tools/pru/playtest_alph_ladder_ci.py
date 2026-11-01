#!/usr/bin/env python3
"""CI-only mGBA Alph exit traversal.

Rebuilds a throwaway ROM that starts a new game one step below the EXISTING
Alph B1F ladder. It never alters the published ROM or the user's save. mGBA
receives a real Up keypress. Visual evidence distinguishes the grey basement
from the green overworld after the warp.
"""
import os
import shutil
import subprocess
import time
from pathlib import Path
from PIL import Image, ImageStat

ROOT = Path(__file__).resolve().parents[2]
TITLE = ROOT / "src/title_screen.c"
NEWGAME = ROOT / "src/new_game.c"
ROM = ROOT / "pokehns.gba"
CANONICAL = ROOT / "pru-canonical-before-playtest.gba"
TEST_ROM = ROOT / "pru-alph-traversal-only.gba"
LOG = ROOT / "pru-mgba-ladder.log"

def cmd(*args, timeout=25):
    return subprocess.run(args, cwd=ROOT, text=True, check=True,
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                          timeout=timeout).stdout

def screenshot(window, name):
    cmd("import", "-window", window, str(ROOT / name))
    im = Image.open(ROOT / name).convert("RGB")
    assert im.width >= 240 and im.height >= 160, im.size
    return im

def green_share(im):
    count = sum(1 for r, g, b in im.getdata()
                if g >= 55 and g > r + 18 and g > b + 12)
    return count / (im.width * im.height)

def main():
    shutil.copy2(ROM, CANONICAL)
    original_title = TITLE.read_text()
    original_newgame = NEWGAME.read_text()
    try:
        a = "#include \"battle.h\""
        assert a in original_title
        target = "#if IS_HNS\n    CB2_InitPruTitleScreen();\n    return;"
        assert original_title.count(target) == 1
        TITLE.write_text(
            original_title.replace(a, a + '\n#include "overworld.h"', 1)
                          .replace(target, "#if IS_HNS\n    CB2_NewGame();\n    return;", 1))
        spawn = "SetWarpDestination(MAP_GROUP(MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F_HNS), MAP_NUM(MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F_HNS), 1, 0, 0);"
        assert original_newgame.count(spawn) == 1
        new_spawn = "SetWarpDestination(MAP_GROUP(MAP_RUINS_OF_ALPH_B1F_HNS), MAP_NUM(MAP_RUINS_OF_ALPH_B1F_HNS), WARP_ID_NONE, 15, 17);"
        NEWGAME.write_text(original_newgame.replace(spawn, new_spawn, 1))
        with (ROOT / "pru-mgba-test-build.log").open("w") as log:
            subprocess.run(["make", "hns", "-j2", "-O"], cwd=ROOT,
                           stdout=log, stderr=subprocess.STDOUT,
                           timeout=720, check=True)
        shutil.copy2(ROM, TEST_ROM)
    finally:
        TITLE.write_text(original_title)
        NEWGAME.write_text(original_newgame)
        shutil.copy2(CANONICAL, ROM)

    # Use mGBA's C core directly. Xvfb window captures on GitHub-hosted
    # runners were uniformly black in BOTH Qt and SDL frontends; core PNG
    # screenshots avoid the broken compositor and prove real GBA pixels.
    source = Path("/tmp/pru-gba-rom-debugger")
    subprocess.run(["git", "clone", "-q", "--depth=1",
                    "https://github.com/JohnnySun/gba-rom-debugger.git",
                    str(source)], check=True, timeout=60)
    with LOG.open("w") as log:
        subprocess.run(["make", "bin/gba-walk", "MGBA_PREFIX=/usr",
                        "LIBPNG_PREFIX=/usr"], cwd=source, check=True,
                       stdout=log, stderr=subprocess.STDOUT, timeout=60)
        subprocess.run([str(source / "bin/gba-walk"), str(TEST_ROM),
                        str(ROOT), "run:720", "snap:pru-alph-before",
                        "press:UP:36", "run:180", "snap:pru-alph-after"],
                       check=True, cwd=ROOT, stdout=log,
                       stderr=subprocess.STDOUT, timeout=90)
    before = Image.open(ROOT / "pru-alph-before.png").convert("RGB")
    after = Image.open(ROOT / "pru-alph-after.png").convert("RGB")
    assert before.size == (240, 160) and after.size == (240, 160), (
        before.size, after.size)
    before_variation = max(ImageStat.Stat(before).stddev)
    after_variation = max(ImageStat.Stat(after).stddev)
    baseline = green_share(before)
    destination = green_share(after)
    print("mGBA core Alph B1F green fraction before:", round(baseline, 4))
    print("mGBA core Ruins Outside green fraction after:", round(destination, 4))
    print("mGBA core framebuffer variation:", before_variation, after_variation)
    assert before_variation > 5 and after_variation > 5, (
        "Black mGBA core pixels; inspect captured frames before claiming gameplay")
    assert destination > baseline + 0.025 and destination > 0.04, (
        "Exit was not visibly traversed; inspect core PNG before releasing")
    print("PASS: actual mGBA core moved UP through Ruins B1F exit to outside")

    assert ROM.read_bytes() == CANONICAL.read_bytes(), "Canonical ROM changed!"
    CANONICAL.unlink(missing_ok=True)
    TEST_ROM.unlink(missing_ok=True)

if __name__ == "__main__":
    main()
