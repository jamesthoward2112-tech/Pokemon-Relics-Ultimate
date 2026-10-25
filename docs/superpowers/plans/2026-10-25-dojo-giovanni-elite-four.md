# Kanto Dojo Gauntlet, Giovanni and E4 Rematch Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Ship a raw PRU .gba with the seven-leader Dojo challenge, Armoured Mewtwo Giovanni finale, Elite Four rematches at levels 82–89, and a repeatable Level-100 double-Chansey XP counter.

**Architecture:** Continue from `pru/combined-rhythm-rocket-balloon-20261025` on an isolated feature branch. Reuse the existing `SaffronCity_FightingDojoVIP_hns` map, trainer definitions, persistent heist flags, Viridian Gym boss event, and cave encounter. Add only the battle-only assets/form logic needed to represent Armoured Mewtwo, and lock progression with declarative save flags. Avoid altering the main Dojo EV-training room or the Rhythm 56 background integration.

**Tech Stack:** Existing PRU decompilation: GBA Pokémon map event scripts (`.inc`), party definitions (`.party`), JSON map objects, C battle/data tables, graphics assets, GitHub Actions ROM build, Python static validation, mGBA smoke tests.

**Spec:** `docs/superpowers/specs/2026-10-25-dojo-giovanni-elite-four-design.md`

## Global Constraints
- Work from Rhythm 56 + Rocket balloon branch, without replacing or overwriting its verified direct .gba.
- Seven Kanto leader singles in Dojo VIP: Brock, Misty, Surge, Erika, Janine, Sabrina, Blaine; heal between battles. Levels 76–80.
- Giovanni in reclaimed Viridian Gym: Omastar 81, skeletal Kabutops 82, skeletal Aerodactyl 83, blue/white Coelossus 83, Rhyperior-P/& 84, Armoured Mewtwo 85 **last**.
- Armoured Mewtwo battle-only: Def 120, SpD 120; ordinary Mewtwo stats elsewhere.
- Existing Kanto first-clear badge mechanics, EV Dojo, Johto VIP events, cave catch, Mewsion requirements and save flags remain intact.
- E4 rematch singles: Will 82–85; Koga 83–86; Bruno 84–87; Karen 85–88; Lance 86–89. Six valid Pokémon per trainer; fair AI and items.
- The BP exchange's three clerks remain intact; add one evenly spaced Chansey on the right, offering repeatable two-Chansey Lv100 double battles using only Memento and Heal Pulse.
- Active Pokédex additions #448 Rhyperior, #449 Electivire and #450 Magmortar; both new evolutions use their existing evolution items.
- No unapproved filler sprites. The exact TRE Rhyperior-P/& and Armoured Mewtwo complete asset sets must be verified before artwork integration.
- Ship an uncompressed `.gba`, preserving source history and passing build + emulator checks.

## Review Focus
1. A prior save in which Blue has already been beaten and the theft has started must still see exactly one correct leader and one correct Giovanni.
2. Saving/reloading after any leader, or losing the seventh or Giovanni fight, must never skip stages or softlock Indigo.
3. Attempting to enter Indigo from alternate warps while theft is active must still be blocked; the guard must give accurate Dojo directions.
4. Players with Mewtwo already caught must not duplicate a wild Mewtwo; players without one must retain their legitimate cave encounter.
5. None of the gauntlet NPC flags should accidentally erase Johto VIP rematches or the main Dojo EV trainers.
6. The BP exchange's three clerks remain fully functional, and the rightmost Chansey trainer supports repeatable Lv100 doubles without unintended BP costs or rewards.

---

### Task 1: Baseline and sprite/form audit

**Files:**
- Inspect: `include/constants/species.h`, `src/data/trainers_hns.party`, `data/maps/SaffronCity_FightingDojoVIP_hns/{scripts.inc,map.json}`
- Inspect: existing `graphics/pokemon/` species/form sprite directories and the TRE donor bank in ChatGPT Library
- Create: `docs/pru/2026-10-25-dojo-asset-audit.md`
- Test: `tools/pru_tests/test_2026_heist_content.py` (new)

**Interfaces:**
- Produces an auditable table of `SPECIES_*` IDs and exact complete front/back/icon palette paths for Rhyperior-P/& and Armoured Mewtwo, and verified map object local IDs/flags.

- [ ] **Step 1: Write a static validation test** asserting seven named heist trainers, `SPECIES_RHYPERIOR == 464`, a distinct Armoured Mewtwo battle-only visual/stat route, and existing cave Mewtwo script references. It should initially fail on the currently missing boss form and gauntlet.
- [ ] **Step 2: Run** `python3 -m unittest tools.pru_tests.test_2026_heist_content -v`; record expected missing-asset/gauntlet failures.
- [ ] **Step 3: Search and visually audit TRE Rhyperior-P/& and Armoured Mewtwo complete sprites; document exact source library file, donor slot and all palettes in the asset audit.** If a full set is unavailable, pause that art-specific change and seek user direction; never silently substitute stock art.
- [ ] **Step 4: Append Rhyperior #448, Electivire #449 and Magmortar #450 in canonical and HNS summary data, without renumbering existing IDs.**
- [ ] **Step 5: Commit only verified asset inventory and test scaffolding.**

### Task 2: Dojo VIP ordered heist events

**Files:**
- Modify: `data/maps/SaffronCity_FightingDojoVIP_hns/scripts.inc`
- Modify: `data/maps/SaffronCity_FightingDojoVIP_hns/map.json`
- Modify: relevant save flag/constants file already defining `FLAG_PRU_HEIST_*`
- Test: `tools/pru_tests/test_2026_heist_content.py`

**Interfaces:**
- Consumes named `FLAG_PRU_HEIST_STARTED` and `FLAG_PRU_HEIST_{BROCK,MISTY,SURGE,ERIKA,JANINE,SABRINA,BLAINE,GIOVANNI}`.
- Produces `PRU_DoJoSync` map-entry event that shows only the next Kanto leader; each victory sets its existing persistent heist flag. Reuses `SaffronCity_FightingDojoVIP_EventScript_Nurse`.

- [ ] **Step 1: Add tests** for exact leader order, one visible Kanto leader at a time, no repeat reward, healing between each fight, re-entry after save, and existing Johto VIP rematch events still present.
- [ ] **Step 2: Run** the tests and confirm at least one fails against current simultaneous VIP leader setup.
- [ ] **Step 3: Add map-entry sync, gate first-clear vs heist scripts, and per-leader post-victory movement/hide/show using persistent flags.** Restore or maintain old VIP normal behavior before the theft.
- [ ] **Step 4: Run tests and emulator walkthrough** from fresh save and mid-heist save; verify no softlock with blackout, nurse and entrance warp.
- [ ] **Step 5: Commit Dojo sequence independently.**

### Task 3: Seven approved rematch teams and original-Gym consistency

**Files:**
- Modify: `src/data/trainers_hns.party`
- Modify: existing Kanto original gym `scripts.inc` / map object visibility scripts where leaders are currently present
- Test: `tools/pru_tests/test_2026_heist_content.py`

**Interfaces:**
- Uses leader flags from Task 2 and exact six-Pokémon team species order in the spec.
- Preserves first-clear rewards and existing original badge flags.

- [ ] **Step 1: Add static trainer-table tests** for seven named six-Pokémon singles, levels 76–80, Misty Blastoise, Erika Venusaur, Blaine Charizard with Mega Charizard X art, Surge Electivire not Noxichu, unique valid held items/abilities, and no invalid species names.
- [ ] **Step 2: Run failing test.**
- [ ] **Step 3: Implement team edits**, ensuring custom skins are graphics overrides (not accidentally unwanted global species replacements).
- [ ] **Step 4: Update gym world event visibility** so original first-visit fights remain valid, but leaders are absent during theft; audit Blue's absence in Viridian/Dojo during this story.
- [ ] **Step 5: Run test and smoke each rematch**, including never-again reward duplication; commit.

### Task 4: Giovanni's finale, Armoured Mewtwo and cave release

**Files:**
- Modify: `src/data/trainers_hns.party`
- Modify: `data/maps/ViridianCity_Gym_hns/scripts.inc`
- Modify: `data/maps/ViridianCity_Gym_hns/map.json`
- Modify: existing Mewtwo battle/form sprite, base-stat/overworld/cave script files as discovered in Task 1
- Test: `tools/pru_tests/test_2026_heist_content.py`

**Interfaces:**
- Consumes seven leader heist flags, preserved `FLAG_PRU_HEIST_GIOVANNI`, normal Mewtwo capture/defeat state.
- Produces a six-Pokémon single battle with **Armoured Mewtwo last**; successful end sets Giovanni flag, returns stolen badge, unlocks Indigo, and restores the legal Cerulean Cave Mewtwo encounter.

- [ ] **Step 1: Add tests** that verify Giovanni's exact six/order/levels, uniquely modified Def/SpD 120 on battle-only form, no global Mewtwo stat change, and correct cave/caught branches.
- [ ] **Step 2: Run failing test.**
- [ ] **Step 3: Import audited donor sprites** and implement separate Armoured battle form (or trainer-only transformation path) consistent with the existing engine and 450 Pokédex limit. No placeholder.
- [ ] **Step 4: Implement Giovanni's fossil/Relic dialogue, armour-break escape, flags and player-control timing; preserve save compatibility.**
- [ ] **Step 5: Test Mewtwo never-caught, caught, defeated, Giovanni defeat/loss, re-entry and backup save; commit.**

### Task 5: Rocket guards, League gate and Elite Four rematches

**Files:**
- Modify: existing Route 26 / Indigo guard event script that checks `FLAG_PRU_HEIST_STARTED` and `FLAG_PRU_HEIST_GIOVANNI`
- Modify: `src/data/trainers_hns.party` entries `TRAINER_{WILL,KOGA,BRUNO,KAREN,LANCE}_POSTOBC_HNS`
- Modify: League rematch gate only if it does not yet depend on heist completion
- Test: `tools/pru_tests/test_2026_heist_content.py`

**Interfaces:**
- Consumes Giovanni completion flag; produces guard removal/clear access and rematch unlock.
- Fixed Elite Four levels per spec and six-mon singles; retains team identity and checks held items/AI.

- [ ] **Step 1: Add tests** for guard text to Saffron Dojo, Indigo entry denial before Giovanni (all routes), access after Giovanni, and five E4 rematch bands Will 82–85 / Koga 83–86 / Bruno 84–87 / Karen 85–88 / Lance 86–89.
- [ ] **Step 2: Run and confirm failing tests** on current 74–79 E4 data.
- [ ] **Step 3: Rebalance E4 levels and audit each six-mon move/ability/held-item set.** Eliminate nonsensical duplicate team members where they undermine a deliberate battle role; keep smart trainer AI and a fair healing limit.
- [ ] **Step 4: Update guards/gates and perform full Dojo→Giovanni→League progression tests with old/new saves.**
- [ ] **Step 5: Commit Elite Four + gate changes.**

### Task 6: BP Exchange counter's repeatable level-100 Chansey doubles

**Files:**
- Locate and modify: the exact existing BP exchange counter map JSON and script containing three equally spaced female BP clerks, as pictured in the user screenshot `Screenshot_20261025_175857_Pizza Boy A Pro.jpg`.
- Modify: `src/data/trainers_hns.party` with a dedicated trainer entry.
- Test: `tools/pru_tests/test_2026_heist_content.py` (can split into `test_2026_chansey_xp.py`).

**Interfaces:**
- Consumes the current battle/receptionist NPC interface and Chansey trainer sprite conventions.
- Produces a separate Chansey overworld NPC behind the right end of the BP counter and a repeatable Yes/No Level-100 double battle.

- [ ] **Step 1: Resolve the exact map** by locating the BP exchange room with three NPC clerks spaced equally behind a long horizontal counter; read their map coordinates, graphics and script IDs. Screenshot requires a fourth NPC Chansey station to their right at the same tile interval, without shifting existing receptionists.
- [ ] **Step 2: Add a failing static test** checking four evenly spaced desk NPC stations with the Chansey rightmost, the exact repeatable two-Pokémon trainer entry, each Chansey level 100 with only Memento/Heal Pulse, `Double Battle: Yes`, and a cancellable Yes/No interaction.
- [ ] **Step 3: Run test** and confirm missing Chansey NPC/trainer failure.
- [ ] **Step 4: Add Chansey overworld object** to the actual counter map, add dialogue and reusable `trainerbattle` dispatch without an irreversible beaten flag; use the existing approved Chansey asset.
- [ ] **Step 5: Retest** all three BP clerk functions, Chansey battle repeated after victory, No/B decline, counter collision and normal EXP gain in emulator. Commit.

### Task 7: Clean GBA build and release handoff

**Files:**
- Verify: the existing PRU GitHub Actions build workflow, build logs, output `.gba` and hash manifest
- Add: `docs/pru/2026-10-25-heist-e4-test-report.md`

**Interfaces:**
- Consumes all committed tasks on the feature branch; produces validated direct .gba preserving Rhythm 56 battle backgrounds and Rocket balloon.

- [ ] **Step 1: Run static tests and normal compile**; fix all warnings/errors related to the change.
- [ ] **Step 2: Verify direct 32 MiB GBA** (`GBA` format, no ZIP wrapper) and record SHA-256.
- [ ] **Step 3: Emulator smoke test** Dojo seven leaders, heal, Giovanni armour break, Indigo guard release, E4 levels, cave encounter and first-clear game paths.
- [ ] **Step 4: Run GitHub CI clean, review changes, open draft PR without auto-merging.**
- [ ] **Step 5: Save the resulting raw `.gba` in the user's Library and provide a direct download link plus exact remaining caveats.**

## Self-review / Scope Notes
- Source audit confirmed `SaffronCity_FightingDojoVIP_hns` already contains leader NPCs and a healing nurse; the `SaffronCity_FightingDojo_hns` main room contains EV-training encounters and must remain unchanged.
- Current `POSTOBC` E4 trainers run 74–79 and thus explicitly fail the new level requirement.
- Rhyperior-P/& and Armoured Mewtwo artwork remain asset-validation dependencies; implementation cannot claim sprites are integrated until the actual front/back/icon sheets are found and verified.
- Red/Blue Mt Silver paired superboss is intentionally a separate feature after this shipping ROM.
- BP exchange screenshot shows three equally spaced clerks; the fourth rightmost Chansey station must be measured using actual map tiles, keeping those clerks unchanged.