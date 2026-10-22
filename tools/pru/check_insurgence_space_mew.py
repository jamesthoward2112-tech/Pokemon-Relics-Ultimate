#!/usr/bin/env python3
"""PRU Mew must use the 64x64 Insurgence Space Mew battle art, not vanilla Mew."""
from pathlib import Path
from PIL import Image
import hashlib

root=Path(__file__).resolve().parents[2]
gfx=root/"graphics/pokemon/mew"
expected={
 "anim_front_gba.png":"e513b34c821124501eec48638e63e278b0f2e6fa",
 "back_gba.png":"bd52dddf219e2ec9134dc6cb2144182df68e1204",
}
# Git blob SHA is stable for these exact PNG bytes, preventing a vanilla art regression.
for name,sha in expected.items():
    content=(gfx/name).read_bytes()
    blob=hashlib.sha1(b"blob "+str(len(content)).encode()+b"\0"+content).hexdigest()
    assert blob==sha, (name,blob,sha)
for name,size in {"anim_front.png":(64,128),"anim_front_gba.png":(64,128),
                  "back.png":(64,64),"back_gba.png":(64,64)}.items():
    with Image.open(gfx/name) as im:
        im.load()
        assert im.mode=="P" and im.size==size and im.info.get("transparency")==0,(name,im.mode,im.size)
        assert max(im.getdata())<16 and len(set(im.getdata()))<=16,name
front=Image.open(gfx/"anim_front_gba.png")
assert list(front.crop((0,0,64,64)).getdata())==list(front.crop((0,64,64,128)).getdata())
assert list(Image.open(gfx/"anim_front.png").getdata())==list(front.getdata())
assert list(Image.open(gfx/"back.png").getdata())==list(Image.open(gfx/"back_gba.png").getdata())
for variant in ("","_gba"):
    normal=(gfx/f"normal{variant}.pal").read_text().splitlines()
    shiny=(gfx/f"shiny{variant}.pal").read_text().splitlines()
    for lines in (normal,shiny):
        assert lines[:3]==["JASC-PAL","0100","16"] and len(lines)==19
        assert all(len(row.split())==3 for row in lines[3:])
    assert normal!=shiny and "155 6 80" in normal and "34 52 119" in shiny
species=(root/"src/data/pokemon/species_info/gen_1_families.h").read_text()
section=species.split("[SPECIES_MEW] =",1)[1].split("#endif //P_FAMILY_MEW",1)[0]
assert ".frontPicSize = MON_COORDS_SIZE(64, 64)" in section
assert ".backPicSize = MON_COORDS_SIZE(64, 64)" in section
assert ".natDexNum = NATIONAL_DEX_MEW" in section
assert ".speciesName = _(" + '"Mew"' + ")" in section
print("PASS: exact authentic Space Mew (normal pink/shiny blue) shared-index graphics; 4bpp-ready, Mew remains Mew")
