"""Lock Torkaldera to the 8 Oct PRL Pokédex Tortemple sprite trio."""
import hashlib
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EXPECTED = {
    "front.png": "21f7b9839373c94cb714732f4c99bcf8e64fe23e4e40d9a5509c66b056701a51",
    "back.png": "940bce8596028aed3b9d8d0c0452985d1e69e38cb8ebaa18ab78b8975f0fee1d",
    "icon.png": "b544be0c27a79af1860749e895c7a87da7c371ccfcab5b63588854c6249f3fe8",
}

class LockedTorkalderaArtTests(unittest.TestCase):
    def test_original_approved_art_not_replaced(self):
        folder = ROOT / "graphics/pokemon/torkaldera"
        for name, expected in EXPECTED.items():
            with self.subTest(name=name):
                self.assertEqual(hashlib.sha256((folder/name).read_bytes()).hexdigest(), expected)

    def test_palettes_follow_locked_front_art(self):
        p = ROOT / "graphics/pokemon/torkaldera/normal.pal"
        vals = p.read_text().splitlines()
        self.assertEqual(vals[:3], ["JASC-PAL","0100","16"])
        self.assertEqual(vals[3], "147 203 154")
        self.assertEqual(len(vals), 19)

if __name__ == "__main__":
    unittest.main()
