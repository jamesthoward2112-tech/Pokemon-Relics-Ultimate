# PRU Stable-Base Mewduo Merge Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Merge only the approved Mewtwo/Mewduo features into the verified `a4d393129e` Indigo-tutor-stable ROM source.

**Architecture:** Branch directly from a4d. Freeze the stable Indigo floor layout, nine NPCs, party/PC tutor selection and compatibility. Port the Mewduo encounter and Shadow Mewtwo battle changes in independently tested batches. Mewduo's overworld shares the exact stable Mewtwo tile art and gets a dedicated colour palette.

**Tech Stack:** Pokémon PRU GBA decomp (C, Poryscript/map scripts, PNG/JASC 4bpp art), Python regression tests, GitHub Actions ARM GCC + mGBA.

**Spec:** `docs/superpowers/specs/2026-10-29-a4d-mewduo-merge.md`

## Global Constraints

- Base full SHA `a4d393129ec3683f0443a80272df71653a3874af`; reference ROM build 40579466155 passes SHA-256.
- Preserve Indigo map x=6..14/y=15 and exactly nine services with Egg Tutor; do not replace `src/chooseboxmon.c` or `src/party_menu.c` with the regressed branch versions.
- Preserve original `graphics/pokemon/mewtwo/overworld.png` and its palette, bytes unchanged.
- Add Mewduo palette only, not a hand-drawn/resized overworld sprite; do not change existing save IDs or Elite 20.
- Raw `.gba` delivery only after successful binary/emulator verification; never overwrite the stable ROM artifact.

## Review Focus

1. Party and PC tutor choices retain the selected move across callbacks, including custom species that share National Dex entries.
2. All nine Indigo NPCs spawn on valid floor tiles and show the requested intro/decline interaction.
3. Mewduo uses Mewtwo's real overworld tiles but a separate red/grey palette in the compiled ROM; ordinary Mewtwo remains unchanged.
4. Mewduo's capture marker never marks an uncaught Mewduo caught merely because Mewtwo was caught.
5. An existing save with Mew and Mewtwo registered sees one Mewduo on cave re-entry; Relic Candy and the Key Items bag remain usable.

---

### Task 1: Lock the stable tutor baseline and add failing merge tests

**Files:**
- Existing tests: `tools/pru/check_indigo_support_row.py`, `tools/pru/check_pru_tutor_party_gate.py`, `test/pru/tutor_and_league.c`
- Create: `tools/pru/test_pru_a4d_mewduo_merge.py`

**Interfaces:** Consumes `a4d393129e` existing NPC scripts and `CanSpeciesLearnPruTutorMove`; produces regression checks for the overlay, capture and new move learnsets.

- [ ] Run the two existing Python tutor checks; expect nine adjacent floor-safe services and valid party/PC gate.
- [ ] Write a failing merge test asserting Mewduo's separate encounter/caught marker, Lv90/95/100 moves, separate palette and exact stable Mewtwo overworld tile source.
- [ ] Run it and confirm failure is due to missing new Mewduo functionality, not test setup.
- [ ] Commit the tests and spec/plan checkpoint.

### Task 2: Restore Mewduo encounter, sprite, icon and learnset

**Files:**
- Modify: `data/maps/CeruleanCave_B2F_hns/{map.json,scripts.inc}`, `src/overworld.c`, `include/constants/{flags.h,flags_hns.h,vars.h,vars_hns.h}`, `src/data/pokemon/{level_up_learnsets/pru.h,species_info/pru_custom.h}`
- Modify: `src/data/graphics/pru_pokemon.h`, `src/data/object_events/object_event_pic_tables_followers.h`, `src/pokemon_icon.c`, `src/battle_interface.c`
- Create: `graphics/pokemon/mewsion/overworld_normal.pal`, `src/pru_mewduo_caught_icon.h`, `src/pru_mewsion_gate.h`
- Test: `tools/pru/test_pru_a4d_mewduo_merge.py`, `tools/pru/test_pru_mewsion_encounter.py`

**Interfaces:** Produces `PruMewsionAllowed`, `PruHasCaughtSpeciesForBattleIcon`, `gOverworldPalette_Mewsion`, `sPicTable_Mewsion`, and save-safe capture scripts. These feed Task 3's move cases without modifying stable tutor selection.

- [ ] Verify the test's red failure under a4d; copy/port only the relevant PR61 quest and source definitions.
- [ ] Map Mewduo's graphic pixels to the unchanged Mewtwo source and its dedicated red/grey overworld palette.
- [ ] Run targeted tests and all a4d Indigo source regressions; expect green.
- [ ] Commit the standalone Mewduo batch.

### Task 3: Restore Shadow Mewtwo battle signature and additive tutor moves

**Files:**
- Modify: `graphics/pokemon/mewtwo/{front/back/icon/normal/shiny}.png` and supported `*_gba` variants (NOT overworld); `src/data/pokemon/species_info/gen_1_families.h` and Mewtwo level-up data.
- Modify: `include/constants/{moves.h,battle_move_effects.h,battle_string_ids.h,battle.h}`, `src/data/moves_info.h`, battle scripts and relevant `src/battle_*.c`.
- Append targeted new-move cases to stable `src/chooseboxmon.c` and stable Indigo tutor menu/scripts; retain its `sActivePruTutorMove` mechanism.
- Test: `tools/pru/test_pru_shadow_mewtwo.py`, `tools/pru/test_pru_insurgence_extra_moves.py`, `tools/pru/check_indigo_support_row.py`, `tools/pru/check_pru_tutor_party_gate.py`.

**Interfaces:** Consumes stable tutor gate and Task 2's Mewduo species. Produces Dark Nova/Permafrost etc. as append-only moves and their battle effects.

- [ ] Copy the existing PR61 Shadow Mewtwo/Insurgence test expectations first, watch missing-feature failure.
- [ ] Port the minimum donor art and battle-effect source, maintaining Mewtwo's original overworld and the stable tutor code.
- [ ] Run all relevant source and emulator tests; expect green, including nine Indigo tutors and special species eligibility.
- [ ] Commit the battle/moves batch.

### Task 4: Build, visually verify, and deliver

**Files:**
- Modify only if needed: `.github/workflows/pru-clean-build.yml` (source and compiled-asset regression checks)
- Final artifact: `Pokemon-Relics-Ultimate-a4d393129e-Mewduo.gba`

**Interfaces:** Consumes exact Task 1–3 commits. Produces a 33,554,432-byte GBA ROM and SHA-256 from GitHub Actions, never an unverified local variant.

- [ ] Check changed files against a4d, confirming no destructive tutor, Elite 20, item or E4 regressions.
- [ ] Push the isolated branch, run the canonical GitHub Actions ARM/mGBA build, inspect each failed step if any.
- [ ] Verify the compiled Mewduo overworld palette and graphics mapping plus visible nine-tutor layout; test saved-game cases when the emulator environment permits.
- [ ] Verify the ROM checksum and deliver a direct `.gba` link with explicit untested paths, if any.
