"""Job 16 source regression: Golden Ho-Oh is a visual teaser, not an early catch."""
from pathlib import Path
credits = Path("src/credits_hns.c").read_text(encoding="utf-8")
event = Path("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc").read_text(encoding="utf-8")
league = Path("data/maps/PokemonLeague_HallOfFame_hns/scripts.inc").read_text(encoding="utf-8")
summit = Path("data/maps/MtSilver_SummitDay_hns/scripts.inc").read_text(encoding="utf-8")

assert "gPruElite20CreditsActive = FlagGet(FLAG_PRU_E20_CREDITS_PENDING);" in credits
assert "if (gPruElite20CreditsActive)" in credits
assert "if (page == E20_INTRO_PAGE_COUNT)" in credits
assert "CreateCreditsRelicHoOhSprite" in credits
assert "sElite20CreditsIntroPages" in credits
assert "sPruElite20OpeningSpecies" in credits
for species in ("RAIKOU","ENTEI","LUGIA","UNOWN_I","CELEBI","SUICUNE","ALPHORACLE","RELIC_HO_OH"):
    assert "SPECIES_" + species in credits
start = event.index("PRU_Elite20_StartFinale::")
end = event.index("PRU_Elite20_StartFinale_Return::", start)
finale = event[start:end]
assert finale.count("call PRU_Elite20_CinematicPrelude") == 1
assert finale.index("call PRU_Elite20_CinematicPrelude") < finale.index("special GameClear")
assert finale.count("setflag FLAG_PRU_E20_CREDITS_PENDING") == 1
assert finale.count("setflag FLAG_PRU_E20_CREDITS_SHOWN") == 1
prelude = event.split("PRU_Elite20_CinematicPrelude::",1)[1].split("PRU_Elite20_Text_CinematicPrelude:",1)[0]
assert "showmonpic SPECIES_RELIC_HO_OH" in prelude
assert "playmoncry SPECIES_RELIC_HO_OH" in prelude
assert "hidemonpic" in prelude
assert "seteventmon" not in prelude
assert "givepokemon" not in prelude
assert "FLAG_PJR_RELIC_HO_OH" not in prelude
assert "PRU_Elite20_ClaimRewards::" in event
assert "giveitem ITEM_MASTER_BALL, 6" in event
assert "giveitem ITEM_ANCIENT_STONE, 5" in event
assert "seteventmon SPECIES_RELIC_HO_OH, 100" in summit
assert "CB2_StartCreditsSequence" not in league
print("PASS Job16: E20-only Ho-Oh flight, RELICS montage and preserved rewards/encounter")
