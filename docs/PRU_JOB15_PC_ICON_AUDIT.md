# PRU Job 15 — PC icon defects from the 5 November 2026 video

**Baseline:** Job 14 playable release `b57ade8693e439447bd596c77721fd53c33e7f6b` (preserves approved Fortotoise and baby sprites, Job 12 Celebi gating, 450-Dex and saves).

## Exactly 15 Pokémon with an opened context menu

| Pokémon | Actual runtime palette | Diagnosis | Action in this commit |
|---|---:|---|---|
| Nimbeon | 2 | Icon colour indices mismatch game's palette (cream/blue source displays yellow) | Flag for individual icon restoration |
| Drakeon | 2 | Purple/red source displays yellow | Flag |
| Champeon | 2 | Red/pink source displays yellow | Flag |
| Grimfowl | 2 | Black/grey source displays bright yellow/red | Flag |
| Kablowfish | 0 | Grey/pink source displays hot-pink/purple | Flag |
| Sunflorid | 1 | Orange/green source displays washed yellow | Flag |
| Sudowarden | 1 | Natural green source displays yellow/magenta | Flag |
| **Gemlin** | 16 | Source and palette colours correct, **PC marking UI palette tag collided with icon tag 16**; party separate | **PC tag collision fixed and wasted palette slot freed; original art unchanged** |
| Sceptitan | 1 | Source palette compatible; icon close to 32×32 edge, crowding and detail issue | Preserve art; visual QA |
| Solaziken | 0 | Source palette compatible; icon close to 32×32 edge | Preserve art; visual QA |
| Cactomb | 1 | Dark green source displays yellow/magenta | Flag |
| Coelossus | 2 | Source palette matches game exactly; nearly fills 32×32 frame | Preserve art; visual QA |
| Tropisaur | 1 | Source palette matches game exactly; nearly fills 32×32 frame | Preserve art; visual QA |
| Torkaldera | 2 | Source palette matches game exactly; nearly fills 32×32 frame | Preserve art; visual QA |
| Gemigoyle | 2 | Magenta/charcoal source displays rainbow-yellow | Flag |

**Nine definite colour-mapping failures; five compatible-palette icons still visually flagged; one PC-only collision.** The number and names come from reviewing the actual moments where the user opened the Pokémon context menu (45-second video). It is not a claim that every hovered Pokémon was selected.

### PC-only palette fix implemented

- The PC had `PALTAG_DISPLAY_MON` at `POKE_ICON_BASE_PAL_TAG +14`, and `PALTAG_MARKING_COMBO` at `+16`, **the same tag as Gemlin's new bespoke icon palette**. The PC reused/wrote its marker colours while the party screen used Gemlin's correct purple/blue colours.
- Move the PC's UI palette tags to the separate base `+32` upward, without touching the global icon palette numbering or any icon pixels.
- Stop eagerly reserving a scarce OBJ palette for Swamplith in *every* box; its icon palette already loads correctly on-demand when Swamplith is visible. This restores one hardware palette slot, helping Gemlin and other custom icons.
- Reduce the unrelated PC preview mosaic from 10 frames to 2, avoiding dramatic temporary pixel blocks.
- GBA still has **16 physical OBJ palette slots**. More bespoke icons in a busy box may exceed these; the fix addresses one definite tag collision and needless preload, not a universal guarantee for every combination.

### The large temporary pixels are not destroyed artwork

The 64×64 Pokémon preview on the left used an intentional **10-frame mosaic reveal** (`StartDisplayMonMosaicEffect`), producing huge blocky previews before the menu opens. This patch reduces it to a subtle **2-frame reveal**, so legitimate artwork appears crisp promptly. This is separate from true **PC/party icon palette mismatches** and is not a malformed PNG.

### Why the other nine are not blindly recoloured in this patch

Nine icons use mismatched palettes. The correct original art is available, but simply shrinking or mapping the pictures to an arbitrary shared palette noticeably makes Grimfowl green, Nimbeon purple, etc. A common-palette candidate was generated and **rejected** for quality. Their replacements require separately reviewed true GBA 16-colour icon palettes, at 32×64/two-frame dimensions, mindful of the GBA's 16-palette display budget.

**No Pokémon battle artwork, icon pixels, stats, names, map events or save structure changed in this fix.**

### Evidence and verification
- `docs/PRU_Job15_Selected_PC_Icons_Source_vs_Runtime.png` — existing 15 source-icon pixels rendered both with their PNG palette and with the colours the game actually assigns.
- `tools/pru/check_job15_pc_icon_palette.py` — asserts 15 audited assets, all nine mismatches, no UI/icon tag overlap, exact unchanged approved Gemlin icon, palette RGB agreement and loading on demand.
- CI includes this test before ROM compile. A manual busy-PC-box visual check is still recommended for tag/palette saturation and the remaining selected icons.
