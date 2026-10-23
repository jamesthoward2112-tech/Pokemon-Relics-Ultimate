# Crystal Advance Redux: all 38 PRU battle backgrounds

Source: approved PRU Library archive `PRU_Crystal_Advance_Redux_38_Backgrounds_GBA_Ready.zip`, dated 2026-10-17.

* Original LZ77 4bpp tiles, 4096-byte tilemaps and 48-colour palettes imported unchanged for indices 00-37.
* 16 Johto/Kanto Gym Leaders get their own fixed scenery (including rematches).
* Maps choose stable environment-matching variants from all 38 source backgrounds.
* BG3 shows complete tiles + map + three palettes, eliminating mismatched halves.
* BG3 remains a complete, stationary backdrop from the first battle frame until the battle concludes.
* All optional Crystal Redux entry tiles, grass/water/rock foreground sweeps and their alpha-fades are **disabled**. The donor assets remain in source control as a recovery backup but are never displayed.
* No panorama, split-screen, HBlank strips, extra palette banks or BG3 movement are introduced.
* Link/Frontier/forced test battles retain the original terrain renderer.
* The Lavender Cubone quest is a separate concurrent addition; it does not modify battle-background rendering.

Automation: `python3 tools/pru/check_crystal_battle_backgrounds.py` and `python3 tools/pru/check_static_battle_backgrounds.py`.
