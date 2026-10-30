DarkCave_NorthSide_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, DarkCave_NorthSide_OnLoadGroudonPassage
	map_script MAP_SCRIPT_ON_TRANSITION, DarkCave_NorthSide_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

DarkCave_NorthSide_OnTransition: 
	callnative SetTimeBasedEncounters
	end


@ Offshoot immediately right of the Blackthorn/Route 45 entrance.
@ Assemble the actual 3-metatile carved black cave-mouth strip from
@ Cave_Default_Hns (0x3B2..0x3B4); its centre is the warp at (46,4).
@ Native code installs full entries, keeping stone sides solid and opening
@ only the centre plus the safe approach.
@ The old man stands in the new approach until FLAG_IS_CHAMPION is set.
DarkCave_NorthSide_OnLoadGroudonPassage::
	callnative PruOpenDarkCaveGroudonDoor
	end

DarkCave_NorthSide_EventScript_GroudonGuard::
	msgbox DarkCave_NorthSide_Text_GroudonGuard, MSGBOX_NPC
	end

DarkCave_NorthSide_Text_GroudonGuard:
	.string "Only the JOHTO CHAMPION may\n"
	.string "enter this ancient magma cave.\p"
	.string "Defeat LANCE at the POKEMON\n"
	.string "LEAGUE, then return here.$"

DarkCave2_EventScript_Item_BlackFlute::
	finditem ITEM_BLACK_FLUTE
	end

DarkCave2_EventScript_Item_StarPiece::
	finditem ITEM_STAR_PIECE
	end

DarkCave2_EventScript_BlackGlasses::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BLACK_GLASSES, DarkCave2_EventScript_BlackGlassesGot
	msgbox DarkCave2_Text_Nerd, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_GLASSES
	setflag FLAG_GOT_BLACK_GLASSES
	closemessage
	release
	end

DarkCave2_EventScript_BlackGlassesGot::
	msgbox DarkCave2_Text_Nerd2, MSGBOX_DEFAULT
	closemessage
	release
	end

DarkCave2_Text_Nerd:
    .string "Whoa! You startled me there!\p"
    .string "I had my BLACK-GLASSES on, so I\n"
    .string "didn't notice you at all.\p"
    .string "What am I doing here?\p"
    .string "Hey, don't you worry about it.\p"
    .string "I'll give you a pair of BLACK-\n"
    .string "GLASSES, so forget you saw me,\n"
    .string "OK?$"

DarkCave2_Text_Nerd2:
    .string "BLACK-GLASSES ups the power of\n"
    .string "DARK-type moves.$"
