#!/usr/bin/env python3
"""Validate the dedicated Job 18 pre-Guardian save fixture."""
from pathlib import Path
import hashlib
import json
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/pru"))
from check_sprite_qa_save import active_sectors, DATA_SIZE, STORAGE_SIZE, SIGNATURE, PERM

SAVE = Path(sys.argv[1]) if len(sys.argv) > 1 else ROOT / "assets/test_saves/PRU_Job18_Before_Ancient_Guardian.sav"
raw = SAVE.read_bytes()
assert len(raw) == 0x20000, f"expected 128 KiB SRAM save, got {len(raw)}"

slots = []
for base in (0, 14):
    rows = {}
    physical = {}
    counters = set()
    for index in range(base, base + 14):
        sector = raw[index * 0x1000:(index + 1) * 0x1000]
        sid, _, signature, counter = struct.unpack_from("<HHII", sector, 0xFF4)
        if signature == SIGNATURE and sid < 14:
            rows[sid] = sector
            physical[sid] = index
            counters.add(counter)
    if len(rows) == 14 and len(counters) == 1:
        slots.append((next(iter(counters)), rows, physical))
assert len(slots) == 2, "expected both intact GBA save slots"
counter, rows, _ = max(slots, key=lambda x: x[0])

# These HNS sizes and offsets are read from the compiled ROM's GFRomHeader.
# SaveBlock1 is 15,760 bytes, so sector 4 contains the remaining 3,856 bytes.
SAVEBLOCK2_SIZE = 3892
SAVEBLOCK1_SIZE = 15760
SAVEBLOCK1_FLAGS_OFFSET = 0x198C
SAVEBLOCK1_VARS_OFFSET = 0x1ABC
PARTY_COUNT_OFFSET = 0x238
PARTY_OFFSET = 0x23C
sizes = {0: SAVEBLOCK2_SIZE, 1: DATA_SIZE, 2: DATA_SIZE, 3: DATA_SIZE, 4: SAVEBLOCK1_SIZE - 3 * DATA_SIZE}
for sid in range(5, 14):
    sizes[sid] = min(DATA_SIZE, max(0, STORAGE_SIZE - (sid - 5) * DATA_SIZE))
for _, slot_rows, _ in slots:
    for sid, sector in slot_rows.items():
        chunk = sector[:sizes[sid]]
        words = struct.unpack("<" + "I" * (len(chunk) // 4), chunk)
        total = sum(words) & 0xFFFFFFFF
        expected = ((total >> 16) + total) & 0xFFFF
        actual = struct.unpack_from("<H", sector, 0xFF6)[0]
        assert actual == expected, f"slot sector {sid}: checksum {actual:#x}, expected {expected:#x}"

sb1 = b"".join(rows[i][:DATA_SIZE] for i in range(1, 4)) + rows[4][:sizes[4]]
groups = json.loads((ROOT / "data/maps/map_groups.json").read_text())
map_group = list(groups).index("gMapGroup_Dungeons_Hns")
map_num = groups["gMapGroup_Dungeons_Hns"].index("TinTower_RoofDay_hns")
assert struct.unpack_from("<bbbxhh", sb1, 0x04) == (map_group, map_num, -1, 10, 13)
assert struct.unpack_from("<H", sb1, 0)[0] == 6, "SaveBlock1 version is not current"
assert sb1[PARTY_COUNT_OFFSET] == 6

flags = sb1[SAVEBLOCK1_FLAGS_OFFSET:]
def flag(value):
    return bool(flags[value // 8] & (1 << (value % 8)))

assert flag(0x89F) and flag(0x941), "Champion and Elite 20 prerequisites missing"
assert all(flag(value) for value in range(0x8CB, 0x8D2)), "one or more RELICS missing"
assert not any(flag(value) for value in (0x94F, 0x950, 0x8D4, 0x23C)), "Guardian/Ho-Oh event already resolved"
assert not flag(0x07E) and flag(0x03D), "Kimono Girls/legacy Ho-Oh visibility flags incorrect"
assert struct.unpack_from("<H", sb1, SAVEBLOCK1_VARS_OFFSET + (0x405E - 0x4000) * 2)[0] == 0

species_ids = range(1578, 1584)
for i, expected_species in enumerate(species_ids):
    mon = sb1[PARTY_OFFSET + i * 100:PARTY_OFFSET + (i + 1) * 100]
    pid, otid = struct.unpack_from("<II", mon)
    secure = bytearray()
    for off in range(32, 80, 4):
        secure += struct.pack("<I", struct.unpack_from("<I", mon, off)[0] ^ (pid ^ otid))
    assert (sum(struct.unpack("<24H", secure)) & 0xFFFF) == struct.unpack_from("<H", mon, 0x1C)[0]
    block = PERM[0][pid % 24] * 12
    species = struct.unpack_from("<H", secure, block)[0] & 0x7FF
    experience = struct.unpack_from("<I", secure, block + 4)[0]
    assert species == expected_species, (i, species)
    assert experience == 60 ** 3, (i, experience)
    hp, max_hp = struct.unpack_from("<HH", mon, 0x56)
    assert mon[0x54] == 60 and 0 < hp == max_hp, (i, mon[0x54], hp, max_hp)

medicine = 0x564 + (236 + 60 + 39 + 160 + 66) * 4
healing = [struct.unpack_from("<HH", sb1, medicine + 4 * i) for i in range(4)]
assert healing == [(30, 20), (33, 10), (31, 5), (34, 5)], healing
print(f"PASS: valid 128 KiB dual-slot save; latest counter {counter}; all sector and Pokémon checksums")
print("PASS: Tin Tower (10,13), Champion + Elite 20 + seven RELICS; Dragonite/Ho-Oh/finale flags unresolved")
print("PASS: six healthy level-60 party members and 40 healing items")
