#!/usr/bin/env python3
"""Verify Khang/Alphoracle PC icon indexed palettes and final ability."""

from pathlib import Path
import re
import hashlib
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
code = (ROOT / "src/pokemon_icon.c").read_text()
species = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()

def palette(symbol):
    found = re.search(r"static const u16 " + symbol + r"\[16\]\s*=\s*\{(.*?)\};", code, re.S)
    assert found, symbol
    return [tuple(map(int, rgb)) for rgb in re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", found.group(1))]

def donor_palette(name):
    with Image.open(ROOT / "graphics/pokemon/prl_authoritative" / name / "icon.png") as im:
        assert im.mode == "P" and im.size == (32, 64)
        src = im.getpalette()[:48]
    return [tuple(round(v * 31 / 255) for v in src[i:i + 3]) for i in range(0, 48, 3)]

# Khang's replacement icon is drawn from the approved sprite and must use
# the dedicated palette that matches its indexed pixels.
assert "{ sPRUKhangIconPalette, POKE_ICON_BASE_PAL_TAG + 18 }" in code
assert "{ sPRUNolaxIconPalette, POKE_ICON_BASE_PAL_TAG + 19 }" in code
assert re.search(r"if \(species == SPECIES_KHANG\)\s*return 18;", code)
assert re.search(r"if \(species == SPECIES_NOLAX\)\s*return 19;", code)
assert "gMonIcon_Khang" in species
assert re.search(r"gMonIcon_Khang,[\s\S]*?P_GBA_STYLE_SPECIES_ICONS \? 1 : 2\)", species)
assert "SPECIES_KHANG, 105, 105, 95, 50, 90, 110, TYPE_NORMAL, TYPE_FIGHTING" in species
assert "SPECIES_NOLAX, 100, 130, 80, 45, 90, 130, TYPE_NORMAL, TYPE_DARK" in species
khang_palette = palette("sPRUKhangIconPalette")
assert khang_palette[1:] == donor_palette("khang")[1:]
# Pin the user-approved 07729 battle assets and Nolax icon; only Khang's icon
# is intentionally regenerated to match the approved Khang front sprite.
expected_sha256 = {
    "khang/front.png": "88aab4c8a03d2899728aef588f5dd80e3c41573706947b1be06a73a2bb35c038",
    "khang/back.png": "c0811deea6934508a8af624943f29f557c833a64220d66809dbe7a2d78935fde",
    "khang/normal.pal": "2e1c21e532cd79b00132d9c368fa392ea4b67c3b51382edfc95b66c827578a90",
    "khang/shiny.pal": "2e1c21e532cd79b00132d9c368fa392ea4b67c3b51382edfc95b66c827578a90",
    "nolax/front.png": "4b027ee5bc1bacc6c5ffcdc83684249152baa889a75092d3b7a0a36b0f10045e",
    "nolax/back.png": "b934d0318b96933ab6748383f32b2f7f14defc8d21f77d066cd86acc21655037",
    "nolax/icon.png": "1c9311c5c18e030daf06a2188d2d23b74b7d1d855ede6f04fad30e239cdeef7a",
    "nolax/normal.pal": "d29d4e6e0c0a12f0749240f14c9ec64ae896c9ca98b3f0f232f4f2405150765b",
    "nolax/shiny.pal": "d29d4e6e0c0a12f0749240f14c9ec64ae896c9ca98b3f0f232f4f2405150765b",
}
for relative_path, expected_hash in expected_sha256.items():
    asset = ROOT / "graphics/pokemon/prl_authoritative" / relative_path
    assert hashlib.sha256(asset.read_bytes()).hexdigest() == expected_hash, relative_path

# Alphoracle's approved icon silhouette must remain intact but its pixels
# are reindexed to the shared palette #2; PC tag #14 is reserved for its
# large Pokémon portrait and caused scrolling colour corruption.
with Image.open(ROOT / "graphics/pokemon/alphoracle/icon.png") as icon, Image.open(ROOT / "graphics/pokemon/prl_authoritative/alphoracle/icon.png") as donor:
    assert icon.mode == donor.mode == "P" and icon.size == donor.size == (32, 64)
    assert icon.tobytes() == donor.tobytes()
    assert icon.info.get("transparency") == 0
assert re.search(r"if \(species == SPECIES_ALPHORACLE\)\s*return 2;", code)
block = species.split("[SPECIES_ALPHORACLE] =", 1)[1].split("[SPECIES_PINSIREX]", 1)[0]
assert "ABILITY_MAGIC_BOUNCE" in block
assert "ABILITY_FULL_METAL_BODY" not in block
print("PASS: Khang/Nolax icon palettes and types; Alphoracle keeps stable shared PC icon palette #2 and Magic Bounce")
