// New PRU HNS spirit-tower instance; original FRLG tower scripts remain untouched.
LavenderSpiritTower_6F_hns_MapScripts::
	.byte 0

// Osteodian is stage two, and can also be caught or defeated.
// Its trigger lies before the seventh-floor stairs.
LavenderSpiritTower_6F_EventScript_Osteodian::
	lockall
	goto_if_set FLAG_PRU_CUBONE_OSTEODIAN_RESOLVED, LavenderSpiritTower_6F_EventScript_Done
	goto_if_unset FLAG_PRU_CUBONE_MAROGHOST_RESOLVED, LavenderSpiritTower_6F_EventScript_StillGrieving
	msgbox LavenderSpiritTower_6F_Text_BonesAwaken
	playmoncry SPECIES_OSTEODIAN, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_OSTEODIAN, 68
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, LavenderSpiritTower_6F_EventScript_Resolved
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, LavenderSpiritTower_6F_EventScript_Resolved
	msgbox LavenderSpiritTower_6F_Text_Return
	releaseall
	end

LavenderSpiritTower_6F_EventScript_Resolved::
	setflag FLAG_PRU_CUBONE_OSTEODIAN_RESOLVED
	setvar VAR_PRU_CUBONE_STAGE_OSTEODIAN, 1
	msgbox LavenderSpiritTower_6F_Text_Calmed
LavenderSpiritTower_6F_EventScript_Done::
	releaseall
	end

LavenderSpiritTower_6F_EventScript_StillGrieving::
	msgbox LavenderSpiritTower_6F_Text_MotherFirst
	releaseall
	end

LavenderSpiritTower_6F_Text_BonesAwaken:
	.string "The bones of the old tower\n"
	.string "begin to rattle!\p"
	.string "OSTEODIAN stands guard!$"

LavenderSpiritTower_6F_Text_Return:
	.string "The bone guardian vanishes.\n"
	.string "Its watch is not yet over.$"

LavenderSpiritTower_6F_Text_Calmed:
	.string "OSTEODIAN's vigil has ended.\p"
	.string "A small shadow calls from above.$"

LavenderSpiritTower_6F_Text_MotherFirst:
	.string "The mother's cries echo below.\n"
	.string "Something is still unresolved.$"
