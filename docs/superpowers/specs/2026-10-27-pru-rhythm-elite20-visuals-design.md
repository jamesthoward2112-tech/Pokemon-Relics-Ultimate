# PRU Rhythm-only battle visuals and Elite 20 duo intros — approved design

## Intent

Every normal PRU battle uses a Pokémon Rhythm background, with the 20 Elite 20 double-battle rounds assigned individual, thematic Rhythm scenes. Do not use Crystal Redux in the compiled game. Give the final four duos the previously approved cinematic art while preserving the working Jessie & James and Steevee & Neevee intros. The user's existing save remains playable, and the separate E4 repair on PR #55 is not modified.

## Approved 20-round mapping

| Round | Pair | Rhythm archive scene ID | Theme |
|---|---|---|---|
| 01 | Brock & Roxanne | 35 | Rocky canyon |
| 02 | Misty & Wallace | 48 | Ocean cliffs |
| 03 | Lt. Surge & Wattson | 46 | Electric grid |
| 04 | Erika & Bugsy | 34 | Flowering forest |
| 05 | Janine & Koga | 39 | Shadowy jungle |
| 06 | Sabrina & Will | 19 | Psychic arena |
| 07 | Blaine & Flannery | 16 | Lava cavern |
| 08 | Jasmine & Clair | 45 | Stone arena |
| 09 | Lorelei & Glacia | 14 | Snowy pass |
| 10 | Bruno & Chuck | 08 | Fighting stadium |
| 11 | Agatha & Phoebe | 18 | Graveyard |
| 12 | Karen & Sidney | 38 | Dark arena |
| 13 | Lance & Drake | 30 | Mountain bridge |
| 14 | Steevee & Neevee | 42 | Pink meadow |
| 15 | Jessie & James | 49 | Rocket facility |
| 16 | Maxie & Archie | 54 | Lava-and-water cavern |
| 17 | Steven Stone & May | 41 | Golden hall |
| 18 | Player-named rival Silver & Giovanni | 36 | Earth cave |
| 19 | Red & Blue | 13 | Mt. Silver snowy forest |
| 20 | Professor Oak & Professor Elm | 00 | Bright sky meadow |

All twenty choices are distinct original Rhythm scene IDs. The archive has 55 scenes but only 44 unique images; avoid importing duplicated graphics twice. The donor pack is `Pokemon_Rhythm_Battle_Backgrounds_Extracted.zip` in the user's ChatGPT Library, whose `rhythm/raw/NN/` entries supply compressed 4bpp tiles, maps, three-palettes and entrance assets.

## Global battle environment behavior

- **Existing baseline (verified in upstream PR #55 at `250c30afdff209615f2f1ae3475da9c59a08009c`):** The complete 55-entry / 44-unique Rhythm set is already imported and wired globally in `src/battle_bg.c`, with Crystal graphics excluded from the production graphics include and tests in `tools/pru/check_rhythm_battle_backgrounds.py`. Reuse this implementation; do not reimport, overwrite or rename it.
- Preserve the established battle background loading pipeline, but route normal wild/trainer environments to compatible Rhythm scenes. Use additional suitable Rhythm scenes beyond the twenty special selections to vary grass, cave, ocean, snow, volcano, indoor, and urban maps.
- Select a special scene for an Elite 20 trainer pair using both opponent IDs; never change normal solo battle backgrounds just because the same character appears elsewhere.
- Do not change Frontier, link, multi-partner, or forced test environments, and keep the normal GBA platform and foreground layers intact. Inspect GBA palette bank 2 usage, BG3 tiles/maps and BG1 entrance layers so magenta transparent areas never appear on screen.
- Preserve map-specific scene exceptions such as Archie/Kyogre, but use Rhythm equivalents.
- Crystal Redux code and art can remain in source history as a reversible backup, but the release binary must not link or display Crystal Redux imagery.

## Battle entrances

- Keep the existing Jessie & James and Steevee & Neevee 4bpp assets and PRL transition logic unchanged.
- Use existing paired trainer mugshots for rounds 1–13 and 16 until dedicated intros are approved, rather than generating unrelated artwork.
- Preserve already implemented Red & Blue and Oak & Elm custom duo transitions; verify dimensions, palette and native widescreen composition on GBA.
- Add GBA-ready BG0 transition art for Steven Stone & May and Silver & Giovanni, using the two artwork files approved by the user. Their high-resolution references are 2172×724 pixels; the deliverable uses the existing transition system's 128×256 tile atlas, 32×32 tilemap and 16-colour palette bank 13, visible across the GBA 240×160 window.
- The Silver/Giovanni art contains **no fixed character name**, as the rival is named by the player. Never add a baked-in `SILVER` caption.

## Elite 20 integration and independence

- Elite 20 is **20 double battles** at the Saffron Fighting Dojo, three Pokémon for each partner; do not move it to Indigo Plateau. Normal Indigo access and E4 seal belong to PR #55, not this graphics feature.
- Current source still calls the 18-round sequence `Elite18`; adding rounds 17/18 for Steven/May and Silver/Giovanni must preserve the old Red/Blue and Oak/Elm trainer IDs by moving their **presentation order** to rounds 19/20, not corrupting saved trainer defeats or item flags. Preserve all existing flags and save layout.
- Work in an isolated branch, initially independent of PR #55. Rebase/integrate onto the verified E4 branch once it is ready, resolve conflicts deliberately and rerun tests.

## Approaches

- **Approved: separate Rhythm renderer/assets and pair-override table.** Maintain donor provenance, clean rollback and source tests while excluding Crystal assets from the build. Slightly more implementation work, but avoids accidentally mixing old and new graphics.
- Rejected: overwrite the existing Crystal tables in place. Fewer edits initially, but confusing asset names and high risk of accidental Crystal leftovers.

## Verification and release boundaries

- Source tests: verify all 20 exact mappings, all scene blobs and unique artwork checksums, global Rhythm routing, and no active Crystal references; verify original two PRL intros byte-identical.
- Runtime: mGBA scene smoke tests including wild land, cave, water, specific E20 pairs, and four custom intros. Verify trainer mugs, palette and player platforms do not glitch.
- Full GBA build: check clean `make hns`, ROM header and file size, and save compatibility assumptions. Never claim gameplay was tested where only scripts were inspected.
- Do **not** publish a ROM until E4/tutor work is integrated and the resulting ROM passes runtime checks. The final deliverable must be a directly downloadable `.gba`, never a ZIP or patch.
