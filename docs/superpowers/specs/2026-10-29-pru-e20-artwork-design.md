# PRU Elite 20 battle artwork — approved staging design (29 October 2026)

## Goal
Prepare E20 visual assets and trainer sprite assignments independently of the Mewduo repair. Work from the last confirmed tutor-stable source commit `a4d393129ec3683f0443a80272df71653a3874af`, on a separate branch, and integrate only after the Mewduo merge is verified.

## Fixed constraints
- E20: 20 consecutive six-Pokémon double battles (three per trainer), with healing, in the Saffron Fighting Dojo. Do not move the challenge to Indigo Plateau.
- Keep round pairings 1–15 unchanged; 16 Jasmine & Clair, 17 Steven & May, 18 Silver & Giovanni, 19 Red & Blue, 20 Oak & Elm.
- Preserve the 450-species cap, existing valid PRU sprites, save compatibility, the verified tutors, and Pokémon Rhythm backgrounds only.
- Do not replace approved Jessie & James, Steevee & Neevee, Red & Blue, Steven & May, or Silver & Giovanni battle entrances.
- Design a replacement Oak & Elm transition showing two different professors, with a Relic/academic/ancient-stone motif.
- Give each of the other fourteen E20 pairs its own joint entry banner, styled after the existing PRU pair banners; no “VS” suffix.
- Assign correct trainer pictures so combined pair/trio art appears once, not twice. Both trainers must retain battle parties and names.
- Increase the presence of approved custom and Relic Pokémon in E20 teams only when names, sprites, icon and moves can be verified; do not introduce or retire species.
- Preserve the dynamic player-named Silver/rival where already supported.
- Later map/dialogue polish: place the white-uniformed steward at the centre of the first smaller ring; improve introductory and round-completion dialogue.

## Investigated source behaviour
- E20 rounds 1–15 currently use `TRAINER_PRU_E18_XX_[AB](_MASTER)_HNS` party data.
- Round 14 assigns `Pic: Twins Hns` twice. That 64×64 picture already contains *both* twins; it therefore appears twice.
- Round 15 uses `Pic: Jessie Hns` plus `Pic: James Hns`, but James's asset already contains the Rocket group. Draw the group once and keep two trainer parties.
- Round 20 has `Pic: Professor Oak Frlg` for **both** Oak and Elm. Elm requires a distinct approved battle picture, not a recoloured second Oak passed off as Elm.
- The battle-transition module already imports six pair banners. Fourteen new banner assets/transition mappings are outstanding, including Jasmine & Clair.
- Some E20 teams already use many PRU-only species; others use few. Team expansion is a separate, later balance pass.

## Current staging scope
First batch fixes the double-rendered Steevee/Neevee and Jessie/James trainer art by using their single approved joint sprites plus a GBA-compatible transparent partner picture; it touches only party Pic assignments and the new graphic registration. It does **not** claim the in-engine placement or all round banners are verified yet.

## Acceptance
An mGBA E20 capture must show one pair for Steevee/Neevee, one established Rocket group for Jessie/James, separate Oak and Elm, the selected banner for each round, no broken palette/party icons, and unchanged battle teams/results. Do not merge until these checks pass.

## Source discrepancy for integration
The tutor-stable source's `PRU_Elite18_Round_08` currently selects Jasmine & Clair, while round 16 selects Maxie & Archie. The approved presentation list places Maxie & Archie at 8 and Jasmine & Clair at 16. Treat the artwork manifest as *approved intended order*, not as evidence that current scripts already match. Reconcile and test the round selection before enabling all twenty new banners; do not silently change this in the sprite-only batch.
