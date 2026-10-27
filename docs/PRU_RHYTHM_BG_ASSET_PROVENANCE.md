# Pokémon Rhythm battle backgrounds in PRU

**Active from 25 October 2026:** The original Pokémon Rhythm 1.0.0 battle
backdrops replace Crystal Advance Redux in ordinary PRU battles. James Howard
states he has permission from Rhythm and the relevant artists to use these
graphics, including publishing them in the public PRU repository. The original
38 Crystal Redux assets remain archived for rollback.

## Source and transformation

- Source: the user-supplied `Pokemon Rhythm.ups` patch, reconstructed privately
  with the user's clean FireRed ROM. The clean ROM, donor ROM, and UPS patch are
  **not** bundled with this repository.
- Original Rhythm patched-ROM CRC32: `51625488`; UPS CRC32: `5eb94b0c`.
- Extracted scene count: **55** (indices 00–54), comprising **44 distinct
  original source sets** and **43 unique visible 240×160 images**. Rhythm
  entries 00 and 33 differ only in content outside the rendered viewport.
- Original identical entry pairs: 01/15, 07/47, 08/12, 10/21, 11/22,
  13/23, 14/24, 16/25, 17/26, 18/27 and 19/29. These point to a single
  canonical asset per pair in the compiled ROM while retaining every index.
- Files: `graphics/battle_environment/rhythm/00` through `54`, with 4bpp
  GBA LZ77 tiles, 4096-byte tilemaps and original 96-byte (48-colour) palettes.
  `assets/pru_rhythm/background_manifest.json` records hashes per scene.
- GBA optimisation: the 30×20 visible tile viewport is repacked to drop only
  unused offscreen tiles; map cells outside the viewport are blanked, with no
  visible pixels, tile flips, or palette banks altered. Every decompressed
  tile set fits entirely between BG3's charblock 2 and screenblock 26.

## Battle selection

Ordinary battles deterministically choose from Rhythm scenery pools for grass,
water, caves, rocks, snow, urban/interior, volcano and burial-ground settings.
All 55 source indices are covered. Special fixed story backdrops:

| Place or opponent | Rhythm index | Scene |
| --- | ---: | --- |
| Seafoam secret cave, Archie / Kyogre | 48 | Ocean waves in a rock inlet |
| Mt Silver Moltres room, Groudon | 16 | Underground lava |
| Lavender Spirit Tower, all seven floors | 44 | Haunting standing stones |

Every Gym Leader (including rematches) has one fixed, different background:

| Johto | Index | Kanto | Index |
| --- | ---: | --- | ---: |
| Falkner | 00 | Brock | 35 |
| Bugsy | 43 | Misty | 48 |
| Whitney | 08 | Lt. Surge | 46 |
| Morty | 44 | Erika | 09 |
| Chuck | 45 | Janine | 31 |
| Jasmine | 30 | Sabrina | 19 |
| Pryce | 14 | Blaine | 16 |
| Clair | 41 | Blue | 51 |

The intro remains a single static BG3 backdrop without split panels, HBlank
scrolling, black-square entry effects or Crystal Redux foreground curtains.
Link battles, Battle Frontier and forced test environments continue using the
engine's original background fallback. The legacy
`IsPruCrystalBattleBgActive()` function name remains for the static-intro
hook consumed elsewhere in PRU; it now detects active Rhythm backgrounds.

## Reproduction and validation

```sh
python3 tools/pru/check_rhythm_battle_background_assets.py
python3 tools/pru/check_rhythm_battle_backgrounds.py
python3 tools/pru/check_static_battle_backgrounds.py
```

The deterministic importer `tools/pru/import_rhythm_battle_backgrounds.py`
can regenerate the imported assets when given the verified private extraction
directory. It does not require or redistribute any copyrighted base ROM.
