#!/usr/bin/env python3
"""Convert approved duo art into native 512-tile, 4bpp BG0 transition banks."""
import argparse
import struct
from dataclasses import dataclass
from pathlib import Path
from PIL import Image

@dataclass
class EntranceAsset:
    tiles: bytes
    tilemap: bytes
    palette: bytes
    preview: Image.Image
    tile_count: int

def _from555(value):
    def channel(shift):
        c = (value >> shift) & 31
        return (c << 3) | (c >> 2)
    return (channel(0), channel(5), channel(10))

def reconstruct_preview(asset):
    palette = [_from555(v) for v in struct.unpack('<16H', asset.palette)]
    entries = struct.unpack('<1024H', asset.tilemap)
    im = Image.new('RGB', (240, 160))
    px = im.load()
    for ty in range(20):
        for tx in range(30):
            tile = asset.tiles[(entries[ty * 32 + tx] & 1023) * 32:]
            for y in range(8):
                for x in range(8):
                    byte = tile[y * 4 + x // 2]
                    index = byte >> 4 if x % 2 else byte & 15
                    px[tx * 8 + x, ty * 8 + y] = palette[index]
    return im

def convert_image(source):
    # A one-tile black border reduces 600 visible screen tiles to 504 unique
    # art tiles plus a border tile, fitting the native 512-tile/16 KB bank.
    art = source.convert('RGB').resize((224, 144), Image.Resampling.LANCZOS)
    quant = art.quantize(colors=15, method=Image.Quantize.MEDIANCUT, dither=Image.Dither.NONE)
    raw = quant.getpalette()
    colors = [tuple(raw[i:i + 3]) for i in range(0, min(45, len(raw)), 3)]
    if len(colors) < 15:
        darkest = len(colors)
        colors.append((0, 0, 0))
    else:
        darkest = min(range(15), key=lambda n: sum(colors[n]))
        colors[darkest] = (0, 0, 0)
    colors += [(0, 0, 0)] * (15 - len(colors))
    palette = struct.pack('<16H', 0, *[((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)) for r, g, b in colors])
    border = darkest + 1
    pixels = bytearray([border] * (240 * 160))
    source_indices = quant.tobytes()
    for y in range(144):
        destination = (y + 8) * 240 + 8
        pixels[destination:destination + 224] = bytes(i + 1 for i in source_indices[y * 224:(y + 1) * 224])
    def encode(indices):
        return bytes(indices[i] | (indices[i + 1] << 4) for i in range(0, 64, 2))
    blank = encode([border] * 64)
    atlas = [blank]
    lookup = {blank: 0}
    tilemap = [13 << 12] * 1024
    for ty in range(20):
        for tx in range(30):
            indices = [pixels[(ty * 8 + y) * 240 + tx * 8 + x] for y in range(8) for x in range(8)]
            tile = encode(indices)
            if tile not in lookup:
                lookup[tile] = len(atlas)
                atlas.append(tile)
            tilemap[ty * 32 + tx] = (13 << 12) | lookup[tile]
    if len(atlas) > 512:
        raise ValueError(f'Exceeded GBA 512 tile bank: {len(atlas)}')
    result = EntranceAsset(b''.join(atlas + [blank] * (512 - len(atlas))),
                           struct.pack('<1024H', *tilemap), palette, None, len(atlas))
    result.preview = reconstruct_preview(result)
    return result

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('red_blue', type=Path)
    parser.add_argument('oak_elm', type=Path)
    parser.add_argument('--output', type=Path, default=Path('graphics/battle_transitions/prl'))
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    for name, source in (('red_blue', args.red_blue), ('oak_elm', args.oak_elm)):
        with Image.open(source) as image:
            asset = convert_image(image)
        for extension, data in (('4bpp', asset.tiles), ('bin', asset.tilemap), ('gbapal', asset.palette)):
            (args.output / f'{name}.{extension}').write_bytes(data)
        asset.preview.save(args.output / f'{name}_preview.png', optimize=True)
        print(f'{name}: 240x160, {asset.tile_count}/512 tiles, 15 colours')

if __name__ == '__main__':
    main()
