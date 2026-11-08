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
trainer = trainers.split("=== TRAINER_MIKEY_HNS ===\n", 1)[1].split("\n=== TRAINER_",1)[0]
assert re.search(r"^Name: ZACHARIAH$",trainer,re.M), "Route 30 trainer must be called Zachariah"
assert "Class: Youngster Hns" in trainer, "Preserve trainer class"
assert "Hoothoot\nLevel: 5" in trainer and "Sentret\nLevel: 8" in trainer, "Preserve team/levels"
assert "trainerbattle_single TRAINER_MIKEY_HNS" in route, "Preserve trainer battle ID and script progression"
print("PASS: Zachariah Sullivan credited as first playtester with thanks; Route 30 Youngster renamed without team/ID changes")
