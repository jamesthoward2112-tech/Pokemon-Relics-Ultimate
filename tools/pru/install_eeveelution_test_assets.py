#!/usr/bin/env python3
"""Install 10 approved PRU Eeveelution front/back sprite pairs for this test only.

Uses the user's approved indexed pixel data; never redraws or resizes art.
Called *after* regular donor syncing/restoration so old assets cannot overwrite it.
"""
from __future__ import annotations
import base64
import hashlib
import lzma
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSET = ROOT / "assets/pru_eeveelutions_test/pixels.xz.b64"
DIR = ROOT / "graphics/pokemon/prl_authoritative"
NAMES = (
    "champeon", "drakeon", "eeveeon", "guardeon", "lepideon",
    "nimbeon", "obsideon", "omeon", "sphynxeon", "toxeon",
)
EXPECTED_COMPRESSED_SHA256 = "045494927fd2d7b2f6dc673aced04edd74f44c22a2c065b25f923e90a6b1f29c"
PIXELS = 64 * 64
BLOCK = 48 + PIXELS * 2

def main() -> None:
    packed = base64.b64decode(ASSET.read_text().strip(), validate=True)
    assert hashlib.sha256(packed).hexdigest() == EXPECTED_COMPRESSED_SHA256, "payload SHA changed"
    decoded = lzma.decompress(packed)
    assert len(decoded) == len(NAMES) * BLOCK, (len(decoded), len(NAMES) * BLOCK)
    for i, slug in enumerate(NAMES):
        chunk = decoded[i * BLOCK:(i + 1) * BLOCK]
        palette = list(chunk[:48])
        colors = [tuple(palette[j:j+3]) for j in range(0,48,3)]
        folder = DIR / slug
        folder.mkdir(parents=True, exist_ok=True)
        for side, offset in (("front",48),("back",48+PIXELS)):
            indices = chunk[offset:offset+PIXELS]
            assert len(indices) == PIXELS and max(indices) <= 15, (slug, side, "4bpp")
            sprite = Image.frombytes("P", (64,64), indices)
            sprite.putpalette(palette + [0] * (768-len(palette)))
            sprite.save(folder / (side+".png"), transparency=0)
            with Image.open(folder / (side+".png")) as check:
                assert check.mode=="P" and check.size==(64,64), (slug,side)
                assert check.info.get("transparency")==0, (slug,side,"transparency")
                assert bytes(check.getdata())==indices, (slug,side,"pixel mutation")
                assert max(check.getdata())<16, (slug,side,"palette")
        jasc = "JASC-PAL\n0100\n16\n" + "".join(f"{r} {g} {b}\n" for r,g,b in colors)
        (folder / "normal.pal").write_text(jasc)
        assert (folder / "normal.pal").read_text().count("\n") == 19
        print("PASS",slug,"front/back 64x64 indexed GBA sprites; common palette <=15 visible colours")
    print("PASS: ten user-approved pairs installed after every normal PRU asset restoration")

if __name__ == "__main__":
    main()
