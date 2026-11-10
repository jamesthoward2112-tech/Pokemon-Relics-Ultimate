# PRU expanded battle backgrounds — Alpha 2.5 follow-on

22 separately illustrated scenes (12 previously approved PRU scenes + 10 CC0 original RPG illustrations), not palette swaps.

**New artwork source:** Nidhoggn, *Backgrounds* (2017), CC0 1.0, https://opengameart.org/content/backgrounds-3
Converted from the original 1104×621 PNG images into 240×160, 4bpp GBA assets (3 palette banks; GBA tiles and tilemaps LZ77 compressed).
All source illustrations used by permission of CC0. The original 12 scenes and Golden Ho-Oh remain unchanged.

| ID | GBA scene | Source | Typical assignment |
|---|---|---|---|
| 67 | twilight_woodland | Nidhoggn battleback1.png | Moonlit forest and ninja/poison woods |
| 68 | winter_pines | Nidhoggn battleback2.png | Pryce snowy forest |
| 69 | burning_crags | Nidhoggn battleback3.png | Blaine and dry volcanic terrain |
| 70 | market_square | Nidhoggn battleback4.png | Goldenrod / Whitney urban courtyard |
| 71 | dark_stone_cavern | Nidhoggn battleback5.png | Dark Cave and Cerulean Cave |
| 72 | ochre_forest | Nidhoggn battleback6.png | Autumn woodland |
| 73 | redwood_copse | Nidhoggn battleback7.png | Ecruteak and autumn woods |
| 74 | lantern_crypt | Nidhoggn battleback8.png | Morty haunted hall and old tower |
| 75 | stone_arena | Nidhoggn battleback9.png | Rock and fighting battle arena |
| 76 | rolling_hills | Nidhoggn battleback10.png | Windy open landscape for Falkner |

## Integration and cave consistency

- Lake of Rage keeps approved rainy lakeside scene ID 64. Special Golden Ho-Oh keeps exclusive sunset ID 62.
- All floors in each cave system continue sharing one scene.
- Gym Leader rematches match their original Gym background (by trainer ID).
- Original Alpha 2.5 save structure and gameplay are unchanged; new graphics are additive.
- Explicit artwork counts exclude palette swaps or derived image copies.

Mapped area assignments updated: MAP_DARK_CAVE_NORTH_SIDE_HNS, MAP_DARK_CAVE_SOUTH_SIDE_HNS, MAP_CERULEAN_CAVE_1F_HNS, MAP_CERULEAN_CAVE_B1F_HNS, MAP_CERULEAN_CAVE_B2F_HNS, MAP_BURNED_TOWER_1F_HNS, MAP_BURNED_TOWER_B1F_HNS, MAP_ROUTE37_HNS, MAP_ROUTE36_HNS, MAP_ROUTE44_HNS, MAP_ECRUTEAK_CITY_HNS, MAP_GOLDENROD_CITY_HNS, MAP_VIRIDIAN_FOREST_HNS, MAP_VIOLET_CITY_GYM_HNS, MAP_AZALEA_TOWN_GYM_HNS, MAP_GOLDENROD_CITY_GYM_HNS, MAP_ECRUTEAK_CITY_GYM_HNS, MAP_CIANWOOD_GYM_HNS, MAP_OLIVINE_CITY_GYM_HNS, MAP_MAHOGANY_TOWN_GYM_HNS, MAP_BLACKTHORN_CITY_GYM_HNS, MAP_PEWTER_CITY_GYM_HNS, MAP_CERULEAN_CITY_GYM_HNS, MAP_VERMILION_CITY_GYM_HNS, MAP_CELADON_CITY_GYM_HNS, MAP_FUCHSIA_CITY_GYM_HNS, MAP_SAFFRON_CITY_GYM_HNS, MAP_SEAFOAM_ISLANDS_GYM_HNS, MAP_VIRIDIAN_CITY_GYM_HNS

## QA

- All 10 new backgrounds are roundtrip-checked with original PJR gbagfx LZ encoder/decoder.
- Every background packs exactly 3 x 16 color palette banks, map 32x32 and visible 240x160 pixels.
- CI build and emulator validation required before publishing a ROM.

## Artwork acceptance and placement review — 10 November 2026

The project owner explicitly approved retaining all ten Nidhoggn CC0 backgrounds after being shown their source art. These are **third-party CC0 illustrations**, not ten commissioned or independently drawn PRU originals. Keep the source link and author credit in any public artwork/credits page.

Assignments are intentional, not one image per arbitrary slot:

| CC0 ID | Background | Context-appropriate use |
|---|---|---|
| 67 | Twilight Woodland | Koga/Janine ninja-poison battles, Viridian Forest, Karen's dark-themed League battles |
| 68 | Winter Pines | Pryce, snowy routes 49/50, cold outdoor scenery |
| 69 | Burning Crags | Blaine, volcanic/Seafoam Gym area |
| 70 | Market Square | Whitney and Goldenrod's urban exterior |
| 71 | Dark Stone Cavern | Dark Cave and all Cerulean Cave floors |
| 72 | Ochre Forest | Autumn routes 36/37 near Ecruteak |
| 73 | Redwood Copse | Ecruteak autumn scenery |
| 74 | Lantern Crypt | Morty, both Burned Tower floors, all seven Lavender Spirit Tower floors, Agatha |
| 75 | Stone Arena | Chuck, Brock, Lt Surge's provisional military/training arena, Bruno, Saffron Fighting Dojo and VIP room |
| 76 | Rolling Hills | Falkner and open windy hillside environments |

**Original PRU art preserved:** Ilex Forest 57, Ruins of Alph 58, crystal/ice caves 59, Mt Mortar 60, rocky Mt Silver 61, Golden Ho-Oh sunset 62, Union Cave/limestone 63, stormy Lake of Rage 64, wooded river 65, and Olivine/Cianwood coast 66. Sprout Tower's three floors temporarily share the original shrine-forest scene 57. Route 44 uses wooded river 65 rather than snowy forest; Olivine harbourfront uses coast 66. Existing multi-floor cave groups remain consistent.

**Remaining artwork limitations:** These 22 paintings do not provide dedicated electric generator, flower-garden Gym, mechanical steel Gym, Psychic chamber or unique Dragon's Den artwork. Their current selections are the closest available thematic substitutes, not claims that those bespoke backgrounds have been drawn. Do not alter the panorama/platform with duplicated bottom rows. Actual in-game layout, 4bpp palettes, VRAM and player/opponent feet must still pass GBA compilation and emulator inspection before the expanded pack is released.
