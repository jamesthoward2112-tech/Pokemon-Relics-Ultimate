#!/usr/bin/env python3
"""Regression checks for the in-game video sprite repair stage."""
from __future__ import annotations

import json
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
    ("jollibird", "front"): 44, ("jollibird", "back"): 50,
    ("kablowfish", "front"): 49, ("kablowfish", "back"): 47,
    ("grimfowl", "front"): 52, ("grimfowl", "back"): 50,
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
        with Image.open(source_path) as src, Image.open(output_path) as out:
            assert src.size == out.size == (32, 64), (name, src.size, out.size)
            assert src.mode == out.mode and out.mode in {"P", "RGBA"}, (name, src.mode, out.mode)
            if out.mode == "P":
                assert src.getpalette() == out.getpalette()
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
