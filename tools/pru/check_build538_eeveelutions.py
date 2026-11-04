#!/usr/bin/env python3
"""Verify Eeveelution art and palettes exactly match unscaled build 538."""
from pathlib import Path
import json
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
GFX = ROOT / "graphics/pokemon"
PINNED = ROOT / "assets/pru_eeveelution_build538"
NAMES = (
    "champeon", "lepideon", "guardeon", "obsideon", "toxeon",
    "sphynxeon", "omeon", "drakeon", "eeveeon", "nimbeon",
)

manifest = json.loads((PINNED / "manifest.json").read_text())
assert manifest["source_commit"] == "3d6a0460d5c151de5bf3c7f1fe49cb6a94d38086"
for name in NAMES:
    for side in ("front.png", "back.png", "normal.pal", "shiny.pal"):
        expected = (PINNED / name / side).read_bytes()
        actual = (GFX / "prl_authoritative" / name / side).read_bytes()
        if side.endswith(".pal"):
            expected, actual = expected.replace(b"\r\n", b"\n"), actual.replace(b"\r\n", b"\n")
        assert actual == expected, (name, side, "must be exactly build 538")
    expected = (PINNED / name / "icon.png").read_bytes()
    actual = (GFX / name / "icon.png").read_bytes()
    assert actual == expected, (name, "icon.png", "must be exactly build 538")
    for path in (GFX / "prl_authoritative" / name / "front.png",
                 GFX / "prl_authoritative" / name / "back.png",
                 GFX / name / "icon.png"):
        with Image.open(path) as im:
            expected_size = (32, 64) if path.name == "icon.png" else (64, 64)
            assert im.mode == "P" and im.size == expected_size, (path, im.mode, im.size)
            assert im.info.get("transparency") in (None, 0), (path, im.info)

pru = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()
assert ".iconPalIndex = 2," in pru.split("[SPECIES_NIMBEON] =", 1)[1].split("\n},", 1)[0]
assert ".iconPalIndex = 7," in pru.split("[SPECIES_EEVEEON] =", 1)[1].split("\n},", 1)[0]
family = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
for name in ("champeon", "lepideon", "guardeon", "obsideon", "toxeon", "sphynxeon", "omeon"):
    block = family.split(f"[SPECIES_{name.upper()}] =", 1)[1].split("\n},", 1)[0]
    assert ".iconPalIndex = 2," in block, name
assert "gMonIcon_Drakeon, 2," in family

print("PASS: all 10 Eeveelutions' fronts, backs, palettes, icons and icon assignments match build 538 at original size")
