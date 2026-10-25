# Primal Cave Presentation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Make the Seafoam Kyogre room blue-water-themed, display the shipped shiny Primal overworld art for Kyogre and Groudon, and keep Archie's Kyogre as his final strong ace.

**Architecture:** Add a Seafoam-specific secondary palette wrapper around the existing Blackthorn Gym tile art and metatiles, with only the magma/water colours transformed to blue. Register new 64×64 shiny Primal event sprites without changing existing generic Kyogre/Groudon graphics, then point the two legendary cave events at these new IDs.

**Tech Stack:** pokeemerald expansion C/event maps, JASC palette, Python source regressions, GitHub Actions GBA clean-build.

**Spec:** `docs/superpowers/specs/2026-10-25-primal-cave-presentation-design.md`

## Global Constraints

- Preserve original Seafoam blockmap, weather, coordinates, exit and script behavior.
- No changes to Blackthorn Gym appearance or other NPC sprites.
- Reuse existing `graphics/pokemon/{kyogre,groudon}/primal/overworld.png` and shiny palettes.
- A caught legendary disappears permanently; KO/whiteout permits retries.

## Review Focus

- Shared palette IDs may recolour Blackthorn Gym: test that only the Seafoam layout switches tileset.
- 64×64 OW sprite may overlap Archie or exit: test coordinates and visibility flags, and inspect in emulator.
- Tile palette remapping may leave red animated lava: test actual palette slots and preview in game.
- Trainer ace AI may still permit forced switching: test ordinary knockout sequence in emulator.
- Shiny palette indexing may mismatch sprite PNG: validate 16 colours and converter build.

---

### Task 1: Cave-only blue water palette

**Files:** `data/layouts/layouts.json`, `src/data/tilesets/{headers,graphics}.h`, `data/tilesets/secondary/blackthorn_gym_hns/palettes/pru_seafoam_blue_12.pal`, `tools/pru/check_20261024_primal_ace.py`.

- [ ] Add failing source test for Seafoam-only palette and blue water RGBs.
- [ ] Run test and record failing assertion.
- [ ] Register cave-specific secondary tileset and blue replacement for lava palette slot 12, preserving remaining geometry.
- [ ] Run source test and verify pass.

### Task 2: Shiny Primal overworld events

**Files:** `include/constants/event_objects.h`, `src/data/object_events/{object_event_graphics,object_event_pic_tables,object_event_graphics_info,object_event_graphics_info_pointers}.h`, `src/event_object_movement.c`, `data/maps/{SeafoamIslands_SecretCave_hns,MtSilver_1F_MoltresRoom_hns}/map.json`, `tools/pru/check_20261024_primal_ace.py`.

- [ ] Add failing assertions for both Primal event graphics IDs and asset registration.
- [ ] Run regression and confirm it fails.
- [ ] Register 64×64 shiny-palette overworld sprite infos and point cave events at them.
- [ ] Run regression and confirm pass.

### Task 3: Battle ace and final verification

**Files:** `src/data/trainers_hns.party`, `tools/pru/check_20261024_primal_ace.py` and build workflow (if new test registration needed).

- [ ] Assert strong final-slot shiny Blue Orb Kyogre, ace AI and minimum boss level above teammate.
- [ ] Run source test red; set boss Kyogre to Lv80, preserve Origin Pulse / Thunder / Ice Beam / Calm Mind.
- [ ] Run targeted and existing regressions; inspect diff and push branch.
- [ ] Require successful GitHub clean-build and ROM artifact before merge or release.
