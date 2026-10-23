LavenderTown_SoulHouse_hns_MapScripts::
	.byte 0

// Mr Fuji's existing Soul House is the entrance to a separate, optional
// memory of the original tower. The modern Radio Tower is never replaced.
LavenderTownSoulHouse_EventScript_MrFuji::
	lock
	faceplayer
	goto_if_set FLAG_PRU_CUBONE_MIMIKYU_CAUGHT, LavenderTownSoulHouse_EventScript_MrFujiResolved
	msgbox MrFuji_Text_Main
	msgbox LavenderTownSoulHouse_Text_CuboneQuest
	goto LavenderTownSoulHouse_EventScript_AskSpiritTower

LavenderTownSoulHouse_EventScript_MrFujiResolved::
	goto_if_set FLAG_PRU_CUBONE_MEMORIAL_REWARDED, LavenderTownSoulHouse_EventScript_MrFujiPeace
	msgbox LavenderTownSoulHouse_Text_ThankYou
	giveitem ITEM_THICK_CLUB, 1
	goto_if_eq VAR_RESULT, FALSE, LavenderTownSoulHouse_EventScript_FullBag
	setflag FLAG_PRU_CUBONE_MEMORIAL_REWARDED
	goto LavenderTownSoulHouse_EventScript_AskSpiritTower

LavenderTownSoulHouse_EventScript_FullBag::
	msgbox LavenderTownSoulHouse_Text_BagFull
	release
	end

LavenderTownSoulHouse_EventScript_MrFujiPeace::
	msgbox LavenderTownSoulHouse_Text_Peace
LavenderTownSoulHouse_EventScript_AskSpiritTower::
	msgbox LavenderTownSoulHouse_Text_EnterTower, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LavenderTownSoulHouse_EventScript_EndQuestTalk
	msgbox LavenderTownSoulHouse_Text_CloseEyes
	setescapewarp MAP_LAVENDER_TOWN_SOUL_HOUSE_HNS, 11, 12
	closemessage
	warp MAP_LAVENDER_SPIRIT_TOWER_1F_HNS, 11, 15
	waitstate
	release
	end

LavenderTownSoulHouse_EventScript_EndQuestTalk::
	release
	end

LavenderTownSoulHouse_EventScript_Cubone::
	goto_if_set FLAG_PRU_CUBONE_MIMIKYU_CAUGHT, LavenderTownSoulHouse_EventScript_CuboneHappy
	msgbox LavenderTownSoulHouse_Text_CuboneCrying, MSGBOX_NPC
	end

LavenderTownSoulHouse_EventScript_CuboneHappy::
	msgbox LavenderTownSoulHouse_Text_CuboneHappy, MSGBOX_NPC
	end

LavenderTownSoulHouse_Text_CuboneQuest:
	.string "Have you heard that CUBONE cry?\p"
	.string "Its mother died protecting it.\p"
	.string "A strange PIKACHU is rumoured\n"
	.string "to be in the old tower.\p"
	.string "Nobody knows why it is there.$"

LavenderTownSoulHouse_Text_EnterTower:
	.string "The old tower is gone, but\n"
	.string "its memories remain.\p"
	.string "I can take you there in spirit.\n"
	.string "Will you come with me?$"

LavenderTownSoulHouse_Text_CloseEyes:
	.string "An ESCAPE ROPE will bring you\n"
	.string "safely back to me.\p"
	.string "Close your eyes...\p"
	.string "Let the memories return.$"

LavenderTownSoulHouse_Text_ThankYou:
	.string "You gave CUBONE a new friend.\n"
	.string "And its mother can rest.\p"
	.string "Please accept this THICK CLUB.$"

LavenderTownSoulHouse_Text_BagFull:
	.string "Your BAG is full. Return when\n"
	.string "you have room for a gift.$"

LavenderTownSoulHouse_Text_Peace:
	.string "The spirits have found peace.\n"
	.string "Thank you, my friend.$"

LavenderTownSoulHouse_Text_CuboneCrying:
	.string "CUBONE: Cu... bone...\p"
	.string "It keeps staring at the memorial.$"

LavenderTownSoulHouse_Text_CuboneHappy:
	.string "CUBONE: Cubone!\p"
	.string "It seems happy with its new\n"
	.string "friend.$"

LavenderTownSoulHouse_EventScript_Lass::
	msgbox SoulHouse_Text_Lass, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Teacher::
	msgbox SoulHouse_Text_Teacher, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Granny::
	msgbox SoulHouse_Text_Granny, MSGBOX_NPC
	end

MrFuji_Text_Main:
	.string "MR.FUJI: Welcome.\p"
	.string "Hmm… You appear to be raising\n"
	.string "your POKéMON in a kind and\l"
	.string "loving manner.\p"
	.string "POKéMON lovers come here to pay\n"
	.string "their respects to departed\l"
	.string "POKéMON.\p"
	.string "Please offer condolences for the\n"
	.string "souls of the departed POKéMON.\p"
	.string "I'm sure that will make them\n"
	.string "happy.$"

SoulHouse_Text_Teacher:
	.string "There are other graves of POKéMON\n"
	.string "here, I think.\p"
	.string "There are many chambers that only\n"
	.string "MR.FUJI may enter.$"

SoulHouse_Text_Lass:
	.string "I came with my mom to visit\n"
	.string "POKéMON graves…$"

SoulHouse_Text_Granny:
	.string "The POKéMON that lived with me…\p"
	.string "I loved them like my\n"
	.string "grandchildren…$"
