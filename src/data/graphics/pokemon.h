// Normally, INCBIN_COMP acts like INCBIN_U32, but appends `.lz` to the file, compressing it;
// If not compressing overworld gfx, make this an alias to INCBIN_32, so gfx will *not* be compressed
#if !(OW_GFX_COMPRESS)
#define INCBIN_COMP INCBIN_U32
#endif

const u32 gMonFrontPic_CircledQuestionMark[] = INCBIN_U32("graphics/pokemon/question_mark/circled/anim_front.4bpp.smol");
const u32 gMonBackPic_CircledQuestionMark[] = INCBIN_U32("graphics/pokemon/question_mark/circled/back.4bpp.smol");
const u16 gMonPalette_CircledQuestionMark[] = INCBIN_U16("graphics/pokemon/question_mark/circled/normal.gbapal");
const u16 gMonShinyPalette_CircledQuestionMark[] = INCBIN_U16("graphics/pokemon/question_mark/circled/shiny.gbapal");
const u8 gMonIcon_QuestionMark[] = INCBIN_U8("graphics/pokemon/question_mark/icon.4bpp");
#if P_FOOTPRINTS
#if !P_GBA_STYLE_SPECIES_FOOTPRINTS
    const u8 gMonFootprint_QuestionMark[] = INCBIN_U8("graphics/pokemon/question_mark/footprint.1bpp");
#else
    const u8 gMonFootprint_QuestionMark[] = INCBIN_U8("graphics/pokemon/question_mark/footprint_gba.1bpp");
#endif //P_GBA_STYLE_SPECIES_FOOTPRINTS
#endif //P_FOOTPRINTS
const u32 gObjectEventPic_Substitute[] = INCBIN_COMP("graphics/pokemon/question_mark/overworld.4bpp");

#if P_FAMILY_BULBASAUR
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Bulbasaur[] = INCBIN_U32("graphics/pokemon/bulbasaur/anim_front.4bpp.smol");
    const u16 gMonPalette_Bulbasaur[] = INCBIN_U16("graphics/pokemon/bulbasaur/normal.gbapal");
    const u32 gMonBackPic_Bulbasaur[] = INCBIN_U32("graphics/pokemon/bulbasaur/back.4bpp.smol");
    const u16 gMonShinyPalette_Bulbasaur[] = INCBIN_U16("graphics/pokemon/bulbasaur/shiny.gbapal");
#else
    const u32 gMonFrontPic_Bulbasaur[] = INCBIN_U32("graphics/pokemon/bulbasaur/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Bulbasaur[] = INCBIN_U16("graphics/pokemon/bulbasaur/normal_gba.gbapal");
    const u32 gMonBackPic_Bulbasaur[] = INCBIN_U32("graphics/pokemon/bulbasaur/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Bulbasaur[] = INCBIN_U16("graphics/pokemon/bulbasaur/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Bulbasaur[] = INCBIN_U8("graphics/pokemon/bulbasaur/icon.4bpp");
#else
    const u8 gMonIcon_Bulbasaur[] = INCBIN_U8("graphics/pokemon/bulbasaur/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Bulbasaur[] = INCBIN_U8("graphics/pokemon/bulbasaur/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Bulbasaur[] = INCBIN_COMP("graphics/pokemon/bulbasaur/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Bulbasaur[] = INCBIN_U16("graphics/pokemon/bulbasaur/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Bulbasaur[] = INCBIN_U16("graphics/pokemon/bulbasaur/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Ivysaur[] = INCBIN_U32("graphics/pokemon/ivysaur/anim_front.4bpp.smol");
    const u16 gMonPalette_Ivysaur[] = INCBIN_U16("graphics/pokemon/ivysaur/normal.gbapal");
    const u32 gMonBackPic_Ivysaur[] = INCBIN_U32("graphics/pokemon/ivysaur/back.4bpp.smol");
    const u16 gMonShinyPalette_Ivysaur[] = INCBIN_U16("graphics/pokemon/ivysaur/shiny.gbapal");
#else
    const u32 gMonFrontPic_Ivysaur[] = INCBIN_U32("graphics/pokemon/ivysaur/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Ivysaur[] = INCBIN_U16("graphics/pokemon/ivysaur/normal_gba.gbapal");
    const u32 gMonBackPic_Ivysaur[] = INCBIN_U32("graphics/pokemon/ivysaur/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Ivysaur[] = INCBIN_U16("graphics/pokemon/ivysaur/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Ivysaur[] = INCBIN_U8("graphics/pokemon/ivysaur/icon.4bpp");
#else
    const u8 gMonIcon_Ivysaur[] = INCBIN_U8("graphics/pokemon/ivysaur/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Ivysaur[] = INCBIN_U8("graphics/pokemon/ivysaur/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Ivysaur[] = INCBIN_COMP("graphics/pokemon/ivysaur/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Ivysaur[] = INCBIN_U16("graphics/pokemon/ivysaur/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Ivysaur[] = INCBIN_U16("graphics/pokemon/ivysaur/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Venusaur[] = INCBIN_U32("graphics/pokemon/venusaur/anim_front.4bpp.smol");
    const u16 gMonPalette_Venusaur[] = INCBIN_U16("graphics/pokemon/venusaur/normal.gbapal");
    const u32 gMonBackPic_Venusaur[] = INCBIN_U32("graphics/pokemon/venusaur/back.4bpp.smol");
    const u16 gMonShinyPalette_Venusaur[] = INCBIN_U16("graphics/pokemon/venusaur/shiny.gbapal");
#else
    const u32 gMonFrontPic_Venusaur[] = INCBIN_U32("graphics/pokemon/venusaur/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Venusaur[] = INCBIN_U16("graphics/pokemon/venusaur/normal_gba.gbapal");
    const u32 gMonBackPic_Venusaur[] = INCBIN_U32("graphics/pokemon/venusaur/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Venusaur[] = INCBIN_U16("graphics/pokemon/venusaur/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Venusaur[] = INCBIN_U8("graphics/pokemon/venusaur/icon.4bpp");
#else
    const u8 gMonIcon_Venusaur[] = INCBIN_U8("graphics/pokemon/venusaur/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Venusaur[] = INCBIN_U8("graphics/pokemon/venusaur/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Venusaur[] = INCBIN_COMP("graphics/pokemon/venusaur/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Venusaur[] = INCBIN_U16("graphics/pokemon/venusaur/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Venusaur[] = INCBIN_U16("graphics/pokemon/venusaur/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_VenusaurF[] = INCBIN_U32("graphics/pokemon/venusaur/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_VenusaurF[] = INCBIN_U32("graphics/pokemon/venusaur/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_VenusaurF[] = INCBIN_COMP("graphics/pokemon/venusaur/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_VenusaurMega[] = INCBIN_U32("graphics/pokemon/venusaur/mega/front.4bpp.smol");
    const u16 gMonPalette_VenusaurMega[] = INCBIN_U16("graphics/pokemon/venusaur/mega/normal.gbapal");
    const u32 gMonBackPic_VenusaurMega[] = INCBIN_U32("graphics/pokemon/venusaur/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_VenusaurMega[] = INCBIN_U16("graphics/pokemon/venusaur/mega/shiny.gbapal");
    const u8 gMonIcon_VenusaurMega[] = INCBIN_U8("graphics/pokemon/venusaur/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_VenusaurMega[] = INCBIN_COMP("graphics/pokemon/venusaur/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_VenusaurMega[] = INCBIN_U16("graphics/pokemon/venusaur/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_VenusaurMega[] = INCBIN_U16("graphics/pokemon/venusaur/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_VenusaurGmax[] = INCBIN_U32("graphics/pokemon/venusaur/gmax/front.4bpp.smol");
    const u32 gMonBackPic_VenusaurGmax[] = INCBIN_U32("graphics/pokemon/venusaur/gmax/back.4bpp.smol");
    const u16 gMonPalette_VenusaurGmax[] = INCBIN_U16("graphics/pokemon/venusaur/gmax/normal.gbapal");
    const u16 gMonShinyPalette_VenusaurGmax[] = INCBIN_U16("graphics/pokemon/venusaur/gmax/shiny.gbapal");
    const u8 gMonIcon_VenusaurGmax[] = INCBIN_U8("graphics/pokemon/venusaur/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_VenusaurGmax[] = INCBIN_COMP("graphics/pokemon/venusaur/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_VenusaurGmax[] = INCBIN_U16("graphics/pokemon/venusaur/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_VenusaurGmax[] = INCBIN_U16("graphics/pokemon/venusaur/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS
#endif //P_FAMILY_BULBASAUR

#if P_FAMILY_CHARMANDER
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Charmander[] = INCBIN_U32("graphics/pokemon/charmander/anim_front.4bpp.smol");
    const u16 gMonPalette_Charmander[] = INCBIN_U16("graphics/pokemon/charmander/normal.gbapal");
    const u32 gMonBackPic_Charmander[] = INCBIN_U32("graphics/pokemon/charmander/back.4bpp.smol");
    const u16 gMonShinyPalette_Charmander[] = INCBIN_U16("graphics/pokemon/charmander/shiny.gbapal");
#else
    const u32 gMonFrontPic_Charmander[] = INCBIN_U32("graphics/pokemon/charmander/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Charmander[] = INCBIN_U16("graphics/pokemon/charmander/normal_gba.gbapal");
    const u32 gMonBackPic_Charmander[] = INCBIN_U32("graphics/pokemon/charmander/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Charmander[] = INCBIN_U16("graphics/pokemon/charmander/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Charmander[] = INCBIN_U8("graphics/pokemon/charmander/icon.4bpp");
#else
    const u8 gMonIcon_Charmander[] = INCBIN_U8("graphics/pokemon/charmander/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Charmander[] = INCBIN_U8("graphics/pokemon/charmander/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Charmander[] = INCBIN_COMP("graphics/pokemon/charmander/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Charmander[] = INCBIN_U16("graphics/pokemon/charmander/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Charmander[] = INCBIN_U16("graphics/pokemon/charmander/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Charmeleon[] = INCBIN_U32("graphics/pokemon/charmeleon/anim_front.4bpp.smol");
    const u16 gMonPalette_Charmeleon[] = INCBIN_U16("graphics/pokemon/charmeleon/normal.gbapal");
    const u32 gMonBackPic_Charmeleon[] = INCBIN_U32("graphics/pokemon/charmeleon/back.4bpp.smol");
    const u16 gMonShinyPalette_Charmeleon[] = INCBIN_U16("graphics/pokemon/charmeleon/shiny.gbapal");
#else
    const u32 gMonFrontPic_Charmeleon[] = INCBIN_U32("graphics/pokemon/charmeleon/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Charmeleon[] = INCBIN_U16("graphics/pokemon/charmeleon/normal_gba.gbapal");
    const u32 gMonBackPic_Charmeleon[] = INCBIN_U32("graphics/pokemon/charmeleon/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Charmeleon[] = INCBIN_U16("graphics/pokemon/charmeleon/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Charmeleon[] = INCBIN_U8("graphics/pokemon/charmeleon/icon.4bpp");
#else
    const u8 gMonIcon_Charmeleon[] = INCBIN_U8("graphics/pokemon/charmeleon/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Charmeleon[] = INCBIN_U8("graphics/pokemon/charmeleon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Charmeleon[] = INCBIN_COMP("graphics/pokemon/charmeleon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Charmeleon[] = INCBIN_U16("graphics/pokemon/charmeleon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Charmeleon[] = INCBIN_U16("graphics/pokemon/charmeleon/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Charizard[] = INCBIN_U32("graphics/pokemon/charizard/anim_front.4bpp.smol");
    const u16 gMonPalette_Charizard[] = INCBIN_U16("graphics/pokemon/charizard/normal.gbapal");
    const u32 gMonBackPic_Charizard[] = INCBIN_U32("graphics/pokemon/charizard/back.4bpp.smol");
    const u16 gMonShinyPalette_Charizard[] = INCBIN_U16("graphics/pokemon/charizard/shiny.gbapal");
#else
    const u32 gMonFrontPic_Charizard[] = INCBIN_U32("graphics/pokemon/charizard/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Charizard[] = INCBIN_U16("graphics/pokemon/charizard/normal_gba.gbapal");
    const u32 gMonBackPic_Charizard[] = INCBIN_U32("graphics/pokemon/charizard/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Charizard[] = INCBIN_U16("graphics/pokemon/charizard/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Charizard[] = INCBIN_U8("graphics/pokemon/charizard/icon.4bpp");
#else
    const u8 gMonIcon_Charizard[] = INCBIN_U8("graphics/pokemon/charizard/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Charizard[] = INCBIN_U8("graphics/pokemon/charizard/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Charizard[] = INCBIN_COMP("graphics/pokemon/charizard/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Charizard[] = INCBIN_U16("graphics/pokemon/charizard/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Charizard[] = INCBIN_U16("graphics/pokemon/charizard/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_CharizardMegaX[] = INCBIN_U32("graphics/pokemon/charizard/mega_x/front.4bpp.smol");
    const u16 gMonPalette_CharizardMegaX[] = INCBIN_U16("graphics/pokemon/charizard/mega_x/normal.gbapal");
    const u32 gMonBackPic_CharizardMegaX[] = INCBIN_U32("graphics/pokemon/charizard/mega_x/back.4bpp.smol");
    const u16 gMonShinyPalette_CharizardMegaX[] = INCBIN_U16("graphics/pokemon/charizard/mega_x/shiny.gbapal");
    const u8 gMonIcon_CharizardMegaX[] = INCBIN_U8("graphics/pokemon/charizard/mega_x/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_CharizardMegaX[] = INCBIN_COMP("graphics/pokemon/charizard/mega_x/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_CharizardMegaX[] = INCBIN_U16("graphics/pokemon/charizard/mega_x/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_CharizardMegaX[] = INCBIN_U16("graphics/pokemon/charizard/mega_x/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS

    const u32 gMonFrontPic_CharizardMegaY[] = INCBIN_U32("graphics/pokemon/charizard/mega_y/front.4bpp.smol");
    const u16 gMonPalette_CharizardMegaY[] = INCBIN_U16("graphics/pokemon/charizard/mega_y/normal.gbapal");
    const u32 gMonBackPic_CharizardMegaY[] = INCBIN_U32("graphics/pokemon/charizard/mega_y/back.4bpp.smol");
    const u16 gMonShinyPalette_CharizardMegaY[] = INCBIN_U16("graphics/pokemon/charizard/mega_y/shiny.gbapal");
    const u8 gMonIcon_CharizardMegaY[] = INCBIN_U8("graphics/pokemon/charizard/mega_y/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_CharizardMegaY[] = INCBIN_COMP("graphics/pokemon/charizard/mega_y/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_CharizardMegaY[] = INCBIN_U16("graphics/pokemon/charizard/mega_y/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_CharizardMegaY[] = INCBIN_U16("graphics/pokemon/charizard/mega_y/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_CharizardGmax[] = INCBIN_U32("graphics/pokemon/charizard/gmax/front.4bpp.smol");
    const u32 gMonBackPic_CharizardGmax[] = INCBIN_U32("graphics/pokemon/charizard/gmax/back.4bpp.smol");
    const u16 gMonPalette_CharizardGmax[] = INCBIN_U16("graphics/pokemon/charizard/gmax/normal.gbapal");
    const u16 gMonShinyPalette_CharizardGmax[] = INCBIN_U16("graphics/pokemon/charizard/gmax/shiny.gbapal");
    const u8 gMonIcon_CharizardGmax[] = INCBIN_U8("graphics/pokemon/charizard/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_CharizardGmax[] = INCBIN_COMP("graphics/pokemon/charizard/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_CharizardGmax[] = INCBIN_U16("graphics/pokemon/charizard/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_CharizardGmax[] = INCBIN_U16("graphics/pokemon/charizard/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS
#endif //P_FAMILY_CHARMANDER

#if P_FAMILY_SQUIRTLE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Squirtle[] = INCBIN_U32("graphics/pokemon/squirtle/anim_front.4bpp.smol");
    const u16 gMonPalette_Squirtle[] = INCBIN_U16("graphics/pokemon/squirtle/normal.gbapal");
    const u32 gMonBackPic_Squirtle[] = INCBIN_U32("graphics/pokemon/squirtle/back.4bpp.smol");
    const u16 gMonShinyPalette_Squirtle[] = INCBIN_U16("graphics/pokemon/squirtle/shiny.gbapal");
#else
    const u32 gMonFrontPic_Squirtle[] = INCBIN_U32("graphics/pokemon/squirtle/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Squirtle[] = INCBIN_U16("graphics/pokemon/squirtle/normal_gba.gbapal");
    const u32 gMonBackPic_Squirtle[] = INCBIN_U32("graphics/pokemon/squirtle/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Squirtle[] = INCBIN_U16("graphics/pokemon/squirtle/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Squirtle[] = INCBIN_U8("graphics/pokemon/squirtle/icon.4bpp");
#else
    const u8 gMonIcon_Squirtle[] = INCBIN_U8("graphics/pokemon/squirtle/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Squirtle[] = INCBIN_U8("graphics/pokemon/squirtle/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Squirtle[] = INCBIN_COMP("graphics/pokemon/squirtle/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Squirtle[] = INCBIN_U16("graphics/pokemon/squirtle/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Squirtle[] = INCBIN_U16("graphics/pokemon/squirtle/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Wartortle[] = INCBIN_U32("graphics/pokemon/wartortle/anim_front.4bpp.smol");
    const u16 gMonPalette_Wartortle[] = INCBIN_U16("graphics/pokemon/wartortle/normal.gbapal");
    const u32 gMonBackPic_Wartortle[] = INCBIN_U32("graphics/pokemon/wartortle/back.4bpp.smol");
    const u16 gMonShinyPalette_Wartortle[] = INCBIN_U16("graphics/pokemon/wartortle/shiny.gbapal");
#else
    const u32 gMonFrontPic_Wartortle[] = INCBIN_U32("graphics/pokemon/wartortle/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Wartortle[] = INCBIN_U16("graphics/pokemon/wartortle/normal_gba.gbapal");
    const u32 gMonBackPic_Wartortle[] = INCBIN_U32("graphics/pokemon/wartortle/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Wartortle[] = INCBIN_U16("graphics/pokemon/wartortle/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Wartortle[] = INCBIN_U8("graphics/pokemon/wartortle/icon.4bpp");
#else
    const u8 gMonIcon_Wartortle[] = INCBIN_U8("graphics/pokemon/wartortle/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Wartortle[] = INCBIN_U8("graphics/pokemon/wartortle/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Wartortle[] = INCBIN_COMP("graphics/pokemon/wartortle/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Wartortle[] = INCBIN_U16("graphics/pokemon/wartortle/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Wartortle[] = INCBIN_U16("graphics/pokemon/wartortle/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Blastoise[] = INCBIN_U32("graphics/pokemon/blastoise/anim_front.4bpp.smol");
    const u16 gMonPalette_Blastoise[] = INCBIN_U16("graphics/pokemon/blastoise/normal.gbapal");
    const u32 gMonBackPic_Blastoise[] = INCBIN_U32("graphics/pokemon/blastoise/back.4bpp.smol");
    const u16 gMonShinyPalette_Blastoise[] = INCBIN_U16("graphics/pokemon/blastoise/shiny.gbapal");
#else
    const u32 gMonFrontPic_Blastoise[] = INCBIN_U32("graphics/pokemon/blastoise/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Blastoise[] = INCBIN_U16("graphics/pokemon/blastoise/normal_gba.gbapal");
    const u32 gMonBackPic_Blastoise[] = INCBIN_U32("graphics/pokemon/blastoise/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Blastoise[] = INCBIN_U16("graphics/pokemon/blastoise/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Blastoise[] = INCBIN_U8("graphics/pokemon/blastoise/icon.4bpp");
#else
    const u8 gMonIcon_Blastoise[] = INCBIN_U8("graphics/pokemon/blastoise/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Blastoise[] = INCBIN_U8("graphics/pokemon/blastoise/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Blastoise[] = INCBIN_COMP("graphics/pokemon/blastoise/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Blastoise[] = INCBIN_U16("graphics/pokemon/blastoise/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Blastoise[] = INCBIN_U16("graphics/pokemon/blastoise/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_BlastoiseMega[] = INCBIN_U32("graphics/pokemon/blastoise/mega/front.4bpp.smol");
    const u16 gMonPalette_BlastoiseMega[] = INCBIN_U16("graphics/pokemon/blastoise/mega/normal.gbapal");
    const u32 gMonBackPic_BlastoiseMega[] = INCBIN_U32("graphics/pokemon/blastoise/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_BlastoiseMega[] = INCBIN_U16("graphics/pokemon/blastoise/mega/shiny.gbapal");
    const u8 gMonIcon_BlastoiseMega[] = INCBIN_U8("graphics/pokemon/blastoise/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_BlastoiseMega[] = INCBIN_COMP("graphics/pokemon/blastoise/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_BlastoiseMega[] = INCBIN_U16("graphics/pokemon/blastoise/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_BlastoiseMega[] = INCBIN_U16("graphics/pokemon/blastoise/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_BlastoiseGmax[] = INCBIN_U32("graphics/pokemon/blastoise/gmax/front.4bpp.smol");
    const u32 gMonBackPic_BlastoiseGmax[] = INCBIN_U32("graphics/pokemon/blastoise/gmax/back.4bpp.smol");
    const u16 gMonPalette_BlastoiseGmax[] = INCBIN_U16("graphics/pokemon/blastoise/gmax/normal.gbapal");
    const u16 gMonShinyPalette_BlastoiseGmax[] = INCBIN_U16("graphics/pokemon/blastoise/gmax/shiny.gbapal");
    const u8 gMonIcon_BlastoiseGmax[] = INCBIN_U8("graphics/pokemon/blastoise/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_BlastoiseGmax[] = INCBIN_COMP("graphics/pokemon/blastoise/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_BlastoiseGmax[] = INCBIN_U16("graphics/pokemon/blastoise/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_BlastoiseGmax[] = INCBIN_U16("graphics/pokemon/blastoise/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS
#endif //P_FAMILY_SQUIRTLE

#if P_FAMILY_CATERPIE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Caterpie[] = INCBIN_U32("graphics/pokemon/caterpie/anim_front.4bpp.smol");
    const u16 gMonPalette_Caterpie[] = INCBIN_U16("graphics/pokemon/caterpie/normal.gbapal");
    const u32 gMonBackPic_Caterpie[] = INCBIN_U32("graphics/pokemon/caterpie/back.4bpp.smol");
    const u16 gMonShinyPalette_Caterpie[] = INCBIN_U16("graphics/pokemon/caterpie/shiny.gbapal");
#else
    const u32 gMonFrontPic_Caterpie[] = INCBIN_U32("graphics/pokemon/caterpie/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Caterpie[] = INCBIN_U16("graphics/pokemon/caterpie/normal_gba.gbapal");
    const u32 gMonBackPic_Caterpie[] = INCBIN_U32("graphics/pokemon/caterpie/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Caterpie[] = INCBIN_U16("graphics/pokemon/caterpie/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Caterpie[] = INCBIN_U8("graphics/pokemon/caterpie/icon.4bpp");
#else
    const u8 gMonIcon_Caterpie[] = INCBIN_U8("graphics/pokemon/caterpie/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Caterpie[] = INCBIN_U8("graphics/pokemon/caterpie/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Caterpie[] = INCBIN_COMP("graphics/pokemon/caterpie/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Caterpie[] = INCBIN_U16("graphics/pokemon/caterpie/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Caterpie[] = INCBIN_U16("graphics/pokemon/caterpie/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Metapod[] = INCBIN_U32("graphics/pokemon/metapod/anim_front.4bpp.smol");
    const u16 gMonPalette_Metapod[] = INCBIN_U16("graphics/pokemon/metapod/normal.gbapal");
    const u32 gMonBackPic_Metapod[] = INCBIN_U32("graphics/pokemon/metapod/back.4bpp.smol");
    const u16 gMonShinyPalette_Metapod[] = INCBIN_U16("graphics/pokemon/metapod/shiny.gbapal");
#else
    const u32 gMonFrontPic_Metapod[] = INCBIN_U32("graphics/pokemon/metapod/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Metapod[] = INCBIN_U16("graphics/pokemon/metapod/normal_gba.gbapal");
    const u32 gMonBackPic_Metapod[] = INCBIN_U32("graphics/pokemon/metapod/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Metapod[] = INCBIN_U16("graphics/pokemon/metapod/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
    const u8 gMonIcon_Metapod[] = INCBIN_U8( "graphics/pokemon/metapod/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Metapod[] = INCBIN_U8("graphics/pokemon/metapod/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Metapod[] = INCBIN_COMP("graphics/pokemon/metapod/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Metapod[] = INCBIN_U16("graphics/pokemon/metapod/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Metapod[] = INCBIN_U16("graphics/pokemon/metapod/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Butterfree[] = INCBIN_U32("graphics/pokemon/butterfree/anim_front.4bpp.smol");
    const u16 gMonPalette_Butterfree[] = INCBIN_U16("graphics/pokemon/butterfree/normal.gbapal");
    const u32 gMonBackPic_Butterfree[] = INCBIN_U32("graphics/pokemon/butterfree/back.4bpp.smol");
    const u16 gMonShinyPalette_Butterfree[] = INCBIN_U16("graphics/pokemon/butterfree/shiny.gbapal");
#else
    const u32 gMonFrontPic_Butterfree[] = INCBIN_U32("graphics/pokemon/butterfree/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Butterfree[] = INCBIN_U16("graphics/pokemon/butterfree/normal_gba.gbapal");
    const u32 gMonBackPic_Butterfree[] = INCBIN_U32("graphics/pokemon/butterfree/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Butterfree[] = INCBIN_U16("graphics/pokemon/butterfree/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Butterfree[] = INCBIN_U8("graphics/pokemon/butterfree/icon.4bpp");
#else
    const u8 gMonIcon_Butterfree[] = INCBIN_U8("graphics/pokemon/butterfree/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Butterfree[] = INCBIN_U8("graphics/pokemon/butterfree/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Butterfree[] = INCBIN_COMP("graphics/pokemon/butterfree/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Butterfree[] = INCBIN_U16("graphics/pokemon/butterfree/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Butterfree[] = INCBIN_U16("graphics/pokemon/butterfree/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_ButterfreeF[] = INCBIN_U32("graphics/pokemon/butterfree/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_ButterfreeF[] = INCBIN_U32("graphics/pokemon/butterfree/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_ButterfreeF[] = INCBIN_COMP("graphics/pokemon/butterfree/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_ButterfreeGmax[] = INCBIN_U32("graphics/pokemon/butterfree/gmax/front.4bpp.smol");
    const u32 gMonBackPic_ButterfreeGmax[] = INCBIN_U32("graphics/pokemon/butterfree/gmax/back.4bpp.smol");
    const u16 gMonPalette_ButterfreeGmax[] = INCBIN_U16("graphics/pokemon/butterfree/gmax/normal.gbapal");
    const u16 gMonShinyPalette_ButterfreeGmax[] = INCBIN_U16("graphics/pokemon/butterfree/gmax/shiny.gbapal");
    const u8 gMonIcon_ButterfreeGmax[] = INCBIN_U8("graphics/pokemon/butterfree/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_ButterfreeGmax[] = INCBIN_COMP("graphics/pokemon/butterfree/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_ButterfreeGmax[] = INCBIN_U16("graphics/pokemon/butterfree/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_ButterfreeGmax[] = INCBIN_U16("graphics/pokemon/butterfree/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS
#endif //P_FAMILY_CATERPIE

#if P_FAMILY_WEEDLE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Weedle[] = INCBIN_U32("graphics/pokemon/weedle/anim_front.4bpp.smol");
    const u16 gMonPalette_Weedle[] = INCBIN_U16("graphics/pokemon/weedle/normal.gbapal");
    const u32 gMonBackPic_Weedle[] = INCBIN_U32("graphics/pokemon/weedle/back.4bpp.smol");
    const u16 gMonShinyPalette_Weedle[] = INCBIN_U16("graphics/pokemon/weedle/shiny.gbapal");
#else
    const u32 gMonFrontPic_Weedle[] = INCBIN_U32("graphics/pokemon/weedle/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Weedle[] = INCBIN_U16("graphics/pokemon/weedle/normal_gba.gbapal");
    const u32 gMonBackPic_Weedle[] = INCBIN_U32("graphics/pokemon/weedle/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Weedle[] = INCBIN_U16("graphics/pokemon/weedle/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Weedle[] = INCBIN_U8("graphics/pokemon/weedle/icon.4bpp");
#else
    const u8 gMonIcon_Weedle[] = INCBIN_U8("graphics/pokemon/weedle/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Weedle[] = INCBIN_U8("graphics/pokemon/weedle/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Weedle[] = INCBIN_COMP("graphics/pokemon/weedle/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Weedle[] = INCBIN_U16("graphics/pokemon/weedle/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Weedle[] = INCBIN_U16("graphics/pokemon/weedle/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Kakuna[] = INCBIN_U32("graphics/pokemon/kakuna/anim_front.4bpp.smol");
    const u16 gMonPalette_Kakuna[] = INCBIN_U16("graphics/pokemon/kakuna/normal.gbapal");
    const u32 gMonBackPic_Kakuna[] = INCBIN_U32("graphics/pokemon/kakuna/back.4bpp.smol");
    const u16 gMonShinyPalette_Kakuna[] = INCBIN_U16("graphics/pokemon/kakuna/shiny.gbapal");
#else
    const u32 gMonFrontPic_Kakuna[] = INCBIN_U32("graphics/pokemon/kakuna/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Kakuna[] = INCBIN_U16("graphics/pokemon/kakuna/normal_gba.gbapal");
    const u32 gMonBackPic_Kakuna[] = INCBIN_U32("graphics/pokemon/kakuna/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Kakuna[] = INCBIN_U16("graphics/pokemon/kakuna/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Kakuna[] = INCBIN_U8("graphics/pokemon/kakuna/icon.4bpp");
#else
    const u8 gMonIcon_Kakuna[] = INCBIN_U8("graphics/pokemon/kakuna/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Kakuna[] = INCBIN_U8("graphics/pokemon/kakuna/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Kakuna[] = INCBIN_COMP("graphics/pokemon/kakuna/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Kakuna[] = INCBIN_U16("graphics/pokemon/kakuna/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Kakuna[] = INCBIN_U16("graphics/pokemon/kakuna/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Beedrill[] = INCBIN_U32("graphics/pokemon/beedrill/anim_front.4bpp.smol");
    const u16 gMonPalette_Beedrill[] = INCBIN_U16("graphics/pokemon/beedrill/normal.gbapal");
    const u32 gMonBackPic_Beedrill[] = INCBIN_U32("graphics/pokemon/beedrill/back.4bpp.smol");
    const u16 gMonShinyPalette_Beedrill[] = INCBIN_U16("graphics/pokemon/beedrill/shiny.gbapal");
#else
    const u32 gMonFrontPic_Beedrill[] = INCBIN_U32("graphics/pokemon/beedrill/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Beedrill[] = INCBIN_U16("graphics/pokemon/beedrill/normal_gba.gbapal");
    const u32 gMonBackPic_Beedrill[] = INCBIN_U32("graphics/pokemon/beedrill/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Beedrill[] = INCBIN_U16("graphics/pokemon/beedrill/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Beedrill[] = INCBIN_U8("graphics/pokemon/beedrill/icon.4bpp");
#else
    const u8 gMonIcon_Beedrill[] = INCBIN_U8("graphics/pokemon/beedrill/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Beedrill[] = INCBIN_U8("graphics/pokemon/beedrill/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Beedrill[] = INCBIN_COMP("graphics/pokemon/beedrill/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Beedrill[] = INCBIN_U16("graphics/pokemon/beedrill/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Beedrill[] = INCBIN_U16("graphics/pokemon/beedrill/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_BeedrillMega[] = INCBIN_U32("graphics/pokemon/beedrill/mega/front.4bpp.smol");
    const u16 gMonPalette_BeedrillMega[] = INCBIN_U16("graphics/pokemon/beedrill/mega/normal.gbapal");
    const u32 gMonBackPic_BeedrillMega[] = INCBIN_U32("graphics/pokemon/beedrill/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_BeedrillMega[] = INCBIN_U16("graphics/pokemon/beedrill/mega/shiny.gbapal");
    const u8 gMonIcon_BeedrillMega[] = INCBIN_U8("graphics/pokemon/beedrill/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_BeedrillMega[] = INCBIN_COMP("graphics/pokemon/beedrill/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_BeedrillMega[] = INCBIN_U16("graphics/pokemon/beedrill/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_BeedrillMega[] = INCBIN_U16("graphics/pokemon/beedrill/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS
#endif //P_FAMILY_WEEDLE

#if P_FAMILY_PIDGEY
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Pidgey[] = INCBIN_U32("graphics/pokemon/pidgey/anim_front.4bpp.smol");
    const u16 gMonPalette_Pidgey[] = INCBIN_U16("graphics/pokemon/pidgey/normal.gbapal");
    const u32 gMonBackPic_Pidgey[] = INCBIN_U32("graphics/pokemon/pidgey/back.4bpp.smol");
    const u16 gMonShinyPalette_Pidgey[] = INCBIN_U16("graphics/pokemon/pidgey/shiny.gbapal");
#else
    const u32 gMonFrontPic_Pidgey[] = INCBIN_U32("graphics/pokemon/pidgey/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Pidgey[] = INCBIN_U16("graphics/pokemon/pidgey/normal_gba.gbapal");
    const u32 gMonBackPic_Pidgey[] = INCBIN_U32("graphics/pokemon/pidgey/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Pidgey[] = INCBIN_U16("graphics/pokemon/pidgey/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Pidgey[] = INCBIN_U8("graphics/pokemon/pidgey/icon.4bpp");
#else
    const u8 gMonIcon_Pidgey[] = INCBIN_U8("graphics/pokemon/pidgey/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Pidgey[] = INCBIN_U8("graphics/pokemon/pidgey/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Pidgey[] = INCBIN_COMP("graphics/pokemon/pidgey/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Pidgey[] = INCBIN_U16("graphics/pokemon/pidgey/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Pidgey[] = INCBIN_U16("graphics/pokemon/pidgey/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Pidgeotto[] = INCBIN_U32("graphics/pokemon/pidgeotto/anim_front.4bpp.smol");
    const u16 gMonPalette_Pidgeotto[] = INCBIN_U16("graphics/pokemon/pidgeotto/normal.gbapal");
    const u32 gMonBackPic_Pidgeotto[] = INCBIN_U32("graphics/pokemon/pidgeotto/back.4bpp.smol");
    const u16 gMonShinyPalette_Pidgeotto[] = INCBIN_U16("graphics/pokemon/pidgeotto/shiny.gbapal");
#else
    const u32 gMonFrontPic_Pidgeotto[] = INCBIN_U32("graphics/pokemon/pidgeotto/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Pidgeotto[] = INCBIN_U16("graphics/pokemon/pidgeotto/normal_gba.gbapal");
    const u32 gMonBackPic_Pidgeotto[] = INCBIN_U32("graphics/pokemon/pidgeotto/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Pidgeotto[] = INCBIN_U16("graphics/pokemon/pidgeotto/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Pidgeotto[] = INCBIN_U8("graphics/pokemon/pidgeotto/icon.4bpp");
#else
    const u8 gMonIcon_Pidgeotto[] = INCBIN_U8("graphics/pokemon/pidgeotto/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Pidgeotto[] = INCBIN_U8("graphics/pokemon/pidgeotto/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Pidgeotto[] = INCBIN_COMP("graphics/pokemon/pidgeotto/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Pidgeotto[] = INCBIN_U16("graphics/pokemon/pidgeotto/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Pidgeotto[] = INCBIN_U16("graphics/pokemon/pidgeotto/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Pidgeot[] = INCBIN_U32("graphics/pokemon/pidgeot/anim_front.4bpp.smol");
    const u16 gMonPalette_Pidgeot[] = INCBIN_U16("graphics/pokemon/pidgeot/normal.gbapal");
    const u32 gMonBackPic_Pidgeot[] = INCBIN_U32("graphics/pokemon/pidgeot/back.4bpp.smol");
    const u16 gMonShinyPalette_Pidgeot[] = INCBIN_U16("graphics/pokemon/pidgeot/shiny.gbapal");
#else
    const u32 gMonFrontPic_Pidgeot[] = INCBIN_U32("graphics/pokemon/pidgeot/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Pidgeot[] = INCBIN_U16("graphics/pokemon/pidgeot/normal_gba.gbapal");
    const u32 gMonBackPic_Pidgeot[] = INCBIN_U32("graphics/pokemon/pidgeot/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Pidgeot[] = INCBIN_U16("graphics/pokemon/pidgeot/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Pidgeot[] = INCBIN_U8("graphics/pokemon/pidgeot/icon.4bpp");
#else
    const u8 gMonIcon_Pidgeot[] = INCBIN_U8("graphics/pokemon/pidgeot/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Pidgeot[] = INCBIN_U8("graphics/pokemon/pidgeot/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Pidgeot[] = INCBIN_COMP("graphics/pokemon/pidgeot/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Pidgeot[] = INCBIN_U16("graphics/pokemon/pidgeot/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Pidgeot[] = INCBIN_U16("graphics/pokemon/pidgeot/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_PidgeotMega[] = INCBIN_U32("graphics/pokemon/pidgeot/mega/front.4bpp.smol");
    const u16 gMonPalette_PidgeotMega[] = INCBIN_U16("graphics/pokemon/pidgeot/mega/normal.gbapal");
    const u32 gMonBackPic_PidgeotMega[] = INCBIN_U32("graphics/pokemon/pidgeot/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_PidgeotMega[] = INCBIN_U16("graphics/pokemon/pidgeot/mega/shiny.gbapal");
    const u8 gMonIcon_PidgeotMega[] = INCBIN_U8("graphics/pokemon/pidgeot/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_PidgeotMega[] = INCBIN_COMP("graphics/pokemon/pidgeot/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_PidgeotMega[] = INCBIN_U16("graphics/pokemon/pidgeot/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_PidgeotMega[] = INCBIN_U16("graphics/pokemon/pidgeot/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS
#endif //P_FAMILY_PIDGEY

#if P_FAMILY_RATTATA
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Rattata[] = INCBIN_U32("graphics/pokemon/rattata/anim_front.4bpp.smol");
    const u16 gMonPalette_Rattata[] = INCBIN_U16("graphics/pokemon/rattata/normal.gbapal");
    const u32 gMonBackPic_Rattata[] = INCBIN_U32("graphics/pokemon/rattata/back.4bpp.smol");
    const u16 gMonShinyPalette_Rattata[] = INCBIN_U16("graphics/pokemon/rattata/shiny.gbapal");
#else
    const u32 gMonFrontPic_Rattata[] = INCBIN_U32("graphics/pokemon/rattata/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Rattata[] = INCBIN_U16("graphics/pokemon/rattata/normal_gba.gbapal");
    const u32 gMonBackPic_Rattata[] = INCBIN_U32("graphics/pokemon/rattata/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Rattata[] = INCBIN_U16("graphics/pokemon/rattata/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Rattata[] = INCBIN_U8("graphics/pokemon/rattata/icon.4bpp");
#else
    const u8 gMonIcon_Rattata[] = INCBIN_U8("graphics/pokemon/rattata/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Rattata[] = INCBIN_U8("graphics/pokemon/rattata/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Rattata[] = INCBIN_COMP("graphics/pokemon/rattata/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Rattata[] = INCBIN_U16("graphics/pokemon/rattata/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Rattata[] = INCBIN_U16("graphics/pokemon/rattata/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_RattataF[] = INCBIN_U32("graphics/pokemon/rattata/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_RattataF[] = INCBIN_U32("graphics/pokemon/rattata/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RattataF[] = INCBIN_COMP("graphics/pokemon/rattata/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Raticate[] = INCBIN_U32("graphics/pokemon/raticate/anim_front.4bpp.smol");
    const u16 gMonPalette_Raticate[] = INCBIN_U16("graphics/pokemon/raticate/normal.gbapal");
    const u32 gMonBackPic_Raticate[] = INCBIN_U32("graphics/pokemon/raticate/back.4bpp.smol");
    const u16 gMonShinyPalette_Raticate[] = INCBIN_U16("graphics/pokemon/raticate/shiny.gbapal");
#else
    const u32 gMonFrontPic_Raticate[] = INCBIN_U32("graphics/pokemon/raticate/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Raticate[] = INCBIN_U16("graphics/pokemon/raticate/normal_gba.gbapal");
    const u32 gMonBackPic_Raticate[] = INCBIN_U32("graphics/pokemon/raticate/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Raticate[] = INCBIN_U16("graphics/pokemon/raticate/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Raticate[] = INCBIN_U8("graphics/pokemon/raticate/icon.4bpp");
#else
    const u8 gMonIcon_Raticate[] = INCBIN_U8("graphics/pokemon/raticate/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Raticate[] = INCBIN_U8("graphics/pokemon/raticate/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Raticate[] = INCBIN_COMP("graphics/pokemon/raticate/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Raticate[] = INCBIN_U16("graphics/pokemon/raticate/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Raticate[] = INCBIN_U16("graphics/pokemon/raticate/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_RaticateF[] = INCBIN_U32("graphics/pokemon/raticate/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_RaticateF[] = INCBIN_U32("graphics/pokemon/raticate/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RaticateF[] = INCBIN_COMP("graphics/pokemon/raticate/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_RattataAlola[] = INCBIN_U32("graphics/pokemon/rattata/alola/front.4bpp.smol");
    const u16 gMonPalette_RattataAlola[] = INCBIN_U16("graphics/pokemon/rattata/alola/normal.gbapal");
    const u32 gMonBackPic_RattataAlola[] = INCBIN_U32("graphics/pokemon/rattata/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_RattataAlola[] = INCBIN_U16("graphics/pokemon/rattata/alola/shiny.gbapal");
    const u8 gMonIcon_RattataAlola[] = INCBIN_U8("graphics/pokemon/rattata/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RattataAlola[] = INCBIN_COMP("graphics/pokemon/rattata/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_RattataAlola[] = INCBIN_U16("graphics/pokemon/rattata/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_RattataAlola[] = INCBIN_U16("graphics/pokemon/rattata/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_RaticateAlola[] = INCBIN_U32("graphics/pokemon/raticate/alola/front.4bpp.smol");
    const u16 gMonPalette_RaticateAlola[] = INCBIN_U16("graphics/pokemon/raticate/alola/normal.gbapal");
    const u32 gMonBackPic_RaticateAlola[] = INCBIN_U32("graphics/pokemon/raticate/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_RaticateAlola[] = INCBIN_U16("graphics/pokemon/raticate/alola/shiny.gbapal");
    const u8 gMonIcon_RaticateAlola[] = INCBIN_U8("graphics/pokemon/raticate/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RaticateAlola[] = INCBIN_COMP("graphics/pokemon/raticate/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_RaticateAlola[] = INCBIN_U16("graphics/pokemon/raticate/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_RaticateAlola[] = INCBIN_U16("graphics/pokemon/raticate/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_RATTATA

#if P_FAMILY_SPEAROW
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Spearow[] = INCBIN_U32("graphics/pokemon/spearow/anim_front.4bpp.smol");
    const u16 gMonPalette_Spearow[] = INCBIN_U16("graphics/pokemon/spearow/normal.gbapal");
    const u32 gMonBackPic_Spearow[] = INCBIN_U32("graphics/pokemon/spearow/back.4bpp.smol");
    const u16 gMonShinyPalette_Spearow[] = INCBIN_U16("graphics/pokemon/spearow/shiny.gbapal");
#else
    const u32 gMonFrontPic_Spearow[] = INCBIN_U32("graphics/pokemon/spearow/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Spearow[] = INCBIN_U16("graphics/pokemon/spearow/normal_gba.gbapal");
    const u32 gMonBackPic_Spearow[] = INCBIN_U32("graphics/pokemon/spearow/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Spearow[] = INCBIN_U16("graphics/pokemon/spearow/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Spearow[] = INCBIN_U8("graphics/pokemon/spearow/icon.4bpp");
#else
    const u8 gMonIcon_Spearow[] = INCBIN_U8("graphics/pokemon/spearow/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Spearow[] = INCBIN_U8("graphics/pokemon/spearow/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Spearow[] = INCBIN_COMP("graphics/pokemon/spearow/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Spearow[] = INCBIN_U16("graphics/pokemon/spearow/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Spearow[] = INCBIN_U16("graphics/pokemon/spearow/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Fearow[] = INCBIN_U32("graphics/pokemon/fearow/anim_front.4bpp.smol");
    const u16 gMonPalette_Fearow[] = INCBIN_U16("graphics/pokemon/fearow/normal.gbapal");
    const u32 gMonBackPic_Fearow[] = INCBIN_U32("graphics/pokemon/fearow/back.4bpp.smol");
    const u16 gMonShinyPalette_Fearow[] = INCBIN_U16("graphics/pokemon/fearow/shiny.gbapal");
#else
    const u32 gMonFrontPic_Fearow[] = INCBIN_U32("graphics/pokemon/fearow/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Fearow[] = INCBIN_U16("graphics/pokemon/fearow/normal_gba.gbapal");
    const u32 gMonBackPic_Fearow[] = INCBIN_U32("graphics/pokemon/fearow/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Fearow[] = INCBIN_U16("graphics/pokemon/fearow/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Fearow[] = INCBIN_U8("graphics/pokemon/fearow/icon.4bpp");
#else
    const u8 gMonIcon_Fearow[] = INCBIN_U8("graphics/pokemon/fearow/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Fearow[] = INCBIN_U8("graphics/pokemon/fearow/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Fearow[] = INCBIN_COMP("graphics/pokemon/fearow/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Fearow[] = INCBIN_U16("graphics/pokemon/fearow/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Fearow[] = INCBIN_U16("graphics/pokemon/fearow/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_SPEAROW

#if P_FAMILY_EKANS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Ekans[] = INCBIN_U32("graphics/pokemon/ekans/anim_front.4bpp.smol");
    const u16 gMonPalette_Ekans[] = INCBIN_U16("graphics/pokemon/ekans/normal.gbapal");
    const u32 gMonBackPic_Ekans[] = INCBIN_U32("graphics/pokemon/ekans/back.4bpp.smol");
    const u16 gMonShinyPalette_Ekans[] = INCBIN_U16("graphics/pokemon/ekans/shiny.gbapal");
#else
    const u32 gMonFrontPic_Ekans[] = INCBIN_U32("graphics/pokemon/ekans/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Ekans[] = INCBIN_U16("graphics/pokemon/ekans/normal_gba.gbapal");
    const u32 gMonBackPic_Ekans[] = INCBIN_U32("graphics/pokemon/ekans/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Ekans[] = INCBIN_U16("graphics/pokemon/ekans/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Ekans[] = INCBIN_U8("graphics/pokemon/ekans/icon.4bpp");
#else
    const u8 gMonIcon_Ekans[] = INCBIN_U8("graphics/pokemon/ekans/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Ekans[] = INCBIN_U8("graphics/pokemon/ekans/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Ekans[] = INCBIN_COMP("graphics/pokemon/ekans/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Ekans[] = INCBIN_U16("graphics/pokemon/ekans/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Ekans[] = INCBIN_U16("graphics/pokemon/ekans/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Arbok[] = INCBIN_U32("graphics/pokemon/arbok/anim_front.4bpp.smol");
    const u16 gMonPalette_Arbok[] = INCBIN_U16("graphics/pokemon/arbok/normal.gbapal");
    const u32 gMonBackPic_Arbok[] = INCBIN_U32("graphics/pokemon/arbok/back.4bpp.smol");
    const u16 gMonShinyPalette_Arbok[] = INCBIN_U16("graphics/pokemon/arbok/shiny.gbapal");
#else
    const u32 gMonFrontPic_Arbok[] = INCBIN_U32("graphics/pokemon/arbok/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Arbok[] = INCBIN_U16("graphics/pokemon/arbok/normal_gba.gbapal");
    const u32 gMonBackPic_Arbok[] = INCBIN_U32("graphics/pokemon/arbok/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Arbok[] = INCBIN_U16("graphics/pokemon/arbok/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Arbok[] = INCBIN_U8("graphics/pokemon/arbok/icon.4bpp");
#else
    const u8 gMonIcon_Arbok[] = INCBIN_U8("graphics/pokemon/arbok/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Arbok[] = INCBIN_U8("graphics/pokemon/arbok/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Arbok[] = INCBIN_COMP("graphics/pokemon/arbok/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Arbok[] = INCBIN_U16("graphics/pokemon/arbok/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Arbok[] = INCBIN_U16("graphics/pokemon/arbok/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_EKANS

#if P_FAMILY_PIKACHU
#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Pichu[] = INCBIN_U32("graphics/pokemon/pichu/anim_front.4bpp.smol");
    const u16 gMonPalette_Pichu[] = INCBIN_U16("graphics/pokemon/pichu/normal.gbapal");
    const u32 gMonBackPic_Pichu[] = INCBIN_U32("graphics/pokemon/pichu/back.4bpp.smol");
    const u16 gMonShinyPalette_Pichu[] = INCBIN_U16("graphics/pokemon/pichu/shiny.gbapal");
#else
    const u32 gMonFrontPic_Pichu[] = INCBIN_U32("graphics/pokemon/pichu/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Pichu[] = INCBIN_U16("graphics/pokemon/pichu/normal_gba.gbapal");
    const u32 gMonBackPic_Pichu[] = INCBIN_U32("graphics/pokemon/pichu/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Pichu[] = INCBIN_U16("graphics/pokemon/pichu/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Pichu[] = INCBIN_U8("graphics/pokemon/pichu/icon.4bpp");
#else
    const u8 gMonIcon_Pichu[] = INCBIN_U8("graphics/pokemon/pichu/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Pichu[] = INCBIN_U8("graphics/pokemon/pichu/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Pichu[] = INCBIN_COMP("graphics/pokemon/pichu/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Pichu[] = INCBIN_U16("graphics/pokemon/pichu/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Pichu[] = INCBIN_U16("graphics/pokemon/pichu/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Pichu[] = INCBIN_U16("graphics/pokemon/pichu/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_PichuSpikyEared[] = INCBIN_U32("graphics/pokemon/pichu/spiky_eared/anim_front.4bpp.smol");
    const u16 gMonPalette_PichuSpikyEared[] = INCBIN_U16("graphics/pokemon/pichu/spiky_eared/normal.gbapal");
    const u32 gMonBackPic_PichuSpikyEared[] = INCBIN_U32("graphics/pokemon/pichu/spiky_eared/back.4bpp.smol");
    const u16 gMonShinyPalette_PichuSpikyEared[] = INCBIN_U16("graphics/pokemon/pichu/spiky_eared/shiny.gbapal");
    const u8 gMonIcon_PichuSpikyEared[] = INCBIN_U8("graphics/pokemon/pichu/spiky_eared/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_PichuSpikyEared[] = INCBIN_COMP("graphics/pokemon/pichu/spiky_eared/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_PichuSpikyEared[] = INCBIN_U16("graphics/pokemon/pichu/spiky_eared/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_PichuSpikyEared[] = INCBIN_U16("graphics/pokemon/pichu/spiky_eared/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Pikachu[] = INCBIN_U32("graphics/pokemon/pikachu/anim_front.4bpp.smol");
    const u16 gMonPalette_Pikachu[] = INCBIN_U16("graphics/pokemon/pikachu/normal.gbapal");
    const u32 gMonBackPic_Pikachu[] = INCBIN_U32("graphics/pokemon/pikachu/back.4bpp.smol");
    const u16 gMonShinyPalette_Pikachu[] = INCBIN_U16("graphics/pokemon/pikachu/shiny.gbapal");
#else
    const u32 gMonFrontPic_Pikachu[] = INCBIN_U32("graphics/pokemon/pikachu/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Pikachu[] = INCBIN_U16("graphics/pokemon/pikachu/normal_gba.gbapal");
    const u32 gMonBackPic_Pikachu[] = INCBIN_U32("graphics/pokemon/pikachu/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Pikachu[] = INCBIN_U16("graphics/pokemon/pikachu/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Pikachu[] = INCBIN_U8("graphics/pokemon/pikachu/icon.4bpp");
#else
    const u8 gMonIcon_Pikachu[] = INCBIN_U8("graphics/pokemon/pikachu/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Pikachu[] = INCBIN_U8("graphics/pokemon/pikachu/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Pikachu[] = INCBIN_COMP("graphics/pokemon/pikachu/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Pikachu[] = INCBIN_U16("graphics/pokemon/pikachu/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Pikachu[] = INCBIN_U16("graphics/pokemon/pikachu/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Pikachu[] = INCBIN_U16("graphics/pokemon/pikachu/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_PikachuF[] = INCBIN_U32("graphics/pokemon/pikachu/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_PikachuF[] = INCBIN_U32("graphics/pokemon/pikachu/backf.4bpp.smol");
#if P_CUSTOM_GENDER_DIFF_ICONS
    const u8 gMonIcon_PikachuF[] = INCBIN_U8("graphics/pokemon/pikachu/iconf.4bpp");
#endif
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_PikachuF[] = INCBIN_COMP("graphics/pokemon/pikachu/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_COSPLAY_PIKACHU_FORMS
    const u32 gMonFrontPic_PikachuCosplay[] = INCBIN_U32("graphics/pokemon/pikachu/cosplay/front.4bpp.smol");
    const u16 gMonPalette_PikachuCosplay[] = INCBIN_U16("graphics/pokemon/pikachu/cosplay/normal.gbapal");
    const u32 gMonBackPic_PikachuCosplay[] = INCBIN_U32("graphics/pokemon/pikachu/cosplay/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuCosplay[] = INCBIN_U16("graphics/pokemon/pikachu/cosplay/shiny.gbapal");
    const u8 gMonIcon_PikachuCosplay[] = INCBIN_U8("graphics/pokemon/pikachu/cosplay/icon.4bpp");

    const u32 gMonFrontPic_PikachuRockStar[] = INCBIN_U32("graphics/pokemon/pikachu/rock_star/front.4bpp.smol");
    const u16 gMonPalette_PikachuRockStar[] = INCBIN_U16("graphics/pokemon/pikachu/rock_star/normal.gbapal");
    const u32 gMonBackPic_PikachuRockStar[] = INCBIN_U32("graphics/pokemon/pikachu/rock_star/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuRockStar[] = INCBIN_U16("graphics/pokemon/pikachu/rock_star/shiny.gbapal");
    const u8 gMonIcon_PikachuRockStar[] = INCBIN_U8("graphics/pokemon/pikachu/rock_star/icon.4bpp");

    const u32 gMonFrontPic_PikachuBelle[] = INCBIN_U32("graphics/pokemon/pikachu/belle/front.4bpp.smol");
    const u16 gMonPalette_PikachuBelle[] = INCBIN_U16("graphics/pokemon/pikachu/belle/normal.gbapal");
    const u32 gMonBackPic_PikachuBelle[] = INCBIN_U32("graphics/pokemon/pikachu/belle/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuBelle[] = INCBIN_U16("graphics/pokemon/pikachu/belle/shiny.gbapal");
    const u8 gMonIcon_PikachuBelle[] = INCBIN_U8("graphics/pokemon/pikachu/belle/icon.4bpp");

    const u32 gMonFrontPic_PikachuPopStar[] = INCBIN_U32("graphics/pokemon/pikachu/pop_star/front.4bpp.smol");
    const u16 gMonPalette_PikachuPopStar[] = INCBIN_U16("graphics/pokemon/pikachu/pop_star/normal.gbapal");
    const u32 gMonBackPic_PikachuPopStar[] = INCBIN_U32("graphics/pokemon/pikachu/pop_star/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuPopStar[] = INCBIN_U16("graphics/pokemon/pikachu/pop_star/shiny.gbapal");
    const u8 gMonIcon_PikachuPopStar[] = INCBIN_U8("graphics/pokemon/pikachu/pop_star/icon.4bpp");

    const u32 gMonFrontPic_PikachuPhD[] = INCBIN_U32("graphics/pokemon/pikachu/phd/front.4bpp.smol");
    const u16 gMonPalette_PikachuPhD[] = INCBIN_U16("graphics/pokemon/pikachu/phd/normal.gbapal");
    const u32 gMonBackPic_PikachuPhD[] = INCBIN_U32("graphics/pokemon/pikachu/phd/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuPhD[] = INCBIN_U16("graphics/pokemon/pikachu/phd/shiny.gbapal");
    const u8 gMonIcon_PikachuPhD[] = INCBIN_U8("graphics/pokemon/pikachu/phd/icon.4bpp");

    const u32 gMonFrontPic_PikachuLibre[] = INCBIN_U32("graphics/pokemon/pikachu/libre/front.4bpp.smol");
    const u16 gMonPalette_PikachuLibre[] = INCBIN_U16("graphics/pokemon/pikachu/libre/normal.gbapal");
    const u32 gMonBackPic_PikachuLibre[] = INCBIN_U32("graphics/pokemon/pikachu/libre/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuLibre[] = INCBIN_U16("graphics/pokemon/pikachu/libre/shiny.gbapal");
    const u8 gMonIcon_PikachuLibre[] = INCBIN_U8("graphics/pokemon/pikachu/libre/icon.4bpp");

#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_PikachuCosplay[] = INCBIN_COMP("graphics/pokemon/pikachu/cosplay/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuRockStar[] = INCBIN_COMP("graphics/pokemon/pikachu/rock_star/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuBelle[] = INCBIN_COMP("graphics/pokemon/pikachu/belle/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuPopStar[] = INCBIN_COMP("graphics/pokemon/pikachu/pop_star/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuPhD[] = INCBIN_COMP("graphics/pokemon/pikachu/phd/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuLibre[] = INCBIN_COMP("graphics/pokemon/pikachu/libre/overworld.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_COSPLAY_PIKACHU_FORMS

#if P_CAP_PIKACHU_FORMS
    const u32 gMonFrontPic_PikachuOriginal[] = INCBIN_U32("graphics/pokemon/pikachu/original/front.4bpp.smol");
    const u16 gMonPalette_PikachuOriginal[] = INCBIN_U16("graphics/pokemon/pikachu/original/normal.gbapal");
    const u32 gMonBackPic_PikachuOriginal[] = INCBIN_U32("graphics/pokemon/pikachu/original/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuOriginal[] = INCBIN_U16("graphics/pokemon/pikachu/original/shiny.gbapal");
    const u8 gMonIcon_PikachuOriginal[] = INCBIN_U8("graphics/pokemon/pikachu/original/icon.4bpp");

    const u32 gMonFrontPic_PikachuHoenn[] = INCBIN_U32("graphics/pokemon/pikachu/hoenn/front.4bpp.smol");
    const u16 gMonPalette_PikachuHoenn[] = INCBIN_U16("graphics/pokemon/pikachu/hoenn/normal.gbapal");
    const u32 gMonBackPic_PikachuHoenn[] = INCBIN_U32("graphics/pokemon/pikachu/hoenn/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuHoenn[] = INCBIN_U16("graphics/pokemon/pikachu/hoenn/shiny.gbapal");
    const u8 gMonIcon_PikachuHoenn[] = INCBIN_U8("graphics/pokemon/pikachu/hoenn/icon.4bpp");

    const u32 gMonFrontPic_PikachuSinnoh[] = INCBIN_U32("graphics/pokemon/pikachu/sinnoh/front.4bpp.smol");
    const u16 gMonPalette_PikachuSinnoh[] = INCBIN_U16("graphics/pokemon/pikachu/sinnoh/normal.gbapal");
    const u32 gMonBackPic_PikachuSinnoh[] = INCBIN_U32("graphics/pokemon/pikachu/sinnoh/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuSinnoh[] = INCBIN_U16("graphics/pokemon/pikachu/sinnoh/shiny.gbapal");
    const u8 gMonIcon_PikachuSinnoh[] = INCBIN_U8("graphics/pokemon/pikachu/sinnoh/icon.4bpp");

    const u32 gMonFrontPic_PikachuUnova[] = INCBIN_U32("graphics/pokemon/pikachu/unova/front.4bpp.smol");
    const u16 gMonPalette_PikachuUnova[] = INCBIN_U16("graphics/pokemon/pikachu/unova/normal.gbapal");
    const u32 gMonBackPic_PikachuUnova[] = INCBIN_U32("graphics/pokemon/pikachu/unova/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuUnova[] = INCBIN_U16("graphics/pokemon/pikachu/unova/shiny.gbapal");
    const u8 gMonIcon_PikachuUnova[] = INCBIN_U8("graphics/pokemon/pikachu/unova/icon.4bpp");

    const u32 gMonFrontPic_PikachuKalos[] = INCBIN_U32("graphics/pokemon/pikachu/kalos/front.4bpp.smol");
    const u16 gMonPalette_PikachuKalos[] = INCBIN_U16("graphics/pokemon/pikachu/kalos/normal.gbapal");
    const u32 gMonBackPic_PikachuKalos[] = INCBIN_U32("graphics/pokemon/pikachu/kalos/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuKalos[] = INCBIN_U16("graphics/pokemon/pikachu/kalos/shiny.gbapal");
    const u8 gMonIcon_PikachuKalos[] = INCBIN_U8("graphics/pokemon/pikachu/kalos/icon.4bpp");

    const u32 gMonFrontPic_PikachuAlola[] = INCBIN_U32("graphics/pokemon/pikachu/alola/front.4bpp.smol");
    const u16 gMonPalette_PikachuAlola[] = INCBIN_U16("graphics/pokemon/pikachu/alola/normal.gbapal");
    const u32 gMonBackPic_PikachuAlola[] = INCBIN_U32("graphics/pokemon/pikachu/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuAlola[] = INCBIN_U16("graphics/pokemon/pikachu/alola/shiny.gbapal");
    const u8 gMonIcon_PikachuAlola[] = INCBIN_U8("graphics/pokemon/pikachu/alola/icon.4bpp");

    const u32 gMonFrontPic_PikachuPartner[] = INCBIN_U32("graphics/pokemon/pikachu/partner/front.4bpp.smol");
    const u16 gMonPalette_PikachuPartner[] = INCBIN_U16("graphics/pokemon/pikachu/partner/normal.gbapal");
    const u32 gMonBackPic_PikachuPartner[] = INCBIN_U32("graphics/pokemon/pikachu/partner/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuPartner[] = INCBIN_U16("graphics/pokemon/pikachu/partner/shiny.gbapal");
    const u8 gMonIcon_PikachuPartner[] = INCBIN_U8("graphics/pokemon/pikachu/partner/icon.4bpp");

    const u32 gMonFrontPic_PikachuWorld[] = INCBIN_U32("graphics/pokemon/pikachu/world/front.4bpp.smol");
    const u16 gMonPalette_PikachuWorld[] = INCBIN_U16("graphics/pokemon/pikachu/world/normal.gbapal");
    const u32 gMonBackPic_PikachuWorld[] = INCBIN_U32("graphics/pokemon/pikachu/world/back.4bpp.smol");
    const u16 gMonShinyPalette_PikachuWorld[] = INCBIN_U16("graphics/pokemon/pikachu/world/shiny.gbapal");
    const u8 gMonIcon_PikachuWorld[] = INCBIN_U8("graphics/pokemon/pikachu/world/icon.4bpp");

#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_PikachuOriginal[] = INCBIN_COMP("graphics/pokemon/pikachu/original/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuHoenn[] = INCBIN_COMP("graphics/pokemon/pikachu/hoenn/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuSinnoh[] = INCBIN_COMP("graphics/pokemon/pikachu/sinnoh/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuUnova[] = INCBIN_COMP("graphics/pokemon/pikachu/unova/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuKalos[] = INCBIN_COMP("graphics/pokemon/pikachu/kalos/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuAlola[] = INCBIN_COMP("graphics/pokemon/pikachu/alola/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuPartner[] = INCBIN_COMP("graphics/pokemon/pikachu/partner/overworld.4bpp");
    // const u32 gObjectEventPic_PikachuWorld[] = INCBIN_COMP("graphics/pokemon/pikachu/world/overworld.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_CAP_PIKACHU_FORMS

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_PikachuGmax[] = INCBIN_U32("graphics/pokemon/pikachu/gmax/front.4bpp.smol");
    const u32 gMonBackPic_PikachuGmax[] = INCBIN_U32("graphics/pokemon/pikachu/gmax/back.4bpp.smol");
    const u16 gMonPalette_PikachuGmax[] = INCBIN_U16("graphics/pokemon/pikachu/gmax/normal.gbapal");
    const u16 gMonShinyPalette_PikachuGmax[] = INCBIN_U16("graphics/pokemon/pikachu/gmax/shiny.gbapal");
    const u8 gMonIcon_PikachuGmax[] = INCBIN_U8("graphics/pokemon/pikachu/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_PikachuGmax[] = INCBIN_COMP("graphics/pokemon/pikachu/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_PikachuGmax[] = INCBIN_U16("graphics/pokemon/pikachu/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_PikachuGmax[] = INCBIN_U16("graphics/pokemon/pikachu/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS

    const u8 gMonIcon_PikachuStarter[] = INCBIN_U8("graphics/pokemon/pikachu/starter/icon.4bpp");
#if P_GENDER_DIFFERENCES && P_CUSTOM_GENDER_DIFF_ICONS
    const u8 gMonIcon_PikachuStarterF[] = INCBIN_U8("graphics/pokemon/pikachu/starter/iconf.4bpp");
#endif //P_GENDER_DIFFERENCES && P_CUSTOM_GENDER_DIFF_ICONS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Raichu[] = INCBIN_U32("graphics/pokemon/raichu/anim_front.4bpp.smol");
    const u16 gMonPalette_Raichu[] = INCBIN_U16("graphics/pokemon/raichu/normal.gbapal");
    const u32 gMonBackPic_Raichu[] = INCBIN_U32("graphics/pokemon/raichu/back.4bpp.smol");
    const u16 gMonShinyPalette_Raichu[] = INCBIN_U16("graphics/pokemon/raichu/shiny.gbapal");
#else
    const u32 gMonFrontPic_Raichu[] = INCBIN_U32("graphics/pokemon/raichu/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Raichu[] = INCBIN_U16("graphics/pokemon/raichu/normal_gba.gbapal");
    const u32 gMonBackPic_Raichu[] = INCBIN_U32("graphics/pokemon/raichu/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Raichu[] = INCBIN_U16("graphics/pokemon/raichu/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Raichu[] = INCBIN_U8("graphics/pokemon/raichu/icon.4bpp");
#else
    const u8 gMonIcon_Raichu[] = INCBIN_U8("graphics/pokemon/raichu/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Raichu[] = INCBIN_U8("graphics/pokemon/raichu/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Raichu[] = INCBIN_COMP("graphics/pokemon/raichu/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Raichu[] = INCBIN_U16("graphics/pokemon/raichu/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Raichu[] = INCBIN_U16("graphics/pokemon/raichu/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Raichu[] = INCBIN_U16("graphics/pokemon/raichu/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_RaichuF[] = INCBIN_U32("graphics/pokemon/raichu/anim_frontf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RaichuF[] = INCBIN_COMP("graphics/pokemon/raichu/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_RaichuAlola[] = INCBIN_U32("graphics/pokemon/raichu/alola/front.4bpp.smol");
    const u16 gMonPalette_RaichuAlola[] = INCBIN_U16("graphics/pokemon/raichu/alola/normal.gbapal");
    const u32 gMonBackPic_RaichuAlola[] = INCBIN_U32("graphics/pokemon/raichu/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_RaichuAlola[] = INCBIN_U16("graphics/pokemon/raichu/alola/shiny.gbapal");
    const u8 gMonIcon_RaichuAlola[] = INCBIN_U8("graphics/pokemon/raichu/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RaichuAlola[] = INCBIN_COMP("graphics/pokemon/raichu/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_RaichuAlola[] = INCBIN_U16("graphics/pokemon/raichu/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_RaichuAlola[] = INCBIN_U16("graphics/pokemon/raichu/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS

#if P_GEN_9_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_RaichuMegaX[] = INCBIN_U32("graphics/pokemon/raichu/mega_x/front.4bpp.smol");
    const u16 gMonPalette_RaichuMegaX[] = INCBIN_U16("graphics/pokemon/raichu/mega_x/normal.gbapal");
    const u32 gMonBackPic_RaichuMegaX[] = INCBIN_U32("graphics/pokemon/raichu/mega_x/back.4bpp.smol");
    const u16 gMonShinyPalette_RaichuMegaX[] = INCBIN_U16("graphics/pokemon/raichu/mega_x/shiny.gbapal");
    const u8 gMonIcon_RaichuMegaX[] = INCBIN_U8("graphics/pokemon/raichu/mega_x/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
//    const u32 gObjectEventPic_RaichuMegaX[] = INCBIN_COMP("graphics/pokemon/raichu/mega_x/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
//    const u16 gOverworldPalette_RaichuMegaX[] = INCBIN_U16("graphics/pokemon/raichu/mega_x/overworld_normal.gbapal");
//    const u16 gShinyOverworldPalette_RaichuMegaX[] = INCBIN_U16("graphics/pokemon/raichu/mega_x/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS

    const u32 gMonFrontPic_RaichuMegaY[] = INCBIN_U32("graphics/pokemon/raichu/mega_y/front.4bpp.smol");
    const u16 gMonPalette_RaichuMegaY[] = INCBIN_U16("graphics/pokemon/raichu/mega_y/normal.gbapal");
    const u32 gMonBackPic_RaichuMegaY[] = INCBIN_U32("graphics/pokemon/raichu/mega_y/back.4bpp.smol");
    const u16 gMonShinyPalette_RaichuMegaY[] = INCBIN_U16("graphics/pokemon/raichu/mega_y/shiny.gbapal");
    const u8 gMonIcon_RaichuMegaY[] = INCBIN_U8("graphics/pokemon/raichu/mega_y/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
//    const u32 gObjectEventPic_RaichuMegaY[] = INCBIN_COMP("graphics/pokemon/raichu/mega_y/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
//    const u16 gOverworldPalette_RaichuMegaY[] = INCBIN_U16("graphics/pokemon/raichu/mega_y/overworld_normal.gbapal");
//    const u16 gShinyOverworldPalette_RaichuMegaY[] = INCBIN_U16("graphics/pokemon/raichu/mega_y/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_GEN_9_MEGA_EVOLUTIONS
#endif //P_FAMILY_PIKACHU

#if P_FAMILY_SANDSHREW
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Sandshrew[] = INCBIN_U32("graphics/pokemon/sandshrew/anim_front.4bpp.smol");
    const u16 gMonPalette_Sandshrew[] = INCBIN_U16("graphics/pokemon/sandshrew/normal.gbapal");
    const u32 gMonBackPic_Sandshrew[] = INCBIN_U32("graphics/pokemon/sandshrew/back.4bpp.smol");
    const u16 gMonShinyPalette_Sandshrew[] = INCBIN_U16("graphics/pokemon/sandshrew/shiny.gbapal");
#else
    const u32 gMonFrontPic_Sandshrew[] = INCBIN_U32("graphics/pokemon/sandshrew/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Sandshrew[] = INCBIN_U16("graphics/pokemon/sandshrew/normal_gba.gbapal");
    const u32 gMonBackPic_Sandshrew[] = INCBIN_U32("graphics/pokemon/sandshrew/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Sandshrew[] = INCBIN_U16("graphics/pokemon/sandshrew/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Sandshrew[] = INCBIN_U8("graphics/pokemon/sandshrew/icon.4bpp");
#else
    const u8 gMonIcon_Sandshrew[] = INCBIN_U8("graphics/pokemon/sandshrew/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Sandshrew[] = INCBIN_U8("graphics/pokemon/sandshrew/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Sandshrew[] = INCBIN_COMP("graphics/pokemon/sandshrew/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Sandshrew[] = INCBIN_U16("graphics/pokemon/sandshrew/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Sandshrew[] = INCBIN_U16("graphics/pokemon/sandshrew/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Sandslash[] = INCBIN_U32("graphics/pokemon/sandslash/anim_front.4bpp.smol");
    const u16 gMonPalette_Sandslash[] = INCBIN_U16("graphics/pokemon/sandslash/normal.gbapal");
    const u32 gMonBackPic_Sandslash[] = INCBIN_U32("graphics/pokemon/sandslash/back.4bpp.smol");
    const u16 gMonShinyPalette_Sandslash[] = INCBIN_U16("graphics/pokemon/sandslash/shiny.gbapal");
#else
    const u32 gMonFrontPic_Sandslash[] = INCBIN_U32("graphics/pokemon/sandslash/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Sandslash[] = INCBIN_U16("graphics/pokemon/sandslash/normal_gba.gbapal");
    const u32 gMonBackPic_Sandslash[] = INCBIN_U32("graphics/pokemon/sandslash/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Sandslash[] = INCBIN_U16("graphics/pokemon/sandslash/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Sandslash[] = INCBIN_U8("graphics/pokemon/sandslash/icon.4bpp");
#else
    const u8 gMonIcon_Sandslash[] = INCBIN_U8("graphics/pokemon/sandslash/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Sandslash[] = INCBIN_U8("graphics/pokemon/sandslash/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Sandslash[] = INCBIN_COMP("graphics/pokemon/sandslash/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Sandslash[] = INCBIN_U16("graphics/pokemon/sandslash/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Sandslash[] = INCBIN_U16("graphics/pokemon/sandslash/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_SandshrewAlola[] = INCBIN_U32("graphics/pokemon/sandshrew/alola/front.4bpp.smol");
    const u16 gMonPalette_SandshrewAlola[] = INCBIN_U16("graphics/pokemon/sandshrew/alola/normal.gbapal");
    const u32 gMonBackPic_SandshrewAlola[] = INCBIN_U32("graphics/pokemon/sandshrew/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_SandshrewAlola[] = INCBIN_U16("graphics/pokemon/sandshrew/alola/shiny.gbapal");
    const u8 gMonIcon_SandshrewAlola[] = INCBIN_U8("graphics/pokemon/sandshrew/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_SandshrewAlola[] = INCBIN_COMP("graphics/pokemon/sandshrew/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_SandshrewAlola[] = INCBIN_U16("graphics/pokemon/sandshrew/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_SandshrewAlola[] = INCBIN_U16("graphics/pokemon/sandshrew/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_SandslashAlola[] = INCBIN_U32("graphics/pokemon/sandslash/alola/front.4bpp.smol");
    const u16 gMonPalette_SandslashAlola[] = INCBIN_U16("graphics/pokemon/sandslash/alola/normal.gbapal");
    const u32 gMonBackPic_SandslashAlola[] = INCBIN_U32("graphics/pokemon/sandslash/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_SandslashAlola[] = INCBIN_U16("graphics/pokemon/sandslash/alola/shiny.gbapal");
    const u8 gMonIcon_SandslashAlola[] = INCBIN_U8("graphics/pokemon/sandslash/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_SandslashAlola[] = INCBIN_COMP("graphics/pokemon/sandslash/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_SandslashAlola[] = INCBIN_U16("graphics/pokemon/sandslash/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_SandslashAlola[] = INCBIN_U16("graphics/pokemon/sandslash/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_SANDSHREW

#if P_FAMILY_NIDORAN
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_NidoranF[] = INCBIN_U32("graphics/pokemon/nidoran_f/anim_front.4bpp.smol");
    const u16 gMonPalette_NidoranF[] = INCBIN_U16("graphics/pokemon/nidoran_f/normal.gbapal");
    const u32 gMonBackPic_NidoranF[] = INCBIN_U32("graphics/pokemon/nidoran_f/back.4bpp.smol");
    const u16 gMonShinyPalette_NidoranF[] = INCBIN_U16("graphics/pokemon/nidoran_f/shiny.gbapal");
#else
    const u32 gMonFrontPic_NidoranF[] = INCBIN_U32("graphics/pokemon/nidoran_f/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_NidoranF[] = INCBIN_U16("graphics/pokemon/nidoran_f/normal_gba.gbapal");
    const u32 gMonBackPic_NidoranF[] = INCBIN_U32("graphics/pokemon/nidoran_f/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_NidoranF[] = INCBIN_U16("graphics/pokemon/nidoran_f/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_NidoranF[] = INCBIN_U8("graphics/pokemon/nidoran_f/icon.4bpp");
#else
    const u8 gMonIcon_NidoranF[] = INCBIN_U8("graphics/pokemon/nidoran_f/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_NidoranF[] = INCBIN_U8("graphics/pokemon/nidoran_f/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_NidoranF[] = INCBIN_COMP("graphics/pokemon/nidoran_f/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_NidoranF[] = INCBIN_U16("graphics/pokemon/nidoran_f/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_NidoranF[] = INCBIN_U16("graphics/pokemon/nidoran_f/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Nidorina[] = INCBIN_U32("graphics/pokemon/nidorina/anim_front.4bpp.smol");
    const u16 gMonPalette_Nidorina[] = INCBIN_U16("graphics/pokemon/nidorina/normal.gbapal");
    const u32 gMonBackPic_Nidorina[] = INCBIN_U32("graphics/pokemon/nidorina/back.4bpp.smol");
    const u16 gMonShinyPalette_Nidorina[] = INCBIN_U16("graphics/pokemon/nidorina/shiny.gbapal");
#else
    const u32 gMonFrontPic_Nidorina[] = INCBIN_U32("graphics/pokemon/nidorina/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Nidorina[] = INCBIN_U16("graphics/pokemon/nidorina/normal_gba.gbapal");
    const u32 gMonBackPic_Nidorina[] = INCBIN_U32("graphics/pokemon/nidorina/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Nidorina[] = INCBIN_U16("graphics/pokemon/nidorina/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Nidorina[] = INCBIN_U8("graphics/pokemon/nidorina/icon.4bpp");
#else
    const u8 gMonIcon_Nidorina[] = INCBIN_U8("graphics/pokemon/nidorina/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Nidorina[] = INCBIN_U8("graphics/pokemon/nidorina/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Nidorina[] = INCBIN_COMP("graphics/pokemon/nidorina/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Nidorina[] = INCBIN_U16("graphics/pokemon/nidorina/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Nidorina[] = INCBIN_U16("graphics/pokemon/nidorina/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Nidoqueen[] = INCBIN_U32("graphics/pokemon/nidoqueen/anim_front.4bpp.smol");
    const u16 gMonPalette_Nidoqueen[] = INCBIN_U16("graphics/pokemon/nidoqueen/normal.gbapal");
    const u32 gMonBackPic_Nidoqueen[] = INCBIN_U32("graphics/pokemon/nidoqueen/back.4bpp.smol");
    const u16 gMonShinyPalette_Nidoqueen[] = INCBIN_U16("graphics/pokemon/nidoqueen/shiny.gbapal");
#else
    const u32 gMonFrontPic_Nidoqueen[] = INCBIN_U32("graphics/pokemon/nidoqueen/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Nidoqueen[] = INCBIN_U16("graphics/pokemon/nidoqueen/normal_gba.gbapal");
    const u32 gMonBackPic_Nidoqueen[] = INCBIN_U32("graphics/pokemon/nidoqueen/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Nidoqueen[] = INCBIN_U16("graphics/pokemon/nidoqueen/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Nidoqueen[] = INCBIN_U8("graphics/pokemon/nidoqueen/icon.4bpp");
#else
    const u8 gMonIcon_Nidoqueen[] = INCBIN_U8("graphics/pokemon/nidoqueen/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Nidoqueen[] = INCBIN_U8("graphics/pokemon/nidoqueen/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Nidoqueen[] = INCBIN_COMP("graphics/pokemon/nidoqueen/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Nidoqueen[] = INCBIN_U16("graphics/pokemon/nidoqueen/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Nidoqueen[] = INCBIN_U16("graphics/pokemon/nidoqueen/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_NidoranM[] = INCBIN_U32("graphics/pokemon/nidoran_m/anim_front.4bpp.smol");
    const u16 gMonPalette_NidoranM[] = INCBIN_U16("graphics/pokemon/nidoran_m/normal.gbapal");
    const u32 gMonBackPic_NidoranM[] = INCBIN_U32("graphics/pokemon/nidoran_m/back.4bpp.smol");
    const u16 gMonShinyPalette_NidoranM[] = INCBIN_U16("graphics/pokemon/nidoran_m/shiny.gbapal");
#else
    const u32 gMonFrontPic_NidoranM[] = INCBIN_U32("graphics/pokemon/nidoran_m/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_NidoranM[] = INCBIN_U16("graphics/pokemon/nidoran_m/normal_gba.gbapal");
    const u32 gMonBackPic_NidoranM[] = INCBIN_U32("graphics/pokemon/nidoran_m/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_NidoranM[] = INCBIN_U16("graphics/pokemon/nidoran_m/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_NidoranM[] = INCBIN_U8("graphics/pokemon/nidoran_m/icon.4bpp");
#else
    const u8 gMonIcon_NidoranM[] = INCBIN_U8("graphics/pokemon/nidoran_m/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_NidoranM[] = INCBIN_U8("graphics/pokemon/nidoran_m/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_NidoranM[] = INCBIN_COMP("graphics/pokemon/nidoran_m/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_NidoranM[] = INCBIN_U16("graphics/pokemon/nidoran_m/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_NidoranM[] = INCBIN_U16("graphics/pokemon/nidoran_m/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Nidorino[] = INCBIN_U32("graphics/pokemon/nidorino/anim_front.4bpp.smol");
    const u16 gMonPalette_Nidorino[] = INCBIN_U16("graphics/pokemon/nidorino/normal.gbapal");
    const u32 gMonBackPic_Nidorino[] = INCBIN_U32("graphics/pokemon/nidorino/back.4bpp.smol");
    const u16 gMonShinyPalette_Nidorino[] = INCBIN_U16("graphics/pokemon/nidorino/shiny.gbapal");
#else
    const u32 gMonFrontPic_Nidorino[] = INCBIN_U32("graphics/pokemon/nidorino/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Nidorino[] = INCBIN_U16("graphics/pokemon/nidorino/normal_gba.gbapal");
    const u32 gMonBackPic_Nidorino[] = INCBIN_U32("graphics/pokemon/nidorino/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Nidorino[] = INCBIN_U16("graphics/pokemon/nidorino/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Nidorino[] = INCBIN_U8("graphics/pokemon/nidorino/icon.4bpp");
#else
    const u8 gMonIcon_Nidorino[] = INCBIN_U8("graphics/pokemon/nidorino/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Nidorino[] = INCBIN_U8("graphics/pokemon/nidorino/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Nidorino[] = INCBIN_COMP("graphics/pokemon/nidorino/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Nidorino[] = INCBIN_U16("graphics/pokemon/nidorino/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Nidorino[] = INCBIN_U16("graphics/pokemon/nidorino/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Nidoking[] = INCBIN_U32("graphics/pokemon/nidoking/anim_front.4bpp.smol");
    const u16 gMonPalette_Nidoking[] = INCBIN_U16("graphics/pokemon/nidoking/normal.gbapal");
    const u32 gMonBackPic_Nidoking[] = INCBIN_U32("graphics/pokemon/nidoking/back.4bpp.smol");
    const u16 gMonShinyPalette_Nidoking[] = INCBIN_U16("graphics/pokemon/nidoking/shiny.gbapal");
#else
    const u32 gMonFrontPic_Nidoking[] = INCBIN_U32("graphics/pokemon/nidoking/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Nidoking[] = INCBIN_U16("graphics/pokemon/nidoking/normal_gba.gbapal");
    const u32 gMonBackPic_Nidoking[] = INCBIN_U32("graphics/pokemon/nidoking/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Nidoking[] = INCBIN_U16("graphics/pokemon/nidoking/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Nidoking[] = INCBIN_U8("graphics/pokemon/nidoking/icon.4bpp");
#else
    const u8 gMonIcon_Nidoking[] = INCBIN_U8("graphics/pokemon/nidoking/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Nidoking[] = INCBIN_U8("graphics/pokemon/nidoking/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Nidoking[] = INCBIN_COMP("graphics/pokemon/nidoking/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Nidoking[] = INCBIN_U16("graphics/pokemon/nidoking/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Nidoking[] = INCBIN_U16("graphics/pokemon/nidoking/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_NIDORAN

#if P_FAMILY_CLEFAIRY
#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Cleffa[] = INCBIN_U32("graphics/pokemon/cleffa/anim_front.4bpp.smol");
    const u16 gMonPalette_Cleffa[] = INCBIN_U16("graphics/pokemon/cleffa/normal.gbapal");
    const u32 gMonBackPic_Cleffa[] = INCBIN_U32("graphics/pokemon/cleffa/back.4bpp.smol");
    const u16 gMonShinyPalette_Cleffa[] = INCBIN_U16("graphics/pokemon/cleffa/shiny.gbapal");
#else
    const u32 gMonFrontPic_Cleffa[] = INCBIN_U32("graphics/pokemon/cleffa/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Cleffa[] = INCBIN_U16("graphics/pokemon/cleffa/normal_gba.gbapal");
    const u32 gMonBackPic_Cleffa[] = INCBIN_U32("graphics/pokemon/cleffa/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Cleffa[] = INCBIN_U16("graphics/pokemon/cleffa/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Cleffa[] = INCBIN_U8("graphics/pokemon/cleffa/icon.4bpp");
#else
    const u8 gMonIcon_Cleffa[] = INCBIN_U8("graphics/pokemon/cleffa/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Cleffa[] = INCBIN_U8("graphics/pokemon/cleffa/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Cleffa[] = INCBIN_COMP("graphics/pokemon/cleffa/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Cleffa[] = INCBIN_U16("graphics/pokemon/cleffa/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Cleffa[] = INCBIN_U16("graphics/pokemon/cleffa/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Clefairy[] = INCBIN_U32("graphics/pokemon/clefairy/anim_front.4bpp.smol");
    const u16 gMonPalette_Clefairy[] = INCBIN_U16("graphics/pokemon/clefairy/normal.gbapal");
    const u32 gMonBackPic_Clefairy[] = INCBIN_U32("graphics/pokemon/clefairy/back.4bpp.smol");
    const u16 gMonShinyPalette_Clefairy[] = INCBIN_U16("graphics/pokemon/clefairy/shiny.gbapal");
#else
    const u32 gMonFrontPic_Clefairy[] = INCBIN_U32("graphics/pokemon/clefairy/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Clefairy[] = INCBIN_U16("graphics/pokemon/clefairy/normal_gba.gbapal");
    const u32 gMonBackPic_Clefairy[] = INCBIN_U32("graphics/pokemon/clefairy/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Clefairy[] = INCBIN_U16("graphics/pokemon/clefairy/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Clefairy[] = INCBIN_U8("graphics/pokemon/clefairy/icon.4bpp");
#else
    const u8 gMonIcon_Clefairy[] = INCBIN_U8("graphics/pokemon/clefairy/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Clefairy[] = INCBIN_U8("graphics/pokemon/clefairy/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Clefairy[] = INCBIN_COMP("graphics/pokemon/clefairy/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Clefairy[] = INCBIN_U16("graphics/pokemon/clefairy/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Clefairy[] = INCBIN_U16("graphics/pokemon/clefairy/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Clefable[] = INCBIN_U32("graphics/pokemon/clefable/anim_front.4bpp.smol");
    const u16 gMonPalette_Clefable[] = INCBIN_U16("graphics/pokemon/clefable/normal.gbapal");
    const u32 gMonBackPic_Clefable[] = INCBIN_U32("graphics/pokemon/clefable/back.4bpp.smol");
    const u16 gMonShinyPalette_Clefable[] = INCBIN_U16("graphics/pokemon/clefable/shiny.gbapal");
#else
    const u32 gMonFrontPic_Clefable[] = INCBIN_U32("graphics/pokemon/clefable/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Clefable[] = INCBIN_U16("graphics/pokemon/clefable/normal_gba.gbapal");
    const u32 gMonBackPic_Clefable[] = INCBIN_U32("graphics/pokemon/clefable/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Clefable[] = INCBIN_U16("graphics/pokemon/clefable/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Clefable[] = INCBIN_U8("graphics/pokemon/clefable/icon.4bpp");
#else
    const u8 gMonIcon_Clefable[] = INCBIN_U8("graphics/pokemon/clefable/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Clefable[] = INCBIN_U8("graphics/pokemon/clefable/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Clefable[] = INCBIN_COMP("graphics/pokemon/clefable/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Clefable[] = INCBIN_U16("graphics/pokemon/clefable/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Clefable[] = INCBIN_U16("graphics/pokemon/clefable/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_9_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_ClefableMega[] = INCBIN_U32("graphics/pokemon/clefable/mega/front.4bpp.smol");
    const u16 gMonPalette_ClefableMega[] = INCBIN_U16("graphics/pokemon/clefable/mega/normal.gbapal");
    const u32 gMonBackPic_ClefableMega[] = INCBIN_U32("graphics/pokemon/clefable/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_ClefableMega[] = INCBIN_U16("graphics/pokemon/clefable/mega/shiny.gbapal");
    const u8 gMonIcon_ClefableMega[] = INCBIN_U8("graphics/pokemon/clefable/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
//    const u32 gObjectEventPic_ClefableMega[] = INCBIN_COMP("graphics/pokemon/clefable/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
//    const u16 gOverworldPalette_ClefableMega[] = INCBIN_U16("graphics/pokemon/clefable/mega/overworld_normal.gbapal");
//    const u16 gShinyOverworldPalette_ClefableMega[] = INCBIN_U16("graphics/pokemon/clefable/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_GEN_9_MEGA_EVOLUTIONS
#endif //P_FAMILY_CLEFAIRY

#if P_FAMILY_VULPIX
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Vulpix[] = INCBIN_U32("graphics/pokemon/vulpix/anim_front.4bpp.smol");
    const u16 gMonPalette_Vulpix[] = INCBIN_U16("graphics/pokemon/vulpix/normal.gbapal");
    const u32 gMonBackPic_Vulpix[] = INCBIN_U32("graphics/pokemon/vulpix/back.4bpp.smol");
    const u16 gMonShinyPalette_Vulpix[] = INCBIN_U16("graphics/pokemon/vulpix/shiny.gbapal");
#else
    const u32 gMonFrontPic_Vulpix[] = INCBIN_U32("graphics/pokemon/vulpix/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Vulpix[] = INCBIN_U16("graphics/pokemon/vulpix/normal_gba.gbapal");
    const u32 gMonBackPic_Vulpix[] = INCBIN_U32("graphics/pokemon/vulpix/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Vulpix[] = INCBIN_U16("graphics/pokemon/vulpix/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Vulpix[] = INCBIN_U8("graphics/pokemon/vulpix/icon.4bpp");
#else
    const u8 gMonIcon_Vulpix[] = INCBIN_U8("graphics/pokemon/vulpix/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Vulpix[] = INCBIN_U8("graphics/pokemon/vulpix/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Vulpix[] = INCBIN_COMP("graphics/pokemon/vulpix/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Vulpix[] = INCBIN_U16("graphics/pokemon/vulpix/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Vulpix[] = INCBIN_U16("graphics/pokemon/vulpix/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Ninetales[] = INCBIN_U32("graphics/pokemon/ninetales/anim_front.4bpp.smol");
    const u16 gMonPalette_Ninetales[] = INCBIN_U16("graphics/pokemon/ninetales/normal.gbapal");
    const u32 gMonBackPic_Ninetales[] = INCBIN_U32("graphics/pokemon/ninetales/back.4bpp.smol");
    const u16 gMonShinyPalette_Ninetales[] = INCBIN_U16("graphics/pokemon/ninetales/shiny.gbapal");
#else
    const u32 gMonFrontPic_Ninetales[] = INCBIN_U32("graphics/pokemon/ninetales/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Ninetales[] = INCBIN_U16("graphics/pokemon/ninetales/normal_gba.gbapal");
    const u32 gMonBackPic_Ninetales[] = INCBIN_U32("graphics/pokemon/ninetales/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Ninetales[] = INCBIN_U16("graphics/pokemon/ninetales/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Ninetales[] = INCBIN_U8("graphics/pokemon/ninetales/icon.4bpp");
#else
    const u8 gMonIcon_Ninetales[] = INCBIN_U8("graphics/pokemon/ninetales/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Ninetales[] = INCBIN_U8("graphics/pokemon/ninetales/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Ninetales[] = INCBIN_COMP("graphics/pokemon/ninetales/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Ninetales[] = INCBIN_U16("graphics/pokemon/ninetales/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Ninetales[] = INCBIN_U16("graphics/pokemon/ninetales/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_VulpixAlola[] = INCBIN_U32("graphics/pokemon/vulpix/alola/front.4bpp.smol");
    const u16 gMonPalette_VulpixAlola[] = INCBIN_U16("graphics/pokemon/vulpix/alola/normal.gbapal");
    const u32 gMonBackPic_VulpixAlola[] = INCBIN_U32("graphics/pokemon/vulpix/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_VulpixAlola[] = INCBIN_U16("graphics/pokemon/vulpix/alola/shiny.gbapal");
    const u8 gMonIcon_VulpixAlola[] = INCBIN_U8("graphics/pokemon/vulpix/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_VulpixAlola[] = INCBIN_COMP("graphics/pokemon/vulpix/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_VulpixAlola[] = INCBIN_U16("graphics/pokemon/vulpix/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_VulpixAlola[] = INCBIN_U16("graphics/pokemon/vulpix/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_NinetalesAlola[] = INCBIN_U32("graphics/pokemon/ninetales/alola/front.4bpp.smol");
    const u16 gMonPalette_NinetalesAlola[] = INCBIN_U16("graphics/pokemon/ninetales/alola/normal.gbapal");
    const u32 gMonBackPic_NinetalesAlola[] = INCBIN_U32("graphics/pokemon/ninetales/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_NinetalesAlola[] = INCBIN_U16("graphics/pokemon/ninetales/alola/shiny.gbapal");
    const u8 gMonIcon_NinetalesAlola[] = INCBIN_U8("graphics/pokemon/ninetales/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_NinetalesAlola[] = INCBIN_COMP("graphics/pokemon/ninetales/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_NinetalesAlola[] = INCBIN_U16("graphics/pokemon/ninetales/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_NinetalesAlola[] = INCBIN_U16("graphics/pokemon/ninetales/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_VULPIX

#if P_FAMILY_JIGGLYPUFF
#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Igglybuff[] = INCBIN_U32("graphics/pokemon/igglybuff/anim_front.4bpp.smol");
    const u16 gMonPalette_Igglybuff[] = INCBIN_U16("graphics/pokemon/igglybuff/normal.gbapal");
    const u32 gMonBackPic_Igglybuff[] = INCBIN_U32("graphics/pokemon/igglybuff/back.4bpp.smol");
    const u16 gMonShinyPalette_Igglybuff[] = INCBIN_U16("graphics/pokemon/igglybuff/shiny.gbapal");
#else
    const u32 gMonFrontPic_Igglybuff[] = INCBIN_U32("graphics/pokemon/igglybuff/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Igglybuff[] = INCBIN_U16("graphics/pokemon/igglybuff/normal_gba.gbapal");
    const u32 gMonBackPic_Igglybuff[] = INCBIN_U32("graphics/pokemon/igglybuff/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Igglybuff[] = INCBIN_U16("graphics/pokemon/igglybuff/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Igglybuff[] = INCBIN_U8("graphics/pokemon/igglybuff/icon.4bpp");
#else
    const u8 gMonIcon_Igglybuff[] = INCBIN_U8("graphics/pokemon/igglybuff/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Igglybuff[] = INCBIN_U8("graphics/pokemon/igglybuff/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Igglybuff[] = INCBIN_COMP("graphics/pokemon/igglybuff/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Igglybuff[] = INCBIN_U16("graphics/pokemon/igglybuff/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Igglybuff[] = INCBIN_U16("graphics/pokemon/igglybuff/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Jigglypuff[] = INCBIN_U32("graphics/pokemon/jigglypuff/anim_front.4bpp.smol");
    const u16 gMonPalette_Jigglypuff[] = INCBIN_U16("graphics/pokemon/jigglypuff/normal.gbapal");
    const u32 gMonBackPic_Jigglypuff[] = INCBIN_U32("graphics/pokemon/jigglypuff/back.4bpp.smol");
    const u16 gMonShinyPalette_Jigglypuff[] = INCBIN_U16("graphics/pokemon/jigglypuff/shiny.gbapal");
#else
    const u32 gMonFrontPic_Jigglypuff[] = INCBIN_U32("graphics/pokemon/jigglypuff/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Jigglypuff[] = INCBIN_U16("graphics/pokemon/jigglypuff/normal_gba.gbapal");
    const u32 gMonBackPic_Jigglypuff[] = INCBIN_U32("graphics/pokemon/jigglypuff/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Jigglypuff[] = INCBIN_U16("graphics/pokemon/jigglypuff/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Jigglypuff[] = INCBIN_U8("graphics/pokemon/jigglypuff/icon.4bpp");
#else
    const u8 gMonIcon_Jigglypuff[] = INCBIN_U8("graphics/pokemon/jigglypuff/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Jigglypuff[] = INCBIN_U8("graphics/pokemon/jigglypuff/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Jigglypuff[] = INCBIN_COMP("graphics/pokemon/jigglypuff/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Jigglypuff[] = INCBIN_U16("graphics/pokemon/jigglypuff/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Jigglypuff[] = INCBIN_U16("graphics/pokemon/jigglypuff/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Wigglytuff[] = INCBIN_U32("graphics/pokemon/wigglytuff/anim_front.4bpp.smol");
    const u16 gMonPalette_Wigglytuff[] = INCBIN_U16("graphics/pokemon/wigglytuff/normal.gbapal");
    const u32 gMonBackPic_Wigglytuff[] = INCBIN_U32("graphics/pokemon/wigglytuff/back.4bpp.smol");
    const u16 gMonShinyPalette_Wigglytuff[] = INCBIN_U16("graphics/pokemon/wigglytuff/shiny.gbapal");
#else
    const u32 gMonFrontPic_Wigglytuff[] = INCBIN_U32("graphics/pokemon/wigglytuff/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Wigglytuff[] = INCBIN_U16("graphics/pokemon/wigglytuff/normal_gba.gbapal");
    const u32 gMonBackPic_Wigglytuff[] = INCBIN_U32("graphics/pokemon/wigglytuff/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Wigglytuff[] = INCBIN_U16("graphics/pokemon/wigglytuff/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Wigglytuff[] = INCBIN_U8("graphics/pokemon/wigglytuff/icon.4bpp");
#else
    const u8 gMonIcon_Wigglytuff[] = INCBIN_U8("graphics/pokemon/wigglytuff/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Wigglytuff[] = INCBIN_U8("graphics/pokemon/wigglytuff/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Wigglytuff[] = INCBIN_COMP("graphics/pokemon/wigglytuff/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Wigglytuff[] = INCBIN_U16("graphics/pokemon/wigglytuff/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Wigglytuff[] = INCBIN_U16("graphics/pokemon/wigglytuff/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_JIGGLYPUFF

#if P_FAMILY_ZUBAT
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Zubat[] = INCBIN_U32("graphics/pokemon/zubat/anim_front.4bpp.smol");
    const u16 gMonPalette_Zubat[] = INCBIN_U16("graphics/pokemon/zubat/normal.gbapal");
    const u32 gMonBackPic_Zubat[] = INCBIN_U32("graphics/pokemon/zubat/back.4bpp.smol");
    const u16 gMonShinyPalette_Zubat[] = INCBIN_U16("graphics/pokemon/zubat/shiny.gbapal");
#else
    const u32 gMonFrontPic_Zubat[] = INCBIN_U32("graphics/pokemon/zubat/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Zubat[] = INCBIN_U16("graphics/pokemon/zubat/normal_gba.gbapal");
    const u32 gMonBackPic_Zubat[] = INCBIN_U32("graphics/pokemon/zubat/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Zubat[] = INCBIN_U16("graphics/pokemon/zubat/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Zubat[] = INCBIN_U8("graphics/pokemon/zubat/icon.4bpp");
#else
    const u8 gMonIcon_Zubat[] = INCBIN_U8("graphics/pokemon/zubat/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Zubat[] = INCBIN_U8("graphics/pokemon/zubat/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Zubat[] = INCBIN_COMP("graphics/pokemon/zubat/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Zubat[] = INCBIN_U16("graphics/pokemon/zubat/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Zubat[] = INCBIN_U16("graphics/pokemon/zubat/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_ZubatF[] = INCBIN_U32("graphics/pokemon/zubat/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_ZubatF[] = INCBIN_U32("graphics/pokemon/zubat/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_ZubatF[] = INCBIN_COMP("graphics/pokemon/zubat/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Golbat[] = INCBIN_U32("graphics/pokemon/golbat/anim_front.4bpp.smol");
    const u16 gMonPalette_Golbat[] = INCBIN_U16("graphics/pokemon/golbat/normal.gbapal");
    const u32 gMonBackPic_Golbat[] = INCBIN_U32("graphics/pokemon/golbat/back.4bpp.smol");
    const u16 gMonShinyPalette_Golbat[] = INCBIN_U16("graphics/pokemon/golbat/shiny.gbapal");
#else
    const u32 gMonFrontPic_Golbat[] = INCBIN_U32("graphics/pokemon/golbat/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Golbat[] = INCBIN_U16("graphics/pokemon/golbat/normal_gba.gbapal");
    const u32 gMonBackPic_Golbat[] = INCBIN_U32("graphics/pokemon/golbat/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Golbat[] = INCBIN_U16("graphics/pokemon/golbat/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Golbat[] = INCBIN_U8("graphics/pokemon/golbat/icon.4bpp");
#else
    const u8 gMonIcon_Golbat[] = INCBIN_U8("graphics/pokemon/golbat/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Golbat[] = INCBIN_U8("graphics/pokemon/golbat/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Golbat[] = INCBIN_COMP("graphics/pokemon/golbat/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Golbat[] = INCBIN_U16("graphics/pokemon/golbat/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Golbat[] = INCBIN_U16("graphics/pokemon/golbat/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_GolbatF[] = INCBIN_U32("graphics/pokemon/golbat/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_GolbatF[] = INCBIN_U32("graphics/pokemon/golbat/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_GolbatF[] = INCBIN_COMP("graphics/pokemon/golbat/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Crobat[] = INCBIN_U32("graphics/pokemon/crobat/anim_front.4bpp.smol");
    const u16 gMonPalette_Crobat[] = INCBIN_U16("graphics/pokemon/crobat/normal.gbapal");
    const u32 gMonBackPic_Crobat[] = INCBIN_U32("graphics/pokemon/crobat/back.4bpp.smol");
    const u16 gMonShinyPalette_Crobat[] = INCBIN_U16("graphics/pokemon/crobat/shiny.gbapal");
#else
    const u32 gMonFrontPic_Crobat[] = INCBIN_U32("graphics/pokemon/crobat/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Crobat[] = INCBIN_U16("graphics/pokemon/crobat/normal_gba.gbapal");
    const u32 gMonBackPic_Crobat[] = INCBIN_U32("graphics/pokemon/crobat/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Crobat[] = INCBIN_U16("graphics/pokemon/crobat/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Crobat[] = INCBIN_U8("graphics/pokemon/crobat/icon.4bpp");
#else
    const u8 gMonIcon_Crobat[] = INCBIN_U8("graphics/pokemon/crobat/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Crobat[] = INCBIN_U8("graphics/pokemon/crobat/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Crobat[] = INCBIN_COMP("graphics/pokemon/crobat/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Crobat[] = INCBIN_U16("graphics/pokemon/crobat/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Crobat[] = INCBIN_U16("graphics/pokemon/crobat/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_ZUBAT

#if P_FAMILY_ODDISH
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Oddish[] = INCBIN_U32("graphics/pokemon/oddish/anim_front.4bpp.smol");
    const u16 gMonPalette_Oddish[] = INCBIN_U16("graphics/pokemon/oddish/normal.gbapal");
    const u32 gMonBackPic_Oddish[] = INCBIN_U32("graphics/pokemon/oddish/back.4bpp.smol");
    const u16 gMonShinyPalette_Oddish[] = INCBIN_U16("graphics/pokemon/oddish/shiny.gbapal");
#else
    const u32 gMonFrontPic_Oddish[] = INCBIN_U32("graphics/pokemon/oddish/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Oddish[] = INCBIN_U16("graphics/pokemon/oddish/normal_gba.gbapal");
    const u32 gMonBackPic_Oddish[] = INCBIN_U32("graphics/pokemon/oddish/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Oddish[] = INCBIN_U16("graphics/pokemon/oddish/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Oddish[] = INCBIN_U8("graphics/pokemon/oddish/icon.4bpp");
#else
    const u8 gMonIcon_Oddish[] = INCBIN_U8("graphics/pokemon/oddish/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Oddish[] = INCBIN_U8("graphics/pokemon/oddish/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Oddish[] = INCBIN_COMP("graphics/pokemon/oddish/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Oddish[] = INCBIN_U16("graphics/pokemon/oddish/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Oddish[] = INCBIN_U16("graphics/pokemon/oddish/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Gloom[] = INCBIN_U32("graphics/pokemon/gloom/anim_front.4bpp.smol");
    const u16 gMonPalette_Gloom[] = INCBIN_U16("graphics/pokemon/gloom/normal.gbapal");
    const u32 gMonBackPic_Gloom[] = INCBIN_U32("graphics/pokemon/gloom/back.4bpp.smol");
    const u16 gMonShinyPalette_Gloom[] = INCBIN_U16("graphics/pokemon/gloom/shiny.gbapal");
#else
    const u32 gMonFrontPic_Gloom[] = INCBIN_U32("graphics/pokemon/gloom/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Gloom[] = INCBIN_U16("graphics/pokemon/gloom/normal_gba.gbapal");
    const u32 gMonBackPic_Gloom[] = INCBIN_U32("graphics/pokemon/gloom/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Gloom[] = INCBIN_U16("graphics/pokemon/gloom/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Gloom[] = INCBIN_U8("graphics/pokemon/gloom/icon.4bpp");
#else
    const u8 gMonIcon_Gloom[] = INCBIN_U8("graphics/pokemon/gloom/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Gloom[] = INCBIN_U8("graphics/pokemon/gloom/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Gloom[] = INCBIN_COMP("graphics/pokemon/gloom/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Gloom[] = INCBIN_U16("graphics/pokemon/gloom/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Gloom[] = INCBIN_U16("graphics/pokemon/gloom/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_GloomF[] = INCBIN_U32("graphics/pokemon/gloom/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_GloomF[] = INCBIN_U32("graphics/pokemon/gloom/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_GloomF[] = INCBIN_COMP("graphics/pokemon/gloom/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Vileplume[] = INCBIN_U32("graphics/pokemon/vileplume/anim_front.4bpp.smol");
    const u16 gMonPalette_Vileplume[] = INCBIN_U16("graphics/pokemon/vileplume/normal.gbapal");
    const u32 gMonBackPic_Vileplume[] = INCBIN_U32("graphics/pokemon/vileplume/back.4bpp.smol");
    const u16 gMonShinyPalette_Vileplume[] = INCBIN_U16("graphics/pokemon/vileplume/shiny.gbapal");
#else
    const u32 gMonFrontPic_Vileplume[] = INCBIN_U32("graphics/pokemon/vileplume/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Vileplume[] = INCBIN_U16("graphics/pokemon/vileplume/normal_gba.gbapal");
    const u32 gMonBackPic_Vileplume[] = INCBIN_U32("graphics/pokemon/vileplume/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Vileplume[] = INCBIN_U16("graphics/pokemon/vileplume/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Vileplume[] = INCBIN_U8("graphics/pokemon/vileplume/icon.4bpp");
#else
    const u8 gMonIcon_Vileplume[] = INCBIN_U8("graphics/pokemon/vileplume/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Vileplume[] = INCBIN_U8("graphics/pokemon/vileplume/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Vileplume[] = INCBIN_COMP("graphics/pokemon/vileplume/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Vileplume[] = INCBIN_U16("graphics/pokemon/vileplume/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Vileplume[] = INCBIN_U16("graphics/pokemon/vileplume/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_VileplumeF[] = INCBIN_U32("graphics/pokemon/vileplume/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_VileplumeF[] = INCBIN_U32("graphics/pokemon/vileplume/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_VileplumeF[] = INCBIN_COMP("graphics/pokemon/vileplume/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Bellossom[] = INCBIN_U32("graphics/pokemon/bellossom/anim_front.4bpp.smol");
    const u16 gMonPalette_Bellossom[] = INCBIN_U16("graphics/pokemon/bellossom/normal.gbapal");
    const u32 gMonBackPic_Bellossom[] = INCBIN_U32("graphics/pokemon/bellossom/back.4bpp.smol");
    const u16 gMonShinyPalette_Bellossom[] = INCBIN_U16("graphics/pokemon/bellossom/shiny.gbapal");
#else
    const u32 gMonFrontPic_Bellossom[] = INCBIN_U32("graphics/pokemon/bellossom/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Bellossom[] = INCBIN_U16("graphics/pokemon/bellossom/normal_gba.gbapal");
    const u32 gMonBackPic_Bellossom[] = INCBIN_U32("graphics/pokemon/bellossom/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Bellossom[] = INCBIN_U16("graphics/pokemon/bellossom/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Bellossom[] = INCBIN_U8("graphics/pokemon/bellossom/icon.4bpp");
#else
    const u8 gMonIcon_Bellossom[] = INCBIN_U8("graphics/pokemon/bellossom/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Bellossom[] = INCBIN_U8("graphics/pokemon/bellossom/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Bellossom[] = INCBIN_COMP("graphics/pokemon/bellossom/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Bellossom[] = INCBIN_U16("graphics/pokemon/bellossom/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Bellossom[] = INCBIN_U16("graphics/pokemon/bellossom/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_ODDISH

#if P_FAMILY_PARAS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Paras[] = INCBIN_U32("graphics/pokemon/paras/anim_front.4bpp.smol");
    const u16 gMonPalette_Paras[] = INCBIN_U16("graphics/pokemon/paras/normal.gbapal");
    const u32 gMonBackPic_Paras[] = INCBIN_U32("graphics/pokemon/paras/back.4bpp.smol");
    const u16 gMonShinyPalette_Paras[] = INCBIN_U16("graphics/pokemon/paras/shiny.gbapal");
#else
    const u32 gMonFrontPic_Paras[] = INCBIN_U32("graphics/pokemon/paras/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Paras[] = INCBIN_U16("graphics/pokemon/paras/normal_gba.gbapal");
    const u32 gMonBackPic_Paras[] = INCBIN_U32("graphics/pokemon/paras/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Paras[] = INCBIN_U16("graphics/pokemon/paras/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Paras[] = INCBIN_U8("graphics/pokemon/paras/icon.4bpp");
#else
    const u8 gMonIcon_Paras[] = INCBIN_U8("graphics/pokemon/paras/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Paras[] = INCBIN_U8("graphics/pokemon/paras/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Paras[] = INCBIN_COMP("graphics/pokemon/paras/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Paras[] = INCBIN_U16("graphics/pokemon/paras/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Paras[] = INCBIN_U16("graphics/pokemon/paras/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Paras[] = INCBIN_U16("graphics/pokemon/paras/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Parasect[] = INCBIN_U32("graphics/pokemon/parasect/anim_front.4bpp.smol");
    const u16 gMonPalette_Parasect[] = INCBIN_U16("graphics/pokemon/parasect/normal.gbapal");
    const u32 gMonBackPic_Parasect[] = INCBIN_U32("graphics/pokemon/parasect/back.4bpp.smol");
    const u16 gMonShinyPalette_Parasect[] = INCBIN_U16("graphics/pokemon/parasect/shiny.gbapal");
#else
    const u32 gMonFrontPic_Parasect[] = INCBIN_U32("graphics/pokemon/parasect/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Parasect[] = INCBIN_U16("graphics/pokemon/parasect/normal_gba.gbapal");
    const u32 gMonBackPic_Parasect[] = INCBIN_U32("graphics/pokemon/parasect/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Parasect[] = INCBIN_U16("graphics/pokemon/parasect/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Parasect[] = INCBIN_U8("graphics/pokemon/parasect/icon.4bpp");
#else
    const u8 gMonIcon_Parasect[] = INCBIN_U8("graphics/pokemon/parasect/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Parasect[] = INCBIN_U8("graphics/pokemon/parasect/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Parasect[] = INCBIN_COMP("graphics/pokemon/parasect/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Parasect[] = INCBIN_U16("graphics/pokemon/parasect/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Parasect[] = INCBIN_U16("graphics/pokemon/parasect/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_PARAS

#if P_FAMILY_VENONAT
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Venonat[] = INCBIN_U32("graphics/pokemon/venonat/anim_front.4bpp.smol");
    const u16 gMonPalette_Venonat[] = INCBIN_U16("graphics/pokemon/venonat/normal.gbapal");
    const u32 gMonBackPic_Venonat[] = INCBIN_U32("graphics/pokemon/venonat/back.4bpp.smol");
    const u16 gMonShinyPalette_Venonat[] = INCBIN_U16("graphics/pokemon/venonat/shiny.gbapal");
#else
    const u32 gMonFrontPic_Venonat[] = INCBIN_U32("graphics/pokemon/venonat/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Venonat[] = INCBIN_U16("graphics/pokemon/venonat/normal_gba.gbapal");
    const u32 gMonBackPic_Venonat[] = INCBIN_U32("graphics/pokemon/venonat/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Venonat[] = INCBIN_U16("graphics/pokemon/venonat/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Venonat[] = INCBIN_U8("graphics/pokemon/venonat/icon.4bpp");
#else
    const u8 gMonIcon_Venonat[] = INCBIN_U8("graphics/pokemon/venonat/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Venonat[] = INCBIN_U8("graphics/pokemon/venonat/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Venonat[] = INCBIN_COMP("graphics/pokemon/venonat/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Venonat[] = INCBIN_U16("graphics/pokemon/venonat/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Venonat[] = INCBIN_U16("graphics/pokemon/venonat/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Venomoth[] = INCBIN_U32("graphics/pokemon/venomoth/anim_front.4bpp.smol");
    const u16 gMonPalette_Venomoth[] = INCBIN_U16("graphics/pokemon/venomoth/normal.gbapal");
    const u32 gMonBackPic_Venomoth[] = INCBIN_U32("graphics/pokemon/venomoth/back.4bpp.smol");
    const u16 gMonShinyPalette_Venomoth[] = INCBIN_U16("graphics/pokemon/venomoth/shiny.gbapal");
#else
    const u32 gMonFrontPic_Venomoth[] = INCBIN_U32("graphics/pokemon/venomoth/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Venomoth[] = INCBIN_U16("graphics/pokemon/venomoth/normal_gba.gbapal");
    const u32 gMonBackPic_Venomoth[] = INCBIN_U32("graphics/pokemon/venomoth/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Venomoth[] = INCBIN_U16("graphics/pokemon/venomoth/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Venomoth[] = INCBIN_U8("graphics/pokemon/venomoth/icon.4bpp");
#else
    const u8 gMonIcon_Venomoth[] = INCBIN_U8("graphics/pokemon/venomoth/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Venomoth[] = INCBIN_U8("graphics/pokemon/venomoth/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Venomoth[] = INCBIN_COMP("graphics/pokemon/venomoth/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Venomoth[] = INCBIN_U16("graphics/pokemon/venomoth/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Venomoth[] = INCBIN_U16("graphics/pokemon/venomoth/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_VENONAT

#if P_FAMILY_DIGLETT
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Diglett[] = INCBIN_U32("graphics/pokemon/diglett/anim_front.4bpp.smol");
    const u16 gMonPalette_Diglett[] = INCBIN_U16("graphics/pokemon/diglett/normal.gbapal");
    const u32 gMonBackPic_Diglett[] = INCBIN_U32("graphics/pokemon/diglett/back.4bpp.smol");
    const u16 gMonShinyPalette_Diglett[] = INCBIN_U16("graphics/pokemon/diglett/shiny.gbapal");
#else
    const u32 gMonFrontPic_Diglett[] = INCBIN_U32("graphics/pokemon/diglett/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Diglett[] = INCBIN_U16("graphics/pokemon/diglett/normal_gba.gbapal");
    const u32 gMonBackPic_Diglett[] = INCBIN_U32("graphics/pokemon/diglett/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Diglett[] = INCBIN_U16("graphics/pokemon/diglett/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Diglett[] = INCBIN_U8("graphics/pokemon/diglett/icon.4bpp");
#else
    const u8 gMonIcon_Diglett[] = INCBIN_U8("graphics/pokemon/diglett/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Diglett[] = INCBIN_U8("graphics/pokemon/diglett/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Diglett[] = INCBIN_COMP("graphics/pokemon/diglett/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Diglett[] = INCBIN_U16("graphics/pokemon/diglett/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Diglett[] = INCBIN_U16("graphics/pokemon/diglett/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Dugtrio[] = INCBIN_U32("graphics/pokemon/dugtrio/anim_front.4bpp.smol");
    const u16 gMonPalette_Dugtrio[] = INCBIN_U16("graphics/pokemon/dugtrio/normal.gbapal");
    const u32 gMonBackPic_Dugtrio[] = INCBIN_U32("graphics/pokemon/dugtrio/back.4bpp.smol");
    const u16 gMonShinyPalette_Dugtrio[] = INCBIN_U16("graphics/pokemon/dugtrio/shiny.gbapal");
#else
    const u32 gMonFrontPic_Dugtrio[] = INCBIN_U32("graphics/pokemon/dugtrio/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Dugtrio[] = INCBIN_U16("graphics/pokemon/dugtrio/normal_gba.gbapal");
    const u32 gMonBackPic_Dugtrio[] = INCBIN_U32("graphics/pokemon/dugtrio/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Dugtrio[] = INCBIN_U16("graphics/pokemon/dugtrio/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Dugtrio[] = INCBIN_U8("graphics/pokemon/dugtrio/icon.4bpp");
#else
    const u8 gMonIcon_Dugtrio[] = INCBIN_U8("graphics/pokemon/dugtrio/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Dugtrio[] = INCBIN_U8("graphics/pokemon/dugtrio/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Dugtrio[] = INCBIN_COMP("graphics/pokemon/dugtrio/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Dugtrio[] = INCBIN_U16("graphics/pokemon/dugtrio/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Dugtrio[] = INCBIN_U16("graphics/pokemon/dugtrio/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_DiglettAlola[] = INCBIN_U32("graphics/pokemon/diglett/alola/front.4bpp.smol");
    const u16 gMonPalette_DiglettAlola[] = INCBIN_U16("graphics/pokemon/diglett/alola/normal.gbapal");
    const u32 gMonBackPic_DiglettAlola[] = INCBIN_U32("graphics/pokemon/diglett/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_DiglettAlola[] = INCBIN_U16("graphics/pokemon/diglett/alola/shiny.gbapal");
    const u8 gMonIcon_DiglettAlola[] = INCBIN_U8("graphics/pokemon/diglett/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_DiglettAlola[] = INCBIN_COMP("graphics/pokemon/diglett/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_DiglettAlola[] = INCBIN_U16("graphics/pokemon/diglett/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_DiglettAlola[] = INCBIN_U16("graphics/pokemon/diglett/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_DugtrioAlola[] = INCBIN_U32("graphics/pokemon/dugtrio/alola/front.4bpp.smol");
    const u16 gMonPalette_DugtrioAlola[] = INCBIN_U16("graphics/pokemon/dugtrio/alola/normal.gbapal");
    const u32 gMonBackPic_DugtrioAlola[] = INCBIN_U32("graphics/pokemon/dugtrio/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_DugtrioAlola[] = INCBIN_U16("graphics/pokemon/dugtrio/alola/shiny.gbapal");
    const u8 gMonIcon_DugtrioAlola[] = INCBIN_U8("graphics/pokemon/dugtrio/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_DugtrioAlola[] = INCBIN_COMP("graphics/pokemon/dugtrio/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_DugtrioAlola[] = INCBIN_U16("graphics/pokemon/dugtrio/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_DugtrioAlola[] = INCBIN_U16("graphics/pokemon/dugtrio/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_DIGLETT

#if P_FAMILY_MEOWTH
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Meowth[] = INCBIN_U32("graphics/pokemon/meowth/anim_front.4bpp.smol");
    const u16 gMonPalette_Meowth[] = INCBIN_U16("graphics/pokemon/meowth/normal.gbapal");
    const u32 gMonBackPic_Meowth[] = INCBIN_U32("graphics/pokemon/meowth/back.4bpp.smol");
    const u16 gMonShinyPalette_Meowth[] = INCBIN_U16("graphics/pokemon/meowth/shiny.gbapal");
#else
    const u32 gMonFrontPic_Meowth[] = INCBIN_U32("graphics/pokemon/meowth/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Meowth[] = INCBIN_U16("graphics/pokemon/meowth/normal_gba.gbapal");
    const u32 gMonBackPic_Meowth[] = INCBIN_U32("graphics/pokemon/meowth/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Meowth[] = INCBIN_U16("graphics/pokemon/meowth/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Meowth[] = INCBIN_U8("graphics/pokemon/meowth/icon.4bpp");
#else
    const u8 gMonIcon_Meowth[] = INCBIN_U8("graphics/pokemon/meowth/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Meowth[] = INCBIN_U8("graphics/pokemon/meowth/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Meowth[] = INCBIN_COMP("graphics/pokemon/meowth/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Meowth[] = INCBIN_U16("graphics/pokemon/meowth/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Meowth[] = INCBIN_U16("graphics/pokemon/meowth/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Persian[] = INCBIN_U32("graphics/pokemon/persian/anim_front.4bpp.smol");
    const u16 gMonPalette_Persian[] = INCBIN_U16("graphics/pokemon/persian/normal.gbapal");
    const u32 gMonBackPic_Persian[] = INCBIN_U32("graphics/pokemon/persian/back.4bpp.smol");
    const u16 gMonShinyPalette_Persian[] = INCBIN_U16("graphics/pokemon/persian/shiny.gbapal");
#else
    const u32 gMonFrontPic_Persian[] = INCBIN_U32("graphics/pokemon/persian/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Persian[] = INCBIN_U16("graphics/pokemon/persian/normal_gba.gbapal");
    const u32 gMonBackPic_Persian[] = INCBIN_U32("graphics/pokemon/persian/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Persian[] = INCBIN_U16("graphics/pokemon/persian/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Persian[] = INCBIN_U8("graphics/pokemon/persian/icon.4bpp");
#else
    const u8 gMonIcon_Persian[] = INCBIN_U8("graphics/pokemon/persian/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Persian[] = INCBIN_U8("graphics/pokemon/persian/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Persian[] = INCBIN_COMP("graphics/pokemon/persian/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Persian[] = INCBIN_U16("graphics/pokemon/persian/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Persian[] = INCBIN_U16("graphics/pokemon/persian/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_MeowthAlola[] = INCBIN_U32("graphics/pokemon/meowth/alola/front.4bpp.smol");
    const u16 gMonPalette_MeowthAlola[] = INCBIN_U16("graphics/pokemon/meowth/alola/normal.gbapal");
    const u32 gMonBackPic_MeowthAlola[] = INCBIN_U32("graphics/pokemon/meowth/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_MeowthAlola[] = INCBIN_U16("graphics/pokemon/meowth/alola/shiny.gbapal");
    const u8 gMonIcon_MeowthAlola[] = INCBIN_U8("graphics/pokemon/meowth/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_MeowthAlola[] = INCBIN_COMP("graphics/pokemon/meowth/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_MeowthAlola[] = INCBIN_U16("graphics/pokemon/meowth/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_MeowthAlola[] = INCBIN_U16("graphics/pokemon/meowth/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_PersianAlola[] = INCBIN_U32("graphics/pokemon/persian/alola/front.4bpp.smol");
    const u16 gMonPalette_PersianAlola[] = INCBIN_U16("graphics/pokemon/persian/alola/normal.gbapal");
    const u32 gMonBackPic_PersianAlola[] = INCBIN_U32("graphics/pokemon/persian/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_PersianAlola[] = INCBIN_U16("graphics/pokemon/persian/alola/shiny.gbapal");
    const u8 gMonIcon_PersianAlola[] = INCBIN_U8("graphics/pokemon/persian/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_PersianAlola[] = INCBIN_COMP("graphics/pokemon/persian/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_PersianAlola[] = INCBIN_U16("graphics/pokemon/persian/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_PersianAlola[] = INCBIN_U16("graphics/pokemon/persian/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS

#if P_GALARIAN_FORMS
    const u32 gMonFrontPic_MeowthGalar[] = INCBIN_U32("graphics/pokemon/meowth/galar/front.4bpp.smol");
    const u16 gMonPalette_MeowthGalar[] = INCBIN_U16("graphics/pokemon/meowth/galar/normal.gbapal");
    const u32 gMonBackPic_MeowthGalar[] = INCBIN_U32("graphics/pokemon/meowth/galar/back.4bpp.smol");
    const u16 gMonShinyPalette_MeowthGalar[] = INCBIN_U16("graphics/pokemon/meowth/galar/shiny.gbapal");
    const u8 gMonIcon_MeowthGalar[] = INCBIN_U8("graphics/pokemon/meowth/galar/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_MeowthGalar[] = INCBIN_COMP("graphics/pokemon/meowth/galar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_MeowthGalar[] = INCBIN_U16("graphics/pokemon/meowth/galar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_MeowthGalar[] = INCBIN_U16("graphics/pokemon/meowth/galar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_Perrserker[] = INCBIN_U32("graphics/pokemon/perrserker/front.4bpp.smol");
    const u16 gMonPalette_Perrserker[] = INCBIN_U16("graphics/pokemon/perrserker/normal.gbapal");
    const u32 gMonBackPic_Perrserker[] = INCBIN_U32("graphics/pokemon/perrserker/back.4bpp.smol");
    const u16 gMonShinyPalette_Perrserker[] = INCBIN_U16("graphics/pokemon/perrserker/shiny.gbapal");
    const u8 gMonIcon_Perrserker[] = INCBIN_U8("graphics/pokemon/perrserker/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Perrserker[] = INCBIN_U8("graphics/pokemon/perrserker/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Perrserker[] = INCBIN_COMP("graphics/pokemon/perrserker/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Perrserker[] = INCBIN_U16("graphics/pokemon/perrserker/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Perrserker[] = INCBIN_U16("graphics/pokemon/perrserker/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GALARIAN_FORMS

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_MeowthGmax[] = INCBIN_U32("graphics/pokemon/meowth/gmax/front.4bpp.smol");
    const u32 gMonBackPic_MeowthGmax[] = INCBIN_U32("graphics/pokemon/meowth/gmax/back.4bpp.smol");
    const u16 gMonPalette_MeowthGmax[] = INCBIN_U16("graphics/pokemon/meowth/gmax/normal.gbapal");
    const u16 gMonShinyPalette_MeowthGmax[] = INCBIN_U16("graphics/pokemon/meowth/gmax/shiny.gbapal");
    const u8 gMonIcon_MeowthGmax[] = INCBIN_U8("graphics/pokemon/meowth/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_MeowthGmax[] = INCBIN_COMP("graphics/pokemon/meowth/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_MeowthGmax[] = INCBIN_U16("graphics/pokemon/meowth/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_MeowthGmax[] = INCBIN_U16("graphics/pokemon/meowth/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS
#endif //P_FAMILY_MEOWTH

#if P_FAMILY_PSYDUCK
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Psyduck[] = INCBIN_U32("graphics/pokemon/psyduck/anim_front.4bpp.smol");
    const u16 gMonPalette_Psyduck[] = INCBIN_U16("graphics/pokemon/psyduck/normal.gbapal");
    const u32 gMonBackPic_Psyduck[] = INCBIN_U32("graphics/pokemon/psyduck/back.4bpp.smol");
    const u16 gMonShinyPalette_Psyduck[] = INCBIN_U16("graphics/pokemon/psyduck/shiny.gbapal");
#else
    const u32 gMonFrontPic_Psyduck[] = INCBIN_U32("graphics/pokemon/psyduck/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Psyduck[] = INCBIN_U16("graphics/pokemon/psyduck/normal_gba.gbapal");
    const u32 gMonBackPic_Psyduck[] = INCBIN_U32("graphics/pokemon/psyduck/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Psyduck[] = INCBIN_U16("graphics/pokemon/psyduck/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Psyduck[] = INCBIN_U8("graphics/pokemon/psyduck/icon.4bpp");
#else
    const u8 gMonIcon_Psyduck[] = INCBIN_U8("graphics/pokemon/psyduck/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Psyduck[] = INCBIN_U8("graphics/pokemon/psyduck/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Psyduck[] = INCBIN_COMP("graphics/pokemon/psyduck/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Psyduck[] = INCBIN_U16("graphics/pokemon/psyduck/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Psyduck[] = INCBIN_U16("graphics/pokemon/psyduck/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Golduck[] = INCBIN_U32("graphics/pokemon/golduck/anim_front.4bpp.smol");
    const u16 gMonPalette_Golduck[] = INCBIN_U16("graphics/pokemon/golduck/normal.gbapal");
    const u32 gMonBackPic_Golduck[] = INCBIN_U32("graphics/pokemon/golduck/back.4bpp.smol");
    const u16 gMonShinyPalette_Golduck[] = INCBIN_U16("graphics/pokemon/golduck/shiny.gbapal");
#else
    const u32 gMonFrontPic_Golduck[] = INCBIN_U32("graphics/pokemon/golduck/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Golduck[] = INCBIN_U16("graphics/pokemon/golduck/normal_gba.gbapal");
    const u32 gMonBackPic_Golduck[] = INCBIN_U32("graphics/pokemon/golduck/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Golduck[] = INCBIN_U16("graphics/pokemon/golduck/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Golduck[] = INCBIN_U8("graphics/pokemon/golduck/icon.4bpp");
#else
    const u8 gMonIcon_Golduck[] = INCBIN_U8("graphics/pokemon/golduck/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Golduck[] = INCBIN_U8("graphics/pokemon/golduck/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Golduck[] = INCBIN_COMP("graphics/pokemon/golduck/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Golduck[] = INCBIN_U16("graphics/pokemon/golduck/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Golduck[] = INCBIN_U16("graphics/pokemon/golduck/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_PSYDUCK

#if P_FAMILY_MANKEY
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Mankey[] = INCBIN_U32("graphics/pokemon/mankey/anim_front.4bpp.smol");
    const u16 gMonPalette_Mankey[] = INCBIN_U16("graphics/pokemon/mankey/normal.gbapal");
    const u32 gMonBackPic_Mankey[] = INCBIN_U32("graphics/pokemon/mankey/back.4bpp.smol");
    const u16 gMonShinyPalette_Mankey[] = INCBIN_U16("graphics/pokemon/mankey/shiny.gbapal");
#else
    const u32 gMonFrontPic_Mankey[] = INCBIN_U32("graphics/pokemon/mankey/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Mankey[] = INCBIN_U16("graphics/pokemon/mankey/normal_gba.gbapal");
    const u32 gMonBackPic_Mankey[] = INCBIN_U32("graphics/pokemon/mankey/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Mankey[] = INCBIN_U16("graphics/pokemon/mankey/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Mankey[] = INCBIN_U8("graphics/pokemon/mankey/icon.4bpp");
#else
    const u8 gMonIcon_Mankey[] = INCBIN_U8("graphics/pokemon/mankey/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Mankey[] = INCBIN_U8("graphics/pokemon/mankey/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Mankey[] = INCBIN_COMP("graphics/pokemon/mankey/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Mankey[] = INCBIN_U16("graphics/pokemon/mankey/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Mankey[] = INCBIN_U16("graphics/pokemon/mankey/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Primeape[] = INCBIN_U32("graphics/pokemon/primeape/anim_front.4bpp.smol");
    const u16 gMonPalette_Primeape[] = INCBIN_U16("graphics/pokemon/primeape/normal.gbapal");
    const u32 gMonBackPic_Primeape[] = INCBIN_U32("graphics/pokemon/primeape/back.4bpp.smol");
    const u16 gMonShinyPalette_Primeape[] = INCBIN_U16("graphics/pokemon/primeape/shiny.gbapal");
#else
    const u32 gMonFrontPic_Primeape[] = INCBIN_U32("graphics/pokemon/primeape/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Primeape[] = INCBIN_U16("graphics/pokemon/primeape/normal_gba.gbapal");
    const u32 gMonBackPic_Primeape[] = INCBIN_U32("graphics/pokemon/primeape/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Primeape[] = INCBIN_U16("graphics/pokemon/primeape/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Primeape[] = INCBIN_U8("graphics/pokemon/primeape/icon.4bpp");
#else
    const u8 gMonIcon_Primeape[] = INCBIN_U8("graphics/pokemon/primeape/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Primeape[] = INCBIN_U8("graphics/pokemon/primeape/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Primeape[] = INCBIN_COMP("graphics/pokemon/primeape/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Primeape[] = INCBIN_U16("graphics/pokemon/primeape/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Primeape[] = INCBIN_U16("graphics/pokemon/primeape/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_9_CROSS_EVOS
    const u32 gMonFrontPic_Annihilape[] = INCBIN_U32("graphics/pokemon/annihilape/front.4bpp.smol");
    const u16 gMonPalette_Annihilape[] = INCBIN_U16("graphics/pokemon/annihilape/normal.gbapal");
    const u32 gMonBackPic_Annihilape[] = INCBIN_U32("graphics/pokemon/annihilape/back.4bpp.smol");
    const u16 gMonShinyPalette_Annihilape[] = INCBIN_U16("graphics/pokemon/annihilape/shiny.gbapal");
    const u8 gMonIcon_Annihilape[] = INCBIN_U8("graphics/pokemon/annihilape/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Annihilape[] = INCBIN_U8("graphics/pokemon/annihilape/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Annihilape[] = INCBIN_COMP("graphics/pokemon/annihilape/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Annihilape[] = INCBIN_U16("graphics/pokemon/annihilape/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Annihilape[] = INCBIN_U16("graphics/pokemon/annihilape/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_9_CROSS_EVOS
#endif //P_FAMILY_MANKEY

#if P_FAMILY_GROWLITHE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Growlithe[] = INCBIN_U32("graphics/pokemon/growlithe/anim_front.4bpp.smol");
    const u16 gMonPalette_Growlithe[] = INCBIN_U16("graphics/pokemon/growlithe/normal.gbapal");
    const u32 gMonBackPic_Growlithe[] = INCBIN_U32("graphics/pokemon/growlithe/back.4bpp.smol");
    const u16 gMonShinyPalette_Growlithe[] = INCBIN_U16("graphics/pokemon/growlithe/shiny.gbapal");
#else
    const u32 gMonFrontPic_Growlithe[] = INCBIN_U32("graphics/pokemon/growlithe/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Growlithe[] = INCBIN_U16("graphics/pokemon/growlithe/normal_gba.gbapal");
    const u32 gMonBackPic_Growlithe[] = INCBIN_U32("graphics/pokemon/growlithe/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Growlithe[] = INCBIN_U16("graphics/pokemon/growlithe/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Growlithe[] = INCBIN_U8("graphics/pokemon/growlithe/icon.4bpp");
#else
    const u8 gMonIcon_Growlithe[] = INCBIN_U8("graphics/pokemon/growlithe/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Growlithe[] = INCBIN_U8("graphics/pokemon/growlithe/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Growlithe[] = INCBIN_COMP("graphics/pokemon/growlithe/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Growlithe[] = INCBIN_U16("graphics/pokemon/growlithe/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Growlithe[] = INCBIN_U16("graphics/pokemon/growlithe/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Arcanine[] = INCBIN_U32("graphics/pokemon/arcanine/anim_front.4bpp.smol");
    const u16 gMonPalette_Arcanine[] = INCBIN_U16("graphics/pokemon/arcanine/normal.gbapal");
    const u32 gMonBackPic_Arcanine[] = INCBIN_U32("graphics/pokemon/arcanine/back.4bpp.smol");
    const u16 gMonShinyPalette_Arcanine[] = INCBIN_U16("graphics/pokemon/arcanine/shiny.gbapal");
#else
    const u32 gMonFrontPic_Arcanine[] = INCBIN_U32("graphics/pokemon/arcanine/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Arcanine[] = INCBIN_U16("graphics/pokemon/arcanine/normal_gba.gbapal");
    const u32 gMonBackPic_Arcanine[] = INCBIN_U32("graphics/pokemon/arcanine/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Arcanine[] = INCBIN_U16("graphics/pokemon/arcanine/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Arcanine[] = INCBIN_U8("graphics/pokemon/arcanine/icon.4bpp");
#else
    const u8 gMonIcon_Arcanine[] = INCBIN_U8("graphics/pokemon/arcanine/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Arcanine[] = INCBIN_U8("graphics/pokemon/arcanine/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Arcanine[] = INCBIN_COMP("graphics/pokemon/arcanine/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Arcanine[] = INCBIN_U16("graphics/pokemon/arcanine/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Arcanine[] = INCBIN_U16("graphics/pokemon/arcanine/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_HISUIAN_FORMS
    const u32 gMonFrontPic_GrowlitheHisui[] = INCBIN_U32("graphics/pokemon/growlithe/hisui/front.4bpp.smol");
    const u16 gMonPalette_GrowlitheHisui[] = INCBIN_U16("graphics/pokemon/growlithe/hisui/normal.gbapal");
    const u32 gMonBackPic_GrowlitheHisui[] = INCBIN_U32("graphics/pokemon/growlithe/hisui/back.4bpp.smol");
    const u16 gMonShinyPalette_GrowlitheHisui[] = INCBIN_U16("graphics/pokemon/growlithe/hisui/shiny.gbapal");
    const u8 gMonIcon_GrowlitheHisui[] = INCBIN_U8("graphics/pokemon/growlithe/hisui/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_GrowlitheHisui[] = INCBIN_COMP("graphics/pokemon/growlithe/hisui/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_GrowlitheHisui[] = INCBIN_U16("graphics/pokemon/growlithe/hisui/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_GrowlitheHisui[] = INCBIN_U16("graphics/pokemon/growlithe/hisui/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_ArcanineHisui[] = INCBIN_U32("graphics/pokemon/arcanine/hisui/front.4bpp.smol");
    const u16 gMonPalette_ArcanineHisui[] = INCBIN_U16("graphics/pokemon/arcanine/hisui/normal.gbapal");
    const u32 gMonBackPic_ArcanineHisui[] = INCBIN_U32("graphics/pokemon/arcanine/hisui/back.4bpp.smol");
    const u16 gMonShinyPalette_ArcanineHisui[] = INCBIN_U16("graphics/pokemon/arcanine/hisui/shiny.gbapal");
    const u8 gMonIcon_ArcanineHisui[] = INCBIN_U8("graphics/pokemon/arcanine/hisui/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_ArcanineHisui[] = INCBIN_COMP("graphics/pokemon/arcanine/hisui/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_ArcanineHisui[] = INCBIN_U16("graphics/pokemon/arcanine/hisui/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_ArcanineHisui[] = INCBIN_U16("graphics/pokemon/arcanine/hisui/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_HISUIAN_FORMS
#endif //P_FAMILY_GROWLITHE

#if P_FAMILY_POLIWAG
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Poliwag[] = INCBIN_U32("graphics/pokemon/poliwag/anim_front.4bpp.smol");
    const u16 gMonPalette_Poliwag[] = INCBIN_U16("graphics/pokemon/poliwag/normal.gbapal");
    const u32 gMonBackPic_Poliwag[] = INCBIN_U32("graphics/pokemon/poliwag/back.4bpp.smol");
    const u16 gMonShinyPalette_Poliwag[] = INCBIN_U16("graphics/pokemon/poliwag/shiny.gbapal");
#else
    const u32 gMonFrontPic_Poliwag[] = INCBIN_U32("graphics/pokemon/poliwag/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Poliwag[] = INCBIN_U16("graphics/pokemon/poliwag/normal_gba.gbapal");
    const u32 gMonBackPic_Poliwag[] = INCBIN_U32("graphics/pokemon/poliwag/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Poliwag[] = INCBIN_U16("graphics/pokemon/poliwag/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Poliwag[] = INCBIN_U8("graphics/pokemon/poliwag/icon.4bpp");
#else
    const u8 gMonIcon_Poliwag[] = INCBIN_U8("graphics/pokemon/poliwag/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Poliwag[] = INCBIN_U8("graphics/pokemon/poliwag/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Poliwag[] = INCBIN_COMP("graphics/pokemon/poliwag/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Poliwag[] = INCBIN_U16("graphics/pokemon/poliwag/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Poliwag[] = INCBIN_U16("graphics/pokemon/poliwag/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Poliwhirl[] = INCBIN_U32("graphics/pokemon/poliwhirl/anim_front.4bpp.smol");
    const u16 gMonPalette_Poliwhirl[] = INCBIN_U16("graphics/pokemon/poliwhirl/normal.gbapal");
    const u32 gMonBackPic_Poliwhirl[] = INCBIN_U32("graphics/pokemon/poliwhirl/back.4bpp.smol");
    const u16 gMonShinyPalette_Poliwhirl[] = INCBIN_U16("graphics/pokemon/poliwhirl/shiny.gbapal");
#else
    const u32 gMonFrontPic_Poliwhirl[] = INCBIN_U32("graphics/pokemon/poliwhirl/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Poliwhirl[] = INCBIN_U16("graphics/pokemon/poliwhirl/normal_gba.gbapal");
    const u32 gMonBackPic_Poliwhirl[] = INCBIN_U32("graphics/pokemon/poliwhirl/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Poliwhirl[] = INCBIN_U16("graphics/pokemon/poliwhirl/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Poliwhirl[] = INCBIN_U8("graphics/pokemon/poliwhirl/icon.4bpp");
#else
    const u8 gMonIcon_Poliwhirl[] = INCBIN_U8("graphics/pokemon/poliwhirl/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Poliwhirl[] = INCBIN_U8("graphics/pokemon/poliwhirl/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Poliwhirl[] = INCBIN_COMP("graphics/pokemon/poliwhirl/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Poliwhirl[] = INCBIN_U16("graphics/pokemon/poliwhirl/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Poliwhirl[] = INCBIN_U16("graphics/pokemon/poliwhirl/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Poliwrath[] = INCBIN_U32("graphics/pokemon/poliwrath/anim_front.4bpp.smol");
    const u16 gMonPalette_Poliwrath[] = INCBIN_U16("graphics/pokemon/poliwrath/normal.gbapal");
    const u32 gMonBackPic_Poliwrath[] = INCBIN_U32("graphics/pokemon/poliwrath/back.4bpp.smol");
    const u16 gMonShinyPalette_Poliwrath[] = INCBIN_U16("graphics/pokemon/poliwrath/shiny.gbapal");
#else
    const u32 gMonFrontPic_Poliwrath[] = INCBIN_U32("graphics/pokemon/poliwrath/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Poliwrath[] = INCBIN_U16("graphics/pokemon/poliwrath/normal_gba.gbapal");
    const u32 gMonBackPic_Poliwrath[] = INCBIN_U32("graphics/pokemon/poliwrath/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Poliwrath[] = INCBIN_U16("graphics/pokemon/poliwrath/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Poliwrath[] = INCBIN_U8("graphics/pokemon/poliwrath/icon.4bpp");
#else
    const u8 gMonIcon_Poliwrath[] = INCBIN_U8("graphics/pokemon/poliwrath/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Poliwrath[] = INCBIN_U8("graphics/pokemon/poliwrath/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Poliwrath[] = INCBIN_COMP("graphics/pokemon/poliwrath/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Poliwrath[] = INCBIN_U16("graphics/pokemon/poliwrath/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Poliwrath[] = INCBIN_U16("graphics/pokemon/poliwrath/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Politoed[] = INCBIN_U32("graphics/pokemon/politoed/anim_front.4bpp.smol");
    const u16 gMonPalette_Politoed[] = INCBIN_U16("graphics/pokemon/politoed/normal.gbapal");
    const u32 gMonBackPic_Politoed[] = INCBIN_U32("graphics/pokemon/politoed/back.4bpp.smol");
    const u16 gMonShinyPalette_Politoed[] = INCBIN_U16("graphics/pokemon/politoed/shiny.gbapal");
#else
    const u32 gMonFrontPic_Politoed[] = INCBIN_U32("graphics/pokemon/politoed/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Politoed[] = INCBIN_U16("graphics/pokemon/politoed/normal_gba.gbapal");
    const u32 gMonBackPic_Politoed[] = INCBIN_U32("graphics/pokemon/politoed/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Politoed[] = INCBIN_U16("graphics/pokemon/politoed/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Politoed[] = INCBIN_U8("graphics/pokemon/politoed/icon.4bpp");
#else
    const u8 gMonIcon_Politoed[] = INCBIN_U8("graphics/pokemon/politoed/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Politoed[] = INCBIN_U8("graphics/pokemon/politoed/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Politoed[] = INCBIN_COMP("graphics/pokemon/politoed/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Politoed[] = INCBIN_U16("graphics/pokemon/politoed/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Politoed[] = INCBIN_U16("graphics/pokemon/politoed/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_PolitoedF[] = INCBIN_U32("graphics/pokemon/politoed/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_PolitoedF[] = INCBIN_U32("graphics/pokemon/politoed/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_PolitoedF[] = INCBIN_COMP("graphics/pokemon/politoed/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_POLIWAG

#if P_FAMILY_ABRA
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Abra[] = INCBIN_U32("graphics/pokemon/abra/anim_front.4bpp.smol");
    const u16 gMonPalette_Abra[] = INCBIN_U16("graphics/pokemon/abra/normal.gbapal");
    const u32 gMonBackPic_Abra[] = INCBIN_U32("graphics/pokemon/abra/back.4bpp.smol");
    const u16 gMonShinyPalette_Abra[] = INCBIN_U16("graphics/pokemon/abra/shiny.gbapal");
#else
    const u32 gMonFrontPic_Abra[] = INCBIN_U32("graphics/pokemon/abra/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Abra[] = INCBIN_U16("graphics/pokemon/abra/normal_gba.gbapal");
    const u32 gMonBackPic_Abra[] = INCBIN_U32("graphics/pokemon/abra/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Abra[] = INCBIN_U16("graphics/pokemon/abra/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Abra[] = INCBIN_U8("graphics/pokemon/abra/icon.4bpp");
#else
    const u8 gMonIcon_Abra[] = INCBIN_U8("graphics/pokemon/abra/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Abra[] = INCBIN_U8("graphics/pokemon/abra/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Abra[] = INCBIN_COMP("graphics/pokemon/abra/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Abra[] = INCBIN_U16("graphics/pokemon/abra/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Abra[] = INCBIN_U16("graphics/pokemon/abra/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Kadabra[] = INCBIN_U32("graphics/pokemon/kadabra/anim_front.4bpp.smol");
    const u16 gMonPalette_Kadabra[] = INCBIN_U16("graphics/pokemon/kadabra/normal.gbapal");
    const u32 gMonBackPic_Kadabra[] = INCBIN_U32("graphics/pokemon/kadabra/back.4bpp.smol");
    const u16 gMonShinyPalette_Kadabra[] = INCBIN_U16("graphics/pokemon/kadabra/shiny.gbapal");
#else
    const u32 gMonFrontPic_Kadabra[] = INCBIN_U32("graphics/pokemon/kadabra/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Kadabra[] = INCBIN_U16("graphics/pokemon/kadabra/normal_gba.gbapal");
    const u32 gMonBackPic_Kadabra[] = INCBIN_U32("graphics/pokemon/kadabra/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Kadabra[] = INCBIN_U16("graphics/pokemon/kadabra/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Kadabra[] = INCBIN_U8("graphics/pokemon/kadabra/icon.4bpp");
#else
    const u8 gMonIcon_Kadabra[] = INCBIN_U8("graphics/pokemon/kadabra/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Kadabra[] = INCBIN_U8("graphics/pokemon/kadabra/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Kadabra[] = INCBIN_COMP("graphics/pokemon/kadabra/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Kadabra[] = INCBIN_U16("graphics/pokemon/kadabra/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Kadabra[] = INCBIN_U16("graphics/pokemon/kadabra/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_KadabraF[] = INCBIN_U32("graphics/pokemon/kadabra/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_KadabraF[] = INCBIN_U32("graphics/pokemon/kadabra/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_KadabraF[] = INCBIN_COMP("graphics/pokemon/kadabra/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Alakazam[] = INCBIN_U32("graphics/pokemon/alakazam/anim_front.4bpp.smol");
    const u16 gMonPalette_Alakazam[] = INCBIN_U16("graphics/pokemon/alakazam/normal.gbapal");
    const u32 gMonBackPic_Alakazam[] = INCBIN_U32("graphics/pokemon/alakazam/back.4bpp.smol");
    const u16 gMonShinyPalette_Alakazam[] = INCBIN_U16("graphics/pokemon/alakazam/shiny.gbapal");
#else
    const u32 gMonFrontPic_Alakazam[] = INCBIN_U32("graphics/pokemon/alakazam/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Alakazam[] = INCBIN_U16("graphics/pokemon/alakazam/normal_gba.gbapal");
    const u32 gMonBackPic_Alakazam[] = INCBIN_U32("graphics/pokemon/alakazam/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Alakazam[] = INCBIN_U16("graphics/pokemon/alakazam/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Alakazam[] = INCBIN_U8("graphics/pokemon/alakazam/icon.4bpp");
#else
    const u8 gMonIcon_Alakazam[] = INCBIN_U8("graphics/pokemon/alakazam/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Alakazam[] = INCBIN_U8("graphics/pokemon/alakazam/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Alakazam[] = INCBIN_COMP("graphics/pokemon/alakazam/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Alakazam[] = INCBIN_U16("graphics/pokemon/alakazam/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Alakazam[] = INCBIN_U16("graphics/pokemon/alakazam/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_AlakazamF[] = INCBIN_U32("graphics/pokemon/alakazam/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_AlakazamF[] = INCBIN_U32("graphics/pokemon/alakazam/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_AlakazamF[] = INCBIN_COMP("graphics/pokemon/alakazam/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_AlakazamMega[] = INCBIN_U32("graphics/pokemon/alakazam/mega/front.4bpp.smol");
    const u16 gMonPalette_AlakazamMega[] = INCBIN_U16("graphics/pokemon/alakazam/mega/normal.gbapal");
    const u32 gMonBackPic_AlakazamMega[] = INCBIN_U32("graphics/pokemon/alakazam/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_AlakazamMega[] = INCBIN_U16("graphics/pokemon/alakazam/mega/shiny.gbapal");
    const u8 gMonIcon_AlakazamMega[] = INCBIN_U8("graphics/pokemon/alakazam/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_AlakazamMega[] = INCBIN_COMP("graphics/pokemon/alakazam/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_AlakazamMega[] = INCBIN_U16("graphics/pokemon/alakazam/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_AlakazamMega[] = INCBIN_U16("graphics/pokemon/alakazam/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS
#endif //P_FAMILY_ABRA

#if P_FAMILY_MACHOP
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Machop[] = INCBIN_U32("graphics/pokemon/machop/anim_front.4bpp.smol");
    const u16 gMonPalette_Machop[] = INCBIN_U16("graphics/pokemon/machop/normal.gbapal");
    const u32 gMonBackPic_Machop[] = INCBIN_U32("graphics/pokemon/machop/back.4bpp.smol");
    const u16 gMonShinyPalette_Machop[] = INCBIN_U16("graphics/pokemon/machop/shiny.gbapal");
#else
    const u32 gMonFrontPic_Machop[] = INCBIN_U32("graphics/pokemon/machop/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Machop[] = INCBIN_U16("graphics/pokemon/machop/normal_gba.gbapal");
    const u32 gMonBackPic_Machop[] = INCBIN_U32("graphics/pokemon/machop/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Machop[] = INCBIN_U16("graphics/pokemon/machop/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Machop[] = INCBIN_U8("graphics/pokemon/machop/icon.4bpp");
#else
    const u8 gMonIcon_Machop[] = INCBIN_U8("graphics/pokemon/machop/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Machop[] = INCBIN_U8("graphics/pokemon/machop/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Machop[] = INCBIN_COMP("graphics/pokemon/machop/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Machop[] = INCBIN_U16("graphics/pokemon/machop/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Machop[] = INCBIN_U16("graphics/pokemon/machop/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Machoke[] = INCBIN_U32("graphics/pokemon/machoke/anim_front.4bpp.smol");
    const u16 gMonPalette_Machoke[] = INCBIN_U16("graphics/pokemon/machoke/normal.gbapal");
    const u32 gMonBackPic_Machoke[] = INCBIN_U32("graphics/pokemon/machoke/back.4bpp.smol");
    const u16 gMonShinyPalette_Machoke[] = INCBIN_U16("graphics/pokemon/machoke/shiny.gbapal");
#else
    const u32 gMonFrontPic_Machoke[] = INCBIN_U32("graphics/pokemon/machoke/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Machoke[] = INCBIN_U16("graphics/pokemon/machoke/normal_gba.gbapal");
    const u32 gMonBackPic_Machoke[] = INCBIN_U32("graphics/pokemon/machoke/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Machoke[] = INCBIN_U16("graphics/pokemon/machoke/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Machoke[] = INCBIN_U8("graphics/pokemon/machoke/icon.4bpp");
#else
    const u8 gMonIcon_Machoke[] = INCBIN_U8("graphics/pokemon/machoke/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Machoke[] = INCBIN_U8("graphics/pokemon/machoke/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Machoke[] = INCBIN_COMP("graphics/pokemon/machoke/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Machoke[] = INCBIN_U16("graphics/pokemon/machoke/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Machoke[] = INCBIN_U16("graphics/pokemon/machoke/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Machamp[] = INCBIN_U32("graphics/pokemon/machamp/anim_front.4bpp.smol");
    const u16 gMonPalette_Machamp[] = INCBIN_U16("graphics/pokemon/machamp/normal.gbapal");
    const u32 gMonBackPic_Machamp[] = INCBIN_U32("graphics/pokemon/machamp/back.4bpp.smol");
    const u16 gMonShinyPalette_Machamp[] = INCBIN_U16("graphics/pokemon/machamp/shiny.gbapal");
#else
    const u32 gMonFrontPic_Machamp[] = INCBIN_U32("graphics/pokemon/machamp/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Machamp[] = INCBIN_U16("graphics/pokemon/machamp/normal_gba.gbapal");
    const u32 gMonBackPic_Machamp[] = INCBIN_U32("graphics/pokemon/machamp/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Machamp[] = INCBIN_U16("graphics/pokemon/machamp/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Machamp[] = INCBIN_U8("graphics/pokemon/machamp/icon.4bpp");
#else
    const u8 gMonIcon_Machamp[] = INCBIN_U8("graphics/pokemon/machamp/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Machamp[] = INCBIN_U8("graphics/pokemon/machamp/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Machamp[] = INCBIN_COMP("graphics/pokemon/machamp/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Machamp[] = INCBIN_U16("graphics/pokemon/machamp/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Machamp[] = INCBIN_U16("graphics/pokemon/machamp/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_MachampGmax[] = INCBIN_U32("graphics/pokemon/machamp/gmax/front.4bpp.smol");
    const u32 gMonBackPic_MachampGmax[] = INCBIN_U32("graphics/pokemon/machamp/gmax/back.4bpp.smol");
    const u16 gMonPalette_MachampGmax[] = INCBIN_U16("graphics/pokemon/machamp/gmax/normal.gbapal");
    const u16 gMonShinyPalette_MachampGmax[] = INCBIN_U16("graphics/pokemon/machamp/gmax/shiny.gbapal");
    const u8 gMonIcon_MachampGmax[] = INCBIN_U8("graphics/pokemon/machamp/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_MachampGmax[] = INCBIN_COMP("graphics/pokemon/machamp/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_MachampGmax[] = INCBIN_U16("graphics/pokemon/machamp/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_MachampGmax[] = INCBIN_U16("graphics/pokemon/machamp/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS
#endif //P_FAMILY_MACHOP

#if P_FAMILY_BELLSPROUT
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Bellsprout[] = INCBIN_U32("graphics/pokemon/bellsprout/anim_front.4bpp.smol");
    const u16 gMonPalette_Bellsprout[] = INCBIN_U16("graphics/pokemon/bellsprout/normal.gbapal");
    const u32 gMonBackPic_Bellsprout[] = INCBIN_U32("graphics/pokemon/bellsprout/back.4bpp.smol");
    const u16 gMonShinyPalette_Bellsprout[] = INCBIN_U16("graphics/pokemon/bellsprout/shiny.gbapal");
#else
    const u32 gMonFrontPic_Bellsprout[] = INCBIN_U32("graphics/pokemon/bellsprout/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Bellsprout[] = INCBIN_U16("graphics/pokemon/bellsprout/normal_gba.gbapal");
    const u32 gMonBackPic_Bellsprout[] = INCBIN_U32("graphics/pokemon/bellsprout/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Bellsprout[] = INCBIN_U16("graphics/pokemon/bellsprout/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Bellsprout[] = INCBIN_U8("graphics/pokemon/bellsprout/icon.4bpp");
#else
    const u8 gMonIcon_Bellsprout[] = INCBIN_U8("graphics/pokemon/bellsprout/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Bellsprout[] = INCBIN_U8("graphics/pokemon/bellsprout/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Bellsprout[] = INCBIN_COMP("graphics/pokemon/bellsprout/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Bellsprout[] = INCBIN_U16("graphics/pokemon/bellsprout/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Bellsprout[] = INCBIN_U16("graphics/pokemon/bellsprout/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Weepinbell[] = INCBIN_U32("graphics/pokemon/weepinbell/anim_front.4bpp.smol");
    const u16 gMonPalette_Weepinbell[] = INCBIN_U16("graphics/pokemon/weepinbell/normal.gbapal");
    const u32 gMonBackPic_Weepinbell[] = INCBIN_U32("graphics/pokemon/weepinbell/back.4bpp.smol");
    const u16 gMonShinyPalette_Weepinbell[] = INCBIN_U16("graphics/pokemon/weepinbell/shiny.gbapal");
#else
    const u32 gMonFrontPic_Weepinbell[] = INCBIN_U32("graphics/pokemon/weepinbell/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Weepinbell[] = INCBIN_U16("graphics/pokemon/weepinbell/normal_gba.gbapal");
    const u32 gMonBackPic_Weepinbell[] = INCBIN_U32("graphics/pokemon/weepinbell/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Weepinbell[] = INCBIN_U16("graphics/pokemon/weepinbell/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Weepinbell[] = INCBIN_U8("graphics/pokemon/weepinbell/icon.4bpp");
#else
    const u8 gMonIcon_Weepinbell[] = INCBIN_U8("graphics/pokemon/weepinbell/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Weepinbell[] = INCBIN_U8("graphics/pokemon/weepinbell/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Weepinbell[] = INCBIN_COMP("graphics/pokemon/weepinbell/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Weepinbell[] = INCBIN_U16("graphics/pokemon/weepinbell/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Weepinbell[] = INCBIN_U16("graphics/pokemon/weepinbell/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Victreebel[] = INCBIN_U32("graphics/pokemon/victreebel/anim_front.4bpp.smol");
    const u16 gMonPalette_Victreebel[] = INCBIN_U16("graphics/pokemon/victreebel/normal.gbapal");
    const u32 gMonBackPic_Victreebel[] = INCBIN_U32("graphics/pokemon/victreebel/back.4bpp.smol");
    const u16 gMonShinyPalette_Victreebel[] = INCBIN_U16("graphics/pokemon/victreebel/shiny.gbapal");
#else
    const u32 gMonFrontPic_Victreebel[] = INCBIN_U32("graphics/pokemon/victreebel/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Victreebel[] = INCBIN_U16("graphics/pokemon/victreebel/normal_gba.gbapal");
    const u32 gMonBackPic_Victreebel[] = INCBIN_U32("graphics/pokemon/victreebel/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Victreebel[] = INCBIN_U16("graphics/pokemon/victreebel/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Victreebel[] = INCBIN_U8("graphics/pokemon/victreebel/icon.4bpp");
#else
    const u8 gMonIcon_Victreebel[] = INCBIN_U8("graphics/pokemon/victreebel/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Victreebel[] = INCBIN_U8("graphics/pokemon/victreebel/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Victreebel[] = INCBIN_COMP("graphics/pokemon/victreebel/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Victreebel[] = INCBIN_U16("graphics/pokemon/victreebel/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Victreebel[] = INCBIN_U16("graphics/pokemon/victreebel/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_9_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_VictreebelMega[] = INCBIN_U32("graphics/pokemon/victreebel/mega/front.4bpp.smol");
    const u16 gMonPalette_VictreebelMega[] = INCBIN_U16("graphics/pokemon/victreebel/mega/normal.gbapal");
    const u32 gMonBackPic_VictreebelMega[] = INCBIN_U32("graphics/pokemon/victreebel/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_VictreebelMega[] = INCBIN_U16("graphics/pokemon/victreebel/mega/shiny.gbapal");
    const u8 gMonIcon_VictreebelMega[] = INCBIN_U8("graphics/pokemon/victreebel/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
//    const u32 gObjectEventPic_VictreebelMega[] = INCBIN_COMP("graphics/pokemon/victreebel/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
//    const u16 gOverworldPalette_VictreebelMega[] = INCBIN_U16("graphics/pokemon/victreebel/mega/overworld_normal.gbapal");
//    const u16 gShinyOverworldPalette_VictreebelMega[] = INCBIN_U16("graphics/pokemon/victreebel/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_GEN_9_MEGA_EVOLUTIONS
#endif //P_FAMILY_BELLSPROUT

#if P_FAMILY_TENTACOOL
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Tentacool[] = INCBIN_U32("graphics/pokemon/tentacool/anim_front.4bpp.smol");
    const u16 gMonPalette_Tentacool[] = INCBIN_U16("graphics/pokemon/tentacool/normal.gbapal");
    const u32 gMonBackPic_Tentacool[] = INCBIN_U32("graphics/pokemon/tentacool/back.4bpp.smol");
    const u16 gMonShinyPalette_Tentacool[] = INCBIN_U16("graphics/pokemon/tentacool/shiny.gbapal");
#else
    const u32 gMonFrontPic_Tentacool[] = INCBIN_U32("graphics/pokemon/tentacool/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Tentacool[] = INCBIN_U16("graphics/pokemon/tentacool/normal_gba.gbapal");
    const u32 gMonBackPic_Tentacool[] = INCBIN_U32("graphics/pokemon/tentacool/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Tentacool[] = INCBIN_U16("graphics/pokemon/tentacool/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Tentacool[] = INCBIN_U8("graphics/pokemon/tentacool/icon.4bpp");
#else
    const u8 gMonIcon_Tentacool[] = INCBIN_U8("graphics/pokemon/tentacool/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Tentacool[] = INCBIN_U8("graphics/pokemon/tentacool/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Tentacool[] = INCBIN_COMP("graphics/pokemon/tentacool/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Tentacool[] = INCBIN_U16("graphics/pokemon/tentacool/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Tentacool[] = INCBIN_U16("graphics/pokemon/tentacool/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Tentacool[] = INCBIN_U16("graphics/pokemon/tentacool/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Tentacruel[] = INCBIN_U32("graphics/pokemon/tentacruel/anim_front.4bpp.smol");
    const u16 gMonPalette_Tentacruel[] = INCBIN_U16("graphics/pokemon/tentacruel/normal.gbapal");
    const u32 gMonBackPic_Tentacruel[] = INCBIN_U32("graphics/pokemon/tentacruel/back.4bpp.smol");
    const u16 gMonShinyPalette_Tentacruel[] = INCBIN_U16("graphics/pokemon/tentacruel/shiny.gbapal");
#else
    const u32 gMonFrontPic_Tentacruel[] = INCBIN_U32("graphics/pokemon/tentacruel/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Tentacruel[] = INCBIN_U16("graphics/pokemon/tentacruel/normal_gba.gbapal");
    const u32 gMonBackPic_Tentacruel[] = INCBIN_U32("graphics/pokemon/tentacruel/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Tentacruel[] = INCBIN_U16("graphics/pokemon/tentacruel/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Tentacruel[] = INCBIN_U8("graphics/pokemon/tentacruel/icon.4bpp");
#else
    const u8 gMonIcon_Tentacruel[] = INCBIN_U8("graphics/pokemon/tentacruel/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Tentacruel[] = INCBIN_U8("graphics/pokemon/tentacruel/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Tentacruel[] = INCBIN_COMP("graphics/pokemon/tentacruel/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Tentacruel[] = INCBIN_U16("graphics/pokemon/tentacruel/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Tentacruel[] = INCBIN_U16("graphics/pokemon/tentacruel/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Tentacruel[] = INCBIN_U16("graphics/pokemon/tentacruel/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_TENTACOOL

#if P_FAMILY_GEODUDE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Geodude[] = INCBIN_U32("graphics/pokemon/geodude/anim_front.4bpp.smol");
    const u16 gMonPalette_Geodude[] = INCBIN_U16("graphics/pokemon/geodude/normal.gbapal");
    const u32 gMonBackPic_Geodude[] = INCBIN_U32("graphics/pokemon/geodude/back.4bpp.smol");
    const u16 gMonShinyPalette_Geodude[] = INCBIN_U16("graphics/pokemon/geodude/shiny.gbapal");
#else
    const u32 gMonFrontPic_Geodude[] = INCBIN_U32("graphics/pokemon/geodude/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Geodude[] = INCBIN_U16("graphics/pokemon/geodude/normal_gba.gbapal");
    const u32 gMonBackPic_Geodude[] = INCBIN_U32("graphics/pokemon/geodude/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Geodude[] = INCBIN_U16("graphics/pokemon/geodude/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Geodude[] = INCBIN_U8("graphics/pokemon/geodude/icon.4bpp");
#else
    const u8 gMonIcon_Geodude[] = INCBIN_U8("graphics/pokemon/geodude/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Geodude[] = INCBIN_U8("graphics/pokemon/geodude/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Geodude[] = INCBIN_COMP("graphics/pokemon/geodude/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Geodude[] = INCBIN_U16("graphics/pokemon/geodude/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Geodude[] = INCBIN_U16("graphics/pokemon/geodude/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Graveler[] = INCBIN_U32("graphics/pokemon/graveler/anim_front.4bpp.smol");
    const u16 gMonPalette_Graveler[] = INCBIN_U16("graphics/pokemon/graveler/normal.gbapal");
    const u32 gMonBackPic_Graveler[] = INCBIN_U32("graphics/pokemon/graveler/back.4bpp.smol");
    const u16 gMonShinyPalette_Graveler[] = INCBIN_U16("graphics/pokemon/graveler/shiny.gbapal");
#else
    const u32 gMonFrontPic_Graveler[] = INCBIN_U32("graphics/pokemon/graveler/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Graveler[] = INCBIN_U16("graphics/pokemon/graveler/normal_gba.gbapal");
    const u32 gMonBackPic_Graveler[] = INCBIN_U32("graphics/pokemon/graveler/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Graveler[] = INCBIN_U16("graphics/pokemon/graveler/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Graveler[] = INCBIN_U8("graphics/pokemon/graveler/icon.4bpp");
#else
    const u8 gMonIcon_Graveler[] = INCBIN_U8("graphics/pokemon/graveler/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Graveler[] = INCBIN_U8("graphics/pokemon/graveler/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Graveler[] = INCBIN_COMP("graphics/pokemon/graveler/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Graveler[] = INCBIN_U16("graphics/pokemon/graveler/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Graveler[] = INCBIN_U16("graphics/pokemon/graveler/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Golem[] = INCBIN_U32("graphics/pokemon/golem/anim_front.4bpp.smol");
    const u16 gMonPalette_Golem[] = INCBIN_U16("graphics/pokemon/golem/normal.gbapal");
    const u32 gMonBackPic_Golem[] = INCBIN_U32("graphics/pokemon/golem/back.4bpp.smol");
    const u16 gMonShinyPalette_Golem[] = INCBIN_U16("graphics/pokemon/golem/shiny.gbapal");
#else
    const u32 gMonFrontPic_Golem[] = INCBIN_U32("graphics/pokemon/golem/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Golem[] = INCBIN_U16("graphics/pokemon/golem/normal_gba.gbapal");
    const u32 gMonBackPic_Golem[] = INCBIN_U32("graphics/pokemon/golem/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Golem[] = INCBIN_U16("graphics/pokemon/golem/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Golem[] = INCBIN_U8("graphics/pokemon/golem/icon.4bpp");
#else
    const u8 gMonIcon_Golem[] = INCBIN_U8("graphics/pokemon/golem/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
#if !P_GBA_STYLE_SPECIES_FOOTPRINTS
    const u8 gMonFootprint_Golem[] = INCBIN_U8("graphics/pokemon/golem/footprint.1bpp");
#else
    const u8 gMonFootprint_Golem[] = INCBIN_U8("graphics/pokemon/golem/footprint_gba.1bpp");
#endif //P_GBA_STYLE_SPECIES_FOOTPRINTS
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Golem[] = INCBIN_COMP("graphics/pokemon/golem/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Golem[] = INCBIN_U16("graphics/pokemon/golem/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Golem[] = INCBIN_U16("graphics/pokemon/golem/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_GeodudeAlola[] = INCBIN_U32("graphics/pokemon/geodude/alola/front.4bpp.smol");
    const u16 gMonPalette_GeodudeAlola[] = INCBIN_U16("graphics/pokemon/geodude/alola/normal.gbapal");
    const u32 gMonBackPic_GeodudeAlola[] = INCBIN_U32("graphics/pokemon/geodude/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_GeodudeAlola[] = INCBIN_U16("graphics/pokemon/geodude/alola/shiny.gbapal");
    const u8 gMonIcon_GeodudeAlola[] = INCBIN_U8("graphics/pokemon/geodude/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_GeodudeAlola[] = INCBIN_COMP("graphics/pokemon/geodude/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_GeodudeAlola[] = INCBIN_U16("graphics/pokemon/geodude/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_GeodudeAlola[] = INCBIN_U16("graphics/pokemon/geodude/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_GravelerAlola[] = INCBIN_U32("graphics/pokemon/graveler/alola/front.4bpp.smol");
    const u16 gMonPalette_GravelerAlola[] = INCBIN_U16("graphics/pokemon/graveler/alola/normal.gbapal");
    const u32 gMonBackPic_GravelerAlola[] = INCBIN_U32("graphics/pokemon/graveler/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_GravelerAlola[] = INCBIN_U16("graphics/pokemon/graveler/alola/shiny.gbapal");
    const u8 gMonIcon_GravelerAlola[] = INCBIN_U8("graphics/pokemon/graveler/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_GravelerAlola[] = INCBIN_COMP("graphics/pokemon/graveler/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_GravelerAlola[] = INCBIN_U16("graphics/pokemon/graveler/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_GravelerAlola[] = INCBIN_U16("graphics/pokemon/graveler/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_GolemAlola[] = INCBIN_U32("graphics/pokemon/golem/alola/front.4bpp.smol");
    const u16 gMonPalette_GolemAlola[] = INCBIN_U16("graphics/pokemon/golem/alola/normal.gbapal");
    const u32 gMonBackPic_GolemAlola[] = INCBIN_U32("graphics/pokemon/golem/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_GolemAlola[] = INCBIN_U16("graphics/pokemon/golem/alola/shiny.gbapal");
    const u8 gMonIcon_GolemAlola[] = INCBIN_U8("graphics/pokemon/golem/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_GolemAlola[] = INCBIN_COMP("graphics/pokemon/golem/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_GolemAlola[] = INCBIN_U16("graphics/pokemon/golem/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_GolemAlola[] = INCBIN_U16("graphics/pokemon/golem/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_GEODUDE

#if P_FAMILY_PONYTA
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Ponyta[] = INCBIN_U32("graphics/pokemon/ponyta/anim_front.4bpp.smol");
    const u16 gMonPalette_Ponyta[] = INCBIN_U16("graphics/pokemon/ponyta/normal.gbapal");
    const u32 gMonBackPic_Ponyta[] = INCBIN_U32("graphics/pokemon/ponyta/back.4bpp.smol");
    const u16 gMonShinyPalette_Ponyta[] = INCBIN_U16("graphics/pokemon/ponyta/shiny.gbapal");
#else
    const u32 gMonFrontPic_Ponyta[] = INCBIN_U32("graphics/pokemon/ponyta/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Ponyta[] = INCBIN_U16("graphics/pokemon/ponyta/normal_gba.gbapal");
    const u32 gMonBackPic_Ponyta[] = INCBIN_U32("graphics/pokemon/ponyta/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Ponyta[] = INCBIN_U16("graphics/pokemon/ponyta/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Ponyta[] = INCBIN_U8("graphics/pokemon/ponyta/icon.4bpp");
#else
    const u8 gMonIcon_Ponyta[] = INCBIN_U8("graphics/pokemon/ponyta/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Ponyta[] = INCBIN_U8("graphics/pokemon/ponyta/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Ponyta[] = INCBIN_COMP("graphics/pokemon/ponyta/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Ponyta[] = INCBIN_U16("graphics/pokemon/ponyta/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Ponyta[] = INCBIN_U16("graphics/pokemon/ponyta/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Rapidash[] = INCBIN_U32("graphics/pokemon/rapidash/anim_front.4bpp.smol");
    const u16 gMonPalette_Rapidash[] = INCBIN_U16("graphics/pokemon/rapidash/normal.gbapal");
    const u32 gMonBackPic_Rapidash[] = INCBIN_U32("graphics/pokemon/rapidash/back.4bpp.smol");
    const u16 gMonShinyPalette_Rapidash[] = INCBIN_U16("graphics/pokemon/rapidash/shiny.gbapal");
#else
    const u32 gMonFrontPic_Rapidash[] = INCBIN_U32("graphics/pokemon/rapidash/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Rapidash[] = INCBIN_U16("graphics/pokemon/rapidash/normal_gba.gbapal");
    const u32 gMonBackPic_Rapidash[] = INCBIN_U32("graphics/pokemon/rapidash/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Rapidash[] = INCBIN_U16("graphics/pokemon/rapidash/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Rapidash[] = INCBIN_U8("graphics/pokemon/rapidash/icon.4bpp");
#else
    const u8 gMonIcon_Rapidash[] = INCBIN_U8("graphics/pokemon/rapidash/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Rapidash[] = INCBIN_U8("graphics/pokemon/rapidash/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Rapidash[] = INCBIN_COMP("graphics/pokemon/rapidash/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Rapidash[] = INCBIN_U16("graphics/pokemon/rapidash/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Rapidash[] = INCBIN_U16("graphics/pokemon/rapidash/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GALARIAN_FORMS
    const u32 gMonFrontPic_PonytaGalar[] = INCBIN_U32("graphics/pokemon/ponyta/galar/front.4bpp.smol");
    const u16 gMonPalette_PonytaGalar[] = INCBIN_U16("graphics/pokemon/ponyta/galar/normal.gbapal");
    const u32 gMonBackPic_PonytaGalar[] = INCBIN_U32("graphics/pokemon/ponyta/galar/back.4bpp.smol");
    const u16 gMonShinyPalette_PonytaGalar[] = INCBIN_U16("graphics/pokemon/ponyta/galar/shiny.gbapal");
    const u8 gMonIcon_PonytaGalar[] = INCBIN_U8("graphics/pokemon/ponyta/galar/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_PonytaGalar[] = INCBIN_COMP("graphics/pokemon/ponyta/galar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_PonytaGalar[] = INCBIN_U16("graphics/pokemon/ponyta/galar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_PonytaGalar[] = INCBIN_U16("graphics/pokemon/ponyta/galar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_RapidashGalar[] = INCBIN_U32("graphics/pokemon/rapidash/galar/front.4bpp.smol");
    const u16 gMonPalette_RapidashGalar[] = INCBIN_U16("graphics/pokemon/rapidash/galar/normal.gbapal");
    const u32 gMonBackPic_RapidashGalar[] = INCBIN_U32("graphics/pokemon/rapidash/galar/back.4bpp.smol");
    const u16 gMonShinyPalette_RapidashGalar[] = INCBIN_U16("graphics/pokemon/rapidash/galar/shiny.gbapal");
    const u8 gMonIcon_RapidashGalar[] = INCBIN_U8("graphics/pokemon/rapidash/galar/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RapidashGalar[] = INCBIN_COMP("graphics/pokemon/rapidash/galar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_RapidashGalar[] = INCBIN_U16("graphics/pokemon/rapidash/galar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_RapidashGalar[] = INCBIN_U16("graphics/pokemon/rapidash/galar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_PONYTA

#if P_FAMILY_SLOWPOKE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Slowpoke[] = INCBIN_U32("graphics/pokemon/slowpoke/anim_front.4bpp.smol");
    const u16 gMonPalette_Slowpoke[] = INCBIN_U16("graphics/pokemon/slowpoke/normal.gbapal");
    const u32 gMonBackPic_Slowpoke[] = INCBIN_U32("graphics/pokemon/slowpoke/back.4bpp.smol");
    const u16 gMonShinyPalette_Slowpoke[] = INCBIN_U16("graphics/pokemon/slowpoke/shiny.gbapal");
#else
    const u32 gMonFrontPic_Slowpoke[] = INCBIN_U32("graphics/pokemon/slowpoke/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Slowpoke[] = INCBIN_U16("graphics/pokemon/slowpoke/normal_gba.gbapal");
    const u32 gMonBackPic_Slowpoke[] = INCBIN_U32("graphics/pokemon/slowpoke/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Slowpoke[] = INCBIN_U16("graphics/pokemon/slowpoke/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Slowpoke[] = INCBIN_U8("graphics/pokemon/slowpoke/icon.4bpp");
#else
    const u8 gMonIcon_Slowpoke[] = INCBIN_U8("graphics/pokemon/slowpoke/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Slowpoke[] = INCBIN_U8("graphics/pokemon/slowpoke/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Slowpoke[] = INCBIN_COMP("graphics/pokemon/slowpoke/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Slowpoke[] = INCBIN_U16("graphics/pokemon/slowpoke/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Slowpoke[] = INCBIN_U16("graphics/pokemon/slowpoke/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Slowbro[] = INCBIN_U32("graphics/pokemon/slowbro/anim_front.4bpp.smol");
    const u16 gMonPalette_Slowbro[] = INCBIN_U16("graphics/pokemon/slowbro/normal.gbapal");
    const u32 gMonBackPic_Slowbro[] = INCBIN_U32("graphics/pokemon/slowbro/back.4bpp.smol");
    const u16 gMonShinyPalette_Slowbro[] = INCBIN_U16("graphics/pokemon/slowbro/shiny.gbapal");
#else
    const u32 gMonFrontPic_Slowbro[] = INCBIN_U32("graphics/pokemon/slowbro/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Slowbro[] = INCBIN_U16("graphics/pokemon/slowbro/normal_gba.gbapal");
    const u32 gMonBackPic_Slowbro[] = INCBIN_U32("graphics/pokemon/slowbro/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Slowbro[] = INCBIN_U16("graphics/pokemon/slowbro/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Slowbro[] = INCBIN_U8("graphics/pokemon/slowbro/icon.4bpp");
#else
    const u8 gMonIcon_Slowbro[] = INCBIN_U8("graphics/pokemon/slowbro/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Slowbro[] = INCBIN_U8("graphics/pokemon/slowbro/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Slowbro[] = INCBIN_COMP("graphics/pokemon/slowbro/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Slowbro[] = INCBIN_U16("graphics/pokemon/slowbro/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Slowbro[] = INCBIN_U16("graphics/pokemon/slowbro/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Slowking[] = INCBIN_U32("graphics/pokemon/slowking/anim_front.4bpp.smol");
    const u16 gMonPalette_Slowking[] = INCBIN_U16("graphics/pokemon/slowking/normal.gbapal");
    const u32 gMonBackPic_Slowking[] = INCBIN_U32("graphics/pokemon/slowking/back.4bpp.smol");
    const u16 gMonShinyPalette_Slowking[] = INCBIN_U16("graphics/pokemon/slowking/shiny.gbapal");
#else
    const u32 gMonFrontPic_Slowking[] = INCBIN_U32("graphics/pokemon/slowking/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Slowking[] = INCBIN_U16("graphics/pokemon/slowking/normal_gba.gbapal");
    const u32 gMonBackPic_Slowking[] = INCBIN_U32("graphics/pokemon/slowking/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Slowking[] = INCBIN_U16("graphics/pokemon/slowking/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Slowking[] = INCBIN_U8("graphics/pokemon/slowking/icon.4bpp");
#else
    const u8 gMonIcon_Slowking[] = INCBIN_U8("graphics/pokemon/slowking/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Slowking[] = INCBIN_U8("graphics/pokemon/slowking/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Slowking[] = INCBIN_COMP("graphics/pokemon/slowking/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Slowking[] = INCBIN_U16("graphics/pokemon/slowking/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Slowking[] = INCBIN_U16("graphics/pokemon/slowking/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_SlowbroMega[] = INCBIN_U32("graphics/pokemon/slowbro/mega/front.4bpp.smol");
    const u16 gMonPalette_SlowbroMega[] = INCBIN_U16("graphics/pokemon/slowbro/mega/normal.gbapal");
    const u32 gMonBackPic_SlowbroMega[] = INCBIN_U32("graphics/pokemon/slowbro/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_SlowbroMega[] = INCBIN_U16("graphics/pokemon/slowbro/mega/shiny.gbapal");
    const u8 gMonIcon_SlowbroMega[] = INCBIN_U8("graphics/pokemon/slowbro/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_SlowbroMega[] = INCBIN_COMP("graphics/pokemon/slowbro/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_SlowbroMega[] = INCBIN_U16("graphics/pokemon/slowbro/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_SlowbroMega[] = INCBIN_U16("graphics/pokemon/slowbro/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS

#if P_GALARIAN_FORMS
    const u32 gMonFrontPic_SlowpokeGalar[] = INCBIN_U32("graphics/pokemon/slowpoke/galar/front.4bpp.smol");
    const u16 gMonPalette_SlowpokeGalar[] = INCBIN_U16("graphics/pokemon/slowpoke/galar/normal.gbapal");
    const u32 gMonBackPic_SlowpokeGalar[] = INCBIN_U32("graphics/pokemon/slowpoke/galar/back.4bpp.smol");
    const u16 gMonShinyPalette_SlowpokeGalar[] = INCBIN_U16("graphics/pokemon/slowpoke/galar/shiny.gbapal");
    const u8 gMonIcon_SlowpokeGalar[] = INCBIN_U8("graphics/pokemon/slowpoke/galar/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_SlowpokeGalar[] = INCBIN_COMP("graphics/pokemon/slowpoke/galar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_SlowpokeGalar[] = INCBIN_U16("graphics/pokemon/slowpoke/galar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_SlowpokeGalar[] = INCBIN_U16("graphics/pokemon/slowpoke/galar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_SlowbroGalar[] = INCBIN_U32("graphics/pokemon/slowbro/galar/front.4bpp.smol");
    const u16 gMonPalette_SlowbroGalar[] = INCBIN_U16("graphics/pokemon/slowbro/galar/normal.gbapal");
    const u32 gMonBackPic_SlowbroGalar[] = INCBIN_U32("graphics/pokemon/slowbro/galar/back.4bpp.smol");
    const u16 gMonShinyPalette_SlowbroGalar[] = INCBIN_U16("graphics/pokemon/slowbro/galar/shiny.gbapal");
    const u8 gMonIcon_SlowbroGalar[] = INCBIN_U8("graphics/pokemon/slowbro/galar/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_SlowbroGalar[] = INCBIN_COMP("graphics/pokemon/slowbro/galar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_SlowbroGalar[] = INCBIN_U16("graphics/pokemon/slowbro/galar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_SlowbroGalar[] = INCBIN_U16("graphics/pokemon/slowbro/galar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_2_CROSS_EVOS
    const u32 gMonFrontPic_SlowkingGalar[] = INCBIN_U32("graphics/pokemon/slowking/galar/front.4bpp.smol");
    const u16 gMonPalette_SlowkingGalar[] = INCBIN_U16("graphics/pokemon/slowking/galar/normal.gbapal");
    const u32 gMonBackPic_SlowkingGalar[] = INCBIN_U32("graphics/pokemon/slowking/galar/back.4bpp.smol");
    const u16 gMonShinyPalette_SlowkingGalar[] = INCBIN_U16("graphics/pokemon/slowking/galar/shiny.gbapal");
    const u8 gMonIcon_SlowkingGalar[] = INCBIN_U8("graphics/pokemon/slowking/galar/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_SlowkingGalar[] = INCBIN_COMP("graphics/pokemon/slowking/galar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_SlowkingGalar[] = INCBIN_U16("graphics/pokemon/slowking/galar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_SlowkingGalar[] = INCBIN_U16("graphics/pokemon/slowking/galar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_SLOWPOKE

#if P_FAMILY_MAGNEMITE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Magnemite[] = INCBIN_U32("graphics/pokemon/magnemite/anim_front.4bpp.smol");
    const u16 gMonPalette_Magnemite[] = INCBIN_U16("graphics/pokemon/magnemite/normal.gbapal");
    const u32 gMonBackPic_Magnemite[] = INCBIN_U32("graphics/pokemon/magnemite/back.4bpp.smol");
    const u16 gMonShinyPalette_Magnemite[] = INCBIN_U16("graphics/pokemon/magnemite/shiny.gbapal");
#else
    const u32 gMonFrontPic_Magnemite[] = INCBIN_U32("graphics/pokemon/magnemite/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Magnemite[] = INCBIN_U16("graphics/pokemon/magnemite/normal_gba.gbapal");
    const u32 gMonBackPic_Magnemite[] = INCBIN_U32("graphics/pokemon/magnemite/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Magnemite[] = INCBIN_U16("graphics/pokemon/magnemite/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Magnemite[] = INCBIN_U8("graphics/pokemon/magnemite/icon.4bpp");
#else
    const u8 gMonIcon_Magnemite[] = INCBIN_U8("graphics/pokemon/magnemite/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Magnemite[] = INCBIN_U8("graphics/pokemon/magnemite/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Magnemite[] = INCBIN_COMP("graphics/pokemon/magnemite/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Magnemite[] = INCBIN_U16("graphics/pokemon/magnemite/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Magnemite[] = INCBIN_U16("graphics/pokemon/magnemite/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Magneton[] = INCBIN_U32("graphics/pokemon/magneton/anim_front.4bpp.smol");
    const u16 gMonPalette_Magneton[] = INCBIN_U16("graphics/pokemon/magneton/normal.gbapal");
    const u32 gMonBackPic_Magneton[] = INCBIN_U32("graphics/pokemon/magneton/back.4bpp.smol");
    const u16 gMonShinyPalette_Magneton[] = INCBIN_U16("graphics/pokemon/magneton/shiny.gbapal");
#else
    const u32 gMonFrontPic_Magneton[] = INCBIN_U32("graphics/pokemon/magneton/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Magneton[] = INCBIN_U16("graphics/pokemon/magneton/normal_gba.gbapal");
    const u32 gMonBackPic_Magneton[] = INCBIN_U32("graphics/pokemon/magneton/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Magneton[] = INCBIN_U16("graphics/pokemon/magneton/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Magneton[] = INCBIN_U8("graphics/pokemon/magneton/icon.4bpp");
#else
    const u8 gMonIcon_Magneton[] = INCBIN_U8("graphics/pokemon/magneton/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Magneton[] = INCBIN_U8("graphics/pokemon/magneton/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Magneton[] = INCBIN_COMP("graphics/pokemon/magneton/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Magneton[] = INCBIN_U16("graphics/pokemon/magneton/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Magneton[] = INCBIN_U16("graphics/pokemon/magneton/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_Magnezone[] = INCBIN_U32("graphics/pokemon/magnezone/anim_front.4bpp.smol");
    const u16 gMonPalette_Magnezone[] = INCBIN_U16("graphics/pokemon/magnezone/normal.gbapal");
    const u32 gMonBackPic_Magnezone[] = INCBIN_U32("graphics/pokemon/magnezone/back.4bpp.smol");
    const u16 gMonShinyPalette_Magnezone[] = INCBIN_U16("graphics/pokemon/magnezone/shiny.gbapal");
    const u8 gMonIcon_Magnezone[] = INCBIN_U8("graphics/pokemon/magnezone/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Magnezone[] = INCBIN_U8("graphics/pokemon/magnezone/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Magnezone[] = INCBIN_COMP("graphics/pokemon/magnezone/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Magnezone[] = INCBIN_U16("graphics/pokemon/magnezone/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Magnezone[] = INCBIN_U16("graphics/pokemon/magnezone/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_4_CROSS_EVOS
#endif //P_FAMILY_MAGNEMITE

#if P_FAMILY_FARFETCHD
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Farfetchd[] = INCBIN_U32("graphics/pokemon/farfetchd/anim_front.4bpp.smol");
    const u16 gMonPalette_Farfetchd[] = INCBIN_U16("graphics/pokemon/farfetchd/normal.gbapal");
    const u32 gMonBackPic_Farfetchd[] = INCBIN_U32("graphics/pokemon/farfetchd/back.4bpp.smol");
    const u16 gMonShinyPalette_Farfetchd[] = INCBIN_U16("graphics/pokemon/farfetchd/shiny.gbapal");
#else
    const u32 gMonFrontPic_Farfetchd[] = INCBIN_U32("graphics/pokemon/farfetchd/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Farfetchd[] = INCBIN_U16("graphics/pokemon/farfetchd/normal_gba.gbapal");
    const u32 gMonBackPic_Farfetchd[] = INCBIN_U32("graphics/pokemon/farfetchd/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Farfetchd[] = INCBIN_U16("graphics/pokemon/farfetchd/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Farfetchd[] = INCBIN_U8("graphics/pokemon/farfetchd/icon.4bpp");
#else
    const u8 gMonIcon_Farfetchd[] = INCBIN_U8("graphics/pokemon/farfetchd/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Farfetchd[] = INCBIN_U8("graphics/pokemon/farfetchd/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Farfetchd[] = INCBIN_COMP("graphics/pokemon/farfetchd/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Farfetchd[] = INCBIN_U16("graphics/pokemon/farfetchd/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Farfetchd[] = INCBIN_U16("graphics/pokemon/farfetchd/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Farfetchd[] = INCBIN_U16("graphics/pokemon/farfetchd/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GALARIAN_FORMS
    const u32 gMonFrontPic_FarfetchdGalar[] = INCBIN_U32("graphics/pokemon/farfetchd/galar/front.4bpp.smol");
    const u16 gMonPalette_FarfetchdGalar[] = INCBIN_U16("graphics/pokemon/farfetchd/galar/normal.gbapal");
    const u32 gMonBackPic_FarfetchdGalar[] = INCBIN_U32("graphics/pokemon/farfetchd/galar/back.4bpp.smol");
    const u16 gMonShinyPalette_FarfetchdGalar[] = INCBIN_U16("graphics/pokemon/farfetchd/galar/shiny.gbapal");
    const u8 gMonIcon_FarfetchdGalar[] = INCBIN_U8("graphics/pokemon/farfetchd/galar/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_FarfetchdGalar[] = INCBIN_COMP("graphics/pokemon/farfetchd/galar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_FarfetchdGalar[] = INCBIN_U16("graphics/pokemon/farfetchd/galar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_FarfetchdGalar[] = INCBIN_U16("graphics/pokemon/farfetchd/galar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_Sirfetchd[] = INCBIN_U32("graphics/pokemon/sirfetchd/front.4bpp.smol");
    const u16 gMonPalette_Sirfetchd[] = INCBIN_U16("graphics/pokemon/sirfetchd/normal.gbapal");
    const u32 gMonBackPic_Sirfetchd[] = INCBIN_U32("graphics/pokemon/sirfetchd/back.4bpp.smol");
    const u16 gMonShinyPalette_Sirfetchd[] = INCBIN_U16("graphics/pokemon/sirfetchd/shiny.gbapal");
    const u8 gMonIcon_Sirfetchd[] = INCBIN_U8("graphics/pokemon/sirfetchd/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Sirfetchd[] = INCBIN_U8("graphics/pokemon/sirfetchd/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Sirfetchd[] = INCBIN_COMP("graphics/pokemon/sirfetchd/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Sirfetchd[] = INCBIN_U16("graphics/pokemon/sirfetchd/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Sirfetchd[] = INCBIN_U16("graphics/pokemon/sirfetchd/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_FARFETCHD

#if P_FAMILY_DODUO
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Doduo[] = INCBIN_U32("graphics/pokemon/doduo/anim_front.4bpp.smol");
    const u16 gMonPalette_Doduo[] = INCBIN_U16("graphics/pokemon/doduo/normal.gbapal");
    const u32 gMonBackPic_Doduo[] = INCBIN_U32("graphics/pokemon/doduo/back.4bpp.smol");
    const u16 gMonShinyPalette_Doduo[] = INCBIN_U16("graphics/pokemon/doduo/shiny.gbapal");
#else
    const u32 gMonFrontPic_Doduo[] = INCBIN_U32("graphics/pokemon/doduo/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Doduo[] = INCBIN_U16("graphics/pokemon/doduo/normal_gba.gbapal");
    const u32 gMonBackPic_Doduo[] = INCBIN_U32("graphics/pokemon/doduo/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Doduo[] = INCBIN_U16("graphics/pokemon/doduo/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Doduo[] = INCBIN_U8("graphics/pokemon/doduo/icon.4bpp");
#else
    const u8 gMonIcon_Doduo[] = INCBIN_U8("graphics/pokemon/doduo/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Doduo[] = INCBIN_U8("graphics/pokemon/doduo/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Doduo[] = INCBIN_COMP("graphics/pokemon/doduo/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Doduo[] = INCBIN_U16("graphics/pokemon/doduo/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Doduo[] = INCBIN_U16("graphics/pokemon/doduo/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_DoduoF[] = INCBIN_U32("graphics/pokemon/doduo/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_DoduoF[] = INCBIN_U32("graphics/pokemon/doduo/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_DoduoF[] = INCBIN_COMP("graphics/pokemon/doduo/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Dodrio[] = INCBIN_U32("graphics/pokemon/dodrio/anim_front.4bpp.smol");
    const u16 gMonPalette_Dodrio[] = INCBIN_U16("graphics/pokemon/dodrio/normal.gbapal");
    const u32 gMonBackPic_Dodrio[] = INCBIN_U32("graphics/pokemon/dodrio/back.4bpp.smol");
    const u16 gMonShinyPalette_Dodrio[] = INCBIN_U16("graphics/pokemon/dodrio/shiny.gbapal");
#else
    const u32 gMonFrontPic_Dodrio[] = INCBIN_U32("graphics/pokemon/dodrio/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Dodrio[] = INCBIN_U16("graphics/pokemon/dodrio/normal_gba.gbapal");
    const u32 gMonBackPic_Dodrio[] = INCBIN_U32("graphics/pokemon/dodrio/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Dodrio[] = INCBIN_U16("graphics/pokemon/dodrio/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Dodrio[] = INCBIN_U8("graphics/pokemon/dodrio/icon.4bpp");
#else
    const u8 gMonIcon_Dodrio[] = INCBIN_U8("graphics/pokemon/dodrio/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Dodrio[] = INCBIN_U8("graphics/pokemon/dodrio/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Dodrio[] = INCBIN_COMP("graphics/pokemon/dodrio/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Dodrio[] = INCBIN_U16("graphics/pokemon/dodrio/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Dodrio[] = INCBIN_U16("graphics/pokemon/dodrio/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_DodrioF[] = INCBIN_U32("graphics/pokemon/dodrio/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_DodrioF[] = INCBIN_U32("graphics/pokemon/dodrio/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_DodrioF[] = INCBIN_COMP("graphics/pokemon/dodrio/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES
#endif //P_FAMILY_DODUO

#if P_FAMILY_SEEL
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Seel[] = INCBIN_U32("graphics/pokemon/seel/anim_front.4bpp.smol");
    const u16 gMonPalette_Seel[] = INCBIN_U16("graphics/pokemon/seel/normal.gbapal");
    const u32 gMonBackPic_Seel[] = INCBIN_U32("graphics/pokemon/seel/back.4bpp.smol");
    const u16 gMonShinyPalette_Seel[] = INCBIN_U16("graphics/pokemon/seel/shiny.gbapal");
#else
    const u32 gMonFrontPic_Seel[] = INCBIN_U32("graphics/pokemon/seel/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Seel[] = INCBIN_U16("graphics/pokemon/seel/normal_gba.gbapal");
    const u32 gMonBackPic_Seel[] = INCBIN_U32("graphics/pokemon/seel/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Seel[] = INCBIN_U16("graphics/pokemon/seel/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Seel[] = INCBIN_U8("graphics/pokemon/seel/icon.4bpp");
#else
    const u8 gMonIcon_Seel[] = INCBIN_U8("graphics/pokemon/seel/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Seel[] = INCBIN_U8("graphics/pokemon/seel/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Seel[] = INCBIN_COMP("graphics/pokemon/seel/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Seel[] = INCBIN_U16("graphics/pokemon/seel/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Seel[] = INCBIN_U16("graphics/pokemon/seel/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Dewgong[] = INCBIN_U32("graphics/pokemon/dewgong/anim_front.4bpp.smol");
    const u16 gMonPalette_Dewgong[] = INCBIN_U16("graphics/pokemon/dewgong/normal.gbapal");
    const u32 gMonBackPic_Dewgong[] = INCBIN_U32("graphics/pokemon/dewgong/back.4bpp.smol");
    const u16 gMonShinyPalette_Dewgong[] = INCBIN_U16("graphics/pokemon/dewgong/shiny.gbapal");
#else
    const u32 gMonFrontPic_Dewgong[] = INCBIN_U32("graphics/pokemon/dewgong/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Dewgong[] = INCBIN_U16("graphics/pokemon/dewgong/normal_gba.gbapal");
    const u32 gMonBackPic_Dewgong[] = INCBIN_U32("graphics/pokemon/dewgong/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Dewgong[] = INCBIN_U16("graphics/pokemon/dewgong/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Dewgong[] = INCBIN_U8("graphics/pokemon/dewgong/icon.4bpp");
#else
    const u8 gMonIcon_Dewgong[] = INCBIN_U8("graphics/pokemon/dewgong/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Dewgong[] = INCBIN_U8("graphics/pokemon/dewgong/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Dewgong[] = INCBIN_COMP("graphics/pokemon/dewgong/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Dewgong[] = INCBIN_U16("graphics/pokemon/dewgong/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Dewgong[] = INCBIN_U16("graphics/pokemon/dewgong/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_SEEL

#if P_FAMILY_GRIMER
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Grimer[] = INCBIN_U32("graphics/pokemon/grimer/anim_front.4bpp.smol");
    const u16 gMonPalette_Grimer[] = INCBIN_U16("graphics/pokemon/grimer/normal.gbapal");
    const u32 gMonBackPic_Grimer[] = INCBIN_U32("graphics/pokemon/grimer/back.4bpp.smol");
    const u16 gMonShinyPalette_Grimer[] = INCBIN_U16("graphics/pokemon/grimer/shiny.gbapal");
#else
    const u32 gMonFrontPic_Grimer[] = INCBIN_U32("graphics/pokemon/grimer/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Grimer[] = INCBIN_U16("graphics/pokemon/grimer/normal_gba.gbapal");
    const u32 gMonBackPic_Grimer[] = INCBIN_U32("graphics/pokemon/grimer/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Grimer[] = INCBIN_U16("graphics/pokemon/grimer/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Grimer[] = INCBIN_U8("graphics/pokemon/grimer/icon.4bpp");
#else
    const u8 gMonIcon_Grimer[] = INCBIN_U8("graphics/pokemon/grimer/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Grimer[] = INCBIN_U8("graphics/pokemon/grimer/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Grimer[] = INCBIN_COMP("graphics/pokemon/grimer/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Grimer[] = INCBIN_U16("graphics/pokemon/grimer/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Grimer[] = INCBIN_U16("graphics/pokemon/grimer/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Muk[] = INCBIN_U32("graphics/pokemon/muk/anim_front.4bpp.smol");
    const u16 gMonPalette_Muk[] = INCBIN_U16("graphics/pokemon/muk/normal.gbapal");
    const u32 gMonBackPic_Muk[] = INCBIN_U32("graphics/pokemon/muk/back.4bpp.smol");
    const u16 gMonShinyPalette_Muk[] = INCBIN_U16("graphics/pokemon/muk/shiny.gbapal");
#else
    const u32 gMonFrontPic_Muk[] = INCBIN_U32("graphics/pokemon/muk/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Muk[] = INCBIN_U16("graphics/pokemon/muk/normal_gba.gbapal");
    const u32 gMonBackPic_Muk[] = INCBIN_U32("graphics/pokemon/muk/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Muk[] = INCBIN_U16("graphics/pokemon/muk/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Muk[] = INCBIN_U8("graphics/pokemon/muk/icon.4bpp");
#else
    const u8 gMonIcon_Muk[] = INCBIN_U8("graphics/pokemon/muk/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Muk[] = INCBIN_U8("graphics/pokemon/muk/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Muk[] = INCBIN_COMP("graphics/pokemon/muk/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Muk[] = INCBIN_U16("graphics/pokemon/muk/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Muk[] = INCBIN_U16("graphics/pokemon/muk/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_GrimerAlola[] = INCBIN_U32("graphics/pokemon/grimer/alola/front.4bpp.smol");
    const u16 gMonPalette_GrimerAlola[] = INCBIN_U16("graphics/pokemon/grimer/alola/normal.gbapal");
    const u32 gMonBackPic_GrimerAlola[] = INCBIN_U32("graphics/pokemon/grimer/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_GrimerAlola[] = INCBIN_U16("graphics/pokemon/grimer/alola/shiny.gbapal");
    const u8 gMonIcon_GrimerAlola[] = INCBIN_U8("graphics/pokemon/grimer/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_GrimerAlola[] = INCBIN_COMP("graphics/pokemon/grimer/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_GrimerAlola[] = INCBIN_U16("graphics/pokemon/grimer/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_GrimerAlola[] = INCBIN_U16("graphics/pokemon/grimer/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_MukAlola[] = INCBIN_U32("graphics/pokemon/muk/alola/front.4bpp.smol");
    const u16 gMonPalette_MukAlola[] = INCBIN_U16("graphics/pokemon/muk/alola/normal.gbapal");
    const u32 gMonBackPic_MukAlola[] = INCBIN_U32("graphics/pokemon/muk/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_MukAlola[] = INCBIN_U16("graphics/pokemon/muk/alola/shiny.gbapal");
    const u8 gMonIcon_MukAlola[] = INCBIN_U8("graphics/pokemon/muk/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_MukAlola[] = INCBIN_COMP("graphics/pokemon/muk/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_MukAlola[] = INCBIN_U16("graphics/pokemon/muk/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_MukAlola[] = INCBIN_U16("graphics/pokemon/muk/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_GRIMER

#if P_FAMILY_SHELLDER
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Shellder[] = INCBIN_U32("graphics/pokemon/shellder/anim_front.4bpp.smol");
    const u16 gMonPalette_Shellder[] = INCBIN_U16("graphics/pokemon/shellder/normal.gbapal");
    const u32 gMonBackPic_Shellder[] = INCBIN_U32("graphics/pokemon/shellder/back.4bpp.smol");
    const u16 gMonShinyPalette_Shellder[] = INCBIN_U16("graphics/pokemon/shellder/shiny.gbapal");
#else
    const u32 gMonFrontPic_Shellder[] = INCBIN_U32("graphics/pokemon/shellder/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Shellder[] = INCBIN_U16("graphics/pokemon/shellder/normal_gba.gbapal");
    const u32 gMonBackPic_Shellder[] = INCBIN_U32("graphics/pokemon/shellder/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Shellder[] = INCBIN_U16("graphics/pokemon/shellder/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Shellder[] = INCBIN_U8("graphics/pokemon/shellder/icon.4bpp");
#else
    const u8 gMonIcon_Shellder[] = INCBIN_U8("graphics/pokemon/shellder/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Shellder[] = INCBIN_U8("graphics/pokemon/shellder/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Shellder[] = INCBIN_COMP("graphics/pokemon/shellder/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Shellder[] = INCBIN_U16("graphics/pokemon/shellder/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Shellder[] = INCBIN_U16("graphics/pokemon/shellder/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Cloyster[] = INCBIN_U32("graphics/pokemon/cloyster/anim_front.4bpp.smol");
    const u16 gMonPalette_Cloyster[] = INCBIN_U16("graphics/pokemon/cloyster/normal.gbapal");
    const u32 gMonBackPic_Cloyster[] = INCBIN_U32("graphics/pokemon/cloyster/back.4bpp.smol");
    const u16 gMonShinyPalette_Cloyster[] = INCBIN_U16("graphics/pokemon/cloyster/shiny.gbapal");
#else
    const u32 gMonFrontPic_Cloyster[] = INCBIN_U32("graphics/pokemon/cloyster/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Cloyster[] = INCBIN_U16("graphics/pokemon/cloyster/normal_gba.gbapal");
    const u32 gMonBackPic_Cloyster[] = INCBIN_U32("graphics/pokemon/cloyster/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Cloyster[] = INCBIN_U16("graphics/pokemon/cloyster/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Cloyster[] = INCBIN_U8("graphics/pokemon/cloyster/icon.4bpp");
#else
    const u8 gMonIcon_Cloyster[] = INCBIN_U8("graphics/pokemon/cloyster/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Cloyster[] = INCBIN_U8("graphics/pokemon/cloyster/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Cloyster[] = INCBIN_COMP("graphics/pokemon/cloyster/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Cloyster[] = INCBIN_U16("graphics/pokemon/cloyster/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Cloyster[] = INCBIN_U16("graphics/pokemon/cloyster/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_SHELLDER

#if P_FAMILY_GASTLY
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Gastly[] = INCBIN_U32("graphics/pokemon/gastly/anim_front.4bpp.smol");
    const u16 gMonPalette_Gastly[] = INCBIN_U16("graphics/pokemon/gastly/normal.gbapal");
    const u32 gMonBackPic_Gastly[] = INCBIN_U32("graphics/pokemon/gastly/back.4bpp.smol");
    const u16 gMonShinyPalette_Gastly[] = INCBIN_U16("graphics/pokemon/gastly/shiny.gbapal");
#else
    const u32 gMonFrontPic_Gastly[] = INCBIN_U32("graphics/pokemon/gastly/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Gastly[] = INCBIN_U16("graphics/pokemon/gastly/normal_gba.gbapal");
    const u32 gMonBackPic_Gastly[] = INCBIN_U32("graphics/pokemon/gastly/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Gastly[] = INCBIN_U16("graphics/pokemon/gastly/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Gastly[] = INCBIN_U8("graphics/pokemon/gastly/icon.4bpp");
#else
    const u8 gMonIcon_Gastly[] = INCBIN_U8("graphics/pokemon/gastly/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Gastly[] = INCBIN_U8("graphics/pokemon/gastly/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Gastly[] = INCBIN_COMP("graphics/pokemon/gastly/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Gastly[] = INCBIN_U16("graphics/pokemon/gastly/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Gastly[] = INCBIN_U16("graphics/pokemon/gastly/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Haunter[] = INCBIN_U32("graphics/pokemon/haunter/anim_front.4bpp.smol");
    const u16 gMonPalette_Haunter[] = INCBIN_U16("graphics/pokemon/haunter/normal.gbapal");
    const u32 gMonBackPic_Haunter[] = INCBIN_U32("graphics/pokemon/haunter/back.4bpp.smol");
    const u16 gMonShinyPalette_Haunter[] = INCBIN_U16("graphics/pokemon/haunter/shiny.gbapal");
#else
    const u32 gMonFrontPic_Haunter[] = INCBIN_U32("graphics/pokemon/haunter/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Haunter[] = INCBIN_U16("graphics/pokemon/haunter/normal_gba.gbapal");
    const u32 gMonBackPic_Haunter[] = INCBIN_U32("graphics/pokemon/haunter/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Haunter[] = INCBIN_U16("graphics/pokemon/haunter/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Haunter[] = INCBIN_U8("graphics/pokemon/haunter/icon.4bpp");
#else
    const u8 gMonIcon_Haunter[] = INCBIN_U8("graphics/pokemon/haunter/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Haunter[] = INCBIN_U8("graphics/pokemon/haunter/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Haunter[] = INCBIN_COMP("graphics/pokemon/haunter/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Haunter[] = INCBIN_U16("graphics/pokemon/haunter/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Haunter[] = INCBIN_U16("graphics/pokemon/haunter/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Haunter[] = INCBIN_U16("graphics/pokemon/haunter/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Gengar[] = INCBIN_U32("graphics/pokemon/gengar/anim_front.4bpp.smol");
    const u16 gMonPalette_Gengar[] = INCBIN_U16("graphics/pokemon/gengar/normal.gbapal");
    const u32 gMonBackPic_Gengar[] = INCBIN_U32("graphics/pokemon/gengar/back.4bpp.smol");
    const u16 gMonShinyPalette_Gengar[] = INCBIN_U16("graphics/pokemon/gengar/shiny.gbapal");
#else
    const u32 gMonFrontPic_Gengar[] = INCBIN_U32("graphics/pokemon/gengar/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Gengar[] = INCBIN_U16("graphics/pokemon/gengar/normal_gba.gbapal");
    const u32 gMonBackPic_Gengar[] = INCBIN_U32("graphics/pokemon/gengar/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Gengar[] = INCBIN_U16("graphics/pokemon/gengar/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Gengar[] = INCBIN_U8("graphics/pokemon/gengar/icon.4bpp");
#else
    const u8 gMonIcon_Gengar[] = INCBIN_U8("graphics/pokemon/gengar/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Gengar[] = INCBIN_U8("graphics/pokemon/gengar/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Gengar[] = INCBIN_COMP("graphics/pokemon/gengar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Gengar[] = INCBIN_U16("graphics/pokemon/gengar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Gengar[] = INCBIN_U16("graphics/pokemon/gengar/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Gengar[] = INCBIN_U16("graphics/pokemon/gengar/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_GengarMega[] = INCBIN_U32("graphics/pokemon/gengar/mega/front.4bpp.smol");
    const u16 gMonPalette_GengarMega[] = INCBIN_U16("graphics/pokemon/gengar/mega/normal.gbapal");
    const u32 gMonBackPic_GengarMega[] = INCBIN_U32("graphics/pokemon/gengar/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_GengarMega[] = INCBIN_U16("graphics/pokemon/gengar/mega/shiny.gbapal");
    const u8 gMonIcon_GengarMega[] = INCBIN_U8("graphics/pokemon/gengar/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_GengarMega[] = INCBIN_COMP("graphics/pokemon/gengar/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_GengarMega[] = INCBIN_U16("graphics/pokemon/gengar/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_GengarMega[] = INCBIN_U16("graphics/pokemon/gengar/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_GengarGmax[] = INCBIN_U32("graphics/pokemon/gengar/gmax/front.4bpp.smol");
    const u32 gMonBackPic_GengarGmax[] = INCBIN_U32("graphics/pokemon/gengar/gmax/back.4bpp.smol");
    const u16 gMonPalette_GengarGmax[] = INCBIN_U16("graphics/pokemon/gengar/gmax/normal.gbapal");
    const u16 gMonShinyPalette_GengarGmax[] = INCBIN_U16("graphics/pokemon/gengar/gmax/shiny.gbapal");
    const u8 gMonIcon_GengarGmax[] = INCBIN_U8("graphics/pokemon/gengar/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_GengarGmax[] = INCBIN_COMP("graphics/pokemon/gengar/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_GengarGmax[] = INCBIN_U16("graphics/pokemon/gengar/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_GengarGmax[] = INCBIN_U16("graphics/pokemon/gengar/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS
#endif //P_FAMILY_GASTLY

#if P_FAMILY_ONIX
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Onix[] = INCBIN_U32("graphics/pokemon/onix/anim_front.4bpp.smol");
    const u16 gMonPalette_Onix[] = INCBIN_U16("graphics/pokemon/onix/normal.gbapal");
    const u32 gMonBackPic_Onix[] = INCBIN_U32("graphics/pokemon/onix/back.4bpp.smol");
    const u16 gMonShinyPalette_Onix[] = INCBIN_U16("graphics/pokemon/onix/shiny.gbapal");
#else
    const u32 gMonFrontPic_Onix[] = INCBIN_U32("graphics/pokemon/onix/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Onix[] = INCBIN_U16("graphics/pokemon/onix/normal_gba.gbapal");
    const u32 gMonBackPic_Onix[] = INCBIN_U32("graphics/pokemon/onix/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Onix[] = INCBIN_U16("graphics/pokemon/onix/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Onix[] = INCBIN_U8("graphics/pokemon/onix/icon.4bpp");
#else
    const u8 gMonIcon_Onix[] = INCBIN_U8("graphics/pokemon/onix/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Onix[] = INCBIN_U8("graphics/pokemon/onix/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Onix[] = INCBIN_COMP("graphics/pokemon/onix/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Onix[] = INCBIN_U16("graphics/pokemon/onix/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Onix[] = INCBIN_U16("graphics/pokemon/onix/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Steelix[] = INCBIN_U32("graphics/pokemon/steelix/anim_front.4bpp.smol");
    const u16 gMonPalette_Steelix[] = INCBIN_U16("graphics/pokemon/steelix/normal.gbapal");
    const u32 gMonBackPic_Steelix[] = INCBIN_U32("graphics/pokemon/steelix/back.4bpp.smol");
    const u16 gMonShinyPalette_Steelix[] = INCBIN_U16("graphics/pokemon/steelix/shiny.gbapal");
#else
    const u32 gMonFrontPic_Steelix[] = INCBIN_U32("graphics/pokemon/steelix/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Steelix[] = INCBIN_U16("graphics/pokemon/steelix/normal_gba.gbapal");
    const u32 gMonBackPic_Steelix[] = INCBIN_U32("graphics/pokemon/steelix/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Steelix[] = INCBIN_U16("graphics/pokemon/steelix/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Steelix[] = INCBIN_U8("graphics/pokemon/steelix/icon.4bpp");
#else
    const u8 gMonIcon_Steelix[] = INCBIN_U8("graphics/pokemon/steelix/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Steelix[] = INCBIN_U8("graphics/pokemon/steelix/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Steelix[] = INCBIN_COMP("graphics/pokemon/steelix/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Steelix[] = INCBIN_U16("graphics/pokemon/steelix/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Steelix[] = INCBIN_U16("graphics/pokemon/steelix/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_SteelixF[] = INCBIN_U32("graphics/pokemon/steelix/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_SteelixF[] = INCBIN_U32("graphics/pokemon/steelix/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_SteelixF[] = INCBIN_COMP("graphics/pokemon/steelix/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_SteelixMega[] = INCBIN_U32("graphics/pokemon/steelix/mega/front.4bpp.smol");
    const u16 gMonPalette_SteelixMega[] = INCBIN_U16("graphics/pokemon/steelix/mega/normal.gbapal");
    const u32 gMonBackPic_SteelixMega[] = INCBIN_U32("graphics/pokemon/steelix/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_SteelixMega[] = INCBIN_U16("graphics/pokemon/steelix/mega/shiny.gbapal");
    const u8 gMonIcon_SteelixMega[] = INCBIN_U8("graphics/pokemon/steelix/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_SteelixMega[] = INCBIN_COMP("graphics/pokemon/steelix/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_SteelixMega[] = INCBIN_U16("graphics/pokemon/steelix/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_SteelixMega[] = INCBIN_U16("graphics/pokemon/steelix/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_ONIX

#if P_FAMILY_DROWZEE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Drowzee[] = INCBIN_U32("graphics/pokemon/drowzee/anim_front.4bpp.smol");
    const u16 gMonPalette_Drowzee[] = INCBIN_U16("graphics/pokemon/drowzee/normal.gbapal");
    const u32 gMonBackPic_Drowzee[] = INCBIN_U32("graphics/pokemon/drowzee/back.4bpp.smol");
    const u16 gMonShinyPalette_Drowzee[] = INCBIN_U16("graphics/pokemon/drowzee/shiny.gbapal");
#else
    const u32 gMonFrontPic_Drowzee[] = INCBIN_U32("graphics/pokemon/drowzee/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Drowzee[] = INCBIN_U16("graphics/pokemon/drowzee/normal_gba.gbapal");
    const u32 gMonBackPic_Drowzee[] = INCBIN_U32("graphics/pokemon/drowzee/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Drowzee[] = INCBIN_U16("graphics/pokemon/drowzee/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Drowzee[] = INCBIN_U8("graphics/pokemon/drowzee/icon.4bpp");
#else
    const u8 gMonIcon_Drowzee[] = INCBIN_U8("graphics/pokemon/drowzee/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Drowzee[] = INCBIN_U8("graphics/pokemon/drowzee/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Drowzee[] = INCBIN_COMP("graphics/pokemon/drowzee/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Drowzee[] = INCBIN_U16("graphics/pokemon/drowzee/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Drowzee[] = INCBIN_U16("graphics/pokemon/drowzee/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Hypno[] = INCBIN_U32("graphics/pokemon/hypno/anim_front.4bpp.smol");
    const u16 gMonPalette_Hypno[] = INCBIN_U16("graphics/pokemon/hypno/normal.gbapal");
    const u32 gMonBackPic_Hypno[] = INCBIN_U32("graphics/pokemon/hypno/back.4bpp.smol");
    const u16 gMonShinyPalette_Hypno[] = INCBIN_U16("graphics/pokemon/hypno/shiny.gbapal");
#else
    const u32 gMonFrontPic_Hypno[] = INCBIN_U32("graphics/pokemon/hypno/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Hypno[] = INCBIN_U16("graphics/pokemon/hypno/normal_gba.gbapal");
    const u32 gMonBackPic_Hypno[] = INCBIN_U32("graphics/pokemon/hypno/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Hypno[] = INCBIN_U16("graphics/pokemon/hypno/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Hypno[] = INCBIN_U8("graphics/pokemon/hypno/icon.4bpp");
#else
    const u8 gMonIcon_Hypno[] = INCBIN_U8("graphics/pokemon/hypno/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Hypno[] = INCBIN_U8("graphics/pokemon/hypno/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Hypno[] = INCBIN_COMP("graphics/pokemon/hypno/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Hypno[] = INCBIN_U16("graphics/pokemon/hypno/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Hypno[] = INCBIN_U16("graphics/pokemon/hypno/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_HypnoF[] = INCBIN_U32("graphics/pokemon/hypno/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_HypnoF[] = INCBIN_U32("graphics/pokemon/hypno/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_HypnoF[] = INCBIN_COMP("graphics/pokemon/hypno/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES
#endif //P_FAMILY_DROWZEE

#if P_FAMILY_KRABBY
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Krabby[] = INCBIN_U32("graphics/pokemon/krabby/anim_front.4bpp.smol");
    const u16 gMonPalette_Krabby[] = INCBIN_U16("graphics/pokemon/krabby/normal.gbapal");
    const u32 gMonBackPic_Krabby[] = INCBIN_U32("graphics/pokemon/krabby/back.4bpp.smol");
    const u16 gMonShinyPalette_Krabby[] = INCBIN_U16("graphics/pokemon/krabby/shiny.gbapal");
#else
    const u32 gMonFrontPic_Krabby[] = INCBIN_U32("graphics/pokemon/krabby/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Krabby[] = INCBIN_U16("graphics/pokemon/krabby/normal_gba.gbapal");
    const u32 gMonBackPic_Krabby[] = INCBIN_U32("graphics/pokemon/krabby/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Krabby[] = INCBIN_U16("graphics/pokemon/krabby/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Krabby[] = INCBIN_U8("graphics/pokemon/krabby/icon.4bpp");
#else
    const u8 gMonIcon_Krabby[] = INCBIN_U8("graphics/pokemon/krabby/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Krabby[] = INCBIN_U8("graphics/pokemon/krabby/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Krabby[] = INCBIN_COMP("graphics/pokemon/krabby/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Krabby[] = INCBIN_U16("graphics/pokemon/krabby/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Krabby[] = INCBIN_U16("graphics/pokemon/krabby/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Kingler[] = INCBIN_U32("graphics/pokemon/kingler/anim_front.4bpp.smol");
    const u16 gMonPalette_Kingler[] = INCBIN_U16("graphics/pokemon/kingler/normal.gbapal");
    const u32 gMonBackPic_Kingler[] = INCBIN_U32("graphics/pokemon/kingler/back.4bpp.smol");
    const u16 gMonShinyPalette_Kingler[] = INCBIN_U16("graphics/pokemon/kingler/shiny.gbapal");
#else
    const u32 gMonFrontPic_Kingler[] = INCBIN_U32("graphics/pokemon/kingler/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Kingler[] = INCBIN_U16("graphics/pokemon/kingler/normal_gba.gbapal");
    const u32 gMonBackPic_Kingler[] = INCBIN_U32("graphics/pokemon/kingler/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Kingler[] = INCBIN_U16("graphics/pokemon/kingler/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Kingler[] = INCBIN_U8("graphics/pokemon/kingler/icon.4bpp");
#else
    const u8 gMonIcon_Kingler[] = INCBIN_U8("graphics/pokemon/kingler/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Kingler[] = INCBIN_U8("graphics/pokemon/kingler/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Kingler[] = INCBIN_COMP("graphics/pokemon/kingler/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Kingler[] = INCBIN_U16("graphics/pokemon/kingler/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Kingler[] = INCBIN_U16("graphics/pokemon/kingler/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_KinglerGmax[] = INCBIN_U32("graphics/pokemon/kingler/gmax/front.4bpp.smol");
    const u32 gMonBackPic_KinglerGmax[] = INCBIN_U32("graphics/pokemon/kingler/gmax/back.4bpp.smol");
    const u16 gMonPalette_KinglerGmax[] = INCBIN_U16("graphics/pokemon/kingler/gmax/normal.gbapal");
    const u16 gMonShinyPalette_KinglerGmax[] = INCBIN_U16("graphics/pokemon/kingler/gmax/shiny.gbapal");
    const u8 gMonIcon_KinglerGmax[] = INCBIN_U8("graphics/pokemon/kingler/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_KinglerGmax[] = INCBIN_COMP("graphics/pokemon/kingler/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_KinglerGmax[] = INCBIN_U16("graphics/pokemon/kingler/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_KinglerGmax[] = INCBIN_U16("graphics/pokemon/kingler/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS
#endif //P_FAMILY_KRABBY

#if P_FAMILY_VOLTORB
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Voltorb[] = INCBIN_U32("graphics/pokemon/voltorb/anim_front.4bpp.smol");
    const u16 gMonPalette_Voltorb[] = INCBIN_U16("graphics/pokemon/voltorb/normal.gbapal");
    const u32 gMonBackPic_Voltorb[] = INCBIN_U32("graphics/pokemon/voltorb/back.4bpp.smol");
    const u16 gMonShinyPalette_Voltorb[] = INCBIN_U16("graphics/pokemon/voltorb/shiny.gbapal");
#else
    const u32 gMonFrontPic_Voltorb[] = INCBIN_U32("graphics/pokemon/voltorb/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Voltorb[] = INCBIN_U16("graphics/pokemon/voltorb/normal_gba.gbapal");
    const u32 gMonBackPic_Voltorb[] = INCBIN_U32("graphics/pokemon/voltorb/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Voltorb[] = INCBIN_U16("graphics/pokemon/voltorb/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Voltorb[] = INCBIN_U8("graphics/pokemon/voltorb/icon.4bpp");
#else
    const u8 gMonIcon_Voltorb[] = INCBIN_U8("graphics/pokemon/voltorb/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Voltorb[] = INCBIN_U8("graphics/pokemon/voltorb/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Voltorb[] = INCBIN_COMP("graphics/pokemon/voltorb/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Voltorb[] = INCBIN_U16("graphics/pokemon/voltorb/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Voltorb[] = INCBIN_U16("graphics/pokemon/voltorb/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Electrode[] = INCBIN_U32("graphics/pokemon/electrode/anim_front.4bpp.smol");
    const u16 gMonPalette_Electrode[] = INCBIN_U16("graphics/pokemon/electrode/normal.gbapal");
    const u32 gMonBackPic_Electrode[] = INCBIN_U32("graphics/pokemon/electrode/back.4bpp.smol");
    const u16 gMonShinyPalette_Electrode[] = INCBIN_U16("graphics/pokemon/electrode/shiny.gbapal");
#else
    const u32 gMonFrontPic_Electrode[] = INCBIN_U32("graphics/pokemon/electrode/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Electrode[] = INCBIN_U16("graphics/pokemon/electrode/normal_gba.gbapal");
    const u32 gMonBackPic_Electrode[] = INCBIN_U32("graphics/pokemon/electrode/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Electrode[] = INCBIN_U16("graphics/pokemon/electrode/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Electrode[] = INCBIN_U8("graphics/pokemon/electrode/icon.4bpp");
#else
    const u8 gMonIcon_Electrode[] = INCBIN_U8("graphics/pokemon/electrode/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Electrode[] = INCBIN_U8("graphics/pokemon/electrode/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Electrode[] = INCBIN_COMP("graphics/pokemon/electrode/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Electrode[] = INCBIN_U16("graphics/pokemon/electrode/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Electrode[] = INCBIN_U16("graphics/pokemon/electrode/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_HISUIAN_FORMS
    const u32 gMonFrontPic_VoltorbHisui[] = INCBIN_U32("graphics/pokemon/voltorb/hisui/front.4bpp.smol");
    const u16 gMonPalette_VoltorbHisui[] = INCBIN_U16("graphics/pokemon/voltorb/hisui/normal.gbapal");
    const u32 gMonBackPic_VoltorbHisui[] = INCBIN_U32("graphics/pokemon/voltorb/hisui/back.4bpp.smol");
    const u16 gMonShinyPalette_VoltorbHisui[] = INCBIN_U16("graphics/pokemon/voltorb/hisui/shiny.gbapal");
    const u8 gMonIcon_VoltorbHisui[] = INCBIN_U8("graphics/pokemon/voltorb/hisui/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_VoltorbHisui[] = INCBIN_COMP("graphics/pokemon/voltorb/hisui/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_VoltorbHisui[] = INCBIN_U16("graphics/pokemon/voltorb/hisui/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_VoltorbHisui[] = INCBIN_U16("graphics/pokemon/voltorb/hisui/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_ElectrodeHisui[] = INCBIN_U32("graphics/pokemon/electrode/hisui/front.4bpp.smol");
    const u16 gMonPalette_ElectrodeHisui[] = INCBIN_U16("graphics/pokemon/electrode/hisui/normal.gbapal");
    const u32 gMonBackPic_ElectrodeHisui[] = INCBIN_U32("graphics/pokemon/electrode/hisui/back.4bpp.smol");
    const u16 gMonShinyPalette_ElectrodeHisui[] = INCBIN_U16("graphics/pokemon/electrode/hisui/shiny.gbapal");
    const u8 gMonIcon_ElectrodeHisui[] = INCBIN_U8("graphics/pokemon/electrode/hisui/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_ElectrodeHisui[] = INCBIN_COMP("graphics/pokemon/electrode/hisui/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_ElectrodeHisui[] = INCBIN_U16("graphics/pokemon/electrode/hisui/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_ElectrodeHisui[] = INCBIN_U16("graphics/pokemon/electrode/hisui/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_HISUIAN_FORMS
#endif //P_FAMILY_VOLTORB

#if P_FAMILY_EXEGGCUTE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Exeggcute[] = INCBIN_U32("graphics/pokemon/exeggcute/anim_front.4bpp.smol");
    const u16 gMonPalette_Exeggcute[] = INCBIN_U16("graphics/pokemon/exeggcute/normal.gbapal");
    const u32 gMonBackPic_Exeggcute[] = INCBIN_U32("graphics/pokemon/exeggcute/back.4bpp.smol");
    const u16 gMonShinyPalette_Exeggcute[] = INCBIN_U16("graphics/pokemon/exeggcute/shiny.gbapal");
#else
    const u32 gMonFrontPic_Exeggcute[] = INCBIN_U32("graphics/pokemon/exeggcute/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Exeggcute[] = INCBIN_U16("graphics/pokemon/exeggcute/normal_gba.gbapal");
    const u32 gMonBackPic_Exeggcute[] = INCBIN_U32("graphics/pokemon/exeggcute/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Exeggcute[] = INCBIN_U16("graphics/pokemon/exeggcute/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Exeggcute[] = INCBIN_U8("graphics/pokemon/exeggcute/icon.4bpp");
#else
    const u8 gMonIcon_Exeggcute[] = INCBIN_U8("graphics/pokemon/exeggcute/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Exeggcute[] = INCBIN_U8("graphics/pokemon/exeggcute/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Exeggcute[] = INCBIN_COMP("graphics/pokemon/exeggcute/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Exeggcute[] = INCBIN_U16("graphics/pokemon/exeggcute/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Exeggcute[] = INCBIN_U16("graphics/pokemon/exeggcute/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Exeggutor[] = INCBIN_U32("graphics/pokemon/exeggutor/anim_front.4bpp.smol");
    const u16 gMonPalette_Exeggutor[] = INCBIN_U16("graphics/pokemon/exeggutor/normal.gbapal");
    const u32 gMonBackPic_Exeggutor[] = INCBIN_U32("graphics/pokemon/exeggutor/back.4bpp.smol");
    const u16 gMonShinyPalette_Exeggutor[] = INCBIN_U16("graphics/pokemon/exeggutor/shiny.gbapal");
#else
    const u32 gMonFrontPic_Exeggutor[] = INCBIN_U32("graphics/pokemon/exeggutor/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Exeggutor[] = INCBIN_U16("graphics/pokemon/exeggutor/normal_gba.gbapal");
    const u32 gMonBackPic_Exeggutor[] = INCBIN_U32("graphics/pokemon/exeggutor/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Exeggutor[] = INCBIN_U16("graphics/pokemon/exeggutor/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Exeggutor[] = INCBIN_U8("graphics/pokemon/exeggutor/icon.4bpp");
#else
    const u8 gMonIcon_Exeggutor[] = INCBIN_U8("graphics/pokemon/exeggutor/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Exeggutor[] = INCBIN_U8("graphics/pokemon/exeggutor/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Exeggutor[] = INCBIN_COMP("graphics/pokemon/exeggutor/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Exeggutor[] = INCBIN_U16("graphics/pokemon/exeggutor/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Exeggutor[] = INCBIN_U16("graphics/pokemon/exeggutor/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_ExeggutorAlola[] = INCBIN_U32("graphics/pokemon/exeggutor/alola/anim_front.4bpp.smol");
    const u16 gMonPalette_ExeggutorAlola[] = INCBIN_U16("graphics/pokemon/exeggutor/alola/normal.gbapal");
    const u32 gMonBackPic_ExeggutorAlola[] = INCBIN_U32("graphics/pokemon/exeggutor/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_ExeggutorAlola[] = INCBIN_U16("graphics/pokemon/exeggutor/alola/shiny.gbapal");
    const u8 gMonIcon_ExeggutorAlola[] = INCBIN_U8("graphics/pokemon/exeggutor/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_ExeggutorAlola[] = INCBIN_COMP("graphics/pokemon/exeggutor/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_ExeggutorAlola[] = INCBIN_U16("graphics/pokemon/exeggutor/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_ExeggutorAlola[] = INCBIN_U16("graphics/pokemon/exeggutor/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_EXEGGCUTE

#if P_FAMILY_CUBONE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Cubone[] = INCBIN_U32("graphics/pokemon/cubone/anim_front.4bpp.smol");
    const u16 gMonPalette_Cubone[] = INCBIN_U16("graphics/pokemon/cubone/normal.gbapal");
    const u32 gMonBackPic_Cubone[] = INCBIN_U32("graphics/pokemon/cubone/back.4bpp.smol");
    const u16 gMonShinyPalette_Cubone[] = INCBIN_U16("graphics/pokemon/cubone/shiny.gbapal");
#else
    const u32 gMonFrontPic_Cubone[] = INCBIN_U32("graphics/pokemon/cubone/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Cubone[] = INCBIN_U16("graphics/pokemon/cubone/normal_gba.gbapal");
    const u32 gMonBackPic_Cubone[] = INCBIN_U32("graphics/pokemon/cubone/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Cubone[] = INCBIN_U16("graphics/pokemon/cubone/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Cubone[] = INCBIN_U8("graphics/pokemon/cubone/icon.4bpp");
#else
    const u8 gMonIcon_Cubone[] = INCBIN_U8("graphics/pokemon/cubone/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Cubone[] = INCBIN_U8("graphics/pokemon/cubone/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Cubone[] = INCBIN_COMP("graphics/pokemon/cubone/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Cubone[] = INCBIN_U16("graphics/pokemon/cubone/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Cubone[] = INCBIN_U16("graphics/pokemon/cubone/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Marowak[] = INCBIN_U32("graphics/pokemon/marowak/anim_front.4bpp.smol");
    const u16 gMonPalette_Marowak[] = INCBIN_U16("graphics/pokemon/marowak/normal.gbapal");
    const u32 gMonBackPic_Marowak[] = INCBIN_U32("graphics/pokemon/marowak/back.4bpp.smol");
    const u16 gMonShinyPalette_Marowak[] = INCBIN_U16("graphics/pokemon/marowak/shiny.gbapal");
#else
    const u32 gMonFrontPic_Marowak[] = INCBIN_U32("graphics/pokemon/marowak/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Marowak[] = INCBIN_U16("graphics/pokemon/marowak/normal_gba.gbapal");
    const u32 gMonBackPic_Marowak[] = INCBIN_U32("graphics/pokemon/marowak/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Marowak[] = INCBIN_U16("graphics/pokemon/marowak/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Marowak[] = INCBIN_U8("graphics/pokemon/marowak/icon.4bpp");
#else
    const u8 gMonIcon_Marowak[] = INCBIN_U8("graphics/pokemon/marowak/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Marowak[] = INCBIN_U8("graphics/pokemon/marowak/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Marowak[] = INCBIN_COMP("graphics/pokemon/marowak/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Marowak[] = INCBIN_U16("graphics/pokemon/marowak/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Marowak[] = INCBIN_U16("graphics/pokemon/marowak/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Marowak[] = INCBIN_U16("graphics/pokemon/marowak/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_ALOLAN_FORMS
    const u32 gMonFrontPic_MarowakAlola[] = INCBIN_U32("graphics/pokemon/marowak/alola/front.4bpp.smol");
    const u16 gMonPalette_MarowakAlola[] = INCBIN_U16("graphics/pokemon/marowak/alola/normal.gbapal");
    const u32 gMonBackPic_MarowakAlola[] = INCBIN_U32("graphics/pokemon/marowak/alola/back.4bpp.smol");
    const u16 gMonShinyPalette_MarowakAlola[] = INCBIN_U16("graphics/pokemon/marowak/alola/shiny.gbapal");
    const u8 gMonIcon_MarowakAlola[] = INCBIN_U8("graphics/pokemon/marowak/alola/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_MarowakAlola[] = INCBIN_COMP("graphics/pokemon/marowak/alola/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_MarowakAlola[] = INCBIN_U16("graphics/pokemon/marowak/alola/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_MarowakAlola[] = INCBIN_U16("graphics/pokemon/marowak/alola/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_CUBONE

#if P_FAMILY_HITMONS
#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Tyrogue[] = INCBIN_U32("graphics/pokemon/tyrogue/anim_front.4bpp.smol");
    const u16 gMonPalette_Tyrogue[] = INCBIN_U16("graphics/pokemon/tyrogue/normal.gbapal");
    const u32 gMonBackPic_Tyrogue[] = INCBIN_U32("graphics/pokemon/tyrogue/back.4bpp.smol");
    const u16 gMonShinyPalette_Tyrogue[] = INCBIN_U16("graphics/pokemon/tyrogue/shiny.gbapal");
#else
    const u32 gMonFrontPic_Tyrogue[] = INCBIN_U32("graphics/pokemon/tyrogue/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Tyrogue[] = INCBIN_U16("graphics/pokemon/tyrogue/normal_gba.gbapal");
    const u32 gMonBackPic_Tyrogue[] = INCBIN_U32("graphics/pokemon/tyrogue/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Tyrogue[] = INCBIN_U16("graphics/pokemon/tyrogue/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Tyrogue[] = INCBIN_U8("graphics/pokemon/tyrogue/icon.4bpp");
#else
    const u8 gMonIcon_Tyrogue[] = INCBIN_U8("graphics/pokemon/tyrogue/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Tyrogue[] = INCBIN_U8("graphics/pokemon/tyrogue/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Tyrogue[] = INCBIN_COMP("graphics/pokemon/tyrogue/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Tyrogue[] = INCBIN_U16("graphics/pokemon/tyrogue/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Tyrogue[] = INCBIN_U16("graphics/pokemon/tyrogue/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Hitmonlee[] = INCBIN_U32("graphics/pokemon/hitmonlee/anim_front.4bpp.smol");
    const u16 gMonPalette_Hitmonlee[] = INCBIN_U16("graphics/pokemon/hitmonlee/normal.gbapal");
    const u32 gMonBackPic_Hitmonlee[] = INCBIN_U32("graphics/pokemon/hitmonlee/back.4bpp.smol");
    const u16 gMonShinyPalette_Hitmonlee[] = INCBIN_U16("graphics/pokemon/hitmonlee/shiny.gbapal");
#else
    const u32 gMonFrontPic_Hitmonlee[] = INCBIN_U32("graphics/pokemon/hitmonlee/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Hitmonlee[] = INCBIN_U16("graphics/pokemon/hitmonlee/normal_gba.gbapal");
    const u32 gMonBackPic_Hitmonlee[] = INCBIN_U32("graphics/pokemon/hitmonlee/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Hitmonlee[] = INCBIN_U16("graphics/pokemon/hitmonlee/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Hitmonlee[] = INCBIN_U8("graphics/pokemon/hitmonlee/icon.4bpp");
#else
    const u8 gMonIcon_Hitmonlee[] = INCBIN_U8("graphics/pokemon/hitmonlee/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Hitmonlee[] = INCBIN_U8("graphics/pokemon/hitmonlee/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Hitmonlee[] = INCBIN_COMP("graphics/pokemon/hitmonlee/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Hitmonlee[] = INCBIN_U16("graphics/pokemon/hitmonlee/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Hitmonlee[] = INCBIN_U16("graphics/pokemon/hitmonlee/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Hitmonchan[] = INCBIN_U32("graphics/pokemon/hitmonchan/anim_front.4bpp.smol");
    const u16 gMonPalette_Hitmonchan[] = INCBIN_U16("graphics/pokemon/hitmonchan/normal.gbapal");
    const u32 gMonBackPic_Hitmonchan[] = INCBIN_U32("graphics/pokemon/hitmonchan/back.4bpp.smol");
    const u16 gMonShinyPalette_Hitmonchan[] = INCBIN_U16("graphics/pokemon/hitmonchan/shiny.gbapal");
#else
    const u32 gMonFrontPic_Hitmonchan[] = INCBIN_U32("graphics/pokemon/hitmonchan/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Hitmonchan[] = INCBIN_U16("graphics/pokemon/hitmonchan/normal_gba.gbapal");
    const u32 gMonBackPic_Hitmonchan[] = INCBIN_U32("graphics/pokemon/hitmonchan/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Hitmonchan[] = INCBIN_U16("graphics/pokemon/hitmonchan/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Hitmonchan[] = INCBIN_U8("graphics/pokemon/hitmonchan/icon.4bpp");
#else
    const u8 gMonIcon_Hitmonchan[] = INCBIN_U8("graphics/pokemon/hitmonchan/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Hitmonchan[] = INCBIN_U8("graphics/pokemon/hitmonchan/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Hitmonchan[] = INCBIN_COMP("graphics/pokemon/hitmonchan/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Hitmonchan[] = INCBIN_U16("graphics/pokemon/hitmonchan/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Hitmonchan[] = INCBIN_U16("graphics/pokemon/hitmonchan/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Hitmontop[] = INCBIN_U32("graphics/pokemon/hitmontop/anim_front.4bpp.smol");
    const u16 gMonPalette_Hitmontop[] = INCBIN_U16("graphics/pokemon/hitmontop/normal.gbapal");
    const u32 gMonBackPic_Hitmontop[] = INCBIN_U32("graphics/pokemon/hitmontop/back.4bpp.smol");
    const u16 gMonShinyPalette_Hitmontop[] = INCBIN_U16("graphics/pokemon/hitmontop/shiny.gbapal");
#else
    const u32 gMonFrontPic_Hitmontop[] = INCBIN_U32("graphics/pokemon/hitmontop/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Hitmontop[] = INCBIN_U16("graphics/pokemon/hitmontop/normal_gba.gbapal");
    const u32 gMonBackPic_Hitmontop[] = INCBIN_U32("graphics/pokemon/hitmontop/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Hitmontop[] = INCBIN_U16("graphics/pokemon/hitmontop/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Hitmontop[] = INCBIN_U8("graphics/pokemon/hitmontop/icon.4bpp");
#else
    const u8 gMonIcon_Hitmontop[] = INCBIN_U8("graphics/pokemon/hitmontop/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Hitmontop[] = INCBIN_U8("graphics/pokemon/hitmontop/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Hitmontop[] = INCBIN_COMP("graphics/pokemon/hitmontop/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Hitmontop[] = INCBIN_U16("graphics/pokemon/hitmontop/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Hitmontop[] = INCBIN_U16("graphics/pokemon/hitmontop/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_HITMONS

#if P_FAMILY_LICKITUNG
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Lickitung[] = INCBIN_U32("graphics/pokemon/lickitung/anim_front.4bpp.smol");
    const u16 gMonPalette_Lickitung[] = INCBIN_U16("graphics/pokemon/lickitung/normal.gbapal");
    const u32 gMonBackPic_Lickitung[] = INCBIN_U32("graphics/pokemon/lickitung/back.4bpp.smol");
    const u16 gMonShinyPalette_Lickitung[] = INCBIN_U16("graphics/pokemon/lickitung/shiny.gbapal");
#else
    const u32 gMonFrontPic_Lickitung[] = INCBIN_U32("graphics/pokemon/lickitung/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Lickitung[] = INCBIN_U16("graphics/pokemon/lickitung/normal_gba.gbapal");
    const u32 gMonBackPic_Lickitung[] = INCBIN_U32("graphics/pokemon/lickitung/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Lickitung[] = INCBIN_U16("graphics/pokemon/lickitung/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Lickitung[] = INCBIN_U8("graphics/pokemon/lickitung/icon.4bpp");
#else
    const u8 gMonIcon_Lickitung[] = INCBIN_U8("graphics/pokemon/lickitung/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Lickitung[] = INCBIN_U8("graphics/pokemon/lickitung/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Lickitung[] = INCBIN_COMP("graphics/pokemon/lickitung/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Lickitung[] = INCBIN_U16("graphics/pokemon/lickitung/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Lickitung[] = INCBIN_U16("graphics/pokemon/lickitung/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_Lickilicky[] = INCBIN_U32("graphics/pokemon/lickilicky/anim_front.4bpp.smol");
    const u16 gMonPalette_Lickilicky[] = INCBIN_U16("graphics/pokemon/lickilicky/normal.gbapal");
    const u32 gMonBackPic_Lickilicky[] = INCBIN_U32("graphics/pokemon/lickilicky/back.4bpp.smol");
    const u16 gMonShinyPalette_Lickilicky[] = INCBIN_U16("graphics/pokemon/lickilicky/shiny.gbapal");
    const u8 gMonIcon_Lickilicky[] = INCBIN_U8("graphics/pokemon/lickilicky/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Lickilicky[] = INCBIN_U8("graphics/pokemon/lickilicky/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Lickilicky[] = INCBIN_COMP("graphics/pokemon/lickilicky/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Lickilicky[] = INCBIN_U16("graphics/pokemon/lickilicky/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Lickilicky[] = INCBIN_U16("graphics/pokemon/lickilicky/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_4_CROSS_EVOS
#endif //P_FAMILY_LICKITUNG

#if P_FAMILY_KOFFING
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Koffing[] = INCBIN_U32("graphics/pokemon/koffing/anim_front.4bpp.smol");
    const u16 gMonPalette_Koffing[] = INCBIN_U16("graphics/pokemon/koffing/normal.gbapal");
    const u32 gMonBackPic_Koffing[] = INCBIN_U32("graphics/pokemon/koffing/back.4bpp.smol");
    const u16 gMonShinyPalette_Koffing[] = INCBIN_U16("graphics/pokemon/koffing/shiny.gbapal");
#else
    const u32 gMonFrontPic_Koffing[] = INCBIN_U32("graphics/pokemon/koffing/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Koffing[] = INCBIN_U16("graphics/pokemon/koffing/normal_gba.gbapal");
    const u32 gMonBackPic_Koffing[] = INCBIN_U32("graphics/pokemon/koffing/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Koffing[] = INCBIN_U16("graphics/pokemon/koffing/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Koffing[] = INCBIN_U8("graphics/pokemon/koffing/icon.4bpp");
#else
    const u8 gMonIcon_Koffing[] = INCBIN_U8("graphics/pokemon/koffing/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Koffing[] = INCBIN_U8("graphics/pokemon/koffing/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Koffing[] = INCBIN_COMP("graphics/pokemon/koffing/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Koffing[] = INCBIN_U16("graphics/pokemon/koffing/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Koffing[] = INCBIN_U16("graphics/pokemon/koffing/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Weezing[] = INCBIN_U32("graphics/pokemon/weezing/anim_front.4bpp.smol");
    const u16 gMonPalette_Weezing[] = INCBIN_U16("graphics/pokemon/weezing/normal.gbapal");
    const u32 gMonBackPic_Weezing[] = INCBIN_U32("graphics/pokemon/weezing/back.4bpp.smol");
    const u16 gMonShinyPalette_Weezing[] = INCBIN_U16("graphics/pokemon/weezing/shiny.gbapal");
#else
    const u32 gMonFrontPic_Weezing[] = INCBIN_U32("graphics/pokemon/weezing/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Weezing[] = INCBIN_U16("graphics/pokemon/weezing/normal_gba.gbapal");
    const u32 gMonBackPic_Weezing[] = INCBIN_U32("graphics/pokemon/weezing/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Weezing[] = INCBIN_U16("graphics/pokemon/weezing/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Weezing[] = INCBIN_U8("graphics/pokemon/weezing/icon.4bpp");
#else
    const u8 gMonIcon_Weezing[] = INCBIN_U8("graphics/pokemon/weezing/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Weezing[] = INCBIN_U8("graphics/pokemon/weezing/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Weezing[] = INCBIN_COMP("graphics/pokemon/weezing/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Weezing[] = INCBIN_U16("graphics/pokemon/weezing/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Weezing[] = INCBIN_U16("graphics/pokemon/weezing/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GALARIAN_FORMS
    const u32 gMonFrontPic_WeezingGalar[] = INCBIN_U32("graphics/pokemon/weezing/galar/front.4bpp.smol");
    const u16 gMonPalette_WeezingGalar[] = INCBIN_U16("graphics/pokemon/weezing/galar/normal.gbapal");
    const u32 gMonBackPic_WeezingGalar[] = INCBIN_U32("graphics/pokemon/weezing/galar/back.4bpp.smol");
    const u16 gMonShinyPalette_WeezingGalar[] = INCBIN_U16("graphics/pokemon/weezing/galar/shiny.gbapal");
    const u8 gMonIcon_WeezingGalar[] = INCBIN_U8("graphics/pokemon/weezing/galar/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_WeezingGalar[] = INCBIN_COMP("graphics/pokemon/weezing/galar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_WeezingGalar[] = INCBIN_U16("graphics/pokemon/weezing/galar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_WeezingGalar[] = INCBIN_U16("graphics/pokemon/weezing/galar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_KOFFING

#if P_FAMILY_RHYHORN
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Rhyhorn[] = INCBIN_U32("graphics/pokemon/rhyhorn/anim_front.4bpp.smol");
    const u16 gMonPalette_Rhyhorn[] = INCBIN_U16("graphics/pokemon/rhyhorn/normal.gbapal");
    const u32 gMonBackPic_Rhyhorn[] = INCBIN_U32("graphics/pokemon/rhyhorn/back.4bpp.smol");
    const u16 gMonShinyPalette_Rhyhorn[] = INCBIN_U16("graphics/pokemon/rhyhorn/shiny.gbapal");
#else
    const u32 gMonFrontPic_Rhyhorn[] = INCBIN_U32("graphics/pokemon/rhyhorn/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Rhyhorn[] = INCBIN_U16("graphics/pokemon/rhyhorn/normal_gba.gbapal");
    const u32 gMonBackPic_Rhyhorn[] = INCBIN_U32("graphics/pokemon/rhyhorn/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Rhyhorn[] = INCBIN_U16("graphics/pokemon/rhyhorn/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Rhyhorn[] = INCBIN_U8("graphics/pokemon/rhyhorn/icon.4bpp");
#else
    const u8 gMonIcon_Rhyhorn[] = INCBIN_U8("graphics/pokemon/rhyhorn/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Rhyhorn[] = INCBIN_U8("graphics/pokemon/rhyhorn/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Rhyhorn[] = INCBIN_COMP("graphics/pokemon/rhyhorn/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Rhyhorn[] = INCBIN_U16("graphics/pokemon/rhyhorn/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Rhyhorn[] = INCBIN_U16("graphics/pokemon/rhyhorn/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_RhyhornF[] = INCBIN_U32("graphics/pokemon/rhyhorn/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_RhyhornF[] = INCBIN_U32("graphics/pokemon/rhyhorn/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RhyhornF[] = INCBIN_COMP("graphics/pokemon/rhyhorn/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Rhydon[] = INCBIN_U32("graphics/pokemon/rhydon/anim_front.4bpp.smol");
    const u16 gMonPalette_Rhydon[] = INCBIN_U16("graphics/pokemon/rhydon/normal.gbapal");
    const u32 gMonBackPic_Rhydon[] = INCBIN_U32("graphics/pokemon/rhydon/back.4bpp.smol");
    const u16 gMonShinyPalette_Rhydon[] = INCBIN_U16("graphics/pokemon/rhydon/shiny.gbapal");
#else
    const u32 gMonFrontPic_Rhydon[] = INCBIN_U32("graphics/pokemon/rhydon/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Rhydon[] = INCBIN_U16("graphics/pokemon/rhydon/normal_gba.gbapal");
    const u32 gMonBackPic_Rhydon[] = INCBIN_U32("graphics/pokemon/rhydon/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Rhydon[] = INCBIN_U16("graphics/pokemon/rhydon/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Rhydon[] = INCBIN_U8("graphics/pokemon/rhydon/icon.4bpp");
#else
    const u8 gMonIcon_Rhydon[] = INCBIN_U8("graphics/pokemon/rhydon/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Rhydon[] = INCBIN_U8("graphics/pokemon/rhydon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Rhydon[] = INCBIN_COMP("graphics/pokemon/rhydon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Rhydon[] = INCBIN_U16("graphics/pokemon/rhydon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Rhydon[] = INCBIN_U16("graphics/pokemon/rhydon/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_RhydonF[] = INCBIN_U32("graphics/pokemon/rhydon/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_RhydonF[] = INCBIN_U32("graphics/pokemon/rhydon/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RhydonF[] = INCBIN_COMP("graphics/pokemon/rhydon/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_Rhyperior[] = INCBIN_U32("graphics/pokemon/rhyperior/anim_front.4bpp.smol");
    const u16 gMonPalette_Rhyperior[] = INCBIN_U16("graphics/pokemon/rhyperior/normal.gbapal");
    const u32 gMonBackPic_Rhyperior[] = INCBIN_U32("graphics/pokemon/rhyperior/back.4bpp.smol");
    const u16 gMonShinyPalette_Rhyperior[] = INCBIN_U16("graphics/pokemon/rhyperior/shiny.gbapal");
    const u8 gMonIcon_Rhyperior[] = INCBIN_U8("graphics/pokemon/rhyperior/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Rhyperior[] = INCBIN_U8("graphics/pokemon/rhyperior/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Rhyperior[] = INCBIN_COMP("graphics/pokemon/rhyperior/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Rhyperior[] = INCBIN_U16("graphics/pokemon/rhyperior/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Rhyperior[] = INCBIN_U16("graphics/pokemon/rhyperior/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_RhyperiorF[] = INCBIN_U32("graphics/pokemon/rhyperior/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_RhyperiorF[] = INCBIN_U32("graphics/pokemon/rhyperior/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_RhyperiorF[] = INCBIN_COMP("graphics/pokemon/rhyperior/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES
#endif //P_GEN_4_CROSS_EVOS
#endif //P_FAMILY_RHYHORN

#if P_FAMILY_CHANSEY
#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_Happiny[] = INCBIN_U32("graphics/pokemon/happiny/anim_front.4bpp.smol");
    const u16 gMonPalette_Happiny[] = INCBIN_U16("graphics/pokemon/happiny/normal.gbapal");
    const u32 gMonBackPic_Happiny[] = INCBIN_U32("graphics/pokemon/happiny/back.4bpp.smol");
    const u16 gMonShinyPalette_Happiny[] = INCBIN_U16("graphics/pokemon/happiny/shiny.gbapal");
    const u8 gMonIcon_Happiny[] = INCBIN_U8("graphics/pokemon/happiny/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Happiny[] = INCBIN_U8("graphics/pokemon/happiny/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Happiny[] = INCBIN_COMP("graphics/pokemon/happiny/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Happiny[] = INCBIN_U16("graphics/pokemon/happiny/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Happiny[] = INCBIN_U16("graphics/pokemon/happiny/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_4_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Chansey[] = INCBIN_U32("graphics/pokemon/chansey/anim_front.4bpp.smol");
    const u16 gMonPalette_Chansey[] = INCBIN_U16("graphics/pokemon/chansey/normal.gbapal");
    const u32 gMonBackPic_Chansey[] = INCBIN_U32("graphics/pokemon/chansey/back.4bpp.smol");
    const u16 gMonShinyPalette_Chansey[] = INCBIN_U16("graphics/pokemon/chansey/shiny.gbapal");
#else
    const u32 gMonFrontPic_Chansey[] = INCBIN_U32("graphics/pokemon/chansey/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Chansey[] = INCBIN_U16("graphics/pokemon/chansey/normal_gba.gbapal");
    const u32 gMonBackPic_Chansey[] = INCBIN_U32("graphics/pokemon/chansey/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Chansey[] = INCBIN_U16("graphics/pokemon/chansey/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Chansey[] = INCBIN_U8("graphics/pokemon/chansey/icon.4bpp");
#else
    const u8 gMonIcon_Chansey[] = INCBIN_U8("graphics/pokemon/chansey/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Chansey[] = INCBIN_U8("graphics/pokemon/chansey/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Chansey[] = INCBIN_COMP("graphics/pokemon/chansey/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Chansey[] = INCBIN_U16("graphics/pokemon/chansey/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Chansey[] = INCBIN_U16("graphics/pokemon/chansey/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Blissey[] = INCBIN_U32("graphics/pokemon/blissey/anim_front.4bpp.smol");
    const u16 gMonPalette_Blissey[] = INCBIN_U16("graphics/pokemon/blissey/normal.gbapal");
    const u32 gMonBackPic_Blissey[] = INCBIN_U32("graphics/pokemon/blissey/back.4bpp.smol");
    const u16 gMonShinyPalette_Blissey[] = INCBIN_U16("graphics/pokemon/blissey/shiny.gbapal");
#else
    const u32 gMonFrontPic_Blissey[] = INCBIN_U32("graphics/pokemon/blissey/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Blissey[] = INCBIN_U16("graphics/pokemon/blissey/normal_gba.gbapal");
    const u32 gMonBackPic_Blissey[] = INCBIN_U32("graphics/pokemon/blissey/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Blissey[] = INCBIN_U16("graphics/pokemon/blissey/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Blissey[] = INCBIN_U8("graphics/pokemon/blissey/icon.4bpp");
#else
    const u8 gMonIcon_Blissey[] = INCBIN_U8("graphics/pokemon/blissey/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Blissey[] = INCBIN_U8("graphics/pokemon/blissey/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Blissey[] = INCBIN_COMP("graphics/pokemon/blissey/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Blissey[] = INCBIN_U16("graphics/pokemon/blissey/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Blissey[] = INCBIN_U16("graphics/pokemon/blissey/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_CHANSEY

#if P_FAMILY_TANGELA
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Tangela[] = INCBIN_U32("graphics/pokemon/tangela/anim_front.4bpp.smol");
    const u16 gMonPalette_Tangela[] = INCBIN_U16("graphics/pokemon/tangela/normal.gbapal");
    const u32 gMonBackPic_Tangela[] = INCBIN_U32("graphics/pokemon/tangela/back.4bpp.smol");
    const u16 gMonShinyPalette_Tangela[] = INCBIN_U16("graphics/pokemon/tangela/shiny.gbapal");
#else
    const u32 gMonFrontPic_Tangela[] = INCBIN_U32("graphics/pokemon/tangela/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Tangela[] = INCBIN_U16("graphics/pokemon/tangela/normal_gba.gbapal");
    const u32 gMonBackPic_Tangela[] = INCBIN_U32("graphics/pokemon/tangela/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Tangela[] = INCBIN_U16("graphics/pokemon/tangela/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Tangela[] = INCBIN_U8("graphics/pokemon/tangela/icon.4bpp");
#else
    const u8 gMonIcon_Tangela[] = INCBIN_U8("graphics/pokemon/tangela/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Tangela[] = INCBIN_U8("graphics/pokemon/tangela/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Tangela[] = INCBIN_COMP("graphics/pokemon/tangela/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Tangela[] = INCBIN_U16("graphics/pokemon/tangela/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Tangela[] = INCBIN_U16("graphics/pokemon/tangela/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_Tangrowth[] = INCBIN_U32("graphics/pokemon/tangrowth/anim_front.4bpp.smol");
    const u16 gMonPalette_Tangrowth[] = INCBIN_U16("graphics/pokemon/tangrowth/normal.gbapal");
    const u32 gMonBackPic_Tangrowth[] = INCBIN_U32("graphics/pokemon/tangrowth/back.4bpp.smol");
    const u16 gMonShinyPalette_Tangrowth[] = INCBIN_U16("graphics/pokemon/tangrowth/shiny.gbapal");
    const u8 gMonIcon_Tangrowth[] = INCBIN_U8("graphics/pokemon/tangrowth/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Tangrowth[] = INCBIN_U8("graphics/pokemon/tangrowth/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Tangrowth[] = INCBIN_COMP("graphics/pokemon/tangrowth/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Tangrowth[] = INCBIN_U16("graphics/pokemon/tangrowth/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Tangrowth[] = INCBIN_U16("graphics/pokemon/tangrowth/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_TangrowthF[] = INCBIN_U32("graphics/pokemon/tangrowth/anim_frontf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_TangrowthF[] = INCBIN_COMP("graphics/pokemon/tangrowth/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES
#endif //P_GEN_4_CROSS_EVOS
#endif //P_FAMILY_TANGELA

#if P_FAMILY_KANGASKHAN
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Kangaskhan[] = INCBIN_U32("graphics/pokemon/kangaskhan/anim_front.4bpp.smol");
    const u16 gMonPalette_Kangaskhan[] = INCBIN_U16("graphics/pokemon/kangaskhan/normal.gbapal");
    const u32 gMonBackPic_Kangaskhan[] = INCBIN_U32("graphics/pokemon/kangaskhan/back.4bpp.smol");
    const u16 gMonShinyPalette_Kangaskhan[] = INCBIN_U16("graphics/pokemon/kangaskhan/shiny.gbapal");
#else
    const u32 gMonFrontPic_Kangaskhan[] = INCBIN_U32("graphics/pokemon/kangaskhan/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Kangaskhan[] = INCBIN_U16("graphics/pokemon/kangaskhan/normal_gba.gbapal");
    const u32 gMonBackPic_Kangaskhan[] = INCBIN_U32("graphics/pokemon/kangaskhan/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Kangaskhan[] = INCBIN_U16("graphics/pokemon/kangaskhan/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Kangaskhan[] = INCBIN_U8("graphics/pokemon/kangaskhan/icon.4bpp");
#else
    const u8 gMonIcon_Kangaskhan[] = INCBIN_U8("graphics/pokemon/kangaskhan/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Kangaskhan[] = INCBIN_U8("graphics/pokemon/kangaskhan/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Kangaskhan[] = INCBIN_COMP("graphics/pokemon/kangaskhan/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Kangaskhan[] = INCBIN_U16("graphics/pokemon/kangaskhan/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Kangaskhan[] = INCBIN_U16("graphics/pokemon/kangaskhan/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_KangaskhanMega[] = INCBIN_U32("graphics/pokemon/kangaskhan/mega/front.4bpp.smol");
    const u16 gMonPalette_KangaskhanMega[] = INCBIN_U16("graphics/pokemon/kangaskhan/mega/normal.gbapal");
    const u32 gMonBackPic_KangaskhanMega[] = INCBIN_U32("graphics/pokemon/kangaskhan/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_KangaskhanMega[] = INCBIN_U16("graphics/pokemon/kangaskhan/mega/shiny.gbapal");
    const u8 gMonIcon_KangaskhanMega[] = INCBIN_U8("graphics/pokemon/kangaskhan/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_KangaskhanMega[] = INCBIN_COMP("graphics/pokemon/kangaskhan/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_KangaskhanMega[] = INCBIN_U16("graphics/pokemon/kangaskhan/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_KangaskhanMega[] = INCBIN_U16("graphics/pokemon/kangaskhan/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS
#endif //P_FAMILY_KANGASKHAN

#if P_FAMILY_HORSEA
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Horsea[] = INCBIN_U32("graphics/pokemon/horsea/anim_front.4bpp.smol");
    const u16 gMonPalette_Horsea[] = INCBIN_U16("graphics/pokemon/horsea/normal.gbapal");
    const u32 gMonBackPic_Horsea[] = INCBIN_U32("graphics/pokemon/horsea/back.4bpp.smol");
    const u16 gMonShinyPalette_Horsea[] = INCBIN_U16("graphics/pokemon/horsea/shiny.gbapal");
#else
    const u32 gMonFrontPic_Horsea[] = INCBIN_U32("graphics/pokemon/horsea/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Horsea[] = INCBIN_U16("graphics/pokemon/horsea/normal_gba.gbapal");
    const u32 gMonBackPic_Horsea[] = INCBIN_U32("graphics/pokemon/horsea/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Horsea[] = INCBIN_U16("graphics/pokemon/horsea/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Horsea[] = INCBIN_U8("graphics/pokemon/horsea/icon.4bpp");
#else
    const u8 gMonIcon_Horsea[] = INCBIN_U8("graphics/pokemon/horsea/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Horsea[] = INCBIN_U8("graphics/pokemon/horsea/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Horsea[] = INCBIN_COMP("graphics/pokemon/horsea/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Horsea[] = INCBIN_U16("graphics/pokemon/horsea/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Horsea[] = INCBIN_U16("graphics/pokemon/horsea/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Seadra[] = INCBIN_U32("graphics/pokemon/seadra/anim_front.4bpp.smol");
    const u16 gMonPalette_Seadra[] = INCBIN_U16("graphics/pokemon/seadra/normal.gbapal");
    const u32 gMonBackPic_Seadra[] = INCBIN_U32("graphics/pokemon/seadra/back.4bpp.smol");
    const u16 gMonShinyPalette_Seadra[] = INCBIN_U16("graphics/pokemon/seadra/shiny.gbapal");
#else
    const u32 gMonFrontPic_Seadra[] = INCBIN_U32("graphics/pokemon/seadra/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Seadra[] = INCBIN_U16("graphics/pokemon/seadra/normal_gba.gbapal");
    const u32 gMonBackPic_Seadra[] = INCBIN_U32("graphics/pokemon/seadra/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Seadra[] = INCBIN_U16("graphics/pokemon/seadra/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Seadra[] = INCBIN_U8("graphics/pokemon/seadra/icon.4bpp");
#else
    const u8 gMonIcon_Seadra[] = INCBIN_U8("graphics/pokemon/seadra/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Seadra[] = INCBIN_U8("graphics/pokemon/seadra/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Seadra[] = INCBIN_COMP("graphics/pokemon/seadra/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Seadra[] = INCBIN_U16("graphics/pokemon/seadra/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Seadra[] = INCBIN_U16("graphics/pokemon/seadra/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Kingdra[] = INCBIN_U32("graphics/pokemon/kingdra/anim_front.4bpp.smol");
    const u16 gMonPalette_Kingdra[] = INCBIN_U16("graphics/pokemon/kingdra/normal.gbapal");
    const u32 gMonBackPic_Kingdra[] = INCBIN_U32("graphics/pokemon/kingdra/back.4bpp.smol");
    const u16 gMonShinyPalette_Kingdra[] = INCBIN_U16("graphics/pokemon/kingdra/shiny.gbapal");
#else
    const u32 gMonFrontPic_Kingdra[] = INCBIN_U32("graphics/pokemon/kingdra/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Kingdra[] = INCBIN_U16("graphics/pokemon/kingdra/normal_gba.gbapal");
    const u32 gMonBackPic_Kingdra[] = INCBIN_U32("graphics/pokemon/kingdra/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Kingdra[] = INCBIN_U16("graphics/pokemon/kingdra/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Kingdra[] = INCBIN_U8("graphics/pokemon/kingdra/icon.4bpp");
#else
    const u8 gMonIcon_Kingdra[] = INCBIN_U8("graphics/pokemon/kingdra/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Kingdra[] = INCBIN_U8("graphics/pokemon/kingdra/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Kingdra[] = INCBIN_COMP("graphics/pokemon/kingdra/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Kingdra[] = INCBIN_U16("graphics/pokemon/kingdra/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Kingdra[] = INCBIN_U16("graphics/pokemon/kingdra/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_HORSEA

#if P_FAMILY_GOLDEEN
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Goldeen[] = INCBIN_U32("graphics/pokemon/goldeen/anim_front.4bpp.smol");
    const u16 gMonPalette_Goldeen[] = INCBIN_U16("graphics/pokemon/goldeen/normal.gbapal");
    const u32 gMonBackPic_Goldeen[] = INCBIN_U32("graphics/pokemon/goldeen/back.4bpp.smol");
    const u16 gMonShinyPalette_Goldeen[] = INCBIN_U16("graphics/pokemon/goldeen/shiny.gbapal");
#else
    const u32 gMonFrontPic_Goldeen[] = INCBIN_U32("graphics/pokemon/goldeen/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Goldeen[] = INCBIN_U16("graphics/pokemon/goldeen/normal_gba.gbapal");
    const u32 gMonBackPic_Goldeen[] = INCBIN_U32("graphics/pokemon/goldeen/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Goldeen[] = INCBIN_U16("graphics/pokemon/goldeen/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Goldeen[] = INCBIN_U8("graphics/pokemon/goldeen/icon.4bpp");
#else
    const u8 gMonIcon_Goldeen[] = INCBIN_U8("graphics/pokemon/goldeen/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Goldeen[] = INCBIN_U8("graphics/pokemon/goldeen/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Goldeen[] = INCBIN_COMP("graphics/pokemon/goldeen/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Goldeen[] = INCBIN_U16("graphics/pokemon/goldeen/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Goldeen[] = INCBIN_U16("graphics/pokemon/goldeen/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_GoldeenF[] = INCBIN_U32("graphics/pokemon/goldeen/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_GoldeenF[] = INCBIN_U32("graphics/pokemon/goldeen/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_GoldeenF[] = INCBIN_COMP("graphics/pokemon/goldeen/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Seaking[] = INCBIN_U32("graphics/pokemon/seaking/anim_front.4bpp.smol");
    const u16 gMonPalette_Seaking[] = INCBIN_U16("graphics/pokemon/seaking/normal.gbapal");
    const u32 gMonBackPic_Seaking[] = INCBIN_U32("graphics/pokemon/seaking/back.4bpp.smol");
    const u16 gMonShinyPalette_Seaking[] = INCBIN_U16("graphics/pokemon/seaking/shiny.gbapal");
#else
    const u32 gMonFrontPic_Seaking[] = INCBIN_U32("graphics/pokemon/seaking/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Seaking[] = INCBIN_U16("graphics/pokemon/seaking/normal_gba.gbapal");
    const u32 gMonBackPic_Seaking[] = INCBIN_U32("graphics/pokemon/seaking/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Seaking[] = INCBIN_U16("graphics/pokemon/seaking/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Seaking[] = INCBIN_U8("graphics/pokemon/seaking/icon.4bpp");
#else
    const u8 gMonIcon_Seaking[] = INCBIN_U8("graphics/pokemon/seaking/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Seaking[] = INCBIN_U8("graphics/pokemon/seaking/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Seaking[] = INCBIN_COMP("graphics/pokemon/seaking/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Seaking[] = INCBIN_U16("graphics/pokemon/seaking/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Seaking[] = INCBIN_U16("graphics/pokemon/seaking/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_SeakingF[] = INCBIN_U32("graphics/pokemon/seaking/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_SeakingF[] = INCBIN_U32("graphics/pokemon/seaking/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_SeakingF[] = INCBIN_COMP("graphics/pokemon/seaking/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES
#endif //P_FAMILY_GOLDEEN

#if P_FAMILY_STARYU
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Staryu[] = INCBIN_U32("graphics/pokemon/staryu/anim_front.4bpp.smol");
    const u16 gMonPalette_Staryu[] = INCBIN_U16("graphics/pokemon/staryu/normal.gbapal");
    const u32 gMonBackPic_Staryu[] = INCBIN_U32("graphics/pokemon/staryu/back.4bpp.smol");
    const u16 gMonShinyPalette_Staryu[] = INCBIN_U16("graphics/pokemon/staryu/shiny.gbapal");
#else
    const u32 gMonFrontPic_Staryu[] = INCBIN_U32("graphics/pokemon/staryu/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Staryu[] = INCBIN_U16("graphics/pokemon/staryu/normal_gba.gbapal");
    const u32 gMonBackPic_Staryu[] = INCBIN_U32("graphics/pokemon/staryu/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Staryu[] = INCBIN_U16("graphics/pokemon/staryu/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Staryu[] = INCBIN_U8("graphics/pokemon/staryu/icon.4bpp");
#else
    const u8 gMonIcon_Staryu[] = INCBIN_U8("graphics/pokemon/staryu/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Staryu[] = INCBIN_U8("graphics/pokemon/staryu/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Staryu[] = INCBIN_COMP("graphics/pokemon/staryu/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Staryu[] = INCBIN_U16("graphics/pokemon/staryu/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Staryu[] = INCBIN_U16("graphics/pokemon/staryu/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Starmie[] = INCBIN_U32("graphics/pokemon/starmie/anim_front.4bpp.smol");
    const u16 gMonPalette_Starmie[] = INCBIN_U16("graphics/pokemon/starmie/normal.gbapal");
    const u32 gMonBackPic_Starmie[] = INCBIN_U32("graphics/pokemon/starmie/back.4bpp.smol");
    const u16 gMonShinyPalette_Starmie[] = INCBIN_U16("graphics/pokemon/starmie/shiny.gbapal");
#else
    const u32 gMonFrontPic_Starmie[] = INCBIN_U32("graphics/pokemon/starmie/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Starmie[] = INCBIN_U16("graphics/pokemon/starmie/normal_gba.gbapal");
    const u32 gMonBackPic_Starmie[] = INCBIN_U32("graphics/pokemon/starmie/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Starmie[] = INCBIN_U16("graphics/pokemon/starmie/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Starmie[] = INCBIN_U8("graphics/pokemon/starmie/icon.4bpp");
#else
    const u8 gMonIcon_Starmie[] = INCBIN_U8("graphics/pokemon/starmie/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Starmie[] = INCBIN_U8("graphics/pokemon/starmie/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Starmie[] = INCBIN_COMP("graphics/pokemon/starmie/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Starmie[] = INCBIN_U16("graphics/pokemon/starmie/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Starmie[] = INCBIN_U16("graphics/pokemon/starmie/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_9_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_StarmieMega[] = INCBIN_U32("graphics/pokemon/starmie/mega/front.4bpp.smol");
    const u16 gMonPalette_StarmieMega[] = INCBIN_U16("graphics/pokemon/starmie/mega/normal.gbapal");
    const u32 gMonBackPic_StarmieMega[] = INCBIN_U32("graphics/pokemon/starmie/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_StarmieMega[] = INCBIN_U16("graphics/pokemon/starmie/mega/shiny.gbapal");
    const u8 gMonIcon_StarmieMega[] = INCBIN_U8("graphics/pokemon/starmie/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
//    const u32 gObjectEventPic_StarmieMega[] = INCBIN_COMP("graphics/pokemon/starmie/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
//    const u16 gOverworldPalette_StarmieMega[] = INCBIN_U16("graphics/pokemon/starmie/mega/overworld_normal.gbapal");
//    const u16 gShinyOverworldPalette_StarmieMega[] = INCBIN_U16("graphics/pokemon/starmie/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_GEN_9_MEGA_EVOLUTIONS
#endif //P_FAMILY_STARYU

#if P_FAMILY_MR_MIME
#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_MimeJr[] = INCBIN_U32("graphics/pokemon/mime_jr/anim_front.4bpp.smol");
    const u16 gMonPalette_MimeJr[] = INCBIN_U16("graphics/pokemon/mime_jr/normal.gbapal");
    const u32 gMonBackPic_MimeJr[] = INCBIN_U32("graphics/pokemon/mime_jr/back.4bpp.smol");
    const u16 gMonShinyPalette_MimeJr[] = INCBIN_U16("graphics/pokemon/mime_jr/shiny.gbapal");
    const u8 gMonIcon_MimeJr[] = INCBIN_U8("graphics/pokemon/mime_jr/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_MimeJr[] = INCBIN_U8("graphics/pokemon/mime_jr/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_MimeJr[] = INCBIN_COMP("graphics/pokemon/mime_jr/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_MimeJr[] = INCBIN_U16("graphics/pokemon/mime_jr/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_MimeJr[] = INCBIN_U16("graphics/pokemon/mime_jr/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_4_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_MrMime[] = INCBIN_U32("graphics/pokemon/mr_mime/anim_front.4bpp.smol");
    const u16 gMonPalette_MrMime[] = INCBIN_U16("graphics/pokemon/mr_mime/normal.gbapal");
    const u32 gMonBackPic_MrMime[] = INCBIN_U32("graphics/pokemon/mr_mime/back.4bpp.smol");
    const u16 gMonShinyPalette_MrMime[] = INCBIN_U16("graphics/pokemon/mr_mime/shiny.gbapal");
#else
    const u32 gMonFrontPic_MrMime[] = INCBIN_U32("graphics/pokemon/mr_mime/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_MrMime[] = INCBIN_U16("graphics/pokemon/mr_mime/normal_gba.gbapal");
    const u32 gMonBackPic_MrMime[] = INCBIN_U32("graphics/pokemon/mr_mime/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_MrMime[] = INCBIN_U16("graphics/pokemon/mr_mime/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_MrMime[] = INCBIN_U8("graphics/pokemon/mr_mime/icon.4bpp");
#else
    const u8 gMonIcon_MrMime[] = INCBIN_U8("graphics/pokemon/mr_mime/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_MrMime[] = INCBIN_U8("graphics/pokemon/mr_mime/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_MrMime[] = INCBIN_COMP("graphics/pokemon/mr_mime/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_MrMime[] = INCBIN_U16("graphics/pokemon/mr_mime/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_MrMime[] = INCBIN_U16("graphics/pokemon/mr_mime/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GALARIAN_FORMS
    const u32 gMonFrontPic_MrMimeGalar[] = INCBIN_U32("graphics/pokemon/mr_mime/galar/front.4bpp.smol");
    const u16 gMonPalette_MrMimeGalar[] = INCBIN_U16("graphics/pokemon/mr_mime/galar/normal.gbapal");
    const u32 gMonBackPic_MrMimeGalar[] = INCBIN_U32("graphics/pokemon/mr_mime/galar/back.4bpp.smol");
    const u16 gMonShinyPalette_MrMimeGalar[] = INCBIN_U16("graphics/pokemon/mr_mime/galar/shiny.gbapal");
    const u8 gMonIcon_MrMimeGalar[] = INCBIN_U8("graphics/pokemon/mr_mime/galar/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_MrMimeGalar[] = INCBIN_COMP("graphics/pokemon/mr_mime/galar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_MrMimeGalar[] = INCBIN_U16("graphics/pokemon/mr_mime/galar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_MrMimeGalar[] = INCBIN_U16("graphics/pokemon/mr_mime/galar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_MrRime[] = INCBIN_U32("graphics/pokemon/mr_rime/front.4bpp.smol");
    const u16 gMonPalette_MrRime[] = INCBIN_U16("graphics/pokemon/mr_rime/normal.gbapal");
    const u32 gMonBackPic_MrRime[] = INCBIN_U32("graphics/pokemon/mr_rime/back.4bpp.smol");
    const u16 gMonShinyPalette_MrRime[] = INCBIN_U16("graphics/pokemon/mr_rime/shiny.gbapal");
    const u8 gMonIcon_MrRime[] = INCBIN_U8("graphics/pokemon/mr_rime/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_MrRime[] = INCBIN_U8("graphics/pokemon/mr_rime/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_MrRime[] = INCBIN_COMP("graphics/pokemon/mr_rime/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_MrRime[] = INCBIN_U16("graphics/pokemon/mr_rime/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_MrRime[] = INCBIN_U16("graphics/pokemon/mr_rime/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_MR_MIME

#if P_FAMILY_SCYTHER
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Scyther[] = INCBIN_U32("graphics/pokemon/scyther/anim_front.4bpp.smol");
    const u16 gMonPalette_Scyther[] = INCBIN_U16("graphics/pokemon/scyther/normal.gbapal");
    const u32 gMonBackPic_Scyther[] = INCBIN_U32("graphics/pokemon/scyther/back.4bpp.smol");
    const u16 gMonShinyPalette_Scyther[] = INCBIN_U16("graphics/pokemon/scyther/shiny.gbapal");
#else
    const u32 gMonFrontPic_Scyther[] = INCBIN_U32("graphics/pokemon/scyther/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Scyther[] = INCBIN_U16("graphics/pokemon/scyther/normal_gba.gbapal");
    const u32 gMonBackPic_Scyther[] = INCBIN_U32("graphics/pokemon/scyther/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Scyther[] = INCBIN_U16("graphics/pokemon/scyther/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Scyther[] = INCBIN_U8("graphics/pokemon/scyther/icon.4bpp");
#else
    const u8 gMonIcon_Scyther[] = INCBIN_U8("graphics/pokemon/scyther/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Scyther[] = INCBIN_U8("graphics/pokemon/scyther/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Scyther[] = INCBIN_COMP("graphics/pokemon/scyther/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Scyther[] = INCBIN_U16("graphics/pokemon/scyther/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Scyther[] = INCBIN_U16("graphics/pokemon/scyther/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Scyther[] = INCBIN_U16("graphics/pokemon/scyther/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_ScytherF[] = INCBIN_U32("graphics/pokemon/scyther/anim_frontf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_ScytherF[] = INCBIN_COMP("graphics/pokemon/scyther/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Scizor[] = INCBIN_U32("graphics/pokemon/scizor/anim_front.4bpp.smol");
    const u16 gMonPalette_Scizor[] = INCBIN_U16("graphics/pokemon/scizor/normal.gbapal");
    const u32 gMonBackPic_Scizor[] = INCBIN_U32("graphics/pokemon/scizor/back.4bpp.smol");
    const u16 gMonShinyPalette_Scizor[] = INCBIN_U16("graphics/pokemon/scizor/shiny.gbapal");
#else
    const u32 gMonFrontPic_Scizor[] = INCBIN_U32("graphics/pokemon/scizor/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Scizor[] = INCBIN_U16("graphics/pokemon/scizor/normal_gba.gbapal");
    const u32 gMonBackPic_Scizor[] = INCBIN_U32("graphics/pokemon/scizor/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Scizor[] = INCBIN_U16("graphics/pokemon/scizor/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Scizor[] = INCBIN_U8("graphics/pokemon/scizor/icon.4bpp");
#else
    const u8 gMonIcon_Scizor[] = INCBIN_U8("graphics/pokemon/scizor/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Scizor[] = INCBIN_U8("graphics/pokemon/scizor/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Scizor[] = INCBIN_COMP("graphics/pokemon/scizor/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Scizor[] = INCBIN_U16("graphics/pokemon/scizor/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Scizor[] = INCBIN_U16("graphics/pokemon/scizor/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_ScizorF[] = INCBIN_U32("graphics/pokemon/scizor/anim_frontf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_ScizorF[] = INCBIN_COMP("graphics/pokemon/scizor/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_ScizorMega[] = INCBIN_U32("graphics/pokemon/scizor/mega/front.4bpp.smol");
    const u16 gMonPalette_ScizorMega[] = INCBIN_U16("graphics/pokemon/scizor/mega/normal.gbapal");
    const u32 gMonBackPic_ScizorMega[] = INCBIN_U32("graphics/pokemon/scizor/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_ScizorMega[] = INCBIN_U16("graphics/pokemon/scizor/mega/shiny.gbapal");
    const u8 gMonIcon_ScizorMega[] = INCBIN_U8("graphics/pokemon/scizor/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_ScizorMega[] = INCBIN_COMP("graphics/pokemon/scizor/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_ScizorMega[] = INCBIN_U16("graphics/pokemon/scizor/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_ScizorMega[] = INCBIN_U16("graphics/pokemon/scizor/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS
#endif //P_GEN_2_CROSS_EVOS

#if P_GEN_8_CROSS_EVOS
    const u32 gMonFrontPic_Kleavor[] = INCBIN_U32("graphics/pokemon/kleavor/front.4bpp.smol");
    const u16 gMonPalette_Kleavor[] = INCBIN_U16("graphics/pokemon/kleavor/normal.gbapal");
    const u32 gMonBackPic_Kleavor[] = INCBIN_U32("graphics/pokemon/kleavor/back.4bpp.smol");
    const u16 gMonShinyPalette_Kleavor[] = INCBIN_U16("graphics/pokemon/kleavor/shiny.gbapal");
    const u8 gMonIcon_Kleavor[] = INCBIN_U8("graphics/pokemon/kleavor/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Kleavor[] = INCBIN_U8("graphics/pokemon/kleavor/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Kleavor[] = INCBIN_COMP("graphics/pokemon/kleavor/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Kleavor[] = INCBIN_U16("graphics/pokemon/kleavor/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Kleavor[] = INCBIN_U16("graphics/pokemon/kleavor/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_8_CROSS_EVOS
#endif //P_FAMILY_SCYTHER

#if P_FAMILY_JYNX
#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Smoochum[] = INCBIN_U32("graphics/pokemon/smoochum/anim_front.4bpp.smol");
    const u16 gMonPalette_Smoochum[] = INCBIN_U16("graphics/pokemon/smoochum/normal.gbapal");
    const u32 gMonBackPic_Smoochum[] = INCBIN_U32("graphics/pokemon/smoochum/back.4bpp.smol");
    const u16 gMonShinyPalette_Smoochum[] = INCBIN_U16("graphics/pokemon/smoochum/shiny.gbapal");
#else
    const u32 gMonFrontPic_Smoochum[] = INCBIN_U32("graphics/pokemon/smoochum/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Smoochum[] = INCBIN_U16("graphics/pokemon/smoochum/normal_gba.gbapal");
    const u32 gMonBackPic_Smoochum[] = INCBIN_U32("graphics/pokemon/smoochum/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Smoochum[] = INCBIN_U16("graphics/pokemon/smoochum/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Smoochum[] = INCBIN_U8("graphics/pokemon/smoochum/icon.4bpp");
#else
    const u8 gMonIcon_Smoochum[] = INCBIN_U8("graphics/pokemon/smoochum/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Smoochum[] = INCBIN_U8("graphics/pokemon/smoochum/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Smoochum[] = INCBIN_COMP("graphics/pokemon/smoochum/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Smoochum[] = INCBIN_U16("graphics/pokemon/smoochum/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Smoochum[] = INCBIN_U16("graphics/pokemon/smoochum/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Jynx[] = INCBIN_U32("graphics/pokemon/jynx/anim_front.4bpp.smol");
    const u16 gMonPalette_Jynx[] = INCBIN_U16("graphics/pokemon/jynx/normal.gbapal");
    const u32 gMonBackPic_Jynx[] = INCBIN_U32("graphics/pokemon/jynx/back.4bpp.smol");
    const u16 gMonShinyPalette_Jynx[] = INCBIN_U16("graphics/pokemon/jynx/shiny.gbapal");
#else
    const u32 gMonFrontPic_Jynx[] = INCBIN_U32("graphics/pokemon/jynx/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Jynx[] = INCBIN_U16("graphics/pokemon/jynx/normal_gba.gbapal");
    const u32 gMonBackPic_Jynx[] = INCBIN_U32("graphics/pokemon/jynx/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Jynx[] = INCBIN_U16("graphics/pokemon/jynx/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Jynx[] = INCBIN_U8("graphics/pokemon/jynx/icon.4bpp");
#else
    const u8 gMonIcon_Jynx[] = INCBIN_U8("graphics/pokemon/jynx/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Jynx[] = INCBIN_U8("graphics/pokemon/jynx/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Jynx[] = INCBIN_COMP("graphics/pokemon/jynx/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Jynx[] = INCBIN_U16("graphics/pokemon/jynx/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Jynx[] = INCBIN_U16("graphics/pokemon/jynx/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_JYNX

#if P_FAMILY_ELECTABUZZ
#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Elekid[] = INCBIN_U32("graphics/pokemon/elekid/anim_front.4bpp.smol");
    const u16 gMonPalette_Elekid[] = INCBIN_U16("graphics/pokemon/elekid/normal.gbapal");
    const u32 gMonBackPic_Elekid[] = INCBIN_U32("graphics/pokemon/elekid/back.4bpp.smol");
    const u16 gMonShinyPalette_Elekid[] = INCBIN_U16("graphics/pokemon/elekid/shiny.gbapal");
#else
    const u32 gMonFrontPic_Elekid[] = INCBIN_U32("graphics/pokemon/elekid/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Elekid[] = INCBIN_U16("graphics/pokemon/elekid/normal_gba.gbapal");
    const u32 gMonBackPic_Elekid[] = INCBIN_U32("graphics/pokemon/elekid/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Elekid[] = INCBIN_U16("graphics/pokemon/elekid/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Elekid[] = INCBIN_U8("graphics/pokemon/elekid/icon.4bpp");
#else
    const u8 gMonIcon_Elekid[] = INCBIN_U8("graphics/pokemon/elekid/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Elekid[] = INCBIN_U8("graphics/pokemon/elekid/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Elekid[] = INCBIN_COMP("graphics/pokemon/elekid/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Elekid[] = INCBIN_U16("graphics/pokemon/elekid/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Elekid[] = INCBIN_U16("graphics/pokemon/elekid/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Elekid[] = INCBIN_U16("graphics/pokemon/elekid/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Electabuzz[] = INCBIN_U32("graphics/pokemon/electabuzz/anim_front.4bpp.smol");
    const u16 gMonPalette_Electabuzz[] = INCBIN_U16("graphics/pokemon/electabuzz/normal.gbapal");
    const u32 gMonBackPic_Electabuzz[] = INCBIN_U32("graphics/pokemon/electabuzz/back.4bpp.smol");
    const u16 gMonShinyPalette_Electabuzz[] = INCBIN_U16("graphics/pokemon/electabuzz/shiny.gbapal");
#else
    const u32 gMonFrontPic_Electabuzz[] = INCBIN_U32("graphics/pokemon/electabuzz/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Electabuzz[] = INCBIN_U16("graphics/pokemon/electabuzz/normal_gba.gbapal");
    const u32 gMonBackPic_Electabuzz[] = INCBIN_U32("graphics/pokemon/electabuzz/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Electabuzz[] = INCBIN_U16("graphics/pokemon/electabuzz/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Electabuzz[] = INCBIN_U8("graphics/pokemon/electabuzz/icon.4bpp");
#else
    const u8 gMonIcon_Electabuzz[] = INCBIN_U8("graphics/pokemon/electabuzz/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Electabuzz[] = INCBIN_U8("graphics/pokemon/electabuzz/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Electabuzz[] = INCBIN_COMP("graphics/pokemon/electabuzz/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Electabuzz[] = INCBIN_U16("graphics/pokemon/electabuzz/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Electabuzz[] = INCBIN_U16("graphics/pokemon/electabuzz/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_Electivire[] = INCBIN_U32("graphics/pokemon/electivire/anim_front.4bpp.smol");
    const u16 gMonPalette_Electivire[] = INCBIN_U16("graphics/pokemon/electivire/normal.gbapal");
    const u32 gMonBackPic_Electivire[] = INCBIN_U32("graphics/pokemon/electivire/back.4bpp.smol");
    const u16 gMonShinyPalette_Electivire[] = INCBIN_U16("graphics/pokemon/electivire/shiny.gbapal");
    const u8 gMonIcon_Electivire[] = INCBIN_U8("graphics/pokemon/electivire/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Electivire[] = INCBIN_U8("graphics/pokemon/electivire/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Electivire[] = INCBIN_COMP("graphics/pokemon/electivire/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Electivire[] = INCBIN_U16("graphics/pokemon/electivire/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Electivire[] = INCBIN_U16("graphics/pokemon/electivire/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_4_CROSS_EVOS
#endif //P_FAMILY_ELECTABUZZ

#if P_FAMILY_MAGMAR
#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Magby[] = INCBIN_U32("graphics/pokemon/magby/anim_front.4bpp.smol");
    const u16 gMonPalette_Magby[] = INCBIN_U16("graphics/pokemon/magby/normal.gbapal");
    const u32 gMonBackPic_Magby[] = INCBIN_U32("graphics/pokemon/magby/back.4bpp.smol");
    const u16 gMonShinyPalette_Magby[] = INCBIN_U16("graphics/pokemon/magby/shiny.gbapal");
#else
    const u32 gMonFrontPic_Magby[] = INCBIN_U32("graphics/pokemon/magby/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Magby[] = INCBIN_U16("graphics/pokemon/magby/normal_gba.gbapal");
    const u32 gMonBackPic_Magby[] = INCBIN_U32("graphics/pokemon/magby/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Magby[] = INCBIN_U16("graphics/pokemon/magby/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Magby[] = INCBIN_U8("graphics/pokemon/magby/icon.4bpp");
#else
    const u8 gMonIcon_Magby[] = INCBIN_U8("graphics/pokemon/magby/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Magby[] = INCBIN_U8("graphics/pokemon/magby/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Magby[] = INCBIN_COMP("graphics/pokemon/magby/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Magby[] = INCBIN_U16("graphics/pokemon/magby/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Magby[] = INCBIN_U16("graphics/pokemon/magby/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Magmar[] = INCBIN_U32("graphics/pokemon/magmar/anim_front.4bpp.smol");
    const u16 gMonPalette_Magmar[] = INCBIN_U16("graphics/pokemon/magmar/normal.gbapal");
    const u32 gMonBackPic_Magmar[] = INCBIN_U32("graphics/pokemon/magmar/back.4bpp.smol");
    const u16 gMonShinyPalette_Magmar[] = INCBIN_U16("graphics/pokemon/magmar/shiny.gbapal");
#else
    const u32 gMonFrontPic_Magmar[] = INCBIN_U32("graphics/pokemon/magmar/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Magmar[] = INCBIN_U16("graphics/pokemon/magmar/normal_gba.gbapal");
    const u32 gMonBackPic_Magmar[] = INCBIN_U32("graphics/pokemon/magmar/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Magmar[] = INCBIN_U16("graphics/pokemon/magmar/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Magmar[] = INCBIN_U8("graphics/pokemon/magmar/icon.4bpp");
#else
    const u8 gMonIcon_Magmar[] = INCBIN_U8("graphics/pokemon/magmar/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Magmar[] = INCBIN_U8("graphics/pokemon/magmar/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Magmar[] = INCBIN_COMP("graphics/pokemon/magmar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Magmar[] = INCBIN_U16("graphics/pokemon/magmar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Magmar[] = INCBIN_U16("graphics/pokemon/magmar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_Magmortar[] = INCBIN_U32("graphics/pokemon/magmortar/anim_front.4bpp.smol");
    const u16 gMonPalette_Magmortar[] = INCBIN_U16("graphics/pokemon/magmortar/normal.gbapal");
    const u32 gMonBackPic_Magmortar[] = INCBIN_U32("graphics/pokemon/magmortar/back.4bpp.smol");
    const u16 gMonShinyPalette_Magmortar[] = INCBIN_U16("graphics/pokemon/magmortar/shiny.gbapal");
    const u8 gMonIcon_Magmortar[] = INCBIN_U8("graphics/pokemon/magmortar/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Magmortar[] = INCBIN_U8("graphics/pokemon/magmortar/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Magmortar[] = INCBIN_COMP("graphics/pokemon/magmortar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Magmortar[] = INCBIN_U16("graphics/pokemon/magmortar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Magmortar[] = INCBIN_U16("graphics/pokemon/magmortar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_4_CROSS_EVOS
#endif //P_FAMILY_MAGMAR

#if P_FAMILY_PINSIR
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Pinsir[] = INCBIN_U32("graphics/pokemon/pinsir/anim_front.4bpp.smol");
    const u16 gMonPalette_Pinsir[] = INCBIN_U16("graphics/pokemon/pinsir/normal.gbapal");
    const u32 gMonBackPic_Pinsir[] = INCBIN_U32("graphics/pokemon/pinsir/back.4bpp.smol");
    const u16 gMonShinyPalette_Pinsir[] = INCBIN_U16("graphics/pokemon/pinsir/shiny.gbapal");
#else
    const u32 gMonFrontPic_Pinsir[] = INCBIN_U32("graphics/pokemon/pinsir/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Pinsir[] = INCBIN_U16("graphics/pokemon/pinsir/normal_gba.gbapal");
    const u32 gMonBackPic_Pinsir[] = INCBIN_U32("graphics/pokemon/pinsir/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Pinsir[] = INCBIN_U16("graphics/pokemon/pinsir/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Pinsir[] = INCBIN_U8("graphics/pokemon/pinsir/icon.4bpp");
#else
    const u8 gMonIcon_Pinsir[] = INCBIN_U8("graphics/pokemon/pinsir/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Pinsir[] = INCBIN_U8("graphics/pokemon/pinsir/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Pinsir[] = INCBIN_COMP("graphics/pokemon/pinsir/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Pinsir[] = INCBIN_U16("graphics/pokemon/pinsir/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Pinsir[] = INCBIN_U16("graphics/pokemon/pinsir/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_PinsirMega[] = INCBIN_U32("graphics/pokemon/pinsir/mega/front.4bpp.smol");
    const u16 gMonPalette_PinsirMega[] = INCBIN_U16("graphics/pokemon/pinsir/mega/normal.gbapal");
    const u32 gMonBackPic_PinsirMega[] = INCBIN_U32("graphics/pokemon/pinsir/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_PinsirMega[] = INCBIN_U16("graphics/pokemon/pinsir/mega/shiny.gbapal");
    const u8 gMonIcon_PinsirMega[] = INCBIN_U8("graphics/pokemon/pinsir/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_PinsirMega[] = INCBIN_COMP("graphics/pokemon/pinsir/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_PinsirMega[] = INCBIN_U16("graphics/pokemon/pinsir/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_PinsirMega[] = INCBIN_U16("graphics/pokemon/pinsir/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS
#endif //P_FAMILY_PINSIR

#if P_FAMILY_TAUROS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Tauros[] = INCBIN_U32("graphics/pokemon/tauros/anim_front.4bpp.smol");
    const u16 gMonPalette_Tauros[] = INCBIN_U16("graphics/pokemon/tauros/normal.gbapal");
    const u32 gMonBackPic_Tauros[] = INCBIN_U32("graphics/pokemon/tauros/back.4bpp.smol");
    const u16 gMonShinyPalette_Tauros[] = INCBIN_U16("graphics/pokemon/tauros/shiny.gbapal");
#else
    const u32 gMonFrontPic_Tauros[] = INCBIN_U32("graphics/pokemon/tauros/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Tauros[] = INCBIN_U16("graphics/pokemon/tauros/normal_gba.gbapal");
    const u32 gMonBackPic_Tauros[] = INCBIN_U32("graphics/pokemon/tauros/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Tauros[] = INCBIN_U16("graphics/pokemon/tauros/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Tauros[] = INCBIN_U8("graphics/pokemon/tauros/icon.4bpp");
#else
    const u8 gMonIcon_Tauros[] = INCBIN_U8("graphics/pokemon/tauros/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Tauros[] = INCBIN_U8("graphics/pokemon/tauros/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Tauros[] = INCBIN_COMP("graphics/pokemon/tauros/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Tauros[] = INCBIN_U16("graphics/pokemon/tauros/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Tauros[] = INCBIN_U16("graphics/pokemon/tauros/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_PALDEAN_FORMS
    const u32 gMonFrontPic_TaurosPaldeaCombat[] = INCBIN_U32("graphics/pokemon/tauros/paldea_combat/front.4bpp.smol");
    const u16 gMonPalette_TaurosPaldeaCombat[] = INCBIN_U16("graphics/pokemon/tauros/paldea_combat/normal.gbapal");
    const u32 gMonBackPic_TaurosPaldeaCombat[] = INCBIN_U32("graphics/pokemon/tauros/paldea_combat/back.4bpp.smol");
    const u16 gMonShinyPalette_TaurosPaldeaCombat[] = INCBIN_U16("graphics/pokemon/tauros/paldea_combat/shiny.gbapal");
    const u8 gMonIcon_TaurosPaldeaCombat[] = INCBIN_U8("graphics/pokemon/tauros/paldea_combat/icon.4bpp");

    const u32 gMonFrontPic_TaurosPaldeaBlaze[] = INCBIN_U32("graphics/pokemon/tauros/paldea_blaze/front.4bpp.smol");
    const u16 gMonPalette_TaurosPaldeaBlaze[] = INCBIN_U16("graphics/pokemon/tauros/paldea_blaze/normal.gbapal");
    const u32 gMonBackPic_TaurosPaldeaBlaze[] = INCBIN_U32("graphics/pokemon/tauros/paldea_blaze/back.4bpp.smol");
    const u16 gMonShinyPalette_TaurosPaldeaBlaze[] = INCBIN_U16("graphics/pokemon/tauros/paldea_blaze/shiny.gbapal");
    const u8 gMonIcon_TaurosPaldeaBlaze[] = INCBIN_U8("graphics/pokemon/tauros/paldea_blaze/icon.4bpp");

    const u32 gMonFrontPic_TaurosPaldeaAqua[] = INCBIN_U32("graphics/pokemon/tauros/paldea_aqua/front.4bpp.smol");
    const u16 gMonPalette_TaurosPaldeaAqua[] = INCBIN_U16("graphics/pokemon/tauros/paldea_aqua/normal.gbapal");
    const u32 gMonBackPic_TaurosPaldeaAqua[] = INCBIN_U32("graphics/pokemon/tauros/paldea_aqua/back.4bpp.smol");
    const u16 gMonShinyPalette_TaurosPaldeaAqua[] = INCBIN_U16("graphics/pokemon/tauros/paldea_aqua/shiny.gbapal");
    const u8 gMonIcon_TaurosPaldeaAqua[] = INCBIN_U8("graphics/pokemon/tauros/paldea_aqua/icon.4bpp");

#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_TaurosPaldeaCombat[] = INCBIN_COMP("graphics/pokemon/tauros/paldea_combat/overworld.4bpp");
    const u32 gObjectEventPic_TaurosPaldeaBlaze[] = INCBIN_COMP("graphics/pokemon/tauros/paldea_blaze/overworld.4bpp");
    const u32 gObjectEventPic_TaurosPaldeaAqua[] = INCBIN_COMP("graphics/pokemon/tauros/paldea_aqua/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_TaurosPaldeaCombat[] = INCBIN_U16("graphics/pokemon/tauros/paldea_combat/overworld_normal.gbapal");
    const u16 gOverworldPalette_TaurosPaldeaBlaze[] = INCBIN_U16("graphics/pokemon/tauros/paldea_blaze/overworld_normal.gbapal");
    const u16 gOverworldPalette_TaurosPaldeaAqua[] = INCBIN_U16("graphics/pokemon/tauros/paldea_aqua/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_TaurosPaldeaCombat[] = INCBIN_U16("graphics/pokemon/tauros/paldea_combat/overworld_shiny.gbapal");
    const u16 gShinyOverworldPalette_TaurosPaldeaBlaze[] = INCBIN_U16("graphics/pokemon/tauros/paldea_blaze/overworld_shiny.gbapal");
    const u16 gShinyOverworldPalette_TaurosPaldeaAqua[] = INCBIN_U16("graphics/pokemon/tauros/paldea_aqua/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_PALDEAN_FORMS
#endif //P_FAMILY_TAUROS

#if P_FAMILY_MAGIKARP
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Magikarp[] = INCBIN_U32("graphics/pokemon/magikarp/anim_front.4bpp.smol");
    const u16 gMonPalette_Magikarp[] = INCBIN_U16("graphics/pokemon/magikarp/normal.gbapal");
    const u32 gMonBackPic_Magikarp[] = INCBIN_U32("graphics/pokemon/magikarp/back.4bpp.smol");
    const u16 gMonShinyPalette_Magikarp[] = INCBIN_U16("graphics/pokemon/magikarp/shiny.gbapal");
#else
    const u32 gMonFrontPic_Magikarp[] = INCBIN_U32("graphics/pokemon/magikarp/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Magikarp[] = INCBIN_U16("graphics/pokemon/magikarp/normal_gba.gbapal");
    const u32 gMonBackPic_Magikarp[] = INCBIN_U32("graphics/pokemon/magikarp/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Magikarp[] = INCBIN_U16("graphics/pokemon/magikarp/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Magikarp[] = INCBIN_U8("graphics/pokemon/magikarp/icon.4bpp");
#else
    const u8 gMonIcon_Magikarp[] = INCBIN_U8("graphics/pokemon/magikarp/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Magikarp[] = INCBIN_U8("graphics/pokemon/magikarp/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Magikarp[] = INCBIN_COMP("graphics/pokemon/magikarp/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Magikarp[] = INCBIN_U16("graphics/pokemon/magikarp/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Magikarp[] = INCBIN_U16("graphics/pokemon/magikarp/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_MagikarpF[] = INCBIN_U32("graphics/pokemon/magikarp/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_MagikarpF[] = INCBIN_U32("graphics/pokemon/magikarp/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_MagikarpF[] = INCBIN_COMP("graphics/pokemon/magikarp/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Gyarados[] = INCBIN_U32("graphics/pokemon/gyarados/anim_front.4bpp.smol");
    const u16 gMonPalette_Gyarados[] = INCBIN_U16("graphics/pokemon/gyarados/normal.gbapal");
    const u32 gMonBackPic_Gyarados[] = INCBIN_U32("graphics/pokemon/gyarados/back.4bpp.smol");
    const u16 gMonShinyPalette_Gyarados[] = INCBIN_U16("graphics/pokemon/gyarados/shiny.gbapal");
#else
    const u32 gMonFrontPic_Gyarados[] = INCBIN_U32("graphics/pokemon/gyarados/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Gyarados[] = INCBIN_U16("graphics/pokemon/gyarados/normal_gba.gbapal");
    const u32 gMonBackPic_Gyarados[] = INCBIN_U32("graphics/pokemon/gyarados/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Gyarados[] = INCBIN_U16("graphics/pokemon/gyarados/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Gyarados[] = INCBIN_U8("graphics/pokemon/gyarados/icon.4bpp");
#else
    const u8 gMonIcon_Gyarados[] = INCBIN_U8("graphics/pokemon/gyarados/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Gyarados[] = INCBIN_U8("graphics/pokemon/gyarados/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Gyarados[] = INCBIN_COMP("graphics/pokemon/gyarados/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Gyarados[] = INCBIN_U16("graphics/pokemon/gyarados/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Gyarados[] = INCBIN_U16("graphics/pokemon/gyarados/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_GyaradosF[] = INCBIN_U32("graphics/pokemon/gyarados/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_GyaradosF[] = INCBIN_U32("graphics/pokemon/gyarados/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_GyaradosF[] = INCBIN_COMP("graphics/pokemon/gyarados/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_GyaradosMega[] = INCBIN_U32("graphics/pokemon/gyarados/mega/front.4bpp.smol");
    const u16 gMonPalette_GyaradosMega[] = INCBIN_U16("graphics/pokemon/gyarados/mega/normal.gbapal");
    const u32 gMonBackPic_GyaradosMega[] = INCBIN_U32("graphics/pokemon/gyarados/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_GyaradosMega[] = INCBIN_U16("graphics/pokemon/gyarados/mega/shiny.gbapal");
    const u8 gMonIcon_GyaradosMega[] = INCBIN_U8("graphics/pokemon/gyarados/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_GyaradosMega[] = INCBIN_COMP("graphics/pokemon/gyarados/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_GyaradosMega[] = INCBIN_U16("graphics/pokemon/gyarados/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_GyaradosMega[] = INCBIN_U16("graphics/pokemon/gyarados/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS
#endif //P_FAMILY_MAGIKARP

#if P_FAMILY_LAPRAS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Lapras[] = INCBIN_U32("graphics/pokemon/lapras/anim_front.4bpp.smol");
    const u16 gMonPalette_Lapras[] = INCBIN_U16("graphics/pokemon/lapras/normal.gbapal");
    const u32 gMonBackPic_Lapras[] = INCBIN_U32("graphics/pokemon/lapras/back.4bpp.smol");
    const u16 gMonShinyPalette_Lapras[] = INCBIN_U16("graphics/pokemon/lapras/shiny.gbapal");
#else
    const u32 gMonFrontPic_Lapras[] = INCBIN_U32("graphics/pokemon/lapras/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Lapras[] = INCBIN_U16("graphics/pokemon/lapras/normal_gba.gbapal");
    const u32 gMonBackPic_Lapras[] = INCBIN_U32("graphics/pokemon/lapras/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Lapras[] = INCBIN_U16("graphics/pokemon/lapras/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Lapras[] = INCBIN_U8("graphics/pokemon/lapras/icon.4bpp");
#else
    const u8 gMonIcon_Lapras[] = INCBIN_U8("graphics/pokemon/lapras/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Lapras[] = INCBIN_U8("graphics/pokemon/lapras/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Lapras[] = INCBIN_COMP("graphics/pokemon/lapras/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Lapras[] = INCBIN_U16("graphics/pokemon/lapras/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Lapras[] = INCBIN_U16("graphics/pokemon/lapras/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Lapras[] = INCBIN_U16("graphics/pokemon/lapras/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_LaprasGmax[] = INCBIN_U32("graphics/pokemon/lapras/gmax/front.4bpp.smol");
    const u32 gMonBackPic_LaprasGmax[] = INCBIN_U32("graphics/pokemon/lapras/gmax/back.4bpp.smol");
    const u16 gMonPalette_LaprasGmax[] = INCBIN_U16("graphics/pokemon/lapras/gmax/normal.gbapal");
    const u16 gMonShinyPalette_LaprasGmax[] = INCBIN_U16("graphics/pokemon/lapras/gmax/shiny.gbapal");
    const u8 gMonIcon_LaprasGmax[] = INCBIN_U8("graphics/pokemon/lapras/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_LaprasGmax[] = INCBIN_COMP("graphics/pokemon/lapras/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_LaprasGmax[] = INCBIN_U16("graphics/pokemon/lapras/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_LaprasGmax[] = INCBIN_U16("graphics/pokemon/lapras/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS
#endif //P_FAMILY_LAPRAS

#if P_FAMILY_DITTO
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Ditto[] = INCBIN_U32("graphics/pokemon/ditto/anim_front.4bpp.smol");
    const u16 gMonPalette_Ditto[] = INCBIN_U16("graphics/pokemon/ditto/normal.gbapal");
    const u32 gMonBackPic_Ditto[] = INCBIN_U32("graphics/pokemon/ditto/back.4bpp.smol");
    const u16 gMonShinyPalette_Ditto[] = INCBIN_U16("graphics/pokemon/ditto/shiny.gbapal");
#else
    const u32 gMonFrontPic_Ditto[] = INCBIN_U32("graphics/pokemon/ditto/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Ditto[] = INCBIN_U16("graphics/pokemon/ditto/normal_gba.gbapal");
    const u32 gMonBackPic_Ditto[] = INCBIN_U32("graphics/pokemon/ditto/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Ditto[] = INCBIN_U16("graphics/pokemon/ditto/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Ditto[] = INCBIN_U8("graphics/pokemon/ditto/icon.4bpp");
#else
    const u8 gMonIcon_Ditto[] = INCBIN_U8("graphics/pokemon/ditto/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Ditto[] = INCBIN_U8("graphics/pokemon/ditto/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Ditto[] = INCBIN_COMP("graphics/pokemon/ditto/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Ditto[] = INCBIN_U16("graphics/pokemon/ditto/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Ditto[] = INCBIN_U16("graphics/pokemon/ditto/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_DITTO

#if P_FAMILY_EEVEE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Eevee[] = INCBIN_U32("graphics/pokemon/eevee/anim_front.4bpp.smol");
    const u16 gMonPalette_Eevee[] = INCBIN_U16("graphics/pokemon/eevee/normal.gbapal");
    const u32 gMonBackPic_Eevee[] = INCBIN_U32("graphics/pokemon/eevee/back.4bpp.smol");
    const u16 gMonShinyPalette_Eevee[] = INCBIN_U16("graphics/pokemon/eevee/shiny.gbapal");
#else
    const u32 gMonFrontPic_Eevee[] = INCBIN_U32("graphics/pokemon/eevee/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Eevee[] = INCBIN_U16("graphics/pokemon/eevee/normal_gba.gbapal");
    const u32 gMonBackPic_Eevee[] = INCBIN_U32("graphics/pokemon/eevee/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Eevee[] = INCBIN_U16("graphics/pokemon/eevee/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Eevee[] = INCBIN_U8("graphics/pokemon/eevee/icon.4bpp");
#else
    const u8 gMonIcon_Eevee[] = INCBIN_U8("graphics/pokemon/eevee/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Eevee[] = INCBIN_U8("graphics/pokemon/eevee/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Eevee[] = INCBIN_COMP("graphics/pokemon/eevee/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Eevee[] = INCBIN_U16("graphics/pokemon/eevee/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Eevee[] = INCBIN_U16("graphics/pokemon/eevee/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GENDER_DIFFERENCES
    const u32 gMonFrontPic_EeveeF[] = INCBIN_U32("graphics/pokemon/eevee/anim_frontf.4bpp.smol");
    const u32 gMonBackPic_EeveeF[] = INCBIN_U32("graphics/pokemon/eevee/backf.4bpp.smol");
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_EeveeF[] = INCBIN_COMP("graphics/pokemon/eevee/overworldf.4bpp");
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GENDER_DIFFERENCES

#if P_GIGANTAMAX_FORMS
    const u32 gMonFrontPic_EeveeGmax[] = INCBIN_U32("graphics/pokemon/eevee/gmax/front.4bpp.smol");
    const u32 gMonBackPic_EeveeGmax[] = INCBIN_U32("graphics/pokemon/eevee/gmax/back.4bpp.smol");
    const u16 gMonPalette_EeveeGmax[] = INCBIN_U16("graphics/pokemon/eevee/gmax/normal.gbapal");
    const u16 gMonShinyPalette_EeveeGmax[] = INCBIN_U16("graphics/pokemon/eevee/gmax/shiny.gbapal");
    const u8 gMonIcon_EeveeGmax[] = INCBIN_U8("graphics/pokemon/eevee/gmax/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS
    // const u32 gObjectEventPic_EeveeGmax[] = INCBIN_COMP("graphics/pokemon/eevee/gmax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    // const u16 gOverworldPalette_EeveeGmax[] = INCBIN_U16("graphics/pokemon/eevee/gmax/overworld_normal.gbapal");
    // const u16 gShinyOverworldPalette_EeveeGmax[] = INCBIN_U16("graphics/pokemon/eevee/gmax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GIGANTAMAX_FORMS

    const u8 gMonIcon_EeveePartner[] = INCBIN_U8("graphics/pokemon/eevee/partner/icon.4bpp");
#if P_GENDER_DIFFERENCES && P_CUSTOM_GENDER_DIFF_ICONS
    const u8 gMonIcon_EeveePartnerF[] = INCBIN_U8("graphics/pokemon/eevee/partner/iconf.4bpp");
#endif //P_GENDER_DIFFERENCES && P_CUSTOM_GENDER_DIFF_ICONS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Vaporeon[] = INCBIN_U32("graphics/pokemon/vaporeon/anim_front.4bpp.smol");
    const u16 gMonPalette_Vaporeon[] = INCBIN_U16("graphics/pokemon/vaporeon/normal.gbapal");
    const u32 gMonBackPic_Vaporeon[] = INCBIN_U32("graphics/pokemon/vaporeon/back.4bpp.smol");
    const u16 gMonShinyPalette_Vaporeon[] = INCBIN_U16("graphics/pokemon/vaporeon/shiny.gbapal");
#else
    const u32 gMonFrontPic_Vaporeon[] = INCBIN_U32("graphics/pokemon/vaporeon/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Vaporeon[] = INCBIN_U16("graphics/pokemon/vaporeon/normal_gba.gbapal");
    const u32 gMonBackPic_Vaporeon[] = INCBIN_U32("graphics/pokemon/vaporeon/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Vaporeon[] = INCBIN_U16("graphics/pokemon/vaporeon/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Vaporeon[] = INCBIN_U8("graphics/pokemon/vaporeon/icon.4bpp");
#else
    const u8 gMonIcon_Vaporeon[] = INCBIN_U8("graphics/pokemon/vaporeon/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Vaporeon[] = INCBIN_U8("graphics/pokemon/vaporeon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Vaporeon[] = INCBIN_COMP("graphics/pokemon/vaporeon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Vaporeon[] = INCBIN_U16("graphics/pokemon/vaporeon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Vaporeon[] = INCBIN_U16("graphics/pokemon/vaporeon/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Vaporeon[] = INCBIN_U16("graphics/pokemon/vaporeon/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Jolteon[] = INCBIN_U32("graphics/pokemon/jolteon/anim_front.4bpp.smol");
    const u16 gMonPalette_Jolteon[] = INCBIN_U16("graphics/pokemon/jolteon/normal.gbapal");
    const u32 gMonBackPic_Jolteon[] = INCBIN_U32("graphics/pokemon/jolteon/back.4bpp.smol");
    const u16 gMonShinyPalette_Jolteon[] = INCBIN_U16("graphics/pokemon/jolteon/shiny.gbapal");
#else
    const u32 gMonFrontPic_Jolteon[] = INCBIN_U32("graphics/pokemon/jolteon/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Jolteon[] = INCBIN_U16("graphics/pokemon/jolteon/normal_gba.gbapal");
    const u32 gMonBackPic_Jolteon[] = INCBIN_U32("graphics/pokemon/jolteon/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Jolteon[] = INCBIN_U16("graphics/pokemon/jolteon/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Jolteon[] = INCBIN_U8("graphics/pokemon/jolteon/icon.4bpp");
#else
    const u8 gMonIcon_Jolteon[] = INCBIN_U8("graphics/pokemon/jolteon/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Jolteon[] = INCBIN_U8("graphics/pokemon/jolteon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Jolteon[] = INCBIN_COMP("graphics/pokemon/jolteon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Jolteon[] = INCBIN_U16("graphics/pokemon/jolteon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Jolteon[] = INCBIN_U16("graphics/pokemon/jolteon/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Jolteon[] = INCBIN_U16("graphics/pokemon/jolteon/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Flareon[] = INCBIN_U32("graphics/pokemon/flareon/anim_front.4bpp.smol");
    const u16 gMonPalette_Flareon[] = INCBIN_U16("graphics/pokemon/flareon/normal.gbapal");
    const u32 gMonBackPic_Flareon[] = INCBIN_U32("graphics/pokemon/flareon/back.4bpp.smol");
    const u16 gMonShinyPalette_Flareon[] = INCBIN_U16("graphics/pokemon/flareon/shiny.gbapal");
#else
    const u32 gMonFrontPic_Flareon[] = INCBIN_U32("graphics/pokemon/flareon/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Flareon[] = INCBIN_U16("graphics/pokemon/flareon/normal_gba.gbapal");
    const u32 gMonBackPic_Flareon[] = INCBIN_U32("graphics/pokemon/flareon/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Flareon[] = INCBIN_U16("graphics/pokemon/flareon/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Flareon[] = INCBIN_U8("graphics/pokemon/flareon/icon.4bpp");
#else
    const u8 gMonIcon_Flareon[] = INCBIN_U8("graphics/pokemon/flareon/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Flareon[] = INCBIN_U8("graphics/pokemon/flareon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Flareon[] = INCBIN_COMP("graphics/pokemon/flareon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Flareon[] = INCBIN_U16("graphics/pokemon/flareon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Flareon[] = INCBIN_U16("graphics/pokemon/flareon/overworld_shiny.gbapal");
    const u16 gShinyModernOverworldPalette_Flareon[] = INCBIN_U16("graphics/pokemon/flareon/overworld_shiny_modern.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Espeon[] = INCBIN_U32("graphics/pokemon/espeon/anim_front.4bpp.smol");
    const u16 gMonPalette_Espeon[] = INCBIN_U16("graphics/pokemon/espeon/normal.gbapal");
    const u32 gMonBackPic_Espeon[] = INCBIN_U32("graphics/pokemon/espeon/back.4bpp.smol");
    const u16 gMonShinyPalette_Espeon[] = INCBIN_U16("graphics/pokemon/espeon/shiny.gbapal");
#else
    const u32 gMonFrontPic_Espeon[] = INCBIN_U32("graphics/pokemon/espeon/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Espeon[] = INCBIN_U16("graphics/pokemon/espeon/normal_gba.gbapal");
    const u32 gMonBackPic_Espeon[] = INCBIN_U32("graphics/pokemon/espeon/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Espeon[] = INCBIN_U16("graphics/pokemon/espeon/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Espeon[] = INCBIN_U8("graphics/pokemon/espeon/icon.4bpp");
#else
    const u8 gMonIcon_Espeon[] = INCBIN_U8("graphics/pokemon/espeon/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Espeon[] = INCBIN_U8("graphics/pokemon/espeon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Espeon[] = INCBIN_COMP("graphics/pokemon/espeon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Espeon[] = INCBIN_U16("graphics/pokemon/espeon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Espeon[] = INCBIN_U16("graphics/pokemon/espeon/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Umbreon[] = INCBIN_U32("graphics/pokemon/umbreon/anim_front.4bpp.smol");
    const u16 gMonPalette_Umbreon[] = INCBIN_U16("graphics/pokemon/umbreon/normal.gbapal");
    const u32 gMonBackPic_Umbreon[] = INCBIN_U32("graphics/pokemon/umbreon/back.4bpp.smol");
    const u16 gMonShinyPalette_Umbreon[] = INCBIN_U16("graphics/pokemon/umbreon/shiny.gbapal");
#else
    const u32 gMonFrontPic_Umbreon[] = INCBIN_U32("graphics/pokemon/umbreon/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Umbreon[] = INCBIN_U16("graphics/pokemon/umbreon/normal_gba.gbapal");
    const u32 gMonBackPic_Umbreon[] = INCBIN_U32("graphics/pokemon/umbreon/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Umbreon[] = INCBIN_U16("graphics/pokemon/umbreon/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Umbreon[] = INCBIN_U8("graphics/pokemon/umbreon/icon.4bpp");
#else
    const u8 gMonIcon_Umbreon[] = INCBIN_U8("graphics/pokemon/umbreon/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Umbreon[] = INCBIN_U8("graphics/pokemon/umbreon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Umbreon[] = INCBIN_COMP("graphics/pokemon/umbreon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Umbreon[] = INCBIN_U16("graphics/pokemon/umbreon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Umbreon[] = INCBIN_U16("graphics/pokemon/umbreon/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_2_CROSS_EVOS

#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_Leafeon[] = INCBIN_U32("graphics/pokemon/leafeon/anim_front.4bpp.smol");
    const u16 gMonPalette_Leafeon[] = INCBIN_U16("graphics/pokemon/leafeon/normal.gbapal");
    const u32 gMonBackPic_Leafeon[] = INCBIN_U32("graphics/pokemon/leafeon/back.4bpp.smol");
    const u16 gMonShinyPalette_Leafeon[] = INCBIN_U16("graphics/pokemon/leafeon/shiny.gbapal");
    const u8 gMonIcon_Leafeon[] = INCBIN_U8("graphics/pokemon/leafeon/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Leafeon[] = INCBIN_U8("graphics/pokemon/leafeon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Leafeon[] = INCBIN_COMP("graphics/pokemon/leafeon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Leafeon[] = INCBIN_U16("graphics/pokemon/leafeon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Leafeon[] = INCBIN_U16("graphics/pokemon/leafeon/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

    const u32 gMonFrontPic_Glaceon[] = INCBIN_U32("graphics/pokemon/glaceon/anim_front.4bpp.smol");
    const u16 gMonPalette_Glaceon[] = INCBIN_U16("graphics/pokemon/glaceon/normal.gbapal");
    const u32 gMonBackPic_Glaceon[] = INCBIN_U32("graphics/pokemon/glaceon/back.4bpp.smol");
    const u16 gMonShinyPalette_Glaceon[] = INCBIN_U16("graphics/pokemon/glaceon/shiny.gbapal");
    const u8 gMonIcon_Glaceon[] = INCBIN_U8("graphics/pokemon/glaceon/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Glaceon[] = INCBIN_U8("graphics/pokemon/glaceon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Glaceon[] = INCBIN_COMP("graphics/pokemon/glaceon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Glaceon[] = INCBIN_U16("graphics/pokemon/glaceon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Glaceon[] = INCBIN_U16("graphics/pokemon/glaceon/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_4_CROSS_EVOS

#if P_GEN_6_CROSS_EVOS
    const u32 gMonFrontPic_Sylveon[] = INCBIN_U32("graphics/pokemon/sylveon/anim_front.4bpp.smol");
    const u16 gMonPalette_Sylveon[] = INCBIN_U16("graphics/pokemon/sylveon/normal.gbapal");
    const u32 gMonBackPic_Sylveon[] = INCBIN_U32("graphics/pokemon/sylveon/back.4bpp.smol");
    const u16 gMonShinyPalette_Sylveon[] = INCBIN_U16("graphics/pokemon/sylveon/shiny.gbapal");
    const u8 gMonIcon_Sylveon[] = INCBIN_U8("graphics/pokemon/sylveon/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Sylveon[] = INCBIN_U8("graphics/pokemon/sylveon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Sylveon[] = INCBIN_COMP("graphics/pokemon/sylveon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Sylveon[] = INCBIN_U16("graphics/pokemon/sylveon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Sylveon[] = INCBIN_U16("graphics/pokemon/sylveon/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_6_CROSS_EVOS
#endif //P_FAMILY_EEVEE

#if P_FAMILY_PORYGON
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Porygon[] = INCBIN_U32("graphics/pokemon/porygon/anim_front.4bpp.smol");
    const u16 gMonPalette_Porygon[] = INCBIN_U16("graphics/pokemon/porygon/normal.gbapal");
    const u32 gMonBackPic_Porygon[] = INCBIN_U32("graphics/pokemon/porygon/back.4bpp.smol");
    const u16 gMonShinyPalette_Porygon[] = INCBIN_U16("graphics/pokemon/porygon/shiny.gbapal");
#else
    const u32 gMonFrontPic_Porygon[] = INCBIN_U32("graphics/pokemon/porygon/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Porygon[] = INCBIN_U16("graphics/pokemon/porygon/normal_gba.gbapal");
    const u32 gMonBackPic_Porygon[] = INCBIN_U32("graphics/pokemon/porygon/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Porygon[] = INCBIN_U16("graphics/pokemon/porygon/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Porygon[] = INCBIN_U8("graphics/pokemon/porygon/icon.4bpp");
#else
    const u8 gMonIcon_Porygon[] = INCBIN_U8("graphics/pokemon/porygon/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Porygon[] = INCBIN_U8("graphics/pokemon/porygon/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Porygon[] = INCBIN_COMP("graphics/pokemon/porygon/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Porygon[] = INCBIN_U16("graphics/pokemon/porygon/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Porygon[] = INCBIN_U16("graphics/pokemon/porygon/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_2_CROSS_EVOS
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Porygon2[] = INCBIN_U32("graphics/pokemon/porygon2/anim_front.4bpp.smol");
    const u16 gMonPalette_Porygon2[] = INCBIN_U16("graphics/pokemon/porygon2/normal.gbapal");
    const u32 gMonBackPic_Porygon2[] = INCBIN_U32("graphics/pokemon/porygon2/back.4bpp.smol");
    const u16 gMonShinyPalette_Porygon2[] = INCBIN_U16("graphics/pokemon/porygon2/shiny.gbapal");
#else
    const u32 gMonFrontPic_Porygon2[] = INCBIN_U32("graphics/pokemon/porygon2/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Porygon2[] = INCBIN_U16("graphics/pokemon/porygon2/normal_gba.gbapal");
    const u32 gMonBackPic_Porygon2[] = INCBIN_U32("graphics/pokemon/porygon2/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Porygon2[] = INCBIN_U16("graphics/pokemon/porygon2/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Porygon2[] = INCBIN_U8("graphics/pokemon/porygon2/icon.4bpp");
#else
    const u8 gMonIcon_Porygon2[] = INCBIN_U8("graphics/pokemon/porygon2/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Porygon2[] = INCBIN_U8("graphics/pokemon/porygon2/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Porygon2[] = INCBIN_COMP("graphics/pokemon/porygon2/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Porygon2[] = INCBIN_U16("graphics/pokemon/porygon2/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Porygon2[] = INCBIN_U16("graphics/pokemon/porygon2/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_PorygonZ[] = INCBIN_U32("graphics/pokemon/porygon_z/anim_front.4bpp.smol");
    const u16 gMonPalette_PorygonZ[] = INCBIN_U16("graphics/pokemon/porygon_z/normal.gbapal");
    const u32 gMonBackPic_PorygonZ[] = INCBIN_U32("graphics/pokemon/porygon_z/back.4bpp.smol");
    const u16 gMonShinyPalette_PorygonZ[] = INCBIN_U16("graphics/pokemon/porygon_z/shiny.gbapal");
    const u8 gMonIcon_PorygonZ[] = INCBIN_U8("graphics/pokemon/porygon_z/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_PorygonZ[] = INCBIN_U8("graphics/pokemon/porygon_z/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_PorygonZ[] = INCBIN_COMP("graphics/pokemon/porygon_z/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_PorygonZ[] = INCBIN_U16("graphics/pokemon/porygon_z/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_PorygonZ[] = INCBIN_U16("graphics/pokemon/porygon_z/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_4_CROSS_EVOS
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_PORYGON

#if P_FAMILY_OMANYTE
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Omanyte[] = INCBIN_U32("graphics/pokemon/omanyte/anim_front.4bpp.smol");
    const u16 gMonPalette_Omanyte[] = INCBIN_U16("graphics/pokemon/omanyte/normal.gbapal");
    const u32 gMonBackPic_Omanyte[] = INCBIN_U32("graphics/pokemon/omanyte/back.4bpp.smol");
    const u16 gMonShinyPalette_Omanyte[] = INCBIN_U16("graphics/pokemon/omanyte/shiny.gbapal");
#else
    const u32 gMonFrontPic_Omanyte[] = INCBIN_U32("graphics/pokemon/omanyte/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Omanyte[] = INCBIN_U16("graphics/pokemon/omanyte/normal_gba.gbapal");
    const u32 gMonBackPic_Omanyte[] = INCBIN_U32("graphics/pokemon/omanyte/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Omanyte[] = INCBIN_U16("graphics/pokemon/omanyte/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Omanyte[] = INCBIN_U8("graphics/pokemon/omanyte/icon.4bpp");
#else
    const u8 gMonIcon_Omanyte[] = INCBIN_U8("graphics/pokemon/omanyte/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Omanyte[] = INCBIN_U8("graphics/pokemon/omanyte/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Omanyte[] = INCBIN_COMP("graphics/pokemon/omanyte/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Omanyte[] = INCBIN_U16("graphics/pokemon/omanyte/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Omanyte[] = INCBIN_U16("graphics/pokemon/omanyte/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Omastar[] = INCBIN_U32("graphics/pokemon/omastar/anim_front.4bpp.smol");
    const u16 gMonPalette_Omastar[] = INCBIN_U16("graphics/pokemon/omastar/normal.gbapal");
    const u32 gMonBackPic_Omastar[] = INCBIN_U32("graphics/pokemon/omastar/back.4bpp.smol");
    const u16 gMonShinyPalette_Omastar[] = INCBIN_U16("graphics/pokemon/omastar/shiny.gbapal");
#else
    const u32 gMonFrontPic_Omastar[] = INCBIN_U32("graphics/pokemon/omastar/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Omastar[] = INCBIN_U16("graphics/pokemon/omastar/normal_gba.gbapal");
    const u32 gMonBackPic_Omastar[] = INCBIN_U32("graphics/pokemon/omastar/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Omastar[] = INCBIN_U16("graphics/pokemon/omastar/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Omastar[] = INCBIN_U8("graphics/pokemon/omastar/icon.4bpp");
#else
    const u8 gMonIcon_Omastar[] = INCBIN_U8("graphics/pokemon/omastar/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Omastar[] = INCBIN_U8("graphics/pokemon/omastar/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Omastar[] = INCBIN_COMP("graphics/pokemon/omastar/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Omastar[] = INCBIN_U16("graphics/pokemon/omastar/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Omastar[] = INCBIN_U16("graphics/pokemon/omastar/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_OMANYTE

#if P_FAMILY_KABUTO
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Kabuto[] = INCBIN_U32("graphics/pokemon/kabuto/anim_front.4bpp.smol");
    const u16 gMonPalette_Kabuto[] = INCBIN_U16("graphics/pokemon/kabuto/normal.gbapal");
    const u32 gMonBackPic_Kabuto[] = INCBIN_U32("graphics/pokemon/kabuto/back.4bpp.smol");
    const u16 gMonShinyPalette_Kabuto[] = INCBIN_U16("graphics/pokemon/kabuto/shiny.gbapal");
#else
    const u32 gMonFrontPic_Kabuto[] = INCBIN_U32("graphics/pokemon/kabuto/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Kabuto[] = INCBIN_U16("graphics/pokemon/kabuto/normal_gba.gbapal");
    const u32 gMonBackPic_Kabuto[] = INCBIN_U32("graphics/pokemon/kabuto/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Kabuto[] = INCBIN_U16("graphics/pokemon/kabuto/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Kabuto[] = INCBIN_U8("graphics/pokemon/kabuto/icon.4bpp");
#else
    const u8 gMonIcon_Kabuto[] = INCBIN_U8("graphics/pokemon/kabuto/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Kabuto[] = INCBIN_U8("graphics/pokemon/kabuto/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Kabuto[] = INCBIN_COMP("graphics/pokemon/kabuto/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Kabuto[] = INCBIN_U16("graphics/pokemon/kabuto/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Kabuto[] = INCBIN_U16("graphics/pokemon/kabuto/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Kabutops[] = INCBIN_U32("graphics/pokemon/kabutops/anim_front.4bpp.smol");
    const u16 gMonPalette_Kabutops[] = INCBIN_U16("graphics/pokemon/kabutops/normal.gbapal");
    const u32 gMonBackPic_Kabutops[] = INCBIN_U32("graphics/pokemon/kabutops/back.4bpp.smol");
    const u16 gMonShinyPalette_Kabutops[] = INCBIN_U16("graphics/pokemon/kabutops/shiny.gbapal");
#else
    const u32 gMonFrontPic_Kabutops[] = INCBIN_U32("graphics/pokemon/kabutops/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Kabutops[] = INCBIN_U16("graphics/pokemon/kabutops/normal_gba.gbapal");
    const u32 gMonBackPic_Kabutops[] = INCBIN_U32("graphics/pokemon/kabutops/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Kabutops[] = INCBIN_U16("graphics/pokemon/kabutops/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Kabutops[] = INCBIN_U8("graphics/pokemon/kabutops/icon.4bpp");
#else
    const u8 gMonIcon_Kabutops[] = INCBIN_U8("graphics/pokemon/kabutops/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Kabutops[] = INCBIN_U8("graphics/pokemon/kabutops/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Kabutops[] = INCBIN_COMP("graphics/pokemon/kabutops/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Kabutops[] = INCBIN_U16("graphics/pokemon/kabutops/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Kabutops[] = INCBIN_U16("graphics/pokemon/kabutops/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_FAMILY_KABUTO

#if P_FAMILY_AERODACTYL
#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Aerodactyl[] = INCBIN_U32("graphics/pokemon/aerodactyl/anim_front.4bpp.smol");
    const u16 gMonPalette_Aerodactyl[] = INCBIN_U16("graphics/pokemon/aerodactyl/normal.gbapal");
    const u32 gMonBackPic_Aerodactyl[] = INCBIN_U32("graphics/pokemon/aerodactyl/back.4bpp.smol");
    const u16 gMonShinyPalette_Aerodactyl[] = INCBIN_U16("graphics/pokemon/aerodactyl/shiny.gbapal");
#else
    const u32 gMonFrontPic_Aerodactyl[] = INCBIN_U32("graphics/pokemon/aerodactyl/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Aerodactyl[] = INCBIN_U16("graphics/pokemon/aerodactyl/normal_gba.gbapal");
    const u32 gMonBackPic_Aerodactyl[] = INCBIN_U32("graphics/pokemon/aerodactyl/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Aerodactyl[] = INCBIN_U16("graphics/pokemon/aerodactyl/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Aerodactyl[] = INCBIN_U8("graphics/pokemon/aerodactyl/icon.4bpp");
#else
    const u8 gMonIcon_Aerodactyl[] = INCBIN_U8("graphics/pokemon/aerodactyl/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Aerodactyl[] = INCBIN_U8("graphics/pokemon/aerodactyl/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Aerodactyl[] = INCBIN_COMP("graphics/pokemon/aerodactyl/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Aerodactyl[] = INCBIN_U16("graphics/pokemon/aerodactyl/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Aerodactyl[] = INCBIN_U16("graphics/pokemon/aerodactyl/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS

#if P_MEGA_EVOLUTIONS
    const u32 gMonFrontPic_AerodactylMega[] = INCBIN_U32("graphics/pokemon/aerodactyl/mega/front.4bpp.smol");
    const u16 gMonPalette_AerodactylMega[] = INCBIN_U16("graphics/pokemon/aerodactyl/mega/normal.gbapal");
    const u32 gMonBackPic_AerodactylMega[] = INCBIN_U32("graphics/pokemon/aerodactyl/mega/back.4bpp.smol");
    const u16 gMonShinyPalette_AerodactylMega[] = INCBIN_U16("graphics/pokemon/aerodactyl/mega/shiny.gbapal");
    const u8 gMonIcon_AerodactylMega[] = INCBIN_U8("graphics/pokemon/aerodactyl/mega/icon.4bpp");
#if OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
    const u32 gObjectEventPic_AerodactylMega[] = INCBIN_COMP("graphics/pokemon/aerodactyl/mega/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_AerodactylMega[] = INCBIN_U16("graphics/pokemon/aerodactyl/mega/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_AerodactylMega[] = INCBIN_U16("graphics/pokemon/aerodactyl/mega/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS && OW_BATTLE_ONLY_FORMS
#endif //P_MEGA_EVOLUTIONS
#endif //P_FAMILY_AERODACTYL

#if P_FAMILY_SNORLAX
#if P_GEN_4_CROSS_EVOS
    const u32 gMonFrontPic_Munchlax[] = INCBIN_U32("graphics/pokemon/munchlax/anim_front.4bpp.smol");
    const u16 gMonPalette_Munchlax[] = INCBIN_U16("graphics/pokemon/munchlax/normal.gbapal");
    const u32 gMonBackPic_Munchlax[] = INCBIN_U32("graphics/pokemon/munchlax/back.4bpp.smol");
    const u16 gMonShinyPalette_Munchlax[] = INCBIN_U16("graphics/pokemon/munchlax/shiny.gbapal");
    const u8 gMonIcon_Munchlax[] = INCBIN_U8("graphics/pokemon/munchlax/icon.4bpp");
#if P_FOOTPRINTS
    const u8 gMonFootprint_Munchlax[] = INCBIN_U8("graphics/pokemon/munchlax/footprint.1bpp");
#endif //P_FOOTPRINTS
#if OW_POKEMON_OBJECT_EVENTS
    const u32 gObjectEventPic_Munchlax[] = INCBIN_COMP("graphics/pokemon/munchlax/overworld.4bpp");
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
    const u16 gOverworldPalette_Munchlax[] = INCBIN_U16("graphics/pokemon/munchlax/overworld_normal.gbapal");
    const u16 gShinyOverworldPalette_Munchlax[] = INCBIN_U16("graphics/pokemon/munchlax/overworld_shiny.gbapal");
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES
#endif //OW_POKEMON_OBJECT_EVENTS
#endif //P_GEN_4_CROSS_EVOS

#if !P_GBA_STYLE_SPECIES_GFX
    const u32 gMonFrontPic_Snorlax[] = INCBIN_U32("graphics/pokemon/snorlax/anim_front.4bpp.smol");
    const u16 gMonPalette_Snorlax[] = INCBIN_U16("graphics/pokemon/snorlax/normal.gbapal");
    const u32 gMonBackPic_Snorlax[] = INCBIN_U32("graphics/pokemon/snorlax/back.4bpp.smol");
    const u16 gMonShinyPalette_Snorlax[] = INCBIN_U16("graphics/pokemon/snorlax/shiny.gbapal");
#else
    const u32 gMonFrontPic_Snorlax[] = INCBIN_U32("graphics/pokemon/snorlax/anim_front_gba.4bpp.smol");
    const u16 gMonPalette_Snorlax[] = INCBIN_U16("graphics/pokemon/snorlax/normal_gba.gbapal");
    const u32 gMonBackPic_Snorlax[] = INCBIN_U32("graphics/pokemon/snorlax/back_gba.4bpp.smol");
    const u16 gMonShinyPalette_Snorlax[] = INCBIN_U16("graphics/pokemon/snorlax/shiny_gba.gbapal");
#endif //P_GBA_STYLE_SPECIES_GFX
#if !P_GBA_STYLE_SPECIES_ICONS
    const u8 gMonIcon_Snorlax[] = INCBIN_U8("graphics/pokemon/snorlax/icon.4bpp");
#else
    const u8 gMonIcon_Snorlax[] = INCBIN_U8("graphics/pokemon/snorlax/icon_gba.4bpp");
#endif //P_GBA_STYLE_SPECIES_ICONS
#if P_FOOTPRINTS
    const u8 gMonFootprint_Snorlax[] = INCBIN_U8("graphics/pokemon/snorlax/footprint.Ч~|Яћ›КЧ¬ўh­µзS—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЫWЬЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЬљXЫЬљ[ФЫTЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЫWЬЫKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЬљXЫЬљ[ФЫTЫVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЫWЬЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЬљXЫЬљ[ФЫTЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЫWЬЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЬљXЫЬљ[ФЫTЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЫWЬЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЬљXЫЬљ[Ф]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬ]KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЬљXЫЬљ[Ф]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬ]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЬљXЫЬљ[Ф]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬ]KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЬљXЫЬљ[Ф]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬ]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЬљXЫЬљ[Ф]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬ]KЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЬљXЫЬљ[Ф]VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬ]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЬљXЫЬљ[Ф]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬ]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЬљXЫЬљ[Ф]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬ]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЬљXЫЬљ[ФЩ[њЭVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЩ[њЭKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЬљXЫЬљ[ФЩ[њЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЩ[њЭKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЬљXЫЬљ[ФЩ[њЭVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЩ[њЭKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЬљXЫЬљ[ФЩ[њЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЩ[њЭKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЬљXЫЬљ[ФЩ[њЭVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЩ[њЭKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЬљXЫЬљ[ФЩ[њЭVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЩ[њЭKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЬљXЫЬљ[ФЩ[њЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЩ[њЭKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЬљXЫЬљ[ФЩ[њЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬљXЫЬљ[ЛЬЩ[њЭKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУФ’PУФ’SВ‚€ЪY€СђSRSWРХUQQ“B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЭ]YY›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭ]YY›KШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЭ]YY›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭ]YY›KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЭ]YY›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭ]YY›KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЭ]YY›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭ]YY›KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЭ]YY›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЭ]YY›KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЭ]YY›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЭ]YY›KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЭ]YY›VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЭ]YY›KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЭ]YY›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭ]YY›KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЭ]YY›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭ]YY›KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФљX›ЫX™YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬљX›ЫX™YKШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФљX›ЫX™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬљX›ЫX™YKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФљX›ЫX™YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬљX›ЫX™YKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФљX›ЫX™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬљX›ЫX™YKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФљX›ЫX™YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬљX›ЫX™YKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФљX›ЫX™YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬљX›ЫX™YKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФљX›ЫX™YVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬљX›ЫX™YKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФљX›ЫX™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬљX›ЫX™YKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФљX›ЫX™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬљX›ЫX™YKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРХUQQ“B‚€ЪY€СђSRSWФ“РТФ•Q‘‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ›ШЪЬќY™–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ШЪЬќY™‹Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ›ШЪЬќY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ШЪЬќY™‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ›ШЪЬќY™–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ШЪЬќY™‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ›ШЪЬќY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ШЪЬќY™‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф›ШЪЬќY™–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь›ШЪЬќY™‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ›ШЪЬќY™–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь›ШЪЬќY™‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ›ШЪЬќY™–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь›ШЪЬќY™‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ›ШЪЬќY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ШЪЬќY™‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ›ШЪЬќY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ШЪЬќY™‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXШ[њ›ШУZY^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXШ[њ›ШУZY^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXШ[њ›ШУZY^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXШ[њ›ШУZY^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXШ[њ›ШУZY^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУXШ[њ›ШЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXШ[њ›ШУZY^VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУXШ[њ›ШУZY^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXШ[њ›ШУZY^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXШ[њ›ШУZYљYЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫZYљYЪШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXШ[њ›ШУZYљYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫZYљYЪЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXШ[њ›ШУZYљYЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫZYљYЪШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXШ[њ›ШУZYљYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫZYљYЪЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXШ[њ›ШУZYљYЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫZYљYЪЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXШ[њ›ШУZYљYЪЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫZYљYЪЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУXШ[њ›ШУZYљYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫZYљYЪЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXШ[њ›ШУZYљYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЫZYљYЪЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXШ[њ›ШС\ЪЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЩ\ЪЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXШ[њ›ШС\ЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЩ\ЪЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXШ[њ›ШС\ЪЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЩ\ЪЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXШ[њ›ШС\ЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЩ\ЪЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXШ[њ›ШС\ЪЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЩ\ЪЛЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXШ[њ›ШС\ЪЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЩ\ЪЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУXШ[њ›ШС\ЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЩ\ЪЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXШ[њ›ШС\ЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXШ[њ›ШЛЩ\ЪЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФ“РТФ•Q‘‚‚€ЪY€СђSRSWХТTТUРTТB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЪ\Ъ]Ш\ЪTЫЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЪ\Ъ]Ш\ЪTЫЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЪ\Ъ]Ш\ЪTЫЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЪ\Ъ]Ш\ЪTЫЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЪ\Ъ]Ш\ЪTЫЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЪ\Ъ]Ш\ЪVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЪ\Ъ]Ш\ЪTЫЫЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЪ\Ъ]Ш\ЪTЫЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЪ\Ъ]Ш\ЪTЫЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЪ\Ъ]Ш\ЪTШЪЫЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЬШЪЫЫЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЪ\Ъ]Ш\ЪTШЪЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЬШЪЫЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЪ\Ъ]Ш\ЪTШЪЫЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЬШЪЫЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЪ\Ъ]Ш\ЪTШЪЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЬШЪЫЫЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЪ\Ъ]Ш\ЪTШЪЫЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЬШЪЫЫЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЪ\Ъ]Ш\ЪTШЪЫЫЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЬШЪЫЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WХЪ\Ъ]Ш\ЪTШЪЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЬШЪЫЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЪ\Ъ]Ш\ЪTШЪЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ\Ъ]Ш\ЪKЬШЪЫЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХТTТUРTТB‚€ЪY€СђSRSWУPT‘PS’QB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУX\™X[љYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\™X[љYKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУX\™X[љYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\™X[љYKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУX\™X[љYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\™X[љYKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУX\™X[љYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\™X[љYKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УX\™X[љYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX\™X[љYKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУX\™X[љYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX\™X[љYKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУX\™X[љYVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫX\™X[љYKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУX\™X[љYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\™X[љYKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУX\™X[љYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\™X[љYKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЮ\^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ\^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЮ\^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ\^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЮ\^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ\^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЮ\^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ\^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЮ\^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ\^ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЮ\^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ\^Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЮ\^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ\^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЮ\^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ\^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЮ\^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ\^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУPT‘PS’QB‚€ЪY€СђSRSWУUQ”ђVB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ]Yњ^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]Yњ^KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ]Yњ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]Yњ^KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ]Yњ^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]Yњ^KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ]Yњ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]Yњ^KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У]Yњ^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы]Yњ^KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУ]Yњ^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы]Yњ^KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ]Yњ^VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы]Yњ^KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ]Yњ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]Yњ^KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ]Yњ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]Yњ^KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ]YЩ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]YЩ[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ]YЩ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]YЩ[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ]YЩ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]YЩ[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ]YЩ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]YЩ[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У]YЩ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы]YЩ[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУ]YЩ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы]YЩ[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ]YЩ[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы]YЩ[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ]YЩ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]YЩ[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ]YЩ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы]YЩ[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУUQ”ђVB‚€ЪY€СђSRSWСUФQT‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС]ЬY\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]ЬY\‹Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС]ЬY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]ЬY\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС]ЬY\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]ЬY\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС]ЬY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]ЬY\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С]ЬY\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ]ЬY\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС]ЬY\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ]ЬY\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС]ЬY\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ]ЬY\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС]ЬY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]ЬY\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС]ЬY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]ЬY\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\\]X[љYЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\\]X[љYШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\\]X[љYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\\]X[љYЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\\]X[љYЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\\]X[љYШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\\]X[љYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\\]X[љYЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\\]X[љYЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\\]X[љYЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\\]X[љYЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\\]X[љYЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\\]X[љYЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\\]X[љYЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\\]X[љYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\\]X[љYЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\\]X[љYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\\]X[љYЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСUФQT‚‚€ЪY€СђSRSWС“УPS•TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС›ЫX[ќ\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЫX[ќ\ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС›ЫX[ќ\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЫX[ќ\ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС›ЫX[ќ\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЫX[ќ\ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС›ЫX[ќ\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЫX[ќ\ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С›ЫX[ќ\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЫX[ќ\ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС›ЫX[ќ\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЫX[ќ\ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС›ЫX[ќ\ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЫX[ќ\ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС›ЫX[ќ\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЫX[ќ\ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС›ЫX[ќ\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЫX[ќ\ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ\[ќ\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы\[ќ\ЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ\[ќ\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы\[ќ\ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ\[ќ\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы\[ќ\ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ\[ќ\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы\[ќ\ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У\[ќ\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы\[ќ\ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУ\[ќ\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы\[ќ\ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ\[ќ\ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы\[ќ\ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ\[ќ\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы\[ќ\ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ\[ќ\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы\[ќ\ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWС“УPS•TВ‚€ЪY€СђSRSWУSФ‘SS€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ[Ь™[[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™[[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ[Ь™[[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™[[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ[Ь™[[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™[[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ[Ь™[[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™[[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У[Ь™[[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™[[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУ[Ь™[[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™[[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ[Ь™[[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™[[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ[Ь™[[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™[[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ[Ь™[[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™[[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪZ[›ЭXЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪZ[›ЭXЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЪZ[›ЭXЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪZ[›ЭXЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪZ[›ЭXЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪZ[›ЭXЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪZ[›ЭXЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪZ[›ЭXЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪZ[›ЭXЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪZ[›ЭXЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪZ[›ЭXЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪZ[›ЭXЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪZ[›ЭXЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪZ[›ЭXЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪZ[›ЭXЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪZ[›ЭXЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪZ[›ЭXЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪZ[›ЭXЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУSФ‘SS‚€ЪY€СђSRSWФРSS‘U€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШ[[™]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[[™]Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШ[[™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[[™]Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШ[[™]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[[™]ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШ[[™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[[™]ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШ[[™]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[[™]ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФШ[[™]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[[™]Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШ[[™]ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[[™]ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФШ[[™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[[™]ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШ[[™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[[™]ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШ[^ћ›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[^ћ›KШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШ[^ћ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[^ћ›KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШ[^ћ›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[^ћ›KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШ[^ћ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[^ћ›KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШ[^ћ›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[^ћ›KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФШ[^ћ›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[^ћ›KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШ[^ћ›VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[^ћ›KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФШ[^ћ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[^ћ›KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШ[^ћ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[^ћ›KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФРSS‘U‚€ЪY€СђSRSWФХQ‘•S€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЭY™ќ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY™ќ[Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЭY™ќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY™ќ[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЭY™ќ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY™ќ[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЭY™ќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY™ќ[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЭY™ќ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY™ќ[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЭY™ќ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY™ќ[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЭY™ќ[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY™ќ[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЭY™ќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY™ќ[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЭY™ќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY™ќ[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР™]ЩX\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™]ЩX\‹Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР™]ЩX\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™]ЩX\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР™]ЩX\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™]ЩX\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР™]ЩX\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™]ЩX\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р™]ЩX\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш™]ЩX\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР™]ЩX\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш™]ЩX\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР™]ЩX\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш™]ЩX\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР™]ЩX\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™]ЩX\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР™]ЩX\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™]ЩX\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФХQ‘•S‚€ЪY€СђSRSWР“ХS”ХСQU€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР›Э[њЭЩY]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Э[њЭЩY]Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР›Э[њЭЩY]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Э[њЭЩY]Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР›Э[њЭЩY]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Э[њЭЩY]ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР›Э[њЭЩY]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Э[њЭЩY]ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р›Э[њЭЩY]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›Э[њЭЩY]ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР›Э[њЭЩY]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›Э[њЭЩY]Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР›Э[њЭЩY]ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш›Э[њЭЩY]ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР›Э[њЭЩY]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Э[њЭЩY]ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР›Э[њЭЩY]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Э[њЭЩY]ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЭY[™YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY[™YKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЭY[™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY[™YKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЭY[™YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY[™YKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЭY[™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY[™YKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЭY[™YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY[™YKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЭY[™YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY[™YKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЭY[™YVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY[™YKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЭY[™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY[™YKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЭY[™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭY[™YKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХШ\™Y[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ\™Y[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХШ\™Y[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ\™Y[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХШ\™Y[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ\™Y[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХШ\™Y[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ\™Y[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХШ\™Y[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭШ\™Y[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХШ\™Y[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭШ\™Y[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХШ\™Y[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭШ\™Y[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХШ\™Y[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ\™Y[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХШ\™Y[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ\™Y[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWР“ХS”ХСQU‚€ЪY€СђSRSWРУУQ‘VB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫЫY™^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЫY™^KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫЫY™^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЫY™^KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫЫY™^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЫY™^KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫЫY™^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЫY™^KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫЫY™^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЫY™^KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЫЫY™^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЫY™^KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫЫY™^VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЫY™^KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫЫY™^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЫY™^KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫЫY™^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЫY™^KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРУУQ‘VB‚€ЪY€СђSRSWУФђS‘ХT•B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЬ[™Э\ќVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ[™Э\ќKШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЬ[™Э\ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ[™Э\ќKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЬ[™Э\ќVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ[™Э\ќKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЬ[™Э\ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ[™Э\ќKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЬ[™Э\ќVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ[™Э\ќKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУЬ[™Э\ќVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ[™Э\ќKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЬ[™Э\ќVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ[™Э\ќKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЬ[™Э\ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ[™Э\ќKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЬ[™Э\ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ[™Э\ќKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУФђS‘ХT•B‚€ЪY€СђSRSWФTФТSRPS‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ\ЬЪ[ZX[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\ЬЪ[ZX[‹Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ\ЬЪ[ZX[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\ЬЪ[ZX[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ\ЬЪ[ZX[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\ЬЪ[ZX[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ\ЬЪ[ZX[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\ЬЪ[ZX[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф\ЬЪ[ZX[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь\ЬЪ[ZX[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ\ЬЪ[ZX[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь\ЬЪ[ZX[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ\ЬЪ[ZX[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь\ЬЪ[ZX[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ\ЬЪ[ZX[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\ЬЪ[ZX[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ\ЬЪ[ZX[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\ЬЪ[ZX[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФTФТSRPS‚‚€ЪY€СђSRSWХТSTС€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЪ[\ЩЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ[\ЩШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЪ[\ЩЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ[\ЩЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЪ[\ЩЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ[\ЩШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЪ[\ЩЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ[\ЩЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЪ[\ЩЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ[\ЩЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЪ[\ЩЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ[\ЩЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЪ[\ЩЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ[\ЩЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЪ[\ЩЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ[\ЩЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЪ[\ЩЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪ[\ЩЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫЫ\ЫЬЩЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫЫ\ЫЬЩЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫЫ\ЫЬЩЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫЫ\ЫЬЩЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫЫ\ЫЬЩЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЫЫ\ЫЬЩЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫЫ\ЫЬЩЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫЫ\ЫЬЩЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫЫ\ЫЬЩЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ССS—ОWУQQРWСU“УUSУ”В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫЫ\ЫЬЩYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫЫ\ЫЬЩYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫЫ\ЫЬЩYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫЫ\ЫЬЩYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫYYШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫЫ\ЫЬЩYYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫЫ\ЫЬЩYYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫЫ\ЫЬЩYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫЫ\ЫЬЩYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЫ\ЫЬЩЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ€Щ[™Y€ЛФССS—ОWУQQРWСU“УUSУ”В€Щ[™Y€ЛФСђSRSWХТSTС‚€ЪY€СђSRSWФРS‘QРTХ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШ[™YШ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™YШ\ЭЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШ[™YШ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™YШ\ЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШ[™YШ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™YШ\ЭШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШ[™YШ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™YШ\ЭЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШ[™YШ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™YШ\ЭЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФШ[™YШ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™YШ\ЭЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШ[™YШ\ЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™YШ\ЭЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФШ[™YШ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™YШ\ЭЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШ[™YШ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™YШ\ЭЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ[ЬЬШ[™ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[ЬЬШ[™Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ[ЬЬШ[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[ЬЬШ[™Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ[ЬЬШ[™ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[ЬЬШ[™ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ[ЬЬШ[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[ЬЬШ[™ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф[ЬЬШ[™ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь[ЬЬШ[™ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ[ЬЬШ[™ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь[ЬЬШ[™Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ[ЬЬШ[™ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь[ЬЬШ[™ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ[ЬЬШ[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[ЬЬШ[™ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ[ЬЬШ[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[ЬЬШ[™ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФРS‘QРTХ‚€ЪY€СђSRSWФURХSURХB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ]ZЭ[]ZЭVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ZЭ[]ZЭKШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ]ZЭ[]ZЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ZЭ[]ZЭKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ]ZЭ[]ZЭVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ZЭ[]ZЭKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ]ZЭ[]ZЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ZЭ[]ZЭKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф]ZЭ[]ZЭVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]ZЭ[]ZЭKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ]ZЭ[]ZЭVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]ZЭ[]ZЭKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ]ZЭ[]ZЭVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь]ZЭ[]ZЭKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ]ZЭ[]ZЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ZЭ[]ZЭKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ]ZЭ[]ZЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ZЭ[]ZЭKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФURХSURХB‚€ЪY€СђSRSWХTWУ•S€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\Sќ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫќ[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\Sќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫќ[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\Sќ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫќ[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\Sќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫќ[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\Sќ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫќ[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\WУќ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫќ[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\Sќ[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫќ[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\Sќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫќ[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\Sќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫќ[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪ[[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪ[[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪ[[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪ[[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪ[[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪ[[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪ[[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLM€У[Ы”[]WФЪ[[S›Ь›X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[S›Ь›X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[QљYЪ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩљYЪ[™ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[QљYЪ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩљYЪ[™ЛЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[Q›Z[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩ›Z[™ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[Q›Z[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩ›Z[™ЛЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[TЪ\ЫЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЬЪ\ЫЫ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[TЪ\ЫЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЬЪ\ЫЫ‹ЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[QЬ›Э[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩЬ›Э[™Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[QЬ›Э[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩЬ›Э[™ЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[T›ШЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЬ›ШЪЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[T›ШЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЬ›ШЪЛЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[PќYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KШќYЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[PќYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KШќYЛЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[QЪЬЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩЪЬЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[QЪЬЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩЪЬЭЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[TЭY[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЬЭY[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[TЭY[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЬЭY[ЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[Qљ\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩљ\™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[Qљ\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩљ\™KЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[UШ]\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЭШ]\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[UШ]\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЭШ]\‹ЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[QЬ\ЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩЬ\ЬЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[QЬ\ЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩЬ\ЬЛЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[Q[XЭљXЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩ[XЭљXЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[Q[XЭљXЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩ[XЭљXЛЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[TЮXЪXЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЬЮXЪXЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[TЮXЪXЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЬЮXЪXЛЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[RXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЪXЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[RXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЪXЩKЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[QYЫЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩYЫЫ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[QYЫЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩYЫЫ‹ЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[Q\љЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩ\љЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[Q\љЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩ\љЛЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WФЪ[[QZ\ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩZ\ћKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[[QZ\ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[[KЩZ\ћKЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛФСђSRSWХTWУ•S‚€ЪY€СђSRSWУRS’SФ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУZ[љ[Ь“Y][Ь–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУZ[љ[Ь“Y][Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУZ[љ[Ь“Y][Ь–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУZ[љ[Ь“Y][Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[љ[Ь“Y][Ь–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУZ[љ[Ь–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУZ[љ[ЬђЫЬ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУZ[љ[ЬђЫЬ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУZ[љ[ЬђЫЬ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLM€У[Ы”[]WУZ[љ[ЬђЫЬ™T™YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЬ™YЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[љ[ЬђЫЬ™T™YЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЬ™YЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLM€У[Ы”[]WУZ[љ[ЬђЫЬ™SЬ[™ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЫЬ[™ЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[љ[ЬђЫЬ™SЬ[™ЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЫЬ[™ЩKЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLM€У[Ы”[]WУZ[љ[ЬђЫЬ™VY[ЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЮY[ЭЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[љ[ЬђЫЬ™VY[ЭЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЮY[ЭЛЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLM€У[Ы”[]WУZ[љ[ЬђЫЬ™QЬ™Y[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЩЬ™Y[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[љ[ЬђЫЬ™QЬ™Y[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЩЬ™Y[‹ЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLM€У[Ы”[]WУZ[љ[ЬђЫЬ™P›YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KШ›YKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[љ[ЬђЫЬ™P›YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KШ›YKЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLM€У[Ы”[]WУZ[љ[ЬђЫЬ™R[™YЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЪ[™YЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[љ[ЬђЫЬ™R[™YЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЪ[™YЫЛЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLM€У[Ы”[]WУZ[љ[ЬђЫЬ™Uљ[Ы]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЭљ[Ы]Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[љ[ЬђЫЬ™Uљ[Ы]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ШЫЬ™KЭљ[Ы]ЪXЫЫ‹ЌњЉNВ‚€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУZ[љ[Ь“Y][Ь–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУZ[љ[Ь“Y][Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУZ[љ[Ь“Y][Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[љ[Ь‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУRS’SФ‚‚€ЪY€СђSRSWТУУPSB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТЫЫX[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫX[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТЫЫX[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫX[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТЫЫX[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫX[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТЫЫX[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫX[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТЫЫX[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫX[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТЫЫX[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫX[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТЫЫX[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫX[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТЫЫX[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫX[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТЫЫX[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫX[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТУУPSB‚€ЪY€СђSRSWХT•УђUФ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\ќЫ]Ь–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\ќЫ]Ь‹Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\ќЫ]Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\ќЫ]Ь‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\ќЫ]Ь–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\ќЫ]Ь‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\ќЫ]Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\ќЫ]Ь‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\ќЫ]Ь–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\ќЫ]Ь‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\ќЫ]Ь–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\ќЫ]Ь‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\ќЫ]Ь–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\ќЫ]Ь‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\ќЫ]Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\ќЫ]Ь‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\ќЫ]Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\ќЫ]Ь‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХT•УђUФ‚‚€ЪY€СђSRSWХССQSPT•B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЩЩY[X\ќVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩЩY[X\ќKШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЩЩY[X\ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩЩY[X\ќKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЩЩY[X\ќVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩЩY[X\ќKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЩЩY[X\ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩЩY[X\ќKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЩЩY[X\ќVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЩЩY[X\ќKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЩЩY[X\ќVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЩЩY[X\ќKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЩЩY[X\ќVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЩЩY[X\ќKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЩЩY[X\ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩЩY[X\ќKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЩЩY[X\ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩЩY[X\ќKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХССQSPT•B‚€ЪY€СђSRSWУRSRRЦUB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУZ[ZZЮ]Q\ЩЭZ\ЩYЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУZ[ZZЮ]Q\ЩЭZ\ЩYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУZ[ZZЮ]Q\ЩЭZ\ЩYЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУZ[ZZЮ]Q\ЩЭZ\ЩYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[ZZЮ]Q\ЩЭZ\ЩYЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУZ[ZZЮ]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУZ[ZZЮ]Q\ЩЭZ\ЩYЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУZ[ZZЮ]Q\ЩЭZ\ЩYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУZ[ZZЮ]Q\ЩЭZ\ЩYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУZ[ZZЮ]Pќ\ЭYЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KШќ\ЭYЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУZ[ZZЮ]Pќ\ЭYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KШќ\ЭYЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУZ[ZZЮ]Pќ\ЭYЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KШќ\ЭYШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУZ[ZZЮ]Pќ\ЭYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KШќ\ЭYЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[ZZЮ]Pќ\ЭYЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KШќ\ЭYЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧУZ[ZZЮ]Pќ\ЭYЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KШќ\ЭYЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WУZ[ZZЮ]Pќ\ЭYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KШќ\ЭYЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУZ[ZZЮ]Pќ\ЭYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[ZZЮ]KШќ\ЭYЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУRSRRЦUB‚€ЪY€СђSRSWР”•VTТ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРњќ^\ЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ^\ЪЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРњќ^\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ^\ЪЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРњќ^\ЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ^\ЪШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРњќ^\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ^\ЪЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Рњќ^\ЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шњќ^\ЪЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРњќ^\ЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шњќ^\ЪЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРњќ^\ЪЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Шњќ^\ЪЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРњќ^\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ^\ЪЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРњќ^\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ^\ЪЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWР”•VTТ‚€ЪY€СђSRSWСђSTB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС[\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС[\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС[\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС[\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С[\VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС[\VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС[\VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС[\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС[\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ССS—ОWУQQРWСU“УUSУ”В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС[\SYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС[\SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС[\SYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС[\SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫYYШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С[\SYYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧС[\SYYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WС[\SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС[\SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[\KЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ€Щ[™Y€ЛФССS—ОWУQQРWСU“УUSУ”В€Щ[™Y€ЛФСђSRSWСђSTB‚€ЪY€СђSRSWСSRTСB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС[Z\ЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[Z\ЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС[Z\ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[Z\ЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС[Z\ЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[Z\ЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС[Z\ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[Z\ЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С[Z\ЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[Z\ЩKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС[Z\ЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[Z\ЩKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС[Z\ЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ[Z\ЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС[Z\ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[Z\ЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС[Z\ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[Z\ЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСSRTСB‚€ЪY€СђSRSWТђS‘УSЧУВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ[™Ы[УЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™Ы[ЧЫЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ[™Ы[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™Ы[ЧЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ[™Ы[УЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™Ы[ЧЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ[™Ы[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™Ы[ЧЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т[™Ы[УЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™Ы[ЧЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ[™Ы[УЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™Ы[ЧЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ[™Ы[УЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™Ы[ЧЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ[™Ы[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™Ы[ЧЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ[™Ы[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™Ы[ЧЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТZШ[[УЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪZШ[[ЧЫЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТZШ[[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪZШ[[ЧЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТZШ[[УЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪZШ[[ЧЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТZШ[[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪZШ[[ЧЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТZШ[[УЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪZШ[[ЧЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТZШ[[УЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪZШ[[ЧЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТZШ[[УЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪZШ[[ЧЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТZШ[[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪZШ[[ЧЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТZШ[[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪZШ[[ЧЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТЫЫ[[УЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫ[[ЧЫЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТЫЫ[[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫ[[ЧЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТЫЫ[[УЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫ[[ЧЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТЫЫ[[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫ[[ЧЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТЫЫ[[УЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫ[[ЧЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТЫЫ[[УЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫ[[ЧЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТЫЫ[[УЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫ[[ЧЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТЫЫ[[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫ[[ЧЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТЫЫ[[УЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЫ[[ЧЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТђS‘УSЧУВ‚€ЪY€СђSRSWХTWТУТУВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\RЫЪЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЪЫЪЫЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\RЫЪЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЪЫЪЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\RЫЪЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЪЫЪЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\RЫЪЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЪЫЪЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\RЫЪЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЪЫЪЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\RЫЪЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЪЫЪЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\RЫЪЫЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЪЫЪЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\RЫЪЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЪЫЪЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\RЫЪЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЪЫЪЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХTWТУТУВ‚€ЪY€СђSRSWХTWУSB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\S[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫ[KШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\S[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫ[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\S[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫ[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\S[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫ[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\S[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫ[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\S[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫ[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\S[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫ[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\S[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫ[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\S[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЫ[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХTWУSB‚€ЪY€СђSRSWХTWР•SB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\Pќ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WШќ[KШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\Pќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WШќ[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\Pќ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WШќ[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\Pќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WШќ[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\Pќ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WШќ[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\Pќ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WШќ[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\Pќ[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\WШќ[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\Pќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WШќ[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\Pќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WШќ[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХTWР•SB‚€ЪY€СђSRSWХTWС’S’B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\Qљ[љVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЩљ[љKШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\Qљ[љVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЩљ[љKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\Qљ[љVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЩљ[љKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\Qљ[љVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЩљ[љKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\Qљ[љVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЩљ[љKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\Qљ[љVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЩљ[љKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\Qљ[љVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\WЩљ[љKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\Qљ[љVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЩљ[љKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\Qљ[љVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\WЩљ[љKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХTWС’S’B‚€ЪY€СђSRSWРУФУSСВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫЬЫ[ЩЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[ЩЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫЬЫ[ЩЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[ЩЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫЬЫ[ЩЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[ЩЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫЬЫ[ЩЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[ЩЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫЬЫ[ЩЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[ЩЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЫЬЫ[ЩЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[ЩЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫЬЫ[ЩЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[ЩЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫЬЫ[ЩЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[ЩЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫЬЫ[ЩЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[ЩЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫЬЫ[Щ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[Щ[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫЬЫ[Щ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[Щ[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫЬЫ[Щ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[Щ[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫЬЫ[Щ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[Щ[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫЬЫ[Щ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[Щ[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЫЬЫ[Щ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[Щ[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫЬЫ[Щ[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[Щ[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫЬЫ[Щ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[Щ[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫЬЫ[Щ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬЫ[Щ[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЫЫШ[[ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЫШ[[ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЫЫШ[[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЫШ[[ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЫЫШ[[ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЫШ[[ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЫЫШ[[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЫШ[[ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЫЫШ[[ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЫШ[[ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЫЫШ[[ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЫШ[[ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЫЫШ[[ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЫШ[[ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЫЫШ[[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЫШ[[ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЫЫШ[[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЫШ[[ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ[[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ[[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ[[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ[[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У[[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы[[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУ[[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы[[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ[[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы[[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ[[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ[[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРУФУSСВ‚€ЪY€СђSRSWУ’RSQУВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУљZ[YЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљZ[YЫЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУљZ[YЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљZ[YЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУљZ[YЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљZ[YЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУљZ[YЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљZ[YЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УљZ[YЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫљZ[YЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУљZ[YЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫљZ[YЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУљZ[YЫЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫљZ[YЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУљZ[YЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљZ[YЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУљZ[YЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљZ[YЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУ’RSQУВ‚€ЪY€СђSRSWР•V–•УУB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРќ^ћќЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шќ^ћќЫЫKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРќ^ћќЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шќ^ћќЫЫKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРќ^ћќЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шќ^ћќЫЫKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРќ^ћќЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шќ^ћќЫЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Рќ^ћќЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шќ^ћќЫЫKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРќ^ћќЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шќ^ћќЫЫKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРќ^ћќЫЫVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Шќ^ћќЫЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРќ^ћќЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шќ^ћќЫЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРќ^ћќЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шќ^ћќЫЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWР•V–•УУB‚€ЪY€СђSRSWФT“УSФРB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ\›Ы[ЬШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\›Ы[ЬШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ\›Ы[ЬШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\›Ы[ЬШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ\›Ы[ЬШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\›Ы[ЬШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ\›Ы[ЬШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\›Ы[ЬШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф\›Ы[ЬШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь\›Ы[ЬШKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ\›Ы[ЬШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь\›Ы[ЬШKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ\›Ы[ЬШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь\›Ы[ЬШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ\›Ы[ЬШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\›Ы[ЬШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ\›Ы[ЬШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\›Ы[ЬШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФT“УSФРB‚€ЪY€СђSRSWЦT’ТU‘QB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦ\љЪ]™YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\љЪ]™YKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦ\љЪ]™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\љЪ]™YKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦ\љЪ]™YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\љЪ]™YKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦ\љЪ]™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\љЪ]™YKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ц\љЪ]™YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю\љЪ]™YKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќЦ\љЪ]™YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю\љЪ]™YKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦ\љЪ]™YVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ю\љЪ]™YKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WЦ\љЪ]™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\љЪ]™YKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦ\љЪ]™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\љЪ]™YKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWЦT’ТU‘QB‚€ЪY€СђSRSWРСSTХQSB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЩ[\ЭY[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[\ЭY[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЩ[\ЭY[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[\ЭY[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЩ[\ЭY[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[\ЭY[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЩ[\ЭY[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[\ЭY[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЩ[\ЭY[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[\ЭY[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЩ[\ЭY[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[\ЭY[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЩ[\ЭY[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[\ЭY[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЩ[\ЭY[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[\ЭY[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЩ[\ЭY[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[\ЭY[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРСSTХQSB‚€ЪY€СђSRSWТРT•SђB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТШ\ќ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪШ\ќ[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТШ\ќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪШ\ќ[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТШ\ќ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪШ\ќ[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТШ\ќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪШ\ќ[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТШ\ќ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪШ\ќ[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТШ\ќ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪШ\ќ[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТШ\ќ[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪШ\ќ[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТШ\ќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪШ\ќ[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТШ\ќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪШ\ќ[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТРT•SђB‚€ЪY€СђSRSWСХV–“Ф‘€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЭ^ћ›Ь™ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ^ћ›Ь™Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЭ^ћ›Ь™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ^ћ›Ь™Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЭ^ћ›Ь™ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ^ћ›Ь™ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЭ^ћ›Ь™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ^ћ›Ь™ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЭ^ћ›Ь™ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ^ћ›Ь™ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЭ^ћ›Ь™ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ^ћ›Ь™Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЭ^ћ›Ь™ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ^ћ›Ь™ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЭ^ћ›Ь™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ^ћ›Ь™ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЭ^ћ›Ь™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ^ћ›Ь™ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСХV–“Ф‘‚€ЪY€СђSRSWУ‘PФ“Ц“PB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ™XЬ›Ю›XVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ™XЬ›Ю›XVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ™XЬ›Ю›XVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ™XЬ›Ю›XVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У™XЬ›Ю›XVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУ™XЬ›Ю›XVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ™XЬ›Ю›XVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ™XЬ›Ю›XVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ™XЬ›Ю›XVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€С•TТSУ—С“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ™XЬ›Ю›XQ\ЪУX[™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ\ЪЧЫX[™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ™XЬ›Ю›XQ\ЪУX[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ\ЪЧЫX[™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ™XЬ›Ю›XQ\ЪУX[™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ\ЪЧЫX[™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ™XЬ›Ю›XQ\ЪУX[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ\ЪЧЫX[™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У™XЬ›Ю›XQ\ЪУX[™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ\ЪЧЫX[™KЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ™XЬ›Ю›XQ\ЪУX[™VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ\ЪЧЫX[™KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ™XЬ›Ю›XQ\ЪУX[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ\ЪЧЫX[™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ™XЬ›Ю›XQ\ЪУX[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ\ЪЧЫX[™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ™XЬ›Ю›XQ]Ы•Ъ[™ЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ]Ы—ЭЪ[™ЬЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ™XЬ›Ю›XQ]Ы•Ъ[™ЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ]Ы—ЭЪ[™ЬЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ™XЬ›Ю›XQ]Ы•Ъ[™ЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ]Ы—ЭЪ[™ЬЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ™XЬ›Ю›XQ]Ы•Ъ[™ЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ]Ы—ЭЪ[™ЬЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У™XЬ›Ю›XQ]Ы•Ъ[™ЬЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ]Ы—ЭЪ[™ЬЛЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ™XЬ›Ю›XQ]Ы•Ъ[™ЬЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ]Ы—ЭЪ[™ЬЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ™XЬ›Ю›XQ]Ы•Ъ[™ЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ]Ы—ЭЪ[™ЬЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ™XЬ›Ю›XQ]Ы•Ъ[™ЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЩ]Ы—ЭЪ[™ЬЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ХSђWР•T”ХС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ™XЬ›Ю›XU[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЭ[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ™XЬ›Ю›XU[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЭ[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ™XЬ›Ю›XU[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЭ[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ™XЬ›Ю›XU[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЭ[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У™XЬ›Ю›XU[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЭ[KЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ™XЬ›Ю›XU[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЭ[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ™XЬ›Ю›XU[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЭ[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ™XЬ›Ю›XU[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы™XЬ›Ю›XKЭ[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФХSђWР•T”ХС“Ф“TВ€Щ[™Y€ЛФС•TТSУ—С“Ф“TВ€Щ[™Y€ЛФСђSRSWУ‘PФ“Ц“PB‚€ЪY€СђSRSWУPQСPT“ђB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXYЩX\›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXYЩX\›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXYЩX\›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXYЩX\›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXYЩX\›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУXYЩX\›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXYЩX\›VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУXYЩX\›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXYЩX\›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXYЩX\›SЬљYЪ[[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXYЩX\›SЬљYЪ[[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXYЩX\›SЬљYЪ[[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXYЩX\›SЬљYЪ[[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXYЩX\›SЬљYЪ[[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXYЩX\›SЬљYЪ[[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУXYЩX\›SЬљYЪ[[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXYЩX\›SЬљYЪ[[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ССS—ОWУQQРWСU“УUSУ”В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXYЩX\›SYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXYЩX\›SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXYЩX\›SYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXYЩX\›SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫYYШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXYЩX\›SYYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXYЩX\›SYYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WУXYЩX\›SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXYЩX\›SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXYЩX\›SЬљYЪ[[YYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXYЩX\›SЬљYЪ[[YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXYЩX\›SЬљYЪ[[YYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXYЩX\›SЬљYЪ[[YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫYYШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXYЩX\›SЬљYЪ[[YYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXYЩX\›SЬљYЪ[[YYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WУXYЩX\›SЬљYЪ[[YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXYЩX\›SЬљYЪ[[YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXYЩX\›KЫЬљYЪ[[ШЫЫЬ‹ЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ€Щ[™Y€ЛФССS—ОWУQQРWСU“УUSУ”В€Щ[™Y€ЛФСђSRSWУPQСPT“ђB‚€ЪY€СђSRSWУPT”ТQХВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУX\њЪYЭЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\њЪYЭЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУX\њЪYЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\њЪYЭЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУX\њЪYЭЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\њЪYЭЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУX\њЪYЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\њЪYЭЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УX\њЪYЭЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX\њЪYЭЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУX\њЪYЭЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX\њЪYЭЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУX\њЪYЭЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫX\њЪYЭЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУX\њЪYЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\њЪYЭЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУX\њЪYЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\њЪYЭЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУPT”ТQХВ‚€ЪY€СђSRSWФТTУB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪ\ЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ\ЫKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЪ\ЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ\ЫKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪ\ЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ\ЫKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ\ЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ\ЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪ\ЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ\ЫKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪ\ЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ\ЫKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪ\ЫVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ\ЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪ\ЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ\ЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪ\ЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ\ЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУYШ[Y[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫYШ[Y[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУYШ[Y[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫYШ[Y[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУYШ[Y[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫYШ[Y[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУYШ[Y[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫYШ[Y[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УYШ[Y[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫYШ[Y[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУYШ[Y[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫYШ[Y[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУYШ[Y[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫYШ[Y[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУYШ[Y[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫYШ[Y[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУYШ[Y[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫYШ[Y[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФТTУB‚€ЪY€СђSRSWФХRРURРB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЭZШ]ZШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭZШ]ZШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЭZШ]ZШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭZШ]ZШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЭZШ]ZШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭZШ]ZШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЭZШ]ZШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭZШ]ZШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЭZШ]ZШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭZШ]ZШKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЭZШ]ZШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭZШ]ZШKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЭZШ]ZШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭZШ]ZШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЭZШ]ZШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭZШ]ZШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЭZШ]ZШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭZШ]ZШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФХRРURРB‚€ЪY€СђSRSWР“PСTSУ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР›XЩ\[Ы–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›XЩ\[Ы‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР›XЩ\[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›XЩ\[Ы‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР›XЩ\[Ы–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›XЩ\[Ы‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР›XЩ\[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›XЩ\[Ы‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р›XЩ\[Ы–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›XЩ\[Ы‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР›XЩ\[Ы–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›XЩ\[Ы‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР›XЩ\[Ы–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш›XЩ\[Ы‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР›XЩ\[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›XЩ\[Ы‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР›XЩ\[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›XЩ\[Ы‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWР“PСTSУ‚‚€ЪY€СђSRSWЦ‘TђSФђB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦ™\[ЬVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦ™\[ЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦ™\[ЬVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦ™\[ЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ц™\[ЬVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќЦ™\[ЬVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦ™\[ЬVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WЦ™\[ЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦ™\[ЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ССS—ОWУQQРWСU“УUSУ”В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦ™\[ЬSYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦ™\[ЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦ™\[ЬSYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦ™\[ЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫYYШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ц™\[ЬSYYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦ™\[ЬSYYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WЦ™\[ЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦ™\[ЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю™\[ЬKЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ€Щ[™Y€ЛФССS—ОWУQQРWСU“УUSУ”В€Щ[™Y€ЛФСђSRSWЦ‘TђSФђB‚€ЪY€СђSRSWУQSS‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУY[[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУY[[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУY[[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУY[[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УY[[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУY[[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУY[[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУY[[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУY[[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУY[Y][ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУY[Y][ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУY[Y][ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУY[Y][ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УY[Y][ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУY[Y][ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУY[Y][ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУY[Y][ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУY[Y][ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУY[Y][ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУY[Y][ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУY[Y][ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУY[Y][ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УY[Y][ЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧУY[Y][ЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WУY[Y][ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУY[Y][ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[Y][ЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWУQSS‚‚€ЪY€СђSRSWСФ“УТСVB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЬ›ЫЪЩ^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ›ЫЪЩ^KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЬ›ЫЪЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ›ЫЪЩ^KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЬ›ЫЪЩ^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ›ЫЪЩ^KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЬ›ЫЪЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ›ЫЪЩ^KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЬ›ЫЪЩ^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ›ЫЪЩ^KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЬ›ЫЪЩ^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ›ЫЪЩ^KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЬ›ЫЪЩ^VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ›ЫЪЩ^KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЬ›ЫЪЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ›ЫЪЩ^KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЬ›ЫЪЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ›ЫЪЩ^KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХШXЪЩ^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШXЪЩ^KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХШXЪЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШXЪЩ^KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХШXЪЩ^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШXЪЩ^KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХШXЪЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШXЪЩ^KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХШXЪЩ^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭШXЪЩ^KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХШXЪЩ^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭШXЪЩ^KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХШXЪЩ^VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭШXЪЩ^KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХШXЪЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШXЪЩ^KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХШXЪЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШXЪЩ^KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФљ[X›ЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФљ[X›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФљ[X›ЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФљ[X›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Фљ[X›ЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФљ[X›ЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФљ[X›ЫЫVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФљ[X›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФљ[X›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФљ[X›ЫЫQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФљ[X›ЫЫQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФљ[X›ЫЫQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФљ[X›ЫЫQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Фљ[X›ЫЫQЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧФљ[X›ЫЫQЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WФљ[X›ЫЫQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФљ[X›ЫЫQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ьљ[X›ЫЫKЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWСФ“УТСVB‚€ЪY€СђSRSWФРУФђ•S“–B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШЫЬќ[›ћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЬќ[›ћKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШЫЬќ[›ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЬќ[›ћKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШЫЬќ[›ћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЬќ[›ћKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШЫЬќ[›ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЬќ[›ћKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШЫЬќ[›ћVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЬќ[›ћKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФШЫЬќ[›ћVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЬќ[›ћKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШЫЬќ[›ћVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЬќ[›ћKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФШЫЬќ[›ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЬќ[›ћKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШЫЬќ[›ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЬќ[›ћKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФX›ЫЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬX›ЫЭЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФX›ЫЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬX›ЫЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФX›ЫЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬX›ЫЭШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФX›ЫЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬX›ЫЭЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФX›ЫЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬX›ЫЭЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФX›ЫЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬX›ЫЭЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФX›ЫЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬX›ЫЭЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФX›ЫЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬX›ЫЭЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФX›ЫЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬX›ЫЭЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЪ[™\XЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЪ[™\XЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЪ[™\XЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЪ[™\XЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЪ[™\XЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЪ[™\XЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЪ[™\XЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЪ[™\XЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЪ[™\XЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЪ[™\XЩQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЪ[™\XЩQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЪ[™\XЩQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЪ[™\XЩQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЪ[™\XЩQЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЪ[™\XЩQЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WРЪ[™\XЩQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЪ[™\XЩQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[™\XЩKЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWФРУФђ•S“–B‚€ЪY€СђSRSWФУРђ“B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЫШ›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫШ›KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЫШ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫШ›KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЫШ›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫШ›KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЫШ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫШ›KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЫШ›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫШ›KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЫШ›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫШ›KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЫШ›VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫШ›KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЫШ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫШ›KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЫШ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫШ›KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСљ^ћљ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ^ћљ[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСљ^ћљ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ^ћљ[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСљ^ћљ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ^ћљ[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСљ^ћљ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ^ћљ[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Сљ^ћљ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щљ^ћљ[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСљ^ћљ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щљ^ћљ[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСљ^ћљ[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щљ^ћљ[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСљ^ћљ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ^ћљ[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСљ^ћљ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ^ћљ[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ[ќ[[Ы–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ[ќ[[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ[ќ[[Ы–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ[ќ[[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т[ќ[[Ы–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ[ќ[[Ы–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ[ќ[[Ы–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ[ќ[[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ[ќ[[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ[ќ[[Ы‘ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ[ќ[[Ы‘ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ[ќ[[Ы‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ[ќ[[Ы‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т[ќ[[Ы‘ЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ[ќ[[Ы‘ЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WТ[ќ[[Ы‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ[ќ[[Ы‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[ќ[[Ы‹ЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWФУРђ“B‚€ЪY€СђSRSWФТХУХ‘U€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪЭЫЭ™]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЭЫЭ™]Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЪЭЫЭ™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЭЫЭ™]Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪЭЫЭ™]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЭЫЭ™]ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪЭЫЭ™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЭЫЭ™]ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪЭЫЭ™]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЭЫЭ™]ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪЭЫЭ™]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЭЫЭ™]Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪЭЫЭ™]ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЭЫЭ™]ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪЭЫЭ™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЭЫЭ™]ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪЭЫЭ™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЭЫЭ™]ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЬ™YY[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™YY[ќЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЬ™YY[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™YY[ќЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЬ™YY[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™YY[ќШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЬ™YY[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™YY[ќЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЬ™YY[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™YY[ќЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЬ™YY[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™YY[ќЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЬ™YY[ќЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™YY[ќЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЬ™YY[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™YY[ќЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЬ™YY[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™YY[ќЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФТХУХ‘U‚€ЪY€СђSRSWФ“УТТQQB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ›ЫЪЪYYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫЪЪYYKШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ›ЫЪЪYYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫЪЪYYKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ›ЫЪЪYYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫЪЪYYKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ›ЫЪЪYYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫЪЪYYKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф›ЫЪЪYYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫЪЪYYKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ›ЫЪЪYYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫЪЪYYKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ›ЫЪЪYYVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫЪЪYYKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ›ЫЪЪYYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫЪЪYYKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ›ЫЪЪYYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫЪЪYYKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫЬќљ\Ь]Z\™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљ\Ь]Z\™KШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫЬќљ\Ь]Z\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљ\Ь]Z\™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫЬќљ\Ь]Z\™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљ\Ь]Z\™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫЬќљ\Ь]Z\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљ\Ь]Z\™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫЬќљ\Ь]Z\™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљ\Ь]Z\™KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЫЬќљ\Ь]Z\™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљ\Ь]Z\™KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫЬќљ\Ь]Z\™VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљ\Ь]Z\™KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫЬќљ\Ь]Z\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљ\Ь]Z\™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫЬќљ\Ь]Z\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљ\Ь]Z\™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫЬќљZЫљYЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫЬќљZЫљYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫЬќљZЫљYЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫЬќљZЫљYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫЬќљZЫљYЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЫЬќљZЫљYЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫЬќљZЫљYЪЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫЬќљZЫљYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫЬќљZЫљYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫЬќљZЫљYЪЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫЬќљZЫљYЪЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫЬќљZЫљYЪЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫЬќљZЫљYЪЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫЬќљZЫљYЪЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫЬќљZЫљYЪЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫЬќљZЫљYЪЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫЬќљZЫљYЪЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬќљZЫљYЪЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWФ“УТТQQB‚€ЪY€СђSRSWР“T•QВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР›\ќYЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›\ќYЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР›\ќYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›\ќYЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР›\ќYЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›\ќYЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР›\ќYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›\ќYЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р›\ќYЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›\ќYЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР›\ќYЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›\ќYЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР›\ќYЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш›\ќYЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР›\ќYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›\ќYЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР›\ќYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›\ќYЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЭ\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЭ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЭ\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЭ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЭ\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЭ\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЭ\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЭ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЭ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЭ\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЬ™Y]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЬ™Y]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЬ™Y]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЬ™Y]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЬ™Y]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУЬ™Y]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЬ™Y]VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЬ™Y]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЬ™Y]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЬ™Y]QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЬ™Y]QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЬ™Y]QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЬ™Y]QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЬ™Y]QЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЬ™Y]QЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WУЬ™Y]QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЬ™Y]QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬ™Y]KЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWР“T•QВ‚€ЪY€СђSRSWУ’PТТU€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУљXЪЪ]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљXЪЪ]Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУљXЪЪ]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљXЪЪ]Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУљXЪЪ]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљXЪЪ]ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУљXЪЪ]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљXЪЪ]ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УљXЪЪ]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫљXЪЪ]ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУљXЪЪ]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫљXЪЪ]Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУљXЪЪ]ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫљXЪЪ]ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУљXЪЪ]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљXЪЪ]ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУљXЪЪ]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫљXЪЪ]ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХY]ќ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭY]ќ[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХY]ќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭY]ќ[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХY]ќ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭY]ќ[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХY]ќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭY]ќ[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХY]ќ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭY]ќ[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХY]ќ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭY]ќ[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХY]ќ[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭY]ќ[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХY]ќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭY]ќ[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХY]ќ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭY]ќ[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУ’PТТU‚€ЪY€СђSRSWСУФФТQ“UT‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫЬЬЪY›]\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЬЬЪY›]\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫЬЬЪY›]\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЬЬЪY›]\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫЬЬЪY›]\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЬЬЪY›]\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫЬЬЪY›]\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЬЬЪY›]\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫЬЬЪY›]\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЬЬЪY›]\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЫЬЬЪY›]\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЬЬЪY›]\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫЬЬЪY›]\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЬЬЪY›]\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫЬЬЪY›]\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЬЬЪY›]\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫЬЬЪY›]\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЬЬЪY›]\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС[YЫЬЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[YЫЬЬЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС[YЫЬЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[YЫЬЬЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС[YЫЬЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[YЫЬЬЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС[YЫЬЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[YЫЬЬЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С[YЫЬЬЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[YЫЬЬЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС[YЫЬЬЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[YЫЬЬЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС[YЫЬЬЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ[YЫЬЬЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС[YЫЬЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[YЫЬЬЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС[YЫЬЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[YЫЬЬЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСУФФТQ“UT‚‚€ЪY€СђSRSWХУУУУВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЫЫЫЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЫЫЫЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЫЫЫЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЫЫЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЫЫЫЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЫЫЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЫЫЫЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЫЫЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЫЫЫЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЫЫЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЫЫЫЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЫЫЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЫЫЫЫЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЫЫЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЫЫЫЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЫЫЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЫЫЫЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЫЫЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСXќЫЫЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXќЫЫЫЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСXќЫЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXќЫЫЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСXќЫЫЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXќЫЫЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСXќЫЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXќЫЫЫЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СXќЫЫЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩXќЫЫЫЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСXќЫЫЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩXќЫЫЫЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСXќЫЫЫЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩXќЫЫЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСXќЫЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXќЫЫЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСXќЫЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXќЫЫЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХУУУУВ‚€ЪY€СђSRSWРТUХB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЪ]ЭVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ]ЭKШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЪ]ЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ]ЭKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЪ]ЭVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ]ЭKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЪ]ЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ]ЭKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЪ]ЭVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ]ЭKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЪ]ЭVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ]ЭKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЪ]ЭVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ]ЭKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЪ]ЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ]ЭKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЪ]ЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ]ЭKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС™Y]ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС™Y]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС™Y]ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС™Y]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С™Y]ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС™Y]ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС™Y]ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС™Y]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС™Y]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС™Y]СЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС™Y]СЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС™Y]СЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС™Y]СЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С™Y]СЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧС™Y]СЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WС™Y]СЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС™Y]СЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y]ЛЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWРТUХB‚€ЪY€СђSRSWЦPSTT‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦX[\\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮX[\\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦX[\\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮX[\\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦX[\\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮX[\\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦX[\\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮX[\\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ЦX[\\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЮX[\\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќЦX[\\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЮX[\\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦX[\\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЮX[\\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WЦX[\\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮX[\\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦX[\\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮX[\\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР›Ы[™ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Ы[™Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР›Ы[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Ы[™Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР›Ы[™ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Ы[™ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР›Ы[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Ы[™ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р›Ы[™ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›Ы[™ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР›Ы[™ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›Ы[™Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР›Ы[™ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш›Ы[™ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР›Ы[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Ы[™ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР›Ы[™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›Ы[™ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWЦPSTT‚‚€ЪY€СђSRSWФ“УPУУB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ›ЫXЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫXЫЫKШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ›ЫXЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫXЫЫKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ›ЫXЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫXЫЫKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ›ЫXЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫXЫЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф›ЫXЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫXЫЫKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ›ЫXЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫXЫЫKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ›ЫXЫЫVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫXЫЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ›ЫXЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫXЫЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ›ЫXЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›ЫXЫЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРШ\љЫЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\љЫЫШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРШ\љЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\љЫЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРШ\љЫЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\љЫЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРШ\љЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\љЫЫЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РШ\љЫЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШШ\љЫЫЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРШ\љЫЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШШ\љЫЫЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРШ\љЫЫЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШШ\љЫЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРШ\љЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\љЫЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРШ\љЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\љЫЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫШ[ЬЬШ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫШ[ЬЬШ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫШ[ЬЬШ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫШ[ЬЬШ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫШ[ЬЬШ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЫШ[ЬЬШ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫШ[ЬЬШ[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫШ[ЬЬШ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫШ[ЬЬШ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫШ[ЬЬШ[ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫШ[ЬЬШ[ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫШ[ЬЬШ[ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫШ[ЬЬШ[ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫШ[ЬЬШ[ЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫШ[ЬЬШ[ЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫШ[ЬЬШ[ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫШ[ЬЬШ[ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ[ЬЬШ[ЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWФ“УPУУB‚€ЪY€СђSRSWРTS‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\[‹Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС›\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС›\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС›\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС›\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С›\VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС›\VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС›\VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС›\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС›\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС›\QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС›\QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС›\QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС›\QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С›\QЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧС›\QЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WС›\QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС›\QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\KЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\][–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\][–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\][–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\][–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\][–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\][–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\][–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\][–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\][–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\][‘ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\][‘ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\][‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\][‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\][‘ЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\][‘ЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WР\][‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\][‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\][‹ЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ‚€ЪY€ССS—ОWРФ“ФФЧСU“ФВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС\[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС\[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС\[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС\[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С\[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ\[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС\[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ\[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС\[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ\[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС\[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС\[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТY\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪY\KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТY\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪY\KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТY\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪY\KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТY\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪY\KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТY\VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪY\KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТY\VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪY\KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТY\VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪY\KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТY\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪY\KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТY\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪY\KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФССS—ОWРФ“ФФЧСU“ФВ€Щ[™Y€ЛФСђSRSWРTS‚‚€ЪY€СђSRSWФТSPУР”ђB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪ[XЫШњVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[XЫШњKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЪ[XЫШњVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[XЫШњKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪ[XЫШњVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[XЫШњKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[XЫШњVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[XЫШњKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪ[XЫШњVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[XЫШњKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪ[XЫШњVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[XЫШњKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪ[XЫШњVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[XЫШњKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪ[XЫШњVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[XЫШњKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪ[XЫШњVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[XЫШњKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШ[™XЫЫ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШ[™XЫЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШ[™XЫЫ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШ[™XЫЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШ[™XЫЫ™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФШ[™XЫЫ™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШ[™XЫЫ™VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФШ[™XЫЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШ[™XЫЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШ[™XЫЫ™QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШ[™XЫЫ™QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШ[™XЫЫ™QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШ[™XЫЫ™QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШ[™XЫЫ™QЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШ[™XЫЫ™QЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WФШ[™XЫЫ™QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШ[™XЫЫ™QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™XЫЫ™KЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWФТSPУР”ђB‚€ЪY€СђSRSWРФђSSФђS•€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЬ[[Ь[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЬ[[Ь[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЬ[[Ь[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЬ[[Ь[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЬ[[Ь[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЬ[[Ь[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЬ[[Ь[ќЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЬ[[Ь[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЬ[[Ь[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЬ[[Ь[ќЭ[[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЭ[[™ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЬ[[Ь[ќЭ[[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЭ[[™ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЬ[[Ь[ќЭ[[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЭ[[™ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЬ[[Ь[ќЭ[[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЭ[[™ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЬ[[Ь[ќЭ[[™ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЭ[[™ЛЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЬ[[Ь[ќЭ[[™ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЭ[[™ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WРЬ[[Ь[ќЭ[[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЭ[[™ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЬ[[Ь[ќЭ[[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЭ[[™ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЬ[[Ь[ќЫЬ™Ъ[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЫЬ™Ъ[™ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЬ[[Ь[ќЫЬ™Ъ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЫЬ™Ъ[™ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЬ[[Ь[ќЫЬ™Ъ[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЫЬ™Ъ[™ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЬ[[Ь[ќЫЬ™Ъ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЫЬ™Ъ[™ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЬ[[Ь[ќЫЬ™Ъ[™ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЫЬ™Ъ[™ЛЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЬ[[Ь[ќЫЬ™Ъ[™ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЫЬ™Ъ[™ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WРЬ[[Ь[ќЫЬ™Ъ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЫЬ™Ъ[™ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЬ[[Ь[ќЫЬ™Ъ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ[[Ь[ќЩЫЬ™Ъ[™ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРФђSSФђS•‚€ЪY€СђSRSWРT”“ТХQB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\њ›ЪЭYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ›ЪЭYKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\њ›ЪЭYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ›ЪЭYKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\њ›ЪЭYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ›ЪЭYKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\њ›ЪЭYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ›ЪЭYKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\њ›ЪЭYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ›ЪЭYKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\њ›ЪЭYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ›ЪЭYKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\њ›ЪЭYVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ›ЪЭYKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\њ›ЪЭYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ›ЪЭYKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\њ›ЪЭYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ›ЪЭYKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\њ\ЪЩ]ЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ\ЪЩ]ЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\њ\ЪЩ]ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ\ЪЩ]ЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\њ\ЪЩ]ЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ\ЪЩ]ЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\њ\ЪЩ]ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ\ЪЩ]ЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\њ\ЪЩ]ЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ\ЪЩ]ЩKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\њ\ЪЩ]ЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ\ЪЩ]ЩKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\њ\ЪЩ]ЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ\ЪЩ]ЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\њ\ЪЩ]ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ\ЪЩ]ЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\њ\ЪЩ]ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\њ\ЪЩ]ЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРT”“ТХQB‚€ЪY€СђSRSWХЦS€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЮ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЮ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЮ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЮ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЮ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЮ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЮ[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЮ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЮ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮ[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЮљXЪ]P[\YЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЮљXЪ]P[\YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЮљXЪ]P[\YЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЮљXЪ]P[\YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЮљXЪ]P[\YЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЮљXЪ]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЮљXЪ]P[\YЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЮљXЪ]P[\YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЮљXЪ]P[\YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЮљXЪ]SЭТЩ^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭЧЪЩ^KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЮљXЪ]SЭТЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭЧЪЩ^KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЮљXЪ]SЭТЩ^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭЧЪЩ^KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЮљXЪ]SЭТЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭЧЪЩ^KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЮљXЪ]SЭТЩ^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭЧЪЩ^KЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЮљXЪ]SЭТЩ^VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭЧЪЩ^KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЮљXЪ]SЭТЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭЧЪЩ^KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЮљXЪ]SЭТЩ^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЫЭЧЪЩ^KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЮљXЪ]QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЮљXЪ]QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЮљXЪ]QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЮљXЪ]QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЮљXЪ]QЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЮљXЪ]QЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WХЮљXЪ]QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЮљXЪ]QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЮљXЪ]KЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWХЦS‚€ЪY€СђSRSWФТV–“TQB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪ^ћ›\YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ^ћ›\YKШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЪ^ћ›\YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ^ћ›\YKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪ^ћ›\YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ^ћ›\YKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ^ћ›\YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ^ћ›\YKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪ^ћ›\YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ^ћ›\YKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪ^ћ›\YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ^ћ›\YKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪ^ћ›\YVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ^ћ›\YKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪ^ћ›\YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ^ћ›\YKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪ^ћ›\YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ^ћ›\YKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЩ[ќ\ЪЫЬЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЩ[ќ\ЪЫЬЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЩ[ќ\ЪЫЬЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЩ[ќ\ЪЫЬЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЩ[ќ\ЪЫЬЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЩ[ќ\ЪЫЬЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЩ[ќ\ЪЫЬЪЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЩ[ќ\ЪЫЬЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЩ[ќ\ЪЫЬЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЩ[ќ\ЪЫЬЪЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЩ[ќ\ЪЫЬЪЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЩ[ќ\ЪЫЬЪЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЩ[ќ\ЪЫЬЪЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЩ[ќ\ЪЫЬЪЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЩ[ќ\ЪЫЬЪЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WРЩ[ќ\ЪЫЬЪЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЩ[ќ\ЪЫЬЪЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ[ќ\ЪЫЬЪЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWФТV–“TQB‚€ЪY€СђSRSWРУРђ“ФTВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫШ›Ь\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ›Ь\ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫШ›Ь\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ›Ь\ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫШ›Ь\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ›Ь\ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫШ›Ь\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ›Ь\ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫШ›Ь\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ›Ь\ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЫШ›Ь\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ›Ь\ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫШ›Ь\ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ›Ь\ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫШ›Ь\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ›Ь\ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫШ›Ь\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫШ›Ь\ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЬ\ШЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ\ШЭЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЬ\ШЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ\ШЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЬ\ШЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ\ШЭШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЬ\ШЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ\ШЭЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЬ\ШЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ\ШЭЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЬ\ШЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ\ШЭЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЬ\ШЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ\ШЭЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЬ\ШЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ\ШЭЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЬ\ШЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ\ШЭЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРУРђ“ФTВ‚€ЪY€СђSRSWФТS’TХPB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪ[љ\ЭXVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭXKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЪ[љ\ЭXVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭXKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪ[љ\ЭXVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭXKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[љ\ЭXVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭXKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪ[љ\ЭXVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭXKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪ[љ\ЭXVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭXKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪ[љ\ЭXVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭXKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪ[љ\ЭXVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭXKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪ[љ\ЭXVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭXKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЫXYЩZ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫXYЩZ\ЭЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЫXYЩZ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫXYЩZ\ЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЫXYЩZ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫXYЩZ\ЭШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЫXYЩZ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫXYЩZ\ЭЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЫXYЩZ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫXYЩZ\ЭЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЫXYЩZ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫXYЩZ\ЭЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЫXYЩZ\ЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫXYЩZ\ЭЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЫXYЩZ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫXYЩZ\ЭЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЫXYЩZ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫXYЩZ\ЭЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФТS’TХPB‚€ЪY€СђSRSWТUS“ђB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ][›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ][›KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ][›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ][›KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ][›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ][›KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ][›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ][›KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т][›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ][›KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ][›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ][›KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ][›VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ][›KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ][›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ][›KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ][›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ][›KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ]™[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]™[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ]™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]™[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ]™[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]™[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ]™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]™[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т]™[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ]™[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ]™[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ]™[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ]™[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ]™[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ]™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]™[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ]™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]™[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ]\™[™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ]\™[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ]\™[™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ]\™[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т]\™[™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ]\™[™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ]\™[™VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ]\™[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ]\™[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ]\™[™QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ]\™[™QЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ]\™[™QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ]\™[™QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т]\™[™QЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ]\™[™QЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WТ]\™[™QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ]\™[™QЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ]\™[™KЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWТUS“ђB‚€ЪY€СђSRSWТSTQST€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ[\Y[\ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[\Y[\Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ[\Y[\ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[\Y[\Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ[\Y[\ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[\Y[\ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ[\Y[\ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[\Y[\ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т[\Y[\ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[\Y[\ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ[\Y[\ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[\Y[\Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ[\Y[\ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[\Y[\ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ[\Y[\ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[\Y[\ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ[\Y[\ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[\Y[\ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ[Ь™Ь™[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™Ь™[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ[Ь™Ь™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™Ь™[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ[Ь™Ь™[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™Ь™[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ[Ь™Ь™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™Ь™[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У[Ь™Ь™[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™Ь™[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУ[Ь™Ь™[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™Ь™[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ[Ь™Ь™[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™Ь™[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ[Ь™Ь™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™Ь™[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ[Ь™Ь™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[Ь™Ь™[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЬљ[[\Ы\›ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЬљ[[\Ы\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЬљ[[\Ы\›ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЬљ[[\Ы\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЬљ[[\Ы\›ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЬљ[[\Ы\›ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЬљ[[\Ы\›ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЬљ[[\Ы\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЬљ[[\Ы\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЬљ[[\Ы\›ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЬљ[[\Ы\›ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЬљ[[\Ы\›ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЬљ[[\Ы\›ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЬљ[[\Ы\›ЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЬљ[[\Ы\›ЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WСЬљ[[\Ы\›ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЬљ[[\Ы\›ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬљ[[\Ы\›ЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWТSTQST‚€ЪY€СђSRSWУRSСT–B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУZ[Щ\ћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[Щ\ћKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУZ[Щ\ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[Щ\ћKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУZ[Щ\ћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[Щ\ћKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУZ[Щ\ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[Щ\ћKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ[Щ\ћVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[Щ\ћKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУZ[Щ\ћVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[Щ\ћKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУZ[Щ\ћVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[Щ\ћKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУZ[Щ\ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[Щ\ћKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУZ[Щ\ћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ[Щ\ћKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР[Ь™[ZYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР[Ь™[ZYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР[Ь™[ZYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYTЭ]Ш™\њћU[љ[PЬ™X[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЪXЫЫ‹ЌњЉNВ€ЛШЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYTЭ]Ш™\њћTќXћPЬ™X[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬќXћWШЬ™X[KЪXЫЫ‹ЌњЉNВ€ЛШЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYTЭ]Ш™\њћSX]ЪPЬ™X[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫX]ЪWШЬ™X[KЪXЫЫ‹ЌњЉNВ€ЛШЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYTЭ]Ш™\њћSZ[ќЬ™X[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫZ[ќШЬ™X[KЪXЫЫ‹ЌњЉNВ€ЛШЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYTЭ]Ш™\њћS[[ЫђЬ™X[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫ[[Ы—ШЬ™X[KЪXЫЫ‹ЌњЉNВ€ЛШЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYTЭ]Ш™\њћTШ[YЬ™X[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬШ[YШЬ™X[KЪXЫЫ‹ЌњЉNВ€ЛШЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYTЭ]Ш™\њћTќXћTЭЪ\›ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬќXћWЬЭЪ\›ЪXЫЫ‹ЌњЉNВ€ЛШЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYTЭ]Ш™\њћPШ\[Y[ЭЪ\›ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШШ\[Y[ЬЭЪ\›ЪXЫЫ‹ЌњЉNВ€ЛШЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYTЭ]Ш™\њћTZ[›ЭФЭЪ\›ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬZ[›ЭЧЬЭЪ\›ЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР[Ь™[ZYTЭ]Ш™\њћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ]Ш™\њћU[љ[PЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWЩY][™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ]Ш™\њћTќXћPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWЬќXћWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ]Ш™\њћSX]ЪPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWЫX]ЪWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ]Ш™\њћSZ[ќЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWЫZ[ќШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ]Ш™\њћS[[ЫђЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWЫ[[Ы—ШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ]Ш™\њћTШ[YЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWЬШ[YШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ]Ш™\њћTќXћTЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWЬќXћWЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ]Ш™\њћPШ\[Y[ЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWШШ\[Y[ЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ]Ш™\њћTZ[›ЭФЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWЬZ[›ЭЧЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР[Ь™[ZYTЭ]Ш™\њћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР[Ь™[ZYTЭ]Ш™\њћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЬЭ]Ш™\њћWЬЪ[ћK™Ш\[ЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР[Ь™[ZYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР[Ь™[ZYP™\њћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYP™\њћU[љ[PЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWЩY][™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYP™\њћTќXћPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWЬќXћWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYP™\њћSX]ЪPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWЫX]ЪWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYP™\њћSZ[ќЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWЫZ[ќШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYP™\њћS[[ЫђЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWЫ[[Ы—ШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYP™\њћTШ[YЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWЬШ[YШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYP™\њћTќXћTЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWЬќXћWЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYP™\њћPШ\[Y[ЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWШШ\[Y[ЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYP™\њћTZ[›ЭФЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWЬZ[›ЭЧЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР[Ь™[ZYP™\њћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР[Ь™[ZYP™\њћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШ™\њћKШ™\њћWЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР[Ь™[ZYSЭ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYSЭ™U[љ[PЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WЩY][™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYSЭ™TќXћPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WЬќXћWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYSЭ™SX]ЪPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WЫX]ЪWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYSЭ™SZ[ќЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WЫZ[ќШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYSЭ™S[[ЫђЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WЫ[[Ы—ШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYSЭ™TШ[YЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WЬШ[YШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYSЭ™TќXћTЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WЬќXћWЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYSЭ™PШ\[Y[ЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WШШ\[Y[ЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYSЭ™TZ[›ЭФЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WЬZ[›ЭЧЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР[Ь™[ZYSЭ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР[Ь™[ZYSЭ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЫЭ™KЫЭ™WЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР[Ь™[ZYTЭ\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ\•[љ[PЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—ЩY][™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ\”ќXћPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—ЬќXћWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ\“X]ЪPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—ЫX]ЪWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ\“Z[ќЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—ЫZ[ќШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ\“[[ЫђЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—Ы[[Ы—ШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ\”Ш[YЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—ЬШ[YШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ\”ќXћTЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—ЬќXћWЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ\ђШ\[Y[ЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—ШШ\[Y[ЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTЭ\”Z[›ЭФЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—ЬZ[›ЭЧЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР[Ь™[ZYTЭ\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР[Ь™[ZYTЭ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ\‹ЬЭ\—ЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР[Ь™[ZYPЫЭ™\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYPЫЭ™\•[љ[PЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—ЩY][™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYPЫЭ™\”ќXћPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—ЬќXћWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYPЫЭ™\“X]ЪPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—ЫX]ЪWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYPЫЭ™\“Z[ќЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—ЫZ[ќШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYPЫЭ™\“[[ЫђЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—Ы[[Ы—ШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYPЫЭ™\”Ш[YЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—ЬШ[YШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYPЫЭ™\”ќXћTЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—ЬќXћWЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYPЫЭ™\ђШ\[Y[ЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—ШШ\[Y[ЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYPЫЭ™\”Z[›ЭФЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—ЬZ[›ЭЧЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР[Ь™[ZYPЫЭ™\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР[Ь™[ZYPЫЭ™\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKШЫЭ™\‹ШЫЭ™\—ЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР[Ь™[ZYQ›ЭЩ\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQ›ЭЩ\•[љ[PЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—ЩY][™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQ›ЭЩ\”ќXћPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—ЬќXћWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQ›ЭЩ\“X]ЪPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—ЫX]ЪWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQ›ЭЩ\“Z[ќЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—ЫZ[ќШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQ›ЭЩ\“[[ЫђЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—Ы[[Ы—ШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQ›ЭЩ\”Ш[YЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—ЬШ[YШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQ›ЭЩ\”ќXћTЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—ЬќXћWЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQ›ЭЩ\ђШ\[Y[ЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—ШШ\[Y[ЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQ›ЭЩ\”Z[›ЭФЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—ЬZ[›ЭЧЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР[Ь™[ZYQ›ЭЩ\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР[Ь™[ZYQ›ЭЩ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩ›ЭЩ\‹Щ›ЭЩ\—ЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР[Ь™[ZYTљX›Ы–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTљX›Ы•[љ[PЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—ЩY][™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTљX›Ы”ќXћPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—ЬќXћWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTљX›Ы“X]ЪPЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—ЫX]ЪWШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTљX›Ы“Z[ќЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—ЫZ[ќШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTљX›Ы“[[ЫђЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—Ы[[Ы—ШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTљX›Ы”Ш[YЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—ЬШ[YШЬ™X[K™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTљX›Ы”ќXћTЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—ЬќXћWЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTљX›ЫђШ\[Y[ЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—ШШ\[Y[ЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYTљX›Ы”Z[›ЭФЭЪ\›ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—ЬZ[›ЭЧЬЭЪ\›™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР[Ь™[ZYTљX›Ы–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР[Ь™[ZYTљX›Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬљX›Ы‹ЬљX›Ы—ЬЪ[ћK™Ш\[ЉNВ‚€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР[Ь™[ZYTЭ]Ш™\њћVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР[Ь™[ZYTЭ]Ш™\њћU[љ[PЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР[Ь™[ZYTЭ]Ш™\њћU[љ[PЬ™X[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЬЭ]Ш™\њћKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР[Ь™[ZYQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР[Ь™[ZYQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР[Ь™[ZYQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР[Ь™[ZYQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р[Ь™[ZYQЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧР[Ь™[ZYQЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WР[Ь™[ZYQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР[Ь™[ZYQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш[Ь™[ZYKЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWУRSСT–B‚€ЪY€СђSRSWСђSS’ФВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС[[љЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС[[љЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС[[љЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС[[љЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С[[љЬЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС[[љЬЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС[[љЬЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС[[љЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС[[љЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ССS—ОWУQQРWСU“УUSУ”В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС[[љЬУYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС[[љЬУYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС[[љЬУYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС[[љЬУYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫYYШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С[[љЬУYYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧС[[љЬУYYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WС[[љЬУYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС[[љЬУYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[[љЬЛЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ€Щ[™Y€ЛФССS—ОWУQQРWСU“УUSУ”В€Щ[™Y€ЛФСђSRSWСђSS’ФВ‚€ЪY€СђSRSWФSђХTђТS‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ[Э\Ъ[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Э\Ъ[‹Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ[Э\Ъ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Э\Ъ[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ[Э\Ъ[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Э\Ъ[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ[Э\Ъ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Э\Ъ[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф[Э\Ъ[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь[Э\Ъ[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ[Э\Ъ[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь[Э\Ъ[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ[Э\Ъ[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь[Э\Ъ[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ[Э\Ъ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Э\Ъ[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ[Э\Ъ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Э\Ъ[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФSђХTђТS‚‚€ЪY€СђSRSWФУ“УB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЫ›ЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ›ЫKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЫ›ЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ›ЫKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЫ›ЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ›ЫKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЫ›ЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ›ЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЫ›ЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ›ЫKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЫ›ЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ›ЫKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЫ›ЫVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ›ЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЫ›ЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ›ЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЫ›ЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ›ЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСњ›ЬЫ[ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щњ›ЬЫ[ЭЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСњ›ЬЫ[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щњ›ЬЫ[ЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСњ›ЬЫ[ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щњ›ЬЫ[ЭШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСњ›ЬЫ[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щњ›ЬЫ[ЭЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Сњ›ЬЫ[ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щњ›ЬЫ[ЭЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСњ›ЬЫ[ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щњ›ЬЫ[ЭЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСњ›ЬЫ[ЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щњ›ЬЫ[ЭЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСњ›ЬЫ[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щњ›ЬЫ[ЭЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСњ›ЬЫ[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щњ›ЬЫ[ЭЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФУ“УB‚€ЪY€СђSRSWФХУ’“ХT“‘T‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЭЫљ›Э\›™\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭЫљ›Э\›™\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЭЫљ›Э\›™\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭЫљ›Э\›™\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЭЫљ›Э\›™\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭЫљ›Э\›™\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЭЫљ›Э\›™\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭЫљ›Э\›™\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЭЫљ›Э\›™\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭЫљ›Э\›™\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЭЫљ›Э\›™\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭЫљ›Э\›™\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЭЫљ›Э\›™\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЭЫљ›Э\›™\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЭЫљ›Э\›™\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭЫљ›Э\›™\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЭЫљ›Э\›™\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЭЫљ›Э\›™\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФХУ’“ХT“‘T‚‚€ЪY€СђSRSWСRTРХQB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСZ\ШЭYRXЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСZ\ШЭYRXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСZ\ШЭYRXЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСZ\ШЭYRXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СZ\ШЭYRXЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСZ\ШЭYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСZ\ШЭYRXЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСZ\ШЭYRXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСZ\ШЭYRXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСZ\ШЭYS›ЪXЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫ›ЪXЩWЩXЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСZ\ШЭYS›ЪXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫ›ЪXЩWЩXЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСZ\ШЭYS›ЪXЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫ›ЪXЩWЩXЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСZ\ШЭYS›ЪXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫ›ЪXЩWЩXЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СZ\ШЭYS›ЪXЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫ›ЪXЩWЩXЩKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧСZ\ШЭYS›ЪXЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫ›ЪXЩWЩXЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WСZ\ШЭYS›ЪXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫ›ЪXЩWЩXЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСZ\ШЭYS›ЪXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZ\ШЭYKЫ›ЪXЩWЩXЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСRTРХQB‚€ЪY€СђSRSWТS‘QQQB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ[™YYYSVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ[™YYYSVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ[™YYYSVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ[™YYYSVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т[™YYYSVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ[™YYYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ[™YYYSVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ[™YYYSVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ[™YYYSVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ[™YYYQ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ[™YYYQ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ[™YYYQ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ[™YYYQ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т[™YYYQ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩ‹ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ[™YYYQ–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ[™YYYQ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ[™YYYQ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ[™YYYKЩ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТS‘QQQB‚€ЪY€СђSRSWУSФ”RУВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ[ЬњZЫСќ[™[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ[ЬњZЫСќ[™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ[ЬњZЫСќ[™[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ[ЬњZЫСќ[™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У[ЬњZЫСќ[™[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУ[ЬњZЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ[ЬњZЫСќ[™[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ[ЬњZЫСќ[™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ[ЬњZЫСќ[™[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ[ЬњZЫТ[™ЬћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЪ[™ЬћKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ[ЬњZЫТ[™ЬћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЪ[™ЬћKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ[ЬњZЫТ[™ЬћVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЪ[™ЬћKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ[ЬњZЫТ[™ЬћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЪ[™ЬћKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У[ЬњZЫТ[™ЬћVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЪ[™ЬћKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ[ЬњZЫТ[™ЬћVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЪ[™ЬћKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WУ[ЬњZЫТ[™ЬћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЪ[™ЬћKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ[ЬњZЫТ[™ЬћVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ЬњZЫЛЪ[™ЬћKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУSФ”RУВ‚€ЪY€СђSRSWРХQђS•€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЭY[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭY[ќЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЭY[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭY[ќЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЭY[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭY[ќШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЭY[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭY[ќЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЭY[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЭY[ќЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЭY[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЭY[ќЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЭY[ќЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЭY[ќЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЭY[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭY[ќЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЭY[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЭY[ќЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫЬ\ZZЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫЬ\ZZЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫЬ\ZZЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫЬ\ZZЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫЬ\ZZЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЫЬ\ZZЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫЬ\ZZЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫЬ\ZZЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫЬ\ZZЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЫЬ\ZZЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЫЬ\ZZЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЫЬ\ZZЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЫЬ\ZZЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЫЬ\ZZЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЫЬ\ZZЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WРЫЬ\ZZЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЫЬ\ZZЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЫЬ\ZZЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWРХQђS•‚€ЪY€СђSRSWСђPУЦ“У€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСXЫЮ›ЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЮ›ЫЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСXЫЮ›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЮ›ЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСXЫЮ›ЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЮ›ЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСXЫЮ›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЮ›ЫЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СXЫЮ›ЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЮ›ЫЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСXЫЮ›ЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЮ›ЫЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСXЫЮ›ЫЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЮ›ЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСXЫЮ›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЮ›ЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСXЫЮ›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЮ›ЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСђPУЦ“У‚€ЪY€СђSRSWРTђХЦ“У€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\ЭЮ›ЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЮ›ЫЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\ЭЮ›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЮ›ЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\ЭЮ›ЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЮ›ЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\ЭЮ›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЮ›ЫЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\ЭЮ›ЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЮ›ЫЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\ЭЮ›ЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЮ›ЫЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\ЭЮ›ЫЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЮ›ЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\ЭЮ›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЮ›ЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\ЭЮ›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЮ›ЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРTђХЦ“У‚€ЪY€СђSRSWСђPУХ’TТ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСXЫЭљ\ЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЭљ\ЪЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСXЫЭљ\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЭљ\ЪЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСXЫЭљ\ЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЭљ\ЪШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСXЫЭљ\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЭљ\ЪЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СXЫЭљ\ЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЭљ\ЪЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСXЫЭљ\ЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЭљ\ЪЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСXЫЭљ\ЪЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЭљ\ЪЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСXЫЭљ\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЭљ\ЪЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСXЫЭљ\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЫЭљ\ЪЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСђPУХ’TТ‚€ЪY€СђSRSWРTђХХ’TТ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\ЭЭљ\ЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЭљ\ЪЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\ЭЭљ\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЭљ\ЪЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\ЭЭљ\ЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЭљ\ЪШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\ЭЭљ\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЭљ\ЪЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\ЭЭљ\ЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЭљ\ЪЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\ЭЭљ\ЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЭљ\ЪЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\ЭЭљ\ЪЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЭљ\ЪЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\ЭЭљ\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЭљ\ЪЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\ЭЭљ\ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭЭљ\ЪЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРTђХХ’TТ‚€ЪY€СђSRSWСTђSQУ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС\[YЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹Ш[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС\[YЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС\[YЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС\[YЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С\[YЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС\[YЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС\[YЫ–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС\[YЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС\[YЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС\[YЫ‘ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС\[YЫ‘ЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС\[YЫ‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС\[YЫ‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С\[YЫ‘ЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЩЫX^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧС\[YЫ‘ЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WС\[YЫ‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЩЫX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС\[YЫ‘ЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\[YЫ‹ЩЫX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ‚€ЪY€ССS—ОWРФ“ФФЧСU“ФВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\Ъ[YЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\Ъ[YЫ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\Ъ[YЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\Ъ[YЫ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\Ъ[YЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\Ъ[YЫ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\Ъ[YЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\Ъ[YЫ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\Ъ[YЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\Ъ[YЫ‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\Ъ[YЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\Ъ[YЫ‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\Ъ[YЫ–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\Ъ[YЫ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\Ъ[YЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\Ъ[YЫ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\Ъ[YЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\Ъ[YЫ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФССS—ОWРФ“ФФЧСU“ФВ€Щ[™Y€ЛФСђSRSWСTђSQУ‚‚€ЪY€СђSRSWС‘QTB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС™Y\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y\KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС™Y\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y\KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС™Y\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y\KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС™Y\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y\KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С™Y\VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y\KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС™Y\VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y\KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС™Y\VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y\KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС™Y\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y\KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС™Y\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™Y\KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСZЫШZЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZЫШZЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСZЫШZЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZЫШZЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСZЫШZЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZЫШZЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСZЫШZЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZЫШZЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СZЫШZЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩZЫШZЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСZЫШZЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩZЫШZЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСZЫШZЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩZЫШZЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСZЫШZЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZЫШZЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСZЫШZЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩZЫШZЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСYШ\[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩYШ\[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСYШ\[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩYШ\[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСYШ\[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩYШ\[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСYШ\[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩYШ\[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СYШ\[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩYШ\[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСYШ\[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩYШ\[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСYШ\[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩYШ\[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСYШ\[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩYШ\[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСYШ\[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩYШ\[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWС‘QTB‚€ЪY€СђSRSWЦђPТPS‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦXЪX[’\›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦXЪX[’\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦXЪX[’\›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦXЪX[’\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ЦXЪX[’\›ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќЦXЪX[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦXЪX[’\›ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WЦXЪX[’\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦXЪX[’\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦXЪX[ђЬ›ЭЫ™YЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ШЬ›ЭЫ™YЬЭЫЬ™Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦXЪX[ђЬ›ЭЫ™YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ШЬ›ЭЫ™YЬЭЫЬ™Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦXЪX[ђЬ›ЭЫ™YЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ШЬ›ЭЫ™YЬЭЫЬ™ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦXЪX[ђЬ›ЭЫ™YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ШЬ›ЭЫ™YЬЭЫЬ™ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ЦXЪX[ђЬ›ЭЫ™YЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ШЬ›ЭЫ™YЬЭЫЬ™ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦXЪX[ђЬ›ЭЫ™YЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ШЬ›ЭЫ™YЬЭЫЬ™ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WЦXЪX[ђЬ›ЭЫ™YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ШЬ›ЭЫ™YЬЭЫЬ™ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦXЪX[ђЬ›ЭЫ™YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЮXЪX[‹ШЬ›ЭЫ™YЬЭЫЬ™ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWЦђPТPS‚‚€ЪY€СђSRSWЦђSPV‘S•B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦ[X^™[ќR\›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦ[X^™[ќR\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦ[X^™[ќR\›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦ[X^™[ќR\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ц[X^™[ќR\›ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќЦ[X^™[ќVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦ[X^™[ќR\›ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WЦ[X^™[ќR\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦ[X^™[ќR\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦ[X^™[ќPЬ›ЭЫ™YЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKШЬ›ЭЫ™YЬЪY[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦ[X^™[ќPЬ›ЭЫ™YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKШЬ›ЭЫ™YЬЪY[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦ[X^™[ќPЬ›ЭЫ™YЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKШЬ›ЭЫ™YЬЪY[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦ[X^™[ќPЬ›ЭЫ™YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKШЬ›ЭЫ™YЬЪY[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ц[X^™[ќPЬ›ЭЫ™YЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKШЬ›ЭЫ™YЬЪY[ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦ[X^™[ќPЬ›ЭЫ™YЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKШЬ›ЭЫ™YЬЪY[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WЦ[X^™[ќPЬ›ЭЫ™YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKШЬ›ЭЫ™YЬЪY[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦ[X^™[ќPЬ›ЭЫ™YЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю[X^™[ќKШЬ›ЭЫ™YЬЪY[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWЦђSPV‘S•B‚€ЪY€СђSRSWСUT“ђUTВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС]\›]\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС]\›]\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС]\›]\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС]\›]\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С]\›]\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС]\›]\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС]\›]\ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС]\›]\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС]\›]\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС]\›]\С]\›[X^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩ]\›[X^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС]\›]\С]\›[X^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩ]\›[X^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС]\›]\С]\›[X^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩ]\›[X^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС]\›]\С]\›[X^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩ]\›[X^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С]\›]\С]\›[X^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩ]\›[X^ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧС]\›]\С]\›[X^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩ]\›[X^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WС]\›]\С]\›[X^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩ]\›[X^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС]\›]\С]\›[X^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ]\›]\ЛЩ]\›[X^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСUT“ђUTВ‚€ЪY€СђSRSWТХP‘•B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТЭX™ќVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭX™ќKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТЭX™ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭX™ќKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТЭX™ќVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭX™ќKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТЭX™ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭX™ќKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТЭX™ќVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЭX™ќKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТЭX™ќVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЭX™ќKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТЭX™ќVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪЭX™ќKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТЭX™ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭX™ќKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТЭX™ќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭX™ќKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\њЪYќTЪ[™ЫTЭљZЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\њЪYќTЪ[™ЫTЭљZЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\њЪYќTЪ[™ЫTЭљZЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\њЪYќTЪ[™ЫTЭљZЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\њЪYќVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\њЪYќVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\њЪYќVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\њЪYќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\њЪYќVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\њЪYќT\YЭљZЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\њЪYќT\YЭљZЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\њЪYќT\YЭљZЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\њЪYќT\YЭљZЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩKЬЪ[ћK™Ш\[ЉNВ‚€ЪY€СТQРS•SPVС“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\њЪYќTЪ[™ЫTЭљZЩQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬЪ[™ЫWЬЭљZЩWЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\њЪYќTЪ[™ЫTЭљZЩQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬЪ[™ЫWЬЭљZЩWЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\њЪYќTЪ[™ЫTЭљZЩQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬЪ[™ЫWЬЭљZЩWЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\њЪYќTЪ[™ЫTЭљZЩQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬЪ[™ЫWЬЭљZЩWЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\њЪYќTЪ[™ЫTЭљZЩQЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬЪ[™ЫWЬЭљZЩWЩЫX^ЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\њЪYќT\YЭљZЩQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩWЩЫX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\њЪYќT\YЭљZЩQЫX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩWЩЫX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\њЪYќT\YЭљZЩQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩWЩЫX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\њЪYќT\YЭљZЩQЫX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩWЩЫX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\њЪYќT\YЭљZЩQЫX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩWЩЫX^ЪXЫЫ‹ЌњЉNВ‚€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\њЪYќTЪ[™ЫTЭљZЩQЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬЪ[™ЫWЬЭљZЩWЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\њЪYќT\YЭљZЩQЫX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\њЪYќKЬ\YЬЭљZЩWЩЫX^ЫЭ™\ќЫЬ›ЌњЉNВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСТQРS•SPVС“Ф“TВ€Щ[™Y€ЛФСђSRSWТХP‘•B‚€ЪY€СђSRSWЦђT•QB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦ\ќYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦ\ќYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦ\ќYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦ\ќYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ц\ќYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧЦ\ќYQYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩYKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WЦ\ќYQYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩYKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧЦ\ќYQYVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩYKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WЦ\ќYQYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩYKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ц\ќYQYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩYKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќЦ\ќYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩ›ЫЭљ[ќЊXњЉNВ€ЫЫњЭNУ[Ы‘›ЫЭљ[ќЦ\ќYQYVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦ\ќYVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЫЭ™\ќЫЬ›ЌњЉNВ€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧЦ\ќYQYVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩYKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WЦ\ќYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦ\ќYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭLM€УЭ™\ќЫЬ›[]WЦ\ќYQYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩYKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WЦ\ќYQYVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ќYKЩYKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWЦђT•QB‚€ЪY€СђSRSWФ‘QТQSRТB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ™YЪY[ZЪVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪY[ZЪKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ™YЪY[ZЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪY[ZЪKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ™YЪY[ZЪVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪY[ZЪKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ™YЪY[ZЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪY[ZЪKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф™YЪY[ZЪVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪY[ZЪKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ™YЪY[ZЪVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪY[ZЪKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ™YЪY[ZЪVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪY[ZЪKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ™YЪY[ZЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪY[ZЪKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ™YЪY[ZЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪY[ZЪKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФ‘QТQSRТB‚€ЪY€СђSRSWФ‘QТQђQУВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ™YЪYYЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪYYЫЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ™YЪYYЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪYYЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ™YЪYYЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪYYЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ™YЪYYЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪYYЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф™YЪYYЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪYYЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ™YЪYYЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪYYЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ™YЪYYЫЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪYYЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ™YЪYYЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪYYЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ™YЪYYЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪYYЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФ‘QТQђQУВ‚€ЪY€СђSRSWСУTХ’QT‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫ\ЭљY\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ\ЭљY\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫ\ЭљY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ\ЭљY\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫ\ЭљY\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ\ЭљY\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫ\ЭљY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ\ЭљY\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫ\ЭљY\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ\ЭљY\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЫ\ЭљY\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ\ЭљY\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫ\ЭљY\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ\ЭљY\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫ\ЭљY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ\ЭљY\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫ\ЭљY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ\ЭљY\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСУTХ’QT‚‚€ЪY€СђSRSWФФPХ’QT‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЬXЭљY\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬXЭљY\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЬXЭљY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬXЭљY\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЬXЭљY\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬXЭљY\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЬXЭљY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬXЭљY\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЬXЭљY\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬXЭљY\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЬXЭљY\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬXЭљY\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЬXЭљY\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬXЭљY\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЬXЭљY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬXЭљY\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЬXЭљY\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬXЭљY\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФФPХ’QT‚‚€ЪY€СђSRSWРРST‘V€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРШ[\™^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРШ[\™^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРШ[\™^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРШ[\™^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РШ[\™^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРШ[\™^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРШ[\™^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРШ[\™^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРШ[\™^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€С•TТSУ—С“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРШ[\™^XЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЪXЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРШ[\™^XЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЪXЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРШ[\™^XЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЪXЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРШ[\™^XЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЪXЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РШ[\™^XЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЪXЩKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРШ[\™^XЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЪXЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРШ[\™^XЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЪXЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРШ[\™^XЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЪXЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФС•TТSУ—С“Ф“TВ‚€ЪY€С•TТSУ—С“Ф“TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРШ[\™^ЪYЭЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЬЪYЭЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРШ[\™^ЪYЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЬЪYЭЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРШ[\™^ЪYЭЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЬЪYЭЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРШ[\™^ЪYЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЬЪYЭЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РШ[\™^ЪYЭЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЬЪYЭЛЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРШ[\™^ЪYЭЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЬЪYЭЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРШ[\™^ЪYЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЬЪYЭЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРШ[\™^ЪYЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ[\™^ЬЪYЭЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФС•TТSУ—С“Ф“TВ€Щ[™Y€ЛФСђSRSWРРST‘V‚€ЪY€СђSRSWФФ’QРUUВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЬљYШ]]ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬљYШ]]ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЬљYШ]]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬљYШ]]ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЬљYШ]]ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬљYШ]]ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЬљYШ]]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬљYШ]]ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЬљYШ]]ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬљYШ]]ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЬљYШ]]ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬљYШ]]ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЬљYШ]]ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬљYШ]]ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЬљYШ]]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬљYШ]]ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЬљYШ]]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬљYШ]]ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС›ЬYШ]ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЬYШ]ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС›ЬYШ]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЬYШ]ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС›ЬYШ]ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЬYШ]ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС›ЬYШ]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЬYШ]ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С›ЬYШ]ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЬYШ]ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС›ЬYШ]ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЬYШ]ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС›ЬYШ]ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЬYШ]ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС›ЬYШ]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЬYШ]ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС›ЬYШ]ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›ЬYШ]ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУY[ЭЬШШ\YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[ЭЬШШ\YKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУY[ЭЬШШ\YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[ЭЬШШ\YKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУY[ЭЬШШ\YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[ЭЬШШ\YKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУY[ЭЬШШ\YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[ЭЬШШ\YKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УY[ЭЬШШ\YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[ЭЬШШ\YKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУY[ЭЬШШ\YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[ЭЬШШ\YKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУY[ЭЬШШ\YVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫY[ЭЬШШ\YKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУY[ЭЬШШ\YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[ЭЬШШ\YKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУY[ЭЬШШ\YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫY[ЭЬШШ\YKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФФ’QРUUВ‚€ЪY€СђSRSWС•QPУРУВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСќYXЫШЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩќYXЫШЫЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСќYXЫШЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩќYXЫШЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСќYXЫШЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩќYXЫШЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСќYXЫШЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩќYXЫШЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СќYXЫШЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩќYXЫШЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСќYXЫШЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩќYXЫШЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСќYXЫШЫЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩќYXЫШЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСќYXЫШЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩќYXЫШЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСќYXЫШЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩќYXЫШЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЬ›ШШ[Ь–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ›ШШ[Ь‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЬ›ШШ[Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ›ШШ[Ь‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЬ›ШШ[Ь–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ›ШШ[Ь‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЬ›ШШ[Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ›ШШ[Ь‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЬ›ШШ[Ь–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ›ШШ[Ь‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЬ›ШШ[Ь–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ›ШШ[Ь‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЬ›ШШ[Ь–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЬ›ШШ[Ь‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЬ›ШШ[Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ›ШШ[Ь‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЬ›ШШ[Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЬ›ШШ[Ь‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪЩ[Y\™ЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЩ[Y\™ЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЪЩ[Y\™ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЩ[Y\™ЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪЩ[Y\™ЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЩ[Y\™ЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪЩ[Y\™ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЩ[Y\™ЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪЩ[Y\™ЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЩ[Y\™ЩKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪЩ[Y\™ЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЩ[Y\™ЩKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪЩ[Y\™ЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЩ[Y\™ЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪЩ[Y\™ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЩ[Y\™ЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪЩ[Y\™ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪЩ[Y\™ЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWС•QPУРУВ‚€ЪY€СђSRSWФUPVB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ]X^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ]X^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ]X^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ]X^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф]X^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ]X^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ]X^VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ]X^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ]X^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ]X^Щ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^Щ[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ]X^Щ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^Щ[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ]X^Щ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^Щ[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ]X^Щ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^Щ[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф]X^Щ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^Щ[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ]X^Щ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^Щ[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ]X^Щ[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^Щ[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ]X^Щ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^Щ[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ]X^Щ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X^Щ[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ]X\]X][ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X\]X][Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ]X\]X][ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X\]X][Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ]X\]X][ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X\]X][ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ]X\]X][ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X\]X][ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф]X\]X][ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]X\]X][ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ]X\]X][ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]X\]X][Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ]X\]X][ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь]X\]X][ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ]X\]X][ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X\]X][ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ]X\]X][ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]X\]X][ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФUPVB‚€ЪY€СђSRSWУPТУ’В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXЪЫљЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЪЫљЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXЪЫљЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЪЫљЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXЪЫљЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЪЫљЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXЪЫљЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЪЫљЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXЪЫљЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXЪЫљЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУXЪЫљЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXЪЫљЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXЪЫљЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXЪЫљЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУXЪЫљЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЪЫљЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXЪЫљЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЪЫљЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЪ[љЫЫЩЫ™SVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЪ[љЫЫЩЫ™SVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЪ[љЫЫЩЫ™SVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЪ[љЫЫЩЫ™SVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЪ[љЫЫЩЫ™SVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУЪ[љЫЫЩЫ™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЪ[љЫЫЩЫ™SVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЪ[љЫЫЩЫ™SVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЪ[љЫЫЩЫ™SVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЪ[љЫЫЩЫ™Q–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЪ[љЫЫЩЫ™Q–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЪ[љЫЫЩЫ™Q–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЪ[љЫЫЩЫ™Q–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЪ[љЫЫЩЫ™Q–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩ‹ЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЪ[љЫЫЩЫ™Q–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЪ[љЫЫЩЫ™Q–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЪ[љЫЫЩЫ™Q–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪ[љЫЫЩЫ™KЩ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУPТУ’В‚€ЪY€СђSRSWХT“ХS•SB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\›Э[ќ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›Э[ќ[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\›Э[ќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›Э[ќ[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\›Э[ќ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›Э[ќ[KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\›Э[ќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›Э[ќ[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\›Э[ќ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\›Э[ќ[KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\›Э[ќ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\›Э[ќ[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\›Э[ќ[VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\›Э[ќ[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\›Э[ќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›Э[ќ[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\›Э[ќ[VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›Э[ќ[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЬYЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬYЬЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЬYЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬYЬЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЬYЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬYЬЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЬYЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬYЬЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЬYЬЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬYЬЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЬYЬЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬYЬЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЬYЬЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬYЬЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЬYЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬYЬЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЬYЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬYЬЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХT“ХS•SB‚€ЪY€СђSRSWУ–SP“B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУћ[X›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ыћ[X›KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУћ[X›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ыћ[X›KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУћ[X›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ыћ[X›KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУћ[X›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ыћ[X›KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ућ[X›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ыћ[X›KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУћ[X›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ыћ[X›KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУћ[X›VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ыћ[X›KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУћ[X›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ыћ[X›KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУћ[X›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ыћ[X›KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЪЪ^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪ^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЪЪ^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪ^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЪЪ^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪ^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЪЪ^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪ^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЪЪ^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪ^ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУЪЪ^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪ^Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЪЪ^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪ^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЪЪ^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪ^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЪЪ^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪ^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУ–SP“B‚€ЪY€СђSRSWФUУRB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ]ЫZVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ЫZKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ]ЫZVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ЫZKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ]ЫZVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ЫZKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ]ЫZVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ЫZKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф]ЫZVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]ЫZKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ]ЫZVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]ЫZKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ]ЫZVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь]ЫZKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ]ЫZVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ЫZKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ]ЫZVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]ЫZKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ]Ы[ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ]Ы[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ]Ы[ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ]Ы[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф]Ы[ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ]Ы[ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ]Ы[ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ]Ы[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ]Ы[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ]Ы[ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЭЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ]Ы[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ]Ы[ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЭШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ]Ы[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЭЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф]Ы[ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЭЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ]Ы[ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЭЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ]Ы[ЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЭЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ]Ы[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЭЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ]Ы[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь]Ы[ЭЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФUУRB‚€ЪY€СђSRSWХS‘SPUTВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ[™[X]\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™[X]\ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ[™[X]\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™[X]\ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ[™[X]\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™[X]\ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ[™[X]\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™[X]\ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х[™[X]\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[™[X]\ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ[™[X]\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[™[X]\ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ[™[X]\ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э[™[X]\ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ[™[X]\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™[X]\ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ[™[X]\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™[X]\ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLM€У[Ы”[]WУX]\ЪЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУX]\ЪЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУX]\ЪЫ™YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУX]\ЪЫ™YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УX]\ЪЫ™YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУX]\ЪЫ™YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУX]\ЪЫ™YVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУX]\ЪЫ™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУX]\ЪЫ™YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУX]\ЪЫ›Э\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЩ›Э\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУX]\ЪЫ›Э\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЩ›Э\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УX]\ЪЫ›Э\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЩ›Э\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУX]\ЪЫ›Э\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЩ›Э\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУX]\ЪЫ›Э\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЩ›Э\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУX]\ЪЫ›Э\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЩ›Э\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУX]\ЪЫ›Э\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX]\ЪЫЩ›Э\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХS‘SPUTВ‚€ЪY€СђSRSWС’QХQТ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСљYЭYЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩљYЭYЪЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСљYЭYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩљYЭYЪЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСљYЭYЪЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩљYЭYЪШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСљYЭYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩљYЭYЪЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СљYЭYЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩљYЭYЪЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСљYЭYЪЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩљYЭYЪЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСљYЭYЪЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩљYЭYЪЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСљYЭYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩљYЭYЪЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСљYЭYЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩљYЭYЪЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСXЪШќ[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЪШќ[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСXЪШќ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЪШќ[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСXЪШќ[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЪШќ[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСXЪШќ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЪШќ[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СXЪШќ[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩXЪШќ[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСXЪШќ[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩXЪШќ[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСXЪШќ[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩXЪШќ[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСXЪШќ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЪШќ[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСXЪШќ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩXЪШќ[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWС’QХQТ‚€ЪY€СђSRSWФУSУU‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЫ[Ы]–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ[Ы]‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЫ[Ы]–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ[Ы]‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЫ[Ы]–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ[Ы]‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЫ[Ы]–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ[Ы]‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЫ[Ы]–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ[Ы]‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЫ[Ы]–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ[Ы]‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЫ[Ы]–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ[Ы]‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЫ[Ы]–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ[Ы]‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЫ[Ы]–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ[Ы]‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫ]–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ]‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫ]–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ]‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫ]–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ]‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫ]–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ]‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫ]–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ]‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЫ]–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ]‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫ]–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ]‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫ]–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ]‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫ]–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ]‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\›Ы]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›Ы]KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\›Ы]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›Ы]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\›Ы]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›Ы]KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\›Ы]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›Ы]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\›Ы]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\›Ы]KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\›Ы]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\›Ы]KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\›Ы]VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\›Ы]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\›Ы]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›Ы]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\›Ы]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›Ы]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФУSУU‚‚€ЪY€СђSRSWФФUPUТРP’SB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЬ]X]ЪШXљ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЬ]X]ЪШXљ[VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KШXЪЛЌњњЫ[ЫЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЬ]X]ЪШXљ[VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В‚€ЫЫњЭLM€У[Ы”[]WФЬ]X]ЪШXљ[QЬ™Y[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЬ]X]ЪШXљ[QЬ™Y[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЬ]X]ЪШXљ[QЬ™Y[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЬ]X]ЪШXљ[QЬ™Y[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЬ]X]ЪШXљ[QЬ™Y[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЬ]X]ЪШXљ[QЬ™Y[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLM€У[Ы”[]WФЬ]X]ЪШXљ[P›YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KШ›YKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЬ]X]ЪШXљ[P›YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KШ›YKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЬ]X]ЪШXљ[P›YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KШ›YKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЬ]X]ЪШXљ[P›YVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KШ›YKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЬ]X]ЪШXљ[P›YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KШ›YKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЬ]X]ЪШXљ[P›YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KШ›YKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLM€У[Ы”[]WФЬ]X]ЪШXљ[VY[ЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЮY[ЭЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЬ]X]ЪШXљ[VY[ЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЮY[ЭЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЬ]X]ЪШXљ[VY[ЭЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЮY[ЭЛЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЬ]X]ЪШXљ[VY[ЭЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЮY[ЭЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЬ]X]ЪШXљ[VY[ЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЮY[ЭЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЬ]X]ЪШXљ[VY[ЭЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЮY[ЭЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLM€У[Ы”[]WФЬ]X]ЪШXљ[UЪ]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЭЪ]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЬ]X]ЪШXљ[UЪ]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЭЪ]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЬ]X]ЪШXљ[UЪ]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЭЪ]KЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЬ]X]ЪШXљ[UЪ]VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЭЪ]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЬ]X]ЪШXљ[UЪ]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЭЪ]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЬ]X]ЪШXљ[UЪ]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЬ]X]ЪШXљ[KЭЪ]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФФUPUТРP’SB‚€ЪY€СђSRSWУђPУB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУXЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXЫVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУXЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXЫЭXЪЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫЭXЪЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXЫЭXЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫЭXЪЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXЫЭXЪЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫЭXЪЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXЫЭXЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫЭXЪЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXЫЭXЪЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫЭXЪЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУXЫЭXЪЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫЭXЪЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXЫЭXЪЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫЭXЪЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУXЫЭXЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫЭXЪЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXЫЭXЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXЫЭXЪЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСШ\™Ш[XЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩШ\™Ш[XЫЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСШ\™Ш[XЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩШ\™Ш[XЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСШ\™Ш[XЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩШ\™Ш[XЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСШ\™Ш[XЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩШ\™Ш[XЫЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СШ\™Ш[XЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩШ\™Ш[XЫЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСШ\™Ш[XЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩШ\™Ш[XЫЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСШ\™Ш[XЫЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩШ\™Ш[XЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСШ\™Ш[XЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩШ\™Ш[XЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСШ\™Ш[XЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩШ\™Ш[XЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУђPУB‚€ЪY€СђSRSWРТTђРQU€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЪ\ШY]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ\ШY]Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЪ\ШY]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ\ШY]Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЪ\ШY]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ\ШY]ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЪ\ШY]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ\ШY]ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЪ\ШY]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ\ШY]ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЪ\ШY]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ\ШY]Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЪ\ШY]ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЪ\ШY]ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЪ\ШY]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ\ШY]ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЪ\ШY]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ\ШY]ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\›X\›ЭYЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›X\›ЭYЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\›X\›ЭYЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›X\›ЭYЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\›X\›ЭYЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›X\›ЭYЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\›X\›ЭYЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›X\›ЭYЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\›X\›ЭYЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\›X\›ЭYЩKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\›X\›ЭYЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\›X\›ЭYЩKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\›X\›ЭYЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\›X\›ЭYЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\›X\›ЭYЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›X\›ЭYЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\›X\›ЭYЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\›X\›ЭYЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЩ\ќ[YЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ\ќ[YЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЩ\ќ[YЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ\ќ[YЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЩ\ќ[YЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ\ќ[YЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЩ\ќ[YЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ\ќ[YЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЩ\ќ[YЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ\ќ[YЩKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЩ\ќ[YЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ\ќ[YЩKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЩ\ќ[YЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ\ќ[YЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЩ\ќ[YЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ\ќ[YЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЩ\ќ[YЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ\ќ[YЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРТTђРQU‚€ЪY€СђSRSWХQ•S‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХYќ[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭYќ[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХYќ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭYќ[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХYќ[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭYќ[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХYќ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭYќ[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХYќ[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭYќ[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХYќ[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭYќ[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХYќ[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭYќ[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХYќ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭYќ[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХYќ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭYќ[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР™[X›ЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™[X›ЫЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР™[X›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™[X›ЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР™[X›ЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™[X›ЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР™[X›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™[X›ЫЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р™[X›ЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш™[X›ЫЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР™[X›ЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш™[X›ЫЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР™[X›ЫЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш™[X›ЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР™[X›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™[X›ЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР™[X›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш™[X›ЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХQ•S‚‚€ЪY€СђSRSWХРU‘S€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХШ]™[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ]™[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХШ]™[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ]™[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХШ]™[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ]™[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХШ]™[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ]™[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХШ]™[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭШ]™[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХШ]™[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭШ]™[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХШ]™[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭШ]™[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХШ]™[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ]™[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХШ]™[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ]™[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТЪ[ЭШ]™[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЪ[ЭШ]™[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТЪ[ЭШ]™[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЪ[ЭШ]™[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТЪ[ЭШ]™[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЪ[ЭШ]™[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТЪ[ЭШ]™[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЪ[ЭШ]™[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТЪ[ЭШ]™[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЪ[ЭШ]™[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТЪ[ЭШ]™[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЪ[ЭШ]™[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТЪ[ЭШ]™[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪЪ[ЭШ]™[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТЪ[ЭШ]™[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЪ[ЭШ]™[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТЪ[ЭШ]™[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЪ[ЭШ]™[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХРU‘S‚€ЪY€СђSRSWУPTРТQ‘‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУX\ШЪY™–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\ШЪY™‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУX\ШЪY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\ШЪY™‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУX\ШЪY™–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\ШЪY™‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУX\ШЪY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\ШЪY™‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УX\ШЪY™–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX\ШЪY™‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУX\ШЪY™–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫX\ШЪY™‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУX\ШЪY™–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫX\ШЪY™‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУX\ШЪY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\ШЪY™‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУX\ШЪY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\ШЪY™‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУXX›ЬЬЭY™–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXX›ЬЬЭY™‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУXX›ЬЬЭY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXX›ЬЬЭY™‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУXX›ЬЬЭY™–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXX›ЬЬЭY™‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУXX›ЬЬЭY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXX›ЬЬЭY™‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УXX›ЬЬЭY™–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXX›ЬЬЭY™‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУXX›ЬЬЭY™–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫXX›ЬЬЭY™‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУXX›ЬЬЭY™–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫXX›ЬЬЭY™‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУXX›ЬЬЭY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXX›ЬЬЭY™‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУXX›ЬЬЭY™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫXX›ЬЬЭY™‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУPTРТQ‘‚‚€ЪY€СђSRSWФТ“УСB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪ›ЫЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ›ЫЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЪ›ЫЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ›ЫЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪ›ЫЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ›ЫЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ›ЫЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ›ЫЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪ›ЫЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ›ЫЩKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪ›ЫЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ›ЫЩKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪ›ЫЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ›ЫЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪ›ЫЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ›ЫЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪ›ЫЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ›ЫЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЬYZXZVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬYZXZKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЬYZXZVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬYZXZKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЬYZXZVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬYZXZKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЬYZXZVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬYZXZKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЬYZXZVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬYZXZKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЬYZXZVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬYZXZKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЬYZXZVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬYZXZKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЬYZXZVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬYZXZKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЬYZXZVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬYZXZKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФТ“УСB‚€ЪY€СђSRSWР”ђSP“S‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРњ[X›[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРњ[X›[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРњ[X›[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРњ[X›[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Рњ[X›[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРњ[X›[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРњ[X›[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРњ[X›[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРњ[X›[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРњ[X›YЪ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›YЪ\ЭЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРњ[X›YЪ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›YЪ\ЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРњ[X›YЪ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›YЪ\ЭШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРњ[X›YЪ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›YЪ\ЭЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Рњ[X›YЪ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›YЪ\ЭЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРњ[X›YЪ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›YЪ\ЭЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРњ[X›YЪ\ЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›YЪ\ЭЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРњ[X›YЪ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›YЪ\ЭЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРњ[X›YЪ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњ[X›YЪ\ЭЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWР”ђSP“S‚‚€ЪY€СђSRSWХСQРУУУ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЩYШЫЫЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЫЫЫЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЩYШЫЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЫЫЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЩYШЫЫЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЫЫЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЩYШЫЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЫЫЫЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЩYШЫЫЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЫЫЫЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЩYШЫЫЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЫЫЫЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЩYШЫЫЫЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЫЫЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЩYШЫЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЫЫЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЩYШЫЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЫЫЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЩYШЬќY[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЬќY[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЩYШЬќY[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЬќY[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЩYШЬќY[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЬќY[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЩYШЬќY[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЬќY[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЩYШЬќY[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЬќY[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЩYШЬќY[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЬќY[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЩYШЬќY[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЬќY[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЩYШЬќY[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЬќY[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЩYШЬќY[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЩYШЬќY[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХСQРУУУ‚€ЪY€СђSRSWТУUС‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТЫ]Щ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫ]Щ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТЫ]Щ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫ]Щ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТЫ]Щ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫ]Щ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТЫ]Щ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫ]Щ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТЫ]Щ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫ]Щ‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТЫ]Щ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫ]Щ‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТЫ]Щ–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫ]Щ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТЫ]Щ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫ]Щ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТЫ]Щ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫ]Щ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТУUС‚‚€ЪY€СђSRSWРРTРRТQ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРШ\ШZЪYЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\ШZЪYЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРШ\ШZЪYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\ШZЪYЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРШ\ШZЪYЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\ШZЪYШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРШ\ШZЪYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\ШZЪYЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РШ\ШZЪYЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШШ\ШZЪYЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРШ\ШZЪYЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШШ\ШZЪYЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРШ\ШZЪYЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШШ\ШZЪYЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРШ\ШZЪYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\ШZЪYЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРШ\ШZЪYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШШ\ШZЪYЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШЫЭљ[Z[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШЫЭљ[Z[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШЫЭљ[Z[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШЫЭљ[Z[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШЫЭљ[Z[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФШЫЭљ[Z[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШЫЭљ[Z[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФШЫЭљ[Z[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШЫЭљ[Z[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ССS—ОWУQQРWСU“УUSУ”В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШЫЭљ[Z[“YYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШЫЭљ[Z[“YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШЫЭљ[Z[“YYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШЫЭљ[Z[“YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫYYШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШЫЭљ[Z[“YYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШЫЭљ[Z[“YYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WФШЫЭљ[Z[“YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШЫЭљ[Z[“YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЫЭљ[Z[‹ЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ€Щ[™Y€ЛФССS—ОWУQQРWСU“УUSУ”В€Щ[™Y€ЛФСђSRSWРРTРRТQ‚€ЪY€СђSRSWФ‘SФ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ™[Ь–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™[Ь‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ™[Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™[Ь‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ™[Ь–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™[Ь‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ™[Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™[Ь‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф™[Ь–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь™[Ь‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ™[Ь–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь™[Ь‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ™[Ь–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь™[Ь‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ™[Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™[Ь‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ™[Ь–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™[Ь‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФXњШШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXњШШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФXњШШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXњШШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФXњШШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXњШШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФXњШШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXњШШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФXњШШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬXњШШKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФXњШШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬXњШШKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФXњШШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬXњШШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФXњШШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXњШШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФXњШШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXњШШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФ‘SФ‚‚€ЪY€СђSRSWС“UB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС›]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС›]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС›]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС›]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С›]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›]KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС›]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›]KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС›]VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ›]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС›]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС›]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС\Ь]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\Ь]KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС\Ь]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\Ь]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС\Ь]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\Ь]KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС\Ь]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\Ь]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С\Ь]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ\Ь]KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС\Ь]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ\Ь]KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС\Ь]VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ\Ь]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС\Ь]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\Ь]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС\Ь]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\Ь]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWС“UB‚€ЪY€СђSRSWХS’РUS’В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ[љШ][љЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ][љЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ[љШ][љЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ][љЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ[љШ][љЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ][љЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ[љШ][љЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ][љЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х[љШ][љЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ][љЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ[љШ][љЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ][љЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ[љШ][љЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ][љЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ[љШ][љЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ][љЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ[љШ][љЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ][љЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ[љШ]Y™–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Y™‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ[љШ]Y™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Y™‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ[љШ]Y™–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Y™‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ[љШ]Y™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Y™‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х[љШ]Y™–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Y™‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ[љШ]Y™–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Y™‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ[љШ]Y™–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Y™‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ[љШ]Y™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Y™‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ[љШ]Y™–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Y™‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ[љШ]Ы–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Ы‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ[љШ]Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Ы‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ[љШ]Ы–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Ы‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ[љШ]Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Ы‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х[љШ]Ы–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Ы‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ[љШ]Ы–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Ы‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ[љШ]Ы–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Ы‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ[љШ]Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Ы‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ[љШ]Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[љШ]Ы‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХS’РUS’В‚€ЪY€СђSRSWХТQУU€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЪYЫ]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪYЫ]Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЪYЫ]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪYЫ]Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЪYЫ]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪYЫ]ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЪYЫ]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪYЫ]ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЪYЫ]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪYЫ]ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЪYЫ]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪYЫ]Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЪYЫ]ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЪYЫ]ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЪYЫ]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪYЫ]ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЪYЫ]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЪYЫ]ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЭYЭљ[ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЭYЭљ[ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЭYЭљ[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЭYЭљ[ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЭYЭљ[ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЭYЭљ[ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЭYЭљ[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЭYЭљ[ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЭYЭљ[ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЭYЭљ[ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЭYЭљ[ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЭYЭљ[ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЭYЭљ[ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЭYЭљ[ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЭYЭљ[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЭYЭљ[ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЭYЭљ[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЭYЭљ[ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХТQУU‚€ЪY€СђSRSWР“УP’T‘QT‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР›ЫXљ\™Y\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›ЫXљ\™Y\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР›ЫXљ\™Y\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›ЫXљ\™Y\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР›ЫXљ\™Y\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›ЫXљ\™Y\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР›ЫXљ\™Y\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›ЫXљ\™Y\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р›ЫXљ\™Y\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›ЫXљ\™Y\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР›ЫXљ\™Y\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш›ЫXљ\™Y\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР›ЫXљ\™Y\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш›ЫXљ\™Y\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР›ЫXљ\™Y\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›ЫXљ\™Y\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР›ЫXљ\™Y\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›ЫXљ\™Y\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWР“УP’T‘QT‚‚€ЪY€СђSRSWС’S’V‘S‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСљ[љ^™[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ[љ^™[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСљ[љ^™[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ[љ^™[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСљ[љ^™[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ[љ^™[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСљ[љ^™[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ[љ^™[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Сљ[љ^™[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щљ[љ^™[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСљ[љ^™[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щљ[љ^™[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСљ[љ^™[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щљ[љ^™[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСљ[љ^™[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ[љ^™[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСљ[љ^™[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щљ[љ^™[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ[Yљ[–™\›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ[Yљ[–™\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ[Yљ[–™\›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ[Yљ[–™\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф[Yљ[–™\›ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ[Yљ[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ[Yљ[–™\›ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ[Yљ[–™\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ[Yљ[–™\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ[Yљ[’\›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Ъ\›ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ[Yљ[’\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Ъ\›ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ[Yљ[’\›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Ъ\›ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ[Yљ[’\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Ъ\›ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф[Yљ[’\›ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Ъ\›ЛЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ[Yљ[’\›ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Ъ\›ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ[Yљ[’\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Ъ\›ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ[Yљ[’\›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[Yљ[‹Ъ\›ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWС’S’V‘S‚‚€ЪY€СђSRSWХђT“УУB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\›ЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›ЫЫKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›ЫЫKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\›ЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›ЫЫKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›ЫЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\›ЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\›ЫЫKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\›ЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\›ЫЫKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\›ЫЫVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\›ЫЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›ЫЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\›ЫЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ™]]њ›ЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™]]њ›ЫЫKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ™]]њ›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™]]њ›ЫЫKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ™]]њ›ЫЫVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™]]њ›ЫЫKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ™]]њ›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™]]њ›ЫЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф™]]њ›ЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь™]]њ›ЫЫKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ™]]њ›ЫЫVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь™]]њ›ЫЫKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ™]]њ›ЫЫVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь™]]њ›ЫЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ™]]њ›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™]]њ›ЫЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ™]]њ›ЫЫVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™]]њ›ЫЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХђT“УУB‚€ЪY€СђSRSWРЦPУVђT‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЮXЫ^\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЮXЫ^\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЮXЫ^\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЮXЫ^\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЮXЫ^\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЮXЫ^\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЮXЫ^\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЮXЫ^\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЮXЫ^\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЮXЫ^\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЮXЫ^\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЮXЫ^\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЮXЫ^\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЮXЫ^\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЮXЫ^\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЮXЫ^\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЮXЫ^\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЮXЫ^\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРЦPУVђT‚‚€ЪY€СђSRSWУФ•УФ“B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЬќЫЬ›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬќЫЬ›KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЬќЫЬ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬќЫЬ›KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЬќЫЬ›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬќЫЬ›KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЬќЫЬ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬќЫЬ›KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЬќЫЬ›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬќЫЬ›KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУЬќЫЬ›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬќЫЬ›KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЬќЫЬ›VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЬќЫЬ›KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЬќЫЬ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬќЫЬ›KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЬќЫЬ›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЬќЫЬ›KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУФ•УФ“B‚€ЪY€СђSRSWСУSSQU€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫ[[Y]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[Y]Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫ[[Y]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[Y]Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫ[[Y]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[Y]ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫ[[Y]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[Y]ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫ[[Y]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[Y]ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЫ[[Y]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[Y]Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫ[[Y]ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[Y]ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫ[[Y]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[Y]ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫ[[Y]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[Y]ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫ[[[ЬVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫ[[[ЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫ[[[ЬVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫ[[[ЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫ[[[ЬVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЫ[[[ЬVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫ[[[ЬVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫ[[[ЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫ[[[ЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ССS—ОWУQQРWСU“УUSУ”В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫ[[[ЬSYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫ[[[ЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫ[[[ЬSYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫ[[[ЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫYYШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫ[[[ЬSYYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫ[[[ЬSYYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫ[[[ЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫ[[[ЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ[[[ЬKЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ€Щ[™Y€ЛФССS—ОWУQQРWСU“УUSУ”В€Щ[™Y€ЛФСђSRSWСУSSQU‚€ЪY€СђSRSWСФ‘PUђT‘€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЬ™X]\™ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]\™Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЬ™X]\™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]\™Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЬ™X]\™ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]\™ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЬ™X]\™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]\™ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЬ™X]\™ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]\™ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЬ™X]\™ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]\™Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЬ™X]\™ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]\™ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЬ™X]\™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]\™ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЬ™X]\™ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]\™ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТЭ[™ЭЫ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭ[™ЭЫ™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТЭ[™ЭЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭ[™ЭЫ™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТЭ[™ЭЫ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭ[™ЭЫ™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТЭ[™ЭЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭ[™ЭЫ™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТЭ[™ЭЫ™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЭ[™ЭЫ™KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТЭ[™ЭЫ™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЭ[™ЭЫ™KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТЭ[™ЭЫ™VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪЭ[™ЭЫ™KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТЭ[™ЭЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭ[™ЭЫ™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТЭ[™ЭЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЭ[™ЭЫ™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСФ‘PUђT‘‚€ЪY€СђSRSWС“SRQУВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС›[ZYЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›[ZYЫЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС›[ZYЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›[ZYЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС›[ZYЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›[ZYЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС›[ZYЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›[ZYЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С›[ZYЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›[ZYЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС›[ZYЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›[ZYЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС›[ZYЫЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ›[ZYЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС›[ZYЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›[ZYЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС›[ZYЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›[ZYЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWС“SRQУВ‚€ЪY€СђSRSWРСUСB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЩ]ЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]ЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЩ]ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]ЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЩ]ЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]ЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЩ]ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]ЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЩ]ЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]ЩKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЩ]ЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]ЩKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЩ]ЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]ЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЩ]ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]ЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЩ]ЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]ЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЩ]][–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]][‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЩ]][–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]][‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЩ]][–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]][‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЩ]][–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]][‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЩ]][–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]][‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЩ]][–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]][‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЩ]][–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]][‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЩ]][–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]][‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЩ]][–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЩ]][‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРСUСB‚€ЪY€СђSRSWХ‘SVђB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ™[^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э™[^KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ™[^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э™[^KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ™[^VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э™[^KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ™[^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э™[^KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х™[^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э™[^KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ™[^VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э™[^KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ™[^VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э™[^KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ™[^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э™[^KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ™[^VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э™[^KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХ‘SVђB‚€ЪY€СђSRSWСУ‘Ц“В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫ™Ю›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ™Ю›ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫ™Ю›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ™Ю›ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫ™Ю›ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ™Ю›ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫ™Ю›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ™Ю›ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫ™Ю›ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ™Ю›ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЫ™Ю›ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ™Ю›ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫ™Ю›ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ™Ю›ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫ™Ю›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ™Ю›ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫ™Ю›ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫ™Ю›ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСУ‘Ц“В‚€ЪY€СђSRSWХUХQТT’B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ]ЭYЪ\љPЭ\›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ]ЭYЪ\љPЭ\›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ]ЭYЪ\љPЭ\›VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ]ЭYЪ\љPЭ\›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х]ЭYЪ\љPЭ\›VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ]ЭYЪ\љVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ]ЭYЪ\љPЭ\›VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ]ЭYЪ\љPЭ\›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ]ЭYЪ\љPЭ\›VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ]ЭYЪ\љQ›ЫЬVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ]ЭYЪ\љQ›ЫЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ]ЭYЪ\љQ›ЫЬVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ]ЭYЪ\љQ›ЫЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х]ЭYЪ\љQ›ЫЬVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ]ЭYЪ\љQ›ЫЬVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ]ЭYЪ\љQ›ЫЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ]ЭYЪ\љQ›ЫЬVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ]ЭYЪ\љTЭ™]ЪVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ]ЭYЪ\љTЭ™]ЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ]ЭYЪ\љTЭ™]ЪVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ]ЭYЪ\љTЭ™]ЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х]ЭYЪ\љTЭ™]ЪVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ]ЭYЪ\љTЭ™]ЪVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ]ЭYЪ\љTЭ™]ЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ]ЭYЪ\љTЭ™]ЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ССS—ОWУQQРWСU“УUSУ”В€ЫЫњЭLM€У[Ы”[]WХ]ЭYЪ\љSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ]ЭYЪ\љSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫYYШKЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ]ЭYЪ\љPЭ\›SYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ]ЭYЪ\љPЭ\›SYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х]ЭYЪ\љPЭ\›SYYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ]ЭYЪ\љPЭ\›SYYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WХ]ЭYЪ\љPЭ\›SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ]ЭYЪ\љPЭ\›SYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ]ЭYЪ\љQ›ЫЬSYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ]ЭYЪ\љQ›ЫЬSYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х]ЭYЪ\љQ›ЫЬSYYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ]ЭYЪ\љQ›ЫЬSYYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WХ]ЭYЪ\љQ›ЫЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ]ЭYЪ\љQ›ЫЬSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЩ›ЫЬKЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ]ЭYЪ\љTЭ™]ЪSYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ]ЭYЪ\љTЭ™]ЪSYYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х]ЭYЪ\љTЭ™]ЪSYYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ]ЭYЪ\љTЭ™]ЪSYYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WХ]ЭYЪ\љTЭ™]ЪSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ]ЭYЪ\љTЭ™]ЪSYYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э]ЭYЪ\љKЬЭ™]ЪKЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ€Щ[™Y€ЛФССS—ОWУQQРWСU“УUSУ”В€Щ[™Y€ЛФСђSRSWХUХQТT’B‚€ЪY€СђSRSWСФ‘PUХTТВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЬ™X]\ЪЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]Э\ЪЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЬ™X]\ЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]Э\ЪЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЬ™X]\ЪЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]Э\ЪЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЬ™X]\ЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]Э\ЪЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЬ™X]\ЪЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]Э\ЪЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЬ™X]\ЪЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]Э\ЪЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЬ™X]\ЪЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]Э\ЪЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЬ™X]\ЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]Э\ЪЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЬ™X]\ЪЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЬ™X]Э\ЪЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСФ‘PUХTТВ‚€ЪY€СђSRSWФРФ‘PSWХRS€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШЬ™X[UZ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЬ™X[WЭZ[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШЬ™X[UZ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЬ™X[WЭZ[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШЬ™X[UZ[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЬ™X[WЭZ[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШЬ™X[UZ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЬ™X[WЭZ[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШЬ™X[UZ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЬ™X[WЭZ[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФШЬ™X[UZ[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЬ™X[WЭZ[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШЬ™X[UZ[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШЬ™X[WЭZ[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФШЬ™X[UZ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЬ™X[WЭZ[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШЬ™X[UZ[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЬ™X[WЭZ[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФРФ‘PSWХRS‚€ЪY€СђSRSWР”•UWР“У“‘U€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРњќ]P›Ы›™]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ]WШ›Ы›™]Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРњќ]P›Ы›™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ]WШ›Ы›™]Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРњќ]P›Ы›™]ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ]WШ›Ы›™]ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРњќ]P›Ы›™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ]WШ›Ы›™]ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Рњќ]P›Ы›™]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шњќ]WШ›Ы›™]ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРњќ]P›Ы›™]ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Шњќ]WШ›Ы›™]Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРњќ]P›Ы›™]ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Шњќ]WШ›Ы›™]ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРњќ]P›Ы›™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ]WШ›Ы›™]ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРњќ]P›Ы›™]ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Шњќ]WШ›Ы›™]ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWР”•UWР“У“‘U‚€ЪY€СђSRSWС“UT—УPS‘B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС›]\“X[™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]\—ЫX[™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС›]\“X[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]\—ЫX[™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС›]\“X[™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]\—ЫX[™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС›]\“X[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]\—ЫX[™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С›]\“X[™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›]\—ЫX[™KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС›]\“X[™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ›]\—ЫX[™KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС›]\“X[™VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ›]\—ЫX[™KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС›]\“X[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]\—ЫX[™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС›]\“X[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›]\—ЫX[™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWС“UT—УPS‘B‚€ЪY€СђSRSWФУUT—ХТS‘В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЫ]\•Ъ[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ]\—ЭЪ[™ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЫ]\•Ъ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ]\—ЭЪ[™ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЫ]\•Ъ[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ]\—ЭЪ[™ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЫ]\•Ъ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ]\—ЭЪ[™ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЫ]\•Ъ[™ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ]\—ЭЪ[™ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЫ]\•Ъ[™ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ]\—ЭЪ[™ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЫ]\•Ъ[™ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ]\—ЭЪ[™ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЫ]\•Ъ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ]\—ЭЪ[™ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЫ]\•Ъ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫ]\—ЭЪ[™ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФУUT—ХТS‘В‚€ЪY€СђSRSWФРS‘WФТРТФВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФШ[™TЪШЪЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™WЬЪШЪЬЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФШ[™TЪШЪЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™WЬЪШЪЬЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФШ[™TЪШЪЬЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™WЬЪШЪЬЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФШ[™TЪШЪЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™WЬЪШЪЬЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФШ[™TЪШЪЬЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™WЬЪШЪЬЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФШ[™TЪШЪЬЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™WЬЪШЪЬЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФШ[™TЪШЪЬЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™WЬЪШЪЬЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФШ[™TЪШЪЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™WЬЪШЪЬЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФШ[™TЪШЪЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШ[™WЬЪШЪЬЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФРS‘WФТРТФВ‚€ЪY€СђSRSWТT“У—Х‘PQВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›Ы•™XYЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э™XYЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›Ы•™XYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э™XYЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›Ы•™XYЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э™XYЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›Ы•™XYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э™XYЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›Ы•™XYЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э™XYЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›Ы•™XYЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э™XYЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›Ы•™XYЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э™XYЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›Ы•™XYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э™XYЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›Ы•™XYЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э™XYЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—Х‘PQВ‚€ЪY€СђSRSWТT“У—Р•S‘B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›Ыђќ[™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Шќ[™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›Ыђќ[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Шќ[™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›Ыђќ[™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Шќ[™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›Ыђќ[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Шќ[™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›Ыђќ[™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Шќ[™KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›Ыђќ[™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Шќ[™KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›Ыђќ[™VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Шќ[™KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›Ыђќ[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Шќ[™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›Ыђќ[™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Шќ[™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—Р•S‘B‚€ЪY€СђSRSWТT“У—ТS‘В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›Ы’[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ъ[™ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›Ы’[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ъ[™ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›Ы’[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ъ[™ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›Ы’[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ъ[™ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›Ы’[™ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ъ[™ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›Ы’[™ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ъ[™ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›Ы’[™ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ъ[™ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›Ы’[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ъ[™ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›Ы’[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ъ[™ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—ТS‘В‚€ЪY€СђSRSWТT“У—Т•QХSTВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›Ы’ќYЭ[\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЪќYЭ[\ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›Ы’ќYЭ[\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЪќYЭ[\ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›Ы’ќYЭ[\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЪќYЭ[\ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›Ы’ќYЭ[\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЪќYЭ[\ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›Ы’ќYЭ[\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЪќYЭ[\ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›Ы’ќYЭ[\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЪќYЭ[\ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›Ы’ќYЭ[\ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЪќYЭ[\ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›Ы’ќYЭ[\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЪќYЭ[\ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›Ы’ќYЭ[\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЪќYЭ[\ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—Т•QХSTВ‚€ЪY€СђSRSWТT“У—УSХ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›Ы“[ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ы[ЭЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›Ы“[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ы[ЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›Ы“[ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ы[ЭШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›Ы“[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ы[ЭЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›Ы“[ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ы[ЭЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›Ы“[ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ы[ЭЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›Ы“[ЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ы[ЭЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›Ы“[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ы[ЭЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›Ы“[ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ы[ЭЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—УSХ‚€ЪY€СђSRSWТT“У—ХФ“”В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›Ы•Ь›њЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЭЬ›њЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›Ы•Ь›њЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЭЬ›њЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›Ы•Ь›њЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЭЬ›њЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›Ы•Ь›њЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЭЬ›њЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›Ы•Ь›њЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЭЬ›њЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›Ы•Ь›њЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЭЬ›њЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›Ы•Ь›њЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЭЬ›њЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›Ы•Ь›њЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЭЬ›њЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›Ы•Ь›њЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЭЬ›њЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—ХФ“”В‚€ЪY€СђSRSWС”’QТPђV€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСњљYЪX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩњљYЪX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСњљYЪX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩњљYЪX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСњљYЪX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩњљYЪX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСњљYЪX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩњљYЪX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СњљYЪX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩњљYЪX^ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСњљYЪX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩњљYЪX^Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСњљYЪX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩњљYЪX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСњљYЪX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩњљYЪX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСњљYЪX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩњљYЪX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР\ЭX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭX^Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР\ЭX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭX^Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР\ЭX^ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭX^ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР\ЭX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭX^ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р\ЭX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭX^ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР\ЭX^ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭX^Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР\ЭX^ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭX^ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР\ЭX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭX^ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР\ЭX^ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш\ЭX^ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР^Ш[Xќ\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР^Ш[Xќ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР^Ш[Xќ\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР^Ш[Xќ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р^Ш[Xќ\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќР^Ш[Xќ\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧР^Ш[Xќ\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WР^Ш[Xќ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР^Ш[Xќ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЪY€ССS—ОWУQQРWСU“УUSУ”В€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧР^Ш[Xќ\“YYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫYYШKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WР^Ш[Xќ\“YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫYYШKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧР^Ш[Xќ\“YYШVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫYYШKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WР^Ш[Xќ\“YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫYYШKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Р^Ш[Xќ\“YYШVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫYYШKЪXЫЫ‹ЌњЉNВ€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧР^Ш[Xќ\“YYШVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫYYШKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WР^Ш[Xќ\“YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫYYШKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WР^Ш[Xќ\“YYШVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш^Ш[Xќ\‹ЫYYШKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•И	‰€ХЧРђUWУУ“WС“Ф“TВ€Щ[™Y€ЛФССS—ОWУQQРWСU“УUSУ”В€Щ[™Y€ЛФСђSRSWС”’QТPђV‚€ЪY€СђSRSWСТSSRQТХS€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЪ[[ZYЪЭ[Ъ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЪ[[ZYЪЭ[Ъ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЪ[[ZYЪЭ[Ъ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЪ[[ZYЪЭ[Ъ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЪ[[ZYЪЭ[Ъ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЪ[[ZYЪЭ[Ъ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЪ[[ZYЪЭ[Ъ\ЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЪ[[ZYЪЭ[Ъ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЪ[[ZYЪЭ[Ъ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЪ[[ZYЪЭ[›Ш[Z[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ь›Ш[Z[™ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЪ[[ZYЪЭ[›Ш[Z[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ь›Ш[Z[™ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЪ[[ZYЪЭ[›Ш[Z[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ь›Ш[Z[™ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЪ[[ZYЪЭ[›Ш[Z[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ь›Ш[Z[™ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЪ[[ZYЪЭ[›Ш[Z[™ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ь›Ш[Z[™ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЪ[[ZYЪЭ[›Ш[Z[™ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ь›Ш[Z[™ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЪ[[ZYЪЭ[›Ш[Z[™ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ь›Ш[Z[™ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WСЪ[[ZYЪЭ[›Ш[Z[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ь›Ш[Z[™ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЪ[[ZYЪЭ[›Ш[Z[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪ[[ZYЪЭ[Ь›Ш[Z[™ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЪЫ[™ЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪЫ[™ЫЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЪЫ[™ЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪЫ[™ЫЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЪЫ[™ЫЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪЫ[™ЫЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЪЫ[™ЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪЫ[™ЫЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЪЫ[™ЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЪЫ[™ЫЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЪЫ[™ЫЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЪЫ[™ЫЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЪЫ[™ЫЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЪЫ[™ЫЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЪЫ[™ЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪЫ[™ЫЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЪЫ[™ЫЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЪЫ[™ЫЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСТSSRQТХS‚€ЪY€СђSRSWХУЧРТQS‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХЫРЪY[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЧШЪY[‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХЫРЪY[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЧШЪY[‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХЫРЪY[–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЧШЪY[‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХЫРЪY[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЧШЪY[‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХЫРЪY[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЧШЪY[‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХЫРЪY[–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЧШЪY[‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХЫРЪY[–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЧШЪY[‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХЫРЪY[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЧШЪY[‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХЫРЪY[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭЫЧШЪY[‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХУЧРТQS‚‚€ЪY€СђSRSWРТQS—ФSВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЪY[”[ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪY[—Ь[ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЪY[”[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪY[—Ь[ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЪY[”[ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪY[—Ь[ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЪY[”[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪY[—Ь[ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЪY[”[ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪY[—Ь[ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЪY[”[ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪY[—Ь[ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЪY[”[ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЪY[—Ь[ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЪY[”[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪY[—Ь[ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЪY[”[ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪY[—Ь[ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРТQS—ФSВ‚€ЪY€СђSRSWХS‘ЧУB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ[™УVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™ЧЫKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ[™УVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™ЧЫKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ[™УVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™ЧЫKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ[™УVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™ЧЫKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х[™УVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[™ЧЫKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ[™УVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э[™ЧЫKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ[™УVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э[™ЧЫKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ[™УVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™ЧЫKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ[™УVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[™ЧЫKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХS‘ЧУB‚€ЪY€СђSRSWРТWЦUB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧРЪV]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪWЮ]KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WРЪV]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪWЮ]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧРЪV]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪWЮ]KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WРЪV]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪWЮ]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—РЪV]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪWЮ]KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќРЪV]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ШЪWЮ]KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧРЪV]VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ШЪWЮ]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WРЪV]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪWЮ]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WРЪV]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪWЮ]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWРТWЦUB‚€ЪY€СђSRSWФ“РT’S‘ЧУSУУ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФ›Ш\љ[™У[ЫЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›Ш\љ[™ЧЫ[ЫЫ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФ›Ш\љ[™У[ЫЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›Ш\љ[™ЧЫ[ЫЫ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФ›Ш\љ[™У[ЫЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›Ш\љ[™ЧЫ[ЫЫ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФ›Ш\љ[™У[ЫЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›Ш\љ[™ЧЫ[ЫЫ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Ф›Ш\љ[™У[ЫЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь›Ш\љ[™ЧЫ[ЫЫ‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФ›Ш\љ[™У[ЫЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ь›Ш\љ[™ЧЫ[ЫЫ‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФ›Ш\љ[™У[ЫЫ–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ь›Ш\љ[™ЧЫ[ЫЫ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФ›Ш\љ[™У[ЫЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›Ш\љ[™ЧЫ[ЫЫ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФ›Ш\љ[™У[ЫЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь›Ш\љ[™ЧЫ[ЫЫ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФ“РT’S‘ЧУSУУ‚‚€ЪY€СђSRSWТT“У—ХђSPS•€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›Ы•[X[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э[X[ќЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›Ы•[X[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э[X[ќЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›Ы•[X[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э[X[ќШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›Ы•[X[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э[X[ќЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›Ы•[X[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э[X[ќЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›Ы•[X[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э[X[ќЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›Ы•[X[ќЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э[X[ќЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›Ы•[X[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э[X[ќЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›Ы•[X[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Э[X[ќЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—ХђSPS•‚€ЪY€СђSRSWТУФђRQУ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТЫЬZYЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЬZYЫ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТЫЬZYЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЬZYЫ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТЫЬZYЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЬZYЫ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТЫЬZYЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЬZYЫ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ТЫЬZYЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЬZYЫ‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТЫЬZYЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЬZYЫ‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТЫЬZYЫ–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЬZYЫ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТЫЬZYЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЬZYЫ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТЫЬZYЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЪЫЬZYЫ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТУФђRQУ‚‚€ЪY€СђSRSWУRTђRQУ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУZ\ZYЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ\ZYЫ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУZ\ZYЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ\ZYЫ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУZ\ZYЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ\ZYЫ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУZ\ZYЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ\ZYЫ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УZ\ZYЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ\ZYЫ‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУZ\ZYЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ\ZYЫ‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУZ\ZYЫ–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫZ\ZYЫ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУZ\ZYЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ\ZYЫ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУZ\ZYЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫZ\ZYЫ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУRTђRQУ‚‚€ЪY€СђSRSWХРSТS‘ЧХРRСB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХШ[Ъ[™ХШZЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ[Ъ[™ЧЭШZЩKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХШ[Ъ[™ХШZЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ[Ъ[™ЧЭШZЩKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХШ[Ъ[™ХШZЩVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ[Ъ[™ЧЭШZЩKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХШ[Ъ[™ХШZЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ[Ъ[™ЧЭШZЩKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ХШ[Ъ[™ХШZЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭШ[Ъ[™ЧЭШZЩKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХШ[Ъ[™ХШZЩVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЭШ[Ъ[™ЧЭШZЩKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХШ[Ъ[™ХШZЩVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЭШ[Ъ[™ЧЭШZЩKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХШ[Ъ[™ХШZЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ[Ъ[™ЧЭШZЩKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХШ[Ъ[™ХШZЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЭШ[Ъ[™ЧЭШZЩKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХРSТS‘ЧХРRСB‚€ЪY€СђSRSWТT“У—УPU‘TВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›Ы“X]™\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЫX]™\ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›Ы“X]™\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЫX]™\ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›Ы“X]™\ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЫX]™\ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›Ы“X]™\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЫX]™\ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›Ы“X]™\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЫX]™\ЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›Ы“X]™\ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЫX]™\ЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›Ы“X]™\ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЫX]™\ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›Ы“X]™\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЫX]™\ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›Ы“X]™\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ЫX]™\ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—УPU‘TВ‚€ЪY€СђSRSWФУТQСRTХ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЫЪYЩZ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЪYЩZ\ЭЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЫЪYЩZ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЪYЩZ\ЭЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЫЪYЩZ\ЭЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЪYЩZ\ЭШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЫЪYЩZ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЪYЩZ\ЭЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЫЪYЩZ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЪYЩZ\ЭЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЫЪYЩZ\ЭЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЪYЩZ\ЭЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЫЪYЩZ\ЭЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЪYЩZ\ЭЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЫЪYЩZ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЪYЩZ\ЭЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЫЪYЩZ\ЭЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЫЪYЩZ\ЭЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФЪ[љ\ЭЪVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭЪKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФЪ[љ\ЭЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭЪKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФЪ[љ\ЭЪVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭЪKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФЪ[љ\ЭЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭЪKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФЪ[љ\ЭЪVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭЪKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФЪ[љ\ЭЪVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭЪKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФЪ[љ\ЭЪVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭЪKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФЪ[љ\ЭЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭЪKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФЪ[љ\ЭЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬЪ[љ\ЭЪKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФУТQСRTХ‚€ЪY€СђSRSWУТТQСТB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЪЪYЩЪVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪYЩЪKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЪЪYЩЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪYЩЪKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЪЪYЩЪVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪYЩЪKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЪЪYЩЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪYЩЪKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЪЪYЩЪVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪYЩЪKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУЪЪYЩЪVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪYЩЪKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЪЪYЩЪVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪYЩЪKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЪЪYЩЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪYЩЪKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЪЪYЩЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЪЪYЩЪKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУТТQСТB‚€ЪY€СђSRSWУUS’ТQФ’B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУ][љЪYЬљVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы][љЪYЬљKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУ][љЪYЬљVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы][љЪYЬљKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУ][љЪYЬљVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы][љЪYЬљKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУ][љЪYЬљVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы][љЪYЬљKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—У][љЪYЬљVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы][љЪYЬљKЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУ][љЪYЬљVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ы][љЪYЬљKЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУ][љЪYЬљVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ы][љЪYЬљKЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУ][љЪYЬљVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы][љЪYЬљKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУ][љЪYЬљVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы][љЪYЬљKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУUS’ТQФ’B‚€ЪY€СђSRSWС‘VђS‘TUB€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧС™^[™\]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™^[™\]KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WС™^[™\]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™^[™\]KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧС™^[™\]VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™^[™\]KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WС™^[™\]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™^[™\]KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—С™^[™\]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ™^[™\]KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќС™^[™\]VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Щ™^[™\]KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧС™^[™\]VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Щ™^[™\]KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WС™^[™\]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™^[™\]KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WС™^[™\]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ™^[™\]KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWС‘VђS‘TUB‚€ЪY€СђSRSWУССT”У‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЩЩ\њЫ•X[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЩЩ\њЫ•X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЩЩ\њЫ•X[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЩЩ\њЫ•X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЩЩ\њЫ•X[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќУЩЩ\њЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЩЩ\њЫ•Щ[Ьљ[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЩЩ\њЫ•Щ[Ьљ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЩЩ\њЫ•Щ[Ьљ[™ЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЩЩ\њЫ•Щ[Ьљ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЩЩ\њЫ•Щ[Ьљ[™ЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЩЩ\њЫ’X\ќ›[YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЩЩ\њЫ’X\ќ›[YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЩЩ\њЫ’X\ќ›[YVЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЩЩ\њЫ’X\ќ›[YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЩЩ\њЫ’X\ќ›[YVЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЩЩ\њЫђЫЬ›™\њЭЫ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЩЩ\њЫђЫЬ›™\њЭЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЩЩ\њЫђЫЬ›™\њЭЫ™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЩЩ\њЫђЫЬ›™\њЭЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—УЩЩ\њЫђЫЬ›™\њЭЫ™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЪXЫЫ‹ЌњЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЩЩ\њЫ•X[\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭX[Э\KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЩЩ\њЫ•X[\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭX[Э\KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЩЩ\њЫ•X[\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭX[Э\KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЩЩ\њЫ•X[\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭX[Э\KЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЩЩ\њЫ•Щ[Ьљ[™Х\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЧЭ\KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЩЩ\њЫ•Щ[Ьљ[™Х\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЧЭ\KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЩЩ\њЫ•Щ[Ьљ[™Х\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЧЭ\KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЩЩ\њЫ•Щ[Ьљ[™Х\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЧЭ\KЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЩЩ\њЫ’X\ќ›[YU\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YWЭ\KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЩЩ\њЫ’X\ќ›[YU\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YWЭ\KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЩЩ\њЫ’X\ќ›[YU\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YWЭ\KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЩЩ\њЫ’X\ќ›[YU\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YWЭ\KЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧУЩЩ\њЫђЫЬ›™\њЭЫ™U\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™WЭ\KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WУЩЩ\њЫђЫЬ›™\њЭЫ™U\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™WЭ\KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧУЩЩ\њЫђЫЬ›™\њЭЫ™U\VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™WЭ\KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WУЩЩ\њЫђЫЬ›™\њЭЫ™U\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™WЭ\KЬЪ[ћK™Ш\[ЉNВ‚€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЩЩ\њЫ•X[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЩЩ\њЫ•Щ[Ьљ[™ЦЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЩЩ\њЫ’X\ќ›[YVЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЫЭ™\ќЫЬ›ЌњЉNВ€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЩЩ\њЫђЫЬ›™\њЭЫ™VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЫЭ™\ќЫЬ›ЌњЉNВ€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЩЩ\њЫ•Щ[Ьљ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЩЩ\њЫ•Щ[Ьљ[™ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЩЩ\њЫ’X\ќ›[YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЩЩ\њЫ’X\ќ›[YVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЩЩ\њЫђЫЬ›™\њЭЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЩЩ\њЫђЫЬ›™\њЭЫ™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЩЩ\њЫ•X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЩЩ\њЫ•X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ‚€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЩЩ\њЫ•X[\VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЩЩ\њЫ•Щ[Ьљ[™Х\VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЫЭ™\ќЫЬ›ЌњЉNВ€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЩЩ\њЫ’X\ќ›[YU\VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЫЭ™\ќЫЬ›ЌњЉNВ€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧУЩЩ\њЫђЫЬ›™\њЭЫ™U\VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЫЭ™\ќЫЬ›ЌњЉNВ€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЩЩ\њЫ•Щ[Ьљ[™Х\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЩЩ\њЫ•Щ[Ьљ[™Х\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЭЩ[Ьљ[™ЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЩЩ\њЫ’X\ќ›[YU\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЩЩ\њЫ’X\ќ›[YU\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЪX\ќ›[YKЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЩЩ\њЫђЫЬ›™\њЭЫ™U\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЩЩ\њЫђЫЬ›™\њЭЫ™U\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ШЫЬ›™\њЭЫ™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭLM€УЭ™\ќЫЬ›[]WУЩЩ\њЫ•X[\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WУЩЩ\њЫ•X[\VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫЩЩ\њЫ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWУССT”У‚‚€ЪY€СђSRSWСУХQТS‘ЧС’T‘B€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСЫЭYЪ[™Сљ\™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЭYЪ[™ЧЩљ\™KЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСЫЭYЪ[™Сљ\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЭYЪ[™ЧЩљ\™KЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧСЫЭYЪ[™Сљ\™VЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЭYЪ[™ЧЩљ\™KШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WСЫЭYЪ[™Сљ\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЭYЪ[™ЧЩљ\™KЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СЫЭYЪ[™Сљ\™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЭYЪ[™ЧЩљ\™KЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќСЫЭYЪ[™Сљ\™VЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЭYЪ[™ЧЩљ\™KЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧСЫЭYЪ[™Сљ\™VЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЭYЪ[™ЧЩљ\™KЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WСЫЭYЪ[™Сљ\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЭYЪ[™ЧЩљ\™KЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WСЫЭYЪ[™Сљ\™VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЫЭYЪ[™ЧЩљ\™KЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWСУХQТS‘ЧС’T‘B‚€ЪY€СђSRSWФђQТS‘ЧР“У€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФYЪ[™Р›ЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬYЪ[™ЧШ›ЫЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФYЪ[™Р›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬYЪ[™ЧШ›ЫЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФYЪ[™Р›ЫЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬYЪ[™ЧШ›ЫШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФYЪ[™Р›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬYЪ[™ЧШ›ЫЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФYЪ[™Р›ЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬYЪ[™ЧШ›ЫЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФYЪ[™Р›ЫЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬYЪ[™ЧШ›ЫЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФYЪ[™Р›ЫЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬYЪ[™ЧШ›ЫЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФYЪ[™Р›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬYЪ[™ЧШ›ЫЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФYЪ[™Р›ЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬYЪ[™ЧШ›ЫЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФђQТS‘ЧР“У‚€ЪY€СђSRSWТT“У—Р“ХST‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›Ыђ›Э[\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ш›Э[\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›Ыђ›Э[\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ш›Э[\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›Ыђ›Э[\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ш›Э[\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›Ыђ›Э[\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ш›Э[\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›Ыђ›Э[\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ш›Э[\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›Ыђ›Э[\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ш›Э[\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›Ыђ›Э[\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ш›Э[\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›Ыђ›Э[\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ш›Э[\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›Ыђ›Э[\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—Ш›Э[\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—Р“ХST‚‚€ЪY€СђSRSWТT“У—РФ“ХУ‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧТ\›ЫђЬ›ЭЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ШЬ›ЭЫ‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WТ\›ЫђЬ›ЭЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ШЬ›ЭЫ‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧТ\›ЫђЬ›ЭЫ–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ШЬ›ЭЫ‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WТ\›ЫђЬ›ЭЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ШЬ›ЭЫ‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Т\›ЫђЬ›ЭЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ШЬ›ЭЫ‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќТ\›ЫђЬ›ЭЫ–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ШЬ›ЭЫ‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧТ\›ЫђЬ›ЭЫ–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ШЬ›ЭЫ‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WТ\›ЫђЬ›ЭЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ШЬ›ЭЫ‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WТ\›ЫђЬ›ЭЫ–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\›Ы—ШЬ›ЭЫ‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWТT“У—РФ“ХУ‚‚€ЪY€СђSRSWХTђTQУФВ€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\\YЫЬУ›Ь›X[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\\YЫЬУ›Ь›X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\\YЫЬУ›Ь›X[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\\YЫЬУ›Ь›X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\\YЫЬУ›Ь›X[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\\YЫЬУ›Ь›X[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\\YЫЬУ›Ь›X[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\\YЫЬУ›Ь›X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\\YЫЬУ›Ь›X[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\\YЫЬХ\\Э[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЭ\\Э[Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\\YЫЬХ\\Э[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЭ\\Э[Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\\YЫЬХ\\Э[ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЭ\\Э[ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\\YЫЬХ\\Э[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЭ\\Э[ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\\YЫЬХ\\Э[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЭ\\Э[ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\\YЫЬХ\\Э[ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЭ\\Э[Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\\YЫЬХ\\Э[ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЭ\\Э[ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\\YЫЬХ\\Э[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЭ\\Э[ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\\YЫЬХ\\Э[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЭ\\Э[ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧХ\\YЫЬФЭ[\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЭ[\‹Щњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WХ\\YЫЬФЭ[\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЭ[\‹Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧХ\\YЫЬФЭ[\–ЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЭ[\‹ШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WХ\\YЫЬФЭ[\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЭ[\‹ЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—Х\\YЫЬФЭ[\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЭ[\‹ЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќХ\\YЫЬФЭ[\–ЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЭ[\‹Щ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В‹ЛИЫЫњЭLМ€УШљ™XЭ]™[ќXЧХ\\YЫЬФЭ[\–ЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЭ[\‹ЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB‹ЛИЫЫњЭLM€УЭ™\ќЫЬ›[]WХ\\YЫЬФЭ[\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЭ[\‹ЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ‹ЛИЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WХ\\YЫЬФЭ[\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\\YЫЬЛЬЭ[\‹ЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWХTђTQУФВ‚€ЪY€СђSRSWФPТT•S•€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧФXЪ\ќ[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪ\ќ[ќЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WФXЪ\ќ[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪ\ќ[ќЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭLМ€У[ЫђXЪФXЧФXЪ\ќ[ќЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪ\ќ[ќШXЪЛЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]WФXЪ\ќ[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪ\ќ[ќЬЪ[ћK™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—ФXЪ\ќ[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪ\ќ[ќЪXЫЫ‹ЌњЉNВ€ЪY€С“УХ’S•В€ЫЫњЭNУ[Ы‘›ЫЭљ[ќФXЪ\ќ[ќЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪ\ќ[ќЩ›ЫЭљ[ќЊXњЉNВ€Щ[™Y€ЛФС“УХ’S•В€ЪY€ХЧФТСSSУ—УР’‘PХСU‘S•В€ЫЫњЭLМ€УШљ™XЭ]™[ќXЧФXЪ\ќ[ќЧHHSђР’S—РУУT
™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪ\ќ[ќЫЭ™\ќЫЬ›ЌњЉNВ€ЪY€ХЧФУS—УР’‘PХЧФТT‘WФSUTИOHђSСB€ЫЫњЭLM€УЭ™\ќЫЬ›[]WФXЪ\ќ[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪ\ќ[ќЫЭ™\ќЫЬ›Ы›Ь›X[™Ш\[ЉNВ€ЫЫњЭLM€ФЪ[ћSЭ™\ќЫЬ›[]WФXЪ\ќ[ќЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪ\ќ[ќЫЭ™\ќЫЬ›ЬЪ[ћK™Ш\[ЉNВ€Щ[™Y€ЛУХЧФУS—УР’‘PХЧФТT‘WФSUTВ€Щ[™Y€ЛУХЧФТСSSУ—УР’‘PХСU‘S•В€Щ[™Y€ЛФСђSRSWФPТT•S•‚€ЫЫњЭLМ€У[Ы‘њ›ЫќXЧСYЩЦЧHHSђР’S—ХLМЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩYЩЛШ[љ[WЩњ›ЫќЌњњЫ[ЫЉNВ€ЫЫњЭLM€У[Ы”[]WСYЩЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩYЩЛЫ›Ь›X[™Ш\[ЉNВ€ЫЫњЭNУ[Ы’XЫЫ—СYЩЦЧHHSђР’S—ХN
™Ь\XЬЛЬЪЩ[[Ы‹ЩYЩЛЪXЫЫ‹ЌњЉNВ‚€ЛИ[Щ\›€Ъ[ћH[]\И
”ИЭ\ЭЫHЪ[љY\КB€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—ФZШXЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬZШXЪKЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—ФZXЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬZXЪKЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—ФXЪVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬXЪKЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Ф\\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь\\ЛЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Х[ќXЫЫЫЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[ќXЫЫЫЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Х[ќXЬќY[ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э[ќXЬќY[ЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—С\™™]ЪЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ\™™]ЪЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Т][ќ\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ][ќ\‹ЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—СЩ[™Ш\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩЩ[™Ш\‹ЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—УX\›ЭШZЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЫX\›ЭШZЛЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—У\\ЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы\\ЛЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Х\Ь™[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Э\Ь™[Ы‹ЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Т›Ы[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ›Ы[Ы‹ЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—С›\™[Ы–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ›\™[Ы‹ЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Ц\ЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю\ЬЛЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—СYЫЫљ]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЩYЫЫљ]KЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—РЪ[ЪЭVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ШЪ[ЪЭKЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—У[ќ\›–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ы[ќ\›‹ЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Ц]VЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ю]KЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—ФШЮ]\–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹ЬШЮ]\‹ЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Т\XЬ›ЬЬЦЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ъ\XЬ›ЬЬЛЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Ф[њVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь[њKЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—С[ZЪYЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Щ[ZЪYЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Р›^љZЩ[–ЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ш›^љZЩ[‹ЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ€ЫЫњЭLM€У[Ы”Ъ[ћT[]S[Щ\›—Ф™YЪXЩVЧHHSђР’S—ХLMЉ™Ь\XЬЛЬЪЩ[[Ы‹Ь™YЪXЩKЬЪ[ћWЫ[Щ\›‹™Ш\[ЉNВ