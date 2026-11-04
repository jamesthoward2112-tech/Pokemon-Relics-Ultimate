# Fortotoise Gigantamax Blastoise asset source

- Approved design: blue Blastoise with a huge dark fortress shell containing multiple cannons.
- Front: the project owner's supplied `source_front.png` (182×180; 14 opaque colours). It is resized to 64×64 with nearest-neighbour pixels and indexed without invented/recoloured artwork.
- Back: the top 70% of that same supplied image (`back_source_crop.png`, 182×126), reduced to 64 pixels wide and grounded in a transparent 64×64 frame.
- Both battle views use the exact shared indexed colours in `normal.pal`; palette index 0 is transparent.
- Party/PC icon: the existing official Mega Blastoise icon in `icon.png`, indexed to palette #2. This is not derived from the battle art.
- `source_back.png` is retained as historical provenance only. It is not used by the installer.
- The former PokeAPI candidate is retained as `source_front_previous.png` in Git history only; it is not installed.
- No authentic shiny palette is supplied or required. Fortotoise retains its existing pinned shiny palette.
