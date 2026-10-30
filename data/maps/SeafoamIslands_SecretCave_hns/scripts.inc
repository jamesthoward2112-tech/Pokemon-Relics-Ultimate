
SeafoamIslands_SecretCave_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_SecretCave_OnTransition
	.byte 0

SeafoamIslands_SecretCave_OnTransition:
	goto_if_set FLAG_PRU_KYOGRE_CAUGHT, SeafoamIslands_SecretCave_OnTransition_HideKyogre
	goto_if_set FLAG_PRU_ARCHIE_KYOGRE_DEFEATED, SeafoamIslands_SecretCave_OnTransition_ShowKyogre
	goto SeafoamIslands_SecretCave_OnTransition_HideKyogre

SeafoamIslands_SecretCave_OnTransition_HideKyogre:
	setflag FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE
	end

SeafoamIslands_SecretCave_OnTransition_ShowKyogre:
	clearflag FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE
	end

SeafoamIslands_SecretCave_EventScript_Archie::
	@ Continue automatically after victory; the normal trainer battle would
	@ stop here and force the player to press A on Archie once more.
	trainerbattle_single TRAINER_PRU_ARCHIE_KYOGRE_HNS, SeafoamIslands_SecretCave_Text_ArchieIntro, SeafoamIslands_SecretCave_Text_ArchieDefeated, SeafoamIslands_SecretCave_EventScript_ArchieAfterBattle
	end

SeafoamIslands_SecretCave_EventScript_ArchieAfterBattle:
	setflag FLAG_PRU_ARCHIE_KYOGRE_DEFEATED
	lockall
	msgbox SeafoamIslands_SecretCave_Text_ArchieAfter, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE
	addobject LOCALID_PRU_KYOGRE
	playmoncry SPECIES_KYOGRE, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox SeafoamIslands_SecretCave_Text_ArchieReveal, MSGBOX_DEFAULT
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
	playmoncry SPECIES_KYOGRE, CRY_MODE_ENCOUNTER
	waitmoncry
	@ Shiny base Kyogre holds the Blue Orb, reverting to shiny Primal form.
	@ Only capture persists; knockout or whiteout allows the wild encounter again.
	setwildbattleshiny SPECIES_KYOGRE, 75
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SeafoamIslands_SecretCave_EventScript_KyogreCaught
	removeobject LOCALID_PRU_KYOGRE
	release
	end

SeafoamIslands_SecretCave_EventScript_KyogreUnavailable::
	release
	end

SeafoamIslands_SecretCave_EventScript_KyogreCaught::
	setflag FLAG_PRU_KYOGRE_CAUGHT
	setflag FLAG_PRU_HIDE_KYOGRE_BEFORE_ARCHIE
	removeobject LOCALID_PRU_KYOGRE
	release
	end

SeafoamIslands_SecretCave_Text_ArchieIntro:
	.string "ARCHIE: TEAM AQUA found an\p"
	.string "ancient RELIC beneath KANTO.\p"
	.string "It awakened a power beyond\n"
	.string "even our darkest dreams.\p"
	.string "Beat me to learn its secret!$"

SeafoamIslands_SecretCave_Text_ArchieDefeated:
	.string "ARCHIE: No! My final ace...$"

SeafoamIslands_SecretCave_Text_ArchieAfter:
	.string "ARCHIE: Even my ace has fallen...\p"
	.string "That RELIC was never mine\p"
	.string "to command. What have I done?$"

SeafoamIslands_SecretCave_Text_ArchieReveal:
	.string "ARCHIE: It's here... behind me!?\p"
	.string "No! I'm leaving! You face it!$"
