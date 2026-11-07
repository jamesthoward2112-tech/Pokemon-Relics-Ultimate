"""PRU alpha regression: E20 story clear vs level-100 MASTER rematch, debug off.

This check guards both paths against accidental conflation. It also keeps
normal one-time Elite 20 rewards separate from the repeatable rematch.
"""
from pathlib import Path

root=Path(__file__).resolve().parents[1]
e20=(root/"data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc").read_text(encoding="utf-8")
cfg=(root/"include/config/debug.h").read_text(encoding="utf-8")

for option in ("DEBUG_OVERWORLD_MENU","DEBUG_BATTLE_MENU"):
    matches=[s.strip() for s in cfg.splitlines() if s.strip().startswith(f"#define {option} ")]
    assert len(matches)==1, (option,matches)
    assert matches[0].split("//",1)[0].split()[-1]=="FALSE", f"{option} must be disabled for every build"
assert "#define DEBUG_POKEMON_SPRITE_VISUALIZER FALSE" in cfg

def section(start,end):
    assert start in e20 and end in e20
    return e20.split(start,1)[1].split(end,1)[0]

gauntlet=section("PRU_Elite18_Gauntlet::","PRU_Elite20_FirstReveal::")
assert gauntlet.count("call PRU_Elite18_Round_")==20, "Full 20-pair E20 run missing rounds"
assert gauntlet.count("call PRU_Elite18_Round_20")==1
assert gauntlet.index("call PRU_Elite18_Round_20") < gauntlet.index(
    "goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite20_MasterRematchesCleared"
) < gauntlet.index("setflag FLAG_PRU_ELITE18_CLEARED")
assert "msgbox PRU_Elite18_Text_Cleared" in gauntlet
assert "goto_if_set FLAG_PRU_E20_RELICS_REVEAL_SHOWN, PRU_Elite20_RepeatReveal" in gauntlet
assert "goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, PRU_Elite20_FirstReveal" in gauntlet

first=section("PRU_Elite20_FirstReveal::","PRU_Elite20_RepeatReveal::")
assert "setflag FLAG_PRU_E20_RELICS_REVEAL_SHOWN" in first
for name in ("PRU_Elite20_Text_ElmRelics","PRU_Elite20_Text_OakRelics",
             "PRU_Elite20_Text_RuinsDirections"):
    assert f"msgbox {name}" in first

rematch=section("PRU_Elite20_MasterRematchesCleared::","PRU_Elite20_StartFinale::")
assert "special HealPlayerParty" in rematch
assert "msgbox PRU_Elite20_Text_MasterRematchesCleared, MSGBOX_DEFAULT" in rematch
assert "\trelease\n\tend" in rematch
for forbidden in ("ClaimRewards","StartFinale","Relics","RELICS","setflag","FLAG_PRU_E20_CREDITS_PENDING"):
    assert forbidden not in rematch, ("Rematches should not repeat one-time story",forbidden)

speech=section("PRU_Elite20_Text_MasterRematchesCleared:","PRU_Elite20_Text_OakRelicsUnused:")
for phrase in ("OAK: {PLAYER}, magnificent!","all twenty","LEVEL 100 MASTER teams!",
               "ELM: Even our best strategies","ULTIMATE CHAMPION.","Congratulations!"):
    assert phrase in speech, "Missing end-of-rematches celebration: "+phrase
assert "RELICS" not in speech and "Alphoracle" not in speech

# The repeatable Master battles must still be selected after the clear.
for n in (1,5,10,15,20):
    assert f"PRU_Elite18_Round_{n:02d}_Master::" in e20
    assert f"TRAINER_PRU_E18_" in e20

print("PASS: first E20 clear preserves the RELICS reveal; all level-100 rematches get unique congratulations.")
print("PASS: no repeated reveal, story rewards or flags after rematches; all debug menus disabled.")
