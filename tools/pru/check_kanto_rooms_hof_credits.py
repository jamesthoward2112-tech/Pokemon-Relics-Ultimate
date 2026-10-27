#!/usr/bin/env python3
"""Regression contract for the visual Kanto League, Oak ceremony and PRU credits."""
import csv
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
read = lambda path: (ROOT / path).read_text(encoding="utf-8")
load_map = lambda name: json.loads(read(f"data/maps/{name}/map.json"))

# The first championship keeps its original Johto rooms and one reliable actor.
johto = (
    ("PokemonLeague_WillsRoom_hns", "LAYOUT_POKEMON_LEAGUE_WILLS_ROOM_HNS", "OBJ_EVENT_GFX_WILL_HNS"),
    ("PokemonLeague_KogasRoom_hns", "LAYOUT_POKEMON_LEAGUE_KOGAS_ROOM_HNS", "OBJ_EVENT_GFX_KOGA_HNS"),
    ("PokemonLeague_BrunosRoom_hns", "LAYOUT_POKEMON_LEAGUE_BRUNOS_ROOM_HNS", "OBJ_EVENT_GFX_BRUNO_HNS"),
    ("PokemonLeague_KarensRoom_hns", "LAYOUT_POKEMON_LEAGUE_KARENS_ROOM_HNS", "OBJ_EVENT_GFX_KAREN_HNS"),
    ("PokemonLeague_ChampionsRoom_hns", "LAYOUT_POKEMON_LEAGUE_CHAMPIONS_ROOM_HNS", "OBJ_EVENT_GFX_LANCE_HNS"),
)
for name, layout, gfx in johto:
    data = load_map(name)
    assert data["layout"] == layout
    assert data["object_events"][0]["graphics_id"] == gfx

# Kanto is routed to the native ice/fighting/ghost/dragon/champion rooms.
will_script = read("data/maps/PokemonLeague_WillsRoom_hns/scripts.inc")
assert "MAP_POKEMON_LEAGUE_LORELEIS_ROOM" in will_script
kanto = (
    ("PokemonLeague_LoreleisRoom_Frlg", "LAYOUT_POKEMON_LEAGUE_LORELEIS_ROOM", "OBJ_EVENT_GFX_LORELEI", "TRAINER_PRU_KANTO_E4_LORELEI_HNS"),
    ("PokemonLeague_BrunosRoom_Frlg", "LAYOUT_POKEMON_LEAGUE_BRUNOS_ROOM", "OBJ_EVENT_GFX_BRUNO", "TRAINER_PRU_KANTO_E4_BRUNO_HNS"),
    ("PokemonLeague_AgathasRoom_Frlg", "LAYOUT_POKEMON_LEAGUE_AGATHAS_ROOM", "OBJ_EVENT_GFX_AGATHA", "TRAINER_PRU_KANTO_E4_AGATHA_HNS"),
    ("PokemonLeague_LancesRoom_Frlg", "LAYOUT_POKEMON_LEAGUE_LANCES_ROOM", "OBJ_EVENT_GFX_LANCE", "TRAINER_PRU_KANTO_E4_LANCE_HNS"),
    ("PokemonLeague_ChampionsRoom_Frlg", "LAYOUT_POKEMON_LEAGUE_CHAMPIONS_ROOM", "OBJ_EVENT_GFX_RED", "TRAINER_PRU_KANTO_E4_RED_HNS"),
)
for name, layout, gfx, trainer in kanto:
    data = load_map(name)
    assert data["layout"] == layout
    assert data["object_events"][0]["graphics_id"] == gfx
    assert trainer in read(f"data/maps/{name}/scripts.inc")

# Oak, not Lance, leads the second Hall of Fame while Johto's Lance path remains.
hof_map = load_map("PokemonLeague_HallOfFame_hns")
assert hof_map["object_events"][0]["graphics_id"] == "OBJ_EVENT_GFX_VAR_0"
hof = read("data/maps/PokemonLeague_HallOfFame_hns/scripts.inc")
assert "VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_PROF_OAK_HNS" in hof
assert "FLAG_PRU_KANTO_LEAGUE_CLEARED" in hof
assert "PRU_HallOfFame_OakText" in hof
assert "PokemonLeague_HallOfFame_LanceText" in hof

# Credits use an explicit roster whitelist; retired contiguous IDs cannot leak in.
credits = read("src/credits_hns.c")
assert "sPruCreditsSpecies[]" in credits
assert "SPECIES_SUDOWARDEN" not in credits
assert "SPECIES_SCARABUB +" not in credits
approved = {r["Species_Constant"] for r in csv.DictReader(open(ROOT / "data/pru/PRU_National_Pokedex_2026-10-16.csv", encoding="utf-8"))}
shown = set(re.findall(r"SPECIES_[A-Z0-9_]+", credits.split("sPruCreditsSpecies[]", 1)[1].split("};", 1)[0]))
assert shown and shown <= approved, sorted(shown - approved)

# Preserve the user-verified Elm reward and reusable 999-candy field action.
new_bark = read("data/maps/NewBarkTown_hns/scripts.inc")
items = read("src/data/items.h")
item_use = read("src/item_use.c")
assert "giveitem ITEM_RELIC_CANDY" in new_bark
assert "setflag FLAG_PRU_ELM_RELIC_CANDY_GIVEN" in new_bark
relic = items.split("[ITEM_RELIC_CANDY]", 1)[1].split("},", 1)[0]
assert ".importance = 1" in relic and ".pocket = POCKET_KEY_ITEMS" in relic
assert ".fieldUseFunc = ItemUseOutOfBattle_InfiniteRareCandies" in relic
assert "AddBagItem(ITEM_RARE_CANDY, 999)" in item_use

print("PASS: Johto/Kanto rooms, Oak Hall of Fame, approved credits roster and Relic Candy")
