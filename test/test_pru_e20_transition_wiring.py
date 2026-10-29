"""Source contract for the fourteen new, dedicated Elite 20 duo intros."""

from pathlib import Path
import unittest

from tools.pru.compose_e20_banners import PAIRS


ROOT = Path(__file__).resolve().parents[1]
TRANSITION = (ROOT / "src/battle_transition.c").read_text()
SETUP = (ROOT / "src/battle_setup.c").read_text()
IDS = (ROOT / "include/battle_transition.h").read_text()


class E20TransitionWiringTests(unittest.TestCase):
    def test_all_fourteen_pair_specific_transitions_are_wired(self):
        for stem in PAIRS:
            token = f"B_TRANSITION_PRU_E20_{stem.upper()}"
            with self.subTest(stem=stem):
                self.assertIn(token, IDS)
                self.assertIn(token, SETUP)
                self.assertIn(token, TRANSITION)
                self.assertIn(f'prl/{stem}.4bpp', TRANSITION)
                self.assertIn(f'prl/{stem}.bin', TRANSITION)
                self.assertIn(f'prl/{stem}.gbapal', TRANSITION)

    def test_normal_and_master_pairs_trigger_the_same_intro(self):
        for index in list(range(1, 14)):
            for master in ("", "_MASTER"):
                with self.subTest(round=index, master=master):
                    first = f"TRAINER_PRU_E18_{index:02}_A{master}_HNS"
                    second = f"TRAINER_PRU_E18_{index:02}_B{master}_HNS"
                    self.assertRegex(SETUP, rf"{first}[^\n]*{second}")
        for master in ("", "_MASTER"):
            self.assertRegex(SETUP, rf"TRAINER_PRU_E20_JASMINE{master}_HNS[^\n]*TRAINER_PRU_E20_CLAIR{master}_HNS")

    def test_legacy_entrances_remain_registered(self):
        for stem in ("JESSIE_JAMES", "EEVEE_TWINS", "RED_BLUE", "OAK_ELM", "STEVEN_MAY", "SILVER_GIOVANNI"):
            self.assertIn(f"B_TRANSITION_{stem}", IDS)
            self.assertIn(f"B_TRANSITION_{stem}", SETUP)

    def test_original_rocket_and_eevee_twins_use_their_existing_prl_art_symbols(self):
        # Existing assets are sPRL_*; the new sPRU_* macro cannot resolve them.
        for stem, task in (("jessie_james", "Task_PRL_JessieJames"), ("eevee_twins", "Task_PRL_EeveeTwins")):
            with self.subTest(stem=stem):
                self.assertIn(f"PRL_DUO_ART({task}, {stem})", TRANSITION)
                self.assertIn(f"sPRL_{stem}_Tiles[]", TRANSITION)


if __name__ == "__main__":
    unittest.main()
