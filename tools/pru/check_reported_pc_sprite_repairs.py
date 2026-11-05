#!/usr/bin/env python3
"""Prevent regression of the four reported Pokémon PC artwork problems."""
from pathlib import Path
import re
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
POKEMON=ROOT/"graphics/pokemon"
code=(ROOT/"src/pokemon_icon.c").read_text()
pc=(ROOT/"src/pokemon_storage_system.c").read_text()
assert re.search(r"if \(species == SPECIES_ALPHORACLE\)\s*return 2;",code)
assert re.search(r"if \(species == SPECIES_UNOWN_I\)\s*return 9;",code)
assert re.search(r"if \(species == SPECIES_MEWSION\)\s*return 2;",code)
assert "PALTAG_MON_ICON_13, // Moltres-P" in pc and "PALTAG_DISPLAY_MON = POKE_ICON_BASE_PAL_TAG + 32," in pc
# These were the two collision-prone bespoke palette tags (14,15).
assert not re.search(r"if \(species == SPECIES_ALPHORACLE\)\s*return 14;",code)
assert not re.search(r"if \(species == SPECIES_UNOWN_I\)\s*return 15;",code)
for name,path in [
    ("Alphoracle",POKEMON/"prl_authoritative/alphoracle/icon.png"),
    ("I-Unown",POKEMON/"unown_eye/icon.png"),
]:
    with Image.open(path) as im:
        assert im.mode=="P" and im.size==(32,64) and im.info.get("transparency")==0,(name,im.mode,im.size)
        assert max(im.getdata())<16,name
with Image.open(POKEMON/"unown_eye/icon.png") as im:
    used=set(im.getdata())
    assert 5 in used and 10 in used and 2 not in used,"I-Unown must stay dark with red eye"
with Image.open(POKEMON/"mewsion/icon.png") as im:
    assert im.mode=="P" and im.size==(32,64) and im.info.get("transparency")==0
    assert max(im.getdata())<16 and 0 in set(im.getdata())
    assert len(set(im.getdata()))>4,"Mewduo icon must retain its indexed colour detail"
for name in ("tropisaur","torkaldera"):
    for side in ("front","back"):
        path=POKEMON/"prl_authoritative"/name/(side+".png")
        with Image.open(path) as im:
            assert im.mode=="P" and im.size==(64,64) and im.info.get("transparency")==0,path
            assert max(im.getdata())<16,path
            assert 0 in set(im.getdata()), (path, "no transparent pixels")
for name, palette_index in (("tropisaur", 1), ("torkaldera", 2), ("coelossus", 2)):
    path = POKEMON / "prl_authoritative" / name / "icon.png"
    with Image.open(path) as icon:
        assert icon.mode == "P" and icon.size == (32,64) and icon.info.get("transparency") == 0, path
        indices = list(icon.getdata())
        assert 0 in indices and max(indices) < 16, f"{name}: opaque or out-of-range icon indices"
        assert icon.crop((0,0,32,32)).tobytes() == icon.crop((0,32,32,64)).tobytes(), f"{name}: icon frames differ"
    species = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()
    block = species.split(f"[SPECIES_{name.upper()}] =",1)[1].split("[SPECIES_",1)[0]
    if name == "torkaldera":
        assert "P_GBA_STYLE_SPECIES_ICONS ? 1 : 2" in block, "Torkaldera's rebuilt icon must follow runtime palette #2"
for name in ("adnokana", "cheauking"):
    path = POKEMON / name / "icon.png"
    with Image.open(path) as icon:
        assert icon.mode == "P" and icon.size == (32, 64) and icon.info.get("transparency") == 0, path
        assert max(icon.getdata()) < 16 and 0 in set(icon.getdata()), path
        assert icon.getpalette()[:48] == [v for line in (POKEMON / "icon_palettes/pal2.pal").read_text().splitlines()[3:19] for v in map(int, line.split())], path
    species = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()
    block = species.split(f"[SPECIES_{name.upper()}] =", 1)[1].split("[SPECIES_", 1)[0]
    assert ".iconPalIndex = 2," in block, name
manifest=(ROOT/"assets/pru_final_polish/manifest.txt").read_text()
assert "Elite Redux Tortemple" in manifest and "Elite Redux Brontonana" in manifest
# Pyroclast is an approved, untouched Elite Redux sprite; no installer changes it.
patcher=(ROOT/"tools/pru/repair_reported_pc_sprites.py").read_text()
assert "remove_donor_background(name)" in patcher
assert "fix_mewduo()" in patcher
assert 'for name in ("tropisaur","torkaldera"):' in patcher
assert not re.search(r"POKEMON\s*/\s*[\"'](?:prl_authoritative/)?pyroclast",patcher)
print("PASS: PC palette repairs, transparent donor icons, indexed Adnokana/Cheauking rebuilds, clean Elite Redux backgrounds; Pyroclast untouched")
