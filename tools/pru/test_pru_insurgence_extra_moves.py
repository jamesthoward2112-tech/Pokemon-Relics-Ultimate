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
        all_ids = re.findall(r"\bMOVE_[A-Z_]+\b(?=,)", tail)
        # Preserve all established Insurgence/PRU move IDs; additional
        # signatures may only be appended after DARK_MATTER.
        self.assertEqual(
            all_ids[:10],
            ["MOVE_SHOCKWAVE_FIST", "MOVE_FAULTLINE", "MOVE_WRAITH_CRY",
             "MOVE_METAL_BARRAGE", "MOVE_MINDWAVE", "MOVE_DARK_NOVA",
             "MOVE_ACHILLES_HEEL", "MOVE_PERMAFROST",
             "MOVE_WILDFIRE", "MOVE_DARK_MATTER"])
        self.assertEqual(all_ids[10:], ["MOVE_RELIC_GAZE"])

    def test_relic_eye_is_battle_ready_and_uses_original_statue(self):
        import json
        species = read("src/data/pokemon/species_info/gen_2_families.h")
        eye = species.split("[SPECIES_UNOWN_I] =", 1)[1].split("[SPECIES_UNOWN_J]", 1)[0]
        for field in (".baseHP        = 120", ".baseAttack    = 30",
                      ".baseDefense   = 10", ".baseSpeed     = 210",
                      ".baseSpAttack  = 220", ".baseSpDefense = 10",
                      "ABILITY_RELIC_EYE", "gMonFrontPic_UnownEye",
                      "gMonIcon_UnownEye"):
            self.assertIn(field, eye)
        self.assertIn("MOVE_RELIC_GAZE", read("src/data/pokemon/level_up_learnsets/pjr.h"))
        self.assertIn(".power = 105", move_block("RELIC_GAZE"))
        battle = read("src/battle_util.c")
        self.assertIn("ctx->abilityDef == ABILITY_RELIC_EYE", battle)
        self.assertIn("calc = (calc * 120) / 100", battle)
        layout = json.loads(read("data/maps/RuinsOfAlph_B1F_hns/map.json"))
        rune = [e for e in layout["object_events"]
                if e["graphics_id"] == "OBJ_EVENT_GFX_EYE_OF_ALPH_HNS"]
        self.assertEqual(len(rune), 1)
        self.assertEqual((rune[0]["x"], rune[0]["y"]), (16, 10))
        # Overlay an existing statue tile: no second freestanding statue.
        original_statue = [e for e in layout["bg_events"]
                           if (e["x"], e["y"]) == (16, 10)]
        self.assertEqual(len(original_statue), 1)
        self.assertEqual(original_statue[0]["script"], "RuinsOfAlph_B1F_hns_RelicUnownI")

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
