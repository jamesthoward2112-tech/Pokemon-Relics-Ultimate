#!/usr/bin/env python3
"""CI-only mGBA Alph exit traversal.

Rebuilds a throwaway ROM that starts a new game one step below the EXISTING
Alph B1F ladder. It never alters the published ROM or the user's save. mGBA
receives a real Up keypress. Visual evidence distinguishes the pale basement
from the brown rocky outside entrance after the warp.
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
                        str(ROOT), "run:2200", "snap:pru-alph-before",
                        "press:UP:60", "run:240", "snap:pru-alph-after"],
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
    interior_brightness = ImageStat.Stat(before.convert("L")).mean[0]
    print("mGBA B1F interior luminance:", round(interior_brightness, 2))
    print("mGBA B1F green fraction BEFORE UP:", round(baseline, 4))
    print("mGBA outside green fraction AFTER UP:", round(destination, 4))
    print("mGBA core framebuffer variation:", before_variation, after_variation)
    assert before_variation > 5 and after_variation > 5, (
        "Black mGBA core pixels; inspect captured frames")
    # Do not misclassify the blue intro scene as the Alph basement!
    # The actual confirmed interior frame is pale stone (~169 luminance)
    # with only ~6% green; the previous false-positive began at 66.
    assert interior_brightness > 140 and 0.015 < baseline < 0.13, (
        "Not yet inside Alph B1F; test never reached the starting map")
    # Confirm actual exit scenery; grass is not present near this entrance.
    # Outside Alph is a BROWN rocky entrance, not grassy green.
    # A verified screenshot at the actual exit is ~75 luminance, while the
    # interior is ~169. Reject fades using variation AND textured brown ground.
    exterior_luminance = ImageStat.Stat(after.convert("L")).mean[0]
    brown_fraction = sum(1 for r, g, b in after.getdata()
                         if 45 <= r <= 125 and 30 <= g <= 115
                         and 25 <= b <= 105 and r >= g + 3 and g >= b
                         ) / (after.width * after.height)
    print("mGBA rocky Ruins outside luminance:", round(exterior_luminance, 2))
    print("mGBA rocky outside brown fraction:", round(brown_fraction, 4))
    assert 45 < exterior_luminance < 120, "No textured exterior frame after warp"
    assert interior_brightness - exterior_luminance > 45 and brown_fraction > 0.35, (
        "Warp to the actual Ruins exterior NOT proven")
    print("PASS: verified mGBA B1F interior BEFORE and rocky exterior AFTER Up")

    assert ROM.read_bytes() == CANONICAL.read_bytes(), "Canonical ROM changed!"
    CANONICAL.unlink(missing_ok=True)
    TEST_ROM.unlink(missing_ok=True)

if __name__ == "__main__":
    main()
