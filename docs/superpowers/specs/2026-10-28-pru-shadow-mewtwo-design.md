# PRU Insurgence Shadow Mewtwo donor design

## Intent

Replace **standard species Mewtwo** (`SPECIES_MEWTWO`, Pokédex #423) with Pokémon Insurgence's standard Shadow Mewtwo, keeping the same species ID and caught flag so existing saves and the Mewsion prerequisite work. Preserve Giovanni's independently scripted Armoured Mewtwo encounter and existing Mewtwo Mega forms; do **not** add Mega Shadow Mewtwo X.

## Authentic donor data

- Base stats: HP 106 / Attack 110 / Defense 90 / Sp. Atk 154 / Sp. Def 90 / Speed 130 (BST 680).
- Type Psychic/Dark, regular ability Intimidate, hidden Cacophony if supported. No Burst Mode, charge meter, or Burst transformation.
- Level-up moves from the [Insurgence Mewtwo page](https://wiki.p-insurgence.com/Mewtwo_(Pok%C3%A9mon)) for its **Shadow Mewtwo** form: Night Slash, Confusion, Disable and Safeguard at start; Recover 50; Psychic 57; Barrier 64; Aura Sphere 70; Amnesia 79; Mist 86; Me First 93; Psystrike and Dark Nova at 100.
- Signature move [Dark Nova](https://wiki.p-insurgence.com/Dark_Nova_(move)): Dark type, PP 5, base power 135 **per hit**, never misses, strikes twice, uses whichever of Attack / Special Attack is higher for damage category; usable as an ordinary battle move. Maintain identical effect where the current engine supports it using native Photon Geyser category logic plus fixed two strikes. Insurgence's once-per-Burst restriction is intentionally omitted.
- Import authentic Insurgence front/back/shiny battle art from official wiki files `150_4.png`, `150b_4.png`, `150s_4.png`, `150sb_4.png`; prepare GBA-compatible 64×64 16-colour palette versions while retaining source graphics and provenance. Derive a coherent icon from actual donor art, not vanilla Mewtwo.
- Match Insurgence's accessible TM and tutor compatibility where the equivalent PRU move exists; don't remove PRU HM progression or unrelated move tutors. Document unsupported Insurgence-only TM moves explicitly if they lack engine implementations.

## Scope and constraints

- Save compatibility: never renumber Mewtwo, existing PRU species, moves or existing flags. New Dark Nova move ID is append-only.
- Giovanni Armoured Mewtwo is not rebalanced or replaced. No Shadow Mega form.
- Insurgence art is 160×160; ROM battle graphics use 64×64 4bpp, so conversion must preserve recognisable silhouettes and shiny palette. The existing Mewtwo overworld is still vanilla and may need distinct official Shadow Mewtwo artwork before the **full** graphics-donor request is complete.
- Respect pre-existing GBA build pipeline and normal `.png`/palette conventions.

## Approaches

James chose a faithful Insurgence standard Shadow Mewtwo with Dark Nova as a regular signature attack. The alternative—importing full Pokkén Burst Mode—was rejected as unnecessary complexity. Mega Shadow Mewtwo X was expressly excluded.

## Acceptance

Compilation and regression checks pass; existing caught Mewtwo remains caught, species and Mewsion IDs stay stable, Shadow Mewtwo shows donor battle/icon artwork and has donor stats/ability/moves, Dark Nova hits twice and switches attacking category correctly, and Giovanni's separate encounter retains its existing behaviour.
