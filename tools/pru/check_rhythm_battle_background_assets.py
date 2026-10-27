#!/usr/bin/env python3
"""Validate every source-exact, BG3-safe Rhythm background in PRU."""

import json
from pathlib import Path

from import_rhythm_battle_backgrounds import decode_lz77, visible_rgb_sha256

ROOT = Path(__file__).resolve().parents[2]
ASSETS = ROOT / "graphics/battle_environment/rhythm"
MANIFEST = ROOT / "assets/pru_rhythm/background_manifest.json"


def main():
    manifest = json.loads(MANIFEST.read_text())
    assert manifest["donor_entries"] == 55
    assert manifest["unique_visual_sets"] == 44
    assert manifest["unique_visible_sets"] == 43
    entries = manifest["entries"]
    assert [x["index"] for x in entries] == list(range(55))

    for entry in entries:
        number = f'{entry["index"]:02d}'
        directory = ASSETS / number
        tiles_lz = (directory / "tiles.4bpp.lz").read_bytes()
        map_lz = (directory / "tilemap.bin.lz").read_bytes()
        palette = (directory / "palette_48colors.gbapal").read_bytes()
        assert len(tiles_lz) % 4 == len(map_lz) % 4 == 0, number
        tiles = decode_lz77(tiles_lz)
        tilemap = decode_lz77(map_lz)
        assert 0 < len(tiles) <= 20480, (number, len(tiles))
        assert len(tilemap) == 4096, number
        assert len(palette) == 96, number
        assert max((int.from_bytes(tilemap[k:k+2], "little") & 1023)
                   for k in range(0, len(tilemap), 2)) < len(tiles) // 32, number
        assert visible_rgb_sha256(tiles, tilemap, palette) == entry["visible_sha256"], number

    duplicate_groups = manifest["duplicate_groups"]
    assert len(duplicate_groups) == 11
    # Rhythm 00 and 33 have the same 240x160 scene but differ offscreen.
    assert len({x["visible_sha256"] for x in entries}) == 43
    assert len(list(ASSETS.glob("[0-9][0-9]"))) == 55
    print("PASS: all 55 Rhythm GBA backgrounds decode, fit VRAM and retain exact visible pixels")


if __name__ == "__main__":
    main()
