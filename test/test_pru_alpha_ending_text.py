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

# The existing flying animation is intentionally unchanged until resource review.
assert 'gMonFrontPic_HoOhRelic' in art
assert 'sAnim_CreditsRelicHoOh[] = { ANIMCMD_FRAME(0, 24)' in art
assert "CreateCreditsRelicHoOhSprite(DISPLAY_WIDTH + 32, 46)" in credits
assert "seteventmon SPECIES_RELIC_HO_OH, 100" in mt_silver
assert "FLAG_PRU_E20_CREDITS_PENDING" in mt_silver

print("PASS: four revised final intro pages, 19 complete credit pages, dual-form Golden Ho-Oh lore")
print("PASS: ending graphics unchanged awaiting dedicated flying asset; encounters/flags untouched")
