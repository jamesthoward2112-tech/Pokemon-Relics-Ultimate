#!/usr/bin/env python3
"""Source regression: PRU randomizer never produces species beyond the canonical 450.

Source-only checks. A full PRU compilation and in-game randomizer QA are still required.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
dex = (ROOT / "src/data/pokemon/pru_dex_order.h").read_text()
engine = (ROOT / "src/randomizer.c").read_text()
menu = (ROOT / "src/challenge_menu.c").read_text()

assert "#define PRU_DEX_COUNT 450" in dex
m = re.search(r"static const u16 sPruDexSpecies\[PRU_DEX_COUNT\] =\s*\{(.*?)\n\};", dex, re.S)
assert m, "canonical PRU Dex array missing"
species = re.findall(r"\bSPECIES_[A-Z0-9_]+\s*,", m.group(1))
assert len(species) == len(set(species)) == 450, "roster must be exactly 450 distinct species"

# A single source of truth for all HNS/PRU randomizer modes.
assert '#include "data/pokemon/pru_dex_order.h"' in engine
assert "for (i = 0; i < PRU_DEX_COUNT; i++)" in engine
assert "const u16 species = sPruDexSpecies[i];" in engine
assert "sGenScopeMask[species / 32] |= 1u << (species & 31);" in engine
assert "return IS_HNS || gSaveBlock3Ptr->challengeSettings.tx_Random_GenScope;" in engine
assert "return IsSpeciesValidForRandomizer(species) && IsSpeciesInGenScope(species);" in engine
assert "if (IsSpeciesPermitted(result))" in engine
assert "if (IsSpeciesPermitted(candidate))" in engine
assert "return (IS_HNS && !IsSpeciesPermitted(form)) ? resultSpecies : form;" in engine
assert engine.count("return (IS_HNS && !IsSpeciesPermitted(form)) ? resultSpecies : form;") == 2
for fn in ("RandomizeEvolution", "RandomizeEvoMethod", "RandomizeMonBaseForm",
           "RandomizeWildEncounter", "RandomizeTrainerMon", "RandomizeFixedEncounterMon"):
    assert fn in engine, fn
assert engine.count("!IsSpeciesPermitted(result)") >= 2

# The inherited Gen 1-9 selector is not visible or adjustable in PRU.
assert 'COMPOUND_STRING("PRU 450")' in menu
assert 'COMPOUND_STRING("POKEMON POOL")' in menu
assert 'COMPOUND_STRING("GEN 1-9")' in menu  # retained only for non-HNS variants
assert 'cs->tx_Random_GenScope         = IS_HNS ? TRUE' in menu
assert 'if (sMenu->currentTab == TAB_RANDOMIZER && itemIndex == ITEM_RANDOM_GEN_SCOPE)' in menu
assert 'if (sMenu->currentTab == TAB_RANDOMIZER && itemId == ITEM_RANDOM_GEN_SCOPE)' in menu

# No altered save layout / species IDs; the inherited bit stays allocated for compatibility.
assert 'u8 tx_Random_GenScope:1;' in (ROOT / "include/global.h").read_text()
print("PASS: PRU 450 unique Dex entries; restricted randomizer forms, outcomes and fixed menu source")
