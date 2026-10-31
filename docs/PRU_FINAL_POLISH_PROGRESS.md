# PRU Final Polish Progress

Updated: 2026-10-31
Branch: `feat/pru-locked-gmax-charaxis-polish-20261031`
Original branch base: `d5308c8c239207130291378f3d0b8c28d2883650`

## Completed

- Resumed the existing branch at `19a5f364cd2831fb40791286e6c599a5364e034d`; no replacement branch or restart.
- Confirmed the clean-build workflow installs `tools/pru/install_charaxis_gmax_relic.py` and `tools/pru/install_approved_relic_palettes.py` after PRL asset synchronisation.
- Confirmed the latest workflow reached source regression tests with 450 species and preserved the approved Charaxis/relic-palette installation steps.
- Root-caused Actions run 41207838869: `tools/pru/check_astrachi_jirachi_encounter.py` still expected obsolete Astrachi dex number 443 after the family-order reorganisation.
- Updated the Astrachi regression assertion and message to canonical display number 449 without changing its internal species ID.

## In progress

- Re-running source regression checks and GitHub Actions compilation after the Astrachi test correction.

## Remaining

- Resolve any subsequent source or compilation failures while preserving approved work.
- Replace Fortotoise, Torkaldera/Tortemple and Tropisaur/Brontonana with their documented approved authentic donor artwork.
- Verify the recovered historical Hoenn Relics Odyssey II Armaldo and Cradily alternatives before installing them.
- Replace Noibat/Noivern with authentic Radical Red Seviian Rock/Ghost artwork and mechanics; level-36 evolution; Dark Cave South Side encounter; no extra species/form switching.
- Make Golden Relic Ho-Oh the only Ho-Oh presentation across battle, icon, trainers, encounters and overworld.
- Add counterable Wonder Guard Shedinja to suitable Agatha Kanto Championship and Ghost-themed Elite 20 teams without altering aces, team sizes or progression.
- Run final source/invariant verification, compile a 33,554,432-byte ROM, publish a direct GitHub release asset and record SHA256/provenance.

## Changed files in this checkpoint

- `tools/pru/check_astrachi_jirachi_encounter.py`
- `docs/PRU_FINAL_POLISH_PROGRESS.md`

## Latest successful commit

- Previous branch HEAD: `19a5f364cd2831fb40791286e6c599a5364e034d` (workflow failed before compilation).
- Current checkpoint commit: pending.

## GitHub Actions

- Current run: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41207838869
- Status: failed at obsolete Astrachi `#443` source assertion; compilation steps were skipped.

## Latest successfully published ROM

- Source: `401214913d3809a5e82f565bce9553f9a438a1fd`
- Tag: `pru-build-401214913d`
- Status: direct 32 MiB GitHub `.gba` published; player validation incomplete. This predates final-polish work.

## Compilation errors or blockers

- No compiler error reached yet for the current branch.
- The latest run stopped at `assert "443,Astrachi,astrachi,SPECIES_ASTRACHI" in dex`; canonical CSV places Astrachi at display number 449.
- Armaldo and Cradily historical alternatives require identity verification before installation.

## Next-session instructions

1. Checkout this exact branch and read this document plus `AGENTS.md`, `PRU_HANDOFF.md` and `docs/PRU_RELEASE_LEDGER.md`.
2. Resume from the actual remote HEAD; do not reset to `d5308c8c` or create a competing branch.
3. Inspect the newest Actions run and continue from its first real failure.
4. Preserve exactly 450 species and all internal species IDs/save compatibility.
5. Commit and push an updated version of this file after every meaningful milestone.
