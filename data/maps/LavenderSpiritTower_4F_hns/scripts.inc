// New PRU HNS spirit-tower instance; original FRLG tower scripts remain untouched.
LavenderSpiritTower_4F_hns_MapScripts::
	.byte 0

LavenderSpiritTower_4F_EventScript_Channeler::
	msgbox LavenderSpiritTower_4F_Text_Channeler, MSGBOX_NPC
	end

LavenderSpiritTower_4F_Text_Channeler:
	.string "The mist thickens above.\p"
	.string "If you need to rest, an\n"
	.string "ESCAPE ROPE will return you\n"
	.string "safely to MR.FUJI.$"
