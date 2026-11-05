#!/usr/bin/env python3
"""Apply targeted, palette-safe fixes from the user's PC sprite review video.

This stage runs after all normal sprite installers. It changes only the four
reviewed Infinity/PRL battle species' front/back images, selected box icons of reviewed custom
species, Fortotoise's party icon, and Charaxis's party icon. It does not touch
species, stats, moves, maps, events, save data, or Eeveelution battle sprites.
"""
from __future__ import annotations

import json
import hashlib
import re
from pathlib import Path

from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
GFX = ROOT / "graphics/pokemon"
SOURCES = ROOT / "assets/pru_video_review"
REPORT_DIR = ROOT / "PRU-QA/video-review"

# The names match each icon graphics symbol in the frames of the attached
# video. Relic Alakazam/Hitmonlee use their vanilla icons and are checked as
# such without resizing a shared species icon. Nolax is deliberately omitted.
ICON_SYMBOLS = (
    "Nimbeon", "Drakeon", "Champeon", "Guardeon", "Toxeon", "Sphynxeon",
    "Skarmet", "Kablowfish", "Grimfowl", "Heracurion", "Scarabub",
    "Skarmadon", "Jollibird", "Osteodian", "Sunflorid", "Sudowarden",
    "Mystynx", "Ghoulbat", "Khang", "Fortotoise", "Charaxis", "HoOhRelic",
    "Hitmonlee", "Alakazam", "Gemlin", "Gemigoyle", "Astrachi", "Adnokana",
    "Cheauking", "Frytning", "Mewsion", "Tropisaur", "Coelossus", "Cactomb",
    "Torkaldera", "Sceptitan", "Solaziken",
)

# Bound each reviewed large/edge-touching battle image within the 64x64 GBA
# canvas using nearest-neighbour scaling, then ground it. Gemlin is the one
# notably undersized front sprite in the video and is enlarged without adding
# or recolouring pixels. The separate approved Eeveelution art is untouched.
BATTLE_FRAME_LIMITS = {
    ("gemlin", "front"): 44,
    ("gemlin", "back"): 44,
    # Player-approved replacement poses, preserved at their hand-framed
    # 64x64 size. The source assets use the existing species palettes.
    ("gemigoyle", "front"): 64,
    ("gemigoyle", "back"): 64,
    ("jollibird", "front"): 64,
    ("jollibird", "back"): 64,
    ("kablowfish", "front"): 64,
    ("kablowfish", "back"): 64,
    ("grimfowl", "front"): 64,
    ("grimfowl", "back"): 64,
}
APPROVED_BATTLE_REPLACEMENTS = {"gemigoyle", "jollibird", "kablowfish", "grimfowl"}


def graphics_asset_paths(kind: str) -> dict[str, Path]:
    paths: dict[str, Path] = {}
    pattern = re.compile(
        rf"gMon{kind}_(\w+)\[\]\s*=\s*INCBIN_U\d+\(\"([^\"]+)\.4bpp(?:\.smol)?\"\)"
    )
    for header in (ROOT / "src/data/graphics/pjr.h", ROOT / "src/data/graphics/pru_pokemon.h"):
        for symbol, rel in pattern.findall(header.read_text()):
            paths[symbol] = ROOT / (rel + ".png")
    return paths


def icon_bbox(frame: Image.Image) -> tuple[int, int, int, int] | None:
    values = frame.convert("P")
    return values.point(lambda value: 255 if value else 0).getbbox()


def shrink_icon(path: Path, symbol: str) -> dict:
    # Scale the icon installed by the complete preceding sprite pipeline.
    # That tree is the approved post-installer source the user sees; pinned
    # review snapshots are references, not replacements for newer installers.
    source_path = path
    with Image.open(source_path) as source:
        source.load()
        assert source.mode in {"P", "RGBA"} and source.size == (32, 64), (path, source.mode, source.size)
        palette = source.getpalette() if source.mode == "P" else None
        if palette:
            assert max(source.getdata()) < 16, path
            out = Image.new("P", (32, 64), 0)
            out.putpalette(palette)
        else:
            out = Image.new("RGBA", (32, 64), (0, 0, 0, 0))
        records = []
        for frame_number, y0 in enumerate((0, 32)):
            frame = source.crop((0, y0, 32, y0 + 32))
            bounds = icon_bbox(frame) if frame.mode == "P" else frame.getchannel("A").getbbox()
            assert bounds is not None, (path, frame_number, "empty icon frame")
            crop = frame.crop(bounds)
            old_size = crop.size
            # Use crisp nearest-neighbour pixels and standard 20% reduction.
            new_size = (max(1, round(old_size[0] * 0.8)), max(1, round(old_size[1] * 0.8)))
            if max(old_size) > 25:
                crop = crop.resize(new_size, Image.Resampling.NEAREST)
            else:
                new_size = old_size
            frame_out = Image.new(source.mode, (32, 32), 0 if source.mode == "P" else (0, 0, 0, 0))
            if palette:
                frame_out.putpalette(palette)
            frame_out.paste(crop, ((32 - crop.width) // 2, 31 - crop.height))
            out.paste(frame_out, (0, y0))
            records.append({"frame": frame_number, "before_bbox_size": list(old_size),
                            "after_bbox_size": list(crop.size),
                            "reduced": crop.size != old_size})
        if out.mode == "P":
            out.info["transparency"] = 0
        out.save(path, optimize=False)
    return {"path": str(path.relative_to(ROOT)), "frames": records}


def fit_battle_sprite(name: str, side: str, max_extent: int) -> dict:
    source_path = SOURCES / name / f"{side}.png"
    assert source_path.is_file(), source_path
    # These files are the pinned approved indexed donor art. Resize indices,
    # never convert through RGB, so the shared original 16-colour palette and
    # every existing donor colour survive exactly.
    with Image.open(source_path) as source:
        source.load()
        assert source.mode == "P" and source.size == (64, 64), (source_path, source.mode, source.size)
        palette = source.getpalette()
        source.info["transparency"] = 0
        if name in APPROVED_BATTLE_REPLACEMENTS:
            # These are the player's accepted alternate poses. Preserve their
            # exact pixel placement and palette indices; only transparent
            # index 0 is used as the background.
            assert source.info.get("transparency") == 0
            normal_pal = (SOURCES / name / "normal.pal").read_text().splitlines()
            colors = [tuple(map(int, line.split())) for line in normal_pal[3:3 + int(normal_pal[2])]]
            assert len(colors) == 16
            assert palette[:48] == [component for color in colors for component in color]
            used = set(source.getdata())
            assert max(used) < 16 and len(used) <= 16
            if side == "back":
                assert all(source.getpixel((x, y)) == 0 for y in range(51, 64) for x in range(64))
            destination = GFX / "prl_authoritative" / name / f"{side}.png"
            destination.parent.mkdir(parents=True, exist_ok=True)
            source_path_bytes = source_path.read_bytes()
            destination.write_bytes(source_path_bytes)
            # The new pixel data is indexed against this exact existing
            # palette; restore it after the older pinned donor sync stage.
            (destination.parent / "normal.pal").write_bytes(
                (SOURCES / name / "normal.pal").read_bytes()
            )
            return {"species": name, "side": side,
                    "path": str(destination.relative_to(ROOT)),
                    "before_bbox": list(icon_bbox(source)), "after_bbox": list(icon_bbox(source)),
                    "method": "exact player-approved 64x64 pixels; existing game palette indices retained",
                    "sha256": hashlib.sha256(source_path_bytes).hexdigest()}
        bounds = icon_bbox(source)
        assert bounds is not None, source_path
        crop = source.crop(bounds)
        before = crop.size
        factor = min(1.5 if name == "gemlin" and side == "front" else 1.0,
                    max_extent / max(before))
        new_size = (max(1, round(before[0] * factor)), max(1, round(before[1] * factor)))
        sprite = crop.resize(new_size, Image.Resampling.NEAREST)
        if name == "gemlin" and side == "back":
            # This is the genuine donor rear view, not a flipped front. Its
            # donor orientation was reversed for the player-side perspective.
            sprite = sprite.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
        out = Image.new("P", (64, 64), 0)
        out.putpalette(palette)
        out.paste(sprite, ((64 - sprite.width) // 2, 62 - sprite.height))
        out.info["transparency"] = 0
        destination = GFX / "prl_authoritative" / name / f"{side}.png"
        destination.parent.mkdir(parents=True, exist_ok=True)
        out.save(destination, optimize=False)
    return {"species": name, "side": side, "path": str(destination.relative_to(ROOT)),
            "before_bbox": list(before), "after_bbox": list(new_size),
            "method": "nearest-neighbour; original palette indices retained; grounded to y=62"}


def make_contact_sheet(icon_paths: list[tuple[str, Path]]) -> None:
    cols, tile_w, tile_h = 6, 150, 140
    rows = (len(icon_paths) + cols - 1) // cols
    sheet = Image.new("RGB", (cols * tile_w, rows * tile_h), (38, 38, 42))
    draw = ImageDraw.Draw(sheet)
    for i, (name, path) in enumerate(icon_paths):
        x0, y0 = (i % cols) * tile_w, (i // cols) * tile_h
        draw.text((x0 + 5, y0 + 4), name, fill="white")
        with Image.open(path) as icon:
            icon.load()
            if icon.mode == "P" and "transparency" not in icon.info:
                icon.info["transparency"] = 0
            frame = icon.crop((0, 0, 32, 32)).convert("RGBA").resize((96, 96), Image.Resampling.NEAREST)
        tile = Image.new("RGBA", frame.size, (180, 180, 180, 255))
        for y in range(0, 96, 8):
            for x in range(0, 96, 8):
                if (x // 8 + y // 8) % 2:
                    tile.paste((220, 220, 220, 255), (x, y, x + 8, y + 8))
        tile.alpha_composite(frame)
        sheet.paste(tile.convert("RGB"), (x0 + 5, y0 + 22))
        rel = path.relative_to(ROOT).as_posix()
        source = "Vanilla shared" if path.parent.name in {"pikachu", "hitmonlee", "alakazam"} else "PRU custom"
        draw.text((x0 + 5, y0 + 122), source + " | " + Path(rel).parent.name, fill=(205, 205, 205))
    REPORT_DIR.mkdir(parents=True, exist_ok=True)
    sheet.save(REPORT_DIR / "selected-party-and-pc-icons.png", optimize=False)


def main() -> None:
    icon_paths_by_symbol = graphics_asset_paths("Icon")
    icon_records = []
    contact = []
    vanilla_shared = []
    for symbol in ICON_SYMBOLS:
        if symbol not in icon_paths_by_symbol and symbol in {"Hitmonlee", "Alakazam"}:
            # The Relic battle forms deliberately reuse these original icons.
            icon_paths_by_symbol[symbol] = GFX / symbol.lower() / "icon.png"
        if symbol not in icon_paths_by_symbol:
            raise SystemExit(f"Missing icon graphics reference for video selection {symbol}")
        path = icon_paths_by_symbol[symbol]
        if path.parent.name in {"pikachu", "hitmonlee", "alakazam"}:
            vanilla_shared.append({"name": symbol, "path": str(path.relative_to(ROOT)),
                                  "result": "uses unchanged canonical vanilla icon"})
            contact.append((symbol, path))
            continue
        if symbol in {"Charaxis", "Fortotoise"}:
            # Both have explicit source/palette installers; those just ran.
            # They still receive the same 20% scale as the other reviewed icons.
            pass
        icon_records.append({"name": symbol, **shrink_icon(path, symbol)})
        contact.append((symbol, path))

    battle_records = [fit_battle_sprite(name, side, limit)
                      for (name, side), limit in BATTLE_FRAME_LIMITS.items()]
    make_contact_sheet(contact)
    summary = {
        "video": "1000043684.mp4",
        "reviewed_species": [symbol for symbol in ICON_SYMBOLS],
        "omitted_by_user_instruction": ["Nolax"],
        "icon_adjustments": icon_records,
        "shared_vanilla_icons_left_unchanged": vanilla_shared,
        "battle_sprite_adjustments": battle_records,
        "palette_policy": "nearest-neighbour only; icon indices and all four reviewed donors' colours retained",
        "human_visual_review_required": True,
        "contact_sheet": "PRU-QA/video-review/selected-party-and-pc-icons.png",
    }
    REPORT_DIR.mkdir(parents=True, exist_ok=True)
    (REPORT_DIR / "report.json").write_text(json.dumps(summary, indent=2) + "\n")
    lines = ["# Video sprite review repairs", "",
             f"Reviewed {len(ICON_SYMBOLS)} icon references from the attached clip. Nolax was excluded.",
             "Custom icons were reduced by 20% with nearest-neighbour pixels when their frame exceeded 25 pixels in either dimension. Shared vanilla icons were left untouched.",
             "", "## Icons reduced", ""]
    for record in icon_records:
        changed = any(frame["reduced"] for frame in record["frames"])
        lines.append(f"- {record['name']}: {'reduced' if changed else 'already compact'} (`{record['path']}`).")
    lines.extend(["", "## Battle image framing", ""])
    for record in battle_records:
        extra = "; genuine Gemlin back donor oriented for player side" if record['species'] == 'gemlin' and record['side'] == 'back' else ""
        lines.append(f"- {record['species']} {record['side']}: {record['before_bbox']} → {record['after_bbox']} px; nearest-neighbour and original palette indexes retained{extra}.")
    lines.extend(["", "Visual acceptance still requires checking the finished ROM in mGBA."])
    (REPORT_DIR / "report.md").write_text("\n".join(lines) + "\n")
    print(f"VIDEO_REVIEW: adjusted {sum(any(f['reduced'] for f in item['frames']) for item in icon_records)} icons; framed {len(battle_records)} battle sprites; Nolax untouched")


if __name__ == "__main__":
    main()
