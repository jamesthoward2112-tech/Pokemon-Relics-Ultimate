#!/usr/bin/env python3
"""Validate video reference snapshots and the live post-installer icons."""
from __future__ import annotations

import re
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
SYMBOLS = (
    "Nimbeon", "Drakeon", "Champeon", "Guardeon", "Toxeon", "Sphynxeon",
    "Skarmet", "Kablowfish", "Grimfowl", "Heracurion", "Scarabub",
    "Skarmadon", "Jollibird", "Osteodian", "Sunflorid", "Sudowarden",
    "Mystynx", "Ghoulbat", "Khang", "Fortotoise", "Charaxis", "HoOhRelic",
    "Hitmonlee", "Alakazam", "Gemlin", "Gemigoyle", "Astrachi", "Adnokana",
    "Cheauking", "Frytning", "Mewsion", "Tropisaur", "Coelossus", "Cactomb",
    "Torkaldera", "Sceptitan", "Solaziken",
)


def main() -> None:
    graphics = {}
    pattern = re.compile(r'gMonIcon_(\w+)\[\]\s*=\s*INCBIN_U\d+\("([^\"]+)\.4bpp(?:\.smol)?"\)')
    for header in (ROOT / "src/data/graphics/pjr.h", ROOT / "src/data/graphics/pru_pokemon.h"):
        for symbol, rel in pattern.findall(header.read_text()):
            graphics[symbol] = ROOT / (rel + ".png")
    graphics.setdefault("Hitmonlee", ROOT / "graphics/pokemon/hitmonlee/icon.png")
    graphics.setdefault("Alakazam", ROOT / "graphics/pokemon/alakazam/icon.png")
    for symbol in SYMBOLS:
        expected = ROOT / "assets/pru_video_review/icons" / f"{symbol}.png"
        actual = graphics[symbol]
        assert expected.is_file() and actual.is_file(), (symbol, expected, actual)
        # The active image comes from the full ordered installer pipeline.
        # Keep snapshots for visual comparison, but never replace a newer
        # approved installer result with stale snapshot bytes.
        with Image.open(expected) as reference, Image.open(actual) as installed:
            assert reference.size == installed.size == (32, 64), (symbol, reference.size, installed.size)
            assert reference.mode in {"P", "RGBA"} and installed.mode in {"P", "RGBA"}, (symbol, reference.mode, installed.mode)
            if installed.mode == "P":
                assert max(installed.getdata()) < 16, symbol
    print(f"PASS: all {len(SYMBOLS)} video icon references and live post-install assets are valid GBA frames")


if __name__ == "__main__":
    main()
