#!/usr/bin/env python3
"""Enlarged lossless preview of only the two player-approved baby Pokemon."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

R=Path(__file__).resolve().parents[2]
assets=R/"assets/pru_approved_babies"
gfx=R/"graphics/pokemon/prl_authoritative"
W,H=1350,630
sheet=Image.new("RGB",(W,H),(245,247,250))
d=ImageDraw.Draw(sheet)
d.text((28,12),"PRU Job 14 | Approved baby sprites (pixel-perfect enlarged preview)",fill=(25,29,37))
d.text((28,47),"GEMLIN: original ChatGPT pre-PoryPal artwork | flipped back | original purple + blue icon",fill=(66,68,83))
def panel(path,x,y,label,scale=3):
    src=Image.open(path)
    # Most old icon PNGs omit tRNS metadata even though index 0 is transparent
    # to the GBA engine. Preview must depict the in-game alpha, not opaque green.
    if src.mode=="P":
        src.info["transparency"]=0
    img=src.convert("RGBA")
    area=img.resize((img.width*scale,img.height*scale),Image.Resampling.NEAREST)
    bg=Image.new("RGBA",area.size,(230,233,240,255))
    bg.alpha_composite(area)
    sheet.paste(bg.convert("RGB"),(x,y))
    d.text((x,y-19),label,fill=(38,42,56))
panel(gfx/"gemlin"/"front.png",30,95,"Front 32x34",3)
panel(gfx/"gemlin"/"back.png",280,95,"Back 31x33 (flipped)",3)
panel(gfx/"gemlin"/"icon.png",570,95,"Icon two frames 18x21",3)
d.line((30,310,1320,310),fill=(205,209,218),width=2)
d.text((28,330),"SCARABUB: same blue original artwork, smaller and cleaned at GBA size; box icon remains BLUE pal3",fill=(66,68,83))
panel(assets/"scarabub"/"original_front.png",30,386,"Before front 60x54",3)
panel(gfx/"scarabub"/"front.png",260,386,"After front 44x40",3)
panel(assets/"scarabub"/"original_back.png",505,386,"Before back 60x56",3)
panel(gfx/"scarabub"/"back.png",750,386,"After back 44x41",3)
panel(gfx/"scarabub"/"icon.png",1000,386,"Blue icon pal3 (same pixels)",3)
out=R/"docs/PRU_Job14_Gemlin_Scarabub_Sprite_Comparison.png"
out.parent.mkdir(exist_ok=True)
sheet.save(out)
print(out)
