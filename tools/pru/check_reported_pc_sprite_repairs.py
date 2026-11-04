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
assert "PALTAG_MON_ICON_13, // Moltres-P" in pc and "PALTAG_DISPLAY_MON," in pc
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
manifest=(ROOT/"assets/pru_final_polish/manifest.txt").read_text()
assert "Elite Redux Tortemple" in manifest and "Elite Redux Brontonana" in manifest
# Pyroclast is an approved, untouched Elite Redux sprite; no installer changes it.
patcher=(ROOT/"tools/pru/repair_reported_pc_sprites.py").read_text()
assert "remove_donor_background(name)" in patcher
assert "fix_mewduo()" in patcher
assert 'for name in ("tropisaur","torkaldera"):' in patcher
assert not re.search(r"POKEMON\s*/\s*[\"'](?:prl_authoritative/)?pyroclast",patcher)
print("PASS: 4 PC sprite repairs, dark I-Unown, stable Alphoracle and clean Elite Redux donor backgrounds; Pyroclast untouched")
