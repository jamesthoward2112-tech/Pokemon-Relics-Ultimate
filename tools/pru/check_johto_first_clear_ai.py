#!/usr/bin/env python3
"""Ensure Johto's first League clear is actually tactically challenging.

Deliberately protect the approved 444-legal species, levels, trainer artwork, team order,
and all rematch/post-Kanto tiers. We only alter first-clear AI/moves/items.
"""
import re
from pathlib import Path

path = Path("src/data/trainers_hns.party")
text = path.read_text(encoding="utf-8")
expected = {
  "TRAINER_WILL_1_HNS": [
    {
      "species": "Valkyvoir",
      "level": 56
    },
    {
      "species": "Slowking",
      "level": 56
    },
    {
      "species": "Espeon",
      "level": 57
    },
    {
      "species": "Slowbro",
      "level": 57
    },
    {
      "species": "Xatu",
      "level": 58
    }
  ],
  "TRAINER_KOGA_1_HNS": [
    {
      "species": "Pinsirex",
      "level": 58
    },
    {
      "species": "Qwilfish",
      "level": 58
    },
    {
      "species": "Muk",
      "level": 59
    },
    {
      "species": "Venomoth",
      "level": 59
    },
    {
      "species": "Ghoulbat",
      "level": 60
    }
  ],
  "TRAINER_BRUNO_1_HNS": [
    {
      "species": "Medicham",
      "level": 59
    },
    {
      "species": "Heracurion",
      "level": 59
    },
    {
      "species": "Hitmonlee",
      "level": 60
    },
    {
      "species": "Steelix",
      "level": 60
    },
    {
      "species": "Machamp",
      "level": 61
    }
  ],
  "TRAINER_KAREN_1_HNS": [
    {
      "species": "Umbreon",
      "level": 60
    },
    {
      "species": "Gengar",
      "level": 60
    },
    {
      "species": "Vileplume",
      "level": 61
    },
    {
      "species": "Grimfowl",
      "level": 61
    },
    {
      "species": "Skulberus",
      "level": 62
    }
  ],
  "TRAINER_LANCE_1_HNS": [
    {
      "species": "Feralodon",
      "level": 62
    },
    {
      "species": "Dragonite",
      "level": 63
    },
    {
      "species": "Charaxis",
      "level": 63
    },
    {
      "species": "Dragonite",
      "level": 64
    },
    {
      "species": "Aerodactyl",
      "level": 64
    },
    {
      "species": "Drakeon",
      "level": 65
    }
  ]
}
def block(label):
    match = re.search(r"^=== " + re.escape(label) + r" ===\n(.*?)(?=^=== |\Z)", text, re.M | re.S)
    assert match, f"Missing first-clear opponent {label}"
    return match.group(1)

for trainer, roster in expected.items():
    entry = block(trainer)
    header, *mon_entries = entry.strip().split("\n\n")
    assert "AI: Smart Trainer / Prediction" in header, trainer
    assert "Double Battle: No" in header, trainer
    assert len(mon_entries) == len(roster), (trainer, len(mon_entries), len(roster))
    for i, (chunk, old) in enumerate(zip(mon_entries, roster)):
        lines = chunk.splitlines()
        spec = lines[0].split(" @ ", 1)[0]
        assert spec == old["species"], (trainer, i, spec)
        assert " @ " in lines[0], (trainer, i, "no held item")
        assert f"Level: {old['level']}" in lines, (trainer, i, "levels changed")
        assert any(line.startswith("EVs: ") for line in lines), (trainer, i)
        assert any(line.endswith(" Nature") for line in lines), (trainer, i)
        moves = [line for line in lines if line.startswith("- ")]
        assert len(moves) == 4 and len(set(moves)) == 4, (trainer, i, moves)
    assert "Items: Full Restore / Full Restore" in header, trainer

for name in ["TRAINER_WILL_1_HNS","TRAINER_KOGA_1_HNS","TRAINER_BRUNO_1_HNS","TRAINER_KAREN_1_HNS","TRAINER_LANCE_1_HNS"]:
    assert "AI: Basic Trainer" not in block(name), name

assert "- Light Screen" in block("TRAINER_WILL_1_HNS")
assert "- Toxic Spikes" in block("TRAINER_KOGA_1_HNS")
assert "- Mach Punch" in block("TRAINER_BRUNO_1_HNS")
assert "- Destiny Bond" in block("TRAINER_KAREN_1_HNS")
assert "- Dragon Dance" in block("TRAINER_LANCE_1_HNS")
assert "- Stealth Rock" in block("TRAINER_LANCE_1_HNS")
print("PASS: Johto E4 and Lance retain 444-legal species/levels, smart AI, distinct sets, items and EVs")
