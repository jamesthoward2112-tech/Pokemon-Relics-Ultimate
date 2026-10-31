PalletTown_Lab_hns_MapScripts::
	.byte 0

PalletTown_Lab_EventScript_Oak::
	lock
	faceplayer
	call_if_unset FLAG_SYS_NATIONAL_DEX, PalletTown_Lab_EventScript_OakGiveNatDex_ForPlaytesters
	@ Existing Kanto-champion saves can reach the repeatable RELICS handoff.
	@ The previous E20 flag was undefined in this source; preserve old saves.
	goto_if_set FLAG_IS_KANTO_CHAMPION, PalletTown_Lab_EventScript_OakRelicsMenu
PalletTown_Lab_EventScript_OakNormalEntry::
	goto_if_unset FLAG_PRU_OAK_AURORA_TICKET_RECEIVED, PalletTown_Lab_EventScript_OakPRUAuroraCheck
PalletTown_Lab_EventScript_OakNormalDialogue:
	goto_if_eq VAR_PALLETTOWN_LABSTATE, 1, PalletTown_Lab_EventScript_OakBadgeCheck
	goto_if_eq VAR_PALLETTOWN_LABSTATE, 2, PalletTown_Lab_EventScript_OakDex
	msgbox PalletTown_Lab_Text_OakWelcomeKanto, MSGBOX_DEFAULT
	@ PRU is Johto-first; Oak's discovery now follows Elm and the ALPH research.
	msgbox PalletTown_Lab_Text_OakResonanceResearch, MSGBOX_DEFAULT
	msgbox PalletTown_Lab_Text_OakLabGoodbye, MSGBOX_DEFAULT
	setvar VAR_PALLETTOWN_LABSTATE, 1
	goto_if_ge VAR_NUM_BADGES, 16, PalletTown_Lab_EventScript_OakBadgeCheck
	closemessage
	release
	end

// Use defined post-Kanto champion flag: old saves work without a migration.
// Keep guidance available after E20 rewards or credits were claimed.
// No items, save flags or story flags are changed by Oak's advice.
PalletTown_Lab_EventScript_OakRelicsMenu::
	message PalletTown_Lab_Text_OakRelicsMenu
	waitmessage
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, PalletTown_Lab_Text_OakRelicsOptionAbout, PalletTown_Lab_Text_OakRelicsOptionNext, PalletTown_Lab_Text_OakRelicsOptionOther
	switch VAR_RESULT
	case 0, PalletTown_Lab_EventScript_OakRelicsExplain
	case 1, PalletTown_Lab_EventScript_OakRelicsNext
	case 2, PalletTown_Lab_EventScript_OakNormalEntry
	case MULTI_B_PRESSED, PalletTown_Lab_EventScript_OakNormalEntry
	goto PalletTown_Lab_EventScript_OakNormalEntry

PalletTown_Lab_EventScript_OakRelicsExplain::
	msgbox PalletTown_Lab_Text_OakRelicsExplain, MSGBOX_DEFAULT
	goto PalletTown_Lab_EventScript_OakRelicsNext

PalletTown_Lab_EventScript_OakRelicsNext::
	goto_if_set FLAG_PJR_RELIC_HO_OH, PalletTown_Lab_EventScript_OakRelicsComplete
	goto_if_unset FLAG_PJR_RELIC_RAIKOU, PalletTown_Lab_EventScript_OakRelicsStart
	goto_if_unset FLAG_PJR_RELIC_ENTEI, PalletTown_Lab_EventScript_OakRelicsEntei
	goto_if_unset FLAG_PJR_RELIC_LUGIA, PalletTown_Lab_EventScript_OakRelicsLugia
	goto_if_unset FLAG_PJR_RELIC_UNOWN_I, PalletTown_Lab_EventScript_OakRelicsUnown
	goto_if_unset FLAG_PJR_RELIC_CELEBI, PalletTown_Lab_EventScript_OakRelicsCelebi
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, PalletTown_Lab_EventScript_OakRelicsSuicune
	goto_if_unset FLAG_PJR_RELIC_ALPHORACLE, PalletTown_Lab_EventScript_OakRelicsAlphoracle
	goto_if_unset FLAG_PJR_GOT_RAINBOW_CREST, PalletTown_Lab_EventScript_OakRelicsCrest
	goto PalletTown_Lab_EventScript_OakRelicsHoOh

PalletTown_Lab_EventScript_OakRelicsStart::
	msgbox PalletTown_Lab_Text_OakRelicsStart, MSGBOX_DEFAULT
	release
	end
PalletTown_Lab_EventScript_OakRelicsEntei::
	msgbox PalletTown_Lab_Text_OakRelicsEntei, MSGBOX_DEFAULT
	release
	end
PalletTown_Lab_EventScript_OakRelicsLugia::
	msgbox PalletTown_Lab_Text_OakRelicsLugia, MSGBOX_DEFAULT
	release
	end
PalletTown_Lab_EventScript_OakRelicsUnown::
	msgbox PalletTown_Lab_Text_OakRelicsUnown, MSGBOX_DEFAULT
	release
	end
PalletTown_Lab_EventScript_OakRelicsCelebi::
	msgbox PalletTown_Lab_Text_OakRelicsCelebi, MSGBOX_DEFAULT
	release
	end
PalletTown_Lab_EventScript_OakRelicsSuicune::
	msgbox PalletTown_Lab_Text_OakRelicsSuicune, MSGBOX_DEFAULT
	release
	end
PalletTown_Lab_EventScript_OakRelicsAlphoracle::
	msgbox PalletTown_Lab_Text_OakRelicsAlphoracle, MSGBOX_DEFAULT
	release
	end
PalletTown_Lab_EventScript_OakRelicsCrest::
	msgbox PalletTown_Lab_Text_OakRelicsCrest, MSGBOX_DEFAULT
	release
	end
PalletTown_Lab_EventScript_OakRelicsHoOh::
	msgbox PalletTown_Lab_Text_OakRelicsHoOh, MSGBOX_DEFAULT
	release
	end
PalletTown_Lab_EventScript_OakRelicsComplete::
	msgbox PalletTown_Lab_Text_OakRelicsComplete, MSGBOX_DEFAULT
	release
	end

PalletTown_Lab_Text_OakRelicsMenu:
	.string "OAK: Congratulations on the\n"
	.string "ELITE 20! What shall we discuss?$"
PalletTown_Lab_Text_OakRelicsOptionAbout:
	.string "About the RELICS$"
PalletTown_Lab_Text_OakRelicsOptionNext:
	.string "Where next?$"
PalletTown_Lab_Text_OakRelicsOptionOther:
	.string "Other research$"
PalletTown_Lab_Text_OakRelicsExplain:
	.string "OAK: ELM and I uncovered six\n"
	.string "ancient powers across JOHTO.\p"
	.string "Their names spell R-E-L-I-C-S.\n"
	.string "Each holds an ancient voice.\p"
	.string "We call this power RESONANCE.\n"
	.string "Together, they may awaken the\n"
	.string "FIRST VOICE: ALPHORACLE.\p"
	.string "The RUINS OF ALPH scientist\n"
	.string "can decode each signal.\p"
	.string "Capture a RELIC, then return\n"
	.string "to the scientist for the next\n"
	.string "clue. I'll guide you there!$"
PalletTown_Lab_Text_OakRelicsStart:
	.string "OAK: Fly to VIOLET CITY.\n"
	.string "Head SOUTH onto ROUTE 32,\p"
	.string "then take the WEST path to\n"
	.string "the RUINS OF ALPH.\p"
	.string "Enter the RESEARCH LAB and\n"
	.string "speak to the SCIENTIST.\p"
	.string "Start with R: RAIKOU.\n"
	.string "Tell me what you discover!$"
PalletTown_Lab_Text_OakRelicsEntei:
	.string "OAK: RAIKOU is recorded!\p"
	.string "Return to the RUINS OF ALPH\n"
	.string "RESEARCH LAB for E: ENTEI.$"
PalletTown_Lab_Text_OakRelicsLugia:
	.string "OAK: ENTEI's power is ours!\p"
	.string "The scientist at the RUINS\n"
	.string "OF ALPH seeks L: LUGIA.$"
PalletTown_Lab_Text_OakRelicsUnown:
	.string "OAK: LUGIA is recorded!\p"
	.string "At the RUINS OF ALPH LAB,\n"
	.string "the next mark is I: UNOWN I.$"
PalletTown_Lab_Text_OakRelicsCelebi:
	.string "OAK: The UNOWN clue is done!\p"
	.string "Return to the RUINS OF ALPH\n"
	.string "LAB for C: CELEBI.$"
PalletTown_Lab_Text_OakRelicsSuicune:
	.string "OAK: CELEBI is recorded!\p"
	.string "The last letter waits at the\n"
	.string "RUINS OF ALPH: S, SUICUNE.$"
PalletTown_Lab_Text_OakRelicsAlphoracle:
	.string "OAK: All six letters shine!\p"
	.string "Visit the RUINS OF ALPH LAB\n"
	.string "for the FIRST VOICE: ALPHORACLE.$"
PalletTown_Lab_Text_OakRelicsCrest:
	.string "OAK: The FIRST VOICE is awake!\p"
	.string "Climb MT. SILVER and challenge\n"
	.string "RED for the RAINBOW CREST.$"
PalletTown_Lab_Text_OakRelicsHoOh:
	.string "OAK: You have the CREST!\p"
	.string "Go to MT. SILVER's summit.\n"
	.string "I'll await your final test,\p"
	.string "then we'll summon the GOLDEN\n"
	.string "RELIC HO-OH together!$"
PalletTown_Lab_Text_OakRelicsComplete:
	.string "OAK: The RELICS are united!\p"
	.string "ELM and I are proud of you,\n"
	.string "ELITE 20 CHAMPION!$"

// Deoxys' Aurora Ticket is now an obtainable post-League Kanto milestone.
// Preserve Oak's normal badge/Indigo Plateau story on every other visit.
PalletTown_Lab_EventScript_OakPRUAuroraCheck:
	goto_if_ge VAR_NUM_BADGES, 12, PalletTown_Lab_EventScript_OakPRUAuroraGift
	goto PalletTown_Lab_EventScript_OakNormalDialogue

PalletTown_Lab_EventScript_OakPRUAuroraGift:
	msgbox PalletTown_Lab_Text_PRUAuroraTicketIntro, MSGBOX_DEFAULT
	giveitem ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, FALSE, PalletTown_Lab_EventScript_OakPRUAuroraBagFull
	setflag FLAG_PRU_OAK_AURORA_TICKET_RECEIVED
	msgbox PalletTown_Lab_Text_PRUAuroraTicketOutro, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_OakPRUAuroraBagFull:
	msgbox PalletTown_Lab_Text_PRUAuroraBagFull, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_Text_PRUAuroraTicketIntro:
	.string "OAK: Four KANTO BADGES already!\p"
	.string "I've been saving a special ticket\n"
	.string "for an exceptional trainer.$"

PalletTown_Lab_Text_PRUAuroraTicketOutro:
	.string "OAK: Take the AURORA TICKET to\n"
	.string "OLIVINE PORT and sail to BIRTH ISLAND.\p"
	.string "They say a strange visitor fell\n"
	.string "from the stars there...$"

PalletTown_Lab_Text_PRUAuroraBagFull:
	.string "OAK: Make room for this ticket\n"
	.string "and come back to me.$"

PalletTown_Lab_EventScript_OakGiveNatDex_ForPlaytesters::
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	return

PalletTown_Lab_EventScript_OakBadgeCheck::
	goto_if_ge VAR_NUM_BADGES, 16, PalletTown_Lab_EventScript_Oak16Badges
	goto_if_ge VAR_NUM_BADGES, 9, PalletTown_Lab_EventScript_Oak9Badges
	msgbox PalletTown_Lab_Text_OakNoKantoBadges, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_Oak16Badges::
	goto_if_set FLAG_IS_KANTO_CHAMPION, PalletTown_Lab_EventScript_OakMtSilverOpen
	msgbox PalletTown_Lab_Text_OakOpenIndigoPlateau, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_OakMtSilverOpen::
	msgbox PalletTown_Lab_Text_OakOpenMtSilver, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ROUTE28_SCIENTIST, 1
	setvar VAR_PALLETTOWN_LABSTATE, 2
	release
	end

PalletTown_Lab_EventScript_Oak9Badges::
	msgbox PalletTown_Lab_Text_OakYesKantoBadges, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_OakDex::
	msgbox PalletTown_Lab_Text_OakLabDexCheck, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_Assistant1::
	msgbox PalletTown_Lab_Text_OaksAssistant1, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_Assistant2::
	msgbox PalletTown_Lab_Text_OaksAssistant2, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_Assistant3::
	msgbox PalletTown_Lab_Text_OaksAssistant3, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_PC::
	msgbox PalletTown_Lab_Text_OaksLabPC, MSGBOX_SIGN
	end

PalletTown_Lab_Text_OakLabDexCheck:
	.string "How is your POKéDEX coming?$"

PalletTown_Lab_Text_OakWelcomeKanto:
	.string "OAK: Ah, {PLAYER}!\n"
	.string "It's good of you to come all this\l"
	.string "way to KANTO.\p"
	.string "What do you think of the trainers\n"
	.string "out here? Pretty tough, huh?$"

PalletTown_Lab_Text_OakResonanceResearch:
	.string "ELM told me about the strange\n"
	.string "RESONANCE at the RUINS OF ALPH.\p"
	.string "Some old KANTO fossils are\n"
	.string "giving off the same signal.\p"
	.string "Your JOHTO findings may help\n"
	.string "us understand the connection.\p"
	.string "ELM will keep studying ALPH.\n"
	.string "I'll examine the KANTO clues.$"

PalletTown_Lab_Text_OakLabGoodbye:
	.string "If you're in the area, I hope you\n"
	.string "come visit again.$"

PalletTown_Lab_Text_OakOpenMtSilver:
	.string "OAK: Wow! That's excellent!\p"
	.string "You collected the BADGES of GYMS\n"
	.string "in KANTO. Well done!\p"
	.string "I was right in my assessment of\n"
	.string "you.\p"
	.string "Tell you what, {PLAYER}. I'll make\n"
	.string "arrangements so that you can go\l"
	.string "to MT.SILVER.\p"
	.string "MT.SILVER is a big mountain that\n"
	.string "is home to many wild POKéMON.\p"
	.string "It's too dangerous for your average\n"
	.string "trainer, so it's off limits. But\l"
	.string "we can make an exception in your\l"
	.string "case, {PLAYER}.\p"
	.string "Go up to INDIGO PLATEAU. You can\n"
	.string "reach MT.SILVER from there.$"

PalletTown_Lab_Text_OakOpenIndigoPlateau:
	.string "Now that you've earned all 16\n"
	.string "BADGES, return to INDIGO PLATEAU.\p"
	.string "Defeat LANCE and the ELITE FOUR\n"
	.string "once more, and the restriction on\l"
	.string "MT.SILVER will be lifted.\p"
	.string "They won't go easy on you this\n"
	.string "time. Good luck, {PLAYER}!$"

PalletTown_Lab_Text_OakNoKantoBadges:
	.string "OAK: Hmm? You're not collecting\n"
	.string "KANTO GYM BADGES?\p"
	.string "The GYM LEADERS in KANTO are as\n"
	.string "tough as any you battled in JOHTO.\p"
	.string "I recommend that you challenge them.$"

PalletTown_Lab_Text_OakYesKantoBadges:
	.string "OAK: Ah, you're collecting KANTO\n"
	.string "GYM BADGES.\p"
	.string "I imagine that it's hard, but the\n"
	.string "experience is sure to help you.\p"
	.string "Come see me when you get them all.\p"
	.string "I'll have a gift for you.\p"
	.string "Keep trying hard, {PLAYER}!$"

PalletTown_Lab_Text_OaksAssistant1:
	.string "The PROF's POKéMON TALK radio\n"
	.string "program isn't aired here in KANTO.\p"
	.string "It's a shame--I'd like to hear it.$"

PalletTown_Lab_Text_OaksAssistant2:
	.string "Thanks to your work on the POKéDEX,\n"
	.string "the PROF's research is coming along\l"
	.string "great.$"

PalletTown_Lab_Text_OaksAssistant3:
	.string "Don't tell anyone, but PROF.OAK'S\n"
	.string "POKéMON TALK isn't a live broadcast.$"

PalletTown_Lab_Text_OaksLabPC:
	.string "There's an e-mail message on the PC.\p"
	.string "…\p"
	.string "PROF.OAK, how is your research\n"
	.string "coming along?\p"
	.string "I'm still plugging away.\p"
	.string "I heard rumors that {PLAYER} is\n"
	.string "getting quite a reputation.\p"
	.string "I'm delighted to hear that.\p"
	.string "ELM in NEW BARK TOWN 8-)$"
