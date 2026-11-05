#!/usr/bin/env python3
"""Job 14 QA: exact approved Gemlin source, clean Scarabub reduction and blue icon.

Only the two specified baby Pokemon may change in this job.
"""
from pathlib import Path
from PIL import Image
import hashlib
import re

ROOT=Path(__file__).resolve().parents[2]
SRC=ROOT/"assets/pru_approved_babies"
GFX=ROOT/"graphics/pokemon/prl_authoritative"

SOURCE_HASHES={
 "front.png":"0fa8fbdd673ff77c22a95f53c0659ba88a986b14826fa96eb9a564875f67b434",
 "back.png":"f2555abfe89d0b24759b80a434096150be7ab9f9a20edc7fffcc3fdcf866100d",
 "icon.png":"d7e51fc49ee9c19852cfcf07a7b307e298a2c06b60c27f6b2a09320290b780de",
 "normal.pal":"0bfd8e9a6954856430a80ce5d68ae83ac449f59e061e53cdd7cb8a63902dc9a8",
 "shiny.pal":"c47e5e529b13f3b4be7df16f65414016cfefb6cc1de47ce30f0b1eace97f101f",
}

def sha(path):
    data=path.read_bytes()
    # Git can check out JASC-PAL text as CRLF on Windows or Linux; preserve
    # source palette colours without comparing platform-specific line endings.
    if path.suffix==".pal":
        data=data.replace(b"\r\n",b"\n")
    return hashlib.sha256(data).hexdigest()
def bbox(image):
    return image.point(lambda idx:255 if idx else 0).getbbox()
def pixcol(image):
    return tuple(image.getpalette()[:48])

for file,digest in SOURCE_HASHES.items():
    source=SRC/"gemlin"/file
    dst=GFX/"gemlin"/file
    assert sha(source)==digest, (file,"unexpected modification to signed-off source")
    assert sha(dst)==digest, (file,"older PoryPal assets replaced accepted original")

for side,expected in (("front",(32,34)),("back",(31,33))):
    with Image.open(GFX/"gemlin"/f"{side}.png") as img:
        assert img.mode=="P" and img.size==(64,64)
        assert img.info.get("transparency")==0
        b=bbox(img)
        assert (b[2]-b[0],b[3]-b[1])==expected,(side,b)
        assert len(img.getcolors(4096))<=16
with Image.open(GFX/"gemlin"/"icon.png") as img:
    assert img.mode=="P" and img.size==(32,64) and img.info.get("transparency")==0
    for y in (0,32):
        b=bbox(img.crop((0,y,32,y+32)))
        assert b is not None
        assert (b[2]-b[0])<=20 and (b[3]-b[1])<=23,(y,b)

icon_c=(ROOT/"src/pokemon_icon.c").read_text()
assert "sPRUGemlinOriginalIconPalette[16]" in icon_c
assert "{ sPRUGemlinOriginalIconPalette, POKE_ICON_BASE_PAL_TAG + 16 }" in icon_c
assert re.search(r"if \(species == SPECIES_GEMLIN\)\s*return 16;",icon_c)
palette_def=icon_c.split("sPRUGemlinOriginalIconPalette[16]",1)[1].split("};",1)[0]
with Image.open(SRC/"gemlin"/"icon.png") as im:
    source_palette=[tuple(round(v*31/255) for v in im.getpalette()[i:i+3]) for i in range(0,48,3)]
icon_constants=[tuple(int(v) for v in tup) for tup in re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)",palette_def)]
assert source_palette==icon_constants,"Custom icon palette must match every source index"

for side,old_max,new_size in (("front",60,(44,40)),("back",60,(44,41))):
    src=SRC/"scarabub"/f"{side}.png"
    dst=GFX/"scarabub"/f"{side}.png"
    with Image.open(src) as original,Image.open(dst) as installed,Image.open(SRC/"scarabub"/f"original_{side}.png") as donor:
        assert donor.mode==original.mode==installed.mode=="P"
        assert original.size==installed.size==donor.size==(64,64)
        assert original.info.get("transparency")==installed.info.get("transparency")==0
        assert pixcol(donor)==pixcol(original)==pixcol(installed)
        assert original.tobytes()==installed.tobytes()
        b=bbox(installed)
        assert (b[2]-b[0],b[3]-b[1])==new_size,(side,b)
        donor_box=bbox(donor)
        assert donor_box[2]-donor_box[0]==old_max
        assert max(installed.getdata())<16
with Image.open(GFX/"scarabub"/"icon.png") as icon:
    assert icon.mode=="P" and icon.size==(32,64)
    pal3=(ROOT/"graphics/pokemon/icon_palettes/pal3.pal").read_text().splitlines()[3:19]
    assert [tuple(map(int,s.split())) for s in pal3]==[tuple(icon.getpalette()[i:i+3]) for i in range(0,48,3)]
source_species=(ROOT/"src/data/pokemon/species_info/pjr_families.h").read_text()
entry=source_species.split("[SPECIES_SCARABUB] =",1)[1].split("[SPECIES_HERACURION] =",1)[0]
assert ".iconPalIndex = 3" in entry
assert ".speciesName = _(\"Scarabub\")" in entry
assert "SPECIES_HERACROSS" in entry
print("JOB14_PASS: Gemlin exact approved front/flipped-back/icon and 16-colour palette; Scarabub 44x40/44x41 and true blue pal3 icon")
