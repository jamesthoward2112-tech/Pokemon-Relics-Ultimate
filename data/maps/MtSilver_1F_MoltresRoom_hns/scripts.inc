.set LOCALID_PRU_GROUDON, 1
.set LOCALID_PRU_MAXIE, 2

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
	playmoncry SPECIES_GROUDON_PRIMAL, CRY_MODE_ENCOUNTER
	waitmoncry
	@ Start in true Primal form: Desolate Land is active from turn one.
	@ The Red Orb is retained if caught, allowing normal battle reversion.
	seteventmon SPECIES_GROUDON_PRIMAL, 75, ITEM_RED_ORB
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtSilver_1F_MoltresRoom_EventScript_GroudonCaught
	removeobject LOCALID_PRU_GROUDON
	release
	end

MtSilver_1F_MoltresRoom_EventScript_GroudonCaught::
	setflag FLAG_PRU_GROUDON_CAUGHT
	removeobject LOCALID_PRU_GROUDON
	release
	end

MtSilver_1F_MoltresRoom_Text_MaxieIntro:
	.string "MAXIE: You trespass on sacred\\n"
	.string "ground! TEAM MAGMA will stop you!$"

MtSilver_1F_MoltresRoom_Text_MaxieDefeated:
	.string "MAXIE: Impossible...$"

MtSilver_1F_MoltresRoom_Text_MaxieAfter:
	.string "MAXIE: The molten heart of\\n"
	.string "GROUDON answers only to strength.$"
