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

if __name__ == "__main__":
    unittest.main()
