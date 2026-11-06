#!/usr/bin/env python3
"""Install user-approved 6 Khang/Nolax sprites without touching other species."""
from pathlib import Path
from PIL import Image
import base64, zlib, struct
ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / "assets" / "pru_khang_nolax_20261106" / "six_sprites.zlib.b64"
payload = zlib.decompress(base64.b64decode(DATA.read_text().strip()))
i = 0
for name in ("Khang", "Nolax"):
    slug = name.lower()
    dst = ROOT / "graphics" / "pokemon" / "prl_authoritative" / slug
    dst.mkdir(parents=True, exist_ok=True)
    chunks = {}
    for kind in ("Front", "Back", "Icon"):
        w,h = ((32,32) if kind == "Icon" else (64,64))
        bytecount = w*h//2
        raw = payload[i:i+bytecount]; i += bytecount
        assert len(raw) == bytecount, (name,kind)
        pix = bytearray(w*h)
        pos = 0
        for ty in range(0,h,8):
            for tx in range(0,w,8):
                for row in range(8):
                    for col in range(0,8,2):
                        b=raw[pos]; pos+=1
                        pix[(ty+row)*w+tx+col]=b & 15
                        pix[(ty+row)*w+tx+col+1]=(b>>4)&15
        assert pos == bytecount
        chunks[kind]=(w,h,bytes(pix))
    palette=payload[i:i+32]; i+=32
    assert len(palette)==32
    rgb=[]
    for idx in range(16):
        v=struct.unpack_from("<H",palette,idx*2)[0]
        rgb.append(tuple(round(((v>>shift)&31)*255/31) for shift in (0,5,10)))
    flat=[c for triple in rgb for c in triple]+[0]*(768-48)
    for kind in ("Front", "Back", "Icon"):
        w,h,buf=chunks[kind]
        if kind == "Icon":
            # PRU expects two stacked 32x32 party animation frames, 32x64 total.
            buf=buf+buf
            h=64
        im=Image.frombytes("P",(w,h),buf)
        im.putpalette(flat)
        im.save(dst/(kind.lower()+".png"), transparency=0, optimize=True)
        assert max(im.getdata()) <=15
        assert im.size == ((32,64) if kind == "Icon" else (64,64))
    paltext="JASC-PAL\n0100\n16\n"+"".join(f"{r} {g} {b}\n" for (r,g,b) in rgb)
    (dst/"normal.pal").write_text(paltext)
    (dst/"shiny.pal").write_text(paltext)
    print(name, "front/back 64x64, party 32x64, GBA palette <= 16")
assert i==len(payload),(i,len(payload))
print("PASS: six imported indexed sprites")
