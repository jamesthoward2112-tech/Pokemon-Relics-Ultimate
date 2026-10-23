# PRU Lavender and Sprite Polish Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Consistent haunted Tower battle scenes, stable Swamplith PC icon, exact approved Pyroclast front and lowered back.

**Architecture:** Preserve Crystal Redux backgrounds and add a map-scoped selection override. Reserve non-overlapping PC palette tags and load palette resources appropriate to visible PC icons. Replace the active Pyroclast front from the pinned Library donor and alter species anchor only.

**Tech Stack:** GBA C source, indexed PNG, Python/Pillow regression scripts, GitHub Actions GBA build.

**Spec:** `docs/superpowers/specs/2026-10-23-pru-lavender-pc-pyroclast-design.md`

## Global Constraints

- Never change donor art pixels or the approved Pyroclast back/icon.
- Preserve all 38 Crystal Redux assets and other locations' map-seeded selection.
- Keep original Tower story, map, and save flag behaviour.
- Produce a direct `.gba`, never a ZIP as the final deliverable.

## Review Focus

- Tower scripted boss fight and random encounters on different floors use the same scene.
- Gym trainers and battles elsewhere retain existing background selection.
- Swamplith PC icon does not collide with large species preview palette or lose its original colours as the cursor moves.
- PC palette use leaves room for waveform, cursor, preview and title when the box contains custom icons.
- Exact original Mega Typhlosion indexed pixel/palette fidelity survives the build pipeline.

---

### Task 1: Haunted Tower background

**Files:** Modify `src/battle_bg.c`; test `tools/pru/check_lavender_graphics_polish.py`.

- [ ] Write a regression check for all Tower map IDs and a single fixed scene #19, excluding forced battle modes.
- [ ] Run it against current main and observe the missing override failure.
- [ ] Add minimal map override to `GetPruCrystalBattleBgIndex`.
- [ ] Run regression and existing Crystal Redux/Tower tests.
- [ ] Commit task.

### Task 2: PC-only Swamplith palette stability

**Files:** Modify `src/pokemon_storage_system.c`, optionally `src/pokemon_icon.c` and its header for palette loading; test `tools/pru/check_lavender_graphics_polish.py`.

- [ ] Write regression reproducing PC display tag #8 collision and unconditional 14-icon palette preload.
- [ ] Observe regression failure against current main.
- [ ] Reserve icon tags #8–13 and scope PC loading to visible custom species while respecting sprite palette capacity.
- [ ] Run focused and existing sprite/icon regressions.
- [ ] Commit task.

### Task 3: Exact Pyroclast graphics

**Files:** Replace `graphics/pokemon/prl_authoritative/pyroclast/front.png`; modify `src/data/pokemon/species_info/pjr_families.h`; test `tools/pru/check_lavender_graphics_polish.py`.

- [ ] Add checks for the approved donor SHA-256, unchanged back/icon and lower back anchor.
- [ ] Observe expected failure on the existing art/placement.
- [ ] Import the exact indexed image from `PJR_Elite_Redux_Fronts_73.zip` and set a modest lower anchor.
- [ ] Validate PNG dimensions, 4bpp conversion, existing normal palette, regression suite.
- [ ] Commit task.

### Task 4: Canonical build and review

**Files:** Modify `.github/workflows/pru-clean-build.yml` to include new regression; verify source and ROM.

- [ ] Run full relevant regression suite and `git diff --check`.
- [ ] Review branch diff; preserve user changes and source backup.
- [ ] Push isolated branch/PR, let canonical GitHub Actions compile, confirm successful direct GBA release before telling the player to test it.
