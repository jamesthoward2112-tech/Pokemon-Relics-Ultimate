#!/usr/bin/env python3
"""Verify build-538 Eeveelution pixels are the only source of scaled art."""
from pathlib import Path
from PIL import Image
import json

ROOT = Path(__file__).resolve().parents[2]
GFX = ROOT / "graphics/pokemon"
PINNED = ROOT / "assets/pru_eeveelution_build538"
EEVEELUTIONS = (
    "champeon", "lepideon", "guardeon", "obsideon", "toxeon",
    "sphynxeon", "omeon", "drakeon", "eeveeon", "nimbeon",
)


def expected_scaled(source: Image.Image, frame_height: int) -> tuple[list[int], list[int]]:
    width, height = source.size
    palette = source.getpalette()[:768]
    result = Image.new("P", (width, height), 0)
    result.putpalette(palette)
    for frame_y in range(0, height, frame_height):
        frame = source.crop((0, frame_y, width, frame_y + frame_height))
        scaled_w, scaled_h = round(width * .8), round(frame_height * .8)
        reduced = frame.resize((scaled_w, scaled_h), Image.Resampling.NEAREST)
        result.paste(reduced, ((width - scaled_w) // 2, frame_y + (frame_height - scaled_h) // 2))
    return list(result.getdata()), palette


manifest = json.loads((PINNED / "manifest.json").read_text())
assert manifest["source_commit"] == "3d6a0460d5c151de5bf3c7f1fe49cb6a94d38086"
assert manifest["pinned_prl_commit"] == "6ee9b984521ac6f2beaf995f771a726379e55c88"
for name in EEVEELUTIONS:
    for side in ("front", "back"):
        original = PINNED / name / f"{side}.png"
        output = GFX / "prl_authoritative" / name / f"{side}.png"
        with Image.open(original) as baseline, Image.open(output) as scaled:
            assert baseline.size == scaled.size == (64, 64) and baseline.mode == scaled.mode == "P"
            pixels, colors = expected_scaled(baseline, 64)
            assert list(scaled.getdata()) == pixels, (name, side, "not exact 80% nearest-neighbour of build 538")
            assert scaled.getpalette()[:768] == colors, (name, side, "palette changed")
            assert scaled.info.get("transparency") == 0
            assert scaled.info.get("PRU_SPRITE_BASE") == "build-538"
            assert scaled.info.get("PRU_SPRITE_SCALE") == "80%"
    original_icon = PINNED / name / "icon.png"
    output_icon = GFX / name / "icon.png"
    with Image.open(original_icon) as baseline, Image.open(output_icon) as scaled:
        assert baseline.size == scaled.size == (32, 64) and baseline.mode == scaled.mode == "P"
        pixels, colors = expected_scaled(baseline, 32)
        assert list(scaled.getdata()) == pixels, (name, "icon", "not exact 80% nearest-neighbour of build 538")
        assert scaled.getpalette()[:768] == colors, (name, "icon", "palette changed")
        assert scaled.info.get("transparency") == 0
        assert scaled.info.get("PRU_SPRITE_BASE") == "build-538"
        assert scaled.info.get("PRU_SPRITE_SCALE") == "80%"

pru = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()
nimbeon = pru.split("[SPECIES_NIMBEON] =", 1)[1].split("\n},", 1)[0]
assert ".iconPalIndex = 2," in nimbeon, "restore build-538 Nimbeon icon palette"
family = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
for name in EEVEELUTIONS:
    if name == "eeveeon":
        assert ".iconPalIndex = 7," in pru.split("[SPECIES_EEVEEON] =", 1)[1].split("\n},", 1)[0]
    elif name == "nimbeon":
        continue
    elif name == "drakeon":
        assert "gMonIcon_Drakeon, 2," in family
    else:
        block = family.split(f"[SPECIES_{name.upper()}] =", 1)[1].split("\n},", 1)[0]
        assert ".iconPalIndex = 2," in block, name

# Calf artwork/palette/icon choices remain part of this same build.
assert ".iconPalIndex = 5, // PRU Mootiny icon is indexed for the warm palette #5." in family
assert "gMonIcon_Miltitan, 0, sMiltitanLevelUpLearnset" in family
print("PASS: all 10 Eeveelutions are exact 80% reductions of build-538 pixels/palettes/icons; Nimbeon palette assignment restored; calf art retained")
