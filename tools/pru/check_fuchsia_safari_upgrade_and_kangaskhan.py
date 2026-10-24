#!/usr/bin/env python3
"""PRU Fuchsia Safari upgrade prices, unlocks and Kangaskhan regression."""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
script = (ROOT / "data/maps/FuchsiaCity_SafariZoneEntrance_hns/scripts.inc").read_text()
wild = (ROOT / "src/wild_encounter.c").read_text()
beach_script = (ROOT / "data/maps/FuchsiaCity_SafariZoneBeach_hns/scripts.inc").read_text()
beach = json.loads((ROOT / "data/maps/FuchsiaCity_SafariZoneBeach_hns/map.json").read_text())
brush = json.loads((ROOT / "data/maps/FuchsiaCity_SafariZoneBrush_hns/map.json").read_text())
encounters = json.loads((ROOT / "src/data/wild_encounters.json").read_text())
species = (ROOT / "include/constants/species.h").read_text()

for current_level, cost in ((1, 20000), (2, 30000), (3, 40000)):
    section = script.split(f"FuchsiaCity_SafariZoneEntrance_UpgradeGuy{current_level}::", 1)[1]
    section = section.split("\nFuchsiaCity_SafariZoneEntrance_UpgradeGuy", 1)[0]
    assert f"checkmoney {cost}" in section, (current_level, "balance check")
    assert f"removemoney {cost}" in section, (current_level, "payment")
    assert f"setvar VAR_KANTO_SAFARI_ZONE_PROGRESS, {current_level + 1}" in section
    label = f"FuchsiaCity_SafariZoneEntrance_Text_Level{current_level}:"
    text = script.split(label, 1)[1].split("\n\n", 1)[0]
    assert f"¥{cost:,}" in text, (current_level, "display price")
    assert f"to {current_level + 1}?" in text, (current_level, "unlock level")

assert "goto_if_eq VAR_KANTO_SAFARI_ZONE_PROGRESS, 4, FuchsiaCity_SafariZoneEntrance_UpgradeGuy3" not in script
assert "FuchsiaCity_SafariZoneEntrance_Text_MaxLevel" in script
assert "SafariZoneFuchsia_Trigger1" in beach_script
assert brush["id"] == "MAP_FUCHSIA_CITY_SAFARI_ZONE_BRUSH_HNS"
assert "SPECIES_KANGASKHAN" in species

# Kangaskhan must be generated in an actual wild land encounter (not overworld decoration).
assert "if (area == WILD_AREA_LAND" in wild
assert "GetSafariZoneFlag()" in wild
assert "MAP_GROUP(MAP_FUCHSIA_CITY_SAFARI_ZONE_BRUSH_HNS)" in wild
assert "MAP_NUM(MAP_FUCHSIA_CITY_SAFARI_ZONE_BRUSH_HNS)" in wild
assert "(Random() % 100) < 10" in wild
assert "species = SPECIES_KANGASKHAN;" in wild
chunk = wild.split("static bool8 TryGenerateWildMon(", 1)[1].split("static u16 GenerateFishingWildMon(", 1)[0]
assert chunk.index("species = SPECIES_KANGASKHAN;") < chunk.index("CreateWildMon(species, level);")
assert "RANDOMIZER_AVAILABLE" in chunk

safari_maps = [e for group in encounters["wild_encounter_groups"]
               for e in group.get("encounters", [])
               if e["map"] == brush["id"]]
assert safari_maps and any(e.get("land_mons", {}).get("encounter_rate", 0) > 0
                           and len(e["land_mons"]["mons"]) > 0 for e in safari_maps)
assert any(c.get("map") == brush["id"] for c in beach.get("connections", []))
print("PASS: Fuchsia Safari level 2/3/4 prices (20k/30k/40k) and catchable Kangaskhan in Brush")
