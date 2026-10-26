#!/usr/bin/env python3
"""Regression guard for the Seafoam Kyogre finale and matching shiny forms."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]


def read(path):
    return (root / path).read_text(encoding="utf-8")


party = read("src/data/trainers_hns.party")
archie = party.split("=== TRAINER_PRU_ARCHIE_KYOGRE_HNS ===", 1)[1].split(
    "=== TRAINER_PRU_MAXIE_GROUDON_HNS ===", 1
)[0]
ace = archie.split("Kyogre @ Blue Orb", 1)[1]
ace_moves = re.findall(r"^- (.+)$", ace, flags=re.MULTILINE)
assert ace_moves == ["Water Spout", "Origin Pulse", "Thunder", "Ice Beam"], ace_moves
assert "Shiny: Yes" in ace
assert archie.index("Swamplith @ Leftovers") < archie.index("Kyogre @ Blue Orb")
assert "AI: Smart Trainer / Prediction / Ace Pokemon" in archie

script = read("data/maps/SeafoamIslands_SecretCave_hns/scripts.inc")
archie_event = script.split("SeafoamIslands_SecretCave_EventScript_Archie::", 1)[1].split(
    "SeafoamIslands_SecretCave_EventScript_Kyogre::", 1
)[0]
assert re.search(
    r"trainerbattle_single TRAINER_PRU_ARCHIE_KYOGRE_HNS,\s*"
    r"SeafoamIslands_SecretCave_Text_ArchieIntro,\s*"
    r"SeafoamIslands_SecretCave_Text_ArchieDefeated,\s*"
    r"SeafoamIslands_SecretCave_EventScript_ArchieAfterBattle",
    archie_event,
), "trainer win must jump directly to the automatic post-battle script"
assert re.search(
    r"\n\s*end\s*\n\s*SeafoamIslands_SecretCave_EventScript_ArchieAfterBattle:",
    archie_event,
), "normal script must not fall through into the win-only reveal"
assert archie_event.index("setflag FLAG_PRU_ARCHIE_KYOGRE_DEFEATED") < archie_event.index(
    "addobject LOCALID_PRU_KYOGRE"
)
assert archie_event.index("addobject LOCALID_PRU_KYOGRE") < archie_event.index(
    "removeobject LOCALID_PRU_ARCHIE"
)

bg = read("src/battle_bg.c")
rhythm = bg.split("static u8 GetPruRhythmBattleBgIndex(u16 environment)", 1)[1].split(
    "static void LoadBattleEnvironmentGfx", 1
)[0]
assert re.search(
    r"case MAP_SEAFOAM_ISLANDS_SECRET_CAVE_HNS:\s*return 48;",
    rhythm,
), "Kyogre cave needs the rocky-wave Rhythm ocean environment, never snow"


def palette(name, form, gba=False):
    location = Path("graphics/pokemon") / name
    if form == "primal":
        location /= "primal"
    suffix = "shiny_gba.pal" if gba else "shiny.pal"
    colors = [tuple(map(int, v.split())) for v in read(location / suffix).splitlines()[3:]]
    assert len(colors) == 16
    return colors


base_kyogre = palette("kyogre", "base")
primal_kyogre = palette("kyogre", "primal")
base_groudon = palette("groudon", "base")
primal_groudon = palette("groudon", "primal")
gba_kyogre = palette("kyogre", "base", gba=True)
gba_groudon = palette("groudon", "base", gba=True)
assert "#define P_GBA_STYLE_SPECIES_GFX         TRUE" in read("include/config/pokemon.h")

# These slots form the signature body and fin colours in the indexed artwork.
# Base-shiny Kyogre used bright magenta; base-shiny Groudon used green.
for i in (5, 6, 7, 9):
    r, g, b = base_kyogre[i]
    assert max(r, g, b) < 100 and abs(r - g) < 25 and abs(g - b) < 25, (i, base_kyogre[i])
for i in (1, 2):
    r, g, b = primal_kyogre[i]
    assert max(r, g, b) < 95 and abs(r - g) < 25, (i, primal_kyogre[i])
for i in (2, 6, 7):
    r, g, b = base_groudon[i]
    assert max(r, g, b) < 105 and abs(r - g) < 25, (i, base_groudon[i])
assert primal_groudon[1] == (0, 0, 0) and max(primal_groudon[2]) < 70
for i in (5, 12, 13, 14):
    r, g, b = gba_kyogre[i]
    assert max(r, g, b) < 100 and abs(r - g) < 25, (i, gba_kyogre[i])
for i in (1, 6, 7):
    r, g, b = gba_groudon[i]
    assert max(r, g, b) < 105 and abs(r - g) < 25, (i, gba_groudon[i])

print("PRU_ARCHIE_FINALE_PASS: auto reveal, ocean backdrop, exact four moves, matching black shiny Primals")
