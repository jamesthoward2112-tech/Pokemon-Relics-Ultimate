# Rocket Balloon Cinematic Design — 25 October 2026

## Intent
James's live Route 22 video shows the balloon renders, but Jessie, James and Meowth remain stationary in a spread-out line, then disappear simultaneously as the Meowth balloon materializes. The escape should show characters deliberately reuniting, boarding, and visibly flying away.

## Goals
- On Kanto Route 22, after stealing the story-only Badge Case, Jessie and James step toward Meowth, forming a tight trio.
- The authentic 64x64 Meowth balloon visibly flies down from above the screen into its pickup location, with a fly sound.
- Each Rocket moves one tile toward its basket, then disappears individually (Jessie, James, Meowth); the balloon visibly ascends out of the scene.
- Repeat the motion-based boarding and fly-away choreography after the Jessie/James Indigo finale.
- Preserve actual Kanto/Johto badge flags, heist progression, guard warp lock, and the original balloon artwork. Preserve existing event object IDs (Route 22 trio 12–14, balloon 15; Indigo trio 1–3, balloon 4).

## Non-goals / anti-goals
- No permanent static balloon or new sprite art.
- No sudden simultaneous trio removal or balloon appearance in the centre of the courtyard.
- No new encounters, badge logic, modifications to League door guard, or gameplay gates.

## Approaches
1. Existing instantaneous swap (rejected by gameplay video): lowest scripting effort, no choreography.
2. Render entirely new composite trio-in-basket animation (rejected): new art, extra VRAM/palette footprint, long implementation.
3. **Selected based on prior user instruction to carry on with PRU fixes:** reuse all approved sprites, apply event-script movement, start balloon off-screen above the gate, descend to the basket, board each NPC in turn, ascend. Small, source-controlled and compatible with old saves.

## Implementation notes
Route 22 initial balloon map position: x12,y6; move down six tiles to x12,y12; Indigo balloon start x11,y4; move down six tiles to x11,y10. Change event movement scripts only, and map initial balloon coordinates. Stage after the current badge theft / Rocket finale dialogue. Ensure the trio starts to move before the balloon appears. Movement commands and pauses should be visible at normal game speed, while the old door guard remains untouched.

## Verification
Static regression script must assert correct local IDs, gathered movement, balloon start/end positioning, descension before boarding, staggered removeobject commands, and ascent. Full canonical GBA build must be green. Gameplay animation still requires user video QA; compiled ROM alone cannot establish visual correctness.
