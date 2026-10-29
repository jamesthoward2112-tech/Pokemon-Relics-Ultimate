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
    def test_player_visible_species_name_is_mewduo_without_changing_species_id(self):
        species = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()
        enum = (ROOT / "include/constants/species.h").read_text()
        self.assertIn('.speciesName = _("Mewduo")', species)
        self.assertIn('#define SPECIES_MEWSION                                       1642', enum)
        self.assertNotIn('.speciesName = _("Mewsion")', species)

    def test_unlock_rule_checks_parent_captures_and_real_mewduo_capture(self):
        source = r'''
#include "pru_mewsion_gate.h"
int main(void)
{
    for (int input = 0; input < 8; ++input)
    {
        int mew = !!(input & 1);
        int mewtwo = !!(input & 2);
        int mewduoCaptured = !!(input & 4);
        int expected = (input == 3);
        if (PruMewsionAllowed(mew, mewtwo, mewduoCaptured) != expected)
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
        self.assertIn("setvar VAR_PRU_MEWDUO_CAPTURE_MARKER, 0x4D44", script)
        self.assertIn("setvar VAR_TEMP_0, 1", script)
        self.assertIn("Dark matter has been detected nearby!", script)

    def test_unlock_on_b2f_reentry_and_uses_caught_dex_and_capture_marker(self):
        code = (ROOT / "src/overworld.c").read_text()
        gate_block = code[code.index("// Returning to B2F"):code.index("for (i = 0; i < ARRAY_COUNT(sLegendaryHideFlags)")]
        self.assertNotIn("MAP_CERULEAN_CITY_HNS", gate_block)
        self.assertNotIn("FlagGet(FLAG_PRU_MEWSION_CAUGHT)", code)
        self.assertIn("VarGet(VAR_PRU_MEWDUO_CAPTURE_MARKER) == 0x4D44", code)
        self.assertIn("NATIONAL_DEX_MEW, FLAG_GET_CAUGHT", code)
        self.assertIn("NATIONAL_DEX_MEWTWO, FLAG_GET_CAUGHT", code)
        self.assertIn("PruMewsionAllowed", code)

    def test_new_capture_marker_is_stable_and_item_910_keeps_ancient_candy(self):
        vars_hns = (ROOT / "include/constants/vars_hns.h").read_text()
        vars_main = (ROOT / "include/constants/vars.h").read_text()
        self.assertIn("#define VAR_PRU_MEWDUO_CAPTURE_MARKER", vars_hns)
        self.assertRegex(vars_hns, r"VAR_PRU_MEWDUO_CAPTURE_MARKER\s+0x40FF\b")
        self.assertRegex(vars_main, r"VAR_PRU_MEWDUO_CAPTURE_MARKER\s+0x40FF\b")
        items = (ROOT / "include/constants/items.h").read_text()
        self.assertIn("ITEM_RELIC_CANDY", items)
        self.assertLess(items.index("ITEM_RELIC_CANDY"), items.index("ITEMS_COUNT"))
        definitions = (ROOT / "src/data/items.h").read_text()
        self.assertIn("[ITEM_RELIC_CANDY]", definitions)
        self.assertIn(".pocket = POCKET_KEY_ITEMS", definitions[definitions.index("[ITEM_RELIC_CANDY]"):])

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
