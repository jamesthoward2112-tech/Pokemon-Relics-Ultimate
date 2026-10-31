#!/usr/bin/env python3
"""Final user-approved PRU Relic colour treatment. Run after PRL sprite sync.

Pixel silhouettes are untouched. Each recolour changes JASC palette RGB rows,
which affect front/back uniformly. No runtime Mega/G-Max form switching.
"""
from pathlib import Path
import shutil
from PIL import Image

ROOT = Path("graphics/pokemon")
PRL = ROOT / "prl_authoritative"

def parse_pal(path):
    lines = path.read_text().strip().splitlines()
    assert lines[:2] == ["JASC-PAL", "0100"], (path, lines[:3])
    count = int(lines[2])
    colors = [tuple(int(n) for n in row.split()) for row in lines[3:]]
    assert len(colors) == count and count <= 16, (path, count, len(colors))
    return colors

def save_pal(path, colors):
    assert len(colors) <= 16 and all(len(c) == 3 and all(0 <= n <= 255 for n in c) for c in colors)
    path.write_text("JASC-PAL\n0100\n" + str(len(colors)) + "\n" +
                    "".join(f"{c[0]} {c[1]} {c[2]}\n" for c in colors))

def palette_replace(name, replacements):
    path = PRL / name / "normal.pal"
    colors = parse_pal(path)
    initial = colors[:]
    # Preserve index ordering and every single sprite pixel.
    for original, new in replacements.items():
        target = min(range(len(colors)), key=lambda i: sum((colors[i][j]-original[j])**2 for j in range(3)))
        error = sum((colors[target][j]-original[j])**2 for j in range(3))
        assert error < 1300, (name, original, colors[target], error)
        colors[target] = new
    save_pal(path, colors)
    assert colors != initial, name
    print("PRU artwork palette:", name, sum(x != y for x, y in zip(colors, initial)), "entries")

# Solaziken must remain red. ONLY the yellow/gold accent family becomes purple.
palette_replace("solaziken", {
    (248, 216, 128): (206, 143, 226),
    (224, 192, 104): (160, 101, 194),
    (245, 198, 36): (188, 78, 218),
    (224, 192, 104): (160, 101, 194),
})

# Owner-approved Sceptitan jade/gold preview.
palette_replace("sceptitan", {
    (65, 156, 65): (33, 173, 148),
    (24, 98, 41): (8, 90, 99),
    (41, 131, 49): (16, 132, 115),
    (24, 74, 41): (16, 66, 82),
    (131, 205, 106): (132, 222, 189),
    (174, 27, 24): (181, 123, 41),
    (221, 72, 55): (239, 181, 66),
    (215, 146, 55): (247, 222, 115),
    (91, 80, 10): (99, 82, 25),
})

# Owner-approved Faeranium amethyst/emerald preview; no sprite redraw.
palette_replace("faeranium", {
    (239, 207, 208): (222, 189, 239),
    (144, 168, 88): (90, 181, 156),
    (142, 45, 45): (90, 49, 148),
    (208, 240, 144): (173, 239, 197),
    (232, 84, 96): (173, 107, 230),
    (240, 148, 173): (206, 148, 247),
    (80, 96, 32): (25, 90, 82),
    (195, 70, 88): (132, 74, 181),
})

# Exact EXISTING G-Max Charizard 64x64 assets from PRU engine, as Charaxis.
# This replaces the previous Mega-based silhouette, NOT Charizard itself.
gmax = ROOT / "charizard" / "gmax"
charaxis = PRL / "charaxis"
for filename in ("front.png", "back.png", "icon.png", "normal.pal", "shiny.pal"):
    src = gmax / filename
    assert src.is_file(), src
    shutil.copyfile(src, charaxis / filename)
for filename in ("front.png", "back.png"):
    pic = Image.open(charaxis / filename)
    assert pic.size == (64, 64) and pic.mode == "P" and max(pic.getdata()) < 16, (filename, pic.size, pic.mode)
palette_replace("charaxis", {
    (132, 49, 25): (51, 36, 56),
    (239, 132, 41): (91, 65, 84),
    (206, 82, 66): (113, 53, 88),
    (255, 214, 16): (255, 205, 73),
    (247, 165, 16): (247, 169, 47),
    (255, 66, 0): (250, 94, 30),
})
print("PRU art lock: Charaxis=GMax; Solaziken red/purple; Sceptitan jade; Faeranium amethyst; Pyroclast/Feralodon UNTOUCHED")
