"""Checks the thematic PRU species choices in both Elite 20 difficulties."""

import json
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
ASSIGNMENTS = json.loads((ROOT / "assets/pru_e20/custom_team_assignments.json").read_text())["assignments"]
PARTIES = (ROOT / "src/data/trainers_hns.party").read_text()
SPECIES = (ROOT / "include/constants/species.h").read_text()


def team(trainer: str) -> str:
    marker = f"=== {trainer} ==="
    start = PARTIES.find(marker)
    if start < 0:
        raise AssertionError(f"Missing {trainer}")
    end = PARTIES.find("\n=== ", start + len(marker))
    return PARTIES[start:end if end != -1 else None]


class E20CustomRosterTests(unittest.TestCase):
    def test_every_custom_species_exists_with_front_sprite(self):
        self.assertEqual(len(ASSIGNMENTS), 16)
        for assignment in ASSIGNMENTS:
            species = assignment["species"]
            with self.subTest(species=species):
                token = f"SPECIES_{species.upper()}"
                self.assertRegex(SPECIES, rf"#define {token}\s+\d+")
                sprites = list((ROOT / "graphics/pokemon").glob(f"**/{species.lower()}/front.png"))
                self.assertTrue(sprites, f"Missing existing GBA sprite for {species}")

    def test_both_difficulties_have_the_selected_custom_species(self):
        for assignment in ASSIGNMENTS:
            for suffix in ("", "_MASTER"):
                trainer = f'TRAINER_{assignment["trainer"]}{suffix}_HNS'
                with self.subTest(trainer=trainer):
                    block = team(trainer)
                    names = re.findall(r"^([^\n]+) @ [^\n]+$", block, re.M)
                    self.assertEqual(len(names), 3)
                    self.assertIn(assignment["species"], names)
                    self.assertNotIn(assignment["replace"], names)
                    monster = block.split(f'\n{assignment["species"]} @ ', 1)[1].split("\n\n", 1)[0]
                    self.assertEqual(re.findall(r"^- (.+)$", monster, re.M), assignment["moves"])
                    if suffix:
                        self.assertEqual(re.findall(r"^Level: (\d+)$", block, re.M), ["100"] * 3)


if __name__ == "__main__":
    unittest.main()
