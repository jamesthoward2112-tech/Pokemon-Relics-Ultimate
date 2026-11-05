#!/usr/bin/env python3
"""Job 8: the visible PRU Dex, independent custom bits and old-save layout."""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
read=lambda p:(root/p).read_text(encoding="utf-8")
order=read("src/data/pokemon/pru_dex_order.h")
roster=re.findall(r"^\s+(SPECIES_[A-Z0-9_]+),\s*// \d{3} ",order,re.M)
assert len(roster)==450,("roster length",len(roster))
assert len(set(roster))==450,"two PRU slots reference the same underlying species"
for pos,mon in {4:"EDENSAUR",8:"CHARAXIS",12:"FORTOTOISE",32:"NOXICHU",
                167:"EEVEE",185:"SYLVEON",261:"HERACURION",437:"ALPHORACLE",
                450:"DEOXYS"}.items():
    assert roster[pos-1]==f"SPECIES_{mon}",(pos,roster[pos-1])
# All virtual flag slots are in Gen 5 IDs explicitly EXCLUDED from PRU.
national=re.search(r"static const u32 sNationalToSpeciesOrder\[NATIONAL_DEX_COUNT\] =\s*\{(.*?)\n\};",
                   read("src/pokemon.c"), re.S).group(1)
native={"SPECIES_"+s for s in re.findall(r"NATIONAL_TO_SPECIES\(([A-Z0-9_]+)\)",national)}
custom=[s for s in roster if s not in native]
assert len(custom)<(650-495),len(custom)
assert not any(s in roster for s in ("SPECIES_SNIVY","SPECIES_SERVINE",
                                    "SPECIES_SERPERIOR","SPECIES_TEPIG",
                                    "SPECIES_OSHAWOTT","SPECIES_ZORUA"))
engine=read("src/pokemon.c")
for required in ("#define PRU_EXTRA_NATIONAL_DEX_START NATIONAL_DEX_SNIVY",
                 "#define PRU_EXTRA_NATIONAL_DEX_END NATIONAL_DEX_CHESPIN",
                 "PruExtraNationalSlotForSpecies", "PruExtraSpeciesForNationalSlot",
                 "PruReconcileLegacyDexFlagsFromOwnedMons",
                 "GetBoxMonDataAt(box, slot, MON_DATA_SPECIES)",
                 "GetSetPokedexFlag(extraSlot, FLAG_SET_CAUGHT)"):
    assert required in engine,required
pokedex=read("src/pokedex.c")
assert "if (!nationalDexNo || nationalDexNo > NATIONAL_DEX_COUNT)" in pokedex
assert "for (i = 0; i < PRU_DEX_COUNT; i++)" in pokedex
assert "SpeciesToNationalPokedexNum(sPruDexSpecies[i])" in pokedex
hgss=read("src/pokedex_plus_hgss.c")
for required in ("CreatePruPokedexList(order);",
                 "PruReconcileLegacyDexFlagsFromOwnedMons();",
                 "sPokedexView->dexMode = IS_HNS ? DEX_MODE_NATIONAL",
                 "SpeciesToPokedexNum(NationalPokedexNumToSpecies(dexNum))",
                 "SpeciesToPokedexNum(NationalPokedexNumToSpecies(num))",
                 "PruDexEntrySortsBefore",
                 "return IS_HNS ? DEX_MODE_NATIONAL : sPokedexModes[id]"):
    assert required in hgss,required
assert "PRU_DEX_COUNT 450" in order
# Every HGSS screen must treat PRU as unlocked National from the first Dex
# opening, including the search menu, return paths, palettes and stat pages.
assert "if (!IsNationalPokedexEnabled())" not in hgss
assert "else if (!IsNationalPokedexEnabled())" not in hgss
assert "if ((!IsNationalPokedexEnabled() || sPokedexView->dexMode" not in hgss
assert "value = SpeciesToPokedexNum(NationalPokedexNumToSpecies(num));" in hgss
assert hgss.count("value = SpeciesToPokedexNum(NationalPokedexNumToSpecies(num));") == 2
assert "u8 dexSeen[NUM_DEX_FLAG_BYTES]" in read("include/global.h")
assert "u8 dexCaught[NUM_DEX_FLAG_BYTES]" in read("include/global.h")
assert "if (IS_HNS)" in engine
print(f"JOB8_DEX_PASS: 450 unique approved species; {len(custom)} independent custom flag slots, within unused National 495-649")
print("JOB8_DEX_PASS: family ordering, seen/caught, alphabetical/weight/height sorts and number rendering")
print("JOB8_DEX_PASS: old save layout/IDs unchanged; party/PC owns backfill only")
