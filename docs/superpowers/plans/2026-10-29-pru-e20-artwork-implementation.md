# PRU E20 battle artwork implementation plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver corrected E20 trainer portraits and twenty themed joint battle entry graphics without touching the ongoing Mewduo repairs.

**Architecture:** Work on `feature/pru-e20-artwork-staging-20261029` forked from tutor-stable `a4d393129e`. Keep trainer portraits in `graphics/trainers/front_pics` and joint battle banners in `graphics/battle_transitions/prl`; register them through the existing battle transition and trainer-data tables.

**Tech Stack:** PRU GBA C/ASM, `.party` trainer definitions, indexed PNG/4bpp tiles, Python regression checks.

**Spec:** `docs/superpowers/specs/2026-10-29-pru-e20-artwork-design.md`

## Global constraints
- Preserve Pokémon Rhythm backgrounds, the 450 Pokédex, save compatibility and all stable tutor features.
- Keep existing five approved entrances (S&N, J&J, R&B, Steven/May, Silver/Giovanni), apart from replacing Oak/Elm as requested.
- Do not merge or release this staging branch while Mewduo repairs are underway.

## Review focus
1. An image already depicting two characters must not be drawn twice for a two-trainer battle.
2. The transparent partner must not render a black box or shift the other image off-screen.
3. Three Pokémon per trainer and their moves/items must remain unchanged during portrait patches.
4. Original solo Jessie/James appearances must retain their working pictures.
5. The later Oak/Elm picture must visually distinguish Elm and use a valid 16-colour palette.

---

### Task 1: Repair duplicated paired trainer pictures
**Files:** `src/data/trainers_hns.party`, `include/constants/trainers.h`, `src/data/graphics/trainers.h`, `graphics/trainers/front_pics/pru_invisible.png`, `test/test_pru_e20_visuals.py`
- [ ] Write regression checks for round 14 and 15 normal/master Pic assignments; verify they fail on stable baseline.
- [ ] Add a 64×64 indexed transparent partner front picture and register its trainer picture ID.
- [ ] Assign the joint Twins image only once and Rocket group only once; retain the two parties and species.
- [ ] Run source tests and build/boot to check transparent placement in both round variants.
- [ ] Commit/checkpoint branch.

### Task 2: Fix Oak versus Elm identity
**Files:** `graphics/trainers/front_pics/*elm*`, trainer picture IDs and `src/data/trainers_hns.party`
- [ ] Identify or create a pixel-perfect, *distinct* Professor Elm asset.
- [ ] Add a test proving Elm does not use Oak's picture in normal/master round 20.
- [ ] Register and assign Elm; confirm in mGBA.
- [ ] Commit.

### Task 3: Build missing pair intros
**Files:** `assets/pru_e20/intro_manifest.json`, `graphics/battle_transitions/prl`, `src/battle_transition.c`, appropriate transition constants/script selectors.
- [ ] Prepare one reviewed 4bpp title banner per missing pairing: rounds 1–13 and 16.
- [ ] Keep the six existing transitions, replace Oak/Elm's banner after artwork approval.
- [ ] Register all twenty transitions, use the proper E20 round selector, and test all 20 entrances in mGBA.
- [ ] Commit.

### Task 4: Custom Pokémon showcase and regression
**Files:** `src/data/trainers_hns.party`, sprite/party data as required.
- [ ] Audit actual 450-species forms, front/back/party sprites, team motifs, move validity.
- [ ] Propose additional existing custom forms for underrepresented rounds without changing approved pair order.
- [ ] Test six-member LV100 doubles, moves, icons, progression, tutor and Mewduo coexistence after merging.
- [ ] Commit only verified assignments, then review staging branch for eventual integration.
