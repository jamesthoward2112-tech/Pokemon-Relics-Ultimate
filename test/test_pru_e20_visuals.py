"""Source-level regression checks for PRU's paired E20 trainer portraits."""
from pathlib import Path
import re
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
PARTY = (ROOT / "src/data/trainers_hns.party").read_text(encoding="utf-8")
TRAINER_PICS = (ROOT / "include/constants/trainers.h").read_text(encoding="utf-8")
GRAPHICS = (ROOT / "src/data/graphics/trainers.h").read_text(encoding="utf-8")


def trainer_pic(trainer_id: str) -> str:
    marker = f"=== {trainer_id} ==="
    start = PARTY.find(marker)
    if start == -1:
        raise AssertionError(f"Missing trainer {trainer_id}")
    end = PARTY.find("\n=== ", start + len(marker))
    block = PARTY[start:end if end != -1 else None]
    match = re.search(r"^Pic: (.+)$", block, re.MULTILINE)
    if match is None:
        raise AssertionError(f"Missing Pic for {trainer_id}")
    return match.group(1)


class E20PortraitTests(unittest.TestCase):
    def test_paired_pics_only_show_once(self):
        for master in ("", "_MASTER"):
            self.assertEqual(trainer_pic(f"TRAINER_PRU_E18_14_A{master}_HNS"), "Twins Hns")
            self.assertEqual(trainer_pic(f"TRAINER_PRU_E18_14_B{master}_HNS"), "Pru Invisible")
            self.assertEqual(trainer_pic(f"TRAINER_PRU_E18_15_A{master}_HNS"), "James Hns")
            self.assertEqual(trainer_pic(f"TRAINER_PRU_E18_15_B{master}_HNS"), "Pru Invisible")

    def test_invisible_sprite_is_registered(self):
        self.assertIn("TRAINER_PIC_FRONT_PRU_INVISIBLE", TRAINER_PICS)
        self.assertIn("gTrainerFrontPic_PruInvisible", GRAPHICS)
        self.assertIn("gTrainerPalette_PruInvisible", GRAPHICS)

    def test_transparent_partner_is_64px_indexed_png(self):
        data = (ROOT / "graphics/trainers/front_pics/pru_invisible.png").read_bytes()
        self.assertTrue(data.startswith(b"\x89PNG\r\n\x1a\n"))
        self.assertEqual(struct.unpack(">II", data[16:24]), (64, 64))
        self.assertEqual(data[25], 3)  # PNG indexed-colour mode
        self.assertIn(b"tRNS", data)


if __name__ == "__main__":
    unittest.main()
