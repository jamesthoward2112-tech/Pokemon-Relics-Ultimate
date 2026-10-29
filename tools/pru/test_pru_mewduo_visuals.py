#!/usr/bin/env python3
"""Regression tests for Mewduo's overworld, icon, and caught indicator."""

from collections import Counter
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]


def pixels(image):
    # The hosted runner's apt-installed Pillow may predate this newer API.
    getter = getattr(image, "get_flattened_data", None)
    return getter() if getter else image.getdata()


class MewduoVisualTests(unittest.TestCase):
    def test_level_90_spawn_and_late_level_moves(self):
        text = (ROOT / "src/data/pokemon/level_up_learnsets/pru.h").read_text()
        block = text.split("sMewsionLevelUpLearnset[]", 1)[1].split("LEVEL_UP_END", 1)[0]
        entries = [(int(level), move) for level, move in re.findall(
            r"LEVEL_UP_MOVE\(\s*(\d+),\s*(MOVE_[A-Z_0-9]+)\s*\)", block
        )]
        level_90 = [move for level, move in entries if level <= 90][-4:]
        self.assertEqual(level_90, [
            "MOVE_NIGHT_DAZE", "MOVE_RECOVER", "MOVE_SUPER_GLITCH", "MOVE_PERMAFROST"
        ])
        self.assertIn((95, "MOVE_PSYSTRIKE"), entries)
        self.assertIn((100, "MOVE_DARK_MATTER"), entries)

    def test_overworld_preserves_six_original_mewtwo_frames(self):
        source = Image.open(ROOT / "assets/mewduo_mewtwo_base_overworld.png")
        recoloured = Image.open(ROOT / "graphics/pokemon/mewsion/overworld.png")
        self.assertEqual(source.size, (192, 32))
        self.assertEqual(recoloured.size, source.size)
        self.assertEqual(recoloured.mode, "P")
        self.assertLess(max(pixels(recoloured)), 16)

        source_mask = bytes(pixel != 0 for pixel in pixels(source))
        result_mask = bytes(pixel != 0 for pixel in pixels(recoloured))
        self.assertTrue(result_mask == source_mask, "Overworld silhouette differs from Mewtwo")

        frames = [recoloured.crop((32 * i, 0, 32 * (i + 1), 32)) for i in range(6)]
        self.assertGreaterEqual(len({frame.tobytes() for frame in frames}), 3)

    def test_overworld_has_red_tail_and_uses_exact_palette(self):
        sprite = Image.open(ROOT / "graphics/pokemon/mewsion/overworld.png")
        self.assertEqual(sprite.mode, "P")
        colour_lines = (ROOT / "graphics/pokemon/mewsion/normal.pal").read_text().splitlines()[3:19]
        expected_palette = [tuple(map(int, line.split())) for line in colour_lines]
        actual_palette = sprite.getpalette()
        self.assertEqual(
            [tuple(actual_palette[3 * i:3 * i + 3]) for i in range(16)],
            expected_palette,
        )
        # The tail's red shades are shared across every walking direction.
        for index in range(6):
            frame = sprite.crop((32 * index, 0, 32 * (index + 1), 32))
            count = Counter(pixels(frame))
            self.assertGreater(sum(count[c] for c in (6, 7, 8, 9)), 3)

    def test_party_icon_uses_its_own_exact_red_and_grey_palette(self):
        source = Image.open(ROOT / "graphics/pokemon/mewsion/icon.png")
        if source.mode == "P":
            # The canonical CI normalises RGBA donor icons to 4bpp *before*
            # invoking regression tests. Index zero is transparent there.
            source_palette = source.getpalette()
            used = sorted(set(pixels(source)) - {0})
            colours = [(0, 0, 0)] + [tuple(source_palette[3 * i:3 * i + 3]) for i in used]
        else:
            counts = Counter(px[:3] for px in pixels(source.convert("RGBA")) if px[3] >= 128)
            colours = [(0, 0, 0)] + [rgb for rgb, _ in counts.most_common(15)]
        expected = [tuple(c // 8 for c in rgb) for rgb in colours]

        c_source = (ROOT / "src/pokemon_icon.c").read_text()
        palette = re.search(r"sPRUMewduoIconPalette\[16\]\s*=\s*\{([^}]+)\}", c_source, re.S)
        self.assertIsNotNone(palette)
        actual = [tuple(map(int, components)) for components in re.findall(
            r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", palette.group(1)
        )]
        self.assertEqual(actual[:len(expected)], expected)
        self.assertIn("{ sPRUMewduoIconPalette, POKE_ICON_BASE_PAL_TAG + 14 }", c_source)
        self.assertRegex(c_source, r"if \(species == SPECIES_MEWSION\)\s*return 14;")

    def test_first_mewduo_encounter_does_not_inherit_mewtwo_caught_icon(self):
        test_source = r'''
#include "pru_mewduo_caught_icon.h"
int main(void)
{
    for (int flags = 0; flags < 8; flags++)
    {
        int isMewduo = !!(flags & 1);
        int parentCaught = !!(flags & 2);
        int mewduoCaught = !!(flags & 4);
        int expected = isMewduo ? mewduoCaught : parentCaught;
        if (PruHasCaughtSpeciesForBattleIcon(isMewduo, parentCaught, mewduoCaught) != expected)
            return flags + 1;
    }
    return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="pru_mewduo_icon_") as tmp:
            binary = Path(tmp) / "caught_icon"
            subprocess.run(
                ["cc", "-std=c11", "-Wall", "-Werror", "-I", str(ROOT / "src"),
                 "-x", "c", "-", "-o", str(binary)],
                input=test_source, text=True, capture_output=True, check=True,
            )
            subprocess.run([str(binary)], check=True, capture_output=True)

        battle_ui = (ROOT / "src/battle_interface.c").read_text()
        self.assertIn("PruHasCaughtSpeciesForBattleIcon", battle_ui)


if __name__ == "__main__":
    unittest.main()
