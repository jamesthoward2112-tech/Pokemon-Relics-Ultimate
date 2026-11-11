"""Keep old PRL paired introductions while registering the new pairs."""
import struct
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

class DuoTransitionIntegration(unittest.TestCase):
    def test_transition_ids_and_tasks(self):
        header = (ROOT / "include/battle_transition.h").read_text()
        source = (ROOT / "src/battle_transition.c").read_text()
        for name in ("JESSIE_JAMES", "EEVEE_TWINS", "RED_BLUE", "OAK_ELM"):
            self.assertTrue(f"B_TRANSITION_{name}," in header)
            self.assertTrue(f"[B_TRANSITION_{name}]" in source)

    def test_assets_and_red_blue_pair_route(self):
        folder = ROOT / "graphics/battle_transitions/prl"
        source = (ROOT / "src/battle_transition.c").read_text()
        for name in ("red_blue", "oak_elm"):
            for ext, size in (("4bpp", 16384), ("bin", 2048), ("gbapal", 32)):
                self.assertEqual((folder / f"{name}.{ext}").stat().st_size, size)
                self.assertIn(f"prl/{name}.{ext}", source)
            self.assertTrue((folder / f"{name}_preview.png").is_file())
        battle_setup = (ROOT / "src/battle_setup.c").read_text()
        self.assertIn("return B_TRANSITION_RED_BLUE;", battle_setup)

if __name__ == "__main__":
    unittest.main()
