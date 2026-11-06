# PRU Job 17 — Official credits and attribution

Built on the verified Job 16 source commit `eaf0f8c6b93159077f0e719666e2650cafab5bcb`. **Job 17 is E20-only**: the standard first Johto and second Kanto League continue using their original Heart & Soul/Emerald-compatible credit table, with no changes to their own endings or existing save flags.

## Implemented

- The four approved Elite 20/Golden Ho-Oh cinematic introduction pages remain unchanged.
- Exactly **16 new PRU-specific credit pages** follow the intro, using the original in-game page timing, fade transitions, font and 240-pixel layout; the same Golden Ho-Oh -> RELICS sprite montage continues behind them.
- Explicitly credited: creator **James Howard**; `pokeemerald-expansion`; Pokémon Heart & Soul, Lil Dill and HnS contributors; prior PRL/PJR work; approved donor artwork from Pokémon Infinity, Insurgence and Elite Redux; Pokésprite and PoryPal; Radical Red references; ChatGPT, Claude, Gemini; GitHub and mGBA; community testers; original Pokémon rights holders.
- No new save flags, encounter scripts, Pokédex entries, trainer/monster assets, catches, move effects, map edits or rewards.
- The original full upstream credits remain in `src/data/credits_hns.h` and are still shown during non-E20 credits. Keep that file untouched so individual upstream contributor names are not removed from source or normal credits.

## Attribution and licence follow-up

The PRU pages are a concise acknowledgement, not a substitute for the underlying projects' full legal notices or artist lists. Before the first public v1.0 release, reconcile each imported graphic/music/code source and any required licences/author permissions in the release package. Do **not** assume these upstream projects have uniform redistribution terms. Avoid asserting individual sprite authors where the donor manifest does not independently identify them.

Relevant source records: `README.md`, `docs/PRU_MASTER_PLAN.md`, `docs/PRL_DUO_TRANSITION_ASSET_PROVENANCE.md`, `docs/PRU_RHYTHM_BG_ASSET_PROVENANCE.md`, and the original `src/data/credits_hns.h`.

## Quality gates

`python3 test/test_pru_job16_cinematic.py` must still pass together with `python3 test/test_pru_job17_custom_credits.py`, the existing source/legendary/battle engine regression suite, a clean 32 MiB `make hns` build and mGBA boot. The E20 sequence must then be watched in gameplay to check text clipping, time per page, transitions, Ho-Oh appearance and the final Champion screen.

Job 17 has **not** reimplemented credits globally, nor changed the already accepted Job 16 cinematic.
