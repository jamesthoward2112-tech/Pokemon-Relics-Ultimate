# PRU Elite 20 Finale Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make E20 a rewarding finale and hand players into RELICS, including players who already finished E20.

**Architecture:** Keep original E20 script and save flag. Introduce a new dedicated reward-claim flag, give all prizes atomically at the Dojo steward and wire a one-time finale path for completed saves. Extend the existing HnS credits and Mt Silver scripts in isolated follow-up batches.

**Tech Stack:** pokeemerald-expansion/HnS GBA event scripts, source Python regression tests, `make hns`, GitHub Actions.

**Spec:** `docs/superpowers/specs/2026-10-29-pru-elite20-finale-design.md`

## Global Constraints

- Start from the latest working PRU `d46842dd24` lineage already present on the E20 feature branch.
- Keep 450 playable Pokémon and all existing flags/species IDs; GBA builds and saves must stay compatible.
- Only the first E20 full completion awards six Master Balls and five Ancient Stones.
- Make rewards and the new credits scene claimable on older E20-cleared saves without a replay.
- Do not interrupt existing RELICS collection or Tin Tower/Rainbow Crest access while adding Oak's later Mt Silver story.

## Review Focus

1. Old E20-cleared save with no claim flag: claim once without re-fighting or giving an Lv100 full-run battle.
2. Full bag in one or both pockets: give nothing until sufficient room, keep claim flag clear.
3. Replay of a single pair or a complete Lv100 gauntlet: never reissue tangible prizes.
4. Already collected any RELICS/Crest: quest dialogue must not reset its progression.
5. First Johto and second Kanto League credits: preserve their existing routes while customizing E20.

---

### Task 1: One-time E20 reward and professor dialogue

**Files:** `include/constants/flags_hns.h`; `data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc`; `data/maps/NewBarkTown_hns/scripts.inc`; `test/test_pru_e20_finale_reward.py`.

**Interfaces:** Existing `FLAG_PRU_ELITE18_CLEARED`; new `FLAG_PRU_E20_REWARD_CLAIMED = 0x947`; new `PRU_Elite20_ClaimRewards` event script shared by first clears and existing saves.

- [ ] Write failing test for exact quantities, flag, full-Bag precheck, retroactive branch and preserved rematches.
- [ ] Run the focused test (RED).
- [ ] Implement reward script and Oak/Elm RELICS dialogue using existing script macros.
- [ ] Run focused + E20 + Mewduo regression tests (GREEN).
- [ ] Commit and push an isolated, save-compatible batch; verify SHA/CI.

### Task 2: E20-only custom credits and Red routing

**Files:** `src/credits_hns.c`; `src/data/credits_hns.h`; `src/intro_credits_graphics.c`; `data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc`; `data/maps/MtSilver_SummitDay_hns/scripts.inc`; new graphics in `graphics/`; `test/test_pru_e20_credits_route.py`.

**Interfaces:** `FLAG_PRU_E20_REWARD_CLAIMED` selects unique E20 credits; E20 steward provides once-only cinematic replay path for an old completed save. Mt Silver Red retains Crest but no `special GameClear`.

- [ ] Add a failing source test for the E20 credits trigger, distinct Ho-Oh/montage art and Red's no-credits exit.
- [ ] Implement art conversion and dedicated E20 credits mode without modifying ordinary E4 Hall of Fame/credits.
- [ ] Run tests, compile in GitHub Actions and visually smoke-test if mGBA is available.
- [ ] Commit and push; document whether visuals were actually tested.

### Task 3: Professor Oak RELICS summit epilogue

**Files:** `data/maps/MtSilver_SummitDay_hns/scripts.inc`, relevant map JSON, `data/maps/TinTower_RoofDay_hns/scripts.inc`, `test/test_pru_relic_oak_epilogue.py`.

**Interfaces:** Reuse existing `FLAG_PJR_RELIC_*`, `FLAG_PJR_GOT_RAINBOW_CREST` and existing Ho-Oh catch flag; no new species/catch-state mappings.

- [ ] Write failing test for post-RELICS Oak appearance and safe handling of pre-completed saves.
- [ ] Add Oak's summit confrontation and shorter ending without breaking prior Tin Tower encounters and Red rematches.
- [ ] Run RELICS + E20 regression and compiled ROM checks, then push.

## Integration

Do not promote to stable until all three tasks compile and the original stable-feature regressions pass. A direct `.gba` artifact should be provided whenever a new verified build is available.

## Checkpoint (2026-10-29)

Task 1 reward and dialogue: five focused source tests plus 28 PRU tests and E20 integration checks green. Full CI build pending; local restricted shell cannot create temp files for the unrelated Mewduo test.
