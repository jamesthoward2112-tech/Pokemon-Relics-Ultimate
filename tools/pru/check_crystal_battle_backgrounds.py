#!/usr/bin/env python3
"""Validate all 38 original Crystal Redux GBA battle-background payloads."""
from pathlib import Path
import re

base = Path("graphics/battle_environment/crystal_redux")
art = Path("src/graphics.c").read_text()
code = Path("src/battle_bg.c").read_text()
gfx = Path("src/data/pru_crystal_gfx.h").read_text()
table = Path("src/data/pru_crystal_bg_table.h").read_text()

assert '#include "data/pru_crystal_gfx.h"' in art
assert '#include "data/pru_crystal_bg_table.h"' in code
assert "GetPruCrystalBattleBgIndex(GetBattleEnvironmentOverride())" in code
assert "DecompressDataWithHeaderVram(bg->tiles" in code
assert "DecompressDataWithHeaderVram(bg->tilemap" in code
assert "LoadPalette(bg->palette" in code

for i in range(38):
    n = f"{i:02d}"
    for name, expected_uncompressed in [
        ("tiles.4bpp.lz", None),
        ("tilemap.bin.lz", 4096),
        ("entry_tiles.4bpp.lz", None),
        ("entry_tilemap.bin.lz", 896),
    ]:
        data = (base / n / name).read_bytes()
        assert data[0] == 0x10, (n, name, "not LZ77")
        assert len(data) % 4 == 0, (n, name, "not 4-byte aligned")
        expanded = int.from_bytes(data[1:4], "little")
        assert 0 < expanded <= 16384
        if expected_uncompressed is not None:
            assert expanded == expected_uncompressed, (n, name, expanded)
    assert len((base / n / "palette_48colors.gbapal").read_bytes()) == 96
    for field in ("gPruCrystalTiles_", "gPruCrystalMap_", "gPruCrystalPal_"):
        assert (field + n) in gfx, (field, n)
        assert (field + n) in table, (field, n)

# Every indexed environment must have an ordinary encounter mapping or leader.
n_by_env = set()
for group in ("Grass", "Water", "Cave", "Rock", "Ice", "Urban", "Special"):
    match = re.search(r"sPruCrystal" + group + r"\[\] = \{([^}]*)\}", code)
    assert match, group
    n_by_env.update(map(int, re.findall(r"\d+", match.group(1))))
assert n_by_env == set(range(38)), sorted(set(range(38)) - n_by_env)

leaders = {
    "FALKNER": 35, "BUGSY": 1, "WHITNEY": 17, "MORTY": 19,
    "CHUCK": 31, "JASMINE": 18, "PRYCE": 6, "CLAIR": 36,
    "BROCK": 7, "MISTY": 32, "LTSURGE": 14, "ERIKA": 9,
    "JANINE": 12, "SABRINA": 8, "BLAINE": 33, "BLUE": 10,
}
assert len(set(leaders.values())) == 16
for leader, idx in leaders.items():
    assert re.search(r"case TRAINER_" + leader + r"(?:_\w+)?_HNS: return " + str(idx) + r";", code), leader

# Prevent regression to PRL's double-entry panorama/seam.
entry = code.split("void DrawBattleEntryBackground(void)", 1)[1].split("bool8 LoadChosenBattleElement", 1)[0]
assert "gPruCrystal" not in entry, "donor entry panels must not be displayed"
print("PASS: all 38 Crystal Redux GBA backgrounds, distinct Gym Leaders, safe intro loading")
