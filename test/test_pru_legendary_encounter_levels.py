#!/usr/bin/env python3
"""PRU level policy audit for catchable scripted legendary encounters.

Source only: run manually from full repository checkout before a ROM build.
Use: python3 test/test_pru_legendary_encounter_levels.py

The checks intentionally ignore trainer parties, roamer spawn tables and
non-HNS variants. Existing map flags, respawns and event logic are untouched.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
MAPS = ROOT / "data/maps"

LEVELS = {
    # Every catchable Ho-Oh form, including Oak's Relic Ho-Oh, is level 100.
    "HO_OH": 100,
    "RELIC_HO_OH": 100,
    # The final relic of the hunt remains level 90.
    "ALPHORACLE": 90,
    # Other catchable legends and the six hunt relics.
    "RAIKOU": 80,
    "ENTEI": 80,
    "SUICUNE": 80,
    "LUGIA": 80,
    "UNOWN_I": 80,
    "CELEBI": 80,
    "ARTICUNO": 80,
    "ZAPDOS": 80,
    "MOLTRES": 80,
    "KYOGRE": 80,
    "GROUDON": 80,
    "RAYQUAZA": 80,
    "MEWTWO": 80,
    "MEWSION": 80,    # Legacy source ID for Mewduo
    "DEOXYS": 80,
    "MEW": 80,
    "LATIAS": 80,
    "LATIOS": 80,
    "JIRACHI": 80,
}

# Hard-coded previously broken paths; these must all be present and correct.
# counts are the number of distinct catchable level-setting statements
# expected in this map. They are deliberately not NPC trainer-team levels.
REQUIRED = {
    ("RuinsOfAlph_Lab_hns", "RAIKOU"): 1,
    ("RuinsOfAlph_Lab_hns", "ENTEI"): 1,
    ("RuinsOfAlph_Lab_hns", "LUGIA"): 1,
    ("RuinsOfAlph_Lab_hns", "UNOWN_I"): 1,
    ("RuinsOfAlph_Lab_hns", "CELEBI"): 1,
    ("RuinsOfAlph_Lab_hns", "SUICUNE"): 1,
    ("RuinsOfAlph_Lab_hns", "ALPHORACLE"): 1,
    ("TinTower_RoofDay_hns", "RELIC_HO_OH"): 1,
    ("Route10_hns", "RAIKOU"): 1,
    ("WhirlIslands_LugiaChamber_hns", "LUGIA"): 2,
    ("IlexForest_hns", "CELEBI"): 2,
    ("DragonsDen_StormShrine_hns", "RAYQUAZA"): 1,
    ("SeafoamIslands_SecretCave_hns", "KYOGRE"): 1,
    ("Route45_GroudonCave_hns", "GROUDON"): 1,
    ("CeruleanCave_B2F_hns", "MEWTWO"): 1,
    ("CeruleanCave_B2F_hns", "MEWSION"): 1,
    ("BirthIsland_Exterior_hns", "DEOXYS"): 1,
    ("EmbeddedTower_hns", "RAYQUAZA"): 1,
    ("SeafoamIslands_B1F_hns", "ARTICUNO"): 1,
    ("Route25_hns", "SUICUNE"): 1,
    ("MtSilver_1F_MoltresRoom_hns", "GROUDON"): 1,
}

# Match only actual legendary-battle setters, not NPC text, trainers, cries,
# map JSON decorations, or a mon in a story sequence.
PATTERN = re.compile(
    r"^\s*(seteventmon|setwildbattle|setwildbattleshiny)\s+SPECIES_([A-Z0-9_]+),\s*(\d+)\b"
)

encounters = {}
mismatches = []
all_hns_scripts = list(MAPS.glob("*_hns/scripts.inc"))
assert len(all_hns_scripts) >= 500, (
    f"Partial map checkout: found only {len(all_hns_scripts)} HNS scripts"
)
for path in sorted(all_hns_scripts):
    for line_number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        # Lines starting with comments are automatically excluded by PATTERN.
        match = PATTERN.match(line)
        if not match:
            continue
        _, species, level_text = match.groups()
        if species not in LEVELS:
            continue
        level = int(level_text)
        key = (path.parent.name, species)
        encounters.setdefault(key, []).append((line_number, level))
        if level != LEVELS[species]:
            mismatches.append(f"{path}:{line_number} {species} Lv{level} (expected Lv{LEVELS[species]})")

for key, count in REQUIRED.items():
    found = encounters.get(key, [])
    if len(found) != count:
        mismatches.append(f"{key[0]} {key[1]}: {len(found)} level setters, expected {count}")

# There must be exactly one catchable Ho-Oh setter across ALL HNS maps,
# not merely one per listed map. Prevent future duplicate spawns.
hooh_encounters = {
    key: entries for key, entries in encounters.items()
    if key[1] in ("HO_OH", "RELIC_HO_OH")
}
if set(hooh_encounters) != {("TinTower_RoofDay_hns", "RELIC_HO_OH")}:
    mismatches.append(f"Catchable Ho-Oh must exist only at Tin Tower: {hooh_encounters!r}")
elif len(hooh_encounters[("TinTower_RoofDay_hns", "RELIC_HO_OH")]) != 1:
    mismatches.append("Exactly one Ho-Oh battle setter is allowed")

assert not mismatches, "Legendary level mismatches:\n" + "\n".join(mismatches)

# Extra invariants: the seven hunt steps remain scripted in the original lab,
# and only a single Lv100 Ho-Oh battle is reachable from Tin Tower.
lab = (MAPS / "RuinsOfAlph_Lab_hns/scripts.inc").read_text(encoding="utf-8")
for species in ("RAIKOU", "ENTEI", "LUGIA", "UNOWN_I", "CELEBI", "SUICUNE", "ALPHORACLE"):
    assert f"seteventmon SPECIES_{species}, {LEVELS[species]}" in lab
    assert f"FLAG_PJR_RELIC_{species}" in lab

tin = (MAPS / "TinTower_RoofDay_hns/scripts.inc").read_text(encoding="utf-8")
silver = (MAPS / "MtSilver_SummitDay_hns/scripts.inc").read_text(encoding="utf-8")
assert tin.count("seteventmon SPECIES_RELIC_HO_OH, 100") == 1
assert "seteventmon SPECIES_HO_OH," not in tin
assert "seteventmon SPECIES_RELIC_HO_OH," not in silver
assert "FLAG_PJR_RELIC_HO_OH" in tin

print(f"PASS: {sum(map(len, encounters.values()))} scripted catchable legendary level setters")
print("PASS: level 80 standard, Alphoracle 90, Ho-Oh (both forms) 100")
print("PASS: original seven-step RELICS hunt and exactly one Lv100 Relic Ho-Oh at Tin Tower")
print("NOTE: does not test actual encounters, roaming mechanics or save compatibility")
