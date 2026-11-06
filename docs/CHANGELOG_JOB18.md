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
- Local ROM build is blocked because this environment lacks `arm-none-eabi-gcc`, `pkg-config`, and `libpng` headers. The Job 18 branch is wired into the canonical clean-build workflow for the hosted build.
- The genuine pre-Dragonite `.sav`, mGBA save/reload test, compiled ROM, hosted emulator results, commit SHA, and release URLs will be recorded after the clean build/save validation completes. No test save or ROM is claimed in this source-only checkpoint.
