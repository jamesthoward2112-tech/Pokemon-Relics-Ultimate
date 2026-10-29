#!/usr/bin/env python3
"""Regression checks for Insurgence-exclusive TM imports into PRU."""

import pathlib
import re
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[2]


def read(relative):
    return (ROOT / relative).read_text()


def move_block(name):
    source = read("src/data/moves_info.h")
    match = re.search(rf"\[MOVE_{name}\]\s*=\s*\{{(.*?)\n    \}},", source, re.S)
    if not match:
        raise AssertionError(f"{name} missing from active move data")
    return match.group(1)


class InsurgenceExtraMoveTests(unittest.TestCase):
    def test_new_ids_append_after_dark_nova_without_shifting_existing_ids(self):
        source = read("include/constants/moves.h")
        tail = source.split("MOVE_KABOOM,", 1)[1].split("MOVES_COUNT,", 1)[0]
        self.assertEqual(
            re.findall(r"\bMOVE_[A-Z_]+\b(?=,)", tail),
            ["MOVE_DARK_NOVA", "MOVE_ACHILLES_HEEL", "MOVE_PERMAFROST",
             "MOVE_WILDFIRE", "MOVE_DARK_MATTER"])

    def test_dark_matter_matches_insurgence_and_recharges(self):
        block = move_block("DARK_MATTER")
        for value in (".power = 150", ".type = TYPE_DARK", ".accuracy = 90",
                      ".pp = 5", ".category = DAMAGE_CATEGORY_SPECIAL",
                      ".moveEffect = MOVE_EFFECT_RECHARGE", ".self = TRUE"):
            self.assertIn(value, block)

    def test_achilles_heel_always_has_two_times_effectiveness_except_immunity(self):
        block = move_block("ACHILLES_HEEL")
        for value in (".power = 45", ".type = TYPE_NORMAL", ".accuracy = 100",
                      ".pp = 15", ".category = DAMAGE_CATEGORY_PHYSICAL"):
            self.assertIn(value, block)
        source = read("src/battle_util.c")
        self.assertIn("ctx->move == MOVE_ACHILLES_HEEL", source)
        self.assertRegex(source, re.compile(
            r"ctx->move == MOVE_ACHILLES_HEEL.*?"
            r"modifier\s*>\s*UQ_4_12\(0\.0\).*?"
            r"modifier\s*=\s*UQ_4_12\(2\.0\)", re.S))

    def test_shadow_mewtwo_learns_all_four_extra_tms(self):
        teachables = read("src/data/pokemon/teachable_learnsets/pru.h")
        block = teachables.split("sInsurgenceShadowMewtwoTeachableLearnset[] =", 1)[1].split("MOVE_UNAVAILABLE", 1)[0]
        for name in ("ACHILLES_HEEL", "PERMAFROST", "WILDFIRE", "DARK_MATTER"):
            self.assertIn(f"MOVE_{name}", block)

    def test_all_four_moves_are_selectable_from_indigo_tutor(self):
        source = read("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
        for name in ("AchillesHeel", "Permafrost", "Wildfire", "DarkMatter"):
            self.assertIn(f"IndigoPlateau_EventScript_TutorTeach_{name}", source)
            self.assertIn(f"IndigoPlateau_Text_TutorMove_{name}", source)

    def test_permafrost_has_independent_five_layer_hazard_and_frostbite_switchin(self):
        block = move_block("PERMAFROST")
        self.assertIn(".effect = EFFECT_PRU_PERMAFROST", block)
        self.assertIn("HAZARDS_PERMAFROST", read("include/constants/battle.h"))
        self.assertIn("permafrostAmount", read("include/battle.h"))
        setter = read("src/battle_script_commands.c")
        self.assertIn("gCurrentMove == MOVE_PERMAFROST", setter)
        self.assertIn("gSideTimers[targetSide].permafrostAmount < 5", setter)
        starter = read("src/battle_util.c").split("static bool32 SetStartingHazardStatus", 1)[1].split("if (effect)", 1)[0]
        self.assertIn("case HAZARDS_PERMAFROST:", starter)
        switch = read("src/battle_switch_in.c")
        self.assertIn("case HAZARDS_PERMAFROST:", switch)
        self.assertIn("MOVE_EFFECT_FROSTBITE", switch)
        self.assertIn("RandomPercentage", switch)
        self.assertIn("STATUS1_FROSTBITE", switch)

    def test_wildfire_uses_grass_trigger_for_reserve_fire_weak_burn(self):
        block = move_block("WILDFIRE")
        self.assertIn(".argument = { .nonVolatileStatus = MOVE_EFFECT_BURN }", block)
        source = read("src/battle_script_commands.c")
        self.assertIn("gCurrentMove == MOVE_WILDFIRE", source)
        self.assertIn("TYPE_GRASS", source)
        self.assertIn("STATUS1_BURN", source)


if __name__ == "__main__":
    unittest.main()
