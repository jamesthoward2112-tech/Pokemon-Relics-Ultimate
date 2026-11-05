# PRU Job 14 — Gemlin + Scarabub approved baby-sized artwork

**Baseline:** accepted Job 13 ROM `3ed448c20afb1659b6580849a93662dd4387e308`. Do not merge rejected Job 10 artwork.

## Gemlin (signed off in chat)
- **Front:** exact GBA-indexed artwork from the *original ChatGPT pre-PoryPal generation*, 32×34 visible pixels on a 64×64 transparent indexed canvas.
- **Back:** corresponding original rear drawing, flipped horizontally on player request so the crystal appears on back-left, 31×33 pixels. Not a mirrored front.
- **Icon:** original 18×21 two-frame sprite, 32×64 indexed canvas.
- **Palette:** same 16-colour normal and shiny palettes supplied with the approved conversion. The icon uses its original exact purple/blue palette by a dedicated, lazy-loaded per-species entry at index 16 rather than distorting it through the six shared palettes.
- **Source checksums:** pinned under `assets/pru_approved_babies/gemlin`; `tools/pru/check_job14_baby_sprites.py` verifies SHA-256 for every file.

## Scarabub (Heracross baby; official name unchanged)
- **Original:** front 60×54 and back 60×56 occupied pixels.
- **Updated front:** 44×40 pixels.
- **Updated back:** 44×41 pixels.
- **Method:** original indexed pixel art reduced with BOX sampling and a nearest-original-palette snapping pass, not arbitrary additional resize in every build. All original blue, yellow-eye, red-mouth, dark outline colours are retained.
- **PC/party icon:** original two-frame indexed pixels unchanged. The species previously selected icon palette 0 (yellow) with P_GBA_STYLE_SPECIES_ICONS off despite its artwork using the blue palette 3. Changed its `.iconPalIndex` to 3, matching the exact PNG palette.
- **No species names, evolution data, stats, moves, story or save structure changed.**

## Build ordering
The older video review installer is preserved only as the baseline prior stage. **`tools/pru/install_approved_baby_sprites.py` runs after that installer** and re-pins only Gemlin and Scarabub, before source/ROM compilation. No unrelated species are rescaled or re-palette-mapped in this job.

## Verification
- `python3 tools/pru/check_job14_baby_sprites.py` — exact approved assets, dimensions, palette indices, original Gemlin colours and Scarabub blue icon palette.
- `python3 tools/pru/check_job13_pr72_sprite_extract.py` — preserves user-approved PR72 Fortotoise front/back and Pokésprite icon.
- `python3 tools/pru/audit_custom_sprites_70.py` — source audit, with ROM 4bpp comparison and mGBA boot verified in CI.
- Enlarged pixel-perfect QA image: `docs/PRU_Job14_Gemlin_Scarabub_Sprite_Comparison.png`.

Manual in-game visual check of the reduced Scarabub face and Gemlin in PC/battle is recommended, though source integrity is verified automatically.
