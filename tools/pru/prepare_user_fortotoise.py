#!/usr/bin/env python3
"""Install user-approved PRL PR72 Fortotoise front/back, without image edits.

Both 64x64 indexed frames were decoded directly from the supplied 32 MiB
PRL_PR72_Kanto_Champion_Dialogue_20261014.gba. No resize or palette remap.
The separately approved Pokésprite G-Max party icon remains a 32x64 pal3 icon.
"""
from __future__ import annotations
from pathlib import Path
from PIL import Image
import hashlib
import json
import shutil

ROOT = Path(__file__).resolve().parents[2]
ASSET = ROOT / "assets/pru_final_polish/fortotoise"
MANIFEST = json.loads((ASSET / "PR72_ROM_PROVENANCE.json").read_text(encoding="utf-8"))

def hash_4bpp(im: Image.Image) -> str:
    """Encode GBA tile-by-tile; compare against ROM's original 4bpp bytes."""
    b = bytearray()
    for tile in range(64):
        x0 = (tile % 8) * 8
        y0 = (tile // 8) * 8
        for y in range(8):
            for x in range(0, 8, 2):
                lo = im.getpixel((x0+x,y0+y))
                hi = im.getpixel((x0+x+1,y0+y))
                assert 0 <= lo < 16 and 0 <= hi < 16
                b.append(lo | (hi << 4))
    assert len(b) == 2048
    return hashlib.sha256(b).hexdigest()

def save_palette(filename: str, colours: list[list[int]]) -> None:
    assert len(colours) == 16 and all(len(c) == 3 for c in colours)
    text = "JASC-PAL\n0100\n16\n" + "\n".join(
        "{} {} {}".format(*rgb) for rgb in colours
    ) + "\n"
    (ASSET / filename).write_bytes(text.encode("ascii"))

def main() -> None:
    assert MANIFEST["rom_sha256"] == "57fac7dd5a4c859ada1612e796b17e9b549a711f80d0fb8fcd523fa03c502c4e"
    original_palette = [component for c in MANIFEST["palette"] for component in c]
    for side in ("front","back"):
        source = ASSET / f"PR72_Fortotoise_{side}.png"
        with Image.open(source) as im:
            assert im.size == (64,64) and im.mode == "P"
            assert im.info.get("transparency") == 0
            assert list(im.getpalette()[:48]) == original_palette
            assert hash_4bpp(im) == MANIFEST[f"{side}_raw_sha256"]
        shutil.copyfile(source, ASSET / f"{side}.png")
    save_palette("normal.pal", MANIFEST["palette"])
    save_palette("shiny.pal", MANIFEST["shiny_palette"])

    # Never silently replace the approved Pokésprite icon with Mega Blastoise.
    selected = ASSET / "pokesprite_gmax_icon_GBA_pal3.png"
    with Image.open(selected) as im:
        assert im.mode == "P" and im.size == (32,64)
        assert im.info.get("transparency") == 0
        assert max(im.getdata()) < 16
    shutil.copyfile(selected,ASSET/"icon.png")
    print("FORTOTOISE_PR72_EXACT: both ROM front/back frames installed byte-for-byte as indices; PR72 normal/shiny palettes; Pokésprite G-Max party icon.")

if __name__ == "__main__":
    main()
