# Crystal Advance Redux: all 38 PRU battle backgrounds

Source: approved PRU Library archive `PRU_Crystal_Advance_Redux_38_Backgrounds_GBA_Ready.zip`, dated 2026-10-17.

* Original LZ77 4bpp tiles, 4096-byte tilemaps and 48-colour palettes imported unchanged for indices 00-37.
* 16 Johto/Kanto Gym Leaders get their own fixed scenery (including rematches).
* Maps choose stable environment-matching variants from all 38 source backgrounds.
* BG3 shows complete tiles + map + three palettes, eliminating mismatched halves.
* During battle-entry slides the original safe GBA intro curtain is retained on BG1/BG2; donor entry_* files remain archived but deliberately aren't displayed to prevent PRL's split/join artifact.
* Link/Frontier/forced test battles retain the original terrain renderer.
* No Pokémon data, save format, roamer or event-script changes.

Automation: `python3 tools/pru/check_crystal_battle_backgrounds.py`.
