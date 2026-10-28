# PRU Mewsion and Insurgence Shadow Mewtwo Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Give PRU an unlockable Mewsion encounter and replace ordinary Mewtwo with the faithful non-Burst Insurgence Shadow Mewtwo donor.

**Architecture:** Keep the existing `SPECIES_MEWTWO` and `SPECIES_MEWSION` IDs. Use a new persistent Mewsion caught and cave-reentry-ready flag, a temporary map visibility flag, and a first-frame script for the warning. Add append-only Dark Nova move metadata, a Shadow Mewtwo learnset/compatibility, and donor sprite files processed into GBA art.

**Tech Stack:** C11/Pokémon expansion engine, event script assembler and map JSON, ImageMagick/gbagfx, Python validation, `make hns`/GitHub Actions.

**Spec:** `docs/superpowers/specs/2026-10-28-pru-mewsion-encounter-design.md` and `docs/superpowers/specs/2026-10-28-pru-shadow-mewtwo-design.md`.

## Global Constraints

- Do not renumber existing species, moves, object ids or save flags; only append new values.
- Mewsion requires Mew and Mewtwo Pokédex CAUGHT, an outside-cave reentry, and its own capture flag because its National Dex number overlaps Mewtwo.
- Keep Giovanni Armoured Mewtwo unchanged and exclude Mega Shadow Mewtwo X and Burst Mode.
- Only verified donor graphics; no vanilla/incorrect stand-ins represented as dedicated new art.

## Review Focus

- Mewtwo caught inside the cave then walking up/down stairs must **not** unlock Mewsion until a cave exit.
- Captured Mew in PC must satisfy the prerequisite without being in the active party.
- Mewsion KO/flight must permit retries but capture must persist through save/reload.
- Reused Dex index must not instantly hide Mewsion based on Mewtwo's caught bit.
- Dark Nova must perform two hits using the higher attacking stat, not just a 270-power single hit.

---

### Task 1: Mewsion save-gated encounter

**Files:** `include/constants/flags_hns.h`, `src/overworld.c`, `data/maps/CeruleanCave_B2F_hns/map.json`, `data/maps/CeruleanCave_B2F_hns/scripts.inc`, `tests/test_pru_mewsion_encounter.py`.

**Interfaces:** New flags `FLAG_PRU_MEWSION_REENTRY_READY`, `FLAG_PRU_MEWSION_CAUGHT`, temp `FLAG_TEMP_B` on map object; uses existing `GetSetPokedexFlag`, `FlagGet/Set/Clear` and `GetBattleOutcome`.

- [ ] Write focused tests for all unlock permutations, map gate, map tile, script outcome and message once per entry.
- [ ] Run tests; verify they fail on missing feature.
- [ ] Implement flags/restore/gating, map object and battle/on-frame scripts, preserving Mewtwo script.
- [ ] Run focused tests and verify all pass; try `make hns` and investigate compiler/CI requirements.
- [ ] Commit verified task and push isolated branch checkpoint.

### Task 2: Insurgence Shadow Mewtwo mechanics

**Files:** `include/constants/moves.h`, `src/data/moves_info.h`, `src/data/pokemon/species_info/gen_1_families.h`, `src/data/pokemon/level_up_learnsets/pru.h`, `src/data/pokemon/teachable_learnsets/pru.h`, `tests/test_pru_shadow_mewtwo.py`.

**Interfaces:** `MOVE_DARK_NOVA` appended after `MOVE_KABOOM`; `sInsurgenceShadowMewtwoLevelUpLearnset` referenced only by base Mewtwo; `EFFECT_PHOTON_GEYSER` provides category switching and `.strikeCount = 2` gives two hits.

- [ ] Write tests for additive move ID, exact move properties, donor type/ability/stats, authentic learnset, and untouched Mega/Giovanni data.
- [ ] Run tests and verify they fail before changes.
- [ ] Add move metadata and donor species/learnset/teachable data.
- [ ] Run focused tests and check affected source declarations; commit and push checkpoint.

### Task 3: Authentic Shadow Mewtwo battle and menu graphics

**Files:** `graphics/pokemon/mewtwo/{anim_front.png,back.png,shiny.pal,normal.pal,icon.png}` and Insurgence original donor PNG copies; `tests/test_pru_shadow_mewtwo_art.py` and donor provenance document.

**Interfaces:** Preserve existing `gMonFrontPic_Mewtwo`, `gMonBackPic_Mewtwo`, `gMonPalette_Mewtwo`, `gMonIcon_Mewtwo` symbols. Imported donor originals from Insurgence wiki 160×160 files with normal/shiny front/back.

- [ ] Write image validation for sprite dimensions, shared palette indices, normal/shiny distinction and source asset identity; verify initial failure.
- [ ] Make GBA-compatible 64×64 front/back and 32×64 icon assets from the actual Insurgence sprites, preserving source copies and palette compatibility.
- [ ] Verify image tests and visual appearance; commit and push checkpoint.

### Task 4: Dedicated overworld sprites and full build

**Files:** `graphics/pokemon/{mewsion,mewtwo}/overworld.png` and associated palettes/species bindings; end-to-end tests and documentation.

- [ ] Obtain/approve distinct Mewsion 32×32 directional sprite matching its approved white/black/red battle sprite; the image-generation service currently blocks creation.
- [ ] Source or create Shadow Mewtwo map art matching the Insurgence black/orange look; never leave the vanilla overworld as a claimed full donor.
- [ ] Register overworld art, test dynamic Pokémon object graphics and map entry.
- [ ] Verify `make hns` / GitHub Actions ROM artifact and the attached `m2` save progression in an emulator where available.
- [ ] Commit/push verified result and hand off a build, or report art/build access as an explicit external blocker.

