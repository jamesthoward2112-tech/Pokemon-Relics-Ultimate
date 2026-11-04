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
    """Build a compact icon from the approved charcoal battle front using palette #6."""
    battle = load_palette(DST / "normal.pal")
    # The indexed battle art uses the shared normal palette written above.
    with Image.open(DST / "front.png") as indexed:
        indexed.load()
        rgba = indexed.copy()
        rgba.putpalette([component for color in battle for component in color] + [0] * (768 - 48))
        rgba.info["transparency"] = 0
        rgba = rgba.convert("RGBA")
    bounds = rgba.getchannel("A").getbbox()
    assert bounds, "empty Charaxis front art"
    crop = rgba.crop(bounds)
    scale = min(30 / crop.width, 30 / crop.height)
    size = (max(1, round(crop.width * scale)), max(1, round(crop.height * scale)))
    sprite = crop.resize(size, Image.Resampling.NEAREST)
    frame = Image.new("RGBA", (32, 32), (0, 0, 0, 0))
    frame.alpha_composite(sprite, ((32 - size[0]) // 2, 31 - size[1]))
    icon = Image.new("RGBA", (32, 64), (0, 0, 0, 0))
    icon.alpha_composite(frame, (0, 0))
    icon.alpha_composite(frame, (0, 32))
    target = icon_palette_6()
    result = Image.new("P", (32, 64), 0)
    indices = []
    for r, g, b, a in icon.getdata():
        if not a:
            indices.append(0)
            continue
        source = tuple(round(c * 31 / 255) for c in (r, g, b))
        index = min(range(1, 16), key=lambda i: sum(
            (source[c] - round(target[i][c] * 31 / 255)) ** 2 for c in range(3)
        ))
        indices.append(index)
    result.putdata(indices)
    result.putpalette([component for color in target for component in color] + [0] * (768 - 48))
    result.info["transparency"] = 0
    result.save(DST / "icon.png", optimize=False)


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
        assert new in info, "Charaxis icon palette must be #6"

    # Protect G-Max against the upstream pinned PRL asset sync on future builds.
    assert (DST / "front.png").read_bytes() == (SRC / "front.png").read_bytes()
    assert (DST / "back.png").read_bytes() == (SRC / "back.png").read_bytes()
    assert normal[5] == (16, 16, 16)
    assert normal[1:5] == load_palette(SRC / "normal.pal")[1:5]
    with Image.open(DST / "icon.png") as icon:
        assert icon.mode == "P" and icon.size == (32, 64) and icon.info.get("transparency") == 0
    print("Charaxis: authentic G-Max front/back/icon; black scales + orange fire")


if __name__ == "__main__":
    install()
