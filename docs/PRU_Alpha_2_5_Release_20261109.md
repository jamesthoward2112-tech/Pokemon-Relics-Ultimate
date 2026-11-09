# Pokémon Relic Ultimate — Alpha 2.5
Release base: original Alpha 02 (commit e3f7d626403897cb129947189478815c7d9a09ea), retaining existing story and gameplay changes.

## Changes from Alpha 02
- Twelve PRU-original GBA-compressed battle backgrounds replace prior donor background selections across 55 historic artwork slots.
- 198 location-specific route, town, cave, terrain and weather assignments, with broader shared-biome fallback elsewhere.
- All sixteen Johto and Kanto Gym rooms and leader/rematch opponents have location-appropriate original background assignments.
- Elite Four and 20 E20 pair battles have original background assignments.
- Cave systems keep the same backdrop throughout their floors (Union Cave, Mt Mortar, Ice Path, Whirl Islands, Dragon's Den).
- Mt Silver trainer battles retain the rocky mountain backdrop; Golden Ho-Oh alone gets the sacred sunset summit.
- Previous black-artifact fix is retained using valid GBA gbagfx LZ compression and 4bpp banks.
- Mootiny pixel art and palette restored from Alpha 02 to avoid unrelated sprite changes from testing branches.

## Save compatibility
No deliberate changes to Pokémon save structures, Trainer flags or item IDs. Use a backup of the original emulator battery .sav file. When using a differently named ROM in Pizza Boy, ensure the existing .sav is copied/renamed to match the new ROM base filename if the emulator does not automatically find it.

## Release identity
Public download filename: Pokemon Relic Ultimate - Alpha 2.5.gba
Alpha 02 download remains separately available. This release does not claim 50 unique backgrounds: 12 approved source artworks are deliberately reused by area. The illustrated battle background guide is a style reference, not a literal asset inventory.

## Validation gates
Compile to a 33,554,432-byte GBA ROM; preserve sprite and source regression checks; mGBA startup and save/load check; publication only after success. Visual verification of every battle type is not automatically guaranteed by mGBA boot checks.
