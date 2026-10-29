#!/usr/bin/env python3
"""Turn James's supplied Elm pixel-art screenshot into a GBA 64x64 front pic.

Usage: python3 tools/pru/prepare_professor_elm_front.py reference.jpg output.png
The output is checked into PRU; the private original screenshot is not.
"""

from collections import deque
from pathlib import Path
import sys

from PIL import Image


def main(source: Path, destination: Path):
    with Image.open(source) as original:
        # The screenshot includes large black letterboxes. Isolate the white
        # reference panel that surrounds the already-drawn pixel sprite.
        panel = original.convert("RGB").crop((65, 420, 550, 1122))

    width, height = panel.size
    pixels = panel.load()
    outside = bytearray(width * height)
    queue = deque()

    def near_white(x, y):
        r, g, b = pixels[x, y]
        return min(r, g, b) >= 241 and max(r, g, b) - min(r, g, b) <= 16

    def seed(x, y):
        index = y * width + x
        if not outside[index] and near_white(x, y):
            outside[index] = 1
            queue.append((x, y))

    for x in range(width):
        seed(x, 0)
        seed(x, height - 1)
    for y in range(height):
        seed(0, y)
        seed(width - 1, y)
    while queue:
        x, y = queue.popleft()
        for xx, yy in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)):
            if 0 <= xx < width and 0 <= yy < height:
                seed(xx, yy)

    rgba = Image.new("RGBA", panel.size, (0, 0, 0, 0))
    rgba_pixels = rgba.load()
    for y in range(height):
        for x in range(width):
            if not outside[y * width + x]:
                rgba_pixels[x, y] = (*pixels[x, y], 255)

    box = rgba.getbbox()
    if box is None:
        raise ValueError("Elm was not found in the supplied sprite image")
    elm = rgba.crop(box)
    scale = min(60 / elm.width, 62 / elm.height)
    size = (round(elm.width * scale), round(elm.height * scale))
    elm = elm.resize(size, Image.Resampling.LANCZOS)
    rgba = Image.new("RGBA", (64, 64), (0, 0, 0, 0))
    rgba.alpha_composite(elm, ((64 - size[0]) // 2, 64 - size[1]))

    # Reserve palette index 0 for transparency; use the remaining 15 GBA
    # colours for Elm's glasses, hair, coat, blue top, trousers and shoes.
    opaque = Image.new("RGB", (64, 64), (255, 255, 255))
    opaque.paste(rgba, mask=rgba.getchannel("A"))
    quantized = opaque.quantize(colors=15, method=Image.Quantize.MEDIANCUT, dither=Image.Dither.NONE)
    palette = quantized.getpalette()[:45]
    output = Image.new("P", (64, 64), 0)
    output.putpalette([0, 0, 0] + palette + [0] * (768 - 3 - len(palette)))
    raw = output.load()
    qraw = quantized.load()
    alpha = rgba.getchannel("A").load()
    for y in range(64):
        for x in range(64):
            if alpha[x, y] >= 128:
                raw[x, y] = qraw[x, y] + 1
    output.info["transparency"] = 0
    destination.parent.mkdir(parents=True, exist_ok=True)
    output.save(destination, optimize=True)
    print(f"Elm: {box=} -> {size}, {len(set(output.getdata()))} GBA palette indices, {destination}")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        raise SystemExit(__doc__)
    main(Path(sys.argv[1]), Path(sys.argv[2]))
