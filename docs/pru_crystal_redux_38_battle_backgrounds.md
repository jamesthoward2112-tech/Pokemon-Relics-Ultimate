# Crystal Advance Redux: all 38 PRU battle backgrounds

Source: approved PRU Library archive `PRU_Crystal_Advance_Redux_38_Backgrounds_GBA_Ready.zip`, dated 2026-10-17.

* Original LZ77 4bpp tiles, 4096-byte tilemaps and 48-colour palettes imported unchanged for indices 00-37.
* 16 Johto/Kanto Gym Leaders get their own fixed scenery (including rematches).
* Maps choose stable environment-matching variants from all 38 source backgrounds.
* BG3 shows complete tiles + map + three palettes, eliminating mismatched halves.
* BG3 remains a complete, stationary backdrop from the first battle frame, including during entrance animations.
* The original matching `entry_tiles.4bpp.lz` and `entry_tilemap.bin.lz` are loaded on BG1 for the 14 donor scenes with genuine entrance artwork (indices 00, 01, 03, 04, 05, 07, 14, 15, 19, 22, 23, 24, 25, 36).
* These BG1 entry assets slide **down** into position, pause, then alpha-fade out before BG1 is released for battle animations. The other 24 scenes contain blank or placeholder entry graphics, so they start with static backgrounds and no overlay.
* The abandoned Emerald foreground overlay is no longer loaded; no panorama, split-screen, HBlank strips, extra palette banks or BG3 movement are introduced.
* Link/Frontier/forced test battles retain the original terrain renderer.
* No Pokémon data, save format, roamer or event-script changes.

Automation: `python3 tools/pru/check_crystal_battle_backgrounds.py` and `python3 tools/pru/check_crystal_entry_transitions.py`.
