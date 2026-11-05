#!/usr/bin/env python3
"""Job 13: assert both installed Fortotoise frames are exact PR72 ROM decodes."""
from pathlib import Path
import hashlib
import json
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
SRC=ROOT/"assets/pru_final_polish/fortotoise"
DST=ROOT/"graphics/pokemon/prl_authoritative/fortotoise"
manifest=json.loads((SRC/"PR72_ROM_PROVENANCE.json").read_text())
assert manifest["rom"]=="PRL_PR72_Kanto_Champion_Dialogue_20261014.gba"
assert manifest["rom_sha256"]=="57fac7dd5a4c859ada1612e796b17e9b549a711f80d0fb8fcd523fa03c502c4e"
expected_palette=tuple(component for rgb in manifest["palette"] for component in rgb)

def raw_gba_4bpp(img):
    encoded=bytearray()
    for tile in range(64):
        tx=(tile%8)*8
        ty=(tile//8)*8
        for y in range(8):
            for x in range(0,8,2):
                lo=img.getpixel((tx+x,ty+y))
                hi=img.getpixel((tx+x+1,ty+y))
                assert 0<=lo<=15 and 0<=hi<=15
                encoded.append(lo | hi<<4)
    assert len(encoded)==2048
    return bytes(encoded)

for side in ("front","back"):
    with Image.open(SRC/f"PR72_Fortotoise_{side}.png") as original:
        assert original.mode=="P" and original.size==(64,64) and original.info.get("transparency")==0
        assert tuple(original.getpalette()[:48])==expected_palette
        original_indices=original.tobytes()
        raw=raw_gba_4bpp(original)
        assert hashlib.sha256(raw).hexdigest()==manifest[f"{side}_raw_sha256"]
        for location in (SRC,DST):
            with Image.open(location/f"{side}.png") as installed:
                assert installed.mode=="P" and installed.size==(64,64)
                assert installed.info.get("transparency")==0
                assert tuple(installed.getpalette()[:48])==expected_palette
                assert installed.tobytes()==original_indices, (location,side,"different pixels")
                assert hashlib.sha256(raw_gba_4bpp(installed)).hexdigest()==manifest[f"{side}_raw_sha256"]
    print("ROM EXACT",side,manifest[f"{side}_raw_sha256"])

for file,colors in (("normal.pal",manifest["palette"]),("shiny.pal",manifest["shiny_palette"])):
    for location in (SRC,DST):
        rows=(location/file).read_text().splitlines()
        assert rows[:3]==["JASC-PAL","0100","16"]
        assert [list(map(int,r.split())) for r in rows[3:19]]==colors, (location,file)

with Image.open(DST/"icon.png") as icon, Image.open(SRC/"pokesprite_gmax_icon_GBA_pal3.png") as approved:
    assert icon.tobytes()==approved.tobytes()
    assert icon.size==(32,64) and icon.mode=="P"

assert '"fortotoise": 3' in (ROOT/"tools/pru/install_final_polish_sprites.py").read_text()
assert "PR72_Fortotoise_front.png" in (ROOT/"tools/pru/prepare_user_fortotoise.py").read_text() or 'f"PR72_Fortotoise_{side}.png"' in (ROOT/"tools/pru/prepare_user_fortotoise.py").read_text()
print("JOB13_PR72_PAIRED_SPRITES_PASS: exact front/back 4bpp and normal/shiny 16 colour palettes; Pokesprite icon unchanged.")
