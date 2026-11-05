#!/usr/bin/env python3
"""Pin player-approved Gemlin and carefully reduced Scarabub after all older art installers.

Gemlin = original pre-PoryPal ChatGPT art, front 32x34, flipped back 31x33,
  2-frame 18x21 icon, 16-colour original palette.
Scarabub = manual visual choice: 44x40 front and 44x41 back, generated from
  original indexed sprite using box sampling + nearest original palette.
  The original blue two-frame icon is retained; species icon index must be 3.
"""
from pathlib import Path
from PIL import Image
import shutil

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "assets/pru_approved_babies"
DEST = ROOT / "graphics/pokemon/prl_authoritative"

for species in ("gemlin", "scarabub"):
    for side in ("front", "back"):
        original = SOURCE / species / f"{side}.png"
        with Image.open(original) as image:
            assert image.mode == "P" and image.size == (64, 64)
            assert image.info.get("transparency") == 0
            assert max(image.getdata()) < 16
            assert image.getbbox() is not None
        dest = DEST / species / f"{side}.png"
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(original, dest)

# Gemlin's exact approved two-frame original icon, plus battle/shiny palettes:
# Do not remap pixels or shrink this icon a second time. It receives its own
# lazily loaded icon palette via GetPruCustomIconPaletteIndex.
for fname in ("icon.png", "normal.pal", "shiny.pal"):
    src = SOURCE / "gemlin" / fname
    assert src.is_file(), src
    shutil.copyfile(src, DEST / "gemlin" / fname)

print("BABY_SPRITES_INSTALLED: approved pre-PoryPal Gemlin (flipped back) and 44px blue Scarabub; no other species modified")
