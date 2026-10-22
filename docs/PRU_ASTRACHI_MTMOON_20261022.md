# PRU — Astrachi second wish at Mt. Moon Square (locked 22 Oct 2026)

## Canonical behaviour
- Jirachi's existing white rock at (13,5) and its encounter in the pool at (13,11) remain intact.
- After Jirachi is **caught** (not merely seen/knocked out), using the same rock again summons the separate **Level 70 Astrachi** at exactly (13,11).
- Reuse the original Jirachi stone/camera/flash/sound/movement event beat-for-beat, with Astrachi's own text, encounter species, and overworld graphics.
- Astrachi may be captured only once. Running away leaves the object there; knocking it out removes it until next map entry, where it respawns; capture permanently hides it.
- Flag IDs `0x4E0` (hide), `0x4E1` (summoned), `0x4E2` (caught) intentionally distinguish it from Jirachi and avoid relying on their currently shared engine National Dex number.
- Save compatibility: on old PRU saves, Astrachi is hidden until specifically summoned. Jirachi catch state comes from the existing caught dex flag.
- Battle species art and stats remain existing PRU assets.

## Art source, adaptation and test notes
- Source artist: **Claude AI**. The project owner provided two Astrachi overworld sprite strips on 22 October 2026; the crisp lower image `1000042881.png` is used as the source, rather than Jirachi.
- 9 original upscaled frames: front (0,3,4), rear (1,5,6), right-facing side (2,7,8). Mirror the sides to make left-facing frames. Indexed as 16 GBA 32x32 frames, source colours preserved, background treated as transparent.
- Installed at `graphics/pokemon/astrachi/overworld.png` and `overworld_{normal,shiny}.pal`. Shiny overworld palette currently mirrors normal; never present that as unique shiny artwork.
- Static encounter always faces down, but test every cardinal direction in mGBA before accepting the overworld sprite as fully verified.
- Test both **new game** and existing saves where Jirachi is already caught. Verify stone once/both times, return after fleeing/knockout, no duplicates after capture, sprite/cry, and no regression of Jirachi.
- Source committed does not mean compiled or player-verified; check CI and artifact separately.
