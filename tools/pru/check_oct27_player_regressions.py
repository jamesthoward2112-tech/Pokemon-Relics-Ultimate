#!/usr/bin/env python3
"""Player-reported PRU checks that must cover the live script entry points."""

import json
import pathlib
import re

ROOT = pathlib.Path(__file__).resolve().parents[2]
CENTER = (ROOT / "data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc").read_text()
MAP = json.loads((ROOT / "data/maps/IndigoPlateau_PokemonCenter_hns/map.json").read_text())
INTERFACE = (ROOT / "src/battle_interface.c").read_text()


def script(label):
    match = re.search(rf"^{re.escape(label)}::\s*$([\s\S]*?)(?=^[A-Za-z0-9_]+::|\Z)", CENTER, re.M)
    assert match, label
    return match.group(1)


# The door is reached through a center coordinate trigger *before* its fixed
# Johto warp. An ON_TRANSITION warp within Will's map does not reliably run.
trigger = next(e for e in MAP["coord_events"] if (e["x"], e["y"]) == (32, 3))
assert trigger["script"] == "PRU_LeagueEntrance_Seal"
entrance = script("PRU_LeagueEntrance_Seal")
assert "FLAG_PRU_KANTO_LEAGUE_CLEARED" in entrance
assert "PRU_LeagueEntrance_Unsealed" in entrance
unsealed = script("PRU_LeagueEntrance_Unsealed")
assert "PRU_KantoE4_CheckActive" in unsealed
assert "PRU_LeagueEntrance_EnterKanto" in unsealed
kanto_entry = script("PRU_LeagueEntrance_EnterKanto")
assert "warp MAP_POKEMON_LEAGUE_LORELEIS_ROOM, 0" in kanto_entry
for flag in ("LORELEI", "BRUNO", "AGATHA", "LANCE", "CHAMP"):
    assert f"clearflag FLAG_DEFEATED_{flag}" in kanto_entry
assert "setvar VAR_MAP_SCENE_POKEMON_LEAGUE, 0" in kanto_entry

# Silver must disappear permanently on battle completion, and legacy saves
# must not find him waiting after the Kanto League has already been cleared.
assert "setflag FLAG_HIDE_INDIGO_PLATEAU_SILVER" in script("IndigoPlateau_EventScript_Silver")
assert "FLAG_PRU_KANTO_LEAGUE_CLEARED" in script("IndigoPlateau_Pokecenter_OnTransition")

# The custom status tiles must have opaque pixels behind their red letters;
# palette index zero is transparent regardless of its RGB value.
gfx = INTERFACE.split("sPruBleedingStatusGfx[4][24]", 1)[1].split("};", 1)[0]
pixels = re.findall(r"0x([0-9a-fA-F]{8})", gfx)
assert len(pixels) == 4 * 24
assert all("0" not in word for word in pixels), "Transparent pixel found inside BLD icon"
assert "RGB_BLACK" in INTERFACE.split("static const u32 sPruBleedingStatusGfx", 1)[1]

print("PASS: live Kanto door redirect, Silver retirement, opaque BLD icon")
