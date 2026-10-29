"""E20 credits retain the Relic montage and use a dedicated ending flow."""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src/credits_hns.c").read_text()


class E20CreditsTests(unittest.TestCase):
    def test_e20_credits_replace_stock_bike_and_rival_scenes_with_relic_montage(self):
        switch = SOURCE.split("static u8 CheckChangeScene(u8 page, u8 taskId)\n{", 1)[1].split("#define tDelay", 1)[0]
        self.assertRegex(switch, re.compile(
            r"if \(gPruElite20CreditsActive\)\s*\{\s*"
            r"if \(page == PAGE_INTERVAL \* 1\)\s*\{\s*"
            r"gTasks\[taskId\]\.tNextMode = MODE_SHOW_MONS;"
        ))

    def test_e20_opening_uses_flying_ho_oh_without_the_bicycle_characters(self):
        opening = SOURCE.split("static bool8 LoadBikeScene(u8 scene, u8 taskId)\n{", 1)[1].split("static void ResetCreditsTasks", 1)[0]
        self.assertIn("if (gPruElite20CreditsActive)", opening)
        self.assertIn("SpriteCB_CreditsRelicHoOh", opening)
        self.assertIn("CreateIntroMaySprite", opening)

    def test_e20_finish_screen_names_the_game_and_elite_20_champion(self):
        end = SOURCE.split("static void Task_CreditsTheEnd5(u8 taskId)\n{", 1)[1].split("static void Task_CreditsTheEnd6", 1)[0]
        self.assertIn("gPruElite20CreditsActive", end)
        self.assertIn("POKEMON RELICS ULTIMATE", SOURCE)
        self.assertIn("ELITE 20 CHAMPION", SOURCE)
        self.assertIn("DrawTheEnd", end)

    def test_curated_credits_montage_keeps_faeranium_and_excludes_retired_species(self):
        roster = SOURCE.split("static const u16 sPruCreditsSpecies[]", 1)[1].split("};", 1)[0]
        self.assertIn("SPECIES_FAERANIUM", roster)
        self.assertNotIn("SPECIES_SUDOWARDEN", roster)
        self.assertIn("gPruElite20CreditsActive ? E20_INTRO_PAGE_COUNT", SOURCE)


if __name__ == "__main__":
    unittest.main()
