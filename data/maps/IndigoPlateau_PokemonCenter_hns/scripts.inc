
@ Indigo Plateau's existing clerk now stocks competitive held items.
@ Keep the nine tutor NPCs, the normal healing service, and map layout unchanged.
PRU_IndigoPlateau_HeldItemsClerk::
	lock
	faceplayer
	message PRU_IndigoPlateau_Text_HeldItemsIntro
	waitmessage
	pokemart PRU_IndigoPlateau_HeldItemMart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PRU_IndigoPlateau_HeldItemMart:
	.2byte ITEM_WEAKNESS_POLICY
	.2byte ITEM_THROAT_SPRAY
	.2byte ITEM_CHOICE_BAND
	.2byte ITEM_CHOICE_SPECS
	.2byte ITEM_CHOICE_SCARF
	.2byte ITEM_LIFE_ORB
	.2byte ITEM_FOCUS_SASH
	.2byte ITEM_ASSAULT_VEST
	.2byte ITEM_HEAVY_DUTY_BOOTS
	.2byte ITEM_EJECT_BUTTON
	.2byte ITEM_EJECT_PACK
	.2byte ITEM_LIGHT_CLAY
	.2byte ITEM_EXPERT_BELT
	.2byte ITEM_SAFETY_GOGGLES
	.2byte ITEM_BLUNDER_POLICY
	.2byte ITEM_AIR_BALLOON
	.2byte ITEM_ROCKY_HELMET
	.2byte ITEM_LEFTOVERS
	pokemartlistend

PRU_IndigoPlateau_Text_HeldItemsIntro:
	.string "Welcome to the INDIGO LEAGUE\n"
	.string "competitive held-item shop!$"

IndigoPlateau_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, IndigoPlateau_PokemonCenter_OnFrame 
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_Pokecenter_OnTransition
	.byte 0

IndigoPlateau_PokemonCenter_OnFrame::
	map_script_2 VAR_LEAGUE_STATE, 0, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 2, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 3, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 4, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 5, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 6, IndigoPlateau_PokemonCenter_Enter
	.2byte 0

IndigoPlateau_PokemonCenter_Enter::
	setflag FLAG_VISITED_INDIGO_PLATEAU
	setvar VAR_LEAGUE_STATE, 1
	end

IndigoPlateau_Pokecenter_OnTransition::
	setrespawn HEAL_LOCATION_INDIGO_PLATEAU_HNS
	goto_if_set FLAG_PRU_KANTO_LEAGUE_CLEARED, PRU_LeagueEntrance_ShowGuard
	goto_if_unset FLAG_PRU_HEIST_COMPLETED, PRU_LeagueEntrance_KeepOldGuard
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, PRU_LeagueEntrance_KeepOldGuard
	setflag FLAG_HIDE_LEAGUE_BLACKBELT
	@ A completed badge heist implies a late Kanto save. Do not make
	@ returning players face Silver's old daily encounter again.
	setflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
	end

PRU_LeagueEntrance_ShowGuard::
	clearflag FLAG_HIDE_LEAGUE_BLACKBELT
	@ Retire Silver in existing post-League saves as well as new playthroughs.
	setflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
	end

PRU_LeagueEntrance_KeepOldGuard::
	end

PRU_LeagueEntrance_Seal::
	goto_if_unset FLAG_PRU_KANTO_LEAGUE_CLEARED, PRU_LeagueEntrance_Unsealed
	lock
	msgbox PRU_LeagueEntrance_Text_Closed, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0
	release
	end

PRU_LeagueEntrance_Unsealed::
	@ The original HNS door at (32,2) reliably enters Will's room.
	@ Do not warp across the FRLG map-group here: that transition froze
	@ Pizza Boy on a black screen during the second championship.
	end

PRU_LeagueEntrance_Text_Closed::
	.string "The KANTO LEAGUE is over.\n"
	.string "These doors are now sealed!\p"
	.string "The ELITE 20 awaits you at\n"
	.string "SAFFRON'S FIGHTING DOJO.$"


IndigoPlateau_EventScript_Cooltrainer::
	goto IndigoPlateau_EventScript_HazardTutor
	end

IndigoPlateau_EventScript_BlackBelt::
	goto_if_set FLAG_PRU_KANTO_LEAGUE_CLEARED, PRU_LeagueEntrance_GuardClosed
	msgbox IndigoPlateau_Text_Blackbelt, MSGBOX_NPC
	end

PRU_LeagueEntrance_GuardClosed::
	msgbox PRU_LeagueEntrance_Text_Closed, MSGBOX_NPC
	end

IndigoPlateau_EventScript_ShigyNinja::
	goto IndigoPlateau_EventScript_CleanupTutor
	end

IndigoPlateau_Text_ShigyNinja:
	.string "Congrats on making it here!\p"
	.string "I've seen tons of trainers come\n"
	.string "through here over the years, and\l"
	.string "all of them are wonderfully unique.\p"
	.string "You should be proud of yourself\n"
	.string "for getting this far!\p"
	.string "Now, go get 'em!$"

IndigoPlateau_Text_Blackbelt:
	.string "The POKéMON LEAGUE is not taking\n"
	.string "new challengers at the moment.\p"
	.string "Please check back later.$"

IndigoPlateau_Text_CooltrainerM:
    .string "At the POKéMON LEAGUE, you'll get\n"
    .string "tested by the ELITE FOUR.\p"
    .string "You have to beat them all. If you\n"
    .string "lose, you have to start all over!$"

IndigoPlateau_EventScript_Silver::
	lock
	faceplayer 
	goto_if_set FLAG_HIDE_INDIGO_PLATEAU_SILVER, IndigoPlateau_EventScript_SilverBeat
	goto_if_set FLAG_DAILY_BEAT_SILVER, IndigoPlateau_EventScript_SilverBeat
	msgbox IndigoPlateau_Text_RivalEntrance1, MSGBOX_DEFAULT
	call_if_eq VAR_STARTER_MON, 0, IndigoPlateau_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, IndigoPlateau_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, IndigoPlateau_Silver_Battle_Chikorita
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	setflag FLAG_DAILY_BEAT_SILVER
	@ One Indigo battle only; no more daily rematches.
	setflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
	release
	end

IndigoPlateau_EventScript_SilverBeat::
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

IndigoPlateau_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_7_HNS, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_7_HNS, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_7_HNS, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Text_RivalEntrance1:
    .string "Hold it.\p"
    .string "You're going to take the POKéMON\n"
    .string "LEAGUE challenge now?\p"
    .string "That's not going to happen.\p"
    .string "My super-well-trained POKéMON\n"
    .string "are going to pound you.\p"
    .string "{PLAYER}!\n"
    .string "I challenge you!$"

IndigoPlateau_Text_RivalWin:
    .string "…\p"
    .string "OK--I lost…$"

IndigoPlateau_Text_RivalAfter:
    .string "…Darn… I still can't win…\p"
    .string "I… I have to think more about my\n"
    .string "POKéMON…\p"
    .string "Humph! Try not to lose!$"

IndigoPlateau_EventScript_Psychic::
	lock
	faceplayer
	msgbox IndigoPlateau_Text_TeleportGuy1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, IndigoPlateau_EventScript_PsychicTeleport
	msgbox IndigoPlateau_Text_TeleportGuyNo, MSGBOX_DEFAULT
	closemessage
	release
	end

IndigoPlateau_EventScript_PsychicTeleport::
	msgbox IndigoPlateau_Text_TeleportGuyYes, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playbgm MUS_HG_NEW_BARK, FALSE
	delay 60
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	applymovement2 LOCALID_INDIGOPLATEAU_ABRA, IndigoPLateau_Movement_Abra
	waitmovement 0
	fadescreen FADE_TO_WHITE
	warpteleport MAP_NEW_BARK_TOWN_HNS, 20, 12
	waitstate
	release
	end
	
IndigoPLateau_Movement_Abra:
	jump_in_place_right
	jump_in_place_right
	step_end

IndigoPlateau_EventScript_Abra::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	msgbox IndigoPlateau_Text_Abra, MSGBOX_DEFAULT
	waitmoncry
	release
	end

IndigoPlateau_Text_TeleportGuy1:
    .string "Ah! You're challenging the ELITE\n"
    .string "FOUR? Are you sure you're ready?\p"
    .string "If you need to train some more,\n"
    .string "my ABRA can help you.\p"
    .string "It can TELEPORT you home.\p"
    .string "Would you like to go home now?$"

IndigoPlateau_Text_TeleportGuyYes:
    .string "OK, OK. Picture your house in your\n"
    .string "mind…$"

IndigoPlateau_Text_TeleportGuyNo:
    .string "OK, OK. The best of luck to you!$"

IndigoPlateau_Text_Abra:
    .string "ABRA: Aabra…$"


@ PJR tactical move tutors: free, repeatable, and deliberately placed in Indigo Plateau.
IndigoPlateau_EventScript_HazardTutor::
	lock
	faceplayer
	msgbox IndigoPlateau_Text_HazardTutorIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, IndigoPlateau_EventScript_TutorDecline
	message IndigoPlateau_Text_HazardTutorChoose
	waitmessage
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, IndigoPlateau_Text_TutorMove_StealthRock, IndigoPlateau_Text_TutorMove_Spikes, IndigoPlateau_Text_TutorMove_ToxicSpikes, IndigoPlateau_Text_TutorMove_StickyWeb, IndigoPlateau_Text_TutorMove_StoneAxe, IndigoPlateau_Text_TutorMove_CeaselessEdge, IndigoPlateau_Text_TutorMove_SaltCure, IndigoPlateau_Text_TutorMove_LeechSeed, IndigoPlateau_Text_TutorMove_Toxic, IndigoPlateau_Text_TutorMove_WillOWisp, IndigoPlateau_Text_TutorMove_ThunderWave, IndigoPlateau_Text_TutorMove_Taunt, IndigoPlateau_Text_TutorMove_Encore, IndigoPlateau_Text_TutorMove_KnockOff, IndigoPlateau_Text_TutorMove_Roar, IndigoPlateau_Text_TutorMove_Whirlwind, IndigoPlateau_Text_TutorMove_DragonTail, IndigoPlateau_Text_TutorMove_Infestation, IndigoPlateau_Text_TutorMove_AchillesHeel, IndigoPlateau_Text_TutorMove_Permafrost, IndigoPlateau_Text_TutorMove_Wildfire, IndigoPlateau_Text_TutorMove_DarkMatter, IndigoPlateau_Text_TutorMove_Cancel
	switch VAR_RESULT
	case 0, IndigoPlateau_EventScript_TutorTeach_StealthRock
	case 1, IndigoPlateau_EventScript_TutorTeach_Spikes
	case 2, IndigoPlateau_EventScript_TutorTeach_ToxicSpikes
	case 3, IndigoPlateau_EventScript_TutorTeach_StickyWeb
	case 4, IndigoPlateau_EventScript_TutorTeach_StoneAxe
	case 5, IndigoPlateau_EventScript_TutorTeach_CeaselessEdge
	case 6, IndigoPlateau_EventScript_TutorTeach_SaltCure
	case 7, IndigoPlateau_EventScript_TutorTeach_LeechSeed
	case 8, IndigoPlateau_EventScript_TutorTeach_Toxic
	case 9, IndigoPlateau_EventScript_TutorTeach_WillOWisp
	case 10, IndigoPlateau_EventScript_TutorTeach_ThunderWave
	case 11, IndigoPlateau_EventScript_TutorTeach_Taunt
	case 12, IndigoPlateau_EventScript_TutorTeach_Encore
	case 13, IndigoPlateau_EventScript_TutorTeach_KnockOff
	case 14, IndigoPlateau_EventScript_TutorTeach_Roar
	case 15, IndigoPlateau_EventScript_TutorTeach_Whirlwind
	case 16, IndigoPlateau_EventScript_TutorTeach_DragonTail
	case 17, IndigoPlateau_EventScript_TutorTeach_Infestation
	case 18, IndigoPlateau_EventScript_TutorTeach_AchillesHeel
	case 19, IndigoPlateau_EventScript_TutorTeach_Permafrost
	case 20, IndigoPlateau_EventScript_TutorTeach_Wildfire
	case 21, IndigoPlateau_EventScript_TutorTeach_DarkMatter
	case 22, IndigoPlateau_EventScript_TutorDecline
	case MULTI_B_PRESSED, IndigoPlateau_EventScript_TutorDecline
	end

IndigoPlateau_EventScript_CleanupTutor::
	lock
	faceplayer
	msgbox IndigoPlateau_Text_CleanupTutorIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, IndigoPlateau_EventScript_TutorDecline
	message IndigoPlateau_Text_CleanupTutorChoose
	waitmessage
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, IndigoPlateau_Text_TutorMove_RapidSpin, IndigoPlateau_Text_TutorMove_Defog, IndigoPlateau_Text_TutorMove_MortalSpin, IndigoPlateau_Text_TutorMove_TidyUp, IndigoPlateau_Text_TutorMove_CourtChange, IndigoPlateau_Text_TutorMove_Haze, IndigoPlateau_Text_TutorMove_ClearSmog, IndigoPlateau_Text_TutorMove_BrickBreak, IndigoPlateau_Text_TutorMove_PsychicFangs, IndigoPlateau_Text_TutorMove_IceSpinner, IndigoPlateau_Text_TutorMove_HealBell, IndigoPlateau_Text_TutorMove_Aromatherapy, IndigoPlateau_Text_TutorMove_UTurn, IndigoPlateau_Text_TutorMove_VoltSwitch, IndigoPlateau_Text_TutorMove_FlipTurn, IndigoPlateau_Text_TutorMove_PartingShot, IndigoPlateau_Text_TutorMove_Snarl, IndigoPlateau_Text_TutorMove_IcyWind, IndigoPlateau_Text_TutorMove_BreakingSwipe, IndigoPlateau_Text_TutorMove_ChillingWater, IndigoPlateau_Text_TutorMove_AcidSpray, IndigoPlateau_Text_TutorMove_Nuzzle, IndigoPlateau_Text_TutorMove_Cancel
	switch VAR_RESULT
	case 0, IndigoPlateau_EventScript_TutorTeach_RapidSpin
	case 1, IndigoPlateau_EventScript_TutorTeach_Defog
	case 2, IndigoPlateau_EventScript_TutorTeach_MortalSpin
	case 3, IndigoPlateau_EventScript_TutorTeach_TidyUp
	case 4, IndigoPlateau_EventScript_TutorTeach_CourtChange
	case 5, IndigoPlateau_EventScript_TutorTeach_Haze
	case 6, IndigoPlateau_EventScript_TutorTeach_ClearSmog
	case 7, IndigoPlateau_EventScript_TutorTeach_BrickBreak
	case 8, IndigoPlateau_EventScript_TutorTeach_PsychicFangs
	case 9, IndigoPlateau_EventScript_TutorTeach_IceSpinner
	case 10, IndigoPlateau_EventScript_TutorTeach_HealBell
	case 11, IndigoPlateau_EventScript_TutorTeach_Aromatherapy
	case 12, IndigoPlateau_EventScript_TutorTeach_UTurn
	case 13, IndigoPlateau_EventScript_TutorTeach_VoltSwitch
	case 14, IndigoPlateau_EventScript_TutorTeach_FlipTurn
	case 15, IndigoPlateau_EventScript_TutorTeach_PartingShot
	case 16, IndigoPlateau_EventScript_TutorTeach_Snarl
	case 17, IndigoPlateau_EventScript_TutorTeach_IcyWind
	case 18, IndigoPlateau_EventScript_TutorTeach_BreakingSwipe
	case 19, IndigoPlateau_EventScript_TutorTeach_ChillingWater
	case 20, IndigoPlateau_EventScript_TutorTeach_AcidSpray
	case 21, IndigoPlateau_EventScript_TutorTeach_Nuzzle
	case 22, IndigoPlateau_EventScript_TutorDecline
	case MULTI_B_PRESSED, IndigoPlateau_EventScript_TutorDecline
	end

IndigoPlateau_EventScript_TutorTeach_StealthRock::
	setvar VAR_0x8005, MOVE_STEALTH_ROCK
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Spikes::
	setvar VAR_0x8005, MOVE_SPIKES
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_ToxicSpikes::
	setvar VAR_0x8005, MOVE_TOXIC_SPIKES
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_StickyWeb::
	setvar VAR_0x8005, MOVE_STICKY_WEB
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_StoneAxe::
	setvar VAR_0x8005, MOVE_STONE_AXE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_CeaselessEdge::
	setvar VAR_0x8005, MOVE_CEASELESS_EDGE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_SaltCure::
	setvar VAR_0x8005, MOVE_SALT_CURE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_LeechSeed::
	setvar VAR_0x8005, MOVE_LEECH_SEED
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Toxic::
	setvar VAR_0x8005, MOVE_TOXIC
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_WillOWisp::
	setvar VAR_0x8005, MOVE_WILL_O_WISP
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_ThunderWave::
	setvar VAR_0x8005, MOVE_THUNDER_WAVE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Taunt::
	setvar VAR_0x8005, MOVE_TAUNT
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Encore::
	setvar VAR_0x8005, MOVE_ENCORE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_KnockOff::
	setvar VAR_0x8005, MOVE_KNOCK_OFF
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Roar::
	setvar VAR_0x8005, MOVE_ROAR
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Whirlwind::
	setvar VAR_0x8005, MOVE_WHIRLWIND
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_DragonTail::
	setvar VAR_0x8005, MOVE_DRAGON_TAIL
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Infestation::
	setvar VAR_0x8005, MOVE_INFESTATION
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_AchillesHeel::
	setvar VAR_0x8005, MOVE_ACHILLES_HEEL
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Permafrost::
	setvar VAR_0x8005, MOVE_PERMAFROST
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Wildfire::
	setvar VAR_0x8005, MOVE_WILDFIRE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_DarkMatter::
	setvar VAR_0x8005, MOVE_DARK_MATTER
	goto IndigoPlateau_EventScript_TutorTeachMove
	end

IndigoPlateau_EventScript_TutorTeach_RapidSpin::
	setvar VAR_0x8005, MOVE_RAPID_SPIN
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Defog::
	setvar VAR_0x8005, MOVE_DEFOG
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_MortalSpin::
	setvar VAR_0x8005, MOVE_MORTAL_SPIN
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_TidyUp::
	setvar VAR_0x8005, MOVE_TIDY_UP
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_CourtChange::
	setvar VAR_0x8005, MOVE_COURT_CHANGE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Haze::
	setvar VAR_0x8005, MOVE_HAZE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_ClearSmog::
	setvar VAR_0x8005, MOVE_CLEAR_SMOG
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_BrickBreak::
	setvar VAR_0x8005, MOVE_BRICK_BREAK
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_PsychicFangs::
	setvar VAR_0x8005, MOVE_PSYCHIC_FANGS
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_IceSpinner::
	setvar VAR_0x8005, MOVE_ICE_SPINNER
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_HealBell::
	setvar VAR_0x8005, MOVE_HEAL_BELL
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Aromatherapy::
	setvar VAR_0x8005, MOVE_AROMATHERAPY
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_UTurn::
	setvar VAR_0x8005, MOVE_U_TURN
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_VoltSwitch::
	setvar VAR_0x8005, MOVE_VOLT_SWITCH
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_FlipTurn::
	setvar VAR_0x8005, MOVE_FLIP_TURN
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_PartingShot::
	setvar VAR_0x8005, MOVE_PARTING_SHOT
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Snarl::
	setvar VAR_0x8005, MOVE_SNARL
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_IcyWind::
	setvar VAR_0x8005, MOVE_ICY_WIND
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_BreakingSwipe::
	setvar VAR_0x8005, MOVE_BREAKING_SWIPE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_ChillingWater::
	setvar VAR_0x8005, MOVE_CHILLING_WATER
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_AcidSpray::
	setvar VAR_0x8005, MOVE_ACID_SPRAY
	goto IndigoPlateau_EventScript_TutorTeachMove
	end
IndigoPlateau_EventScript_TutorTeach_Nuzzle::
	setvar VAR_0x8005, MOVE_NUZZLE
	goto IndigoPlateau_EventScript_TutorTeachMove
	end

IndigoPlateau_EventScript_TutorTeachMove::
	buffermovename STR_VAR_1, VAR_0x8005
	msgbox IndigoPlateau_Text_TutorConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, IndigoPlateau_EventScript_TutorDecline
	msgbox IndigoPlateau_Text_TutorWhichMon, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	chooseboxmon SELECT_PC_MON_PJR_CONTROL_TUTOR
	waitstate
	goto_if_eq VAR_RESULT, FALSE, IndigoPlateau_EventScript_TutorCancelled
	msgbox IndigoPlateau_Text_TutorDone, MSGBOX_DEFAULT
	release
	end

IndigoPlateau_EventScript_TutorCancelled::
	msgbox IndigoPlateau_Text_TutorComeBack, MSGBOX_DEFAULT
	release
	end

IndigoPlateau_EventScript_TutorDecline::
	msgbox IndigoPlateau_Text_TutorComeBack, MSGBOX_DEFAULT
	release
	end

IndigoPlateau_Text_HazardTutorIntro:
	.string "I teach free battlefield HAZARDS,\n"
	.string "traps and control. Want my help?$"

IndigoPlateau_Text_HazardTutorChoose:
	.string "Which control move do you want?$"

IndigoPlateau_Text_CleanupTutorIntro:
	.string "I teach free CLEANUP moves to\n"
	.string "clear hazards. Want my help?$"

IndigoPlateau_Text_CleanupTutorChoose:
	.string "Which cleanup move do you want?$"

IndigoPlateau_Text_TutorConfirm:
	.string "Teach {STR_VAR_1}?$"

IndigoPlateau_Text_TutorWhichMon:
	.string "Which POKEMON should learn it?$"

IndigoPlateau_Text_TutorDone:
	.string "Done. Use it well.$"

IndigoPlateau_Text_TutorComeBack:
	.string "No problem. Come back anytime.$"

IndigoPlateau_Text_TutorMove_StealthRock:
	.string "STEALTH ROCK$"
IndigoPlateau_Text_TutorMove_Spikes:
	.string "SPIKES$"
IndigoPlateau_Text_TutorMove_ToxicSpikes:
	.string "TOXIC SPIKES$"
IndigoPlateau_Text_TutorMove_StickyWeb:
	.string "STICKY WEB$"
IndigoPlateau_Text_TutorMove_StoneAxe:
	.string "STONE AXE$"
IndigoPlateau_Text_TutorMove_CeaselessEdge:
	.string "CEASELESS EDGE$"
IndigoPlateau_Text_TutorMove_SaltCure:
	.string "SALT CURE$"
IndigoPlateau_Text_TutorMove_LeechSeed:
	.string "LEECH SEED$"
IndigoPlateau_Text_TutorMove_Toxic:
	.string "TOXIC$"
IndigoPlateau_Text_TutorMove_WillOWisp:
	.string "WILL-O-WISP$"
IndigoPlateau_Text_TutorMove_ThunderWave:
	.string "THUNDER WAVE$"
IndigoPlateau_Text_TutorMove_Taunt:
	.string "TAUNT$"
IndigoPlateau_Text_TutorMove_Encore:
	.string "ENCORE$"
IndigoPlateau_Text_TutorMove_KnockOff:
	.string "KNOCK OFF$"
IndigoPlateau_Text_TutorMove_Roar:
	.string "ROAR$"
IndigoPlateau_Text_TutorMove_Whirlwind:
	.string "WHIRLWIND$"
IndigoPlateau_Text_TutorMove_DragonTail:
	.string "DRAGON TAIL$"
IndigoPlateau_Text_TutorMove_Infestation:
	.string "INFESTATION$"
IndigoPlateau_Text_TutorMove_AchillesHeel:
	.string "ACHILLES HEEL$"
IndigoPlateau_Text_TutorMove_Permafrost:
	.string "PERMAFROST$"
IndigoPlateau_Text_TutorMove_Wildfire:
	.string "WILDFIRE$"
IndigoPlateau_Text_TutorMove_DarkMatter:
	.string "DARK MATTER$"
IndigoPlateau_Text_TutorMove_RapidSpin:
	.string "RAPID SPIN$"
IndigoPlateau_Text_TutorMove_Defog:
	.string "DEFOG$"
IndigoPlateau_Text_TutorMove_MortalSpin:
	.string "MORTAL SPIN$"
IndigoPlateau_Text_TutorMove_TidyUp:
	.string "TIDY UP$"
IndigoPlateau_Text_TutorMove_CourtChange:
	.string "COURT CHANGE$"
IndigoPlateau_Text_TutorMove_Haze:
	.string "HAZE$"
IndigoPlateau_Text_TutorMove_ClearSmog:
	.string "CLEAR SMOG$"
IndigoPlateau_Text_TutorMove_BrickBreak:
	.string "BRICK BREAK$"
IndigoPlateau_Text_TutorMove_PsychicFangs:
	.string "PSYCHIC FANGS$"
IndigoPlateau_Text_TutorMove_IceSpinner:
	.string "ICE SPINNER$"
IndigoPlateau_Text_TutorMove_HealBell:
	.string "HEAL BELL$"
IndigoPlateau_Text_TutorMove_Aromatherapy:
	.string "AROMATHERAPY$"
IndigoPlateau_Text_TutorMove_UTurn:
	.string "U-TURN$"
IndigoPlateau_Text_TutorMove_VoltSwitch:
	.string "VOLT SWITCH$"
IndigoPlateau_Text_TutorMove_FlipTurn:
	.string "FLIP TURN$"
IndigoPlateau_Text_TutorMove_PartingShot:
	.string "PARTING SHOT$"
IndigoPlateau_Text_TutorMove_Snarl:
	.string "SNARL$"
IndigoPlateau_Text_TutorMove_IcyWind:
	.string "ICY WIND$"
IndigoPlateau_Text_TutorMove_BreakingSwipe:
	.string "BREAKING SWIPE$"
IndigoPlateau_Text_TutorMove_ChillingWater:
	.string "CHILLING WATER$"
IndigoPlateau_Text_TutorMove_AcidSpray:
	.string "ACID SPRAY$"
IndigoPlateau_Text_TutorMove_Nuzzle:
	.string "NUZZLE$"
IndigoPlateau_Text_TutorMove_Cancel:
	.string "CANCEL$"

@ Nine individual specialists stand side-by-side along the lower-left wall.
@ The early Daycare relearner is unchanged; these are additional services.
PRU_TrainingHub_Relearner::
	lockall
	faceplayer
	msgbox PRU_TrainingHub_Text_RelearnerIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PRU_TrainingHub_Exit
	setmoverelearnerstate MOVE_RELEARNER_LEVEL_UP_MOVES
	bufferstring STR_VAR_3, MoveRelearner_Text_LevelUpMoveLWR
	goto PRU_TrainingHub_RelearnerTeach

PRU_TrainingHub_EggTutor::
	lockall
	faceplayer
	msgbox PRU_TrainingHub_Text_EggTutorIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PRU_TrainingHub_Exit
	setmoverelearnerstate MOVE_RELEARNER_EGG_MOVES
	bufferstring STR_VAR_3, MoveRelearner_Text_EggMoveLWR
	goto PRU_TrainingHub_RelearnerTeach

PRU_TrainingHub_RelearnerTeach::
	getpartysize
	goto_if_eq VAR_RESULT, 0, PRU_TrainingHub_RelearnerNoMon
	msgbox MoveRelearner_Text_ChoosePkmn, MSGBOX_DEFAULT
	chooseboxmon SELECT_PC_MON_MOVE_RELEARNER
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, PRU_TrainingHub_Exit
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, PRU_TrainingHub_RelearnerNoMoves
	special HasMovesToRelearn
	goto_if_eq VAR_RESULT, FALSE, PRU_TrainingHub_RelearnerNoMoves
	msgbox MoveRelearner_Text_WhichXmoveShouldTeach, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto PRU_TrainingHub_Exit

PRU_TrainingHub_RelearnerNoMon::
	msgbox MoveRelearner_Text_HaveNoPkmn, MSGBOX_DEFAULT
	goto PRU_TrainingHub_Exit

PRU_TrainingHub_RelearnerNoMoves::
	msgbox MoveRelearner_Text_CantTeachMoveToPkmn, MSGBOX_DEFAULT
	goto PRU_TrainingHub_Exit

PRU_TrainingHub_Text_RelearnerIntro:
	.string "I restore forgotten LEVEL-UP\n"
	.string "moves for free. Want my help?$"

PRU_TrainingHub_Text_EggTutorIntro:
	.string "I teach inherited EGG MOVES\n"
	.string "for free. Want my help?$"

PRU_SetupTutor::
	lock
	faceplayer
	msgbox PRU_SetupTutor_Text_Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, IndigoPlateau_EventScript_TutorDecline
	message PRU_SetupTutor_Text_Choose
	waitmessage
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, PRU_SetupTutor_Text_SwordsDance, PRU_SetupTutor_Text_NastyPlot, PRU_SetupTutor_Text_DragonDance, PRU_SetupTutor_Text_CalmMind, PRU_SetupTutor_Text_BulkUp, PRU_SetupTutor_Text_Agility, PRU_SetupTutor_Text_Protect, IndigoPlateau_Text_TutorMove_Cancel
	switch VAR_RESULT
	case 0, PRU_SetupTutor_SwordsDance
	case 1, PRU_SetupTutor_NastyPlot
	case 2, PRU_SetupTutor_DragonDance
	case 3, PRU_SetupTutor_CalmMind
	case 4, PRU_SetupTutor_BulkUp
	case 5, PRU_SetupTutor_Agility
	case 6, PRU_SetupTutor_Protect
	case 7, IndigoPlateau_EventScript_TutorDecline
	case MULTI_B_PRESSED, IndigoPlateau_EventScript_TutorDecline
	end
PRU_SetupTutor_SwordsDance::
	setvar VAR_0x8005, MOVE_SWORDS_DANCE
	goto IndigoPlateau_EventScript_TutorTeachMove
PRU_SetupTutor_NastyPlot::
	setvar VAR_0x8005, MOVE_NASTY_PLOT
	goto IndigoPlateau_EventScript_TutorTeachMove
PRU_SetupTutor_DragonDance::
	setvar VAR_0x8005, MOVE_DRAGON_DANCE
	goto IndigoPlateau_EventScript_TutorTeachMove
PRU_SetupTutor_CalmMind::
	setvar VAR_0x8005, MOVE_CALM_MIND
	goto IndigoPlateau_EventScript_TutorTeachMove
PRU_SetupTutor_BulkUp::
	setvar VAR_0x8005, MOVE_BULK_UP
	goto IndigoPlateau_EventScript_TutorTeachMove
PRU_SetupTutor_Agility::
	setvar VAR_0x8005, MOVE_AGILITY
	goto IndigoPlateau_EventScript_TutorTeachMove
PRU_SetupTutor_Protect::
	setvar VAR_0x8005, MOVE_PROTECT
	goto IndigoPlateau_EventScript_TutorTeachMove

PRU_SetupTutor_Text_Intro:
	.string "I teach free SETUP moves.\nWant me to train your team?$"
PRU_SetupTutor_Text_Choose:
	.string "Which setup move do you want?$"
PRU_SetupTutor_Text_SwordsDance:
	.string "SWORDS DANCE$"
PRU_SetupTutor_Text_NastyPlot:
	.string "NASTY PLOT$"
PRU_SetupTutor_Text_DragonDance:
	.string "DRAGON DANCE$"
PRU_SetupTutor_Text_CalmMind:
	.string "CALM MIND$"
PRU_SetupTutor_Text_BulkUp:
	.string "BULK UP$"
PRU_SetupTutor_Text_Agility:
	.string "AGILITY$"
PRU_SetupTutor_Text_Protect:
	.string "PROTECT$"

PRU_TrainingHub_MoveDeleter::
	lockall
	faceplayer
	msgbox PRU_TrainingHub_Text_DeleterIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PRU_TrainingHub_Exit
	goto_if_eq VAR_RESULT, YES, BlackthornCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	goto BlackthornCity_MoveDeletersHouse_EventScript_ComeAgain

PRU_TrainingHub_Text_DeleterIntro:
	.string "I delete unwanted moves for\n"
	.string "free. Want me to remove one?$"

PRU_TrainingHub_AbilityNature::
	lockall
	faceplayer
	msgbox PRU_TrainingHub_Text_AbilityNature, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PRU_TrainingHub_Exit
	message PRU_TrainingHub_Text_AbilityNatureChoose
	waitmessage
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, PRU_TrainingHub_Text_Ability, PRU_TrainingHub_Text_Nature, PRU_TrainingHub_Text_Cancel
	switch VAR_RESULT
	case 0, PRU_TrainingHub_Ability
	case 1, PRU_TrainingHub_Nature
	case 2, PRU_TrainingHub_Exit
	case MULTI_B_PRESSED, PRU_TrainingHub_Exit
	end
PRU_TrainingHub_Ability::
	msgbox PRU_TrainingHub_Text_ChooseMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, PRU_TrainingHub_Exit
	special SwitchMonAbility
	goto_if_eq VAR_RESULT, FALSE, PRU_TrainingHub_AbilityFailed
	msgbox PRU_TrainingHub_Text_AbilityDone, MSGBOX_DEFAULT
	goto PRU_TrainingHub_Exit
PRU_TrainingHub_AbilityFailed::
	msgbox PRU_TrainingHub_Text_AbilityFailed, MSGBOX_DEFAULT
	goto PRU_TrainingHub_Exit
PRU_TrainingHub_Nature::
	msgbox PRU_TrainingHub_Text_ChooseMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, PRU_TrainingHub_Exit
	dynmultipush Debug_EventScript_ChangeNature_Text_Hardy, 0
	dynmultipush Debug_EventScript_ChangeNature_Text_Lonely, 1
	dynmultipush Debug_EventScript_ChangeNature_Text_Brave, 2
	dynmultipush Debug_EventScript_ChangeNature_Text_Adamant, 3
	dynmultipush Debug_EventScript_ChangeNature_Text_Naughty, 4
	dynmultipush Debug_EventScript_ChangeNature_Text_Bold, 5
	dynmultipush Debug_EventScript_ChangeNature_Text_Docile, 6
	dynmultipush Debug_EventScript_ChangeNature_Text_Relaxed, 7
	dynmultipush Debug_EventScript_ChangeNature_Text_Impish, 8
	dynmultipush Debug_EventScript_ChangeNature_Text_Lax, 9
	dynmultipush Debug_EventScript_ChangeNature_Text_Timid, 10
	dynmultipush Debug_EventScript_ChangeNature_Text_Hasty, 11
	dynmultipush Debug_EventScript_ChangeNature_Text_Serious, 12
	dynmultipush Debug_EventScript_ChangeNature_Text_Jolly, 13
	dynmultipush Debug_EventScript_ChangeNature_Text_Naive, 14
	dynmultipush Debug_EventScript_ChangeNature_Text_Modest, 15
	dynmultipush Debug_EventScript_ChangeNature_Text_Mild, 16
	dynmultipush Debug_EventScript_ChangeNature_Text_Quiet, 17
	dynmultipush Debug_EventScript_ChangeNature_Text_Bashful, 18
	dynmultipush Debug_EventScript_ChangeNature_Text_Rash, 19
	dynmultipush Debug_EventScript_ChangeNature_Text_Calm, 20
	dynmultipush Debug_EventScript_ChangeNature_Text_Gentle, 21
	dynmultipush Debug_EventScript_ChangeNature_Text_Sassy, 22
	dynmultipush Debug_EventScript_ChangeNature_Text_Careful, 23
	dynmultipush Debug_EventScript_ChangeNature_Text_Quirky, 24
	dynmultistack 0, 0, TRUE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, PRU_TrainingHub_Exit
	special SetHiddenNature
	msgbox PRU_TrainingHub_Text_NatureDone, MSGBOX_DEFAULT
	goto PRU_TrainingHub_Exit

PRU_TrainingHub_EvIv::
	lockall
	faceplayer
	msgbox PRU_TrainingHub_Text_EvIvIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PRU_TrainingHub_Exit
	msgbox PRU_TrainingHub_Text_ChooseMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, PRU_TrainingHub_Exit
	message PRU_TrainingHub_Text_EvIv
	waitmessage
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, PRU_TrainingHub_Text_PerfectIVs, PRU_TrainingHub_Text_PhysicalEVs, PRU_TrainingHub_Text_SpecialEVs, PRU_TrainingHub_Text_BulkyEVs, PRU_TrainingHub_Text_ResetEVs, PRU_TrainingHub_Text_Cancel
	switch VAR_RESULT
	case 0, PRU_TrainingHub_PerfectIVs
	case 1, PRU_TrainingHub_PhysicalEVs
	case 2, PRU_TrainingHub_SpecialEVs
	case 3, PRU_TrainingHub_BulkyEVs
	case 4, PRU_TrainingHub_ResetEVs
	case 5, PRU_TrainingHub_Exit
	case MULTI_B_PRESSED, PRU_TrainingHub_Exit
	end
PRU_TrainingHub_PerfectIVs::
	special PRU_SetSelectedMonPerfectIVs
	goto PRU_TrainingHub_StatsDone
PRU_TrainingHub_PhysicalEVs::
	special PRU_SetSelectedMonPhysicalEVs
	goto PRU_TrainingHub_StatsDone
PRU_TrainingHub_SpecialEVs::
	special PRU_SetSelectedMonSpecialEVs
	goto PRU_TrainingHub_StatsDone
PRU_TrainingHub_BulkyEVs::
	special PRU_SetSelectedMonBulkyEVs
	goto PRU_TrainingHub_StatsDone
PRU_TrainingHub_ResetEVs::
	special PRU_ResetSelectedMonEVs
PRU_TrainingHub_StatsDone::
	msgbox PRU_TrainingHub_Text_StatsDone, MSGBOX_DEFAULT
PRU_TrainingHub_Exit::
	releaseall
	end

PRU_TrainingHub_Text_AbilityNature:
	.string "I change ABILITIES and NATURES\n"
	.string "for free. Want my help?$"
PRU_TrainingHub_Text_AbilityNatureChoose:
	.string "Which should I change?$"
PRU_TrainingHub_Text_Ability:
	.string "ABILITY$"
PRU_TrainingHub_Text_Nature:
	.string "NATURE$"
PRU_TrainingHub_Text_Cancel:
	.string "CANCEL$"
PRU_TrainingHub_Text_ChooseMon:
	.string "Choose a POKéMON from your party.$"
PRU_TrainingHub_Text_AbilityDone:
	.string "Its alternate ABILITY is active!$"
PRU_TrainingHub_Text_AbilityFailed:
	.string "That POKéMON has no alternate\nABILITY to activate.$"
PRU_TrainingHub_Text_NatureDone:
	.string "Its effective NATURE was changed!$"
PRU_TrainingHub_Text_EvIv:
	.string "Perfect IVs or a legal EV spread?\nEvery service here is free.$"
PRU_TrainingHub_Text_EvIvIntro:
	.string "I train EVs and perfect IVs\n"
	.string "for free. Want my help?$"
PRU_TrainingHub_Text_PerfectIVs:
	.string "PERFECT IVS$"
PRU_TrainingHub_Text_PhysicalEVs:
	.string "PHYSICAL EVS$"
PRU_TrainingHub_Text_SpecialEVs:
	.string "SPECIAL EVS$"
PRU_TrainingHub_Text_BulkyEVs:
	.string "BULKY EVS$"
PRU_TrainingHub_Text_ResetEVs:
	.string "RESET EVS$"
PRU_TrainingHub_Text_StatsDone:
	.string "Training complete!$"

PRU_Elite18_Steward::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_KANTO_LEAGUE_CLEARED, PRU_Elite18_Locked
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite20_Steward_Cleared
	goto PRU_Elite18_AskChallenge

PRU_Elite20_Steward_Cleared::
	goto_if_unset FLAG_PRU_E20_REWARD_CLAIMED, PRU_Elite20_Steward_PendingReward
	@ Saves that claimed the prize in an earlier build still get their finale.
	call PRU_Elite20_StartFinale
	goto PRU_Elite18_AskChallenge

PRU_Elite20_Steward_PendingReward::
	@ Older E20-cleared saves can still claim missed one-time rewards.
	@ Oak's repeatable RELICS explanation is also available in his lab.
	call PRU_Elite20_ClaimRewards
	goto_if_unset FLAG_PRU_E20_REWARD_CLAIMED, PRU_Elite18_Exit
	call PRU_Elite20_StartFinale
	goto PRU_Elite18_AskChallenge

PRU_Elite18_AskChallenge::
	msgbox PRU_Elite18_Text_FullRun, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PRU_Elite18_ChoosePair
	goto PRU_Elite18_Gauntlet

PRU_Elite18_Locked::
	msgbox PRU_Elite18_Text_Locked, MSGBOX_DEFAULT
	release
	end

PRU_Elite18_RequireTwo::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, PRU_Elite18_NeedTwo
	return

PRU_Elite18_NeedTwo::
	msgbox PRU_Elite18_Text_NeedTwo, MSGBOX_DEFAULT
	release
	end

PRU_Elite18_Gauntlet::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_01
	call PRU_Elite18_Round_02
	call PRU_Elite18_Round_03
	call PRU_Elite18_Round_04
	call PRU_Elite18_Round_05
	call PRU_Elite18_Round_06
	call PRU_Elite18_Round_07
	call PRU_Elite18_Round_08
	call PRU_Elite18_Round_09
	call PRU_Elite18_Round_10
	call PRU_Elite18_Round_11
	call PRU_Elite18_Round_12
	call PRU_Elite18_Round_13
	call PRU_Elite18_Round_14
	call PRU_Elite18_Round_15
	call PRU_Elite18_Round_16
	call PRU_Elite18_Round_17
	call PRU_Elite18_Round_18
	call PRU_Elite18_Round_19
	call PRU_Elite18_Round_20
	setflag FLAG_PRU_ELITE18_CLEARED
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Cleared, MSGBOX_DEFAULT
	@ Independent of rewards / credits flags, so every E20 gauntlet win
	@ receives Oak and Elm's story reveal (including repeat victories).
	msgbox PRU_Elite20_Text_ElmRelics, MSGBOX_DEFAULT
	msgbox PRU_Elite20_Text_OakRelics, MSGBOX_DEFAULT
	msgbox PRU_Elite20_Text_RuinsDirections, MSGBOX_DEFAULT
	call PRU_Elite20_ClaimRewards
	call PRU_Elite20_StartFinale
	release
	end

PRU_Elite20_StartFinale::
	goto_if_set FLAG_PRU_E20_CREDITS_SHOWN, PRU_Elite20_StartFinale_Return
	goto_if_unset FLAG_PRU_E20_REWARD_CLAIMED, PRU_Elite20_StartFinale_Return
	msgbox PRU_Elite20_Text_FinalCelebration, MSGBOX_DEFAULT
	setflag FLAG_PRU_E20_CREDITS_SHOWN
	setflag FLAG_PRU_E20_CREDITS_PENDING
	special GameClear
	waitstate
PRU_Elite20_StartFinale_Return::
	return

PRU_Elite20_Text_FinalCelebration:
	.string "OAK: You defeated the ELITE 20!\p"
	.string "ELM: Every region's finest have\n"
	.string "seen your extraordinary team.\p"
	.string "OAK: Let your journey be\n"
	.string "remembered among the RELICS!$"

PRU_Elite20_ClaimRewards::
	@ Both pockets must have room before giving either prize. The new flag
	@ is only set after BOTH gifts succeed; old completed saves retry here.
	goto_if_set FLAG_PRU_E20_REWARD_CLAIMED, PRU_Elite20_ClaimRewards_Return
	checkitemspace ITEM_MASTER_BALL, 6
	goto_if_eq VAR_RESULT, FALSE, PRU_Elite20_BagFull
	checkitemspace ITEM_ANCIENT_STONE, 5
	goto_if_eq VAR_RESULT, FALSE, PRU_Elite20_BagFull
	giveitem ITEM_MASTER_BALL, 6
	goto_if_eq VAR_RESULT, FALSE, PRU_Elite20_BagFull
	giveitem ITEM_ANCIENT_STONE, 5
	goto_if_eq VAR_RESULT, FALSE, PRU_Elite20_BagFull
	setflag FLAG_PRU_E20_REWARD_CLAIMED
	msgbox PRU_Elite20_Text_Champion, MSGBOX_DEFAULT
	return

PRU_Elite20_BagFull::
	msgbox PRU_Elite20_Text_NoRoom, MSGBOX_DEFAULT
	return

PRU_Elite20_ClaimRewards_Return::
	return

PRU_Elite18_ChoosePair::
	message PRU_Elite18_Text_Choose
	waitmessage
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, PRU_Elite18_Text_Option_01, PRU_Elite18_Text_Option_02, PRU_Elite18_Text_Option_03, PRU_Elite18_Text_Option_04, PRU_Elite18_Text_Option_05, PRU_Elite18_Text_Option_06, PRU_Elite18_Text_Option_07, PRU_Elite18_Text_Option_08, PRU_Elite18_Text_Option_09, PRU_Elite18_Text_Option_10, PRU_Elite18_Text_Option_11, PRU_Elite18_Text_Option_12, PRU_Elite18_Text_Option_13, PRU_Elite18_Text_Option_14, PRU_Elite18_Text_Option_15, PRU_Elite18_Text_Option_16, PRU_Elite18_Text_Option_17, PRU_Elite18_Text_Option_18, PRU_Elite18_Text_Option_19, PRU_Elite18_Text_Option_20, PRU_Elite18_Text_Option_Cancel
	switch VAR_RESULT
	case 0, PRU_Elite18_One_01
	case 1, PRU_Elite18_One_02
	case 2, PRU_Elite18_One_03
	case 3, PRU_Elite18_One_04
	case 4, PRU_Elite18_One_05
	case 5, PRU_Elite18_One_06
	case 6, PRU_Elite18_One_07
	case 7, PRU_Elite18_One_08
	case 8, PRU_Elite18_One_09
	case 9, PRU_Elite18_One_10
	case 10, PRU_Elite18_One_11
	case 11, PRU_Elite18_One_12
	case 12, PRU_Elite18_One_13
	case 13, PRU_Elite18_One_14
	case 14, PRU_Elite18_One_15
	case 15, PRU_Elite18_One_16
	case 16, PRU_Elite18_One_17
	case 17, PRU_Elite18_One_18
	case 18, PRU_Elite18_One_19
	case 19, PRU_Elite18_One_20
	case 20, PRU_Elite18_Exit
	case MULTI_B_PRESSED, PRU_Elite18_Exit
	end

PRU_Elite18_One_01::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_01
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_02::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_02
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_03::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_03
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_04::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_04
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_05::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_05
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_06::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_06
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_07::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_07
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_08::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_08
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_09::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_09
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_10::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_10
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_11::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_11
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_12::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_12
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_13::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_13
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_14::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_14
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_15::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_15
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_16::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_16
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_17::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_17
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_18::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_18
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_19::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_19
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_One_20::
	call PRU_Elite18_RequireTwo
	call PRU_Elite18_Round_20
	special HealPlayerParty
	goto PRU_Elite18_Exit

PRU_Elite18_Exit::
	closemessage
	release
	end

PRU_Elite18_Round_01::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_01, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_01_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_01_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_01_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_01_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_01_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_01_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_02::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_02, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_02_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_02_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_02_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_02_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_02_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_02_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_03::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_03, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_03_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_03_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_03_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_03_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_03_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_03_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_04::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_04, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_04_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_04_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_04_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_04_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_04_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_04_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_05::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_05, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_05_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_05_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_05_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_05_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_05_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_05_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_06::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_06, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_06_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_06_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_06_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_06_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_06_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_06_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_07::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_07, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_07_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_07_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_07_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_07_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_07_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_07_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_08::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_08, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_08_Master
	trainerbattle_two_trainers TRAINER_PRU_E20_JASMINE_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E20_CLAIR_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_08_Master::
	trainerbattle_two_trainers TRAINER_PRU_E20_JASMINE_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E20_CLAIR_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_09::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_09, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_09_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_09_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_09_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_09_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_09_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_09_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_10::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_10, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_10_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_10_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_10_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_10_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_10_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_10_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_11::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_11, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_11_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_11_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_11_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_11_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_11_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_11_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_12::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_12, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_12_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_12_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_12_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_12_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_12_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_12_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_13::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_13, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_13_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_13_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_13_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_13_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_13_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_13_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_14::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_14, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_14_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_14_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_14_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_14_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_14_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_14_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_15::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_15, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_15_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_15_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_15_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_15_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_15_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_15_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_16::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_16, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_16_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_08_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_08_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_16_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_08_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_08_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_17::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_17, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_17_Master
	trainerbattle_two_trainers TRAINER_PRU_E20_STEVEN_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E20_MAY_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_17_Master::
	trainerbattle_two_trainers TRAINER_PRU_E20_STEVEN_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E20_MAY_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_18::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_18, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_18_Master
	trainerbattle_two_trainers TRAINER_PRU_E20_RIVAL_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E20_GIOVANNI_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_18_Master::
	trainerbattle_two_trainers TRAINER_PRU_E20_RIVAL_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E20_GIOVANNI_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_19::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_19, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_19_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_17_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_17_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_19_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_17_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_17_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_Elite18_Round_20::
	special HealPlayerParty
	msgbox PRU_Elite18_Text_Round_20, MSGBOX_DEFAULT
	goto_if_set FLAG_PRU_ELITE18_CLEARED, PRU_Elite18_Round_20_Master
	trainerbattle_two_trainers TRAINER_PRU_E18_18_A_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_18_B_HNS, PRU_Elite18_Text_Victory
	return
PRU_Elite18_Round_20_Master::
	trainerbattle_two_trainers TRAINER_PRU_E18_18_A_MASTER_HNS, PRU_Elite18_Text_Victory, TRAINER_PRU_E18_18_B_MASTER_HNS, PRU_Elite18_Text_Victory
	return

PRU_KantoLeague_Text_Locked:
	.string "Finish all eight KANTO BADGES,\nTEAM ROCKET and GIOVANNI first!$"
PRU_KantoLeague_Text_Confirm:
	.string "KANTO LEAGUE: five single battles.\nHealing between each. Ready?$"
PRU_KantoLeague_Text_Lost:
	.string "The League demands your best.$"
PRU_KantoLeague_Text_Cleared:
	.string "RED: You earned this title.\p"
	.string "The ELITE 20 awaits at the\nSAFFRON FIGHTING DOJO!$"
PRU_KantoLeague_Text_LORELEI:
	.string "LORELEI: Time for your KANTO\nLEAGUE challenge!$"
PRU_KantoLeague_Text_BRUNO:
	.string "BRUNO: Time for your KANTO\nLEAGUE challenge!$"
PRU_KantoLeague_Text_AGATHA:
	.string "AGATHA: Time for your KANTO\nLEAGUE challenge!$"
PRU_KantoLeague_Text_LANCE:
	.string "LANCE: Time for your KANTO\nLEAGUE challenge!$"
PRU_KantoLeague_Text_RED:
	.string "RED: Time for your KANTO\nLEAGUE challenge!$"
PRU_Elite18_Text_Locked:
	.string "Defeat RED in the new KANTO\nLEAGUE first!$"
PRU_Elite18_Text_FullRun:
	.string "ELITE 20: twenty paired\ndouble battles, healing each round.\p"
	.string "Take the full challenge?\nNO: choose an individual pair.$"
PRU_Elite18_Text_Choose:
	.string "Choose your ELITE 20 pair:$"
PRU_Elite18_Text_Victory:
	.string "An impressive victory!$"
PRU_Elite18_Text_NeedTwo:
	.string "Bring at least two healthy\nPOKEMON for DOUBLE BATTLES!$"
PRU_Elite18_Text_Cleared:
	.string "OAK: Incredible! You've beaten\n"
	.string "all twenty legendary pairs!\p"
	.string "The ELITE 20 is yours.\n"
	.string "Our MASTER teams await rematches!$"
PRU_Elite20_Text_ElmRelics:
	.string "ELM: Listen, {PLAYER}!\p"
	.string "Our research found six ancient\n"
	.string "RELICS, each with a hidden voice.\p"
	.string "Follow R - E - L - I - C - S.\n"
	.string "The RUINS OF ALPH hold clues.$"
PRU_Elite20_Text_OakRelics:
	.string "OAK: Their combined resonance\n"
	.string "may awaken a GOLDEN RELIC HO-OH.\p"
	.string "When the RELICS quest is done,\n"
	.string "seek me atop MT. SILVER.\p"
	.string "We've also prepared a prize\n"
	.string "worthy of an ELITE 20 CHAMPION!$"
PRU_Elite20_Text_RuinsDirections:
	.string "OAK: To begin, fly to VIOLET\n"
	.string "CITY and go SOUTH to ROUTE 32.\p"
	.string "Take the WEST path to the\n"
	.string "RUINS OF ALPH RESEARCH LAB.\p"
	.string "Speak to the SCIENTIST there.\n"
	.string "Our first clue is R: RAIKOU.$"
PRU_Elite20_Text_Champion:
	.string "ELITE 20 CHAMPION!\p"
	.string "Your triumph is now recorded.\n"
	.string "Enjoy the MASTER rematches!$"
PRU_Elite20_Text_NoRoom:
	.string "ELM: Keep room for SIX MASTER\n"
	.string "BALLS and FIVE ANCIENT STONES!\p"
	.string "Come back when your BAG has\n"
	.string "space. Your prize is safe.$"
PRU_Elite18_Text_Round_01:
	.string "ROUND 01: BROCK and ROXANNE!$"
PRU_Elite18_Text_Option_01:
	.string "01 BROCK/ROXANNE$"
PRU_Elite18_Text_Round_02:
	.string "ROUND 02: MISTY and WALLACE!$"
PRU_Elite18_Text_Option_02:
	.string "02 MISTY/WALLACE$"
PRU_Elite18_Text_Round_03:
	.string "ROUND 03: SURGE and WATTSON!$"
PRU_Elite18_Text_Option_03:
	.string "03 SURGE/WATTSON$"
PRU_Elite18_Text_Round_04:
	.string "ROUND 04: ERIKA and BUGSY!$"
PRU_Elite18_Text_Option_04:
	.string "04 ERIKA/BUGSY$"
PRU_Elite18_Text_Round_05:
	.string "ROUND 05: JANINE and KOGA!$"
PRU_Elite18_Text_Option_05:
	.string "05 JANINE/KOGA$"
PRU_Elite18_Text_Round_06:
	.string "ROUND 06: SABRINA and WILL!$"
PRU_Elite18_Text_Option_06:
	.string "06 SABRINA/WILL$"
PRU_Elite18_Text_Round_07:
	.string "ROUND 07: BLAINE and FLANNERY!$"
PRU_Elite18_Text_Option_07:
	.string "07 BLAINE/FLANNERY$"
PRU_Elite18_Text_Round_08:
	.string "ROUND 08: JASMINE and CLAIR!$"
PRU_Elite18_Text_Option_08:
	.string "08 JASMINE/CLAIR$"
PRU_Elite18_Text_Round_09:
	.string "ROUND 09: LORELEI and GLACIA!$"
PRU_Elite18_Text_Option_09:
	.string "09 LORELEI/GLACIA$"
PRU_Elite18_Text_Round_10:
	.string "ROUND 10: BRUNO and CHUCK!$"
PRU_Elite18_Text_Option_10:
	.string "10 BRUNO/CHUCK$"
PRU_Elite18_Text_Round_11:
	.string "ROUND 11: AGATHA and PHOEBE!$"
PRU_Elite18_Text_Option_11:
	.string "11 AGATHA/PHOEBE$"
PRU_Elite18_Text_Round_12:
	.string "ROUND 12: KAREN and SIDNEY!$"
PRU_Elite18_Text_Option_12:
	.string "12 KAREN/SIDNEY$"
PRU_Elite18_Text_Round_13:
	.string "ROUND 13: LANCE and DRAKE!$"
PRU_Elite18_Text_Option_13:
	.string "13 LANCE/DRAKE$"
PRU_Elite18_Text_Round_14:
	.string "ROUND 14: STEEVEE and NEEVEE!$"
PRU_Elite18_Text_Option_14:
	.string "14 STEEVEE/NEEVEE$"
PRU_Elite18_Text_Round_15:
	.string "ROUND 15: JESSIE and JAMES!$"
PRU_Elite18_Text_Option_15:
	.string "15 JESSIE/JAMES$"
PRU_Elite18_Text_Round_16:
	.string "ROUND 16: MAXIE and ARCHIE!$"
PRU_Elite18_Text_Option_16:
	.string "16 MAXIE/ARCHIE$"
PRU_Elite18_Text_Round_17:
	.string "ROUND 17: STEVEN and MAY!$"
PRU_Elite18_Text_Option_17:
	.string "17 STEVEN/MAY$"
PRU_Elite18_Text_Round_18:
	.string "ROUND 18: {RIVAL} and GIOVANNI!$"
PRU_Elite18_Text_Option_18:
	.string "18 {RIVAL}/GIOVANNI$"
PRU_Elite18_Text_Round_19:
	.string "ROUND 19: RED and BLUE!$"
PRU_Elite18_Text_Option_19:
	.string "19 RED/BLUE$"
PRU_Elite18_Text_Round_20:
	.string "ROUND 20: OAK and ELM!$"
PRU_Elite18_Text_Option_20:
	.string "20 OAK/ELM$"
PRU_Elite18_Text_Option_Cancel:
	.string "CANCEL$"
@ PRU spread-move tutor: its eligibility filter checks either species type
@ for every member of the active Dex, including the Relic evolutions.
PRU_DoublesTutor::
	lock
	faceplayer
	msgbox PRU_DoublesTutor_Text_Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PRU_Elite18_Exit
	message PRU_DoublesTutor_Text_Choose
	waitmessage
	dynmultichoice 0, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, PRU_DoublesTutor_Text_ShockwaveFist, PRU_DoublesTutor_Text_Faultline, PRU_DoublesTutor_Text_WraithCry, PRU_DoublesTutor_Text_MetalBarrage, PRU_DoublesTutor_Text_Mindwave, IndigoPlateau_Text_TutorMove_Cancel
	switch VAR_RESULT
	case 0, PRU_DoublesTutor_ShockwaveFist
	case 1, PRU_DoublesTutor_Faultline
	case 2, PRU_DoublesTutor_WraithCry
	case 3, PRU_DoublesTutor_MetalBarrage
	case 4, PRU_DoublesTutor_Mindwave
	case 5, PRU_Elite18_Exit
	case MULTI_B_PRESSED, PRU_Elite18_Exit
	end

PRU_DoublesTutor_ShockwaveFist::
	setvar VAR_0x8005, MOVE_SHOCKWAVE_FIST
	goto PRU_DoublesTutor_Teach
PRU_DoublesTutor_Faultline::
	setvar VAR_0x8005, MOVE_FAULTLINE
	goto PRU_DoublesTutor_Teach
PRU_DoublesTutor_WraithCry::
	setvar VAR_0x8005, MOVE_WRAITH_CRY
	goto PRU_DoublesTutor_Teach
PRU_DoublesTutor_MetalBarrage::
	setvar VAR_0x8005, MOVE_METAL_BARRAGE
	goto PRU_DoublesTutor_Teach
PRU_DoublesTutor_Mindwave::
	setvar VAR_0x8005, MOVE_MINDWAVE
	goto PRU_DoublesTutor_Teach

PRU_DoublesTutor_Teach::
	buffermovename STR_VAR_1, VAR_0x8005
	msgbox IndigoPlateau_Text_TutorConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PRU_Elite18_Exit
	msgbox IndigoPlateau_Text_TutorWhichMon, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	chooseboxmon SELECT_PC_MON_PRU_DOUBLE_TUTOR
	waitstate
	goto_if_eq VAR_RESULT, FALSE, PRU_Elite18_Exit
	msgbox IndigoPlateau_Text_TutorDone, MSGBOX_DEFAULT
	release
	end

PRU_DoublesTutor_Text_Intro:
	.string "I teach five free moves that\n"
	.string "strike BOTH foes. Want my help?$"
PRU_DoublesTutor_Text_Choose:
	.string "Which spread move do you want?$"
PRU_DoublesTutor_Text_ShockwaveFist:
	.string "SHOCKWAVE FIST$"
PRU_DoublesTutor_Text_Faultline:
	.string "FAULTLINE$"
PRU_DoublesTutor_Text_WraithCry:
	.string "WRAITH CRY$"
PRU_DoublesTutor_Text_MetalBarrage:
	.string "METAL BARRAGE$"
PRU_DoublesTutor_Text_Mindwave:
	.string "MINDWAVE$"
