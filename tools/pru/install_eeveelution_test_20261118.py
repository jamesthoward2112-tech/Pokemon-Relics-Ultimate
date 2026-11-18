#!/usr/bin/env python3
"""Install ten approved PRU Eeveelution sprite pairs AFTER all donor/Build538 installers.
Isolated test build only. Existing PRU/PRR releases and species data are untouched.
"""
from pathlib import Path
from PIL import Image
import base64, hashlib, lzma

ROOT = Path(__file__).resolve().parents[2]
PAYLOAD = ROOT / "assets/pru_eeveelutions_approved_20261118/graphics.xz.b64"
DEST = ROOT / "graphics/pokemon/prl_authoritative"
NAMES = ("champeon", "drakeon", "eeveeon", "guardeon", "lepideon",
         "nimbeon", "obsideon", "omeon", "sphynxeon", "toxeon")
EXPECTED_SHA = "08c872654fd73ff46782a6035bce307d77606512ca822165a124cb936b56d992"

def main():
    data = lzma.decompress(base64.b64decode(PAYLOAD.read_text().strip()))
    assert len(data) == 10 * (2048 * 2 + 48), len(data)
    assert hashlib.sha256(data).hexdigest() == EXPECTED_SHA
    pos = 0
    for name in NAMES:
        back = data[pos:pos+2048]; pos += 2048
        front = data[pos:pos+2048]; pos += 2048
        pal = list(data[pos:pos+48]); pos += 48
        dest = DEST / name
        dest.mkdir(parents=True, exist_ok=True)
        for side, raw in (("front", front), ("back", back)):
            indices = [index for byte in raw for index in (byte & 15, byte >> 4)]
            assert len(indices) == 4096 and max(indices) < 16
            sprite = Image.new("P", (64, 64))
            sprite.putpalette(pal + [0]*(768-len(pal)))
            sprite.putdata(indices)
            sprite.save(dest / (side + ".png"), transparency=0)
            with Image.open(dest / (side + ".png")) as check:
                assert check.mode == "P" and check.size == (64, 64)
                assert check.info["transparency"] == 0
                assert max(check.getdata()) < 16
        jasc = "JASC-PAL\n0100\n16\n" + "".join(
            f"{pal[i]} {pal[i+1]} {pal[i+2]}\n" for i in range(0, 48, 3))
        (dest/"normal.pal").write_text(jasc)
        (dest/"shiny.pal").write_text(jasc)  # Test-only, no unapproved shiny recolours
        print(f"PASS: {name} front+back, 64x64 4bpp and one shared palette")
    assert pos == len(data)
    # This Alpha5 follower-recovery branch references noxichu/follower.png,
    # but that source PNG was never committed. Supply a scoped build-only
    # 8-frame, 32x32 one-tile sheet from its existing indexed icon frames.
    follower = DEST / "noxichu/follower.png"
    if not follower.exists():
        icon = DEST / "noxichu/icon.png"
        with Image.open(icon) as original:
            assert original.mode == "P" and original.size == (32, 64), (original.mode, original.size)
            sheet = Image.new("P", (32, 256), 0)
            sheet.putpalette(original.getpalette())
            for frame in range(8):
                region = original.crop((0, (frame % 2) * 32, 32, (frame % 2 + 1) * 32))
                sheet.paste(region, (0, frame * 32))
            sheet.save(follower, transparency=0)
        print("BUILD_ONLY: missing Noxichu follower input restored from existing indexed party icon; source branch unchanged")
    print("PASS: all ten approved Eeveelution pairs staged for PRU test")

if __name__ == "__main__":
    main()
