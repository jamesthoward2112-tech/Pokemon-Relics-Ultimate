# Lavender Spirit Tower Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make PRU's seven Lavender Spirit Tower floors playable, atmospheric and safely escapable while preserving the existing Cubone quest.

**Architecture:** Keep HNS map instances backed by checked-in FRLG layout/tileset binaries. Add wild data to the central JSON, map fog/escape flags and Fuji's scripted return warp. A focused source regression test checks donor geometry, map links, encounter coverage and quest stability.

**Tech Stack:** Pokeemerald/PJR HNS source, event ASM, map/wild JSON, Python 3 regression, GitHub Actions `make hns`.

**Spec:** `docs/superpowers/specs/2026-10-23-lavender-spirit-tower-design.md`

## Global Constraints

- Do not touch Lavender Radio Tower, existing map ordering, PRU 447 species, quest flags or existing boss battle implementation.
- Escape Rope returns in front of Mr Fuji at Soul House (11,12); 1F door also returns to Soul House.
- No new species, no costume spoiler, and no compulsory trainer gauntlet.
- Preserve original full FRLG maps, 24×20 layout, tilesets, metadata and 7-floor route.
- Do not claim gameplay verification without running the ROM.

## Review Focus

- Invalid stair destination: check matching warp index and coordinates for every floor and original donor.
- Incorrect map collision: check each warp tile against original binary and tileset metadata; targeted emulator walk still required.
- Rope using stale overworld destination: assert `setescapewarp` before script `warp`, `allow_escaping` on all floors, and destination (11,12).
- No ghost encounters or out-of-dex species: assert new HNS entries for 2F–7F, each of 12 slots valid in approved list.
- Save-game progression: retain exact species levels, flags, stage scripting and 7F Mimikyu repeat on defeat.

---

### Task 1: Donor geometry and return regression

**Files:**
- Create: `tools/pru/check_lavender_tower_restoration.py`
- Inspect: `data/maps/LavenderSpiritTower_{1..7}F_hns/map.json`, `data/maps/PokemonTower_{1..7}F_Frlg/map.json`, `data/layouts/layouts.json`

**Interfaces:** Reads existing maps/layouts; exits zero if constraints hold.

- [ ] **Step 1:** Write failing assertions for reciprocal donor stair warps, 24×20 dimensions, valid warp indices, binary blockdata size, Escape Rope flags and Fuji script text/target.
- [ ] **Step 2:** Run `python3 -B tools/pru/check_lavender_tower_restoration.py` and observe failure for unimplemented return/fog/encounters.
- [ ] **Step 3:** Fix any independently demonstrated map/warp mismatch; leave the original donor layout unchanged otherwise.
- [ ] **Step 4:** Run the test; record remaining failures for subsequent tasks.
- [ ] **Step 5:** Commit a coherent test/geometry batch.

### Task 2: Spirit transport and ghost atmosphere

**Files:**
- Modify: `data/maps/LavenderTown_SoulHouse_hns/scripts.inc`
- Modify: `data/maps/LavenderSpiritTower_{1..7}F_hns/map.json`

**Interfaces:** Sets the native escape destination from Mr Fuji's script; maps permit rope and carry weather.

- [ ] **Step 1:** Use the Task 1 failing test as the RED return/fog regression.
- [ ] **Step 2:** Reword the rumour, add close-eyes message and `setescapewarp MAP_LAVENDER_TOWN_SOUL_HOUSE_HNS, 11, 12` before the warp; enable rope across seven floors, fog from 2F upward.
- [ ] **Step 3:** Run targeted and original Cubone tests and check exit 0 or isolate the remaining wild-data failure.
- [ ] **Step 4:** Commit the story/navigation batch.

### Task 3: Wild ghosts and sparse exploration

**Files:**
- Modify: `src/data/wild_encounters.json`
- Optionally modify: `data/maps/LavenderSpiritTower_2F_hns/map.json`, `data/maps/LavenderSpiritTower_4F_hns/map.json` and matching scripts for at most two optional Channelers.

**Interfaces:** 2F–7F HNS encounter data using existing `gWildMonHeaders` 12-slot land tables.

- [ ] **Step 1:** Observe RED regression for six absent HNS encounter entries.
- [ ] **Step 2:** Add land encounter tables for floors 2–7, max 12 approved slots per floor, levels rising from 48 to 65 and no new species.
- [ ] **Step 3:** Run both tower checks and `python3 -B tools/pru/check_pru_444_gameplay.py`.
- [ ] **Step 4:** Commit the encounter batch.

### Task 4: CI and ROM validation

**Files:**
- Modify: `.github/workflows/pru-clean-build.yml` to execute targeted regression and allow checking the feature branch without publishing a non-main release.

**Interfaces:** Main push continues to publish direct `.gba`; feature-branch build uploads a test artifact only.

- [ ] **Step 1:** Wire the new regression into the workflow, run all available source checks.
- [ ] **Step 2:** Push isolated branch and inspect a fresh GitHub Actions compilation result.
- [ ] **Step 3:** If green, report exact commit/run/artifact; if red, fix from actual log and repeat. Keep the feature branch for a separate merge decision.
