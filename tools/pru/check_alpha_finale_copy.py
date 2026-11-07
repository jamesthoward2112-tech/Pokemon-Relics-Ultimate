#!/usr/bin/env python3
"""PRU alpha finale copy regression checks.

Run from PRU checkout: python3 tools/pru/check_alpha_finale_copy.py
Only final E20 credits and the two Ho-Oh Pokédex descriptions are in scope.
No changes to first-clear credits, sprite assets, or Golden Ho-Oh battle logic.
"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
credits = (ROOT / "src/credits_hns.c").read_text(encoding="utf-8")
pages = (ROOT / "src/data/credits_pru.h").read_text(encoding="utf-8")
dex = (ROOT / "src/data/pokemon/species_info/gen_2_families.h").read_text(encoding="utf-8")
relic = (ROOT / "src/data/pokemon/species_info/pjr_families.h").read_text(encoding="utf-8")
flyby = (ROOT / "src/intro_credits_graphics.c").read_text(encoding="utf-8")

required = {
    "SEVEN RELICS UNITED": credits,
    "GOLDEN HO-OH TAKES FLIGHT": credits,
    "AT THE MT SILVER SUMMIT": credits,
    "PROF OAK KEEPS HIS PROMISE": credits,
    "THE ULTIMATE RELIC ANSWERS": credits,
    "AN ANCIENT LEGEND REBORN": credits,
    "SEVEN RELICS REUNITED": pages,
    "GOLDEN HO-OH HAS ANSWERED": pages,
    "YOUR LEGEND LIVES ON": pages,
    "THANK YOU FOR PLAYING": pages,
}
for expected, source in required.items():
    assert expected in source, f"Missing finale text: {expected}"

for old in ("THE SIX RELICS STIR", "THE SIX RELICS AWAKEN",
            "ALPHORACLE AWAITS", "GOLDEN HO-OH AWAITS"):
    assert old not in credits + pages, f"Outdated ending copy: {old}"

# The original four intro pages and 19 custom-credits pages must remain.
intro = credits.split("sElite20CreditsIntroPages[][ENTRIES_PER_PAGE] = {",1)[1].split("};",1)[0]
assert len(re.findall(r"^\s*\{ &sE20",intro,re.M)) == 4
custom = pages.split("sPruE20CreditsPages[][ENTRIES_PER_PAGE] =",1)[1].split("};",1)[0]
assert len(re.findall(r"^\s*\{ &sPruCreditEntry",custom,re.M)) == 19

# Preserve actual artwork and HnS/fan contributions in the credits.
for required_artist in ("balesleftpeg", "POKEEMERALD-EXPANSION",
                        "POKEMON HEART & SOUL", "POKEMON INFINITY",
                        "POKEMON ELITE REDUX", "GAME FREAK",
                        "NINTENDO", "CREATURES INC."):
    assert required_artist in pages, f"Attribution lost: {required_artist}"

for file_content, var_prefix in ((credits,"sPRUE20Text_"), (pages,"sPruCreditText_")):
    for name, content in re.findall(
            r"static const u8 ("+var_prefix+r"[A-Za-z0-9_]+)\[\] = _\(\"([^\"]+)\"\);",
            file_content):
        # Practical 240px screen safety for mostly uppercase default-font lines.
        assert len(content) <= 29, (name,len(content),content)

expected_lines = [
    "An ancient golden Ho-Oh that answers",
    "only a Trainer proven worthy by the",
    "seven RELICS. Its radiant wings are",
    "said to herald rebirth and new hope.",
]
for species, source, marker in (
    ("Ho-Oh", dex, "[SPECIES_HO_OH] ="),
    ("Relic Ho-Oh", relic, "[SPECIES_RELIC_HO_OH] =")):
    tail = source.split(marker,1)[1]
    assert "gMonFrontPic_HoOhRelic" in tail[:4000]
    assert "gMonBackPic_HoOhRelic" in tail[:4000]
    body = tail.split(".description = COMPOUND_STRING(",1)[1].split("),",1)[0]
    lines = re.findall(r'\"([^\"]*)\"',body)
    assert len(lines)==4,(species,lines)
    decoded=[]
    for index,line in enumerate(lines):
        if index<3:
            assert line.endswith(r"\n") and not line.endswith(r"\\n"), (species,index,line)
            line=line[:-2]
        decoded.append(line)
    assert decoded==expected_lines, (species, decoded)
    assert all(len(line)<=38 for line in decoded)
assert '.categoryName = _("Golden")' in dex.split("[SPECIES_HO_OH] =",1)[1][:2500]

# The temporary artwork placeholder remains untouched for the user's approved
# 64x64, four-frame flying Ho-Oh sprite job. Do not substitute a front battle pic.
assert "ANIMCMD_FRAME(0, 24), ANIMCMD_JUMP(0)" in flyby
assert "gMonFrontPic_HoOhRelic" in flyby
assert "CreateCreditsRelicHoOhSprite" in credits
print("PASS: all 23 E20 finale pages audited, old six-RELICS text removed, attribution preserved")
print("PASS: canonical golden Ho-Oh category and four-line bio on both species variants")
print("PENDING: replacement Golden Ho-Oh flying artwork and full emulator visual verification")
