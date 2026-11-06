"""Regression: Frytning has Levitate as ordinary ability for both saved normal slots."""
import re
from pathlib import Path

text = Path("src/data/pokemon/species_info/pru_custom.h").read_text()
match = re.search(r"\[SPECIES_FRYTNING\]\s*=\s*\{(?P<body>.*?)\n\},", text, re.S)
assert match, "Frytning species record missing"
body = match.group("body")
assert re.search(
    r"\.abilities\s*=\s*\{\s*ABILITY_LEVITATE\s*,\s*ABILITY_LEVITATE\s*,\s*ABILITY_NONE\s*\}",
    body,
), "Levitate must occupy both ordinary ability slots; no ability patch needed"
assert "TYPE_DARK, TYPE_ELECTRIC" in body, "Preserve Frytning typing"
assert '.speciesName = _("Frytning")' in body
ci = Path(".github/workflows/pru-clean-build.yml").read_text()
assert "python3 test/test_pru_frytning_levitate.py" in ci
print("PRU_FRYTNING_LEVITATE_PASS: ordinary slots both Levitate; save-compatible")
