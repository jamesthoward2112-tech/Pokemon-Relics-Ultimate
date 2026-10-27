# Elite 18 — trainer-only sprite bank

These are optional **trainer battle cosmetics**. Do not use them to replace
the standard Arcanine, Raikou, Entei or Suicune species graphics, or their
wild/party appearances. Do not create Pokédex species for these designs.

| Battle | Existing species | Trainer-specific asset | Provenance |
| --- | --- | --- | --- |
| Blue's ace | Arcanine | `blue_arcanine_mega/{front,back,icon}.png` | PJR Elite Redux `ARCANINE_MEGA.png`, James's approved *bottom-left* E4 design |
| Elm | Raikou | `elm_raikou_amp/{front,back}.png` | TRE Johto special candidate #1006, Raikou-& |
| Elm | Entei | `elm_entei_amp/{front,back}.png` | TRE Johto special candidate #1008, Entei-& |
| Elm | Suicune | `elm_suicune_amp/{front,back}.png` | TRE Johto special candidate #1011, Suicune-& |

Arcanine's original 64x64 battle PNGs and 32x64 icon come directly from the
approved PJR Elite Redux front/back/icon donor ZIPs, unchanged.

The TRE beast PNGs are reconstructed as transparent native-size 64x64 sprites
using point sampling of the **ROM-extracted front/back comparison contact
sheet** `TRE_Beast_Candidate_Fronts_Backs.png`, whose six exact designs were
approved for this trio. This was necessary because the separate October PRL
`approved_legendary_beasts_Team_Rocket/` migration-pack images are the
**ordinary** beasts, not the requested `-&` forms. The source ROM is
`Pokémon TRE Johto Release.gba`. Verify the extracted ROM's native palettes
and compression before using these in a release build.

**Integration guard:** import this bank only when the associated Elite 18
trainer battle exists and apply via a trainer/battler-scoped cosmetic front
sprite/palette override (cf. the existing Kimono Ghost special art pathway).
Never point the global species `frontPic`, `backPic` or icon at this bank.
