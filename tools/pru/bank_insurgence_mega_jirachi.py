#!/usr/bin/env python3
"""Bank the FOUR original Mega Jirachi PNGs from Pokémon Insurgence.

IMPORTANT: exact source sprites, not regular Jirachi, not TRE Jirachi-Bond,
not wiki thumbnails, not regenerated art. This step never touches game art.
"""
from pathlib import Path
from PIL import Image
from collections import Counter
import hashlib
import urllib.request

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / "assets" / "insurgence_mega_jirachi"
OUT.mkdir(parents=True, exist_ok=True)

SOURCES = {
    "front": "https://wiki.p-insurgence.com/images/8/84/385_1.png",
    "back": "https://wiki.p-insurgence.com/images/8/80/385b_1.png",
    "front_shiny": "https://wiki.p-insurgence.com/images/d/d8/385s_1.png",
    "back_shiny": "https://wiki.p-insurgence.com/images/c/c9/385sb_1.png",
}

for name, url in SOURCES.items():
    req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0 (PRU source-asset attribution)"})
    with urllib.request.urlopen(req, timeout=40) as response:
        blob = response.read()
    target = OUT / f"source_{name}.png"
    target.write_bytes(blob)
    with Image.open(target) as im:
        im.load()
        if im.format != "PNG" or min(im.size) < 64:
            raise ValueError(f"Unexpected source image for {name}: {im.format} {im.size}")
        rgba = im.convert("RGBA")
        mask = rgba.getchannel("A")
        bounds = mask.point(lambda x: 255 if x > 127 else 0).getbbox()
        numcolors = len({p[:3] for p in rgba.getdata() if p[3] > 127})
        print(f"{name}: source={im.size} actualBounds={bounds} "
              f"visibleRGB={numcolors} SHA256={hashlib.sha256(blob).hexdigest()} url={url}")

(OUT / "SOURCE.md").write_text("""# Mega Jirachi — Pokémon Insurgence original sprites

Exact full-resolution images linked in the **Mega Jirachi** (NOT plain Jirachi)
sprite subsection of the [Pokémon Insurgence wiki](https://wiki.p-insurgence.com/Jirachi_%28Pok%C3%A9mon%29).

- source_front.png: https://wiki.p-insurgence.com/images/8/84/385_1.png
- source_back.png: https://wiki.p-insurgence.com/images/8/80/385b_1.png
- source_front_shiny.png: https://wiki.p-insurgence.com/images/d/d8/385s_1.png
- source_back_shiny.png: https://wiki.p-insurgence.com/images/c/c9/385sb_1.png

Preserved source bytes. Any 64x64 GBA conversions must crop transparent
padding, retain aspect ratio, avoid stretching, and be verified visually.
Credit: Pokémon Insurgence team and original artists (as attributed by the game).
This is donor artwork only; PRU will retain normal Jirachi's species slot
and game mechanics; the static encounter map and overworld are unchanged.
""")
print("PASS: four untouched Insurgence Mega Jirachi original PNGs banked")
