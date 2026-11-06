TinTower_RoofDay_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_RoofDay_OnTransition
	.byte 0

TinTower_RoofDay_OnTransition:
	call_if_set FLAG_DAY_POKEMON, TinTower_RoofDay_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, TinTower_RoofDay_EventScript_SetDay
	call TinTower_RoofDay_EventScript_SyncGuardianState
	goto_if_eq VAR_COMPLETED_HO_OH, 2, TinTower_RoofDay_MapScript_GuardianStory
	end

@ Save-compatible self-heal for the final RELIC encounter.  Older saves could
@ own the Crest and Alphoracle but still have VAR_COMPLETED_HO_OH stuck at 3,
@ leaving an empty roof.  Derive the unlock from the real quest flags on entry.
TinTower_RoofDay_EventScript_SyncGuardianState::
	goto_if_set FLAG_PRU_TIN_GUARDIAN_DEFEATED, TinTower_RoofDay_EventScript_GuardianDone
	goto_if_set FLAG_PJR_RELIC_HO_OH, TinTower_RoofDay_EventScript_GuardianLegacyDone
	goto_if_ge VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_GuardianLegacyDone
	return

TinTower_RoofDay_EventScript_GuardianLegacyDone::
	setflag FLAG_PRU_TIN_GUARDIAN_DEFEATED
TinTower_RoofDay_EventScript_GuardianDone::
	setflag FLAG_HIDE_TIN_TOWER_GUARDIAN
	return


TinTower_RoofDay_EventScript_SetNight::
	setmaplayoutindex LAYOUT_TIN_TOWER_ROOF_NIGHT_HNS
	return

TinTower_RoofDay_EventScript_SetDay::
	setmaplayoutindex LAYOUT_TIN_TOWER_ROOF_DAY_HNS
	return

TinTower_RoofDay_MapScript_GuardianStory::
	goto_if_set FLAG_PRU_TIN_GUARDIAN_DEFEATED, TinTower_RoofDay_MapScript_GuardianDone
	setflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	clearflag FLAG_HIDE_TIN_TOWER_GUARDIAN
	end

TinTower_RoofDay_MapScript_GuardianDone::
	setflag FLAG_HIDE_TIN_TOWER_GUARDIAN
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
	applymovement LOCALID_TIN_TOWER_GUARDIAN, TinTower_RoofDay_Movement_GuardianAppear
	applymovement OBJ_EVENT_ID_CAMERA, TinTower_RoofDay_Movement_CameraPanUp
	waitmovement 0
	delay 50
	@ setweather WEATHER_NONE
	@ doweather
	waitse
	playbgm MUS_HG_HO_OH_APPEARS, 0
	playmoncry SPECIES_DRAGONITE, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	delay 60
	setvar VAR_0x8004, 3  @ num loops
	setvar VAR_0x8005, 35 @ delay
	special LoopWingFlapSE
	applymovement LOCALID_TIN_TOWER_GUARDIAN, TinTower_RoofDay_Movement_GuardianApproach
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
	playse SE_M_PETAL_DANCE
	delay 30
	msgbox TinTower_RoofDay_Text_GuardianChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_ANCIENT_GUARDIAN_DRAGONITE, TinTower_RoofDay_Text_GuardianVictory
	setflag FLAG_PRU_TIN_GUARDIAN_DEFEATED
	setflag FLAG_HIDE_TIN_TOWER_GUARDIAN
	removeobject LOCALID_TIN_TOWER_GUARDIAN
	setflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	setvar VAR_ECRUTEAK_CITY_THEATER, 8
	setvar VAR_COMPLETED_HO_OH, 3
	playse SE_M_PETAL_DANCE
	delay 30
	msgbox TinTower_RoofDay_Text_GuardianFarewell, MSGBOX_DEFAULT
	releaseall
	end

TinTower_RoofDay_EventScript_GuardianDragonite::
	lockall
	goto_if_set FLAG_PRU_TIN_GUARDIAN_DEFEATED, TinTower_RoofDay_EventScript_GuardianAlreadyDefeated
	msgbox TinTower_RoofDay_Text_GuardianRumour, MSGBOX_DEFAULT
	releaseall
	end

TinTower_RoofDay_EventScript_GuardianAlreadyDefeated::
	msgbox TinTower_RoofDay_Text_GuardianFarewell, MSGBOX_DEFAULT
	releaseall
	end

TinTower_RoofDay_EventScript_Zuki::
	goto_if_eq VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_ZukiAfter
	msgbox TinTower_RoofDay_Text_Zuki_Before, MSGBOX_NPC
	end
TinTower_RoofDay_EventScript_ZukiAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
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

TinTower_RoofDay_Text_GuardianRumour:
	.string "A blue-crystal Dragonite\n"
	.string "watches over the TIN TOWER.$"

TinTower_RoofDay_Text_GuardianChallenge:
	.string "The KIMONO GIRLS bow as one.\p"
	.string "The ancient guardian accepts\n"
	.string "your challenge!$"

TinTower_RoofDay_Text_GuardianVictory:
	.string "The KIMONO GIRLS honour\n"
	.string "the guardian's strength.$"

TinTower_RoofDay_Text_GuardianFarewell:
	.string "The guardian bows, then\n"
	.string "vanishes in blue light.\p"
	.string "The KIMONO GIRLS complete\n"
	.string "their ancient ceremony.$"

TinTower_RoofDay_Text_Kimono_AfterNotCaught:
	.string "The ancient guardian has been\n"
	.string "honoured. Travel safely.$"

TinTower_RoofDay_Text_Kimono_AfterCaught:
	.string "The ancient guardian has been\n"
	.string "honoured. Travel safely.$"

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

TinTower_RoofDay_Movement_GuardianApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	delay_16
	delay_16
	step_end

TinTower_RoofDay_Movement_GuardianAppear:
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

TinTower_RoofDay_Text_Zuki_Before::
	.string "ZUKI: The guardian awaits.$"
TinTower_RoofDay_Text_Naoko_Before::
	.string "NAOKO: The guardian awaits.$"
TinTower_RoofDay_Text_Miki_Before::
	.string "MIKI: The guardian awaits.$"
TinTower_RoofDay_Text_Sayo_Before::
	.string "SAYO: The guardian awaits.$"
TinTower_RoofDay_Text_Kuni_Before::
	.string "KUNI: The guardian awaits.$"

TinTower_RoofDay_Text_Kimono_Opening::
	.string "The CLEAR BELL resounds\n"
	.string "through this tower.\p"
	.string "Our dance will call the\n"
	.string "guardian watches over it.$"

TinTower_RoofDay_Text_Kimono_Closing1::
	.string "The CLEAR BELL has answered!\p"
	.string "The ancient guardian is here\n"
	.string "to test your heart and\n"
	.string "strength.$"

TinTower_RoofDay_Text_Kimono_After::
	.string "You have honoured the guardian.\n"
	.string "Say hello to PROF. ELM for us.$"

