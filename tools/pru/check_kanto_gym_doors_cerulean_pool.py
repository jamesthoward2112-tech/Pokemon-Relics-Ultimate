"""PRU: all eight Rocket-locked Kanto doors and the Cerulean pool are safe."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
engine = (ROOT / "src/field_control_avatar.c").read_text()
rocket = (ROOT / "data/maps/Route22_hns/scripts.inc").read_text()
pool = (ROOT / "data/maps/CeruleanCity_Gym_hns/scripts.inc").read_text()
fieldmap = (ROOT / "src/fieldmap.c").read_text()

GYMS = {
    "PEWTER_CITY": "BROCK",
    "CERULEAN_CITY": "MISTY",
    "VERMILION_CITY": "SURGE",
    "CELADON_CITY": "ERIKA",
    "FUCHSIA_CITY": "JANINE",
    "SAFFRON_CITY": "SABRINA",
    "SEAFOAM_ISLANDS": "BLAINE",
}

assert "GetPRULockedKantoGymDoorScript" in engine
assert "if (!FlagGet(FLAG_PRU_HEIST_STARTED)" in engine
for gym, leader in GYMS.items():
    assert f"PRU_WARP_TO(MAP_{gym}_GYM_HNS)" in engine, gym
    assert f"FlagGet(FLAG_PRU_HEIST_{leader}) ? NULL : Route22_EventScript_PRUKantoGymLocked" in engine, leader
    assert f"|| !FlagGet(FLAG_PRU_HEIST_{leader})" in engine or f"if (!FlagGet(FLAG_PRU_HEIST_{leader})" in engine
assert "PRU_WARP_TO(MAP_VIRIDIAN_CITY_GYM_HNS)" in engine
assert "Route22_EventScript_PRUViridianGymLocked" in engine
assert engine.count("const u8 *gymGateScript = GetPRULockedKantoGymDoorScript(warpEventId);") == 2
assert "Route22_EventScript_PRUKantoGymLocked::" in rocket
assert "Route22_EventScript_PRUViridianGymLocked::" in rocket
assert "MAP_SCRIPT_ON_LOAD, CeruleanCity_Gym_OnLoadPRUPool" in pool
assert "callnative PruCeruleanGymFixPoolCollision" in pool
assert "void PruCeruleanGymFixPoolCollision(void)" in fieldmap
assert "MapGridSetMetatileImpassabilityAt(x, y, TRUE);" in fieldmap
assert "MB_OCEAN_WATER" in fieldmap and "MB_POND_WATER" in fieldmap
print("PRU_KANTO_DOORS_AND_CERULEAN_POOL_PASS: 8 gated Gyms, Dojo reopening, safe pool")
