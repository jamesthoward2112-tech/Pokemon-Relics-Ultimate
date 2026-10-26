#!/usr/bin/env python3
"""Birth Island uses the approved BYOXYS encounter sprite and matching overworld."""
import json
from pathlib import Path

from PIL import Image

root = Path(__file__).resolve().parents[2]
read = lambda p: (root / p).read_text()

birth = json.loads(read("data/maps/BirthIsland_Exterior_hns/map.json"))
assert any(o["graphics_id"] == "OBJ_EVENT_GFX_PRU_BYOXYS_HNS"
           for o in birth["object_events"]), "Birth Island must spawn BYOXYS"
assert "OBJ_EVENT_GFX_PRU_BYOXYS_HNS" in read("include/constants/event_objects.h")
assert "sPicTable_PruByoxys_hns" in read("src/data/object_events/object_event_pic_tables.h")
assert "gObjectEventGraphicsInfo_PruByoxys_hns" in read("src/data/object_events/object_event_graphics_info.h")
ow = Image.open(root / "graphics/object_events/pics/misc/pru_byoxys_hns.png")
assert ow.size == (64, 32), "Overworld must contain two 32x32 frames"
assert Image.open(root / "graphics/pokemon/deoxys/byoxys_anim_front_gba.png").size == (64, 128)
assert Image.open(root / "graphics/pokemon/deoxys/byoxys_back_gba.png").size == (64, 128)
assert "deoxys/byoxys_anim_front_gba.4bpp.smol" in read("src/data/graphics/pru_pokemon.h")
assert ".frontPic = gMonFrontPic_PruByoxys" in read("src/data/pokemon/species_info/gen_3_families.h")
print("PASS: Birth Island BYOXYS overworld and battle graphics")
