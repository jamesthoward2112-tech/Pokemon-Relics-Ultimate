
MtSilver_1F_MoltresRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_1F_MoltresRoom_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, MtSilver_1F_MoltresRoom_OnResume
	.byte 0

MtSilver_1F_MoltresRoom_OnResume::
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	end

MtSilver_1F_MoltresRoom_OnTransition:
	callnative SetTimeBasedEncounters
	goto_if_set FLAG_PRU_GROUDON_CAUGHT, MtSilver_1F_MoltresRoom_OnTransition_HideGroudon
	goto_if_set FLAG_PRU_MAXIE_GROUDON_DEFEATED, MtSilver_1F_MoltresRoom_OnTransition_ShowGroudon
	goto MtSilver_1F_MoltresRoom_OnTransition_HideGroudon

MtSilver_1F_MoltresRoom_OnTransition_HideGroudon:
	setflag FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE
	end

MtSilver_1F_MoltresRoom_OnTransition_ShowGroudon:
	clearflag FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE
	end

MtSilver_1F_MoltresRoom_EventScript_Maxie::
	@ Continue directly after victory without asking the player to press A.
	trainerbattle_single TRAINER_PRU_MAXIE_GROUDON_HNS, MtSilver_1F_MoltresRoom_Text_MaxieIntro, MtSilver_1F_MoltresRoom_Text_MaxieDefeated, MtSilver_1F_MoltresRoom_EventScript_MaxieAfterBattle
	end

MtSilver_1F_MoltresRoom_EventScript_MaxieAfterBattle:
	setflag FLAG_PRU_MAXIE_GROUDON_DEFEATED
	lockall
	msgbox MtSilver_1F_MoltresRoom_Text_MaxieAfter, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE
	addobject LOCALID_PRU_GROUDON
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox MtSilver_1F_MoltresRoom_Text_MaxieReveal, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_PRU_MAXIE
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

MtSilver_1F_MoltresRoom_EventScript_Groudon::
	lock
	faceplayer
	goto_if_set FLAG_PRU_GROUDON_CAUGHT, MtSilver_1F_MoltresRoom_EventScript_GroudonUnavailable
	goto_if_unset FLAG_PRU_MAXIE_GROUDON_DEFEATED, MtSilver_1F_MoltresRoom_EventScript_Maxie
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	waitmoncry
	@ Shiny base Groudon holds the Red Orb and reverts to shiny Primal form.
	@ Only capture persists; knockout or whiteout allows the wild encounter again.
	setwildbattleshiny SPECIES_GROUDON, 75, ITEM_RED_ORB
	special PruPreparePrimalLegendMoves
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtSilver_1F_MoltresRoom_EventScript_GroudonCaught
	removeobject LOCALID_PRU_GROUDON
	release
	end

MtSilver_1F_MoltresRoom_EventScript_GroudonUnavailable::
	release
	end

MtSilver_1F_MoltresRoom_EventScript_GroudonCaught::
	setflag FLAG_PRU_GROUDON_CAUGHT
	setflag FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE
	removeobject LOCALID_PRU_GROUDON
	release
	end

MtSilver_1F_MoltresRoom_Text_MaxieIntro:
	.string "MAXIE: TEAM MAGMA found an\p"
	.string "ancient RELIC in MT. SILVER.\p"
	.string "It awakened a power beyond\n"
	.string "even our darkest dreams.\p"
	.string "Beat me to learn its secret!$"

MtSilver_1F_MoltresRoom_Text_MaxieDefeated:
	.string "MAXIE: No! My final ace...$"

MtSilver_1F_MoltresRoom_Text_MaxieAfter:
	.string "MAXIE: Even my ace has fallen...\p"
	.string "That RELIC was never mine\p"
	.string "to command. What have I done?$"

MtSilver_1F_MoltresRoom_Text_MaxieReveal:
	.string "MAXIE: It's here... behind me!?\p"
	.string "No! I'm leaving! You face it!$"
