"""Regression checks for the post-Dojo hint and Giovanni's fossil finale."""

import unittest
from hashlib import sha256
from pathlib import Path
from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
TRE_SOURCE_DIGESTS = {
    "aerodactyl": "7170396edfe298c9084789f7af23edb231cdd32f0d84f8f5ba0d770b5d84668d",
    "kabutops": "c9d0f63ddeaa41db6aa3b2fcab95c54ddd6e70db8489574d876c9782814317c2",
    "rhyperior": "233b804d988d188dcea9f75a8f12aa4da4a87748581925170ee0e9099c2d47b6",
}


class FinalBadgeSceneTests(unittest.TestCase):
    def test_blaine_points_to_eighth_badge_without_naming_city(self):
        source = (ROOT / "data/maps/SaffronCity_FightingDojoVIP_hns/scripts.inc").read_text()
        finale = source.split("SaffronCity_FightingDojoVIP_Text_PRUHeistNextBlaine:", 1)[1].split("\n\n", 1)[0]
        self.assertIn("EIGHTH BADGE", finale)
        self.assertIn("PALLET TOWN", finale)
        self.assertNotIn("VIRIDIAN", finale)
        self.assertIn("msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNextBlaine", source)

    def test_giovanni_exits_visibly_after_dialogue(self):
        source = (ROOT / "data/maps/ViridianCity_Gym_hns/scripts.inc").read_text()
        finale = source.split("ViridianCity_Gym_EventScript_PRUMewtwoAlreadyCaught::", 1)[1].split("ViridianCity_Gym_EventScript_PRUHeistNotReady::", 1)[0]
        self.assertRegex(finale, r"closemessage\s+fadescreenswapbuffers FADE_TO_WHITE")
        self.assertRegex(finale, r"removeobject 3\s+fadescreenswapbuffers FADE_FROM_WHITE")

    def test_exact_tre_fossil_sprite_assets_are_battle_ready(self):
        artwork = ROOT / "graphics/pokemon/giovanni_relic"
        for name in ("aerodactyl", "kabutops", "rhyperior"):
            with self.subTest(name=name):
                sprite = artwork / f"{name}_front.png"
                palette = artwork / f"{name}_normal.pal"
                self.assertTrue(sprite.is_file())
                self.assertTrue(palette.is_file())
                original = artwork / f"{name}_source_front.png"
                self.assertEqual(sha256(original.read_bytes()).hexdigest(), TRE_SOURCE_DIGESTS[name])
                with Image.open(sprite) as image:
                    self.assertEqual(image.size, (64, 64))
                    self.assertEqual(image.mode, "P")
                    self.assertLessEqual(len(image.getcolors(4096) or []), 16)

    def test_giovanni_only_battle_sprite_selection(self):
        loader = (ROOT / "src/battle_gfx_sfx_util.c").read_text()
        sprites = (ROOT / "src/graphics.c").read_text()
        self.assertIn("GetPruGiovanniRelicSprite", loader)
        self.assertIn("TRAINER_PRU_HEIST_GIOVANNI_HNS", loader)
        for name in ("Aerodactyl", "Kabutops", "Rhyperior"):
            self.assertIn(f"gPruGiovanni{name}FrontGfx", sprites)
            self.assertIn(f"gPruGiovanni{name}Palette", sprites)


if __name__ == "__main__":
    unittest.main()
