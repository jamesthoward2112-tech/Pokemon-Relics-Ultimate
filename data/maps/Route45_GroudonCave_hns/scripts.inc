Route45_GroudonCave_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route45_GroudonCave_OnTransition
	.byte 0

Route45_GroudonCave_OnTransition::
	goto_if_set FLAG_PRU_GROUDON_CAUGHT, Route45_GroudonCave_HideGroudon
	goto_if_set FLAG_PRU_MAXIE_GROUDON_DEFEATED, Route45_GroudonCave_ShowGroudon
	goto Route45_GroudonCave_HideGroudon

Route45_GroudonCave_HideGroudon::
	setflag FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE
	end

Route45_GroudonCave_ShowGroudon::
	clearflag FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE
	end

Route45_GroudonCave_EventScript_Maxie::
	@ His shiny Primal Groudon is the final ace of a six-Pokémon team.
	trainerbattle_single TRAINER_PRU_MAXIE_GROUDON_HNS, Route45_GroudonCave_Text_MaxieIntro, Route45_GroudonCave_Text_MaxieDefeated, Route45_GroudonCave_EventScript_MaxieAfterBattle
	end

Route45_GroudonCave_EventScript_MaxieAfterBattle::
	setflag FLAG_PRU_MAXIE_GROUDON_DEFEATED
	lockall
	msgbox Route45_GroudonCave_Text_MaxieAfter, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE
	addobject LOCALID_PRU_GROUDON
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox Route45_GroudonCave_Text_MaxieReveal, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_PRU_MAXIE
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

Route45_GroudonCave_EventScript_Groudon::
	lock
	faceplayer
	goto_if_set FLAG_PRU_GROUDON_CAUGHT, Route45_GroudonCave_GroudonUnavailable
	goto_if_unset FLAG_PRU_MAXIE_GROUDON_DEFEATED, Route45_GroudonCave_EventScript_Maxie
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	waitmoncry
	@ The Red Orb reverts shiny base Groudon into its black Primal form.
	@ Only capture is permanent: a knockout or loss lets it return.
	setwildbattleshiny SPECIES_GROUDON, 75, ITEM_RED_ORB
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route45_GroudonCave_GroudonCaught
	removeobject LOCALID_PRU_GROUDON
	release
	end

Route45_GroudonCave_GroudonUnavailable::
	release
	end

Route45_GroudonCave_GroudonCaught::
	setflag FLAG_PRU_GROUDON_CAUGHT
	setflag FLAG_PRU_HIDE_GROUDON_BEFORE_MAXIE
	removeobject LOCALID_PRU_GROUDON
	release
	end

Route45_GroudonCave_Text_MaxieIntro:
	.string "MAXIE: Beneath JOHTO sleeps\p"
	.string "an ancient RELIC of the land.\p"
	.string "Its power cannot be claimed\n"
	.string "by the weak. Face TEAM MAGMA!$"

Route45_GroudonCave_Text_MaxieDefeated:
	.string "MAXIE: Even my final ace...$"

Route45_GroudonCave_Text_MaxieAfter:
	.string "MAXIE: The earth itself has\n"
	.string "rejected me. I was a fool...$"

Route45_GroudonCave_Text_MaxieReveal:
	.string "MAXIE: GROUDON is behind me!\p"
	.string "It is yours to face now.\n"
	.string "I must leave this place!$"
