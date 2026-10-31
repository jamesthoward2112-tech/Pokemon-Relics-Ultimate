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
- Five-species checkpoint `c0d98e67df00e1b1340c7b4fb3f851e922bf328a` compiled and published successfully.
- Recovered the exact Radical Red 4.1 Seviian Noibat/Noivern front, back, icon, normal and shiny palette bytes from the official UPS expansion; no base ROM or generated artwork was used.
- Replaced the existing Noibat/Noivern slots with Rock/Ghost stats, Levitate/Rock Head/Sturdy, their RR level-up sets, level-36 evolution and a Dark Cave South Side encounter.

## In progress

- Awaiting GitHub Actions compilation of the Seviian Noibat/Noivern milestone.

## Remaining

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
- `assets/pru_final_polish/seviian_noibat/noibat/{front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `assets/pru_final_polish/seviian_noibat/noivern/{front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `graphics/pokemon/noibat/{anim_front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `graphics/pokemon/noivern/{anim_front.png,back.png,icon.png,normal.pal,shiny.pal}`
- `src/data/pokemon/species_info/gen_6_families.h`
- `src/data/pokemon/level_up_learnsets/gen_3.h`
- `src/data/wild_encounters.json`
- `tools/pru/check_seviian_noibat.py`
- `tools/pru/check_444_species_dex.py`

## Latest successful commit

- `c0d98e67df00e1b1340c7b4fb3f851e922bf328a` (successful five-sprite source checks, compilation and release).

## GitHub Actions

- Current run: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41208617652
- Five-sprite run: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41209515617
- Status: successful; source regression, compilation, 32 MiB ROM validation, artifact upload and release publication all passed.
- Next run: pending push of the Seviian checkpoint.

## Latest successfully published ROM

- Source: `c0d98e67df00e1b1340c7b4fb3f851e922bf328a`
- Tag: `pru-build-c0d98e67df`
- Direct asset: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-c0d98e67df/Pokemon-Relics-Ultimate-c0d98e67df.gba
- Size: 33,554,432 bytes; SHA256 `a85bde3b7a754cddf40a7396eeac7be057bf3d855b82f13683db9ef1179974db`.

## Compilation errors or blockers

- No current compilation blocker.
- Seviian focused source/format/mechanics/encounter check passes locally; full compilation is delegated to GitHub Actions as required.

## Next-session instructions

1. Checkout this exact branch and read this document plus `AGENTS.md`, `PRU_HANDOFF.md` and `docs/PRU_RELEASE_LEDGER.md`.
2. Resume from the actual remote HEAD; do not reset to `d5308c8c` or create a competing branch.
3. Inspect the newest Actions run and continue from its first real failure.
4. Preserve exactly 450 species and all internal species IDs/save compatibility.
5. Commit and push an updated version of this file after every meaningful milestone.
