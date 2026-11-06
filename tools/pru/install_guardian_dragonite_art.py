#!/usr/bin/env python3
"""Install byte-locked Job 18 Dragonite art and export its source palettes."""
from __future__ import annotations

import hashlib
import json
import shutil
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSET_DIR = ROOT / "assets/pru_guardian_dragonite"
DEST = ROOT / "graphics/pokemon/ancient_guardian_dragonite"
ICON_PALETTE = ROOT / "graphics/pokemon/icon_palettes/pal6.pal"
LOCK = json.loads((ASSET_DIR / "asset-lock.json").read_text())

def to_jasc(path: Path, output: Path) -> None:
    with Image.open(path) as im:
        im.load()
        palette = im.getpalette()
        assert im.mode == "P" and len(palette) >= 48
        colors = [tuple(palette[i:i + 3]) for i in range(0, 48, 3)]
    output.write_text("JASC-PAL\n0100\n16\n" + "".join(f"{r} {g} {b}\n" for r, g, b in colors))

for name, expected in LOCK["sha256"].items():
    src = ASSET_DIR / name
    assert hashlib.sha256(src.read_bytes()).hexdigest() == expected, name
    with Image.open(src) as im:
        assert im.mode == "P" and im.size == ((32, 64) if name == "icon.png" else (64, 64)), (name, im.size, im.mode)
        assert max(im.getdata()) < 16, name

DEST.mkdir(parents=True, exist_ok=True)
for name in LOCK["sha256"]:
    shutil.copyfile(ASSET_DIR / name, DEST / name)
to_jasc(ASSET_DIR / "front.png", DEST / "normal.pal")
to_jasc(ASSET_DIR / "front.png", DEST / "shiny.pal")
to_jasc(ASSET_DIR / "icon.png", ICON_PALETTE)
print("PASS: byte-locked blue-crystal Dragonite sprites installed without modifying standard Dragonite art")
