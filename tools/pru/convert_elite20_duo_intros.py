#!/usr/bin/env python3
"""Package approved 3:1 Elite 20 duo banners as letterboxed 4bpp GBA BG0 art."""
import argparse
from pathlib import Path

from PIL import Image

from tools.pru.convert_duo_entrances import convert_image


def build_entrances(steven_may: Path, silver_giovanni: Path, output: Path) -> dict[str, int]:
    output.mkdir(parents=True, exist_ok=True)
    sizes = {}
    for name, source in (("steven_may", steven_may), ("silver_giovanni", silver_giovanni)):
        with Image.open(source) as image:
            asset = convert_image(image, preserve_aspect=True)
        for extension, contents in (("4bpp", asset.tiles), ("bin", asset.tilemap), ("gbapal", asset.palette)):
            (output / f"{name}.{extension}").write_bytes(contents)
        asset.preview.save(output / f"{name}_preview.png", optimize=True)
        sizes[name] = asset.tile_count
    return sizes


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("steven_may", type=Path)
    parser.add_argument("silver_giovanni", type=Path)
    parser.add_argument("--output", type=Path, default=Path("graphics/battle_transitions/prl"))
    arguments = parser.parse_args()
    for name, count in build_entrances(arguments.steven_may, arguments.silver_giovanni, arguments.output).items():
        print(f"{name}: 240x160 letterbox, {count}/512 tiles, 15 colours")


if __name__ == "__main__":
    main()
