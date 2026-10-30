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

    def test_mart_clerk_and_held_items(self):
        map_data = json.loads(source("data/maps/IndigoPlateau_PokemonCenter_hns/map.json"))
        clerks = [o for o in map_data["object_events"] if o["script"] == "PRU_IndigoPlateau_HeldItemsClerk"]
        self.assertEqual(len(clerks), 1)
        script = source("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
        self.assertIn("pokemart PRU_IndigoPlateau_HeldItemMart", script)
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
        self.assertIn("setmetatile 46, 4, 0x287, FALSE", script)
        self.assertIn("DarkCave_NorthSide_Text_GroudonGuard", script)
        self.assertIn("FLAG_IS_CHAMPION", source("include/constants/flags_hns.h"))


if __name__ == "__main__":
    unittest.main()
