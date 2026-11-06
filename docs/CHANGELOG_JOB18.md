# Pokémon Relics Ultimate — Job 18

## Story and encounters

- Professor Oak remains the final Elite 20 opponent. His post-battle dialogue foreshadows an Ultimate Ancient Relic without identifying its location.
- The Alph Lab directions require Oak's Elite 20 defeat and all seven RELICS, then point to Mt. Silver's summit.
- Mt. Silver's summit now hosts Oak's no-battle, retry-safe Golden Ho-Oh summoning scene. Golden Ho-Oh is level 100 and is the only new Ho-Oh encounter in this route; capture begins the existing Job 16/17 credits sequence once.
- Tin Tower's Kimono Girls summon the non-catchable level 60 Ancient Guardian Dragonite boss, with its dedicated Multiscale / Weakness Policy battle build. The summit shortcut sign reads `Shortcut to Top`.
- No Guardian Wing or Rainbow Wing is required for the Golden Ho-Oh finale.

## Artwork and compatibility

- Added the approved Elite Redux Mega Dragonite front, back, and icon assets as a dedicated permanent Dragonite visual form. The source PNGs are SHA-256 locked and the normal Dragonite art remains unchanged.
- Tin Tower saves already marked as Ho-Oh complete or holding the old Ho-Oh relic are recognized as completed; they do not repeat the rooftop encounter.
- Existing E20 rewards remain on their prior one-time reward flag. No user save is edited.

## Validation status

- Source regressions: `check_job18_story.py`, `check_golden_hooh.py`, and `check_job18_assets.py` pass.
- `git diff --check` passes.
- GitHub Actions run [42274347783](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/42274347783) passed source regressions, Golden Reign/Phoenix Soul battle-engine tests, clean build, compiled sprite checks, exact 32 MiB ROM verification, and mGBA boot with the existing inspection save.
- ROM size: 33,554,432 bytes. SHA-256: `87be3adf60608fcd452dc567198703f225d3cd8e250b36065773807c77ca03d2`.
- Release: [Pokémon Relics Ultimate — Job 18 Test Release](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-job18-test-40490e6102). [Download the ROM](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-job18-test-40490e6102/Pokemon-Relics-Ultimate-40490e6102.gba).
- The genuine pre-Dragonite `.sav` and mGBA save/close/reload test remain unavailable. Existing sprite QA saves do not satisfy this requirement and were excluded from the Job 18 release.
- The mGBA check covers ROM boot using the existing inspection save; it does not validate the Dragonite ceremony, Golden Ho-Oh finale, save persistence, or dialogue visually. Player gameplay testing remains outstanding.
- Source commit in the release: `40490e61023667726d039f2b1c731baa8b85328b`.
