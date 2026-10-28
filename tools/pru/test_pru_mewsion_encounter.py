#!/usr/bin/env python3
"""Native rule check + source integration checks for PRU's Mewsion event."""

import json
import pathlib
import re
import subprocess
import tempfile
import unittest


ROOT = pathlib.Path(__file__).resolve().parents[2]


class MewsionEncounterTests(unittest.TestCase):
    def test_unlock_rule_checks_every_capture_and_reentry_combination(self):
        source = r'''
#include "pru_mewsion_gate.h"
int main(void)
{
    for (int input = 0; input < 16; ++input)
    {
        int mew = !!(input & 1);
        int mewtwo = !!(input & 2);
        int returned = !!(input & 4);
        int mewsion = !!(input & 8);
        int expected = (input == 7);
        if (PruMewsionAllowed(mew, mewtwo, returned, mewsion) != expected)
            return input + 1;
    }
    return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="pru_mewsion_test_") as tmp:
            binary = pathlib.Path(tmp) / "mewsion_gate"
            subprocess.run(
                ["cc", "-std=c11", "-Wall", "-Werror", "-I", str(ROOT / "src"),
                 "-x", "c", "-", "-o", str(binary)],
                input=source, text=True, capture_output=True, check=True,
            )
            subprocess.run([str(binary)], check=True, capture_output=True)

    def test_map_object_on_mewtwo_tile_with_independent_hide_flag(self):
        data = json.loads((ROOT / "data/maps/CeruleanCave_B2F_hns/map.json").read_text())
        event, = [e for e in data["object_events"]
                  if e.get("script") == "CeruleanCave3_EventScript_Mewsion"]
        self.assertEqual((event["x"], event["y"]), (8, 14))
        self.assertEqual(event["graphics_id"], "OBJ_EVENT_GFX_MON_BASE+SPECIES_MEWSION")
        self.assertEqual(event["flag"], "FLAG_TEMP_B")
        self.assertEqual(len([e for e in data["object_events"]
                              if e.get("script") == "CeruleanCave3_EventScript_MewtwoNew"]), 1)

    def test_script_uses_level90_caught_only_and_one_warning(self):
        script = (ROOT / "data/maps/CeruleanCave_B2F_hns/scripts.inc").read_text()
        self.assertIn("seteventmon SPECIES_MEWSION, 90", script)
        self.assertIn("goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, CeruleanCave3_EventScript_MewsionCaught", script)
        self.assertIn("setflag FLAG_PRU_MEWSION_CAUGHT", script)
        self.assertIn("setvar VAR_TEMP_0, 1", script)
        self.assertIn("Dark matter has been detected nearby!", script)

    def test_unlock_only_on_cerulean_city_map_load_and_uses_caught_dex(self):
        code = (ROOT / "src/overworld.c").read_text()
        self.assertIn("MAP_CERULEAN_CITY_HNS", code)
        self.assertIn("FLAG_PRU_MEWSION_REENTRY_READY", code)
        self.assertIn("FLAG_PRU_MEWSION_CAUGHT", code)
        self.assertIn("NATIONAL_DEX_MEW, FLAG_GET_CAUGHT", code)
        self.assertIn("NATIONAL_DEX_MEWTWO, FLAG_GET_CAUGHT", code)
        self.assertIn("PruMewsionAllowed", code)

    def test_new_flags_are_distinct_and_do_not_overlap_existing(self):
        flags = (ROOT / "include/constants/flags_hns.h").read_text()
        values = {}
        for name, val in re.findall(r"^#define\s+(FLAG_[A-Z_0-9]+)\s+(0x[0-9A-Fa-f]+)\b", flags, re.M):
            values.setdefault(int(val, 16), []).append(name)
        for name in ("FLAG_PRU_MEWSION_REENTRY_READY", "FLAG_PRU_MEWSION_CAUGHT"):
            found = [val for val, names in values.items() if name in names]
            self.assertEqual(len(found), 1, name)
            self.assertEqual(len(values[found[0]]), 1, name)
            self.assertLess(found[0], 0x500)


if __name__ == "__main__":
    unittest.main()
