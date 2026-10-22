#!/usr/bin/env python3
"""PRU TRE P-form birds: source and prepared GBA-art integration regression."""
from pathlib import Path
from PIL import Image
import re

ROOT = Path(__file__).resolve().parents[2]
read = lambda p: (ROOT / p).read_text(encoding="utf8")
flow = read(".github/workflows/pru-clean-build.yml")
assert "python3 tools/pru/install_p_bird_sprites.py" in flow
roam = read("src/roamer.c")
hdr = read("include/roamer.h")
ow = read("src/overworld.c")
flags = read("include/constants/flags_hns.h")
icons = read("src/pokemon_icon.c")
for n in ("ARTICUNO", "ZAPDOS", "MOLTRES"):
    assert "SPECIES_" + n in roam
    assert "FLAG_PRU_" + n + "_ROAMER_INITIALIZED" in flags
    assert "SPECIES_" + n in icons
assert "TryAddRoamer(species, 70, ROAMER_LOC_TABLE_KANTO)" in roam
assert "EnsurePruKantoBirdRoamers();" in ow
assert "ApplyPruKantoBirdWeather();" in ow
assert "WEATHER_SNOW" in roam
assert "WEATHER_RAIN_THUNDERSTORM" in roam
assert "WEATHER_DROUGHT" in roam
assert "FLAG_PRU_KANTO_BIRDS_UNLOCKED" in ow
assert "void EnsurePruKantoBirdRoamers(void);" in hdr
assert "RestorePruDefeatedRoamers();" in ow

for name in ("articuno", "zapdos", "moltres"):
    path = ROOT / "graphics/pokemon" / name
    for filename, size in (
        ("anim_front.png", (64, 128)),
        ("back.png", (64, 64)),
        ("icon.png", (32, 64)),
    ):
        with Image.open(path / filename) as img:
            assert img.mode == "P", (name, filename, img.mode)
            assert img.size == size, (name, filename, img.size)
            assert max(img.getdata()) < 16, (name, filename)
            if filename == "icon.png":
                assert list(img.crop((0,0,32,32)).getdata()) == list(img.crop((0,32,32,64)).getdata())
    for kind in ("normal", "shiny"):
        lines = (path / f"{kind}.pal").read_text().splitlines()
        assert lines[:3] == ["JASC-PAL", "0100", "16"]
        assert len(lines[3:]) == 16
print("PASS: Articuno-P, Zapdos-P and Moltres-P native-size indexed graphics, palette, overworld weather and roamer hooks")
