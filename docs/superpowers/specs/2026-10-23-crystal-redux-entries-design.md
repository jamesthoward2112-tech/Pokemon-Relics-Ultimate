# Original Crystal Redux Battle Entries — Design
Date: 2026-10-23

## Intent
Use the original Crystal Advance Redux per-environment entry art for all 38 imported PRU battle scenes. Replace the separately imported Emerald animated foreground. Preserve the approved fully assembled, stationary background from PRU #22.

## Goals
- Match every Crystal background's own `entry_tiles.4bpp.lz` and `entry_tilemap.bin.lz` to the same chosen index as its main BG3 tiles/map/palette.
- Use the existing engine BG1 battle-entry surface for temporary donor entry art; add no new renderer/layer or Emerald sprite strip.
- Keep BG3 visible from the first battle frame; no HBlank split, opposite-half horizontal scroll, panoramic joins, black gaps, or background wipes.
- Animate only temporary donor entry graphics; clean BG1 after the intro without flashes.
- Keep all 38 wild/environment variants, 16 unique Gym scenes and standard Pokémon/trainer/platform entrances.
- Link, partner, facility, forced-test and other unsupported contexts retain their known-good normal entry.
- Keep direct `.gba` publishing, with no ZIP delivery.

## Non-goals
Changing backgrounds, Pokémon, encounters, trainers, scripts, save format, or introducing new Emerald art. No new scene compositing engine.

## Constraints and trade-offs
Crystal Redux's ROM provided the 38 paired entry assets, but its original executable transition timing was not imported. Compare donor gameplay when available; re-create the safe entrance using the existing BG1 interface and per-scene donor art. Do not copy any donor motion that requires moving/splitting the settled BG3 image. BG1 temporarily showing entrance art is the existing hardware layer, not a new overlay system. Donor colours must not overwrite the BG3 palette.

## Approaches considered
1. Selected: each Crystal scene's own entry asset on existing BG1 over stationary BG3. Closest to donor artwork, keeps safe background.
2. Fully static: least risk, but loses the expressly chosen animated entrance.
3. Additional Emerald-specific foreground: rejected; has caused upward sweep/flash and mismatched art.

## Acceptance
All 38 scene IDs resolve both entry and settled artwork; the selected pair cannot differ. Grass/water/sand/rock and gym/indoor cases show no BG3 movement or seams. Entries finish cleanly and ordinary battle UI/animation recovers. Existing build/source regressions and a complete 32 MiB ROM compile pass. Actual emulator visual QA remains a distinct gate.
