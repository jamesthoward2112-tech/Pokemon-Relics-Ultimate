# Rocket Balloon Preload Visibility Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Make the original approved 64x64 Meowth balloon visibly fly away during both Great Badge Heist scenes without changing League access or actual badge flags.

**Architecture:** Gameplay footage from two builds shows Jessie, James and Meowth disappear while the later `addobject` balloon does not render, even when placed in the open with a 50-frame pause. The balloon asset, graphics ID and 64x64 graphics metadata are present. Preload the balloon into the map's active object list and hide it via `MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE`, which runs after `TrySpawnObjectEvents`; reveal/hide the existing object via `showobjectat`/`hideobjectat` during the cutscene instead of late `addobject`/`removeobject`. Keep its movement type `NONE` so a later callback cannot reset invisibility.

**Tech Stack:** PJR-derived GBA engine, map JSON, assembly event scripts, Python source regression checks, GitHub Actions canonical build.

**Spec:** Existing request and footage from 25 October 2026: Route 22 Rocket balloon visibly carries away Jessie/James/Meowth; Indigo guard remains secure until the Badge Case is returned.

## Global Constraints

- Retain the original approved indexed 64x64 MrNightology balloon art and palette.
- Preserve Kanto Route 22 gate and Indigo Plateau guard coordinates, door script, quest flags and player save progression.
- Deliver verified unzipped `.gba` after CI build.
- Do not merge the draft PR until gameplay QA.

## Review Focus

- Object active and hidden on entering Route 22 from Viridian (no early flash).
- Balloon becomes visible on a save before Badge Heist and stays on-screen during the 50-frame pause.
- Balloon flies up and becomes hidden at cutscene end, including map re-entry.
- Indigo final battle balloon also shows and hides correctly.
- Guard blocking, Giovanni progression, real badge flags and pre-heist saves remain unchanged.

### Task 1: Source regression covering preload instead of dynamic spawn

**Files:** `tools/pru/check_route22_heist_indigo_guard.py`

- [ ] Write assertions for active map balloon (`flag=0`, `movement_type=MOVEMENT_TYPE_NONE`) and warp-in prehide script.
- [ ] Assert that heist and finale use `showobjectat`/`hideobjectat`, never late `addobject`/`removeobject` for the balloon.
- [ ] Run red in GitHub Actions, confirming the old scene fails expected assertions.

### Task 2: Route 22 scene

**Files:** `data/maps/Route22_hns/map.json`, `data/maps/Route22_hns/scripts.inc`

- [ ] Make balloon an always-instantiated map event, initially hidden after object creation.
- [ ] After removing trio objects, reveal loaded local object 14, wait, ascend, then hide (do not despawn).
- [ ] Preserve the pre-heist trigger and other Route 22 events.

### Task 3: Indigo finale

**Files:** `data/maps/IndigoPlateau_hns/map.json`, `data/maps/IndigoPlateau_hns/scripts.inc`

- [ ] Repeat preload and hide/reveal for Indigo local balloon object 4.
- [ ] Keep door entry check, Rocket guard and completion flags intact.

### Task 4: Full verification and ROM

- [ ] Confirm regression checks pass in canonical CI.
- [ ] Confirm full 32MiB GBA build and SHA256 verification pass.
- [ ] Inspect artifact, extract `pokehns.gba` without ZIP, hash-check, replace existing Library ROM.
- [ ] Tell James gameplay replay on a pre-heist save remains required.
