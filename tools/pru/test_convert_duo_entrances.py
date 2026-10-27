"""Regression coverage for the GBA-ready 240x160 duo entrances."""
import struct
import unittest
from PIL import Image
from tools.pru.convert_duo_entrances import convert_image, reconstruct_preview

class DuoEntranceTests(unittest.TestCase):
    def test_opaque_native_assets_and_round_trip(self):
        art = Image.new("RGB", (1536, 1024), (192, 44, 25))
        result = convert_image(art)
        self.assertEqual(result.preview.size, (240, 160))
        self.assertEqual([len(result.tiles), len(result.tilemap), len(result.palette)], [16384, 2048, 32])
        self.assertLessEqual(result.tile_count, 512)
        self.assertEqual(result.preview.tobytes(), reconstruct_preview(result).tobytes())
        self.assertTrue(all((b & 15) and (b >> 4) for b in result.tiles))
        self.assertEqual(struct.unpack("<H", result.palette[:2])[0], 0)
        self.assertTrue(all((entry >> 12) == 13 and (entry & 1023) < 512
                            for entry in struct.unpack("<1024H", result.tilemap)))

    def test_extra_wide_banner_preserves_aspect_with_letterbox(self):
        banner = Image.new("RGB", (1500, 500), (240, 55, 30))
        result = convert_image(banner, preserve_aspect=True)
        # Native widescreen art must not be squashed to 224x144. Its original
        # 3:1 composition fits as a centered banner inside the GBA window.
        self.assertEqual(result.preview.size, (240, 160))
        self.assertEqual(result.preview.getpixel((120, 20)), (0, 0, 0))
        self.assertNotEqual(result.preview.getpixel((120, 80)), (0, 0, 0))
        self.assertEqual(len(result.tiles), 16384)
        self.assertLessEqual(result.tile_count, 512)

if __name__ == "__main__":
    unittest.main()
