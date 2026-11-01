# PRU — queued next patch (prepared 2026-11-01; DO NOT BUILD OR RELEASE)

**Status: requirements and implementation checkpoints only.** No gameplay change in this file, no binary, no build request, no ROM release, no claim of testing.

**Repository:** https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate  
**Current integration branch:** `feat/pru-relic-hunt-20261101`  
**Last observed successful source/build:** `8ceb68cb4cfe3120cc85b5adb09875db3921688f`, Actions [run 41328773459](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41328773459), as checked 2026-11-01. This is a reference, **not a frozen branch HEAD**; recheck latest HEAD and user's latest tested ROM before coding.  
**Release control:** Do not commit source modifications, trigger workflows, build a ROM, publish releases, merge PRs, or disturb active parallel work until explicitly asked to implement/build this change set. The preparation document itself is exempt from those source/build actions.

Read `AGENTS.md`, `PRU_HANDOFF.md`, `docs/PRU_RELEASE_LEDGER.md`; preserve all working features, existing save IDs, the 450-species order, species graphics, E20, legendaries, custom moves and tutor coverage.

## 1. Ecruteak Rock Shop: more stones, half-price, Ancient Stone

- Existing files: `data/maps/EcruteakCity_RockShop_hns/scripts.inc`, `src/shop.c`, `src/data/items.h`.
- Existing basic list includes Fire, Water, Thunder, Leaf, Ice, Moon, Sun; the Fog Badge unlocks Shiny, Dusk and Dawn. Keep badge progression unless there is a compelling gameplay reason to change it.
- Add `ITEM_ANCIENT_STONE` to both stock tiers and complete the supported stone selection. Audit Oval Stone and Everstone as relevant stock choices; do not reintroduce the seven retired relic catalysts. Ancient Stone retains its level-45 evolution restriction and existing item ID.
- **Only Ecruteak Rock Shop charges half of normal item purchase prices.** Do not globally halve item values, sales prices, Poké Marts or other inventories. Implement a shop-context price resolver in `src/shop.c` or an equivalent isolated discount mechanism; apply consistently to displayed unit price, initial total, quantity changes, payment/validation and final deduction. Preserve existing non-rock-shop/Slaterport-news logic. Prices should never round to zero.
- Add a targeted test comparing Ecruteak display/charge vs another mart and both badge states.

## 2. False Swipe available early and in both department stores

- **Early location:** Cherrygrove Mart (or the earliest guaranteed accessible Johto mart after obtaining Poké Balls); distinguish its pre-Poké-Balls scripted stock from its post-progression dynamic stock.
- **Both big marts:** Goldenrod Dept. Store 5F TM corner and Celadon Dept. Store 3F TM shop, currently `data/maps/GoldenrodCity_DepartmentStore_5F_hns/scripts.inc` and `data/maps/CeladonCity_DepartmentStore_3F_hns/scripts.inc`.
- **Confirmed existing TM54:** `FOREACH_TM` in `include/constants/tms_hms.h` maps False Swipe to the 54th TM; the macro in `include/constants/items.h` generates `ITEM_TM_FALSE_SWIPE = ITEM_TM54 = 635`. `[ITEM_TM54]` in `src/data/items.h` is a real ¥3,000 teaching item; `MOVE_FALSE_SWIPE` has its original non-KO effect. Reuse this exact TM and retain its stable item ID; do not add a replacement or duplicate.
- The item should be purchasable repeatedly and actually teach False Swipe. Verify against existing saves and trainer battles.

## 3. Indigo Plateau tutors: Eerie Fog + Scary Face; Scary Face inflicts Fear

- Preserve the complete existing Indigo tutors, row alignment, Move Relearner, Egg Move service and all compatibility lists.
- Both moves already exist: `MOVE_EERIE_FOG` creates 8-turn fog; `MOVE_SCARY_FACE` currently has `EFFECT_SPEED_DOWN_2` while its description claims Fear.
- Add BOTH as actual teachable moves to existing Indigo tutor menus, with sufficiently broad and logical compatibility. Do not create duplicate moves/TMs merely for tutor coverage.
- Fix **runtime** Scary Face to lower Speed two stages **and** attempt to inflict the project's existing Fear volatile upon a successful valid target; match established Fear duration/immunity, Magic Bounce/Protect and failure behaviour. Specifically test a target at minimum Speed and a target where Fear is blocked. Do not rely on description changes alone.
- Do not replace `EERIE_FOG`'s authentic weather effect or disturb other status effects.

## 4. Trainer-battle Quit freeze: prevent quitting

- Reproduce the exact trainer-battle Quit/Forfeit menu path and trace the freeze; inspect `src/battle_main.c`, `src/battle_controller_player.c`, controller/menu code and custom scripts.
- In a **trainer battle**, hide or disable the inappropriate Quit/Forfeit action and route controller inputs to a safe prompt. Preserve normal Fight/Bag/Pokémon interaction, trainer battle defeat/victory scripts, and ordinary wild-battle Run behaviour, plus Safari and link battle logic.
- Do not simply disable escaping globally. Add a regression covering repeated presses and returning to the same menu without softlock.

## 5. Route 34 Day-Care: repeatable ¥5,000 Mystery Egg vendor

- Existing indoor map: `data/maps/Route34_DayCare_hns/map.json`; events in `scripts.inc`. Existing NPC offers a **one-time free Odd Egg** with `FLAG_RECEIVED_ODD_EGG`; do not overwrite it.
- Add a **separate vendor NPC** at a clear walkable indoor tile, with buy/decline/insufficient-funds/party-full messages; purchase is **¥5,000 per Egg** and repeatable. Ensure no deduction until purchase is confirmed and an Egg is actually awarded.
- Select **uniformly/randomly from an explicit vetted baby-species pool** restricted to species in PRU's approved 450. Include custom babies `SPECIES_SKARMET`, `SPECIES_MOOTINY`, and `SPECIES_SCARABUB` (canonical source name; referred to as 'Herabub' in the request), plus legitimate vanilla baby species in the 450. Validate each species has egg-compatible data, real front/back/icon assets and a valid hatch species; no egg with a bad-mon/invalid-ID result.
- Use normal hatch steps, daycare egg and party mechanics; no unintentional flag consumption, duplicate charge, or save-ID changes. Respect challenge-party limits if applicable. Ensure users can buy more than one.
- Keep Day-Care Move Expert and its tutor access intact.

## 6. RELICS legendary encounter levels

- Audit **all player-catchable scripted RELICS legendary encounters** across Johto/Kanto/quest areas and their repeat/respawn paths.
- Standardize level **80** except **Alphoracle at level 90**. Include I-Unown's Relic encounter, legendary beasts, Lugia, Celebi and other quest legendary encounters if present. Do not change trainer-owned Pokémon, ordinary wild encounter tables, scripted noncatchable showcases or NPC sprites.
- Preserve catches, defeat/respawn, flags, conditions, positions, sprites, pedestal objects and story dialogue. Targeted tests should list location, script label, intended level and re-encounter handling.

## 7. All ending credits replaced with PRU-specific credits

- Source: `src/credits_hns.c`, `src/data/credits_hns.h`, and endgame invocation scripts. Existing E20 code only prepends PRU intro pages and then falls through into Heart & Soul base credit pages. Replace the **actual displayed closing credit pages** for all ending paths: Johto E4, Kanto E4 and Elite 20, without removing their gameplay reward or finale presentation.
- Opening: **POKÉMON RELICS ULTIMATE**; lead project/design/creative direction; acknowledgements of tools and collaborators actually used, including GitHub, OpenAI/ChatGPT, Anthropic/Claude, Google/Gemini, PokéSprite, Porypal, pokeemerald-expansion, pret/pokeemerald, and Heart & Soul where accurate.
- Next pages: authentic source repositories and original ROM-hack teams, sprite artists/asset donors and custom sprite makers **verified** from `docs/*PROVENANCE*`, `CREDITS.md`, donor manifests, and source history. Include Azul Agua's Rock Shop artwork provenance; don't misattribute community sprites or imply the named AI tools alone own others' art. Preserve underlying applicable notices/licences and a human-readable credit file in the repo.
- Screen text must fit GBA widths/page counts; no overflow, missing page arrays or soft-reset regressions. Preserve Elite 20 golden Ho-Oh opening, montages and reward events.

## 8. Repair the HGSS Pokédex and preserve 450 independent entries

- Canonical ordering lives in `src/data/pokemon/pru_dex_order.h`, exactly `PRU_DEX_COUNT = 450`. **Do not change that sequence, species constants or save file species IDs.**
- `src/pokedex_plus_hgss.c` still contains inherited `NATIONAL_DEX_COUNT`-based listing/search order and historical National Dex seen/caught indexing; `docs/PRU_444_SPECIES_SOURCE_AUDIT_20261018.md` records the original unresolved problem (when 444 species were supported).
- Rebuild the on-screen PRU Dex rows, numerical order, seen/caught flags, numbering, evolution branch display, icon lookup, sorting and completion counters around the 450 **approved species**. Custom species sharing vanilla National Dex numbers must display and record independently.
- Provide a **save-compatible migration/fallback** for existing saves; never silently wipe/reset Seen/Caught or remap their bits. Test fresh save and existing save, showing custom Relics adjacent to their families, correct last six entries and no blank/doubled rows.

## 9. GitHub 450-species sprite review folder

- Produce one repository directory `assets/pru_450_sprite_review/` with **all 450 × 3 = 1,350** PNGs labelled in canonical Dex order: `001_Bulbasaur_front.png`, `001_Bulbasaur_back.png`, `001_Bulbasaur_icon.png`, etc. Add `manifest.csv` (dex #, canonical species constant/name, front/back/icon source path, asset SHA256, palette/alpha validation, custom donor attribution).
- Obtain each **actual active** front/back/party icon from the effective compile inputs. Important: CI installers may replace source art. Do not export obsolete pre-PRU images simply because they exist on disk.
- Copy/convert transparent background pixels for the **review exports only**; preserve 1:1 pixel art, palettes, aspect and any approved cropping. Do not strip colours or alter original game sprite/palettes. Flag and report missing/mismatched assets rather than reusing a different species' icon.
- Include ordinary Pokémon, Relics, and the 450 roster's exact special cases. Trainer-only alternative assets are additional and separately labelled only if requested later; never count them toward the 450.
- Assert 450 unique IDs, 450 front/back/icon, zero opaque/background padding in preview copies where appropriate, and manifest hash validation.

## 10. Radical Red move parity; priority Dark Void on I-Unown

- Take an **identified** Pokémon Radical Red release/official move data as reference, build a machine-readable move-by-move delta against PRU's own move registry, and identify genuinely missing moves. No indiscriminate ROM data copying, no wholesale enum renumbering, no unaudited rebalancing of existing PRU signatures. Document additions, existing matches and exceptions.
- For missing moves, import/register **all feasible distinct moves** including type/power/accuracy/PP, category, target, real effects, animation, AI, battle messages and meaningful level-up/tutor/egg/technical learnability. Where full parity cannot fit engine/save/build constraints, clearly enumerate blockers instead of claiming all complete.
- `MOVE_DARK_VOID` **already exists** in `src/data/moves_info.h`: Dark-type, status, 10 PP, 50% accuracy under Gen 7+ data settings (otherwise 80%), both foes and Sleep; existing animation. It must become **legitimately learnable and usable by I-Unown**, including handling any Darkrai-only move-use restriction that would otherwise make it fail. Retain I-Unown's approved **Omen Eye** signature move and its Fear effect; Dark Void is additional, not a replacement.
- Preserve all current PRU custom moves, Frostbite/Bleeding/Fear/Eerie Fog, existing move IDs/known-move saves, tutor compatibility and effect handlers. Add tests for I-Unown using Dark Void in singles and doubles, and a table comparing Radical Red and PRU supported moves.

## Integration acceptance and hold

- This checklist is intentionally staged without touching gameplay files. On later authorization, re-read the latest HEAD/release ledger and incorporate only after checking any parallel branch edits.
- Apply one owner/source integration approach and focused scripted regression checks for each section; verify **all 450 entries**, stable constants/saves, complete Indigo tutors, quest flags, no battle freeze, new credits pages and sprite manifest; only then run the full 32 MiB `make hns -j2 -O` clean build.
- **Hold now:** no code commit, no Action workflow trigger, no ROM compile, no GitHub release/asset upload and no user-visible GBA link until explicitly requested. Track statuses distinctly: *queued* → *coded* → *tested* → *compiled* → *released* → *player-tested*.


## Addendum: actual Pokédex gameplay evidence, 2026-11-01 (user video `1000043619.mp4`)

The player supplied a ~49-second in-game Pizza Boy A recording, scrolling from the first entry to the end of the presently shown National Pokédex. This was inspected directly. These are **observed in gameplay** (unlike source-only assumptions):

| Evidence | Currently visible | Required PRU canonical order |
|---|---|---|
| Opening | #001 Bulbasaur; #002 Ivysaur; #003 Venusaur; **#004 Charmander**, #005 Charmeleon, **#006 Charizard** | #001–003 unchanged; **#004 Edensaur**, #005 Charmander, #006 Charmeleon, **#007 Charizard**, **#008 Charaxis** |
| Kanto starter family transition | #007 hidden/dashes; **#008 Wartortle**, #009 Blastoise | #009 Squirtle, #010 Wartortle, #011 Blastoise, **#012 Fortotoise** |
| Middle of list | #147 Elekid, #148 Electabuzz, #149 Electivire; #279 Tyranitar; **#280 Lugia** | Use the entire authoritative `sPruDexSpecies[450]` family-grouped sequence; **#435 Lugia** in that sequence |
| End of presently browsable list | **#419 Deoxys** is displayed at the end, with no further entries visible | **#450 Deoxys**; full 450-species PRU Pokédex |
| Side counters throughout | JOHTO Seen 245 / Own 41; NATIONAL Seen 303 / Own 69 | Counts must be recalculated from the correct tracked species pool. Preserve existing sightings/catches on old saves and avoid false independent custom-species counts. |

**Important distinction:** Rows with `----------` and question-mark art may be correctly hidden **unseen** entries; do not mark every hidden row as a missing species. The **wrong displayed identities and numeric positions** are proven. The existing #419 end could also involve last-seen truncation, so test full-roster availability separately from list scroll limits rather than assuming exactly 31 missing underlying species records.

### Confirmed source mechanism for this observed failure

- `src/data/pokemon/pru_dex_order.h` already defines the **approved 450-species order**, including #004 Edensaur, #008 Charaxis, #012 Fortotoise, #435 Lugia, #437 Alphoracle and #450 Deoxys. **Do not reorder this canonical source or rewrite its IDs.**
- `src/pokedex_plus_hgss.c::CreatePokedexList` constructs the visible list from inherited `REGIONAL_DEX_COUNT` / `OBTAINABLE_DEX_COUNT`, `RegionalToNationalOrder` / `ObtainableToNationalOrder`, and National Dex `GetSetPokedexFlag`, not the canonical species array.
- That function sets `pokemonListCount` to the last **seen** numeric entry rather than always providing a 450-slot view; consequently unseen tail slots may be inaccessible. Audit intended browse behavior and ensure all 450 can be reached with appropriate hidden/seen presentation.
- Alphabetical / Weight / Height sorts still traverse inherited `NATIONAL_DEX_COUNT` and legacy order arrays, so they also need a **PRU-specific** species-keyed implementation.
- `GetPokemonSpriteToDisplay` still guards entries using `species >= NATIONAL_DEX_COUNT`; avoid rejecting valid PRU custom species/indices during rendering.
- Existing documentation `docs/PRU_444_SPECIES_SOURCE_AUDIT_20261018.md` had already identified the core seen/caught collision: multiple custom Relics share a base National Dex ID. Implement **independent tracked records with compatible migration**, not merely swapping the displayed number strings.

### Acceptance tests that must be demonstrated before the next ROM release

1. Fresh save and existing save both display the **identical full approved 450 order**, with #004 Edensaur, #007 Charizard, #008 Charaxis, #012 Fortotoise and #450 Deoxys; every intermediate index maps exactly to `sPruDexSpecies`.
2. A caught/seen Charaxis creates its **own** Dex status, distinct from Charizard. Same independent test for Edensaur/Venusaur and other canonical Relics. Unseen entries remain hidden by normal Pokédex design rather than being silently omitted or shifted.
3. Scroll reaches the end and back safely; entries after the previous last-seen slot are available according to the new 450-entry design. No blank beyond-bounds sprite/icon, corruption or crashes.
4. Numbers, details, cry, shiny/normal sprite selection, species name, evolution guides, family order, multiple search modes and completion counters reflect the same approved species ID at every step.
5. Save compatibility: previous 303 seen / 69 owned *as observed* must not be discarded or blindly copied to a new count. Migrate vanilla seen/caught bits accurately for unambiguous base species; use robust conservative behavior for previously shared custom IDs, preserving legitimate catches without falsely claiming individual custom species.
6. Preserve Johto mode as a separate intentionally defined subset **only if desired**; both the main PRU and National browse modes must not accidentally fall back to old Heart & Soul or inherited 419-number ordering.
7. Regression must catch the failure with source assertions for `CreatePokedexList` and practical emulator tests (player can independently verify; no unrelated screenshot/boot test gates before source implementation is ready).

**Status of addendum:** video reviewed, issue diagnosed at source level, **not yet patched, compiled or player-tested**. Preserve the instruction to **not build or release** until the user explicitly authorizes implementation.


## False Swipe TM54 source-stage checkpoint (2026-11-01)

- Work branch: `prep/pru-rockshop-no-build-20261101`, staged **without compilation or publication**.
- `data/maps/CherrygroveCity_Mart_hns/scripts.inc`: adds the real `ITEM_TM_FALSE_SWIPE` to the initial pre-Poké-Ball stock.
- `src/shop.c`: extends the existing `pokemart 0` dynamic badge-based stock **only when standing inside Cherrygrove Mart**, preserving Potion/Ball availability and all other towns' inventories; continues to share the shop's normal purchase path.
- `data/maps/GoldenrodCity_DepartmentStore_5F_hns/scripts.inc` and `data/maps/CeladonCity_DepartmentStore_3F_hns/scripts.inc`: add TM54 to the pre-existing TM inventory; don't replace any items.
- `test/test_pru_false_swipe_marts.py`: source-only guard for TM54 identity and mapping, proper item use/effect, and all three inventories.
- **Remaining before a player-ready ROM:** run source regression and compile on later user approval; independently confirm at least a few eligible Pokémon can learn the TM, and both fresh/existing saves retain the item and shop stock. TM item is **consumable under current `I_REUSABLE_TMS = FALSE` configuration**; repeated purchases are supported.
- **Hold remains:** do not run GitHub Actions, build or publish a GBA until the user requests it.
