MtSilver_SummitDay_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_SummitDay_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MtSilver_SummitDay_OnFrame
	.byte 0

MtSilver_SummitDay_OnFrame::
	map_script_2 VAR_TEMP_MTSILVER_RESUME_BLIZZARD_SE, 0, MtSilver_SummitDay_Blizzard
	.2byte 0

MtSilver_SummitDay_Blizzard::
	playse SE_M_BLIZZARD
	setvar VAR_TEMP_MTSILVER_RESUME_BLIZZARD_SE, 1
	end

MtSilver_SummitDay_OnTransition:
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	call_if_set FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetDay
	call MtSilver_SummitDay_EventScript_SyncRelicOak
	end

MtSilver_SummitDay_EventScript_SetNight::
	setmaplayoutindex LAYOUT_MT_SILVER_SUMMIT_NIGHT_HNS
	return

MtSilver_SummitDay_EventScript_SetDay::
	setmaplayoutindex LAYOUT_MT_SILVER_SUMMIT_DAY_HNS
	return

MtSilver_SummitDay_EventScript_Red::
	lock
	faceplayer
	@ A full-bag Crest can be collected on a later conversation, without
	@ preventing ordinary Red rematches once the Crest is received.
	goto_if_unset FLAG_DEFEATED_RED, MtSilver_SummitDay_EventScript_RedBattleNormal
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_CheckPendingCrest
MtSilver_SummitDay_EventScript_RedBattleNormal::
	msgbox MtSilver_SummitDay_Text_Red, MSGBOX_DEFAULT
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, MtSilver_SummitDay_EventScript_RedStandard
	goto_if_ge VAR_SINJOH_STORYLINE, 13, MtSilver_SummitDay_EventScript_RedPostOBC

MtSilver_SummitDay_EventScript_RedStandard::
	trainerbattle_no_intro TRAINER_RED_HNS, MtSilver_SummitDay_Text_RedBeaten
	goto MtSilver_SummitDay_EventScript_RedOnDefeat

MtSilver_SummitDay_EventScript_RedPostOBC::
	trainerbattle_no_intro TRAINER_RED_POSTOBC_HNS, MtSilver_SummitDay_Text_RedBeaten
	goto MtSilver_SummitDay_EventScript_RedOnDefeat

MtSilver_SummitDay_EventScript_RedOnDefeat::
	playse SE_M_BLIZZARD
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN_HNS
	msgbox MtSilver_SummitDay_Text_Red, MSGBOX_DEFAULT
	special GivePartyMonLandRibbon
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_MTSILVER_RED
	removeobject LOCALID_MTSILVER_RED
	fadescreenswapbuffers FADE_FROM_BLACK
	delay 180
	fadescreenspeed FADE_TO_BLACK, 24
	setflag FLAG_DEFEATED_RED
	setflag FLAG_PJR_RED_DEFEATED
	goto_if_set FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_AfterCrest
	call MtSilver_SummitDay_EventScript_AwardCrest
MtSilver_SummitDay_EventScript_AfterCrest:
	@ Only unlock the Relic form after the actual Crest has been granted.
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_ContinueClear
	call_if_set FLAG_PJR_RELIC_ALPHORACLE, MtSilver_SummitDay_EventScript_UnlockRelicHoOh
MtSilver_SummitDay_EventScript_ContinueClear::
	setflag FLAG_END_NUZLOCKE
	goto_if_set FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_RedVictoryComplete
	@ Keep the defeated Red available only if a full bag blocked the Crest.
	@ His saved defeat flag routes this conversation to item recovery, not battle.
	clearflag FLAG_HIDE_MTSILVER_RED
	MtSilver_SummitDay_EventScript_RedVictoryComplete:
	@ Red keeps the Crest but does not start the game's full credits.
	fadescreen FADE_FROM_BLACK
	releaseall
	end

@ Both initial reward and a subsequent safe retry use the same one-time
@ Crest handoff.  A full bag MUST NOT mark the Crest as received.
MtSilver_SummitDay_EventScript_AwardCrest::
	giveitem ITEM_ANCIENT_RAINBOW_CREST
	goto_if_eq VAR_RESULT, FALSE, MtSilver_SummitDay_EventScript_CrestFullBag
	setflag FLAG_PJR_GOT_RAINBOW_CREST
	msgbox MtSilver_SummitDay_Text_Crest, MSGBOX_DEFAULT
	return

MtSilver_SummitDay_EventScript_CrestFullBag::
	msgbox MtSilver_SummitDay_Text_CrestFullBag, MSGBOX_DEFAULT
	return

MtSilver_SummitDay_EventScript_CheckPendingCrest::
	goto_if_set FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_RedBattleNormal
	msgbox MtSilver_SummitDay_Text_CrestPending, MSGBOX_DEFAULT
	call MtSilver_SummitDay_EventScript_AwardCrest
	call_if_set FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_UnlockRelicHoOh
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_RedCrestStillPending
	setflag FLAG_HIDE_MTSILVER_RED
	removeobject LOCALID_MTSILVER_RED
	release
	end

MtSilver_SummitDay_EventScript_RedCrestStillPending::
	release
	end

MtSilver_SummitDay_Text_CrestPending:
	.string "RED left something behind.\p"
	.string "Make room for the CREST\n"
	.string "if your bag is full.$"

MtSilver_SummitDay_Text_CrestFullBag:
	.string "There is no room for the\n"
	.string "ANCIENT RAINBOW CREST!\p"
	.string "Return with bag space.\n"
	.string "The CREST is still here.$"

MtSilver_SummitDay_Text_Red:
	.string ".........................\n"
	.string ".........................$"

MtSilver_SummitDay_EventScript_UnlockRelicHoOh::
	@ Crest alone cannot reveal HO-OH. The Tin Tower roof checks every
	@ preceding RELIC's caught flag and the physical Crest on map entry.
	return

MtSilver_SummitDay_Text_RedBeaten:
	.string "...!$"

MtSilver_SummitDay_Text_Crest:
	.string "RED leaves behind the ANCIENT\n"
	.string "RAINBOW CREST.\p"
	.string "Some say golden wings fly above\n"
	.string "JOHTO's oldest towers.\p"
	.string "For now, it is only a rumour.$"



@ Endgame epilogue: the professors' E20 invitation pays off on Mt Silver.
@ Use only established quest flags. The original Tin Tower route is retained
@ for saves already in that quest, but both locations share the same catch flag.
MtSilver_SummitDay_EventScript_SyncRelicOak::
	setflag FLAG_PRU_HIDE_MT_SILVER_RELIC_OAK
	goto_if_set FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PRU_ELITE18_CLEARED, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_RAIKOU, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_ENTEI, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_LUGIA, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_UNOWN_I, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_CELEBI, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_SyncOakDone
	clearflag FLAG_PRU_HIDE_MT_SILVER_RELIC_OAK
	@ On completion, Oak replaces the original Red rematch at the same tile.
	setflag FLAG_HIDE_MTSILVER_RED
	return

MtSilver_SummitDay_EventScript_SyncOakDone::
	@ Red's first summit victory is permanent, including after Oak's finale.
	return

MtSilver_SummitDay_EventScript_RelicOak::
	lock
	faceplayer
	@ Keep Oak's final trainer battle even if HO-OH was caught before
	@ visiting him. No separate Mt Silver HO-OH encounter exists.
	goto_if_set FLAG_PRU_RELIC_OAK_BATTLE_WON, MtSilver_SummitDay_EventScript_OakAfterBattle
	msgbox MtSilver_SummitDay_Text_OakChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_E18_18_A_MASTER_HNS, MtSilver_SummitDay_Text_OakBeaten
	setflag FLAG_PRU_RELIC_OAK_BATTLE_WON
	msgbox MtSilver_SummitDay_Text_OakReady, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_EventScript_OakAfterBattle::
	goto_if_set FLAG_PJR_RELIC_HO_OH, MtSilver_SummitDay_EventScript_OakEpilogue
	goto MtSilver_SummitDay_EventScript_OakSummon

MtSilver_SummitDay_EventScript_OakSummon::
	@ Legacy label: retain for old scripts, but Oak can no longer summon
	@ a second HO-OH. Tin Tower is the only catchable encounter.
	msgbox MtSilver_SummitDay_Text_OakSummon, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_EventScript_OakRelicCaught::
	@ Old label kept without a second capture or setting catch flags.
	goto MtSilver_SummitDay_EventScript_OakSummon

MtSilver_SummitDay_EventScript_OakEpilogue::
	msgbox MtSilver_SummitDay_Text_OakEpilogue, MSGBOX_DEFAULT
	setflag FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE
	setflag FLAG_PRU_HIDE_MT_SILVER_RELIC_OAK
	release
	end

MtSilver_SummitDay_EventScript_OakNeedCrest::
	msgbox MtSilver_SummitDay_Text_OakNeedCrest, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_EventScript_OakDecline::
	msgbox MtSilver_SummitDay_Text_OakDecline, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_Text_OakChallenge:
	.string "OAK: You followed every RELIC\n"
	.string "and reached the summit!\p"
	.string "But one final test remains.\p"
	.string "Show me the strength that\n"
	.string "conquered the ELITE 20!$"

MtSilver_SummitDay_Text_OakBeaten:
	.string "OAK: Magnificent!$"

MtSilver_SummitDay_Text_OakReady:
	.string "OAK: Our research hints at a\n"
	.string "golden bird above TIN TOWER.\p"
	.string "That may be the last RELIC!\n"
	.string "Go and see for yourself.$"

MtSilver_SummitDay_Text_OakSummon:
	.string "OAK: Search TIN TOWER's roof.\n"
	.string "No other summit can summon it.$"

MtSilver_SummitDay_Text_OakNeedCrest:
	.string "OAK: Bring the ANCIENT RAINBOW\n"
	.string "CREST before we begin.$"

MtSilver_SummitDay_Text_OakDecline:
	.string "OAK: Take your time.\n"
	.string "History can wait a little!$"

MtSilver_SummitDay_Text_OakRetry:
	.string "OAK: The RELIC HO-OH is still\n"
	.string "out there. Try again!$"

MtSilver_SummitDay_Text_OakEpilogue:
	.string "OAK: You have united the RELICS!\p"
	.string "ELM and I could not be prouder.\p"
	.string "Your legend will live on,\n"
	.string "ELITE 20 CHAMPION!$"

