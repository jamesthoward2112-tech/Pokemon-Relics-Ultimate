#!/usr/bin/env python3
"""Protect the approved PRU title art from the PJR title regression."""

import hashlib
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
asset = ROOT / "assets/pru_title/Noxichu_Title_GBA_240x160_256colour.png"
assert hashlib.sha256(asset.read_bytes()).hexdigest() == (
    "0cfdc68858e6818c771dd10e3d79b41a41658f642c0aaec7cd017b2cc60a2c64"
), "Approved PRU title image changed"
image = Image.open(asset)
assert image.mode == "P" and image.size == (240, 160)

raw = ROOT / "graphics/title_screen/pru/PRU_TitleScreen_Mode4.8bpp"
palette = ROOT / "graphics/title_screen/pru/PRU_TitleScreen_Mode4.gbapal"
assert raw.is_file() and len(raw.read_bytes()) == 38_400
assert palette.is_file() and len(palette.read_bytes()) == 512
assert raw.read_bytes() == image.tobytes(), "Compiled title pixels differ from approved image"

source = (ROOT / "src/title_screen.c").read_text()
assert 'graphics/title_screen/pru/PRU_TitleScreen_Mode4.8bpp' in source
assert 'graphics/title_screen/pru/PRU_TitleScreen_Mode4.gbapal' in source
assert "graphics/title_screen/pjr/PJR_TitleScreen_Mode4" not in source
assert "CB2_InitPruTitleScreen();" in source
assert "CreatePressStartBanner(START_BANNER_X, 138);" in source

print("PASS: title screen links the approved PRU Noxichu image and preserves flashing PRESS START")
