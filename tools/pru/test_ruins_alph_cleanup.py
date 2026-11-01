#!/usr/bin/env python3
"""Focused regression checks for the Ruins of Alph / I-Unown visual patch."""

import json
import re
import unittest
from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
MAPS = ROOT / "data/maps"


def read_map(name):
    return json.loads((MAPS / name / "map.json").read_text())


class RuinsOfAlphCleanupTests(unittest.TestCase):
    def test_monolith_is_removed_and_relic_encounter_moves_to_final_statue(self):
        interior = read_map("RuinsOfAlph_B1F_hns")
        objects = interior["object_events"]
        self.assertFalse(any(o["graphics_id"] == "OBJ_EVENT_GFX_ALPHORACLE_MONOLITH_HNS" for o in objects))

        # Keep the I-Unown statue and its exact encounter interaction in place.
        eye = [o for o in objects if o["graphics_id"] == "OBJ_EVENT_GFX_EYE_OF_ALPH_HNS"]
        self.assertEqual(len(eye), 1)
        self.assertEqual((eye[0]["x"], eye[0]["y"]), (16, 10))
        self.assertEqual(eye[0]["script"], "RuinsOfAlph_B1F_hns_RelicUnownI")

        last_statue = [e for e in interior["bg_events"] if e["x"] == 25 and e["y"] == 28]
        self.assertEqual(len(last_statue), 1)
        self.assertEqual(last_statue[0]["script"], "RuinsOfAlph_B1F_hns_RelicAlphoracleOrStatue")

    def test_relic_ladder_is_inside_at_bottom_right_and_keeps_original_route(self):
        interior = read_map("RuinsOfAlph_B1F_hns")
        outside = read_map("RuinsOfAlph_Outside_hns")
        outside_ladders = [o for o in outside["object_events"] if o["graphics_id"] == "OBJ_EVENT_GFX_RELIC_LADDER_HNS"]
        inside_ladders = [o for o in interior["object_events"] if o["graphics_id"] == "OBJ_EVENT_GFX_RELIC_LADDER_HNS"]
        self.assertEqual(outside_ladders, [])
        self.assertEqual(len(inside_ladders), 1)
        self.assertEqual((inside_ladders[0]["x"], inside_ladders[0]["y"]), (26, 28))
        self.assertEqual(inside_ladders[0]["script"], "RuinsOfAlph_Outside_RelicLadder")

        # Preserve the ordinary building entrance and both directions of its warp.
        main_exit = next(w for w in interior["warp_events"] if w["dest_map"] == "MAP_RUINS_OF_ALPH_OUTSIDE_HNS")
        main_entry = next(w for w in outside["warp_events"] if w["dest_map"] == "MAP_RUINS_OF_ALPH_B1F_HNS" and w["dest_warp_id"] == "0")
        self.assertEqual((main_exit["x"], main_exit["y"], main_exit["dest_warp_id"]), (15, 16, "5"))
        self.assertEqual((main_entry["x"], main_entry["y"]), (21, 21))

        scripts = (MAPS / "RuinsOfAlph_B1F_hns/scripts.inc").read_text()
        self.assertIn("warp MAP_RUINS_OF_ALPH_B1F_HNS, 12, 18", (MAPS / "RuinsOfAlph_Outside_hns/scripts.inc").read_text())
        self.assertRegex(scripts, r"RuinsOfAlph_B1F_hns_RelicAlphoracleOrStatue::[\s\S]*?FLAG_PJR_RELIC_RAIKOU[\s\S]*?FLAG_PJR_RELIC_SUICUNE[\s\S]*?goto RuinsOfAlph_B1F_hns_RelicAlphoracle")

    def test_i_unown_icon_uses_mewduo_palette_without_changing_front_or_back_assets(self):
        icon = Image.open(ROOT / "graphics/pokemon/unown_eye/icon.png")
        self.assertEqual(icon.mode, "P")
        self.assertEqual(icon.size, (32, 64))
        self.assertEqual(icon.info.get("transparency"), 0)
        self.assertTrue({1, 2, 3, 4, 5, 6, 7}.issubset(set(icon.get_flattened_data())))

        icon_source = (ROOT / "src/pokemon_icon.c").read_text()
        i_unown_branch = re.search(r"if \(species == SPECIES_UNOWN_I\)\s*return 15;", icon_source)
        mewduo_branch = re.search(r"if \(species == SPECIES_MEWSION\)\s*return 15;", icon_source)
        self.assertIsNotNone(i_unown_branch)
        self.assertIsNotNone(mewduo_branch)

        species_source = (ROOT / "src/data/pokemon/species_info/gen_2_families.h").read_text()
        self.assertRegex(species_source, r"\[SPECIES_UNOWN_I\]\s*=\s*\{[\s\S]*?\.frontPic = gMonFrontPic_UnownEye,[\s\S]*?\.backPic = gMonBackPic_UnownEye,[\s\S]*?\.iconSprite = gMonIcon_UnownEye,")


if __name__ == "__main__":
    unittest.main()
