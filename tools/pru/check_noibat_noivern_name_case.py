#!/usr/bin/env python3
"""Keep the two PRU Noibat/Noivern species names in display case, not all caps."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
source = (ROOT / "src/data/pokemon/species_info/gen_6_families.h").read_text(encoding="utf-8")

for symbol, expected in (("SPECIES_NOIBAT", "Noibat"), ("SPECIES_NOIVERN", "Noivern")):
    entry = source.split(f"[{symbol}] =", 1)[1].split("\n    },", 1)[0]
    assert f'.speciesName = _("{expected}")' in entry, (
        f"{symbol} must show as {expected}, not all capitals"
    )
    assert ".natDexNum = NATIONAL_DEX_" + symbol.removeprefix("SPECIES_") in entry, (
        f"{symbol} must keep its existing Pokédex mapping"
    )
print("PASS: Noibat and Noivern display names and Pokédex mappings")
