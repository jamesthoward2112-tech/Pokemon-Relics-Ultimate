"""Static safety check for the final Tin Tower shortcut and Rocket ambush."""
import json
from pathlib import Path

root = Path(__file__).resolve().parents[1]
maps = root / "data" / "maps"
first = json.loads((maps / "TinTower_1F_hns" / "map.json").read_text())
statues = {(7, 16), (11, 16), (7, 17), (11, 17)}
wired = {
    (event["x"], event["y"])
    for event in first["bg_events"]
    if event.get("script") == "EcruteakBellchimeTrail_EventScript_RelicShortcut"
}
assert wired == statues, (wired, statues)

shortcut = (maps / "BellchimeTrail_hns" / "scripts.inc").read_text()
# Finale access requires cleared Elite 20 and seven recorded RELICS.
# Legacy Wing/Crest items and flags must not gate new or existing saves.
for flag in (
    "FLAG_PRU_ELITE18_CLEARED",
    "FLAG_PJR_RELIC_RAIKOU", "FLAG_PJR_RELIC_ENTEI",
    "FLAG_PJR_RELIC_LUGIA", "FLAG_PJR_RELIC_UNOWN_I",
    "FLAG_PJR_RELIC_CELEBI", "FLAG_PJR_RELIC_SUICUNE",
    "FLAG_PJR_RELIC_ALPHORACLE",
):
    assert f"goto_if_unset {flag}" in shortcut, flag
assert "FLAG_PJR_GOT_RAINBOW_CREST" not in shortcut
assert "ITEM_ANCIENT_RAINBOW_CREST" not in shortcut
assert "setflag FLAG_PJR_RELIC_ALPHORACLE" not in shortcut
assert "EcruteakBellchimeTrail_EventScript_RelicShortcutBackfill" not in shortcut
assert "warp MAP_TIN_TOWER_ROOF_DAY_HNS, 10, 13" in shortcut

# Job 18 now stages the Ancient Guardian Dragonite on the day roof;
# the old automatic Rocket/Ho-Oh roof ambush checks are obsolete.
roof = (maps / "TinTower_RoofDay_hns" / "scripts.inc").read_text()
assert "TinTower_RoofDay_EventScript_SyncGuardianState" in roof
assert "SPECIES_DRAGONITE_GUARDIAN" in roof
assert "FLAG_PRU_GUARDIAN_DRAGONITE_COMPLETE" in roof
assert "seteventmon SPECIES_RELIC_HO_OH" not in roof
print("PASS: Tin Tower shortcut requires seven RELICS + Elite 20; Guardian scene preserved")

generic = (maps / "RuinsOfAlph_PuzzleAndRewardChambers_hns" / "scripts.inc").read_text()
assert "specialvar VAR_RESULT, IsPjrTinTowerEntranceStatue" in generic
assert "goto_if_eq VAR_RESULT, TRUE, EcruteakBellchimeTrail_EventScript_RelicShortcut" in generic
special = (root / "src/field_specials.c").read_text()
assert "MAP_GROUP(MAP_TIN_TOWER_1F_HNS)" in special
assert "MAP_NUM(MAP_TIN_TOWER_1F_HNS)" in special
assert "x -= MAP_OFFSET;" in special and "y -= MAP_OFFSET;" in special
assert "def_special IsPjrTinTowerEntranceStatue" in (root / "data/specials.inc").read_text()
print("PASS: runtime generic statue fallback resolves entrance statues only")
