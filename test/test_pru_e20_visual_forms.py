"""E20 uses existing trainer-only special art without increasing the Dex."""

import json
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
ASSIGNMENTS = json.loads((ROOT / "assets/pru_e20/visual_form_assignments.json").read_text())["forms"]
PARTIES = (ROOT / "src/data/trainers_hns.party").read_text()
SPECIES = (ROOT / "include/constants/species.h").read_text()
FORM_DATA = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()


def trainer_block(trainer: str) -> str:
    start = PARTIES.index(f"=== {trainer} ===")
    end = PARTIES.find("\n=== ", start + 5)
    return PARTIES[start:end if end != -1 else None]


class E20VisualFormsTests(unittest.TestCase):
    def test_all_visual_forms_are_already_registered(self):
        self.assertGreaterEqual(len(ASSIGNMENTS), 14)
        for entry in ASSIGNMENTS:
            const = "SPECIES_" + entry["form"].replace(" ", "_").upper()
            with self.subTest(form=entry["form"]):
                self.assertRegex(SPECIES, rf"#define {const}\s+\d+")
                self.assertIn(f"PJR_E4_VISUAL_FORM({const},", FORM_DATA)

    def test_each_special_sprite_belongs_to_one_e20_trainer(self):
        used = {}
        for entry in ASSIGNMENTS:
            previous = used.get(entry["form"])
            with self.subTest(sprite=entry["form"], trainer=entry["trainer_name"]):
                self.assertIsNone(previous, f'{entry["form"]} reused by {previous} and {entry["trainer_name"]}')
            used[entry["form"]] = entry["trainer_name"]

    def test_correct_form_is_in_both_normal_and_master_teams(self):
        for entry in ASSIGNMENTS:
            for difficulty in ("", "_MASTER"):
                trainer = f'TRAINER_{entry["trainer"]}{difficulty}_HNS'
                with self.subTest(trainer=trainer, form=entry["form"]):
                    block = trainer_block(trainer)
                    names = re.findall(r"^([^\n]+) @ [^\n]+$", block, re.M)
                    self.assertEqual(len(names), 3)
                    self.assertIn(entry["form"], names)
                    self.assertNotIn(entry["replace"], names)
                    if "moves" in entry:
                        monster = block.split(f'\n{entry["form"]} @ ', 1)[1].split("\n\n", 1)[0]
                        self.assertEqual(re.findall(r"^- (.+)$", monster, re.M), entry["moves"])
                    if difficulty:
                        self.assertEqual(re.findall(r"^Level: (\d+)$", block, re.M), ["100"] * 3)


if __name__ == "__main__":
    unittest.main()
