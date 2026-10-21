# PRU Astrachi — Mt Moon Square encounter integration handoff (22 October 2026)

**Status: staged design and sprite preparation ONLY. Do not merge into main or build a player ROM until the concurrent Jirachi sprite update has landed.**

## Approved user decision
- Keep the current Mt Moon Square Jirachi event, camera and battle untouched.
- After **Jirachi is actually CAUGHT**, touching the same white stone a second time invokes **Astrachi** (Lv70) at exactly Jirachi's location in the pond.
- The second summon duplicates Jirachi's reveal: sound, exclamation/question, shake, white fade, pan down, hopping object, cry, pan back, and regular static legendary battle.
- For Astrachi, use the **Claude-provided 22 Oct overworld sprite** (lower, crisp PNG sheet), not Jirachi or a generated replacement. Leave Astrachi's existing front/back/icon and data untouched.
- Stone text for the second event:
  "The stone begins to shimmer once more..."
  "A forgotten wish has awakened!"
- Caught Astrachi is permanently gone; on faint/defeat Astrachi should reappear after leaving and returning to Mt Moon Square. Running retains the encounter.

## Exact existing master source inspected
- `data/maps/MtMoon_Outside_hns/map.json`: Jirachi object local id `LOCALID_MTMOON_JIRACHI`, `x:13`, `y:11`; stone bg event `x:13`, `y:5`.
- `data/maps/MtMoon_Outside_hns/scripts.inc`: `MtMoon_Outside_EventScript_WhiteRock`, `MtMoon_Outside_EventScript_WhiteRockSpawnJirachi`, `MtMoon_Outside_EventScript_Jirachi`, `MtMoon_Outside_Movement_CameraPanDown/Up`, `MtMoon_Outside_Movement_Jirachi`.
- Existing Jirachi summon flag `FLAG_SUMMONED_MTMOON_JIRACHI` only means 'summoned', **not** caught.
- Existing Jirachi uses `OBJ_EVENT_GFX_MON_BASE+SPECIES_JIRACHI` and `FLAG_HIDE_MTMOON_JIRACHI`.
- `SPECIES_ASTRACHI` exists in `src/data/pokemon/species_info/pru_custom.h`; types Psychic/Fairy, Wishmaker ability, existing sprites and moves, but currently **lacks an OVERWORLD(...) registration** and aliases `NATIONAL_DEX_JIRACHI`. Do not treat this alias as independent caught tracking.
- `include/constants/battle.h`: `B_OUTCOME_CAUGHT=7`, `B_OUTCOME_RAN=4`, `B_OUTCOME_WON=1`.

## Integration implementation checklist (after the other chat's Jirachi changes)
1. Sync latest PRU `main` **after Jirachi sprite update**; inspect modified script and graphics before patching. Do not overwrite that work.
2. Register `graphics/pokemon/astrachi/overworld.png` plus `overworld_normal.pal` and `overworld_shiny.pal` and required `sPicTable_Astrachi`/palette symbols. Add an `OVERWORLD(...)` entry to Astrachi's species data, matching Jirachi's 32x32 footprint and frame ordering. Preserve palette index 0 as transparent.
3. Add a **second map object** with `local_id:LOCALID_MTMOON_ASTRACHI`, graphics `OBJ_EVENT_GFX_MON_BASE+SPECIES_ASTRACHI`, at `(13,11)`, same elevation/facing as Jirachi. Never have both visible simultaneously.
4. Introduce **distinct durable Astrachi caught / hide / summon flags** using verified unoccupied save flag IDs; audit against latest `flags_hns.h` and save compatibility. Do not consume a conflicting value in HNS's tightly packed hide/quest ranges.
5. The stone's second-use gate must check Jirachi caught **specifically**, not just summoned or battled. Implement a script-callable caught check from current Pokédex data or explicit Jirachi catch-state migration; account for existing player saves where Jirachi was caught before this feature.
6. Copy *current* Jirachi's summon camera, movement, cries, sfx and battle control for Astrachi, changing only its species/local id, Level 70 and second-use messages. Preserve the current night/day constraints of the existing shrine unless explicitly overridden.
7. On Astrachi `B_OUTCOME_CAUGHT`, permanently set its own caught flag, remove/hide its object, and block future stone summoning. On KO/defeat, remove temporarily and make it available on map reentry; on RUN, allow retry. Use `GetBattleOutcome` rather than assuming all non-runs are captures.
8. Confirm own caught/seen/dex registration: current Astrachi species data points at `NATIONAL_DEX_JIRACHI`; the wider PRU 444-Dex pipeline must not falsely mark Astrachi caught when Jirachi is caught. Keep distinct flag in any case.
9. Build HNS ROM, inspect 32 MiB GBA, smoke test mGBA, and gameplay test on the current user save. Do not distribute a ZIP as the player's ROM.

## Target test matrix
- Jirachi untouched/not yet caught: original stone event; no Astrachi.
- Jirachi battled, defeated or escaped: no Astrachi unlock.
- Jirachi CAUGHT: second stone use produces Astrachi Lv70 on the same (13,11) tile.
- Both Jirachi and Astrachi objects never overlap; no overwrite of new Jirachi overworld sprite.
- Astrachi run: retry possible.
- Astrachi defeated: exit/re-enter; second summon works again.
- Astrachi caught: never respawns, even after reload.
- Existing save with Jirachi caught before patch: unlock works.
- Animated front/up/left/right Astrachi frames, alpha and palette work in PokeBall-sized field sprite; water reflection/camera match Jirachi.

## Provenance and scope
Claude user-provided two sprite sheets in the ChatGPT conversation of 22 Oct 2026. The PNG source is the sharper/lower sheet with 9 provided designs; frames have been laid out in a 128x128 4x4-style GBA-compatible contact sheet pending engine-specific animation validation. Credit the user-provided/Claude asset in final `CREDITS.md`. **No Jirachi source, art, event, map or built ROM is changed by this prep branch.**
