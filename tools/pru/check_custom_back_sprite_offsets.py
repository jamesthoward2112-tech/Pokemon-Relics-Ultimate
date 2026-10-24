#!/usr/bin/env python3
"""Regression: ground every original PRU/PJR custom backsprite without undoing tuned offsets."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
PJR = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text()
PRU = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()

# First pass grounded every species that was still at 0. Keep these
# expectations explicit so a new/reimported sprite cannot quietly regress.
NEWLY_GROUNDED = {
    "ADNOKANA",
    "ALPHORACLE",
    "ASTRACHI",
    "CACTOMB",
    "CHAMPEON",
    "CHEAUKING",
    "COELOSSUS",
    "DRAKEON",
    "EEVEEON",
    "FAERANIUM",
    "FERALODON",
    "FRYTNING",
    "GEMIGOYLE",
    "GEMLIN",
    "GHOULBAT",
    "GRIMFOWL",
    "GUARDEON",
    "HERACURION",
    "JOLLIBIRD",
    "KABLOWFISH",
    "KHANG",
    "LEPIDEON",
    "MAROGHOST",
    "MAWYRM",
    "MEWSION",
    "MILTITAN",
    "MOOTINY",
    "MYSTYNX",
    "NIMBEON",
    "OBSIDEON",
    "OMEON",
    "OSTEODIAN",
    "PINSIREX",
    "SCARABUB",
    "SHUCKOLOSSE",
    "SKARMADON",
    "SKARMET",
    "SKULBERUS",
    "SOLAZIKEN",
    "SPHYNXEON",
    "SUNFLORID",
    "TORKALDERA",
    "TOXEON",
    "TROPISAUR",
}
# Deliberately tuned values, including previous sprite-lowering fixes.
PRESERVED_OFFSETS = {
    "CHARAXIS": 1,
    "DONPHALANX": 16,
    "EDENSAUR": 7,
    "FORTOTOISE": 5,
    "NOLAX": 8,
    "NOXICHU": 20,
    "PYROCLAST": 8,
    "RELIC_HO_OH": 1,
    "SCEPTITAN": 10,
    "SUDOWARDEN": 6,
    "SWAMPLITH": 10,
    "VALKYVOIR": 6,
}

def read_offsets(source: str) -> dict[str, int]:
    result: dict[str, int] = {}
    entries = list(re.finditer(r"\[SPECIES_([A-Z0-9_]+)\]\s*=\s*\{", source))
    for i, match in enumerate(entries):
        segment = source[match.end():entries[i + 1].start() if i + 1 < len(entries) else len(source)]
        found = re.search(r"\.backPicYOffset\s*=\s*(\d+)\b", segment)
        assert found, f"{match.group(1)}: no numeric backsprite offset"
        name = match.group(1)
        assert name not in result, f"duplicate {name}"
        result[name] = int(found.group(1))
    return result

offsets = read_offsets(PJR)
for name, val in read_offsets(PRU).items():
    assert name not in offsets, f"duplicate custom species {name}"
    offsets[name] = val

for match in re.finditer(r"PJR_(FINAL|RED)_SPECIES\(SPECIES_([A-Z0-9_]+),.*?\),", PJR, re.S):
    kind, name = match.group(1), match.group(2)
    fields = [part.strip() for part in match.group(0)[:-2].split(",")]
    value = fields[-1] if kind == "FINAL" else fields[-2]
    assert value.isdecimal(), f"{name}: bad numeric macro offset {value!r}"
    assert name not in offsets, f"duplicate custom species {name}"
    offsets[name] = int(value)

assert set(offsets) == NEWLY_GROUNDED | set(PRESERVED_OFFSETS), (
    "Unreviewed custom species definitions: "
    f"missing={sorted((NEWLY_GROUNDED | set(PRESERVED_OFFSETS)) - set(offsets))}, "
    f"unexpected={sorted(set(offsets) - NEWLY_GROUNDED - set(PRESERVED_OFFSETS))}"
)
for name in NEWLY_GROUNDED:
    assert offsets[name] == 6, f"{name}: expected +6 downward grounding, got {offsets[name]}"
for name, expected in PRESERVED_OFFSETS.items():
    assert offsets[name] == expected, f"{name}: approved offset {expected} altered to {offsets[name]}"

# These trainer-only art forms intentionally reuse FRONT graphics as backs;
# a bulk replacement must never touch them.
form = re.search(
    r"#define PJR_E4_VISUAL_FORM\(.*?\.backPic = front,"
    r".*?\.backPicYOffset = (\d+)", PJR, re.S
)
assert form and form.group(1) == "0", "Trainer-only E4 visual forms unexpectedly moved"

print(
    f"CUSTOM_BACK_SPRITES_PASS: {len(NEWLY_GROUNDED)} grounded to +6; "
    f"{len(PRESERVED_OFFSETS)} previously tuned offsets preserved"
)
