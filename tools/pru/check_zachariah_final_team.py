#!/usr/bin/env python3
"""Verify the optional Mt Silver Zachariah battle uses his exact six Pokémon."""
import json
import re
from pathlib import Path
root=Path(__file__).resolve().parents[2]
trainers=(root/"src/data/trainers_hns.party").read_text(encoding="utf-8")
constants=(root/"include/constants/opponents_hns.h").read_text(encoding="utf-8")
mapinfo=json.loads((root/"data/maps/MtSilver_PokemonCenter_hns/map.json").read_text(encoding="utf-8"))
script=(root/"data/maps/MtSilver_PokemonCenter_hns/scripts.inc").read_text(encoding="utf-8")
credits=(root/"src/data/credits_pru.h").read_text(encoding="utf-8")
name="TRAINER_PRU_ZACHARIAH_MT_SILVER_HNS"
assert f"#define {name}" in constants
assert re.search(rf"^#define\s+{name}\s+786$",constants,re.M)
assert re.search(r"^#define\s+TRAINERS_COUNT_HNS\s+787$",constants,re.M)
assert trainers.count(f"=== {name} ===")==1
section=trainers.split(f"=== {name} ===\n",1)[1].split("\n=== TRAINER_",1)[0]
assert "Name: Zachariah" in section and "AI: Smart Trainer / Prediction" in section
assert "Double Battle: No" in section and "Pic: Cooltrainer M" in section
mons=re.findall(r"^([A-Za-z][A-Za-z -]+) @ ([^\n]+)\nLevel: (\d+)",section,re.M)
expected=["Charaxis","Dragonite","Pyroclast","Pikachu","Edensaur","Gengar"]
assert [m[0] for m in mons]==expected, f"Wrong final team: {mons}"
assert [int(m[2]) for m in mons]==[96,97,98,100,99,100]
assert mons[3][1]=="Light Ball" and mons[3][0]=="Pikachu", "Keep Pikachu unevolved, with Light Ball"
assert all(section.count("IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe") >= 6 for _ in [0])
assert section.count("EVs: ")==6
assert section.count("\n- ")==24, "Each of the six needs four usable moves"
objects=[x for x in mapinfo["object_events"] if x.get("script")=="MtSilver_PokemonCenter_EventScript_Zachariah"]
assert len(objects)==1 and (objects[0]["x"],objects[0]["y"])==(3,5)
assert objects[0]["trainer_type"]=="TRAINER_TYPE_NONE", "Battle is optional, on interaction"
assert "trainerbattle_single "+name in script
assert "MtSilver_PokemonCenter_Text_ZachariahAfter" in script
assert "ZACHARIAH SULLIVAN" in credits and "FIRST PLAYTESTER" in credits
early=trainers.split("=== TRAINER_MIKEY_HNS ===\n",1)[1].split("\n=== TRAINER_",1)[0]
assert "Name: MIKEY" in early and "Hoothoot\nLevel: 5" in early and "Sentret\nLevel: 8" in early
print("PASS: Mt Silver optional Zachariah battle, exact six 96-100 team, first-playtester credits and save-safe ID")
