#!/usr/bin/env python3
"""Fail the PRU build if any Johto/Kanto trainer, wild slot or static
HNS event exposes a species outside the approved 444.

This is deliberately separate from the Pokédex-numbering test: a 444-entry
Pokédex does not prevent Gen 4+ Pokémon appearing in battles or encounters.
Other game modes are not affected by the HNS checks.
"""
import csv
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
with (ROOT / "data/pru/PRU_National_Pokedex_2026-10-16.csv").open(
    encoding="utf-8-sig", newline=""
) as fh:
    rows = list(csv.DictReader(fh))
assert len(rows) == 444
allowed = {row["Species_Constant"] for row in rows}
allowed_names = {row["Name"] for row in rows}
# Internal source name for Valkiri, and the shared species name for Sevii Noivern.
allowed_names.update({"Valkyvoir", "Noivern"})
name_aliases = {
    "Mr Mime": "Mr. Mime",
    "Farfetchd": "Farfetch'd",
    "Nidoran M": "Nidoran♂",
    "Nidoran F": "Nidoran♀",
}
# These forms share a canonical Pokédex species and do not add entries.
form_pattern = re.compile(r"SPECIES_UNOWN_[A-Z_]+|SPECIES_CASTFORM_(NORMAL|SUNNY|RAINY|SNOWY)|SPECIES_DEOXYS_(NORMAL|ATTACK|DEFENSE|SPEED)")

def valid_constant(species):
    return species in allowed or species in {"SPECIES_NONE", "SPECIES_EGG", "SPECIES_WOOPER_PALDEA"} or bool(form_pattern.fullmatch(species))

errors = []
trainer_count = 0
pokemon_count = 0
party = (ROOT / "src/data/trainers_hns.party").read_text(encoding="utf-8")
for section in re.split(r"(?=^=== TRAINER_[^\n]+ ===\s*$)", party, flags=re.M):
    match = re.match(r"^=== (TRAINER_[A-Z0-9_]+) ===", section)
    if not match:
        continue
    trainer = match.group(1)
    trainer_count += 1
    for block in re.split(r"\n[ \t]*\n", section):
        if not re.search(r"^\s*Level:\s*\d+", block, flags=re.M):
            continue
        name = next((line.strip() for line in block.splitlines() if line.strip()), "")
        species = name.split(" @ ", 1)[0].strip()
        species = re.sub(r" \([FM]\)$", "", species)
        pokemon_count += 1
        if species not in allowed_names and name_aliases.get(species) not in allowed_names:
            errors.append(f"{trainer}: forbidden trainer Pokémon {species}")
assert trainer_count >= 650 and pokemon_count >= 1800, (
    "Trainer file was unexpectedly truncated or audit skipped trainer data"
)

wild = json.loads((ROOT / "src/data/wild_encounters.json").read_text(encoding="utf-8"))
wild_maps = set()
wild_slots = 0
for group in wild["wild_encounter_groups"]:
    for encounter in group.get("encounters", []):
        map_name = encounter.get("map", "")
        if not map_name.endswith("_HNS"):
            continue
        wild_maps.add(map_name)
        for area_name, area in encounter.items():
            if not isinstance(area, dict):
                continue
            for mon in area.get("mons", []):
                wild_slots += 1
                if not valid_constant(mon["species"]):
                    errors.append(f"{map_name}/{area_name}: forbidden wild Pokémon {mon['species']}")
assert len(wild_maps) >= 150 and wild_slots >= 6000, (
    "Wild-encounter source unexpectedly missing HNS maps or slots"
)

# Scripted gifts and static battles are encounters too. Keep the check on HNS
# map scripts, not shared Emerald/FRLG donor scripts.
event_scripts = 0
for path in sorted((ROOT / "data/maps").glob("*_hns/scripts.inc")):
    event_scripts += 1
    source = path.read_text(encoding="utf-8")
    for line_number, line in enumerate(source.splitlines(), 1):
        if line.lstrip().startswith(("//", "@")):
            continue
        for species in re.findall(r"\bSPECIES_[A-Z0-9_]+\b", line):
            if not valid_constant(species):
                errors.append(f"{path.relative_to(ROOT)}:{line_number}: forbidden scripted Pokémon {species}")

evolution = (ROOT / "src/pokemon.c").read_text(encoding="utf-8")
assert "IsPruApprovedEvolutionTarget(targetSpecies)" in evolution
assert "sPruDexSpecies[i] == species" in evolution
assert "#define PRU_DEX_COUNT 444" in (ROOT / "src/data/pokemon/pru_dex_order.h").read_text()

if errors:
    print(f"FAIL: {len(errors)} forbidden PRU species placements:")
    for problem in errors[:120]:
        print("  " + problem)
    raise SystemExit(1)
print(f"PASS: {trainer_count} HNS trainers / {pokemon_count} legal Pokémon")
print(f"PASS: {len(wild_maps)} HNS wild maps / {wild_slots} legal wild slots")
print(f"PASS: {event_scripts} HNS map scripts with no out-of-dex species constants")
print("PASS: evolution targets remain confined to the approved 444")
