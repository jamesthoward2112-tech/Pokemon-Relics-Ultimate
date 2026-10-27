# Rhythm-only Battle Visuals and Elite 20 Entrances Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace compiled Crystal Redux battlefield art with Rhythm scenes throughout PRU and display the agreed matching background and GBA-ready duo entrance for each Elite 20 round.

**Architecture:** Import unique donor Rhythm 4bpp/tiles/maps/palettes as a new static graphics table. Reuse the existing BG3 battle-background and BG0 duo-transition loading paths, injecting a pair-specific override before the normal environment lookup. Make the current dojo gauntlet a save-compatible Elite 20 by inserting two new pairs before the preexisting Red/Blue and Oak/Elm pairs.

**Tech Stack:** GBA C + event scripts, Python 3 source/regression tests and donor asset pipeline, `make hns`, mGBA.

**Spec:** `docs/superpowers/specs/2026-10-27-pru-rhythm-elite20-visuals-design.md`

## Global Constraints

- Preserve all preexisting trainer IDs and save flag numeric IDs; append any new opponent IDs and retain legacy Elite18 flag values.
- All 20 named pairs and exact donor scene IDs come from the spec mapping; 20 distinct backgrounds, no Crystal Redux art linked into the release ROM.
- Keep Jessie/James and Steevee/Neevee transition assets byte-for-byte; keep Red/Blue and Oak/Elm approved transitions.
- Steven/May and Silver/Giovanni use the approved 2172×724 art, BG0 4bpp, 16-colour palette bank 13; never print the player's chosen rival name in fixed artwork.
- The Elite 20 lives in Saffron Fighting Dojo, never Indigo Plateau; no E4 room, tutor, or main-story progression edits in this branch.
- Source `.ups`/ZIP packs are donor inputs, not download deliverables; user downloads an uncompressed `.gba` after integrated QA.
- This branch is separate from PR #55; no integration/merge until the E4 branch is stable.
- PR #55 commit `250c30afdff209615f2f1ae3475da9c59a08009c` already imported all Rhythm assets, switched the global loader, removed active Crystal linkage and added source tests. Preserve those working upstream changes; **Tasks 1 and 2 are verification-only** on this branch.

## Review Focus

- Unexpected custom trainer teams: a solo battle with Brock/Red must not inherit an E20-only background. **Task 3 test:** both opponent IDs must match.
- Donor transparency/palette mismatch: there must be no opaque magenta or palette corruption in mGBA. **Task 2 test:** screenshot comparison of representative background variants and entry graphics.
- Reserved systems: Frontier, link, forced test environment and partner battles retain their original backdrops. **Task 2 test:** source assertions and mGBA spot checks.
- Existing saves: prior Elite18 trainer IDs and completion flags must preserve meanings. **Task 3 test:** IDs and flag values unchanged.
- Limited GBA VRAM / ROM: new atlas and unique backgrounds must not overflow tile/palette or 32 MiB limits. **Task 4/5 tests:** asset bounds, clean link, ROM audit.

---

### Task 1: Import and validate the unique Rhythm donor scenes

**Upstream status:** Already implemented and source-tested in PR #55; verify without duplicating. Do not create another importer or asset table.

**Files:**
- Create: `tools/pru/import_rhythm_battle_backgrounds.py` — deterministic extraction/import from donor zip, checksum manifest, duplicate deduplication.
- Create: `tools/pru/check_rhythm_assets.py` — verify LZ77 signatures, palette length, map dimensions and duplicate reuse.
- Create: `src/data/pru_rhythm_gfx.h`, `src/data/pru_rhythm_bg_table.h` — include definitions, 55-ID-to-44-unique lookup table.
- Create: `graphics/battle_environment/rhythm/<scene-id>/` — only one graphics set for each of 44 unique scenes.
- Update: `src/data/battle_environment.h` or its existing donor include location, linking Rhythm graphics once.

**Interfaces:**
- Produces `struct PruRhythmBattleBg { const u32 *tiles; const u32 *tilemap; const u16 *palette; const u32 *entryTiles; const u32 *entryTilemap; }` and `sPruRhythmBattleBgs` indexed by donor original ID, with shared data references for duplicate originals.
- Importer consumes `Pokemon_Rhythm_Battle_Backgrounds_Extracted.zip`; output is reproducible and traceable to `extraction_manifest.json`.

- [x] **Step 1:** Reused upstream `tools/pru/import_rhythm_battle_backgrounds.py` and existing 55-entry/44-unique scene assets; no duplicate files written.
- [x] **Step 2:** Ran upstream `python3 tools/pru/check_rhythm_battle_background_assets.py`; all 55 source scenes decoded and respected GBA VRAM/pixel limits.
- [x] **Step 3:** Reused PR #55 head `250c30afdff209615f2f1ae3475da9c59a08009c` without recommitting donor blobs.

### Task 2: Replace Crystal Redux rendering with Rhythm throughout normal PRU battles

**Upstream status:** Already implemented and mGBA smoke-tested in PR #55; verify and preserve. Do not rewrite the loader.

**Files:**
- Modify: `src/battle_bg.c` — replace `GetPruCrystalBattleBgIndex` and associated load/entry references with Rhythm equivalents; keep special modes untouched.
- Modify: `src/battle_bg.h` / `include/battle_bg.h` as needed for the existing `IsPruCrystalBattleBgActive` caller and replacement name.
- Modify: `src/data/battle_environment.h` — remove active Crystal graphics include after Task 1.
- Create: `tools/pru/check_rhythm_battle_backgrounds.py` — global routing, exclusions, map exceptions, no active Crystal linkage.
- Update: `.github/workflows/pru-clean-build.yml` in the later integration commit, not in the concurrent E4 branch.

**Interfaces:**
- Consumes Task 1's scene table.
- Produces `static u8 GetPruRhythmBattleBgIndex(u16 environment)` returning 0xFF for unaffected special modes, and `bool8 IsPruRhythmBattleBgActive(void)` used by transition code, while maintaining BG3/entry curtain layering.

- [x] **Step 1:** Reused upstream `src/battle_bg.c` Rhythm-only static renderer, distinct Gym scenes and map exceptions.
- [x] **Step 2:** Ran `python3 tools/pru/check_rhythm_battle_backgrounds.py`; all 55 backgrounds reachable and 16 Gym settings unique. Full visual mGBA smoke testing remains an integration requirement.
- [x] **Step 3:** Kept upstream renderer unchanged; do not duplicate its import or its legacy function-name compatibility wrapper.

### Task 3: Elite 20 dojo roster, contextual backgrounds and save-compatible routing

**Files:**
- Modify: `data/maps/SaffronCity_FightingDojoVIP_hns/scripts.inc` — keep dojo gauntlet location and insert new rounds 17 and 18.
- Modify: wherever the preexisting `PRU_Elite18_Round_*` scripts actually live on the latest integrated branch; do not assume an outdated Indigo copy is current.
- Modify: `include/constants/opponents_hns.h` / `src/data/trainers_hns.party` — append four new duo team opponent IDs for Steven/May and Silver/Giovanni, plus replay master IDs.
- Modify: `src/battle_bg.c`, `src/battle_setup.c` — both-opponent ID matching to the approved scene IDs and intros.
- Create: `tools/pru/check_elite20_visuals.py` — order, 20 unique scenes, correct master variants, no solo-match leakage and legacy numeric stability.

**Interfaces:**
- Consumes `GetPruRhythmBattleBgIndex` and Task 4's two new transition IDs.
- Produces source table `sPruElite20RhythmScenes[20]` with exact scene IDs `[35,48,46,34,39,19,16,45,14,8,18,38,30,42,49,54,41,36,13,0]` in presentation order; lookup from both opponent IDs, including master teams.

- [ ] **Step 1:** Write and run failing source tests for the approved roster, ID stability, 20 scene IDs and both-opponent-only overrides.
- [ ] **Step 2:** Append Steven/May and Silver/Giovanni team IDs without repurposing former Red/Blue and Oak/Elm IDs. Insert two battles ahead of them, keep round-selection/full-gauntlet and replay flow intact, and update E20 text.
- [ ] **Step 3:** Wire dual-ID background and transition choices for all 20 pairs (including Lv100 master); preserve PRL duo logic.
- [ ] **Step 4:** Pass source tests and run mGBA tests for rounds 1, 7, 14–20 in both original and master difficulty, including existing-save setup.
- [ ] **Step 5:** Commit roster/lookup/test changes, avoiding overlap with the active E4 repair until integration.

### Task 4: Convert and register the two new cinematic duo entrances

**Files:**
- Create: `tools/pru/convert_elite20_duo_intros.py` — GBA palette quantization and 240×160 letterboxing without distorting 3:1 artwork, with existing 512-tile atlas/tilemap.
- Create: `graphics/battle_transitions/prl/steven_may.{4bpp,bin,gbapal}` and `silver_giovanni.{4bpp,bin,gbapal}`, plus previews.
- Modify: `include/battle_transition.h`, `src/battle_transition.c`, `src/battle_setup.c` — route new task IDs through the existing PRL emblem fade/wipe and BG0 palette bank 13.
- Extend: `tools/pru/test_duo_transition_integration.py` — exact asset sizes, route, no `SILVER` title, existing asset hash preservation.

**Interfaces:**
- Produces `B_TRANSITION_STEVEN_MAY` and `B_TRANSITION_SILVER_GIOVANNI`; `GetTrainerBattleTransition` routes only their E20 paired IDs (regular and master).

- [x] **Step 1:** Wrote red-then-green tests for aspect-preserving wide-banner conversion and both GBA intro packages; existing Red/Blue and Oak/Elm output behavior remains the default.
- [x] **Step 2:** Converted and visually inspected both approved images as 240×160 aspect-preserving letterboxes, 15 artwork colours (plus black), 276/512 and 281/512 tiles respectively.
- [ ] **Step 3:** Add the two BG0 transition tasks and route them to the correct trainer pairs without changing other pair transitions.
- [ ] **Step 4:** Run source tests and capture mGBA frames for all six themed duo intros; confirm existing Jessie/James and Eevee-twins hashes unchanged.
- [ ] **Step 5:** Commit and push new intro art/converters/tests on this separate branch. Register transitions and their runtime routing later as part of the integrated Elite20 feature branch.

### Task 5: Integration, complete game verification and direct ROM release

**Files:**
- Modify: `.github/workflows/pru-clean-build.yml` after PR #55 is ready — append Rhythm and Elite20 tests; drop Crystal-dependent gating.
- Update: `docs/superpowers/specs/2026-10-27-pru-rhythm-elite20-visuals-design.md` with accurate verified status and art provenance.

**Interfaces:**
- Consumes all prior tasks and a verified base carrying the E4/tutor repairs.
- Produces one validated, direct-download PRU `.gba` GitHub Release asset.

- [ ] **Step 1:** Integrate the tested E4/tutor PR #55 branch without discarding its fixes; resolve source conflicts and rerun all affected tests.
- [ ] **Step 2:** Run existing `python3 tools/pru/check_rhythm_battle_background_assets.py`, `python3 tools/pru/check_rhythm_battle_backgrounds.py`, and forthcoming Elite20 source/runtime tests; all must pass.
- [ ] **Step 3:** Run clean `make hns` and mGBA runtime checks for E4 first/second run, twenty dojo fights, custom intros, tutors and representative wild battles.
- [ ] **Step 4:** Confirm GBA header, title, checksum and ≤32 MiB ROM size; publish only if green. Provide one direct `.gba` URL, not a ZIP.
- [ ] **Step 5:** Commit and push a checkpoint with tested status after each task. If credits run low, preserve branch, exact commit SHA, passing/failing test list and next action; no unverified ROM release.
