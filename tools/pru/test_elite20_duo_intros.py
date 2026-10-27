"""The two newly approved cinematic banners are native, widescreen GBA art."""
import tempfile
import unittest
from pathlib import Path

from PIL import Image

from tools.pru.convert_elite20_duo_intros import build_entrances


class Elite20DuoEntrances(unittest.TestCase):
    def test_creates_two_paired_gba_assets_without_squashing_banner(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            sources = [root / "hoenn.png", root / "rocket.png"]
            for color, source in zip(((180, 30, 50), (90, 56, 25)), sources):
                Image.new("RGB", (1500, 500), color).save(source)
            output = root / "result"
            sizes = build_entrances(sources[0], sources[1], output)
            self.assertEqual(set(sizes), {"steven_may", "silver_giovanni"})
            for name in sizes:
                self.assertLessEqual(sizes[name], 512)
                for extension, length in (("4bpp", 16384), ("bin", 2048), ("gbapal", 32)):
                    self.assertEqual((output / f"{name}.{extension}").stat().st_size, length)
                with Image.open(output / f"{name}_preview.png") as preview:
                    self.assertEqual(preview.size, (240, 160))
                    self.assertEqual(preview.getpixel((120, 20)), (0, 0, 0))
                    self.assertNotEqual(preview.getpixel((120, 80)), (0, 0, 0))


if __name__ == "__main__":
    unittest.main()
