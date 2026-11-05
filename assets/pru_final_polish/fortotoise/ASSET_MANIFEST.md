# Fortotoise — user-approved PRL PR72 direct extraction

- **Authoritative ROM:** `PRL_PR72_Kanto_Champion_Dialogue_20261014.gba`, 32 MiB, SHA-256 `57fac7dd5a4c859ada1612e796b17e9b549a711f80d0fb8fcd523fa03c502c4e`.
- **Front:** `PR72_Fortotoise_front.png`, exact 64×64 indexed pixels decoded from original ROM compressed `0x8BEFB0` payload. No scaling, mirroring or recolouring. Raw 4bpp SHA-256: `fc76447d81a19214d2d2d75284c6bbffbca771eaae46f0ec7d9281b090ac6c6f`.
- **Back:** `PR72_Fortotoise_back.png`, exact 64×64 indexed pixels decoded from original ROM compressed `0x8BEBFC` payload. No scaling, mirroring or recolouring. Raw 4bpp SHA-256: `1763c8dc5a151c66c0b3c66d342d565f5a4c0ef258764eb718a906015d3bb36d`.
- **Battle palette:** Original 16-entry normal palette from ROM `0x8BEF90`. Shiny palette similarly from original ROM `0x8BEBDC`; matching palette indexes are essential to preserving the exact pixels and shiny colours.
- **Party/PC icon:** User-selected standard Gigantamax Blastoise from `msikma/pokesprite`, original `pokemon-gen8/regular/blastoise-gmax.png` (68×56). The converted 32×64 two-frame 4bpp icon is `pokesprite_gmax_icon_GBA_pal3.png`; existing palette 3, reserved transparency at index 0. This is not from PR72 and is intentionally a separate approved source.
- `front.png`, `back.png`, `normal.pal`, `shiny.pal`, and `icon.png` are generated/copied by `tools/pru/prepare_user_fortotoise.py` and installed after PRL sync via `tools/pru/install_final_polish_sprites.py`.
- The previous PokeAPI 96×96 `source_front.png` and Mercury donor `source_back.png` are **retired** historical files. Do not use them to generate Fortotoise artwork.
- **Scope is ONLY Fortotoise.** No Job 10 mass sprite resizing/icons, no other species; Job 12 is the gameplay baseline.
- Verified by `tools/pru/check_job13_pr72_sprite_extract.py` and `tools/pru/check_job13_fortotoise_icon.py`; direct PR72 raw 4bpp SHA checks guarantee image fidelity.
