EcruteakCity_RockShop_hns_MapScripts::
	.byte 0

@ Azul Agua / Water Blue inspired Rock Shop.
@ Keep PJR progression/economy; visuals are ported separately from the donor asset bank.
EcruteakCity_RockShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_BADGE04_GET, EcruteakCity_RockShop_EventScript_ClerkAdvanced
	message gText_HowMayIServeYou
	waitmessage
	pokemart EcruteakCity_RockShop_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

EcruteakCity_RockShop_EventScript_ClerkAdvanced::
	message gText_HowMayIServeYou
	waitmessage
	pokemart EcruteakCity_RockShop_Advanced
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

EcruteakCity_RockShop_EventScript_Collector::
	lock
	faceplayer
	msgbox EcruteakCity_RockShop_Text_Collector, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_RockShop_EventScript_EeveelutionExpert::
	lock
	faceplayer
	msgbox EcruteakCity_RockShop_Text_ExpertGreeting, MSGBOX_DEFAULT
	goto EcruteakCity_RockShop_EventScript_EeveelutionExpertMenu
	end

EcruteakCity_RockShop_EventScript_EeveelutionExpertMenu::
	msgbox EcruteakCity_RockShop_Text_ExpertPrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, EcruteakCity_RockShop_Text_ExpertOptionClassic, EcruteakCity_RockShop_Text_ExpertOptionRelic, EcruteakCity_RockShop_Text_ExpertOptionUnusual, EcruteakCity_RockShop_Text_ExpertOptionGoodbye
	switch VAR_RESULT
	case 0, EcruteakCity_RockShop_EventScript_ExpertClassic
	case 1, EcruteakCity_RockShop_EventScript_ExpertRelic
	case 2, EcruteakCity_RockShop_EventScript_ExpertUnusual
	case 3, EcruteakCity_RockShop_EventScript_ExpertGoodbye
	case MULTI_B_PRESSED, EcruteakCity_RockShop_EventScript_ExpertGoodbye
	goto EcruteakCity_RockShop_EventScript_EeveelutionExpertMenu
	end

EcruteakCity_RockShop_EventScript_ExpertClassic::
	msgbox EcruteakCity_RockShop_Text_ExpertClassic, MSGBOX_DEFAULT
	goto EcruteakCity_RockShop_EventScript_EeveelutionExpertMenu
	end

EcruteakCity_RockShop_EventScript_ExpertRelic::
	msgbox EcruteakCity_RockShop_Text_ExpertRelic, MSGBOX_DEFAULT
	goto EcruteakCity_RockShop_EventScript_EeveelutionExpertMenu
	end

EcruteakCity_RockShop_EventScript_ExpertUnusual::
	msgbox EcruteakCity_RockShop_Text_ExpertUnusual, MSGBOX_DEFAULT
	goto EcruteakCity_RockShop_EventScript_EeveelutionExpertMenu
	end

EcruteakCity_RockShop_EventScript_ExpertGoodbye::
	msgbox EcruteakCity_RockShop_Text_ExpertGoodbye, MSGBOX_DEFAULT
	release
	end

EcruteakCity_RockShop_EventScript_ExpertEevee::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_EEVEE, CRY_MODE_NORMAL
	msgbox EcruteakCity_RockShop_Text_ExpertEevee, MSGBOX_DEFAULT
	waitmoncry
	release
	end

	.align 2
EcruteakCity_RockShop_Basic:
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_ICE_STONE
	.2byte ITEM_MOON_STONE
	.2byte ITEM_SUN_STONE
	.2byte ITEM_OVAL_STONE
	.2byte ITEM_EVERSTONE
	.2byte ITEM_ANCIENT_STONE
	pokemartlistend

	.align 2
EcruteakCity_RockShop_Advanced:
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_ICE_STONE
	.2byte ITEM_MOON_STONE
	.2byte ITEM_SUN_STONE
	.2byte ITEM_OVAL_STONE
	.2byte ITEM_EVERSTONE
	.2byte ITEM_ANCIENT_STONE
	.2byte ITEM_SHINY_STONE
	.2byte ITEM_DUSK_STONE
	.2byte ITEM_DAWN_STONE
	pokemartlistend

EcruteakCity_RockShop_Text_ExpertGreeting:
    .string "Ah, an EEVEE fan!\n"
    .string "My friend and I studied\p"
    .string "all 18 of PRU's\n"
    .string "approved EEVEELUTIONS!$"

EcruteakCity_RockShop_Text_ExpertPrompt:
    .string "Which evolution group\n"
    .string "would you like to study?$"

EcruteakCity_RockShop_Text_ExpertOptionClassic:
    .string "Classic Eeveelutions$"
EcruteakCity_RockShop_Text_ExpertOptionRelic:
    .string "Relic Eeveelutions$"
EcruteakCity_RockShop_Text_ExpertOptionUnusual:
    .string "More unusual evolutions$"
EcruteakCity_RockShop_Text_ExpertOptionGoodbye:
    .string "Goodbye$"

EcruteakCity_RockShop_Text_ExpertClassic:
    .string "WATER STONE: VAPOREON\n"
    .string "THUNDER STONE: JOLTEON\p"
    .string "FIRE STONE: FLAREON\n"
    .string "SUN STONE: ESPEON\p"
    .string "MOON STONE: UMBREON\n"
    .string "LEAF STONE: LEAFEON\p"
    .string "ICE STONE: GLACEON\n"
    .string "DAWN STONE: SYLVEON\p"
    .string "DAWN STONE is sold here after the\n"
    .string "FOG BADGE.$"

EcruteakCity_RockShop_Text_ExpertRelic:
    .string "ANCIENT STONE: EEVEEON\n"
    .string "SHINY STONE: NIMBEON\p"
    .string "DUSK STONE: OMEON\n"
    .string "ANCIENT STONE is sold here.\p"
    .string "SHINY and DUSK STONES\n"
    .string "unlock after the FOG BADGE.$"

EcruteakCity_RockShop_Text_ExpertUnusual:
    .string "EXPERT BELT: CHAMPEON\n"
    .string "SILVER POWDER: LEPIDEON\p"
    .string "SOFT SAND: SPHYNXEON\n"
    .string "METAL COAT: GUARDEON\p"
    .string "HARD STONE: OBSIDEON\n"
    .string "POISON BARB: TOXEON\p"
    .string "DRAGON FANG: DRAKEON\n"
    .string "Use the matching item on EEVEE.\p"
    .string "These seven items aren't\n"
    .string "stocked in this Rock Shop.$"

EcruteakCity_RockShop_Text_ExpertGoodbye:
    .string "Happy evolving! EEVEE and I\n"
    .string "are always here to help!$"

EcruteakCity_RockShop_Text_ExpertEevee:
    .string "EEVEE tilts its head and\n"
    .string "chirps happily!$"

EcruteakCity_RockShop_Text_Collector:
	.string "These stones have been gathered\n"
	.string "from all across JOHTO.\p"
	.string "Some seem to react strangely near\n"
	.string "ECRUTEAK's old towers...$"
