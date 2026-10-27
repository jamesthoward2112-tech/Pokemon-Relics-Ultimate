# PRU Indigo Tutor Repair Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox syntax for tracking.

**Goal:** Deliver nine adjacent self-explanatory support NPCs and working type-appropriate move compatibility without modifying PRU's other systems.

**Architecture:** Reuse existing PRU map events, native relearner state, and chooser controls. Change the minimum necessary selection logic after reproducing the broken cases. Add regression cases to the current Python source contract and C engine test; verify on GitHub Actions.

**Tech Stack:** pokeemerald-expansion scripts/map JSON/C engine tests, Python 3, GitHub Actions GBA compiler.

**Spec:** `docs/superpowers/specs/2026-10-27-indigo-tutor-repair-design.md`

## Global Constraints

- Keep the ROM save layout and current staged Dex unchanged in this isolated tutor repair. **450 is the approved final roster**, but the checkout currently activates 447 with three reserved; do not claim Dex completion from this patch.
- Preserve the original Daycare Move Relearner; add an additional Indigo specialist.
- Do not alter E4/Dojo/story, battle teams/backgrounds or unrelated moves.
- Nine individual adjacent NPCs at Indigo, facing north, each with introduction and Yes/No.
- Preserve free teaching and standard PC/party selection.

## Review Focus

- A canceled service does not open a menu or modify Pokémon.
- Level-up and egg relearner modes do not mix and do not change other relearner locations.
- Party and boxed Shuckle/Valkiri have consistent move eligibility.
- Other tutors and TMs retain pre-existing compatibility.
- Nine NPCs fit on-screen without hiding the nurse, Mart or Chansey.

---

### Task 1: Reproduce tutor incompatibility and strengthen engine coverage

**Files:** `test/pru/tutor_and_league.c`, `tools/pru/check_pru_tutor_party_gate.py`, `src/chooseboxmon.c`, `src/party_menu.c`

- [ ] Write tests for Shuckle→Sticky Web, Valkiri→Mindwave and Psychic moves, Fighting→Shockwave Fist, Steel→Metal Barrage, and negative cross-type/dex cases; exercise party and boxed teaching decisions.
- [ ] Run the focused engine test and inspect the failure or weakness of the old gate.
- [ ] Fix the shared selection gate at its root without broadening TM compatibility.
- [ ] Re-run focused tests, source regression checks, and commit the repair.

### Task 2: Nine compact specialists and introductions

**Files:** `data/maps/IndigoPlateau_PokemonCenter_hns/map.json`, `data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc`, `tools/pru/check_indigo_support_row.py`

- [ ] Update the source contract first: exactly nine unique specialists at consecutive x coordinates in a row, with a dedicated Egg Tutor, intro and confirm gates.
- [ ] Run the contract and observe its expected failure.
- [ ] Move the eight existing specialists and add the ninth using an existing compatible NPC graphic.
- [ ] Implement free dedicated level-up/egg services, intro/Yes-No for all nine, reusable completion/exit paths; do not alter shared relearner source.
- [ ] Run the contract and other map/progression checks; commit.

### Task 3: Verify end-to-end and hand off

**Files:** only regression/test files as required by actual failures.

- [ ] Run all focused Python tests, including tutoring and map contracts.
- [ ] Run engine tests and GBA compile locally if toolchain is present; otherwise use the canonical GitHub workflow on a separate branch.
- [ ] Verify mGBA boot/screenshots, binary size/header and SHA from CI.
- [ ] Review diff for unrelated changes, then release a raw `.gba` only after checks pass.
