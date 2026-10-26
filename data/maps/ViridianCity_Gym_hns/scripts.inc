ViridianCity_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_Gym_OnTransition
	.byte 0

@ Repair old saves where the Dojo invitation left a second Blue in the gym.
ViridianCity_Gym_OnTransition::
	call ViridianCity_Gym_EventScript_PRUHeistSync
	goto_if_unset FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_BlueNotDefeated
	setflag FLAG_HIDE_CINNABAR_BLUE
	setflag FLAG_HIDE_VIRIDIAN_BLUE
	goto_if_set FLAG_PRU_HEIST_STARTED, ViridianCity_Gym_OnTransition_HideDojoBlue
	goto_if_set FLAG_HIDE_DOJO_BLUE, ViridianCity_Gym_OnTransition_End
	setflag FLAG_HIDE_VIRIDIAN_BLUE
ViridianCity_Gym_OnTransition_End::
	end

ViridianCity_Gym_OnTransition_HideDojoBlue::
	setflag FLAG_HIDE_DOJO_BLUE
	end

ViridianCity_Gym_BlueNotDefeated::
	setflag FLAG_HIDE_DOJO_BLUE
	goto_if_set FLAG_HIDE_CINNABAR_BLUE, ViridianCity_Gym_OnTransition_End
	setflag FLAG_HIDE_VIRIDIAN_BLUE
	end

ViridianCity_Gym_EventScript_Blue::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_BlueGotoDojo
	goto_if_unset FLAG_HIDE_CINNABAR_BLUE, ViridianCity_Gym_EventScript_BlueNotReady
	msgbox ViridianCity_Gym_Text_LeaderBlue_Before, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BLUE_HNS, ViridianCity_Gym_Text_LeaderBlue_Win
	message ViridianCity_Gym_Text_ReceivedEarthBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox ViridianCity_Gym_Text_LeaderBlue_After, MSGBOX_DEFAULT
	msgbox ViridianCity_Gym_Text_LeaderBlue_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_TRICK_ROOM
	msgbox ViridianCity_Gym_Text_LeaderBlue_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE16_GET
	setflag FLAG_DEFEATED_VIRIDIAN_GYM
	call ViridianCity_Gym_EventScript_PRUReward
	setflag FLAG_HIDE_CINNABAR_BLUE
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 16
	call Common_EventScript_SetGymTrainers_hns
	closemessage
	setflag FLAG_HIDE_LEAGUE_BLACKBELT
	clearflag FLAG_HIDE_CINNABAR_BLAINE
	setvar VAR_OAK_MT_SILVER_CALL, 1
	release
	end

ViridianCity_Gym_EventScript_BlueNotReady::
	msgbox ViridianCity_Gym_Text_BlueNotReady, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_VIRIDIAN_BLUE
	removeobject LOCALID_VIRIDIAN_BLUE
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

ViridianCity_Gym_EventScript_BlueGotoDojo::
	call ViridianCity_Gym_EventScript_PRUReward
	msgbox ViridianCity_Gym_Text_BlueGotoDojo, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_VIRIDIAN_BLUE
	setflag FLAG_HIDE_CINNABAR_BLUE
	clearflag FLAG_HIDE_DOJO_BLUE
	removeobject LOCALID_VIRIDIAN_BLUE
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

ViridianCity_Gym_Text_BlueNotReady:
	.string "BLUE: You're early.\p"
	.string "VIRIDIAN is KANTO's final GYM.\p"
	.string "Beat the other seven LEADERS first.\n"
	.string "Start with BROCK in PEWTER CITY.$"

ViridianCity_Gym_Text_BlueGotoDojo:
	.string "BLUE: Ready for a rematch?\p"
	.string "Meet me at the FIGHTING DOJO\n"
	.string "in SAFFRON CITY!$"

ViridianCity_Gym_Text_LeaderBlue_Before:
	.string "BLUE: Yo! Finally got here, huh?\p"
	.string "I wasn't in the mood at CINNABAR,\p"
	.string "but now I'm ready to battle you.\p"
	.string "…\p"
	.string "You're telling me you conquered all\n"
	.string "the GYMS in JOHTO?\p"
	.string "Heh! JOHTO's GYMS must be pretty\n"
	.string "pathetic then.\p"
	.string "Hey, don't worry about it.\p"
	.string "I'll know if you are good or not by\n"
	.string "battling you right now.\p"
	.string "Ready, JOHTO CHAMP?$"

ViridianCity_Gym_Text_LeaderBlue_Win:
	.string "BLUE: What?\p"
	.string "How the heck did I lose to you?\p"
	.string "…\p"
	.string "Tch, all right… Here, take this--it's\n"
	.string "EARTHBADGE.$"

ViridianCity_Gym_Text_ReceivedEarthBadge:
	.string "{PLAYER} received EARTHBADGE.$"

ViridianCity_Gym_Text_LeaderBlue_After:
	.string "BLUE: …\p"
	.string "All right, I was wrong. You're the\n"
	.string "real deal. You are a good trainer.\p"
	.string "But I'm going to beat you someday.\p"
	.string "Don't you forget it!$"

ViridianCity_Gym_Text_LeaderBlue_GiveTM:
	.string "Take this with you.$"

ViridianCity_Gym_Text_LeaderBlue_ExplainTM:
	.string "That's TRICK ROOM.\p"
	.string "All POKEMON in battle will change speed.\n"
	.string "Slow goes first. Fast goes last.\p"
	.string "Use it to turn a battle on its head.$"

ViridianCity_Gym_Text_LeaderBlue_Epilogue:
	.string "BLUE: Listen, you.\p"
	.string "You'd better not lose until I beat\n"
	.string "you. Got it?$"


ViridianCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_GymGuyAfter
	msgbox ViridianCity_Gym_Text_Guide, MSGBOX_NPC
	end

ViridianCity_Gym_EventScript_GymGuyAfter::
	lock
	faceplayer
	call ViridianCity_Gym_EventScript_PRUReward
	msgbox ViridianCity_Gym_Text_Guide_Win, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_Gym_Text_Guide:
	.string "Yo, CHAMP in making!\p"
	.string "VIRIDIAN is KANTO's final GYM.\p"
	.string "If you've just arrived from JOHTO,\n"
	.string "head north to PEWTER CITY first.\p"
	.string "A good route is PEWTER, CERULEAN,\n"
	.string "VERMILION, SAFFRON and CELADON,\p"
	.string "then FUCHSIA, SEAFOAM and finally\n"
	.string "back here to VIRIDIAN.\p"
	.string "With seven KANTO BADGES, find BLUE\n"
	.string "on CINNABAR ISLAND.$"

ViridianCity_Gym_Text_Guide_Win:
	.string "Man, you are truly tough…\p"
	.string "That was a heck of an inspirational\n"
	.string "battle. It brought tears to my eyes.$"


ViridianCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE16_GET, ViridianCity_Gym_EventScript_GymStatuePostVictory
	msgbox ViridianCity_Gym_Text_GymStatue
	releaseall
	end

ViridianCity_Gym_EventScript_GymStatuePostVictory::
	msgbox ViridianCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

ViridianCity_Gym_Text_GymStatue::
    .string "VIRIDIAN POKéMON GYM\n"
    .string "LEADER: BLUE\p"
	.string "WINNING TRAINERS:\n"
	.string "BLUE, RED$"

ViridianCity_Gym_Text_GymStatuePlayerWon::
    .string "VIRIDIAN POKéMON GYM\n"
    .string "LEADER: BLUE\p"
    .string "WINNING TRAINERS:\n"
	.string "BLUE, RED, {PLAYER}$"

@ PRU first-clear Gym bonus. Do not consume reward flag with a full BAG.
@ Previously defeated leaders can still award the bonus on return.
ViridianCity_Gym_EventScript_PRUReward::
	goto_if_set FLAG_PRU_KANTO_GYM_REWARD_BLUE, ViridianCity_Gym_EventScript_PRURewardDone
	msgbox ViridianCity_Gym_Text_PRURewardIntro, MSGBOX_DEFAULT
	giveitem ITEM_CHOICE_BAND
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_Gym_EventScript_PRURewardBagFull
	addmoney 10000
	setflag FLAG_PRU_KANTO_GYM_REWARD_BLUE
	msgbox ViridianCity_Gym_Text_PRURewardMoney, MSGBOX_DEFAULT
ViridianCity_Gym_EventScript_PRURewardDone:
	return
ViridianCity_Gym_EventScript_PRURewardBagFull:
	msgbox ViridianCity_Gym_Text_PRURewardBagFull, MSGBOX_DEFAULT
	return

ViridianCity_Gym_Text_PRURewardIntro:
	.string "Your bonus prize for defeating\n"
	.string "the GYM LEADER!$"

ViridianCity_Gym_Text_PRURewardMoney:
	.string "You also received 10,000 in\n"
	.string "GYM prize money!$"

ViridianCity_Gym_Text_PRURewardBagFull:
	.string "Your BAG is full! Make some room\n"
	.string "and come back for your prize.$"


@ Giovanni is an additional late-game recovery boss; BLUE's Gym battle
@ and the Route 22 father/son cutscene are never replaced.
ViridianCity_Gym_EventScript_PRUHeistSync::
	setflag FLAG_PRU_HIDE_HEIST_GIOVANNI
	goto_if_unset FLAG_PRU_HEIST_STARTED, ViridianCity_Gym_EventScript_PRUHeistSyncDone
	goto_if_set FLAG_PRU_HEIST_GIOVANNI, ViridianCity_Gym_EventScript_PRUHeistSyncDone
	goto_if_unset FLAG_PRU_HEIST_BROCK, ViridianCity_Gym_EventScript_PRUHeistSyncDone
	goto_if_unset FLAG_PRU_HEIST_MISTY, ViridianCity_Gym_EventScript_PRUHeistSyncDone
	goto_if_unset FLAG_PRU_HEIST_SURGE, ViridianCity_Gym_EventScript_PRUHeistSyncDone
	goto_if_unset FLAG_PRU_HEIST_ERIKA, ViridianCity_Gym_EventScript_PRUHeistSyncDone
	goto_if_unset FLAG_PRU_HEIST_JANINE, ViridianCity_Gym_EventScript_PRUHeistSyncDone
	goto_if_unset FLAG_PRU_HEIST_SABRINA, ViridianCity_Gym_EventScript_PRUHeistSyncDone
	goto_if_unset FLAG_PRU_HEIST_BLAINE, ViridianCity_Gym_EventScript_PRUHeistSyncDone
	clearflag FLAG_PRU_HIDE_HEIST_GIOVANNI
ViridianCity_Gym_EventScript_PRUHeistSyncDone::
	return

ViridianCity_Gym_EventScript_PRUHeistGiovanni::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_HEIST_STARTED, ViridianCity_Gym_EventScript_PRUHeistNotReady
	goto_if_set FLAG_PRU_HEIST_GIOVANNI, ViridianCity_Gym_EventScript_PRUHeistNotReady
	goto_if_unset FLAG_PRU_HEIST_BROCK, ViridianCity_Gym_EventScript_PRUHeistNotReady
	goto_if_unset FLAG_PRU_HEIST_MISTY, ViridianCity_Gym_EventScript_PRUHeistNotReady
	goto_if_unset FLAG_PRU_HEIST_SURGE, ViridianCity_Gym_EventScript_PRUHeistNotReady
	goto_if_unset FLAG_PRU_HEIST_ERIKA, ViridianCity_Gym_EventScript_PRUHeistNotReady
	goto_if_unset FLAG_PRU_HEIST_JANINE, ViridianCity_Gym_EventScript_PRUHeistNotReady
	goto_if_unset FLAG_PRU_HEIST_SABRINA, ViridianCity_Gym_EventScript_PRUHeistNotReady
	goto_if_unset FLAG_PRU_HEIST_BLAINE, ViridianCity_Gym_EventScript_PRUHeistNotReady
	msgbox ViridianCity_Gym_Text_PRUHeistGiovanniIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_HEIST_GIOVANNI_HNS, ViridianCity_Gym_Text_PRUHeistGiovanniWin
	setflag FLAG_PRU_HEIST_GIOVANNI
	setflag FLAG_PRU_HIDE_HEIST_GIOVANNI
	@ Armour cracks; do not duplicate a Mewtwo caught on an old save.
	specialvar VAR_RESULT, PruIsMewtwoCaught
	goto_if_eq VAR_RESULT, TRUE, ViridianCity_Gym_EventScript_PRUMewtwoAlreadyCaught
	clearflag FLAG_HIDE_MEWTWO
ViridianCity_Gym_EventScript_PRUMewtwoAlreadyCaught::
	msgbox ViridianCity_Gym_Text_PRUHeistGiovanniAfter, MSGBOX_DEFAULT
	@ Giovanni vanishes in a burst of white light after his final speech.
	closemessage
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject 3
	fadescreenswapbuffers FADE_FROM_WHITE
	release
	end

ViridianCity_Gym_EventScript_PRUHeistNotReady::
	msgbox ViridianCity_Gym_Text_PRUHeistNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_Gym_Text_PRUHeistGiovanniIntro:
	.string "GIOVANNI: BLUE is gone.\p"
	.string "I have reclaimed VIRIDIAN GYM.\n"
	.string "I am KANTO's EIGHTH LEADER!\p"
	.string "ROCKET rebuilt ancient fossils\n"
	.string "using forbidden RELIC power.\p"
	.string "My final experiment wears\n"
	.string "armour no attack can break!$"

ViridianCity_Gym_Text_PRUHeistGiovanniWin:
	.string "GIOVANNI: Impossible!\n"
	.string "Even Armoured MEWTWO fell!$"

ViridianCity_Gym_Text_PRUHeistGiovanniAfter:
	.string "MEWTWO's armour shatters!\p"
	.string "Freed from ROCKET's control,\n"
	.string "MEWTWO returns to Cerulean Cave.\p"
	.string "GIOVANNI returns the final\n"
	.string "KANTO BADGE. INDIGO is open!$"

ViridianCity_Gym_Text_PRUHeistNotReady:
	.string "GIOVANNI: Come back after all\n"
	.string "seven KANTO GYM rematches.$"
