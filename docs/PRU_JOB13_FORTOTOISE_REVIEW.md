# PRU Job 13 — Fortotoise front + back from PR72, Pokésprite G-Max icon

**Approved player direction (5 November 2026):** Both Fortotoise battle sprites come directly from the uploaded PRL PR72 ROM; preserve the separate previously selected Pokésprite G-Max icon. No changes to any other species.

- **Gameplay baseline:** Job 12 `3ecca7c4300bd4813a9a8db7e171ed773907b910`.
- **ROM:** `PRL_PR72_Kanto_Champion_Dialogue_20261014.gba`, 32 MiB, SHA-256 `57fac7dd5a4c859ada1612e796b17e9b549a711f80d0fb8fcd523fa03c502c4e`.
- **Front:** exact ROM-extracted sprite `assets/pru_final_polish/fortotoise/PR72_Fortotoise_front.png`, source compressed graphic at 0x8BEFB0.
- **Back:** exact ROM-extracted sprite `assets/pru_final_polish/fortotoise/PR72_Fortotoise_back.png`, source compressed graphic at 0x8BEBFC.
- **Colours:** exact original PR72 normal and shiny 16-colour palettes. Indexed GBA raw payloads are verified byte-equivalent by SHA-256, no resizing, mirroring, crop or recolour.
- **Icon:** `assets/pru_final_polish/fortotoise/pokesprite_gmax_icon_GBA_pal3.png` from Pokésprite, 32×64 2-frame pal3; no Mega Blastoise fallback.
- **Build source:** `tools/pru/prepare_user_fortotoise.py` now pins PR72 direct extractions and restores exact graphics in clean builds; `install_final_polish_sprites.py` copies both battle palettes and only the existing Fortotoise icon while leaving all other sprites alone.
- **Verification:** `python3 tools/pru/check_job13_pr72_sprite_extract.py` and `python3 tools/pru/check_job13_fortotoise_icon.py` run in CI before compiling.
- **Playtest:** mGBA boot test verifies ROM health; a manual in-battle preview of front/back and PC icon remains useful for final QA.
