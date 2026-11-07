#!/usr/bin/env python3
"""Restore Khang's original front shape with approved recent Khang palette.
Keep BOTH current back sprites byte-for-byte, restore Nolax front and both
party icons to the earlier approved initial six-sprite build (006e1603).

This script is intentionally one-time and should only be run on the
test/khang-nolax-sprites-20261106 branch at 22874b2d.
"""
import io, subprocess, hashlib
from pathlib import Path
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
GFX=ROOT/"graphics/pokemon/prl_authoritative"
ORIGINAL_KHANG="e5d1677118c3a28c0a2bbf8918e049ad6750330d"
PRE_REGRESSION="006e1603bb2781e1d07e430af650c0547325afd1"
def git_image(rev,slug,filename):
    path=f"graphics/pokemon/prl_authoritative/{slug}/{filename}.png"
    contents=subprocess.check_output(["git","show",f"{rev}:{path}"],cwd=ROOT)
    return Image.open(io.BytesIO(contents)).copy()

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

# Snapshot files we are strictly forbidden to change, including all artwork
# that would change the appearance of an approved back sprite.
protected=[GFX/n/"back.png" for n in ("khang","nolax")]
protected += [GFX/n/filename for n in ("khang","nolax")
              for filename in ("normal.pal","shiny.pal")]
before={str(p):sha(p) for p in protected}

p=GFX/"khang/front.png"
original=git_image(ORIGINAL_KHANG,"khang","front")
assert original.size==(64,64) and original.mode=="P"
back=Image.open(GFX/"khang/back.png")
assert back.mode=="P" and back.size==(64,64) and back.info.get("transparency")==0
palette=back.getpalette()
assert len(palette)>=48

# Re-index original Khang's existing pixels to the new Khang RGB555 colour
# family shared with his approved current back. No pixels enter or leave the
# silhouette and no scaling, interpolation, new lines or pose changes.
remap={0:0,1:12,2:7,3:7,4:6,5:6,6:5,7:5,8:4,9:4,10:3,
       11:3,12:2,13:2,14:1,15:1}
cream={1:13,2:12,3:12,4:11,5:11,6:7,7:6}
out=Image.new("P",(64,64),0)
out.putpalette(palette)
src=original.load()
pixels=out.load()
for y in range(64):
    for x in range(64):
        v=src[x,y]
        dst=remap[v]
        # The original chest and stomach were the brightest tan. Colour
        # their existing lit pixels cream without changing the original pose.
        if 24 <= y <= 56 and ((x-31.5)/12)**2 + ((y-39)/15)**2 < 1:
            dst=cream.get(v,dst)
        pixels[x,y]=dst
out.save(p,transparency=0,optimize=True)

# Undo ONLY the two recent unwanted Nolax-front / party-icon edits; retain
# the approved back sprites and palettes. Both animation frames are included.
for slug,kind in (("nolax","front"),("khang","icon"),("nolax","icon")):
    file=GFX/slug/f"{kind}.png"
    image=git_image(PRE_REGRESSION,slug,kind)
    assert image.mode=="P" and image.size==((32,64) if kind=="icon" else (64,64))
    image.save(file,transparency=0,optimize=True)

for x in protected:
    assert sha(x)==before[str(x)],f"Protected graphic or palette altered: {x}"

restored=Image.open(p)
assert restored.getbbox()==original.getbbox(),"Original Khang silhouette changed"
for y in range(64):
    for x in range(64):
        assert bool(src[x,y])==bool(restored.getpixel((x,y))),"Shape changed"
assert restored.mode=="P" and max(restored.getdata())<=15
assert restored.getpalette()[:48]==palette[:48]
for slug,kind in (("nolax","front"),("khang","icon"),("nolax","icon")):
    ref=git_image(PRE_REGRESSION,slug,kind)
    now=Image.open(GFX/slug/f"{kind}.png")
    assert ref.tobytes()==now.tobytes() and ref.getpalette()[:48]==now.getpalette()[:48]
    assert now.info.get("transparency")==0
    assert max(now.getdata()) <= 15
print("PASS: Khang original front silhouette recoloured to current approved brown/cream back palette")
print("PASS: Nolax front and both normal-size party icons restored from",PRE_REGRESSION[:8])
print("PASS: both back sprite images plus both normal/shiny palettes unchanged, SHA256 verified")
