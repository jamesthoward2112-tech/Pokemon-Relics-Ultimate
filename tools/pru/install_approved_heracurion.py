#!/usr/bin/env python3
"""Install the user-approved relic Heracurion battle artwork after PRL sync."""
from __future__ import annotations

import hashlib
import shutil
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "assets/pru_final_polish/heracurion"
GRAPHICS = ROOT / "graphics/pokemon"
DESTINATIONS = [
    GRAPHICS / "prl_authoritative/heracurion",
    GRAPHICS / "pjr_locked/heracurion",
]
EXPECTED_SHA256 = {
    "front.png": "3534c7dc5f271add3448e51557410b013b0cb103bf72acdf73d1774aa715bb6f",
    "back.png": "9e115d56be6e17eafbb3043be65917bff1a9b15ccdf6c64947426e9349c8e3bc",
    "icon.png": "cc45d6300468299bdd9e7f95844e527f04c5adc9d2e5925bad1279294353d382",
    "normal.pal": "62093becf5f80b875b2a97b344c4d6c030a2639123b6762db1a24052528ef688",
    "shiny.pal": "62093becf5f80b875b2a97b344c4d6c030a2639123b6762db1a24052528ef688",
}

def colors_from_jasc(path: Path) -> list[tuple[int, int, int]]:
    rows = path.read_text().splitlines()
    assert rows[:3] == ["JASC-PAL", "0100", "16"], path
    colors = [tuple(int(v) for v in row.split()) for row in rows[3:19]]
    assert len(colors) == 16 and all(len(c) == 3 for c in colors), path
    return colors

def recolor_icon_to_shared_palette(source: Path, shared_palette: Path) -> Image.Image:
    with Image.open(source) as im:
        im.load()
        assert im.mode == "P" and im.size == (32, 64)
        raw = list(im.getdata())
        # Pixel index zero is the source's transparent colour.
        rgba = list(im.convert("RGBA").getdata())
    dest_colors = colors_from_jasc(shared_palette)
    out = Image.new("P", (32, 64), 0)
    remapped = []
    for index, color in zip(raw, rgba):
        if index == 0:
            remapped.append(0)
            continue
        rgb = color[:3]
        remapped.append(min(range(1, 16), key=lambda i: sum((rgb[k] - dest_colors[i][k]) ** 2 for k in range(3))))
    out.putdata(remapped)
    palette = [v for c in dest_colors for v in c]
    out.putpalette(palette + [0] * (768 - len(palette)))
    out.info["transparency"] = 0
    return out

def install() -> None:
    for name, expected in EXPECTED_SHA256.items():
        raw = (SOURCE / name).read_bytes()
        if name.endswith(".pal"):
            # Repository .gitattributes may check palettes out as CRLF on the runner.
            raw = raw.replace(b"\r\n", b"\n")
        assert hashlib.sha256(raw).hexdigest() == expected, name

    donor_colors = colors_from_jasc(SOURCE / "normal.pal")
    for side in ("front", "back"):
        with Image.open(SOURCE / f"{side}.png") as im:
            im.load()
            assert im.mode == "P" and im.size == (64, 64), side
            assert max(im.getdata()) < 16, side
            flat = im.getpalette()
            for i in set(im.getdata()):
                assert tuple(flat[3 * i:3 * i + 3]) == donor_colors[i], (side, i)

    icon = recolor_icon_to_shared_palette(
        SOURCE / "icon.png", GRAPHICS / "icon_palettes/pal2.pal"
    )
    for destination in DESTINATIONS:
        destination.mkdir(parents=True, exist_ok=True)
        for side in ("front", "back"):
            with Image.open(SOURCE / f"{side}.png") as im:
                im.info["transparency"] = 0
                im.save(destination / f"{side}.png")
        shutil.copyfile(SOURCE / "normal.pal", destination / "normal.pal")
        shutil.copyfile(SOURCE / "shiny.pal", destination / "shiny.pal")
        icon.save(destination / "icon.png", optimize=False)
        assert Image.open(destination / "icon.png").mode == "P"
    print("PASS: approved Heracurion relic artwork installed after PRL sync (front/back/icon/palettes)")

if __name__ == "__main__":
    install()
