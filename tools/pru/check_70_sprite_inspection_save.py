#!/usr/bin/env python3
"""Validate the preserved 70-species, non-shiny inspection save without editing it."""
from pathlib import Path
import hashlib
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/pru"))
from check_sprite_qa_save import active_sectors, DATA_SIZE, STORAGE_SIZE, PERM, SECTOR, SIGNATURE

EXPECTED_SHA256 = "bd3f85d9288ba342434c9c602508480d94a7fe5132f2c292bb60e0a83097699c"
EXPECTED_COUNTS = (10, 21, 22, 17)
BOX_START = 4


def main(path: str = "assets/test_saves/PRU-70-Sprite-Inspection.sav") -> None:
    data = Path(path).read_bytes()
    assert len(data) == 0x20000, f"expected 128 KiB, got {len(data)}"
    sha = hashlib.sha256(data).hexdigest()
    assert sha == EXPECTED_SHA256, f"preserved inspection save changed: {sha}"
    sectors = active_sectors(data)
    sizes = [DATA_SIZE] * 8 + [STORAGE_SIZE - DATA_SIZE * 8]
    storage = bytearray().join(sectors[sid][:sizes[sid - 5]] for sid in range(5, 14))
    assert len(storage) == STORAGE_SIZE
    total = []
    for box, count in enumerate(EXPECTED_COUNTS):
        names = []
        for slot in range(30):
            start = BOX_START + (box * 30 + slot) * 80
            record = bytes(storage[start:start + 80])
            if not any(record):
                continue
            pid, otid = struct.unpack_from("<II", record, 0)
            assert record[19] == 0x02, f"Box {box+1} slot {slot+1}: invalid Pokémon flags"
            key = pid ^ otid
            secure = bytearray()
            for off in range(32, 80, 4):
                secure += struct.pack("<I", struct.unpack_from("<I", record, off)[0] ^ key)
            assert (sum(struct.unpack("<24H", secure)) & 0xFFFF) == struct.unpack_from("<H", record, 28)[0], f"Box {box+1} slot {slot+1}: checksum"
            block = PERM[0][pid % 24]
            species = struct.unpack_from("<H", secure, block * 12)[0] & 0x7FF
            shiny = ((pid & 0xFFFF) ^ (pid >> 16) ^ (otid & 0xFFFF) ^ (otid >> 16)) < 8
            assert not shiny, f"Box {box+1} slot {slot+1}: unexpected shiny"
            names.append(species)
        assert len(names) == count, f"Box {box+1}: expected {count}, found {len(names)}"
        total.extend(names)
    assert set(total) == set(range(1573, 1643)), "save does not contain each custom species ID 1573–1642 exactly once"
    assert len(total) == len(set(total)) == 70
    print(f"PASS: original inspection save unchanged (sha256 {sha}); 70 valid unique normal-colour records in 4 PC boxes")


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "assets/test_saves/PRU-70-Sprite-Inspection.sav")
