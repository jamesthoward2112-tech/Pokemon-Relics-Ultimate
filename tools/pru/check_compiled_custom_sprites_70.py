#!/usr/bin/env python3
"""Compare all 70 installed source images with their compiled GBA 4bpp payloads."""
from __future__ import annotations
import subprocess
import tempfile
import hashlib
import json
from pathlib import Path

from audit_custom_sprites_70 import definitions, graphics_symbols, png_from_symbol, picture_symbols, species_source

ROOT = Path(__file__).resolve().parents[2]
SMOL = ROOT / "tools/compresSmol/compresSmol"
GBAGFX = ROOT / "tools/gbagfx/gbagfx"


def compare_png(source: Path, compiled: Path, temp: Path, *, compressed: bool) -> str:
    assert source.is_file(), f"missing source PNG: {source}"
    assert compiled.is_file(), f"missing compiled graphics: {compiled}"
    raw = temp / "source.4bpp"
    subprocess.run([str(GBAGFX), str(source), str(raw)], check=True, cwd=ROOT)
    if compressed:
        decoded = temp / "compiled.4bpp"
        subprocess.run([str(SMOL), "-d", str(compiled), str(decoded)], check=True, cwd=ROOT)
    else:
        decoded = compiled
    source_bytes, compiled_bytes = raw.read_bytes(), decoded.read_bytes()
    assert source_bytes == compiled_bytes, f"compiled 4bpp payload differs from source: {source} -> {compiled}"
    return hashlib.sha256(compiled_bytes).hexdigest()


def main() -> None:
    assert SMOL.is_file() and GBAGFX.is_file(), "sprite graphics converters were not built"
    refs = graphics_symbols()
    checked = 0
    skipped = []
    entries = []
    with tempfile.TemporaryDirectory(prefix="pru-sprite-rom-check-") as tmpdir:
        temp = Path(tmpdir)
        for name, species_id in sorted(definitions().items(), key=lambda item: item[1]):
            symbols = picture_symbols(species_source(name))
            for side, key in (("front", "front"), ("back", "back"), ("icon", "icon")):
                symbol = symbols[key]
                source = png_from_symbol(symbol, refs)
                if not source or not source.is_file():
                    skipped.append({"id": species_id, "name": name, "side": side, "reason": "source unresolved"})
                    continue
                registered = refs[symbol]
                raw_path = ROOT / registered
                if side == "icon":
                    compiled = raw_path
                    compressed = False
                else:
                    compiled = raw_path
                    compressed = True
                digest = compare_png(source, compiled, temp, compressed=compressed)
                entries.append({"id": species_id, "name": name, "side": side,
                                "source": str(source.relative_to(ROOT)),
                                "compiled": str(compiled.relative_to(ROOT)),
                                "compressed": compressed, "status": "PASS",
                                "compiled_4bpp_sha256": digest})
                checked += 1
    assert checked >= 200, f"too few compiled sprite assets compared: {checked}"
    report = {
        "title": "PRU 70-species compiled sprite payload audit",
        "method": "Convert source PNGs to GBA 4bpp with gbagfx; decompress .smol battle payloads and compare exact indices. Palette colours are recorded in sprite-audit-70.json.",
        "compiled_matches": checked, "compiled_mismatches": 0,
        "unresolved": skipped, "entries": entries,
    }
    out = ROOT / "PRU-QA"
    out.mkdir(exist_ok=True)
    (out / "compiled-sprite-audit-70.json").write_text(json.dumps(report, indent=2) + "\n")
    lines = ["# PRU compiled sprite payload audit", "",
             f"Exact source-to-ROM 4bpp matches: **{checked}**",
             f"Unresolved source references: **{len(skipped)}**", "",
             "This verifies compiled tile indices against source PNGs; it is not emulator-rendered visual verification.", "",
             "## Unresolved references", ""]
    lines += [f"- {entry['id']} {entry['name']} {entry['side']}: {entry['reason']}" for entry in skipped]
    lines += ["", "## Checked payloads", "", "| ID | Species | Side | Compiled asset | SHA-256 |", "|---:|---|---|---|---|"]
    lines += [f"| {entry['id']} | {entry['name']} | {entry['side']} | `{entry['compiled']}` | `{entry['compiled_4bpp_sha256']}` |" for entry in entries]
    (out / "compiled-sprite-audit-70.md").write_text("\n".join(lines) + "\n")
    print(f"PASS: {checked} compiled front/back/icon 4bpp payloads match source PNG pixel indices")
    print(f"REVIEW: {len(skipped)} references unresolved; reports written to PRU-QA/compiled-sprite-audit-70.*")


if __name__ == "__main__":
    main()
