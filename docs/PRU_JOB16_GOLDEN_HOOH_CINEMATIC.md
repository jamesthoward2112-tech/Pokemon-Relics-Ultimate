# PRU Job 16 — Golden Ho-Oh Elite 20 ending cinematic

Base: Job 15 approved 450-Dex sprite/palette commit `77f9bf0b4fb592c591c5048da66b369b52e9b9fe`. This job does not merge rejected Job 10 artwork or change game progression, catchable Ho-Oh, reward totals, NPCs, source IDs, maps or save layout.

The existing E20 steward already launches `special GameClear` and defines independent `FLAG_PRU_E20_CREDITS_PENDING` and `FLAG_PRU_E20_CREDITS_SHOWN`. Previous credits code declared `gPruElite20CreditsActive` but never initialised it from the pending event flag, so the Ho-Oh flyover and E20 intro pages were unreachable.

Job 16 binds the credits mode to the saved E20 flag, adds a Golden Ho-Oh battle-sprite preview and cry before the game-clear handoff, expands the E20-only introduction, and puts the six R-E-L-I-C-S captures, Alphoracle and Golden Ho-Oh at the front of the existing curated credits sprite montage. The Ho-Oh preview is **cinematic only**. It neither awards nor spawns another Pokémon.

QA: source regression `python3 test/test_pru_job16_cinematic.py`, full existing checks, clean HNS compile, 32 MiB ROM/header validation and mGBA boot via the canonical PRU GitHub Actions workflow. Runtime visual acceptance still requires checking the actual E20 replay from a post-E20 save.

Job 17 will replace the inherited Heart & Soul scrolling names with official PRU creator, donor and tool acknowledgements separately.
