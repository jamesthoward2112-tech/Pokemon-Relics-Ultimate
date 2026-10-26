"""Import exact TRE 2026 slot 0922 sprites without recolouring the pixels.

Usage: python3 tools/pru/import_tre_armoured_mewtwo.py /path/to/extracted/0922-assets

The input files are from TRE_Johto_Extended_Custom_Sprite_Bank.zip.
The bank is a donor: only Giovanni's trainer sprite uses this artwork.
"""

import argparse
from pathlib import Path
from shutil import copyfile

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / "graphics/pokemon/mewtwo/armoured"
STEMS = {
    "front": "0922_Mewtwo.Arm_front.png",
    "back": "0922_Mewtwo.Arm_back.png",
    "icon": "0922_Mewtwo.Arm_icon_2frames.png",
}


def pixels(image: Image.Image) -> set[tuple[int, int, int]]:
    return {(r, g, b) for r, g, b, a in image.get_flattened_data() if a}


def palette(colors: set[tuple[int, int, int]]) -> list[tuple[int, int, int]]:
    assert len(colors) <= 15, f"GBA 4bpp only permits 15 visible colours, got {len(colors)}"
    return [(0, 0, 0), *sorted(colors), *([(0, 0, 0)] * (15 - len(colors)))]


def convert(image: Image.Image, colours: list[tuple[int, int, int]], output: Path) -> None:
    index = {rgb: i for i, rgb in enumerate(colours) if i != 0}
    indexed = Image.new("P", image.size)
    indexed.putpalette([c for rgb in colours for c in rgb] + [0] * (768 - 48))
    indexed.putdata([0 if a == 0 else index[(r, g, b)] for r, g, b, a in image.get_flattened_data()])
    indexed.info["transparency"] = 0
    indexed.save(output)


def write_pal(colours: list[tuple[int, int, int]], output: Path) -> None:
    output.write_text("JASC-PAL\n0100\n16\n" + "\n".join(f"{r} {g} {b}" for r, g, b in colours) + "\n")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("donor_dir", type=Path)
    args = parser.parse_args()

    originals = {stem: args.donor_dir / filename for stem, filename in STEMS.items()}
    images = {stem: Image.open(path).convert("RGBA") for stem, path in originals.items()}
    assert images["front"].size == images["back"].size == (64, 64)
    assert images["icon"].size == (32, 64)
    battle_colors = palette(pixels(images["front"]) | pixels(images["back"]))
    icon_colors = palette(pixels(images["icon"]))

    OUT.mkdir(parents=True, exist_ok=True)
    for stem, source in originals.items():
        copyfile(source, OUT / f"source_{stem}.png")
        convert(images[stem], battle_colors if stem != "icon" else icon_colors, OUT / f"{stem}.png")
    write_pal(battle_colors, OUT / "normal.pal")
    write_pal(icon_colors, OUT / "icon.pal")

    print(f"Imported authentic TRE 0922 Armoured Mewtwo: {OUT}")


if __name__ == "__main__":
    main()
