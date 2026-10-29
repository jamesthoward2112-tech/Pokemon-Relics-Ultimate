#!/usr/bin/env python3
"""Colour vanilla Mewtwo's six overworld frames as Mewduo, without redrawing."""

from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
BASE = ROOT / "assets/mewduo_mewtwo_base_overworld.png"
TARGET = ROOT / "graphics/pokemon/mewsion/overworld.png"
PALETTE = ROOT / "graphics/pokemon/mewsion/normal.pal"

# Vanilla Mewtwo's purple tail/lower belly becomes dark-to-bright red.
# Grey/lilac body shades become the existing Mewduo battle palette's whites.
# Using the same palette as its battle art avoids consuming another OBJ palette.
INDEX_MAP = {
    0: 0,   # transparent background
    1: 2,   # medium-dark grey
    2: 10,  # black outline
    3: 3,   # white highlight
    4: 12,  # charcoal outline
    5: 4,   # very light body grey
    6: 5,   # body shadow
    7: 6,   # red shadow on tail and lower belly
    8: 1,   # mid-grey shadow
    9: 7,   # dark red outline
    10: 9,  # red highlight
}


def main() -> None:
    base = Image.open(BASE)
    if base.mode != "P" or base.size != (192, 32):
        raise ValueError("Mewtwo reference must be an indexed six-frame 192x32 sheet")

    colours = [tuple(map(int, line.split())) for line in PALETTE.read_text().splitlines()[3:19]]
    if len(colours) != 16:
        raise ValueError("Mewduo palette must contain exactly sixteen colours")
    source_indices = list(base.getdata())
    if set(source_indices) != set(INDEX_MAP):
        raise ValueError("Unexpected vanilla Mewtwo palette indexes; source art changed")

    output = Image.new("P", base.size)
    output.putpalette([channel for colour in colours for channel in colour] + [0] * (768 - 48))
    output.putdata([INDEX_MAP[pixel] for pixel in source_indices])
    output.save(TARGET, format="PNG", transparency=0, optimize=False)
    print(f"Wrote {TARGET.relative_to(ROOT)}: six original Mewtwo frames, recoloured")


if __name__ == "__main__":
    main()
