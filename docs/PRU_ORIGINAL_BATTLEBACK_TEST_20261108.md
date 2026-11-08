# PRU Original Battle Backdrop Test (8 November 2026)

Test branch based on PRU Alpha 02 / PR #84 (`e3f7d626`). This is not a replacement for the official Alpha 02 release.

- **Route 29** (`MAP_ROUTE29_HNS`): original grassy countryside pixel-art battle backdrop, image generated for PRU on 8 November 2026.
- **Mt Silver entrance and first cave room** (`MAP_MT_SILVER_OUTSIDE_HNS`, `MAP_MT_SILVER_1F_WATERFALL_ROOM_HNS`): original rocky snowy-mountain/cave-entrance battle backdrop, image generated for PRU on 8 November 2026.
- Both are compiled as 4bpp BG3 tiles (<512 unique tiles each), GBA LZ77 maps/tiles and 48-colour palette banks (2–4).
- Only these maps are remapped; all 55 Rhythm backgrounds and original story/special battle scenery remain unchanged.
- The lower 48px are repeated ground tiles because the battle menu obscures this area.
- QA: GBA LZ decode, 4bpp palette and 512-tile bound checks. Full-ROM compile and emulator test are separate gates.
- This is freshly generated artwork, *not* a recolouring of unlicensed donor art.
