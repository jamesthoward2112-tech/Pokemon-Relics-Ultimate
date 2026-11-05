#!/usr/bin/env python3
"""Job 13: pin only the user-selected G-Max Blastoise Pokésprite icon."""
import hashlib
import importlib.util
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSET = ROOT / "assets/pru_final_polish/fortotoise"
DEST = ROOT / "graphics/pokemon/prl_authoritative/fortotoise"
ICON = ASSET / "icon.png"
PIN = ASSET / "pokesprite_gmax_icon_GBA_pal3.png"
SOURCE = ASSET / "pokesprite_gmax_icon_source.png"

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

assert sha(SOURCE) == "c0bc21061a512b2e00aac77b785314129ab02ac2ec9645274938058fa9764875"
assert sha(ICON) == sha(PIN) == sha(DEST / "icon.png")
with Image.open(SOURCE) as source:
    assert source.size == (68, 56)
with Image.open(ICON) as icon:
    assert icon.mode == "P" and icon.size == (32, 64)
    assert icon.info.get("transparency") == 0
    assert max(icon.getdata()) < 16
    assert icon.crop((0,0,32,32)).tobytes() != icon.crop((0,32,32,64)).tobytes()
    installed_palette = [tuple(icon.getpalette()[i:i+3]) for i in range(0,48,3)]
jasc = (ROOT / "graphics/pokemon/icon_palettes/pal3.pal").read_text().splitlines()[3:19]
assert installed_palette == [tuple(map(int,s.split())) for s in jasc]

prepare = (ROOT / "tools/pru/prepare_user_fortotoise.py").read_text()
assert "pokesprite_gmax_icon_GBA_pal3.png" in prepare
assert 'graphics/pokemon/blastoise/mega/icon.png' not in prepare
installer = (ROOT / "tools/pru/install_final_polish_sprites.py").read_text()
assert '"fortotoise": 3' in installer
species = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
entry = species.split("PJR_RED_SPECIES(SPECIES_FORTOTOISE",1)[1].split("PJR_RED_SPECIES(",1)[0]
assert "sFortotoiseLevelUpLearnset, sBlastoiseTeachableLearnset, 600, 0, 5, 3)" in entry

# Verify the actual install palette conversion is lossless for the pinned PNG.
spec = importlib.util.spec_from_file_location("pru_final_icons", ROOT / "tools/pru/install_final_polish_sprites.py")
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)
indexed = mod.indexed_from_rgba(mod.make_icon_source("fortotoise"), mod.load_jasc(ROOT / "graphics/pokemon/icon_palettes/pal3.pal"), nearest=True)
assert indexed.tobytes() == Image.open(PIN).tobytes()

print("JOB13_POKESPRITE_ICON_PASS: 68x56 original; 32x64 two-frame, pal3, transparent index0, no Mega fallback")
print("JOB13_SCOPE: Only Fortotoise selected for this review; front/back not yet changed or approved")
