#!/usr/bin/env python3
"""Prepare PR72-style Fortotoise front and the genuine PRL Mercury donor back.

The G-Max fortress-shell front is preserved unchanged. The separate original
64x64 PRL donor back is palette-snapped to the same GBA 16-colour bank without
resizing, mirroring, cropping, or changing any visible/transparent pixels.
"""
from __future__ import annotations

from collections import Counter
import hashlib
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSET = ROOT / "assets/pru_final_polish/fortotoise"
USER_SOURCE_SHA256 = "86ee4553eeb7b64ee6441d11786395a5256d5dea8e1d89aa092d4409a21a12a4"
PRL_BACK_SOURCE_SHA256 = "4c9b04650c8c174846e533b09caf1e6e9dcaab590324f3a34c485712e2cc6e49"


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


def match_donor_back_palette(donor: Image.Image, colors: list[tuple[int, int, int]]) -> Image.Image:
    """Map PRL's near-identical BGR555 colours to the front's indexed palette.

    Keep the original 64x64 back-view pixels and transparency exactly in place.
    An unexpected colour fails instead of being silently mis-recoloured.
    """
    original = donor.convert("RGBA")
    assert original.size == (64, 64), original.size
    palette = colors[1:]
    lookup: dict[tuple[int, int, int], tuple[int, int, int]] = {}
    converted = []
    for r, g, b, alpha in original.getdata():
        if alpha == 0:
            converted.append((0, 0, 0, 0))
            continue
        key = (r, g, b)
        if key not in lookup:
            distance, position = min(
                (sum((key[channel] - colour[channel]) ** 2 for channel in range(3)), i)
                for i, colour in enumerate(palette)
            )
            assert distance <= 100, f"Unexpected PRL back colour: {key}"
            lookup[key] = palette[position]
        converted.append((*lookup[key], 255))
    result = Image.new("RGBA", original.size, (0, 0, 0, 0))
    result.putdata(converted)
    assert list(original.getchannel("A").getdata()) == list(result.getchannel("A").getdata())
    return result

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

    # This is PRL's independent back battle sprite, not a crop of the front.
    back_source_path = ASSET / "source_back.png"
    assert hashlib.sha256(back_source_path.read_bytes()).hexdigest() == PRL_BACK_SOURCE_SHA256, (
        "Fortotoise's approved PRL donor back changed; re-review before converting"
    )
    with Image.open(back_source_path) as original_back:
        donor_back = original_back.convert("RGBA")
    assert donor_back.size == (64, 64), donor_back.size
    remapped_back = match_donor_back_palette(donor_back, colors)
    indexed(remapped_back, colors).save(ASSET / "back.png", optimize=False)
    save_palette(ASSET / "normal.pal", colors)

    # User-selected Pokésprite Gigantamax Blastoise icon. Never replace this
    # with Mega Blastoise during CI; keep the approved two-frame GBA candidate.
    source_icon = ASSET / "pokesprite_gmax_icon_GBA_pal3.png"
    with Image.open(source_icon) as icon:
        assert icon.mode == "P" and icon.size == (32, 64)
        assert icon.info.get("transparency") == 0
        assert max(icon.getdata()) < 16
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
    print("FORTOTOISE: existing PR72 fortress front and PRL back preserved; Pokésprite G-Max icon (palette 3) prepared")


if __name__ == "__main__":
    main()
