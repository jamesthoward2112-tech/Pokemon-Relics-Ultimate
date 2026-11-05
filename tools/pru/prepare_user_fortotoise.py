#!/usr/bin/env python3
"""Prepare Fortotoise's user-supplied G-Max Blastoise battle art.

The front is a nearest-neighbour 64x64 reduction of the PR72-approved
back-facing G-Max Blastoise artwork (mirrored for the requested orientation). The
back uses exactly its top 70 percent, reduced to 64 pixels wide and grounded
inside a 64x64 frame. Both pictures share the source's original colours.
"""
from __future__ import annotations

from collections import Counter
import hashlib
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSET = ROOT / "assets/pru_final_polish/fortotoise"
USER_SOURCE_SHA256 = "86ee4553eeb7b64ee6441d11786395a5256d5dea8e1d89aa092d4409a21a12a4"


def colors_from_source(image: Image.Image) -> list[tuple[int, int, int]]:
    rgba = image.convert("RGBA")
    frequencies = Counter((r, g, b) for r, g, b, a in rgba.getdata() if a)
    colors = [color for color, _ in frequencies.most_common()]
    assert len(colors) <= 15, f"GBA needs at most 15 opaque colours; source has {len(colors)}"
    return [(0, 0, 0), *colors] + [(0, 0, 0)] * (15 - len(colors))


def indexed(image: Image.Image, colors: list[tuple[int, int, int]]) -> Image.Image:
    rgba = image.convert("RGBA")
    lookup = {color: i for i, color in enumerate(colors) if i and color != (0, 0, 0)}
    # Keep a real black artwork pixel if present even though palette slot zero
    # is reserved as the GBA transparency colour.
    black_slots = [i for i, color in enumerate(colors) if i and color == (0, 0, 0)]
    if black_slots:
        lookup[(0, 0, 0)] = black_slots[0]
    pixels = []
    for r, g, b, a in rgba.getdata():
        if not a:
            pixels.append(0)
        else:
            pixels.append(lookup[(r, g, b)])
    out = Image.new("P", rgba.size, 0)
    out.putdata(pixels)
    out.putpalette([v for c in colors for v in c] + [0] * (768 - 48))
    out.info["transparency"] = 0
    return out


def save_palette(path: Path, colors: list[tuple[int, int, int]]) -> None:
    path.write_text("JASC-PAL\n0100\n16\n" + "\n".join(
        f"{r} {g} {b}" for r, g, b in colors
    ) + "\n")


def main() -> None:
    source_path = ASSET / "source_front.png"
    assert hashlib.sha256(source_path.read_bytes()).hexdigest() == USER_SOURCE_SHA256, (
        "Fortotoise source changed; re-review before converting it"
    )
    with Image.open(source_path) as original:
        source = original.convert("RGBA")
    assert source.size == (96, 96), (source_path, source.size)
    assert source.getchannel("A").getbbox() is not None
    colors = colors_from_source(source)
    ASSET.mkdir(parents=True, exist_ok=True)

    front = source.resize((64, 64), Image.Resampling.NEAREST)
    indexed(front, colors).save(ASSET / "front.png", optimize=False)

    crop_height = round(source.height * 0.70)
    crop = source.crop((0, 0, source.width, crop_height))
    crop.save(ASSET / "back_source_crop.png", optimize=False)
    back_width = 64
    back_height = round(crop.height * back_width / crop.width)
    reduced_back = crop.resize((back_width, back_height), Image.Resampling.NEAREST)
    back_canvas = Image.new("RGBA", (64, 64), (0, 0, 0, 0))
    back_canvas.alpha_composite(reduced_back, ((64 - back_width) // 2, 62 - back_height))
    indexed(back_canvas, colors).save(ASSET / "back.png", optimize=False)
    save_palette(ASSET / "normal.pal", colors)

    with Image.open(ROOT / "graphics/pokemon/blastoise/mega/icon.png") as icon:
        assert icon.mode == "P" and icon.size == (32, 64)
        icon.load()
        icon.info["transparency"] = 0
        icon.save(ASSET / "icon.png", optimize=False)

    # The approved build retains its previously pinned shiny palette; the
    # supplied art pack's duplicate shiny colours are not an authentic shiny.
    with Image.open(ASSET / "front.png") as check:
        assert check.mode == "P" and check.size == (64, 64)
        assert max(check.getdata()) < 16 and check.info.get("transparency") == 0
    with Image.open(ASSET / "back.png") as check:
        assert check.mode == "P" and check.size == (64, 64)
        assert max(check.getdata()) < 16 and check.info.get("transparency") == 0
    with Image.open(ASSET / "icon.png") as check:
        assert check.mode == "P" and check.size == (32, 64)
    print("FORTOTOISE: supplied G-Max Blastoise front, top-70%-crop back, Mega Blastoise icon; shared 16-colour GBA palette")


if __name__ == "__main__":
    main()
