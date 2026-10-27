#!/usr/bin/env python3
"""Latias/Latios must both roam Johto with visible, distinct weather cues."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
roamer = (root / "src/roamer.c").read_text()
overworld = (root / "src/overworld.c").read_text()
constants = (root / "include/constants/global.h").read_text()

assert re.search(r"#define ROAMER_COUNT [5-7]\b", constants), "Need room for birds and both Lati roamers"
assert "void EnsurePruJohtoLatiRoamers(void)" in roamer
assert "EnsurePruJohtoLatiRoamers();" in overworld
for species in ("LATIAS", "LATIOS"):
    assert f"SPECIES_{species}" in roamer
    assert f"TryAddRoamer(SPECIES_{species}, 60, ROAMER_LOC_TABLE_JOHTO)" in roamer
assert "case SPECIES_LATIAS: SetSavedWeather(WEATHER_DROUGHT)" in roamer
assert "case SPECIES_LATIOS: SetSavedWeather(WEATHER_SUNNY_CLOUDS)" in roamer
assert "ROAMER_LOC_TABLE_JOHTO" in roamer[roamer.index("void RestorePruDefeatedRoamers("):]

print("PASS: both Johto Lati roamers and distinct proximity weather")
