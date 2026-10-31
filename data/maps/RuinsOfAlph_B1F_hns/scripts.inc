RuinsOfAlph_B1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RuinsOfAlph_B1F_OnFrame
	.byte 0

RuinsOfAlph_B1F_OnFrame::
	map_script_2 VAR_RUINSOFALPH_STATE, 1, RuinsOfAlph_B1F_EventScript_Presence
	.2byte 0

RuinsOfAlph_B1F_EventScript_Presence::
	lock
	msgbox RuinsOfAlph_B1F_Text_Presence, MSGBOX_DEFAULT
	closemessage
	setvar VAR_RUINSOFALPH_STATE, 0
	release
	end


RuinsOfAlph_B1F_EventScript_Teacher::
	lock
	faceplayer
	msgbox RuinsOfAlph_B1F_Text_Teacher, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_B1F_EventScript_Hiker::
	lock
	faceplayer
	msgbox RuinsOfAlph_B1F_Text_Hiker, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_B1F_EventScript_Gramps::
	lock
	faceplayer
	msgbox RuinsOfAlph_B1F_Text_Gramps, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_HelixFossil::
	finditem ITEM_HELIX_FOSSIL
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_DomeFossil::
	finditem ITEM_DOME_FOSSIL
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_OldAmber::
	finditem ITEM_OLD_AMBER
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_GSBALL::
	finditem ITEM_GS_BALL
	end

RuinsOfAlph_B1F_Text_Presence:
	.string "There is a strange presence here.$"

RuinsOfAlph_B1F_Text_Hiker:
	.string "This is a big room, but there's\n"
	.string "nothing here.$"

RuinsOfAlph_B1F_Text_Teacher:
	.string "This place has a mystical\n"
	.string "quality to it.\p"
	.string "It feels sort of ethereal\n"
	.string "even.$"

RuinsOfAlph_B1F_Text_Gramps:
	.string "Ancient buildings are often\n"
	.string "tombs of kings.\p"
	.string "Like the pyramids, for\n"
	.string "instance.$"

@ PRU RELICS: the lab guide supplies clues; encounters are on this map.
RuinsOfAlph_B1F_hns_RelicUnownI::
	lock
	faceplayer
	goto_if_unset FLAG_IS_CHAMPION, RuinsOfAlph_B1F_hns_RelicUnownI_Unavailable
	goto_if_unset FLAG_PJR_RELIC_LUGIA, RuinsOfAlph_B1F_hns_RelicUnownI_Unavailable
	goto_if_set FLAG_PJR_RELIC_UNOWN_I, RuinsOfAlph_B1F_hns_RelicUnownI_Complete
	goto RuinsOfAlph_Lab_EventScript_RelicUnownI

RuinsOfAlph_B1F_hns_RelicUnownI_Unavailable::
	msgbox RuinsOfAlph_B1F_hns_RelicUnownI_TextUnavailable, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_B1F_hns_RelicUnownI_Complete::
	msgbox RuinsOfAlph_B1F_hns_RelicUnownI_TextComplete, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_B1F_hns_RelicUnownI_TextUnavailable:
	.string "The ancient RELIC is still sealed.\n"
	.string "Ask the ALPH RUINS scientist.$"
RuinsOfAlph_B1F_hns_RelicUnownI_TextComplete:
	.string "This RELIC has already answered.\n"
	.string "Return to the ALPH scientist.$"

RuinsOfAlph_B1F_hns_RelicAlphoracle::
	lock
	faceplayer
	goto_if_unset FLAG_IS_CHAMPION, RuinsOfAlph_B1F_hns_RelicAlphoracle_Unavailable
	goto_if_unset FLAG_PJR_RELIC_SUICUNE, RuinsOfAlph_B1F_hns_RelicAlphoracle_Unavailable
	goto_if_set FLAG_PJR_RELIC_ALPHORACLE, RuinsOfAlph_B1F_hns_RelicAlphoracle_Complete
	goto RuinsOfAlph_Lab_EventScript_RelicAlphoracle

RuinsOfAlph_B1F_hns_RelicAlphoracle_Unavailable::
	msgbox RuinsOfAlph_B1F_hns_RelicAlphoracle_TextUnavailable, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_B1F_hns_RelicAlphoracle_Complete::
	msgbox RuinsOfAlph_B1F_hns_RelicAlphoracle_TextComplete, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_B1F_hns_RelicAlphoracle_TextUnavailable:
	.string "The ancient RELIC is still sealed.\n"
	.string "Ask the ALPH RUINS scientist.$"
RuinsOfAlph_B1F_hns_RelicAlphoracle_TextComplete:
	.string "This RELIC has already answered.\n"
	.string "Return to the ALPH scientist.$"

