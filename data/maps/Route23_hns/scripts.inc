Route23_hns_MapScripts::
	.byte 0

@ Kanto Eevee Twins finale after the eight recovered Badge Heist challenges.
Route23_EventScript_PRUSteevee::
	goto_if_unset FLAG_PRU_HEIST_GIOVANNI, Route23_EventScript_PRUTwinsWaiting
	trainerbattle_double TRAINER_STEEVE_NEEVEE_KANTO_FINALE_HNS, Route23_Text_PRUTwinsIntro, Route23_Text_PRUTwinsWon, Route104_Text_GinaNotEnoughMons
	msgbox Route23_Text_PRUTwinsAfter, MSGBOX_AUTOCLOSE
	end

Route23_EventScript_PRUNeevee::
	goto Route23_EventScript_PRUSteevee

Route23_EventScript_PRUTwinsWaiting::
	msgbox Route23_Text_PRUTwinsWaiting, MSGBOX_NPC
	end

Route23_Text_PRUTwinsWaiting:
	.string "NEEVEE: TEAM ROCKET took your\n"
	.string "KANTO BADGE CASE?\p"
	.string "Win it back, then battle us!$"

Route23_Text_PRUTwinsIntro:
	.string "STEEVEE: Your KANTO BADGES\n"
	.string "are safe again!\p"
	.string "NEEVEE: One final double battle\n"
	.string "before the LEAGUE!$"

Route23_Text_PRUTwinsWon:
	.string "STEEVEE: You've earned it!$"

Route23_Text_PRUTwinsAfter:
	.string "NEEVEE: Good luck at\n"
	.string "INDIGO PLATEAU!$"
