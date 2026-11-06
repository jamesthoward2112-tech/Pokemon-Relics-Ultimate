"""Job 16 source regression: Golden Ho-Oh is a visual teaser, not an early catch."""
from pathlib import Path
credits = Path("src/credits_hns.c").read_text(encoding="utf-8")
event = Path("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc").read_text(encoding="utf-8")
league = Path("data/maps/PokemonLeague_HallOfFame_hns/scripts.inc").read_text(encoding="utf-8")
summit = Path("data/maps/MtSilver_SummitDay_hns/scripts.inc").read_text(encoding="utf-8")

game_clear = Path("src/post_battle_event_funcs.c").read_text(encoding="utf-8")
assert "gPruElite20CreditsActive = FlagGet(FLAG_PRU_E20_CREDITS_PENDING);" in game_clear
assert "FlagClear(FLAG_PRU_E20_CREDITS_PENDING);" in game_clear
assert "gPruElite20CreditsActive = FlagGet(FLAG_PRU_E20_CREDITS_PENDING);" not in credits
assert "if (gPruElite20CreditsActive)" in credits
assert "if (page == E20_INTRO_PAGE_COUNT)" in credits
assert "CreateCreditsRelicHoOhSprite" in credits
assert "sElite20CreditsIntroPages" in credits
assert "sPruElite20OpeningSpecies" in credits
for species in ("RAIKOU","ENTEI","LUGIA","UNOWN_I","CELEBI","SUICUNE","ALPHORACLE","RELIC_HO_OH"):
    assert "SPECIES_" + species in credits
start = summit.index("MtSilver_SummitDay_EventScript_OakRelicCaught::")
end = summit.index("MtSilver_SummitDay_EventScript_OakEpilogue::", start)
finale = summit[start:end]
assert "setflag FLAG_PRU_E20_CREDITS_PENDING" in finale
assert "setflag FLAG_PRU_GOLDEN_FINALE_SHOWN" in finale
assert finale.index("setflag FLAG_PRU_E20_CREDITS_PENDING") < finale.index("special GameClear")
assert finale.count("special GameClear") == 1
assert "PRU_Elite20_StartFinale::\n\treturn" in event
assert "PRU_Elite20_CinematicPrelude" not in event
assert "PRU_Elite20_Text_GoldenSky:" in event
assert "PRU_Elite20_ClaimRewards::" in event
assert "giveitem ITEM_MASTER_BALL, 6" in event
assert "giveitem ITEM_ANCIENT_STONE, 5" in event
assert "seteventmon SPECIES_RELIC_HO_OH, 100" in summit
assert "CB2_StartCreditsSequence" not in league
print("PASS Job16: E20-only Ho-Oh flight, RELICS montage and preserved rewards/encounter")
