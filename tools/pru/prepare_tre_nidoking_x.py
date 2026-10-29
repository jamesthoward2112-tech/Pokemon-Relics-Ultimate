#!/usr/bin/env python3
"""Extract the unused TRE Nidoking-X (907) pose from the archived variant sheet.

Usage: python3 tools/pru/prepare_tre_nidoking_x.py variants_tre.png output.png
The user-owned reference sheet lives outside git; only GBA-compatible art ships.
"""

from pathlib import Path
import sys

from PIL import Image


def main(source: Path, destination: Path):
    with Image.open(source) as picture:
        if picture.size != (960, 375):
            raise ValueError("Unexpected TRE Nidoking variants sheet dimensions")
        # Three columns: normal Nidoking, Nidoking-X (907), Nidogod (910).
        # Blue exclusively gets the middle sprite; Giovanni keeps Nidogod.
        art = picture.convert("RGB").crop((320, 0, 640, 315))

    rgba = Image.new("RGBA", art.size, (0, 0, 0, 0))
    src, dst = art.load(), rgba.load()
    for y in range(art.height):
        for x in range(art.width):
            color = src[x, y]
            if color != (35, 35, 38):
                dst[x, y] = (*color, 255)
    bounds = rgba.getbbox()
    if bounds is None:
        raise ValueError("The Nidoking-X portion of the sprite sheet is empty")
    rgba = rgba.crop(bounds)
    ratio = min(60 / rgba.width, 60 / rgba.height)
    dimensions = (round(rgba.width * ratio), round(rgba.height * ratio))
    rgba = rgba.resize(dimensions, Image.Resampling.NEAREST)
    frame = Image.new("RGBA", (64, 64), (0, 0, 0, 0))
    frame.alpha_composite(rgba, ((64 - dimensions[0]) // 2, 64 - dimensions[1] - 1))
    flat = Image.new("RGB", frame.size, (255, 255, 255))
    flat.paste(frame, mask=frame.getchannel("A"))
    indexed = flat.quantize(colors=15, method=Image.Quantize.MEDIANCUT, dither=Image.Dither.NONE)
    pal = indexed.getpalette()[:45]
    out = Image.new("P", (64, 64), 0)
    out.putpalette([0, 0, 0] + pal + [0] * (768 - 3 - len(pal)))
    target, source_colors = out.load(), indexed.load()
    alpha = frame.getchannel("A").load()
    for y in range(64):
        for x in range(64):
            if alpha[x, y] >= 128:
                target[x, y] = source_colors[x, y] + 1
    out.info["transparency"] = 0
    destination.parent.mkdir(parents=True, exist_ok=True)
    out.save(destination, optimize=True)
    print(f"TRE Nidoking-X: {bounds=} -> {dimensions}, {len(set(out.getdata()))} palette indices")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        raise SystemExit(__doc__)
    main(Path(sys.argv[1]), Path(sys.argv[2]))
