DragonsDen_StormShrine_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DragonsDen_StormShrine_OnTransition
	.byte 0

DragonsDen_StormShrine_OnTransition::
	goto_if_set FLAG_PRU_RAYQUAZA_CAUGHT, DragonsDen_StormShrine_HideRayquaza
	clearflag FLAG_PRU_HIDE_RAYQUAZA
	end

DragonsDen_StormShrine_HideRayquaza::
	setflag FLAG_PRU_HIDE_RAYQUAZA
	end

DragonsDen_StormShrine_EventScript_Rayquaza::
	lock
	faceplayer
	goto_if_set FLAG_PRU_RAYQUAZA_CAUGHT, DragonsDen_StormShrine_RayquazaUnavailable
	msgbox DragonsDen_StormShrine_Text_Intro, MSGBOX_DEFAULT
	fadescreenswapbuffers FADE_TO_BLACK
	playse SE_THUNDER
	fadescreenswapbuffers FADE_FROM_BLACK
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattleshiny SPECIES_RAYQUAZA, 85
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, DragonsDen_StormShrine_RayquazaCaught
	removeobject LOCALID_PRU_STORM_RAYQUAZA
	release
	end

DragonsDen_StormShrine_RayquazaUnavailable::
	release
	end

DragonsDen_StormShrine_RayquazaCaught::
	setflag FLAG_PRU_RAYQUAZA_CAUGHT
	setflag FLAG_PRU_HIDE_RAYQUAZA
	removeobject LOCALID_PRU_STORM_RAYQUAZA
	msgbox DragonsDen_StormShrine_Text_Caught, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Trigger_StormShrine::
	lock
	goto_if_unset FLAG_BADGE08_GET, DragonsDen_Shrine_StormShrineLocked
	goto_if_unset FLAG_IS_CHAMPION, DragonsDen_Shrine_StormShrineLocked
	msgbox DragonsDen_Shrine_StormShrineOpenText, MSGBOX_DEFAULT
	playse SE_THUNDER
	fadescreenswapbuffers FADE_TO_BLACK
	warp MAP_DRAGONS_DEN_STORM_SHRINE_HNS, 6, 15
	waitstate
	end

DragonsDen_Shrine_StormShrineLocked::
	msgbox DragonsDen_Shrine_StormShrineLockedText, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_StormShrineLockedText:
	.string "A powerful wind resists your passage...\p"
	.string "Only a JOHTO LEAGUE Champion who has\n"
	.string "earned CLAIR's trust may enter.$"

DragonsDen_Shrine_StormShrineOpenText:
	.string "The dragon seal recognises you...\\p"
	.string "Beyond this door lies the STORM\\n"
	.string "SHRINE. A strong wind draws you in!$"

DragonsDen_StormShrine_Text_Intro:
	.string "A violent wind fills the chamber...\p"
	.string "Lightning tears through the darkness!\p"
	.string "RAYQUAZA descended from the storm!$"

DragonsDen_StormShrine_Text_Caught:
	.string "The storm has fallen silent...\p"
	.string "RAYQUAZA will remain with you.$"
