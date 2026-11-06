#!/usr/bin/env python3
"""Verify locked user-approved Job 18 Dragonite artwork and exclusive references."""
from __future__ import annotations

import hashlib
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ART = ROOT / "assets/pru_guardian_dragonite"
EXPECTED = {
    "front.png": "b35cd8dcb12cae133beb608144902172262fda90110e28b45008fbe2bbf84589",
    "back.png": "8b68818cd56def13e61beb9703db428151ad52fd4734098ca34a5ce35c560cd0",
    "icon.png": "332ab7c028bb6b51c84e282ebc39d16ccd82cad367e1156a83a1fd16253656c8",
}

for name, expected in EXPECTED.items():
    path = ART / name
    assert hashlib.sha256(path.read_bytes()).hexdigest() == expected, f"approved source changed: {name}"
    with Image.open(path) as image:
        assert image.mode == "P", (name, image.mode)
        assert image.size == ((32, 64) if name == "icon.png" else (64, 64)), (name, image.size)
        assert max(image.getdata()) < 16, name

species = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
assert "gMonFrontPic_AncientGuardianDragonite" in species
assert "gMonBackPic_AncientGuardianDragonite" in species
assert "gMonIcon_AncientGuardianDragonite" in species
assert "PJR_E4_VISUAL_FORM(SPECIES_ANCIENT_GUARDIAN_DRAGONITE," in species
assert "BODY_COLOR_BROWN,gMonFrontPic_AncientGuardianDragonite" in species
assert "gMonIcon_AncientGuardianDragonite,0,sDragoniteLevelUpLearnset" in species
icon_code = (ROOT / "src/pokemon_icon.c").read_text()
assert "if (species == SPECIES_ANCIENT_GUARDIAN_DRAGONITE)\n        return 17;" in icon_code

print("PASS: approved Dragonite artwork is byte-locked, 4bpp-ready, and registered to its dedicated species")
