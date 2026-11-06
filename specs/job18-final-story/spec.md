# Job 18 — Final story and Guardian Dragonite

## Requested behaviour

- Keep Oak as the final Elite 20 battle; his victory dialogue introduces a mysterious Ultimate Ancient Relic without revealing its location.
- The Ruins of Alph lab scientist sends the player to Mt Silver only after both the final Elite 20 victory and the seven RELICS are recorded, with useful incomplete-state dialogue for every branch.
- Replace the Mt Silver Oak battle with an original, increasingly obsessive but ultimately respectful summoning scene. Golden Ho-Oh remains the sole catchable Ho-Oh and can be safely retried after an uncaught battle.
- Replace the Tin Tower Kimono Girls' Ho-Oh ceremony with the unique, non-catchable Level 60 Ancient Guardian Dragonite battle, using the exact approved front/back/icon asset pack and exact requested set.
- On Golden Ho-Oh capture, play the established Job 16 cinematic and Job 17 credits once, give the existing six Master Balls once, and resume safely.

## Acceptance scenarios

1. Oak's Elite 20 victory is retained and does not set the Mt Silver summon/catch flags.
2. Alph lab dialogue independently recognizes missing Oak victory, missing RELICS, both missing, and both completed, including earlier saves.
3. No Mt Silver Oak battle remains. After prerequisites, Oak can summon the sole Level 100 Golden Ho-Oh; defeat/run-away permit a retry; capture marks the existing completion flags exactly once.
4. The exact attached Dragonite art is used only for the Tin Tower guardian. Its internal species identity is an existing trainer-only Dragonite visual form, so no Pokédex species is added.
5. The guardian has Multiscale, Weakness Policy, Adamant nature, 31 IVs, 252 HP / 252 Atk / 4 Spe EVs and Dragon Dance / Dual Wingbeat / Dragon Claw / Roost, at level 60. Victory completes the ceremony without making Dragonite catchable.
6. Existing successful saves are reconciled without replaying completed ceremonies or receiving a second Ho-Oh/reward.
7. Golden Reign, Phoenix Soul, credits artwork/montage, Red, the 450-species roster, Job 17 changes, and all unrelated map content remain intact.

## Preservation and validation

- Preserve all current save IDs and append any new event flags; do not modify main or playtester saves.
- Keep the sole Ho-Oh gating on the final Elite 20 flag and all seven existing RELIC flags. The Ancient Rainbow Crest item is not a gate.
- Run focused source regressions, the canonical 32 MiB build, battle-engine checks, and the repository's existing mGBA workflow. Gameplay-specific ceremony/save-file QA must be reported separately from source and CI results.

## Known constraint at specification time

The repository contains sprite-inspection fixtures, but no pre-Dragonite Tin Tower playthrough save. A genuine pre-battle save must be captured in mGBA from progressed game state; an empty or fabricated `.sav` is not acceptable.
