#!/usr/bin/env python3
"""Job 11: guarantee Rock Shop Expert text pages fit the two-row MSGBOX_DEFAULT."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
SCRIPT = (ROOT / "data/maps/EcruteakCity_RockShop_hns/scripts.inc").read_text(encoding="utf-8")
SPECIES = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text(encoding="utf-8")
PREFIX = "EcruteakCity_RockShop_Text_Expert"

# The two-line GBA message window requires a page break after at most two rows.
labels = ["Greeting", "Prompt", "Classic", "Relic", "Unusual", "Goodbye", "Eevee"]
for label in labels:
    match = re.search(
        rf"(?m)^{PREFIX}{label}:\s*\n((?:\s*\.string\s+\"[^\"]*\"\s*\n)+)",
        SCRIPT,
    )
    assert match, f"Missing Expert {label} dialogue"
    chunks = re.findall(r'\.string\s+"([^"]+)"', match.group(1))
    msg = "".join(chunks)
    assert msg.endswith("$"), (label, "missing terminator")
    assert "\\l" not in msg, (label, "scroll escape not handled by test")
    for page_no, page in enumerate(msg.rstrip("$").split(r"\p"), 1):
        rows = page.split(r"\n")
        assert 1 <= len(rows) <= 2, (label, page_no, rows)
        for row in rows:
            assert row.strip(), (label, page_no, "blank row")
            # Conservative bound for 240px GBA field. Never depend on auto-wrap.
            assert len(row) <= 34, (label, page_no, "oversized line", row)
    print(f"{label}: validated {len(msg.rstrip('$').split(chr(92)+'p'))} page(s)")

# User wants one name only; this remains a distinct internal form for
# endgame gating, Phoenix Soul, Golden Reign and its battle sprite.
entry = SPECIES.split("[SPECIES_RELIC_HO_OH] =", 1)[1].split("\n[", 1)[0]
assert '.speciesName = _("Ho-Oh")' in entry
assert '.speciesName = _("Relic Ho-Oh")' not in entry
assert ".abilities = { ABILITY_PHOENIX_SOUL" in entry
assert ".frontPic = gMonFrontPic_HoOhRelic" in entry
assert ".backPic = gMonBackPic_HoOhRelic" in entry
assert (ROOT / "include/constants/species.h").read_text().count("#define SPECIES_RELIC_HO_OH") == 1

print("Job 11 text pagination and Ho-Oh display name checks PASSED.")
