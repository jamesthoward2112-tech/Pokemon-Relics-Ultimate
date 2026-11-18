#!/usr/bin/env python3
"""Install 10 Nov 17 approved Eeveelution front/back pairs after donor overlays.

Source: ChatGPT Library PRU_Eeveelution_20_Sprites_v2.pixels.xz.b64.
This contains the final approved Eartheon ears and Eeveeon G-Max rear, with
joint 16-colour indexed GBA palettes for each front/back pair. Isolated PRU
test branch only; this does not change the released Alpha 5 baseline.
"""
from pathlib import Path
from PIL import Image
import base64
import hashlib
import lzma

ROOT = Path(__file__).resolve().parents[2]
PAYLOAD = ROOT / "assets/pru_eeveelutions_approved_20261118/PRU_Eeveelution_20_Sprites_v2.pixels.xz.b64"
DEST = ROOT / "graphics/pokemon/prl_authoritative"
NAMES = ("champeon", "drakeon", "eeveeon", "guardeon", "lepideon",
         "nimbeon", "obsideon", "omeon", "sphynxeon", "toxeon")
EXPECTED_SHA = "ec1d4d68fe6b69e1000e366072b041f2f5c99050ff8a051a80257e3b4c08a0b5"
# SHA-256 masks verify exact opaque pixels against each of the ten individual
# GBA-approved rear sprites recovered from 17 Nov in the Library.
EXPECTED_BACK_MASKS = (
    "efeabcc0d44e6efa829a245a528528b6f56dc84244d300b26f3cd8ac0c7fac06",
    "47893627bf2a73b6ef2ec79888bbe0cd885194d2542e8ef2fe743c0629b0b577",
    "2826698a08f9fc6bd5989114be070c3aac12c5c66701d917e99ab0ed4ed18b91",
    "6e057ac7ecdca18959a45de9a221cff7a3c700b4d1427f0960ef19a2dbfb1a86",
    "ae0e890ab82abe8d765350bccdf075f8d2a731d08a7e0ed805297e2a676fc19b",
    "814ace47b45dbcdeb75858533a9a6ed84c4996ef82975b9c829930b64b7f26f5",
    "45bb2b5a2dfc0a5f6fb113344965696b6375c15d2113cd6baa2b8263c367f9c1",
    "63881a775ad65b0e32e8aa0de3aeb7b0748a5f95526c626c2e3b744f478a990a",
    "e04421a990ec7cffc638bb91b0ea6d1f678ba7ccdee974426f528a0df281c1ab",
    "65a89539a098347d4d310354f5841b8bb89b5a55ce752c028078616ad1189f53",
)


def main():
    data = lzma.decompress(base64.b64decode(PAYLOAD.read_text().strip()))
    assert len(data) == len(NAMES) * (48 + 4096 + 4096), len(data)
    assert hashlib.sha256(data).hexdigest() == EXPECTED_SHA, "Approved source changed"
    pos = 0
    for number, name in enumerate(NAMES):
        pal = list(data[pos:pos+48]); pos += 48
        front = data[pos:pos+4096]; pos += 4096
        back = data[pos:pos+4096]; pos += 4096
        assert len(pal) == 48 and len(front) == len(back) == 4096
        assert max(front) <= 15 and max(back) <= 15, f"{name}: not GBA indexed"
        back_mask = bytes(int(index != 0) for index in back)
        assert hashlib.sha256(back_mask).hexdigest() == EXPECTED_BACK_MASKS[number], (
            name, "rear sprite differs from the 17 Nov approved pixels"
        )
        dest = DEST / name
        dest.mkdir(parents=True, exist_ok=True)
        for side, pixels in (("front", front), ("back", back)):
            sprite = Image.frombytes("P", (64, 64), pixels)
            sprite.putpalette(pal + [0] * (768 - len(pal)))
            sprite.save(dest / (side + ".png"), transparency=0)
            with Image.open(dest / (side + ".png")) as check:
                assert check.mode == "P" and check.size == (64, 64), (name, side)
                assert check.info.get("transparency") == 0, (name, side)
                assert len(check.getcolors(4097) or []) <= 16, (name, side)
        jasc = "JASC-PAL\\n0100\\n16\\n" + "".join(
            f"{pal[i]} {pal[i+1]} {pal[i+2]}\\n" for i in range(0, 48, 3))
        (dest / "normal.pal").write_text(jasc)
        (dest / "shiny.pal").write_text(jasc)  # Test only, no invented shiny recolour
        print(f"PASS: {name}: approved front/back, exact rear silhouette, 64x64 4bpp/shared 16 palette")
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
    print("PASS: all ten Nov 17 approved Eeveelution fronts and backs staged for PRU test")

if __name__ == "__main__":
    main()
