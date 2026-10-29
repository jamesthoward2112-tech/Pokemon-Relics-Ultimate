"""Regression checks for native GBA E20 duo battle-intro banners."""

import unittest
from pathlib import Path

from PIL import Image

from tools.pru.compose_e20_banners import PAIRS, build_banner


ROOT = Path(__file__).resolve().parents[1]


class E20BannerTests(unittest.TestCase):
    def test_oak_elm_relic_professor_banner_has_a_reproducible_gba_preview(self):
        base = ROOT / "graphics/battle_transitions/prl/oak_elm"
        self.assertEqual(base.with_suffix(".4bpp").stat().st_size, 16384)
        self.assertEqual(base.with_suffix(".bin").stat().st_size, 2048)
        self.assertEqual(base.with_suffix(".gbapal").stat().st_size, 32)
        with Image.open(base.parent / "oak_elm_preview.png") as art:
            self.assertEqual(art.size, (240, 160))
            self.assertNotEqual(art.getpixel((60, 30)), art.getpixel((190, 30)))

    def test_every_new_duo_banner_is_distinct_native_gba_asset(self):
        self.assertEqual(len(PAIRS), 14)
        for stem in PAIRS:
            with self.subTest(pair=stem):
                asset = build_banner(stem)
                self.assertEqual(asset.preview.size, (240, 160))
                self.assertEqual(len(asset.tiles), 16384)
                self.assertEqual(len(asset.tilemap), 2048)
                self.assertEqual(len(asset.palette), 32)
                self.assertLessEqual(asset.tile_count, 512)
                pixels = asset.preview.get_flattened_data() if hasattr(asset.preview, "get_flattened_data") else asset.preview.getdata()
                self.assertGreater(len(set(pixels)), 6)


if __name__ == "__main__":
    unittest.main()
