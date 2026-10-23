// New PRU HNS spirit-tower instance; original FRLG tower scripts remain untouched.
LavenderSpiritTower_1F_hns_MapScripts::
	.byte 0

LavenderSpiritTower_1F_EventScript_MemorialSign::
	msgbox LavenderSpiritTower_1F_Text_Entry, MSGBOX_SIGN
	end

LavenderSpiritTower_1F_Text_Entry:
	.string "The memories of fallen POKeMON\n"
	.string "linger in these halls.$"
