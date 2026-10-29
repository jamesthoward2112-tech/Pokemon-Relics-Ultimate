#!/usr/bin/env python3
"""Compose GBA-native Elite 20 duo banners from the existing approved trainer art.

These are distinct cinematic pair portraits, not replacements for the locked
Jessie/James, Eevee twins, Red/Blue, Steven/May or Silver/Giovanni transitions.
"""

import argparse
from dataclasses import dataclass
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

from tools.pru.convert_duo_entrances import EntranceAsset, convert_image


ROOT = Path(__file__).resolve().parents[2]
PORTRAITS = ROOT / "graphics/trainers/front_pics"


@dataclass(frozen=True)
class Pair:
    names: str
    portraits: tuple[str, str]
    colors: tuple[str, str]
    motif: str


PAIRS = {
    "brock_roxanne": Pair("BROCK & ROXANNE", ("leader_brock_hns.png", "leader_roxanne.png"), ("#b99254", "#809097"), "stone"),
    "misty_wallace": Pair("MISTY & WALLACE", ("leader_misty_hns.png", "champion_wallace.png"), ("#2d9eb7", "#67b9a9"), "water"),
    "surge_wattson": Pair("SURGE & WATTSON", ("leader_surge_hns.png", "leader_wattson.png"), ("#edc848", "#b78624"), "electric"),
    "erika_bugsy": Pair("ERIKA & BUGSY", ("leader_erika_hns.png", "leader_bugsy_hns.png"), ("#53a570", "#8eb94a"), "leaf"),
    "janine_koga": Pair("JANINE & KOGA", ("leader_janine_hns.png", "elite_four_koga_hns.png"), ("#8b55a4", "#b54b81"), "poison"),
    "sabrina_will": Pair("SABRINA & WILL", ("leader_sabrina_hns.png", "elite_four_will_hns.png"), ("#866ac8", "#5875c0"), "psychic"),
    "blaine_flannery": Pair("BLAINE & FLANNERY", ("leader_blaine_hns.png", "leader_flannery.png"), ("#ed7a36", "#c64744"), "fire"),
    "maxie_archie": Pair("MAXIE & ARCHIE", ("magma_leader_maxie.png", "aqua_leader_archie.png"), ("#bb4137", "#277ca9"), "magma"),
    "lorelei_glacia": Pair("LORELEI & GLACIA", ("elite_four_lorelei_frlg.png", "elite_four_glacia.png"), ("#a8dce6", "#5aa6cd"), "ice"),
    "bruno_chuck": Pair("BRUNO & CHUCK", ("elite_four_bruno_hns.png", "leader_chuck_hns.png"), ("#c78b47", "#bc5944"), "fighting"),
    "agatha_phoebe": Pair("AGATHA & PHOEBE", ("elite_four_agatha_frlg.png", "elite_four_phoebe.png"), ("#a36ac2", "#56a3a0"), "ghost"),
    "karen_sidney": Pair("KAREN & SIDNEY", ("elite_four_karen_hns.png", "elite_four_sidney.png"), ("#765c9f", "#46688e"), "dark"),
    "lance_drake": Pair("LANCE & DRAKE", ("champion_lance_hns.png", "elite_four_drake.png"), ("#4c80bb", "#b84d59"), "dragon"),
    "jasmine_clair": Pair("JASMINE & CLAIR", ("leader_jasmine_hns.png", "leader_clair_hns.png"), ("#b0bdc4", "#7765ab"), "steel"),
}


def _rgb(hex_color: str) -> tuple[int, int, int]:
    return tuple(bytes.fromhex(hex_color.removeprefix("#")))


def _dark(color: tuple[int, int, int], factor: float) -> tuple[int, int, int]:
    return tuple(int(x * factor) for x in color)


def _sprite(filename: str) -> Image.Image:
    with Image.open(PORTRAITS / filename) as image:
        image.load()
        # All GBA OBJ palettes reserve index 0 for transparency, regardless
        # of whether the original PNG happens to contain a tRNS chunk.
        if image.mode == "P":
            mask = Image.new("L", image.size)
            mask.putdata([0 if index == 0 else 255 for index in image.get_flattened_data()])
            result = image.convert("RGBA")
            result.putalpha(mask)
        else:
            result = image.convert("RGBA")
    return result


def _motif(draw: ImageDraw.ImageDraw, motif: str, left: tuple[int, int, int], right: tuple[int, int, int]) -> None:
    # Different silhouettes keep the fourteen entrances recognisable even
    # after GBA's severe 15-colour quantisation.
    if motif in {"stone", "steel"}:
        for x in (8, 28, 188, 208):
            draw.polygon([(x, 27), (x + 8, 15), (x + 17, 28), (x + 8, 41)], outline=left if x < 110 else right, width=2)
        if motif == "steel":
            for x in (15, 199):
                for y in (48, 74, 100):
                    draw.ellipse((x, y, x + 5, y + 5), fill="#d7d7df")
    elif motif == "water":
        for x in (14, 35, 169, 190):
            for y in (28, 57, 86):
                draw.arc((x, y, x + 30, y + 18), 5, 170, fill=left if x < 110 else right, width=3)
    elif motif == "electric":
        for x, color in ((12, left), (190, right)):
            draw.line([(x + 11, 18), (x, 52), (x + 15, 47), (x + 2, 83)], fill=color, width=4, joint="curve")
    elif motif in {"leaf", "poison"}:
        for x, color in ((20, left), (188, right)):
            for y in (23, 55, 87):
                if motif == "leaf":
                    draw.ellipse((x, y, x + 18, y + 10), outline=color, width=2)
                    draw.line([(x + 2, y + 8), (x + 16, y + 1)], fill=color, width=2)
                else:
                    draw.ellipse((x, y, x + 13, y + 13), outline=color, width=2)
    elif motif in {"psychic", "ghost", "dark"}:
        for radius in (18, 31, 44):
            draw.arc((112 - radius, 65 - radius, 112 + radius, 65 + radius), 20, 170, fill=left, width=2)
            draw.arc((112 - radius, 65 - radius, 112 + radius, 65 + radius), 200, 350, fill=right, width=2)
        if motif == "ghost":
            for x in (27, 191):
                draw.arc((x, 34, x + 22, 77), 45, 260, fill=left if x < 112 else right, width=3)
        if motif == "dark":
            draw.ellipse((95, 48, 129, 82), outline=left, width=3)
            draw.ellipse((103, 45, 135, 79), fill="#111a2a")
    elif motif in {"fire", "magma"}:
        for x, color in ((15, left), (185, right)):
            for y in (30, 68):
                draw.polygon([(x, y + 20), (x + 7, y), (x + 12, y + 12), (x + 20, y + 3), (x + 22, y + 20)], outline=color, width=2)
    elif motif == "ice":
        for x, color in ((24, left), (194, right)):
            for y in (32, 69):
                draw.line([(x - 10, y), (x + 10, y)], fill=color, width=2)
                draw.line([(x, y - 10), (x, y + 10)], fill=color, width=2)
                draw.line([(x - 7, y - 7), (x + 7, y + 7)], fill=color, width=1)
                draw.line([(x - 7, y + 7), (x + 7, y - 7)], fill=color, width=1)
    elif motif == "fighting":
        for x, color in ((10, left), (182, right)):
            draw.line([(x, 25), (x + 31, 88)], fill=color, width=5)
            draw.line([(x + 31, 25), (x, 88)], fill=color, width=5)
    elif motif == "dragon":
        for x, color in ((13, left), (174, right)):
            for y in (22, 44, 66, 88):
                draw.polygon([(x, y + 13), (x + 15, y), (x + 30, y + 13)], outline=color, width=2)


def render_banner(stem: str) -> Image.Image:
    spec = PAIRS[stem]
    left, right = map(_rgb, spec.colors)
    canvas = Image.new("RGBA", (224, 144), (11, 17, 30, 255))
    draw = ImageDraw.Draw(canvas)
    draw.polygon([(0, 0), (132, 0), (90, 144), (0, 144)], fill=_dark(left, 0.28))
    draw.polygon([(132, 0), (224, 0), (224, 144), (90, 144)], fill=_dark(right, 0.28))
    for x in range(-96, 300, 17):
        draw.line([(x, 0), (x + 70, 144)], fill=_dark(left if x < 106 else right, 0.43), width=3)
    draw.line([(111, 13), (111, 114)], fill=(236, 222, 178), width=2)
    draw.polygon([(112, 20), (133, 65), (112, 110), (91, 65)], outline=(231, 208, 148), width=3)
    _motif(draw, spec.motif, left, right)
    for side, filename in enumerate(spec.portraits):
        portrait = _sprite(filename)
        bbox = portrait.getbbox()
        if bbox is None:
            raise ValueError(f"Transparent trainer sprite: {filename}")
        portrait = portrait.crop(bbox)
        scale = min(103 / portrait.width, 107 / portrait.height)
        width, height = round(portrait.width * scale), round(portrait.height * scale)
        portrait = portrait.resize((width, height), Image.Resampling.NEAREST)
        x = (5 + (105 - width) // 2) if side == 0 else (115 + (104 - width) // 2)
        y = 115 - height
        shadow = Image.new("RGBA", portrait.size, (0, 0, 0, 0))
        shadow.putalpha(portrait.getchannel("A").point(lambda value: 135 if value else 0))
        canvas.alpha_composite(shadow, (x + 3, y + 3))
        canvas.alpha_composite(portrait, (x, y))
    draw = ImageDraw.Draw(canvas)
    draw.rectangle((0, 119, 223, 143), fill=(10, 14, 25), outline=(231, 208, 148), width=2)
    draw.line([(2, 121), (73, 121)], fill=left, width=2)
    draw.line([(151, 121), (221, 121)], fill=right, width=2)
    try:
        font = ImageFont.truetype("DejaVuSansMono-Bold.ttf", 14)
        small = ImageFont.truetype("DejaVuSansMono-Bold.ttf", 9)
    except OSError:
        font = ImageFont.load_default()
        small = font
    text_width = draw.textbbox((0, 0), spec.names, font=font)[2]
    draw.text(((224 - text_width) // 2 + 1, 122), spec.names, font=font, fill=(0, 0, 0))
    draw.text(((224 - text_width) // 2, 121), spec.names, font=font, fill=(255, 240, 197))
    top_label = "ELITE 20"
    draw.rectangle((82, 2, 141, 17), fill=(10, 14, 25), outline=(231, 208, 148))
    lw = draw.textbbox((0, 0), top_label, font=small)[2]
    draw.text(((224 - lw) // 2, 3), top_label, font=small, fill=(255, 240, 197))
    return canvas.convert("RGB")


def build_banner(stem: str) -> EntranceAsset:
    return convert_image(render_banner(stem), preserve_aspect=True)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("names", nargs="*", choices=sorted(PAIRS))
    parser.add_argument("--output", type=Path, default=ROOT / "graphics/battle_transitions/prl")
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    for stem in args.names or PAIRS:
        asset = build_banner(stem)
        for ext, payload in (("4bpp", asset.tiles), ("bin", asset.tilemap), ("gbapal", asset.palette)):
            (args.output / f"{stem}.{ext}").write_bytes(payload)
        asset.preview.save(args.output / f"{stem}_preview.png", optimize=True)
        print(f"{stem}: {asset.tile_count}/512 tiles")


if __name__ == "__main__":
    main()
