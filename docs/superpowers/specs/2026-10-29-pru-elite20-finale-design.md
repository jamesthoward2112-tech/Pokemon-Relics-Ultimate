# PRU Elite 20 finale, rewards and RELICS hand-off — approved design

## Intent and constraints

The end of the twenty double battles at Saffron's Fighting Dojo must feel like PRU's actual grand finale. Keep the current stable `d46842dd24` lineage and existing E20 art, teams, 450-species IDs, original RELICS catches, crest flags and save layout intact. A player who already completed all twenty rounds must be able to experience and claim the finale once without fighting them again.

## Approved experience

- After the full E20 gauntlet, Oak and Elm congratulate the player, present the **Elite 20 Champion** distinction and tell the R→E→L→I→C→S RELICS story. Elm alludes to an ancient resonance following the Kanto League; Oak promises a later encounter on Mt Silver once the RELICS quest is complete.
- One-time tangible prize: **six Master Balls and five Ancient Stones**, with no duplication through rematches or reloading. A full Bag must not silently consume any prize. The existing Lv100 individual-pair rematches stay available.
- Show a distinct Golden Relic Ho-Oh flight, Kanto/Johto journey montage, six-member party Hall of Fame and custom PRU Elite 20 champion credits. The normal running-Suicune credits are not suitable for this finale.
- Defeating Red on Mt Silver no longer triggers the full credits; preserve the existing Crest reward and already earned quest flags.
- Maintain Oak's eventual Mt Silver encounter for the post-RELICS Ho-Oh payoff, and include a shorter epilogue then. The current repository has Red at Mt Silver and Relic Ho-Oh on Tin Tower; relocate or integrate this carefully in a separate tested progression batch, without removing any already caught Pokémon or blocking an existing save.

## Approach

Chosen: add save-safe, one-time E20 reward state and explicit finale trigger at the existing Dojo steward, then adapt the current in-game Hall of Fame/credits machinery with new assets. Do not wholesale replace the engine or splice in a donor ROM's binary credits. Work in small, individually buildable batches: rewards/dialogue first; credits presentation and Red exit second; the Mt Silver/Oak epilogue and full RELICS integration last.

Rejected: replacing all credits globally (would regress both League championships); giving items whenever E20 clear flag is read (would duplicate rewards); making the RELICS collection dependent on a newly added E20 prerequisite (would risk save compatibility).

## Verification

Regression tests must verify the exact six/five quantities, independent claim flag, bag-full retry, retroactive E20-cleared path, no cross-contamination of League or RELICS flags and no credits at Red. Run relevant existing source tests and a clean GitHub Actions GBA compilation for each pushed batch; do not claim runtime visuals checked without mGBA.
