#!/usr/bin/env python3
"""Lock the five approved final-polish sprite donors and post-sync install order."""
from __future__ import annotations

import hashlib
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSETS = ROOT / "assets/pru_final_polish"

EXPECTED = {
    # Fortotoise is pinned separately by check_job13_pr72_sprite_extract.py;
    # legacy Mercury/PokeAPI/Mega sources are no longer authoritative.
    "torkaldera/front.png": "c3c5f51399a037d3b4a50ca63a4ce8ac28de05e36d03e4125cfcfe88f46ff35c",
    "torkaldera/back.png": "95ae8f8a73aafe65dfcc017e35de6f6be5031f97710b49f297ff7fd9cd6fdaef",
    "torkaldera/icon.png": "b544be0c27a79af1860749e895c7a87da7c371ccfcab5b63588854c6249f3fe8",
    "torkaldera/normal.pal": "685eae2a54eb7a2874b979b4bfe82f92c5aad8851f48f28d9c7a14d99ec9a2f3",
    "torkaldera/shiny.pal": "bda3afa232c2038458b9e7fcbcc469abaa851f6523feb86e6d212581e345b427",
    "tropisaur/front.png": "2359d76e46154119ee6ceb40748a51053e8e0f7c37f52db2bce7099b77da54a3",
    "tropisaur/back.png": "d55c06a2e5924770ce1b12b584366708e9e929b6a32b5b0a839e49de0b2554b4",
    "tropisaur/icon.png": "02754ff3f0beda9c2c8d6b96af30bb8109d7d5839e559c6474b67cf46ea0a198",
    "tropisaur/normal.pal": "94c8c03ca8ec6517a1b4474e3419b7950c31f2329e45fc029fe5410121087253",
    "tropisaur/shiny.pal": "0aa1787e52716a24ddeb7dd8cdf2a52bc1fef118bda2e95f54442c3825d3aca8",
    # James-locked Odyssey II selected package intentionally names these
    # historical alternatives front/back in this orientation.
    "cradily/front.png": "0e786369d82c38d09f30f61ea74e03e4816e1a2710b9924296f9d5c9ee7feaa2",
    "cradily/back.png": "ce43450243f7817da50a6fa014560b2684466330abfb7c51de82eeb970bd4585",
    "armaldo/front.png": "d11a5d6b2006bdd9481bd0a87c3d51fc84c77c81a85b5b742e291e6c9e47332f",
    "armaldo/back.png": "cbce188509404a303208b507ff7efaab5d8e8d6df28a33c6fa752e8cbda67b2e",
}

for relative, expected in EXPECTED.items():
    path = ASSETS / relative
    assert path.is_file(), f"missing approved donor: {relative}"
    payload = path.read_bytes()
    # Palette files are line-oriented text and historical Git attributes may
    # check them out with CRLF. Pin their canonical content independent of OS.
    if path.suffix == ".pal":
        payload = payload.replace(b"\r\n", b"\n")
    assert hashlib.sha256(payload).hexdigest() == expected, relative

workflow = (ROOT / ".github/workflows/pru-clean-build.yml").read_text()
sync = workflow.index("python3 tools/pru/sync_prl_authoritative_sprites.py")
install = workflow.index("python3 tools/pru/install_final_polish_sprites.py")
prepare_gmax = workflow.index("python3 tools/pru/prepare_user_fortotoise.py")
assert install > sync, "final-polish sprites must install after PRL sync"
assert sync < prepare_gmax < install, "prepare the owner's replacement Fortotoise art before final install"
assert "python3 tools/pru/check_final_polish_sprite_sources.py" in workflow
assert "python3 tools/pru/install_charaxis_gmax_relic.py" in workflow
assert "python3 tools/pru/restore_build538_eeveelution_art.py" in workflow
assert "python3 tools/pru/install_video_review_sprite_repairs.py" in workflow

for species, icon_palette in {
    "fortotoise": 3,
    "torkaldera": 2,
    "tropisaur": 1,
    "cradily": 0,
    "armaldo": 0,
}.items():
    folder = ROOT / "graphics/pokemon" / ("prl_authoritative" if species in {"fortotoise", "torkaldera", "tropisaur"} else "") / species
    for kind, size in (("front", (64, 64)), ("back", (64, 64)), ("icon", (32, 64))):
        with Image.open(folder / f"{kind}.png") as im:
            im.load()
            assert im.mode == "P" and im.size == size, (species, kind, im.mode, im.size)
            assert max(im.getdata()) < 16, (species, kind)
    # The installer rewrites icons to the species' existing shared palette;
    # no SpeciesInfo/save ABI change or extra runtime palette is introduced.
    manifest = (ASSETS / "manifest.txt").read_text()
    assert f"{species}: icon palette {icon_palette}" in manifest

# This regression runs after all artwork installation stages. It catches the
# previously observed Fortotoise overwrite after donor synchronization.
fort = ROOT / "graphics/pokemon/prl_authoritative/fortotoise"
for side in ("front", "back"):
    with Image.open(fort / f"{side}.png") as installed, Image.open(ASSETS / "fortotoise" / f"{side}.png") as donor:
        assert installed.mode == donor.mode == "P" and installed.size == donor.size == (64, 64)
        assert installed.tobytes() == donor.tobytes(), f"Fortotoise {side} was overwritten after final-polish install"
with Image.open(fort / "icon.png") as icon:
    assert icon.mode == "P" and icon.size == (32, 64) and icon.info.get("transparency") == 0
    assert icon.getbbox() is not None
with Image.open(ASSETS / "fortotoise/icon.png") as source_icon:
    assert source_icon.mode == "P" and source_icon.size == (32, 64)
    assert list(source_icon.getdata()) == list(Image.open(fort / "icon.png").getdata())
    assert source_icon.info.get("transparency") == 0
# Fortotoise must always use exact paired PR72 extraction and Pokésprite icon,
# never the historical unapproved PokeAPI/Mercury/Mega substitute files.
assert (ASSETS / "fortotoise/PR72_Fortotoise_front.png").is_file()
assert (ASSETS / "fortotoise/PR72_Fortotoise_back.png").is_file()
assert (ASSETS / "fortotoise/pokesprite_gmax_icon_GBA_pal3.png").is_file()
assert 'f"PR72_Fortotoise_{side}.png"' in (ROOT / "tools/pru/prepare_user_fortotoise.py").read_text()
assert "python3 tools/pru/check_job13_pr72_sprite_extract.py" in workflow

print("PASS: Fortotoise uses exactly paired PR72 ROM artwork and Pokésprite G-Max icon after final install")
print("PASS: Tortemple, Brontonana and James-locked Odyssey II fossil donors remain pinned")
print("PASS: all five install after PRL sync with indexed front/back/icon assets and save-safe IDs")
