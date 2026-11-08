#!/usr/bin/env python3
"""Regression guard for PRU DexNav walking / auto-run search approach."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
config = (ROOT / "include/config/dexnav.h").read_text(encoding="utf-8")
source = (ROOT / "src/dexnav.c").read_text(encoding="utf-8")
search = source.split("bool32 OnStep_DexNavSearch(void)", 1)[1].split("\n}\n", 1)[0]

assert "#define DEXNAV_TIMEOUT                  30" in config, "Scan should last 30 seconds"
assert "EventScript_MovedTooFast" not in search, "Walking/running/bike must not fail a scan"
assert "gPlayerAvatar.creeping" not in search, "No special creeping control required"
assert "sDexNavSearchDataPtr->proximity > MAX_PROXIMITY" in search, "Preserve range limit"
assert "frameCount > DEXNAV_TIMEOUT * 60" in search, "Preserve timeout"
assert "sDexNavSearchDataPtr->proximity < 1" in search, "Preserve target-tile encounter"
assert "CreateDexNavWildMon(" in search and "EventScript_StartDexNavBattle" in search, "Preserve scanned encounter"
print("PASS: DexNav allows walking/running/biking while retaining range, timeout and target battle")
