"""Import Giovanni-only GBA battle graphics from James's exact TRE donor banks.

Usage:
    python3 tools/pru/import_tre_giovanni_relic_sprites.py \
      --additional TRE_2026_Additional_Finds_Extracted.zip \
      --extended TRE_Johto_Extended_Custom_Sprite_Bank.zip

Only the enemy trainer's battle art changes. Species, Pokédex and party art
remain untouched. Donor RGB pixels are preserved in indexed PNG form.
"""

import argparse
from hashlib import sha256
from pathlib import Path
from zipfile import ZipFile
from io import BytesIO

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / "graphics/pokemon/giovanni_relic"
SOURCES = {
    "aerodactyl": ("additional", "912_Aerodactyl-Skeleton/front_normal.png", "7170396edfe298c9084789f7af23edb231cdd32f0d84f8f5ba0d770b5d84668d"),
    "kabutops": ("additional", "951_Kabutops-Skeleton/front_normal.png", "c9d0f63ddeaa41db6aa3b2fcab95c54ddd6e70db8489574d876c9782814317c2"),
    "rhyperior": ("extended", "0936_Rhyper&_front.png", "233b804d988d188dcea9f75a8f12aa4da4a87748581925170ee0e9099c2d47b6"),
}


def load(zip_file: ZipFile, basename: str) -> bytes:
    candidates = [name for name in zip_file.namelist() if name.endswith("/" + basename)]
    if len(candidates) != 1:
        raise ValueError(f"Expected exactly one TRE sprite {basename}, got {len(candidates)}")
    return zip_file.read(candidates[0])


def convert_png(source: bytes, output_png: Path, output_pal: Path) -> None:
    original = Image.open(BytesIO(source)).convert("RGBA")
    if original.size != (64, 64):
        raise ValueError(f"Expected 64x64 TRE battle sprite, got {original.size}")
    unique = sorted({(r, g, b) for r, g, b, a in original.get_flattened_data() if a})
    if len(unique) > 15:
        raise ValueError(f"GBA 4bpp supports only 15 visible colors, got {len(unique)}")
    colors = [(0, 0, 0), *unique, *([(0, 0, 0)] * (15 - len(unique)))]
    indexed = Image.new("P", original.size)
    indexed.putpalette([channel for rgb in colors for channel in rgb] + [0] * (768 - 48))
    positions = {rgb: i + 1 for i, rgb in enumerate(unique)}
    indexed.putdata([0 if not a else positions[(r, g, b)] for r, g, b, a in original.get_flattened_data()])
    indexed.info["transparency"] = 0
    indexed.save(output_png)
    output_pal.write_text("JASC-PAL\n0100\n16\n" + "\n".join(f"{r} {g} {b}" for r, g, b in colors) + "\n")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--additional", type=Path, required=True)
    parser.add_argument("--extended", type=Path, required=True)
    args = parser.parse_args()

    DEST.mkdir(parents=True, exist_ok=True)
    with ZipFile(args.additional) as additional, ZipFile(args.extended) as extended:
        banks = {"additional": additional, "extended": extended}
        for name, (bank, member, expected_digest) in SOURCES.items():
            original = load(banks[bank], member)
            if sha256(original).hexdigest() != expected_digest:
                raise ValueError(f"The source TRE art was modified: {member}")
            (DEST / f"{name}_source_front.png").write_bytes(original)
            convert_png(original, DEST / f"{name}_front.png", DEST / f"{name}_normal.pal")
            print(f"Imported TRE {member} for Giovanni's {name}")


if __name__ == "__main__":
    main()
