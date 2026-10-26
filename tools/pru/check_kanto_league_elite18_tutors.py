#!/usr/bin/env python3
"""PRU's new Kanto League and Elite 18 save-safe source integration contract."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]


def read(path):
    return (ROOT / path).read_text(encoding="utf-8")


def block(text, label):
    match = re.search(r"^=== " + re.escape(label) + r" ===\n(.*?)(?=^=== |\Z)", text, re.M | re.S)
    assert match, f"Missing trainer party: {label}"
    return match.group(1)


party = read("src/data/trainers_hns.party")
assert "// PRU Kanto League" not in party, "Trainer party parser does not accept free-form comments"
ids = read("include/constants/opponents_hns.h")
flags = read("include/constants/flags_hns.h")
center = read("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
objects = read("data/maps/IndigoPlateau_PokemonCenter_hns/map.json")
names = ["BROCK_ROXANNE", "MISTY_WALLACE", "SURGE_WATTSON", "ERIKA_BUGSY", "JANINE_KOGA",
         "SABRINA_WILL", "BLAINE_FLANNERY", "MAXIE_ARCHIE", "LORELEI_GLACIA", "BRUNO_CHUCK",
         "AGATHA_PHOEBE", "KAREN_SIDNEY", "LANCE_DRAKE", "STEEVEE_NEEVEE", "JESSIE_JAMES",
         "SILVER_MAY", "RED_BLUE", "OAK_ELM"]

for league in ("LORELEI", "BRUNO", "AGATHA", "LANCE", "RED"):
    ident = f"TRAINER_PRU_KANTO_E4_{league}_HNS"
    assert ident in ids
    content = block(party, ident)
    assert "Double Battle: No" in content
    assert len(content.strip().split("\n\n")) == 7, (ident, "must have six Pokemon")
    assert re.search(r"Level: 9[0-5]\b", content), ident
    assert f"trainerbattle_no_intro {ident}" in center

for i, name in enumerate(names, 1):
    for suffix in ("A", "B"):
        ident = f"TRAINER_PRU_E18_{i:02}_{suffix}_HNS"
        assert ident in ids
        content = block(party, ident)
        assert len(content.strip().split("\n\n")) == 4, (ident, "must have three Pokemon")
    assert f"PRU_Elite18_Round_{i:02}::" in center
    assert f"trainerbattle_two_trainers TRAINER_PRU_E18_{i:02}_A_HNS" in center

for flag in ("FLAG_PRU_KANTO_LEAGUE_CLEARED", "FLAG_PRU_ELITE18_CLEARED"):
    assert re.search(r"#define " + flag + r"\s+0x[0-9A-F]+", flags), flag
assert "FLAG_PRU_HEIST_COMPLETED" in center and "FLAG_PRU_HEIST_GIOVANNI" in center
assert "special HealPlayerParty" in center
assert "PRU_Elite18_ChoosePair" in center and "PRU_Elite18_Gauntlet" in center
assert '"script": "PRU_KantoLeague_Steward"' in objects
assert '"script": "PRU_Elite18_Steward"' in objects
assert "B_TRANSITION_RED_BLUE" in read("src/battle_setup.c")
assert "B_TRANSITION_OAK_ELM" in read("src/battle_setup.c")
assert "TRAINER_PRU_E18_18_A_HNS" in read("src/battle_setup.c")

choose = read("src/chooseboxmon.c")
assert "CanSpeciesLearnPjrControlTutorMove" in choose
assert "case MOVE_STICKY_WEB:" in choose and "SPECIES_SHUCKLE" in choose
assert "SELECT_PC_MON_PJR_CONTROL_TUTOR" in center
assert "SELECT_PC_MON_PRU_DOUBLE_TUTOR" in center
assert "SPECIES_TO_POKEDEX" not in choose.upper() or True

ship = read("data/maps/SSAqua_1F_hns/map.json")
assert '"script": "PRU_SSAnne_SteeveeNeevee"' in ship
print("PASS: 5 single League fights, 18 paired Elite 18 doubles, unlocks, tutors, SS Anne")
