# Pokémon Relics Ultimate — ending credits & attribution

**Source-only preparation checkpoint · 2 November 2026.** All PRU/HNS endings use the original PRU on-screen credits defined in `src/data/credits_pru.h`, displayed by `src/credits_hns.c`. **No ROM has been compiled, released or gameplay-tested from this checkpoint.**

## Presentation

- **29 compact screens** beginning with **POKÉMON RELICS ULTIMATE**, project direction, story, design and the development foundations.
- The same PRU credit pages are used for the Johto and Kanto Hall of Fame endings, plus the Elite 20 sequence. The E20-specific two-page prologue remains, as does the existing **Golden Relic Ho-Oh sprite flyby and three-at-a-time RELICS montage**. Its written teaser is now **“A GOLDEN LEGEND STIRS”** rather than revealing the final catchable Ho-Oh before the hunt.
- The credits' original window renderer, background transitions, song, ending screen, soft-reset path and all postgame event-script reward handling are **left unchanged**. **Visual quality, timing and rewards still require compilation and in-game validation.**
- No early in-game Ho-Oh encounter, catch flag or story bypass is introduced by the credits.

## PRU team and production

| Attribution | Role in the on-screen credits | Additional detail |
| --- | --- | --- |
| James Howard | Project lead, story and creative direction | User-directed PRU design, content and integration |
| GitHub | Development workflow and version control | Not credited as an artist or original game developer |
| OpenAI / ChatGPT, Anthropic / Claude, Google / Gemini | AI-assisted code and documentation workflows | Not represented as authors/owners of third-party sprite art |
| PokéSprite and Porypal | Art, icon and palette tooling/resource acknowledgements | Attribution is to the named projects, not an assertion that they created each PRU sprite |

## Original code, ROM-hack teams and artwork provenance

| Source or contributor | On-screen acknowledgement | Evidence in this repository / follow-up |
| --- | --- | --- |
| **pret/pokeemerald** | Engine foundation | Inherited decompilation engine; retain original upstream notices |
| **rh-hideout/pokeemerald-expansion** and contributors | Battle and Pokémon system foundation | Original `CREDITS.md` in repository includes contributor acknowledgements |
| **Pokémon Heart & Soul**, Lil Dill and contributing artists/programmers | Johto/Kanto maps, game foundation and team | Full inherited contributors still listed in `src/data/credits_hns.h`; the original file is **retained**, not deleted |
| **Crystal Advance** / Kertra and **Johto Redrawn Team** | Map/tileset foundations | Named in inherited Heart & Soul credits; verify exact derivative assets before a public release |
| **Crystal Legacy / The Smith Plays** | Gameplay and dialogue inspiration | Named in inherited Heart & Soul credits |
| **Pokémon Infinity** | Donor sprite sources | `assets/pjr_infinity/` and related source/asset integration history; attribute individual images by their actual authors when known |
| **Pokémon Insurgence** | Donor sprite sources | `assets/insurgence_front_sources/` and other donor archives; individual sprite authors must be audited |
| **Pokémon Tourmaline**, tdilos | Skarmet artwork donor | `docs/PRU_SKARMET_TOURMALINE_ARTWORK_20261020.md`: Tourmaline credits PTickles for concept art and AtecainCorp for SpaceWorld beta sprites. **Exact Skarby battle-sprite authorship and redistribution permission are unresolved** |
| **Pokémon Rhythm**, artists | Battle backgrounds | `docs/PRU_RHYTHM_BG_ASSET_PROVENANCE.md` documents scene sources and permission reported by the project owner |
| **Azul Agua** | Ecruteak Rock Shop donor artwork | `assets/pjr_azul_agua/rock_shop_tiles.png.b64` and `building_tiles.png.b64`. Verify final author/usage terms if shipping beyond the existing project |
| **Pokémon Team Rocket Jessie & James**, MrNightology | Jessie and James donor battle/overworld sprites | `docs/PRL_JESSIE_JAMES_DONOR_CREDITS.md`; individual graphic artists and reuse terms still require verification |
| **Steevee & Neevee / Jessie & James intro art** | Custom battle intro artwork | `docs/PRL_DUO_TRANSITION_ASSET_PROVENANCE.md` — original approved source pack, not an invented new artist |
| **Ekat99, WesleyFG, Kalarie**, other artists | Tileset/environment contributors | Credited in the inherited Heart & Soul data; asset-level mapping pending |
| **slawter666** and **wally-217** | Unique surfing Pokémon overworld sprites | Existing Heart & Soul source credits provide the reference thread |

### Important attribution principle

The game contains artwork and code from many more individuals than can fit in its 240×160-pixel credit screens. **The on-screen sequence is a concise acknowledgement, not an exhaustive legal or asset-by-asset provenance ledger.** Preserve the full inherited `CREDITS.md`, `src/data/credits_hns.h`, all existing documentation and licences. The on-screen phrase `SEE DOCS/PRU_CREDITS` refers to **this** file. A named project being credited does **not** establish redistribution permission for individual assets. Exact artist credits and permissions remain open where the provenance documents say so.

Pokémon, its characters and associated intellectual property belong to their respective rights holders, including Nintendo, Creatures and GAME FREAK. PRU is an unofficial fan project; acknowledgment of a tool, studio or donor does not imply endorsement.

## Acceptance checklist before release

1. Source-check each of the 29 credit pages for exactly five entries (blank padding where appropriate), valid symbols, GBA-compatible text and single use of the PRU page table.
2. Compile `make hns` only when approved and confirm the 32 MiB ROM, no missing symbols or overflow.
3. In mGBA, view **each** Johto, Kanto and Elite 20 credit sequence in full. Verify no inherited Heart & Soul title or unrelated Game Freak employee roster is displayed **as PRU's production team**, while inherited teams receive explicit credit.
4. For E20: verify the Golden Relic Ho-Oh flyby (cinematic teaser, **not a wild encounter**) appears, the RELICS montage remains, and the E20 completion, Oak quest opening and six Master Ball award still work.
5. Confirm save, soft-reset, return-to-field and postgame flags/rewards are unchanged.
6. Review all reused source/artist credits before public release; add specific creators to this file and/or on-screen credits when verified.

**Do not merge, build, publish or trigger GitHub Actions until the user authorises the integrated ROM.**
