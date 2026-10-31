#!/usr/bin/env python3
"""Install the five approved final-polish sprite donors after PRL synchronisation."""
from __future__ import annotations

import shutil
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / "assets/pru_final_polish"
POKEMON = ROOT / "graphics/pokemon"

DESTINATIONS = {
    "fortotoise": POKEMON / "prl_authoritative/fortotoise",
    "torkaldera": POKEMON / "prl_authoritative/torkaldera",
    "tropisaur": POKEMON / "prl_authoritative/tropisaur",
    "armaldo": POKEMON / "armaldo",
    "cradily": POKEMON / "cradily",
}
ICON_PALETTES = {
    "fortotoise": 2,
    "torkaldera": 1,
    "tropisaur": 1,
    "armaldo": 0,
    "cradily": 0,
}


def load_jasc(path: Path) -> list[tuple[int, int, int]]:
    lines = path.read_text().splitlines()
    assert lines[:3] == ["JASC-PAL", "0100", "16"], path
    colors = [tuple(map(int, line.split())) for line in lines[3:19]]
    assert len(colors) == 16 and all(len(color) == 3 for color in colors), path
    return colors


def save_jasc(path: Path, colors: list[tuple[int, int, int]]) -> None:
    assert len(colors) == 16
    path.write_text(
        "JASC-PAL\n0100\n16\n"
        + "\n".join(f"{red} {green} {blue}" for red, green, blue in colors)
        + "\n"
    )


def indexed_from_rgba(
    image: Image.Image, colors: list[tuple[int, int, int]], *, nearest: bool
) -> Image.Image:
    rgba = image.convert("RGBA")
    out = Image.new("P", rgba.size, 0)
    flat: list[int] = []
    for red, green, blue, alpha in rgba.getdata():
        if alpha == 0:
            flat.append(0)
            continue
        rgb = (red, green, blue)
        if nearest:
            index = min(
                range(1, 16),
                key=lambda item: sum((rgb[channel] - colors[item][channel]) ** 2 for channel in range(3)),
            )
        else:
            index = colors.index(rgb)
        flat.append(index)
    out.putdata(flat)
    palette = [component for color in colors for component in color]
    out.putpalette(palette + [0] * (768 - len(palette)))
    out.info["transparency"] = 0
    return out


def exact_battle_palette(species: str) -> list[tuple[int, int, int]]:
    colors: list[tuple[int, int, int]] = [(0, 0, 0)]
    for name in ("front.png", "back.png"):
        with Image.open(SRC / species / name) as image:
            for red, green, blue, alpha in image.convert("RGBA").getdata():
                rgb = (red, green, blue)
                if alpha and rgb not in colors:
                    colors.append(rgb)
    assert len(colors) <= 16, (species, len(colors))
    return colors + [(0, 0, 0)] * (16 - len(colors))


def make_icon_source(species: str) -> Image.Image:
    donor = SRC / species / "icon.png"
    if donor.is_file():
        with Image.open(donor) as icon:
            return icon.convert("RGBA")

    with Image.open(SRC / species / "front.png") as front:
        rgba = front.convert("RGBA")
    alpha = rgba.getchannel("A")
    box = alpha.getbbox()
    assert box is not None, species
    cropped = rgba.crop(box)
    scale = min(30 / cropped.width, 30 / cropped.height)
    size = (max(1, round(cropped.width * scale)), max(1, round(cropped.height * scale)))
    reduced = cropped.resize(size, Image.Resampling.NEAREST)
    frame = Image.new("RGBA", (32, 32), (0, 0, 0, 0))
    frame.alpha_composite(reduced, ((32 - size[0]) // 2, 31 - size[1]))
    icon = Image.new("RGBA", (32, 64), (0, 0, 0, 0))
    icon.alpha_composite(frame, (0, 0))
    icon.alpha_composite(frame, (0, 32))
    return icon


def install() -> None:
    for species, destination in DESTINATIONS.items():
        destination.mkdir(parents=True, exist_ok=True)
        source = SRC / species

        if species in {"armaldo", "cradily"}:
            battle_palette = exact_battle_palette(species)
            for side in ("front", "back"):
                with Image.open(source / f"{side}.png") as image:
                    installed = indexed_from_rgba(image, battle_palette, nearest=False)
                installed.save(destination / f"{side}.png", optimize=False)
            save_jasc(destination / "normal.pal", battle_palette)
            save_jasc(destination / "shiny.pal", battle_palette)
        else:
            for side in ("front", "back"):
                shutil.copyfile(source / f"{side}.png", destination / f"{side}.png")
            shutil.copyfile(source / "normal.pal", destination / "normal.pal")
            shiny = source / "shiny.pal"
            shutil.copyfile(shiny if shiny.is_file() else source / "normal.pal", destination / "shiny.pal")

        icon_palette = load_jasc(POKEMON / "icon_palettes" / f"pal{ICON_PALETTES[species]}.pal")
        icon = indexed_from_rgba(make_icon_source(species), icon_palette, nearest=True)
        assert icon.size == (32, 64) and max(icon.getdata()) < 16
        icon.save(destination / "icon.png", optimize=False)

        for side in ("front", "back"):
            with Image.open(destination / f"{side}.png") as image:
                assert image.size == (64, 64) and max(image.getdata()) < 16, (species, side)

    print("Installed approved Fortotoise, Tortemple, Brontonana and Odyssey II fossil sprites")


if __name__ == "__main__":
    install()
