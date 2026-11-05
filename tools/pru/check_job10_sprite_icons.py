#!/usr/bin/env python3
"""Job 10: assert the final ROM-linked PC icons are correctly framed."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
from PIL import Image
from install_job10_sprite_icons import ROOT, OUT, MANIFEST, MAX_SIZE, unique_path, frame_box

report = json.loads((OUT / "icon-changes.json").read_text(encoding="utf-8"))
assert report["job"] == 10 and report["max_icon_extent_px"] == MAX_SIZE
assert report["changed_icon_count"] == len(report["changes"])
assert report["checked_custom_icon_count"] >= 45
assert len(report["changes"]) >= 10
assert (OUT / "before-after-icons.png").is_file()
assert report["unresolved_elite_four_relic_back_art_count"] == 10
assert report["source_visual_check_only"] is True
manifest = json.loads(MANIFEST.read_text(encoding="utf-8"))
assert len(manifest["species"]) == 70
checked = 0
for row in manifest["species"]:
    icon = row["images"].get("icon", {})
    rel = icon.get("path")
    if not rel or not unique_path(row["name"], rel):
        continue
    with Image.open(ROOT / rel) as im:
        if im.mode != "P":  # may be externally prepared after check for non-P donors
            continue
        checked += 1
        assert im.size == (32, 64) and im.info.get("transparency", 0) == 0, rel
        assert max(im.getdata()) < 16, rel
        for i in range(2):
            b = frame_box(im, i)
            assert b is not None, (rel, i, "empty animation frame")
            assert max(b[2] - b[0], b[3] - b[1]) <= MAX_SIZE, (rel, i, b)
            assert b[0] >= 1 and b[1] >= 1 and b[2] <= 31 and b[3] <= 31, (rel, i, b)
assert checked >= 45, checked
for changed in report["changes"]:
    path = ROOT / changed["path"]
    with Image.open(path) as im:
        assert hashlib.sha256(im.tobytes()).hexdigest() == changed["after_sha256"], changed["name"]
        assert all(max(b[2]-b[0], b[3]-b[1]) <= MAX_SIZE for b in changed["after"])
# These palettes were previously repaired and must not be reset by image framing.
icon_code = (ROOT / "src/pokemon_icon.c").read_text(encoding="utf-8")
assert "if (species == SPECIES_ALPHORACLE)" in icon_code
assert "if (species == SPECIES_UNOWN_I)" in icon_code
with Image.open(ROOT / "graphics/pokemon/unown_eye/icon.png") as eye:
    used = set(eye.getdata())
    assert eye.mode == "P" and eye.size == (32, 64)
    assert 5 in used and 10 in used and 2 not in used, "I-Unown must remain dark with red eye"
print(f"PASS: Job 10 {checked} unique custom indexed icons, {len(report['changes'])} revised; "
      "no clipped frames, palette collision or save-layout changes.")
