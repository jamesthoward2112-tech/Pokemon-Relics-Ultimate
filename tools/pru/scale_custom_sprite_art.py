#!/usr/bin/env python3
"""Restore the approved build-538 Eeveelution art, then shrink it by 20%.

The pinned source files are byte-for-byte copies of the art and palettes used
for build 538. Restore them after donor synchronization so the build cannot
substitute newer donor artwork. Only indexed pixels are nearest-neighbour
resampled; palettes, transparency, frame layout, and icon palette assignments
stay as they were in build 538.
"""
from __future__ import annotations

from pathlib import Path
from PIL import Image, PngImagePlugin
import hashlib
import json

ROOT = Path(__file__).resolve().parents[2]
GFX = ROOT / "graphics/pokemon"
PINNED = ROOT / "assets/pru_eeveelution_build538"
EEVEELUTIONS = (
    "champeon", "lepideon", "guardeon", "obsideon", "toxeon",
    "sphynxeon", "omeon", "drakeon", "eeveeon", "nimbeon",
)


def restore_build538_art() -> dict:
    manifest = json.loads((PINNED / "manifest.json").read_text())
    assert manifest["source_commit"] == "3d6a0460d5c151de5bf3c7f1fe49cb6a94d38086"
    assert manifest["pinned_prl_commit"] == "6ee9b984521ac6f2beaf995f771a726379e55c88"
    assert len(manifest["files"]) == 50
    for relative, expected in manifest["files"].items():
        source = PINNED / relative
        payload = source.read_bytes()
        # Git's .gitattributes checks palettes out as CRLF on Actions runners.
        # Hash the canonical text so that checkout line endings are irrelevant.
        if source.suffix == ".pal":
            payload = payload.replace(b"\r\n", b"\n")
        assert hashlib.sha256(payload).hexdigest() == expected, relative
        name, filename = relative.split("/", 1)
        dest = (GFX / "prl_authoritative" / name / filename
                if filename != "icon.png" else GFX / name / filename)
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(source.read_bytes())
    return manifest


def save_indexed(path: Path, image: Image.Image, palette: list[int], tags: dict[str, str]) -> None:
    image.putpalette(palette)
    image.info["transparency"] = 0
    info = PngImagePlugin.PngInfo()
    for key, value in tags.items():
        info.add_text(key, value)
    image.save(path, optimize=False, pnginfo=info)


def scale_frames(path: Path, *, frame_height: int, scale: float = 0.8) -> None:
    with Image.open(path) as source:
        assert source.mode == "P" and source.info.get("transparency") in (None, 0), (path, source.mode, source.info)
        width, height = source.size
        assert height % frame_height == 0, (path, source.size, frame_height)
        colors = source.getpalette()
        assert colors is not None and len(colors) >= 48
        palette = colors[:768]
        frames = [source.crop((0, y, width, y + frame_height)) for y in range(0, height, frame_height)]

    out = Image.new("P", (width, height), 0)
    out.putpalette(palette)
    for frame_index, frame in enumerate(frames):
        scaled_w, scaled_h = round(width * scale), round(frame_height * scale)
        resized = frame.resize((scaled_w, scaled_h), Image.Resampling.NEAREST)
        xoff, yoff = (width - scaled_w) // 2, (frame_height - scaled_h) // 2
        out.paste(resized, (xoff, frame_index * frame_height + yoff))
    save_indexed(path, out, palette, {"PRU_SPRITE_SCALE": "80%", "PRU_SPRITE_BASE": "build-538"})


def main() -> None:
    restore_build538_art()
    for name in EEVEELUTIONS:
        folder = GFX / "prl_authoritative" / name
        for side in ("front", "back"):
            scale_frames(folder / f"{side}.png", frame_height=64)
        scale_frames(GFX / name / "icon.png", frame_height=32)
    print("SPRITE_SCALE: restored build-538 artwork/palettes/icons; only 20% rescaled")


if __name__ == "__main__":
    main()
