ReceptionGate_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ReceptionGate_OnTransition
	.byte 0

@ PJR progression repair: the east/Kanto route opens after the first League clear,
@ while the west/Mt. Silver route opens only after the rematch League clear.
@ Running this on transition also repairs existing saves created before these gates
@ were tied directly to the two Champion flags.
ReceptionGate_OnTransition::
	call ReceptionGate_EventScript_PRUSyncRocket
	goto_if_unset FLAG_IS_CHAMPION, ReceptionGate_OnTransition_NotJohtoChampion
	setflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD
	goto_if_unset FLAG_IS_KANTO_CHAMPION, ReceptionGate_OnTransition_LockMtSilver
	setflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	end

ReceptionGate_OnTransition_LockMtSilver::
	clearflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	end

ReceptionGate_OnTransition_NotJohtoChampion::
	clearflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD
	clearflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	end

ReceptionGate_EventScript_Janine::
    lock
    faceplayer
    msgbox ReceptionGate_Text_Janine, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_ROUTE22_JANINE
    removeobject LOCALID_INDIGOJUNCTION_JANINE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_JANINE
    release
    end

ReceptionGate_Text_Janine:
    .string "JANINE: I'm on the way to my dad's\n"
    .string "house to give him his lunch.\p"
    .string "The ELITE FOUR has no time to rest\n"
    .string "day or night. It's such hard work,\l"
    .string "you know?\p"
    .string "If you're ready for another battle,\n"
    .string "I'll be at the DOJO later.$"


ReceptionGate_EventScript_Officer::
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_NPC
    end

ReceptionGate_Trigger::
    lock
    playse SE_PIN
    applymovement LOCALID_INDIGOJUNCTION_POLICEMAN, Common_Movement_ExclamationMark
    delay 55
    waitmovement LOCALID_INDIGOJUNCTION_POLICEMAN
    goto_if_lt VAR_ECRUTEAK_CITY_THEATER, 8, ReceptionGate_EventScript_Kimono
    msgbox VictoryRoadGate_Text_Officer, MSGBOX_DEFAULT
    goto_if_unset FLAG_BADGE08_GET, ReceptionGate_EventScript_NotEnough
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_DEFAULT
    closemessage
    setvar VAR_ROUTE27_STATE, 2
    release
    end

ReceptionGate_EventScript_Kimono::
    msgbox VictoryRoadGate_Text_Kimono, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end 

ReceptionGate_EventScript_NotEnough::
    msgbox VictoryRoadGate_Text_NotEnoughBadges, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end

ReceptionGate_EventScript_SilverGuard::
    msgbox VictoryRoadGate_Text_LeftBlackBelt, MSGBOX_NPC
    end
ReceptionGate_EventScript_KantoGuard::
    msgbox VictoryRoadGate_Text_RightBlackBelt, MSGBOX_NPC
    end

VictoryRoadGate_Text_Officer:
    .string "Only trainers who have proven\n"
    .string "themselves may pass.$"

VictoryRoadGate_Text_Kimono:
    .string "Sorry kid, this way is closed until\n"
    .string "someone deals with that LEGENDARY\l"
    .string "POKéMON...$"

VictoryRoadGate_Text_NotEnoughBadges:
    .string "You don't have all the GYM BADGES\n"
    .string "of JOHTO.\p"
    .string "I'm sorry, but I can't let you go\n"
    .string "through.$"

VictoryRoadGate_Text_EightBadges:
    .string "Oh! The eight BADGES of JOHTO!\p"
    .string "Please, go right on through!$"

VictoryRoadGate_Text_LeftBlackBelt:
    .string "This way leads to MT.SILVER.\p"
    .string "You'll see scary-strong POKéMON out\n"
    .string "there.$"

VictoryRoadGate_Text_RightBlackBelt:
    .string "Off to the POKéMON LEAGUE, are you?\p"
    .string "The ELITE FOUR are so strong it's\n"
    .string "scary, and they're ready for you!$"

@ Keep the original Johto/East/West gate progression untouched.
@ The theft unlocks only after Blue's Earth Badge; no real badge is removed.
ReceptionGate_EventScript_PRUSyncRocket::
	setvar VAR_TEMP_0, 0
	setflag FLAG_PRU_HIDE_ROCKET_HEIST_GATE
	setflag FLAG_PRU_HIDE_MEOWTH_BALLOON
	goto_if_unset FLAG_BADGE16_GET, ReceptionGate_EventScript_PRUSyncDone
	goto_if_set FLAG_PRU_HEIST_STARTED, ReceptionGate_EventScript_PRUSyncDone
	clearflag FLAG_PRU_HIDE_ROCKET_HEIST_GATE
ReceptionGate_EventScript_PRUSyncDone::
	return

ReceptionGate_EventScript_PRURocket::
	goto ReceptionGate_EventScript_PRUHeistTrigger

ReceptionGate_EventScript_PRUHeistTrigger::
	goto_if_unset FLAG_BADGE16_GET, ReceptionGate_EventScript_PRUHeistNoop
	goto_if_set FLAG_PRU_HEIST_STARTED, ReceptionGate_EventScript_PRUHeistNoop
	lockall
	setvar VAR_TEMP_0, 1
	playse SE_PIN
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 5
	msgbox ReceptionGate_Text_PRURocketStolen, MSGBOX_DEFAULT
	@ The physical display case is stolen; the original badge bits remain
	@ intact so HM use, 16-badge count and old save progression never regress.
	setflag FLAG_PRU_HEIST_STARTED
	msgbox ReceptionGate_Text_PRURocketBalloon, MSGBOX_DEFAULT
	closemessage
	@ Display authentic MrNightology 64x64 Meowth balloon and animate
	@ its ascent without redrawing or replacing any existing sprites.
	clearflag FLAG_PRU_HIDE_MEOWTH_BALLOON
	addobject 8
	setflag FLAG_PRU_HIDE_ROCKET_HEIST_GATE
	removeobject 5
	removeobject 6
	removeobject 7
	applymovement 8, ReceptionGate_Movement_PRUBalloonRise
	waitmovement 8
	fadescreenswapbuffers FADE_TO_WHITE
	setflag FLAG_PRU_HIDE_MEOWTH_BALLOON
	removeobject 8
	playse SE_M_TELEPORT
	fadescreenswapbuffers FADE_FROM_WHITE
	releaseall
	end

ReceptionGate_EventScript_PRUHeistNoop::
	end

ReceptionGate_Text_PRURocketStolen:
	.string "JESSIE: All sixteen BADGES?\p"
	.string "JAMES: We'll be taking the\n"
	.string "KANTO BADGE CASE!\p"
	.string "MEOWTH: The LEAGUE can wait!\p"
	.string "TEAM ROCKET snatches your\n"
	.string "BADGE CASE!$"

ReceptionGate_Text_PRURocketBalloon:
	.string "MEOWTH: To the balloon!\p"
	.string "The TEAM ROCKET trio escapes\n"
	.string "toward INDIGO PLATEAU!\p"
	.string "Recover seven BADGES from\n"
	.string "KANTO's GYM LEADERS, then\l"
	.string "challenge GIOVANNI!$"


ReceptionGate_Movement_PRUBalloonRise:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
