#!/usr/bin/env python3
"""Audit custom species 1573–1642 and create source-grouped visual review sheets.

This is a reproducible asset/source audit, not a claim that screenshots have
been reviewed in a running game. Run it after every sprite installer.
"""
from __future__ import annotations

import hashlib
import json
import re
from collections import defaultdict
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / "PRU-QA"
RANGE = range(1573, 1643)
FLAGGED = {
    "GEMLIN", "KABLOWFISH", "SUNFLORID", "TROPISAUR", "CROBAT_RELIC",
    "COELOSSUS", "CACTOMB", "CHEAUKING", "GRIMFOWL", "NIMBEON",
    "ADNOKANA", "BEEDRILL_RELIC", "JOLLIBIRD", "FORTOTOISE",
    "GEMIGOYLE", "SCARABUB", "TORKALDERA", "CHARAXIS", "KHANG",
    "RELIC_HO_OH", "UNOWN_EYE",
}
REPAIR_NOTES = {
    "GEMLIN": "Retained its distinct authentic rear donor, corrected rear orientation and grounding, and reframed the undersized front with nearest-neighbour pixels.",
    "JOLLIBIRD": "Retained its established donor design and palette; reduced oversized front/rear framing with nearest-neighbour pixels and grounded the back.",
    "GRIMFOWL": "Retained the dark owl and pale horns; reduced oversized front/rear framing with nearest-neighbour pixels and grounded both views.",
    "KABLOWFISH": "Retained the white-spiked body and purple features; reduced oversized front/rear framing with nearest-neighbour pixels and grounded both views.",
    "FORTOTOISE": "Replaced wrong fossil/PRL front and back with supplied normal G-Max Blastoise assets; matching icon installed.",
    "ASUDEM_JJ": "Uses its own existing donor back file; no longer uses the front as back.",
    "NIDOGOD_JJ": "Uses its own existing donor back file; no longer uses the front as back.",
    "VICTREEBEL_REDUX_JJ": "Uses its own existing donor back file; no longer uses the front as back.",
    "TYRANITAR_REDUX_JJ": "Uses its own existing donor back file; no longer uses the front as back.",
}
UNRESOLVED = {
    "ALAKAZAM_RELIC", "SLOWKING_RELIC", "BEEDRILL_RELIC", "CROBAT_RELIC",
    "HITMONCHAN_RELIC", "HITMONLEE_RELIC", "MACHAMP_RELIC", "HOUNDOOM_RELIC",
    "GYARADOS_RELIC", "DRAGONITE_RELIC",
}


def definitions() -> dict[str, int]:
    text = (ROOT / "include/constants/species.h").read_text()
    return {m.group(1): int(m.group(2)) for m in re.finditer(
        r"#define\s+SPECIES_([A-Z0-9_]+)\s+(\d+)\b", text
    ) if int(m.group(2)) in RANGE}


def graphics_symbols() -> dict[str, str]:
    result = {}
    for path in (ROOT / "src/data/graphics").rglob("*.h"):
        text = path.read_text(errors="replace")
        for m in re.finditer(
            r"const\s+\w+\s+(gMon(?:FrontPic|BackPic|Icon|Palette|ShinyPalette)_\w+)\[\]\s*=\s*INCBIN_\w+\(\"([^\"]+)\"\)", text
        ):
            result[m.group(1)] = m.group(2)
    return result


def species_source(name: str) -> str:
    for path in (ROOT / "src/data/pokemon/species_info").glob("*.h"):
        text = path.read_text(errors="replace")
        direct = re.search(rf"\[SPECIES_{name}\]\s*=\s*\{{", text)
        if direct:
            nxt = re.search(r"\[SPECIES_[A-Z0-9_]+\]\s*=\s*\{", text[direct.end():])
            return text[direct.start():direct.end() + nxt.start() if nxt else len(text)]
        call = re.search(rf"(?:PJR_[A-Z0-9_]+)\(SPECIES_{name},", text)
        if call:
            start = call.start()
            depth = 0
            for i in range(text.index("(", start), len(text)):
                if text[i] == "(": depth += 1
                elif text[i] == ")":
                    depth -= 1
                    if depth == 0:
                        return text[start:i + 1]
    return ""


def source_kind(paths: list[str]) -> str:
    joined = " ".join(paths).lower()
    if "pjr_e4" in joined: return "Elite Four Relic forms"
    if any(k in joined for k in ("arbok/asudem", "nidoking/nidogod", "victreebel/redux", "tyranitar/mega_redux")):
        return "Jessie & James forms"
    if "prl_authoritative" in joined: return "Pinned PRL imports"
    if "pjr_infinity" in joined or "pru_eeveelution" in joined: return "Infinity / approved Eeveelutions"
    if any(k in joined for k in ("pru_final_polish", "pru_user_calf", "pru_valkiri", "pru_whackahack")):
        return "Bespoke PRU assets"
    return "Other donor / engine assets"


def image_info(path: Path | None) -> dict:
    if not path or not path.is_file():
        return {"exists": False}
    try:
        with Image.open(path) as im:
            im.load()
            rgba = im.convert("RGBA")
            alpha = rgba.getchannel("A")
            indices = list(im.getdata()) if im.mode == "P" else []
            transparent = im.info.get("transparency") if im.mode == "P" else None
            # GBA indexed art treats palette index 0 as transparent even when
            # the source PNG omitted a PNG tRNS chunk.
            if im.mode == "P" and transparent is None and 0 in indices:
                transparent = 0
                alpha = Image.eval(im, lambda value: 0 if value == 0 else 255)
            box = alpha.getbbox()
            used = sorted(set(indices)) if indices else sorted(set(rgba.getdata()))
            return {
                "exists": True, "path": str(path.relative_to(ROOT)), "mode": im.mode,
                "dimensions": list(im.size), "used_indices": used if indices else None,
                "used_index_count": len(used) if indices else None,
                "transparent_index": transparent,
                "has_transparent_pixels": alpha.getextrema()[0] < 255,
                "visible_bounds": list(box) if box else None,
                "touches_canvas_edge": bool(box and (box[0] == 0 or box[1] == 0 or box[2] == im.width or box[3] == im.height)),
                "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
            }
    except Exception as exc:
        return {"exists": True, "path": str(path.relative_to(ROOT)), "error": str(exc)}


def png_from_symbol(symbol: str | None, symbols: dict[str, str]) -> Path | None:
    if not symbol or symbol not in symbols:
        return None
    src = symbols[symbol]
    # INCBIN files are generated from same-stem PNGs; palette paths are not art.
    if ".4bpp" not in src and not src.endswith(".png"):
        return None
    png = re.sub(r"\.4bpp(?:\.smol)?$", ".png", src)
    return ROOT / png


def picture_symbols(src: str) -> dict[str, str | None]:
    return {key: (re.search(rf"gMon{prefix}_(\w+)", src).group(0)
                  if re.search(rf"gMon{prefix}_(\w+)", src) else None)
            for key, prefix in (("front", "FrontPic"), ("back", "BackPic"), ("icon", "Icon"), ("palette", "Palette"))}


def call_arguments(src: str) -> list[str] | None:
    start = src.find("(")
    if start < 0: return None
    depth = 0
    args, part = [], []
    for char in src[start + 1:]:
        if char == "(" : depth += 1
        elif char == ")":
            if depth == 0:
                args.append("".join(part).strip())
                return args
            depth -= 1
        if char == "," and depth == 0:
            args.append("".join(part).strip()); part = []
        else:
            part.append(char)
    return None


def back_y_offset(src: str) -> int | None:
    direct = re.search(r"\.backPicYOffset\s*=\s*(-?\d+)", src)
    if direct:
        return int(direct.group(1))
    args = call_arguments(src)
    if not args:
        return None
    prefix = src[:src.find("(")].strip()
    if prefix == "PJR_E4_VISUAL_FORM":
        return 0
    index = {"PJR_FINAL_SPECIES": 26, "PJR_RED_SPECIES": 23}.get(prefix)
    if index is None or len(args) <= index or not re.fullmatch(r"-?\d+", args[index]):
        return None
    return int(args[index])


def effective_icon_palette(name: str, src: str) -> int | None:
    # Per-species overrides are resolved by the runtime palette lookup.
    icon_code = (ROOT / "src/pokemon_icon.c").read_text()
    override = re.search(rf"if \(species == SPECIES_{name}\)\s*return (\d+);", icon_code)
    if override:
        return int(override.group(1))
    field = re.search(r"\.iconPalIndex\s*=\s*([^,\n]+)", src)
    if field:
        expression = field.group(1).strip()
    else:
        args = call_arguments(src)
        if not args: return None
        prefix = src[:src.find("(")].strip()
        index = {"PJR_FINAL_SPECIES": 22, "PJR_RED_SPECIES": 24, "PJR_E4_VISUAL_FORM": 21}.get(prefix)
        if index is None or len(args) <= index: return None
        expression = args[index]
    if expression.isdecimal(): return int(expression)
    conditional = re.search(r"P_GBA_STYLE_SPECIES_ICONS\s*\?\s*(\d+)\s*:\s*(\d+)", expression)
    if conditional:
        config = (ROOT / "include/config/pokemon.h").read_text()
        enabled = bool(re.search(r"#define\s+P_GBA_STYLE_SPECIES_ICONS\s+TRUE", config))
        return int(conditional.group(1 if enabled else 2))
    return None


def icon_palette_colors(index: int | None) -> list[tuple[int, int, int]] | None:
    if index is None: return None
    if index < 6:
        path = ROOT / f"graphics/pokemon/icon_palettes/pal{index}.pal"
        lines = path.read_text().splitlines()[3:19]
        return [tuple(map(int, line.split())) for line in lines]
    code = (ROOT / "src/pokemon_icon.c").read_text()
    table = re.search(r"const struct SpritePalette gMonIconPaletteTable\[\]\s*=\s*\{(.*?)\};", code, re.S)
    assert table
    row = re.search(rf"\{{\s*(\w+)\s*,\s*POKE_ICON_BASE_PAL_TAG\s*\+\s*{index}\s*\}}", table.group(1))
    if not row: return None
    colors = re.search(rf"static const u16 {row.group(1)}\[16\]\s*=\s*\{{(.*?)\}};", code, re.S)
    if not colors: return None
    rgb5 = [tuple(map(int, item)) for item in re.findall(r"RGB\((\d+),\s*(\d+),\s*(\d+)\)", colors.group(1))]
    return [tuple(round(channel * 255 / 31) for channel in color) for color in rgb5]


def visible_equal(a: Path | None, b: Path | None) -> bool | None:
    if not a or not b or not a.is_file() or not b.is_file(): return None
    try:
        with Image.open(a) as ia, Image.open(b) as ib:
            return ia.size == ib.size and list(ia.convert("RGBA").getdata()) == list(ib.convert("RGBA").getdata())
    except Exception:
        return None


def alpha_checker(size: tuple[int, int]) -> Image.Image:
    bg = Image.new("RGB", size, (224, 224, 224))
    d = ImageDraw.Draw(bg)
    step = 8
    for y in range(0, size[1], step):
        for x in range(0, size[0], step):
            if (x // step + y // step) % 2:
                d.rectangle((x, y, x + step - 1, y + step - 1), fill=(180, 180, 180))
    return bg


def render(path: Path | None, size: tuple[int, int], palette: list[tuple[int, int, int]] | None = None) -> Image.Image:
    tile = alpha_checker(size)
    if path:
        path = Path(path)
    if path and path.is_file():
        with Image.open(path) as src:
            src.load()
            if palette and src.mode == "P":
                src.putpalette([v for color in palette for v in color] + [0] * (768 - 48))
                src.info["transparency"] = 0
            elif src.mode == "P" and "transparency" not in src.info and 0 in set(src.getdata()):
                # Match GBA indexed-art semantics when a donor omitted tRNS.
                src.info["transparency"] = 0
            rgba = src.convert("RGBA")
            if rgba.size != size:
                rgba.thumbnail(size, Image.Resampling.NEAREST)
            tile.paste(rgba, ((size[0] - rgba.width) // 2, (size[1] - rgba.height) // 2), rgba)
    return tile


def make_sheet(group: str, rows: list[dict], out: Path) -> None:
    cell_w, cell_h, cols = 320, 220, 3
    title_h = 48
    height = title_h + ((len(rows) + cols - 1) // cols) * cell_h
    sheet = Image.new("RGB", (cols * cell_w, height), "white")
    draw = ImageDraw.Draw(sheet)
    draw.text((10, 12), f"PRU sprite review — {group} — transparency checkerboard; nearest-neighbour", fill="black")
    for i, row in enumerate(rows):
        x = (i % cols) * cell_w
        y = title_h + (i // cols) * cell_h
        draw.rectangle((x + 2, y + 2, x + cell_w - 3, y + cell_h - 3), outline=(170, 170, 170))
        status_color = {"FAIL": (180, 0, 0), "REVIEW": (150, 90, 0), "PASS": (0, 110, 0)}[row["status"]]
        draw.text((x + 8, y + 6), f"{row['name']} ({row['id']}) — {row['status']}", fill=status_color)
        for j, key in enumerate(("front", "back", "icon")):
            w, h = ((64, 64) if key != "icon" else (32, 64))
            runtime_pal = row.get("_runtime_icon_palette") if key == "icon" else None
            im = render(row["images"][key].get("_path"), (w, h), runtime_pal)
            im = im.resize((w * 3 // 2, h * 3 // 2), Image.Resampling.NEAREST)
            px = x + 10 + j * 102
            py = y + 30
            sheet.paste(im, (px, py))
            draw.text((px, py + h * 3 // 2 + 2), key, fill="black")
        paths = (row.get("source_paths") or "").split("; ")
        if paths:
            front_source = Path(paths[0]).parent.name
            icon_source = Path(paths[2]).parent.name if len(paths) > 2 else "?"
            source_label = f"front/back donor: {front_source} · icon: {icon_source}"
        else:
            source_label = "source unresolved"
        draw.text((x + 8, y + 171), source_label[:51], fill=(40, 40, 40))
        notes = " · ".join(row.get("failures", []) or row.get("repairs", []) or ["human visual review pending"])
        draw.text((x + 8, y + 191), notes[:51], fill=(110, 30, 30) if row["status"] == "FAIL" else (60, 60, 60))
    out.parent.mkdir(parents=True, exist_ok=True)
    sheet.save(out, optimize=True)


def main() -> None:
    ids = definitions()
    assert len(ids) == 70, f"Expected 70 IDs 1573-1642, found {len(ids)}"
    symbols = graphics_symbols()
    workflow = (ROOT / ".github/workflows/pru-clean-build.yml").read_text()
    audit_at = workflow.index("python3 tools/pru/audit_custom_sprites_70.py")
    required_stages = (
        "python3 tools/pru/install_final_polish_sprites.py",
        "python3 tools/pru/repair_reported_pc_sprites.py",
        "python3 tools/pru/install_user_calf_sprites.py",
        "python3 tools/pru/restore_build538_eeveelution_art.py",
    )
    stage_order = {stage: workflow.index(stage) < audit_at for stage in required_stages}
    assert all(stage_order.values()), f"Sprite audit runs before final installers: {stage_order}"
    rows = []
    for name, species_id in sorted(ids.items(), key=lambda item: item[1]):
        src = species_source(name)
        refs = picture_symbols(src)
        paths = {k: png_from_symbol(v, symbols) for k, v in refs.items()}
        images = {k: image_info(paths[k]) for k in ("front", "back", "icon")}
        for k in images:
            images[k]["_path"] = str(paths[k]) if paths[k] else None
        failures, warnings = [], []
        for key, expected in (("front", [64, 64]), ("back", [64, 64]), ("icon", [32, 64])):
            info = images[key]
            if not info.get("exists"):
                failures.append(f"missing {key} source file")
            elif info.get("dimensions") != expected:
                failures.append(f"{key} dimensions {info.get('dimensions')} != {expected}")
            elif info.get("mode") == "P" and info.get("used_index_count", 99) > 16:
                failures.append(f"{key} uses >16 indices")
            elif info.get("mode") == "P" and info.get("transparent_index") != 0:
                warnings.append(f"{key} transparency index is {info.get('transparent_index')!r}")
            elif not info.get("has_transparent_pixels"):
                failures.append(f"{key} has no transparency")
            if info.get("touches_canvas_edge"):
                warnings.append(f"{key} visible art touches canvas edge; inspect for clipping")
        same = visible_equal(paths["front"], paths["back"])
        if same:
            warnings.append("front and back pixels are identical; human review required")
        if not src:
            failures.append("species graphics references were not parsed")
        source_paths = [images[k].get("path", "") for k in ("front", "back", "icon")]
        group = source_kind(source_paths)
        if name in UNRESOLVED:
            warnings.append("authentic species-specific back art unavailable in pinned source pack; current macro still duplicates front")
        palette_index = effective_icon_palette(name, src)
        back_y = back_y_offset(src)
        runtime_palette = icon_palette_colors(palette_index)
        if palette_index is None or runtime_palette is None:
            warnings.append("runtime icon palette could not be resolved")
        if back_y is None:
            warnings.append("effective back-sprite vertical offset could not be resolved")
        elif back_y < 0 or back_y > 16:
            warnings.append(f"back-sprite vertical offset {back_y} is unusual; inspect grounding and clipping")
        if images["icon"].get("exists") and images["icon"].get("has_transparent_pixels") is False:
            failures.append("party/PC icon has no transparent pixels")
        human = "NOT DONE — source/contact-sheet review is not in-game visual validation"
        tech = "FAIL" if failures else "PASS"
        status = "FAIL" if failures else "REVIEW"
        rows.append({
            "id": species_id, "name": name, "source_group": group,
            "back_pic_y_offset": back_y,
            "back_visible_bounds": images["back"].get("visible_bounds"),
            "back_visible_bottom_gap_px": (64 - images["back"]["visible_bounds"][3]) if images["back"].get("visible_bounds") else None,
            "species_front_symbol": refs["front"], "species_back_symbol": refs["back"],
            "icon_symbol": refs["icon"], "palette_symbol": refs["palette"], "icon_palette_index": palette_index,
            "source_paths": "; ".join(p for p in source_paths if p), "images": images,
            "front_back_pixel_identical": same, "technical_status": tech, "status": status,
            "source_provenance": group, "ci_workflow_stage_order_valid": all(stage_order.values()),
            "repairs": [REPAIR_NOTES[name]] if name in REPAIR_NOTES else [],
            "unresolved": name in UNRESOLVED,
            "human_visual_review": human, "failures": failures, "warnings": warnings,
            "_runtime_icon_palette": runtime_palette,
        })
    assert [r["id"] for r in rows] == list(RANGE)
    OUT.mkdir(parents=True, exist_ok=True)
    for r in rows:
        for im in r["images"].values(): im.pop("_path", None)
        r.pop("_runtime_icon_palette", None)
    additional_checks = [{
        "id": 1644, "name": "NIDOKING_X_BLUE", "scope": "outside the 70-species range",
        "status": "FAIL", "back_pic_y_offset": 0,
        "front_symbol": "gMonFrontPic_NidokingXBlue", "back_symbol": "gMonFrontPic_NidokingXBlue",
        "limitation": "The macro uses the front image because the pinned source pack contains no authentic rear sprite.",
    }, {
        "id": 250, "name": "GOLDEN_HO_OH", "scope": "outside the 70 custom-species range",
        "status": "REVIEW", "icon_symbol": "gMonIcon_HoOhRelic", "icon_palette_index": 6,
        "icon_path": "graphics/pokemon/ho_oh_relic/icon.png",
        "repair": "Kept the accepted icon silhouette and remapped feather indices to gold/cream/charcoal palette #6.",
    }]
    report = {
        "title": "PRU 70 custom Pokémon sprite technical audit",
        "scope": "species IDs 1573–1642; final source graphics references after CI installer order",
        "baseline": "Build #542 / e1346f10bf035e0a93fd93085f1cc58abeb66f4a",
        "totals": {
            "species": len(rows), "technical_pass": sum(r["technical_status"] == "PASS" for r in rows),
            "technical_fail": sum(r["technical_status"] == "FAIL" for r in rows),
            "status_pass": sum(r["status"] == "PASS" for r in rows),
            "status_review": sum(r["status"] == "REVIEW" for r in rows),
            "status_fail": sum(r["status"] == "FAIL" for r in rows),
            "requiring_human_visual_review": len(rows),
            "unresolved_authentic_back_sources": len(UNRESOLVED),
        },
        "emulator_validation": "Not performed by this source QA tool.",
        "ci_stage_order": stage_order,
        "species": rows,
        "additional_out_of_range_checks": additional_checks,
    }
    (OUT / "sprite-audit-70.json").write_text(json.dumps(report, indent=2) + "\n")
    lines = ["# PRU 70-species sprite audit", "", f"Baseline: #542 (`e1346f10bf`).", "",
             "This report validates source references and image technical properties. It does not claim in-game visual verification.", "",
             f"Species: **{len(rows)}** · Technical PASS: **{report['totals']['technical_pass']}** · FAIL: **{report['totals']['technical_fail']}** · Status PASS **{report['totals']['status_pass']}**, REVIEW **{report['totals']['status_review']}**, FAIL **{report['totals']['status_fail']}** · Human review pending: **{len(rows)}** · authentic E4 backs unresolved: **{len(UNRESOLVED)}**", "",
             "## Species status", "", "| ID | Species | Technical | Review | Source group | Front/back identical | Notes |", "|---:|---|---|---|---|---|---|"]
    for r in rows:
        notes = "; ".join(r["failures"] + r["warnings"] + r["repairs"])
        lines.append(f"| {r['id']} | {r['name']} | {r['technical_status']} | {r['status']} | {r['source_group']} | {r['front_back_pixel_identical']} | {notes or 'visual inspection pending'} |")
    lines += ["", "## Source-group review sheets", ""]
    for group in sorted({r["source_group"] for r in rows}):
        lines.append(f"- `{group}`: `contact-sheets/{slug(group)}.png`")
    lines += ["", "## Additional checks outside IDs 1573–1642", "", "Golden Ho-Oh (national species ID 250) has a custom gold icon using palette #6; its icon remains pending in-game confirmation. Nidoking X Blue (ID 1644) uses the front for its back because no authentic rear art is present in the pinned source tree.", "", "## Known source limitation", "", "The ten first-clear Elite Four Relic forms (IDs 1610–1619) have no authentic species-specific rear sprites in the pinned asset tree. They remain explicitly unresolved; no mirrored or palette-guessed rear art was substituted. The four Jessie & James forms use their existing separate rear PNGs.", "", "No emulator-rendered screenshot verification is claimed. Review sheets are source artwork previews only.", ""]
    (OUT / "sprite-audit-70.md").write_text("\n".join(lines))
    grouped = defaultdict(list)
    for r in rows:
        # restore image paths removed from report serialization
        src = species_source(r["name"])
        refs = picture_symbols(src)
        r["images"] = {k: {"_path": str(png_from_symbol(refs[k], symbols)) if png_from_symbol(refs[k], symbols) else None}
                        for k in ("front", "back", "icon")}
        r["_runtime_icon_palette"] = icon_palette_colors(r["icon_palette_index"])
        grouped[r["source_group"]].append(r)
    sheets = OUT / "contact-sheets"
    for group, items in grouped.items(): make_sheet(group, items, sheets / f"{slug(group)}.png")
    print(f"SPRITE_AUDIT_70_PASS: {len(rows)} species indexed; {report['totals']['technical_pass']} technical passes, {report['totals']['technical_fail']} failures; emulator visuals pending")


def slug(value: str) -> str:
    return re.sub(r"[^a-z0-9]+", "-", value.lower()).strip("-")


if __name__ == "__main__":
    main()
