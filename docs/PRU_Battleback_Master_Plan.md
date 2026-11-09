# PRU Original Battle Background Master Plan — 112 Scenes

Goal: replace donated battle backgrounds with original PRU artwork, with a location-aware visual system spanning Johto, Kanto, RELICS and E20. This is the **production target**, not a claim that all artwork has been built.

## Technical baseline

- 240×160 viewport, 4bpp GBA BG3 tilemap (32×32), 3×16-colour palettes with dedicated banks 12–14.
- Up to 512 8×8 tiles (16 KiB charbase 2); LZ77-compressed tiles/tilemap.
- Keep palettes isolated from textbox palette banks to avoid black streaks; verify decoded graphics and in-game battles.
- Align the ground contact ring approximately 5 native GBA pixels higher than the previously tested paintings; review sprite feet for trainers, wild encounters and bosses.
- Prioritize region/location scripts over generic type matching; preserve existing gameplay and existing PRU sprites.
- No borrowed battle backgrounds in final package. Artist/source/licence notes accompany each item.

## Routes and outdoor (26)

- **PRU-BG-001** — Route 29 — New Bark grasslands — existing tested
- **PRU-BG-002** — Route 30 — winding wooded path — planned
- **PRU-BG-003** — Route 31 — Violet approach — planned
- **PRU-BG-004** — Route 32 — southern coast grass — planned
- **PRU-BG-005** — Route 33 — rain-soaked forest — planned
- **PRU-BG-006** — Route 34 — southern meadows — planned
- **PRU-BG-007** — Route 35 — National Park approach — planned
- **PRU-BG-008** — Route 36 — ancient crossroads — planned
- **PRU-BG-009** — Route 37 — autumn trees — planned
- **PRU-BG-010** — Route 38 — grazing pasture — planned
- **PRU-BG-011** — Route 39 — lighthouse farmland — planned
- **PRU-BG-012** — Route 40 — western sea cliff — planned
- **PRU-BG-013** — Route 41 — Whirl Islands coast — planned
- **PRU-BG-014** — Route 42 — Mt Mortar lakeside — planned
- **PRU-BG-015** — Route 43 — Lake of Rage road — planned
- **PRU-BG-016** — Route 44 — rocky river pass — planned
- **PRU-BG-017** — Route 45 — Blackthorn cliffs — planned
- **PRU-BG-018** — Route 46 — mountain foothills — planned
- **PRU-BG-019** — Route 26 — Indigo ascent — planned
- **PRU-BG-020** — Route 27 — Tohjo Falls valley — planned
- **PRU-BG-021** — Route 28 — Mt Silver lower path — planned
- **PRU-BG-022** — Kanto Route 1 — Pallet woodland — planned
- **PRU-BG-023** — Kanto Route 2 — Viridian forest edge — planned
- **PRU-BG-024** — Kanto Route 3 — Moon Mountain pass — planned
- **PRU-BG-025** — Kanto Route 24 — Nugget Bridge — planned
- **PRU-BG-026** — Kanto Route 25 — northern cape — planned

## Towns and cities (20)

- **PRU-BG-027** — New Bark — village edge — planned
- **PRU-BG-028** — Cherrygrove — seaside gardens — planned
- **PRU-BG-029** — Violet — Sprout Tower skyline — planned
- **PRU-BG-030** — Azalea — timber village — planned
- **PRU-BG-031** — Goldenrod — city plaza — planned
- **PRU-BG-032** — Ecruteak — autumn shrine street — planned
- **PRU-BG-033** — Olivine — harbourfront — planned
- **PRU-BG-034** — Cianwood — island coast — planned
- **PRU-BG-035** — Mahogany — mountain village — planned
- **PRU-BG-036** — Blackthorn — Dragon Den approach — planned
- **PRU-BG-037** — Pallet — Professor Oak hometown — planned
- **PRU-BG-038** — Viridian — forest district — planned
- **PRU-BG-039** — Pewter — stone town — planned
- **PRU-BG-040** — Cerulean — canal waterside — planned
- **PRU-BG-041** — Vermilion — port docks — planned
- **PRU-BG-042** — Lavender — misty tower street — planned
- **PRU-BG-043** — Celadon — garden rooftop — planned
- **PRU-BG-044** — Saffron — metropolitan plaza — planned
- **PRU-BG-045** — Fuchsia — Safari crossroads — planned
- **PRU-BG-046** — Cinnabar — volcanic harbour — planned

## Caves, forests, towers and dungeons (18)

- **PRU-BG-047** — Ilex Forest — shrine clearing — batch01 converted
- **PRU-BG-048** — Ruins of Alph — outdoor meadow — batch01 converted
- **PRU-BG-049** — Union Cave — mossy tunnels — planned
- **PRU-BG-050** — Slowpoke Well — damp cavern — planned
- **PRU-BG-051** — Dark Cave — deep shadowed tunnel — planned
- **PRU-BG-052** — Mt Mortar — rugged interior — planned
- **PRU-BG-053** — Burned Tower — charred timbers — planned
- **PRU-BG-054** — Tin Tower — ancient timber chamber — planned
- **PRU-BG-055** — Whirl Islands — flooded caves — planned
- **PRU-BG-056** — Ice Path — blue crystal chamber — batch01 converted
- **PRU-BG-057** — Mt Silver — first cave — existing tested
- **PRU-BG-058** — Mt Silver — deep cave — planned
- **PRU-BG-059** — Victory Road — Indigo corridor — planned
- **PRU-BG-060** — Cerulean Cave — luminous depths — planned
- **PRU-BG-061** — Rock Tunnel — lantern-lit passage — planned
- **PRU-BG-062** — Seafoam Islands — frozen cavern — planned
- **PRU-BG-063** — Power Plant — relic generator hall — planned
- **PRU-BG-064** — Pokémon Tower — spectral floors — planned

## Water and coast (8)

- **PRU-BG-065** — Open ocean — surf battle — planned
- **PRU-BG-066** — Shoreline — sand and surf — planned
- **PRU-BG-067** — Whirlpool — stormy water — planned
- **PRU-BG-068** — Waterfall — river basin — planned
- **PRU-BG-069** — Lake of Rage — red sky — planned
- **PRU-BG-070** — Pond — lily pads — planned
- **PRU-BG-071** — Bridge — suspended pathway — planned
- **PRU-BG-072** — Island reef — warm shallows — planned

## Gym Leader arenas (16)

- **PRU-BG-073** — Falkner — wind and sky — planned
- **PRU-BG-074** — Bugsy — woodland gym — planned
- **PRU-BG-075** — Whitney — Goldenrod arena — planned
- **PRU-BG-076** — Morty — spiritual sanctum — planned
- **PRU-BG-077** — Chuck — fighting dojo — planned
- **PRU-BG-078** — Jasmine — steel foundry — planned
- **PRU-BG-079** — Pryce — frozen arena — planned
- **PRU-BG-080** — Clair — dragon cave — planned
- **PRU-BG-081** — Brock — stone gym — planned
- **PRU-BG-082** — Misty — Cerulean pool — planned
- **PRU-BG-083** — Lt Surge — electric generator — planned
- **PRU-BG-084** — Erika — flower garden — planned
- **PRU-BG-085** — Janine — ninja maze — planned
- **PRU-BG-086** — Sabrina — psychic chamber — planned
- **PRU-BG-087** — Blaine — volcanic challenge — planned
- **PRU-BG-088** — Blue — Viridian ultimate gym — planned

## Elite and E20 (12)

- **PRU-BG-089** — Will — psychic chess hall — planned
- **PRU-BG-090** — Koga — toxic ninja hall — planned
- **PRU-BG-091** — Bruno — martial stone ring — planned
- **PRU-BG-092** — Karen — moonlit dark arena — planned
- **PRU-BG-093** — Lance — dragon championship — planned
- **PRU-BG-094** — Lorelei — cold blue vault — planned
- **PRU-BG-095** — Agatha — haunted hall — planned
- **PRU-BG-096** — Red — silent summit — planned
- **PRU-BG-097** — Oak and Elm — professor laboratory — planned
- **PRU-BG-098** — Jessie and James — Rocket duo — planned
- **PRU-BG-099** — Steevee and Neevee — Eeveelution stage — planned
- **PRU-BG-100** — Elite 20 — ancient champions chamber — planned

## Relics and legendary encounters (12)

- **PRU-BG-101** — Raikou — Power Plant podium — planned
- **PRU-BG-102** — Entei — Mt Mortar volcanic relic — batch01 converted
- **PRU-BG-103** — Suicune — sacred waters — planned
- **PRU-BG-104** — Lugia — deepest Whirl chamber — planned
- **PRU-BG-105** — Celebi — Ilex Forest shrine — planned
- **PRU-BG-106** — I-Unown — Alph Eye chamber — planned
- **PRU-BG-107** — Alphoracle — Alph ritual hall — planned
- **PRU-BG-108** — Ancient Guardian Dragonite — Tin Tower roof — planned
- **PRU-BG-109** — Golden Ho-Oh — Mt Silver finale — planned
- **PRU-BG-110** — Armoured Mewtwo — Giovanni laboratory — planned
- **PRU-BG-111** — Primal Groudon — magma temple — planned
- **PRU-BG-112** — Primal Kyogre — ocean throne — planned

