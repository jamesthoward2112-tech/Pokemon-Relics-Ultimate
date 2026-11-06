# PRU Job 16 — Golden Ho-Oh Elite 20 ending cinematic

Base: Job 15 approved 450-Dex sprite/palette commit `77f9bf0b4fb592c591c5048da66b369b52e9b9fe`. This job does not merge rejected Job 10 artwork or change game progression, catchable Ho-Oh, reward totals, NPCs, source IDs, maps or save layout.

The existing E20 steward already launches `special GameClear` and defines independent `FLAG_PRU_E20_CREDITS_PENDING` and `FLAG_PRU_E20_CREDITS_SHOWN`. The original GameClear function already consumes `FLAG_PRU_E20_CREDITS_PENDING` and sets `gPruElite20CreditsActive`; this runtime state must remain unchanged when credits initialise. The new code uses it to drive the additional intro and flyby.

Job 16 preserves the mode already transferred by GameClear, adds Golden Ho-Oh story dialogue at the Dojo (without any scripted legendary sprite or encounter), expands the E20-only introduction, and puts the six R-E-L-I-C-S captures, Alphoracle and Golden Ho-Oh at the front of the existing curated credits sprite montage. The E20 credits renderer handles Ho-Oh's actual animated flight; the Dojo adds dialogue only. The flight is **cinematic only**. It neither awards nor spawns another Pokémon.

QA: source regression `python3 test/test_pru_job16_cinematic.py`, full existing checks, clean HNS compile, 32 MiB ROM/header validation and mGBA boot via the canonical PRU GitHub Actions workflow. Runtime visual acceptance still requires checking the actual E20 replay from a post-E20 save.

Job 17 will replace the inherited Heart & Soul scrolling names with official PRU creator, donor and tool acknowledgements separately.
