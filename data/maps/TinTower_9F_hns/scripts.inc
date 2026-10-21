TinTower_9F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_9F_OnTransition
	.byte 0

@ Existing finale relocated without changing battle or dialogue; 9F upper-right between statues.
TinTower_9F_OnTransition::
	call TinTower_9F_EventScript_SyncFinalRocketState
	call TinTower_OnTransition
	end

@ Story flags arm coordinate approach triggers; entering the floor no longer starts the battle automatically.

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
	lockall
	setvar VAR_TEMP_0, 0
	applymovement 4, TinTower_9F_Movement_JessieNoticePlayer
	waitmovement 4
	goto TinTower_9F_EventScript_JessieJamesTrainer

TinTower_9F_EventScript_JessieJamesInteract::
	goto_if_set FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED, TinTower_9F_EventScript_NoFinalRocket
	goto TinTower_9F_EventScript_JessieJamesTrainer

@ Compatibility alias for previously referenced mandatory encounter.
TinTower_9F_EventScript_JessieJamesBattle::
	goto TinTower_9F_EventScript_JessieJamesTrigger

@ Direct trainerbattle as the first command allows the normal trainer-sight
@ engine to spot the player, show ! and start the double battle automatically.
@ The explicit continuation ensures the victory dialogue and walk-off start
@ immediately without requiring another interaction.
TinTower_9F_EventScript_JessieJamesTrainer::
	trainerbattle_double TRAINER_JESSIE_JAMES_TINTOWER_HNS, TinTower_9F_Text_JessieJamesFinalSeen, TinTower_9F_Text_JessieJamesFinalBeaten, TinTower_9F_Text_JessieJamesNeedTwo, TinTower_9F_EventScript_JessieJamesAfterBattle
	end

TinTower_9F_EventScript_JessieJamesAfterBattle::
	lockall
	setvar VAR_TEMP_0, 0
	setflag FLAG_PJR_JESSIE_JAMES_FINAL_DEFEATED
	msgbox TinTower_9F_Text_JessieJamesFinalAfter, MSGBOX_DEFAULT
	closemessage
	@ Stagger the trio: James leads, Meowth follows, then Jessie.
	@ All three walk right, then turn south along the right-hand passage.
	applymovement 5, TinTower_9F_Movement_JamesExit
	delay 32
	applymovement 6, TinTower_9F_Movement_MeowthExit
	delay 32
	applymovement 4, TinTower_9F_Movement_JessieExit
	waitmovement 0
	removeobject 4
	removeobject 5
	removeobject 6
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

@ Start: Jessie (11,3), Meowth (12,3), James (13,3).
@ The statue at x16,y3 blocks going straight east; turn south at x15.
@ Their routes are staggered so they do not run into one another.
TinTower_9F_Movement_JamesExit:
	walk_right
	walk_right
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

TinTower_9F_Movement_MeowthExit:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

TinTower_9F_Movement_JessieExit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ Jessie spots the player in the corridor when a coordinate trigger fires.
@ Natural trainer sight also shows this alert via the standard engine.
TinTower_9F_Movement_JessieNoticePlayer:
	emote_exclamation_mark
	step_end
