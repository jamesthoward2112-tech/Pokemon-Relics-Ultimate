"""Regression checks for the Champion-only Storm Shrine doorway in Dragon Shrine."""

import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SHRINE = ROOT / "data/maps/DragonsDen_Shrine_hns"
STORM = ROOT / "data/maps/DragonsDen_StormShrine_hns"


class TestStormShrineDoor(unittest.TestCase):
    def test_door_is_behind_elder_not_on_quiz_approach(self):
        shrine = json.loads((SHRINE / "map.json").read_text())
        elder = next(event for event in shrine["object_events"]
                     if event["script"] == "DragonsDen_Shrine_EventScript_Elder")
        self.assertEqual((elder["x"], elder["y"]), (6, 9))
        door = [event for event in shrine["bg_events"]
                if event["script"] == "DragonsDen_Shrine_Trigger_StormShrine"]
        self.assertEqual(len(door), 1)
        self.assertEqual((door[0]["x"], door[0]["y"]), (6, 7))
        self.assertFalse(any(event["script"] == "DragonsDen_Shrine_Trigger_StormShrine"
                             for event in shrine["coord_events"]))
        self.assertTrue(any(event["script"] == "DragonsDen_Shrine_Trigger_ElderQuizTop"
                            for event in shrine["coord_events"]))

    def test_badge_and_champion_gate_without_elite20(self):
        script = (STORM / "scripts.inc").read_text()
        begin = script.index("DragonsDen_Shrine_Trigger_StormShrine::")
        end = script.index("DragonsDen_Shrine_StormShrineLocked::", begin)
        gate = script[begin:end]
        self.assertIn("goto_if_unset FLAG_BADGE08_GET", gate)
        self.assertIn("goto_if_unset FLAG_IS_CHAMPION", gate)
        self.assertIn("warp MAP_DRAGONS_DEN_STORM_SHRINE_HNS, 6, 15", gate)
        self.assertNotIn("ELITE20", gate.upper())

    def test_return_warp_and_existing_rayquaza_flags(self):
        storm_map = json.loads((STORM / "map.json").read_text())
        self.assertEqual(storm_map["warp_events"][0]["dest_map"],
                         "MAP_DRAGONS_DEN_SHRINE_HNS")
        self.assertEqual(storm_map["warp_events"][0]["dest_warp_id"], "0")
        script = (STORM / "scripts.inc").read_text()
        self.assertIn("FLAG_PRU_RAYQUAZA_CAUGHT", script)
        self.assertIn("FLAG_PRU_HIDE_RAYQUAZA", script)
        self.assertIn("setwildbattleshiny SPECIES_RAYQUAZA, 85", script)


if __name__ == "__main__":
    unittest.main()
