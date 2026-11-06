BellchimeTrail_hns_MapScripts::
	.byte 0


BellchimeTrail_EventScript_Morty::
	lock
	faceplayer
	msgbox BellchimeTrail_Text_Morty, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_BELLCHIME_MORTY
	removeobject LOCALID_BELLCHIME_MORTY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_MORTY
	release
	end

BellchimeTrail_Text_Morty:
	.string "MORTY: The legendary POKéMON\n"
	.string "did not choose me...\p"
	.string "But that does not mean that I\n"
	.string "have lost out on my future.\p"
	.string "I will continue my training until I\n"
	.string "I discover a new future for me.\p"
	.string "If you seek another battle, find\n"
	.string "me at the FIGHTING DOJO.$"

EcruteakBellchimeTrail_EventScript_Item_BigMushroom::
	finditem ITEM_BIG_MUSHROOM
	end

EcruteakBellchimeTrail_EventScript_DoorTrigger::
	lock
	opendoor 28, 12
	waitdooranim
	addobject OBJ_EVENT_ID_CAMERA
	removeobject OBJ_EVENT_ID_PLAYER
	closedoor 28, 12
	applymovement OBJ_EVENT_ID_CAMERA, EcruteakBellchimeTrail_Movement_CameraPanUp
	waitmovement 0
	warp MAP_TIN_TOWER_1F_HNS, 1
	release
	end

EcruteakBellchimeTrail_Movement_CameraPanUp::
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end


EcruteakBellchimeTrail_EventScript_RelicShortcut::
	@ PRU is a fresh standalone story. Never backfill or create mythical
	@ catches from old VAR_COMPLETED_HO_OH / defeated-Red flags.
	@ Access follows completed Elite 20 and the seven RELICS, never a relic item.
	goto_if_unset FLAG_PRU_ELITE18_CLEARED, EcruteakBellchimeTrail_EventScript_RelicShortcutDormant
	goto_if_unset FLAG_PJR_RELIC_RAIKOU, EcruteakBellchimeTrail_EventScript_RelicShortcutDormant
	goto_if_unset FLAG_PJR_RELIC_ENTEI, EcruteakBellchimeTrail_EventScript_RelicShortcutDormant
	goto_if_unset FLAG_PJR_RELIC_LUGIA, EcruteakBellchimeTrail_EventScript_RelicShortcutDormant
	goto_if_unset FLAG_PJR_RELIC_UNOWN_I, EcruteakBellchimeTrail_EventScript_RelicShortcutDormant
	goto_if_unset FLAG_PJR_RELIC_CELEBI, EcruteakBellchimeTrail_EventScript_RelicShortcutDormant
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, EcruteakBellchimeTrail_EventScript_RelicShortcutDormant
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, EcruteakBellchimeTrail_EventScript_RelicShortcutDormant
	goto EcruteakBellchimeTrail_EventScript_RelicShortcutReady

EcruteakBellchimeTrail_EventScript_RelicShortcutReady::
	msgbox EcruteakBellchimeTrail_Text_RelicShortcutReady, MSGBOX_DEFAULT
	warp MAP_TIN_TOWER_ROOF_DAY_HNS, 10, 13
	waitstate
	end

EcruteakBellchimeTrail_EventScript_RelicShortcutDormant::
	msgbox EcruteakBellchimeTrail_Text_RelicShortcutDormantMsg, MSGBOX_DEFAULT
	end

EcruteakBellchimeTrail_Text_RelicShortcutReady:
	.string "The seven RELICS resonate.\p"
	.string "A passage opens to the\n"
	.string "TIN TOWER roof.$"

EcruteakBellchimeTrail_Text_RelicShortcutDormantMsg:
	.string "The ancient statue is silent.\p"
	.string "Complete the ELITE 20 and\n"
	.string "gather all seven RELICS.$"
