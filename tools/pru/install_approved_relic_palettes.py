#!/usr/bin/env python3
"""Apply the PRU owner-approved Relic starter palettes after pinned PRL sync.

Only Solaziken's YELLOW accents, Sceptitan and Faeranium are recoloured.
Pyroclast, Feralodon, Swamplith, Noxichu and Edensaur remain unchanged.
Charaxis is handled separately by install_charaxis_gmax_relic.py.
"""
from pathlib import Path

ROOT = Path("graphics/pokemon")
PRL = ROOT / "prl_authoritative"

def read_pal(path):
    lines = path.read_text().splitlines()
    assert lines[:2] == ["JASC-PAL", "0100"], path
    n = int(lines[2])
    vals = [tuple(map(int, line.split())) for line in lines[3:3+n]]
    assert len(vals) == n and n <= 16, path
    return vals

def write_pal(path, vals):
    assert 0 < len(vals) <= 16
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("JASC-PAL\n0100\n"+str(len(vals))+"\n"+
                    "\n".join(" ".join(map(str,rgb)) for rgb in vals)+"\n")

def patch(path, changes):
    vals=read_pal(path)
    for i, (old, new) in changes.items():
        assert vals[i] == old, (path, i, vals[i], old)
        vals[i] = new
    write_pal(path, vals)

# Solaziken: change gold/yellow areas to violet only. Fire/red body untouched.
patch(PRL/"solaziken"/"normal.pal", {
    2: ((248,216,128), (216,176,235)),
    3: ((224,192,104), (167,119,205)),
    4: ((245,198,36),  (166,91,215)),
    8: ((185,144,37),  (100,48,146)),
})

# Sceptitan: distinctly ancient jade + gold, preserving the donor Mega pose.
patch(PRL/"sceptitan"/"normal.pal", {
    3: ((131,205,106), (132,222,189)),
    4: ((215,146,55),  (247,222,115)),
    6: ((65,156,65),   (33,173,148)),
    8: ((41,131,49),   (16,132,115)),
    9: ((221,72,55),   (239,181,66)),
   10: ((174,27,24),   (181,123,41)),
   12: ((91,80,10),    (99,82,25)),
   13: ((24,98,41),    (8,90,99)),
   14: ((24,74,41),    (16,66,82)),
})

# Faeranium uses Mega Meganium frames globally, but only the unique FAERANIUM
# species receives this palette: do NOT recolour ordinary Mega Meganium.
mega = ROOT/"meganium"/"mega"
dest = ROOT/"pjr_locked"/"faeranium"
dest.mkdir(parents=True, exist_ok=True)
normal=read_pal(mega/"normal.pal")
for i, new in {
    1: (25,132,115), 2: (25,90,82), 3: (90,49,148),
    4: (132,74,181), 5: (156,99,206), 6: (173,107,230),
    9: (90,181,156), 10: (173,140,206), 11: (206,148,247),
    13: (173,239,197), 14: (222,189,239)
}.items():
    normal[i]=new
write_pal(dest/"normal.pal",normal)
write_pal(dest/"shiny.pal",read_pal(mega/"shiny.pal"))

header=Path("src/data/graphics/pjr.h")
code=header.read_text()
for suffix in ("normal", "shiny"):
    orig=f'graphics/pokemon/meganium/mega/{suffix}.gbapal'
    replacement=f'graphics/pokemon/pjr_locked/faeranium/{suffix}.gbapal'
    if suffix == "normal":
        marker="const u16 gMonPalette_Faeranium[]"
    else:
        marker="const u16 gMonShinyPalette_Faeranium[]"
    lines=code.splitlines(keepends=True)
    hits=[i for i,l in enumerate(lines) if marker in l]
    assert len(hits)==1,marker
    i=hits[0]
    assert orig in lines[i],(marker,lines[i])
    lines[i]=lines[i].replace(orig,replacement)
    code="".join(lines)
header.write_text(code)
print("PRU approved palettes installed: red/purple Solaziken, jade Sceptitan, amethyst Faeranium")
