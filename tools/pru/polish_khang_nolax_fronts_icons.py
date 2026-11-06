#!/usr/bin/env python3
"""Small, reversible Khang/Nolax sprite-only repair on the approved 4bpp art.
No back-sprite, Pokemon stats, palette, map, or save changes.
One-time source preparation. Do not run repeatedly after integrating the PNGs.
"""
from collections import Counter
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2] / "graphics/pokemon/prl_authoritative"
FACE_PATCHES = {
    "khang": {
        (32,14):14,(31,14):15,(33,14):14,(37,16):14,(37,17):15,
        (30,18):13,(32,19):12,(36,19):12,(34,20):1,(35,20):1,(36,20):4,
    },
    "nolax": {
        (27,17):13,(26,18):13,(27,18):12,(28,18):13,
        (35,16):13,(35,17):12,(37,17):13,(36,18):12,(37,18):13,
        (30,21):14,(31,21):1,(32,21):14,(33,21):1,(34,21):14,
        (29,22):1,(31,22):14,(33,22):14,
    },
}

def polish_front(name: str):
    p = ROOT / name / "front.png"
    im = Image.open(p)
    assert im.mode == "P" and im.size == (64,64) and im.info.get("transparency")==0
    source = im.load()
    orig = [[int(source[x,y]) for x in range(64)] for y in range(64)]
    result = [row[:] for row in orig]
    family = {3,4,5,6,7} if name=="khang" else {8,9,10,11}
    cleanup = 0
    for y in range(26,56):
        for x in range(5,59):
            if name=="khang" and not (x<25 or x>41):
                continue
            if name=="nolax" and not (23<x<41):
                continue
            current=orig[y][x]
            if current not in family: continue
            vals=[orig[dy][dx] for dy in (y-1,y,y+1) for dx in (x-1,x,x+1)]
            vote,count=Counter(vals).most_common(1)[0]
            if vote in family and vote!=current and count>=6:
                result[y][x]=vote
                cleanup+=1
    for (x,y),new in FACE_PATCHES[name].items():
        assert orig[y][x] != 0, (name,x,y)
        result[y][x]=new
    for y in range(64):
        for x in range(64):
            source[x,y]=result[y][x]
    assert max(im.getdata()) <= 15
    im.save(p, transparency=0, optimize=True)
    print(f"{name}: front polished with {len(FACE_PATCHES[name])} feature accents and {cleanup} shading cleanups")

def resize_icon(name:str):
    p=ROOT / name / "icon.png"
    im=Image.open(p)
    assert im.mode=="P" and im.size==(32,64) and im.info.get("transparency")==0
    frame=im.crop((0,0,32,32))
    bbox=frame.getbbox()
    assert bbox
    cropped=frame.crop(bbox)
    old=cropped.size
    small=cropped.resize((max(1,round(old[0]*.5)), max(1,round(old[1]*.5))),
                         Image.Resampling.NEAREST)
    out=Image.new("P",(32,64),0)
    out.putpalette(im.getpalette())
    x=(32-small.width)//2
    y=31-small.height
    out.paste(small,(x,y))
    out.paste(small,(x,y+32))
    assert max(out.getdata())<=15
    assert list(out.crop((0,0,32,32)).getdata()) == list(out.crop((0,32,32,64)).getdata())
    out.save(p, transparency=0, optimize=True)
    print(f"{name}: party icon {old[0]}x{old[1]} -> {small.width}x{small.height}; full GBA canvas 32x64")

if __name__=="__main__":
    for species in ("khang","nolax"):
        polish_front(species)
        resize_icon(species)
    print("Back sprites intentionally untouched; palettes unchanged")
