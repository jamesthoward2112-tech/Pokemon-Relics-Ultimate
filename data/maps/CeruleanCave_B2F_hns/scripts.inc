CeruleanCave_B2F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeruleanCave3_OnFrame
	.byte 0

CeruleanCave3_OnFrame::
	map_script_2 VAR_TEMP_0, 0, CeruleanCave3_EventScript_CheckPresence
	.2byte 0

CeruleanCave3_EventScript_CheckPresence::
	setvar VAR_TEMP_0, 1
	goto_if_set FLAG_TEMP_B, CeruleanCave3_EventScript_NoPresence
	lockall
	msgbox CeruleanCave3_Text_MewsionPresence, MSGBOX_DEFAULT
	closemessage
	releaseall
CeruleanCave3_EventScript_NoPresence::
	end

CeruleanCave3_Text_MewsionPresence:
	.string "A strange presence fills the air...\p"
	.string "Dark matter has been detected nearby!$"

CeruleanCave3_EventScript_MewtwoNew::
	lock
	faceplayer
	playmoncry SPECIES_MEWTWO, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_MEWTWO, 80
	special BattleSetup_StartLegendaryBattle
waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, CeruleanCave3_EventScript_MewtwoRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_CERULEANCAVE_MEWTWO
	setflag FLAG_HIDE_MEWTWO
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

CeruleanCave3_EventScript_MewtwoRan::
	release
	end

CeruleanCave3_EventScript_Mewsion::
	lock
	faceplayer
	playmoncry SPECIES_MEWSION, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_MEWSION, 90
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, CeruleanCave3_EventScript_MewsionRan
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, CeruleanCave3_EventScript_MewsionCaught
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_CERULEANCAVE_MEWSION
	setflag FLAG_TEMP_B
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

CeruleanCave3_EventScript_MewsionCaught::
	setflag FLAG_PRU_MEWSION_CAUGHT
	setvar VAR_PRU_MEWDUO_CAPTURE_MARKER, 0x4D44
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_CERULEANCAVE_MEWSION
	setflag FLAG_TEMP_B
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

CeruleanCave3_EventScript_MewsionRan::
	release
	end

CeruleanCave3_EventScript_MaxRevive::
    finditem ITEM_MAX_REVIVE
    end

CeruleanCave3_EventScript_UltraBall::
    finditem ITEM_ULTRA_BALL
    end

