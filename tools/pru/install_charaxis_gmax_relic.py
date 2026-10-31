#!/usr/bin/env python3
"""Install the authentic G-Max Charizard silhouette as PRU Charaxis (black Relic palette).

Runs after PRL sprite sync, which otherwise overwrites Charaxis with its old Mega
asset. This is a graphics-only substitution: no Mega/G-Max mechanic is enabled.
"""
from __future__ import annotations

from pathlib import Path
from PIL import Image

ROOT = Path("graphics/pokemon")
SRC = ROOT / "charizard" / "gmax"
DST = ROOT / "prl_authoritative" / "charaxis"
FILES = ("front.png", "back.png", "icon.png")


def load_palette(path: Path) -> list[tuple[int, int, int]]:
    lines = path.read_text().splitlines()
    assert lines[:3] == ["JASC-PAL", "0100", "16"], (path, lines[:3])
    result = [tuple(map(int, line.split())) for line in lines[3:19]]
    assert len(result) == 16 and all(len(row) == 3 for row in result)
    return result


def save_palette(path: Path, palette: list[tuple[int, int, int]]) -> None:
    assert len(palette) == 16
    path.write_text("JASC-PAL\n0100\n16\n" +
                    "\n".join(f"{r} {g} {b}" for r, g, b in palette) + "\n")


def install() -> None:
    DST.mkdir(parents=True, exist_ok=True)
    for name in FILES:
        source = SRC / name
        assert source.is_file(), f"Missing authentic G-Max sprite: {source}"
        with Image.open(source) as img:
            assert img.size[0] <= 64 and img.size[1] <= 64, (
                f"Charaxis must fit GBA battle/icon dimensions: {source} {img.size}"
            )
            if name in ("front.png", "back.png"):
                assert img.size == (64, 64), (source, img.size)
            assert img.mode in ("P", "RGBA"), (source, img.mode)
        (DST / name).write_bytes(source.read_bytes())

    # G-Max original shiny palette supplies the charcoal-coloured body and
    # uncompromised blazing orange/yellow flames. Deepen body greys to match
    # the user-supplied ancient Charaxis artwork; do not recolour flame indices.
    normal = load_palette(SRC / "shiny.pal")
    normal[6] = (25, 25, 28)     # shadowed scales / near-black
    normal[7] = (70, 70, 75)     # illuminated charcoal
    normal[8] = (43, 41, 44)     # dark armour
    normal[11] = (111, 102, 93)  # warm ash highlight
    normal[13] = (23, 23, 28)    # deepest shadow
    # Original bright-orange G-Max remains the rare shiny alternate colourway.
    shiny = load_palette(SRC / "normal.pal")
    save_palette(DST / "normal.pal", normal)
    save_palette(DST / "shiny.pal", shiny)

    # Protect G-Max against the upstream pinned PRL asset sync on future builds.
    assert (DST / "front.png").read_bytes() == (SRC / "front.png").read_bytes()
    assert (DST / "back.png").read_bytes() == (SRC / "back.png").read_bytes()
    assert normal[5] == (16, 16, 16)
    assert normal[1:5] == load_palette(SRC / "normal.pal")[1:5]
    print("Charaxis: authentic G-Max front/back/icon; black scales + orange fire")


if __name__ == "__main__":
    install()
