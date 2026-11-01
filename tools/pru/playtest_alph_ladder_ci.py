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

    env = os.environ.copy()
    env.update({"LIBGL_ALWAYS_SOFTWARE": "1", "QT_OPENGL": "software"})
    with LOG.open("w") as log:
        proc = subprocess.Popen(["mgba-qt", str(TEST_ROM)], cwd=ROOT,
                                env=env, stdout=log, stderr=subprocess.STDOUT)
        try:
            window = None
            for _ in range(20):
                if proc.poll() is not None:
                    raise RuntimeError("mGBA exited before the ladder playtest")
                found = subprocess.run(
                    ["xdotool", "search", "--pid", str(proc.pid)],
                    stdout=subprocess.PIPE, stderr=subprocess.DEVNULL,
                    text=True).stdout.split()
                if found:
                    window = found[-1]
                    break
                time.sleep(0.5)
            assert window, "Could not locate the live mGBA test window"
            time.sleep(12)
            before = screenshot(window, "pru-alph-before.png")
            cmd("xdotool", "windowfocus", window)
            cmd("xdotool", "keydown", "Up")
            time.sleep(4)
            cmd("xdotool", "keyup", "Up")
            time.sleep(4)
            after = screenshot(window, "pru-alph-after.png")
            baseline = green_share(before)
            destination = green_share(after)
            print("mGBA Alph B1F green fraction before:", round(baseline, 4))
            print("mGBA Ruins Outside green fraction after:", round(destination, 4))
            print("mGBA rendered frame std devs:",
                  [round(x, 1) for x in ImageStat.Stat(after).stddev])
            assert max(ImageStat.Stat(after).stddev) > 5, "Blank mGBA framebuffer"
            assert destination > baseline + 0.025 and destination > 0.04, (
                "mGBA did not visibly arrive on the green exterior map; see screenshots")
            print("PASS: mGBA test avatar walked UP from Alph B1F ladder into Ruins Outside")
        finally:
            proc.terminate()
            try:
                proc.wait(timeout=4)
            except subprocess.TimeoutExpired:
                proc.kill()
                proc.wait()
    assert ROM.read_bytes() == CANONICAL.read_bytes(), "Canonical ROM changed!"
    CANONICAL.unlink(missing_ok=True)
    TEST_ROM.unlink(missing_ok=True)

if __name__ == "__main__":
    main()
