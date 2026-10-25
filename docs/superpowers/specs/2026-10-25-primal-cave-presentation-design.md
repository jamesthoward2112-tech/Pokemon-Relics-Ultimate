# PRU Primal cave presentation

## Intent

The Seafoam Kyogre finale must show deep blue water, rain and a shiny Primal Kyogre overworld after Archie loses. Archie must reserve the Blue Orb shiny Kyogre for his final party slot, with a powerful coherent rain moveset. The corresponding future Groudon scene must use matching shiny Primal battle and overworld sprites with the Red Orb.

## Boundaries

- Preserve the already-restored Seafoam map layout, walkability, exit, dialogue, and encounter flags.
- Scope the water palette to this cave, not Blackthorn Gym or other maps.
- Reuse the existing `graphics/pokemon/{kyogre,groudon}/primal` sprite and palette assets; do not redraw.
- Keep the capture-only permanent removal and KO/whiteout respawn behavior.
- Verify source regressions and GitHub clean ROM build before releasing.

## Approach

Use a cave-specific palette clone of the Blackthorn Gym secondary tileset, and register new 64×64 Primal overworld event graphics using the shipped six-frame sprite sheets and shiny palettes. This retains map geometry and avoids global palette changes. Other approaches (replacing the cave with a donor layout, changing Blackthorn's global palette, or using a regular Kyogre icon) would regress prior approved behavior or the desired art.
