#!/usr/bin/env python3
"""Restore the exact build-538 Eeveelution art without resizing it."""
from __future__ import annotations

from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[2]
GFX = ROOT / "graphics/pokemon"
PINNED = ROOT / "assets/pru_eeveelution_build538"


def canonical_bytes(path: Path, payload: bytes) -> bytes:
    # Git attributes may check palette text out with CRLF in CI.
    return payload.replace(b"\r\n", b"\n") if path.suffix == ".pal" else payload


def main() -> None:
    manifest = json.loads((PINNED / "manifest.json").read_text())
    assert manifest["source_commit"] == "3d6a0460d5c151de5bf3c7f1fe49cb6a94d38086"
    assert manifest["pinned_prl_commit"] == "6ee9b984521ac6f2beaf995f771a726379e55c88"
    assert len(manifest["files"]) == 50
    for relative, expected in manifest["files"].items():
        source = PINNED / relative
        payload = source.read_bytes()
        assert hashlib.sha256(canonical_bytes(source, payload)).hexdigest() == expected, relative
        name, filename = relative.split("/", 1)
        destination = (GFX / "prl_authoritative" / name / filename
                       if filename != "icon.png" else GFX / name / filename)
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(payload)
    print("EEVEELUTIONS: exact build-538 sprites, palettes and icons restored; original size retained")


if __name__ == "__main__":
    main()
