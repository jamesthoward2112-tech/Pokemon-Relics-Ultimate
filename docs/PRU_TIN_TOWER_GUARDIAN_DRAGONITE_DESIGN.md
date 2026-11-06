# PRU Tin Tower — Guardian Dragonite and Ultimate Relic encounter design

User proposed replacing the original non-catchable Kimono Girls' rooftop Ho-Oh appearance with a unique custom-sprite Dragonite, while reserving the sole Ho-Oh for post-RELICS.

Current first rooftop state (VAR_COMPLETED_HO_OH == 2): Kimono Girls dance, Ho-Oh sprite approaches, and is no longer catchable. Current late state ==4 incorrectly keeps that sprite hidden. The Ruins of Alph Relic Professor and Red direct the player to the Tin Tower roof, while the only catchable Relic Ho-Oh was moved to Oak on Mt Silver. This is a story inconsistency requiring a future event revision.

Proposed story resolution, pending finished custom GBA assets and gameplay validation:

1. **First story visit**: Kimono Girls summon an ancient Dragonite guardian as a flyby. Give it its OWN approved original overworld/cutscene sprites (not a global Dragonite recolour); change cry and all Ho-Oh-specific animation/dialogue references for that cutscene. Do not grant or set any Ho-Oh catch flags.
2. **After seven RELICS and authentic Ancient Rainbow Crest**: Rooftop displays a **single catchable Golden Relic Ho-Oh** (SPECIES_RELIC_HO_OH), with battle attempt retry when not caught, atomic caught flag, and save-compatible map-entry reconciliation. Do not spawn before flags or a second Ho-Oh elsewhere.
3. **Mt Silver**: Retain Oak as optional/rewarding final trainer challenge, but do NOT let him summon a second Ho-Oh. Preserve completed E20 status, current save flags, Red's history and Oak's epilogue. Align Relic Professor/Red/Jessie & James hints to the rooftop.
4. **GBA asset QA**: custom Guardian Dragonite overworld walk/flight frames and appropriate battle/front/back/party art if it will be catchable (otherwise do not create unnecessary new species slots). Respect 64x64 sprite budgets, transparent edges, 16-colour per sprite, palette isolation, 450 species, icons unchanged unless requested.
5. **Phoenix Soul**: post-lethal HP bar must visibly show a drop to 1 HP and a second heal animation of 25% max HP; internal HP increase alone is insufficient. Source confirmation and emulator battle QA needed. Do not claim this item complete in the Ground-immunity patch.

Already implemented separately: Mt Silver sign wording to 'Shortcut to the top?' and Phoenix Soul Ground immunity via the ungrounded-ability path; base Fire/Fairy typing retained. Both need real gameplay QA.

Do not silently alter story events or publish the Guardian Dragonite cutscene before its source graphics and tests exist.