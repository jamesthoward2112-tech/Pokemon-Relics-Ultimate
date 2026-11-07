#!/usr/bin/env python3
"""Sprite QA: six game assets, indexed depth and separate icon palette routing."""
from pathlib import Path
from PIL import Image
root=Path(__file__).resolve().parents[2]
s=(root/'src/pokemon_icon.c').read_text(encoding='utf-8')
for species in ('khang','nolax'):
  d=root/'graphics/pokemon/prl_authoritative'/species
  for asset,size in (('front',(64,64)),('back',(64,64)),('icon',(32,64))):
    im=Image.open(d/(asset+'.png'))
    assert im.size==size,(species,asset,im.size)
    assert im.mode=='P', (species,asset,im.mode)
    assert im.info.get('transparency')==0, (species,asset,'non-transparent palette index')
    assert max(im.getdata())<=15, (species,asset,'invalid 4bpp index')
    assert len(im.getcolors())<=16, (species,asset,'too many colours')
    if asset=='icon':
      # Original PRU icons have two DIFFERENT 32x32 animation frames.
      # Do not duplicate a frame or shrink the original animation.
      import subprocess, io
      legacy_path=f'graphics/pokemon/prl_authoritative/{species}/icon.png'
      old=Image.open(io.BytesIO(subprocess.check_output(['git','show','e5d16771:'+legacy_path],cwd=root)))
      assert im.tobytes()==old.tobytes(),(species,'icon animation differs from original')
  p=(d/'normal.pal').read_text().splitlines()
  assert p[0]=='JASC-PAL' and p[2]=='16' and len(p)==19
  assert ('SPECIES_'+species.upper()) in s
  assert ('sPRU'+species.capitalize()+'IconPalette') in s
  assert (d/'normal.pal').read_bytes()==(d/'shiny.pal').read_bytes()
  print('PASS',species,'front/back 64x64; icon 32x64; palette16; transparent0')
print('PASS: GBA-ready 6 sprites, isolated palettes')
