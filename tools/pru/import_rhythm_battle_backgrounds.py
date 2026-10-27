#!/usr/bin/env python3
"""Import Pokémon Rhythm's 55 LZ77 battle scenes into PRU's static BG3.

The source is the artist-authorised, user-provided Rhythm extraction. Importing
only the visible 30×20 tiles preserves every on-screen pixel and guarantees the
tiles fit before BG3's screenblock 26 (20 KiB past character block 2).
"""

import argparse
from hashlib import sha256
import json
from pathlib import Path
from struct import pack, unpack_from

ROOT = Path(__file__).resolve().parents[2]
TARGET = ROOT / "graphics/battle_environment/rhythm"
MANIFEST = ROOT / "assets/pru_rhythm/background_manifest.json"


def decode_lz77(data: bytes) -> bytes:
    if not data or data[0] != 0x10 or len(data) < 4:
        raise ValueError("GBA LZ77 header required")
    target = int.from_bytes(data[1:4], "little")
    output = bytearray()
    offset = 4
    while len(output) < target:
        flags = data[offset]
        offset += 1
        for bit in range(7, -1, -1):
            if flags & (1 << bit):
                lead, trail = data[offset:offset+2]
                offset += 2
                span = (lead >> 4) + 3
                distance = ((lead & 15) << 8 | trail) + 1
                if distance > len(output):
                    raise ValueError("Invalid GBA LZ77 back-reference")
                for _ in range(min(span, target - len(output))):
                    output.append(output[-distance])
            else:
                output.append(data[offset])
                offset += 1
            if len(output) >= target:
                break
    return bytes(output)


def encode_lz77(data: bytes) -> bytes:
    """Use hardware-compatible literal blocks; the ROM build needs no compressor."""
    if not 0 < len(data) < (1 << 24):
        raise ValueError("GBA LZ77 data length is out of range")
    output = bytearray(b"\x10" + len(data).to_bytes(3, "little"))
    for start in range(0, len(data), 8):
        output.append(0)  # eight uncompressed literals, no invalid VRAM spans
        output.extend(data[start:start+8])
    output.extend(b"\x00" * (-len(output) % 4))
    assert decode_lz77(output) == data
    return bytes(output)


def visible_rgb_sha256(tiles: bytes, tilemap: bytes, palette: bytes) -> str:
    """Hash actual RGB pixels shown in PRU's stationary 240×160 viewport."""
    if len(tilemap) != 4096 or len(palette) != 96:
        raise ValueError("Battle map must be 4096 bytes with 48 colours")
    colors = []
    for pos in range(0, 96, 2):
        value = unpack_from("<H", palette, pos)[0]
        colors.append(bytes(((component * 255 + 15) // 31 for component in
                             (value & 31, (value >> 5) & 31, (value >> 10) & 31))))
    frame = bytearray(240 * 160 * 3)
    for ty in range(20):
        for tx in range(30):
            word = unpack_from("<H", tilemap, 2 * (ty * 32 + tx))[0]
            tile_id = word & 1023
            palette_bank = word >> 12
            base = tile_id * 32
            if base + 32 > len(tiles):
                raise ValueError("Tilemap exceeds character tile data")
            for py in range(8):
                sy = 7-py if word & 0x800 else py
                for px in range(8):
                    sx = 7-px if word & 0x400 else px
                    packed = tiles[base + sy*4 + sx//2]
                    color = (packed >> 4) if (sx & 1) else (packed & 15)
                    color_idx = (palette_bank - 2)*16 + color
                    if not 0 <= color_idx < 48:
                        raise ValueError("Palette index outside imported BG palette")
                    dest = 3 * ((ty*8+py)*240 + tx*8+px)
                    frame[dest:dest+3] = colors[color_idx]
    return sha256(frame).hexdigest()


def repack_visible_tiles(tiles: bytes, tilemap: bytes) -> tuple[bytes, bytes]:
    """Drop tiles that PRU's static, zero-scrolled viewport cannot display."""
    if len(tilemap) != 4096 or len(tiles) % 32:
        raise ValueError("Invalid 4bpp background input")
    new_tiles = bytearray(32)  # visible tile ID 0 is reserved for offscreen fill
    remap = {}
    new_map = bytearray(pack("<H", 0x2000) * 2048)
    for y in range(20):
        for x in range(30):
            at = 2*(y*32+x)
            word = unpack_from("<H", tilemap, at)[0]
            original_id = word & 1023
            if original_id * 32 + 32 > len(tiles):
                raise ValueError("Donor tilemap exceeds tile data")
            if original_id not in remap:
                remap[original_id] = len(new_tiles)//32
                new_tiles.extend(tiles[original_id*32:original_id*32+32])
            new_map[at:at+2] = pack("<H", (word & ~1023) | remap[original_id])
    if len(new_tiles) > 20480:
        raise ValueError(f"BG3 VRAM tile overflow: {len(new_tiles)}")
    return bytes(new_tiles), bytes(new_map)


def import_assets(source: Path) -> dict:
    TARGET.mkdir(parents=True, exist_ok=True)
    groups = {}
    entries = []
    for i in range(55):
        label = f"{i:02d}"
        directory = source / label
        donor_tiles = decode_lz77((directory / "tiles.4bpp.lz").read_bytes())
        donor_map = decode_lz77((directory / "tilemap.bin.lz").read_bytes())
        palette = decode_lz77((directory / "palette_48colors.gbapal.lz").read_bytes())
        original_hash = visible_rgb_sha256(donor_tiles, donor_map, palette)
        unique_hash = sha256(donor_tiles + donor_map + palette).hexdigest()
        groups.setdefault(unique_hash, []).append(i)
        tiles, tilemap = repack_visible_tiles(donor_tiles, donor_map)
        if visible_rgb_sha256(tiles, tilemap, palette) != original_hash:
            raise ValueError(f"Visible pixels changed for Rhythm {label}")
        output = TARGET / label
        output.mkdir(parents=True, exist_ok=True)
        (output / "tiles.4bpp.lz").write_bytes(encode_lz77(tiles))
        (output / "tilemap.bin.lz").write_bytes(encode_lz77(tilemap))
        (output / "palette_48colors.gbapal").write_bytes(palette)
        entries.append({"index": i, "original_sha256": unique_hash,
                        "visible_sha256": original_hash, "decompressed_tiles": len(tiles)})
    duplicates = [g for g in groups.values() if len(g) > 1]
    manifest = {
        "source": "Pokémon Rhythm v1.0.0 user-authorised UPS extraction",
        "source_ups_crc32": "5eb94b0c",
        "source_patched_rom_crc32": "51625488",
        "donor_entries": 55,
        "unique_visual_sets": len(groups),
        "unique_visible_sets": len({x["visible_sha256"] for x in entries}),
        "duplicate_groups": sorted(duplicates, key=lambda g: g[0]),
        "entries": entries,
    }
    if len(groups) != 44 or len(duplicates) != 11:
        raise ValueError("Unexpected donor asset identity or table count")
    MANIFEST.parent.mkdir(parents=True, exist_ok=True)
    MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--source-dir", type=Path, required=True,
                        help="Existing Rhythm extraction with 00..54/raw LZ77 asset directories")
    args = parser.parse_args()
    result = import_assets(args.source_dir)
    print(f"Imported {result['donor_entries']} Rhythm backgrounds ({result['unique_visual_sets']} unique) with verified 240×160 pixels")
