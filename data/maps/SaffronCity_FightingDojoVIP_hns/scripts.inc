SaffronCity_FightingDojoVIP_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_FightingDojoVIP_OnTransition
	.byte 0

SaffronCity_FightingDojoVIP_OnTransition::
	call SaffronCity_FightingDojoVIP_EventScript_PRUHeistSync
	end

SaffronCity_FightingDojoVIP_EventScript_PRUHeistSync::
	@ During the heist all undefeated Kanto leaders stand on the main stage.
	@ The original VIP rematches are still available outside this storyline.
	goto_if_unset FLAG_PRU_HEIST_STARTED, SaffronCity_FightingDojoVIP_EventScript_PRUHeistSyncDone
	goto_if_set FLAG_PRU_HEIST_GIOVANNI, SaffronCity_FightingDojoVIP_EventScript_PRUHeistSyncFinished
	setflag FLAG_HIDE_DOJO_BLUE
	setflag FLAG_HIDE_DOJO_BROCK
	setflag FLAG_HIDE_DOJO_MISTY
	setflag FLAG_HIDE_DOJO_SURGE
	setflag FLAG_HIDE_DOJO_ERIKA
	setflag FLAG_HIDE_DOJO_JANINE
	setflag FLAG_HIDE_DOJO_SABRINA
	setflag FLAG_HIDE_DOJO_BLAINE
	goto_if_set FLAG_PRU_HEIST_BROCK, SaffronCity_FightingDojoVIP_EventScript_PRUAfterBrock
	clearflag FLAG_HIDE_DOJO_BROCK
SaffronCity_FightingDojoVIP_EventScript_PRUAfterBrock::
	goto_if_set FLAG_PRU_HEIST_MISTY, SaffronCity_FightingDojoVIP_EventScript_PRUAfterMisty
	clearflag FLAG_HIDE_DOJO_MISTY
SaffronCity_FightingDojoVIP_EventScript_PRUAfterMisty::
	goto_if_set FLAG_PRU_HEIST_SURGE, SaffronCity_FightingDojoVIP_EventScript_PRUAfterSurge
	clearflag FLAG_HIDE_DOJO_SURGE
SaffronCity_FightingDojoVIP_EventScript_PRUAfterSurge::
	goto_if_set FLAG_PRU_HEIST_ERIKA, SaffronCity_FightingDojoVIP_EventScript_PRUAfterErika
	clearflag FLAG_HIDE_DOJO_ERIKA
SaffronCity_FightingDojoVIP_EventScript_PRUAfterErika::
	goto_if_set FLAG_PRU_HEIST_JANINE, SaffronCity_FightingDojoVIP_EventScript_PRUAfterJanine
	clearflag FLAG_HIDE_DOJO_JANINE
SaffronCity_FightingDojoVIP_EventScript_PRUAfterJanine::
	goto_if_set FLAG_PRU_HEIST_SABRINA, SaffronCity_FightingDojoVIP_EventScript_PRUAfterSabrina
	clearflag FLAG_HIDE_DOJO_SABRINA
SaffronCity_FightingDojoVIP_EventScript_PRUAfterSabrina::
	goto_if_set FLAG_PRU_HEIST_BLAINE, SaffronCity_FightingDojoVIP_EventScript_PRUAfterBlaine
	clearflag FLAG_HIDE_DOJO_BLAINE
SaffronCity_FightingDojoVIP_EventScript_PRUAfterBlaine::
	return
SaffronCity_FightingDojoVIP_EventScript_PRUHeistSyncFinished::
	clearflag FLAG_HIDE_DOJO_BROCK
	clearflag FLAG_HIDE_DOJO_MISTY
	clearflag FLAG_HIDE_DOJO_SURGE
	clearflag FLAG_HIDE_DOJO_ERIKA
	clearflag FLAG_HIDE_DOJO_JANINE
	clearflag FLAG_HIDE_DOJO_SABRINA
	clearflag FLAG_HIDE_DOJO_BLAINE
	clearflag FLAG_HIDE_DOJO_BLUE
SaffronCity_FightingDojoVIP_EventScript_PRUHeistSyncDone::
	return

@ The seven leader battles happen here during the Badge Heist, once each.
@ The existing Dojo nurse remains available after each battle.

SaffronCity_FightingDojoVIP_EventScript_PRUHeistBrock::
	goto_if_set FLAG_PRU_HEIST_BROCK, SaffronCity_FightingDojoVIP_EventScript_PRUAlreadyBeaten
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_HEIST_BROCK_HNS, SaffronCity_FightingDojoVIP_Text_PRUHeistDefeat
	setflag FLAG_PRU_HEIST_BROCK
	setflag FLAG_HIDE_DOJO_BROCK
	removeobject 2
	removeobject 28 @ Onix leaves the battle stage with Brock.
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNext, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_PRUHeistMisty::
	goto_if_unset FLAG_PRU_HEIST_BROCK, SaffronCity_FightingDojoVIP_EventScript_PRUNotReady
	goto_if_set FLAG_PRU_HEIST_MISTY, SaffronCity_FightingDojoVIP_EventScript_PRUAlreadyBeaten
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_HEIST_MISTY_HNS, SaffronCity_FightingDojoVIP_Text_PRUHeistDefeat
	setflag FLAG_PRU_HEIST_MISTY
	setflag FLAG_HIDE_DOJO_MISTY
	removeobject 1
	removeobject 23 @ Starmie leaves with Misty.
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNext, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_PRUHeistSurge::
	goto_if_unset FLAG_PRU_HEIST_MISTY, SaffronCity_FightingDojoVIP_EventScript_PRUNotReady
	goto_if_set FLAG_PRU_HEIST_SURGE, SaffronCity_FightingDojoVIP_EventScript_PRUAlreadyBeaten
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_HEIST_SURGE_HNS, SaffronCity_FightingDojoVIP_Text_PRUHeistDefeat
	setflag FLAG_PRU_HEIST_SURGE
	setflag FLAG_HIDE_DOJO_SURGE
	removeobject 3
	removeobject 19 @ Raichu leaves with Surge.
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNext, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_PRUHeistErika::
	goto_if_unset FLAG_PRU_HEIST_SURGE, SaffronCity_FightingDojoVIP_EventScript_PRUNotReady
	goto_if_set FLAG_PRU_HEIST_ERIKA, SaffronCity_FightingDojoVIP_EventScript_PRUAlreadyBeaten
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_HEIST_ERIKA_HNS, SaffronCity_FightingDojoVIP_Text_PRUHeistDefeat
	setflag FLAG_PRU_HEIST_ERIKA
	setflag FLAG_HIDE_DOJO_ERIKA
	removeobject 4
	removeobject 24 @ Victreebel leaves with Erika.
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNext, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_PRUHeistJanine::
	goto_if_unset FLAG_PRU_HEIST_ERIKA, SaffronCity_FightingDojoVIP_EventScript_PRUNotReady
	goto_if_set FLAG_PRU_HEIST_JANINE, SaffronCity_FightingDojoVIP_EventScript_PRUAlreadyBeaten
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_HEIST_JANINE_HNS, SaffronCity_FightingDojoVIP_Text_PRUHeistDefeat
	setflag FLAG_PRU_HEIST_JANINE
	setflag FLAG_HIDE_DOJO_JANINE
	removeobject 5
	removeobject 30 @ Muk leaves with Janine.
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNext, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_PRUHeistSabrina::
	goto_if_unset FLAG_PRU_HEIST_JANINE, SaffronCity_FightingDojoVIP_EventScript_PRUNotReady
	goto_if_set FLAG_PRU_HEIST_SABRINA, SaffronCity_FightingDojoVIP_EventScript_PRUAlreadyBeaten
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_HEIST_SABRINA_HNS, SaffronCity_FightingDojoVIP_Text_PRUHeistDefeat
	setflag FLAG_PRU_HEIST_SABRINA
	setflag FLAG_HIDE_DOJO_SABRINA
	removeobject 6
	removeobject 27 @ Kadabra leaves with Sabrina.
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNext, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_PRUHeistBlaine::
	goto_if_unset FLAG_PRU_HEIST_SABRINA, SaffronCity_FightingDojoVIP_EventScript_PRUNotReady
	goto_if_set FLAG_PRU_HEIST_BLAINE, SaffronCity_FightingDojoVIP_EventScript_PRUAlreadyBeaten
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRU_HEIST_BLAINE_HNS, SaffronCity_FightingDojoVIP_Text_PRUHeistDefeat
	setflag FLAG_PRU_HEIST_BLAINE
	setflag FLAG_HIDE_DOJO_BLAINE
	removeobject 7
	removeobject 34 @ Magmar leaves with Blaine.
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistGiovanni, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_PRUNotReady::
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_PRUAlreadyBeaten::
	msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistAlready, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_Text_PRUHeistChallenge:
	.string "ROCKET stole your KANTO BADGES!\p"
	.string "Win our full-strength rematches\l"
	.string "to take them back! Ready?$"

SaffronCity_FightingDojoVIP_Text_PRUHeistDefeat:
	.string "An excellent battle!$"

SaffronCity_FightingDojoVIP_Text_PRUHeistNext:
	.string "Your next KANTO LEADER awaits\l"
	.string "here in the DOJO. Heal up!$"

SaffronCity_FightingDojoVIP_Text_PRUHeistGiovanni:
	.string "BLAINE: That's seven! But\n"
	.string "BLUE has disappeared...\p"
	.string "Who's KANTO's eighth LEADER?\l"
	.string "Try VIRIDIAN GYM!$"

SaffronCity_FightingDojoVIP_Text_PRUHeistNotReady:
	.string "Face the other KANTO LEADERS\l"
	.string "first, in the proper order.$"

SaffronCity_FightingDojoVIP_Text_PRUHeistAlready:
	.string "Our BADGE rematch is over.\l"
	.string "Find the next leader!$"

SaffronCity_FightingDojoVIP_EventScript_Nurse::
	lock
	faceplayer
	specialvar VAR_RESULT, IsPokecenterChallengeActivated
	goto_if_eq VAR_RESULT, TRUE, SSAquaRooms_EventScript_Bed_PokecenterChallenge
	msgbox SaffronCity_FightingDojoVIP_Text_Nurse1, MSGBOX_NPC
	waitmessage
	fadescreen 0x1
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	fadescreen 0x0
	msgbox SaffronCity_FightingDojoVIP_Text_Nurse2, MSGBOX_NPC
	waitmessage
	release
	end

SaffronCity_FightingDojoVIP_Text_Nurse1:
	.string "Hi! Welcome to the TRAINING DOJO!\n"
	.string "I will heal your POKéMON.$"

SaffronCity_FightingDojoVIP_Text_Nurse2:
	.string "We hope to see you again!$"


SaffronCity_FightingDojoVIP_EventScript_Declined::
	closemessage
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Falkner::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojoVIP_Text_Falkner_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Falkner_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Falkner_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Falkner_Rematch::
	trainerbattle_no_intro TRAINER_FALKNER_2_HNS, SaffronCity_FightingDojoVIP_Text_Falkner_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Falkner_PostOBC::
	trainerbattle_no_intro TRAINER_FALKNER_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Falkner_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Bugsy::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojoVIP_Text_Bugsy_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Bugsy_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Bugsy_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Bugsy_Rematch::
	trainerbattle_no_intro TRAINER_BUGSY_2_HNS, SaffronCity_FightingDojoVIP_Text_Bugsy_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Bugsy_PostOBC::
	trainerbattle_no_intro TRAINER_BUGSY_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Bugsy_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Whitney::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojoVIP_Text_Whitney_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Whitney_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Whitney_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Whitney_Rematch::
	trainerbattle_no_intro TRAINER_WHITNEY_2_HNS, SaffronCity_FightingDojoVIP_Text_Whitney_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Whitney_PostOBC::
	trainerbattle_no_intro TRAINER_WHITNEY_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Whitney_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Morty::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojoVIP_Text_Morty_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Morty_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Morty_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Morty_Rematch::
	trainerbattle_no_intro TRAINER_MORTY_2_HNS, SaffronCity_FightingDojoVIP_Text_Morty_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Morty_PostOBC::
	trainerbattle_no_intro TRAINER_MORTY_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Morty_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Chuck::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojoVIP_Text_Chuck_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Chuck_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Chuck_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Chuck_Rematch::
	trainerbattle_no_intro TRAINER_CHUCK_2_HNS, SaffronCity_FightingDojoVIP_Text_Chuck_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Chuck_PostOBC::
	trainerbattle_no_intro TRAINER_CHUCK_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Chuck_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Jasmine::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojoVIP_Text_Jasmine_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Jasmine_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Jasmine_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Jasmine_Rematch::
	trainerbattle_no_intro TRAINER_JASMINE_2_HNS, SaffronCity_FightingDojoVIP_Text_Jasmine_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Jasmine_PostOBC::
	trainerbattle_no_intro TRAINER_JASMINE_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Jasmine_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Pryce::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojoVIP_Text_Pryce_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Pryce_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Pryce_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Pryce_Rematch::
	trainerbattle_no_intro TRAINER_PRYCE_2_HNS, SaffronCity_FightingDojoVIP_Text_Pryce_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Pryce_PostOBC::
	trainerbattle_no_intro TRAINER_PRYCE_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Pryce_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Clair::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojoVIP_Text_Clair_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Clair_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Clair_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Clair_Rematch::
	trainerbattle_no_intro TRAINER_CLAIR_2_HNS, SaffronCity_FightingDojoVIP_Text_Clair_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Clair_PostOBC::
	trainerbattle_no_intro TRAINER_CLAIR_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Clair_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Brock::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_HEIST_STARTED, SaffronCity_FightingDojoVIP_EventScript_Brock_Normal
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, SaffronCity_FightingDojoVIP_EventScript_PRUHeistBrock
SaffronCity_FightingDojoVIP_EventScript_Brock_Normal::
	msgbox SaffronCity_FightingDojoVIP_Text_Brock_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Brock_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Brock_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Brock_Rematch::
	trainerbattle_no_intro TRAINER_BROCK_HNS, SaffronCity_FightingDojoVIP_Text_Brock_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Brock_PostOBC::
	trainerbattle_no_intro TRAINER_BROCK_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Brock_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Misty::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_HEIST_STARTED, SaffronCity_FightingDojoVIP_EventScript_Misty_Normal
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, SaffronCity_FightingDojoVIP_EventScript_PRUHeistMisty
SaffronCity_FightingDojoVIP_EventScript_Misty_Normal::
	msgbox SaffronCity_FightingDojoVIP_Text_Misty_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Misty_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Misty_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Misty_Rematch::
	trainerbattle_no_intro TRAINER_MISTY_HNS, SaffronCity_FightingDojoVIP_Text_Misty_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Misty_PostOBC::
	trainerbattle_no_intro TRAINER_MISTY_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Misty_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Surge::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_HEIST_STARTED, SaffronCity_FightingDojoVIP_EventScript_Surge_Normal
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, SaffronCity_FightingDojoVIP_EventScript_PRUHeistSurge
SaffronCity_FightingDojoVIP_EventScript_Surge_Normal::
	msgbox SaffronCity_FightingDojoVIP_Text_Surge_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Surge_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Surge_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Surge_Rematch::
	trainerbattle_no_intro TRAINER_LTSURGE_HNS, SaffronCity_FightingDojoVIP_Text_Surge_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Surge_PostOBC::
	trainerbattle_no_intro TRAINER_LTSURGE_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Surge_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Erika::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_HEIST_STARTED, SaffronCity_FightingDojoVIP_EventScript_Erika_Normal
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, SaffronCity_FightingDojoVIP_EventScript_PRUHeistErika
SaffronCity_FightingDojoVIP_EventScript_Erika_Normal::
	msgbox SaffronCity_FightingDojoVIP_Text_Erika_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Erika_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Erika_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Erika_Rematch::
	trainerbattle_no_intro TRAINER_ERIKA_HNS, SaffronCity_FightingDojoVIP_Text_Erika_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Erika_PostOBC::
	trainerbattle_no_intro TRAINER_ERIKA_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Erika_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Janine::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_HEIST_STARTED, SaffronCity_FightingDojoVIP_EventScript_Janine_Normal
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, SaffronCity_FightingDojoVIP_EventScript_PRUHeistJanine
SaffronCity_FightingDojoVIP_EventScript_Janine_Normal::
	msgbox SaffronCity_FightingDojoVIP_Text_Janine_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Janine_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Janine_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Janine_Rematch::
	trainerbattle_no_intro TRAINER_JANINE_HNS, SaffronCity_FightingDojoVIP_Text_Janine_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Janine_PostOBC::
	trainerbattle_no_intro TRAINER_JANINE_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Janine_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Sabrina::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_HEIST_STARTED, SaffronCity_FightingDojoVIP_EventScript_Sabrina_Normal
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, SaffronCity_FightingDojoVIP_EventScript_PRUHeistSabrina
SaffronCity_FightingDojoVIP_EventScript_Sabrina_Normal::
	msgbox SaffronCity_FightingDojoVIP_Text_Sabrina_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Sabrina_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Sabrina_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Sabrina_Rematch::
	trainerbattle_no_intro TRAINER_SABRINA_HNS, SaffronCity_FightingDojoVIP_Text_Sabrina_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Sabrina_PostOBC::
	trainerbattle_no_intro TRAINER_SABRINA_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Sabrina_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Blaine::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_HEIST_STARTED, SaffronCity_FightingDojoVIP_EventScript_Blaine_Normal
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, SaffronCity_FightingDojoVIP_EventScript_PRUHeistBlaine
SaffronCity_FightingDojoVIP_EventScript_Blaine_Normal::
	msgbox SaffronCity_FightingDojoVIP_Text_Blaine_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Blaine_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Blaine_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Blaine_Rematch::
	trainerbattle_no_intro TRAINER_BLAINE_HNS, SaffronCity_FightingDojoVIP_Text_Blaine_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Blaine_PostOBC::
	trainerbattle_no_intro TRAINER_BLAINE_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Blaine_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Blue::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojoVIP_Text_Blue_Rematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojoVIP_EventScript_Declined
	closemessage
	goto_if_unset FLAG_IS_KANTO_CHAMPION, SaffronCity_FightingDojoVIP_EventScript_Blue_Rematch
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SaffronCity_FightingDojoVIP_EventScript_Blue_PostOBC

SaffronCity_FightingDojoVIP_EventScript_Blue_Rematch::
	trainerbattle_no_intro TRAINER_BLUE_HNS, SaffronCity_FightingDojoVIP_Text_Blue_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_FightingDojoVIP_EventScript_Blue_PostOBC::
	trainerbattle_no_intro TRAINER_BLUE_POSTOBC_HNS, SaffronCity_FightingDojoVIP_Text_Blue_RematchDefeat
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	givebp 10
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_DEFAULT
	closemessage
	release
	end

@===============MONS===============================================================================================================

SaffronCity_FightingDojoVIP_EventScript_Scizor::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SCIZOR, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Scizor, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Scizor:
	.string "SCIZOR: Scii-zor!$"

SaffronCity_FightingDojoVIP_EventScript_Miltank::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Miltank, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Miltank:
	.string "MILTANK: MooOOO!$"

SaffronCity_FightingDojoVIP_EventScript_Poliwhirl::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWHIRL, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Poliwhirl, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Poliwhirl:
	.string "POLIWHIRL: Whirl-whirl!$"

SaffronCity_FightingDojoVIP_EventScript_Dewgong::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DEWGONG, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Dewgong, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Dewgong:
	.string "DEWGONG: Goooooong!$"

SaffronCity_FightingDojoVIP_EventScript_Steelix::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_STEELIX, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Steelix, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Steelix:
	.string "STEELIX: GraaAAANk!$"

SaffronCity_FightingDojoVIP_EventScript_Kingdra::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KINGDRA, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Kingdra, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Kingdra:
	.string "KINGDRA: Draaa...$"

SaffronCity_FightingDojoVIP_EventScript_Onix::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ONIX, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Onix, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Onix:
	.string "ONIX: Oooonix!$"

SaffronCity_FightingDojoVIP_EventScript_Starmie::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_STARMIE, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Starmie, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Starmie:
	.string "STARMIE: Hyaaa!$"

SaffronCity_FightingDojoVIP_EventScript_Victreebel::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_VICTREEBEL, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Victreebel, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Victreebel:
	.string "VICTREEBEL: Vreeee!$"

SaffronCity_FightingDojoVIP_EventScript_Muk::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MUK, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Muk, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Muk:
	.string "MUK: Muuuk...$"

SaffronCity_FightingDojoVIP_EventScript_Kadabra::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KADABRA, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Kadabra, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Kadabra:
	.string "KADABRA: Kadabra!$"

SaffronCity_FightingDojoVIP_EventScript_Magmar::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MAGMAR, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Magmar, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Magmar:
	.string "MAGMAR: Magmaaaar!$"

SaffronCity_FightingDojoVIP_EventScript_Raichu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RAICHU, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Raichu, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Raichu:
	.string "RAICHU: Rai-CHU!$"

SaffronCity_FightingDojoVIP_EventScript_Machamp::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHAMP, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojoVIP_Text_Machamp, MSGBOX_DEFAULT
	waitmoncry
	applymovement2 VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SaffronCity_FightingDojoVIP_Text_Machamp:
	.string "MACHAMP: Maa-champ!$"

SaffronCity_FightingDojo_EventScript_Chased::
	msgbox SaffronCity_FightingDojoVIP_Text_Chased, MSGBOX_NPC
	end

SaffronCity_FightingDojoVIP_Text_Chased:
	.string "Help!$"

SaffronCity_FightingDojoVIP_EvetScript_Statue::
	msgbox SaffronCity_FightingDojoVIP_Text_Statue, MSGBOX_SIGN
	end

SaffronCity_FightingDojoVIP_Text_Statue:
	.string "FIGHTING DOJO VIP LOUNGE$"

SaffronCity_FightingDojoVIP_Text_Falkner_Rematch:
	.string "Congratulations on defeating\n"
	.string "the ELITE 4!\p"
	.string "I've been training my\n"
	.string "FLYING-type POKéMON even harder.\p"
	.string "Think you can take on the power\n"
	.string "of the skies again?$"

SaffronCity_FightingDojoVIP_Text_Falkner_RematchDefeat:
	.string "Wow… You beat me again.\p"
	.string "I'm going to train harder to\n"
	.string "become the greatest bird master!$"

SaffronCity_FightingDojoVIP_Text_Bugsy_Rematch:
	.string "Wow, you're the JOHTO CHAMPION\n"
	.string "now!\p"
	.string "Your skills are truly impressive!\p"
	.string "I've been busy with my research.\p"
	.string "I'm ready to show you my new\n"
	.string "findings.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Bugsy_RematchDefeat:
	.string "Wow, you must be an expert\n"
	.string "trainer.\p"
	.string "My research must not be\n"
	.string "complete…$"

SaffronCity_FightingDojoVIP_Text_Whitney_Rematch:
	.string "Hi! It's you!\p"
	.string "Wow, JOHTO CHAMPION now?\p"
	.string "You really are amazing!\p"
	.string "I want to see how strong you are.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Whitney_RematchDefeat:
	.string "Waaaaah!\p"
	.string "Waaaaah!\p"
	.string "…Snivel, hic… …You meanie!$"

SaffronCity_FightingDojoVIP_Text_Morty_Rematch:
	.string "Ah, the JOHTO CHAMPION! Good of\n"
	.string "you to come.\p"
	.string "You've shown your strength and\n"
	.string "skill, but have you improved\l"
	.string "since our last battle?\p"
	.string "I've been training with my\n"
	.string "GHOST-type POKéMON.\p"
	.string "Let's see if you can overcome\n"
	.string "the shadows once again.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Morty_RematchDefeat:
	.string "I'm not good enough yet…\p"
	.string "You have witnessed much more\n"
	.string "than I.\p"
	.string "I envy you for that…$"

SaffronCity_FightingDojoVIP_Text_Chuck_Rematch:
	.string "WAHAHAH! JOHTO CHAMPION!\p"
	.string "You've come back for more!\p"
	.string "I see your skills have improved!\p"
	.string "Ready to see who's stronger?$"

SaffronCity_FightingDojoVIP_Text_Chuck_RematchDefeat:
	.string "Wha? Huh? I lost? Again?$"

SaffronCity_FightingDojoVIP_Text_Jasmine_Rematch:
	.string "…Congratulations, JOHTO\n"
	.string "CHAMPION.\p"
	.string "You have become so strong…\p"
	.string "I wonder if I have improved.\p"
	.string "Would you like to test that?\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Jasmine_RematchDefeat:
	.string "…You are a better trainer than\n"
	.string "me,\p"
	.string "in both skill and kindness.$"

SaffronCity_FightingDojoVIP_Text_Pryce_Rematch:
	.string "Ah, JOHTO CHAMPION!\p"
	.string "Your skills are indeed\n"
	.string "remarkable.\p"
	.string "I am impressed.\p"
	.string "But even now, there is much to\n"
	.string "learn from each other.\p"
	.string "I, PRYCE--the winter trainer--\p"
	.string "still have a few tricks left.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Pryce_RematchDefeat:
	.string "Ah, yet again I'm impressed by\n"
	.string "your prowess.\p"
	.string "With your strong will, I know\n"
	.string "you will overcome all life's\l"
	.string "obstacles.$"

SaffronCity_FightingDojoVIP_Text_Clair_Rematch:
	.string "You did it, huh?\p"
	.string "You are now the JOHTO CHAMP.\p"
	.string "You've proven your strength but\n"
	.string "can you handle me again?\p"
	.string "As a Dragon Master, I won't hold\n"
	.string "back.\p"
	.string "Not this time.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Clair_RematchDefeat:
	.string "I lost?\p"
	.string "Again?\p"
	.string "I don't believe it. There must\n"
	.string "be some mistake…$"

SaffronCity_FightingDojoVIP_Text_Brock_Rematch:
	.string "BROCK: Hey there, {PLAYER}!\p"
	.string "I heard you are now the KANTO\n"
	.string "CHAMPION.\p"
	.string "That's incredible!\p"
	.string "You must be even stronger now.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Brock_RematchDefeat:
	.string "BROCK: Your POKéMON once again\n"
	.string "overcame my rock-hard defense…$"

SaffronCity_FightingDojoVIP_Text_Misty_Rematch:
	.string "MISTY: Wow, you're the KANTO\n"
	.string "CHAMPION now!\p"
	.string "That's amazing! You've come a\n"
	.string "long way, {PLAYER}.\p"
	.string "But I'm not backing down.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Misty_RematchDefeat:
	.string "MISTY: You really are good…$"

SaffronCity_FightingDojoVIP_Text_Surge_Rematch:
	.string "SURGE: So, you're now KANTO\n"
	.string "CHAMPION!\p"
	.string "Impressive work, kid! But don't\n"
	.string "think I'm done!\p"
	.string "How about we have a go again?$"

SaffronCity_FightingDojoVIP_Text_Surge_RematchDefeat:
	.string "SURGE: Arrrgh! You're still just\n"
	.string "as strong!$"

SaffronCity_FightingDojoVIP_Text_Erika_Rematch:
	.string "ERIKA: Oh, hello.\p"
	.string "What a surprise, CHAMPION!\p"
	.string "It's so lovely to see you again.\p"
	.string "Your journey must have been so\n"
	.string "exciting.\p"
	.string "Even champions enjoy a challenge.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Erika_RematchDefeat:
	.string "ERIKA: Losing still leaves a\n"
	.string "bitter aftertaste…\p"
	.string "But knowing that there are strong\n"
	.string "trainers spurs me to do better…$"

SaffronCity_FightingDojoVIP_Text_Sabrina_Rematch:
	.string "SABRINA: Ah, the CHAMPION.\p"
	.string "I sensed your return.\p"
	.string "Your power has grown immensely.\p"
	.string "Even now, I feel your aura.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Sabrina_RematchDefeat:
	.string "SABRINA: Your love for your\n"
	.string "POKéMON again overwhelmed my\l"
	.string "psychic power…$"

SaffronCity_FightingDojoVIP_Text_Janine_Rematch:
	.string "Fufufufu…\p"
	.string "Wow, you did it!\p"
	.string "You're the CHAMPION now!\p"
	.string "I'm so proud of you! But don't\n"
	.string "think I'll go easy on you.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Janine_RematchDefeat:
	.string "JANINE: You're still just as\n"
	.string "tough!\p"
	.string "You definitely won…$"

SaffronCity_FightingDojoVIP_Text_Blaine_Rematch:
	.string "BLAINE: Whoa!\p"
	.string "I see you've become the KANTO\n"
	.string "CHAMPION!\p"
	.string "That's blazing!\p"
	.string "Your skills are top-notch.\p"
	.string "I'm always up for a battle.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Blaine_RematchDefeat:
	.string "BLAINE: Your skills are truly\n"
	.string "fiery!\p"
	.string "You've burned right through my\n"
	.string "defenses.$"

SaffronCity_FightingDojoVIP_Text_Blue_Rematch:
	.string "BLUE: Well, well. CHAMPION!\p"
	.string "Looks like you've come a long way.\p"
	.string "I used to have that title too,\n"
	.string "you know. But I won't go easy.\p"
	.string "Let's see if you can keep it up.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_FightingDojoVIP_Text_Blue_RematchDefeat:
	.string "BLUE: What?\p"
	.string "How the heck did I lose again?$"

