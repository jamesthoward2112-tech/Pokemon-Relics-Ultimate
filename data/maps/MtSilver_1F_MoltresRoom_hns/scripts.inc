
MtSilver_1F_MoltresRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_1F_MoltresRoom_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, MtSilver_1F_MoltresRoom_OnResume
	.byte 0

MtSilver_1F_MoltresRoom_OnResume::
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	end

MtSilver_1F_MoltresRoom_OnTransition:
	callnative SetTimeBasedEncounters
	end

MtSilver_1F_MoltresRoom_EventScript_Maxie::
	trainerbattle_single TRAINER_PRU_MAXIE_GROUDON_HNS, MtSilver_1F_MoltresRoom_Text_MaxieIntro, MtSilver_1F_MoltresRoom_Text_MaxieDefeated
	setflag FLAG_PRU_MAXIE_GROUDON_DEFEATED
	msgbox MtSilver_1F_MoltresRoom_Text_MaxieAfter, MSGBOX_DEFAULT
	end

MtSilver_1F_MoltresRoom_EventScript_Groudon::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_MAXIE_GROUDON_DEFEATED, MtSilver_1F_MoltresRoom_EventScript_Maxie
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	waitmoncry
	@ Groudon holds the Red Orb and automatically becomes Primal on entry.
	@ Capture keeps base Groudon plus the Orb for future Primal Reversion.
	seteventmon SPECIES_GROUDON, 75, ITEM_RED_ORB
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtSilver_1F_MoltresRoom_EventScript_GroudonCaught
	removeobject 1
	release
	end

MtSilver_1F_MoltresRoom_EventScript_GroudonCaught::
	setflag FLAG_PRU_GROUDON_CAUGHT
	removeobject 1
	release
	end

MtSilver_1F_MoltresRoom_Text_MaxieIntro:
	.string "MAXIE: You trespass on sacred\n"
	.string "ground! TEAM MAGMA will stop you!$"

MtSilver_1F_MoltresRoom_Text_MaxieDefeated:
	.string "MAXIE: Impossible...$"

MtSilver_1F_MoltresRoom_Text_MaxieAfter:
	.string "MAXIE: The molten heart of\n"
	.string "GROUDON answers only to strength.$"
