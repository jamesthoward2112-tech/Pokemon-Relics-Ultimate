"""Job 17 PRU credits source regression — run from repository root."""
import re
from pathlib import Path

credits = Path("src/credits_hns.c").read_text(encoding="utf-8")
pru = Path("src/data/credits_pru.h").read_text(encoding="utf-8")
legacy = Path("src/data/credits_hns.h").read_text(encoding="utf-8")
clear = Path("src/post_battle_event_funcs.c").read_text(encoding="utf-8")
finale = Path("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc").read_text(encoding="utf-8")
workflow = Path(".github/workflows/pru-clean-build.yml").read_text(encoding="utf-8")

assert '#include "data/credits_pru.h"' in credits
assert "sPruE20CreditsPages[gTasks[taskId].tCurrentPage - E20_INTRO_PAGE_COUNT][i]" in credits
assert "sCreditsEntryPointerTable[gTasks[taskId].tCurrentPage][i]" in credits
assert "gTasks[taskId].tCurrentPage < (gPruElite20CreditsActive ? E20_TOTAL_PAGE_COUNT : PAGE_COUNT)" in credits
assert "if (page == E20_INTRO_PAGE_COUNT)" in credits  # Ho-Oh -> RELICS gallery
assert "#define PAGE_INTERVAL (PAGE_COUNT / 9)" in credits
assert "gPruElite20CreditsActive = FlagGet(FLAG_PRU_E20_CREDITS_PENDING);" in clear
assert "FlagClear(FLAG_PRU_E20_CREDITS_PENDING);" in clear
assert "gPruElite20CreditsActive = FlagGet(FLAG_PRU_E20_CREDITS_PENDING);" not in credits
assert "sCreditsEntryPointerTable[PAGE_COUNT][ENTRIES_PER_PAGE]" in legacy
assert "sElite20CreditsIntroPages" in credits
assert "FLAG_PRU_E20_CREDITS_PENDING" in finale
assert "FLAG_PRU_E20_REWARD_CLAIMED" in finale
assert "giveitem ITEM_MASTER_BALL, 6" in finale
assert "giveitem ITEM_ANCIENT_STONE, 5" in finale

lines = re.findall(r'static const u8 sPruCreditText_\d+_\d+\[\] = _\("([^"]+)"\);', pru)
page_count = len(re.findall(r'^    \{ &sPruCreditEntry_', pru, re.MULTILINE))
assert page_count == 19, f"Expected 19 unique credit pages: {page_count}"
assert len(lines) >= 70, f"Only {len(lines)} credit lines"
assert all(len(line) <= 27 for line in lines), "Text may overflow the 240-pixel GBA display"
for text in ("balesleftpeg", "CHATGPT", "CLAUDE", "GEMINI", "POKEEMERALD-EXPANSION",
             "LIL DILL", "POKESPRITE", "PORYPAL", "GITHUB", "GAME FREAK",
             "NINTENDO", "CREATURES INC.", "THANK YOU FOR PLAYING"):
    assert text in lines, f"Missing required attribution: {text}"
assert not re.search(r"james\\s+howard", pru, re.IGNORECASE), "Private creator name leaked into game credits"
for donor in ("POKEMON RELIC LEGACY", "POKEMON JOHTO RELICS", "POKEMON KANTO RELICS",
              "POKEMON HOENN RELICS", "POKEMON INFINITY", "POKEMON INSURGENCE",
              "POKEMON ELITE REDUX", "POKEMON XENOVERSE", "POKEMON SHINING VICTORY",
              "POKEMON ODYSSEY II", "POKEMON TOURMALINE", "POKEMON ALTERED",
              "TRE 2026 SPRITE BANK", "POKEMON RHYTHM", "POKEMON HOENN'S LAST WISH"):
    assert donor in lines, f"Missing documented sprite donor: {donor}"
assert "E20_TOTAL_PAGE_COUNT" in pru
assert "test/test_pru_job17_custom_credits.py" in workflow
assert "feat/pru-job17-custom-credits-20261106" in workflow
print(f"PRU_JOB17_CREDITS_PASS: {page_count} PRU-only pages with balesleftpeg attribution, {len(lines)} credit lines, original Leagues preserved")
