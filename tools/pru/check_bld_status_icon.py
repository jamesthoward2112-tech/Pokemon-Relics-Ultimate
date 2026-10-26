#!/usr/bin/env python3
"""PRU Bleeding battle UI: BLD graphic must be displayed for all battlers."""
from pathlib import Path
import re
src = Path("src/battle_interface.c").read_text()
battle = Path("include/constants/battle.h").read_text()
assert "#define STATUS1_BLEED" in battle
assert "STATUS1_BLEED)" in src
assert "sPruBleedingStatusGfx[battler]" in src
assert "PAL_STATUS_BLD" in src
assert "RGB(31, 0, 0)" in src, "BLD letters should be bright red against black"
assert "FillPalette(RGB(0, 0, 0), OBJ_PLTT_OFFSET + blackPltOffset" in src, (
    "the opaque BLD background palette entry must be solid black"
)
assert "else if (IS_HNS && (status & STATUS1_BLEED))" in src
assert "CpuCopy32(statusGfxPtr," in src
assert "FillPalette(sStatusIconColors[statusPalId]" in src
body = src.split("static const u32 sPruBleedingStatusGfx[4][24] =",1)[1].split("};",1)[0]
words = re.findall(r"0x[0-9a-fA-F]{8}",body)
assert len(words) == 4*24, len(words)
for battler in range(4):
    data = b"".join(int(v,16).to_bytes(4,"little") for v in words[battler*24:(battler+1)*24])
    assert len(data)==96
    pixels = [(byte >> nibble) & 15 for byte in data for nibble in (0,4)]
    assert set(pixels) == {11, 12+battler}, (battler, set(pixels))
    assert pixels.count(11) > pixels.count(12+battler), "BLD must have an opaque black background"
    assert all((12+battler) in pixels[tile*64:(tile+1)*64] for tile in range(3)), (
        "all B, L and D letters should remain red"
    )
print("PRU_BLD_STATUS_PASS: opaque black BLD badge with vivid red letters in all four battler palettes")
