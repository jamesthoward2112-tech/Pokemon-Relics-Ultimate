#!/usr/bin/env python3
from pathlib import Path
from collections import Counter
from PIL import Image
root=Path("assets/insurgence_mega_jirachi")
for name in ["front","back","front_shiny","back_shiny"]:
    im=Image.open(root/f"source_{name}.png").convert("RGBA")
    w,h=im.size
    co=Counter(im.getdata())
    print("COLORS",name,"mode:",Image.open(root/f"source_{name}.png").mode,"RGBAunique",len(co))
    for k,n in co.most_common(30):
        xs=[];ys=[]
        for y in range(h):
            for x in range(w):
                if im.getpixel((x,y)) == k:
                    xs.append(x);ys.append(y)
        print(" ",k,n,"bounding",(min(xs),min(ys),max(xs)+1,max(ys)+1),
              "corner?",[im.getpixel(t)==k for t in [(0,0),(w-1,0),(0,h-1),(w-1,h-1)]])
    print("SAMPLE",name,
          "corners",[im.getpixel(t) for t in [(0,0),(w-1,0),(0,h-1),(w-1,h-1)]],
          "mid",[im.getpixel(t) for t in [(w//2,30),(w//2,h//2),(w//2,h-1),(10,h//2)]])
