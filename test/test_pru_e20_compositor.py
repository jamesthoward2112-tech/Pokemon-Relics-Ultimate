"""Regression checks for native GBA E20 duo battle-intro banners."""

import unittest

from tools.pru.compose_e20_banners import PAIRS, build_banner


class E20BannerTests(unittest.TestCase):
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
                self.assertGreater(len(set(asset.preview.get_flattened_data())), 6)


if __name__ == "__main__":
    unittest.main()
