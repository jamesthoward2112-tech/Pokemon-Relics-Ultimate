#!/usr/bin/env python3
"""Job 12: source and transition-simulation tests for one post-E20 RELICS Celebi."""
import itertools
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
read = lambda p: (ROOT / p).read_text(encoding="utf-8")
ilex = read("data/maps/IlexForest_hns/scripts.inc")
lab = read("data/maps/RuinsOfAlph_Lab_hns/scripts.inc")
hof = read("data/maps/PokemonLeague_HallOfFame_hns/scripts.inc")
azalea = read("data/maps/AzaleaTown_KurtsHouse_hns/scripts.inc")
objects = json.loads(read("data/maps/IlexForest_hns/map.json"))["object_events"]
flags = ["FLAG_IS_CHAMPION", "FLAG_PRU_ELITE18_CLEARED", "FLAG_PJR_RELIC_UNOWN_I"]
legacy = "FLAG_CAUGHT_CELEBI"
relic = "FLAG_PJR_RELIC_CELEBI"

def block(text, start, end):
    assert text.count(start) == 1, start
    assert text.count(end) >= 1, end
    return text.split(start, 1)[1].split(end, 1)[0]

trans = block(ilex, "IlexForest_OnTransition:", "IlexForest_EventScript_ReenterWhenFarfetchdLeaving::")
shrine = block(ilex, "IlexForest_EventScript_Shrine::", "IlexForest_EventScript_Shrine_PreRelics::")
actor = block(ilex, "IlexForest_hns_RelicCelebi::", "IlexForest_hns_RelicCelebi_Unavailable::")
old = block(ilex, "IlexForest_EventScript_Celebi_Event::", "IlexForest_EventScript_SecondCelebi::")
second = block(ilex, "IlexForest_EventScript_SecondCelebi::", "IlexForest_EventScript_Sign::")
battle = block(lab, "RuinsOfAlph_Lab_EventScript_RelicCelebi::", "RuinsOfAlph_Lab_EventScript_RelicSuicune::")
scientist = block(lab, "RuinsOfAlph_Lab_EventScript_Scientist1::", "RuinsOfAlph_Lab_EventScript_RelicNeedsCrest::")

for flag in flags:
    assert f"goto_if_unset {flag}," in trans, flag
    assert f"goto_if_unset {flag}," in shrine, flag
    assert f"goto_if_unset {flag}," in actor, flag
    assert f"goto_if_unset {flag}," in battle, flag
assert trans.index("call_if_set FLAG_CAUGHT_CELEBI") > trans.index("goto_if_unset FLAG_PJR_RELIC_UNOWN_I")
assert trans.index("call_if_set FLAG_CAUGHT_CELEBI") < trans.index("clearflag FLAG_TEMP_6")
assert "setflag FLAG_PJR_RELIC_CELEBI" in trans
assert "call_if_set FLAG_CAUGHT_CELEBI, RuinsOfAlph_Lab_EventScript_CreditLegacyCelebi" in scientist
assert scientist.index("goto_if_unset FLAG_PJR_RELIC_UNOWN_I") < scientist.index("call_if_set FLAG_CAUGHT_CELEBI")
for b in (shrine, actor, battle):
    assert f"goto_if_set {relic}," in b
    assert f"goto_if_set {legacy}," in b
    assert b.index(f"goto_if_set {legacy}") < b.index("goto RuinsOfAlph_Lab_EventScript_RelicCelebi") if b != battle else b.index(f"goto_if_set {legacy}") < b.index("seteventmon SPECIES_CELEBI")
assert 'seteventmon SPECIES_CELEBI, 40' not in ilex
assert 'seteventmon SPECIES_CELEBI, 67' in battle
assert lab.count("seteventmon SPECIES_CELEBI, 67") == 1
assert "BattleSetup_StartLegendaryBattle" not in old + second
assert "BattleSetup_StartLegendaryBattle" in battle
assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, RuinsOfAlph_Lab_EventScript_RelicCelebiCaught" in battle
assert "goto RuinsOfAlph_Lab_EventScript_RelicRetry" in battle
caught = block(lab, "RuinsOfAlph_Lab_EventScript_RelicCelebiCaught::", "RuinsOfAlph_Lab_EventScript_RelicSuicune::")
assert "setflag FLAG_CAUGHT_CELEBI" in caught and "setflag FLAG_PJR_RELIC_CELEBI" in caught
assert "setflag FLAG_TEMP_6" in caught
assert "clearflag FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI" not in hof
assert "setflag FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI" in hof
assert "call_if_set FLAG_CAUGHT_CELEBI, PokemonLeague_HallOfFame_EventScript_SpawnSecondCelebi" not in hof
assert "FLAG_HIDE_CELEBI" in trans and "FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI" in trans
assert "GS BALL" in ilex and "ITEM_GS_BALL" in azalea

relic_actors = [o for o in objects if o.get("script") == "IlexForest_hns_RelicCelebi"]
assert len(relic_actors) == 1 and relic_actors[0]["flag"] == "FLAG_TEMP_6"
retired = [o for o in objects if o.get("script") == "IlexForest_EventScript_SecondCelebi"]
assert len(retired) == 1 and retired[0]["flag"] == "FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI"

# Execute the actual Ilex Forest ON_TRANSITION script's flow over legacy/save
# combinations. This is a focused interpreter of the event commands it uses.
source_lines = ilex.splitlines()
labels = {}
for ix, line in enumerate(source_lines):
    m = re.fullmatch(r"([A-Za-z_][A-Za-z0-9_]*)::?", line.strip())
    if m:
        labels[m.group(1)] = ix
assert "IlexForest_OnTransition" in labels
assert "IlexForest_OnTransition_CreditLegacyCelebi" in labels
def enter(saved_flags):
    current = set(saved_flags)
    pc = labels["IlexForest_OnTransition"] + 1
    stack = []
    for steps in range(100):
        line = source_lines[pc].split("@", 1)[0].strip()
        pc += 1
        if not line or line.endswith(":"):
            continue
        bits=line.split()
        cmd=bits[0]; arg=bits[1].rstrip(",") if len(bits)>1 else ""
        target=bits[2] if len(bits)>2 else ""
        if cmd=="setflag":
            current.add(arg)
        elif cmd=="clearflag":
            current.discard(arg)
        elif cmd=="goto_if_unset":
            if arg not in current: pc=labels[target]
        elif cmd=="goto_if_set":
            if arg in current: pc=labels[target]
        elif cmd=="call_if_set":
            if arg in current:
                stack.append(pc);pc=labels[target]
        elif cmd=="goto":
            pc=labels[arg]
        elif cmd=="return":
            pc=stack.pop()
        elif cmd=="end":
            return current
        elif cmd in ("callnative","call_if_eq"):
            continue # unrelated map/NPC state, no Celebi writes
        else:
            raise AssertionError(("Unexpected event command", cmd, steps))
    raise AssertionError("Event transition failed to terminate")

for champion, elite20, unown_i, old_caught, already_relic in itertools.product((0,1), repeat=5):
    initial={flag for flag,value in zip(flags,(champion,elite20,unown_i)) if value}
    if old_caught: initial.add(legacy)
    if already_relic: initial.add(relic)
    final=enter(initial)
    unlocked=bool(champion and elite20 and unown_i)
    credited=bool(already_relic or (unlocked and old_caught))
    assert (relic in final)==credited, (initial,final)
    assert ("FLAG_TEMP_6" not in final)==(unlocked and not credited), (initial,final)
    assert "FLAG_HIDE_CELEBI" in final and "FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI" in final

# Specific acceptance cases are among the 32 simulated combinations:
# pre-E4 with state 9, post-Kanto pre-E20, normal post-Unown, and legacy
# Celebi owner (including old Kanto clear). KO/run never sets completion flag.
assert "goto_if_eq VAR_AZALEA_TOWN_STATE" not in shrine

# Old Alola donor content mislabeled a visible TAPU BULU actor as a Celebi
# battle. Keep that legendary encounter intact, but fight the depicted species.
alola = read("data/maps/UlaUla_Forest_hns/scripts.inc")
alola_objects = json.loads(read("data/maps/UlaUla_Forest_hns/map.json"))["object_events"]
assert any(o.get("script") == "Alola_Ulaula_BattleVsTapuBulu" and
           o.get("graphics_id") == "OBJ_EVENT_GFX_SPECIES(TAPU_BULU)" for o in alola_objects)
assert "seteventmon SPECIES_TAPU_BULU, 60" in alola
assert "playmoncry SPECIES_TAPU_BULU, CRY_MODE_ENCOUNTER" in alola
all_celebi_events = [
    str(path.relative_to(ROOT)).replace("\\", "/")
    for path in (ROOT / "data/maps").glob("*/scripts.inc")
    for line in path.read_text(encoding="utf-8").splitlines()
    if re.match(r"^\s*seteventmon\s+SPECIES_CELEBI\b", line)
]
assert all_celebi_events == ["data/maps/RuinsOfAlph_Lab_hns/scripts.inc"], all_celebi_events
print("JOB12_CELEBI_PASS: 32 progression states, legacy saves, one Celebi encounter across all maps, Tapu Bulu donor repaired")
