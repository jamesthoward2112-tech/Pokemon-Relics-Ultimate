// Pokémon Johto Relics custom species.
// Rebuild stage 2: all three baby starters. No overworld follower data by design.

[SPECIES_SCARABUB] =
{
    .baseHP        = 45,
    .baseAttack    = 55,
    .baseDefense   = 45,
    .baseSpeed     = 50,
    .baseSpAttack  = 30,
    .baseSpDefense = 40,
    .types = MON_TYPES(TYPE_BUG),
    .catchRate = 45,
    .expYield = 65,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 5,
    .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
    .abilities = { ABILITY_SWARM, ABILITY_GUTS, ABILITY_BATTLE_ARMOR },
    .bodyColor = BODY_COLOR_BLUE,
    .speciesName = _("Scarabub"),
    .cryId = CRY_HERACROSS,
    .natDexNum = NATIONAL_DEX_HERACROSS,
    .categoryName = _("Scarab"),
    .height = 6,
    .weight = 120,
    .description = COMPOUND_STRING("Its small horn grows harder every\ntime it wrestles a rival. It drags\nfallen friends out of danger."),
    .pokemonScale = 256,
    .pokemonOffset = 0,
    .trainerScale = 256,
    .trainerOffset = 0,
    .frontPic = gMonFrontPic_Scarabub,
    .frontPicSize = MON_COORDS_SIZE(64, 64),
    .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder,
    .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
    .backPic = gMonBackPic_Scarabub,
    .backPicSize = MON_COORDS_SIZE(64, 64),
    .backPicYOffset = 6,
    .backAnimId = BACK_ANIM_JOLT_RIGHT,
    .palette = gMonPalette_Scarabub,
    .shinyPalette = gMonShinyPalette_Scarabub,
    .iconSprite = gMonIcon_Scarabub,
    .iconPalIndex = 3, // Scarabub's existing indexed icon uses BLUE pal3, never yellow pal0.
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sScarabubLevelUpLearnset,
    .teachableLearnset = sHeracrossTeachableLearnset,
    .evolutions = EVOLUTION({EVO_LEVEL, 18, SPECIES_HERACROSS}),
},

/*
 * IDs 1574 and 1576 are deliberately reserved for the locked Relic
 * evolutions Heracurion and Skarmadon. Keep them non-randomizable until
 * their full species data is installed in a later rebuild stage.
 */
[SPECIES_HERACURION] =
{
    .baseHP = 95, .baseAttack = 140, .baseDefense = 110,
    .baseSpeed = 75, .baseSpAttack = 45, .baseSpDefense = 85,
    .types = MON_TYPES(TYPE_BUG, TYPE_FIGHTING),
    .catchRate = 45, .expYield = 220, .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 25, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
    .abilities = { ABILITY_MOXIE, ABILITY_GUTS, ABILITY_BATTLE_ARMOR }, .bodyColor = BODY_COLOR_BLUE,
    .speciesName = _("Heracurion"),
    .cryId = CRY_HERACROSS,
    .natDexNum = NATIONAL_DEX_HERACROSS,
    .categoryName = _("Relic Horn"), .height = 18, .weight = 950,
    .description = COMPOUND_STRING("Its ancient horn can pierce stone.\nIt stands firm while protecting\nweaker Pokémon."),
    .pokemonScale = 256, .trainerScale = 256,
    .frontPic = gMonFrontPic_Heracurion, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder,
    .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
    .backPic = gMonBackPic_Heracurion, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6,
    .backAnimId = BACK_ANIM_V_SHAKE_LOW,
    .palette = gMonPalette_Heracurion, .shinyPalette = gMonShinyPalette_Heracurion,
    .iconSprite = gMonIcon_Heracurion, .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sHeracurionLevelUpLearnset, .teachableLearnset = sHeracrossTeachableLearnset,
},

[SPECIES_SKARMET] =
{
    .baseHP        = 45,
    .baseAttack    = 45,
    .baseDefense   = 65,
    .baseSpeed     = 50,
    .baseSpAttack  = 30,
    .baseSpDefense = 35,
    .types = MON_TYPES(TYPE_STEEL, TYPE_FLYING),
    .catchRate = 45,
    .expYield = 65,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 5,
    .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
    .abilities = { ABILITY_KEEN_EYE, ABILITY_STURDY, ABILITY_WEAK_ARMOR },
    .bodyColor = BODY_COLOR_GRAY,
    .speciesName = _("Skarmet"),
    .cryId = CRY_SKARMORY,
    .natDexNum = NATIONAL_DEX_SKARMORY,
    .categoryName = _("Armor Chick"),
    .height = 5,
    .weight = 180,
    .description = COMPOUND_STRING(
        "Its light metal feathers harden as it\n"
        "grows. It practices short flights while\n"
        "testing its sharp wings on stone."),
    .pokemonScale = 256,
    .pokemonOffset = 0,
    .trainerScale = 256,
    .trainerOffset = 0,
    .frontPic = gMonFrontPic_Skarmet,
    .frontPicSize = MON_COORDS_SIZE(64, 64),
    .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder,
    .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Skarmet,
    .backPicSize = MON_COORDS_SIZE(64, 64),
    .backPicYOffset = 6,
    .backAnimId = BACK_ANIM_JOLT_RIGHT,
    .palette = gMonPalette_Skarmet,
    .shinyPalette = gMonShinyPalette_Skarmet,
    .iconSprite = gMonIcon_Skarmet,
    .iconPalIndex = 0,
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sSkarmetLevelUpLearnset,
    .teachableLearnset = sSkarmoryTeachableLearnset,
    .evolutions = EVOLUTION({EVO_LEVEL, 18, SPECIES_SKARMORY}),
},

[SPECIES_SKARMADON] =
{
    .baseHP = 80, .baseAttack = 125, .baseDefense = 140,
    .baseSpeed = 85, .baseSpAttack = 45, .baseSpDefense = 80,
    .types = MON_TYPES(TYPE_STEEL, TYPE_FLYING),
    .catchRate = 45, .expYield = 220, .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 25, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
    .abilities = { ABILITY_STURDY, ABILITY_KEEN_EYE, ABILITY_BATTLE_ARMOR }, .bodyColor = BODY_COLOR_GRAY,
    .speciesName = _("Skarmadon"),
    .cryId = CRY_SKARMORY,
    .natDexNum = NATIONAL_DEX_SKARMORY,
    .categoryName = _("Relic Armor"), .height = 20, .weight = 880,
    .description = COMPOUND_STRING("Its relic-plated wings ring like\nforged steel. It rides violent winds\nwithout yielding."),
    .pokemonScale = 256, .trainerScale = 256,
    .frontPic = gMonFrontPic_Skarmadon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder,
    .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Skarmadon, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6,
    .backAnimId = BACK_ANIM_H_SHAKE,
    .palette = gMonPalette_Skarmadon, .shinyPalette = gMonShinyPalette_Skarmadon,
    .iconSprite = gMonIcon_Skarmadon,
    .iconPalIndex = 0,
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sSkarmadonLevelUpLearnset, .teachableLearnset = sSkarmoryTeachableLearnset,
},

[SPECIES_MOOTINY] =
{
    .baseHP        = 50,
    .baseAttack    = 45,
    .baseDefense   = 55,
    .baseSpeed     = 45,
    .baseSpAttack  = 30,
    .baseSpDefense = 45,
    .types = MON_TYPES(TYPE_NORMAL),
    .catchRate = 45,
    .expYield = 65,
    .genderRatio = MON_FEMALE,
    .eggCycles = 5,
    .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    .abilities = { ABILITY_THICK_FAT, ABILITY_SCRAPPY, ABILITY_SAP_SIPPER },
    .bodyColor = BODY_COLOR_PINK,
    .speciesName = _("Mootiny"),
    .cryId = CRY_MILTANK,
    .natDexNum = NATIONAL_DEX_MILTANK,
    .categoryName = _("Calf"),
    .height = 5,
    .weight = 280,
    .description = COMPOUND_STRING(
        "This cheerful calf builds strong legs by\n"
        "running in circles. It is surprisingly\n"
        "stubborn when protecting its friends."),
    .pokemonScale = 256,
    .pokemonOffset = 0,
    .trainerScale = 256,
    .trainerOffset = 0,
    .frontPic = gMonFrontPic_Mootiny,
    .frontPicSize = MON_COORDS_SIZE(64, 64),
    .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder,
    .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE_SLOW,
    .backPic = gMonBackPic_Mootiny,
    .backPicSize = MON_COORDS_SIZE(64, 64),
    .backPicYOffset = 6,
    .backAnimId = BACK_ANIM_H_SLIDE,
    .palette = gMonPalette_Mootiny,
    .shinyPalette = gMonShinyPalette_Mootiny,
    .iconSprite = gMonIcon_Mootiny,
    .iconPalIndex = 5, // PRU Mootiny icon is indexed for the warm palette #5.
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sMootinyLevelUpLearnset,
    .teachableLearnset = sMiltankTeachableLearnset,
    .evolutions = EVOLUTION({EVO_LEVEL, 18, SPECIES_MILTANK}),
},

// Pokémon Infinity donor additions approved for PJR.

[SPECIES_CHAMPEON] =
{
    .baseHP = 65, .baseAttack = 110, .baseDefense = 65,
    .baseSpeed = 130, .baseSpAttack = 95, .baseSpDefense = 60,
    .types = MON_TYPES(TYPE_FIGHTING),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    .abilities = { ABILITY_SCRAPPY, ABILITY_NONE, ABILITY_COMPETITIVE }, .bodyColor = BODY_COLOR_RED,
    .speciesName = _("Champeon"), .cryId = CRY_EEVEE, .natDexNum = NATIONAL_DEX_EEVEE,
    .categoryName = _("Champion"), .height = 10, .weight = 230,
    .description = COMPOUND_STRING("It trains its forelegs until its\nstrikes blur. A trusted partner\nnever backs down from a match."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Champeon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Champeon, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Champeon, .shinyPalette = gMonPalette_Champeon,
    .iconSprite = gMonIcon_Champeon, .iconPalIndex = 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sChampeonLevelUpLearnset, .teachableLearnset = sChampeonInfinityTeachableLearnset,
},

[SPECIES_LEPIDEON] =
{
    .baseHP = 80, .baseAttack = 65, .baseDefense = 72,
    .baseSpeed = 103, .baseSpAttack = 115, .baseSpDefense = 90,
    .types = MON_TYPES(TYPE_BUG),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    .abilities = { ABILITY_RATTLED, ABILITY_NONE, ABILITY_TINTED_LENS }, .bodyColor = BODY_COLOR_YELLOW,
    .speciesName = _("Moffeon"), .cryId = CRY_EEVEE, .natDexNum = NATIONAL_DEX_EEVEE,
    .categoryName = _("Silk Moth"), .height = 11, .weight = 120,
    .description = COMPOUND_STRING("Its powdery wings leave patterns\nof glowing dust. It weaves silk\nnests high in the forest canopy."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Lepideon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Lepideon, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Lepideon, .shinyPalette = gMonPalette_Lepideon,
    .iconSprite = gMonIcon_Lepideon, .iconPalIndex = 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sLepideonLevelUpLearnset, .teachableLearnset = sLepideonInfinityTeachableLearnset,
},

[SPECIES_GUARDEON] =
{
    .baseHP = 65, .baseAttack = 60, .baseDefense = 130,
    .baseSpeed = 65, .baseSpAttack = 110, .baseSpDefense = 95,
    .types = MON_TYPES(TYPE_STEEL),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    .abilities = { ABILITY_BULLETPROOF, ABILITY_NONE, ABILITY_HEATPROOF }, .bodyColor = BODY_COLOR_GRAY,
    .speciesName = _("Galveon"), .cryId = CRY_EEVEE, .natDexNum = NATIONAL_DEX_EEVEE,
    .categoryName = _("Iron Knight"), .height = 12, .weight = 585,
    .description = COMPOUND_STRING("Metallic fur hardens when danger\napproaches. It guards its trainer\nwith the poise of an old knight."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Guardeon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Guardeon, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Guardeon, .shinyPalette = gMonPalette_Guardeon,
    .iconSprite = gMonIcon_Guardeon, .iconPalIndex = 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sGuardeonLevelUpLearnset, .teachableLearnset = sGuardeonInfinityTeachableLearnset,
},

[SPECIES_OBSIDEON] =
{
    .baseHP = 75, .baseAttack = 120, .baseDefense = 75,
    .baseSpeed = 80, .baseSpAttack = 60, .baseSpDefense = 115,
    .types = MON_TYPES(TYPE_ROCK),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    .abilities = { ABILITY_ROCK_HEAD, ABILITY_NONE, ABILITY_SAND_RUSH }, .bodyColor = BODY_COLOR_BLACK,
    .speciesName = _("Pebleon"), .cryId = CRY_EEVEE, .natDexNum = NATIONAL_DEX_EEVEE,
    .categoryName = _("Obsidian"), .height = 13, .weight = 780,
    .description = COMPOUND_STRING("Its rocky coat gleams like black\nglass. It sheds razor-sharp chips\nto ward off approaching foes."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Obsideon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Obsideon, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Obsideon, .shinyPalette = gMonPalette_Obsideon,
    .iconSprite = gMonIcon_Obsideon, .iconPalIndex = 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sObsideonLevelUpLearnset, .teachableLearnset = sObsideonInfinityTeachableLearnset,
},

[SPECIES_TOXEON] =
{
    .baseHP = 65, .baseAttack = 111, .baseDefense = 105,
    .baseSpeed = 110, .baseSpAttack = 84, .baseSpDefense = 50,
    .types = MON_TYPES(TYPE_POISON),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    .abilities = { ABILITY_POISON_TOUCH, ABILITY_NONE, ABILITY_LIGHTNING_ROD }, .bodyColor = BODY_COLOR_PURPLE,
    .speciesName = _("Toxeon"), .cryId = CRY_EEVEE, .natDexNum = NATIONAL_DEX_EEVEE,
    .categoryName = _("Toxic"), .height = 11, .weight = 230,
    .description = COMPOUND_STRING("Bright marks on its fur warn off\npredators. It stores poison in\nsmall glands along its tail."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Toxeon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 5,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Toxeon, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Toxeon, .shinyPalette = gMonPalette_Toxeon,
    .iconSprite = gMonIcon_Toxeon, .iconPalIndex = 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sToxeonLevelUpLearnset, .teachableLearnset = sToxeonInfinityTeachableLearnset,
},

[SPECIES_SPHYNXEON] =
{
    .baseHP = 120, .baseAttack = 88, .baseDefense = 106,
    .baseSpeed = 61, .baseSpAttack = 70, .baseSpDefense = 80,
    .types = MON_TYPES(TYPE_GROUND),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    .abilities = { ABILITY_SYNCHRONIZE, ABILITY_NONE, ABILITY_TECHNICIAN }, .bodyColor = BODY_COLOR_BROWN,
    .speciesName = _("Eartheon"), .cryId = CRY_EEVEE, .natDexNum = NATIONAL_DEX_EEVEE,
    .categoryName = _("Desert"), .height = 9, .weight = 240,
    .description = COMPOUND_STRING("It reads distant footsteps from\nvibrations in the sand. By day,\nit sleeps beneath cool dunes."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Sphynxeon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Sphynxeon, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Sphynxeon, .shinyPalette = gMonPalette_Sphynxeon,
    .iconSprite = gMonIcon_Sphynxeon, .iconPalIndex = 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sSphynxeonLevelUpLearnset, .teachableLearnset = sSphynxeonInfinityTeachableLearnset,
},

[SPECIES_OMEON] =
{
    .baseHP = 70, .baseAttack = 124, .baseDefense = 85,
    .baseSpeed = 116, .baseSpAttack = 65, .baseSpDefense = 65,
    .types = MON_TYPES(TYPE_GHOST),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    .abilities = { ABILITY_SUPER_LUCK, ABILITY_NONE, ABILITY_MOXIE }, .bodyColor = BODY_COLOR_BLACK,
    .speciesName = _("Obliveon"), .cryId = CRY_EEVEE, .natDexNum = NATIONAL_DEX_EEVEE,
    .categoryName = _("Omen"), .height = 11, .weight = 180,
    .description = COMPOUND_STRING("Its shadow moves a moment before\nits body does. Travelers say its\ncry foretells a sudden change."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Omeon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 7,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Omeon, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Omeon, .shinyPalette = gMonPalette_Omeon,
    .iconSprite = gMonIcon_Omeon, .iconPalIndex = 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sOmeonLevelUpLearnset, .teachableLearnset = sOmeonInfinityTeachableLearnset,
},

[SPECIES_JOLLIBIRD] =
{
    .baseHP = 80, .baseAttack = 50, .baseDefense = 105,
    .baseSpeed = 75, .baseSpAttack = 120, .baseSpDefense = 115,
    .types = MON_TYPES(TYPE_ICE, TYPE_FAIRY),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FAIRY),
    .abilities = { ABILITY_THICK_FAT, ABILITY_NONE, ABILITY_SNOW_WARNING }, .bodyColor = BODY_COLOR_RED,
    .speciesName = _("Jollibird"), .cryId = CRY_DELIBIRD, .natDexNum = NATIONAL_DEX_DELIBIRD,
    .categoryName = _("Present"), .height = 11, .weight = 290,
    .description = COMPOUND_STRING("It wraps berries in packed snow\nand leaves them on lonely paths.\nIts gifts can revive the weary."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Jollibird, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Jollibird, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 14, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Jollibird, .shinyPalette = gMonPalette_Jollibird,
    .iconSprite = gMonIcon_Jollibird, .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 0 : 1, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sJollibirdLevelUpLearnset, .teachableLearnset = sJollibirdInfinityTeachableLearnset,
},

[SPECIES_GRIMFOWL] =
{
    .baseHP = 112, .baseAttack = 63, .baseDefense = 80,
    .baseSpeed = 78, .baseSpAttack = 130, .baseSpDefense = 77,
    .types = MON_TYPES(TYPE_DARK, TYPE_FLYING),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
    .abilities = { ABILITY_UNNERVE, ABILITY_NONE, ABILITY_NO_GUARD }, .bodyColor = BODY_COLOR_BLACK,
    .speciesName = _("Grimfowl"), .cryId = CRY_NOCTOWL, .natDexNum = NATIONAL_DEX_NOCTOWL,
    .categoryName = _("Harbinger"), .height = 24, .weight = 700,
    .description = COMPOUND_STRING("It circles above silent woods\nbefore a storm. Its dark feathers\nmuffle the sound of its flight."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Grimfowl, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Grimfowl, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Grimfowl, .shinyPalette = gMonPalette_Grimfowl,
    .iconSprite = gMonIcon_Grimfowl, .iconPalIndex = 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sGrimfowlLevelUpLearnset, .teachableLearnset = sGrimfowlInfinityTeachableLearnset,
},

[SPECIES_KABLOWFISH] =
{
    .baseHP = 85, .baseAttack = 100, .baseDefense = 125,
    .baseSpeed = 75, .baseSpAttack = 65, .baseSpDefense = 85,
    .types = MON_TYPES(TYPE_WATER, TYPE_STEEL),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
    .abilities = { ABILITY_POISON_POINT, ABILITY_SWIFT_SWIM, ABILITY_INTIMIDATE }, .bodyColor = BODY_COLOR_GRAY,
    .speciesName = _("Kablowfish"), .cryId = CRY_QWILFISH, .natDexNum = NATIONAL_DEX_QWILFISH,
    .categoryName = _("Naval Mine"), .height = 17, .weight = 980,
    .description = COMPOUND_STRING("Its armored spines click as it\nswells with pressure. It bursts\nforward like a drifting mine."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Kablowfish, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Kablowfish, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 14, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Kablowfish, .shinyPalette = gMonPalette_Kablowfish,
    .iconSprite = gMonIcon_Kablowfish, .iconPalIndex = 0, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sKablowfishLevelUpLearnset, .teachableLearnset = sKablowfishInfinityTeachableLearnset,
},

[SPECIES_MYSTYNX] =
{
    .baseHP = 75, .baseAttack = 60, .baseDefense = 40,
    .baseSpeed = 125, .baseSpAttack = 130, .baseSpDefense = 105,
    .types = MON_TYPES(TYPE_ICE, TYPE_FAIRY),
    .catchRate = 45, .expYield = 184,
    .genderRatio = MON_FEMALE,
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
    .abilities = { ABILITY_COMPETITIVE, ABILITY_OBLIVIOUS, ABILITY_SNOW_WARNING }, .bodyColor = BODY_COLOR_PURPLE,
    .speciesName = _("Mystynx"), .cryId = CRY_JYNX, .natDexNum = NATIONAL_DEX_JYNX,
    .categoryName = _("Mystic"), .height = 17, .weight = 450,
    .description = COMPOUND_STRING("It sketches secret runes in frost.\nThose who follow the glittering\nmarks often lose their way."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Mystynx, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Mystynx, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Mystynx, .shinyPalette = gMonShinyPalette_Mystynx,
    .iconSprite = gMonIcon_Mystynx, .iconPalIndex = 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sMystynxLevelUpLearnset, .teachableLearnset = sMystynxInfinityTeachableLearnset,
},

[SPECIES_SUNFLORID] =
{
    .baseHP = 110, .baseAttack = 90, .baseDefense = 75,
    .baseSpeed = 65, .baseSpAttack = 115, .baseSpDefense = 80,
    .types = MON_TYPES(TYPE_GRASS, TYPE_FIRE),
    .catchRate = 45, .expYield = 184,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
    .abilities = { ABILITY_CHLOROPHYLL, ABILITY_SOLAR_POWER, ABILITY_DROUGHT }, .bodyColor = BODY_COLOR_YELLOW,
    .speciesName = _("Sunflorid"), .cryId = CRY_SUNFLORA, .natDexNum = NATIONAL_DEX_SUNFLORA,
    .categoryName = _("Sunfire"), .height = 10, .weight = 340,
    .description = COMPOUND_STRING("Its petals hold heat long after\nsunset. A ring of warm earth\nfollows it through cold fields."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Sunflorid, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Sunflorid, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Sunflorid, .shinyPalette = gMonPalette_Sunflorid,
    .iconSprite = gMonIcon_Sunflorid, .iconPalIndex = 1, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sSunfloridLevelUpLearnset, .teachableLearnset = sSunfloridInfinityTeachableLearnset,
},

[SPECIES_OSTEODIAN] =
{
    .baseHP = 105, .baseAttack = 95, .baseDefense = 145,
    .baseSpeed = 60, .baseSpAttack = 60, .baseSpDefense = 95,
    .types = MON_TYPES(TYPE_GROUND),
    .catchRate = 45, .expYield = 220,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER),
    .abilities = { ABILITY_BATTLE_ARMOR, ABILITY_STURDY, ABILITY_SOLID_ROCK },
    .bodyColor = BODY_COLOR_BROWN,
    .speciesName = _("Osteodian"), .cryId = CRY_MAROWAK, .natDexNum = NATIONAL_DEX_MAROWAK,
    .categoryName = _("Guardian"), .height = 20, .weight = 1200,
    .description = COMPOUND_STRING(
        "Its ancient skeleton has hardened into\n"
        "natural armor. It stands guard over\n"
        "weaker Pokémon without retreating."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Osteodian, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Osteodian, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Osteodian, .shinyPalette = gMonShinyPalette_Osteodian,
    .iconSprite = gMonIcon_Osteodian, .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sOsteodianLevelUpLearnset, .teachableLearnset = sOsteodianTeachableLearnset,
},

[SPECIES_MAROGHOST] =
{
    .baseHP = 100, .baseAttack = 140, .baseDefense = 120,
    .baseSpeed = 70, .baseSpAttack = 50, .baseSpDefense = 90,
    .types = MON_TYPES(TYPE_GROUND, TYPE_GHOST),
    .catchRate = 45, .expYield = 220,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_MEDIUM_FAST,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER),
    .abilities = { ABILITY_CURSED_BODY, ABILITY_INFILTRATOR, ABILITY_LEVITATE },
    .bodyColor = BODY_COLOR_PURPLE,
    .speciesName = _("Maroghost"), .cryId = CRY_MAROWAK, .natDexNum = NATIONAL_DEX_MAROWAK,
    .categoryName = _("Bone Wraith"), .height = 16, .weight = 260,
    .description = COMPOUND_STRING("A pale flame clings to its bone\nclub. It prowls old burial sites\nwithout making a sound."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Maroghost, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
    .backPic = gMonBackPic_Maroghost, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Maroghost, .shinyPalette = gMonShinyPalette_Maroghost,
    .iconSprite = gMonIcon_Maroghost, .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 2, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sMaroghostLevelUpLearnset, .teachableLearnset = sMaroghostTeachableLearnset,
},

[SPECIES_ALPHORACLE] =
{
    .baseHP = 100, .baseAttack = 70, .baseDefense = 110,
    .baseSpeed = 100, .baseSpAttack = 150, .baseSpDefense = 150,
    .types = MON_TYPES(TYPE_PSYCHIC, TYPE_FAIRY),
    .catchRate = 3, .expYield = 306,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120, .friendship = 0,
    .growthRate = GROWTH_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_MAGIC_BOUNCE, ABILITY_NONE, ABILITY_NONE }, .bodyColor = BODY_COLOR_PURPLE,
    .speciesName = _("Alphoracle"), .cryId = CRY_UNOWN, .natDexNum = NATIONAL_DEX_UNOWN,
    .categoryName = _("First Voice"), .height = 25, .weight = 999,
    .description = COMPOUND_STRING("It speaks in patterns older than\nthe Ruins of Alph. Each whisper\nstirs dormant Relic energy."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Alphoracle, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH,
    .backPic = gMonBackPic_Alphoracle, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 6, .backAnimId = BACK_ANIM_NONE,
    .palette = gMonPalette_Alphoracle, .shinyPalette = gMonPalette_Alphoracle,
    .iconSprite = gMonIcon_Alphoracle, .iconPalIndex = 0, .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sAlphoracleLevelUpLearnset, .teachableLearnset = sAlphoracleInfinityTeachableLearnset,
},

[SPECIES_PINSIREX] =
{
    .baseHP = 80, .baseAttack = 135, .baseDefense = 100,
    .baseSpeed = 110, .baseSpAttack = 45, .baseSpDefense = 80,
    .types = MON_TYPES(TYPE_BUG, TYPE_FLYING),
    .catchRate = 45, .expYield = 210,
    .genderRatio = PERCENT_FEMALE(50),
    .eggCycles = 25, .friendship = STANDARD_FRIENDSHIP,
    .growthRate = GROWTH_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
    .abilities = { ABILITY_AERILATE, ABILITY_MOLD_BREAKER, ABILITY_HYPER_CUTTER },
    .bodyColor = BODY_COLOR_BROWN,
    .speciesName = _("Pinsirex"), .cryId = CRY_PINSIR, .natDexNum = NATIONAL_DEX_PINSIR,
    .categoryName = _("Relic Stag"), .height = 17, .weight = 590,
    .description = COMPOUND_STRING(
        "Ancient power has awakened its wings.\n"
        "It dives at high speed before locking\n"
        "its mighty horns around its foe."),
    .pokemonScale = 256, .pokemonOffset = 2, .trainerScale = 257, .trainerOffset = 0,
    .frontPic = gMonFrontPic_Pinsirex, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
    .backPic = gMonBackPic_Pinsirex, .backPicSize = MON_COORDS_SIZE(64, 56), .backPicYOffset = 6,
    .backAnimId = BACK_ANIM_V_SHAKE_LOW,
    .palette = gMonPalette_Pinsirex, .shinyPalette = gMonShinyPalette_Pinsirex,
    .iconSprite = gMonIcon_Pinsirex, .iconPalIndex = 2,
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    .levelUpLearnset = sPinsirexLevelUpLearnset,
    .teachableLearnset = sPinsirTeachableLearnset,
},

#define PJR_FINAL_SPECIES(species, hp, atk, def, spa, spd, spe, type1, type2, ability1, ability2, hidden, name, cry, natdex, category, color, front, back, pal, shiny, icon, iconPal, levelMoves, teachMoves, frontY, backY, dexHt, dexWt, dexBio) \
[species] = { \
    .baseHP = hp, .baseAttack = atk, .baseDefense = def, .baseSpAttack = spa, .baseSpDefense = spd, .baseSpeed = spe, \
    .types = MON_TYPES(type1, type2), .catchRate = 45, .expYield = 220, .genderRatio = PERCENT_FEMALE(50), \
    .eggCycles = 25, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_SLOW, \
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD), .abilities = { ability1, ability2, hidden }, .bodyColor = color, \
    .speciesName = _(name), .cryId = cry, .natDexNum = natdex, .categoryName = _(category), .height = dexHt, .weight = dexWt, \
    .description = COMPOUND_STRING(dexBio), \
    .pokemonScale = 256, .trainerScale = 256, \
    .frontPic = front, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = frontY, \
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH, \
    .backPic = back, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = backY, .backAnimId = BACK_ANIM_NONE, \
    .palette = pal, .shinyPalette = shiny, .iconSprite = icon, .iconPalIndex = iconPal, \
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE, .levelUpLearnset = levelMoves, .teachableLearnset = teachMoves, \
}

// Miltitan's PRL icon uses the neutral/pink palette #0 indices.
PJR_FINAL_SPECIES(SPECIES_MILTITAN, 110, 120, 105, 45, 100, 75, TYPE_NORMAL, TYPE_FAIRY,
    ABILITY_THICK_FAT, ABILITY_SCRAPPY, ABILITY_SAP_SIPPER, "Miltitan", CRY_MILTANK,
    NATIONAL_DEX_MILTANK, "Relic Cow", BODY_COLOR_PINK, gMonFrontPic_Miltitan, gMonBackPic_Miltitan,
    gMonPalette_Miltitan, gMonShinyPalette_Miltitan, gMonIcon_Miltitan, 0, sMiltitanLevelUpLearnset, sMiltankTeachableLearnset, 0, 6, 19, 1550, "It charges through open fields with\nits horns lowered. Herds gather\nbehind it in fierce winters."),

PJR_FINAL_SPECIES(SPECIES_SHUCKOLOSSE, 40, 30, 230, 30, 230, 20, TYPE_BUG, TYPE_ROCK,
    ABILITY_ANCIENT_BASTION, ABILITY_NONE, ABILITY_NONE, "Shuckolosse", CRY_SHUCKLE,
    NATIONAL_DEX_SHUCKLE, "Bastion", BODY_COLOR_YELLOW, gMonFrontPic_Shuckolosse, gMonBackPic_Shuckolosse,
    gMonPalette_Shuckolosse, gMonShinyPalette_Shuckolosse, gMonIcon_Shuckolosse, 1, sShuckolosseLevelUpLearnset, sShuckleTeachableLearnset, 0, 6, 14, 1850, "Its shell withstands falling rock.\nSmaller Pokemon find shelter in\nits shadow during landslides."),

PJR_FINAL_SPECIES(SPECIES_SUDOWARDEN, 90, 125, 145, 40, 95, 40, TYPE_ROCK, TYPE_GRASS,
    ABILITY_STURDY, ABILITY_ROCK_HEAD, ABILITY_SAP_SIPPER, "Sudowarden", CRY_SUDOWOODO,
    NATIONAL_DEX_SUDOWOODO, "Ancient Tree", BODY_COLOR_BROWN, gMonFrontPic_Sudowarden, gMonBackPic_Sudowarden,
    gMonPalette_Sudowarden, gMonShinyPalette_Sudowarden, gMonIcon_Sudowarden, 1, sSudowardenLevelUpLearnset, sSudowoodoTeachableLearnset, 2, 6, 21, 1150, "It stands unmoving for weeks at a\ntime. Leaves sprout from its stone\nbranches after spring rain."),

PJR_FINAL_SPECIES(SPECIES_DONPHALANX, 110, 140, 135, 60, 85, 60, TYPE_GROUND, TYPE_DARK,
    ABILITY_STAMINA, ABILITY_INTIMIDATE, ABILITY_SAND_RUSH, "Donphalanx", CRY_DONPHAN,
    NATIONAL_DEX_DONPHAN, "War Tusk", BODY_COLOR_GRAY, gMonFrontPic_Donphalanx, gMonBackPic_Donphalanx,
    gMonPalette_Donphalanx, gMonShinyPalette_Donphalanx, gMonIcon_Donphalanx, 0, sDonphalanxLevelUpLearnset, sDonphanTeachableLearnset, 0, 16, 18, 1700, "Its heavy tusks form a moving\nwall. Herds follow behind it\nthrough fierce sandstorms."),

PJR_FINAL_SPECIES(SPECIES_FAERANIUM, 100, 85, 115, 105, 120, 65, TYPE_GRASS, TYPE_FAIRY,
    ABILITY_ANCIENT_BLOOM, ABILITY_NONE, ABILITY_NONE, "Faeranium", CRY_MEGANIUM,
    NATIONAL_DEX_MEGANIUM, "Bloom Relic", BODY_COLOR_GREEN, gMonFrontPic_Faeranium, gMonBackPic_Faeranium,
    gMonPalette_Faeranium, gMonShinyPalette_Faeranium, gMonIcon_Faeranium, 1, sFaeraniumLevelUpLearnset, sMeganiumTeachableLearnset, 0, 6, 20, 1350, "The scent of its glowing flowers\ncalms raging Pokemon. Ancient\ngroves bloom in its footsteps."),

PJR_FINAL_SPECIES(SPECIES_PYROCLAST, 85, 95, 85, 130, 90, 105, TYPE_FIRE, TYPE_GHOST,
    ABILITY_CINDER_VEIL, ABILITY_NONE, ABILITY_NONE, "Pyroclast", CRY_TYPHLOSION,
    NATIONAL_DEX_TYPHLOSION, "Cinder Relic", BODY_COLOR_RED, gMonFrontPic_Pyroclast, gMonBackPic_Pyroclast,
    gMonPalette_Pyroclast, gMonShinyPalette_Pyroclast, gMonIcon_Pyroclast, P_GBA_STYLE_SPECIES_ICONS ? 1 : 3, sPyroclastLevelUpLearnset, sTyphlosionTeachableLearnset, 0, 8, 19, 900, "Its back burns like a volcano.\nGhostly cinders drift for hours\nafter it unleashes its flames."),

PJR_FINAL_SPECIES(SPECIES_FERALODON, 105, 135, 105, 70, 85, 80, TYPE_WATER, TYPE_DRAGON,
    ABILITY_TIDAL_ROAR, ABILITY_NONE, ABILITY_NONE, "Feralodon", CRY_FERALIGATR,
    NATIONAL_DEX_FERALIGATR, "Tidal Relic", BODY_COLOR_BLUE, gMonFrontPic_Feralodon, gMonBackPic_Feralodon,
    gMonPalette_Feralodon, gMonShinyPalette_Feralodon, gMonIcon_Feralodon, 0, sFeralodonLevelUpLearnset, sFeraligatrTeachableLearnset, 0, 6, 28, 1250, "Its roar churns rivers into\nwhirlpools. Even rough currents\ncannot slow its massive tail."),

PJR_FINAL_SPECIES(SPECIES_DRAKEON, 75, 130, 85, 110, 65, 80, TYPE_DRAGON, TYPE_DRAGON,
    ABILITY_INTIMIDATE, ABILITY_NONE, ABILITY_MULTISCALE, "Mytheon", CRY_EEVEE,
    NATIONAL_DEX_EEVEE, "Wyvern", BODY_COLOR_BLUE, gMonFrontPic_Drakeon, gMonBackPic_Drakeon,
    gMonPalette_Drakeon, gMonShinyPalette_Drakeon, gMonIcon_Drakeon, 2, sDrakeonLevelUpLearnset, sEeveeTeachableLearnset, 0, 6, 13, 390, "It sharpens its claws on cliffs\nand calls to passing dragons.\nIts scales shine in moonlight."),

PJR_FINAL_SPECIES(SPECIES_GHOULBAT, 95, 110, 90, 80, 95, 130, TYPE_GHOST, TYPE_FLYING,
    ABILITY_INFILTRATOR, ABILITY_PRESSURE, ABILITY_CURSED_BODY, "Ghoulbat", CRY_CROBAT,
    NATIONAL_DEX_CROBAT, "Wraith", BODY_COLOR_PURPLE, gMonFrontPic_Ghoulbat, gMonBackPic_Ghoulbat,
    gMonPalette_Ghoulbat, gMonShinyPalette_Ghoulbat, gMonIcon_Ghoulbat, 2, sGhoulbatLevelUpLearnset, sCrobatTeachableLearnset, 0, 6, 21, 440, "Its wings make no sound at all.\nIt drains warmth from cave walls\nbefore fading into darkness."),

[SPECIES_RELIC_HO_OH] =
{
    .baseHP = 106, .baseAttack = 100, .baseDefense = 100,
    .baseSpeed = 114, .baseSpAttack = 140, .baseSpDefense = 140,
    .types = MON_TYPES(TYPE_FIRE, TYPE_FAIRY),
    .catchRate = 3, .expYield = 340,
    .evYield_SpDefense = 3,
    .itemCommon = ITEM_SACRED_ASH, .itemRare = ITEM_SACRED_ASH,
    .genderRatio = MON_GENDERLESS, .eggCycles = 120, .friendship = 0,
    .growthRate = GROWTH_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_PHOENIX_SOUL, ABILITY_PHOENIX_SOUL, ABILITY_PHOENIX_SOUL },
    .bodyColor = BODY_COLOR_YELLOW,
    .speciesName = _("Ho-Oh"), .cryId = CRY_HO_OH, .natDexNum = NATIONAL_DEX_HO_OH,
    .categoryName = _("Phoenix"), .height = 38, .weight = 1990,
    .description = COMPOUND_STRING(
        "Summoned atop Mt. Silver by\n"
        "Professor Oak, this golden relic\n"
        "answers only the worthiest Trainer.\n"
        "Its sacred flames promise rebirth."),
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 610, .trainerOffset = 17,
    .frontPic = gMonFrontPic_HoOhRelic, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_GROW_VIBRATE,
    .enemyMonElevation = 6,
    .backPic = gMonBackPic_HoOhRelic, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 1,
    .backAnimId = BACK_ANIM_SHAKE_GLOW_RED,
    .palette = gMonPalette_HoOhRelic, .shinyPalette = gMonPalette_HoOhRelic,
    .iconSprite = gMonIcon_HoOhRelic, .iconPalIndex = 1,
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
    SHADOW(1, 17, SHADOW_SIZE_L)
    FOOTPRINT(HoOh)
    OVERWORLD(
        sPicTable_HoOh,
        SIZE_64x64,
        SHADOW_SIZE_M,
        TRACKS_NONE,
        sAnimTable_Following,
        gOverworldPalette_HoOh,
        gOverworldPalette_HoOh
    )
    .isRestrictedLegendary = TRUE,
    .isFrontierBanned = TRUE,
    .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
    .levelUpLearnset = sRelicHoOhLevelUpLearnset,
    .teachableLearnset = sHoOhTeachableLearnset,
},

#undef PJR_FINAL_SPECIES

#define PJR_RED_SPECIES(species, hp, atk, def, spa, spd, spe, type1, type2, ability, name, cry, natdex, color, front, back, pal, shiny, icon, levelMoves, teachMoves, weightKgTenths, frontY, backY, iconPal, dexCategory, dexHt, dexBio) \
[species] = { \
    .baseHP = hp, .baseAttack = atk, .baseDefense = def, .baseSpAttack = spa, .baseSpDefense = spd, .baseSpeed = spe, \
    .types = MON_TYPES(type1, type2), .catchRate = 45, .expYield = 250, .genderRatio = PERCENT_FEMALE(50), \
    .eggCycles = 25, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW, \
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD), .abilities = { ability, ABILITY_NONE, ABILITY_NONE }, .bodyColor = color, \
    .speciesName = _(name), .cryId = cry, .natDexNum = natdex, .categoryName = _(dexCategory), .height = dexHt, .weight = weightKgTenths, \
    .description = COMPOUND_STRING(dexBio), \
    .pokemonScale = 256, .trainerScale = 256, \
    .frontPic = front, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = frontY, \
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH, \
    .backPic = back, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = backY, .backAnimId = BACK_ANIM_NONE, \
    .palette = pal, .shinyPalette = shiny, .iconSprite = icon, .iconPalIndex = iconPal, \
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE, .levelUpLearnset = levelMoves, .teachableLearnset = teachMoves, \
}

PJR_RED_SPECIES(SPECIES_EDENSAUR, 95, 80, 110, 135, 105, 55, TYPE_GRASS, TYPE_POISON,
    ABILITY_GRASSY_SURGE, "Edensaur", CRY_VENUSAUR, NATIONAL_DEX_VENUSAUR, BODY_COLOR_GREEN,
    gMonFrontPic_Edensaur, gMonBackPic_Edensaur, gMonPalette_Edensaur, gMonShinyPalette_Edensaur, gMonIcon_Edensaur,
    sEdensaurLevelUpLearnset, sVenusaurTeachableLearnset, 1450, 0, 7, P_GBA_STYLE_SPECIES_ICONS ? 1 : 4, "Bloom Relic", 21, "Ancient roots spread beneath its\nflower. Soil touched by them\nbursts into sudden greenery."),

PJR_RED_SPECIES(SPECIES_CHARAXIS, 80, 120, 85, 90, 80, 125, TYPE_FIRE, TYPE_FLYING,
    ABILITY_GALE_WINGS, "Charaxis", CRY_CHARIZARD, NATIONAL_DEX_CHARIZARD, BODY_COLOR_RED,
    gMonFrontPic_Charaxis, gMonBackPic_Charaxis, gMonPalette_Charaxis, gMonShinyPalette_Charaxis, gMonIcon_Charaxis,
    sCharaxisLevelUpLearnset, sCharizardTeachableLearnset, 1030, 0, 1, 6, "Blaze Wing", 20, "It climbs on fierce updrafts,\nthen dives like an arrow with\nits burning wings tucked close."),

PJR_RED_SPECIES(SPECIES_FORTOTOISE, 95, 80, 155, 100, 105, 50, TYPE_WATER, TYPE_STEEL,
    ABILITY_STURDY, "Fortotoise", CRY_BLASTOISE, NATIONAL_DEX_BLASTOISE, BODY_COLOR_BLUE,
    gMonFrontPic_Fortotoise, gMonBackPic_Fortotoise, gMonPalette_Fortotoise, gMonShinyPalette_Fortotoise, gMonIcon_Fortotoise,
    sFortotoiseLevelUpLearnset, sBlastoiseTeachableLearnset, 1900, 0, 5, 3, "Fortress", 18, "Its fortress shell withstands\nmighty blows. Water cannons fire\nthrough iron-plated ports."),

PJR_RED_SPECIES(SPECIES_KHANG, 105, 105, 95, 50, 90, 110, TYPE_NORMAL, TYPE_FIGHTING,
    ABILITY_PARENTAL_BOND, "Khang", CRY_KANGASKHAN, NATIONAL_DEX_KANGASKHAN, BODY_COLOR_BROWN,
    gMonFrontPic_Khang, gMonBackPic_Khang, gMonPalette_Khang, gMonShinyPalette_Khang, gMonIcon_Khang,
    sKhangLevelUpLearnset, sKangaskhanTeachableLearnset, 1260, 0, 6, P_GBA_STYLE_SPECIES_ICONS ? 1 : 2, "Relic Parent", 23, "It fights fiercely while keeping\nits young close. Even mighty\nfoes retreat from its punches."),

PJR_RED_SPECIES(SPECIES_NOLAX, 100, 130, 80, 45, 90, 130, TYPE_NORMAL, TYPE_DARK,
    ABILITY_INSOMNIA, "Nolax", CRY_SNORLAX, NATIONAL_DEX_SNORLAX, BODY_COLOR_BLUE,
    gMonFrontPic_Nolax, gMonBackPic_Nolax, gMonPalette_Nolax, gMonShinyPalette_Nolax, gMonIcon_Nolax,
    sNolaxLevelUpLearnset, sNolaxTeachableLearnset, 2100, 0, 8, 3, "Restless", 21, "It never sleeps through danger.\nIts restless strength turns even\nshort charges into heavy blows."),

PJR_RED_SPECIES(SPECIES_NOXICHU, 70, 110, 70, 110, 80, 125, TYPE_ELECTRIC, TYPE_DARK,
    ABILITY_INFILTRATOR, "Noxichu", CRY_PIKACHU, NATIONAL_DEX_PIKACHU, BODY_COLOR_YELLOW,
    gMonFrontPic_Noxichu, gMonBackPic_Noxichu, gMonPalette_Noxichu, gMonShinyPalette_Noxichu, gMonIcon_Noxichu,
    sNoxichuLevelUpLearnset, sPikachuTeachableLearnset, 180, 0, 20, 6, "Eclipse", 10, "Relic lightning races across\nits shadowy fur. It watches\nover allies without flinching."),

#undef PJR_RED_SPECIES

// Trainer-only first-clear Elite Four visual forms.
#define PJR_E4_VISUAL_FORM(species, hp, atk, def, spa, spd, spe, type1, type2, ability1, ability2, hidden, name, cry, natdex, color, front, back, pal, shiny, icon, iconPal, levelMoves, teachMoves, dexCategory, dexHt, dexWt, dexBio) \
[species] = { \
    .baseHP = hp, .baseAttack = atk, .baseDefense = def, .baseSpAttack = spa, .baseSpDefense = spd, .baseSpeed = spe, \
    .types = MON_TYPES(type1, type2), .catchRate = 45, .expYield = 220, .genderRatio = PERCENT_FEMALE(50), \
    .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_FAST, \
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD), .abilities = { ability1, ability2, hidden }, .bodyColor = color, \
    .speciesName = _(name), .cryId = cry, .natDexNum = natdex, .categoryName = _(dexCategory), .height = dexHt, .weight = dexWt, \
    .description = COMPOUND_STRING(dexBio), \
    .pokemonScale = 256, .pokemonOffset = 0, .trainerScale = 256, .trainerOffset = 0, \
    .frontPic = front, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0, \
    .frontAnimFrames = sAnims_SingleFramePlaceHolder, .frontAnimId = ANIM_V_STRETCH, \
    .backPic = back, .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0, .backAnimId = BACK_ANIM_NONE, \
    .palette = pal, .shinyPalette = shiny, .iconSprite = icon, .iconPalIndex = iconPal, \
    .pokemonJumpType = PKMN_JUMP_TYPE_NONE, .levelUpLearnset = levelMoves, .teachableLearnset = teachMoves, \
    .randomizerMode = MON_RANDOMIZER_INVALID, \
}
PJR_E4_VISUAL_FORM(SPECIES_ALAKAZAM_RELIC,55,50,45,135,95,120,TYPE_PSYCHIC,TYPE_PSYCHIC,ABILITY_SYNCHRONIZE,ABILITY_INNER_FOCUS,ABILITY_MAGIC_GUARD,"Alakazam",CRY_ALAKAZAM,NATIONAL_DEX_ALAKAZAM,BODY_COLOR_BROWN,gMonFrontPic_AlakazamRelic,gMonFrontPic_AlakazamRelic,gMonPalette_AlakazamRelic,gMonShinyPalette_AlakazamRelic,gMonIcon_Alakazam,2,sAlakazamLevelUpLearnset,sAlakazamTeachableLearnset, "Mind Relic", 15, 480, "Its spoons bend toward unseen\nthoughts. Foes find their focus\nslipping during battle."),
PJR_E4_VISUAL_FORM(SPECIES_SLOWKING_RELIC,95,75,80,100,110,30,TYPE_WATER,TYPE_PSYCHIC,ABILITY_OBLIVIOUS,ABILITY_OWN_TEMPO,ABILITY_REGENERATOR,"Slowking",CRY_SLOWKING,NATIONAL_DEX_SLOWKING,BODY_COLOR_PINK,gMonFrontPic_SlowkingRelic,gMonFrontPic_SlowkingRelic,gMonPalette_SlowkingRelic,gMonShinyPalette_SlowkingRelic,gMonIcon_Slowking,0,sSlowkingLevelUpLearnset,sSlowkingTeachableLearnset, "Tide Relic", 20, 795, "Ancient tides sharpen its mind.\nIt predicts danger by listening\nto echoes in its crown."),
PJR_E4_VISUAL_FORM(SPECIES_BEEDRILL_RELIC,65,90,40,45,80,75,TYPE_BUG,TYPE_POISON,ABILITY_SWARM,ABILITY_NONE,ABILITY_SNIPER,"Beedrill",CRY_BEEDRILL,NATIONAL_DEX_BEEDRILL,BODY_COLOR_YELLOW,gMonFrontPic_BeedrillRelic,gMonFrontPic_BeedrillRelic,gMonPalette_BeedrillRelic,gMonShinyPalette_BeedrillRelic,gMonIcon_Beedrill,2,sBeedrillLevelUpLearnset,sBeedrillTeachableLearnset, "Sting Relic", 10, 295, "It darts in silent formations.\nIts twin stingers leave marks\nthat glow after every strike."),
PJR_E4_VISUAL_FORM(SPECIES_CROBAT_RELIC,85,90,80,70,80,130,TYPE_POISON,TYPE_FLYING,ABILITY_INNER_FOCUS,ABILITY_NONE,ABILITY_INFILTRATOR,"Crobat",CRY_CROBAT,NATIONAL_DEX_CROBAT,BODY_COLOR_PURPLE,gMonFrontPic_CrobatRelic,gMonFrontPic_CrobatRelic,gMonPalette_CrobatRelic,gMonShinyPalette_CrobatRelic,gMonIcon_Crobat,2,sCrobatLevelUpLearnset,sCrobatTeachableLearnset, "Night Relic", 18, 750, "In total darkness it maps the\nworld with a single cry, then\nsweeps past before dawn."),
PJR_E4_VISUAL_FORM(SPECIES_HITMONCHAN_RELIC,50,105,79,35,110,76,TYPE_FIGHTING,TYPE_FIGHTING,ABILITY_KEEN_EYE,ABILITY_IRON_FIST,ABILITY_INNER_FOCUS,"Hitmonchan",CRY_HITMONCHAN,NATIONAL_DEX_HITMONCHAN,BODY_COLOR_BROWN,gMonFrontPic_HitmonchanRelic,gMonFrontPic_HitmonchanRelic,gMonPalette_HitmonchanRelic,gMonShinyPalette_HitmonchanRelic,gMonIcon_Hitmonchan,2,sHitmonchanLevelUpLearnset,sHitmonchanTeachableLearnset, "Fist Relic", 14, 502, "The glow around its fists grows\nbrighter with each punch. It\nnever strikes a fallen foe."),
PJR_E4_VISUAL_FORM(SPECIES_HITMONLEE_RELIC,50,120,53,35,110,87,TYPE_FIGHTING,TYPE_FIGHTING,ABILITY_LIMBER,ABILITY_RECKLESS,ABILITY_UNBURDEN,"Hitmonlee",CRY_HITMONLEE,NATIONAL_DEX_HITMONLEE,BODY_COLOR_BROWN,gMonFrontPic_HitmonleeRelic,gMonFrontPic_HitmonleeRelic,gMonPalette_HitmonleeRelic,gMonShinyPalette_HitmonleeRelic,gMonIcon_Hitmonlee,2,sHitmonleeLevelUpLearnset,sHitmonleeTeachableLearnset, "Kick Relic", 15, 498, "It stores force in its coiled\nlegs. One leap carries it across\nan entire ruined courtyard."),
PJR_E4_VISUAL_FORM(SPECIES_MACHAMP_RELIC,90,130,80,65,85,55,TYPE_FIGHTING,TYPE_FIGHTING,ABILITY_GUTS,ABILITY_NO_GUARD,ABILITY_STEADFAST,"Machamp",CRY_MACHAMP,NATIONAL_DEX_MACHAMP,BODY_COLOR_GRAY,gMonFrontPic_MachampRelic,gMonFrontPic_MachampRelic,gMonPalette_MachampRelic,gMonShinyPalette_MachampRelic,gMonIcon_Machamp,0,sMachampLevelUpLearnset,sMachampTeachableLearnset, "Might Relic", 16, 1300, "Ancient bands around its arms\nfocus its strength. It lifts\nfallen stones without effort."),
PJR_E4_VISUAL_FORM(SPECIES_HOUNDOOM_RELIC,75,90,50,110,80,95,TYPE_DARK,TYPE_FIRE,ABILITY_EARLY_BIRD,ABILITY_FLASH_FIRE,ABILITY_UNNERVE,"Houndoom",CRY_HOUNDOOM,NATIONAL_DEX_HOUNDOOM,BODY_COLOR_BLACK,gMonFrontPic_HoundoomRelic,gMonFrontPic_HoundoomRelic,gMonPalette_HoundoomRelic,gMonShinyPalette_HoundoomRelic,gMonIcon_Houndoom,0,sHoundoomLevelUpLearnset,sHoundoomTeachableLearnset, "Ember Relic", 14, 350, "Its horns gleam in moonlight.\nFires left by its paws linger\nlong after its tracks fade."),
PJR_E4_VISUAL_FORM(SPECIES_GYARADOS_RELIC,95,125,79,60,100,81,TYPE_WATER,TYPE_FLYING,ABILITY_INTIMIDATE,ABILITY_NONE,ABILITY_MOXIE,"Gyarados",CRY_GYARADOS,NATIONAL_DEX_GYARADOS,BODY_COLOR_BLUE,gMonFrontPic_GyaradosRelic,gMonFrontPic_GyaradosRelic,gMonPalette_GyaradosRelic,gMonShinyPalette_GyaradosRelic,gMonIcon_Gyarados,0,sGyaradosLevelUpLearnset,sGyaradosTeachableLearnset, "Rage Relic", 65, 2350, "The river falls silent before\nit surfaces. Relic scales shine\nbeneath the breaking waves."),
// Lance's trainer-only Relic keeps its own species and battle data.
PJR_E4_VISUAL_FORM(SPECIES_DRAGONITE_RELIC,91,134,95,100,100,80,TYPE_DRAGON,TYPE_FLYING,ABILITY_INNER_FOCUS,ABILITY_NONE,ABILITY_MULTISCALE,"Dragonite",CRY_DRAGONITE,NATIONAL_DEX_DRAGONITE,BODY_COLOR_BROWN,gMonFrontPic_Dragonite,gMonBackPic_Dragonite,gMonPalette_Dragonite,gMonShinyPalette_Dragonite,gMonIcon_Dragonite,2,sDragoniteLevelUpLearnset,sDragoniteTeachableLearnset, "Sky Relic", 22, 2100, "It carries old messages across\nstorm-tossed seas. Its wings\nhold steady in lightning."),
// Battle-only species identity for the Tin Tower Guardian. It shares the
// existing Dragonite Pokédex number and is excluded from Dex/randomizer lists.
PJR_E4_VISUAL_FORM(SPECIES_DRAGONITE_GUARDIAN,91,134,95,100,100,80,TYPE_DRAGON,TYPE_FLYING,ABILITY_MULTISCALE,ABILITY_MULTISCALE,ABILITY_MULTISCALE,"Dragonite",CRY_DRAGONITE,NATIONAL_DEX_DRAGONITE,BODY_COLOR_BROWN,gMonFrontPic_DragoniteGuardian,gMonBackPic_DragoniteGuardian,gMonPalette_DragoniteGuardian,gMonShinyPalette_DragoniteGuardian,gMonIcon_DragoniteGuardian,2,sDragoniteLevelUpLearnset,sDragoniteTeachableLearnset),


PJR_E4_VISUAL_FORM(SPECIES_ASUDEM_JJ,60,110,79,70,79,100,TYPE_POISON,TYPE_DARK,ABILITY_INTIMIDATE,ABILITY_SHED_SKIN,ABILITY_UNNERVE,"Arbok",CRY_ARBOK,NATIONAL_DEX_ARBOK,BODY_COLOR_PURPLE,gMonFrontPic_AsudemJJ,gMonBackPic_AsudemJJ,gMonPalette_AsudemJJ,gMonPalette_AsudemJJ,gMonIcon_Arbok,2,sArbokLevelUpLearnset,sArbokTeachableLearnset, "Hood Relic", 35, 650, "Its patterned hood unnerves\nanyone who meets its gaze. It\ncoils beside its closest ally."),
PJR_E4_VISUAL_FORM(SPECIES_NIDOGOD_JJ,90,115,90,105,85,95,TYPE_POISON,TYPE_GROUND,ABILITY_POISON_POINT,ABILITY_RIVALRY,ABILITY_SHEER_FORCE,"Nidoking",CRY_NIDOKING,NATIONAL_DEX_NIDOKING,BODY_COLOR_PURPLE,gMonFrontPic_NidogodJJ,gMonBackPic_NidogodJJ,gMonPalette_NidogodJJ,gMonPalette_NidogodJJ,gMonIcon_Nidoking,2,sNidokingLevelUpLearnset,sNidokingTeachableLearnset, "Horn Relic", 14, 620, "Its horn cracks armored walls.\nIt shields its partner from\nattacks with its thick hide."),
PJR_E4_VISUAL_FORM(SPECIES_NIDOKING_X_BLUE,90,115,90,105,85,95,TYPE_POISON,TYPE_GROUND,ABILITY_POISON_POINT,ABILITY_RIVALRY,ABILITY_SHEER_FORCE,"Nidoking",CRY_NIDOKING,NATIONAL_DEX_NIDOKING,BODY_COLOR_PURPLE,gMonFrontPic_NidokingXBlue,gMonFrontPic_NidokingXBlue,gMonPalette_NidokingXBlue,gMonPalette_NidokingXBlue,gMonIcon_Nidoking,2,sNidokingLevelUpLearnset,sNidokingTeachableLearnset),
PJR_E4_VISUAL_FORM(SPECIES_VICTREEBEL_REDUX_JJ,80,115,75,110,75,80,TYPE_GRASS,TYPE_POISON,ABILITY_CHLOROPHYLL,ABILITY_NONE,ABILITY_GLUTTONY,"Victreebel",CRY_VICTREEBEL,NATIONAL_DEX_VICTREEBEL,BODY_COLOR_GREEN,gMonFrontPic_VictreebelReduxJJ,gMonBackPic_VictreebelReduxJJ,gMonPalette_VictreebelReduxJJ,gMonPalette_VictreebelReduxJJ,gMonIcon_Victreebel,1,sVictreebelLevelUpLearnset,sVictreebelTeachableLearnset, "Vine Relic", 17, 155, "It waits in tangled vines and\nstrikes without warning. Its\nsweet scent hides sharp jaws."),
PJR_E4_VISUAL_FORM(SPECIES_TYRANITAR_REDUX_JJ,100,164,150,95,120,71,TYPE_ROCK,TYPE_DARK,ABILITY_SAND_STREAM,ABILITY_NONE,ABILITY_UNNERVE,"Tyranitar",CRY_TYRANITAR,NATIONAL_DEX_TYRANITAR,BODY_COLOR_GREEN,gMonFrontPic_TyranitarReduxJJ,gMonBackPic_TyranitarReduxJJ,gMonPalette_TyranitarReduxJJ,gMonPalette_TyranitarReduxJJ,gMonIcon_Tyranitar,1,sTyranitarLevelUpLearnset,sTyranitarTeachableLearnset, "Crag Relic", 20, 2020, "Each step scatters stones across\nthe ground. It roars louder\nwhen its partner is threatened."),

#undef PJR_E4_VISUAL_FORM

