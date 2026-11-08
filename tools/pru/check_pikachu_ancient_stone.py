#!/usr/bin/env python3
"""PRU hero evolution: Ancient Stone gives Pikachu -> Noxichu, without a level gate."""
import re
from pathlib import Path

root = Path(__file__).resolve().parents[2]
gen1 = (root / "src/data/pokemon/species_info/gen_1_families.h").read_text(encoding="utf-8")
item_data = (root / "src/data/items.h").read_text(encoding="utf-8")
items = (root / "include/constants/items.h").read_text(encoding="utf-8")
start = gen1.index("    [SPECIES_PIKACHU] =")
end = gen1.index("    [SPECIES_PIKACHU_COSPLAY]", start)
pikachu = gen1[start:end]
assert re.search(r"\{EVO_ITEM,\s*ITEM_ANCIENT_STONE,\s*SPECIES_NOXICHU\}", pikachu), "Pikachu must evolve to Noxichu with Ancient Stone, no minimum level"
assert "{EVO_ITEM, ITEM_MOON_STONE, SPECIES_NOXICHU}" not in pikachu, "Moon Stone must not cause Noxichu evolution"
assert "{EVO_ITEM, ITEM_THUNDER_STONE, SPECIES_RAICHU" in pikachu, "Preserve Raichu evolution"
assert "ITEM_ANCIENT_STONE" in items, "Keep existing Ancient Stone item ID"
assert "[ITEM_ANCIENT_STONE]" in item_data, "Ancient Stone must exist in items data"
assert "ItemUseOutOfBattle_EvolutionStone" in item_data, "Retain normal stone use path"
assert "SPECIES_NOXICHU" in gen1, "Noxichu must remain a registered species"
print("PASS: Pikachu -> Noxichu by Ancient Stone without level gate; Raichu remains on Thunder Stone")
