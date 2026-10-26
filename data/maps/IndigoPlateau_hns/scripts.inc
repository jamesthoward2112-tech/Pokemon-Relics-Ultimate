IndigoPlateau_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_EventScript_PRUSyncRocket
	map_script MAP_SCRIPT_ON_FRAME_TABLE, IndigoPlateau_EventScript_PRUOnFrame
	.byte 0

IndigoPlateau_Sign::
	msgbox IndigoPlateau_Text_Sign, MSGBOX_SIGN
	end

IndigoPlateau_Text_Sign:
	.string "INDIGO PLATEAU\p"
	.string "The Ultimate Goal for Trainers!\p"
	.string "POKéMON LEAGUE HQ$"


@ This second Indigo battle follows eight recovery rematches, not the first
@ Johto League challenge. The Badge Heist is a physical story case only.
IndigoPlateau_EventScript_PRUSyncRocket::
	setvar VAR_TEMP_3, 0
	setflag FLAG_PRU_HIDE_ROCKET_HEIST_INDIGO
	setflag FLAG_PRU_HIDE_MEOWTH_BALLOON
	setflag FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD
	goto_if_unset FLAG_PRU_HEIST_STARTED, IndigoPlateau_EventScript_PRUSyncDone
	goto_if_set FLAG_PRU_HEIST_COMPLETED, IndigoPlateau_EventScript_PRUSyncDone
	clearflag FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, IndigoPlateau_EventScript_PRUSyncDone
	setflag FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD
	clearflag FLAG_PRU_HIDE_ROCKET_HEIST_INDIGO
	@ The Fly landing is (11, 7), directly north of Meowth (11, 9).
	@ Trainer sight checks walking steps, so initiate a one-time arrival
	@ alert here instead of waiting for the player to leave the Fly tile.
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_eq VAR_TEMP_0, 11, IndigoPlateau_EventScript_PRUCheckFlyLanding
	goto IndigoPlateau_EventScript_PRUSyncDone
IndigoPlateau_EventScript_PRUCheckFlyLanding::
	goto_if_eq VAR_TEMP_1, 7, IndigoPlateau_EventScript_PRUArmFlyAmbush
	goto IndigoPlateau_EventScript_PRUSyncDone
IndigoPlateau_EventScript_PRUArmFlyAmbush::
	setvar VAR_TEMP_3, 1
IndigoPlateau_EventScript_PRUSyncDone::
	end

IndigoPlateau_EventScript_PRUOnFrame::
	map_script_2 VAR_TEMP_3, 1, IndigoPlateau_EventScript_PRUFlyAmbush
	.2byte 0

IndigoPlateau_EventScript_PRUFlyAmbush::
	setvar VAR_TEMP_3, 0
	goto IndigoPlateau_EventScript_PRUMeowthAlert

IndigoPlateau_EventScript_PRUMeowthAlert::
	lockall
	applymovement 3, Common_Movement_ExclamationMark
	waitmovement 3
	releaseall
	goto IndigoPlateau_EventScript_PRUJessie

IndigoPlateau_EventScript_PRUJessie::
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, IndigoPlateau_EventScript_PRUWaiting
	trainerbattle_double TRAINER_JESSIE_JAMES_KANTO_FINALE_HNS, IndigoPlateau_Text_PRURocketIntro, IndigoPlateau_Text_PRURocketWin, Route104_Text_GinaNotEnoughMons
	goto IndigoPlateau_EventScript_PRUEscape

IndigoPlateau_EventScript_PRUJames::
	goto IndigoPlateau_EventScript_PRUJessie

IndigoPlateau_EventScript_PRUMeowth::
	@ Meowth is the central lookout: sight (or talking) starts the duo fight.
	goto IndigoPlateau_EventScript_PRUJessie

IndigoPlateau_EventScript_PRUWaiting::
	msgbox IndigoPlateau_Text_PRUWaiting, MSGBOX_NPC
	end

IndigoPlateau_EventScript_PRUEscape::
	lockall
	msgbox IndigoPlateau_Text_PRUBadgeCaseReturn, MSGBOX_DEFAULT
	setflag FLAG_PRU_JESSIE_JAMES_INDIGO
	setflag FLAG_PRU_HEIST_COMPLETED
	setflag FLAG_PRU_HIDE_INDIGO_ROCKET_GUARD
	removeobject 5
	msgbox IndigoPlateau_Text_PRUBalloonDeparture, MSGBOX_DEFAULT
	closemessage
	@ Last Rocket rendezvous: respond, then board one at a time.
	applymovement 1, IndigoPlateau_Movement_PRUJessieReady
	applymovement 2, IndigoPlateau_Movement_PRUJamesReady
	applymovement 3, IndigoPlateau_Movement_PRUMeowthReady
	waitmovement 1
	waitmovement 2
	waitmovement 3
	playse SE_M_FLY
	clearflag FLAG_PRU_HIDE_MEOWTH_BALLOON
	addobject 4
	applymovement 4, IndigoPlateau_Movement_PRUBalloonArrive
	waitmovement 4
	delay 12
	applymovement 1, IndigoPlateau_Movement_PRUJessieBoard
	waitmovement 1
	removeobject 1
	applymovement 2, IndigoPlateau_Movement_PRUJamesBoard
	waitmovement 2
	removeobject 2
	applymovement 3, IndigoPlateau_Movement_PRUMeowthBoard
	waitmovement 3
	removeobject 3
	setflag FLAG_PRU_HIDE_ROCKET_HEIST_INDIGO
	delay 18
	playse SE_M_FLY
	applymovement 4, IndigoPlateau_Movement_PRUBalloonDepart
	waitmovement 4
	setflag FLAG_PRU_HIDE_MEOWTH_BALLOON
	removeobject 4
	releaseall
	end

IndigoPlateau_Text_PRURocketIntro:
	.string "JESSIE: All your BADGES are\n"
	.string "back? Not so fast!\p"
	.string "JAMES: Our final KANTO battle!\p"
	.string "MEOWTH: Let's get 'em!$"

IndigoPlateau_Text_PRURocketWin:
	.string "JESSIE: How can this be?\p"
	.string "JAMES: Our best team lost!$"

IndigoPlateau_Text_PRUBadgeCaseReturn:
	.string "TEAM ROCKET drops your\n"
	.string "original KANTO BADGE CASE!\p"
	.string "All sixteen BADGES are safe.\n"
	.string "The LEAGUE awaits!$"

IndigoPlateau_Text_PRUBalloonDeparture:
	.string "MEOWTH: Prepare to blast off!\p"
	.string "The MEOWTH BALLOON rises and\n"
	.string "TEAM ROCKET flies away!$"

IndigoPlateau_Text_PRUMeowth:
	.string "MEOWTH: That's right!$"

IndigoPlateau_Text_PRUWaiting:
	.string "TEAM ROCKET's final challenge\n"
	.string "awaits the eight BADGES!$"


IndigoPlateau_Movement_PRUJessieReady:
	walk_in_place_down
	step_end

IndigoPlateau_Movement_PRUJamesReady:
	walk_in_place_down
	step_end

IndigoPlateau_Movement_PRUMeowthReady:
	jump_in_place_down
	step_end

IndigoPlateau_Movement_PRUBalloonArrive:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

IndigoPlateau_Movement_PRUJessieBoard:
	walk_fast_down
	step_end

IndigoPlateau_Movement_PRUJamesBoard:
	walk_fast_down
	step_end

IndigoPlateau_Movement_PRUMeowthBoard:
	walk_fast_down
	step_end

IndigoPlateau_Movement_PRUBalloonDepart:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

IndigoPlateau_EventScript_PRUGuard::
	lock
	faceplayer
	msgbox IndigoPlateau_Text_PRUGuard, MSGBOX_DEFAULT
	release
	end

@ The NPC alone cannot stop a tile-warp; this coord event runs before
@ warp handling and denies entry regardless of sprite collision state.
IndigoPlateau_EventScript_PRUDoorGate::
	goto_if_unset FLAG_PRU_HEIST_STARTED, IndigoPlateau_EventScript_PRUDoorUnlocked
	goto_if_set FLAG_PRU_HEIST_COMPLETED, IndigoPlateau_EventScript_PRUDoorUnlocked
	@ Even if the player skirts the lookout coming from Victory Road, the
	@ League door forces the final Jessie/James showdown before entry.
	goto_if_set FLAG_PRU_HEIST_GIOVANNI, IndigoPlateau_EventScript_PRUMeowthAlert
	lockall
	msgbox IndigoPlateau_Text_PRUGuard, MSGBOX_DEFAULT
	releaseall
	end

IndigoPlateau_EventScript_PRUDoorUnlocked::
	warp MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS, 19, 15
	waitstate
	end

IndigoPlateau_Text_PRUGuard:
	.string "ROCKET: LEAGUE is closed!\p"
	.string "Reclaim your KANTO BADGES\n"
	.string "in SAFFRON's DOJO.\p"
	.string "Then find the final LEADER\n"
	.string "to reach the LEAGUE!$"
