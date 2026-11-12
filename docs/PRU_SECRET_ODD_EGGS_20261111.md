# PRU — Route 34 Secret Odd Eggs

Updated: 11 November 2026.

**Development status:** Source change on branch `fix/pru-four-secret-eggs-and-nursery-clues-20261111`. This is **not part of downloadable public Alpha 3**. A new ROM build and full in-game egg/password/hatching/save-persistence QA are still required. No GitHub Actions ROM build was run.

## Nursery-rhyme NPC

A separate NPC outside the Route 34 Day-Care recites these clues. Four baby Pokémon overworld sprites wander nearby (Pichu, Cleffa, Igglybuff and Togepi). The NPC does not reveal what the phrases unlock and remains available for repeat conversations.

| Clue | Egg Pokémon | Easy Chat password (in order) |
|---|---|---|
| Baby Bug | Scarabub | GUTS / BUG / BABY / PLAY |
| Baby Bird | Skarmet | STURDY / FLYING / SILVER / SHINE |
| Baby Calf | Mootiny | THICK FAT / NORMAL / CUTE / SLEEP |
| Baby Gem | Gemlin | KEEN EYE / GHOST / MYSTERY / SHINE |

Each custom egg is independently obtainable once per save via four persistent flags; their normal fixed day/night wild encounter slots are removed. The original Pokémon evolution families and 450-species Pokédex remain unchanged.

## Seven original Odd Egg choices

The Day-Care couple's son retains the original seven baby Pokémon (one classic Odd Egg per save):

| Pokémon | Easy Chat password (in order) |
|---|---|
| Pichu | STATIC / ELECTRIC / WAAAH / PLAY |
| Cleffa | CUTE CHARM / NORMAL / EEK / LOOKS |
| Igglybuff | CUTE CHARM / NORMAL / LALALA / SLEEP |
| Tyrogue | GUTS / FIGHTING / HIYAH / TRAINS |
| Smoochum | OBLIVIOUS / ICE / EHEHE / SHOW |
| Elekid | STATIC / ELECTRIC / OI OI OI / STORES |
| Magby | FLAME BODY / FIRE / TCH / ANGERS |

Players need a free party space to receive an egg. The development implementation is intended to preserve existing save files and allow all four new babies in one playthrough.

## Move Relearner cleanup

Disable the summary-screen Move Relearner shortcut (party-menu shortcut was already disabled). Keep the dedicated NPC Move Relearner available.

## Approved Gemlin artwork

On 11 November, the user confirmed the new Gemlin normal front and rear-three-quarter back sprites in the local **Alpha 3 Gemlin + All 22 Backgrounds Fixed** QA ROM. ROM SHA-256: `7be1f821f66084941c61cd1d0349a2db8f9a6638d2a7d8de37cb9becd103d59e`. Website PNGs were recovered exactly from this ROM's Smol-compressed sprites and GBA palette, **not redrawn**. The party icon remains unchanged. The approved sprite is not to be replaced by the older small purple Gemlin image in future website or ROM updates.

## Implementation/source paths

- `src/easy_chat.c` — 11 four-word passwords.
- `src/scrcmd.c` — species mappings for 11 eggs.
- `data/maps/Route34_DayCare_hns/scripts.inc` — independent custom egg claim events.
- `data/maps/Route34_hns/scripts.inc` and `map.json` — nursery-rhyme NPC and wandering babies.
- `src/data/wild_encounters.json` — six replaced fixed encounter slots.
- `include/constants/flags_hns.h` — per-baby persistent flags.
- `include/config/summary_screen.h` — summary shortcut disabled.
- `data/scripts/new_game.inc` — reset custom claim flags.

**Website:** https://relicdex.github.io/odd-eggs.html (source design guide; four custom eggs explicitly marked as upcoming).
## Alpha 4.2 update: typed SINGLE-word passwords (2026-11-12)

The player uses the existing 11-character GBA Enter code keyboard, with
special EnterCode; waitstate; specialvar VAR_RESULT, PruCheckOddEggSingleCode.
This replaces the four Easy Chat words for all Day-Care eggs.
All other game Easy Chat functionality is untouched.

Index | Egg | Typed code
1 | Pichu | PICHU
2 | Cleffa | CLEFFA
3 | Igglybuff | IGGLYBUFF
4 | Tyrogue | TYROGUE
5 | Smoochum | SMOOCHUM
6 | Elekid | ELEKID
7 | Magby | MAGBY
8 | Scarabub (Baby Bug) | BEETLE
9 | Skarmet (Baby Bird) | FEATHER
10 | Mootiny (Baby Calf) | MILK
11 | Gemlin (Baby Gem) | CRYSTAL

Case-insensitive. The reachable Baby Expert outside Route 34 Day-Care
now provides the four single-word custom codes in the same order.
No new save flags or species are added; original one-classic-Egg-per-save
flag and four independent custom Egg claim flags remain untouched.

Source:
- src/field_specials.c: PruCheckOddEggSingleCode
- data/specials.inc: new special appended after all original special IDs
- data/maps/Route34_DayCare_hns/scripts.inc: keyboard flow and dialogue
- data/maps/Route34_hns/scripts.inc: nursery clues

Codes are stored in a temporary string variable, not the save data.
