PokemonLeague_KarensRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_KarensRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PRU_KantoE4_KarenOrLance::
	call PRU_KantoE4_CheckActive
	goto_if_eq VAR_RESULT, TRUE, PRU_KantoE4_Lance
	goto PokemonLeague_KarensRoom_EventScript_Karen

PRU_KantoE4_Lance::
	lock
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 5, PRU_KantoE4_LanceAlreadyWon
	msgbox PRU_KantoLeague_Text_LANCE, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_PRU_KANTO_E4_LANCE_HNS, PRU_KantoLeague_Text_Lost
	clearflag FLAG_TEMP_5
	msgbox PRU_KantoE4_LanceAfter, MSGBOX_DEFAULT
	closemessage
	goto PRU_KantoE4_LanceOpenExit

PRU_KantoE4_LanceAlreadyWon::
	msgbox PRU_KantoE4_LanceAfter, MSGBOX_DEFAULT
	release
	end

PRU_KantoE4_LanceAfter:
	.string "LANCE: You're worthy.\n"
	.string "RED is the last obstacle.$"

PokemonLeague_KarensRoom_OnResume::
	setvar VAR_0x8004, 3
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_KarensRoom_EventScript_Karen::
	lock 
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 5, PokemonLeague_KarensRoom_EventScript_KarenDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematch
	msgbox PokemonLeague_KarensRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_1_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematch::
	goto_if_unset FLAG_IS_KANTO_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematchStandard
	goto_if_ge VAR_SINJOH_STORYLINE, 13, PokemonLeague_KarensRoom_EventScript_KarenRematchPostOBC

PokemonLeague_KarensRoom_EventScript_KarenRematchStandard::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_2_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematchPostOBC::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_POSTOBC_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenOnDefeat::
    clearflag FLAG_TEMP_5
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage

PRU_KantoE4_LanceOpenExit::
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
	setvar VAR_LEAGUE_STATE, 5
	release
	end

PokemonLeague_KarensRoom_EventScript_KarenDefeated::
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KarensRoom_Text_RematchBefore:
    .string "KAREN: Ah, it's you again.\p"
    .string "I trust you haven't forgotten\n"
    .string "my belief:\p"
    .string "True strength arises from trust\n"
    .string "in one's POKéMON.\p"
    .string "Since our last encounter, my\n"
    .string "bond with my POKéMON has\l"
    .string "deepened further.\p"
    .string "Are you ready to face a team\n"
    .string "united by an unbreakable bond?\p"
    .string "Show me the power of the bond\n"
    .string "with your POKéMON.$"

PokemonLeague_KarensRoom_Text_Before:
    .string "I am KAREN of the ELITE FOUR.\p"
    .string "You're {PLAYER}? How amusing.\p"
    .string "I love DARK-type POKéMON.\p"
    .string "I find their wild, tough image\n"
    .string "to be so appealing. And they're\l"
    .string "so strong.\p"
    .string "Think you can take them?\n"
    .string "Just try to entertain me.\p"
    .string "Let's go.$"

PokemonLeague_KarensRoom_Text_Beaten:
    .string "Well, aren't you good. I like that\n"
    .string "in a trainer.$"

PokemonLeague_KarensRoom_Text_Defeat:
    .string "Strong POKéMON.\p"
    .string "Weak POKéMON.\p"
    .string "That is only the selfish\n"
    .string "perception of people.\p"
    .string "Truly skilled trainers should\n"
    .string "try to win with their favorites.\p"
    .string "I like your style. You understand\n"
    .string "what's important.\p"
    .string "Go on--the CHAMPION is waiting.$"

