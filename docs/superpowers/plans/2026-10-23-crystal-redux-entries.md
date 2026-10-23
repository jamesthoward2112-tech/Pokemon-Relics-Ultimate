# Crystal Redux Original Entries Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace Emerald entry effects with each Crystal Redux scene's matching original entrance art without moving the finished backdrop.

**Architecture:** BG3 remains the complete stationary scene. Extend the existing 38-entry asset table with donor entry graphics; temporarily load/animate those graphics on the already-used BG1 battle-entry surface and clean up before combat. Keep unsupported/special battles on existing fallback transitions.

**Tech Stack:** PRU/pokeemerald-derived C, GBA 4bpp/LZ77 BG tilemaps, Python source regressions, GNU ARM toolchain.

**Spec:** `docs/superpowers/specs/2026-10-23-crystal-redux-entries-design.md`

## Global Constraints
- All 38 backgrounds and 16 unique Gym leaders retained; match entry and background index.
- BG3 never scrolls/splits/wipes. No additional Emerald foreground, black gap or seam.
- Existing ordinary trainer/Pokémon/platform entry callbacks unchanged.
- Link/partner/facility/forced-test fallbacks unchanged.
- Compile and package direct `.gba`, not zip.

## Review Focus
- Palette conflicts: special weather/Gym palettes must not corrupt donor entry or BG3; test remapping by palette bits.
- Background selection: rematches and dynamic maps must use one index for both components; test 38 indices and leader overrides.
- First/last frame: entry art must be offscreen before cleared; test frame bounds and cleanup order.
- Unsupported battles: link/partner/facility/legendary must avoid altered transition; test all flags.
- Combat effects: BG1 register/tilemap reset must preserve later move animation; verify cleanup and an emulator battle.

---

### Task 1: Pair all 38 donor entry assets with their scenes

**Files:**
- Modify: `src/data/pru_crystal_gfx.h`
- Modify: `src/data/pru_crystal_bg_table.h`
- Modify: `tools/pru/check_crystal_battle_backgrounds.py`

**Interfaces:**
- Produces: `struct PruCrystalBattleBg` fields `entryTiles`, `entryTilemap` beside `tiles`, `tilemap`, `palette`.

- [ ] **Step 1: Write regression for 38 matching entry symbols/table pointers and LZ77 asset lengths (entry map 896 B).**
- [ ] **Step 2: Run `python3 tools/pru/check_crystal_battle_backgrounds.py`; expected missing-entry assertion fails.**
- [ ] **Step 3: Add `INCBIN_U32` symbols and table pointers for every ID 00–37; use donor files unchanged.**
- [ ] **Step 4: Rerun the source check; expected PASS.**
- [ ] **Step 5: Commit focused asset-table change.**

### Task 2: Load a matched donor entry without palette or BG3 interference

**Files:**
- Modify: `src/battle_bg.c`
- Modify: `include/battle_bg.h`
- Create: `tools/pru/check_crystal_entry_transitions.py`

**Interfaces:**
- Produces: `bool8 IsPruCrystalEntryActive(void)`, `void EndPruCrystalBattleEntry(void)`; selected entry index must use the existing `GetPruCrystalBattleBgIndex(GetBattleEnvironmentOverride())` mapping.
- Consumes: paired art from Task 1.

- [ ] **Step 1: Add source regressions asserting no Emerald loader, donor `entryTiles/entryTilemap` load into BG1, palette isolation/remapping and special-battle fallbacks.**
- [ ] **Step 2: Run new check; expected failure because existing Emerald loader is still present.**
- [ ] **Step 3: Replace Emerald loader/callback with matching donor entry, bounded map copy, palette remap and deterministic BG1 cleanup; BG3 untouched.**
- [ ] **Step 4: Run both background/entry checks; expected PASS.**
- [ ] **Step 5: Commit loader change.**

### Task 3: Animate original entry and preserve stationary main scene

**Files:**
- Modify: `src/battle_intro.c`
- Modify: `tools/pru/check_crystal_entry_transitions.py`
- Modify: `docs/pru_crystal_redux_38_battle_backgrounds.md`

**Interfaces:**
- Consumes: Task 2 entry active/cleanup API; normal `HandleIntroSlide` dispatch.
- Produces: bounded intro task moving only BG1, never BG3 or HBlank offset buffers.

- [ ] **Step 1: Add tests for starting position, end-of-screen cleanup, stationary BG3, and fallback when no entry is active.**
- [ ] **Step 2: Run check; expected failure on current `gBattle_BG1_Y` -160 to +160 Emerald sweep.**
- [ ] **Step 3: Implement donor entry timing in the existing BG1 path; keep static PR #22 guard, normal sprite callbacks and safe layer restoration.**
- [ ] **Step 4: Run entry + full source regressions; expected PASS.**
- [ ] **Step 5: Commit intro and design documentation.**

### Task 4: Build and verify

**Files:**
- Modify: `.github/workflows/pru-clean-build.yml` (replace obsolete Emerald checker)
- Modify: `tools/pru/check_crystal_entry_transitions.py`

- [ ] **Step 1: Assert workflow invokes Crystal entry regression, not `check_emerald_foregrounds.py`; run failing test.**
- [ ] **Step 2: Switch workflow check and run complete source suite; expected PASS.**
- [ ] **Step 3: Compile `make hns -j2 -O` in prepared PRU environment; expected exit 0, `pokehns.gba` 33,554,432 bytes.**
- [ ] **Step 4: Inspect emulator wild grass, water, rocky, indoor and Gym entry, plus menu/move animation restoration; report unverified cases separately.**
- [ ] **Step 5: Commit workflow/test change, review branch, open PR for user approval before merging/publishing.**
