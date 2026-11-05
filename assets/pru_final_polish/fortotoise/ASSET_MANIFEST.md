# Fortotoise Gigantamax Blastoise asset source

- Approved design: blue Blastoise with a huge dark fortress shell containing multiple cannons.
- Front: the PRL PR72-approved fortress-shell G-Max Blastoise `source_front.png` (96×96; 14 opaque colours), selected from the back-facing G-Max sprite and mirrored to match the owner's reference. It is resized to 64×64 with nearest-neighbour pixels and indexed without invented/recoloured artwork.
- Back: the top 70% of that same approved image (`back_source_crop.png`, 96×67), reduced to 64 pixels wide and grounded in a transparent 64×64 frame.
- Both battle views use the exact shared indexed colours in `normal.pal`; palette index 0 is transparent.
- Party/PC icon: the existing official Mega Blastoise icon in `icon.png`, indexed to palette #2. This is not derived from the battle art.
- `source_back.png` is retained as historical provenance only. It is not used by the installer.
- The former red-bellied/front-facing candidate is not installed.
- No authentic shiny palette is supplied or required. Fortotoise retains its existing pinned shiny palette.

- Source: PokeAPI Pokémon #10197 back battle sprite, horizontally mirrored to match the PRL PR72 ROM screenshot. Source provenance is PokeAPI, not a binary extraction from the supplied ROM.
- The PR72 screenshot/rear-facing design is the authority; do not substitute the red-bellied front-facing sprite.
