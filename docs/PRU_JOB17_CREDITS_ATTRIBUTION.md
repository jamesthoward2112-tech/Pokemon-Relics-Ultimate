# PRU Job 17 — Official credits and attribution

Built on the verified Job 16 source commit `eaf0f8c6b93159077f0e719666e2650cafab5bcb`. **Job 17 is E20-only**: the standard first Johto and second Kanto League continue using their original Heart & Soul/Emerald-compatible credit table, with no changes to their own endings or existing save flags.

## Implemented

- The four approved Elite 20/Golden Ho-Oh cinematic introduction pages remain unchanged.
- Exactly **19 new PRU-specific credit pages** follow the intro, using the original in-game page timing, fade transitions, font and 240-pixel layout; the same Golden Ho-Oh -> RELICS sprite montage continues behind them.
- Explicitly credited: creator **balesleftpeg**; `pokeemerald-expansion`; Pokémon Heart & Soul, Lil Dill and HnS contributors; prior PRL/PJR work; approved donor artwork from Pokémon Infinity, Insurgence and Elite Redux; Pokésprite and PoryPal; Radical Red references; ChatGPT, Claude, Gemini; GitHub and mGBA; community testers; original Pokémon rights holders.
- No new save flags, encounter scripts, Pokédex entries, trainer/monster assets, catches, move effects, map edits or rewards.
- The original full upstream credits remain in `src/data/credits_hns.h` and are still shown during non-E20 credits. Keep that file untouched so individual upstream contributor names are not removed from source or normal credits.


## Complete documented donor/game credit list (source checked 6 Nov 2026)

**Creator:** `balesleftpeg`. Never use the owner's private personal name in PRU in-game credits.

**Earlier Relic-series sprite banks:** Pokémon Relic Legacy (PRL), Pokémon Johto Relics (PJR), Pokémon Kanto Relics (PKR), Pokémon Hoenn Relics (PHR).

**External ROM/artwork projects represented in PRU source and its approved sprite manifests:** Pokémon Infinity (Eevee evolutions and custom species), Pokémon Insurgence (Mega Heracross/Miltank/Jirachi and related art), Pokémon Elite Redux (multiple Relic forms), Pokémon Xenoverse (Relic creature donor bank in PRL lineage), Pokémon Shining Victory (Wyveon/Drakeon), Pokémon Odyssey II (approved Registeel and other artwork), Pokémon Tourmaline (Skarby -> Skarmet), Pokémon AlteRed (the unique Mewduo/Mewsion visual), and the approved **TRE 2026 sprite bank** (not expanded to an unverified project title).

**Other borrowed visual assets:** Pokémon Rhythm (static 240x160 battle background artwork), Pokémon Hoenn's Last Wish (intro animation background/scene assets), Pokésprite (party icon artwork) and PoryPal (conversion/palette tools). **Pokémon Radical Red** is acknowledged under gameplay/moves references, not falsely presented as a verified sprite donor. The prior Heart & Soul Johto base and pokeemerald-expansion are credited separately as engine foundations.

These names are grounded in the PRL Custom Sprite Port Manifest, PRU canonical Pokémon data, the current CI build's donor art installers, and `docs/PRU_RHYTHM_BG_ASSET_PROVENANCE.md`. Excluded: rejected/retired visual assets (e.g. Crystal Advance Redux battle backgrounds); do not credit them as currently used source art without a matching live source. This is a project-level acknowledgement; final v1.0 packaging must still verify artist-by-artist licensing.

## Attribution and licence follow-up

The PRU pages are a concise acknowledgement, not a substitute for the underlying projects' full legal notices or artist lists. Before the first public v1.0 release, reconcile each imported graphic/music/code source and any required licences/author permissions in the release package. Do **not** assume these upstream projects have uniform redistribution terms. Avoid asserting individual sprite authors where the donor manifest does not independently identify them.

Relevant source records: `README.md`, `docs/PRU_MASTER_PLAN.md`, `docs/PRL_DUO_TRANSITION_ASSET_PROVENANCE.md`, `docs/PRU_RHYTHM_BG_ASSET_PROVENANCE.md`, and the original `src/data/credits_hns.h`.

## Quality gates

`python3 test/test_pru_job16_cinematic.py` must still pass together with `python3 test/test_pru_job17_custom_credits.py`, the existing source/legendary/battle engine regression suite, a clean 32 MiB `make hns` build and mGBA boot. The E20 sequence must then be watched in gameplay to check text clipping, time per page, transitions, Ho-Oh appearance and the final Champion screen.

Job 17 has **not** reimplemented credits globally, nor changed the already accepted Job 16 cinematic.
