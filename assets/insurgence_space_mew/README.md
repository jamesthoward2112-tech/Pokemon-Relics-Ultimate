# Space Mew sprites for PRU Mew (22 October 2026)

The battle appearance of SPECIES_MEW is replaced with Pokémon Insurgence's Space Mew form, not added as a new species. No species IDs, mechanics, evolution, encounter or Mewsion assets are changed.

Provenance: the user's saved ChatGPT Library archives `Insurgence images.zip` and `Insurgence_TRS_Custom_Sprite_Library.zip` both contained identical Space Mew RPG Maker originals:
- normal front: `151_1.png`
- normal back: `151b_1.png`
- shiny blue front: `151s_1.png`
- shiny blue back: `151sb_1.png`

The originals are 192x192 at 2x pixel scale. Prepared GBA graphics use a 64x64 canvas, 16-colour indexed PNGs (15 colours including transparency), and a shared colour-index image with separate pink normal / blue shiny palettes. The 32x37 front is kept at its natural pixel size; back art (native 68x40) is proportionally reduced to 63x37. The front battle sheet duplicates the same frame to honour the game's two-frame sprites and avoid stale vanilla animation frames. Both GBA-style and alternate sprite branches use these files.

Assets: `graphics/pokemon/mew/anim_front[_gba].png`, `back[_gba].png`, `normal[_gba].pal`, `shiny[_gba].pal`.
The existing Mew party icon and overworld art are deliberately retained until explicitly approved replacement artwork exists. Credit the Insurgence community sprite artists if redistribution is planned; source availability does not establish redistribution permission.

Quality gate: `python3 tools/pru/check_insurgence_space_mew.py`.
