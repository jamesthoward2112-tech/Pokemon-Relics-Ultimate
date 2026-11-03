# Bug Fix Specification: Ruins of Alph mGBA ladder regression

**Created:** 2026-11-03  
**Status:** Code restored; production GitHub Actions verification pending  
**Active branch:** `feat/pru-relic-hunt-20261101`  
**Reference passing source:** `400372497ed46571226c0e87cc18edd10cdebc59`  
**Last failed source:** `c15d0d3c6e2edfb277881f92b56e50dd08e6ca78`  
**Correction commit:** `d9ee4e3542449b2756070871e0604f71cfa0f4d7`

## Player outcome

The existing Ruins of Alph outside → B1F → outside → B1F map transitions must remain functional, with no alteration to game maps, ladder art, shrine objects, events, scripts or save flags just to satisfy automated testing.

## Reproduction and evidence

- CI passing run: [41656113506](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41656113506).
- CI failing run: [41663729607](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41663729607).
- The passing test starts outside at map `(24,5)`, coordinates `(21,22)`, and presses UP to enter.
- The failing test was modified to start at `(21,20)` and press DOWN for eight frames. mGBA still reported `(24,5,21,20)` when B1F `(24,6,15,16)` was expected.
- Comparing the passing and failed build revisions showed changes only to the CI workflow and `tools/pru/playtest_alph_ladder_ci.py` rather than the shipped map logic.
- The smallest correction restored the last passing ladder test script byte-for-byte. This is a test-harness correction, not proof that every existing save enters B1F correctly.

## Acceptance criteria

1. Actual mGBA EWRAM probes confirm outside `(24,5,21,22)` → B1F `(24,6,15,16)`.
2. The emulator exits to outside `(24,5,21,21)` after walking off and back onto the ladder.
3. The emulator re-enters B1F `(24,6,15,16)`.
4. Existing source regression and Golden Reign/Phoenix Soul battle-engine checks pass unchanged.
5. The production ROM builds to exactly 33,554,432 bytes with a recorded SHA-256.
6. A directly downloadable .gba asset is published before delivery is claimed.

## Protected behaviours and scope

- Do not change `src/`, map JSON, `data/`, artwork, encounter flags, species/move IDs, Golden Ho-Oh or RELICS quest data for this CI-only fix.
- Do not disable the emulator test, fake probes, change expected values to the observed failure, or bypass the release gate.
- Preserve the last known-good ROM until the new build and release have passed.
- Future proposed changes to ladder coordinates must first demonstrate a failing production warp or collision, not merely test-harness disagreement.

## Implementation and verification

- **Coded:** Restored `tools/pru/playtest_alph_ladder_ci.py` to its exact passing version from `400372497e`.
- **Pending:** CI build [41669026811](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41669026811), ROM checksum and released asset.
- **Player-tested:** Not claimed.
