"""Source checks for standalone PRU endgame access / new-game setup changes."""
import json
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def source(path):
    return (ROOT / path).read_text()


class PRUChallengeMartGroudonTests(unittest.TestCase):
    def test_new_game_reaches_existing_challenge_menu(self):
        script = source("src/oak_speech_hns.c")
        section = script.split("static void Task_NewGameHnsSpeech_ChallengeDisclaimer(u8 taskId)\n{", 1)[1].split("\nstatic void ", 1)[0]
        self.assertIn("Task_NewGameHnsSpeech_ChallengeMenu", section)
        self.assertNotIn("Task_NewGameHnsSpeech_SlidePlatformAway2", section)
        for tab in ("TAB_NUZLOCKE", "TAB_RANDOMIZER", "TAB_DIFFICULTY", "TAB_CHALLENGES"):
            self.assertIn(tab, source("src/challenge_menu.c"))

    def test_debug_is_inaccessible(self):
        cfg = source("include/config/debug.h")
        for setting in ("DEBUG_OVERWORLD_MENU", "DEBUG_BATTLE_MENU", "DEBUG_POKEMON_SPRITE_VISUALIZER"):
            self.assertRegex(cfg, r"#define\s+" + setting + r"\s+FALSE")

    def test_rayquaza_shrine_dialogue_uses_assembler_escapes(self):
        script = source("data/maps/DragonsDen_StormShrine_hns/scripts.inc")
        self.assertIn(r'.string "The dragon seal recognises you...\p"', script)
        self.assertIn(r'.string "Beyond this door lies the STORM\n"', script)
        self.assertNotIn(r'\\p"', script)
        self.assertNotIn(r'\\n"', script)

    def test_mart_clerk_and_held_items(self):
        map_data = json.loads(source("data/maps/IndigoPlateau_PokemonCenter_hns/map.json"))
        clerks = [o for o in map_data["object_events"] if o["script"] == "PRU_IndigoPlateau_HeldItemsClerk"]
        self.assertEqual(len(clerks), 1)
        script = source("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
        self.assertIn("pokemart PRU_IndigoPlateau_HeldItemMart", script)
        self.assertIn(r'.string "Welcome to the INDIGO LEAGUE\n"', script)
        self.assertNotIn(r'.string "Welcome to the INDIGO LEAGUE\\n"', script)
        for item in ("WEAKNESS_POLICY", "THROAT_SPRAY", "CHOICE_BAND", "FOCUS_SASH", "HEAVY_DUTY_BOOTS"):
            self.assertIn("ITEM_" + item, script)

    def test_groudon_guard_disappears_after_champion(self):
        # One actual new entrance inside the Blackthorn-side Dark Cave, NOT
        # an impassable outdoor tile beside its existing Route 45 entrance.
        outside = json.loads(source("data/maps/Route45_hns/map.json"))
        interior = json.loads(source("data/maps/DarkCave_NorthSide_hns/map.json"))
        chamber = json.loads(source("data/maps/Route45_GroudonCave_hns/map.json"))

        self.assertFalse(any(w["dest_map"] == "MAP_ROUTE45_GROUDON_CAVE_HNS"
                             for w in outside["warp_events"]))
        self.assertFalse(any(o["script"] == "Route45_EventScript_GroudonCaveGuard"
                             for o in outside["object_events"]))
        self.assertTrue(any(w["x"] == 45 and w["y"] == 9 and
                            w["dest_map"] == "MAP_ROUTE45_HNS"
                            for w in interior["warp_events"]))

        guards = [o for o in interior["object_events"]
                  if o["script"] == "DarkCave_NorthSide_EventScript_GroudonGuard"]
        self.assertEqual(len(guards), 1)
        self.assertEqual((guards[0]["x"], guards[0]["y"]), (46, 5))
        self.assertEqual(guards[0]["flag"], "FLAG_IS_CHAMPION")
        # Player-tested existing rock already blocks the right side.
        self.assertFalse(any(o["script"] == "DarkCave_NorthSide_EventScript_GroudonSideRock"
                             for o in interior["object_events"]))
        self.assertFalse(any((o["x"], o["y"]) == (47, 5)
                             for o in interior["object_events"]))
        self.assertNotIn("DarkCave_NorthSide_EventScript_GroudonSideRock",
                         source("data/maps/DarkCave_NorthSide_hns/scripts.inc"))

        entrance = [i for i, w in enumerate(interior["warp_events"])
                    if w["dest_map"] == "MAP_ROUTE45_GROUDON_CAVE_HNS"]
        self.assertEqual(len(entrance), 1)
        self.assertEqual((interior["warp_events"][entrance[0]]["x"],
                          interior["warp_events"][entrance[0]]["y"]), (46, 4))
        self.assertTrue(any(w["dest_map"] == "MAP_DARK_CAVE_NORTH_SIDE_HNS" and
                            int(w["dest_warp_id"]) == entrance[0]
                            for w in chamber["warp_events"]))

        script = source("data/maps/DarkCave_NorthSide_hns/scripts.inc")
        self.assertIn("map_script MAP_SCRIPT_ON_LOAD, DarkCave_NorthSide_OnLoadGroudonPassage", script)
        self.assertIn("callnative PruOpenDarkCaveGroudonDoor", script)
        map_patch = source("src/fieldmap.c")
        # Confirm the chosen tile already functions as Dark Cave's entrance.
        import struct
        raw = (ROOT / "data/layouts/DarkCave_NorthSide_hns/map.bin").read_bytes()
        self.assertEqual(struct.unpack_from("<H", raw, 2 * (9 * 57 + 45))[0], 0x3287)
        # Existing Cave_Default_Hns ladder tile, not the corrupt 0x3B2..0x3B4 cutout.
        self.assertIn("MapGridSetMetatileEntryAt(46 + MAP_OFFSET, 4 + MAP_OFFSET, 0x3285)", map_patch)
        self.assertNotIn("MapGridSetMetatileEntryAt(45 + MAP_OFFSET, 4 + MAP_OFFSET", map_patch)
        self.assertNotIn("MapGridSetMetatileEntryAt(47 + MAP_OFFSET, 4 + MAP_OFFSET", map_patch)
        art = (ROOT / "data/tilesets/secondary/cave_default_hns/metatiles.bin").read_bytes()
        attrs = (ROOT / "data/tilesets/secondary/cave_default_hns/metatile_attributes.bin").read_bytes()
        self.assertEqual(len(art), 306 * 16)  # Failed 0x3B2..0x3B4 tiles removed
        self.assertEqual(len(attrs), 306 * 2)
        self.assertEqual(struct.unpack_from("<8H", art, (0x285 - 0x280) * 16),
                         (0x9288, 0x9289, 0x9298, 0x9299, 0, 0, 0, 0))
        self.assertEqual(struct.unpack_from("<H", attrs, (0x285 - 0x280) * 2)[0], 0x0061)
        self.assertIn("MapGridSetMetatileEntryAt(46 + MAP_OFFSET, 5 + MAP_OFFSET, 0x3281)", map_patch)
        self.assertIn("DarkCave_NorthSide_Text_GroudonGuard", script)
        self.assertIn("FLAG_IS_CHAMPION", source("include/constants/flags_hns.h"))


    def test_existing_e20_save_receives_oak_relics_advice(self):
        oak = source("data/maps/PalletTown_Lab_hns/scripts.inc")
        e20 = source("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
        lab = json.loads(source("data/maps/PalletTown_Lab_hns/map.json"))
        self.assertEqual(sum(o["script"] == "PalletTown_Lab_EventScript_Oak"
                             for o in lab["object_events"]), 1)
        entry = oak.split("PalletTown_Lab_EventScript_Oak::", 1)[1].split(
            "PalletTown_Lab_EventScript_OakNormalEntry::", 1)[0]
        self.assertIn("goto_if_set FLAG_PRU_ELITE18_CLEARED, PalletTown_Lab_EventScript_OakRelicsMenu", entry)
        self.assertNotIn("FLAG_PRU_E20_REWARD_CLAIMED", entry)
        self.assertNotIn("FLAG_PRU_E20_CREDITS_SHOWN", entry)
        menu = oak.split("PalletTown_Lab_EventScript_OakRelicsMenu::", 1)[1].split(
            "PalletTown_Lab_EventScript_OakRelicsExplain::", 1)[0]
        for choice in ("About the RELICS", "Where next?", "Other research"):
            self.assertIn(choice, oak)
        self.assertIn("dynmultichoice 0, 0, FALSE, 3", menu)
        self.assertIn("case MULTI_B_PRESSED, PalletTown_Lab_EventScript_OakNormalEntry", menu)
        self.assertIn("PalletTown_Lab_EventScript_OakDex", oak)
        for flag in (
            "FLAG_PJR_RELIC_RAIKOU", "FLAG_PJR_RELIC_ENTEI", "FLAG_PJR_RELIC_LUGIA",
            "FLAG_PJR_RELIC_UNOWN_I", "FLAG_PJR_RELIC_CELEBI", "FLAG_PJR_RELIC_SUICUNE",
            "FLAG_PJR_RELIC_ALPHORACLE", "FLAG_PJR_GOT_RAINBOW_CREST",
            "FLAG_PJR_RELIC_HO_OH",
        ):
            self.assertIn(flag, oak)
        for location in ("VIOLET CITY", "ROUTE 32", "RUINS OF ALPH", "RESEARCH LAB", "RAIKOU"):
            self.assertIn(location, oak)
        # The final Oak/Elm round now tells everyone where the quest starts
        # regardless of any previous one-time rewards/credits flags.
        cleared = e20.split("PRU_Elite18_Gauntlet::", 1)[1].split(
            "PRU_Elite20_StartFinale::", 1)[0]
        self.assertLess(cleared.index("call PRU_Elite18_Round_20"),
                        cleared.index("msgbox PRU_Elite20_Text_RuinsDirections"))
        self.assertLess(cleared.index("msgbox PRU_Elite20_Text_RuinsDirections"),
                        cleared.index("call PRU_Elite20_ClaimRewards"))
        self.assertIn("goto_if_set FLAG_PRU_E20_REWARD_CLAIMED", e20)
        self.assertIn("goto_if_set FLAG_PRU_E20_CREDITS_SHOWN", e20)
        self.assertNotIn(r'\\n"', oak)
        self.assertNotIn(r'\\p"', oak)


if __name__ == "__main__":
    unittest.main()
