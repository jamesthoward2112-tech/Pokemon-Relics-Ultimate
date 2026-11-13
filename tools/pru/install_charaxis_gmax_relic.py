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


def icon_palette_6() -> list[tuple[int, int, int]]:
    code = (Path("src/pokemon_icon.c")).read_text()
    import re
    match = re.search(r"static const u16 sPRLNoxichuIconPalette\[16\]\s*=\s*\{(.*?)\};", code, re.S)
    assert match, "missing pinned dark/orange icon palette #6"
    rgb5 = [tuple(map(int, item)) for item in re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", match.group(1))]
    assert len(rgb5) == 16
    return [tuple(round(c * 255 / 31) for c in color) for color in rgb5]


def make_black_gmax_icon() -> None:
    """Use the Mega Charizard X icon with its blue accents changed to fire."""
    source_path = ROOT / "charizard" / "mega_x" / "icon.png"
    with Image.open(source_path) as source:
        assert source.mode == "P" and source.size == (32, 64), source_path
        source.load()
        indices = list(source.getdata())
    # Retain the original indexed Mega X pixels. Its 3 blue shades (8, 9, 12)
    # become burnt orange, ember and hot gold in the already assigned PRU #6
    # icon palette. Index zero remains the transparent background.
    mapping = {
        0: 0, 1: 5, 2: 4, 3: 13, 6: 12,
        8: 8, 9: 7, 12: 10, 14: 3, 15: 1,
    }
    assert set(indices) <= set(mapping), f"Unexpected Mega X icon indices: {set(indices) - set(mapping)}"
    icon = Image.new("P", (32, 64), 0)
    icon.putdata([mapping[index] for index in indices])
    target = icon_palette_6()
    icon.putpalette([component for color in target for component in color] + [0] * (768 - 48))
    icon.info["transparency"] = 0
    icon.save(DST / "icon.png", optimize=False)


def install() -> None:
    DST.mkdir(parents=True, exist_ok=True)
    for name in ("front.png", "back.png"):
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
    make_black_gmax_icon()

    # Palette #6 is the dark/ember palette already owned by PRU's custom-icon
    # palette table; it does not alter another species or shared palette data.
    species_info = Path("src/data/pokemon/species_info/pjr_families.h")
    info = species_info.read_text()
    old = "sCharizardTeachableLearnset, 600, 0, 1, 0),"
    new = "sCharizardTeachableLearnset, 600, 0, 1, 6),"
    if old in info:
        info = info.replace(old, new, 1)
        species_info.write_text(info)
    else:
        # Newer species records include Dex metadata after the icon palette.
        # Require the approved #6 rather than the old positional formatting.
        start = info.index("PJR_RED_SPECIES(SPECIES_CHARAXIS,")
        end = info.index("),", start) + 2
        charaxis = info[start:end]
        suffix = charaxis.split("sCharizardTeachableLearnset,", 1)[1]
        assert suffix.split(",")[3].strip() == "6", "Charaxis icon palette must be #6"

    # Protect G-Max against the upstream pinned PRL asset sync on future builds.
    assert (DST / "front.png").read_bytes() == (SRC / "front.png").read_bytes()
    assert (DST / "back.png").read_bytes() == (SRC / "back.png").read_bytes()
    assert normal[5] == (16, 16, 16)
    assert normal[1:5] == load_palette(SRC / "normal.pal")[1:5]
    with Image.open(DST / "icon.png") as icon:
        assert icon.mode == "P" and icon.size == (32, 64) and icon.info.get("transparency") == 0
    print("Charaxis: G-Max black/orange battle art preserved; Mega Charizard X party icon recoloured from blue to orange")


if __name__ == "__main__":
    install()
