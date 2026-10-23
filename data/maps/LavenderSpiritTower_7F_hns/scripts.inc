// New PRU HNS spirit-tower instance; original FRLG tower scripts remain untouched.
LavenderSpiritTower_7F_hns_MapScripts::
	.byte 0

// After defeating/catching both guardians, Mimikyu can be caught.
// Defeated Mimikyu disappears for this visit, but returns when the map reloads.
LavenderSpiritTower_7F_EventScript_Mimikyu::
	lock
	faceplayer
	goto_if_unset FLAG_PRU_CUBONE_MAROGHOST_RESOLVED, LavenderSpiritTower_7F_EventScript_Locked
	goto_if_unset FLAG_PRU_CUBONE_OSTEODIAN_RESOLVED, LavenderSpiritTower_7F_EventScript_Locked
	goto_if_set FLAG_PRU_CUBONE_MIMIKYU_CAUGHT, LavenderSpiritTower_7F_EventScript_Done
	msgbox LavenderSpiritTower_7F_Text_Reveal
	playmoncry SPECIES_MIMIKYU_DISGUISED, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_MIMIKYU_DISGUISED, 70
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, LavenderSpiritTower_7F_EventScript_Caught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, LavenderSpiritTower_7F_EventScript_Fainted
	goto LavenderSpiritTower_7F_EventScript_Done

LavenderSpiritTower_7F_EventScript_Caught::
	setflag FLAG_PRU_CUBONE_MIMIKYU_CAUGHT
	removeobject LOCALID_LAVENDER_SPIRIT_MIMIKYU
	msgbox LavenderSpiritTower_7F_Text_Caught
	release
	end

LavenderSpiritTower_7F_EventScript_Fainted::
	removeobject LOCALID_LAVENDER_SPIRIT_MIMIKYU
	msgbox LavenderSpiritTower_7F_Text_Fainted
	release
	end

LavenderSpiritTower_7F_EventScript_Locked::
	msgbox LavenderSpiritTower_7F_Text_Locked
LavenderSpiritTower_7F_EventScript_Done::
	release
	end

LavenderSpiritTower_7F_EventScript_Cubone::
	goto_if_set FLAG_PRU_CUBONE_MIMIKYU_CAUGHT, LavenderSpiritTower_7F_EventScript_CuboneHappy
	msgbox LavenderSpiritTower_7F_Text_Cubone, MSGBOX_NPC
	end

LavenderSpiritTower_7F_EventScript_CuboneHappy::
	msgbox LavenderSpiritTower_7F_Text_CuboneHappy, MSGBOX_NPC
	end

LavenderSpiritTower_7F_Text_Reveal:
	.string "A familiar PIKACHU-shaped\n"
	.string "silhouette trembles in the mist.\p"
	.string "It isn't haunting CUBONE.\p"
	.string "It came here to protect a\n"
	.string "lonely friend.\p"
	.string "MIMIKYU steps into the light!$"

LavenderSpiritTower_7F_Text_Caught:
	.string "MIMIKYU has found a new friend!\p"
	.string "CUBONE's cries finally stop.$"

LavenderSpiritTower_7F_Text_Fainted:
	.string "MIMIKYU slips into the fog.\p"
	.string "Perhaps it will return if\n"
	.string "you visit this place again.$"

LavenderSpiritTower_7F_Text_Locked:
	.string "A trembling shadow waits.\p"
	.string "First calm the spirits guarding\n"
	.string "CUBONE's memories.$"

LavenderSpiritTower_7F_Text_Cubone:
	.string "CUBONE: Cu...bone?\p"
	.string "It glances toward the small\n"
	.string "PIKACHU-shaped shadow.$"

LavenderSpiritTower_7F_Text_CuboneHappy:
	.string "CUBONE: Cubone!\p"
	.string "It seems less lonely now.$"
