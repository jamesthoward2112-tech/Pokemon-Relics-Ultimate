PokemonLeague_WillsRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_WillsRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, PRU_KantoE4_SelectSprites
	.byte 0

@ Johto League remains the original challenge. The post-Giovanni rooms
@ replace its trainers with the Kanto Elite Four and Red.
PRU_KantoE4_SelectSprites::
	goto_if_unset FLAG_IS_CHAMPION, PRU_KantoE4_ShowJohto
	goto_if_unset FLAG_BADGE16_GET, PRU_KantoE4_ShowJohto
	goto_if_unset FLAG_PRU_HEIST_COMPLETED, PRU_KantoE4_ShowJohto
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, PRU_KantoE4_ShowJohto
	goto_if_set FLAG_PRU_KANTO_LEAGUE_CLEARED, PRU_KantoE4_ShowJohto
	setflag FLAG_PRU_HIDE_JOHTO_E4
	clearflag FLAG_PRU_HIDE_KANTO_E4
	end

PRU_KantoE4_ShowJohto::
	clearflag FLAG_PRU_HIDE_JOHTO_E4
	setflag FLAG_PRU_HIDE_KANTO_E4
	end

EliteFourRoom_OnLoad::
	call_if_eq VAR_TEMP_0, 1, EliteFourRoom_CreateDoor
	end

EliteFourRoom_CreateDoor::
	setmetatile 5, 11, 0x29D, TRUE
	setmetatile 6, 11, 0x29E, TRUE
	setmetatile 7, 11, 0x29F, TRUE
	setmetatile 5, 12, 0x2A5, TRUE
	setmetatile 6, 12, 0x2A6, TRUE
	setmetatile 7, 12, 0x2A7, TRUE
	return

PokemonLeague_WillsRoom_OnResume::
	setvar VAR_0x8004, 0
	special DoPokemonLeagueLightingEffect
	end

EliteFourRoom_OnFrame::
	map_script_2 VAR_TEMP_0, 0, EliteFourRoom_CloseDoor
	.2byte 0

EliteFourRoom_CloseDoor::
	lock
	setflag FLAG_TEMP_2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	setmetatile 5, 11, 0x29D, TRUE
	setmetatile 6, 11, 0x29E, TRUE
	setmetatile 7, 11, 0x29F, TRUE
	setmetatile 5, 12, 0x2A5, TRUE
	setmetatile 6, 12, 0x2A6, TRUE
	setmetatile 7, 12, 0x2A7, TRUE
	playse SE_BANG
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar VAR_TEMP_0, 1
	release
	end

PokemonLeague_WillsRoom_EventScript_Will::
	lock 
	faceplayer
	@ The completed Kanto Badge Heist is required for the second League.
	@ This check does not affect the player's first Johto Elite Four clear.
	goto_if_unset FLAG_BADGE16_GET, PokemonLeague_WillsRoom_EventScript_PRUHeistCleared
	goto_if_set FLAG_PRU_HEIST_COMPLETED, PokemonLeague_WillsRoom_EventScript_PRUHeistCleared
	msgbox PokemonLeague_WillsRoom_Text_PRUHeistBlocked, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS, 32, 5
	waitstate
	release
	end

PRU_KantoE4_Lorelei::
	lock
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 2, PRU_KantoE4_LoreleiAlreadyWon
	msgbox PRU_KantoLeague_Text_LORELEI, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_PRU_KANTO_E4_LORELEI_HNS, PRU_KantoLeague_Text_Lost
	clearflag FLAG_TEMP_5
	msgbox PRU_KantoE4_LoreleiAfter, MSGBOX_DEFAULT
	closemessage
	goto PRU_KantoE4_LoreleiOpenExit

PRU_KantoE4_LoreleiAlreadyWon::
	msgbox PRU_KantoE4_LoreleiAfter, MSGBOX_DEFAULT
	release
	end

PRU_KantoE4_LoreleiAfter:
	.string "LORELEI: Incredible! You are\n"
	.string "ready for BRUNO. Go on!$"

PokemonLeague_WillsRoom_EventScript_PRUHeistCleared::
	@ The final Kanto Eevee Twins match at Route 23 is also required.
	goto_if_unset FLAG_BADGE16_GET, PokemonLeague_WillsRoom_EventScript_PRUAllCleared
	checktrainerflag TRAINER_STEEVE_NEEVEE_KANTO_FINALE_HNS
	goto_if TRUE, PokemonLeague_WillsRoom_EventScript_PRUAllCleared
	msgbox PokemonLeague_WillsRoom_Text_PRUTwinsBlocked, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS, 32, 5
	waitstate
	release
	end

PokemonLeague_WillsRoom_EventScript_PRUAllCleared::
	goto_if_ge VAR_LEAGUE_STATE, 2, PokemonLeague_WillsRoom_EventScript_WillDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_WillsRoom_EventScript_WillRematch
	msgbox PokemonLeague_WillsRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_WILL_1_HNS, PokemonLeague_WillsRoom_Text_Beaten
	goto PokemonLeague_WillsRoom_EventScript_WillOnDefeat

PokemonLeague_WillsRoom_EventScript_WillRematch::
	goto_if_unset FLAG_IS_KANTO_CHAMPION, PokemonLeague_WillsRoom_EventScript_WillRematchStandard
	goto_if_ge VAR_SINJOH_STORYLINE, 13, PokemonLeague_WillsRoom_EventScript_WillRematchPostOBC

PokemonLeague_WillsRoom_EventScript_WillRematchStandard::
	msgbox PokemonLeague_WillsRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_WILL_2_HNS, PokemonLeague_WillsRoom_Text_Beaten
	goto PokemonLeague_WillsRoom_EventScript_WillOnDefeat

PokemonLeague_WillsRoom_EventScript_WillRematchPostOBC::
	msgbox PokemonLeague_WillsRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_WILL_POSTOBC_HNS, PokemonLeague_WillsRoom_Text_Beaten
	goto PokemonLeague_WillsRoom_EventScript_WillOnDefeat

PokemonLeague_WillsRoom_EventScript_WillOnDefeat::
	clearflag FLAG_TEMP_5
	msgbox PokemonLeague_WillsRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage

PRU_KantoE4_LoreleiOpenExit::
	setmetatile 6, 1, 0x28E, FALSE
	setmetatile 6, 2, 0x296, FALSE	
	playse SE_BANG
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar VAR_LEAGUE_STATE, 2
	release
	end

PokemonLeague_WillsRoom_EventScript_WillDefeated::
	msgbox PokemonLeague_WillsRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_WillsRoom_Text_Before:
    .string "Welcome to POKéMON LEAGUE,\n"
    .string "{PLAYER}.\p"
    .string "Allow me to introduce myself.\n"
    .string "I am WILL.\p"
    .string "I have trained all around the\n"
    .string "world, making my psychic\l"
    .string "POKéMON powerful.\p"
    .string "And, at last, I've been accepted\n"
    .string "into the ELITE FOUR.\p"
    .string "I can only keep getting better!\p"
    .string "Losing is not an option!$"

PokemonLeague_WillsRoom_Text_Beaten:
    .string "I… I can't… believe it…$"

PokemonLeague_WillsRoom_Text_Defeat:
    .string "Even though I was defeated, I\n"
    .string "won't change my course.\p"
    .string "I will continue battling until I\n"
    .string "stand above all trainers!\p"
    .string "Now, {PLAYER}, move on and\n"
    .string "experience the true ferocity of\l"
    .string "the ELITE FOUR.$"

PokemonLeague_WillsRoom_Text_RematchBefore:
    .string "WILL: Ah, welcome back.\p"
    .string "I have foreseen this encounter.\p"
    .string "My psychic POKéMON and\n"
    .string "I have evolved, developing\l"
    .string "new tactics.\p"
    .string "Prepare yourself for a battle of\n"
    .string "enhanced strategy and might.\p"
    .string "Let us see if your foresight\n"
    .string "matches mine.$"


PokemonLeague_WillsRoom_Text_PRUHeistBlocked:
	.string "WILL: TEAM ROCKET's KANTO\n"
	.string "BADGE HEIST isn't finished!\p"
	.string "Recover the eight badges and\n"
	.string "defeat JESSIE and JAMES before\l"
	.string "challenging us again!$"

PokemonLeague_WillsRoom_Text_PRUTwinsBlocked:
	.string "WILL: STEEVEE and NEEVEE\n"
	.string "are waiting on ROUTE 23!\p"
	.string "Face them before the LEAGUE.$"
