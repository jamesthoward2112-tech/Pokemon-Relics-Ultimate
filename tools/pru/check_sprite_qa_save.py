#!/usr/bin/env python3
"""Validate the released PRU sprite QA save and its Box 3 contents."""
from pathlib import Path
import struct
import sys

SECTOR = 0x1000
DATA_SIZE = 3968
SIGNATURE = 0x08012025
STORAGE_SIZE = 0x8560
BOX_OFFSET = 4 + 2 * 30 * 80
SPECIES = [
    ("Champeon", 1578), ("Lepideon", 1579), ("Guardeon", 1580),
    ("Obsideon", 1581), ("Toxeon", 1582), ("Sphynxeon", 1583),
    ("Omeon", 1584), ("Drakeon", 1600), ("Eeveeon", 1637),
    ("Nimbeon", 1638), ("Mootiny", 1577), ("Miltitan", 1593),
]
PERM = [
    [0,0,0,0,0,0,1,1,2,3,2,3,1,1,2,3,2,3,1,1,2,3,2,3],
    [1,1,2,3,2,3,0,0,0,0,0,0,2,3,1,1,3,2,2,3,1,1,3,2],
    [2,3,1,1,3,2,2,3,1,1,3,2,0,0,0,0,0,0,3,2,3,2,1,1],
    [3,2,3,2,1,1,3,2,3,2,1,1,3,2,3,2,1,1,0,0,0,0,0,0],
]

def fail(message):
    raise SystemExit(f"FAIL: {message}")

def checksum(data):
    total = sum(struct.unpack("<" + "I" * (len(data) // 4), data[:len(data)//4*4])) & 0xFFFFFFFF
    return ((total >> 16) + total) & 0xFFFF

def active_sectors(data):
    valid = []
    for base in (0, 14):
        rows = {}
        counters = set()
        for physical in range(base, base + 14):
            raw = data[physical*SECTOR:(physical+1)*SECTOR]
            sid, cksum, sig, counter = struct.unpack_from("<HHII", raw, 0xFF4)
            if sig == SIGNATURE and sid < 14:
                rows[sid] = raw
                counters.add(counter)
        if len(rows) == 14 and len(counters) == 1:
            valid.append((next(iter(counters)), rows))
    if not valid:
        fail("no complete 14-sector save slot")
    return max(valid, key=lambda x: x[0])[1]

def main(path):
    data = Path(path).read_bytes()
    if len(data) != 0x20000:
        fail(f"expected 128 KiB save, got {len(data)} bytes")
    sectors = active_sectors(data)
    sizes = [DATA_SIZE] * 8 + [STORAGE_SIZE - DATA_SIZE*8]
    storage = bytearray().join(sectors[sid][:sizes[sid-5]] for sid in range(5, 14))
    if len(storage) != STORAGE_SIZE:
        fail(f"storage size mismatch: {len(storage):#x}")
    if storage[0] != 2:
        fail(f"current box is {storage[0]+1}, expected Box 3")
    if storage[0x8344 + 2*9:0x8344 + 2*9 + 8] != bytes((205, 202, 204, 195, 206, 191, 203, 187)):
        fail("Box 3 name is not SPRITEQA")
    otid = struct.unpack_from("<I", sectors[0], 0x0A)[0]
    for p, (name, species) in enumerate(SPECIES):
        for shiny in (False, True):
            slot = p*2 + int(shiny)
            record = bytes(storage[BOX_OFFSET + slot*80:BOX_OFFSET + (slot+1)*80])
            if len(record) != 80:
                fail(f"slot {slot+1}: incomplete record")
            pid, record_otid = struct.unpack_from("<II", record, 0)
            flags = record[19]
            if flags != 0x02:
                fail(f"slot {slot+1} {name}: Bad Egg/egg/species flag state {flags:#x}")
            if record_otid != otid:
                fail(f"slot {slot+1} {name}: OT ID mismatch")
            key = pid ^ record_otid
            secure = bytearray()
            for off in range(32, 80, 4):
                secure += struct.pack("<I", struct.unpack_from("<I", record, off)[0] ^ key)
            if (sum(struct.unpack("<24H", secure)) & 0xFFFF) != struct.unpack_from("<H", record, 28)[0]:
                fail(f"slot {slot+1} {name}: Pokémon checksum mismatch")
            s0_index = PERM[0][pid % 24]
            s0 = secure[s0_index*12:(s0_index+1)*12]
            actual_species, held_item = struct.unpack_from("<HH", s0, 0)
            actual_species &= 0x7FF
            held_item &= 0x3FF
            level_exp = struct.unpack_from("<I", s0, 4)[0]
            if actual_species != species:
                fail(f"slot {slot+1} {name}: species {actual_species}, expected {species}")
            if held_item != 0:
                fail(f"slot {slot+1} {name}: held item {held_item}")
            curve = "medium_fast" if name in {"Champeon", "Lepideon", "Guardeon", "Obsideon", "Toxeon", "Sphynxeon", "Omeon", "Eeveeon", "Nimbeon"} else "slow"
            expected_exp = 50**3 if curve == "medium_fast" else (5*50**3)//4
            if level_exp != expected_exp:
                fail(f"slot {slot+1} {name}: experience {level_exp}, expected level-50 {expected_exp}")
            shiny_value = (pid & 0xFFFF) ^ (pid >> 16) ^ (otid & 0xFFFF) ^ (otid >> 16)
            if (shiny_value < 8) != shiny:
                fail(f"slot {slot+1} {name}: shiny state incorrect")
            print(f"Box 3 slot {slot+1:02}: {name:10} {'shiny' if shiny else 'normal'} level 50 item 0; species={actual_species}")
    if any(storage[BOX_OFFSET+24*80:BOX_OFFSET+30*80]):
        fail("one or more of Box 3 slots 25–30 is occupied")
    print("PASS: save structure, Box 3 name, 24 species records, shiny values, and checksums")

if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "assets/test_saves/Pru.sav")
