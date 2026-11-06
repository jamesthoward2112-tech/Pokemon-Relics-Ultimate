"""Regression tests for the final PRU named-trainer and legend-item cleanup."""

from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]


def read(path):
    return (ROOT / path).read_text(encoding="utf-8")


class FinalPolishTests(unittest.TestCase):
    def test_elite20_display_uses_names_without_classes(self):
        source = read("src/battle_message.c")
        trainer_data = read("src/data/trainers_hns.party")
        self.assertIn("IsPRUFinaleTrainer(trainerId)", source)
        self.assertIn("return sText_PRUNameOnlyClass;", source)
        self.assertIn("if (classLength != 0)", source)
        # Both battle tiers, plus follow-up Elite 20 opponents, keep their
        # gameplay trainer class while showing only each individual's name.
        e18 = re.findall(
            r"(?m)^=== TRAINER_PRU_E18_[A-Z0-9_]+ ===\n"
            r"Name: ([^\n]+)\nClass: ([^\n]+)",
            trainer_data,
        )
        self.assertEqual(len(e18), 72)
        self.assertTrue(all(name and klass for name, klass in e18))
        self.assertIn(("Red", "Pkmn Trainer 1 Hns"), e18)
        self.assertIn(("Bruno", "Elite Four Hns"), e18)
        self.assertIn(("Steevee", "Pkmn Trainer 1 Hns"), e18)
        self.assertIn(("Neevee", "Pkmn Trainer 1 Hns"), e18)
        self.assertIn(("Prof. Oak", "Pkmn Trainer 1 Hns"), e18)
        self.assertIn(("Prof. Elm", "Pkmn Trainer 1 Hns"), e18)

    def test_obsolete_items_cannot_gate_new_finale(self):
        trail = read("data/maps/BellchimeTrail_hns/scripts.inc")
        summit = read("data/maps/MtSilver_SummitDay_hns/scripts.inc")
        rocket = read("data/maps/TinTower_9F_hns/scripts.inc")
        goldenrod = read("data/maps/GoldenrodCity_RadioTower_5F_hns/scripts.inc")
        pewter = read("data/maps/PewterCity_hns/scripts.inc")

        for flag in (
            "FLAG_PRU_ELITE18_CLEARED",
            "FLAG_PJR_RELIC_RAIKOU", "FLAG_PJR_RELIC_ENTEI",
            "FLAG_PJR_RELIC_LUGIA", "FLAG_PJR_RELIC_UNOWN_I",
            "FLAG_PJR_RELIC_CELEBI", "FLAG_PJR_RELIC_SUICUNE",
            "FLAG_PJR_RELIC_ALPHORACLE",
        ):
            self.assertIn("goto_if_unset " + flag, trail)
        self.assertNotIn("ITEM_ANCIENT_RAINBOW_CREST", trail)
        self.assertNotIn("FLAG_PJR_GOT_RAINBOW_CREST", trail)
        self.assertNotIn("giveitem ITEM_ANCIENT_RAINBOW_CREST", summit)
        self.assertNotIn("FLAG_PJR_GOT_RAINBOW_CREST", rocket)
        for script in (goldenrod, pewter):
            self.assertNotIn("giveitem ITEM_RAINBOW_WING", script)
            self.assertNotIn("giveitem ITEM_SILVER_WING", script)

        # Never change allocated numeric item IDs; already-existing saves
        # can still store these obsolete items without a shifted layout.
        items = read("include/constants/items.h")
        for name in ("ITEM_RAINBOW_WING", "ITEM_SILVER_WING",
                     "ITEM_ANCIENT_RAINBOW_CREST", "ITEM_GS_BALL",
                     "ITEM_CLEAR_BELL", "ITEM_ANCIENT_STONE"):
            self.assertIn(name, items)


if __name__ == "__main__":
    unittest.main()
