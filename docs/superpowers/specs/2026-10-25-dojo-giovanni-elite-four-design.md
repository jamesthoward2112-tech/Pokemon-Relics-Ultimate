# Kanto Badge-Heist Finale and Elite Four Rematches — Design

**Date:** 2026-10-25
**Approved conversation baseline:** James approved the seven-leader Dojo sequence, Giovanni's fossil/Relic team ending in defensively enhanced Armoured Mewtwo, and Elite Four rematch levels around 85 on 2026-10-25.

## Intent
Make the stolen-badge recovery a coherent postgame quest, culminating in Giovanni's true ace, then unlock an Elite Four rematch that is harder than the Kanto Gym Leader rematches. Preserve the working Rhythm 56 + Rocket balloon ROM, save compatibility, Kanto original badges and rewards, and unrelated Johto gameplay.

## Player-visible sequence
1. Rocket guard at Indigo Plateau blocks entry while badges are stolen, directs the player to the Saffron Fighting Dojo.
2. A single Kanto leader appears in the Dojo VIP arena at a time, in order Brock → Misty → Lt. Surge → Erika → Janine → Sabrina → Blaine. Each offers a six-Pokémon **single battle**. After a victory, that leader leaves and the next arrives, retaining a persistent completion flag. Nurse heals the party between battles. Leaders are absent from their original gyms during the heist (but first-clear rewards and original Kanto progression remain intact).
3. After seven wins, Giovanni occupies/reclaims Viridian Gym, where Blue is absent. His six are Omastar Lv81, skeletal Kabutops Lv82, skeletal Aerodactyl Lv83, blue/white Coelossus Lv83, Rhyperior Lv84 with verified TRE P or & sprite, and **Armoured Mewtwo Lv85 as the final Pokémon**. Relic dialogue foregrounds Team Rocket's stolen fossils and experiments. On defeat, the armour breaks and Mewtwo returns to Cerulean Cave, remaining normally catchable under existing Mewtwo/Mewsion rules. Giovanni returns the final badge and Indigo guard unblocks access.
4. Elite Four rematches (Will, Koga, Bruno, Karen, Lance) remain six-Pokémon singles and unlock after the heist. Gradation: Will 82–85, Koga 83–86, Bruno 84–87, Karen 85–88, Lance 86–89. Keep their Relic-heavy identities, intelligent AI, useful held items, reasonable healing resources, and an explicit move/ability audit. They must feel tougher than the seven Kanto leaders (76–80), without becoming the optional Red/Blue superboss.
5. The separate future Red and Blue Mt Silver paired encounter stays a follow-up feature; Blue's approved team is Pidgeot, Exeggutor, Tyranitar, Arcanine, Nidoking, Gyarados. This scope does not rework it or break the existing Red encounter.

## Kanto Rematch Team Locks
- Brock: Golem, Omastar, Kabutops, Aerodactyl, Obsideon, Pinsirex.
- Misty: Politoed, Cloyster, Vaporeon, Kingdra, custom-sprite Starmie, **Blastoise** (not Fortotoise).
- Surge: Electrode (Levitate/Kaboom!), Magneton, **Electivire**, Jolteon, Porygon2, Raichu with approved special sprite (not Noxichu).
- Erika: Vileplume, Bellossom, Exeggutor, Leafeon, special-sprite Victreebel, **Venusaur** (not Edensaur).
- Janine: Muk, Venomoth, Crobat, Tentacruel, Adnokana, Frytning.
- Sabrina: Mr. Mime, Hypno, Slowbro, Espeon, Mystynx, Alakazam.
- Blaine: Ninetales, Rapidash, **Magmortar**, Flareon, Arcanine, **Charizard using Mega Charizard X sprite**.
Each uses Kanto Pokémon or evolutions thereof and 1–2 established custom/special sprites; six Pokémon, suitable held items and smart-but-fair AI. Audit legality of custom forms in the current 450-entry roster before defining teams.

## Expanded 450-entry Pokédex
- #448 Rhyperior (Protector sold at Goldenrod 2F; Giovanni's approved custom TRE sprite remains to be verified).
- #449 Electivire: use an Electirizer on Electabuzz (sold at Goldenrod 2F).
- #450 Magmortar: use a Magmarizer on Magmar (sold at Goldenrod 2F).
- Existing front/back, party and overworld artwork is reused; preserve #001–#447 unchanged.

## Battle-Only Form and Sprite Rules
- Armoured Mewtwo: 90→120 Defence and 90→120 Special Defence, otherwise normal Mewtwo's offensive stats, move capability and speed. A separate trainer-only form or battle-only battle data, **not** global Mewtwo base-stat changes, should implement this. The catchable cave Mewtwo remains the ordinary species.
- Rhyperior: add to active Pokédex without disrupting legacy PRU species IDs; existing engine species ID is 464. Source its custom front/back/icon from verified TRE Rhyperior-P or Rhyperior-& art, never a silent stock-art substitution; the exact donor slot is presently **unverified**.
- Skeletal Kabutops/Aerodactyl and blue-white Coelossus use established library art; Coelossus remains a standalone guardian in the player's Pokédex rather than reclassified as a Relicanth evolution.
- Existing normal Mewtwo cave capture and subsequent Mewsion Lv90 requirements must not be corrupted. If an already-caught Mewtwo exists in an older save, Giovanni's armour event must not duplicate one.

## Approaches Considered
1. **Chosen:** repurpose the existing Dojo VIP leader area for a sequential Kanto gauntlet, preserving the EV-training Dojo and the Johto VIP leader rematches outside the heist. The VIP area already contains all seven Kanto NPCs and a nurse; fastest compatible route with least map rebuilding.
2. Individual gyms for the seven rematches: consistent geography, but sacrifices the requested progression and healing flow.
3. New bespoke arena/map: greater presentation freedom, but additional map, collision, warp and save-state risk for no player benefit.

## Bonus: BP Exchange Counter Level-100 XP Station
A separate, optional training service in the **BP exchange counter room shown in James's 2026-10-25 Pizza Boy A Pro screenshot**, not in the Dojo VIP arena. Preserve all three BP exchange ladies. Add exactly one Chansey overworld NPC **behind the same desk to their right**, at an equal gap to the gap between the three existing ladies (the screenshot shows a fourth evenly spaced station just before the counter's right end). The NPC must face the customer and be interactable from in front of the counter without warping, clipping or moving clerks.

On talking to Chansey: explanatory XP-training dialogue, `Yes/No` prompt (B cancels); accept triggers a **repeatable double battle against exactly two level-100 Chansey**, both using only **Memento and Heal Pulse** (the user's approved gentle Chansey-training move pattern). No level scaling, no badges/BP are consumed or awarded, and no one-time completion flag. Trainer battle can be repeated immediately after win/loss; battle grants ordinary experience. Reuse established PRU Chansey training sprite/trainer-battle mechanics where compatible. The BP exchange staff and functions must be unaffected.

## Out of Scope
- Rhythm battle-background redesign (Rhythm 56 is the fixed baseline).
- Reworking Rocket balloon animation already approved.
- Red/Blue Mt Silver encounter redesign (a separate implementation).
- Replacing every existing E4 move/team member wholesale unless an audit finds a specific problem.

## Acceptance / Anti-goals
- No skip, bypass, out-of-order battle, stuck nurse, double Blue, duplicate badge or stolen-badge softlock on old/new saves.
- Main Dojo's existing EV battle functions remain available.
- Giovanni's final Pokémon is visibly armoured, defensively stronger, and always last.
- Defeating Giovanni returns Mewtwo to a catchable cave encounter without awarding Mewtwo from the trainer fight.
- Re-entering areas, blacking out, saving and reloading preserve progress.
- Every updated team has six valid movesets, items/abilities, no invalid species IDs or missing art; clean CI GBA build and emulator smoke tests.
- Direct uncompressed .gba deliverable; never ZIP-only.