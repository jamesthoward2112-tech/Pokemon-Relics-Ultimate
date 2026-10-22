#!/usr/bin/env python3
"""Block releases if PRU Jirachi falls back to plain/TRE or invalid GBA art."""
from pathlib import Path
import hashlib
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
ASSETS=ROOT/"assets/insurgence_mega_jirachi"
GFX=ROOT/"graphics/pokemon/jirachi"

expect={
"front":"bf561f61aeaaba9ad6cacd65b244bba9ef1d735e1069c148de9f2e53ad3ab4fc",
"back":"619282a36188403f364e4851948d48bb19ec657525b539f2f5c862725240a2ac",
"front_shiny":"0c66b908ecd3d3502dbb74b48970b0961d27924a81f165180a2aa3ca05cee486",
"back_shiny":"3f6ad5a9a3289296ffe5abddeb0277956827beb464ba1146c241d078808872c7"}
for part,sha in expect.items():
    p=ASSETS/f"source_{part}.png"
    assert hashlib.sha256(p.read_bytes()).hexdigest()==sha, f"Unverified Jirachi donor {p}"
for name,size in {"anim_front_gba.png":(64,128),"anim_front.png":(64,128),
                  "back_gba.png":(64,64),"back.png":(64,64)}.items():
    p=GFX/name
    with Image.open(p) as im:
        im.load()
        assert im.mode=="P" and im.size==size, (p,im.mode,im.size)
        colors=set(im.getdata())
        assert len(colors)<=16 and min(colors)>=0 and max(colors)<16, (p,colors)
        assert 0 in colors, "No transparent palette 0"
        assert len(colors)>6, "Blank or severely degraded donor"
front=Image.open(GFX/"anim_front_gba.png")
assert list(front.crop((0,0,64,64)).getdata())==list(front.crop((0,64,64,128)).getdata()), "Jirachi's second animation frame is not locked"
# User gameplay feedback: guard against reintroducing the old global shrink
# (50x60) which made this exact Insurgence front distorted and jagged.
assert front.crop((0,0,64,64)).getbbox() == (2,0,60,64), \
    "Jirachi lost its native 59-column detail-preserving front composition"

for name in ("normal.pal","normal_gba.pal","shiny.pal","shiny_gba.pal"):
    rows=(GFX/name).read_text().splitlines()
    assert rows[:3]==["JASC-PAL","0100","16"], name
    assert len(rows)==19, (name,len(rows))
    assert all(len(row.split())==3 for row in rows[3:]), name
assert (GFX/"normal_gba.pal").read_bytes()!=(GFX/"shiny_gba.pal").read_bytes(), "Shiny palette must differ from normal"
species=(ROOT/"src/data/pokemon/species_info/gen_3_families.h").read_text()
section=species.split("[SPECIES_JIRACHI] =",1)[1].split("#endif //P_FAMILY_JIRACHI",1)[0]
assert ".frontPicSize = MON_COORDS_SIZE(64, 64)" in section
assert ".backPicSize = MON_COORDS_SIZE(64, 64)" in section
assert ".frontPicYOffset = 1," in section
assert ".backPicYOffset = 4," in section
assert ".types = MON_TYPES(TYPE_STEEL, TYPE_PSYCHIC)" in section
assert ".abilities = { ABILITY_SERENE_GRACE, ABILITY_NONE, ABILITY_NONE }" in section
assert ".natDexNum = NATIONAL_DEX_JIRACHI" in section
print("PASS: Insurgence Mega Jirachi source authenticity, 64x64 4bpp frames, shiny palettes, no distortion, original gameplay and 444 preserved.")
