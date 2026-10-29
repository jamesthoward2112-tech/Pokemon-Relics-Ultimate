# Rhythm Battle Backgrounds Design

## Intent

Replace PRU's 38 active Crystal Redux battle backgrounds with **all 55 Pokémon Rhythm entries** at the user's request. The user states that permission from the Rhythm team and the relevant artists is already held. Keep original Crystal Redux source files for rollback, not active loading.

## Requirements

- Preserve the complete visible Rhythm scene, its tilemap and original 48-colour palette; use no combined/split scene, foreground curtain, BG3 scrolling or black-square introductory transition.
- Keep the existing static battle renderer, normal battle menus and GBA-compatible VRAM layout. Link/Frontier/forced test battles retain their existing fallback.
- All 55 Rhythm indices must be reachable through stable environment/map selection or named Gym Leader choices. Duplicate entries from the source are intentional: 55 positions, 44 unique sets.
- Assign a unique appropriate backdrop to each of Johto and Kanto's 16 Gym Leaders, including rematches. Use water/rock/ghost/lava themes in special encounters (Kyogre cave, Lavender Spirit Tower, Blaine/Groudon).
- Validate all assets after import, including GBA LZ77, 4096-byte maps, 96-byte palettes, 4-byte alignment, tile indices and 20480-byte BG3 tile-memory ceiling; compare the rendered 240×160 viewport pixel-for-pixel with the donor.
- Preserve unused Crystal Redux files and other PRU content. Document artwork source, permission attestation and index mapping.

## Design choices

- Keep each donor index 00–54, but alias the 11 exact repeats in compiled pointer tables to avoid storing duplicate ROM payloads twice.
- Optimise tile sets into the visible 30×20 tile viewport, remapping tile indices and leaving the offscreen 64×32 tilemap area blank. This removes unused donor tiles and guarantees fit into BG3 memory without changing any on-screen pixels.
- Check in GBA-ready compressed tiles/maps and raw palettes alongside a deterministic import/test script; do not bundle the source FireRed or reconstructed Rhythm ROM in PRU.
- Use one new `sPruRhythmBattleBgs[55]` table and fixed selection pools, retaining `IsPruCrystalBattleBgActive()` only as a compatibility-named static-viewport hook for existing intro code.

## Scope boundaries

No changes to Pokémon sprites, battle moves, scripted quests, gym teams or battle transitions beyond the background selection/asset references. No active Crystal Redux art after successful import. Original donor entry/foreground animation assets are not displayed because the user explicitly prefers a single static backdrop.

## Verification

The dedicated Rhythm test inspects 55 assets, all 55 reachable entries, 16 distinct Gym choices, viewport fidelity, VRAM safety and static transition rules. The canonical GitHub Actions source build must still compile a direct 32 MiB `.gba` artifact before rollout is reported complete.
