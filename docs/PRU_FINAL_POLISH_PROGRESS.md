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
- GitHub Actions run 41208617652 passed every source check, compiled successfully, verified the 33,554,432-byte ROM and published it.
- Verified Armaldo and Cradily against the James-locked `PHR_OdysseyII_Selected_Hoenn_Sprites.zip` and installed that exact front/back orientation.
- Installed approved PKR/PRL Kantomon Fortotoise and pinned Elite Redux Tortemple/Brontonana front, back, palette and icon artwork.
- Added a deterministic post-PRL-sync installer and regression lock; no species IDs, forms or icon-palette table entries were added.

## In progress

- Awaiting GitHub Actions compilation of the five-species sprite milestone.

## Remaining

- Replace Noibat/Noivern with authentic Radical Red Seviian Rock/Ghost artwork and mechanics; level-36 evolution; Dark Cave South Side encounter; no extra species/form switching.
- Make Golden Relic Ho-Oh the only Ho-Oh presentation across battle, icon, trainers, encounters and overworld.
- Add counterable Wonder Guard Shedinja to suitable Agatha Kanto Championship and Ghost-themed Elite 20 teams without altering aces, team sizes or progression.
- Run final source/invariant verification, compile a 33,554,432-byte ROM, publish a direct GitHub release asset and record SHA256/provenance.

## Changed files in this checkpoint

- `tools/pru/check_astrachi_jirachi_encounter.py`
- `docs/PRU_FINAL_POLISH_PROGRESS.md`
- `.github/workflows/pru-clean-build.yml`
- `assets/pru_final_polish/manifest.txt`
- `assets/pru_final_polish/fortotoise/{front.png,back.png,normal.pal}`
- `assets/pru_final_polish/torkaldera/{front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `assets/pru_final_polish/tropisaur/{front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `assets/pru_final_polish/armaldo/{front.png,back.png}`
- `assets/pru_final_polish/cradily/{front.png,back.png}`
- `tools/pru/install_final_polish_sprites.py`
- `tools/pru/check_final_polish_sprite_sources.py`
- `graphics/pokemon/prl_authoritative/fortotoise/{front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `graphics/pokemon/prl_authoritative/torkaldera/{front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `graphics/pokemon/prl_authoritative/tropisaur/{front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `graphics/pokemon/armaldo/{front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `graphics/pokemon/cradily/{front.png,back.png,icon.png,normal.pal,shiny.pal}`

## Latest successful commit

- `5f927ef0a64bc318f24a0e1391d13d1b5b445478` (successful source checks, compilation and release).

## GitHub Actions

- Current run: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41208617652
- Status: successful; source regression, compilation, 32 MiB ROM validation, artifact upload and release publication all passed.
- Next run: pending push of the five-species sprite checkpoint.

## Latest successfully published ROM

- Source: `5f927ef0a64bc318f24a0e1391d13d1b5b445478`
- Tag: `pru-build-5f927ef0a6`
- Direct asset: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-5f927ef0a6/Pokemon-Relics-Ultimate-5f927ef0a6.gba
- Size: 33,554,432 bytes; SHA256 `f055a780c8325d3d615d22fb6c5e99fce8883625de226f6baec91631e59e253e`.

## Compilation errors or blockers

- No current compilation blocker.
- Five-species focused source/format check passes locally; full compilation is delegated to GitHub Actions as required.

## Next-session instructions

1. Checkout this exact branch and read this document plus `AGENTS.md`, `PRU_HANDOFF.md` and `docs/PRU_RELEASE_LEDGER.md`.
2. Resume from the actual remote HEAD; do not reset to `d5308c8c` or create a competing branch.
3. Inspect the newest Actions run and continue from its first real failure.
4. Preserve exactly 450 species and all internal species IDs/save compatibility.
5. Commit and push an updated version of this file after every meaningful milestone.
