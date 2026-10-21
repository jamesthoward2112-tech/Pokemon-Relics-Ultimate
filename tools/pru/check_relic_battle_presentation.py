#!/usr/bin/env python3
"""PRU: defend the custom back-sprite anchor and readable hazard messages."""
import re
from pathlib import Path

species = Path("src/data/pokemon/species_info/pjr_families.h").read_text()
battle = Path("data/battle_scripts_1.s").read_text()
commands = Path("src/battle_script_commands.c").read_text()
constants = Path("include/constants/battle.h").read_text()
moves = Path("src/data/moves_info.h").read_text()

match = re.search(
    r"PJR_FINAL_SPECIES\(SPECIES_DONPHALANX,.*?sDonphalanxLevelUpLearnset,\s*sDonphanTeachableLearnset,\s*(\d+),\s*(\d+)\)",
    species, re.DOTALL
)
assert match, "Donphalanx species entry missing"
assert tuple(map(int, match.groups())) == (0, 12), "Donphalanx back art should sit 12 GBA pixels lower"

assert "#define B_WAIT_TIME_PRU_HAZARD_MESSAGE 120" in constants
for move, effect in [("MOVE_CEASELESS_EDGE", "EFFECT_CEASELESS_EDGE"),
                     ("MOVE_STONE_AXE", "EFFECT_STONE_AXE"),
                     ("MOVE_SIEGE_TUSK", "EFFECT_STONE_AXE")]:
    segment = moves.split(f"[{move}] =", 1)[1].split("\n    },", 1)[0]
    assert f".effect = {effect}" in segment, f"{move} effect changed unexpectedly"

for script in ["BattleScript_SpikesActivates::", "BattleScript_StealthRockActivates::"]:
    segment = battle.split(script, 1)[1].split("\n\treturn", 1)[0]
    assert "\tprintfromtable gDmgHazardsStringIds" in segment
    assert "\twaitmessage B_WAIT_TIME_PRU_HAZARD_MESSAGE" in segment
assert "bool8 preserveHazardText = toWait == B_WAIT_TIME_PRU_HAZARD_MESSAGE;" in commands
assert "(!preserveHazardText && !gSaveBlock3Ptr->challengeSettings.fastBattle)" in commands
assert "gTestRunnerHeadless ||" in commands

# Inventory, not a global re-anchor: transparent margins vary across art donors.
pru = Path("src/data/pokemon/species_info/pru_custom.h").read_text()
zeroes = re.findall(r"\[SPECIES_([A-Z0-9_]+)\]\s*=\s*\{(?:(?!\n\},).)*?\.backPicYOffset\s*=\s*0", pru, re.DOTALL)
print("PASS: Donphalanx back sprite lowered; three hazard moves show 120-frame message")
print(f"AUDIT: {len(zeroes)} PRU custom species still specify backPicYOffset = 0; inspect art individually: " + ", ".join(zeroes))
