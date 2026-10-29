"""Elite 20's one-time six-Master-Ball prize must be safe for old saves."""

from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[1]
SCRIPTS = (ROOT / "data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc").read_text()
FLAGS = (ROOT / "include/constants/flags_hns.h").read_text()
ELM = (ROOT / "data/maps/NewBarkTown_hns/scripts.inc").read_text()


def section(label):
    match = re.search(rf"(?m)^{re.escape(label)}::\n(.*?)(?=^\S[^\n]*::|\Z)", SCRIPTS, re.S | re.M)
    if match is None:
        raise AssertionError(f"missing script label: {label}")
    return match.group(1)


class Elite20FinaleRewardTests(unittest.TestCase):
    def test_claim_flag_uses_new_permanent_save_bit(self):
        self.assertRegex(FLAGS, r"#define FLAG_PRU_E20_REWARD_CLAIMED\s+0x947\b")

    def test_full_gauntlet_sets_existing_clear_flag_then_claims_prize(self):
        script = section("PRU_Elite18_Gauntlet")
        self.assertLess(script.index("setflag FLAG_PRU_ELITE18_CLEARED"), script.index("call PRU_Elite20_ClaimRewards"))

    def test_old_completed_save_can_claim_without_replaying_all_twenty(self):
        steward = section("PRU_Elite18_Steward")
        self.assertIn("goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite20_Steward_Cleared", steward)
        cleared = section("PRU_Elite20_Steward_Cleared")
        self.assertIn("goto_if_unset FLAG_PRU_E20_REWARD_CLAIMED, PRU_Elite20_Steward_PendingReward", cleared)
        self.assertIn("call PRU_Elite20_ClaimRewards", section("PRU_Elite20_Steward_PendingReward"))

    def test_exact_rewards_checked_before_giving_and_flag_set_after(self):
        script = section("PRU_Elite20_ClaimRewards")
        ordered = [
            "checkitemspace ITEM_MASTER_BALL, 6",
            "checkitemspace ITEM_ANCIENT_STONE, 5",
            "giveitem ITEM_MASTER_BALL, 6",
            "giveitem ITEM_ANCIENT_STONE, 5",
            "setflag FLAG_PRU_E20_REWARD_CLAIMED",
        ]
        positions = [script.index(token) for token in ordered]
        self.assertEqual(positions, sorted(positions))
        self.assertGreaterEqual(script.count("goto_if_eq VAR_RESULT, FALSE, PRU_Elite20_BagFull"), 2)
        self.assertNotIn("setflag FLAG_PRU_E20_REWARD_CLAIMED", section("PRU_Elite20_BagFull"))

    def test_professors_tease_six_relics_and_oak_at_mt_silver(self):
        self.assertIn("R - E - L - I - C - S", SCRIPTS)
        self.assertIn("MT. SILVER", SCRIPTS)
        self.assertIn("ELITE 20", ELM)
        self.assertNotIn("ELITE 18 in SAFFRON", ELM)


if __name__ == "__main__":
    unittest.main()
