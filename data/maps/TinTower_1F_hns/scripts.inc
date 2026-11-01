TinTower_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_OnTransition
	.byte 0

TinTower_OnTransition::
	setescapewarp MAP_BELLCHIME_TRAIL_HNS, 35, 42
	end

TinTower_1F_EventScript_SageA::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageA_Hooh
	msgbox TinTower_1F_Sage4_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageA_Hooh::
	msgbox TinTower_1F_Sage4_Text1, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageB_Hooh
	msgbox TinTower_1F_Sage2_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB_Hooh::
	msgbox TinTower_1F_Sage1_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageC_Hooh
	msgbox TinTower_1F_Sage6_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC_Hooh::
	msgbox TinTower_1F_Sage3_Text, MSGBOX_DEFAULT
	closemessage
	release
	end


TinTower_1F_Sage1_Text:
	.string "Old scrolls speak of a bird\n"
	.string "with golden wings.\p"
	.string "No one here has seen it.\n"
	.string "Some symbols resemble ALPH.$"

TinTower_1F_Sage2_Text:
	.string "When the BRASS TOWER burned,\n"
	.string "three POKéMON lost their lives.\p"
	.string "HO-OH restored them with a power\n"
	.string "our records could not explain.\p"
	.string "ALPH scholars think it was pure,\n"
	.string "natural RESONANCE.$"

TinTower_1F_Sage3_Text:
	.string "The two TOWERS stand on older\n"
	.string "foundations.\p"
	.string "Stonework beneath them resembles\n"
	.string "the RUINS OF ALPH.\p"
	.string "ECRUTEAK may be only one part\n"
	.string "of a much older network.$"

TinTower_1F_Sage4_Text1:
	.string "Some speak of golden wings\n"
	.string "above the old TIN TOWER.\p"
	.string "It may be only a rumour.$"

TinTower_1F_Sage4_Text2:
	.string "The legendary beasts embody\n"
	.string "lightning, fire and rain.\p"
	.string "UNOWN react to the same old pulse.\p"
	.string "Different legends...\n"
	.string "one RESONANCE.$"

TinTower_1F_Sage6_Text2:
	.string "Of the legendary POKéMON,\n"
	.string "SUICUNE is closest to HO-OH.\p"
	.string "Old records show UNOWN glyphs\n"
	.string "beside drawings of the beasts.\p"
	.string "The connection predates ECRUTEAK.$"

TinTower_1F_EusineHoOh_Text:
	.string "EUSINE: They say a golden bird\n"
	.string "once crossed these skies.\p"
	.string "I haven't seen proof yet!\n"
	.string "I'll keep researching it.$"

TinTower_1F_EusineSuicune_Text:
	.string "EUSINE: That was amazing!\p"
	.string "SUICUNE was tough, but your\n"
	.string "bond was stronger, <PLAYER>.\p"
	.string "I have heard rumours of a bird\n"
	.string "with rainbow-coloured wings.\p"
	.string "It is still only a legend.\n"
	.string "I shall keep studying!$"
