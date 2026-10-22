# PRU legendary additions — 22 October 2026

## Source changes on branch (NOT a verified ROM build)
- **Power Plant Route 10:** replace old static Zapdos with special Level 80 *shiny* Electrode, using blue-white shiny overworld graphics and a native shiny battle. It has unique 765 BST (HP 100 / Attack 100 / Defense 115 / Sp. Atk 150 / Sp. Def 125 / Speed 175), **Levitate**, and Thunderbolt / Volt Switch / Thunder Wave / Electro Ball. Uses a persistent fateful shiny marker stored with the Pokémon so caught stats/ability are retained; other Electrode are unchanged. Catch flag persists; defeat/flight does not permanently consume the encounter.
- **Seafoam Secret Cave:** Kyogre is now Level 75 **Primal Kyogre**, with matching primal overworld sprite, native Primal battle sprite, **Primordial Sea**, and held **Blue Orb**. Team Aqua's **Archie** has a six-Pokémon Level 73–78 boss battle guarding the cave; defeated boss status is saved separately; a captured Kyogre is not re-fought.
- **Mt. Silver — former Moltres room:** Groudon is now Level 75 **Primal Groudon**, with primal overworld sprite, battle sprite, **Desolate Land**, held **Red Orb**, and a similarly challenging six-Pokémon boss **Maxie**. The three birds remain roamers, so retiring the old static Moltres frees this room.
- **Deoxys:** **Oak** awards the **Aurora Ticket** once after the player has 12 badges (8 Johto + 4 Kanto); take Olivine's ferry to the existing Birth Island Level 70 triangle encounter. This does not create a new Pokémon.
- **Wild legendary defeat rules for the above:** only successful captures set persistent catch flags. Other outcomes remove the object for the current map visit at most; returning to the area restores it.

## Approved decisions not yet fully applied on this branch
- Regirock, Regice, Registeel stay Level 80 in their existing Sinjoh Ruins rooms, with **Odyssey II** native 64×64 battle fronts/backs and two-frame icons. Registeel Odyssey II Option A was already approved; explicit source PNG import and emulator verification are outstanding.
- Latias and Latios: use **Elite Redux Mega Latias/Mega Latios** sprites; preserve Steven's roaming and Southern Island systems. Sprite import / confirm Mega-form presentation still outstanding.
- Rayquaza: **locked shiny Mega Rayquaza** sprite appearance for its existing Level 70 Embedded Tower encounter; battle and catch-form semantics need implementation/QA without adding a species.
- **Mewsion** remains Level 90 in Cerulean Cave B2F, after **both Mew and Mewtwo are captured**, then exiting and re-entering the cave. It must be independently catchable, and KO/flee/whiteout must not exhaust it. Earlier approved specification remains authoritative; coding/QA still needed.
- **Mew**: Space Mew Insurgence normal/shiny front/back/icons. Existing Faraway Island map is reachable using the Old Sea Map found in Vermilion. An *additional* S.S. Anne truck encounter is conditional: the FRLG S.S. Anne map files exist, but the HNS Vermilion port does **not** currently lead to their truck area. Do not claim truck Mew obtainable without creating and checking a reachable route. Make either encounter respect the same shared caught flag to prevent duplicate captures.
- Global legend rule: return on defeat/escape, permanent removal on capture. Existing old scripts need comprehensive QA; do not infer this branch has fixed **all** events.

## Graphics source archive
- Odyssey II bank: `/Project Hoenn Relics/Sprite Resources/Odyssey II - Complete Sprite Bank/Odyssey_II_Complete_Sprite_Bank.zip`.
- Mega donor: `/Project Hoenn Relics/Sprite Resources/Elite Redux v2.65 beta2/PHR_Elite_Redux_Hoenn_Mega_Sprites_v2.65.zip`.
- Insurgence Space Mew assets: `/Space_Mew_Insurgence_GBA_Assets.zip` in ChatGPT Library.
- Existing repo already contains `graphics/pokemon/{kyogre,groudon}/primal/` overworld/battle palettes/sprites; the new events use these engine-native forms.

## Testing / acceptance gates
1. Compile canonical HNS `make hns`, pass all existing PRU regression scripts and verify exactly 444 approved Dex species.
2. Play through Route 10 Electrode: shows **blue and white on map**, shiny in combat, survives catch with 765 BST and Levitate after storing/withdrawing; normal Electrode unaffected. Retry after defeat and disappear after catch.
3. Play cave boss battles: sight trigger; cannot bypass boss to challenge legendary; no repeat after victory; primal sprite and Primordial Sea/Desolate Land activate from the first turn. Caught Pokémon retains orb and works in player battles. Defeat/flight respawns on re-entry; captured doesn't.
4. Check Oak gives Aurora Ticket exactly once even if player exits and re-enters, and ferry/Birth Island are usable; test bag-full path.
5. Ensure existing save compatibility, Johto/Kanto story progression, and the existing three bird roaming/weather system are unchanged.
