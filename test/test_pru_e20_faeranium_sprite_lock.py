"""Keep Faeranium's approved Mega Meganium art across E20 and later builds."""

from pathlib import Path
import re
import unittest

from PIL import Image

from tools.pru.sync_prl_authoritative_sprites import PRU_VISUAL_OVERRIDES


ROOT = Path(__file__).resolve().parents[1]
HEADER = (ROOT / "src/data/graphics/pjr.h").read_text()
APPROVED = "graphics/pokemon/meganium/mega"


class FaeraniumSpriteLockTests(unittest.TestCase):
    def test_all_five_faeranium_sprite_inputs_use_locked_mega_meganium(self):
        for symbol, asset in (
            ("FrontPic", "front.4bpp.smol"),
            ("BackPic", "back.4bpp.smol"),
            ("Palette", "normal.gbapal"),
            ("ShinyPalette", "shiny.gbapal"),
            ("Icon", "icon.4bpp"),
        ):
            with self.subTest(symbol=symbol):
                matched = re.search(
                    rf'gMon{symbol}_Faeranium\[\]\s*=\s*INCBIN_U\d+\("([^"]+)"\)',
                    HEADER,
                )
                self.assertIsNotNone(matched, f"Missing Faeranium {symbol} resource")
                self.assertEqual(matched.group(1), f"{APPROVED}/{asset}")

    def test_pinned_prl_import_must_not_replace_the_user_approved_art(self):
        self.assertIn("faeranium", PRU_VISUAL_OVERRIDES)

    def test_approved_art_is_gba_sized_and_has_matching_palettes(self):
        directory = ROOT / APPROVED
        for file, size in (("front.png", (64, 64)), ("back.png", (64, 64)), ("icon.png", (32, 64))):
            with self.subTest(file=file), Image.open(directory / file) as image:
                self.assertEqual(image.size, size)
                self.assertEqual(image.mode, "P")
                self.assertLessEqual(len(set(image.getdata())), 16)
        for file in ("normal.pal", "shiny.pal"):
            self.assertTrue((directory / file).is_file(), file)


if __name__ == "__main__":
    unittest.main()
