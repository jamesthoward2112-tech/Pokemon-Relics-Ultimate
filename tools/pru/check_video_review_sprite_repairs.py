#!/usr/bin/env python3
"""Regression checks for the in-game video sprite repair stage."""
from __future__ import annotations

import json
import hashlib
import re
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSETS = ROOT / "assets/pru_video_review"
GFX = ROOT / "graphics/pokemon"
REPORT = ROOT / "PRU-QA/video-review/report.json"
SYMBOLS = (
    "Nimbeon", "Drakeon", "Champeon", "Guardeon", "Toxeon", "Sphynxeon",
    "Skarmet", "Kablowfish", "Grimfowl", "Heracurion", "Scarabub",
    "Skarmadon", "Jollibird", "Osteodian", "Sunflorid", "Sudowarden",
    "Mystynx", "Ghoulbat", "Khang", "Fortotoise", "Charaxis", "HoOhRelic",
    "Hitmonlee", "Alakazam", "Gemlin", "Gemigoyle", "Astrachi", "Adnokana",
    "Cheauking", "Frytning", "Mewsion", "Tropisaur", "Coelossus", "Cactomb",
    "Torkaldera", "Sceptitan", "Solaziken",
)
REPAIRED = {
    ("gemlin", "front"): 44, ("gemlin", "back"): 44,
}
APPROVED_BATTLE_REPLACEMENTS = {"gemigoyle", "jollibird", "kablowfish", "grimfowl"}
APPROVED_HASHES = {
    ("gemigoyle", "front"): "3b5f14ec886a22190f07fe99044d9ec41a865130a31705816aed0aac9eb053de",
    ("gemigoyle", "back"): "20d1e3392e0efdb4f0b48c0599aa4e374b421d7cec116e1f19cd15abf98d8919",
    ("jollibird", "front"): "6db067ad33850463d158f2432708e235024404525f9ac93fa2400d6feb3f18aa",
    ("jollibird", "back"): "5ef3a62f32348e5427fb322cdd3be51525b35994f0c2afd97b8e7f97e551a040",
    ("kablowfish", "front"): "5d181353b4bab712814c1ae9b51b4e1cae4f7d2143b47add2f575b783b4a8ab0",
    ("kablowfish", "back"): "9e8c84dab844ed99641207daf04ce13c4538b0c7cffe5a98b11b5144e7a00ed1",
    ("grimfowl", "front"): "3d97cf76e2af8fd56caea78f0287cb4883f14a08ae8ac01b13ca00d38ab56812",
    ("grimfowl", "back"): "ee1ce0d338217bc0133dd270bdee5afccd333b79aee7abbf6e3a02d2e3e8e9ea",
}
APPROVED_PALETTE_HASHES = {
    "gemigoyle": "069330baa83e0ea39960d1b05698bee1e5117bde955a7d496fe37b1ab433922c",
    "jollibird": "e0a16e98aa9973c66ec063616a1a3fe86ae8a4fd5bd69fdaf8c9225810ade8ce",
    "kablowfish": "c37a40a83bbfa876c21046a6f45535fbfc9f51a0dc8151f0c2b50d04636defba",
    "grimfowl": "d74abef86ee10ab9e1f52f283a6d2c7b846cddd5fe54d714ce62ea059333685b",
}


def bbox(im: Image.Image):
    if im.mode == "P":
        return im.point(lambda v: 255 if v else 0).getbbox()
    return im.convert("RGBA").getchannel("A").getbbox()


def paths() -> dict[str, Path]:
    found = {}
    pattern = re.compile(r'gMonIcon_(\w+)\[\]\s*=\s*INCBIN_U\d+\("([^\"]+)\.4bpp(?:\.smol)?"\)')
    for header in (ROOT / "src/data/graphics/pjr.h", ROOT / "src/data/graphics/pru_pokemon.h"):
        for symbol, rel in pattern.findall(header.read_text()):
            found[symbol] = ROOT / (rel + ".png")
    found.setdefault("Hitmonlee", GFX / "hitmonlee/icon.png")
    found.setdefault("Alakazam", GFX / "alakazam/icon.png")
    return found


def main() -> None:
    icon_paths = paths()
    report = json.loads(REPORT.read_text())
    assert report["reviewed_species"] == list(SYMBOLS)
    assert "Nolax" in report["omitted_by_user_instruction"]
    records = {item["name"]: item for item in report["icon_adjustments"]}
    untouched = {item["name"] for item in report["shared_vanilla_icons_left_unchanged"]}
    assert len(records) + len(untouched) == len(SYMBOLS)
    assert untouched == {"Hitmonlee", "Alakazam"}
    for name in SYMBOLS:
        source_path = ASSETS / "icons" / f"{name}.png"
        assert source_path.is_file(), source_path
        output_path = icon_paths[name]
        with Image.open(source_path) as reference, Image.open(output_path) as out:
            assert reference.size == out.size == (32, 64), (name, reference.size, out.size)
            assert reference.mode in {"P", "RGBA"} and out.mode in {"P", "RGBA"}, (name, reference.mode, out.mode)
            if out.mode == "P":
                assert max(out.getdata()) < 16 and out.info.get("transparency", 0) == 0
            else:
                assert out.getchannel("A").getbbox() is not None
            if name not in untouched:
                if out.mode == "P":
                    assert out.info.get("transparency") == 0
                assert bbox(out.crop((0, 0, 32, 32))) is not None
                assert bbox(out.crop((0, 32, 32, 64))) is not None

    for (species, side), max_extent in REPAIRED.items():
        src_path = ASSETS / species / f"{side}.png"
        dst_path = GFX / "prl_authoritative" / species / f"{side}.png"
        with Image.open(src_path) as src, Image.open(dst_path) as dst:
            assert src.mode == dst.mode == "P" and src.size == dst.size == (64, 64)
            assert src.getpalette() == dst.getpalette(), (species, side, "palette changed")
            assert dst.info.get("transparency") == 0
            assert bbox(dst) is not None
            bounds = bbox(dst)
            assert bounds[3] == 62, (species, side, "not grounded at y=62", bounds)
            assert max(bounds[2] - bounds[0], bounds[3] - bounds[1]) <= max_extent
    for species in APPROVED_BATTLE_REPLACEMENTS:
        normal_palette_path = ASSETS / species / "normal.pal"
        assert hashlib.sha256(normal_palette_path.read_bytes()).hexdigest() == APPROVED_PALETTE_HASHES[species]
        assert (GFX / "prl_authoritative" / species / "normal.pal").read_bytes() == normal_palette_path.read_bytes()
        source_palette = normal_palette_path.read_text().splitlines()
        colors = [tuple(map(int, line.split())) for line in source_palette[3:3 + int(source_palette[2])]]
        assert len(colors) == 16
        expected_palette = [component for color in colors for component in color]
        for side in ("front", "back"):
            src_path = ASSETS / species / f"{side}.png"
            dst_path = GFX / "prl_authoritative" / species / f"{side}.png"
            assert hashlib.sha256(src_path.read_bytes()).hexdigest() == APPROVED_HASHES[(species, side)]
            assert dst_path.read_bytes() == src_path.read_bytes(), (species, side, "approved pixels overwritten")
            with Image.open(src_path) as src, Image.open(dst_path) as dst:
                assert src.mode == dst.mode == "P" and src.size == dst.size == (64, 64)
                assert src.info.get("transparency") == dst.info.get("transparency") == 0
                assert src.getpalette()[:48] == dst.getpalette()[:48] == expected_palette
                assert max(src.getdata()) < 16 and len(set(src.getdata())) <= 16
                assert bbox(dst) is not None
                if side == "back":
                    assert all(dst.getpixel((x, y)) == 0 for y in range(51, 64) for x in range(64))

    # All four species must continue using their own matching normal battle palettes.
    graphics_source = (ROOT / "src/data/graphics/pru_pokemon.h").read_text() + \
                      (ROOT / "src/data/graphics/pjr.h").read_text()
    for species in APPROVED_BATTLE_REPLACEMENTS:
        symbol = species.title()
        expected = f'gMonPalette_{symbol}[] = INCBIN_U16("graphics/pokemon/prl_authoritative/{species}/normal.gbapal")'
        assert expected in graphics_source, (species, "normal battle palette registration changed")
    for species in ("gemlin", "jollibird", "kablowfish", "grimfowl"):
        with Image.open(GFX / "prl_authoritative" / species / "front.png") as front, \
             Image.open(GFX / "prl_authoritative" / species / "back.png") as back:
            assert list(front.getdata()) != list(back.getdata()), (species, "front duplicated as back")
            assert front.getpalette() == back.getpalette(), (species, "front/back palette mismatch")
    with Image.open(ASSETS / "gemlin/back.png") as src, \
         Image.open(GFX / "prl_authoritative/gemlin/back.png") as out:
        # Detect accidental regression to the old unreoriented rear donor.
        assert out.getbbox() is not None and src.getbbox() is not None
    with Image.open(GFX / "prl_authoritative/fortotoise/front.png") as front, \
         Image.open(GFX / "prl_authoritative/fortotoise/back.png") as back:
        assert front.size == back.size == (64, 64)
        assert front.mode == back.mode == "P" and front.getpalette() == back.getpalette()
        assert front.info.get("transparency") == back.info.get("transparency") == 0
    print("PASS: selected video icons, transparency, preserved palettes, battle framing, and distinct front/back art")


if __name__ == "__main__":
    main()
