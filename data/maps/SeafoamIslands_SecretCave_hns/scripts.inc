
SeafoamIslands_SecretCave_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_SecretCave_OnTransition
	.byte 0

SeafoamIslands_SecretCave_OnTransition:
	setvar VAR_TEMP_1, 1
	end

SeafoamIslands_SecretCave_EventScript_Archie::
	trainerbattle_single TRAINER_PRU_ARCHIE_KYOGRE_HNS, SeafoamIslands_SecretCave_Text_ArchieIntro, SeafoamIslands_SecretCave_Text_ArchieDefeated
	setflag FLAG_PRU_ARCHIE_KYOGRE_DEFEATED
	lockall
	msgbox SeafoamIslands_SecretCave_Text_ArchieAfter, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_PRU_ARCHIE
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

SeafoamIslands_SecretCave_EventScript_Kyogre::
	lock
	faceplayer
	goto_if_set FLAG_PRU_KYOGRE_CAUGHT, SeafoamIslands_SecretCave_EventScript_KyogreUnavailable
	goto_if_unset FLAG_PRU_ARCHIE_KYOGRE_DEFEATED, SeafoamIslands_SecretCave_EventScript_Archie
	setvar VAR_TEMP_1, 0
	playmoncry SPECIES_KYOGRE, CRY_MODE_ENCOUNTER
	waitmoncry
	@ Kyogre holds the Blue Orb and automatically becomes Primal on entry.
	@ Capture keeps base Kyogre plus the Orb for future Primal Reversion.
	seteventmon SPECIES_KYOGRE, 75, ITEM_BLUE_ORB
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SeafoamIslands_SecretCave_EventScript_KyogreCaught
	removeobject 1
	release
	end

SeafoamIslands_SecretCave_EventScript_KyogreUnavailable::
	setvar VAR_TEMP_1, 0
	release
	end

SeafoamIslands_SecretCave_EventScript_KyogreCaught::
	setflag FLAG_PRU_KYOGRE_CAUGHT
	removeobject 1
	release
	end

SeafoamIslands_SecretCave_Text_ArchieIntro:
	.string "ARCHIE: You made it this far?\p"
	.string "KYOGRE answered TEAM AQUA's call!\p"
	.string "You may beat the rest of my team,\p"
	.string "but can you survive KYOGRE?$"

SeafoamIslands_SecretCave_Text_ArchieDefeated:
	.string "ARCHIE: KYOGRE... no!$"

SeafoamIslands_SecretCave_Text_ArchieAfter:
	.string "ARCHIE: Even KYOGRE has fallen...\p"
	.string "It is free of my command now.\p"
	.string "It has retreated to the pool.\p"
	.string "Challenge it yourself, if you dare!$"
