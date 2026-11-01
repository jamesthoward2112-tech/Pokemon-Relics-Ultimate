TinTower_RoofDay_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_RoofDay_OnTransition
	.byte 0

TinTower_RoofDay_OnTransition:
	call_if_set FLAG_DAY_POKEMON, TinTower_RoofDay_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, TinTower_RoofDay_EventScript_SetDay
	call TinTower_RoofDay_EventScript_SyncRelicHoOhState
	end

@ One-time final RELIC encounter only. Never show the old story Ho-Oh.
@ Both old state=2 saves and earlier ordinary Ho-Oh catches are respected.
TinTower_RoofDay_EventScript_SyncRelicHoOhState::
	setflag FLAG_HIDE_HO_OH
	setflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	goto_if_set FLAG_PJR_RELIC_HO_OH, TinTower_RoofDay_EventScript_SyncRelicHoOhCaught
	goto_if_set FLAG_CAUGHT_HO_OH, TinTower_RoofDay_EventScript_SyncLegacyHoOhCaught
	goto_if_unset FLAG_PJR_RELIC_RAIKOU, TinTower_RoofDay_EventScript_SyncRelicHoOhLocked
	goto_if_unset FLAG_PJR_RELIC_ENTEI, TinTower_RoofDay_EventScript_SyncRelicHoOhLocked
	goto_if_unset FLAG_PJR_RELIC_LUGIA, TinTower_RoofDay_EventScript_SyncRelicHoOhLocked
	goto_if_unset FLAG_PJR_RELIC_UNOWN_I, TinTower_RoofDay_EventScript_SyncRelicHoOhLocked
	goto_if_unset FLAG_PJR_RELIC_CELEBI, TinTower_RoofDay_EventScript_SyncRelicHoOhLocked
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, TinTower_RoofDay_EventScript_SyncRelicHoOhLocked
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, TinTower_RoofDay_EventScript_SyncRelicHoOhLocked
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, TinTower_RoofDay_EventScript_SyncRelicHoOhLocked
	checkitem ITEM_ANCIENT_RAINBOW_CREST
	goto_if_eq VAR_RESULT, FALSE, TinTower_RoofDay_EventScript_SyncRelicHoOhLocked
	setvar VAR_COMPLETED_HO_OH, 4
	setobjectxyperm LOCALID_HO_OH, 10, 6
	clearflag FLAG_HIDE_HO_OH
	return

TinTower_RoofDay_EventScript_SyncLegacyHoOhCaught::
	@ Earlier saves may have caught the retired Lv50 Ho-Oh. Avoid offering a
	@ second Ho-Oh, even when the later quest unlocks.
	setflag FLAG_PJR_RELIC_HO_OH
	goto TinTower_RoofDay_EventScript_SyncRelicHoOhCaught

TinTower_RoofDay_EventScript_SyncRelicHoOhCaught::
	setvar VAR_COMPLETED_HO_OH, 3
	setflag FLAG_HIDE_HO_OH
	return

TinTower_RoofDay_EventScript_SyncRelicHoOhLocked::
	@ Even an old VAR_COMPLETED_HO_OH=2 or =4 cannot bypass the quest.
	setvar VAR_COMPLETED_HO_OH, 3
	setflag FLAG_HIDE_HO_OH
	return

TinTower_RoofDay_EventScript_SetNight::
	setmaplayoutindex LAYOUT_TIN_TOWER_ROOF_NIGHT_HNS
	return

TinTower_RoofDay_EventScript_SetDay::
	setmaplayoutindex LAYOUT_TIN_TOWER_ROOF_DAY_HNS
	return

@ The early Kimono roof-spawn states are deliberately retired.
@ A single Lv100 Relic Ho-Oh becomes visible only through SyncRelicHoOhState.
TinTower_RoofDay_MapScript_HoohStory::
TinTower_RoofDay_MapScript_HoohPostStoryGone::
TinTower_RoofDay_MapScript_HoohCaught::
TinTower_RoofDay_MapScript_HoohPostStoryEncounter::
TinTower_RoofDay_MapScript_RelicHoOhLocked::
	setflag FLAG_HIDE_HO_OH
	end

TinTower_RoofDay_EventScript_TalkToKimono::
	lockall
	playbgm MUS_HG_KIMONO_GIRL_DANCE, FALSE
	msgbox TinTower_RoofDay_Text_Kimono_Opening, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Step_Aside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, TinTower_RoofDay_Walk_To_Center
	waitmovement 0
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Step_In
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Step_Start_Left
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Step_Start_Right
	waitmovement 5
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid	
	waitmovement 0
	playse SE_M_PETAL_DANCE
	setweather WEATHER_DROUGHT
	doweather
	@ 1
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left
	waitmovement LOCALID_KIMONO_4
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	@ 2
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Right
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Left
	waitmovement LOCALID_KIMONO_4
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	@ 3
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	waitmovement LOCALID_TINTOWER_KIMONO_3
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	@ 4
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Right
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Left
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	waitmovement LOCALID_TINTOWER_KIMONO_3
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	@ 5
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left_Up
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right_Up
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Step_Up
	waitmovement LOCALID_KIMONO_1
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	waitse
	setvar VAR_TEMP_1, 1
	special SpawnCameraObject
	setvar VAR_0x8004, 3  @ num loops
	setvar VAR_0x8005, 35 @ delay
	special LoopWingFlapSE
	applymovement LOCALID_HO_OH, TinTower_RoofDay_Movement_HoOhAppear
	applymovement OBJ_EVENT_ID_CAMERA, TinTower_RoofDay_Movement_CameraPanUp
	waitmovement 0
	delay 50
	@ setweather WEATHER_NONE
	@ doweather
	waitse
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	delay 60
	setvar VAR_0x8004, 3  @ num loops
	setvar VAR_0x8005, 35 @ delay
	special LoopWingFlapSE
	applymovement LOCALID_HO_OH, TinTower_RoofDay_Movement_HoOhApproach
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, TinTower_RoofDay_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	waitmovement 0
	msgbox TinTower_RoofDay_Text_Kimono_Closing1, MSGBOX_DEFAULT
	waitmessage
	closemessage
	releaseall
	end

TinTower_RoofDay_EventScript_HoOh::
	lockall
	goto_if_set FLAG_PJR_RELIC_HO_OH, TinTower_RoofDay_EventScript_HoOhAlreadyCaught
	goto_if_set FLAG_CAUGHT_HO_OH, TinTower_RoofDay_EventScript_HoOhAlreadyCaught
	goto TinTower_RoofDay_EventScript_HoOhPostgame

@ Legacy retry label kept for script/save compatibility, without a second
@ Ho-Oh battle. Rechecks all quest conditions before allowing capture.
TinTower_RoofDay_EventScript_HoOhRetry::
	goto TinTower_RoofDay_EventScript_HoOh

TinTower_RoofDay_EventScript_HoOhPostgame::
	goto_if_unset FLAG_PJR_RELIC_RAIKOU, TinTower_RoofDay_EventScript_HoOhLocked
	goto_if_unset FLAG_PJR_RELIC_ENTEI, TinTower_RoofDay_EventScript_HoOhLocked
	goto_if_unset FLAG_PJR_RELIC_LUGIA, TinTower_RoofDay_EventScript_HoOhLocked
	goto_if_unset FLAG_PJR_RELIC_UNOWN_I, TinTower_RoofDay_EventScript_HoOhLocked
	goto_if_unset FLAG_PJR_RELIC_CELEBI, TinTower_RoofDay_EventScript_HoOhLocked
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, TinTower_RoofDay_EventScript_HoOhLocked
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, TinTower_RoofDay_EventScript_RelicHoOhNeedsAlphoracle
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, TinTower_RoofDay_EventScript_RelicHoOhNeedsCrest
	checkitem ITEM_ANCIENT_RAINBOW_CREST
	goto_if_eq VAR_RESULT, FALSE, TinTower_RoofDay_EventScript_RelicHoOhNeedsCrest
	playmoncry SPECIES_RELIC_HO_OH, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	playbgm MUS_HG_VS_HO_OH, 0
	seteventmon SPECIES_RELIC_HO_OH, 100
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_LAST_TALKED, LOCALID_HO_OH
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, TinTower_RoofDay_EventScript_CaughtRelicHoOh
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, TinTower_RoofDay_EventScript_RanFromHoOh
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, TinTower_RoofDay_EventScript_RanFromHoOh
	msgbox TinTower_RoofDay_Text_RelicHoOhRetry, MSGBOX_DEFAULT
	releaseall
	end

TinTower_RoofDay_EventScript_HoOhLocked::
	msgbox TinTower_RoofDay_Text_RelicHoOhLocked, MSGBOX_DEFAULT
	releaseall
	end

TinTower_RoofDay_EventScript_HoOhAlreadyCaught::
	setflag FLAG_HIDE_HO_OH
	msgbox TinTower_RoofDay_Text_RelicHoOhAlreadyCaught, MSGBOX_DEFAULT
	releaseall
	end

TinTower_RoofDay_EventScript_RelicHoOhNeedsAlphoracle::
	msgbox TinTower_RoofDay_Text_RelicHoOhNeedsAlphoracle, MSGBOX_DEFAULT
	releaseall
	end

TinTower_RoofDay_EventScript_RelicHoOhNeedsCrest::
	msgbox TinTower_RoofDay_Text_RelicHoOhNeedsCrest, MSGBOX_DEFAULT
	releaseall
	end

TinTower_RoofDay_EventScript_CaughtRelicHoOh::
	setflag FLAG_PJR_RELIC_HO_OH
	setflag FLAG_CAUGHT_HO_OH
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HO_OH
	setweather WEATHER_NONE
	doweather
	setflag FLAG_HIDE_HO_OH
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_COMPLETED_HO_OH, 3
	releaseall
	end

TinTower_RoofDay_EventScript_HoohFlewAway::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HO_OH
	setweather WEATHER_NONE
	doweather
	setflag FLAG_HIDE_HO_OH
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, SPECIES_HO_OH
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	return

TinTower_RoofDay_EventScript_CaughtHooh::
	@ Retired ordinary Ho-Oh result: apply the same one-catch flags.
	goto TinTower_RoofDay_EventScript_CaughtRelicHoOh

TinTower_RoofDay_EventScript_RanFromHoOh::
	releaseall
	end

TinTower_RoofDay_EventScript_Zuki::
	goto_if_eq VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_ZukiAfter
	msgbox TinTower_RoofDay_Text_Zuki_Before, MSGBOX_NPC
	end
TinTower_RoofDay_EventScript_ZukiAfter::
	goto_if_unset FLAG_CAUGHT_HO_OH, TinTower_RoofDay_EventScript_ZukiAfterNotCaught
	msgbox TinTower_RoofDay_Text_Kimono_AfterCaught, MSGBOX_NPC
	end
TinTower_RoofDay_EventScript_ZukiAfterNotCaught::
	msgbox TinTower_RoofDay_Text_Kimono_AfterNotCaught, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Naoko::
	goto_if_eq VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_NaokoAfter
	msgbox TinTower_RoofDay_Text_Naoko_Before, MSGBOX_NPC
	end
TinTower_RoofDay_EventScript_NaokoAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Miki::
	goto_if_eq VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_MikiAfter
	msgbox TinTower_RoofDay_Text_Miki_Before, MSGBOX_NPC
	end
TinTower_RoofDay_EventScript_MikiAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Sayo::
	goto_if_eq VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_SayoAfter
	msgbox TinTower_RoofDay_Text_Sayo_Before, MSGBOX_NPC
	end
TinTower_RoofDay_EventScript_SayoAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Kuni::
	goto_if_eq VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_KuniAfter
	msgbox TinTower_RoofDay_Text_Kuni_Before, MSGBOX_NPC
	end
TinTower_RoofDay_EventScript_KuniAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_Text_RelicHoOhLocked:
	.string "Only whispers of golden wings\n"
	.string "linger above the empty tower.$"

TinTower_RoofDay_Text_RelicHoOhAlreadyCaught:
	.string "The golden RELIC has already\n"
	.string "answered your call.$"

TinTower_RoofDay_Text_RelicHoOhNeedsAlphoracle:
	.string "The rainbow resonance is incomplete.\p"
	.string "The FIRST VOICE must awaken at the\n"
	.string "RUINS OF ALPH first.$"

TinTower_RoofDay_Text_RelicHoOhNeedsCrest:
	.string "The golden wind is still.\p"
	.string "The ANCIENT RAINBOW CREST\n"
	.string "has not answered yet.$"

TinTower_RoofDay_Text_RelicHoOhRetry:
	.string "The ancient HO-OH rises again.\p"
	.string "Its resonance will remain here\n"
	.string "until you form a true bond.$"

TinTower_RoofDay_Text_Kimono_AfterNotCaught:
	.string "We hope your journey gives\n"
	.string "life to the ancient legends.$"

TinTower_RoofDay_Text_Kimono_AfterCaught:
	.string "The old tales still have so\n"
	.string "many secrets to reveal.$"

TinTower_RoofDay_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

TinTower_RoofDay_Movement_CameraPanDown:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

TinTower_RoofDay_Movement_HoOhApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	delay_16
	delay_16
	step_end

TinTower_RoofDay_Movement_HoOhAppear:
	delay_16
	delay_16
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	step_end


TinTower_RoofDay_Movement_Kimono_Step_Aside:
	face_right
	delay_16
	walk_right
	delay_16
	face_left
	step_end

TinTower_RoofDay_Walk_To_Center:
	walk_up
	walk_up
	walk_up
	delay_16
	face_down
	step_end

TinTower_RoofDay_Movement_Kimono_Step_In:
	walk_left
	delay_16
	face_down
	step_end


TinTower_RoofDay_Movement_Kimono_Step_Start_Left:
	face_right
	delay_16
	face_up
	delay_16
	walk_up
	walk_up
	delay_16
	face_left
	delay_16
	walk_left
	delay_16
	face_down
	step_end

TinTower_RoofDay_Movement_Kimono_Step_Start_Right:
	face_right
	delay_16
	face_up
	delay_16
	walk_up
	walk_up
	delay_16
	face_right
	delay_16
	walk_right
	delay_16
	face_down
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Mid:
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	delay_8
	delay_8
	delay_8
	delay_8
	delay_16
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down:
	face_down
	delay_8
	walk_down
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right:
	face_right
	delay_8
	walk_right
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up:
	face_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	walk_left
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Right:
	face_right
	delay_8
	walk_right
	walk_right
	walk_right
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Left:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	walk_left
	walk_left
	walk_left
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left_Up:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	walk_left
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_left
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right_Up:
	face_right
	delay_8
	walk_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_right
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Look_Up:
	face_right
	delay_8
	face_up
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Step_Up:
	face_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_left
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right2:
	face_right
	delay_8
	walk_right
	delay_8
	face_down
	delay_16
	face_left
	step_end

@ The former early HO-OH ceremony is unavailable. Keep safe legacy
@ text labels for old script references, but describe rumours only.
TinTower_RoofDay_Text_Zuki_Before::
	.string "ZUKI: Some speak of gold wings\n"
	.string "beyond the clouds.$"
TinTower_RoofDay_Text_Naoko_Before::
	.string "NAOKO: An old tower holds\n"
	.string "many secrets.$"
TinTower_RoofDay_Text_Miki_Before::
	.string "MIKI: A golden shadow?\n"
	.string "Perhaps it was sunlight.$"
TinTower_RoofDay_Text_Sayo_Before::
	.string "SAYO: Legends can take years\n"
	.string "to uncover.$"
TinTower_RoofDay_Text_Kuni_Before::
	.string "KUNI: No one has proved the\n"
	.string "story of the golden bird.$"

TinTower_RoofDay_Text_Kimono_Opening::
	.string "An old song tells of golden\n"
	.string "wings above JOHTO's sky.$"

TinTower_RoofDay_Text_Kimono_Closing1::
	.string "The song ends, leaving only\n"
	.string "the sound of the wind.$"

TinTower_RoofDay_Text_Kimono_After::
	.string "You have done a great job.\n"
	.string "Say hello to PROF.ELM for us.$"
