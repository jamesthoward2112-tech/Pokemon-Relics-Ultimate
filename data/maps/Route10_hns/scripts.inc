Route10_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route10_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route10_OnTransition:
	callnative SetTimeBasedEncounters
	goto_if_unset FLAG_IS_CHAMPION, Route10_RelicWeatherDone
	goto_if_set FLAG_PJR_RELIC_RAIKOU, Route10_RelicWeatherDone
	setweather WEATHER_RAIN_THUNDERSTORM
	doweather
Route10_RelicWeatherDone:
	end

Route10_EventScript_Surge::
    lock
    faceplayer
    msgbox Route10_Text_Surge, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_PLANT_SURGE
    removeobject LOCALID_ROUTE10_SURGE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_SURGE
    release
    end

Route10_Text_Surge:
    .string "Hey, kid!\p"
	.string "Keep your guard up out here,\n"
	.string "this place is cracklin' with power!\p"
	.string "If you want a rematch, report to\n"
	.string "the FIGHTING DOJO!$"

Route10_EventScript_Item_Rock_Polish::
    finditem ITEM_TM_ROCK_POLISH
    end

Route10_EventScript_Jim::
	trainerbattle_single TRAINER_JIM_HNS, Route10_Text_HikerJimSeen, Route10_Text_HikerJimBeaten
	msgbox Route10_Text_HikerJimAfter, MSGBOX_AUTOCLOSE
	end

Route10_EventScript_Robert::
	trainerbattle_single TRAINER_ROBERT_HNS, Route10_Text_PokefanmRobertSeen, Route10_Text_PokefanmRobertBeaten
	msgbox Route10_Text_PokefanmRobertAfter, MSGBOX_AUTOCLOSE
	end

Route10_EventScript_Sign::
	msgbox Route10_Text_Sign, MSGBOX_SIGN
	end

Route10_EventScript_PPSign::
	msgbox Route10_Text_PowerPlant, MSGBOX_SIGN
	end

Route10_EventScript_PRU_ShinyElectrode::
	lock
	faceplayer
	msgbox Route10_Text_PRU_ShinyElectrode, MSGBOX_DEFAULT
	playmoncry SPECIES_ELECTRODE, CRY_MODE_ENCOUNTER
	waitmoncry
	@ This guarantees the same white-and-blue shiny shown on the ledge.
	setwildbattleshiny SPECIES_ELECTRODE, 80
	special PruPrepareChargedElectrode
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route10_EventScript_PRU_ElectrodeCaught
	@ Kaboom! self-KO, any other KO, escape, or whiteout must not
	@ consume the encounter or hide the sprite. Allow an immediate rematch.
	@ Only a successful capture sets the permanent disappearance flag.
	release
	end

Route10_EventScript_PRU_ElectrodeCaught::
	setflag FLAG_PRU_POWER_PLANT_ELECTRODE_CAUGHT
	removeobject LOCALID_ROUTE10_PRU_ELECTRODE
	release
	end

Route10_Text_PRU_ShinyElectrode:
	.string "The POWER PLANT is vibrating!\p"
	.string "A strange blue ELECTRODE is\n"
	.string "overflowing with energy!$"

Route10_Text_HikerJimSeen:
	.string "Hahahah!$"

Route10_Text_HikerJimBeaten:
	.string "Hahaha-hachoo!$"

Route10_Text_HikerJimAfter:
	.string "Hay fever is making me sneeze!\n"
	.string "Ahahah-CHOO!$"

Route10_Text_PokefanmRobertSeen:
	.string "You like POKéMON, don't you?\p"
	.string "Me too!$"

Route10_Text_PokefanmRobertBeaten:
	.string "I'd have to say that's my loss.$"

Route10_Text_PokefanmRobertAfter:
	.string "Look what you did to my POKéMON…\p"
	.string "I won't forget this…$"

Route10_Text_PowerPlant:
	.string "POWER PLANT$"

Route10_Text_Sign:
	.string "ROUTE 10\p"
	.string "CERULEAN CITY - LAVENDER TOWN$"

@ PRU RELICS: the lab guide supplies clues; encounters are on this map.
Route10_hns_RelicRaikou::
	lock
	faceplayer
	goto_if_unset FLAG_IS_CHAMPION, Route10_hns_RelicRaikou_Unavailable
	goto_if_set FLAG_PJR_RELIC_RAIKOU, Route10_hns_RelicRaikou_Complete
	goto RuinsOfAlph_Lab_EventScript_RelicRaikou

Route10_hns_RelicRaikou_Unavailable::
	msgbox Route10_hns_RelicRaikou_TextUnavailable, MSGBOX_DEFAULT
	release
	end

Route10_hns_RelicRaikou_Complete::
	msgbox Route10_hns_RelicRaikou_TextComplete, MSGBOX_DEFAULT
	release
	end

Route10_hns_RelicRaikou_TextUnavailable:
	.string "The ancient RELIC is still sealed.\n"
	.string "Ask the ALPH RUINS scientist.$"
Route10_hns_RelicRaikou_TextComplete:
	.string "This RELIC has already answered.\n"
	.string "Return to the ALPH scientist.$"

