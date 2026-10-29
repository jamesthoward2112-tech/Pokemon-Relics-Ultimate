#!/usr/bin/env python3
"""Donor-data regression tests for standard Insurgence Shadow Mewtwo."""

import pathlib
import re
import struct
import unittest


ROOT = pathlib.Path(__file__).resolve().parents[2]


def read(path):
    return (ROOT / path).read_text()


def between(text, start, end):
    begin = text.find(start)
    if begin < 0:
        return ""
    finish = text.find(end, begin + len(start))
    return text[begin:finish] if finish >= 0 else text[begin:]


def png_details(path):
    image = (ROOT / path).read_bytes()
    assert image[:8] == b"\x89PNG\r\n\x1a\n"
    width, height, depth, kind = struct.unpack(">IIBB", image[16:26])
    return width, height, depth, kind, image


class ShadowMewtwoTests(unittest.TestCase):
    def test_dark_nova_is_appended_without_shifting_existing_move_ids(self):
        source = read("include/constants/moves.h")
        source = re.sub(r"//[^\n]*", "", source)
        # Keep all moves added by the latest playable PRU build ahead of
        # Insurgence's additions; shifting them corrupts learned moves.
        self.assertRegex(source, r"MOVE_MINDWAVE,\s*MOVE_DARK_NOVA,")
        self.assertLess(source.index("MOVE_DARK_NOVA,"), source.index("MOVES_COUNT,"))

    def test_dark_nova_is_a_two_hit_dynamic_category_dark_move(self):
        move = between(read("src/data/moves_info.h"), "[MOVE_DARK_NOVA] =", "\n    },")
        for expected in (
            'COMPOUND_STRING("DARK NOVA")',
            ".effect = EFFECT_PHOTON_GEYSER",
            ".power = 135",
            ".type = TYPE_DARK",
            ".accuracy = 0",
            ".pp = 5",
            ".strikeCount = 2",
            ".category = DAMAGE_CATEGORY_SPECIAL",
        ):
            self.assertTrue(expected in move, f"Dark Nova missing {expected}")
        self.assertNotIn("BURST", move.upper())

    def test_normal_mewtwo_is_shadow_donor_with_same_species_identity(self):
        data = between(read("src/data/pokemon/species_info/gen_1_families.h"),
                       "[SPECIES_MEWTWO] =", "#if P_MEGA_EVOLUTIONS")
        for expected in (
            ".baseHP        = 106", ".baseAttack    = 110",
            ".baseDefense   = 90", ".baseSpeed     = 130",
            ".baseSpAttack  = 154", "MON_TYPES(TYPE_PSYCHIC, TYPE_DARK)",
            "ABILITY_INTIMIDATE", ".natDexNum = NATIONAL_DEX_MEWTWO",
            ".levelUpLearnset = sInsurgenceShadowMewtwoLevelUpLearnset",
            ".teachableLearnset = &sInsurgenceShadowMewtwoTeachableLearnset[0]",
        ):
            self.assertTrue(expected in data, f"Standard Mewtwo missing {expected}")
        self.assertIn(".formChangeTable = sMewtwoFormChangeTable", data)

    def test_authentic_insurgence_shadow_mewtwo_levelup_moves(self):
        data = between(read("src/data/pokemon/level_up_learnsets/pru.h"),
                       "sInsurgenceShadowMewtwoLevelUpLearnset[]", "LEVEL_UP_END")
        actual = [(int(level), move) for level, move in
                  re.findall(r"LEVEL_UP_MOVE\(\s*(\d+),\s*MOVE_([A-Z0-9_]+)\)", data)]
        expected = [
            (1, "NIGHT_SLASH"), (1, "CONFUSION"), (1, "DISABLE"), (1, "SAFEGUARD"),
            (8, "SWIFT"), (15, "FUTURE_SIGHT"), (22, "PSYCH_UP"),
            (29, "MIRACLE_EYE"), (36, "PSYCHO_CUT"), (43, "POWER_SWAP"),
            (43, "GUARD_SWAP"), (50, "RECOVER"), (57, "PSYCHIC"),
            (64, "BARRIER"), (70, "AURA_SPHERE"), (79, "AMNESIA"),
            (86, "MIST"), (93, "ME_FIRST"), (100, "PSYSTRIKE"),
            (100, "DARK_NOVA"),
        ]
        self.assertEqual(actual, expected)

    def test_shadow_donor_teachable_moves_not_replaced_with_vanilla(self):
        data = between(read("src/data/pokemon/teachable_learnsets/pru.h"),
                       "sInsurgenceShadowMewtwoTeachableLearnset[]", "MOVE_UNAVAILABLE,")
        for move in ("BULLDOZE", "CALM_MIND", "DARK_PULSE", "FOUL_PLAY", "HURRICANE",
                     "TRICK", "ZEN_HEADBUTT", "ICE_BEAM", "THUNDERBOLT",
                     "ROCK_SMASH", "DIVE", "STRENGTH"):
            self.assertTrue(f"MOVE_{move}" in data, f"Shadow Mewtwo cannot learn {move}")

    def test_donor_graphics_are_indexed_and_include_two_frames(self):
        files = {
            "graphics/pokemon/mewtwo/anim_front.png": (64, 128),
            "graphics/pokemon/mewtwo/anim_front_gba.png": (64, 128),
            "graphics/pokemon/mewtwo/back.png": (64, 64),
            "graphics/pokemon/mewtwo/back_gba.png": (64, 64),
            "graphics/pokemon/mewtwo/icon.png": (32, 64),
            "graphics/pokemon/mewtwo/icon_gba.png": (32, 64),
            "graphics/pokemon/mewtwo/overworld.png": (192, 32),
            "graphics/pokemon/mewsion/overworld.png": (192, 32),
        }
        for path, dimensions in files.items():
            with self.subTest(path=path):
                width, height, depth, kind, blob = png_details(path)
                self.assertEqual((width, height, depth, kind), (*dimensions, 8, 3))
                self.assertIn(b"PLTE", blob)
                self.assertIn(b"tRNS", blob)
                self.assertGreater(len(blob), 150)

    def test_shiny_palette_is_donor_blue_and_distinct_from_normal(self):
        normal = read("graphics/pokemon/mewtwo/normal.pal")
        shiny = read("graphics/pokemon/mewtwo/shiny.pal")
        self.assertNotEqual(normal, shiny)
        self.assertIn("211 104 0", normal)  # orange-tipped normal shadow
        self.assertIn("3 19 37", shiny)  # blue-black shiny shadow
        for name in ("normal_gba.pal", "overworld_normal.pal"):
            self.assertEqual(normal, read(f"graphics/pokemon/mewtwo/{name}"))
        for name in ("shiny_gba.pal", "overworld_shiny.pal"):
            self.assertEqual(shiny, read(f"graphics/pokemon/mewtwo/{name}"))

    def test_mewsion_has_real_overworld_species_graphics(self):
        species = between(read("src/data/pokemon/species_info/pru_custom.h"),
                          "[SPECIES_MEWSION] =", "[SPECIES_")
        self.assertIn("sPicTable_Mewsion", species)
        self.assertIn("gOverworldPalette_Mewsion", species)
        self.assertIn("gObjectEventPic_Mewsion", read("src/data/graphics/pru_pokemon.h"))
        self.assertIn("overworld_ascending_frames(gObjectEventPic_Mewsion, 4, 4)",
                      read("src/data/object_events/object_event_pic_tables_followers.h"))
        self.assertNotEqual((ROOT / "graphics/pokemon/mewsion/overworld.png").read_bytes(),
                            (ROOT / "graphics/pokemon/mewtwo/overworld.png").read_bytes())


if __name__ == "__main__":
    unittest.main()
