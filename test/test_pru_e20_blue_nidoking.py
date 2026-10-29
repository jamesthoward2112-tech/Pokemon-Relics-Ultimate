"""Blue owns a TRE Nidoking-X portrait; Giovanni exclusively owns Nidogod."""

import json
from pathlib import Path
import unittest

from PIL import Image


ROOT = Path(__file__).resolve().parents[1]


class E20BlueNidokingTests(unittest.TestCase):
    def test_blue_has_unique_tre_nidoking_form_in_both_rosters(self):
        data = (ROOT / "src/data/trainers_hns.party").read_text()
        for suffix in ("", "_MASTER"):
            key = f"TRAINER_PRU_E18_17_B{suffix}_HNS"
            blue = data.split(f"=== {key} ===", 1)[1].split("\n=== ", 1)[0]
            self.assertIn("\nNidoking X Blue @ Sitrus Berry", blue)
            self.assertNotIn("\nNidogod Jj @ ", blue)
        roster = json.loads((ROOT / "assets/pru_e20/visual_form_assignments.json").read_text())["forms"]
        blue = [x for x in roster if x["trainer_name"] == "Blue"]
        self.assertEqual(len(blue), 1)
        self.assertEqual(blue[0]["form"], "Nidoking X Blue")
        self.assertEqual(blue[0]["trainer"], "PRU_E18_17_B")

    def test_trainer_only_id_preserves_all_existing_species_and_egg(self):
        header = (ROOT / "include/constants/species.h").read_text()
        self.assertIn("#define SPECIES_EGG                                     (SPECIES_MEWSION + 1)", header)
        self.assertRegex(header, r"#define SPECIES_NIDOKING_X_BLUE\s+1644\b")
        self.assertIn("#define NUM_SPECIES (SPECIES_NIDOKING_X_BLUE + 1)", header)
        info = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
        self.assertIn("PJR_E4_VISUAL_FORM(SPECIES_NIDOKING_X_BLUE,", info)
        graphics = (ROOT / "src/data/graphics/pjr.h").read_text()
        self.assertIn("gMonFrontPic_NidokingXBlue", graphics)

    def test_actual_tre_x_front_sprite_is_indexed_gba_art(self):
        path = ROOT / "graphics/pokemon/nidoking/tre_x_blue/front.png"
        self.assertTrue(path.is_file())
        with Image.open(path) as sprite:
            self.assertEqual(sprite.size, (64, 64))
            self.assertEqual(sprite.mode, "P")
            self.assertLessEqual(len(set(sprite.getdata())), 16)
            self.assertEqual(sprite.info.get("transparency"), 0)


if __name__ == "__main__":
    unittest.main()
