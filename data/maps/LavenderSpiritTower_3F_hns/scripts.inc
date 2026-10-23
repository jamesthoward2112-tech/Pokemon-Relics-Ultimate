// New PRU HNS spirit-tower instance; original FRLG tower scripts remain untouched.
LavenderSpiritTower_3F_hns_MapScripts::
	.byte 0

LavenderSpiritTower_3F_EventScript_Channeler::
	msgbox LavenderSpiritTower_3F_Text_Channeler, MSGBOX_NPC
	end

LavenderSpiritTower_3F_Text_Channeler:
	.string "The old tower remembers grief.\p"
	.string "Even now, lost spirits wander\n"
	.string "through its memories.$"
