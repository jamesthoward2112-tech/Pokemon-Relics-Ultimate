#!/usr/bin/env python3
"""Restore approved Infinity sprite pixels after PRL sync; report shiny gaps.

This uses the *checked-in*, pinned PJR Infinity donor archive, not scraped art.
No species IDs, gameplay data, save flags or previously normalized icons change.
The original Infinity pack contains front/back PNGs only, not authentic shiny
variants. Report that gap rather than making up replacement shiny colours.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
DONOR = Path("/tmp/pjr-infinity-assets")
DEST = ROOT / "graphics/pokemon/prl_authoritative"
REPORT = ROOT / "PRU-QA/infinity-sprite-cleanup.json"

# Confirmed contents of the approved zipped donor embedded in this repository.
# Later PRL-only additions (Eeveeon, Nimbeon, Drakeon, Miltitan) are not
# present in this archive. Never substitute a guessed source for those species.
INFINITY_ARCHIVE = (
    "champeon", "guardeon", "lepideon", "obsideon",
    "omeon", "sphynxeon", "toxeon", "mootiny",
)
OTHER_PRL = ("eeveeon", "nimbeon", "drakeon", "miltitan", "shuckolosse")
ALL_REVIEWED = (*INFINITY_ARCHIVE, *OTHER_PRL)


def donor_image(path: Path) -> tuple[list[int], list[tuple[int, int, int]]]:
    with Image.open(path) as pic:
        assert pic.mode == "P" and pic.size == (64, 64), (path, pic.mode, pic.size)
        palette = pic.getpalette()
        assert palette is not None and len(palette) >= 48, path
        values = list(pic.getdata())
        assert max(values) < 16, (path, max(values))
        rgb = [tuple(palette[3 * k:3 * k + 3]) for k in range(16)]
    assert any(k for k in values), f"Empty donor sprite: {path}"
    return values, rgb


def write_indexed(path: Path, indices: list[int], colors: list[tuple[int, int, int]]):
    img = Image.new("P", (64, 64))
    img.putpalette([c for rgb in colors for c in rgb] + [0] * (768 - 3 * len(colors)))
    img.putdata(indices)
    img.info["transparency"] = 0
    path.parent.mkdir(parents=True, exist_ok=True)
    img.save(path, optimize=False)


def write_palette(path: Path, colors: list[tuple[int, int, int]]):
    assert len(colors) == 16
    path.write_text(
        "JASC-PAL\n0100\n16\n"
        + "\n".join("{} {} {}".format(*c) for c in colors) + "\n"
    )


def apply_one(name: str) -> dict:
    origin = DONOR / name
    dst = DEST / name
    data = [donor_image(origin / (side + ".png")) for side in ("front", "back")]
    # Each GBA species has ONE 16-colour normal palette for both perspectives.
    # Reindex by *exact RGB*, never by nearest-neighbour colour replacement.
    colors = [(0, 0, 0)]
    for values, table in data:
        for idx in values:
            if idx and table[idx] not in colors:
                colors.append(table[idx])
    if len(colors) > 16:
        # Avoid silently losing original outline/detail shades. Caller reports
        # this honestly; current approved artwork remains in place.
        raise ValueError(f"{name}: {len(colors)-1} nontransparent colours, GBA maximum 15")
    colors += [(0, 0, 0)] * (16 - len(colors))
    lookup = {rgb: i for i, rgb in enumerate(colors) if i}
    for side, (indices, table) in zip(("front", "back"), data):
        converted = [0 if i == 0 else lookup[table[i]] for i in indices]
        write_indexed(dst / (side + ".png"), converted, colors)
    write_palette(dst / "normal.pal", colors)
    # This donor zip has NO shiny assets. Existing PRL shiny palettes are
    # identical to normal, so don't synthesize and mislabel a fake Infinity
    # shiny; use neutral duplicate pending authentic source images.
    write_palette(dst / "shiny.pal", colors)
    return {
        "name": name, "source": "pinned PJR Infinity archive",
        "front_sha256": hashlib.sha256((dst / "front.png").read_bytes()).hexdigest(),
        "back_sha256": hashlib.sha256((dst / "back.png").read_bytes()).hexdigest(),
        "normal_palette_sha256": hashlib.sha256((dst / "normal.pal").read_bytes()).hexdigest(),
        "shiny": "MISSING AUTHENTIC DONOR; still uses normal colours",
        "icon": "unchanged: existing GBA party palette normalization retained",
        "colors": len(set(colors[1:]) - {(0, 0, 0)}),
    }


def main():
    if not DONOR.is_dir():
        raise SystemExit("Pinned original Infinity donor folder missing; restore it first")
    if not DEST.is_dir():
        raise SystemExit("PRL sync must run BEFORE Infinity sprite cleanup")
    entries = []
    for name in INFINITY_ARCHIVE:
        try:
            entries.append(apply_one(name))
        except (ValueError, AssertionError) as exc:
            entries.append({"name": name, "source": "existing PRL fallback",
                            "error": str(exc), "shiny": "UNVERIFIED"})
    for name in OTHER_PRL:
        root = DEST / name
        assert all((root / file).is_file() for file in (
            "front.png", "back.png", "icon.png", "normal.pal", "shiny.pal"
        )), name
        entries.append({"name": name, "source": "pinned PRL, NOT Infinity archive",
                        "shiny": "needs authentic source verification",
                        "icon": "unchanged"})
    REPORT.parent.mkdir(parents=True, exist_ok=True)
    REPORT.write_text(json.dumps({
        "purpose": "original-pixel donor restore and transparent shiny gap audit",
        "species": entries,
        "preserved": ["existing party icons", "original sprite scale",
                       "species IDs", "Pokedex", "saves", "Ruins of Alph"],
        "source_reference": "https://p-infinity.fandom.com/wiki/Guardeon",
    }, indent=2) + "\n")
    print("PRU Infinity original sprite audit: {} checked".format(len(entries)))
    for entry in entries:
        print("SPRITE", entry["name"], entry["source"], entry.get("error", ""),
              "| shiny:", entry["shiny"])
    print("NOTE: authentic shiny palette/source retrieval remains outstanding.")


if __name__ == "__main__":
    main()
