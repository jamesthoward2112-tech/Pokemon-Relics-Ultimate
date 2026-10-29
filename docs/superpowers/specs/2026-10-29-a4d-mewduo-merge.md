# PRU a4d393129e stable-base Mewtwo/Mewduo merge

James's authoritative stable reference is `Pokemon-Relics-Ultimate-a4d393129e.gba`, built successfully in Actions run 40579466155 from commit `a4d393129ec3683f0443a80272df71653a3874af` on `fix/pru-indigo-tutors-20261027`.

## Required outcome

- Build from that exact source, never from the later Mewduo branch with tutor regressions.
- Preserve nine **visible**, adjacent, upward-facing Indigo support NPCs on floor tiles x=6..14/y=15, including distinct level-up and egg move tutors. Preserve their introductory yes/no dialogs.
- Preserve the stable PC/party move-tutor selection snapshot and expanded move-specific eligibility, including special evolutions. Keep every existing stable move option and its compatibility. The user found only six visible NPCs and poor move learnability in the later branch.
- Add the previously approved Shadow Mewtwo donor front/back/icon art, dual Psychic/Dark stats, signature Dark Nova and supporting new moves without changing Giovanni's Armoured Mewtwo or the existing Mewtwo species/flag IDs.
- Add the Level 90 Mewduo encounter at Cerulean Cave B2F after Mew and Mewtwo are caught and the cave is re-entered; it should disappear permanently only when captured. Preserve prior saves and Relic Candy item 910.
- Preserve Mewduo's approved battle art. Mewduo's overworld must be **the exact working six-frame vanilla Mewtwo graphic with its palette recoloured**: white/grey body, red tail and lower belly. Do not replace/reduce the real Mewtwo overworld graphic or redraw its silhouette.
- Give Mewduo Permafrost at 90, Psystrike at 95, Dark Matter at 100. Fix its party-icon red/grey palette and ensure the first encounter's caught Poké Ball is independent of Mewtwo's existing Dex record.
- Keep the original Johto/Kanto Elite Four, Elite 20, Rhythm backgrounds, Hall of Fame, credits and other a4d functionality. Elite 20 gameplay issues will be addressed separately.
- Deliver a checksum-verified **raw `.gba`**, no ZIP, after an actual compiled build and emulator checks. Never claim source checks prove visual gameplay.

## Implementation decisions

- Keep the a4d source files for Indigo map, tutor scripts, tutor selection/party menu, and baseline compatibility logic; append only new move cases and script choices required by Shadow Mewtwo.
- Use Mewtwo's **stable overworld graphics data** for Mewduo too, with a dedicated indexed palette. This avoids the later overworld replacement and tests the game-visible graphics path, not just an unused PNG.
- Keep all existing numeric species, item, move and quest identifiers stable; append new identifiers only if absent from a4d.
- Preserve the existing save file untouched. Any save-based emulator tests operate on temporary copies.
