# PRU Job 9 — Trainer Battle Quit/Forfeit Freeze

Baseline: `fcc031f780` (Job 8 playable ROM). HNS-only; other build variants retain their existing trainer-battle configuration.

## Behaviour
- PRU normal trainer battles and trainer doubles no longer offer the inherited Quit/Forfeit confirmation. Trying the bottom-right RUN option produces the standard "can't run from a trainer" response and returns to action selection.
- Frontier and Trainer Hill trainer battles in PRU also bypass the separate forfeit confirmation path. The accidental forfeit outcome is not set by the normal RUN route.
- Wild encounters retain the R-button quick-run shortcut and unchanged wild escape checks; no battle-outcome or Pokémon-save data layout has been modified.
- The battle menu still labels the action RUN (as in GBA); it is unavailable in trainer fights. Fight/Bag/Pokémon options are untouched.

## Tests
- `python3 tools/pru/check_job9_trainer_forfeit.py` verifies guarded trainer branches and preserved wild-run logic.
- `make -j2 check BUILD=hns TESTS=test/pru/trainer_forfeit_disabled.c` runs compiled assertions for normal trainers, doubles, Frontier/Hill and wild battle classification.
- The PRU clean-build workflow rebuilds a 32 MiB ROM, checks previous jobs and launches mGBA with the inspection save.

No save conversion is needed. Verify a real trainer battle interactively with your playtest save; automated boot testing is not a substitute for pressing RUN against a trainer.
