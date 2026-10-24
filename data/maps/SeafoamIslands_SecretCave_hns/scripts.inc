
SeafoamIslands_SecretCave_hns_MapScripts::
	.byte 0

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
	goto_if_unset FLAG_PRU_ARCHIE_KYOGRE_DEFEATED, SeafoamIslands_SecretCave_EventScript_Archie
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

SeafoamIslands_SecretCave_EventScript_KyogreCaught::
	setflag FLAG_PRU_KYOGRE_CAUGHT
	removeobject 1
	release
	end

SeafoamIslands_SecretCave_Text_ArchieIntro:
	.string "ARCHIE: Stop right there!\p"
	.string "KYOGRE's power belongs to the sea,\n"
	.string "not to the likes of you!\p"
	.string "If you want to reach it,\n"
	.string "you'll have to defeat me!$"

SeafoamIslands_SecretCave_Text_ArchieDefeated:
	.string "ARCHIE: My perfect plan...$"

SeafoamIslands_SecretCave_Text_ArchieAfter:
	.string "ARCHIE: Hah... You're strong.\p"
	.string "Even I cannot command this storm.\p"
	.string "Go on. KYOGRE is waiting.\p"
	.string "Let the sea judge your strength!$"
