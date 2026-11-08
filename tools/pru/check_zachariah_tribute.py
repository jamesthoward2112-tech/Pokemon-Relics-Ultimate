#!/usr/bin/env python3
"""Ensure Zachariah Sullivan's player-approved first-playtester tribute remains in PRU."""
import re
from pathlib import Path
root = Path(__file__).resolve().parents[2]
credits = (root / "src/data/credits_pru.h").read_text(encoding="utf-8")
trainers = (root / "src/data/trainers_hns.party").read_text(encoding="utf-8")
route = (root / "data/maps/Route30_hns/scripts.inc").read_text(encoding="utf-8")
old = (root / "src/data/credits_hns.h").read_text(encoding="utf-8")
assert 'sPruCreditText_19_0[] = _("FIRST PLAYTESTER")' in credits
assert 'sPruCreditText_19_1[] = _("ZACHARIAH SULLIVAN")' in credits
assert 'sPruCreditText_19_2[] = _("THANK YOU FOR TESTING PRU!")' in credits
assert len("THANK YOU FOR TESTING PRU!") <= 27
assert 'sPruCreditEntry_13_3, &sCreditsEntry_EmptyString },\n    { &sPruCreditEntry_19_0' in credits, "Tribute page must follow the other playtesters"
assert credits.count("sPruCreditEntry_19_0, &sPruCreditEntry_19_1") == 1, "Only one dedicated tribute page"
assert 'sPruCreditText_18_0[] = _("THANK YOU FOR PLAYING")' in credits, "Preserve final thank-you"
assert "sCreditsEntryPointerTable" in old, "Preserve legacy H&S credits"
assert len(re.findall(r"^\s*\{ &sPruCreditEntry_\d+_0", credits, re.M)) == 20, "Expected 20 E20 credit pages"
early = trainers.split("=== TRAINER_MIKEY_HNS ===\\n", 1)[1].split("\\n=== TRAINER_",1)[0]
assert re.search(r"^Name: MIKEY$", early, re.M), "Keep the original early Route 30 trainer"
assert "Hoothoot\\nLevel: 5" in early and "Sentret\\nLevel: 8" in early, "Preserve original Route 30 team"
assert "trainerbattle_single TRAINER_MIKEY_HNS" in route, "Preserve early trainer battle ID and script progression"
late = trainers.split("=== TRAINER_PRU_ZACHARIAH_MT_SILVER_HNS ===\\n", 1)[1]
assert re.search(r"^Name: Zachariah$", late, re.M), "Late-game Zachariah must carry the tribute"
assert "Class: Cooltrainer Hns" in late and "Items: Full Restore / Full Restore" in late
print("PASS: Zachariah credited as first playtester; optional late-game Mt Silver final team; early Youngster Mikey preserved")
