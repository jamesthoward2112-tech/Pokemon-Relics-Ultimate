#!/usr/bin/env python3
"""Game-asset contracts for a4d393129e-based Mewduo, never the old tutor branch."""

import hashlib
import json
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
STABLE_MEWTWO_PNG_SHA256 = "161cbe14d199ae0fa453c4a98c466b3f9802925bf043c4f6259a0bfa01138d0a"


def jasc_colours(path):
    lines = path.read_text().splitlines()
    assert lines[:3] == ["JASC-PAL", "0100", "16"]
    return [tuple(map(int, line.split())) for line in lines[3:19]]


class StableBaseMewduoTests(unittest.TestCase):
    def test_all_nine_indigo_tutors_and_pc_party_eligibility_stay_on_a4d_contract(self):
        for check in ("check_indigo_support_row.py", "check_pru_tutor_party_gate.py"):
            result = subprocess.run(
                ["python3", str(ROOT / "tools/pru" / check)],
                capture_output=True, text=True,
            )
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_mewduo_reuses_exact_stable_mewtwo_overworld_tiles_with_red_palette(self):
        mewtwo_image = ROOT / "graphics/pokemon/mewtwo/overworld.png"
        self.assertEqual(hashlib.sha256(mewtwo_image.read_bytes()).hexdigest(), STABLE_MEWTWO_PNG_SHA256)
        sprite = Image.open(mewtwo_image)
        self.assertEqual(sprite.size, (192, 32))
        self.assertEqual(sprite.mode, "P")

        # This is the actual object-event graphics path: not a different PNG
        # whose pixels can look fine in tests yet render differently in game.
        objects = (ROOT / "src/data/graphics/pru_pokemon.h").read_text()
        self.assertRegex(objects, re.compile(
            r'gObjectEventPic_Mewsion\[\].*INCBIN_COMP\("graphics/pokemon/mewtwo/overworld\.4bpp"\)'
        ))
        self.assertIn('INCBIN_U16("graphics/pokemon/mewsion/overworld_normal.gbapal")', objects)
        palette_path = ROOT / "graphics/pokemon/mewsion/overworld_normal.pal"
        self.assertTrue(palette_path.is_file(), "Mewduo must own its red/grey overworld palette")
        colours = jasc_colours(palette_path)
        self.assertEqual(colours[0], jasc_colours(ROOT / "graphics/pokemon/mewtwo/overworld_normal.pal")[0])
        # Purple tail/detail indices must render red, not the old lavender.
        for i in (7, 9, 10):
            red, green, blue = colours[i]
            self.assertGreater(red, green * 1.7, f"palette index {i} must be red")
            self.assertGreater(red, blue * 1.35, f"palette index {i} must be red")

    def test_mewduo_level_90_95_100_moves_are_defined(self):
        text = (ROOT / "src/data/pokemon/level_up_learnsets/pru.h").read_text()
        block = text.split("sMewsionLevelUpLearnset[]", 1)[1].split("LEVEL_UP_END", 1)[0]
        moves = set(re.findall(r"LEVEL_UP_MOVE\((\d+),\s*(MOVE_[A-Z_0-9]+)\)", block))
        self.assertTrue({
            ("90", "MOVE_PERMAFROST"),
            ("95", "MOVE_PSYSTRIKE"),
            ("100", "MOVE_DARK_MATTER"),
        }.issubset(moves))
        species = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()
        self.assertRegex(species, r'\[SPECIES_MEWSION\][\s\S]*?\.speciesName\s*=\s*_\("Mewduo"\)')

    def test_encounter_only_after_both_parent_captures_and_cave_reentry(self):
        events = json.loads((ROOT / "data/maps/CeruleanCave_B2F_hns/map.json").read_text())["object_events"]
        mewduo = [o for o in events if o.get("script") == "CeruleanCave3_EventScript_Mewsion"]
        self.assertEqual(len(mewduo), 1)
        self.assertEqual((mewduo[0]["x"], mewduo[0]["y"]), (8, 14))
        self.assertEqual(mewduo[0]["flag"], "FLAG_TEMP_B")
        source = (ROOT / "src/overworld.c").read_text()
        self.assertIn("PruMewsionAllowed", source)
        self.assertIn("VAR_PRU_MEWDUO_CAPTURE_MARKER", source)
        script = (ROOT / "data/maps/CeruleanCave_B2F_hns/scripts.inc").read_text()
        self.assertIn("setvar VAR_PRU_MEWDUO_CAPTURE_MARKER, 0x4D44", script)

    def test_first_mewduo_encounter_does_not_use_mewtwo_caught_ball(self):
        header = ROOT / "src/pru_mewduo_caught_icon.h"
        self.assertTrue(header.exists(), "Mewduo needs a distinct caught icon source")
        program = '''
#include "pru_mewduo_caught_icon.h"
int main(void) {
    for (int flags = 0; flags < 8; ++flags) {
        int isMewduo = !!(flags & 1);
        int mewtwoCaught = !!(flags & 2);
        int mewduoCaught = !!(flags & 4);
        int want = isMewduo ? mewduoCaught : mewtwoCaught;
        if (PruHasCaughtSpeciesForBattleIcon(isMewduo, mewtwoCaught, mewduoCaught) != want)
            return flags + 1;
    }
    return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="pru_a4d_caught_") as tmp:
            exe = Path(tmp) / "test"
            subprocess.run(["cc", "-std=c11", "-Werror", "-I", str(ROOT / "src"),
                            "-x", "c", "-", "-o", str(exe)],
                           input=program, text=True, check=True, capture_output=True)
            subprocess.run([str(exe)], check=True, capture_output=True)


if __name__ == "__main__":
    unittest.main()
