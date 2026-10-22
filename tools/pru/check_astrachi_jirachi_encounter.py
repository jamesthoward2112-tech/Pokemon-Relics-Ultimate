#!/usr/bin/env python3
"""Source regression checks for PRU Jirachi + Astrachi encounter.
Full ROM compilation and mGBA smoke run separately in the workflow.
"""
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
read = lambda p: (ROOT / p).read_text(encoding="utf-8")
event = read("data/maps/MtMoon_Outside_hns/scripts.inc")
gate = event.split("MtMoon_Outside_EventScript_WhiteRock::", 1)[1].split("MtMoon_OutsideEventScript_WhiteRockNoReaction::", 1)[0]
assert "specialvar VAR_RESULT, PruIsJirachiCaught" in gate
assert "goto_if_eq VAR_RESULT, TRUE, MtMoon_Outside_EventScript_WhiteRockAstrachiCheck" in gate
assert "goto_if_set FLAG_SUMMONED_MTMOON_JIRACHI" in gate
assert ("goto_if_unset FLAG_NIGHT_POKEMON, MtMoon_Outside_EventScript_WhiteRockSpawnJirachi\n"
        "\tgoto MtMoon_OutsideEventScript_WhiteRockNoReaction\n"
        "MtMoon_Outside_EventScript_WhiteRockAstrachiCheck::") in gate
assert "goto_if_set FLAG_CAUGHT_MTMOON_ASTRACHI, MtMoon_OutsideEventScript_WhiteRockNoReaction" in gate
assert "goto_if_set FLAG_SUMMONED_MTMOON_ASTRACHI, MtMoon_OutsideEventScript_WhiteRockNoReaction" in gate
assert "seteventmon SPECIES_JIRACHI, 50" in event
assert "seteventmon SPECIES_ASTRACHI, 70" in event
assert "goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtMoon_Outside_EventScript_AstrachiCaught" in event
assert "setflag FLAG_CAUGHT_MTMOON_ASTRACHI" in event
assert "goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MtMoon_Outside_EventScript_AstrachiRan" in event
assert "clearflag FLAG_HIDE_MTMOON_ASTRACHI" in event
flags = read("include/constants/flags_hns.h")
for symbol, value in {"FLAG_HIDE_MTMOON_ASTRACHI": "0x4E0",
                      "FLAG_SUMMONED_MTMOON_ASTRACHI": "0x4E1",
                      "FLAG_CAUGHT_MTMOON_ASTRACHI": "0x4E2"}.items():
    assert f"#define {symbol}" in flags and value in flags.split(f"#define {symbol}", 1)[1].split("\n",1)[0]
overworld = read("src/overworld.c")
assert "FlagGet(FLAG_CAUGHT_MTMOON_ASTRACHI)" in overworld
assert "FlagGet(FLAG_SUMMONED_MTMOON_ASTRACHI)" in overworld
special = read("src/field_specials.c")
# A 'specialvar' command stores the special's u16 return value. The prior
# void function assigned VAR_RESULT directly, then scrcmd overwrote it with
# an undefined return register: user could catch Jirachi yet never get Astrachi.
assert "u16 PruIsJirachiCaught(void)" in special, "Stone gate must be return-valued for specialvar"
gate_fn = special.split("u16 PruIsJirachiCaught(void)", 1)[1]
assert "FLAG_GET_CAUGHT" in gate_fn
assert "MON_DATA_SPECIES, NULL) == SPECIES_JIRACHI" in gate_fn
assert "return TRUE;" in gate_fn and "return FALSE;" in gate_fn
assert "gSpecialVar_Result =" not in gate_fn, "Do not fake a specialvar result via side effect"
sprite = ROOT / "graphics/pokemon/astrachi/overworld.png"
assert sprite.is_file() and sprite.stat().st_size > 0
info = read("src/data/pokemon/species_info/pru_custom.h")
assert "sPicTable_Astrachi" in info and "gOverworldPalette_Astrachi" in info
dex = read("data/pru/PRU_National_Pokedex_2026-10-16.csv")
assert "443,Astrachi,astrachi,SPECIES_ASTRACHI" in dex
workflow = read(".github/workflows/pru-clean-build.yml")
assert "install_insurgence_mega_jirachi.py" in workflow
assert "check_insurgence_mega_jirachi.py" in workflow
assert "check_astrachi_jirachi_encounter.py" in workflow
print("PASS: Jirachi caught-only gate, Level 70 Astrachi, independent capture flags and retry")
print("PASS: Astrachi #443 + Claude overworld and Insurgence Jirachi art guards")
