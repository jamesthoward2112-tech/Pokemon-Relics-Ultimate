#!/usr/bin/env python3
"""Install the original 64x64 Meowth balloon donor (no redrawing)."""
from pathlib import Path
import base64
import hashlib
from PIL import Image

src = Path("tools/pru/OriginalMeowthBalloon.indexed.png.base64")
raw = base64.b64decode(src.read_text().strip(), validate=True)
expected = "ffe986bb70797831b6852ad1ff29172efd2f4fc908615256e280dc456ebc620f"
assert hashlib.sha256(raw).hexdigest() == expected, "Balloon donor mismatch"
png = Path("graphics/object_events/pics/misc/pru_meowth_balloon_hns.png")
png.parent.mkdir(parents=True, exist_ok=True)
png.write_bytes(raw)
im = Image.open(png)
assert im.size == (64, 64) and im.mode == "P", "Original balloon must be 64x64 indexed"
assert im.info.get("transparency") == 0
assert len(im.getcolors(maxcolors=17)) <= 16

colors = [(0,0,0), (0,0,0), (222,189,65), (164,131,32), (255,213,180),
          (222,148,115), (246,189,148), (255,255,255), (57,139,0),
          (82,82,32), (131,205,49)]
colors += [(0,0,0)] * (16-len(colors))
palette = Path("graphics/object_events/palettes/pru_meowth_balloon_hns.pal")
palette.parent.mkdir(parents=True, exist_ok=True)
palette.write_text("JASC-PAL\n0100\n16\n" + "\n".join("%d %d %d" % c for c in colors)+"\n")
print("PRU original MrNightology Meowth balloon: 64x64 4bpp-compatible original art installed")
