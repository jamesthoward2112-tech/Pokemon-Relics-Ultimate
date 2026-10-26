# PRU second League finale — approved design

After Rocket's Kanto badge heist, Giovanni and the Route 23 twins are cleared, the player re-enters the **existing** Indigo Plateau League rooms. The five visible opponents are Lorelei, Bruno, Agatha, Lance and Red with their existing agreed teams (~Lv90–95). The original Johto League remains available earlier in the story.

Red's defeat brings Professor Oak physically into the Champion's room. Oak congratulates the player and directs them to Saffron Fighting Dojo VIP for the Elite 18. The normal Hall of Fame and credits play. After respawning in New Bark, Elm approaches and gives **Ancient Candy**, retaining the existing candy item ID and gift flag so saves stay compatible. The League door seals permanently; Indigo Plateau's centre and tutors stay accessible. There is no Elite 18 steward at Indigo Plateau, but one inside the VIP dojo, alongside the relocated double Lv100 Chansey trainer at the end of the BP counter.

Additional regressions: Eerie Fog text must fit the two-line move detail box; Steven must leave main Sinjoh Ruins after his one-time Stone Plate battle, without affecting the separate Arceus-room Steven scene.

## Technical design

Each League room must have exactly one always-visible trainer event. The room transition selects its sprite via `VAR_OBJ_GFX_ID_0`, and the trainer script selects its battle via the same shared progression predicate. This removes reliance on a pair of saved object-hide flags with identical map coordinates. All original Johto cutscene local IDs and postgame flags remain unchanged.

Do not allocate new save variables or remap item enumerations. The badge-heist prerequisites and the once-only clear flag continue to gate the finale. Include focused static regression checks and a compiled `.gba` from CI.
