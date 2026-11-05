#!/usr/bin/env python3
"""Job 15: protect PC icon palettes while auditing 15 player-flagged species.

This test deliberately does NOT approve recolouring or resizing battle art.
"""
from pathlib import Path
import re
import sys
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/"tools/pru"))
from audit_custom_sprites_70 import (
  species_source, graphics_symbols, picture_symbols, png_from_symbol,
  effective_icon_palette, icon_palette_colors,
)

pc=(ROOT/"src/pokemon_storage_system.c").read_text()
icons=(ROOT/"src/pokemon_icon.c").read_text()
table=re.search(r"const struct SpritePalette gMonIconPaletteTable\[\]\s*=\s*\{(.*?)\};",icons,re.S)
assert table
indices=[int(n) for n in re.findall(r"POKE_ICON_BASE_PAL_TAG\s*\+\s*(\d+)",table.group(1))]
assert indices==list(range(len(indices)))
assert len(indices)<=32, "Icon tags now overlap the reserved PC UI palette range"
assert "PALTAG_DISPLAY_MON = POKE_ICON_BASE_PAL_TAG + 32" in pc
assert "PALTAG_MARKING_COMBO," in pc
assert "PALTAG_DISPLAY_MON = POKE_ICON_BASE_PAL_TAG + 14" not in pc
assert "GetMonIconPaletteIndexFromSpecies(species)" in pc
assert "sStorage->displayMonSprite->data[0] = 2;" in pc, "PC mosaic must not make selected sprites look broken"
creator=pc.rsplit("static struct Sprite *CreateMonIconSprite(u16 species,",1)[1]
creator=creator.split("static void DestroyBoxMonIcon",1)[0]
assert "LoadMonIconPalette(species);" in creator
setup=pc.split("static void InitMonIconFields(void)\n{",1)[1].split("\n}",1)[0]
assert "LoadMonIconBasePalettes();" in setup
assert "LoadMonIconPalette(SPECIES_SWAMPLITH);" not in setup
assert re.search(r"if\s*\(species == SPECIES_GEMLIN\)\s*return 16;",icons)

original=ROOT/"assets/pru_approved_babies/gemlin/icon.png"
installed=ROOT/"graphics/pokemon/prl_authoritative/gemlin/icon.png"
with Image.open(original) as src,Image.open(installed) as dst:
    assert src.size==dst.size==(32,64) and src.mode==dst.mode=="P"
    assert src.tobytes()==dst.tobytes(),"Gemlin icon artwork should remain exact"
    cols=icon_palette_colors(16)
    assert cols is not None and len(cols)==16
    used=set(src.getdata())
    pngcols=[tuple(src.getpalette()[3*i:3*i+3]) for i in range(16)]
    assert max(max(abs(pngcols[i][k]-cols[i][k]) for k in range(3)) for i in used)<6
    assert 0 in used

selected="NIMBEON DRAKEON CHAMPEON GRIMFOWL KABLOWFISH SUNFLORID SUDOWARDEN GEMLIN SCEPTITAN SOLAZIKEN CACTOMB COELOSSUS TROPISAUR TORKALDERA GEMIGOYLE".split()
expected_mismatches=set("NIMBEON DRAKEON CHAMPEON GRIMFOWL KABLOWFISH SUNFLORID SUDOWARDEN CACTOMB GEMIGOYLE".split())
syms=graphics_symbols()
problems=set()
for name in selected:
    src=species_source(name)
    icon_path=png_from_symbol(picture_symbols(src)["icon"],syms)
    assert icon_path and icon_path.is_file(),name
    with Image.open(icon_path) as icon:
        assert icon.mode=="P" and icon.size==(32,64),(name,icon_path)
        assert max(icon.getdata())<16
        colors=icon.getpalette()
        own=[tuple(colors[3*i:3*i+3]) for i in range(16)]
        idx=effective_icon_palette(name,src)
        linked=icon_palette_colors(idx)
        assert linked and len(linked)==16,(name,idx)
        used=set(icon.getdata())-{0}
        error=sum(sum((own[i][ch]-linked[i][ch])**2 for ch in range(3)) for i in used)/max(1,len(used))
        if error>1000: problems.add(name)
assert problems==expected_mismatches,(sorted(problems),sorted(expected_mismatches))
print("JOB15_PASS: Gemlin original palette 16 no longer collides with PC markings tag; 16-palette hardware constraints guarded")
print("JOB15_AUDIT: nine visually broken palettes identified for dedicated artwork-safe repairs: "+", ".join(sorted(problems)))
print("JOB15_AUDIT: the five other flagged icons use compatible palettes; must be checked visually, not recoloured automatically")
