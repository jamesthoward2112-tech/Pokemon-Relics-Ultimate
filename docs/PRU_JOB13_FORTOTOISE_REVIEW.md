# PRU Job 13 — Fortotoise sprite review (stage 1: icon only)

- Approved gameplay baseline: Job 12 `3ecca7c4300bd4813a9a8db7e171ed773907b910`.
- Source reference uploaded by player: `PRL_PR72_Kanto_Champion_Dialogue_20261014.gba` (32 MiB, FireRed/BPRE, SHA-256 `57fac7dd5a4c859ada1612e796b17e9b549a711f80d0fb8fcd523fa03c502c4e`).
- Official source of selected icon: [msikma/pokesprite, Gigantamax Blastoise regular](https://github.com/msikma/pokesprite/blob/master/pokemon-gen8/regular/blastoise-gmax.png).
- Source saved as `assets/pru_final_polish/fortotoise/pokesprite_gmax_icon_source.png` (68×56).
- Conversion: nearest-neighbour original pixel reduction, transparency preserved, centred 32×32, second frame 1px bob; indexed 32×64 palette 3, ≤16 colours.
- Selected output saved as `pokesprite_gmax_icon_GBA_pal3.png`; both Fortotoise icon asset paths use exactly this candidate.
- Fixed the stale CI preparer which overwrote the icon with Mega Blastoise on every build. Linked species icon palette and final-polish mapping to palette 3.
- **Only Fortotoise's icon and its icon pipeline were changed.** Existing front and back PNGs are untouched from Job 12; do not use Job 10 artwork.
- The PR72 ROM remains a reference. The current front/back have **not** been verified pixel-for-pixel against that ROM yet; no claim of front/back completion.
- Approval of all three sprites and visual in-game checks are required before Job 13 ROM release.
- Regression: `python tools/pru/check_job13_fortotoise_icon.py`.
