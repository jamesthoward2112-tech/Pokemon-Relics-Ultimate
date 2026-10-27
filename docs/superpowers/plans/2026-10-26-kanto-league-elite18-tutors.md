# Kanto League, Elite 18, and move-tutor completion

## Save-compatibility boundaries

- Keep trainer IDs 0-695, Johto Elite Four events, gym encounters, and existing heist flags stable.
- Append new trainer IDs and reserve previously unused story flags only.
- The new League challenge is a distinct sequence of five **single** six-Pokémon battles: Lorelei, Bruno, Agatha, Lance and Red. Required: heist recovered and Giovanni beaten.
- Unlock the Elite 18 only after defeating Red. Eighteen **double** battles have six opponents per round, three belonging to each named trainer. Heal between rounds. Expose both full-run and selected-pair play. The subsequent full replay reaches Lv100.
- Award repeatable Rare Candies after Red's defeat, without removing or replacing save inventory.

## Build

1. Add regression tests defining five League battles, all eighteen Elite 18 rounds, order, story flags and tutor coverage. Run them red.
2. Implement new save-safe trainer definitions, entry NPCs, gauntlet event scripts, opponent transition routing and unlock/replay flow.
3. Implement and test move tutor eligibility shared by the Indigo control tutors and relearner, add specialist double-move tutor when the moves are available, and confirm Shuckle's Sticky Web eligibility.
4. Correct the Olivine-departure ship encounter to Steevee and Neevee. This ship is named **S.S. Aqua** in HNS even though it was described as S.S. Anne; edit the Olivine vessel instead of the unrelated Vermilion S.S. Anne.
5. Execute source regressions, build the canonical `.gba` in CI and verify a direct downloadable ROM.

## Validation

Never describe a feature as shipped until the relevant source tests and clean ROM build have succeeded. Report any incomplete feature explicitly.
