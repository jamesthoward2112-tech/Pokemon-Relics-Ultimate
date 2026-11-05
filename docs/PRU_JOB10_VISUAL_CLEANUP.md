# PRU Job 10 - remaining custom sprites and PC icons

Baseline: Job 9 `768ca315f8`, branch `feat/pru-relic-hunt-20261101`.

## Intent
Clean the overlarge, poorly framed PC icons without replacing the custom Pokemon's
approved artwork, changing any sprite's palette, or breaking previous sprite repairs.

## Implementation
- Run `tools/pru/install_job10_sprite_icons.py` as the FINAL icon installer,
  after the existing video-review stage, so earlier sprite imports cannot
  overwrite the cleanup.
- Inspect the 70-species custom roster's ROM-linked icon paths. Select only
  individually owned custom species icons, never shared vanilla donors.
- Preserve both 32x32 animation frames, their source palette, 4-bit colour
  indices, palette-0 transparency, design, and body proportions.
- Bound selected icons to 24x24 occupied pixels with nearest-neighbour scaling,
  horizontally centred and 1px above the bottom of the 32x32 frame.
- Preserve Pyroclast (approved) and Nolax (excluded from prior video review).
  Preserve original approved Fortotoise/Charaxis appearance; change framing only.
- Include I-Unown's special icon only if its palette and red-eye/dark palette
  indices can remain unchanged.
- Publish generated `PRU-QA/job10/icon-changes.json` and the enlarged
  `before-after-icons.png` contact sheet.
- Do not alter maps, story, battle data, moves, Pokemon species IDs, Pokédex
  ordering, save block layouts, or any `*.sav` file.

## Acceptance and limitations
- `tools/pru/check_job10_sprite_icons.py` passes after all prior installers.
- Run `tools/pru/audit_custom_sprites_70.py`, Job 8's 450 Pokédex check and
  Job 9's trainer-forfeit check again.
- A clean CI build must emit a 32 MiB `.gba` and mGBA boot inspection.
- Ten Elite Four Relic forms still have no approved, authentic battle rear
  donors. They remain technical FAIL until genuine rear art is supplied;
  DO NOT flip/mirror the fronts or mark them visually correct.
- Static contact sheets and boot testing are not equivalent to a human PC-box
  and battle-side visual review. Complete that separately.

This Job 10 pass is a reliable icon-sizing milestone, not a claim that all
70 battle views and 450 Pokemon were manually visually approved.
