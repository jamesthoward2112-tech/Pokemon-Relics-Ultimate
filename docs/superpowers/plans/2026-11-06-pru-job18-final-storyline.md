# PRU Job 18 Final Storyline Implementation Plan

> **For agentic workers:** Follow the user's explicit end-to-end execution request; no planning-only handoff.

**Goal:** Implement and release the Job 18 story, unique non-catchable Tin Tower Dragonite boss, Golden Ho-Oh ending, and a clean pre-battle save.

**Architecture:** Extend current PRU field scripts and save flags, reuse the existing E20 cinematic/credits code, and create a dedicated internal battle-only Guardian Dragonite species record so art stays isolated without a National Dex entry. Reuse current production build tooling and add focused source regressions and asset locks.

**Tech Stack:** pokeemerald-expansion C, Poryscript/assembly map scripts, PNG 4bpp graphics pipeline, Python regression checks, ARM GCC/make, mGBA, GitHub Actions releases.

**Spec:** `specs/job18/spec.md`

## Global Constraints
- ROM must be exactly 33,554,432 bytes.
- Keep total public roster at 450 and add no Pokédex entry.
- Do not modify existing user or Zacharias saves.
- Do not change Lance's Dragonite Relic, existing E20 opponents/rewards, or unrelated mechanics.
- Mt Silver sign text must be exactly `Shortcut to Top`.
- Phoenix Soul must survive lethal damage at 1 HP then restore an additional 25% max HP once per battle.
- Golden Reign: Fire/Special/110/100/5, both opposing Pokémon, 20% burn, five turns harsh sunlight, Make It Rain animation.

## Review Focus
- Legacy saves with only some E20/RELICS flags: assert no repeated event and correct next dialogue.
- Failed/escaped Dragonite and Ho-Oh battles: assert retry without duplicate rewards.
- Art exclusivity and GBA transparency/palette: verify asset hashes/specs and references.
- Cinematic re-entry/save reload: assert persistent completion and one-time six Master Balls.
- Existing battle edge cases: test Phoenix Soul once-only/multihit/switching and Golden Reign singles/doubles.

---

### Task 1: Lock requirements and guardian art

**Files:**
- Create `assets/pru_guardian_dragonite/{front,back,icon}.png`, `asset-lock.json`, installer and focused test.
- Modify `.github/workflows/pru-clean-build.yml` to install and validate the locked assets.
- Test `tools/pru/check_job18_assets.py`.

- [ ] Write failing checks for the exact approved SHA-256 hashes, 64x64 battle images, 32x64 icon, indexed <=16-color transparency, and reference exclusivity.
- [ ] Run the focused check and observe baseline failure.
- [ ] Copy exact attachment assets; add installer/CI integration without mutating any shared Dragonite artwork.
- [ ] Re-run asset checks and `git diff --check`.

### Task 2: Elite 20 and RELICS state-aware storyline

**Files:**
- Modify `data/maps/RuinsOfAlph_Lab_hns/scripts.inc`, `data/maps/PalletTown_Lab_hns/scripts.inc`, and Oak E20 post-battle script.
- Test `tools/pru/check_job18_story.py`.

- [ ] Test Oak's location-free reveal, E20-complete + seven-RELIC gate, and legacy save flag reconciliation.
- [ ] Run test and observe failure.
- [ ] Implement the branches without changing existing E20 rewards or battle sequence.
- [ ] Run focused story regression.

### Task 3: Mt Silver Oak and sole Golden Ho-Oh

**Files:**
- Modify `data/maps/MtSilver_SummitDay_hns/scripts.inc` and summit signs in map data.
- Modify existing Ho-Oh encounter/credits entry point only as needed.
- Test `tools/pru/check_job18_hooh.py` and existing `tools/pru/check_golden_hooh.py`.

- [ ] Add tests that summit Oak never starts a trainer battle, checks only E20 + seven RELICS, and level-100 Ho-Oh retries until caught.
- [ ] Observe failures.
- [ ] Replace the summit battle with original possessive/fatigued dialogue and a summon ceremony; remove Crest requirements while leaving unrelated Crest data intact.
- [ ] Reuse existing Job 16/17 cinematic, credits, and one-time reward path; test persistent completion and six Master Balls.
- [ ] Run focused and existing Ho-Oh regressions.

### Task 4: Unique Tin Tower Guardian Dragonite

**Files:**
- Add an internal trainer-only species identifier and record in `include/constants/species.h`, `src/data/pokemon/species_info/pjr_families.h`, and `src/data/graphics/pjr.h`.
- Modify Tin Tower Kimono Girls script and trainer roster.
- Test `tools/pru/check_job18_guardian.py`.

- [ ] Test exact type, ability, held item, level, nature, IVs, EVs, moves, non-catchable battle and non-Dex mapping.
- [ ] Observe failures.
- [ ] Add boss encounter and post-battle ceremony with retry behavior; never reference its art through regular Dragonite.
- [ ] Run focused test, existing Kimono regressions, and exact 450 roster/Dex checks.

### Task 5: Build, regression, save, changelog, release

**Files:**
- Create `assets/test_saves/PRU_Job18_Before_Ancient_Guardian.sav` and `docs/PRU_JOB18_CHANGELOG.md`.
- Update `docs/PRU_RELEASE_LEDGER.md` and build/release workflow as needed.

- [ ] Generate the save by running the Job 18 ROM to the pre-trigger position, verify party/items/flags, close/reopen mGBA and verify it reloads.
- [ ] Run focused source checks and battle-engine tests.
- [ ] Build `make hns -j2 -O`, verify ROM size/header/checksum and SHA256.
- [ ] Publish the test release only after binary and save verification; report exact URLs and evidence, and list untested paths plainly.
