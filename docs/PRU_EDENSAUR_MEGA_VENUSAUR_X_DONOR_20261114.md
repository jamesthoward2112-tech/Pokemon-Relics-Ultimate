# Alpha 5 — Edensaur uses Elite Redux Mega Venusaur X artwork

**User-selected NextDex source:** https://forwardfeed.github.io/ER-nextdex/?v=2.65.5&p=2188&t=929

This URL's Pokémon ID **2188** corresponds to **VENUSAUR_MEGA_X**
(`SPECIES_VENUSAUR_MEGA_X = 2188` in Elite Redux source).
Original donor directory: https://github.com/Elite-Redux/eliteredux-source/tree/upcoming/graphics/pokemon/venusaur/mega_x

The five donor files are copied **byte for byte** into
`graphics/pokemon/prl_authoritative/edensaur/`:

| File | Format | Exact source Git blob SHA |
|---|---|---|
| front.png | 64×64 indexed 4bpp | e0b162a5c1f9167a4f5bdc6991b8af1c6a58b0fa |
| back.png | 64×64 indexed 4bpp | de5d9668dbeae1f403c4b604f7a7ccfe9e36e158 |
| icon.png | 32×64, two 32×32 icon frames | 523e647999488633e3bf9660a1a45bee94930567 |
| normal.pal | 16-colour JASC palette | 94625d901b3d2479ba33a2e6a28f9dd6e6dd0558 |
| shiny.pal | 16-colour JASC palette | 40bc068b4d9bed64eb38e52f28edda2ebfa85889 |

**Important engine details:**

- The donor icon palette is *exactly equivalent at GBA 5-bit RGB depth*
  to Edensaur's existing `sPRUEdensaurIconPalette` (index 21).
  Retain `GetPruCustomIconPaletteIndex(SPECIES_EDENSAUR) = 21`.
  Do not remap or recolour the icon.
- The donor back PNG's internal indexed PLTE matches its shiny palette;
  its in-game normal colours are supplied by the separate
  `normal.pal` during sprite assembly. This matches the source's
  normal back rendering in NextDex. Do not rebuild the back from the
  embedded preview colours.
- The PRL sprite sync preserves all five Edensaur donor files and the
  existing PRU custom graphics references through
  `REPO_ASSET_OVERRIDES` and `PRU_VISUAL_OVERRIDES`.
- **Art only:** Keep Edensaur as Edensaur in the 450-species PRU game.
  No Mega evolution mechanic, additional species, extra Pokédex slot,
  stats/typing/moves/abilities change, evolution change, or save reset.
- This patch is based on the existing Alpha 5 branch *after* the
  complete Sopranice-to-Mystynx donor update; both remain intact.
  Do not build on the older `main` branch.

**Release checks still required:** compile the Alpha 5 ROM; inspect the
normal/shiny Edensaur front/back in battle and both icon frames in party,
storage PC and summary screen. Verify Mystynx, Feralodon and current
Alpha 5 learnset/event fixes have not changed.

Credit the Elite Redux project for the donor sprites in release documentation.
