#!/usr/bin/env python3
"""Restore original PRU Nolax FRONT and both original party icons.
Strictly preserve Khang's improved FRONT, and both approved BACK images plus
both existing battle palettes, so battle backs do not change appearance.
"""
import io
import re
import subprocess
import hashlib
from pathlib import Path
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
SPRITES=ROOT / "graphics" / "pokemon" / "prl_authoritative"
ICON_CODE=ROOT / "src" / "pokemon_icon.c"
BEFORE_REDRAWS="e5d1677118c3a28c0a2bbf8918e049ad6750330d"

def original_png(species,side):
    path=f"graphics/pokemon/prl_authoritative/{species}/{side}.png"
    b=subprocess.check_output(["git","show",f"{BEFORE_REDRAWS}:{path}"],cwd=ROOT)
    return Image.open(io.BytesIO(b)).copy()

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

# These files must remain byte-for-byte unchanged.
protected = [SPRITES/"khang"/"front.png"]
protected += [SPRITES/s/"back.png" for s in ("khang","nolax")]
protected += [SPRITES/s/n for s in ("khang","nolax") for n in ("normal.pal","shiny.pal")]
hashes={p:sha(p) for p in protected}

# Original Nolax FRONT pixel silhouette, pose, shading geometry and expression.
# Map old palette to current shared Nolax battle palette because FRONT and BACK
# share the same hardware palette. The existing back remains completely untouched.
old=original_png("nolax","front")
assert old.mode=="P" and old.size==(64,64) and old.info.get("transparency")==0
destination=SPRITES/"nolax"/"front.png"
recent=Image.open(destination)
assert recent.mode=="P" and recent.size==(64,64) and recent.info.get("transparency")==0
target_palette=recent.getpalette()
# Old original navy-blue, cream belly, red eye detail and greys.
# Hand-map shades to the approved 16-entry modern palette; keep shape identical.
mapping={
    0:0,  1:2,  2:4,  3:6,  4:6,
    5:11, 6:10, 7:9,  8:7,
    9:12, 10:13, 11:15, 12:14,
    13:8, 14:5, 15:2,
}
data=bytes(mapping[i] for i in old.tobytes())
out=Image.frombytes("P",old.size,data)
out.putpalette(target_palette)
out.save(destination,transparency=0,optimize=True)
assert out.getbbox()==old.getbbox()
assert all((a==0)==(b==0) for a,b in zip(old.tobytes(),out.tobytes()))
assert max(out.getdata())<16

# Restore both exact original animated 32x64 icon graphics (two 32x32 frames).
# Their source palettes are different from the newer icon redesign; register
# each original indexed palette separately in pokemon_icon.c for correct colours.
code=ICON_CODE.read_text(encoding="utf-8")
for species in ("khang","nolax"):
    legacy=original_png(species,"icon")
    assert legacy.mode=="P" and legacy.size==(32,64)
    # The original PNGs predate the transparent-index metadata. The PRU
    # icon engine treats palette slot 0 as transparency; add that on import.
    assert legacy.info.get("transparency",0)==0
    assert max(legacy.getdata())<16
    legacy.save(SPRITES/species/"icon.png",transparency=0,optimize=True)
    symbol="sPRU"+species.capitalize()+"IconPalette"
    colors=[tuple(round(v*31/255) for v in legacy.getpalette()[i*3:i*3+3]) for i in range(16)]
    lines=["    RGB(%d, %d, %d)," % c for c in colors]
    replacement="static const u16 "+symbol+"[16] =\n{\n"+"\n".join(lines)+"\n};"
    pattern=r"static const u16 "+re.escape(symbol)+r"\[16\]\s*=\s*\{.*?\};"
    code,count=re.subn(pattern,lambda m:replacement,code,flags=re.S)
    assert count==1,(symbol,count)
    restored=Image.open(SPRITES/species/"icon.png")
    assert legacy.tobytes()==restored.tobytes()
    print("PASS:",species,"original party icon restored exactly, with matching palette")

ICON_CODE.write_text(code,encoding="utf-8",newline="\n")
for p,h in hashes.items():
    assert sha(p)==h,f"PROTECTED ASSET CHANGED: {p}"
print("PASS: Nolax original front silhouette and expression restored (recoloured to shared battle palette)")
print("PASS: Khang improved front, both approved backs and both battle palettes byte-for-byte untouched")
