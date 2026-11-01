#!/usr/bin/env python3
"""Focused regression checks for the Ruins of Alph / I-Unown visual patch."""

import json
import re
import struct
import unittest
from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
MAPS = ROOT / "data/maps"


def read_map(name):
    return json.loads((MAPS / name / "map.json").read_text())


class RuinsOfAlphCleanupTests(unittest.TestCase):
    def test_visible_monolith_marks_final_statue_without_changing_i_unown(self):
        interior = read_map("RuinsOfAlph_B1F_hns")
        objects = interior["object_events"]
        altars = [o for o in objects if o["graphics_id"] == "OBJ_EVENT_GFX_ALPHORACLE_MONOLITH_HNS"]
        self.assertEqual(len(altars), 1)
        self.assertEqual((altars[0]["x"], altars[0]["y"]), (25, 28))
        self.assertEqual(altars[0]["script"], "RuinsOfAlph_B1F_hns_RelicAlphoracleOrStatue")
        self.assertEqual(altars[0]["flag"], "FLAG_PJR_RELIC_ALPHORACLE")

        # Keep the I-Unown statue and its exact encounter interaction in place.
        eye = [o for o in objects if o["graphics_id"] == "OBJ_EVENT_GFX_EYE_OF_ALPH_HNS"]
        self.assertEqual(len(eye), 1)
        self.assertEqual((eye[0]["x"], eye[0]["y"]), (16, 10))
        self.assertEqual(eye[0]["script"], "RuinsOfAlph_B1F_hns_RelicUnownI")

        last_statue = [e for e in interior["bg_events"] if e["x"] == 25 and e["y"] == 28]
        self.assertEqual(len(last_statue), 1)
        self.assertEqual(last_statue[0]["script"], "RuinsOfAlph_B1F_hns_RelicAlphoracleOrStatue")

    def test_custom_statues_use_independent_cool_palettes_and_alphoracle_reference_art(self):
        eye_palette = (ROOT / "graphics/object_events/palettes/eye_of_alph.pal").read_text()
        oracle_palette = (ROOT / "graphics/object_events/palettes/alphoracle_monolith.pal").read_text()
        self.assertNotEqual(eye_palette, oracle_palette)
        for palette_text in (eye_palette, oracle_palette):
            colors = [tuple(map(int, line.split())) for line in palette_text.splitlines()
                      if re.fullmatch(r"\d+ \d+ \d+", line)]
            self.assertGreaterEqual(len(colors), 16)
            for red, green, blue in colors[1:]:
                self.assertLessEqual(abs(red - green), 3)
                self.assertLessEqual(abs(green - blue), 3)

        with Image.open(ROOT / "graphics/object_events/pics/misc/eye_of_alph.png") as eye:
            self.assertEqual(eye.size, (64, 64))
        with Image.open(ROOT / "graphics/object_events/pics/misc/alphoracle_monolith.png") as oracle:
            self.assertEqual(oracle.size, (64, 64))
            self.assertEqual(oracle.mode, "P")
        self.assertTrue((ROOT / "assets/pru/alphoracle_monolith_reference.jpg").is_file())

        graphics_info = (ROOT / "src/data/object_events/object_event_graphics_info.h").read_text()
        oracle_info = graphics_info.split("gObjectEventGraphicsInfo_AlphoracleMonolith_hns =", 1)[1].split(";", 1)[0]
        self.assertIn("2048, 64, 64", oracle_info)
        eye_info = graphics_info.split("gObjectEventGraphicsInfo_EyeOfAlph_hns =", 1)[1].split(";", 1)[0]
        self.assertIn("2048, 64, 64", eye_info)

    def test_original_statue_foreground_is_cleared_beneath_both_custom_objects(self):
        layout = ROOT / "data/layouts/RuinsOfAlph_B1F_hns/map.bin"
        values = struct.unpack("<%dH" % (len(layout.read_bytes()) // 2), layout.read_bytes())
        width = 29
        tileset = ROOT / "data/tilesets/secondary/ruins_of_alph_b1_f_hns"
        metatiles = struct.unpack("<%dH" % (len((tileset / "metatiles.bin").read_bytes()) // 2),
                                  (tileset / "metatiles.bin").read_bytes())
        attributes = (tileset / "metatile_attributes.bin").read_bytes()

        for row, col, original, clone in ((9, 16, 99, 200), (10, 16, 10, 201),
                                          (27, 25, 99, 202), (28, 25, 10, 203)):
            cell = values[row * width + col]
            self.assertEqual(cell & 0x3FF, 640 + clone)
            source = metatiles[original * 8:(original + 1) * 8]
            copied = metatiles[clone * 8:(clone + 1) * 8]
            self.assertEqual(copied[:4], source[:4])
            self.assertEqual(copied[4:], (0, 0, 0, 0))
            self.assertEqual(attributes[clone * 2:clone * 2 + 2], attributes[original * 2:original * 2 + 2])

    def test_only_the_eye_statues_foreground_tiles_are_cleared(self):
        layout = ROOT / "data/layouts/RuinsOfAlph_B1F_hns/map.bin"
        raw = layout.read_bytes()
        width = 29
        values = struct.unpack("<%dH" % (len(raw) // 2), raw)
        upper = values[9 * width + 16]
        lower = values[10 * width + 16]

        # These two cells are local copies of the statue tiles with their
        # BG1 foreground layer cleared; map flags/collision bits stay intact.
        self.assertEqual(upper & 0x3FF, 640 + 200)
        self.assertEqual(lower & 0x3FF, 640 + 201)
        self.assertEqual(upper & 0xFC00, 0x3000)
        self.assertEqual(lower & 0xFC00, 0x0400)

        tileset = ROOT / "data/tilesets/secondary/ruins_of_alph_b1_f_hns"
        metatiles = tileset / "metatiles.bin"
        entries = struct.unpack("<%dH" % (len(metatiles.read_bytes()) // 2), metatiles.read_bytes())
        attributes = (tileset / "metatile_attributes.bin").read_bytes()
        for original, clone in ((99, 200), (10, 201)):
            source = entries[original * 8:(original + 1) * 8]
            copied = entries[clone * 8:(clone + 1) * 8]
            self.assertEqual(copied[:4], source[:4])
            self.assertEqual(copied[4:], (0, 0, 0, 0))
            self.assertEqual(attributes[clone * 2:clone * 2 + 2], attributes[original * 2:original * 2 + 2])

    def test_final_statue_opens_alphoracle_directly_without_ladder_or_warp(self):
        interior = read_map("RuinsOfAlph_B1F_hns")
        outside = read_map("RuinsOfAlph_Outside_hns")
        for game_map in (interior, outside):
            self.assertFalse(any(
                o["graphics_id"] == "OBJ_EVENT_GFX_RELIC_LADDER_HNS"
                for o in game_map["object_events"]
            ))

        # Keep the ordinary B1F exit and entrance exactly as they were.
        exit_warp = next(w for w in interior["warp_events"] if w["dest_map"] == "MAP_RUINS_OF_ALPH_OUTSIDE_HNS")
        entry_warp = next(w for w in outside["warp_events"] if w["dest_map"] == "MAP_RUINS_OF_ALPH_B1F_HNS" and w["dest_warp_id"] == "0")
        self.assertEqual((exit_warp["x"], exit_warp["y"], exit_warp["dest_warp_id"]), (15, 16, "5"))
        self.assertEqual((entry_warp["x"], entry_warp["y"]), (21, 21))

        statue = [e for e in interior["bg_events"] if (e["x"], e["y"]) == (25, 28)]
        self.assertEqual(len(statue), 1)
        self.assertEqual(statue[0]["script"], "RuinsOfAlph_B1F_hns_RelicAlphoracleOrStatue")

        shrine = (MAPS / "RuinsOfAlph_B1F_hns/scripts.inc").read_text()
        activation = shrine.split("RuinsOfAlph_B1F_hns_RelicAlphoracleOrStatue::", 1)[1].split("RuinsOfAlph_B1F_hns_RelicAlphoracle::", 1)[0]
        for flag in ("FLAG_IS_CHAMPION", "FLAG_PRU_ELITE18_CLEARED",
                     "FLAG_PJR_RELIC_RAIKOU", "FLAG_PJR_RELIC_ENTEI",
                     "FLAG_PJR_RELIC_LUGIA", "FLAG_PJR_RELIC_UNOWN_I",
                     "FLAG_PJR_RELIC_CELEBI", "FLAG_PJR_RELIC_SUICUNE"):
            self.assertIn(flag, activation)
        self.assertIn("goto RuinsOfAlph_B1F_hns_RelicAlphoracle", activation)
        self.assertIn("goto RuinsOfAlph_Lab_EventScript_RelicAlphoracle", shrine)
        self.assertNotIn("RuinsOfAlph_Outside_RelicLadder::",
                         (MAPS / "RuinsOfAlph_Outside_hns/scripts.inc").read_text())
        self.assertNotIn("warp MAP_RUINS_OF_ALPH_B1F_HNS, 12, 18",
                         (MAPS / "RuinsOfAlph_Outside_hns/scripts.inc").read_text())
        hint = (MAPS / "RuinsOfAlph_Lab_hns/scripts.inc").read_text()
        self.assertIn('Touch the FINAL STONE STATUE', hint)

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
