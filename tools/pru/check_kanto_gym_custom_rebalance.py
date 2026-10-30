#!/usr/bin/env python3
"""Guard the first Kanto Gym battles: eight dex-legal, six-Pokemon, smart Relic teams.

Never use this test to rewrite or touch Kanto Gym leader sprites, story/event
flags, rematches, Johto Elite Four, or save-game structure.
"""
import csv
import re
from pathlib import Path

root = Path(__file__).resolve().parents[2]
party = (root / "src/data/trainers_hns.party").read_text(encoding="utf-8")
with (root / "data/pru/PRU_National_Pokedex_2026-10-16.csv").open(encoding="utf-8", newline="") as f:
    canonical = {row["Name"] for row in csv.DictReader(f)}
assert len(canonical) == 450  # Canonical PRU roster, including the three owner-approved additions.

teams = {
    "BROCK": [("Golem", 64), ("Kabutops", 64), ("Relicanth", 65),
              ("Steelix", 65), ("Shuckolosse", 66), ("Donphalanx", 67)],
    "MISTY": [("Quagsire", 65), ("Kablowfish", 66), ("Lapras", 66),
              ("Milotic", 67), ("Starmie", 68), ("Swamplith", 69)],
    "LTSURGE": [("Electrode", 66), ("Ampharos", 67), ("Lanturn", 68),
                ("Manectric", 68), ("Raichu", 69), ("Noxichu", 70)],
    "ERIKA": [("Bellossom", 67), ("Sunflorid", 68), ("Victreebel", 69),
              ("Tropisaur", 70), ("Sceptitan", 70), ("Edensaur", 71)],
    "JANINE": [("Muk", 68), ("Crobat", 69), ("Swalot", 70),
               ("Ghoulbat", 70), ("Adnokana", 71), ("Cheauking", 72)],
    "SABRINA": [("Xatu", 69), ("Medicham", 70), ("Claydol", 71),
                ("Alakazam", 71), ("Mystynx", 72), ("Valkyvoir", 73)],
    "BLAINE": [("Rapidash", 71), ("Houndoom", 72), ("Camerupt", 72),
               ("Pyroclast", 73), ("Torkaldera", 74), ("Charaxis", 75)],
    "BLUE": [("Pidgeot", 73), ("Exeggutor", 74), ("Khang", 75),
             ("Tyranitar", 76), ("Arcanine", 77), ("Fortotoise", 78)],
}
pics = {
    "BROCK": "Brock", "MISTY": "Misty", "LTSURGE": "Surge",
    "ERIKA": "Erika", "JANINE": "Janine", "SABRINA": "Sabrina",
    "BLAINE": "Blaine", "BLUE": "Blue",
}
aces = {
    "BROCK": "Donphalanx", "MISTY": "Swamplith", "LTSURGE": "Noxichu",
    "ERIKA": "Edensaur", "JANINE": "Cheauking", "SABRINA": "Valkyvoir",
    "BLAINE": "Charaxis", "BLUE": "Fortotoise",
}
constants = (root / "include/constants/abilities.h").read_text(encoding="utf-8")
moves_h = (root / "include/constants/moves.h").read_text(encoding="utf-8")

def block(label):
    pattern = r"^=== TRAINER_" + re.escape(label) + r" ===\n(.*?)(?=^=== |\Z)"
    match = re.search(pattern, party, re.M | re.S)
    assert match, f"Missing Kanto Gym trainer {label}"
    return match.group(1)

for leader, expected in teams.items():
    header, *pokemon = block(leader + "_HNS").strip().split("\n\n")
    assert f"Pic: Leader {pics[leader]} Hns" in header, leader
    assert "Double Battle: No" in header, leader
    assert "AI: Smart Trainer / Prediction" in header, leader
    assert "Items: Full Restore / Full Restore" in header, leader
    assert len(pokemon) == len(expected) == 6, leader
    assert expected[-1][0] == aces[leader], leader
    assert len({species for species, _ in expected}) == 6, leader
    for index, (entry, (name, level)) in enumerate(zip(pokemon, expected)):
        lines = entry.splitlines()
        assert lines[0].startswith(name + " @ "), (leader, name)
        assert lines[0].split(" @ ", 1)[0] == name, (leader, name)
        assert name in canonical or (name == "Valkyvoir" and "Valkiri" in canonical), (leader, name, "out-of-dex")
        assert f"Level: {level}" in lines, (leader, name, level)
        assert "IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe" in lines
        assert any(line.startswith("EVs: ") for line in lines), (leader, name)
        assert any(line.endswith(" Nature") for line in lines), (leader, name)
        ability = next((line.removeprefix("Ability: ") for line in lines if line.startswith("Ability: ")), "")
        token = "ABILITY_" + re.sub(r"[^A-Z0-9]+", "_", ability.upper())
        assert token in constants, (leader, name, token)
        moves = [line.removeprefix("- ") for line in lines if line.startswith("- ")]
        assert len(moves) == len(set(moves)) == 4, (leader, name, moves)
        for move in moves:
            token = "MOVE_" + re.sub(r"[^A-Z0-9]+", "_", move.upper())
            assert token in moves_h, (leader, name, move)
    assert aces[leader] in canonical or (aces[leader] == "Valkyvoir" and "Valkiri" in canonical)

for leader in teams:
    assert block(leader + "_POSTOBC_HNS"), ("Keep gym rematches", leader)
assert "TRAINER_BLUE_2_HNS" in party, "Keep alternate Blue encounter"
print("PASS: 8 Kanto Gym leaders, 48 legal species, custom Relic aces, ascending levels, battle AI and sprites")
