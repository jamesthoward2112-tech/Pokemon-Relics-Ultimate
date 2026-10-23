#!/usr/bin/env python3
"""Source-only Cubone/Lavender regression audit. No ROM build or emulator launch.

The user approved *exactly three* new Pokédex species (#445-447), with three
future slots intentionally RESERVED. This script MUST NOT treat 448-450 as
already populated, and MUST NOT change main until the other integrated ROM
has completed and this branch has been explicitly approved.
"""
import csv
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
READ = lambda p: (ROOT / p).read_text(encoding="utf-8")
dex = list(csv.DictReader((ROOT / "data/pru/PRU_National_Pokedex_2026-10-16.csv").open(
    encoding="utf-8-sig", newline="")))
assert len(dex) == 447, "444 original plus only three approved additions"
assert [r["PRU_No"] for r in dex[-3:]] == ["445", "446", "447"]
assert [r["Name"] for r in dex[-3:]] == ["Glaceon", "Leafeon", "Mimikyu"]
assert [r["Species_Constant"] for r in dex[-3:]] == [
    "SPECIES_GLACEON", "SPECIES_LEAFEON", "SPECIES_MIMIKYU_DISGUISED"]
order = READ("src/data/pokemon/pru_dex_order.h")
assert "#define PRU_DEX_COUNT 447" in order
assert "SPECIES_MIMIKYU_DISGUISED, // 447 Mimikyu" in order
assert "SPECIES_DUSKNOIR, // 448" not in order
assert "SPECIES_ROTOM, // 450" not in order
evo = READ("src/data/pokemon/species_info/gen_1_families.h")
hns_eevee = evo.split("[SPECIES_EEVEE] =", 1)[1].split("#if IS_HNS", 1)[1].split("#else", 1)[0]
assert "ITEM_ICE_STONE, SPECIES_GLACEON" in hns_eevee
assert "ITEM_LEAF_STONE, SPECIES_LEAFEON" in hns_eevee
mimi_moves = READ("src/data/pokemon/level_up_learnsets/gen_7.h").split(
    "static const struct LevelUpMove sMimikyuLevelUpLearnset[]", 1)[1].split("LEVEL_UP_END", 1)[0]
assert "LEVEL_UP_MOVE(60, MOVE_EERIE_FOG)" in mimi_moves
assert "LEVEL_UP_MOVE(65, MOVE_SHADOW_CLAW)" in mimi_moves

groups = json.loads(READ("data/maps/map_groups.json"))
lavender_group = groups["gMapGroup_IndoorLavender_Hns"]
assert lavender_group[:7] == [
    "LavenderTown_PokemonCenter_hns", "LavenderTown_Mart_hns",
    "LavenderTown_House1_hns", "LavenderTown_House2_hns",
    "LavenderTown_House3_hns", "LavenderTown_RadioStation_hns",
    "LavenderTown_SoulHouse_hns"
], "Existing Lavender map numbers cannot move (old saves)"
for n in range(1, 8):
    key = f"LavenderSpiritTower_{n}F_hns"
    assert key in lavender_group
    m = json.loads(READ(f"data/maps/{key}/map.json"))
    assert m["id"] == f"MAP_LAVENDER_SPIRIT_TOWER_{n}F_HNS"
    assert m["layout"] == f"LAYOUT_POKEMON_TOWER_{n}F"
    assert m["game_version"] == "hns"
    scripts = READ(f"data/maps/{key}/scripts.inc")
    assert f"{key}_MapScripts::" in scripts
    for portal in m["warp_events"]:
        assert portal["dest_map"] in (
            "MAP_LAVENDER_TOWN_SOUL_HOUSE_HNS",
            *(f"MAP_LAVENDER_SPIRIT_TOWER_{i}F_HNS" for i in range(1, 8))
        )
    for event in m["object_events"] + m["coord_events"] + m["bg_events"]:
        if event.get("script"):
            assert f'{event["script"]}::' in scripts, (key, event["script"])

soul = json.loads(READ("data/maps/LavenderTown_SoulHouse_hns/map.json"))
assert len(soul["warp_events"]) == 1, "Preserve original Soul House exit and save warp index"
assert any(e["script"] == "LavenderTownSoulHouse_EventScript_Cubone" for e in soul["object_events"])
soul_script = READ("data/maps/LavenderTown_SoulHouse_hns/scripts.inc")
assert "warp MAP_LAVENDER_SPIRIT_TOWER_1F_HNS, 11, 15" in soul_script
assert "FLAG_PRU_CUBONE_MIMIKYU_CAUGHT" in soul_script
assert "FLAG_PRU_CUBONE_MEMORIAL_REWARDED" in soul_script
f1 = json.loads(READ("data/maps/LavenderSpiritTower_1F_hns/map.json"))
assert all(w["dest_map"] == "MAP_LAVENDER_TOWN_SOUL_HOUSE_HNS"
           for w in f1["warp_events"][:3]), "Return to original Soul House"

flags = READ("include/constants/flags_hns.h")
for flag, address in [
    ("FLAG_PRU_CUBONE_MAROGHOST_RESOLVED", "0x93B"),
    ("FLAG_PRU_CUBONE_OSTEODIAN_RESOLVED", "0x93C"),
    ("FLAG_PRU_CUBONE_MIMIKYU_CAUGHT", "0x93D"),
    ("FLAG_PRU_CUBONE_MEMORIAL_REWARDED", "0x93E"),
]:
    assert re.search(rf"#define\s+{flag}\s+{address}\b", flags), (flag, address)
var_defs = READ("include/constants/vars.h")
for var in ("VAR_PRU_CUBONE_STAGE_MAROGHOST", "VAR_PRU_CUBONE_STAGE_OSTEODIAN"):
    assert var in var_defs

for n, species, stage, flag in [
    (5, "MAROGHOST", "VAR_PRU_CUBONE_STAGE_MAROGHOST", "FLAG_PRU_CUBONE_MAROGHOST_RESOLVED"),
    (6, "OSTEODIAN", "VAR_PRU_CUBONE_STAGE_OSTEODIAN", "FLAG_PRU_CUBONE_OSTEODIAN_RESOLVED"),
]:
    key = f"LavenderSpiritTower_{n}F_hns"
    script = READ(f"data/maps/{key}/scripts.inc")
    m = json.loads(READ(f"data/maps/{key}/map.json"))
    assert len(m["coord_events"]) >= 2
    assert all(event["var"] == stage for event in m["coord_events"])
    assert f"seteventmon SPECIES_{species}, {66 if n == 5 else 68}" in script
    assert "special BattleSetup_StartLegendaryBattle" in script
    assert "B_OUTCOME_WON" in script and "B_OUTCOME_CAUGHT" in script
    assert f"setflag {flag}" in script
    assert f"setvar {stage}, 1" in script
    # Explicit retry (no stage flag on fleeing or losing)
    assert "releaseall" in script
final = READ("data/maps/LavenderSpiritTower_7F_hns/scripts.inc")
assert "goto_if_unset FLAG_PRU_CUBONE_MAROGHOST_RESOLVED" in final
assert "goto_if_unset FLAG_PRU_CUBONE_OSTEODIAN_RESOLVED" in final
assert "seteventmon SPECIES_MIMIKYU_DISGUISED, 70" in final
assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT" in final
assert "setflag FLAG_PRU_CUBONE_MIMIKYU_CAUGHT" in final
assert "goto_if_eq VAR_RESULT, B_OUTCOME_WON" in final
assert "removeobject LOCALID_LAVENDER_SPIRIT_MIMIKYU" in final
native = READ("src/battle_util.c")
for i in (5, 6, 7):
    assert f"MAP_LAVENDER_SPIRIT_TOWER_{i}F_HNS" in native
assert "BATTLE_WEATHER_FOG, ABILITY_NONE" in native
assert "BattleScript_OverworldWeatherStarts" in native
assert "The spectral tower summons Eerie Fog" in native

print("PASS (source only): Lavender quest maps and warps, three approved dex additions,")
print("  ordered catch/KO stage flags, Mimikyu replay, native Eerie Fog, save-safe IDs.")
print("OPEN: no ROM built; compile/link, emulator, save migration and map collision testing pending.")
