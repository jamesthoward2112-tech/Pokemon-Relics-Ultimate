# PRU Job 18 implementation brief

## Goal
Ship the approved endgame story and unique Ancient Guardian Dragonite as a playable Job 18 ROM, with a separate clean pre-ceremony save.

## Binding requirements
- Professor Oak remains the Elite 20 final opponent; he reveals an unnamed Ultimate Ancient Relic without a location, and never fights at Mt Silver.
- The Alph Lab scientist gates Mt Silver summit directions on Oak's Elite 20 completion and all seven RELICS, with repeat-safe recognition for existing saves.
- Mt Silver summit Oak is a story character, not a trainer battle. He summons the single level-100 catchable Golden Ho-Oh only after those same gates; defeated/escaped Ho-Oh retries safely.
- Capture begins the existing Job 16 Ho-Oh opening and Job 17 custom credits, with six Master Balls granted once and a persistent completion flag.
- Tin Tower Kimono Girls summon a unique, non-catchable level-60 boss using only the attached Elite Redux Mega Dragonite front/back/icon artwork. No Mega mechanic or new Pokédex entry; do not alter Lance's Dragonite Relic.
- Guardian Dragonite: Dragon/Flying, Multiscale, Weakness Policy, Adamant, 31 IVs, 252 HP / 252 Attack / 4 Speed, Dragon Dance, Dual Wingbeat, Dragon Claw, Roost; no Earthquake.
- Do not require or add Ancient Guardian Wing or Ancient Rainbow Wing. Preserve saves, six Master Ball reward count, existing progression, and all prior Job 17 fixes.
- Changelog, commit, test release, test save, ROM size/hash, and exact test evidence must be reported; no unverified emulator or release claims.

## Architecture calls
- Extend existing flags and event scripts where possible to preserve older saves and all existing E20 content.
- Use a trainer-only internal Dragonite form for the dedicated boss so its art is not assigned globally and no Pokédex entry is introduced.
- Keep the user-approved three sprite PNGs byte-identical as source art; convert only when the existing GBA asset pipeline requires it.
- Reuse existing cinematic and credits routines; trigger them from Golden Ho-Oh capture exactly once.

## Non-goals
- No new Ho-Oh encounter at Tin Tower, no second Oak battle, no Mega Evolution, no unrelated gameplay changes, and no modification of user or playtester saves.

## Validation
Run focused source regressions, build and verify a 32 MiB ROM, exercise battle tests and save-state checks, and run mGBA only when a reproducible save/automation path is available. Release only the resulting ROM and the standalone pre-battle save.
