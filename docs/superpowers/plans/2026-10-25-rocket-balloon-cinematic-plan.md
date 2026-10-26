# Rocket Balloon Cinematic Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the Route 22 and Indigo Rocket escapes animated scenes with visible balloon arrival and individual boarding.

**Architecture:** Use existing local NPC and 64×64 balloon object events. Move the balloon from an initially off-screen spawn position into its courtyard location with script movement, stagger the three NPC boarding actions, then fly the same balloon back off-screen.

**Tech Stack:** Pokémon Relics Ultimate GBA/PJR event scripts (.inc), map JSON, Python source regression suite, GitHub Actions build.

**Spec:** `docs/superpowers/specs/2026-10-25-rocket-balloon-cinematic-design.md`

## Global Constraints
- Keep guard and Badge Case story flags unchanged.
- Route 22 Jessie 12, James 13, Meowth 14, balloon 15; Indigo Jessie 1, James 2, Meowth 3, balloon 4.
- Reuse existing balloon sprite without changing art.
- Deliver raw `.gba`; no zip.

## Review Focus
1. Local IDs and map JSON positions match event scripts in each scene.
2. Movement scripts use valid assembler tokens, and each movement is awaited before its object is removed.
3. NPCs move toward the basket before disappearing, not simultaneously.
4. The balloon begins above the visible play area and visibly descends before boarding.
5. Guard/door lock and heist-completed flags remain intact.

---

### Task 1: Define new choreography in regression tests

**Files:** Modify `tools/pru/check_route22_heist_indigo_guard.py`.

- [ ] Assert initial Route22 balloon coordinate (12,6), Indigo (11,4), and 6-step descent to the original courtyard coordinates.
- [ ] Assert gather movement for Jessie/James before addobject.
- [ ] Assert descending balloon movement occurs before per-NPC boarding sequence.
- [ ] Assert each boarding movement is followed by corresponding waitmovement then removeobject, ordered for all three NPCs.
- [ ] Assert upward movement after removal and preserve guard checks.
- [ ] Trigger CI and verify the new regression fails on current static cutscene.

### Task 2: Animate Route 22 theft departure

**Files:** Modify `data/maps/Route22_hns/map.json`, `data/maps/Route22_hns/scripts.inc`.

- [ ] Stage the balloon at 12,6, add scripted descending movement to 12,12.
- [ ] Add two NPC gather sequences and a Meowth reaction before balloon entry.
- [ ] Move Jessie, James and Meowth one by one into basket; remove each only after movement finishes.
- [ ] Rise six tiles, then hide/remove balloon; leave heist gating untouched.

### Task 3: Animate Indigo finale

**Files:** Modify `data/maps/IndigoPlateau_hns/map.json`, `data/maps/IndigoPlateau_hns/scripts.inc`.

- [ ] Stage balloon at 11,4 and descend six tiles to 11,10.
- [ ] Use small reaction/boarding movements and per-NPC removal in sequence.
- [ ] Ascend six tiles and complete with existing fade and guard removal.

### Task 4: Verify and package

- [ ] Run full CI source regression and full canonical 32 MiB GBA build.
- [ ] Check build artifact's ROM checksum.
- [ ] Provide a direct `.gba` and retain previous verified ROM as rollback version.
- [ ] State that user gameplay QA is needed to confirm visual timing and staging.
