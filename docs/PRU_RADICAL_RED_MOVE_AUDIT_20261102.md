# Radical Red v4.1 move audit — 2 November 2026

## Reference and limits

Primary reference: [Radical Red Dex](https://dex.radicalred.net/?table=movesTable). The live page labels its save-data control `Upload save file (v4.1)`, but the requested moves-table URL currently renders the species table; selecting its Move filter and searching does not return move records. The Dex therefore establishes the v4.1 reference, but could not provide a complete machine-readable move catalogue in this session.

Version-specific cross-check: [Radical Red v4.1 changelog](https://gbacodes.com/pokemon-radical-red-changelog/). The changelog says some Scarlet/Violet DLC buffs may be undocumented, so this audit covers the move additions and move-specific fixes it explicitly names, plus the requested Dark Void case. It does not claim an exhaustive learner-by-learner parity audit.

Dark Void's baseline modern values were cross-checked against [Pokémon Database](https://pokemondb.net/move/dark-void), which lists 50 accuracy and 10 PP.

## Findings and changes

| Move or group | PRU source at baseline | v4.1 comparison | Result |
| --- | --- | --- | --- |
| Dark Void | Dark type; modern accuracy 50; targets both foes; applies Sleep; existing Dark Void animation; 10 PP; Gen 7+ battle rule rejected all users except Darkrai; I-Unown did not learn it | v4.1 allows Hypno to learn it; 10 PP and 50 accuracy are retained | Keep its 10 PP, spread target, Sleep effect, animation and 50 accuracy. Add Dark Void to I-Unown's level-1 learnset and allow I-Unown through the existing battle and AI restriction while preserving the Darkrai restriction for other species. |
| Omen Eye | 95 power, Ghost, 100 accuracy, 10 PP, selected target, 20% Fear, Mean Look animation | PRU-specific move, not a Radical Red move | Unchanged and guarded by the regression check. |
| Supercell Slam | 100 power; existing Electric physical recoil-on-miss effect, 95 accuracy and animation | v4.1 raises 100 BP to 120 BP | Raise power to 120; retain its existing effect and other move data. |
| Flash | Existing accuracy-lowering move, marked Magic Coat affected | v4.1 fixes Flash being affected by Magic Coat | Set `magicCoatAffected` to false. |
| Tidy Up | Existing effect script calls hazard clearing before its stat changes; implementation traverses both battle sides | v4.1 fixes hazard removal | Already present; no code change. |
| Loaded Dice multi-hit | Engine already selects 4–5 hits for ordinary multi-hit moves and 4–10 for Population Bomb | v4.1 fixes Loaded Dice interactions for Triple Axel, Population Bomb and Triple Kick | Existing source path is present; no code change. |
| Dragon Tail | 10 PP | v4.1 lists a Dragon Tail PP fix | Already at 10 PP; no code change. |
| Other v4.1 move additions named in the changelog | IDs and one move-data record each are present in PRU | Alluring Voice, Barb Barrage, Burning Bulwark, Electro Shot, Fickle Beam, Flip Turn, Grassy Glide, Heat Crash, Jet Punch, Lunge, Mighty Cleave, Psychic Noise, Shed Tail, Tidy Up, Thunderclap, Upper Hand and Vacuum Wave | No missing move IDs or placeholder records found in this documented set; no duplicate move IDs added. |

No new move IDs or forms were introduced. The documented v4.1 move fixes above use existing engine effects. Other v4.1 learnset/compatibility edits are not bulk-imported because PRU has its own species availability and progression decisions.

## Verification state

- `tools/pru/check_dark_void_i_unown.py`: source regression passes, including move registration, Dark Void target/effect/PP/learnability/restrictions, Supercell Slam's 120 BP, Flash's Magic Coat flag, and checks for the already-correct Tidy Up, Loaded Dice and Dragon Tail source paths.
- `git diff --check`: passes.
- Clean ROM build and gameplay testing: pending. Local ARM GBA compiler is unavailable; the existing GitHub clean-build workflow is the next build path.
- The web Dex's inaccessible move-table records remain a limit on full catalogue and species-learnability comparison.
