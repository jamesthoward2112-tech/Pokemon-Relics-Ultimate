#!/usr/bin/env python3
"""Reproduce the approved BYOXYS battle sprite sheet from the AlteRed donor ROM.

Usage: python3 tools/pru/extract_byoxys_from_altered.py <AlteRed ZIP> <output dir>
This is a one-time art import tool; it does not modify the donor ROM.
"""
import sys
import zipfile
from pathlib import Path

from PIL import Image

FRONT_OFFSET = 0x959928
PALETTE_OFFSET = 0x959F00
BACK_OFFSET = 0x959F28


def gba_lz77(blob, offset):
    assert blob[offset] == 0x10, hex(offset)
    length = int.from_bytes(blob[offset + 1:offset + 4], 'little')
    out = bytearray()
    pos = offset + 4
    while len(out) < length:
        control = blob[pos]
        pos += 1
        for bit in range(7, -1, -1):
            if len(out) >= length:
                break
            if control & (1 << bit):
                first, second = blob[pos], blob[pos + 1]
                pos += 2
                count = (first >> 4) + 3
                disp = ((first & 0x0F) << 8 | second) + 1
                for _ in range(count):
                    out.append(out[-disp])
            else:
                out.append(blob[pos])
                pos += 1
    return bytes(out)


def unpack_image(blob, gba_pal):
    assert len(blob) == 64 * 64 // 2
    out = Image.new('P', (64, 64))
    colors = []
    for i in range(16):
        c = int.from_bytes(gba_pal[2 * i:2 * i + 2], 'little')
        colors += [((c >> shift) & 31) * 255 // 31 for shift in (0, 5, 10)]
    out.putpalette(colors + [0] * (768 - 48))
    out.info['transparency'] = 0
    pixels = out.load()
    for tile_y in range(8):
        for tile_x in range(8):
            tile_start = (tile_y * 8 + tile_x) * 32
            for y in range(8):
                for x in range(8):
                    byte = blob[tile_start + y * 4 + x // 2]
                    pixels[tile_x * 8 + x, tile_y * 8 + y] = (byte >> (4 * (x & 1))) & 15
    return out


def main():
    with zipfile.ZipFile(sys.argv[1]) as z:
        blob = z.read(z.namelist()[0])
    pal = gba_lz77(blob, PALETTE_OFFSET)
    front = unpack_image(gba_lz77(blob, FRONT_OFFSET), pal)
    back = unpack_image(gba_lz77(blob, BACK_OFFSET), pal)
    directory = Path(sys.argv[2])
    directory.mkdir(parents=True, exist_ok=True)
    front.save(directory / 'byoxys_donor_front.png')
    back.save(directory / 'byoxys_donor_back.png')
    for name, image in [('byoxys_anim_front_gba.png', front), ('byoxys_back_gba.png', back)]:
        sheet = Image.new('P', (64, 128))
        sheet.putpalette(image.getpalette())
        sheet.paste(image, (0, 0))
        sheet.paste(image, (0, 64))
        sheet.info['transparency'] = 0
        sheet.save(directory / name)
    print('Decompressed donor BYOXYS front and back', directory)


if __name__ == '__main__':
    main()
