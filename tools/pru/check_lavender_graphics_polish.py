#!/usr/bin/env python3
"""PRU source and asset regressions for Lavender Tower and approved sprites."""

from pathlib import Path
import hashlib
import re
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]


def read(path):
    return (ROOT / path).read_text(encoding="utf-8")


# Every encounter on any of the seven Tower floors must use one existing,
# unmodified haunted Crystal Redux environment, not the per-map random choice.
bg = read("src/battle_bg.c")
scene_selector = bg.split("static u8 GetPruCrystalBattleBgIndex(u16 environment)", 1)[1]
assert "return 19;" in scene_selector.split("if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)", 1)[0], (
    "Tower override must run before any ordinary trainer or map-seeded scene selection"
)
for floor in range(1, 8):
    assert f"MAP_LAVENDER_SPIRIT_TOWER_{floor}F_HNS" in scene_selector, floor

print("PASS: all seven Lavender Tower floors use the original graveyard battle scene")


# Swamplith uses bespoke icon tag +8. The PC used to assign its fullscreen
# display-mon palette the same tag, so selecting another Pokémon overwrote the
# colours of Swamplith's box icon. Reserve all 14 icon tags before PC UI tags.
pc = read("src/pokemon_storage_system.c")
pc_tags = pc.split("PALTAG_MON_ICON_0 = POKE_ICON_BASE_PAL_TAG", 1)[1].split("};", 1)[0]
for index in range(8, 14):
    assert f"PALTAG_MON_ICON_{index}," in pc_tags, (
        f"storage UI tag +{index} must not collide with a dedicated icon palette"
    )
assert pc_tags.index("PALTAG_MON_ICON_13,") < pc_tags.index("PALTAG_DISPLAY_MON")

# GBA has only 16 OBJ palette slots. The PC already needs some for the cursor,
# big portrait, markings and icons. Do not waste 14 slots preloading every icon
# variant before knowing which ones are visible; load custom icons on demand.
pc_icon_init = pc.split("static void InitMonIconFields(void)\n{", 1)[1].split("\n}", 1)[0]
assert "LoadMonIconBasePalettes();" in pc_icon_init
assert "LoadMonIconPalettes();" not in pc_icon_init
pc_sprite_creator = pc.rsplit("static struct Sprite *CreateMonIconSprite(u16 species,", 1)[1]
pc_sprite_creator = pc_sprite_creator.split("static void DestroyBoxMonIcon", 1)[0]
assert "LoadMonIconPalette(species);" in pc_sprite_creator
assert "LoadMonIconPalette(SPECIES_SWAMPLITH);" in pc_icon_init

print("PASS: PC icon palette tags and loading protect Swamplith colours")


# The exact approved Elite Redux indexed Typhlosion Mega front must be what
# the ROM actually compiles, not a similarly named Insurgence/PRL replacement.
front = ROOT / "graphics/pokemon/prl_authoritative/pyroclast/front.png"
assert hashlib.sha256(front.read_bytes()).hexdigest() == (
    "cc3193a3668381c6d83c0642e0ead50cbfae0553081f770e1ce316fdbf842773"
), "Pyroclast must use the original TYPHLOSION_MEGA.png bytes"
with Image.open(front) as image:
    assert image.size == (64, 64) and image.mode == "P"
    assert len(image.getcolors(maxcolors=256)) <= 16

# Existing back and icon are approved and may not be changed/recoloured.
for name, digest in {
    "back.png": "f0e1b26ea40b6013146a289154aba02558af83f07a2df0e761d67a538efdd8b5",
    "icon.png": "947fb15afad11b415899a16f56fff722943899f82dd3e78e93e13a064b7d62cc",
}.items():
    art = ROOT / "graphics/pokemon/prl_authoritative/pyroclast" / name
    assert hashlib.sha256(art.read_bytes()).hexdigest() == digest, name

family = read("src/data/pokemon/species_info/pjr_families.h")
pyro = family.split("PJR_FINAL_SPECIES(SPECIES_PYROCLAST,", 1)[1].split("),", 1)[0]
assert re.search(r"sTyphlosionTeachableLearnset,\s*0,\s*8\b", pyro), (
    "Pyroclast's existing back art must sit eight pixels lower in battle"
)
gfx = read("src/data/graphics/pjr.h")
assert 'graphics/pokemon/prl_authoritative/pyroclast/front.4bpp.smol' in gfx
sync = read("tools/pru/sync_prl_authoritative_sprites.py")
assert "PYROCLAST_ELITE_REDUX_SHA256" in sync

print("PASS: exact Elite Redux Pyroclast front, approved back/icon and lower anchor")
