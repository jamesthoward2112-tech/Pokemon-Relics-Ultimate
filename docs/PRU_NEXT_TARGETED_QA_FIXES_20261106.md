# PRU next targeted QA fixes — 6 November 2026

Keep latest accepted Job 17 credits, Golden Ho-Oh cinematic, debug Win Encounter, save compatibility and existing game fixes.

1. **Frytning normal ability — implemented in source**: Previously Plus/Minus, now both ordinary ability slots are Levitate. Existing Frytning with either saved ordinary slot will therefore use Levitate without save editing. Hidden ability is unchanged; Dark/Electric type and Thunder Stone evolution stay unchanged. Verify in party summary and battle.

2. **Text overflow — remaining targeted fix**: screenshots show Skullberus move-page RIP AND TEAR description visibly clipping/overprinting, crowded five-row move list, and I-Unown info page ability/memo heading collisions. Reproduce on real GBA UI and fix line wrapping/window offsets without truncating mechanics or altering other screen layouts.

3. **I-Unown party icon outline — remaining targeted fix**: currently has red outline; user wants grey outline. Keep dark body and intended inner accents. Change only the affected icon asset/palette and check party menu, PC and summary. Avoid global palette changes or touching battle front/back sprites.

Release a combined targeted QA ROM only after all three fixes are tested, not merely after the source ability change.