# PRU Lavender battle scenes and sprite polish

## Intent

Make Lavender Spirit Tower battles consistently eerie, eliminate Swamplith's PC-only colour changes, and restore the approved Pyroclast artwork and lower back-sprite placement.

## Scope and constraints

- All seven Lavender Spirit Tower floors use the existing static Crystal Redux graveyard scene (#19) for ordinary and scripted battles. The other 37 donor scenes, 16 Gym scenes, fog, stairs, Escape Rope and quest remain unchanged.
- Correct the PC-specific Pokémon icon palette-tag collision and avoid spending scarce PC sprite palette slots on icons that are not currently needed. Party-menu behaviour stays unchanged. Swamplith's approved two-frame icon and literal donor colours remain unchanged.
- Pyroclast front uses the original, indexed 64×64 `TYPHLOSION_MEGA.png` in Library archive `PJR_Elite_Redux_Fronts_73.zip`, unaltered. Existing normal palette already matches the source exactly. Preserve the approved back image, party icon and shiny palette; change only its battle back anchor so it sits lower.
- Do not change Pokémon IDs, saves, battle gameplay or other locations' background selection.

## Approach

Use one explicit seven-map override in the established Crystal Redux background picker, fix PC palette tags and loading at the storage UI boundary, and replace the active compiled Pyroclast front asset rather than its unused legacy copy. Keep small regression checks adjacent to existing `tools/pru` audits.

## Alternatives considered

- A new custom haunted background would add unapproved artwork and asset conversion, so reuse the existing graveyard scene.
- Replacing the Swamplith icon or recolouring its palette would discard the approved art and not solve the PC tag conflict; correct the storage UI instead.
- Redrawing Mega Typhlosion would fail the user's exact-source request; import its original PNG bytes.

## Verification

Show the new regression failing on current main, then passing on the branch; run existing Tower, Crystal Redux and sprite audits, compile in canonical GitHub Actions, and leave in-game emulator QA as a separate user-visible check.
