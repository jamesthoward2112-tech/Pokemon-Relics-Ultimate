TinTower_6F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_6F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TinTower_6F_OnFrame
	.byte 0

@ Original Jessie & James event, relocated only: 6F, north-wall gap between statues x7 and x11.
TinTower_6F_OnTransition::
	call TinTower_6F_EventScript_SyncFinalRocketState
	call TinTower_OnTransition
	end

@ One-time mandatory Johto finale on 6F, in the statue gallery.
@ Keep the existing Ho-Oh roof scripts independent.
TinTower_6F_OnFrame::
	map_script_2 VAR_TEMP_0, 1, TinTower_6F_EventScript_JessieJamesBattle
	.2byte 0

TinTower_6F_EventScript_SyncFinalRocketState::
	setvar VAR_TEMP_0, 0
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, TinTower_6F_EventScript_HideFinalRocket
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, TinTower_6F_EventScript_HideFinalRocket
	goto_if_set FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED, TinTower_6F_EventScript_HideFinalRocket
	setvar VAR_TEMP_0, 1
	return

TinTower_6F_EventScript_HideFinalRocket::
	removeobject LOCALID_TINTOWER6F_JESSIE
	removeobject LOCALID_TINTOWER6F_JAMES
	removeobject 5  @ Meowth: fifth local object on this map
	return

TinTower_6F_EventScript_JessieJamesTrigger::
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, TinTower_6F_EventScript_NoFinalRocket
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, TinTower_6F_EventScript_NoFinalRocket
	goto_if_set FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED, TinTower_6F_EventScript_NoFinalRocket
	goto TinTower_6F_EventScript_JessieJamesBattle

TinTower_6F_EventScript_JessieJamesInteract::
	goto_if_set FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED, TinTower_6F_EventScript_NoFinalRocket
	goto TinTower_6F_EventScript_JessieJamesBattle

TinTower_6F_EventScript_JessieJamesBattle::
	lockall
	setvar VAR_TEMP_0, 0
	applymovement LOCALID_TINTOWER6F_JESSIE, Common_Movement_FacePlayer
	applymovement LOCALID_TINTOWER6F_JAMES, Common_Movement_FacePlayer
	waitmovement 0
	trainerbattle_double TRAINER_JESSIE_JAMES_TINTOWER_HNS, TinTower_6F_Text_JessieJamesFinalSeen, TinTower_6F_Text_JessieJamesFinalBeaten, TinTower_6F_Text_JessieJamesNeedTwo
	setflag FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED
	msgbox TinTower_6F_Text_JessieJamesFinalAfter, MSGBOX_DEFAULT
	removeobject LOCALID_TINTOWER6F_JESSIE
	removeobject LOCALID_TINTOWER6F_JAMES
	removeobject 5  @ Meowth
	releaseall
	end

TinTower_6F_EventScript_NoFinalRocket::
	end

TinTower_6F_Text_JessieJamesFinalSeen:
	.string "JESSIE: Twerp! Did you really think\n"
	.string "we'd let you claim the ULTIMATE RELIC?\p"
	.string "JAMES: One last performance.\n"
	.string "And this time, we're not holding back!$"

TinTower_6F_Text_JessieJamesFinalBeaten:
	.string "JESSIE & JAMES: Blasting off...\n"
	.string "from JOHTO... for now!$"

TinTower_6F_Text_JessieJamesFinalAfter:
	.string "JESSIE: Fine! The summit is yours.\p"
	.string "JAMES: But if that HO-OH joins you...\n"
	.string "we're taking credit for the warm-up!$"

TinTower_6F_Text_JessieJamesNeedTwo:
	.string "JAMES: This is a double battle!\n"
	.string "Bring at least two POK?MON.$"
