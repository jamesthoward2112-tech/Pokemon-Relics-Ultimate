"""Pre-flight regression for PRU's final Golden Ho-Oh ending text.

This deliberately does not change Ho-Oh artwork, animation, encounter flags,
credits sequence timing, original League credits or save layout.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[1]
credits = (root / "src/credits_hns.c").read_text(encoding="utf-8")
pages = (root / "src/data/credits_pru.h").read_text(encoding="utf-8")
hgss = (root / "src/data/credits_hns.h").read_text(encoding="utf-8")
hooh = (root / "src/data/pokemon/species_info/gen_2_families.h").read_text(encoding="utf-8")
golden = (root / "src/data/pokemon/species_info/pjr_families.h").read_text(encoding="utf-8")
art = (root / "src/intro_credits_graphics.c").read_text(encoding="utf-8")
mt_silver = (root / "data/maps/MtSilver_SummitDay_hns/scripts.inc").read_text(encoding="utf-8")

# Credits are post-capture, not a teaser for a quest still to complete.
retired = ("THE SIX RELICS STIR", "THE SIX RELICS AWAKEN",
           "ALPHORACLE AWAITS", "GOLDEN HO-OH AWAITS",
           "YOUR JOURNEY CONTINUES", "RAIKOU / ENTEI / LUGIA",
           "I-UNOWN / CELEBI / SUICUNE")
for word in retired:
    assert word not in credits and word not in pages, f"Outdated final credits text: {word}"
for word in ("GOLDEN HO-OH RISES", "OAK AT MT SILVER",
             "THE FINAL SUMMONING", "THE JOURNEY IS COMPLETE"):
    assert word in credits, f"Missing revised cinematic page: {word}"
for word in ("THE GOLDEN FLAME ENDURES", "MT SILVER REMEMBERS",
             "YOUR LEGEND LIVES ON", "THANK YOU FOR PLAYING"):
    assert word in pages, f"Missing post-finale page: {word}"

intro = credits.split("static const struct CreditsEntry *const sElite20CreditsIntroPages", 1)[1].split("};", 1)[0]
assert intro.count(" { &sE20") == 4, "The four final intro pages must be preserved"
assert len(re.findall(r'^    \{ &sPruCreditEntry_', pages, re.M)) == 19, "All 19 attribution pages must remain"
assert 'sCreditsEntryPointerTable[PAGE_COUNT][ENTRIES_PER_PAGE]' in hgss, "Original League credits missing"
assert "sPruE20CreditsPages[gTasks[taskId].tCurrentPage - E20_INTRO_PAGE_COUNT][i]" in credits
assert 'sCreditsEntryPointerTable[gTasks[taskId].tCurrentPage][i]' in credits
for title in re.findall(r'sPRUE20Text_\w+\[\] = _\("([^"]+)"\)', credits):
    assert len(title) <= 27, f"GBA cinematic line exceeds safe width: {title}"
for line in re.findall(r'sPruCreditText_\d+_\d+\[\] = _\("([^"]+)"\)', pages):
    assert len(line) <= 27, f"GBA credits line exceeds safe width: {line}"
for name in ("balesleftpeg", "POKEMON INFINITY", "POKEMON INSURGENCE",
             "POKEMON ELITE REDUX", "POKEMON HEART & SOUL", "POKESPRITE",
             "CLAUDE", "GEMINI", "CHATGPT"):
    assert name in pages, f"Attribution must be preserved: {name}"

bio_pat = re.compile(r'\.description\s*=\s*COMPOUND_STRING\(\s*((?:"(?:[^"\\]|\\.)*"\s*)+)\)')
def gold_bio(species_source: str, species_decl: str):
    assert species_source.count(species_decl) == 1, "Missing/duplicated Ho-Oh declaration"
    body = species_source.split(species_decl, 1)[1].split(".pokemonScale", 1)[0]
    assert '.categoryName = _("Relic")' in body
    hit = bio_pat.search(body)
    assert hit, "Missing Golden Ho-Oh description"
    raw = hit.group(1)
    lines = re.findall(r'"((?:[^"\\]|\\.)*)"', raw)
    assert len(lines) == 4, ("Expected four screen-safe Dex lines", lines)
    for text in lines:
        visible = text.replace(r"\n", "")
        assert len(visible) <= 39, ("Dex bio too long", visible)
    return lines

normal_bio = gold_bio(hooh, "[SPECIES_HO_OH] =")
relic_bio = gold_bio(golden, "[SPECIES_RELIC_HO_OH] =")
assert normal_bio == relic_bio, "Ho-Oh summary and Relic form must use the same lore"
assert "Professor Oak" in "".join(normal_bio) and "Mt. Silver" in "".join(normal_bio)
assert "rainbow" not in "".join(normal_bio).lower()

# Dedicated leftward flyby uses a three-pose 64x64 4bpp GBA sheet, not
# the static Ho-Oh battle sprite. 64 OBJ tiles per pose, animated 0-64-128-64.
assert 'gMonFrontPic_HoOhRelic' not in art, "Credits still reference static battle Ho-Oh"
assert 'relic_ho_oh_flight.4bpp.smol' in art
assert 'relic_ho_oh_flight.gbapal' in art
assert '.size = 0x1800, .tag = TAG_RELIC_HO_OH' in art
anim = art.split("static const union AnimCmd sAnim_CreditsRelicHoOh[]", 1)[1].split("};", 1)[0]
assert [int(i) for i in re.findall(r"ANIMCMD_FRAME\((\d+),", anim)] == [0, 64, 128, 64]
assert "ANIMCMD_JUMP(0)" in anim
assert "CreateCreditsRelicHoOhSprite(DISPLAY_WIDTH + 32, 46)" in credits
assert "sprite->x -= 2;" in credits, "Preserve credits-only leftward flight"
assert "seteventmon SPECIES_RELIC_HO_OH, 100" in mt_silver
assert "FLAG_PRU_E20_CREDITS_PENDING" in mt_silver

# Validate the source PNG without requiring an imaging library in CI. The
# converter creates a 3 x 0x800-byte sprite sheet from this 64x192 source.
import struct
import zlib

flight = (root / "graphics/intro/scene_2/relic_ho_oh_flight.png").read_bytes()
assert flight.startswith(b"\x89PNG\r\n\x1a\n")
width, height, depth, mode = struct.unpack(">IIBB", flight[16:26])
assert (width, height, depth, mode) == (64, 192, 8, 3)
pos = 8
palette_size = None
compressed = b""
while pos < len(flight):
    size = struct.unpack_from(">I", flight, pos)[0]
    kind = flight[pos + 4:pos + 8]
    chunk = flight[pos + 8:pos + 8 + size]
    if kind == b"PLTE":
        palette_size = len(chunk) // 3
    if kind == b"IDAT":
        compressed += chunk
    pos += size + 12
assert palette_size == 16, f"4bpp flight must have exactly 16 palette entries, got {palette_size}"
raw = zlib.decompress(compressed)
assert len(raw) == height * (width + 1)
rows = []
last = bytearray(width)
for y in range(height):
    rowstart = y * (width + 1)
    filt = raw[rowstart]
    src = raw[rowstart + 1:rowstart + width + 1]
    assert filt in range(5)
    out = bytearray(width)
    for x, v in enumerate(src):
        left = out[x-1] if x else 0
        up = last[x]
        above_left = last[x-1] if x else 0
        if filt == 0: delta = 0
        elif filt == 1: delta = left
        elif filt == 2: delta = up
        elif filt == 3: delta = (left + up) // 2
        else:
            prediction = left + up - above_left
            distances = (abs(prediction-left), abs(prediction-up), abs(prediction-above_left))
            delta = (left,up,above_left)[distances.index(min(distances))]
        out[x] = (v + delta) & 255
    rows.append(bytes(out))
    last = out
frames = [b"".join(rows[i*64:(i+1)*64]) for i in range(3)]
assert all(max(frame) < 16 and frame.count(0) > 0 and frame.count(0) < 3750 for frame in frames)
assert len(set(frames)) == 3, "Flying frames must be different poses"

print("PASS: four revised final intro pages, 19 complete credit pages, dual-form Golden Ho-Oh lore")
print("PASS: three distinct GBA flight poses, 16-color indexed sheet, 0-64-128-64 animation, credits flyby preserved")
