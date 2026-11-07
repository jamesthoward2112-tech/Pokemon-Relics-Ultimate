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
	@ Red's rematch does not award or require an obsolete Rainbow Crest.
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
	setflag FLAG_END_NUZLOCKE
	fadescreen FADE_FROM_BLACK
	releaseall
	end

@ Compatibility labels for historic event references; no item is given.
MtSilver_SummitDay_EventScript_AfterCrest:
MtSilver_SummitDay_EventScript_ContinueClear::
MtSilver_SummitDay_EventScript_RedVictoryComplete:
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MtSilver_SummitDay_EventScript_AwardCrest::
MtSilver_SummitDay_EventScript_CrestFullBag::
MtSilver_SummitDay_EventScript_RedCrestStillPending::
	return

MtSilver_SummitDay_EventScript_CheckPendingCrest::
	goto MtSilver_SummitDay_EventScript_RedBattleNormal

MtSilver_SummitDay_Text_Red:
	.string ".........................\n"
	.string ".........................$"

@ Historic shortcut must not unlock Golden Ho-Oh outside the RELICS quest.
MtSilver_SummitDay_EventScript_UnlockRelicHoOh::
	return

MtSilver_SummitDay_Text_RedBeaten:
	.string "...!$"

@ Endgame epilogue: the professors' E20 invitation pays off on Mt Silver.
@ Use only established quest flags. The original Tin Tower route is retained
@ for saves already in that quest, but both locations share the same catch flag.
MtSilver_SummitDay_EventScript_SyncRelicOak::
	setflag FLAG_PRU_HIDE_MT_SILVER_RELIC_OAK
	goto_if_set FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_set FLAG_PJR_RELIC_HO_OH, MtSilver_SummitDay_EventScript_MigrateLegacyHoOh
	goto_if_set FLAG_CAUGHT_HO_OH, MtSilver_SummitDay_EventScript_MigrateLegacyHoOh
	goto_if_unset FLAG_PRU_ELITE18_CLEARED, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_RAIKOU, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_ENTEI, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_LUGIA, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_UNOWN_I, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_CELEBI, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, MtSilver_SummitDay_EventScript_SyncOakDone
	clearflag FLAG_PRU_HIDE_MT_SILVER_RELIC_OAK
	setflag FLAG_HIDE_MTSILVER_RED
	return

MtSilver_SummitDay_EventScript_MigrateLegacyHoOh::
	@ A legacy save that already owns Ho-Oh must never receive another one.
	setflag FLAG_PJR_RELIC_HO_OH
	setflag FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE
	setflag FLAG_PRU_GOLDEN_FINALE_SHOWN
	setflag FLAG_HIDE_HO_OH
	goto MtSilver_SummitDay_EventScript_SyncOakDone

MtSilver_SummitDay_EventScript_SyncOakDone::
	@ Red remains available unless the player already defeated him.
	goto_if_set FLAG_DEFEATED_RED, MtSilver_SummitDay_EventScript_SyncOakReturn
	clearflag FLAG_HIDE_MTSILVER_RED
MtSilver_SummitDay_EventScript_SyncOakReturn::
	return

MtSilver_SummitDay_EventScript_RelicOak::
	lock
	faceplayer
	goto_if_set FLAG_PJR_RELIC_HO_OH, MtSilver_SummitDay_EventScript_OakEpilogue
	goto_if_set FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE, MtSilver_SummitDay_EventScript_OakEpilogue
	goto_if_unset FLAG_PRU_ELITE18_CLEARED, MtSilver_SummitDay_EventScript_OakNeedRequirements
	goto_if_unset FLAG_PJR_RELIC_RAIKOU, MtSilver_SummitDay_EventScript_OakNeedRequirements
	goto_if_unset FLAG_PJR_RELIC_ENTEI, MtSilver_SummitDay_EventScript_OakNeedRequirements
	goto_if_unset FLAG_PJR_RELIC_LUGIA, MtSilver_SummitDay_EventScript_OakNeedRequirements
	goto_if_unset FLAG_PJR_RELIC_UNOWN_I, MtSilver_SummitDay_EventScript_OakNeedRequirements
	goto_if_unset FLAG_PJR_RELIC_CELEBI, MtSilver_SummitDay_EventScript_OakNeedRequirements
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, MtSilver_SummitDay_EventScript_OakNeedRequirements
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, MtSilver_SummitDay_EventScript_OakNeedRequirements
	goto MtSilver_SummitDay_EventScript_OakSummon

@ Professor Oak has no second battle here. He concedes this summon to a
@ trainer whose value he has already witnessed in the final Elite 20 round.
MtSilver_SummitDay_EventScript_OakSummon::
	msgbox MtSilver_SummitDay_Text_OakObsession, MSGBOX_DEFAULT
	msgbox MtSilver_SummitDay_Text_OakSummon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtSilver_SummitDay_EventScript_OakDecline
	playbgm MUS_HG_KIMONO_GIRL_DANCE, FALSE
	playse SE_M_PETAL_DANCE
	setweather WEATHER_DROUGHT
	doweather
	delay 30
	playmoncry SPECIES_RELIC_HO_OH, CRY_MODE_ENCOUNTER
	waitmoncry
	playbgm MUS_HG_VS_HO_OH, 0
	seteventmon SPECIES_RELIC_HO_OH, 100
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtSilver_SummitDay_EventScript_OakRelicCaught
	msgbox MtSilver_SummitDay_Text_OakRetry, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_EventScript_OakRelicCaught::
	setflag FLAG_PJR_RELIC_HO_OH
	setvar VAR_COMPLETED_HO_OH, 3
	setflag FLAG_HIDE_HO_OH
	setflag FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE
	setflag FLAG_PRU_HIDE_MT_SILVER_RELIC_OAK
	goto_if_set FLAG_PRU_GOLDEN_FINALE_SHOWN, MtSilver_SummitDay_EventScript_OakEpilogue
	setflag FLAG_PRU_GOLDEN_FINALE_SHOWN
	setflag FLAG_PRU_E20_CREDITS_PENDING
	special GameClear
	waitstate
	goto MtSilver_SummitDay_EventScript_OakEpilogue

MtSilver_SummitDay_EventScript_OakEpilogue::
	msgbox MtSilver_SummitDay_Text_OakEpilogue, MSGBOX_DEFAULT
	setflag FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE
	setflag FLAG_PRU_HIDE_MT_SILVER_RELIC_OAK
	goto_if_set FLAG_DEFEATED_RED, MtSilver_SummitDay_EventScript_OakEpilogueDone
	clearflag FLAG_HIDE_MTSILVER_RED
MtSilver_SummitDay_EventScript_OakEpilogueDone::
	release
	end

MtSilver_SummitDay_EventScript_OakNeedRequirements::
	msgbox MtSilver_SummitDay_Text_OakNeedRequirements, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_EventScript_OakDecline::
	msgbox MtSilver_SummitDay_Text_OakDecline, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_Text_OakObsession:
	.string "OAK: Golden Ho-Oh... Every trace\n"
	.string "of it leads me back here.\p"
	.string "I tried to summon it myself.\n"
	.string "It overwhelmed me before I could\p"
	.string "reach for a Poké Ball.\p"
	.string "Since then, I've thought of\n"
	.string "little else. I want to see it...\p"
	.string "I want it to choose me.\p"
	.string "No. That isn't who I am.\n"
	.string "You earned its answer, not me.\p"
	.string "I'll call it for you. Please...\n"
	.string "show it respect I could not.$"

MtSilver_SummitDay_Text_OakSummon:
	.string "OAK: Are you ready to meet\n"
	.string "the ULTIMATE ANCIENT RELIC?$"

MtSilver_SummitDay_Text_OakNeedRequirements:
	.string "OAK: The ELITE 20 victory and\n"
	.string "all seven RELICS are required.$"

MtSilver_SummitDay_Text_OakDecline:
	.string "OAK: Take your time.\n"
	.string "History can wait a little!$"

MtSilver_SummitDay_Text_OakRetry:
	.string "OAK: It remains beyond reach.\p"
	.string "When you're ready, we'll try\n"
	.string "again. This time I'll stand back.$"

MtSilver_SummitDay_Text_OakEpilogue:
	.string "OAK: You met Golden Ho-Oh with\n"
	.string "courage and humility.\p"
	.string "I wanted to claim that moment.\n"
	.string "Instead, I got to witness it.\p"
	.string "ELM will want every detail.\n"
	.string "You have made history, {PLAYER}.$"


