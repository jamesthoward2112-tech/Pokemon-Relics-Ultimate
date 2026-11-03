# PRU — queued next patch (prepared 2026-11-01; DO NOT BUILD OR RELEASE)

## Job 4 release discrepancy — hotfix MUST precede Indigo tutors (3 November 2026)

**CONFIRMED CODE/RELEASE DEFECT AGAINST APPROVED REQUIREMENTS:** Work published Job 4 release `pru-build-0d51e26326` (source `0d51e263260c4a28e6de77e8389bb5563a231b7d`, checkpoint `bb11c3123e7ac4f58d94e61b0f9b56da1d6b4862`) with **badge-tiered TM loot**, despite owner's explicit latest requirement that ordinary former Escape Rope field loot give **one Max Revive**. This mismatch is verified in `src/item_ball.c` and `test/test_pru_false_swipe_escape_rope.py` on the published source. Do not report Job 4 loot conversion as approved/completed, and do not begin Job 5 tutors before a small repair.

**Minimal hotfix details:**
1. In `src/item_ball.c`, remove the entire badge-tier `GetPruEscapeRopePickupTm` implementation; for HNS visible item ball templates with `ITEM_ESCAPE_ROPE`, return **`ITEM_MAX_REVIVE`**, quantity **1**, with no badge check. Remove now-unused badges header.
2. In `src/field_control_avatar.c`, when HNS hidden pickup uses original `ITEM_ESCAPE_ROPE`, set `gSpecialVar_0x8005 = ITEM_MAX_REVIVE` and `gSpecialVar_0x8009 = 1`, preserving original hidden-item flags. Delete no-longer-needed helper declaration from `include/item_ball.h`.
3. Replace exactly the four already-converted HNS field scripts, preserving script labels and flags: `data/maps/MtMortar_1F_North_hns/scripts.inc` (was Brick Break TM), `data/maps/WhirlIslands_B1F_hns/scripts.inc` (was Swords Dance TM), `data/maps/SproutTower_3F_hns/scripts.inc` (was Bullet Seed TM), `data/maps/TinTower_3F_hns/scripts.inc` (was Rock Slide TM), all to `finditem ITEM_MAX_REVIVE`. Do not change Sprout Tower's unrelated **rival Escape Rope dialogue** or its movement script.
4. Update `test/test_pru_false_swipe_escape_rope.py` to assert **Max Revive** rather than badge-tier selection/TMs, retain all False Swipe, Key Item and flags assertions; source test must explicitly reject remaining `GetPruEscapeRopePickupTm` or TM replacement code in former Rope field pickup paths. Conduct full HNS map/source audit; do not replace legitimate Key Item `giveitem ITEM_ESCAPE_ROPE` in New Bark Lab or non-HNS scripts. No change to TM reusability mechanics.
5. Preserve the proven original H&S Alph ladder blocking mGBA regression, Sylveon, 450 canonical Pokédex, all preceding changes. Update GitHub checkpoint/release ledger and Notion, push focused fix, compile/release another valid 32 MiB ROM with SHA-256. Report mGBA Max Revive pickup gameplay accurately as passed only if tested; do not conflate Alph ladder test with field-item test. Keep prior ROM as fallback.

**Source verification:** Latest GitHub branch HEAD was checkpoint `bb11c3123e7ac4f58d94e61b0f9b56da1d6b4862` and published ROM was [0d51e26326](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-0d51e26326) when discrepancy discovered. **Research/documentation only**, no gameplay source changed in this entry.


## 3 November — OWNER OVERRIDE: Job 4 Escape Rope pickups give MAX REVIVES, NOT TMs

**Latest approved instruction, superseding all earlier staged Rope→TM tiers in this document:** Every *formerly obtainable* Escape Rope from PRU/HNS **visible item balls, hidden/background loot, and explicit scripted field item pickups** should now award **ONE `ITEM_MAX_REVIVE`**, not any TM. Preserve its exact original pickup location, object/script identity, one-time item flag, quantity=1, bag-space behaviour, and existing-save compatibility. Don't grant a duplicate for already collected pickups. Do not make the reward depend on badge count or current TM collection.

- Keep `ITEM_ESCAPE_ROPE` unchanged as a **reusable Key Item**, available via the approved early-game New Bark lab aide grant and Elm's missing-item recovery for old saves; don't convert the legitimate Key Item gift to Max Revive.
- Remove redundant purchasable Escape Rope entries from normal HNS shop stock. **Do not replace those shop entries with TMs**; retain unrelated stock and shop progression, and do not introduce Max Revive into every shop by default.
- False Swipe shop availability in Cherrygrove (both pre/post Poké Ball states), Goldenrod 5F, and Celadon 3F remains part of Job 4; use the existing TM54 unchanged. **No changes to TM consumption/reusability in this job**. User confirms TMs are reusable in their gameplay; code/config must be inspected separately if a source discrepancy is reported, not changed as a side effect of this item placement job.
- The old `GetPruEscapeRopePickupTm()` badge selector, TM reward tables, and the staged `test_pru_escape_rope_and_*tutors.py` TM expectations are **not approved** for Job 4. Do not cherry-pick them. Instead implement narrow replacement logic to grant `ITEM_MAX_REVIVE` consistently for ordinary visible/hidden loot, and replace explicit scripted field gifts with the same item, while leaving normal Key Item grants intact. Validate a full sweep of HNS maps/scripts and no incidental changes to non-HNS variants.
- Keep the blocking original H&S Alph ladder mGBA regression from Job 3C passing. Commit/push checkpoints and update the PRU Notion journal as usual. This is a **requirement update only**, not implementation or a ROM release.


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
- Select uniformly from an explicit **13-species pool:** the nine Kanto/Johto/Hoenn traditional first-stage starters and **four** custom Relic babies: `SPECIES_SKARMET`, `SPECIES_MOOTINY`, `SPECIES_SCARABUB` (Herabub) and `SPECIES_GEMLIN`. All must belong to PRU's approved 450. Verify egg cycles and real front/back/icon/hatch assets; never deliver an invalid Egg.
- Use normal hatch steps, daycare egg and party mechanics; no unintentional flag consumption, duplicate charge, or save-ID changes. Respect challenge-party limits if applicable. Ensure users can buy more than one.
- Keep Day-Care Move Expert and its tutor access intact.

## 6. RELICS legendary encounter levels

- Audit **all player-catchable scripted RELICS legendary encounters** across Johto/Kanto/quest areas and their repeat/respawn paths.
- Standardize **catchable scripted encounters** to level **80**, except **Alphoracle at 90** and **the single final Ho-Oh (Relic Ho-Oh) at 100**. Do not change trainer-owned Pokémon, roaming tables, or noncatchable appearances. Only one Ho-Oh battle can exist in new playthroughs, unlocked after catching all other seven RELICS and obtaining the Ancient Rainbow Crest.
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


## Escape Rope → progression TMs and Indigo tutors checkpoint (1 Nov 2026)

**Scope:** staged source only on `prep/pru-rockshop-no-build-20261101`. Do **not** merge, launch Actions, compile or publish a ROM until separately requested.

### Escape Rope replacement

- Keep `ITEM_ESCAPE_ROPE = 120` intact as a **reusable Key Item**: `include/config/item.h` currently has `I_KEY_ESCAPE_ROPE = GEN_8`, and `src/data/items.h` places it in the Key Item pocket, importance 1, with its normal escape field-use callback. Do not change this item ID or ability.
- `src/item_ball.c::GetItemBallIdFromTemplate`: when an HNS map object still contains `ITEM_ESCAPE_ROPE`, substitute a valid existing TM at award time. Keep the map object, flags and one-time pickup behaviour intact. Force quantity one on converted pickups, even if older map loot had multiple ropes.
- `src/field_control_avatar.c::GetInteractedBackgroundEventScript`: also intercept former Escape Rope **hidden-item pickups**. These bypass the item-ball helper, so both paths now use a shared `GetPruEscapeRopePickupTm()` from `src/item_ball.c`, declared in `include/item_ball.h`. Keep their original hidden-item flags, give only one TM, and leave other map/region variants alone.
- **Pickup tiers by total badges at time of collection:** 0–1 Bullet Seed; 2–3 Rock Tomb; 4–5 Brick Break; 6–7 Shadow Ball; 8–11 Roost; 12–14 Rock Slide; 15+ Earthquake. Progression depends on **story progress when obtained**, not original cave's placement; backtracking can award a higher-tier TM.
- `src/shop.c`: remove obsolete purchasable Rope from all 18 global HNS badge-based/PC-stock tables; replace the slot with one of nine escalating TMs at badge tiers 0 through 8+: Bullet Seed, Rock Tomb, Aerial Ace, Brick Break, Facade, Shadow Ball, Roost, Rock Slide, Earthquake.
- **Reusable Rope acquisition:** `data/maps/NewBarkTown_Lab_hns/scripts.inc` now awards `ITEM_ESCAPE_ROPE` as a **permanent Key Item** from the aide immediately after the first Poké Ball progression flag. Professor Elm also offers a missing copy on later interaction once that flag exists, allowing compatible old saves to recover the key item if they never collected it.
- This covers **visible object item balls, hidden/background item pickups** and global dynamic Poké Marts. A direct scripted `giveitem ITEM_ESCAPE_ROPE` is not covered by the object interceptor: `test/test_pru_escape_rope_and_indigo_tutors.py` scans every **HNS** map's `scripts.inc` and now **fails** on any remaining direct Rope use other than the two deliberate reusable Key Item grants; the audit must be executed before a playable release. Also review any explicit non-global specialty marts and scripted/trainer rewards. Do **not** blindly replace the two intentional early/recovery Rope Key Item grants. Any other direct Rope gifts must be reviewed and replaced where they are consumable-style loot.
- All reward TMs exist in the current `FOREACH_TM` table, retaining existing TM item IDs. New asset, species and item slots are unnecessary.

### Indigo Plateau tutors and Fear

- `data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc`: append two menu options **EERIE FOG** and **SCARY FACE** to the current Hazard/Control Tutor, with new text and `MOVE_EERIE_FOG` / `MOVE_SCARY_FACE` routes to the original free `SELECT_PC_MON_PJR_CONTROL_TUTOR` service. Cancel now maps to option 24. Existing 22 control moves, Cleanup Tutor, all other Indigo specialists, Relearner and Egg Tutor remain unchanged.
- `src/chooseboxmon.c`: register both with `IsPjrControlTutorMove` (which also governs party/PC eligibility). Eerie Fog: Ghost, Dark, Psychic or Poison types, plus existing special learnability. Scary Face: Dark, Ghost, Dragon, Normal, Fighting or Psychic types, plus existing learnability. Keep actual move-specific legality; neither becomes universal.
- Existing Fear wiring was already found in `data/battle_scripts_1.s`: `BattleScript_EffectStatDown` branches on `MOVE_SCARY_FACE` into `BattleScript_PRU_ScaryFaceFear`, which uses native `seteffectprimary BS_ATTACKER, BS_TARGET, MOVE_EFFECT_FEAR`. `src/battle_script_commands.c` sets `fearTimer = 2` if not already feared. Preserve `MOVE_SCARY_FACE`'s -2 Speed, successful-hit and protection checks. Eerie Fog keeps its 8-turn weather effect.
- **Gameplay QA still required:** Scary Face target at minimum Speed, unprotected/protected/substitute targets, already-feared target, and Mirror Bounce; Eerie Fog field weather and expiration; compatibility on party and PC Pokémon, including custom Relics; free/repeatable tutors with clean cancel.
- `src/script_menu.c` uses a dynamic scroll-list with `argc` as `u8`; both added menu rows are below that limit. The control tutor now has 25 options (24 moves + cancel), and the original six-visible-rows scrolling remains.

**Source-only guard:** `test/test_pru_escape_rope_and_indigo_tutors.py` added. It checks the hidden-item path and explicitly rejects stale HNS scripted Rope pickups. It is committed but has **not** been executed in a checkout or compiled into a ROM. **Status: staged, unbuilt, untested in-game.**


## Escape Rope replacement and Indigo tutor checkpoint (2026-11-01)

**New user direction:** Escape Rope is now a Key Item in the active configuration (`I_KEY_ESCAPE_ROPE = GEN_8`). Replace placed, collectible Escape Rope rewards throughout **PRU Johto/Kanto** with real TM items, scaling by story progress rather than awarding a late-game powerhouse at the beginning. Protect overworld puzzles and save compatibility. Do not delete or repurpose `ITEM_ESCAPE_ROPE` or edit non-PRU game modes. Do not replace shop stock by a TM; separate any obsolete Escape Rope merchandise audit from placed pickup replacements.

Suggested progression for individual overworld pickup locations, adjusting to actual level/availability after locating them: early Johto `ITEM_TM_FALSE_SWIPE`, early-middle Johto `ITEM_TM_AERIAL_ACE`, middle Johto `ITEM_TM_BRICK_BREAK`, late Johto `ITEM_TM_SWORDS_DANCE`, Kanto `ITEM_TM_SHADOW_BALL`, late Kanto/postgame `ITEM_TM_EARTHQUAKE`. These are existing TM constants; verify each item is present and map progress first. Preserve event-item graphics, story flags, existing saves, and obtainability; avoid excessive repeat reward TMs where possible. **Location-wide inventory and all pickup source edits are not complete**: project has 561 HNS map script files and 570 map.json files, and the repository search endpoint did not return individual Escape Rope placements. Do not claim every pickup is replaced until a complete map/script sweep and a source regression show zero collectible Escape Ropes.

**Indigo tutors:** the active `data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc` already has `IndigoPlateau_Text_TutorMove_EerieFog` and `IndigoPlateau_Text_TutorMove_ScaryFace`, selection cases, and their `TutorTeach` scripts in the existing hazard tutor; do not duplicate NPCs or scripts. Source stage commit `80fcf44418ab739aeaaabf1a9d6a672a7f915cab` adds a 100% `MOVE_EFFECT_FEAR` additional effect to `MOVE_SCARY_FACE` while retaining `EFFECT_SPEED_DOWN_2`. **Runtime validation needed:** confirm secondary status effects are executed on successful pure status moves in this engine; check Fear immunity/accuracy, whether dropping Speed can fail independently, and coverage/learnability in both menu and teaching party. Do not claim battle testing passed.

**No GBA ROM build or release authorised for preparation branch.**

### Concrete pickup replacements staged

- `data/maps/MtMortar_1F_North_hns/scripts.inc`: original `MtMortar_1F_North_EventScript_Item_EscapeRope` now rewards `ITEM_TM_BRICK_BREAK` (middle Johto), preserving existing script ID and flag; commit `fc91057bbd758108f6a7892d746e4d4ac4c03422`.
- `data/maps/WhirlIslands_B1F_hns/scripts.inc`: original `WhirlIslands_B1F_EventScript_Item_Escape_Rope` now rewards `ITEM_TM_SWORDS_DANCE` (late Johto), preserving original script ID and flag; commit `ea5f9da08e1cdbd3187ac475b95a35f19dbd5cdb`.
- Added `test/test_pru_escape_rope_and_tutors.py`, which scans **every** `*_hns/scripts.inc` and `*_hns/map.json` for remaining collectible Escape Rope instances and checks both tutor selection cases and Scary Face source effect. Do not assert a full replacement is complete until this regression is run and passes in a full checkout.


## Reconciled implementation checkpoint — 1 November 2026 (authoritative for current staged branch)

This checkpoint supersedes earlier *suggested* replacement lists and temporary audit
assumptions in this document; it is NOT evidence of a playable or tested ROM.

**Implemented in source on `prep/pru-rockshop-no-build-20261101`:**

- `ITEM_ESCAPE_ROPE` keeps its original ID, permanent Key Item pocket, and non-consumable escape action.
- Elm's lab intentionally uses two `giveitem ITEM_ESCAPE_ROPE` lines (early gift and old-save missing-item recovery) plus a `checkitem` condition. **These are not obsolete Rope loot.**
- Ordinary visible item balls (`src/item_ball.c`) and hidden/background pickups (`src/field_control_avatar.c`) use the **same shared badge-tier TM resolver**, before any receipt/item-space handling. Existing map JSON item names may still say `ITEM_ESCAPE_ROPE`; the award result is a TM, and the same original object/hidden flag is retained.
- Former explicitly scripted Rope pickups in Mt Mortar 1F North and Whirl Islands B1F now give **Brick Break** and **Swords Dance**, respectively.
- The shared badge-tiered Poké Mart inventories offer TMs instead of stockpiling unusable extra Key Item Ropes. The Ecruteak half-price shop and Cherrygrove False Swipe TM remain staged.
- The existing Indigo control tutor now offers Eerie Fog and Scary Face. Move compatibility checks extend to the new moves without removing existing tutors or services.
- Scary Face retains `EFFECT_SPEED_DOWN_2`. Fear uses **one** guarded native battle-script effect (`BattleScript_PRU_ScaryFaceFear`), not both a battle-script effect and a second automatic `additionalEffects` roll. Missed/failed/no-effect moves do not cause Fear.
- Source checks in `test/test_pru_escape_rope_and_indigo_tutors.py` and `test/test_pru_escape_rope_and_tutors.py` now recognize intentional Key Item grants and centrally converted map-JSON item awards; they reject extra direct HNS Rope loot.

**Still required before release:** execute the tests on a complete checkout, confirm no further scripted HNS Rope rewards remain, compile the full GBA, and test early and late visible/hidden pickups, old-save Elm recovery, real TM teaching, all Indigo menus, Fear against misses/Protect/Substitute/stat-limit/abilities, fog expiration, save/reload, and mGBA. Do **not** build or publish as part of this preparation checkpoint.


## Trainer-battle Quit/Forfeit freeze — source fix staged (1 November 2026)

**Status:** source implemented and committed on `prep/pru-rockshop-no-build-20261101`; no ROM compilation, workflow run or mGBA gameplay test.

**Root-cause candidate:** the normal trainer action menu could submit `B_ACTION_RUN`; `src/battle_main.c` routed that to `BattleScript_QuestionForfeitBattle` (or Frontier/Trainer Hill forfeit), with `B_OUTCOME_FORFEITED` thereafter entering the script-specific return-to-field/whiteout path. A player reported this freezes. This is a code-path diagnosis, **not yet a proven exact freeze cause**.

**Staged safeguards, HNS only:**
- `src/battle_controller_player.c::HandleInputChooseAction`: pressing A on the bottom-right RUN tile in a local trainer battle plays `SE_BOO` and **returns without emitting a Run command, completing the controller, changing the action cursor, or ending battle**. The normal wild quick-run R shortcut remains intact; link and recorded battles retain their distinct behavior.
- `data/battle_scripts_1.s` and `include/battle_scripts.h`: create and declare `BattleScript_PRU_CantQuitTrainer`, a proper **selection script** that prints the existing no-running-from-trainers message and calls `endselectionscript`. It must not call `end2` and accidentally finish an active battle.
- `src/battle_main.c`: defensive intercept of any stale/unexpected `B_ACTION_RUN` from a local HNS trainer battle, ahead of both the Frontier and normal trainer forfeiting branches. Set `STATE_SELECTION_SCRIPT`, then `STATE_BEFORE_ACTION_CHOSEN` as the safe return destination. Link and recorded battles are exempt.
- `CanPlayerForfeitNormalTrainerBattle` returns FALSE in HNS, blocking other accidental entry into the normal forfeit endpoint. The original non-HNS logic is left unchanged.
- `test/test_pru_trainer_battle_no_quit.py`: new *source-only* audit for the above invariants, including preserved wild/Link behavior.

**Before any ROM release:** run the complete source tests and a fresh compile, then use mGBA to attempt Run/forfeit from ordinary singles, trainer doubles, boss/Elite Four, scripted trainer battles and challenge modes. Confirm repeated A-presses cannot leave the fight or freeze, fight/bag/switch still work, defeat/victory and rematch flags still advance, wild run/R quick-run succeeds normally, and Link/Safari/recorded behavior has not regressed.

**Do not build, publish, merge, or trigger Actions until explicitly approved.** The next separate queued item is the repeatable ¥5,000 Day-Care Mystery Egg seller.


## Day-Care repeatable Mystery Egg seller — source checkpoint (1 November 2026)

**Scope:** Stage on `prep/pru-rockshop-no-build-20261101`; no ROM build, release, main-branch merge, or automatic Actions run.

**Changed:**
- `src/daycare.c`: new `PruBuyDaycareMysteryEgg` script special using the existing `CreateEgg` function. It checks real party count vs `GetMaxPartySize()` (including challenge cap), then money, chooses a canonical baby uniformly, checks species and egg cycles, creates and validates an actual Egg, inserts into the party, then deducts **exactly ¥5,000**. Returns separate codes for success, full party, insufficient money or invalid egg data. No charge on refusal, insufficient funds or invalid Egg. Shared special gets a non-HNS linkage stub; no save IDs or flags added.
- `data/specials.inc`: registered `PruBuyDaycareMysteryEgg`.
- `data/maps/Route34_DayCare_hns/scripts.inc`: dedicated NPC script with offer/decline, full-party, insufficient-funds, unavailable and success responses. The original one-off `giveoddegg` clerk and the free breeding Move Expert are unchanged.
- `data/maps/Route34_DayCare_hns/map.json`: one permanently available Lass NPC at **(9,7)**, not overlapping another NPC and inside the 14×11 map bounds. **Collision tile and walk-up accessibility have not been verified in the emulator.**
- `test/test_pru_mystery_egg_seller.py`: focused static regression for pool, correct order of capacity/money/delivery/charge, script, NPC and original services.

**Final approved Mystery Egg pool: 13 species, all drawn uniformly from PRU's canonical 450.**

| Group | Species |
|---|---|
| Kanto starters | Bulbasaur, Charmander, Squirtle |
| Johto starters | Chikorita, Cyndaquil, Totodile |
| Hoenn starters | Treecko, Torchic, Mudkip |
| Custom Relic babies | Scarabub (also called Herabub), Skarmet, Mootiny, Gemlin |

The original 12-species pool of ordinary baby Pokémon was **superseded by user instruction**. `src/daycare.c::sPruMysteryEggSpecies` and `test/test_pru_mystery_egg_seller.py` now require exactly these 13, with each species represented once. At the source level, Gemlin is defined in `src/data/pokemon/species_info/pru_custom.h` with nonzero `eggCycles`, while the three other Relic babies live in `pjr_families.h`.

The seller's dialogue now advertises a Starter or Relic baby, rather than only babies. The ¥5,000 transaction logic, unchanged Odd Egg event, repeatable purchases and no-charge safeguards stay intact. New game data are **staged only**, with no compiled/tested GBA.

**Release gate:** still needs full checkout source-test execution, clean compilation (only when authorised), and mGBA tests for NPC walkability, declining, purchasing twice, party full, challenge-limited party, exactly ¥4,999 and ¥5,000, hatch of all 13 (nine traditional starters and four Relic babies, including Gemlin), saving/reloading with an Egg, plus verifying the old free Odd Egg and Move Expert still work. Do not declare gameplay verified based only on static source checks.

**Next queued item after Mystery Eggs:** audit RELICS legendary encounter levels (80 except Alphoracle 90). Preserve existing hunt flags, encounter positions and caught/respawn rules.


## Single final Ho-Oh, legends 80/90/100 — staged source checkpoint (1 November 2026)

**Approved final design:** The previous ordinary Ho-Oh battle, its retry, and Professor Oak's separate Relic Ho-Oh summon are **retired**. There is exactly **one catchable Ho-Oh**, a **level-100 Relic Ho-Oh at Tin Tower roof**. Do not allow any earlier sighting/summon. NPCs may mention only uncertain rumours of a golden flying Pokémon until the post-RELIC finale. Preserve Oak's existing trainer fight, the Crest reward, and all unrelated story progression.

**The seven required catches before Ho-Oh:** Raikou, Entei, Lugia, I-Unown (`SPECIES_UNOWN_I`), Celebi, Suicune, and Alphoracle. All seven associated `FLAG_PJR_RELIC_*` flags must be set, along with `FLAG_PJR_GOT_RAINBOW_CREST` and physical possession of `ITEM_ANCIENT_RAINBOW_CREST`. They are checked on roof entry **and again immediately before starting the battle**, preventing old state variables or direct NPC scripts from bypassing progression.

**Implementation prepared:**
- `TinTower_RoofDay_hns/scripts.inc`: only one `seteventmon SPECIES_RELIC_HO_OH, 100` remains. Roof transition hides the old Ho-Oh/Kimono dance by default; only revealing the sole legendary after all seven RELICS and the Crest. Catching sets both new and legacy catch flags and hides the overworld sprite. Faint/escape leaves it available for a later attempt. Old saves with `FLAG_CAUGHT_HO_OH` are marked final-caught on visiting the roof, to avoid a **second** Ho-Oh. No new save flags or IDs were allocated.
- `TinTower_RoofDay_hns/map.json`: removed the original early Kimono dance coordinate trigger and extraneous offscreen Ho-Oh event object; the single real roof Ho-Oh object remains conditional on its hidden flag.
- `MtSilver_SummitDay_hns/scripts.inc`: removed Oak's separate Ho-Oh battle entirely; Oak's trainer battle still occurs. After winning, he directs the player toward the Tin Tower rumour. The old Crest reward and Alphoracle dialogue no longer forcibly reveal Ho-Oh early.
- `EcruteakCity_Theater_hns/scripts.inc`: completing the Kimono gauntlet no longer sets Ho-Oh's early story-spawn state or enables the old roof Kimono choreography. **The theater now finishes immediately at story state 8**, restoring its original dancers and townsfolk without making the player wait for the retired Ho-Oh fight; access to Tin Tower is still unlocked. Zuki's introduction and the girl/Zuki sightings now discuss only **rumours** rather than promising Ho-Oh's arrival.
- `TinTower_1F_hns/scripts.inc`: removed the sage/Eusine claims that Ho-Oh already descended; now only unverified folklore. `TinTower_RoofDay_hns/scripts.inc` also replaces the unused early ceremony dialogue with rumours.
- `RuinsOfAlph_Lab_hns/scripts.inc`: Alphoracle capture no longer spawns Ho-Oh by directly setting the old roof variable or clearing the hide flag; it can only lead the player to the final location.
- `test/test_pru_legendary_encounter_levels.py` and `test/test_pru_single_final_hooh.py`: audit battle levels, double gate, legacy catch handling, no early roof map trigger and no Oak summon.

**Encounter levels also staged:** `RuinsOfAlph_Lab_hns` hunt: Raikou/Entei/Lugia/I-Unown/Celebi/Suicune 80, Alphoracle 90. All scripted normal Lugia, Celebi, Rayquaza, Kyogre, Groudon, Articuno, Suicune, Deoxys and Mewduo instances inspected in the listed map sources have been brought to 80; Mewtwo's existing 80 remains. Both legacy and alternate Groudon maps now use 80. `Ho-Oh=100` is enforced **only at the final Tin Tower encounter**, including replay following fainting. Roaming tables, non-HNS builds and trainer-owned species remain out of scope.

**Still untested in ROM:** No compilation, GitHub Actions or mGBA run was initiated. Before release run all source regression tests, compile and mGBA-test first-time and existing saves (including legacy Ho-Oh caught and state=2/3/4), with zero through six captures, all seven captures without Crest, flag-only Crest without actual item, normal final catch, a faint/escape/retry, save/reload, Oak battle/epilogue, Kimono story progression and real NPC navigation. The new Ho-Oh sprite and forms must display properly.

**Important:** Older existing saves where the ordinary Ho-Oh was already caught will retain that Ho-Oh and have the final RELIC flag marked completed to avoid dupes. A truly clean one-Ho-Oh run requires a new game after this patch. No ROM build or release until explicitly approved.


## PRU credits replacement — source checkpoint (2 November 2026)

**Staged, not compiled or published.** `src/data/credits_pru.h` defines **29 original PRU credit pages**, each with five valid pointer slots, short credit lines and explicit project, engine, donor, visual-art and tool acknowledgments. `src/credits_hns.c` now includes it in place of the inherited display page table, so the existing shared HNS Hall of Fame and Elite 20 credit routine displays PRU pages rather than using Heart & Soul's full inherited pages. Full H&S contributor file `src/data/credits_hns.h` and upstream `CREDITS.md` are preserved in the repository.

The E20 prologue still precedes the shared PRU pages; its text now reads **A GOLDEN LEGEND STIRS**, retaining the existing flying Golden Relic Ho-Oh sprite and curated RELICS Pokémon montage. The existing music, scrolling/scenery engine, ending screen and soft reset remain untouched. This cinematic reference does **not** create an extra catchable Ho-Oh or change the unique late-game encounter gate.

`docs/PRU_CREDITS.md` provides a fuller human-readable donor ledger, distinguishing upstream original credits, community sprite sources and permission/authorship questions. `test/test_pru_credits.py` audits source links and layout. An additional readback source audit confirmed **29 contiguous pages, 29 five-pointer table rows, 87 lines of credit copy, each under 33 characters, all required filenames present and the Golden opening reference intact**.

**Release QA outstanding:** run Python source tests in a checked-out repository; compile only with explicit permission; verify text rendering, transitions, opening graphics, credits termination, completion flags and Master Ball rewards across Johto E4, Kanto E4 and E20 in an emulator. Review remaining unresolved third-party sprite permissions before public release. **No ROM build/release and no GitHub Actions requested.**

**Next substantive preparation item:** repair the 450-species Pokédex ordering and distinct seen/caught rows without renumbering species or disturbing save compatibility.


## Canonical 450-Pokédex and save-compatible tracking — source checkpoint (2 November 2026)

**Implemented and committed on the existing no-build preparation branch. No .gba, GitHub Actions workflow or emulator run was initiated.**

### Immutable, approved 450-species sequence

- `src/data/pokemon/pru_dex_order.h` remains the single ordered source. **All 450 entries are present, sequential and distinct**. Key checkpoints: #004 Edensaur, #007 Charizard, **#008 Charaxis**, #012 Fortotoise, #435 Lugia, #437 Alphoracle, #450 Deoxys.
- **No `SPECIES_*` numeric IDs, evolved species, in-game events, existing quest flags or species-table entries were renumbered.**
- The old HGSS implementation iterated regional/obtainable National Dex numbers and truncated at the last seen entry, explaining the player's scrolling video.

### HGSS-style Pokédex UI

- `src/pokedex_plus_hgss.c` uses `HGSS_LIST_CAPACITY = PRU_DEX_COUNT` in HNS/PRU, reserving **450 rows plus a sentinel**, rather than assuming the inherited 419-species visible sequence or the expansion's vanilla National Dex.
- Numerical order now displays **all 450 slot numbers**. Unseen species keep their masked name and no captured-ball icon; seen and caught names/details use the canonical species (not their inherited National Dex alias). The numerical mode can scroll through the unseen tail; it does **not** force every Pokémon into Seen or Caught.
- Info screens, stats numbering, cries, portraits, species details, alternate forms, evolution links, search parameters and in-Pokédex completion counters route through conditional HNS wrappers: canonical species lookup/number and independent flags. Non-HNS builds retain their native Nation/Regional lookup.
- Alphabetical, weight and height sorts operate on canonical species data; when nothing qualifies, the UI returns to the complete numerical list rather than underflowing the sorted selection. Selection is clamped to current list capacity.
- National visual mode is used for PRU even before the unrelated upstream National Dex unlock flag. The story save flag and non-HNS behavior remain unchanged.

### Independent Seen/Caught data with old saves

- `src/pokedex.c` adds `PruDexNumToSpecies`, `PruSpeciesToDexNum`, `GetSetPruDexFlag`, `GetPruDexCount`.
- Stores **two 450-bit records** (57 bytes each) in the already allocated SaveBlock1 `dexPadding1`/`dexPadding2`, with per-array four-byte `PRD1` initialization markers. Compile-time `STATIC_ASSERT` checks verify capacity. SaveBlock1 struct size and relative offsets, legacy National bits, game flags and species constants are unchanged.
- First migration copies legacy National seen/caught flags **only for species matching the original National Dex species**, not indiscriminately into every PRU variant with the same native number; scans existing party and non-Egg PC boxes to recover known owned Relic species. On future catches and wild sightings, both exact PRU bitfields and the engine's original National bits are updated. Catch-popup checks use the independent PRU caught flag, avoiding a Relic silently inheriting its ancestor's Seen/Caught status.
- **Honest limitation:** an old save's shared National Dex bit cannot identify which of two aliased custom species was previously caught if the unique species no longer exists in the party or PC. The migration cannot reconstruct that history without inventing progress. Reencountering or obtaining it again records it independently.
- `ResetPokedex` also clears the new padding bitfields when resetting the entire Pokédex.
- **No new save flags, event variables or saved species IDs were allocated.**

### Regression guard

- `test/test_pru_450_pokedex.py` checks canonical all-450 identity and numbering, separate storage, no-save-layout expansion, migration strategy, encounter/capture hooks, UI lookup wrappers, independent seen/caught totals, sprite and evolution routing and safe list bounds.
- A current-turn GitHub source readback passed **16/16 focused structural checks**. This is source validation, not compiling, save-compatibility certification or gameplay verification.
- Before release: run the full repository tests, clean compile **only on explicit permission**, inspect all 450 list rows and multiple sort/search orders in mGBA, compare fresh/old saves, check Charizard versus Charaxis and Venusaur versus Edensaur separate flags, test seen wild species, evolved and gifted Pokémon, egg hatch, Pokémon Box migration, last row and underflow, and confirm all UI thumbnails and evolution pages render correctly. Preserve a backup of the previous working save before applying the new build.

**Next preparation item:** stage the complete 450-species sprite-review assets and manifest, plus trainer-exclusive artwork in a separately labelled section. No automatic build, merge or release.

## Pokémon Infinity Eeveelution front-sprite polish — queued 2 November 2026

**Status: user-approved work request, NOT implemented, compiled or play-tested.** The user supplied [Pokémon Infinity's Eevee reference](https://p-infinity.fandom.com/wiki/Eevee) as the original donor source. The current PRU front sprites for Obsideon and related Eeveelutions look small/degraded and need a source-faithful 64×64 GBA front-art repair, not invented redesigns or a blind upscale of the already-imported PNG.

- **Primary Infinity donor group to review:** Obsideon, Champeon, Lepideon, Guardeon, Sphynxeon, Toxeon and Omeon. Also inspect Eeveeon, Nimbeon and Drakeon for the same import defects, verifying each donor's provenance before assuming all artwork came from the same pack.
- **Mootiny added to this same sprite-polish batch (3 November 2026).** Owner reports its current battle sprite looks rough and unclean, like the Eeveelutions. Inspect the actual compiled `graphics/pokemon/prl_authoritative/mootiny/front.4bpp.smol` and its source `assets/sprites/mootiny/front.png`, alongside normal/shiny palettes and `frontPicYOffset`; compare with the highest-quality approved Mootiny original. Restore crisp, intentional 64×64 pixel-art linework, correct proportions/shading, indexed transparency and palette, without blurry scaling, invented redesigns or changing species identity. Inspect back and party icon for related defects, but only replace them if genuinely defective or the owner approves an alternate design. Update the authoritative upstream asset/sync or CI pin so the fix survives a clean build; verify sprite in starter/egg-hatch context and battle. Do not alter the Job 2 Mystery Egg pool or evolution mechanics. **Queued only: no changes made to sprite graphics or released ROM.**
- Recover the highest-fidelity authentic Pokémon Infinity original front battle artwork legally available (and original normal/shiny palettes if provided). Compare originals pixel-for-pixel with the active PRU front sprites. Determine which failures are caused by donor crop, bad resize, palette conversion, animation frame selection, 64×64 compositing, centering, `frontPicSize` or `frontPicYOffset`.
- Convert with **nearest-neighbour only where scaling is necessary**; otherwise preserve 1:1 source pixels, correct GBA indexed transparency and <=16-colour battle palettes, coherent silhouette and framing. If the authentic artwork cannot fit naturally at 64×64, mark that species for manual pixel-art review, **not a smear/stretch or generative replacement**.
- **Critical CI/source-of-truth issue:** `.github/workflows/pru-clean-build.yml` restores Infinity donor PNGs from `assets/pjr_infinity/parts` and then executes `tools/pru/sync_prl_authoritative_sprites.py`, which fetches pinned PRL art into `graphics/pokemon/prl_authoritative/`; active front declarations in `src/data/graphics/pjr.h` point at this authoritative directory. Make the final approved front replacements survive both stages on every clean build. Do not merely edit `graphics/pokemon/obsideon/front.png` if that file is not the compiled front.
- Preserve all already-approved back sprites, party icons, animation identities, shiny exceptions, species numbering, ability/learnset changes (including the separate Skill Link branch), and evolution routes. This front-only scope must not regress any current PRU sprite decisions.
- Add a deterministic donor/source manifest and source-level regression test for all affected fronts (original source, installed path, palette/transparency, hash, effective final compile path). Include the fixed 450-species sprite-review exports in the existing `assets/pru_450_sprite_review/` task.
- **Release QA:** compare normal and shiny front sprites in an actual battle (correct player-facing enemy fronts, GBA animated-frame lookup, cropping, palettes, scale and offsets); run a repeat clean-build asset provenance check to ensure no build-step restoration silently undoes the fix. Record each species' before/after and attribution. No new ROM or release until separately authorised.

**Integration note (2 November):** A separate branch `feat/pru-skill-link-early-obsideon-20261102` at `ecb0739c0830f6b117459c0c2455cad646e794c7` contains committed Heracurion/Obsideon Skill Link, evolution-time Pin Missile / Arm Thrust / Rock Blast and a one-time Route 29 Hard Stone gift. Source structure checks passed; these changes have NOT been integrated into this no-build preparation branch, compiled or player-tested. Reconcile both branch heads when preparing the next explicitly authorised build. Preserve all newer Relic Hunt progress and save compatibility.

**Hold:** documentation update only. No gameplay edit, automated GitHub workflow, merge, ROM compilation or release.

## PRU-only 450-species randomizer pool — source checkpoint (2 November 2026)

**Owner requirement:** Never choose between Pokémon Gen 1–9 or Gen 1–3 in PRU's randomizer. The entire generated species pool must be a subset of the **same exactly 450 Pokémon** defined in `src/data/pokemon/pru_dex_order.h`. Preserve choice of randomization features (wild/trainer/egg/gift/static species, move/type/abilities, evolution methods, legend-aware balancing). No extra species, alternate forms counted as new Pokémon or off-roster output. Preserve saved Pokémon and save format.

**Source implemented on `prep/pru-rockshop-no-build-20261101`, not merged, compiled or released:**

- `src/randomizer.c`: builds its HNS species membership bitmask directly from all 450 unique `sPruDexSpecies` constants instead of 1–9 or 1–3 generation-family walks. The bitmask is used by `IsSpeciesPermitted` across the dynamic species tables and random-evolution methods. `IsGenScopeRestricted` forces TRUE for PRU irrespective of any existing save's historical `tx_Random_GenScope` bit, without reallocating/clearing that bit; non-HNS modes preserve their original behaviour. On an off-roster source and a failed group lookup, the HNS fallback selects an eligible canonical entry. Post-selection alternate forms are explicitly rejected if not themselves in the approved 450; the canonical base result is used.
- `src/challenge_menu.c`: the fixed informational **POKEMON POOL — PRU 450** row replaces the visible Gen 1–9 / Gen 1–3 options in PRU, ignores LEFT/RIGHT on that row and normalises saved value when editing settings. Other randomizer options remain operational. Non-HNS variants retain their original generation control.
- `test/test_pru_randomizer_450.py`: source guard added for exactly 450 unique canonical species, membership masks, form safety, evolution restrictions, old-save forcing and fixed menu, without changing species IDs or saved challenge-settings layout.
- Commits: randomizer `b7a492785f90`, menu `ef654c0d7056`, test `6712a60da22f`.

**Validation:** 11/11 focused GitHub source-readback checks passed, including roster length and uniqueness. **No Python test suite, ROM compile, mGBA execution, save-migration test, or randomized playthrough has run.** Before release test both Gen-scope values on old saves, all randomizer toggle combinations, randomized wild/trainer/static/gift/egg and evolution paths, exception species/forms, legend-aware balancing, empty-group and form-selection fallbacks. Verify every generated output's internal species ID belongs to the immutable 450 roster, and the new menu label renders cleanly. Protect saved Dex flags and all 450 existing Pokédex entries.

**Integration gate:** The no-build branch also contains other unmerged next-patch changes; the separate `feat/pru-skill-link-early-obsideon-20261102` branch needs reconciliation, as do newer approved Infinity Eeveelution art revisions. No automatic build, merge or release.

## Eeveelution Expert and Eevee in Ecruteak Rock Shop — added 3 November 2026

**Status: user-requested game addition, requirements documented only.** Build it as a small isolated feature on the newest successful PRU ROM lineage, not by merging the entire preparation branch. As of 3 November the latest independently published Rock Shop build was [`pru-build-b4967a4948`](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-b4967a4948), source `b4967a4948fcef832dc7ef95686fc707275b0054`. Recheck for newer confirmed playable releases and the branch HEAD before changes.

- **Location:** `data/maps/EcruteakCity_RockShop_hns/map.json` and `scripts.inc`. Add a *dedicated, permanent, friendly Eeveelution Expert* with a **visible Eevee standing on the neighbouring tile**, so the pair clearly belong together. The Eevee is a non-interfering decorative overworld Pokémon (optionally one short line/cry), **not** a giveaway, gift or encounter. Reuse existing suitable approved Eevee overworld sprites/object event systems; avoid an invented graphics constant. The shop currently has a clerk at (2,3), collector at (7,5) and a door at (4,7). Inspect actual layout/collision/NPC limits, choose two adjacent walkable, interactable tiles away from the shop counter and doorway, and preserve all existing NPC scripts. Avoid hidden/overlapping sprites, blocking movement or warp.
- **Gameplay:** Talking to the expert opens a clear *repeatable optional guide* with concise category choices or paginated dialogue. Teach how to obtain **each of PRU's exact 17 Eeveelutions** through **direct item use**, not canonical friendship/time/location tricks or holding items through level-up. Item names and methods below come from the `#if IS_HNS` Eevee evolution table in `src/data/pokemon/species_info/gen_1_families.h` on the published PRU lineage:

| Evolution | Direct-use item |
| --- | --- |
| Vaporeon | Water Stone |
| Jolteon | Thunder Stone |
| Flareon | Fire Stone |
| Espeon | Sun Stone |
| Umbreon | Moon Stone |
| Leafeon | Leaf Stone |
| Glaceon | Ice Stone |
| Eeveeon | Ancient Stone |
| Nimbeon | Shiny Stone |
| Omeon | Dusk Stone |
| Champeon | Expert Belt |
| Lepideon | Silver Powder |
| Sphynxeon | Soft Sand |
| Guardeon | Metal Coat |
| Obsideon | Hard Stone |
| Toxeon | Poison Barb |
| Drakeon | Dragon Fang |

- **Do not mention Sylveon** or invent other Eevee evolutions: `sPruDexSpecies[450]` does not include it, and the HNS Evee evolution table has exactly 17 reachable entries. Do not add new Pokémon or change evolution conditions to fit the dialogue.
- **Clarity:** Show players that in PRU, Expert Belt, Silver Powder, Soft Sand, Metal Coat, Hard Stone, Poison Barb and Dragon Fang are **used on Eevee from the Bag**, even when those items are normally held items elsewhere. Distinguish which stones are stocked now, which are stocked after Fog Badge, and which special items come from elsewhere. If stating where to find Eevee or a required item, verify the actual current map/shop source first; never fabricate a location or suggest an item is sold in the Rock Shop when it is not.
- **Testing:** source regression asserting the expert and Eevee objects exist in this map, occupy distinct collision-free tiles with a walk-up route, original clerk/collector/warp still work, every one of 17 species + item mappings exactly matches `#if IS_HNS` `Eevee` data and no Sylveon is advertised. Run relevant existing Job 1–3 regressions; compile and publish a valid new 32 MiB ROM only for an explicitly authorised Work run. In mGBA where available, walk to both NPCs, cycle all pages/menu branches, and use representative items to evolve Eevee. Do not claim emulator QA without execution.
- **Credit / durability:** minimise Work credits; preserve all earlier ROM fixes; commit and push each meaningful implementation/checkpoint; keep `docs/PRU_WORK_RESUME_CHECKPOINT.md` and the PRU Notion Development Journal up to date with exact SHA, actual tests and next action. If interrupted, prioritise pushed source + GitHub and Notion resume instructions. No unrelated sprite overhaul or job backlog changes.

## Approved next job: Sylveon replaces Luvdisc, 450-species Pokédex stays capped (3 November 2026)

**User-approved decision:** Sylveon must return to PRU and **replace Luvdisc as one of the 450 canonical species**. The owner has already sent the previous Eeveelution Expert NPC prompt to Work, so **DO NOT amend, interrupt or merge this change into that running NPC job**. Apply the following in a separate next Work prompt, **starting from that job's latest confirmed successful published ROM and checkpoint**, not from the older Ecruteak baseline. The preceding 17-evolution instructions in this document describe the *already sent previous NPC job* only; **this newer decision supersedes them for subsequent ROMs**.

- **Exact Pokédex family order:** In \`src/data/pokemon/pru_dex_order.h\`, insert \`SPECIES_SYLVEON\` **immediately after \`SPECIES_GLACEON\`**, as the **last Eevee evolution**, before Porygon. In the current 450 order Eevee is #167, Glaceon #184; Sylveon therefore becomes **new display #185**. Remove \`SPECIES_LUVDISC\` (formerly **display #417**) from the canonical Pokédex. Recalculate every displayed number consecutively, retaining exactly **450 unique canonical species**. Insertion at #185 shifts the old #185–416 entries forward one place; the former #417 Luvdisc entry vanishes and later species retain their original numbers after the offset cancels. Do **not** append Sylveon at #417 or leave an unexplained gap.
- **Critical save compatibility:** The ordered display/Pokédex number is **not** the internal species ID. Keep existing Pokémon internal species constants, IDs, party/PC data, moves and item IDs intact. Sylveon already has underlying engine support; do not repurpose the Luvdisc species ID or delete Luvdisc engine data. Audit existing Pokédex Seen/Caught indexing/migration on old saves, including the queued 450-save migration changes; map by stable species IDs rather than blindly copying per-number flags. Luvdisc may still exist in old parties/saves and should not become corrupt. Update any derived 450 roster, forms, randomizer whitelist, RelicDex/docs and regression tests consistently; avoid accidentally merging unrelated pending Pokédex/randomizer preparation code.
- **Evolution:** In the active HNS Eevee evolution table \`src/data/pokemon/species_info/gen_1_families.h\`, add one **direct-use Dawn Stone → Sylveon** entry. Verify the Dawn Stone genuinely works when used directly on Eevee (not just held or used in regular non-HNS variants), and retain the other 17 approved direct item evolutions exactly as before. Preserve Fairy typing and Sylveon's existing correct sprites, palettes, icon, stats, move data and abilities. Dawn Stone remains the item sold at the Ecruteak Rock Shop after Fog Badge. Verify actual item-use behaviour. No other Eeveelution condition changes.
- **Rock Shop Eeveelution Expert:** Once the earlier NPC job is complete, update the guide from **17 to 18 Eeveelutions**, add **Sylveon — Dawn Stone**, and accurately state Fog Badge stock if offered. Do not remove or disrupt the expert, its companion Eevee, or the shop's 50% discount. Avoid GBA text overflow; update conversation/navigation regression checks accordingly.
- **Replace Luvdisc content thoughtfully:** Removing Luvdisc from the *canonical 450 roster* does not automatically erase it from engine data. Audit HNS wild encounters, NPC decorative uses (Route 25 contains Luvdisc overworld objects), gifts/trades, trainers, breeding and other player-accessible species generation; ensure the game does not newly award out-of-roster Luvdisc. Replace/retire affected in-world occurrences in a lore-appropriate, save-safe way only where required; do not edit default non-HNS game variants. Preserve other existing species and scripted encounters.
- **Release gate:** Dedicated regressions for 450 count/uniqueness, Eevee family contiguous display ordering, #185 Sylveon, no #417 Luvdisc, no save-ID renumbering, Dawn Stone evolution and all other Eevee evolutions, expert dialogue 18/18, old save handling, Luvdisc off-roster references, and any randomizer/egg/encounter whitelist. Compile a new 32 MiB GBA ROM after the active NPC job; mGBA/gameplay test where available and disclose missing tests. Record exact previous and new ROM/hash.
- **Work efficiency and continuity:** minimise Work credits, reuse existing source where possible, commit and **push** coherent milestones plus \`docs/PRU_WORK_RESUME_CHECKPOINT.md\` after each one; update the [PRU Notion Development Journal](https://app.notion.com/p/3ff4939d4316814e9b74c8508d790925) at the same checkpoints, with test state and exact resume instructions. If credits run low, preserve pushed code and Notion state first. **This line is documentation only; no game source modification, build, or release has been authorised in this turn.**


## Next prompt addition: restore original H&S Alph B1F ladder / warp behaviour (3 November 2026 — donor verified, implementation queued)

**Owner instruction:** Stop layering ad-hoc fixes on the Alph ladder; restore its ordinary behaviour exactly as in the **original Heart & Soul ROM/source**. **Do not edit the active Sylveon Work session**; include this as a dedicated high-priority section of the **next Work prompt after Sylveon's latest confirmed playable ROM**. This is a documented comparison only, not an implemented or emulator-tested fix.

**Original donor verified:** [PokemonHnS-Development/pokehns-expansion](https://github.com/PokemonHnS-Development/pokehns-expansion) \`master\`. Compare this original donor before coding; for reproducibility pin the then-current donor commit SHA. Exact original source paths:

- [Original B1F warp map](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/master/data/maps/RuinsOfAlph_B1F_hns/map.json) — Git blob \`1af963a96190defb735147cd57f078c2c3e08772\`.
- [Original B1F scripts](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/master/data/maps/RuinsOfAlph_B1F_hns/scripts.inc) — blob \`64bb356b1f06ce3cf62fda676f68d5b27e7a81a0\`.
- [Original B1F map tiles](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/master/data/layouts/RuinsOfAlph_B1F_hns/map.bin) — blob \`df4677c7cce828c5b5643a87bc7e96927a59d44d\`.
- [Original B1F metatile attributes](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/master/data/tilesets/secondary/ruins_of_alph_b1_f_hns/metatile_attributes.bin) — blob \`9124ef5235fe8172a7dcafeffcb8750716066fc6\`.
- Original \`data/maps/RuinsOfAlph_Outside_hns/map.json\` blob \`e206eb3051d0a1158ee3b554fe30018afd54b14e\`, **identical to current PRU**.
- Original \`data/maps/RuinsOfAlph_PuzzleAndRewardChambers_hns/map.json\` blob \`b736735d4227284df729d2c204289355671638d7\`, **identical to current PRU**.

**Concrete differences already confirmed by comparing donor files to PRU checkpoint \`c52b6f5e78974b613859e80f40b5f2408857b795\`:**

1. Original B1F has **exactly five** warp events. Warp index **0** at (15,16) → \`MAP_RUINS_OF_ALPH_OUTSIDE_HNS\`, destination warp **5**. Original B1F warp indices **1–4** lead to PuzzleAndRewardChambers destination indices **8,10,6,4** respectively. PRU added another outside warp at (15,15) **as index 1**, shifting the four puzzle-room warps to indices **2–5**. However, the adjacent PuzzleAndRewardChambers' unchanged returns still point at old B1F indices **1–4**! This mismatch is a concrete correctness bug and must be fixed by **restoring donor warp order**, rather than editing the puzzle-room returns.
2. Original B1F has no \`RuinsOfAlph_B1F_EventScript_ExitLadder\`, no \`bg_events\` scripted interaction at (15,15). PRU added both; remove these redundant extras when restoring donor behaviour, without changing non-ladder event scripts (I-Unown, Alphoracle, etc.).
3. Comparing 29×32 tile-map binaries, exactly **four** PRU tile cells differ from donor, at the **two custom statue positions**: (16,9),(16,10),(25,27),(25,28). **Entrance/exit cells (15,15) and (15,16) have the same map tile values as donor in the committed source.** Retain the four approved statue background-clearing changes; don't wholesale restore the map.bin.
4. Original B1F metatile attribute at index **100** is **0x0008**, at index **101** is **0x1061**. PRU committed attributes are **0x0061** for both. Original lower exit cell (15,16) is **0x42e5** (metatile 741 including elevation 4); PRU checked-in map.bin also has this value, but \`tools/pru/install_ruins_alph_statues.py\` **modifies it on CI builds**, clearing bit \`0x4000\` (changing elevation 4 to 0). That same script also forcibly rewrites attributes 100 and 101 to \`MB_LADDER 0x61\` during CI; merely changing checked-in files won't survive a clean build. Restore donor ladder attributes/elevation and remove CI re-patching specifically for the entrance ladder while preserving statue-tile installation. Check all active workflows for equivalent runtime patching.
5. The existing \`tools/pru/test_ruins_alph_cleanup.py\` has a test **requiring** the extra (15,15) warp, ladder BG script and changed attributes/elevation; **update those assertions** to enforce the real H&S donor behaviour (five ordered warps, original metatiles/attributes, original bidirectional route) while preserving the custom statues.
6. Existing mGBA script \`tools/pru/playtest_alph_ladder_ci.py\` starts a temporary test ROM at B1F (15,17), holds UP **60 frames**, then evaluates an exterior screenshot using a hard-coded brown-pixel fraction/luminance threshold. This has failed with 'brown fraction 0.1881' and 'No textured exterior frame after warp'. Diagnose whether holding Up traverses additional tiles or the screenshot captures a transition/fade, or the warp actually fails. A screenshot-colour heuristic is **not proof of the current map**. Make a reliable real-input test that takes deliberate step(s), waits for completion, and validates **actual loaded map ID / coordinates / warp target** (with image evidence only as supplementary). Test both entering from outside (21,21) and exiting B1F, plus all four puzzle-room returns and the statue interactions. Compare behaviour against a temporary donor H&S test ROM where feasible. **Do not mask or remove failed tests to publish falsely.**
7. **Do not replace** the approved Eye of Alph I-Unown statue at (16,10), Alphoracle monolith at (25,28), their flags/scripts or their underlying four modified statue cells. Do not change the GS Ball, room puzzles, other entrances, story gates, Pokémon data, earlier jobs or saves.
8. Targeted source-level donor parity check (pin donor blobs/values locally) plus a clean CI build and real mGBA traversal. If emulator cannot prove the result, report failure or untested rather than 'fixed'. Don't silently weaken tests. Keep GitHub code+resume checkpoint and Notion journal up to date after coherent milestones, minimise Work credits, and deliver a valid 32 MiB GBA on success.

**Current status:** Donor retrieved and compared; exact implementation is queued **only** for the next prompt after the currently running Sylveon job. No PRU game code changed by this documentation entry.
