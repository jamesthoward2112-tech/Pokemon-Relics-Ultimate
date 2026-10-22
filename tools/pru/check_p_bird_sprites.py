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

# Party/PC sprite palettes must match the literal 4bpp image colour indices,
# not the separate battle palette or a manually reordered colour subset.
icon_defs = {
    "articuno": "sPRUArticunoPIconPalette",
    "zapdos": "sPRUZapdosPIconPalette",
    "moltres": "sPRUMoltresPIconPalette",
    "swamplith": "sPRUSwamplithIconPalette",
}
for slug, symbol in icon_defs.items():
    palette_match = re.search(
        r"static const u16 " + symbol + r"\[16\]\s*=\s*\{([^}]*)\}",
        icons, re.S,
    )
    assert palette_match, (slug, symbol)
    c_rgb = [
        tuple(map(int, xyz))
        for xyz in re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", palette_match.group(1))
    ]
    assert len(c_rgb) == 16, (slug, c_rgb)
    with Image.open(ROOT / "graphics/pokemon" / slug / "icon.png") as im:
        assert im.mode == "P" and im.size == (32, 64), slug
        assert im.getpalette() is not None, slug
        png_rgb = [
            tuple(im.getpalette()[i:i + 3]) for i in range(0, 48, 3)
        ]
        expected = [tuple(v // 8 for v in rgb) for rgb in png_rgb]
        assert c_rgb == expected, (
            slug, "icon palette does not match indexed sprite", c_rgb, expected
        )

# Swamplith's old PRL authoritative icon.4bpp uses different colour indices.
# The palette-matched local 32x64 icon must be compiled and not overwritten
# on repeat PRL donor synchronisation.
gfx = read("src/data/graphics/pru_pokemon.h")
sync = read("tools/pru/sync_prl_authoritative_sprites.py")
assert 'gMonIcon_Swamplith[] = INCBIN_U8("graphics/pokemon/swamplith/icon.4bpp")' in gfx
assert '"swamplith", # Green-detail' in sync

# A failed Poké Ball must not trigger the old flee-on-first-turn AI.
# Use competitive wild-mon moves instead, preserve Lati roaming behaviour,
# and reject stray opponent RUN commands as a second line of defence.
ai = read("src/battle_ai_main.c")
util = read("src/battle_util.c")
main = read("src/battle_main.c")
assert "flags = GetWildAiFlags() & ~AI_FLAG_ROAMING;" in ai
assert "flags = AI_FLAG_ROAMING;" in ai  # other roamers are unchanged
assert "gBattleMons[battlerAtk].species == SPECIES_ARTICUNO" in ai
assert "gBattleMons[battlerAtk].species == SPECIES_ZAPDOS" in ai
assert "gBattleMons[battlerAtk].species == SPECIES_MOLTRES" in ai
for n in ("ARTICUNO", "ZAPDOS", "MOLTRES"):
    assert "gBattleMons[gBattlerAttacker].species == SPECIES_" + n in util
assert "gBattleOutcome = B_OUTCOME_MON_FLED;" in util  # only for non-bird opponents
assert "gBattleOutcome == B_OUTCOME_WON" in roam
assert "RoamerMoveToOtherLocationSet(gEncounteredRoamerIndex);" in roam
assert "if ((!IS_HNS && gBattleOutcome == B_OUTCOME_WON) || gBattleOutcome == B_OUTCOME_CAUGHT)" in main

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
print("PASS: Articuno-P, Zapdos-P and Moltres-P native-size indexed graphics, palette, weather, no-flee battles, and defeat relocation")
