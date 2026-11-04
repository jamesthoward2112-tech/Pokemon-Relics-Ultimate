# PRU sprite restoration and 70-species audit

## Acceptance

- Preserve the successful #542 ROM, its ten original-size build-538 Eeveelutions, Mootiny, Miltitan, Pyroclast, gameplay data, IDs and saves.
- Install the supplied, indexed normal G-Max Blastoise Fortotoise front/back art after all older sprite import stages; its icon must match the installed sprite.
- Use genuine, distinct backs for the four Jessie & James forms. Do not manufacture backs for the ten Elite Four Relic forms; report missing authentic sources clearly.
- Audit all species IDs 1573–1642 against the final post-installer source tree, report source/art path and technical metadata, and generate donor-grouped pixel review sheets with transparency shown.
- Record human/emulator review separately from automated checks; never claim technical checks prove visual correctness.
- Keep the #542 ROM and original save intact. Publish a separate 70-species inspection save with the new ROM.

## Scope and preservation

Changes are limited to sprite assets/install precedence, sprite QA/report tooling, tests, release packaging, and documentation. No species, Pokédex, battle, map, story, save-layout, or evolution data changes are intended. Build #542 is the fallback.

## Verification

Run the sprite pipeline regression and full source tests, perform the clean 32 MiB release build, validate compiled graphics and the inspection save, then check any real emulator evidence separately. Unavailable authentic back art remains unresolved.
