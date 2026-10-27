# PRU Indigo Tutor Repair — Design

## Intent

Repair the Indigo Plateau Pokémon Centre's support row and tutor eligibility without changing the League, Dojo, story or existing save layout. These changes address observed failures in the 32 MiB ROM released as `pru-build-15413a8492` (SHA-256 `699bb54a...`).

## Requirements

- Nine distinct, visible NPCs at consecutive grid positions, all facing north, with no gaps: level-up relearner, egg tutor, setup, doubles, hazards, cleanup, deleter, ability/nature, and EV/IV.
- The original early-game Daycare Move Relearner stays exactly as it is. Indigo gets an additional, independent Level-Up Relearner, not a relocation.
- Each NPC introduces its service and asks Yes/No before opening menus or selecting a Pokémon. Declining never alters any Pokémon.
- Keep services free and support normal party/PC selection where the underlying service already does.
- Shuckle/its Relic evolution can learn Sticky Web; Valkiri can learn Mindwave; Psychic tutor moves are available to Psychic Pokémon, Shockwave Fist to compatible Fighting Pokémon, Metal Barrage to Steel Pokémon. Preserve existing regular TM/tutor access and exclusions for eggs/out-of-Dex species.
- Test the actual selection/teaching gate, not merely whether strings appear in source. Cover several positive and negative species/move pairs.
- Preserve save compatibility and every unrelated map, trainer, script, and release. The approved PRU roster target is **450 species**. The current source still stages 447 and reserves #448-450 for later work; this tutor-only patch does not silently treat 447 as final or alter the Dex.

## Approaches

- **Chosen:** nine separate adjacent NPCs with specialist scripts; isolate changes to the Indigo map/scripts and move tutor selection/eligibility. This keeps each service discoverable and avoids modifying shared relearner menus.
- Alternative: fewer multipurpose NPCs. Rejected by the user, who wants individual specialists.

## Verification

Run focused source tests, engine tests for tutor eligibility, then the repository's canonical GitHub Actions ROM compile and mGBA smoke test. Publish only after successful evidence; leave E4 and Dojo gameplay to separate testing.
