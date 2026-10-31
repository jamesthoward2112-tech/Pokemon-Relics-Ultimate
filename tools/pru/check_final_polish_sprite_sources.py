#!/usr/bin/env python3
"""Lock the five approved final-polish sprite donors and post-sync install order."""
from __future__ import annotations

import hashlib
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSETS = ROOT / "assets/pru_final_polish"

EXPECTED = {
    "fortotoise/front.png": "2eccfcd24c2efb04b88f268575283bccd66e26c4b231a4d686effbdc74954548",
    "fortotoise/back.png": "e4850e2bf2cad0cb166508559c48a820281b40661ac732ac7e1ef91ac4ce4ea8",
    "fortotoise/normal.pal": "ccd94d730c8c295824b46f48766ee28d1cc1bbc0464bbe00150d9d0430d7c859",
    "torkaldera/front.png": "c3c5f51399a037d3b4a50ca63a4ce8ac28de05e36d03e4125cfcfe88f46ff35c",
    "torkaldera/back.png": "95ae8f8a73aafe65dfcc017e35de6f6be5031f97710b49f297ff7fd9cd6fdaef",
    "torkaldera/icon.png": "b544be0c27a79af1860749e895c7a87da7c371ccfcab5b63588854c6249f3fe8",
    "torkaldera/normal.pal": "2ab503c3782be7e8e60bdc7be4c8367eac526741af4a472e732530c3a6e151f4",
    "torkaldera/shiny.pal": "5b8d6f3b7afff3b862293f5b05d7c0a7d99bb14a2a2f0fd81602127f562b64ad",
    "tropisaur/front.png": "2359d76e46154119ee6ceb40748a51053e8e0f7c37f52db2bce7099b77da54a3",
    "tropisaur/back.png": "d55c06a2e5924770ce1b12b584366708e9e929b6a32b5b0a839e49de0b2554b4",
    "tropisaur/icon.png": "02754ff3f0beda9c2c8d6b96af30bb8109d7d5839e559c6474b67cf46ea0a198",
    "tropisaur/normal.pal": "d18752f3054bf3fb51ecc06389cef1c36956a632a15923469b079e4bc2dfe0b7",
    "tropisaur/shiny.pal": "a2136ce95651282fded3d3742274c115b14396120460e6d1e83602d93530f420",
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
    assert hashlib.sha256(path.read_bytes()).hexdigest() == expected, relative

workflow = (ROOT / ".github/workflows/pru-clean-build.yml").read_text()
sync = workflow.index("python3 tools/pru/sync_prl_authoritative_sprites.py")
install = workflow.index("python3 tools/pru/install_final_polish_sprites.py")
assert install > sync, "final-polish sprites must install after PRL sync"
assert "python3 tools/pru/check_final_polish_sprite_sources.py" in workflow

for species, icon_palette in {
    "fortotoise": 2,
    "torkaldera": 1,
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

print("PASS: approved Fortotoise, Tortemple, Brontonana and James-locked Odyssey II fossil donors")
print("PASS: all five install after PRL sync with indexed front/back/icon assets and save-safe IDs")
