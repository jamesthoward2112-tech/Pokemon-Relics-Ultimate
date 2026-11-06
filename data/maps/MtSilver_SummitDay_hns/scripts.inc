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
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_ContinueClear
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

MtSilver_SummitDay_Text_RedBeaten:
	.string "...!$"

MtSilver_SummitDay_Text_Crest:
	.string "RED leaves behind the ANCIENT\n"
	.string "RAINBOW CREST.\p"
	.string "The CREST hums with a faint\n"
	.string "RESONANCE, but gives no direction.\p"
	.string "Ask the RUINS OF ALPH scientists\n"
	.string "what its old marks might mean.$"



@ Endgame epilogue: the professors' E20 invitation pays off on Mt Silver.
@ Use only established quest flags. The original Tin Tower route is retained
@ for saves already in that quest, but both locations share the same catch flag.
MtSilver_SummitDay_EventScript_SyncRelicOak::
	setflag FLAG_PRU_HIDE_MT_SILVER_RELIC_OAK
	setflag FLAG_HIDE_MT_SILVER_GOLDEN_HO_OH
	goto_if_set FLAG_PJR_RELIC_HO_OH, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_set FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PRU_ELITE18_CLEARED, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_RAIKOU, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_ENTEI, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_LUGIA, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_UNOWN_I, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_CELEBI, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, MtSilver_SummitDay_EventScript_SyncOakDone
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, MtSilver_SummitDay_EventScript_SyncOakDone
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
	goto_if_set FLAG_PJR_RELIC_HO_OH, MtSilver_SummitDay_EventScript_OakEpilogue
	goto_if_unset FLAG_PRU_ELITE18_CLEARED, MtSilver_SummitDay_EventScript_OakNeedElite20
	goto_if_unset FLAG_PJR_RELIC_RAIKOU, MtSilver_SummitDay_EventScript_OakNeedRelics
	goto_if_unset FLAG_PJR_RELIC_ENTEI, MtSilver_SummitDay_EventScript_OakNeedRelics
	goto_if_unset FLAG_PJR_RELIC_LUGIA, MtSilver_SummitDay_EventScript_OakNeedRelics
	goto_if_unset FLAG_PJR_RELIC_UNOWN_I, MtSilver_SummitDay_EventScript_OakNeedRelics
	goto_if_unset FLAG_PJR_RELIC_CELEBI, MtSilver_SummitDay_EventScript_OakNeedRelics
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, MtSilver_SummitDay_EventScript_OakNeedRelics
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, MtSilver_SummitDay_EventScript_OakNeedRelics
	goto MtSilver_SummitDay_EventScript_OakSummon

MtSilver_SummitDay_EventScript_OakSummon::
	msgbox MtSilver_SummitDay_Text_OakObsessed, MSGBOX_DEFAULT
	msgbox MtSilver_SummitDay_Text_OakReluctant, MSGBOX_DEFAULT
	msgbox MtSilver_SummitDay_Text_OakSummon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtSilver_SummitDay_EventScript_OakDecline
	setweather WEATHER_SUNNY
	doweather
	clearflag FLAG_HIDE_MT_SILVER_GOLDEN_HO_OH
	applymovement LOCALID_MT_SILVER_GOLDEN_HO_OH, MtSilver_SummitDay_Movement_HoOhRise
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 35
	special LoopWingFlapSE
	playbgm MUS_HG_HO_OH_APPEARS, 0
	playse SE_M_PETAL_DANCE
	delay 45
	playmoncry SPECIES_RELIC_HO_OH, CRY_MODE_ENCOUNTER
	waitmoncry
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 35
	special LoopWingFlapSE
	seteventmon SPECIES_RELIC_HO_OH, 100
	playbgm MUS_HG_VS_HO_OH, 0
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtSilver_SummitDay_EventScript_OakRelicCaught
	setflag FLAG_HIDE_MT_SILVER_GOLDEN_HO_OH
	setweather WEATHER_SNOW
	doweather
	msgbox MtSilver_SummitDay_Text_OakRetry, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_EventScript_OakRelicCaught::
	setflag FLAG_PJR_RELIC_HO_OH
	setflag FLAG_HIDE_HO_OH
	setflag FLAG_HIDE_MT_SILVER_GOLDEN_HO_OH
	setweather WEATHER_SNOW
	doweather
	removeobject VAR_LAST_TALKED
	call PRU_Elite20_StartFinale
	goto MtSilver_SummitDay_EventScript_OakEpilogue

MtSilver_SummitDay_EventScript_OakEpilogue::
	msgbox MtSilver_SummitDay_Text_OakEpilogue, MSGBOX_DEFAULT
	setflag FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE
	setflag FLAG_PRU_HIDE_MT_SILVER_RELIC_OAK
	release
	end

MtSilver_SummitDay_EventScript_OakNeedElite20::
	msgbox MtSilver_SummitDay_Text_OakNeedElite20, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_EventScript_OakNeedRelics::
	msgbox MtSilver_SummitDay_Text_OakNeedRelics, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_EventScript_OakDecline::
	msgbox MtSilver_SummitDay_Text_OakDecline, MSGBOX_DEFAULT
	release
	end

MtSilver_SummitDay_Text_OakObsessed:
	.string "OAK: You came... I knew the\n"
	.string "RELIC resonance would lead\n"
	.string "you here. I tried to catch\p"
	.string "GOLDEN HO-OH. It overpowered\n"
	.string "me. I still hear its wings...\p"
	.string "I have to see it again.$"

MtSilver_SummitDay_Text_OakReluctant:
	.string "OAK: It's magnificent.\n"
	.string "Its power deserves careful\n"
	.string "study...\p"
	.string "No. I can't let anyone else\n"
	.string "take it from me. It's mine...\p"
	.string "I can't stand here forever.\n"
	.string "I'll summon it for you.$"

MtSilver_SummitDay_Text_OakSummon:
	.string "OAK: If it chooses you, I'll\n"
	.string "accept your worthiness.\n"
	.string "Are you ready?$"

MtSilver_SummitDay_Text_OakNeedElite20:
	.string "OAK: Prove yourself in the\n"
	.string "ELITE 20 first, Trainer.$"

MtSilver_SummitDay_Text_OakNeedRelics:
	.string "OAK: Unite the seven RELICS\n"
	.string "before I can summon it.$"

MtSilver_SummitDay_Text_OakDecline:
	.string "OAK: Take your time.\n"
	.string "History can wait a little!$"

MtSilver_SummitDay_Text_OakRetry:
	.string "OAK: It is still out there...\p"
	.string "I can summon it again when\n"
	.string "you're ready. Don't give up.$"

MtSilver_SummitDay_Text_OakEpilogue:
	.string "OAK: It chose you... and you\n"
	.string "earned that choice.\p"
	.string "ELM and I are proud of you,\n"
	.string "ELITE 20 CHAMPION.$"

MtSilver_SummitDay_Movement_HoOhRise:
	walk_in_place_up
	walk_in_place_down
	walk_in_place_up
	walk_in_place_down
	step_end


