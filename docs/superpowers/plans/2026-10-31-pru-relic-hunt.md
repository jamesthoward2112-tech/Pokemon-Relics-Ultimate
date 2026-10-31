# PRU RELICS Hunt Implementation Plan

> **For agentic workers:** Use the existing PRU source patterns and the approved issue/spec. This plan is executed in the isolated `workmode/pru-relic-hunt-20261031` branch.

**Goal:** Move the RELICS quest out of the lab and deliver a compiled direct `.gba` with the approved Eye of Alph and Six-Rune Monolith.

**Architecture:** Keep all seven milestones on existing maps, retaining existing catch flags and normal story encounters. Register two dedicated 16-colour object-event sprites; gate the existing underground monolith encounter on the six recorded captures. Build and publish from a branch based on latest release commit `d5308c8c239207130291378f3d0b8c28d2883650`.

**Tech Stack:** PJR-derived C/event scripts, JSON map data, indexed PNG object-event art, existing GitHub Actions clean-build workflow.

**Spec:** GitHub issue #67 and attached `PRU_RELICS_Final_Work_Prompt.txt`.

## Global Constraints

- Preserve exactly 450 species, save compatibility, Elite 20, tutors, permanent forms, and Rayquaza/Groudon routes.
- The scientist never starts a battle; he repeats the next exact location hint after each recorded catch.
- Use existing accessible maps and rooms only.
- Preserve standard Lugia, Celebi, and Suicune story events; only catches credit milestones.
- Eye of Alph and Six-Rune Monolith must be separate registered object-event graphics derived from the approved image.
- Do not use unverified ordinary sprites or Elm's trainer-only -& sprites as the approved -P art.
- No optional gameplay or screenshot testing. Compile and verify a usable 32 MiB ROM, then give the direct release URL and full commit SHA.

## Review Focus

- Existing saves with prior lab catches: preserve their `FLAG_PJR_RELIC_*` milestones without recapture.
- Run or KO: preserve the encounter and leave the milestone unset.
- Canonical Lugia/Celebi/Suicune story events: preserve their existing sequencing and award relic credit only on a successful catch.
- Object-event palettes and frame sizes: keep each art asset within a 16-colour GBA object palette.
- Build/release isolation: do not move the current PR #66 branch or cancel an existing workflow.

### Task 1: Verify Pokémon sprite sources and effective registrations

**Files:**
- Inspect `graphics/pokemon/{raikou,entei,suicune,lugia,celebi,unown_eye,alphoracle}/`
- Inspect `src/data/graphics/pokemon.h`, `src/data/graphics/pjr.h`, `src/data/graphics/pru_pokemon.h`, and the pinned sprite import workflow/scripts.

- [ ] Compare source assets and palette/icon/back registrations with the approved Xenoverse/TRE assignments; retain the existing effective source where verified.
- [ ] Correct only missing or incorrect registrations, with no new species IDs or form-changing behavior.

### Task 2: Add the approved Ruins objects

**Files:**
- Create `graphics/object_events/pics/misc/eye_of_alph.png` and `graphics/object_events/pics/misc/alphoracle_monolith.png` plus their 16-colour palettes.
- Modify `include/constants/event_objects.h`, `src/data/object_events/object_event_graphics.h`, `src/data/object_events/object_event_graphics_info.h`, `src/data/object_events/object_event_graphics_info_pointers.h`, `src/data/object_events/object_event_pic_tables.h`.

- [ ] Draw separate crisp object-event sprites from the approved silhouettes; Eye is a stone altar with cyan eye and I pupil, Monolith is a stepped tablet with six gold runes and violet core.
- [ ] Register distinct graphics IDs, palettes, dimensions and static animation tables.

### Task 3: Implement the repeatable hunt on existing maps

**Files:**
- Modify `data/maps/RuinsOfAlph_Lab_hns/map.json` and `scripts.inc`.
- Modify `data/maps/Route10_hns/{map.json,scripts.inc}`, `MtMortar_B1F_hns/{map.json,scripts.inc}`, `WhirlIslands_LugiaChamber_hns/{map.json,scripts.inc}`, `IlexForest_hns/{map.json,scripts.inc}`, `Route25_hns/{map.json,scripts.inc}`, `RuinsOfAlph_B1F_hns/{map.json,scripts.inc}`, and `RuinsOfAlph_Outside_hns/{map.json,scripts.inc}`.
- Modify Oak's existing post-Elite-20 lab dialogue in `data/maps/PalletTown_ProfessorOaksLab_Frlg/scripts.inc`.

- [ ] Keep the main scientist at (1,3), face-down, zero movement range; replace direct lab battle paths with repeatable R-E-L-I-C-S hints.
- [ ] Place encounters at the specified existing locations. Preserve canonical story events and record a milestone only after a successful catch.
- [ ] Script reliable Route 10 thunderstorm weather while Raikou remains uncaught.
- [ ] Make the Eye awaken Unown I; make one obvious ladder enter an existing Ruins underground map only after all six catches, where the Monolith awakens Alphoracle.
- [ ] Keep retry access after run/KO and preserve the Crest → Mt. Silver Oak → golden Relic Ho-Oh finale.

### Task 4: Build and publish the isolated ROM

**Files:**
- Modify `.github/workflows/pru-clean-build.yml` only to allow the new isolated build branch and publish condition.

- [ ] Run the existing clean ROM build on this branch without altering the active PR #66 branch or canceling its run.
- [ ] Require successful compile and 32 MiB ROM verification; publish the raw `.gba` prerelease asset.
- [ ] Return the direct asset URL, full commit SHA and concise included-fixes list. Do not run optional emulator gameplay or screenshot checks.
