#!/usr/bin/env python3
"""Convert the FOUR authentic Insurgence Mega Jirachi donor sprites to PRU 4bpp.

Pixel-art safe: use the ORIGINAL PNG alpha mask to remove all transparent RGB
(rectangles in the image preview are actually transparent), trim true-alpha
padding, resize with a SINGLE uniform factor by nearest-neighbor, centre
horizontally, and place the visible bottom near the bottom of the GBA frame.
Preserves exact normal/shiny relationship; does not introduce a new species.
"""
from __future__ import annotations
from collections import Counter, defaultdict
from pathlib import Path
import hashlib
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
SOURCES = ROOT / "assets/insurgence_mega_jirachi"
OUT = ROOT / "graphics/pokemon/jirachi"

EXPECTED_SHA256 = {
    "front": "bf561f61aeaaba9ad6cacd65b244bba9ef1d735e1069c148de9f2e53ad3ab4fc",
    "back": "619282a36188403f364e4851948d48bb19ec657525b539f2f5c862725240a2ac",
    "front_shiny": "0c66b908ecd3d3502dbb74b48970b0961d27924a81f165180a2aa3ca05cee486",
    "back_shiny": "3f6ad5a9a3289296ffe5abddeb0277956827beb464ba1146c241d078808872c7",
}

# These source colors are near-duplicates in the original normal sprite.
# We merge them so front and back use ONE GBA 15-opaque-color palette.
# 16,16,16 is the back outline and 0,0,0 the front outline.
# 255,218,91 is the back yellow, 255,230,90 its front counterpart.
CANONICAL = {
    (16, 16, 16): (0, 0, 0),
    (255, 218, 91): (255, 230, 90),
}

def key(rgb):
    return CANONICAL.get(rgb, rgb)

def read(name):
    p=SOURCES / f"source_{name}.png"
    data=p.read_bytes()
    assert hashlib.sha256(data).hexdigest()==EXPECTED_SHA256[name], f"Original Insurgence source changed: {p}"
    with Image.open(p) as im:
        assert im.format=="PNG"
        return im.convert("RGBA")

orig={name:read(name) for name in EXPECTED_SHA256}
palette_counts=Counter()
shiny_link=defaultdict(Counter)
for part in ("front","back"):
    normal=orig[part]
    shiny=orig[part+"_shiny"]
    assert normal.size==shiny.size
    mask_n=[a>127 for a in normal.getchannel("A").getdata()]
    mask_s=[a>127 for a in shiny.getchannel("A").getdata()]
    differences=sum(x!=y for x,y in zip(mask_n,mask_s))
    # The Insurgence wiki sprite exports contain a few shiny alpha holes.
    # In battle one form cannot acquire/remove physical body pixels, so
    # use the original NORMAL alpha silhouette consistently for both forms.
    assert differences < len(mask_n)//10, f"Donor shapes differ excessively: {part} {differences}"
    print(f"INFO: source shiny alpha differs at {differences} pixels; "
          "normal silhouette retained for both palettes")
    for n,s in zip(normal.getdata(),shiny.getdata()):
        if n[3] <= 127:
            continue
        k=key(n[:3])
        palette_counts[k]+=1
        shiny_link[k][s[:3]]+=1

colors=[c for c,_ in palette_counts.most_common()]
assert len(colors)<=15, f"Normal/Back palette overflow: {len(colors)} opaque colours"
colors_shiny=[]
for c in colors:
    possibilities=shiny_link[c]
    color=possibilities.most_common(1)[0][0]
    disagreement=sum(possibilities.values())-possibilities[color]
    if disagreement:
        print(f"INFO: merged color {c}: dominant shiny {color}, {disagreement} pixels other variants")
    colors_shiny.append(color)
assert len(colors_shiny)==len(colors) and len(colors_shiny)<=15

palette_normal=[(0, 0, 0)]+colors
palette_shiny=[(0, 0, 0)]+colors_shiny
while len(palette_normal)<16:
    palette_normal.append((0,0,0))
    palette_shiny.append((0,0,0))
indices={c:i+1 for i,c in enumerate(colors)}

def convert(part):
    im=orig[part.removesuffix("_shiny")]
    mask=im.getchannel("A").point(lambda a: 255 if a>127 else 0)
    bbox=mask.getbbox()
    assert bbox, f"Empty donor {part}"
    cropped=im.crop(bbox)
    src_w,src_h=cropped.size
    max_w,max_h=((60,60) if part.startswith("front") else (64,58))
    # Single aspect-preserving scale for width AND height. No stretching.
    factor=min(max_w/src_w,max_h/src_h,1)
    out_w=max(1,round(src_w*factor))
    out_h=max(1,round(src_h*factor))
    assert 0<out_w<=64 and 0<out_h<=64
    assert abs((out_w/out_h)/(src_w/src_h)-1)<0.025
    scaled=cropped.resize((out_w,out_h),Image.Resampling.NEAREST)
    # Both views visually grounded; front larger vertically, back wider.
    x=(64-out_w)//2
    y=64-out_h-2 if part.startswith("front") else 64-out_h
    canvas=Image.new("P",(64,64),0)
    rgbpal=palette_shiny if part.endswith("shiny") else palette_normal
    flatpal=[v for rgb in rgbpal for v in rgb]+[0]*(768-48)
    canvas.putpalette(flatpal)
    data=[0]*4096
    normal_scaled=(orig[part.removesuffix("_shiny")].crop(bbox).resize((out_w,out_h), Image.Resampling.NEAREST) if part.endswith("_shiny") else None)
    for py in range(out_h):
        for px in range(out_w):
            rgba=scaled.getpixel((px,py))
            if rgba[3]<=127:
                continue
            rgb=key(rgba[:3]) if not part.endswith("shiny") else rgba[:3]
            if part.endswith("shiny"):
                # Use colour pairing with the normal sprite at the same source
                # coordinate to preserve indexed shiny palette ordering.
                nrgba=normal_scaled.getpixel((px,py))
                rgb=key(nrgba[:3])
            data[(y+py)*64+(x+px)]=indices[rgb]
    canvas.putdata(data)
    canvas.info["transparency"]=0
    assert max(data)<16 and len(set(data))<=16
    print(f"{part}: original visible bbox={bbox} {src_w}x{src_h}; "
          f"frame visible={out_w}x{out_h} x={x} y={y}; "
          f"aspect error={abs(out_w/out_h/(src_w/src_h)-1):.3f}; indexed max={max(data)}")
    return canvas

normal_front=convert("front")
normal_back=convert("back")
shiny_front=convert("front_shiny")
shiny_back=convert("back_shiny")
assert list(normal_front.getdata())==list(shiny_front.getdata()), "Shiny front must retain identical colour indices"
assert list(normal_back.getdata())==list(shiny_back.getdata()), "Shiny back must retain identical colour indices"

OUT.mkdir(parents=True,exist_ok=True)

def write_png(im,path):
    im.save(path,format="PNG",transparency=0,optimize=False)
    with Image.open(path) as check:
        assert check.mode=="P" and max(check.getdata())<16, path

# The original two-frame Jirachi animation references frame 1. Duplicate
# the correct Mega front so no garbage appears on the second frame.
front_sheet=Image.new("P",(64,128),0)
front_sheet.putpalette(normal_front.getpalette())
front_sheet.paste(normal_front,(0,0))
front_sheet.paste(normal_front,(0,64))
write_png(front_sheet,OUT/"anim_front_gba.png")
write_png(front_sheet,OUT/"anim_front.png")
write_png(normal_back,OUT/"back_gba.png")
write_png(normal_back,OUT/"back.png")

for filename in ("normal.pal","normal_gba.pal"):
    pal=palette_normal
    (OUT/filename).write_text("JASC-PAL\n0100\n16\n"+"\n".join(" ".join(map(str,c)) for c in pal)+"\n")
for filename in ("shiny.pal","shiny_gba.pal"):
    pal=palette_shiny
    (OUT/filename).write_text("JASC-PAL\n0100\n16\n"+"\n".join(" ".join(map(str,c)) for c in pal)+"\n")

# Preview normal and shiny through the same shared index frame & matching
# palette (no ad-hoc recolour); checkerboard is a visual aid ONLY.
preview=Image.new("RGB",(4*4*64,4*64+35),(24,30,42))
d=ImageDraw.Draw(preview)
for i,(name,im) in enumerate([
    ("Front",normal_front),("Back",normal_back),
    ("Shiny front",shiny_front),("Shiny back",shiny_back),
]):
    panel=Image.new("RGB",(64,64),(59,66,75))
    pix=im.convert("RGBA")
    # Palette index zero is transparent even when it has an RGB value.
    alpha=Image.new("L",im.size)
    alpha.putdata([0 if k==0 else 255 for k in im.getdata()])
    panel.paste(pix.convert("RGB"),(0,0),alpha)
    large=panel.resize((256,256),Image.Resampling.NEAREST)
    preview.paste(large,(i*256,30))
    d.text((i*256+6,9),name,fill=(255,255,255))
preview.save(SOURCES/"preview_4x.png")
print("PASS: native 64x64 indexed Mega Jirachi from exact Insurgence sources; 2-frame front; 4 shared normal/shiny matching palettes; NO aspect distortion")
