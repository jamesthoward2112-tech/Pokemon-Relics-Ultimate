#!/usr/bin/env python3
"""Check the HNS Lavender memory tower against its original FRLG donor."""

import csv
import json
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]


def load_json(path):
    return json.loads((ROOT / path).read_text(encoding="utf-8"))


def main():
    layouts = {layout["id"]: layout for layout in load_json("data/layouts/layouts.json")["layouts"]}
    soul = load_json("data/maps/LavenderTown_SoulHouse_hns/map.json")
    assert any(o["script"] == "LavenderTownSoulHouse_EventScript_MrFuji" for o in soul["object_events"])
    assert soul["warp_events"][0]["dest_map"] == "MAP_LAVENDER_TOWN_HNS"

    channelers = []
    for floor in range(1, 8):
        path = f"data/maps/LavenderSpiritTower_{floor}F_hns/map.json"
        current = load_json(path)
        donor = load_json(f"data/maps/PokemonTower_{floor}F_Frlg/map.json")
        layout = layouts[current["layout"]]
        donor_layout = layouts[donor["layout"]]
        assert (layout["width"], layout["height"]) == (24, 20)
        assert (layout["width"], layout["height"]) == (donor_layout["width"], donor_layout["height"])
        assert layout["blockdata_filepath"] == donor_layout["blockdata_filepath"]
        assert layout["border_filepath"] == donor_layout["border_filepath"]
        # The copied FRLG tilesets have 32-bit metatile attributes.  An HNS
        # layoutVersion makes fieldmap.c read them as 16-bit Emerald attrs,
        # silently disabling directional staircase warp behaviours.
        assert layout["game_version"] == "hns"
        assert layout["layout_version"] == donor_layout["layout_version"] == "frlg", floor
        assert (ROOT / layout["blockdata_filepath"]).stat().st_size == 24 * 20 * 2
        map_bytes = (ROOT / layout["blockdata_filepath"]).read_bytes()
        tower_attrs = (ROOT / "data/tilesets/secondary/pokemon_tower_frlg/metatile_attributes.bin").read_bytes()
        assert len(current["warp_events"]) == len(donor["warp_events"])

        for portal, old in zip(current["warp_events"], donor["warp_events"]):
            assert (portal["x"], portal["y"], portal["elevation"]) == (
                old["x"], old["y"], old["elevation"]), (floor, portal, old)
            assert 0 <= portal["x"] < 24 and 0 <= portal["y"] < 20
            original_target = old["dest_map"]
            if original_target == "MAP_LAVENDER_TOWN":
                target = "MAP_LAVENDER_TOWN_SOUL_HOUSE_HNS"
                assert portal["dest_warp_id"] == "0"
            else:
                target_floor = int(original_target.removeprefix("MAP_POKEMON_TOWER_").removesuffix("F"))
                target = f"MAP_LAVENDER_SPIRIT_TOWER_{target_floor}F_HNS"
                assert portal["dest_warp_id"] == old["dest_warp_id"]
                destination = load_json(f"data/maps/LavenderSpiritTower_{target_floor}F_hns/map.json")
                matching = destination["warp_events"][int(portal["dest_warp_id"])]
                assert matching["dest_map"] == current["id"], (floor, portal, matching)
                metatile = struct.unpack_from("<H", map_bytes, 2 * (portal["y"] * 24 + portal["x"]))[0] & 0x3FF
                assert metatile >= 0x280, (floor, metatile)
                behavior = struct.unpack_from("<I", tower_attrs, (metatile - 0x280) * 4)[0] & 0x1FF
                assert behavior in (0xEB, 0xEC, 0xED, 0xEE), (floor, portal, behavior)
            assert portal["dest_map"] == target

        if floor == 1:
            # Walkable floor 1 stair: FRLG tile 0x2A8 holds 0xEB
            # (MB_UP_RIGHT_STAIR_WARP).  Misreading its 32-bit attribute as
            # 16-bit produces 0x08 (MB_CAVE) and blocks the player.
            staircase = current["warp_events"][-1]
            assert (staircase["x"], staircase["y"]) == (18, 9)
            tile = struct.unpack_from("<H", map_bytes, 2 * (staircase["y"] * 24 + staircase["x"]))[0] & 0x3FF
            assert tile == 0x2A8
            attribute_offset = (tile - 0x280) * 4
            assert (struct.unpack_from("<I", tower_attrs, attribute_offset)[0] & 0x1FF) == 0xEB
            assert (struct.unpack_from("<H", tower_attrs, attribute_offset // 2)[0] & 0xFF) == 0x08

        assert current["allow_escaping"] is True, f"Escape Rope unavailable on floor {floor}"
        expected_weather = "WEATHER_NONE" if floor == 1 else "WEATHER_FOG_HORIZONTAL"
        assert current["weather"] == expected_weather
        donor_positions = {(o["x"], o["y"]) for o in donor["object_events"] if o["graphics_id"] == "OBJ_EVENT_GFX_CHANNELER"}
        for npc in current["object_events"]:
            if npc["graphics_id"] != "OBJ_EVENT_GFX_CHANNELER":
                continue
            channelers.append(npc)
            assert (npc["x"], npc["y"]) in donor_positions
            assert npc["trainer_type"] == "TRAINER_TYPE_NONE", "No Channeler gauntlet"
            npc_scripts = (ROOT / f"data/maps/LavenderSpiritTower_{floor}F_hns/scripts.inc").read_text(encoding="utf-8")
            assert f'{npc["script"]}::' in npc_scripts

    assert len(channelers) == 2, "Exactly two optional Channelers across seven floors"

    script = (ROOT / "data/maps/LavenderTown_SoulHouse_hns/scripts.inc").read_text(encoding="utf-8")
    assert "strange PIKACHU" in script, "Do not spoil Mimikyu's identity"
    assert "costume" not in script.lower(), "Do not reveal the costume"
    assert "Close your eyes" in script
    escape_command = "setescapewarp MAP_LAVENDER_TOWN_SOUL_HOUSE_HNS, 11, 12"
    assert escape_command in script
    assert script.index(escape_command) < script.index("warp MAP_LAVENDER_SPIRIT_TOWER_1F_HNS, 11, 15")

    encounters = load_json("src/data/wild_encounters.json")["wild_encounter_groups"][0]["encounters"]
    approved = {
        entry["Species_Constant"]
        for entry in csv.DictReader((ROOT / "data/pru/PRU_National_Pokedex_2026-10-16.csv").open(encoding="utf-8-sig"))
    }
    assert len(approved) == 450
    assert "SPECIES_DUSKNOIR" not in approved
    for floor in range(2, 8):
        map_id = f"MAP_LAVENDER_SPIRIT_TOWER_{floor}F_HNS"
        tables = [enc for enc in encounters if enc["map"] == map_id]
        assert len(tables) == 1, (map_id, len(tables))
        land = tables[0]["land_mons"]
        assert 6 <= land["encounter_rate"] <= 15
        assert len(land["mons"]) == 12
        for slot in land["mons"]:
            assert slot["species"] in approved
            assert 48 <= slot["min_level"] <= slot["max_level"] <= 66
            assert slot["species"] not in ("SPECIES_GASTLY", "SPECIES_SHUPPET", "SPECIES_DUSKULL")
    assert not any(e["map"] == "MAP_LAVENDER_SPIRIT_TOWER_1F_HNS" for e in encounters)

    print("PASS: seven-floor FRLG donor, 32-bit stair behaviours, reciprocal warps, fog, Rope return and ghost tables")


if __name__ == "__main__":
    main()
