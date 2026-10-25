#!/usr/bin/env python3
"""PRU 450-species expansion and Kanto heist ace regression."""
import csv
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DEX = ROOT / "data/pru/PRU_National_Pokedex_2026-10-16.csv"
ORDER = ROOT / "src/data/pokemon/pru_dex_order.h"
SPECIES = ROOT / "src/data/pokemon/species_info/gen_1_families.h"
TEAMS = ROOT / "src/data/trainers_hns.party"

def heist_party(name: str) -> str:
    content = TEAMS.read_text(encoding="utf-8")
    return content.split(f"=== TRAINER_PRU_HEIST_{name}_HNS ===", 1)[1].split("===", 1)[0]

def check() -> None:
    with DEX.open(encoding="utf-8-sig", newline="") as f:
        rows = list(csv.DictReader(f))
    assert len(rows) == 450, f"Expected 450 PRU species, found {len(rows)}"
    assert [int(r["PRU_No"]) for r in rows] == list(range(1, 451))
    assert [(r["Name"], r["Species_Constant"]) for r in rows[-3:]] == [
        ("Rhyperior", "SPECIES_RHYPERIOR"),
        ("Electivire", "SPECIES_ELECTIVIRE"),
        ("Magmortar", "SPECIES_MAGMORTAR"),
    ]

    order = ORDER.read_text(encoding="utf-8")
    assert "#define PRU_DEX_COUNT 450" in order
    for no, constant in [(448, "SPECIES_RHYPERIOR"), (449, "SPECIES_ELECTIVIRE"), (450, "SPECIES_MAGMORTAR")]:
        assert f"{constant}, // {no:03d}" in order

    families = SPECIES.read_text(encoding="utf-8")
    for item, species in [("ELECTIRIZER", "ELECTIVIRE"), ("MAGMARIZER", "MAGMORTAR")]:
        assert f"{{EVO_ITEM, ITEM_{item}, SPECIES_{species}}}" in families
        art = ROOT / "graphics/pokemon" / species.lower()
        for asset in ("anim_front.png", "back.png", "icon.png", "normal.pal"):
            assert (art / asset).is_file(), f"Missing {species} asset {asset}"

    shop = (ROOT / "data/maps/GoldenrodCity_DepartmentStore_2F_hns/scripts.inc").read_text(encoding="utf-8")
    for item in ("PROTECTOR", "ELECTIRIZER", "MAGMARIZER"):
        assert f".2byte ITEM_{item}" in shop, f"{item} must be obtainable in Goldenrod"

    surge, blaine = heist_party("SURGE"), heist_party("BLAINE")
    assert "Electivire" in surge and "Noxichu" not in surge
    assert "Magmortar" in blaine
    assert "Double Battle: No" in surge and "Double Battle: No" in blaine

if __name__ == "__main__":
    check()
    print("PASS: PRU 450 roster, item evolutions, sprites and Kanto heist aces")
