Route34_DayCare_hns_MapScripts::
	.byte 0

Route34_DayCare_Bookshelf1::
	lock
	msgbox Route34_DayCare_Text_Bookshelf1, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE1_WINDOW
	release
	end

Route34_DayCare_Bookshelf2::
	lock
	msgbox Route34_DayCare_Text_Bookshelf2, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE2_WINDOW
	release
	end

Route34_DayCare_Bookshelf3::
	lock
	msgbox Route34_DayCare_Text_Bookshelf3, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE3_WINDOW
	release
	end

Route34_DayCare_Bookshelf4::
	lock
	msgbox Route34_DayCare_Text_Bookshelf4, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE4_WINDOW
	release
	end

Route34_DayCare_Text_Bookshelf1:
	.string "A BABY POKéMON encyclopedia!\p"
	.string "VOLUME 1: ALL ABOUT ABILITIES$"

Route34_DayCare_Text_Bookshelf2:
	.string "A BABY POKéMON encyclopedia!\p"
	.string "VOLUME 2: TYPICAL TYPES$"

Route34_DayCare_Text_Bookshelf3:
	.string "A BABY POKéMON encyclopedia!\p"
	.string "VOLUME 3: BABIES' CRIES$"

Route34_DayCare_Text_Bookshelf4:
	.string "A BABY POKéMON encyclopedia!\p"
	.string "VOLUME 4: ADORABLE ACTIONS$"

@ PRU Mystery Egg seller. Separate from the existing one-time Odd Egg
@ and free Move Expert; no flags are set, and eggs can be bought repeatedly.
Route34_DayCare_EventScript_MysteryEggSeller::
	lock
	faceplayer
	msgbox Route34_DayCare_Text_MysteryEggOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route34_DayCare_EventScript_MysteryEggDecline
	@ The special validates party cap, funds and hatchable species, gives the
	@ egg, then charges exactly 5000; no payment on failure or cancellation.
	specialvar VAR_RESULT, PruBuyDaycareMysteryEgg
	switch VAR_RESULT
	case 0, Route34_DayCare_EventScript_MysteryEggSuccess
	case 1, Route34_DayCare_EventScript_MysteryEggPartyFull
	case 2, Route34_DayCare_EventScript_MysteryEggNoMoney
	goto Route34_DayCare_EventScript_MysteryEggUnavailable

Route34_DayCare_EventScript_MysteryEggSuccess::
	playfanfare MUS_HG_OBTAIN_EGG
	message Route34_DayCare_Text_MysteryEggReceived
	waitfanfare
	waitmessage
	closemessage
	release
	end

Route34_DayCare_EventScript_MysteryEggPartyFull::
	msgbox Route34_DayCare_Text_MysteryEggPartyFull, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_MysteryEggNoMoney::
	msgbox Route34_DayCare_Text_MysteryEggNoMoney, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_MysteryEggUnavailable::
	msgbox Route34_DayCare_Text_MysteryEggUnavailable, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_MysteryEggDecline::
	msgbox Route34_DayCare_Text_MysteryEggDecline, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_Text_MysteryEggOffer:
	.string "I sell MYSTERY EGGS!\p"
	.string "For ¥5,000, your EGG could hold\n"
	.string "one of NINE classic STARTERS!\p"
	.string "Would you like one?$"

Route34_DayCare_Text_MysteryEggReceived:
	.string "You received a MYSTERY EGG!\n"
	.string "Take good care of it!$"

Route34_DayCare_Text_MysteryEggPartyFull:
	.string "Your party has no room,\n"
	.string "even with your challenge limit.\p"
	.string "Make space and come back!$"

Route34_DayCare_Text_MysteryEggNoMoney:
	.string "You need ¥5,000 for one EGG.\n"
	.string "Come back when you have it!$"

Route34_DayCare_Text_MysteryEggUnavailable:
	.string "Sorry, that EGG isn't ready.\n"
	.string "You haven't been charged.$"

Route34_DayCare_Text_MysteryEggDecline:
	.string "No problem! My EGG stock\n"
	.string "is always changing. Come back!$"


Route34_DayCare_EventScript_Clerk::
	lock
	faceplayer
	msgbox Route34_DayCare_Text_ClerkBefore, MSGBOX_DEFAULT
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	getpartysize
	goto_if_eq VAR_RESULT, VAR_0x8004, Route34_DayCare_EventScript_ClerkPartyFull
	msgbox Route34_DayCare_Text_ClerkQuestion, MSGBOX_DEFAULT
	closemessage
	@ One-word naming keyboard; no Easy Chat word availability restrictions.
	special EnterCode
	waitstate
	specialvar VAR_RESULT, PruCheckOddEggSingleCode
	lock
	faceplayer
	switch VAR_RESULT
	case 0, Route34_DayCare_EventScript_ClerkRejection
	case 1, Route34_DayCare_EventScript_GivePichu
	case 2, Route34_DayCare_EventScript_GiveCleffa
	case 3, Route34_DayCare_EventScript_GiveIgglybuff
	case 4, Route34_DayCare_EventScript_GiveTyrogue
	case 5, Route34_DayCare_EventScript_GiveSmoochum
	case 6, Route34_DayCare_EventScript_GiveElekid
	case 7, Route34_DayCare_EventScript_GiveMagby
	case 8, Route34_DayCare_EventScript_GiveScarabub
	case 9, Route34_DayCare_EventScript_GiveSkarmet
	case 10, Route34_DayCare_EventScript_GiveMootiny
	case 11, Route34_DayCare_EventScript_GiveGemlin
	case 12, Route34_DayCare_EventScript_GiveKan
	case 13, Route34_DayCare_EventScript_GiveChikorita
	case 14, Route34_DayCare_EventScript_GiveCyndaquil
	case 15, Route34_DayCare_EventScript_GiveTotodile
	case 16, Route34_DayCare_EventScript_GiveBulbasaur
	case 17, Route34_DayCare_EventScript_GiveCharmander
	case 18, Route34_DayCare_EventScript_GiveSquirtle
	case 19, Route34_DayCare_EventScript_GiveTreecko
	case 20, Route34_DayCare_EventScript_GiveTorchic
	case 21, Route34_DayCare_EventScript_GiveMudkip
	closemessage
	release
	end

Route34_DayCare_EventScript_GivePichu::
	goto_if_set FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 1
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveCleffa::
	goto_if_set FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 2
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveIgglybuff::
	goto_if_set FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 3
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveTyrogue::
	goto_if_set FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 4
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveSmoochum::
	goto_if_set FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 5
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveElekid::
	goto_if_set FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 6
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveMagby::
	goto_if_set FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 7
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveScarabub::
	goto_if_set FLAG_PRU_SECRET_EGG_SCARABUB, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 8
	setflag FLAG_PRU_SECRET_EGG_SCARABUB
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveSkarmet::
	goto_if_set FLAG_PRU_SECRET_EGG_SKARMET, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 9
	setflag FLAG_PRU_SECRET_EGG_SKARMET
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveMootiny::
	goto_if_set FLAG_PRU_SECRET_EGG_MOOTINY, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 10
	setflag FLAG_PRU_SECRET_EGG_MOOTINY
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveGemlin::
	goto_if_set FLAG_PRU_SECRET_EGG_GEMLIN, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 11
	setflag FLAG_PRU_SECRET_EGG_GEMLIN
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveKan::
	goto_if_set FLAG_PRU_SECRET_EGG_KAN, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 12
	setflag FLAG_PRU_SECRET_EGG_KAN
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveChikorita::
	goto_if_set FLAG_PRU_STARTER_EGG_CHIKORITA, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 13
	setflag FLAG_PRU_STARTER_EGG_CHIKORITA
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveCyndaquil::
	goto_if_set FLAG_PRU_STARTER_EGG_CYNDAQUIL, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 14
	setflag FLAG_PRU_STARTER_EGG_CYNDAQUIL
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveTotodile::
	goto_if_set FLAG_PRU_STARTER_EGG_TOTODILE, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 15
	setflag FLAG_PRU_STARTER_EGG_TOTODILE
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveBulbasaur::
	goto_if_set FLAG_PRU_STARTER_EGG_BULBASAUR, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 16
	setflag FLAG_PRU_STARTER_EGG_BULBASAUR
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveCharmander::
	goto_if_set FLAG_PRU_STARTER_EGG_CHARMANDER, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 17
	setflag FLAG_PRU_STARTER_EGG_CHARMANDER
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveSquirtle::
	goto_if_set FLAG_PRU_STARTER_EGG_SQUIRTLE, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 18
	setflag FLAG_PRU_STARTER_EGG_SQUIRTLE
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveTreecko::
	goto_if_set FLAG_PRU_STARTER_EGG_TREECKO, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 19
	setflag FLAG_PRU_STARTER_EGG_TREECKO
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveTorchic::
	goto_if_set FLAG_PRU_STARTER_EGG_TORCHIC, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 20
	setflag FLAG_PRU_STARTER_EGG_TORCHIC
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_GiveMudkip::
	goto_if_set FLAG_PRU_STARTER_EGG_MUDKIP, Route34_DayCare_EventScript_ClerkAfter
	giveoddegg 21
	setflag FLAG_PRU_STARTER_EGG_MUDKIP
	goto Route34_DayCare_EventScript_Clerk_GaveCustomEgg

Route34_DayCare_EventScript_Clerk_GaveEgg::
	setflag FLAG_RECEIVED_ODD_EGG
	goto Route34_DayCare_EventScript_Clerk_ReceiveEgg

Route34_DayCare_EventScript_Clerk_GaveCustomEgg::
	goto Route34_DayCare_EventScript_Clerk_ReceiveEgg

Route34_DayCare_EventScript_Clerk_ReceiveEgg::
	msgbox Route34_DayCare_Text_TakeCare, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message Route34_DayCare_Text_ReceivedOddEgg
	waitfanfare
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkPartyFull::
	msgbox Route34_DayCare_Text_ClerkNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkRejection::
	msgbox Route34_DayCare_Text_Rejection, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkAfter::
	msgbox Route34_DayCare_Text_ClerkAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_Text_ClerkBefore:
	.string "I'm the DAY-CARE couple's son.\p"
	.string "We've found unusual ODD EGGS.\p"
	.string "Enter ONE secret word.\n"
	.string "Ask the BABY EXPERT for clues.\p"
	.string "For a STARTER, enter its NAME!$"

Route34_DayCare_Text_ClerkNoRoom:
	.string "It looks like you can't carry another\n"
	.string "POKéMON anyway.$"

Route34_DayCare_Text_ClerkQuestion:
	.string "Type your secret password.\n"
	.string "Even a baby's NAME can work!$"

Route34_DayCare_Text_Rejection:
	.string "Sorry, I don't know that word.\p"
	.string "Ask the BABY EXPERT for clues,\n"
	.string "or enter a STARTER name!$"

Route34_DayCare_Text_ReceivedOddEgg:
	.string "{PLAYER} Received the ODD EGG.$"

Route34_DayCare_Text_TakeCare:
	.string "I knew you were the right trainer\n"
	.string "for the job. Take good care of it!$"

Route34_DayCare_Text_ClerkAfter:
	.string "You've already claimed that EGG.\p"
	.string "Try a different secret word\n"
	.string "to discover another!$"

Route34_DayCare_EventScript_Ditto::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_Ditto, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route34_DayCare_Text_Ditto:
	.string "DITTO: Tto!$"

Route34_EventScript_DaycareMan::
	lock
	faceplayer
	specialvar VAR_RESULT, IsPartyLimitChallengeActive @ tx_randomizer_and_challenges
	goto_if_eq VAR_RESULT, TRUE, Route34_DayCare_EventScript_ClosedForChallenge
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_EventScript_DaycareEggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_EventScript_CheckOnOneMon
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route34_EventScript_CheckOnTwoMons
	msgbox Route34_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

Route34_EventScript_DaycareEggWaiting::
	msgbox Route34_Text_DoYouWantEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_EventScript_DaycareAcceptEgg
	msgbox Route34_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_EventScript_DaycareAcceptEgg
	msgbox Route34_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

Route34_EventScript_DaycareAcceptEgg::
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, VAR_0x8004, Route34_EventScript_DaycareReceiveEgg
	msgbox Route34_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

Route34_EventScript_DaycareReceiveEgg::
	message Route34_Text_ReceivedEgg
	playfanfare MUS_HG_OBTAIN_EGG
	waitfanfare
	waitbuttonpress
	msgbox Route34_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag FLAG_PENDING_DAYCARE_EGG
	release
	end

Route34_EventScript_CheckMonReceivedMail::
	specialvar VAR_RESULT, CheckDaycareMonReceivedMail
	call_if_eq VAR_RESULT, 1, Route34_EventScript_MonReceivedMail
	return

Route34_EventScript_MonReceivedMail::
	msgbox Route34_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

Route34_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox Route34_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_EventScript_CheckMonReceivedMail
	release
	end

Route34_EventScript_CheckOnTwoMons::
	special GetDaycareMonNicknames
	msgbox Route34_Text_YourMonsAreDoingFine, MSGBOX_DEFAULT
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call Route34_EventScript_CheckMonReceivedMail
	setvar VAR_0x8004, 1
	call Route34_EventScript_CheckMonReceivedMail
	release
	end

Route34_DayCare_EventScript_DaycareWoman::
	lock
	faceplayer
	specialvar VAR_RESULT, IsPartyLimitChallengeActive @ tx_randomizer_and_challenges
	goto_if_eq VAR_RESULT, TRUE, Route34_DayCare_EventScript_ClosedForChallenge
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_DayCare_EventScript_EggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_OneMonInDaycare
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route34_DayCare_EventScript_TwoMonsInDaycare
	msgbox Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	msgbox Route34_DayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_GiveMonToRaise::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_eq VAR_RESULT, 1, Route34_DayCare_EventScript_OnlyOneMon
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_eq VAR_RESULT, 2, Route34_DayCare_EventScript_OnlyTwoAliveMons
	msgbox Route34_DayCare_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseSendDaycareMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route34_DayCare_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	goto_if_eq VAR_RESULT, 0, Route34_DayCare_EventScript_OnlyOneAliveMon
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry VAR_0x8005, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	callnative UpdateFollowingPokemon
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_CanRaiseOneMore
	release
	end

Route34_DayCare_EventScript_ComeAgain::
	msgbox Route34_DayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_CanRaiseOneMore::
	msgbox Route34_DayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_ClosedForChallenge::
	msgbox Route34_DayCare_Text_ClosedForChallenge, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_Text_ClosedForChallenge:
	.string "Sorry, we can't look after your\n"
	.string "POKéMON during a party limit\l"
	.string "challenge!$"

Route34_DayCare_EventScript_OnlyOneMon::
	msgbox Route34_DayCare_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_OnlyOneAliveMon::
	msgbox Route34_DayCare_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_OnlyTwoAliveMons::
	msgbox Route34_DayCare_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_EggWaiting::
	msgbox Route34_DayCare_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_YourMonHasGrownXLevels::
	msgbox Route34_DayCare_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

Route34_DayCare_EventScript_DisplayLevelsGained::
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	call_if_ne VAR_RESULT, 0, Route34_DayCare_EventScript_YourMonHasGrownXLevels
	return

Route34_DayCare_EventScript_OneMonInDaycare::
	msgbox Route34_DayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_DayCare_EventScript_DisplayLevelsGained
	msgbox Route34_DayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	msgbox Route34_DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_TryRetrieveMon::
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, VAR_0x8004, Route34_DayCare_EventScript_NoRoom
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	goto_if_eq VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU, Route34_DayCare_EventScript_ComeAgain
	goto Route34_DayCare_EventScript_CostPrompt
	end

Route34_DayCare_EventScript_CostPrompt::
	special GetDaycareCost
	msgbox Route34_DayCare_Text_ItWillCostX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_CheckEnoughMoney
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_CheckEnoughMoney::
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	goto_if_eq VAR_RESULT, 1, Route34_DayCare_EventScript_RetrieveMon
	msgbox Route34_DayCare_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_RetrieveMon::
	@applymovement LOCALID_DAYCARE_LADY, Route34_DayCare_Movement_RetrieveDaycareMon
	@waitmovement 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_SHOP
	msgbox Route34_DayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry VAR_RESULT, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_AskRetrieveOtherMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_AskRetrieveOtherMon::
	msgbox Route34_DayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_NoRoom::
	msgbox Route34_DayCare_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_Movement_RetrieveDaycareMon:
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_right
	delay_16
	delay_16
	face_up
	walk_slow_up
	set_invisible
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	set_visible
	walk_slow_down
	step_end

@ Unused. Possibly a commented script, or a typo end added to the above Movement script
Route34_DayCare_EventScript_UnusedEnd::
	end

Route34_DayCare_EventScript_TwoMonsInDaycare::
	msgbox Route34_DayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_DayCare_EventScript_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call Route34_DayCare_EventScript_DisplayLevelsGained
	msgbox Route34_DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	msgbox Route34_DayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_Text_SeeWifeIfYoudLikeMeToRaiseMon:
	.string "I'm the DAY-CARE MAN.\p"
	.string "I help take care of the precious\n"
	.string "POKéMON of TRAINERS.\p"
	.string "If you'd like me to raise your POKéMON,\n"
	.string "have a word with my wife.$"

Route34_Text_DoYouWantEgg:
	.string "Ah, it's you!\p"
	.string "We were raising your POKéMON,\n"
	.string "and my goodness, were we surprised!\p"
	.string "Your POKéMON had an EGG!\p"
	.string "We don't know how it got there,\n"
	.string "but your POKéMON had it.\p"
	.string "You do want it, yes?$"

Route34_Text_YourMonIsDoingFine:
	.string "Ah, it's you! Good to see you.\n"
	.string "Your {STR_VAR_1}'s doing fine.$"

Route34_Text_IllKeepIt:
	.string "Well then, I'll keep it.\n"
	.string "Thanks!$"

Route34_Text_YouHaveNoRoomForIt:
	.string "You have no room for it…\n"
	.string "Come back when you've made room.$"

Route34_Text_ReceivedEgg:
	.string "{PLAYER} received the EGG from\n"
	.string "the DAY-CARE MAN.$"

Route34_Text_TakeGoodCareOfIt:
	.string "Take good care of it.$"

Route34_Text_FriendlyWithOtherTrainersMon:
	.string "By the way, about your {STR_VAR_1},\n"
	.string "it seemed to be friendly with\l"
	.string "{STR_VAR_2}'s {STR_VAR_3}.\p"
	.string "I may even have seen it receiving\n"
	.string "a piece of MAIL.$"

@ Unused
Route34_Text_SeeWifeIfYouWantToPickUpMon:
	.string "If you want to pick up your POKéMON,\n"
	.string "have a word with my wife.$"

Route34_Text_YourMonsAreDoingFine:
	.string "Ah, it's you! Your {STR_VAR_1} and\n"
	.string "{STR_VAR_2} are doing fine.$"

Route34_Text_IWillKeepDoYouWantIt:
	.string "I really will keep it.\n"
	.string "You do want this, yes?$"

Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon:
	.string "I'm the DAY-CARE LADY.\p"
	.string "We can raise POKéMON for you.\p"
	.string "Would you like us to raise one?$"

Route34_DayCare_Text_WhichMonShouldWeRaise:
	.string "Which POKéMON should we raise for\n"
	.string "you?$"

Route34_DayCare_Text_WellRaiseYourMon:
	.string "Fine, we'll raise your {STR_VAR_1}\n"
	.string "for a while.\p"
	.string "Come back for it later.$"

Route34_DayCare_Text_WeCanRaiseOneMore:
	.string "We can raise two of your POKéMON.\n"
	.string "Would you like us to raise one more?$"

Route34_DayCare_Text_HusbandWasLookingForYou:
	.string "My husband was looking for you.$"

Route34_DayCare_Text_FineThenComeAgain:
	.string "Oh, fine, then.\n"
	.string "Come again.$"

Route34_DayCare_Text_NotEnoughMoney:
	.string "You don't have enough money…$"

Route34_DayCare_Text_TakeOtherOneBackToo:
	.string "Will you take back the other one,\n"
	.string "too?$"

Route34_DayCare_Text_ComeAgain:
	.string "Fine.\n"
	.string "Come again.$"

Route34_DayCare_Text_GoodToSeeYou:
	.string "Ah, it's you! Good to see you.\n"
	.string "Your POKéMON can only be doing good!$"

Route34_DayCare_Text_YourMonHasGrownXLevels:
	.string "By level, your {STR_VAR_1} has\n"
	.string "grown by {STR_VAR_2}.$"

Route34_DayCare_Text_YourTeamIsFull:
	.string "Your POKéMON team is full.\n"
	.string "Make room, then come see me.$"

@ Unused
Route34_DayCare_Text_TakeBackWhichMon:
	.string "Which POKéMON will you take back?$"

Route34_DayCare_Text_ItWillCostX:
	.string "If you want your {STR_VAR_1} back,\n"
	.string "it will cost ¥{STR_VAR_2}.$"

Route34_DayCare_Text_HeresYourMon:
	.string "Perfect!\n"
	.string "Here's your POKéMON.$"

Route34_DayCare_Text_TookBackMon:
	.string "{PLAYER} took back {STR_VAR_1} from\n"
	.string "the DAY-CARE LADY.$"

Route34_DayCare_Text_YouHaveJustOneMon:
	.string "Oh? But you have just one\n"
	.string "POKéMON.\p"
	.string "Come back another time.$"

Route34_DayCare_Text_TakeYourMonBack:
	.string "Will you take your POKéMON back?$"

Route34_DayCare_Text_WhatWillYouBattleWith:
	.string "If you leave me that POKéMON,\n"
	.string "what will you battle with?\p"
	.string "Come back another time.$"

Route34_DayCare_Text_YoullBeLeftWithJustOne:
	.string "Huh?\n"
	.string "Now, now.\p"
	.string "If you leave that POKéMON with\n"
	.string "me, you'll be left with just one.\p"
	.string "You will be better off if you catch\n"
	.string "some more, I dare say.$"


@ PRU Breeding Centre move expert: free, repeatable Egg/Tutor moves from
@ existing expansion Move Relearner UI. Selection also supports PC Pokémon.
@ The original Day-Care and Odd Egg gift scripts are not modified.
Route34_DayCare_EventScript_PRUMoveExpert::
	lock
	faceplayer
	msgbox Route34_DayCare_Text_PRUExpertIntro, MSGBOX_DEFAULT
	msgbox Route34_DayCare_Text_PRUExpertEggOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_PRUExpertEggMoves
	msgbox Route34_DayCare_Text_PRUExpertTutorOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_PRUExpertTutorMoves
	goto Route34_DayCare_EventScript_PRUExpertDone

Route34_DayCare_EventScript_PRUExpertEggMoves::
	setmoverelearnerstate MOVE_RELEARNER_EGG_MOVES
	goto Route34_DayCare_EventScript_PRUExpertChooseMon

Route34_DayCare_EventScript_PRUExpertTutorMoves::
	setmoverelearnerstate MOVE_RELEARNER_TUTOR_MOVES
	goto Route34_DayCare_EventScript_PRUExpertChooseMon

Route34_DayCare_EventScript_PRUExpertChooseMon::
	msgbox Route34_DayCare_Text_PRUExpertChooseMon, MSGBOX_DEFAULT
	chooseboxmon SELECT_PC_MON_MOVE_RELEARNER
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route34_DayCare_EventScript_PRUExpertDone
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, Route34_DayCare_EventScript_PRUExpertCannotTeachEgg
	special HasMovesToRelearn
	goto_if_eq VAR_RESULT, FALSE, Route34_DayCare_EventScript_PRUExpertNoMoves
	msgbox Route34_DayCare_Text_PRUExpertChooseMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, Route34_DayCare_EventScript_PRUExpertChooseMon
	msgbox Route34_DayCare_Text_PRUExpertTaughtMove, MSGBOX_DEFAULT
	goto Route34_DayCare_EventScript_PRUExpertChooseMon

Route34_DayCare_EventScript_PRUExpertCannotTeachEgg::
	msgbox Route34_DayCare_Text_PRUExpertCannotTeachEgg, MSGBOX_DEFAULT
	goto Route34_DayCare_EventScript_PRUExpertChooseMon

Route34_DayCare_EventScript_PRUExpertNoMoves::
	msgbox Route34_DayCare_Text_PRUExpertNoMoves, MSGBOX_DEFAULT
	goto Route34_DayCare_EventScript_PRUExpertChooseMon

Route34_DayCare_EventScript_PRUExpertDone::
	msgbox Route34_DayCare_Text_PRUExpertGoodbye, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_Text_PRUExpertIntro:
	.string "I'm the BREEDING CENTRE's\n"
	.string "MOVE EXPERT!\p"
	.string "I can teach EGG MOVES and\n"
	.string "special TUTOR MOVES, for free.$"

Route34_DayCare_Text_PRUExpertEggOffer:
	.string "Would you like to learn\n"
	.string "some EGG MOVES?$"

Route34_DayCare_Text_PRUExpertTutorOffer:
	.string "How about TUTOR MOVES\n"
	.string "instead?$"

Route34_DayCare_Text_PRUExpertChooseMon:
	.string "Choose a POKéMON from your\n"
	.string "party or PC.$"

Route34_DayCare_Text_PRUExpertChooseMove:
	.string "Which move shall I teach?$"

Route34_DayCare_Text_PRUExpertCannotTeachEgg:
	.string "An EGG must hatch before\n"
	.string "I can teach it moves.$"

Route34_DayCare_Text_PRUExpertNoMoves:
	.string "No more moves of this kind\n"
	.string "are available for it.$"

Route34_DayCare_Text_PRUExpertTaughtMove:
	.string "Great! Another move learned!$"

Route34_DayCare_Text_PRUExpertGoodbye:
	.string "Come back whenever you need\n"
	.string "some new moves!$"
