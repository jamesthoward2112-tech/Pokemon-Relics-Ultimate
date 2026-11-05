#!/usr/bin/env python3
"""Job 10: deterministic, palette-preserving final PC icon framing.

Run LAST, after the existing video sprite installer. Never invent donor art:
scale only uniquely-owned custom icons; leave shared vanilla icons alone.
"""
from __future__ import annotations
import argparse
import hashlib
import json
import math
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[2]
MANIFEST = ROOT / "PRU-QA/sprite-audit-70.json"
OUT = ROOT / "PRU-QA/job10"
MAX_SIZE = 24
# User approved Pyroclast and explicitly omitted Nolax from the video sweep.
PRESERVE = {"PYROCLAST", "NOLAX"}
# These forms deliberately reuse a normal Pokemon's icon, and cannot be edited
# without silently changing that normal Pokemon's PC and party appearance.
SHARED = {"DONPHALANX", "FAERANIUM", "FERALODON"}

def bbox(frame: Image.Image):
    return frame.point(lambda v: 255 if v else 0).getbbox()

def unique_path(name: str, relative: str) -> bool:
    relative = relative.replace(chr(92), "/")
    p = Path(relative)
    if not relative.startswith("graphics/pokemon/") or p.name != "icon.png":
        return False
    if "_RELIC" in name and name != "RELIC_HO_OH":
        return False
    if name.endswith("_JJ") or name in SHARED | PRESERVE:
        return False
    return (
        name.lower() in [part.lower() for part in p.parts]
        or (name == "RELIC_HO_OH" and "ho_oh_relic" in p.parts)
    )

def centred_frame(src: Image.Image, ratio: float) -> Image.Image:
    bounds = bbox(src)
    assert bounds, "empty animation frame"
    crop = src.crop(bounds)
    if ratio < 1:
        size = (max(1, round(crop.width * ratio)), max(1, round(crop.height * ratio)))
        crop = crop.resize(size, Image.Resampling.NEAREST)
    result = Image.new("P", (32, 32), 0)
    result.putpalette(src.getpalette())
    result.paste(crop, ((32 - crop.width) // 2, 31 - crop.height))
    return result

def frame_box(sheet, i):
    return bbox(sheet.crop((0, i * 32, 32, (i + 1) * 32)))

def resize_icon(path: Path, dry_run: bool):
    with Image.open(path) as im:
        im.load()
        assert im.size == (32, 64), path
        if im.mode != "P":
            return None  # preparation stage converts approved RGBA donors first
        assert im.info.get("transparency", 0) == 0, path
        assert max(im.getdata()) < 16 and im.getpalette(), path
        boxes = [frame_box(im, i) for i in range(2)]
        assert all(boxes), f"empty icon frame in {path}"
        dims = [(b[2] - b[0], b[3] - b[1]) for b in boxes]
        largest = max(max(v) for v in dims)
        needs = largest > MAX_SIZE or any(
            b[0] == 0 or b[1] == 0 or b[2] == 32 or b[3] == 32 for b in boxes
        )
        if not needs:
            return None
        ratio = min(1.0, MAX_SIZE / largest)
        out = Image.new("P", im.size, 0)
        out.putpalette(im.getpalette())
        for i in range(2):
            frame = im.crop((0, i * 32, 32, (i + 1) * 32))
            out.paste(centred_frame(frame, ratio), (0, i * 32))
        out.info["transparency"] = 0
        before = im.copy()
        after = [frame_box(out, i) for i in range(2)]
        assert all(b and max(b[2]-b[0], b[3]-b[1]) <= MAX_SIZE for b in after), path
        assert all(b[0] >= 1 and b[1] >= 1 and b[2] <= 31 and b[3] <= 31 for b in after), path
        assert out.getpalette() == im.getpalette()
        assert set(out.getdata()).issubset(set(im.getdata()) | {0})
        # No need to modify already-identical bytes.
        if out.tobytes() == im.tobytes():
            return None
        if not dry_run:
            out.save(path, transparency=0, optimize=False)
        return {
            "before": [list(b) for b in boxes],
            "after": [list(b) for b in after],
            "before_occupied": [list(v) for v in dims],
            "after_occupied": [[b[2]-b[0], b[3]-b[1]] for b in after],
            "before_sha256": hashlib.sha256(before.tobytes()).hexdigest(),
            "after_sha256": hashlib.sha256(out.tobytes()).hexdigest(),
            "_before_image": before,
            "_after_image": out,
        }

def render_sheet(changes: list[dict]):
    if not changes:
        return
    columns = 4
    tile_w, tile_h = 280, 163
    canvas = Image.new("RGB", (columns * tile_w, math.ceil(len(changes) / columns) * tile_h), "#f6f6f6")
    pen = ImageDraw.Draw(canvas)
    for i, record in enumerate(changes):
        x = (i % columns) * tile_w
        y = (i // columns) * tile_h
        pen.text((x + 8, y + 6), record["name"], fill="#141414")
        for k, key in enumerate(("_before_image", "_after_image")):
            im = record[key].crop((0, 0, 32, 32)).convert("RGBA").resize((112, 112), Image.Resampling.NEAREST)
            background = Image.new("RGBA", (112, 112), (224, 224, 224, 255))
            background.alpha_composite(im)
            canvas.paste(background.convert("RGB"), (x + 8 + 132 * k, y + 26))
        pen.text((x + 8, y + 141), "BEFORE", fill="#444444")
        pen.text((x + 140, y + 141), "AFTER", fill="#444444")
    canvas.save(OUT / "before-after-icons.png")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()
    j = json.loads(MANIFEST.read_text(encoding="utf-8"))
    assert len(j["species"]) == 70
    changes = []
    unique_paths = set()
    for s in j["species"]:
        rel = s["images"].get("icon", {}).get("path")
        rel = rel.replace(chr(92), "/") if rel else rel
        if not rel or not unique_path(s["name"], rel):
            continue
        assert rel not in unique_paths, f"custom icon unexpectedly shared: {rel}"
        unique_paths.add(rel)
        path = ROOT / rel
        result = resize_icon(path, args.dry_run)
        if result:
            result["name"] = s["name"]
            result["path"] = rel
            changes.append(result)
    # Include the dark, red-eyed I-Unown icon outside the custom-ID 70 block.
    eye = "graphics/pokemon/unown_eye/icon.png"
    if (ROOT / eye).is_file() and eye not in unique_paths:
        result = resize_icon(ROOT / eye, args.dry_run)
        if result:
            result["name"] = "I-UNOWN"
            result["path"] = eye
            changes.append(result)
    print(f"Job 10 icon cleanup: {len(changes)} unique icons adjusted; "
          f"{len(unique_paths)} custom icons inspected; dry_run={args.dry_run}")
    for r in changes:
        print(f"  {r['name']}: {r['before_occupied']} -> {r['after_occupied']}")
    if not args.dry_run:
        OUT.mkdir(parents=True, exist_ok=True)
        render_sheet(changes)
        safe = [{k: v for k, v in r.items() if not k.startswith("_")} for r in changes]
        report = {
            "job": 10, "baseline": "Job 9 commit 768ca315f8",
            "max_icon_extent_px": MAX_SIZE,
            "checked_custom_icon_count": len(unique_paths),
            "changed_icon_count": len(safe),
            "excluded_shared_source_icons": sorted(SHARED),
            "preserved_approved_species": sorted(PRESERVE),
            "unresolved_elite_four_relic_back_art_count": 10,
            "source_visual_check_only": True,
            "changes": safe,
        }
        (OUT / "icon-changes.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        (OUT / "README.md").write_text(
            "# PRU Job 10 icon QA\n\n"
            f"Normalised {len(safe)} distinct PC/party icons to fit within {MAX_SIZE}px. "
            "Each retains its existing 4-bit palette, two animation frames and transparent index zero.\n\n"
            "These are GBA source sprite comparisons, not screenshots of live PC boxes. "
            "Do not report a visual emulator review as passed until performed.\n\n"
            "**Still outstanding:** ten Elite Four Relic rear sprites lack approved authentic "
            "back-view donors. Existing front-art substitutions have NOT been disguised as real rears.\n",
            encoding="utf-8",
        )

if __name__ == "__main__":
    main()
