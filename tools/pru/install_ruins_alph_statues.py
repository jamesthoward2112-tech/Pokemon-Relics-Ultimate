#!/usr/bin/env python3
"""Install the approved Ruins of Alph statue art and clear only their old tiles."""

from pathlib import Path
import struct

from PIL import Image, ImageDraw, ImageOps


ROOT = Path(__file__).resolve().parents[2]
ART = ROOT / "assets/pru"
PICS = ROOT / "graphics/object_events/pics/misc"
PALS = ROOT / "graphics/object_events/palettes"


def _foreground_mask(image):
    """Mark near-white background connected to the image border as transparent."""
    rgb = image.convert("RGB")
    pixels = rgb.load()
    width, height = rgb.size
    near_white = Image.new("L", rgb.size)
    out = near_white.load()
    for y in range(height):
        for x in range(width):
            r, g, b = pixels[x, y]
            out[x, y] = 255 if min(r, g, b) >= 238 and max(r, g, b) - min(r, g, b) <= 12 else 0

    # Flood-fill only border-connected white pixels. Pale carved highlights remain.
    for x in range(width):
        for y in (0, height - 1):
            if near_white.getpixel((x, y)) == 255:
                ImageDraw.floodfill(near_white, (x, y), 128, thresh=0)
    for y in range(height):
        for x in (0, width - 1):
            if near_white.getpixel((x, y)) == 255:
                ImageDraw.floodfill(near_white, (x, y), 128, thresh=0)
    return near_white.point(lambda p: 0 if p == 128 else 255)


def _install_sprite(source_name, output_name, palette_name, max_width):
    source = Image.open(ART / source_name).convert("RGB")
    mask = _foreground_mask(source)
    bounds = mask.getbbox()
    if bounds is None:
        raise ValueError(f"No statue artwork found in {source_name}")

    crop = source.crop(bounds)
    alpha = mask.crop(bounds)
    # Keep the approved portrait artwork, but fit it to the same 32x32
    # object frame as the nearby standard statues. Their visible stonework
    # is 16x32 px within the frame, so these portraits use matching bounds.
    scale = min(max_width / crop.width, 32 / crop.height)
    size = (max(1, round(crop.width * scale)), max(1, round(crop.height * scale)))
    crop = crop.resize(size, Image.Resampling.LANCZOS)
    alpha = alpha.resize(size, Image.Resampling.LANCZOS)

    # Both approved artworks are monochrome stone. Keep separate indexed palettes
    # so their colors can never be changed by sharing an object-event palette tag.
    grayscale = ImageOps.grayscale(crop)
    quantized = grayscale.quantize(colors=15, method=Image.Quantize.MEDIANCUT,
                                   dither=Image.Dither.NONE)
    used_palette = quantized.getpalette()[:45]
    indices = quantized.point(lambda index: index + 1)
    canvas = Image.new("P", (32, 32), 0)
    left = (32 - size[0]) // 2
    top = 32 - size[1]
    canvas.paste(indices, (left, top), alpha)

    palette = [0, 0, 0]
    colors = []
    for index in range(15):
        value = used_palette[index * 3]
        palette.extend((value, value, value))
        colors.append((value, value, value))
    palette.extend([0] * (768 - len(palette)))
    canvas.putpalette(palette)
    canvas.info["transparency"] = 0
    canvas.save(PICS / output_name, optimize=False)

    lines = ["JASC-PAL", "0100", "16", "0 0 0"]
    lines.extend(f"{r} {g} {b}" for r, g, b in colors)
    (PALS / palette_name).write_text("\n".join(lines) + "\n")


def _install_eye_sprite():
    """Keep the Eye's 32px silhouette and size its inscribed stand consistently."""
    source = Image.open(ART / "eye_of_alph_reference.jpg").convert("RGB")
    mask = _foreground_mask(source)
    bounds = mask.getbbox()
    if bounds is None:
        raise ValueError("No statue artwork found in eye_of_alph_reference.jpg")

    crop = source.crop(bounds)
    alpha = mask.crop(bounds)
    # The source changes from the rounded eye monolith to the rectangular
    # inscribed pedestal at this point. Fit those sections independently:
    # the portrait stays 16x20px and the matching stone base is 16x12px.
    split = 410
    body = crop.crop((0, 0, crop.width, split))
    body_alpha = alpha.crop((0, 0, alpha.width, split))
    stand_alpha = alpha.crop((0, split, alpha.width, alpha.height))
    stand_bounds = stand_alpha.getbbox()
    if stand_bounds is None:
        raise ValueError("No pedestal found in eye_of_alph_reference.jpg")
    stand = crop.crop((stand_bounds[0], split + stand_bounds[1],
                       stand_bounds[2], split + stand_bounds[3]))
    stand_alpha = stand_alpha.crop(stand_bounds)

    body = body.resize((16, 20), Image.Resampling.LANCZOS)
    body_alpha = body_alpha.resize((16, 20), Image.Resampling.LANCZOS)
    stand = stand.resize((16, 12), Image.Resampling.LANCZOS)
    stand_alpha = stand_alpha.resize((16, 12), Image.Resampling.LANCZOS)

    rgb = Image.new("RGB", (32, 32), (0, 0, 0))
    alpha_canvas = Image.new("L", (32, 32), 0)
    rgb.paste(body, (8, 0))
    alpha_canvas.paste(body_alpha, (8, 0))
    rgb.paste(stand, (8, 20))
    alpha_canvas.paste(stand_alpha, (8, 20))

    visible = alpha_canvas.getbbox()
    grayscale = ImageOps.grayscale(rgb.crop(visible))
    quantized = grayscale.quantize(colors=15, method=Image.Quantize.MEDIANCUT,
                                   dither=Image.Dither.NONE)
    used_palette = quantized.getpalette()[:45]
    indices = quantized.point(lambda index: index + 1)
    canvas = Image.new("P", (32, 32), 0)
    canvas.paste(indices, visible[:2], alpha_canvas.crop(visible))

    palette = [0, 0, 0]
    colors = []
    for index in range(15):
        value = used_palette[index * 3]
        palette.extend((value, value, value))
        colors.append((value, value, value))
    palette.extend([0] * (768 - len(palette)))
    canvas.putpalette(palette)
    canvas.info["transparency"] = 0
    canvas.save(PICS / "eye_of_alph.png", optimize=False)

    lines = ["JASC-PAL", "0100", "16", "0 0 0"]
    lines.extend(f"{r} {g} {b}" for r, g, b in colors)
    (PALS / "eye_of_alph.pal").write_text("\n".join(lines) + "\n")


def _install_alphoracle_sprite():
    """Enlarge the shrine figure while keeping its pedestal at statue scale."""
    source = Image.open(ART / "alphoracle_monolith_reference.jpg").convert("RGB")
    mask = _foreground_mask(source)
    bounds = mask.getbbox()
    if bounds is None:
        raise ValueError("No statue artwork found in alphoracle_monolith_reference.jpg")

    crop = source.crop(bounds)
    alpha = mask.crop(bounds)
    # The supplied art changes from the broad sculpted figure to its narrow
    # rectangular stand here. Scale these independently so the figure can be
    # prominent while its inscribed lower stand matches the nearby statues.
    split = 560
    body = crop.crop((0, 0, crop.width, split))
    body_alpha = alpha.crop((0, 0, crop.width, split))
    stand_alpha = alpha.crop((0, split, crop.width, crop.height))
    stand_bounds = stand_alpha.getbbox()
    stand = crop.crop((stand_bounds[0], split + stand_bounds[1],
                       stand_bounds[2], split + stand_bounds[3]))
    stand_alpha = stand_alpha.crop(stand_bounds)

    body_size = (32, max(1, round(body.height * 32 / body.width)))
    body = body.resize(body_size, Image.Resampling.LANCZOS)
    body_alpha = body_alpha.resize(body_size, Image.Resampling.LANCZOS)
    stand = stand.resize((16, 12), Image.Resampling.LANCZOS)
    stand_alpha = stand_alpha.resize((16, 12), Image.Resampling.LANCZOS)

    rgb_canvas = Image.new("RGB", (64, 64), (0, 0, 0))
    alpha_canvas = Image.new("L", (64, 64), 0)
    body_x = (64 - body_size[0]) // 2
    body_y = 64 - body_size[1] - 12
    rgb_canvas.paste(body, (body_x, body_y))
    alpha_canvas.paste(body_alpha, (body_x, body_y))
    stand_x = (64 - 16) // 2
    rgb_canvas.paste(stand, (stand_x, 52))
    alpha_canvas.paste(stand_alpha, (stand_x, 52))

    # Quantize only visible pixels; palette index zero remains transparent.
    visible = alpha_canvas.getbbox()
    grayscale = ImageOps.grayscale(rgb_canvas.crop(visible))
    quantized = grayscale.quantize(colors=15, method=Image.Quantize.MEDIANCUT,
                                   dither=Image.Dither.NONE)
    used_palette = quantized.getpalette()[:45]
    indices = quantized.point(lambda index: index + 1)
    canvas = Image.new("P", (64, 64), 0)
    canvas.paste(indices, visible[:2], alpha_canvas.crop(visible))

    palette = [0, 0, 0]
    colors = []
    for index in range(15):
        value = used_palette[index * 3]
        palette.extend((value, value, value))
        colors.append((value, value, value))
    palette.extend([0] * (768 - len(palette)))
    canvas.putpalette(palette)
    canvas.info["transparency"] = 0
    canvas.save(PICS / "alphoracle_monolith.png", optimize=False)

    lines = ["JASC-PAL", "0100", "16", "0 0 0"]
    lines.extend(f"{r} {g} {b}" for r, g, b in colors)
    (PALS / "alphoracle_monolith.pal").write_text("\n".join(lines) + "\n")


def _clear_original_statue_tiles():
    layout_path = ROOT / "data/layouts/RuinsOfAlph_B1F_hns/map.bin"
    width = 29
    layout = bytearray(layout_path.read_bytes())
    if len(layout) % (width * 2):
        raise ValueError("Unexpected Ruins of Alph B1F layout dimensions")
    values = list(struct.unpack(f"<{len(layout) // 2}H", layout))

    # Clone the source statue metatiles and clear only their foreground/BG1 half.
    tileset = ROOT / "data/tilesets/secondary/ruins_of_alph_b1_f_hns"
    meta_path = tileset / "metatiles.bin"
    attr_path = tileset / "metatile_attributes.bin"
    entries = list(struct.unpack(f"<{len(meta_path.read_bytes()) // 2}H", meta_path.read_bytes()))
    attributes = bytearray(attr_path.read_bytes())
    for original, clone in ((99, 200), (10, 201), (99, 202), (10, 203)):
        start = original * 8
        cloned = entries[start:start + 4] + [0, 0, 0, 0]
        target = clone * 8
        if len(entries) < target + 8:
            entries.extend([0] * (target + 8 - len(entries)))
        entries[target:target + 8] = cloned
        needed = (clone + 1) * 2
        if len(attributes) < needed:
            attributes.extend(b"\0" * (needed - len(attributes)))
        attributes[clone * 2:clone * 2 + 2] = attributes[original * 2:original * 2 + 2]

    # Upper/lower map cells for the Eye statue and final Alphoracle statue.
    for row, col, clone in ((9, 16, 200), (10, 16, 201),
                            (27, 25, 202), (28, 25, 203)):
        offset = row * width + col
        values[offset] = (values[offset] & 0xFC00) | (640 + clone)

    layout_path.write_bytes(struct.pack(f"<{len(values)}H", *values))
    meta_path.write_bytes(struct.pack(f"<{len(entries)}H", *entries))
    # Both halves of the existing visible entrance ladder use custom HNS metatiles.
    # They were accidentally tagged MB_NORMAL (0). The GBA warp handler checks
    # MetatileBehavior_IsLadder BEFORE it even looks at the warp event, so the
    # existing (15, 16) and (15, 15) warp events could never fire.
    # MB_LADDER = 97 (0x61) in include/constants/metatile_behaviors.h.
    # Preserve all other attribute bits, all graphics, and every other tile.
    for ladder_metatile in (100, 101):
        attr_offset = ladder_metatile * 2
        old = struct.unpack_from("<H", attributes, attr_offset)[0]
        struct.pack_into("<H", attributes, attr_offset,
                         (old & 0xFF00) | 0x61)

    attr_path.write_bytes(attributes)


def main():
    _install_eye_sprite()
    _install_alphoracle_sprite()
    _clear_original_statue_tiles()


if __name__ == "__main__":
    main()
