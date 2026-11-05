# Fortotoise Gigantamax Blastoise asset source

- Approved design: blue Blastoise with a huge dark fortress shell containing multiple cannons.
- Front: the PRL PR72-approved fortress-shell G-Max Blastoise `source_front.png` (96×96; 14 opaque colours), selected from the back-facing G-Max sprite and mirrored to match the owner's reference. It is resized to 64×64 with nearest-neighbour pixels and indexed without invented/recoloured artwork.
- Back: the separate, authentic 64×64 back-view artwork from the PRL Mercury G-Max Blastoise donor pack (`source_back.png`), preserved without cropping, flipping, scaling or changing its silhouette. Its small donor palette differences are snapped to the front's existing 16-colour GBA palette.
- Both battle views use the exact shared indexed colours in `normal.pal`; palette index 0 is transparent.
- Party/PC icon (Job 13 player choice): original Gigantamax Blastoise sprite from `msikma/pokesprite` (`pokemon-gen8/regular/blastoise-gmax.png`), pinned as `pokesprite_gmax_icon_source.png`. The approved candidate `pokesprite_gmax_icon_GBA_pal3.png` is a centred 32x64 two-frame indexed GBA icon on shared icon palette #3, installed as `icon.png`. Never revert to Mega Blastoise on a clean build.
- Job 13 has changed the icon only; existing Job 12 front/back remain pending comparison with the uploaded PRL PR72 ROM and player visual approval. No bulk sprite edits.
- `source_back.png` is authoritative for the back sprite; `back_source_crop.png` is obsolete and must not be installed.
- The former red-bellied/front-facing candidate is not installed.
- No authentic shiny palette is supplied or required. Fortotoise retains its existing pinned shiny palette.

- Source: PokeAPI Pokémon #10197 back battle sprite, horizontally mirrored to match the PRL PR72 ROM screenshot. Source provenance is PokeAPI, not a binary extraction from the supplied ROM.
- The PR72 screenshot/rear-facing design is the authority; do not substitute the red-bellied front-facing sprite.

- Original PRL back donor: `/Pokémon Relic Legacy/Sprite Resources/Mercury/Mercury_GMax_Blastoise_Charizard_Eevee_Full_Donor_Pack.zip` → `Mercury_Gigantamax_Blastoise_Donor/Gigantamax_Blastoise_back_normal_64x64.png`; SHA-256 `4c9b04650c8c174846e533b09caf1e6e9dcaab590324f3a34c485712e2cc6e49`.
- This source comes from the PRL artwork archive; it is not claimed to be a binary sprite extraction from PR72.
