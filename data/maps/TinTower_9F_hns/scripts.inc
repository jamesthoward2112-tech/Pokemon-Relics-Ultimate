TinTower_9F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_9F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TinTower_9F_OnFrame
	.byte 0

@ Existing finale relocated without changing battle or dialogue; 9F upper-right between statues.
TinTower_9F_OnTransition::
	call TinTower_9F_EventScript_SyncFinalRocketState
	call TinTower_OnTransition
	end

@ One-time mandatory Johto finale on 9F, in the statue gallery.
@ Keep the existing Ho-Oh roof scripts independent.
TinTower_9F_OnFrame::
	map_script_2 VAR_TEMP_0, 1, TinTower_9F_EventScript_JessieJamesBattle
	.2byte 0

TinTower_9F_EventScript_SyncFinalRocketState::
	setvar VAR_TEMP_0, 0
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, TinTower_9F_EventScript_HideFinalRocket
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, TinTower_9F_EventScript_HideFinalRocket
	goto_if_set FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED, TinTower_9F_EventScript_HideFinalRocket
	setvar VAR_TEMP_0, 1
	return

TinTower_9F_EventScript_HideFinalRocket::
	removeobject 4
	removeobject 5
	removeobject 6  @ Meowth: sixth local object on this map
	return

TinTower_9F_EventScript_JessieJamesTrigger::
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, TinTower_9F_EventScript_NoFinalRocket
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, TinTower_9F_EventScript_NoFinalRocket
	goto_if_set FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED, TinTower_9F_EventScript_NoFinalRocket
	goto TinTower_9F_EventScript_JessieJamesBattle

TinTower_9F_EventScript_JessieJamesInteract::
	goto_if_set FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED, TinTower_9F_EventScript_NoFinalRocket
	goto TinTower_9F_EventScript_JessieJamesBattle

TinTower_9F_EventScript_JessieJamesBattle::
	lockall
	setvar VAR_TEMP_0, 0
	applymovement 4, Common_Movement_FacePlayer
	applymovement 5, Common_Movement_FacePlayer
	waitmovement 0
	trainerbattle_double TRAINER_JESSIE_JAMES_TINTOWER_HNS, TinTower_9F_Text_JessieJamesFinalSeen, TinTower_9F_Text_JessieJamesFinalBeaten, TinTower_9F_Text_JessieJamesNeedTwo
	setflag FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED
	msgbox TinTower_9F_Text_JessieJamesFinalAfter, MSGBOX_DEFAULT
	removeobject 4
	removeobject 5
	removeobject 6  @ Meowth
	releaseall
	end

TinTower_9F_EventScript_NoFinalRocket::
	end

TinTower_9F_Text_JessieJamesFinalSeen:
	.string "JESSIE: Twerp! Did you really think\n"
	.string "we'd let you claim the ULTIMATE RELIC?\p"
	.string "JAMES: One last performance.\n"
	.string "And this time, we're not holding back!$"

TinTower_9F_Text_JessieJamesFinalBeaten:
	.string "JESSIE & JAMES: Blasting off...\n"
	.string "from JOHTO... for now!$"

TinTower_9F_Text_JessieJamesFinalAfter:
	.string "JESSIE: Fine! The summit is yours.\p"
	.string "JAMES: But if that HO-OH joins you...\n"
	.string "we're taking credit for the warm-up!$"

TinTower_9F_Text_JessieJamesNeedTwo:
	.string "JAMES: This is a double battle!\n"
	.string "Bring at least two POK?MON.$"
