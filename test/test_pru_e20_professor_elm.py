"""Oak and Elm must have different front portraits in both E20 difficulties."""

from pathlib import Path
import unittest

from PIL import Image


ROOT = Path(__file__).resolve().parents[1]
PARTIES = (ROOT / "src/data/trainers_hns.party").read_text()


def trainer_block(name):
    return PARTIES.split(f"=== {name} ===", 1)[1].split("\n=== ", 1)[0]


class ProfessorElmE20Tests(unittest.TestCase):
    def test_elm_has_own_front_pic_in_normal_and_master_battles(self):
        for suffix in ("", "_MASTER"):
            elm = trainer_block(f"TRAINER_PRU_E18_18_B{suffix}_HNS")
            oak = trainer_block(f"TRAINER_PRU_E18_18_A{suffix}_HNS")
            self.assertIn("Pic: Professor Elm Pru", elm)
            self.assertIn("Pic: Professor Oak Frlg", oak)

    def test_front_sprite_is_registered_independently_of_oak(self):
        constants = (ROOT / "include/constants/trainers.h").read_text()
        graphics = (ROOT / "src/data/graphics/trainers.h").read_text()
        self.assertIn("TRAINER_PIC_FRONT_PROFESSOR_ELM_PRU", constants)
        self.assertIn('graphics/trainers/front_pics/professor_elm_pru.4bpp.smol', graphics)
        self.assertIn('graphics/trainers/palettes/professor_elm_pru.gbapal', graphics)
        self.assertIn("TRAINER_SPRITE(TRAINER_PIC_FRONT_PROFESSOR_ELM_PRU,", graphics)

    def test_uploaded_elm_sprite_is_gba_indexed(self):
        sprite = ROOT / "graphics/trainers/front_pics/professor_elm_pru.png"
        self.assertTrue(sprite.is_file())
        with Image.open(sprite) as pic:
            self.assertEqual(pic.size, (64, 64))
            self.assertEqual(pic.mode, "P")
            self.assertLessEqual(len(set(pic.getdata())), 16)
            self.assertEqual(pic.info.get("transparency"), 0)


if __name__ == "__main__":
    unittest.main()
