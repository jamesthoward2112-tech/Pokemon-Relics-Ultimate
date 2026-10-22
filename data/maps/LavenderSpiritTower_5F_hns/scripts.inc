// New PRU HNS spirit-tower instance; original FRLG tower scripts remain untouched.
LavenderSpiritTower_5F_hns_MapScripts::
	.byte 0

// The old tower's first guardian can be caught OR defeated.
LavenderSpiritTower_5F_EventScript_Maroghost::
	lockall
	goto_if_set FLAG_PRU_CUBONE_MAROGHOST_RESOLVED, LavenderSpiritTower_5F_EventScript_Done
	msgbox LavenderSpiritTower_5F_Text_Mother
	playmoncry SPECIES_MAROGHOST, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_MAROGHOST, 66
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, LavenderSpiritTower_5F_EventScript_Resolved
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, LavenderSpiritTower_5F_EventScript_Resolved
	msgbox LavenderSpiritTower_5F_Text_Retreat
	releaseall
	end

LavenderSpiritTower_5F_EventScript_Resolved::
	setflag FLAG_PRU_CUBONE_MAROGHOST_RESOLVED
	setvar VAR_PRU_CUBONE_STAGE_MAROGHOST, 1
	msgbox LavenderSpiritTower_5F_Text_Calmed
LavenderSpiritTower_5F_EventScript_Done::
	releaseall
	end

LavenderSpiritTower_5F_Text_Mother:
	.string "A mother's grief fills the air.\p"
	.string "A spectral MAROGHOST appears!$"

LavenderSpiritTower_5F_Text_Retreat:
	.string "MAROGHOST slips into the mist.\n"
	.string "Its grief remains unresolved.$"

LavenderSpiritTower_5F_Text_Calmed:
	.string "MAROGHOST's restless heart\n"
	.string "finally grows quiet.\p"
	.string "A deeper tremor shakes the tower.$"
