# PRU Kanto E4 and Dojo hotfix plan

1. **RED:** Add regression assertions for the five co-located trainer NPCs, visible dispatch, Oak's appearance, Elm's Ancient Candy, sealed Indigo door, Dojo Elite 18 and Chansey, Sinjoh Steven removal, and Eerie Fog wrap. Verify failure on baseline.
2. **GREEN:** Replace overlapping League NPCs with one variable-sprite NPC in each original room; share a single progression predicate for sprite and battle selection.
3. Add Oak's on-map farewell in the Champion's room, preserve HoF/credits, and rename the *displayed* reusable `ITEM_RELIC_CANDY` to Ancient Candy in Elm's existing gift script.
4. Remove Indigo Elite 18 NPC, place accessible Dojo Elite 18 and Chansey behind the far-right BP counter; update directions and prevent Starmie overlap.
5. Hide Steven permanently after the Stone Plate scene, leaving the Arceus-room NPC intact; fit Eerie Fog's description in two lines.
6. Run all relevant static regression tests, source checks, then GitHub Actions clean ROM build and artifact verification; publish source via an isolated feature branch/PR, deliver one raw `.gba` file.
