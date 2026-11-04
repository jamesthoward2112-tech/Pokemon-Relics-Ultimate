#!/usr/bin/env python3
"""Ensure the reviewed icon snapshots match the fully installed approved assets."""
from __future__ import annotations

import re
from pathlib import Path

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
        assert expected.read_bytes() == actual.read_bytes(), (
            f"{symbol} installed icon differs from its explicitly approved review snapshot; inspect and update the pin"
        )
    print(f"PASS: all {len(SYMBOLS)} reviewed icon snapshots match the post-install source tree")


if __name__ == "__main__":
    main()
