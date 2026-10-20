# Original PRL duo battle-transition assets — provenance and integrity

**Restored to the canonical PRU repository on 20 October 2026.**

The approved artwork originates from the user's ChatGPT Library asset pack:

`/Pokémon Relic Legacy/Generated Assets/Battle Transitions/PRL_Duo_Animated_Trainer_Transitions_GBA_Assets_20261011.zip`

The original ZIP, GIF/MP4 storyboard approvals, and `PRL_Battle_Transitions_Integration.md` remain in the Library for historical provenance. Source files below were imported **byte-for-byte** from the original approved archive, with the Eevee-twins filenames changed to match the current engine's internal `eevee_twins` identifier. No image was regenerated or recoloured.

| Repository filename under `graphics/battle_transitions/prl/` | Original source in ZIP | SHA-256 |
|---|---|---|
| `jessie_james.png` | `jessie_james/jessie_james_tiles.png` | `ac7318687d5e297bdfb46d11106f2bcdc75fa844992b999f989c59ddea91d6fa` |
| `jessie_james.bin` | `jessie_james/jessie_james.bin` | `724962a93f219537967c1b313d1d1ff6f19859a1306272eff9b099b3b12e9484` |
| `jessie_james.pal` | `jessie_james/jessie_james.pal` | `04909505575521ae8d1dd24b84b71a2e53b4bdfa84f42613280044914326bb6d` |
| `eevee_twins.png` | `steevee_neevee/steevee_neevee_tiles.png` | `f259b0fc79c9b2cb67de1e94e5bf75fd1f8d6b928f7e0cc1f9569a0132c72c28` |
| `eevee_twins.bin` | `steevee_neevee/steevee_neevee.bin` | `839a517cbec2298a3ddfb346313fff657d9a7c5318df5ee1f4664e109ffd541c` |
| `eevee_twins.pal` | `steevee_neevee/steevee_neevee.pal` | `d6f2f3d3ea4fb369ec905313eac3818523fa8bb4424139811c7745c0e4fbe5ad` |

Both imported atlases are `128×256` indexed 16-colour GBA source PNGs (512 8×8 tiles). The accompanying binary `.bin` map is 2,048 bytes (32×32 16-bit entries), with **palette bank 15 embedded in all entries**. The colours of the PNG indexed palettes were compared against the JASC `.pal` source values and match exactly.

The migrated PRU transition implementation incorrectly loaded palette bank 13. In the *PRL duo transition initializer only*, that bank has been corrected to **15** in `src/battle_transition.c` (preserving native PatternWeave timing and other transitions).

**Verification completed:** Original ZIP extraction, PNG dimensions/mode/palette check, matching JASC palettes, BG tilemap bank check and exact SHA-1 Git blob matching.

**Still required:** full new-repo `make hns` source compilation, mGBA boot and visual in-game comparison of both intros; verify no art deformation, no incorrect transparency and no regression to other battle transitions. This source import is not itself user gameplay verification.
