PokemonLeague_FrlgBrunosRoom_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_FrlgBrunosRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, PokemonLeague_FrlgBrunosRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_FrlgBrunosRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_FrlgBrunosRoom_OnFrame
	.byte 0

PokemonLeague_FrlgBrunosRoom_OnResume::
	setvar VAR_0x8004, 1
	call PokemonLeague_EventScript_DoLightingEffect
	end

PokemonLeague_FrlgBrunosRoom_OnLoad::
	call_if_set FLAG_DEFEATED_BRUNO, PokemonLeague_FrlgBrunosRoom_EventScript_SetDoorOpen
	call_if_eq VAR_MAP_SCENE_POKEMON_LEAGUE, 2, PokemonLeague_FrlgBrunosRoom_EventScript_CloseEntry
	end

PokemonLeague_FrlgBrunosRoom_EventScript_CloseEntry::
	call PokemonLeague_EventScript_CloseEntry
	return

PokemonLeague_FrlgBrunosRoom_EventScript_SetDoorOpen::
	call PokemonLeague_EventScript_SetDoorOpen
	return

PokemonLeague_FrlgBrunosRoom_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_FrlgBrunosRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_FrlgBrunosRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_FrlgBrunosRoom_OnFrame::
	map_script_2 VAR_MAP_SCENE_POKEMON_LEAGUE, 1, PokemonLeague_FrlgBrunosRoom_EventScript_EnterRoom
	.2byte 0

PokemonLeague_FrlgBrunosRoom_EventScript_EnterRoom::
	lockall
	call PokemonLeague_EventScript_EnterRoom
	setvar VAR_MAP_SCENE_POKEMON_LEAGUE, 2
	releaseall
	end

PokemonLeague_FrlgBrunosRoom_EventScript_Bruno::
	lock
	faceplayer
	famechecker FAMECHECKER_BRUNO, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	goto_if_set FLAG_DEFEATED_BRUNO, PokemonLeague_FrlgBrunosRoom_EventScript_PostBattle
	famechecker FAMECHECKER_BRUNO, 0
	famechecker FAMECHECKER_BRUNO, 1
	call_if_unset FLAG_SYS_GAME_CLEAR, PokemonLeague_FrlgBrunosRoom_EventScript_Intro
	call_if_set FLAG_SYS_GAME_CLEAR, PokemonLeague_FrlgBrunosRoom_EventScript_RematchIntro
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	call_if_unset FLAG_IS_CHAMPION, PokemonLeague_FrlgBrunosRoom_EventScript_Battle
	call_if_set FLAG_IS_CHAMPION, PokemonLeague_FrlgBrunosRoom_EventScript_Rematch
	clearflag FLAG_TEMP_5
	goto PokemonLeague_FrlgBrunosRoom_EventScript_DefeatedBruno
	end

PokemonLeague_FrlgBrunosRoom_EventScript_Intro::
	msgbox PokemonLeague_FrlgBrunosRoom_Text_Intro
	return

PokemonLeague_FrlgBrunosRoom_EventScript_RematchIntro::
	msgbox PokemonLeague_FrlgBrunosRoom_Text_RematchIntro
	return

PokemonLeague_FrlgBrunosRoom_EventScript_Battle::
	trainerbattle_no_intro TRAINER_ELITE_FOUR_BRUNO, PokemonLeague_FrlgBrunosRoom_Text_Defeat
	return

PokemonLeague_FrlgBrunosRoom_EventScript_Rematch::
	trainerbattle_no_intro TRAINER_PRU_KANTO_E4_BRUNO_HNS, PokemonLeague_FrlgBrunosRoom_Text_Defeat
	return

PokemonLeague_FrlgBrunosRoom_EventScript_PostBattle::
	msgbox PokemonLeague_FrlgBrunosRoom_Text_PostBattle
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayRight
	call_if_eq VAR_FACING, DIR_SOUTH, PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayLeft
	call_if_eq VAR_FACING, DIR_WEST, PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayDown
	call_if_eq VAR_FACING, DIR_EAST, PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayDown
	release
	end

PokemonLeague_FrlgBrunosRoom_EventScript_DefeatedBruno::
	setflag FLAG_DEFEATED_BRUNO
	call PokemonLeague_EventScript_OpenDoor
	msgbox PokemonLeague_FrlgBrunosRoom_Text_PostBattle
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayRight
	call_if_eq VAR_FACING, DIR_SOUTH, PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayLeft
	call_if_eq VAR_FACING, DIR_WEST, PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayDown
	call_if_eq VAR_FACING, DIR_EAST, PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayDown
	release
	end

PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayLeft::
	applymovement LOCALID_BRUNO, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayRight::
	applymovement LOCALID_BRUNO, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

PokemonLeague_FrlgBrunosRoom_EventScript_BrunoLookAwayDown::
	applymovement LOCALID_BRUNO, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PokemonLeague_FrlgBrunosRoom_Text_Intro::
	.string "I am BRUNO of the ELITE FOUR!\p"
	.string "Through rigorous training, people\n"
	.string "and POKéMON can become stronger\l"
	.string "without limit.\p"
	.string "I've lived and trained with my\n"
	.string "fighting POKéMON!\l"
	.string "And that will never change!\p"
	.string "{PLAYER}!\p"
	.string "We will grind you down with our\n"
	.string "superior power!\p"
	.string "Hoo hah!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

PokemonLeague_FrlgBrunosRoom_Text_RematchIntro::
	.string "I am BRUNO of the ELITE FOUR!\p"
	.string "Through rigorous training, people\n"
	.string "and POKéMON can become stronger\l"
	.string "without limit.\p"
	.string "I've lived and trained with my\n"
	.string "fighting POKéMON!\l"
	.string "And that will never change!\p"
	.string "{PLAYER}!\p"
	.string "We will grind you down with our\n"
	.string "superior power!\p"
	.string "Hoo hah!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

PokemonLeague_FrlgBrunosRoom_Text_Defeat::
	.string "Why?\n"
	.string "How could I lose?$"

PokemonLeague_FrlgBrunosRoom_Text_PostBattle::
	.string "My job is done.\n"
	.string "Go face your next challenge.$"

