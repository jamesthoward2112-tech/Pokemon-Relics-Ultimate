#!/usr/bin/env python3
"""Create a dedicated, checksum-correct 128 KiB PRU Eeveelutions test .sav.
Reuses existing level-50 normal/shiny boxed Pokémon without altering personal saves.
"""
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "assets/test_saves/Pru.sav"
OUTPUT = Path("PRU_Eeveelutions_PC_Test.sav")
SECTOR, DATA = 0x1000, 3968
STORAGE_SIZE, SIGNATURE = 0x8560, 0x08012025
BOX3 = 4 + 2 * 30 * 80
IDS = (1638, 1578, 1583, 1637, 1580, 1579, 1600, 1584, 1581, 1582)
PERM0 = [0,0,0,0,0,0,1,1,2,3,2,3,1,1,2,3,2,3,1,1,2,3,2,3]

def checksum(chunk):
    words = struct.unpack("<" + "I"*(len(chunk)//4), chunk)
    total = sum(words) & 0xffffffff
    return ((total >> 16) + total) & 0xffff

def find_slots(data):
    slots = []
    for base in (0, 14):
        ids = {}
        counters = set()
        for physical in range(base, base + 14):
            sid, _, sig, count = struct.unpack_from("<HHII", data, physical*SECTOR+0xff4)
            if sid < 14 and sig == SIGNATURE:
                ids[sid] = physical
                counters.add(count)
        if len(ids) == 14 and len(counters) == 1:
            slots.append(ids)
    assert slots, "No valid save slot"
    return slots

def species_from_record(record):
    pid, otid = struct.unpack_from("<II", record)
    assert record[19] == 2
    key = pid ^ otid
    secure = bytearray().join(struct.pack("<I",
        struct.unpack_from("<I", record, off)[0] ^ key)
        for off in range(32, 80, 4))
    assert (sum(struct.unpack("<24H", secure)) & 65535) == struct.unpack_from("<H",record,28)[0]
    sid = struct.unpack_from("<H", secure, PERM0[pid%24]*12)[0] & 0x7ff
    shiny = ((pid & 65535) ^ (pid>>16) ^ (otid & 65535) ^ (otid>>16)) < 8
    return sid, shiny

def main():
    raw = bytearray(SOURCE.read_bytes())
    assert len(raw) == 0x20000
    for ids in find_slots(raw):
        sizes = [DATA]*8 + [STORAGE_SIZE - DATA*8]
        storage = bytearray().join(raw[ids[sid]*SECTOR:ids[sid]*SECTOR+sizes[sid-5]]
                                      for sid in range(5,14))
        assert len(storage) == STORAGE_SIZE
        lookup = {}
        for pos in range(30):
            record = bytes(storage[BOX3+pos*80:BOX3+(pos+1)*80])
            if any(record):
                sid, shiny = species_from_record(record)
                lookup[(sid,shiny)] = record
        assert all((sid,shiny) in lookup for sid in IDS for shiny in (False,True)), "Missing Eeveelution save fixture"
        storage[0] = 2  # PC Box 3
        for slot in range(30):
            start = BOX3 + slot*80
            storage[start:start+80] = bytes(80)
        for shiny in (False, True):
            for idx, sid in enumerate(IDS):
                slot = idx + (10 if shiny else 0)
                start = BOX3 + slot * 80
                storage[start:start+80] = lookup[(sid,shiny)]
        # Game character codes A=0xBB; title 'EEVEELUT'.
        storage[0x8344+2*9:0x8344+2*9+9] = bytes(
            [0xbf,0xbf,0xd0,0xbf,0xbf,0xc6,0xcf,0xce,0xff])
        offset = 0
        for sid in range(5,14):
            physical = ids[sid] * SECTOR
            size = sizes[sid-5]
            chunk = storage[offset:offset+size]
            raw[physical:physical+size] = chunk
            struct.pack_into("<H", raw, physical+0xff6, checksum(chunk))
            offset += size
        assert offset == STORAGE_SIZE
    OUTPUT.write_bytes(raw)
    for ids in find_slots(raw):
        sizes = [DATA]*8 + [STORAGE_SIZE-DATA*8]
        storage = b"".join(raw[ids[sid]*SECTOR:ids[sid]*SECTOR+sizes[sid-5]] for sid in range(5,14))
        assert storage[0] == 2
        for ix, sid in enumerate(IDS):
            for shiny, slot in ((False,ix),(True,ix+10)):
                rec = storage[BOX3+80*slot:BOX3+80*(slot+1)]
                assert species_from_record(rec) == (sid,shiny)
        for sid in range(5,14):
            physical = ids[sid]*SECTOR
            size = sizes[sid-5]
            assert checksum(raw[physical:physical+size]) == struct.unpack_from("<H",raw,physical+0xff6)[0]
    print("PASS: 10 level-50 Eeveelutions + 10 shinies in Box 3 EEVEELUT; checksum-valid .sav")

if __name__ == "__main__":
    main()
