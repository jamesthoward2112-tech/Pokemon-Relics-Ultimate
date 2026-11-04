#!/usr/bin/env python3
"""Guard the Jessie & James donor backs and document the ten unavailable E4 backs."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
species = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
graphics = (ROOT / "src/data/graphics/pjr.h").read_text()
unresolved = {
    "ALAKAZAM_RELIC", "SLOWKING_RELIC", "BEEDRILL_RELIC", "CROBAT_RELIC",
    "HITMONCHAN_RELIC", "HITMONLEE_RELIC", "MACHAMP_RELIC", "HOUNDOOM_RELIC",
    "GYARADOS_RELIC", "DRAGONITE_RELIC",
}
fixed = {
    "ASUDEM_JJ": "AsudemJJ", "NIDOGOD_JJ": "NidogodJJ",
    "VICTREEBEL_REDUX_JJ": "VictreebelReduxJJ",
    "TYRANITAR_REDUX_JJ": "TyranitarReduxJJ",
}
for name in unresolved | set(fixed) | {"NIDOKING_X_BLUE"}:
    m = re.search(rf"PJR_E4_VISUAL_FORM\(SPECIES_{name},([^\n]+)", species)
    assert m, f"missing visual form {name}"
    row = m.group(1)
    symbols = re.findall(r"gMon(?:FrontPic|BackPic)_\w+", row)
    assert len(symbols) >= 2, f"{name}: explicit front/back arguments missing"
    front, back = symbols[:2]
    if name in fixed:
        assert back == "gMonBackPic_" + fixed[name], (name, back)
        assert back != front
        assert back + "[]" in graphics, f"missing graphics registration {back}"
    else:
        assert back == front, f"{name}: unexpected guessed rear source {back}"
        assert f"{name}" in unresolved or name == "NIDOKING_X_BLUE"

for name, slug in {
    "AsudemJJ": "arbok/asudem", "NidogodJJ": "nidoking/nidogod",
    "VictreebelReduxJJ": "victreebel/redux", "TyranitarReduxJJ": "tyranitar/mega_redux",
}.items():
    path = ROOT / "graphics/pokemon" / slug / "back.png"
    assert path.is_file(), path

assert ".backPic = back," in species
print("PASS: all four Jessie & James visual forms use their own distinct back assets")
print("REVIEW: ten Elite Four Relic forms and Nidoking X Blue retain explicit front fallbacks; authentic back sources unavailable")
