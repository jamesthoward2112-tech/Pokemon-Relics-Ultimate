#!/usr/bin/env python3
"""PRU source-only credits audit. No build, release or emulator required.

Run from a full checkout:
    python3 test/test_pru_credits.py
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
source = (ROOT / "src/credits_hns.c").read_text(encoding="utf-8")
header = (ROOT / "src/data/credits_pru.h").read_text(encoding="utf-8")
attribution = (ROOT / "docs/PRU_CREDITS.md").read_text(encoding="utf-8")

def require(ok, why):
    if not ok:
        raise AssertionError(why)

require('#include "data/credits_pru.h"' in source, "PRU page table must be used")
require('#include "data/credits_hns.h"' not in source, "Inherited Heart & Soul pages cannot render")
require((ROOT / "src/data/credits_hns.h").exists(), "Keep source of original Heart & Soul acknowledgements")
require((ROOT / "CREDITS.md").exists(), "Keep upstream contributor acknowledgements")
require('#define ENTRIES_PER_PAGE 5' in header, "Credits renderer requires five slots")

names = re.findall(r"^\s*PAGE_PRU_(\d{2}),", header, re.MULTILINE)
require(names == [f"{i:02}" for i in range(1, 30)],
        "Expected 29 numbered PRU credit pages, in order")
require("PAGE_COUNT" in header.split("enum", 1)[1].split("};", 1)[0],
        "PAGE_COUNT must follow the pages")

page_rows = re.findall(r"\[PAGE_PRU_\d{2}\]\s*=\s*\{([^}]*)\}", header)
require(len(page_rows) == 29, "Every page needs a table row")
for page_number, row in enumerate(page_rows, 1):
    slots = [slot.strip() for slot in row.split(",") if slot.strip()]
    require(len(slots) == 5, f"Page {page_number} does not have 5 slots")
    require(all(slot.startswith("&s") for slot in slots),
            f"Page {page_number} has a non-pointer slot")

texts = re.findall(r'sPRUCreditsText_\d+_\d+\[\]\s*=\s*_\("([^"]*)"\)', header)
require(len(texts) == 87, "Expected three text entries per page")
for text in texts:
    require(len(text) <= 32, f"Credit line too long: {text}")
    require("\\n" not in text and "\\p" not in text,
            f"Credit line has an unexpected control sequence: {text}")
require("POKéMON RELICS ULTIMATE" in header, "PRU title credit missing")
require("JAMES HOWARD" in header, "Project lead credit missing")
for term in ("POKEEMERALD-EXPANSION", "OPENAI / CHATGPT", "ANTHROPIC / CLAUDE",
             "GOOGLE / GEMINI", "POKéSPRITE", "PORYPAL",
             "POKéMON HEART & SOUL", "POKéMON RHYTHM"):
    require(term in header, f"Expected acknowledgment missing: {term}")

# All HNS endings share the credits engine. E20 keeps its cinematic flyby
# and Relic slideshow, while changing its teaser to avoid plot spoilers.
require("sElite20CreditsIntroPages" in source, "Elite 20 intro must remain")
require("A GOLDEN LEGEND STIRS" in source, "Spoiler-safe Elite 20 teaser missing")
require("CreateCreditsRelicHoOhSprite" in source, "Golden sprite opening removed")
require("sPruCreditsSpecies" in source and "DeterminePokemonToShow" in source,
        "The RELICS montage must remain")
require("Task_CreditsSoftReset" in source and "CB2_StartCreditsSequence" in source,
        "Credits lifecycle/return path missing")
require("sCreditsEntryPointerTable" in source, "Page pointer rendering missing")

# Full contributor records and unresolved provenance must remain accessible.
for source_name in ("pret/pokeemerald", "pokeemerald-expansion", "Pokémon Heart & Soul",
                    "Pokémon Tourmaline", "Pokémon Rhythm", "Pokémon Insurgence"):
    require(source_name in attribution, f"Attribution document missing {source_name}")
require("permission" in attribution.lower(), "Unverified asset permissions must be flagged")

print("PASS: 29 original pages and five renderable entries per page")
print("PASS: engine, project, tool and donor credits included")
print("PASS: all endings share PRU page table; Golden flyby and RELICS montage retained")
print("PASS: original contributor files and provenance caveats preserved")
print("NOTE: source-only; in-game text widths, timing, music and rewards remain untested.")
