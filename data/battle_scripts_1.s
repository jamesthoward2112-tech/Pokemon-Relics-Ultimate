Warning: truncated output (original token count: 69715)
Total output lines: 8459

#include "config/general.h"
#include "config/battle.h"
#include "constants/global.h"
#include "constants/battle.h"
#include "constants/pokemon.h"
#include "constants/battle_arena.h"
#include "constants/battle_move_resolution.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_anim.h"
#include "constants/battle_string_ids.h"
#include "constants/abilities.h"
#include "constants/hold_effects.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/game_stat.h"
#include "constants/trainers.h"
#include "constants/species.h"
#include "constants/generational_changes.h"
	.include "asm/macros.inc"
	.include "asm/macros/battle_script.inc"
	.include "constants/constants.inc"

	.section script_data, "aw", %progbits

BattleScript_TryRevertWeatherform:
    setbyte gEffectBattler, 0
    sortbattlers
BattleScript_TryRevertWeatherformLoop:
    tryrevertweatherform
    addbyte gEffectBattler, 1
    jumpifbytenotequal gEffectBattler, gBattlersCount, BattleScript_TryRevertWeatherformLoop
    return

BattleScript_FickleBeamMessage::
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_FICKLEBEAMDOUBLED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MagnitudeMessage::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MAGNITUDESTRENGTH
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_Terastallization::
	@ TODO: no string prints in S/V, but right now this helps with clarity
	printstring STRINGID_PKMNSTORINGENERGY
	playanimation BS_ATTACKER, B_ANIM_TERA_CHARGE
	waitanimation
	applyterastallization
	playanimation BS_ATTACKER, B_ANIM_TERA_ACTIVATE
	waitanimation
	printstring STRINGID_PKMNTERASTALLIZEDINTO
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_TeraFormChange::
	@ TODO: no string prints in S/V, but right now this helps with clarity
	printstring STRINGID_PKMNSTORINGENERGY
	handleformchange BS_ATTACKER, 0, FALSE @ Prevent species name from overriting type name
	handleformchange BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_TERA_CHARGE
	waitanimation
	applyterastallization
	playanimation BS_ATTACKER, B_ANIM_TERA_ACTIVATE
	waitanimation
	printstring STRINGID_PKMNTERASTALLIZEDINTO
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	end3

BattleScript_LowerAtkSpAtk::
	jumpifstat BS_EFFECT_BATTLER, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_LowerAtkSpAtkDoAnim
	jumpifstat BS_EFFECT_BATTLER, CMP_EQUAL, STAT_SPATK, MIN_STAT_STAGE, BattleScript_LowerAtkSpAtkEnd
BattleScript_LowerAtkSpAtkDoAnim::
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_LowerAtkSpAtkTrySpAtk, BIT_SPATK
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_LowerAtkSpAtkTrySpAtk::
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_LowerAtkSpAtkEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_LowerAtkSpAtkEnd:
	return

BattleScript_EffectSpicyExtract::
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
	accuracycheck BattleScript_MoveMissedPause
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_SpicyExtract_CheckShouldSkipAttackAnim
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_SpicyExtract_CheckShouldSkipAttackAnim
	goto BattleScript_ButItFailed
BattleScript_SpicyExtract_CheckShouldSkipAttackAnim:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_SpicyExtract_RaiseAtk
	goto BattleScript_SpicyExtract_SkipAttackAnim
BattleScript_SpicyExtract_RaiseAtk:
	attackanimation
	waitanimation
BattleScript_SpicyExtract_SkipAttackAnim:
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectSpicyExtractDefenseDown
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectSpicyExtractDefenseDown:
	setstatchanger STAT_DEF, 2, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectSpicyExtract_End
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectSpicyExtract_End:
	goto BattleScript_MoveEnd

BattleScript_EffectTidyUp::
	attackcanceler
	pause B_WAIT_TIME_MED
	waitstate
	saveattacker
	savetarget
	trytidyup FALSE, BattleScript_EffectTidyUpDoMoveAnimation
	restoreattacker
	restoretarget
	goto BattleScript_EffectDragonDanceFromStatUp

BattleScript_EffectTidyUpDoMoveAnimation::
	attackanimation
	waitanimation
	trytidyup TRUE, NULL
	printstring STRINGID_TIDYINGUPCOMPLETE
	waitmessage B_WAIT_TIME_LONG
	restoreattacker
	restoretarget
	goto BattleScript_EffectDragonDanceFromStatUp

BattleScript_EffectShedTail::
	attackcanceler
	waitstate
	jumpifvolatile BS_ATTACKER, VOLATILE_SUBSTITUTE, BattleScript_AlreadyHasSubstitute
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_ButItFailed
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_ButItFailed
	setsubstitute
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_SUBSTITUTE_FAILED, BattleScript_SubstituteString
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printstring STRINGID_SHEDITSTAIL
	waitmessage B_WAIT_TIME_LONG
	moveendto MOVEEND_ATTACKER_VISIBLE
	moveendfrom MOVEEND_TARGET_VISIBLE
	call BattleScript_MoveSwitchOpenPartyScreenReturnWithNoAnim
	switchinanim BS_ATTACKER, FALSE, TRUE
	waitstate
	switchineffects BS_ATTACKER
	switchinevents
	end

BattleScript_EffectPsychicNoise::
	printstring STRINGID_PKMNPREVENTEDFROMHEALING
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectFilletAway::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_FilletAwayTryAttack
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_FilletAwayTryAttack
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ButItFailed
BattleScript_FilletAwayTryAttack::
	halvehp BattleScript_ButItFailed
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_FilletAwayTrySpAtk, BIT_SPATK | BIT_SPEED
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FilletAwayTrySpAtk::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_FilletAwayTrySpeed, BIT_SPEED
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FilletAwayTrySpeed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_FilletAwayEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FilletAwayEnd::
	clearmoveresultflags MOVE_RESULT_NO_EFFECT
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	goto BattleScript_MoveEnd

BattleScript_EffectDoodle::
	attackcanceler
	trycopyability BS_ATTACKER, BattleScript_ButItFailed
	saveattacker
	attackanimation
	waitanimation
	setbyte gBattleCommunication, 0
	goto BattleScript_EffectDoodle_AfterCopy
BattleScript_EffectDoodle_CopyAbility:
	trycopyability BS_ATTACKER, BattleScript_EffectDoodleMoveEnd
BattleScript_EffectDoodle_AfterCopy:
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUpOverwriteThenNormal
	recordability BS_ATTACKER
	printstring STRINGID_PKMNCOPIEDFOE
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_EffectDoodleMoveEnd
	addbyte gBattleCommunication, 1
	jumpifnoally BS_ATTACKER, BattleScript_EffectDoodleMoveEnd
	setallytonextattacker BattleScript_EffectDoodle_CopyAbility
BattleScript_EffectDoodleMoveEnd:
	restoreattacker
	goto BattleScript_MoveEnd

BattleScript_SyrupBombActivates::
	printstring STRINGID_TARGETCOVEREDINSTICKYCANDYSYRUP
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SyrupBombEndTurn::
	flushtextbox
	playanimation BS_ATTACKER, B_ANIM_SYRUP_BOMB_SPEED_DROP
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange BS_ATTACKER, STAT_CHANGE_CHECK_PREVENTION | STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_SyrupBombTurnDmgEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SyrupBombTurnDmgEnd:
	end2

BattleScript_MoveSwitchPursuitEnd:
	call BattleScript_MoveSwitchPursuitRet
	end

BattleScript_MoveSwitchPursuitRet:
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_MoveSwitchEnd
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_MoveSwitchEnd
	printstring STRINGID_PKMNWENTBACK
	waitmessage B_WAIT_TIME_SHORT
	jumpifnopursuitswitchdmg BattleScript_MoveSwitchOpenPartyScreenRet
	return

BattleScript_MoveSwitch::
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_MoveSwitchEnd
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_MoveSwitchEnd
	printstring STRINGID_PKMNWENTBACK
	waitmessage B_WAIT_TIME_SHORT
BattleScript_MoveSwitchOpenPartyScreen::
	call BattleScript_MoveSwitchOpenPartyScreenRet
BattleScript_MoveSwitchEnd:
	end

BattleScript_MoveSwitchOpenPartyScreenRet:
	call BattleScript_MoveSwitchOpenPartyScreenReturnWithNoAnim
	switchinanim BS_ATTACKER, FALSE, FALSE
	waitstate
	switchineffects BS_ATTACKER
	switchinevents
	return

BattleScript_MoveSwitchOpenPartyScreenReturnWithNoAnim:
	openpartyscreen BS_ATTACKER, BattleScript_MoveSwitchEnd
	waitstate
	returntoball BS_ATTACKER, FALSE
	switchoutabilities BS_ATTACKER
	switchhandleorder BS_ATTACKER, 2
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring STRINGID_SWITCHINMON
	return

BattleScript_EffectPledge::
	attackcanceler
	setpledge BattleScript_HitFromAccCheck
	pause B_WAIT_TIME_MED
	printstring STRINGID_WAITINGFORPARTNERSMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCombinedPledge_Water::
	call BattleScript_EffectHit_Pledge
	setpledgestatus BS_ATTACKER, SIDE_STATUS_RAINBOW
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_ARAINBOWAPPEAREDONSIDE
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RAINBOW
	waitanimation
	goto BattleScript_MoveEnd

BattleScript_TheRainbowDisappeared::
	printstring STRINGID_THERAINBOWDISAPPEARED
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_EffectCombinedPledge_Fire::
	call BattleScript_EffectHit_Pledge
	setpledgestatus BS_TARGET, SIDE_STATUS_SEA_OF_FIRE
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_SEAOFFIREENVELOPEDSIDE
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_TARGET, B_ANIM_SEA_OF_FIRE
	waitanimation
	goto BattleScript_MoveEnd

BattleScript_HurtByTheSeaOfFire::
	printstring STRINGID_HURTBYTHESEAOFFIRE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoTurnDmg

BattleScript_TheSeaOfFireDisappeared::
	printstring STRINGID_THESEAOFFIREDISAPPEARED
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_EffectCombinedPledge_Grass::
	call BattleScript_EffectHit_Pledge
	setpledgestatus BS_TARGET, SIDE_STATUS_SWAMP
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_SWAMPENVELOPEDSIDE
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_TARGET, B_ANIM_SWAMP
	waitanimation
	goto BattleScript_MoveEnd

BattleScript_TheSwampDisappeared::
	printstring STRINGID_THESWAMPDISAPPEARED
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_EffectHit_Pledge::
	pause B_WAIT_TIME_MED
	printstring STRINGID_THETWOMOVESBECOMEONE
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_EffectHit_RetFromAccCheck
	return

BattleScript_MoveEffectSaltCure::
	printstring STRINGID_TARGETISBEINGSALTCURED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SaltCureExtraDamage::
	playanimation BS_ATTACKER, B_ANIM_SALT_CURE_DAMAGE, NULL
	waitanimation
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printstring STRINGID_TARGETISHURTBYSALTCURE
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	tryactivateitem BS_ATTACKER, ACTIVATION_ON_HP_THRESHOLD
	end2

BattleScript_EffectCorrosiveGas::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	jumpifsubstituteblocks BattleScript_CorrosiveGasFail
	jumpifcantloseitem BattleScript_CorrosiveGasFail
	attackanimation
	waitanimation
	jumpifability BS_TARGET, ABILITY_STICKY_HOLD, BattleScript_StickyHoldActivates
	setlastuseditem BS_TARGET
	removeitem BS_TARGET
	printstring STRINGID_PKMNITEMMELTED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_CorrosiveGasFail:
	pause B_WAIT_TIME_SHORT
	setmoveresultflags MOVE_RESULT_FAILED
	printstring STRINGID_NOEFFECTONTARGET
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectTakeHeart::
	attackcanceler
	curestatuswithmove BattleScript_CalmMindTryToRaiseStats
	attackanimation
	waitanimation
	updatestatusicon BS_ATTACKER
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CalmMindStatRaise
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_CalmMindStatRaise
	goto BattleScript_CantRaiseMultipleStats

BattleScript_EffectRevivalBlessing::
	attackcanceler
	tryrevivalblessing BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNREVIVEDREADYTOFIGHT
	waitmessage B_WAIT_TIME_LONG
	jumpifbyte CMP_EQUAL, gBattleCommunication, TRUE, BattleScript_EffectRevivalBlessingSendOut
	goto BattleScript_MoveEnd

BattleScript_EffectRevivalBlessingSendOut:
	getswitchedmondata BS_SCRIPTING
	switchindataupdate BS_SCRIPTING
	hpthresholds BS_SCRIPTING
	switchinanim BS_SCRIPTING, FALSE, FALSE
	waitstate
	switchineffects BS_SCRIPTING
	switchinevents
	goto BattleScript_MoveEnd

BattleScript_StealthRockActivates::
	setstealthrock BattleScript_StealthRockActivatesRet
	printfromtable gDmgHazardsStringIds
	waitmessage B_WAIT_TIME_PRU_HAZARD_MESSAGE
BattleScript_StealthRockActivatesRet:
	return

BattleScript_SpikesActivates::
	trysetspikes BattleScript_SpikesActivatesRet
	printfromtable gDmgHazardsStringIds
	waitmessage B_WAIT_TIME_PRU_HAZARD_MESSAGE
BattleScript_SpikesActivatesRet:
	return

BattleScript_EffectTeatime::
	attackcanceler
	checkteatimetargets BattleScript_ButItFailed
	attackanimation
	waitanimation
	movevaluescleanup
	goto BattleScript_EffectTeatimeGetTarget
BattleScript_EffectTeatimeNextTarget:
	jumpifnoberry BS_TARGET, BattleScript_EffectTeatimeGetTarget
	setbyte sBERRY_OVERRIDE, TRUE @ override the requirements for eating berries
	consumeberry BS_TARGET, TRUE @ consume the berry, then restore the item from changedItems
	setbyte sBERRY_OVERRIDE, FALSE
	removeitem BS_TARGET
	moveendcase MOVEEND_NEXT_TARGET
BattleScript_EffectTeatimeGetTarget:
	getpossiblenexttarget BattleScript_EffectTeatimeNextTarget
	moveendfrom MOVEEND_ITEM_EFFECTS_ATTACKER_2
	end

BattleScript_AffectionBasedEndurance::
	playanimation BS_TARGET, B_ANIM_AFFECTION_HANGED_ON
	printstring STRINGID_TARGETTOUGHEDITOUT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AffectionBasedStatusHeal::
	jumpifstatus BS_ATTACKER, STATUS1_POISON | STATUS1_TOXIC_POISON, BattleScript_AffectionBasedStatus_HealPoisonString
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP, BattleScript_AffectionBasedStatus_HealSleepString
	jumpifstatus BS_ATTACKER, STATUS1_PARALYSIS, BattleScript_AffectionBasedStatus_HealParalysisString
	jumpifstatus BS_ATTACKER, STATUS1_BURN, BattleScript_AffectionBasedStatus_HealBurnString
	jumpifstatus BS_ATTACKER, STATUS1_FREEZE, BattleScript_AffectionBasedStatus_HealFreezeString
	jumpifstatus BS_ATTACKER, STATUS1_FROSTBITE, BattleScript_AffectionBasedStatus_HealFrostbiteString
	end2
BattleScript_AffectionBasedStatus_HealPoisonString:
	printstring STRINGID_ATTACKEREXPELLEDTHEPOISON
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealSleepString:
	printstring STRINGID_ATTACKERSHOOKITSELFAWAKE
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealParalysisString:
	printstring STRINGID_ATTACKERBROKETHROUGHPARALYSIS
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealBurnString:
	printstring STRINGID_ATTACKERHEALEDITSBURN
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealFreezeString:
	printstring STRINGID_ATTACKERMELTEDTHEICE
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealFrostbiteString:
	printstring STRINGID_ATTACKERHEALEDITSFROSTBITE
BattleScript_AffectionBasedStatusHeal_Continue:
	waitmessage B_WAIT_TIME_LONG
	clearstatus BS_ATTACKER
	waitstate
	updatestatusicon BS_ATTACKER
	waitstate
	end2

BattleScript_ShellTrapSetUp::
	flushtextbox
	playanimation BS_ATTACKER, B_ANIM_SHELL_TRAP_SETUP, NULL
	printstring STRINGID_PREPARESHELLTRAP
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_EffectShellTrap::
	attackcanceler
	jumpifshelltrap BS_ATTACKER, BattleScript_HitFromAccCheck
	printstring STRINGID_SHELLTRAPDIDNTWORK
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCourtChange::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	swapsidestatuses
	attackanimation
	waitanimation
	printstring STRINGID_COURTCHANGE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_BeakBlastSetUp::
	flushtextbox
	playanimation BS_ATTACKER, B_ANIM_BEAK_BLAST_SETUP, NULL
	printstring STRINGID_HEATUPBEAK
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_BeakBlastBurn::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectBurn
	return

BattleScript_EffectFling::
	attackcanceler
	accuracycheck BattleScript_FlingMissed
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNFLUNG
	waitmessage B_WAIT_TIME_SHORT
	damagecalc
	removeitem BS_ATTACKER
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET, MOVE_DAMAGE_HP_UPDATE
	datahpupdate BS_TARGET, MOVE_DAMAGE_HP_UPDATE
	critmessage
	waitmessage B_WAIT_TIME_MED
	resultmessage
	waitmessage B_WAIT_TIME_MED
	tryflingholdeffect
	goto BattleScript_FlingEnd

BattleScript_EffectFlingConsumeBerry::
	savebattleritem
	battleritemtolastuseditem
	setbyte sBERRY_OVERRIDE, 1 @ override the requirements for eating berries
	orword gHitMarker, HITMARKER_DISABLE_ANIMATION
	consumeberry BS_TARGET, FALSE
	bicword gHitMarker, HITMARKER_DISABLE_ANIMATION
	setbyte sBERRY_OVERRIDE, 0
	restorebattleritem
BattleScript_FlingEnd:
	trysymbiosis BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_FlingFailConsumeItem::
	removeitem BS_ATTACKER
	goto BattleScript_ButItFailed

BattleScript_TargetAvoidsAttackConsumeFlingItem::
	pause B_WAIT_TIME_SHORT
	printfromtable gMissStringIds
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

BattleScript_FlingBlockedByShieldDust::
	printstring STRINGID_ITEMWASUSEDUP
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_FlingEnd

BattleScript_FlingMissed:
	removeitem BS_ATTACKER
	goto BattleScript_MoveMissedPause

BattleScript_EffectClangorousSoul::
	attackcanceler
	cutonethirdhpandraisestats BattleScript_ButItFailed
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	call BattleScript_AllStatsUp
	goto BattleScript_MoveEnd

BattleScript_EffectOctolock::
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
	accuracycheck BattleScript_MoveMissedPause
	trysetoctolock BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_OctolockEndTurn::
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_OctolockTryLowerSpDef, BIT_SPDEF
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_OctolockTryLowerSpDef:
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_OctlockTurnDmgEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_OctlockTurnDmgEnd:
	end2

BattleScript_EffectPoltergeist::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	setpoltergeistmessage
	printstring STRINGID_ABOUTTOUSEPOLTERGEIST
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromDamageCalc

BattleScript_EffectTarShot::
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
	accuracycheck BattleScript_MoveMissedPause
	cantarshotwork BattleScript_ButItFailed
	setstatchanger STAT_SPEED, 1, TRUE
	attackanimation
	waitanimation
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_TryTarShot
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryTarShot:
	trytarshot BattleScript_MoveEnd
	printstring STRINGID_PKMNBECAMEWEAKERTOFIRE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectNoRetreat::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	jumpifvolatile BS_TARGET, VOLATILE_NO_RETREAT, BattleScript_ButItFailed
	setvolatile BS_TARGET, VOLATILE_NO_RETREAT
	attackanimation
	waitanimation
	call BattleScript_AllStatsUp
	jumpifvolatile BS_TARGET, VOLATILE_ESCAPE_PREVENTION, BattleScript_MoveEnd
	seteffectprimary BS_TARGET, BS_TARGET, MOVE_EFFECT_PREVENT_ESCAPE
	printstring STRINGID_CANTESCAPEDUETOUSEDMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_BothCanNoLongerEscape::
	printstring STRINGID_BOTHCANNOLONGERESCAPE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectHyperspaceFury::
	jumpifspecies SPECIES_HOOPA_UNBOUND, BattleScript_EffectHit
	jumpifspecies SPECIES_HOOPA_CONFINED, BattleScript_ButHoopaCantUseIt
	goto BattleScript_PokemonCantUseTheMove

BattleScript_ButHoopaCantUseIt:
	printstring STRINGID_BUTHOOPACANTUSEIT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_HyperspaceFuryRemoveProtect::
	printstring STRINGID_BROKETHROUGHPROTECTION
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectIonDeluge::
	printstring STRINGID_IONDELUGEON
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectHaze::
	printstring STRINGID_STATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectLeechSeed::
	printstring STRINGID_PKMNSEEDED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MoveEffectReflect::
	printfromtable gReflectLightScreenSafeguardStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectLightScreen::
	printfromtable gReflectLightScreenSafeguardStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectStuffCheeks::
	attackcanceler
	attackanimation
	waitanimation
	setbyte sBERRY_OVERRIDE, 1
	orword gHitMarker, HITMARKER_DISABLE_ANIMATION
	consumeberry BS_ATTACKER, TRUE
	bicword gHitMarker, HITMARKER_DISABLE_ANIMATION
	setbyte sBERRY_OVERRIDE, 0
	removeitem BS_ATTACKER
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_StuffCheeksEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StuffCheeksEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectDecorate::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_DecorateBoost
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_DecorateBoost
	goto BattleScript_ButItFailed
BattleScript_DecorateBoost:
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_DecorateBoostSpAtk, BIT_SPATK
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_DecorateBoostSpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DecorateBoostSpAtk:
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCoaching::
	attackcanceler
	jumpifnoally BS_ATTACKER, BattleScript_ButItFailed
	copybyte gBattlerTarget, gBattlerAttacker
	setallytonexttarget EffectCoaching_CheckAllyStats
	goto BattleScript_ButItFailed
EffectCoaching_CheckAllyStats:
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_CoachingWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_DEF, MAX_STAT_STAGE, BattleScript_CoachingWorks
	goto BattleScript_ButItFailed   @ ally at max atk, def
BattleScript_CoachingWorks:
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_CoachingBoostDef, BIT_DEF
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_CoachingBoostDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoachingBoostDef:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectJungleHealing::
	attackcanceler
	jumpifteamhealthy BattleScript_ButItFailed
	attackanimation
	waitanimation
	copybyte gBattlerTarget, gBattlerAttacker
	setbyte gBattleCommunication, 0
JungleHealing_RestoreTargetHealth:
	copybyte gBattlerAttacker, gBattlerTarget
	tryhealquarterhealth BS_TARGET, BattleScript_JungleHealing_TryCureStatus
	healthbarupdate BS_TARGET, PASSIVE_HP_UPDATE
	datahpupdate BS_TARGET, PASSIVE_HP_UPDATE
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_JungleHealing_TryCureStatus:
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_JungleHealingCureStatus
	goto BattleScript_JungleHealingTryRestoreAlly
BattleScript_JungleHealingCureStatus:
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
BattleScript_JungleHealingTryRestoreAlly:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_MoveEnd
	addbyte gBattleCommunication, 1
	jumpifnoally BS_TARGET, BattleScript_MoveEnd
	setallytonexttarget JungleHealing_RestoreTargetHealth
	goto BattleScript_MoveEnd

BattleScript_EffectLifeDew::
	attackcanceler
	jumpiffullhp BS_ATTACKER, BattleScript_EffectLifeDewCheckPartner
	copybyte gBattlerTarget, gBattlerAttacker
	attackanimation
	waitanimation
	call BattleScript_EffectLifeDewHealing
	jumpifabsent BS_ATTACKER_PARTNER, BattleScript_EffectLifeDewEnd
	jumpiffullhp BS_ATTACKER_PARTNER, BattleScript_EffectLifeDewEnd
	setallytonexttarget BattleScript_EffectLifeDewNextTarget
BattleScript_EffectLifeDewNextTarget:
	call BattleScript_EffectLifeDewHealing
BattleScript_EffectLifeDewEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectLifeDewCheckPartner:
	jumpifabsent BS_ATTACKER_PARTNER, BattleScript_ButItFailed
	jumpiffullhp BS_ATTACKER_PARTNER, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setallytonexttarget BattleScript_EffectLifeDewNextTarget

BattleScript_EffectLifeDewHealing:
	tryhealquarterhealth BS_TARGET, BattleScript_EffectLifeDewEnd
	healthbarupdate BS_TARGET, PASSIVE_HP_UPDATE
	datahpupdate BS_TARGET, PASSIVE_HP_UPDATE
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectAllySwitch::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	tryallyswitch BattleScript_ButItFailed
	attackanimation
	waitanimation
	@ The actual data/gfx swap happens in the move animation. Here it's just the gBattlerAttacker / scripting battler change
	allyswitchswapbattlers
	printstring STRINGID_ALLYSWITCHPOSITION
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFairyLock::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	trysetfairylock BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_NOONEWILLBEABLETORUNAWAY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_RemoveFireType::
	printstring STRINGID_ATTACKERLOSTFIRETYPE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_RemoveElectricType::
	printstring STRINGID_ATTACKERLOSTELECTRICTYPE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_RemoveGenericType::
	printstring STRINGID_ATTACKERLOSTITSTYPE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_DefDown::
	modifybattlerstatstage BS_TARGET, STAT_DEF, DECREASE, 1, BattleScript_DefDown_Ret, ANIM_ON
BattleScript_DefDown_Ret:
	return

BattleScript_EffectPurify::
	attackcanceler
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_PurifyWorks
	goto BattleScript_ButItFailed
BattleScript_PurifyWorks:
	attackanimation
	waitanimation
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
	printstring STRINGID_ATTACKERCUREDTARGETSTATUS
	waitmessage B_WAIT_TIME_LONG
	tryhealhalfhealth BS_ATTACKER, BattleScript_AlreadyAtFullHp
	goto BattleScript_RestoreHp

BattleScript_EffectStrengthSap::
	setstatchanger STAT_ATK, 1, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
	accuracycheck BattleScript_MoveMissedPause
	jumpifstatignorecontrary BS_TARGET, CMP_EQUAL, STAT_ATK, MIN_STAT_STAGE, BattleScript_StrengthSapPrintStatMessage
	attackanimation
	waitanimation
	getstatvalue STAT_ATK
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGE_EMPTY, BattleScript_MoveEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_StrengthSapPrintStatMessage:
	pause B_WAIT_TIME_SHORT
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MoveEffectIncinerate::
	printstring STRINGID_INCINERATEBURN
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectBugBite::
	printstring STRINGID_BUGBITE
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_DISABLE_ANIMATION
	setbyte sBERRY_OVERRIDE, 1   @ override the requirements for eating berries
	savetarget
	consumeberry BS_ATTACKER, FALSE
	bicword gHitMarker, HITMARKER_DISABLE_ANIMATION
	setbyte sBERRY_OVERRIDE, 0
	restoretarget
	trysymbiosis BS_TARGET
	return

BattleScript_MoveEffectCoreEnforcer::
	setgastroacid BattleScript_CoreEnforcerRet
	printstring STRINGID_PKMNSABILITYSUPPRESSED
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	call BattleScript_TryRevertWeatherform
	flushtextbox
	tryendneutralizinggas
BattleScript_CoreEnforcerRet:
	return

BattleScript_EffectLaserFocus::
	attackcanceler
	trysetvolatile BS_ATTACKER, VOLATILE_LASER_FOCUS, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_LASERFOCUS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_VCreateStatLoss::
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_VCreateStatAnim
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_VCreateStatAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_VCreateStatLossRet
BattleScript_VCreateStatAnim:
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange BS_ATTACKER, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_CERTAIN, BattleScript_VCreateTrySpDef, BIT_SPDEF | BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_VCreateTrySpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VCreateTrySpDef:
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange BS_ATTACKER, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_CERTAIN, BattleScript_VCreateTrySpeed, BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_VCreateTrySpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VCreateTrySpeed:
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange BS_ATTACKER, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_CERTAIN, BattleScript_VCreateStatLossRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_VCreateStatLossRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VCreateStatLossRet:
	return

BattleScript_EffectPartingShot::
	attackcanceler
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_EffectPartingShotTryAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MIN_STAT_STAGE, BattleScript_EffectPartingShotCantLowerMultipleStats
BattleScript_EffectPartingShotTryAtk:
	accuracycheck BattleScript_MoveMissedPause
	attackanimation
	waitanimation
	setbyte sB_ANIM_TARGETS_HIT, 0
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectPartingShotTrySpAtk, BIT_SPATK
	call BattleScript_EffectPartingShotMaybePrintStat
BattleScript_EffectPartingShotTrySpAtk:
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectPartingShotMaybeSwitch
	call BattleScript_EffectPartingShotMaybePrintStat
BattleScript_EffectPartingShotMaybeSwitch:
	jumpifgenconfiglowerthan CONFIG_B_PARTING_SHOT_SWITCH, GEN_7, BattleScript_EffectPartingShotSwitch
	jumpifbyte CMP_NOT_EQUAL, sB_ANIM_TARGETS_HIT, 0, BattleScript_EffectPartingShotSwitch
	goto BattleScript_MoveEnd

BattleScript_EffectPartingShotSwitch:
	moveendall
	goto BattleScript_MoveSwitchPursuitEnd

BattleScript_EffectPartingShotCantLowerMultipleStats:
	pause B_WAIT_TIME_SHORT
	setmoveresultflags MOVE_RESULT_FAILED
	call BattleScript_EffectPartingShotPrintWontDecrease
	setbyte sB_ANIM_TARGETS_HIT, 0
	goto BattleScript_EffectPartingShotMaybeSwitch

BattleScript_EffectPartingShotMaybePrintStat:
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_ATTACKER_STAT_CHANGED, BattleScript_EffectPartingShotPrintStat
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_CHANGED, BattleScript_EffectPartingShotPrintStat
	return

BattleScript_EffectPartingShotPrintStat:
	setbyte sB_ANIM_TARGETS_HIT, 1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectPartingShotPrintWontDecrease:
	jumpifability BS_TARGET, ABILITY_CONTRARY, BattleScript_EffectPartingShotPrintWontDecreaseContrary
	printstring STRINGID_STATSWONTDECREASE2
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectPartingShotPrintWontDecreaseContrary:
	swapattackerwithtarget
	printstring STRINGID_STATSWONTDECREASE2
	waitmessage B_WAIT_TIME_LONG
	swapattackerwithtarget
	return

BattleScript_EffectPowder::
	attackcanceler
	jumpifvolatile BS_TARGET, VOLATILE_POWDER, BattleScript_ButItFailed
	setvolatile BS_TARGET, VOLATILE_POWDER
	attackanimation
	waitanimation
	printstring STRINGID_COVEREDINPOWDER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectAromaticMist::
	attackcanceler
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_ButItFailed
	jumpiftargetally BattleScript_EffectAromaticMistWorks
	goto BattleScript_ButItFailed
BattleScript_EffectAromaticMistWorks:
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ONLY_CHECKING, BattleScript_EffectAromaticMistWontGoHigher
	attackanimation
	waitanimation
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectAromaticMistEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectAromaticMistEnd:
	goto BattleScript_MoveEnd
BattleScript_EffectAromaticMistWontGoHigher:
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage B_WAIT_TIME_LONG
	setmoveresultflags MOVE_RESULT_MISSED @ TODO: Is this even necessary?
	goto BattleScript_EffectAromaticMistEnd

BattleScript_EffectMagneticFlux::
	attackcanceler
	savetarget
	setbyte gBattleCommunication, 0
BattleScript_EffectMagneticFluxStart:
	jumpifability BS_TARGET, ABILITY_MINUS, BattleScript_EffectMagneticFluxCheckStats
	jumpifability BS_TARGET, ABILITY_PLUS, BattleScript_EffectMagneticFluxCheckStats
	goto BattleScript_EffectMagneticFluxLoop
BattleScript_EffectMagneticFluxCheckStats:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_EffectMagneticFluxTryDef
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_EffectMagneticFluxLoop
BattleScript_EffectMagneticFluxTryDef:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_EffectMagneticFluxSkipAnim
	attackanimation
	waitanimation
BattleScript_EffectMagneticFluxSkipAnim:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectMagneticFluxTrySpDef, BIT_SPDEF
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_EffectMagneticFluxTrySpDef
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectMagneticFluxTrySpDef:
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectMagneticFluxLoop
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_EffectMagneticFluxLoop
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectMagneticFluxLoop:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectMagneticFluxEnd
	jumpifnoally BS_ATTACKER, BattleScript_EffectMagneticFluxEnd
	setallytonexttarget BattleScript_EffectMagneticFluxStart
BattleScript_EffectMagneticFluxEnd:
	restoretarget
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_MoveEnd
	goto BattleScript_ButItFailed

BattleScript_EffectGearUp::
	attackcanceler
	savetarget
	setbyte gBattleCommunication, 0
BattleScript_EffectGearUpStart:
	jumpifability BS_TARGET, ABILITY_MINUS, BattleScript_EffectGearUpCheckStats
	jumpifability BS_TARGET, ABILITY_PLUS, BattleScript_EffectGearUpCheckStats
	goto BattleScript_EffectGearUpLoop
BattleScript_EffectGearUpCheckStats:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_EffectGearUpTryAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_EffectGearUpLoop
BattleScript_EffectGearUpTryAtk:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_EffectGearUpSkipAnim
	attackanimation
	waitanimation
BattleScript_EffectGearUpSkipAnim:
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectGearUpTrySpAtk, BIT_SPATK
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_EffectGearUpTrySpAtk
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectGearUpTrySpAtk:
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectGearUpLoop
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_EffectGearUpLoop
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectGearUpLoop:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectGearUpEnd
	jumpifnoally BS_ATTACKER, BattleScript_EffectGearUpEnd
	setallytonexttarget BattleScript_EffectGearUpStart
BattleScript_EffectGearUpEnd:
	restoretarget
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_MoveEnd
	goto BattleScript_ButItFailed

BattleScript_EffectAcupressure::
	attackcanceler
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectAcupressureTry
	jumpifvolatile BS_TARGET, VOLATILE_SUBSTITUTE, BattleScript_MoveMissedPause
BattleScript_EffectAcupressureTry:
	tryacupressure BattleScript_ButItFailed
	attackanimation
	waitanimation
	statbuffchange BS_TARGET, STAT_CHANGE_CERTAIN, BattleScript_MoveEnd
	printstring STRINGID_DEFENDERSSTATROSE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MoveEffectFeint::
	printstring STRINGID_FELLFORFEINT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectThirdType::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	trythirdtype BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_THIRDTYPEADDED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFlowerShield::
	attackcanceler
	savetarget
	setbyte gBattlerTarget, 0
	selectfirstvalidtarget
BattleScript_FlowerShieldIsAnyValidTarget:
	jumpifvolatile BS_TARGET, VOLATILE_SEMI_INVULNERABLE, BattleScript_FlowerShieldCheckNextTarget
	jumpiftype BS_TARGET, TYPE_GRASS, BattleScript_FlowerShieldLoopStart
BattleScript_FlowerShieldCheckNextTarget:
	jumpifnexttargetvalid BattleScript_FlowerShieldIsAnyValidTarget
	goto BattleScript_RestoreTargetButItFailed
BattleScript_FlowerShieldLoopStart:
	selectfirstvalidtarget
BattleScript_FlowerShieldLoop:
	movevaluescleanup
	jumpifvolatile BS_TARGET, VOLATILE_SEMI_INVULNERABLE, BattleScript_FlowerShieldMoveTargetEnd
	jumpiftype BS_TARGET, TYPE_GRASS, BattleScript_FlowerShieldLoop2
	goto BattleScript_FlowerShieldMoveTargetEnd
BattleScript_FlowerShieldLoop2:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_FlowerShieldMoveTargetEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_FlowerShieldDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGE_EMPTY, BattleScript_FlowerShieldMoveTargetEnd
	pause 21
	goto BattleScript_FlowerShieldString
BattleScript_FlowerShieldDoAnim:
	attackanimation
	waitanimation
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_FlowerShieldMoveTargetEnd
BattleScript_FlowerShieldString:
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FlowerShieldMoveTargetEnd:
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_FlowerShieldLoop
	restoretarget
	moveendfrom MOVEEND_ITEM_EFFECTS_ATTACKER_2
	end

BattleScript_EffectRototiller::
	attackcanceler
	getrototillertargets BattleScript_ButItFailed
	@ at least one battler is affected
	attackanimation
	waitanimation
	goto BattleScript_EffectRototillerGetTarget
BattleScript_RototillerLoop:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_RototillerCheckAffected
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_RototillerCantRaiseMultipleStats
BattleScript_RototillerCheckAffected:
	jumpifmoveresultflags MOVE_RESULT_NO_EFFECT, BattleScript_EffectRototillerGetTarget
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_RototillerTrySpAtk, BIT_SPATK
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_RototillerTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RototillerTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectRototillerMoves
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_EffectRototillerMoves
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectRototillerMoves:
	moveendcase MOVEEND_NEXT_TARGET
BattleScript_EffectRototillerGetTarget:
	getpossiblenexttarget BattleScript_RototillerLoop
	moveendfrom MOVEEND_ITEM_EFFECTS_ATTACKER_2
	end

BattleScript_RototillerCantRaiseMultipleStats:
	saveattacker
	copybyte gBattlerAttacker, gBattlerTarget
	printstring STRINGID_STATSWONTINCREASE2
	restoreattacker
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EffectRototillerGetTarget

BattleScript_RototillerNoEffect:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NOEFFECTONTARGET
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EffectRototillerGetTarget

BattleScript_EffectBestow::
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
	trybestow BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_BESTOWITEMGIVING
	waitmessage B_WAIT_TIME_LONG
	tryactivateabilitywithabilityshield BS_TARGET, FALSE
	tryactivateitem BS_TARGET, ACTIVATION_ON_USABLE_AGAIN
	trysymbiosis BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_ActivateSwitchInAbility::
	switchinabilities BS_SCRIPTING
	return

BattleScript_EffectAfterYou::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	tryafteryou BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_KINDOFFER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MoveEffectFlameBurst::
	printstring STRINGID_BURSTINGFLAMESHIT
	waitmessage B_WAIT_TIME_LONG
	healthbarupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	datahpupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	tryfaintmon BS_SCRIPTING
	return

BattleScript_EffectPowerTrick::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	powertrick
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDATKANDDEF
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPsychoShift::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	jumpifstatus BS_ATTACKER, STATUS1_ANY, BattleScript_EffectPsychoShiftCanWork
	goto BattleScript_ButItFailed
BattleScript_EffectPsychoShiftCanWork:
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	jumpifsafeguard BattleScript_SafeguardProtected
	trypsychoshift BattleScript_ButItFailed, BattleScript_SleepClauseBlocked
	attackanimation
	waitanimation
	copybyte gEffectBattler, gBattlerTarget
	printfromtable gStatusConditionsStringIds
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_TARGET
	updatestatusicon BS_TARGET
	curestatus BS_ATTACKER
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_ItDoesntAffectFoe::
	savetarget
	copybyte gBattlerTarget, sBATTLER
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_SHORT
	flushtextbox
	restoretarget
	return

BattleScript_MoveEffectSmackDown::
	printstring STRINGID_FELLSTRAIGHTDOWN
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectHitEnemyHealAlly::
	jumpiftargetally BattleScript_EffectHealPulse
	goto BattleScript_EffectHit

BattleScript_EffectDefog::
	setstatchanger STAT_EVASION, 1, TRUE
	attackcanceler
	jumpifgenconfiglowerthan CONFIG_B_DEFOG_EFFECT_CLEARING, GEN_5, BattleScript_DefogAfterSubstituteCheck
	jumpifsubstituteblocks BattleScript_DefogIfCanClearHazards
BattleScript_DefogAfterSubstituteCheck:
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_EVASION, MIN_STAT_STAGE, BattleScript_DefogWorks
BattleScript_DefogIfCanClearHazards:
	trydefog FALSE, BattleScript_ButItFailed
BattleScript_DefogWorks:
	accuracycheck BattleScript_MoveMissedPause
	jumpifgenconfiglowerthan CONFIG_B_DEFOG_EFFECT_CLEARING, GEN_5, BattleScript_DefogWorksAfterSubstituteCheck
	jumpifsubstituteblocks BattleScript_DefogTryHazardsWithAnim
BattleScript_DefogWorksAfterSubstituteCheck:
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_DefogTryHazardsWithAnim
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_DefogDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGE_EMPTY, BattleScript_DefogTryHazardsWithAnim
	pause B_WAIT_TIME_SHORT
	setmoveresultflags MOVE_RESULT_MISSED @ TODO: Is this even necessary?
	goto BattleScript_DefogPrintString
BattleScript_DefogDoAnim::
	attackanimation
	waitanimation
	call BattleScript_SwapFromSubstitute
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_DefogTryHazards
	call BattleScript_SwapToSubstitute
BattleScript_DefogPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefogTryHazards:
	copybyte gEffectBattler, gBattlerAttacker
	trydefog TRUE, NULL
	copybyte gBattlerAttacker, gEffectBattler
	goto BattleScript_MoveEnd
BattleScript_DefogTryHazardsWithAnim:
	attackanimation
	waitanimation
	goto BattleScript_DefogTryHazards

BattleScript_MoveEffectDefog::
	saveattacker
	trydefog TRUE, NULL
	restoreattacker
	return

BattleScript_EffectInstruct::
	attackcanceler
	pause B_WAIT_TIME_SHORT
	tryinstruct BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_USEDINSTRUCTEDMOVE
	waitmessage B_WAIT_TIME_LONG
	copybyte gBattlerAttacker, gBattlerTarget
	copybyte gBattlerTarget, gEffectBattler
	jumptocalledmove TRUE

BattleScript_EffectAutotomize::
	setstatchanger STAT_SPEED, 2, FALSE
	attackcanceler
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_AutotomizeWeightLoss
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_AutotomizeAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_AutotomizePrintString
BattleScript_AutotomizeAttackAnim::
	attackanimation
	waitanimation
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_AutotomizeWeightLoss
BattleScript_AutotomizePrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AutotomizeWeightLoss::
	jumpifmovehadnoeffect BattleScript_MoveEnd
	tryautotomize BattleScript_MoveEnd
	printstring STRINGID_BECAMENIMBLE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_FinalGambit::
	setatkhptozero
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	tryfaintmon BS_ATTACKER
	return

BattleScript_TryHitSwitchTarget::
	forcerandomswitch BattleScript_HitSwitchTargetForceRandomSwitchFailed
	return

BattleScript_HitSwitchTargetDynamaxed::
	printstring STRINGID_MOVEBLOCKEDBYDYNAMAX
	waitmessage B_WAIT_TIME_LONG
BattleScript_HitSwitchTargetForceRandomSwitchFailed:
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	return

BattleScript_EffectToxicThread::
	setstatchanger STAT_SPEED, 1, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
	checknonvolatiletrigger MOVE_EFFECT_POISON, BattleScript_EffectStatDownFromAccCheck
	accuracycheck BattleScript_MoveMissedPause
	attackanimation
	waitanimation
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_ToxicThreadTryPsn
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_ToxicThreadDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGE_EMPTY, BattleScript_ToxicThreadTryPsn
	pause B_WAIT_TIME_SHORT
	goto BattleScript_ToxicThreadPrintString
BattleScript_ToxicThreadDoAnim::
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_ToxicThreadTryPsn
BattleScript_ToxicThreadPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ToxicThreadTryPsn::
	seteffectprimary BS_ATTACKER, BS_TARGET, MOVE_EFFECT_POISON
	goto BattleScript_MoveEnd

BattleScript_EffectVenomDrench::
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_PSN_ANY, BattleScript_EffectVenomDrenchCanBeUsed
	goto BattleScript_ButItFailed
BattleScript_EffectVenomDrenchCanBeUsed:
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPATK, MIN_STAT_STAGE, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_VenomDrenchDoMoveAnim::
	accuracycheck BattleScript_ButItFailed
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchTryLowerSpAtk, BIT_SPATK | BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_VenomDrenchTryLowerSpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchTryLowerSpAtk::
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchTryLowerSpeed, BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_VenomDrenchTryLowerSpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchTryLowerSpeed::
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_VenomDrenchEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectNobleRoar::
	attackcanceler
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_NobleRoarDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_NobleRoarDoMoveAnim::
	accuracycheck BattleScript_ButItFailed
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_NobleRoarTryLowerSpAtk, BIT_SPATK
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_NobleRoarTryLowerSpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_NobleRoarTryLowerSpAtk::
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_NobleRoarEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_NobleRoarEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_NobleRoarEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectShellSmash::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_ButItFailed
BattleScript_ShellSmashTryDef::
	attackanimation
	waitanimation
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_CERTAIN, BattleScript_ShellSmashTrySpDef, BIT_SPDEF
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_ShellSmashTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashTrySpDef:
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_CERTAIN, BattleScript_ShellSmashTryAttack
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_ShellSmashTryAttack
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashTryAttack:
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ShellSmashTrySpAtk, BIT_SPATK | BIT_SPEED,
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_ShellSmashTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashTrySpAtk:
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ShellSmashTrySpeed, BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_ShellSmashTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashTrySpeed:
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ShellSmashEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_ShellSmashEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectGrowth::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_GrowthDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_GrowthDoMoveAnim::
	attackanimation
	waitanimation
	jumpifweatheraffected B_WEATHER_SUN, BattleScript_GrowthAtk2
	setstatchanger STAT_ATK, 1, FALSE
	goto BattleScript_GrowthAtk
BattleScript_GrowthAtk2:
	setstatchanger STAT_ATK, 2, FALSE
BattleScript_GrowthAtk:
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_GrowthTrySpAtk, BIT_SPATK
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_GrowthTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GrowthTrySpAtk::
	jumpifweatheraffected B_WEATHER_SUN, BattleScript_GrowthSpAtk2
	setstatchanger STAT_SPATK, 1, FALSE
	goto BattleScript_GrowthSpAtk
BattleScript_GrowthSpAtk2:
	setstatchanger STAT_SPATK, 2, FALSE
BattleScript_GrowthSpAtk:
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_GrowthEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_GrowthEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GrowthEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectSoak::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	jumpifability BS_TARGET, ABILITY_MULTITYPE, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_RKS_SYSTEM, BattleScript_ButItFailed
	jumpifsubstituteblocks BattleScript_ButItFailed
	attackanimation
	waitanimation
	trysoak BattleScript_ButItFailed
	printstring STRINGID_TARGETCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectReflectType::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	tryreflecttype BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_REFLECTTARGETSTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectElectrify::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	tryelectrify BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TARGETELECTRIFIED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectShiftGear::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ShiftGearDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_ShiftGearDoMoveAnim:
	attackanimation
	waitanimation
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPEED, 10, BattleScript_ShiftGearSpeedBy1
	setstatchanger STAT_SPEED, 2, FALSE
	goto BattleScript_ShiftGearDoSpeed
BattleScript_ShiftGearSpeedBy1:
	setstatchanger STAT_SPEED, 1, FALSE
BattleScript_ShiftGearDoSpeed:
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGearTryAtk, BIT_ATK
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_ShiftGearTryAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGearTryAtk:
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGearEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_ShiftGearEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGearEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectCoil::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_CoilDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_CoilDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ACC, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_CoilDoMoveAnim:
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_CoilTryDef, BIT_DEF | BIT_ACC
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_CoilTryDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoilTryDef:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_CoilTryAcc, BIT_ACC
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_CoilTryAcc
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoilTryAcc:
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_CoilEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_CoilEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoilEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectQuiverDance::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_QuiverDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_QuiverDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_QuiverDanceDoMoveAnim::
	attackanimation
	waitanimation
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_QuiverDanceTrySpDef, BIT_SPDEF | BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_QuiverDanceTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_QuiverDanceTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_QuiverDanceTrySpeed, BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_QuiverDanceTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_QuiverDanceTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_QuiverDanceEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_QuiverDanceEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_QuiverDanceEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectVictoryDance::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_VictoryDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_VictoryDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_VictoryDanceDoMoveAnim::
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_VictoryDanceTryDef, BIT_DEF | BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_VictoryDanceTryDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VictoryDanceTryDef::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_VictoryDanceTrySpeed, BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_VictoryDanceTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VictoryDanceTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_VictoryDanceEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_VictoryDanceEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VictoryDanceEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectAttackSpAttackUp::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_AttackSpAttackUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_AttackSpAttackUpDoMoveAnim::
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_AttackSpAttackUpTrySpAtk, BIT_SPATK
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_AttackSpAttackUpTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackSpAttackUpTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_AttackSpAttackUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_AttackSpAttackUpEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackSpAttackUpEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectAttackAccUp::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_AttackAccUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ACC, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_AttackAccUpDoMoveAnim::
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_AttackAccUpTryAcc, BIT_ACC
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_AttackAccUpTryAcc
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackAccUpTryAcc::
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_AttackAccUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_AttackAccUpEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackAccUpEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectMistyTerrain::
BattleScript_EffectGrassyTerrain::
BattleScript_EffectElectricTerrain::
BattleScript_EffectPsychicTerrain::
	attackcanceler
	setterrain BattleScript_ButItFailed
	attackanimation
	waitanimation
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	goto BattleScript_MoveEnd

BattleScript_EffectTopsyTurvy::
	attackcanceler
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_DEF, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPATK, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPDEF, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPEED, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ACC, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_EVASION, 6, BattleScript_ButItFailed
BattleScript_EffectTopsyTurvyWorks:
	attackanimation
	waitanimation
	invertstatstages
	printstring STRINGID_TOPSYTURVYSWITCHEDSTATS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectIonDeluge::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	orword gFieldStatuses, STATUS_FIELD_ION_DELUGE
	attackanimation
	waitanimation
	printstring STRINGID_IONDELUGEON
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectQuash::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	tryquash BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_QUASHSUCCESS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHealPulse::
	attackcanceler
	jumpifvolatile BS_ATTACKER, VOLATILE_HEAL_BLOCK, BattleScript_MoveUsedHealBlockPrevents @ stops pollen puff
	jumpifvolatile BS_TARGET, VOLATILE_HEAL_BLOCK, BattleScript_MoveUsedHealBlockPrevents
	jumpifsubstituteblocks BattleScript_ButItFailed
	tryhealpulse BattleScript_AlreadyAtFullHp
	attackanimation
	waitanimation
	healthbarupdate BS_TARGET, PASSIVE_HP_UPDATE
	datahpupdate BS_TARGET, PASSIVE_HP_UPDATE
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectEntrainment::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	tryentrainment BattleScript_ButItFailed
	attackanimation
	waitanimation
	switchinabilities BS_TARGET
	printstring STRINGID_PKMNACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	call BattleScript_TryRevertWeatherform
	flushtextbox
	tryendneutralizinggas
	goto BattleScript_MoveEnd

BattleScript_EffectLuckyChant::
	attackcanceler
	setluckychant BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_SHIELDEDFROMCRITICALHITS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHealingWish::
	attackcanceler
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
	instanthpdrop
	setatkhptozero
	tryfaintmon BS_ATTACKER
	storehealingwish BS_ATTACKER
	jumpifgenconfiglowerthan CONFIG_B_HEALING_WISH_SWITCH, GEN_5, BattleScript_EffectHealingWishGen4
	goto BattleScript_MoveEnd

BattleScript_EffectHealingWishGen4:
	openpartyscreen BS_ATTACKER, BattleScript_MoveEnd
	waitstate
	switchhandleorder BS_ATTACKER, 2
	returnatktoball
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	trytoclearprimalweather
	call BattleScript_TryRevertWeatherform
	flushtextbox
	tryendneutralizinggas
	flushtextbox
	printstring STRINGID_SWITCHINMON
	switchinanim BS_ATTACKER, FALSE, TRUE
	waitstate
	switchineffects BS_ATTACKER
	switchinevents
	goto BattleScript_MoveEnd

BattleScript_HealingWishActivates::
	setbyte cMULTISTRING_CHOOSER, 0
	goto BattleScript_EffectHealingWishRestore
BattleScript_LunarDanceActivates::
	setbyte cMULTISTRING_CHOOSER, 1
	restoremovepp BS_SCRIPTING
BattleScript_EffectHealingWishRestore:
	printfromtable gHealingWishStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_WISH_HEAL
	waitanimation
	healthbarupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	datahpupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	clearstatus BS_SCRIPTING,
	waitstate
	updatestatusicon BS_SCRIPTING
	waitstate
	printstring STRINGID_HEALINGWISHHEALED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectOverwriteAbility::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	tryoverwriteability BattleScript_ButItFailed
	attackanimation
	waitanimation
	copybyte gBattlerAbility, gBattlerTarget
	call BattleScript_AbilityPopUpOverwriteThenNormal
	recordability BS_TARGET
	printstring STRINGID_PKMNACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	call BattleScript_TryRevertWeatherform
	flushtextbox
	tryendneutralizinggas
	goto BattleScript_MoveEnd

BattleScript_EffectPowerSplit::
	attackcanceler
	averagestats STAT_ATK
	averagestats STAT_SPATK
	attackanimation
	waitanimation
	printstring STRINGID_SHAREDITSPOWER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGuardSplit::
	attackcanceler
	averagestats STAT_DEF
	averagestats STAT_SPDEF
	attackanimation
	waitanimation
	printstring STRINGID_SHAREDITSGUARD
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHeartSwap::
	attackcanceler
	swapstatstages STAT_ATK
	swapstatstages STAT_DEF
	swapstatstages STAT_SPEED
	swapstatstages STAT_SPATK
	swapstatstages STAT_SPDEF
	swapstatstages STAT_EVASION
	swapstatstages STAT_ACC
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDSTATCHANGES
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPowerSwap::
	attackcanceler
	swapstatstages STAT_ATK
	swapstatstages STAT_SPATK
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDSTATCHANGES
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGuardSwap::
	attackcanceler
	swapstatstages STAT_DEF
	swapstatstages STAT_SPDEF
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDSTATCHANGES
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSpeedSwap::
	attackcanceler
	swapstats STAT_SPEED
	attackanimation
	waitanimation
	printstring STRINGID_ATTACKERSWITCHEDSTATWITHTARGET
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectTelekinesis::
	attackcanceler
	settelekinesis BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_HURLEDINTOTHEAIR
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectStealthRock::
	attackcanceler
	setstealthrock BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_POINTEDSTONESFLOAT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectStickyWeb::
	attackcanceler
	setstickyweb BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_STICKYWEBUSED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGastroAcid::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	jumpifvolatile BS_TARGET, VOLATILE_GASTRO_ACID, BattleScript_ButItFailed
	setgastroacid BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSABILITYSUPPRESSED
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	call BattleScript_TryRevertWeatherform
	flushtextbox
	tryendneutralizinggas
	goto BattleScript_MoveEnd

BattleScript_EffectToxicSpikes::
	attackcanceler
	settoxicspikes BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_POISONSPIKESSCATTERED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMagnetRise::
	attackcanceler
	jumpifvolatile BS_ATTACKER, VOLATILE_ROOT, BattleScript_ButItFailed
	jumpifvolatile BS_ATTACKER, VOLATILE_SMACK_DOWN, BattleScript_ButItFailed
	trysetvolatile BS_ATTACKER, VOLATILE_MAGNET_RISE, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNLEVITATEDONELECTROMAGNETISM
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectTrickRoom::
	attackcanceler
	setroom
	attackanimation
	waitanimation
	printfromtable gRoomsStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryRoomServiceLoop
	goto BattleScript_MoveEnd

BattleScript_TryRoomServiceLoop:
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_RoomServiceLoop:
	copybyte sBATTLER, gBattlerTarget
	tryroomservice BS_TARGET, BattleScript_RoomServiceLoop_NextBattler
	removeitem BS_TARGET
BattleScript_RoomServiceLoop_NextBattler:
	addbyte gBattlerTarget, 0x1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_RoomServiceLoop
	restoretarget
	return

BattleScript_EffectWonderRoom::
BattleScript_EffectMagicRoom::
	attackcanceler
	setroom
	attackanimation
	waitanimation
	printfromtable gRoomsStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectAquaRing::
	attackcanceler
	jumpifvolatile BS_ATTACKER, VOLATILE_AQUA_RING, BattleScript_ButItFailed
	setvolatile BS_ATTACKER, VOLATILE_AQUA_RING
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSURROUNDEDWITHVEILOFWATER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectEmbargo::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	setembargo BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCANTUSEITEMSANYMORE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectTailwind::
	attackcanceler
	settailwind BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TAILWINDBLEW
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryTailwindAbilitiesLoop
	goto BattleScript_MoveEnd

BattleScript_TryTailwindAbilitiesLoop:
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_TryTailwindAbilitiesLoop_Iter:
	trywindriderpower BS_TARGET, BattleScript_TryTailwindAbilitiesLoop_Increment
	jumpifability BS_TARGET, ABILITY_WIND_RIDER, BattleScript_TryTailwindAbilitiesLoop_WindRider
	jumpifability BS_TARGET, ABILITY_WIND_POWER, BattleScript_TryTailwindAbilitiesLoop_WindPower
BattleScript_TryTailwindAbilitiesLoop_Increment:
	addbyte gBattlerTarget, 0x1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_TryTailwindAbilitiesLoop_Iter
	restoretarget
	return

BattleScript_TryTailwindAbilitiesLoop_WindRider:
	call BattleScript_AbilityPopUp
	modifybattlerstatstage BS_TARGET, STAT_ATK, INCREASE, 1, BattleScript_TryTailwindAbilitiesLoop_Increment, ANIM_ON
	goto BattleScript_TryTailwindAbilitiesLoop_Increment

BattleScript_TryTailwindAbilitiesLoop_WindPower:
	call BattleScript_AbilityPopUp
	setvolatile BS_TARGET, VOLATILE_CHARGE_TIMER, 2
	printstring STRINGID_BEINGHITCHARGEDPKMNWITHPOWER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_TryTailwindAbilitiesLoop_Increment

BattleScript_EffectMiracleEye::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	jumpifgenconfiglowerthan CONFIG_B_MIRACLE_EYE_FAIL, GEN_5, BattleScript_MiracleEyeSet
	jumpifvolatile BS_TARGET, VOLATILE_MIRACLE_EYE, BattleScript_ButItFailed
BattleScript_MiracleEyeSet:
	setvolatile BS_TARGET, VOLATILE_MIRACLE_EYE
	goto BattleScript_IdentifiedFoe

BattleScript_EffectGravity::
	call BattleScript_EffectGravityInternal
	goto BattleScript_MoveEnd

BattleScript_EffectGravityInternal:
	attackcanceler
	setgravity BattleScript_ButItFailed
	attackanimation
	waitanimation
BattleScript_EffectGravitySuccess::
	printstring STRINGID_GRAVITYINTENSIFIED
	waitmessage B_WAIT_TIME_LONG
	savetarget
	selectfirstvalidtarget
BattleScript_GravityLoop:
	movevaluescleanup
	jumpfifsemiinvulnerable BS_TARGET, STATE_ON_AIR, BattleScript_GravityLoopDrop
	jumpifvolatile BS_TARGET, VOLATILE_MAGNET_RISE, BattleScript_GravityLoopDrop
	jumpifvolatile BS_TARGET, VOLATILE_TELEKINESIS, BattleScript_GravityLoopDrop
	goto BattleScript_GravityLoopEnd
BattleScript_GravityLoopDrop:
	gravityonairbornemons
	printstring STRINGID_GRAVITYGROUNDING
	waitmessage B_WAIT_TIME_LONG
BattleScript_GravityLoopEnd:
	moveendcase MOVEEND_TARGET_VISIBLE
	jumpifnexttargetvalid BattleScript_GravityLoop
	restoretarget
	return

BattleScript_EffectRoost::
	attackcanceler
	tryhealhalfhealth BS_TARGET, BattleScript_AlreadyAtFullHp
	setroost
	goto BattleScript_PresentHealTarget

BattleScript_EffectCaptivate::
	setstatchanger STAT_SPATK, 2, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifcaptivateaffected BattleScript_CaptivateCheckAcc
	goto BattleScript_ButItFailed
BattleScript_CaptivateCheckAcc:
	accuracycheck BattleScript_MoveMissedPause
	goto BattleScript_EffectStatDownFromStatBuffChange

BattleScript_EffectHealBlock::
	attackcanceler
	accuracycheck BattleScript_MoveMissedPause
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilProtects
	sethealblock BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNPREVENTEDFROMHEALING
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHitEscape::
	jumpiffainted BS_TARGET, FALSE, BattleScript_HitEscapeSwitch
	setbyte sGIVEEXP_STATE, 0
	getexp BS_TARGET
BattleScript_HitEscapeSwitch:
	call BattleScript_MoveSwitchPursuitRet
	return

BattleScript_EffectPlaceholder::
	attackcanceler
	pause 5
	printstring STRINGID_NOTDONEYET
	goto BattleScript_MoveEnd

BattleScript_EffectHit::
	attackcanceler
BattleScript_HitFromAccCheck::
	accuracycheck BattleScript_MoveMissedPause
	copybyte gEffectBattler, gBattlerAttacker
	setpreattackadditionaleffect
BattleScript_HitFromDamageCalc::
	damagecalc
	call BattleScript_Hit_RetFromAtkAnimation
BattleScript_MoveEnd::
	moveendall
	end

BattleScript_EffectHit_RetFromAccCheck::
	accuracycheck BattleScript_MoveMissedPause
	copybyte gEffectBattler, gBattlerAttacker
	setpreattackadditionaleffect
	damagecalc
BattleScript_Hit_RetFromAtkAnimation::
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET, MOVE_DAMAGE_HP_UPDATE
	datahpupdate BS_TARGET, MOVE_DAMAGE_HP_UPDATE
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	setadditionaleffects
	return

BattleScript_MakeMoveMissed::
	setmoveresultflags MOVE_RESULT_MISSED
BattleScript_MoveMissedPause::
	pause B_WAIT_TIME_SHORT
BattleScript_MoveMissed::
	effectivenesssound
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_TerrainPreventsEnd2::
	pause B_WAIT_TIME_SHORT
	printfromtable gTerrainPreventsStringIds
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_ImmunityProtectedEnd2::
	call BattleScript_AbilityPopUp
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_ElectricTerrainPrevents::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ELECTRICTERRAINPREVENTS
	waitmessage B_WAIT_TIME_LONG
	setmoveresultflags MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_MistyTerrainPrevents::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MISTYTERRAINPREVENTS
	waitmessage B_WAIT_TIME_LONG
	setmoveresultflags MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_FlowerVeilProtectsRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_FLOWERVEILPROTECTED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_FlowerVeilProtects::
	call BattleScript_FlowerVeilProtectsRet
	setmoveresultflags MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_SweetVeilProtectsRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_FLOWERVEILPROTECTED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SweetVeilProtects:
	call BattleScript_SweetVeilProtectsRet
	setmoveresultflags MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_AromaVeilProtectsRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_AROMAVEILPROTECTED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AromaVeilProtects:
	call BattleScript_AromaVeilProtectsRet
	setmoveresultflags MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_AbilityProtectsDoesntAffectRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityProtectsDoesntAffect::
	call BattleScript_AbilityProtectsDoesntAffectRet
	setmoveresultflags MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_InsomniaProtects::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSTAYEDAWAKEUSING
	waitmessage B_WAIT_TIME_LONG
	setmoveresultflags MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_AlreadyAsleep::
	setalreadystatusedmoveattempt
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNALREADYASLEEP
	waitmessage B_WAIT_TIME_LONG
	setmoveresultflags MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_CantMakeAsleep::
	pause B_WAIT_TIME_SHORT
	printfromtable gUproarAwakeStringIds
	waitmessage B_WAIT_TIME_LONG
	setmoveresultflags MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_EffectAbsorbLiquidOoze::
	call BattleScript_AbilityPopUpTarget
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_EffectAbsorbRet
	goto BattleScript_EffectAbsorb

BattleScript_EffectAbsorb::
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
BattleScript_EffectAbsorbRet:
	return

BattleScript_Explosion::
	tryexplosion
	setatkhptozero
	return

BattleScript_FaintAttackerForExplosion::
	tryfaintmon BS_ATTACKER
	return

BattleScript_MaxHp50Recoil::
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	tryfaintmon BS_ATTACKER
	return

BattleScript_EffectDreamEater::
	attackcanceler
.if B_DREAM_EATER_SUBSTITUTE < GEN_5
	jumpifsubstituteblocks BattleScript_DoesntAffectTargetAtkString
.endif
	jumpifstatus BS_TARGET, STATUS1_SLEEP, BattleScript_HitFromAccCheck
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_HitFromAccCheck
	goto BattleScript_DoesntAffectTargetAtkString

BattleScript_EffectAttackUp::
	setstatchanger STAT_ATK, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectDefenseUp::
	setstatchanger STAT_DEF, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialAttackUp::
	setstatchanger STAT_SPATK, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpeedUp::
	setstatchanger STAT_SPEED, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialDefenseUp::
	setstatchanger STAT_SPDEF, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectAccuracyUp::
	setstatchanger STAT_ACC, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectEvasionUp::
	setstatchanger STAT_EVASION, 1, FALSE
BattleScript_EffectStatUp::
	attackcanceler
BattleScript_EffectStatUpAfterAtkCanceler::
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_StatUpEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_StatUpAttackAnim
	pause B_WAIT_TIME_SHORT
	setmoveresultflags MOVE_RESULT_MISSED @ TODO: Is this even necessary?
	goto BattleScript_StatUpPrintString
BattleScript_StatUpAttackAnim::
	attackanimation
	waitanimation
BattleScript_StatUpDoAnim::
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_StatUpEnd
BattleScript_StatUpPrintString::
	saveattacker
	copybyte gBattlerAttacker, gBattlerTarget
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	restoreattacker
BattleScript_StatUpEnd::
	goto BattleScript_MoveEnd

BattleScript_StatUp::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectAttackDown::
	setstatchanger STAT_ATK, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectDefenseDown::
	setstatchanger STAT_DEF, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpeedDown::
	setstatchanger STAT_SPEED, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectAccuracyDown::
	setstatchanger STAT_ACC, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialAttackDown::
	setstatchanger STAT_SPATK, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialDefenseDown::
	setstatchanger STAT_SPDEF, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectEvasionDown::
	setstatchanger STAT_EVASION, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectStatDown:
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
BattleScript_EffectStatDownFromAccCheck:
	accuracycheck BattleScript_MoveMissedPause
BattleScript_EffectStatDownFromStatBuffChange:
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_StatDownEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_StatDownDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGE_EMPTY, BattleScript_StatDownEnd
	pause B_WAIT_TIME_SHORT
	setmoveresultflags MOVE_RESULT_MISSED @ TODO: Is this even necessary?
	goto BattleScript_StatDownPrintString
BattleScript_StatDownDoAnim::
	attackanimation
	waitanimation
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_StatDownEnd
	bicword gHitMarker, HITMARKER_DISABLE_ANIMATION
BattleScript_StatDownPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StatDownEnd::
#if IS_HNS
	// PRU Scary Face retains its -2 Speed drop and now also inflicts
	// Fear on a successful hit (including a target already at -6 Speed).
	// Do not apply Fear on misses or blocked status moves.
	jumpifhalfword CMP_EQUAL, gCurrentMove, MOVE_SCARY_FACE, BattleScript_PRU_ScaryFaceFear
#endif
	goto BattleScript_MoveEnd

#if IS_HNS
BattleScript_PRU_ScaryFaceFear::
	@ A stat-loss immunity or other no-effect result also blocks the added Fear.
	jumpifword CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_NO_EFFECT, BattleScript_MoveEnd
	seteffectprimary BS_ATTACKER, BS_TARGET, MOVE_EFFECT_FEAR
	goto BattleScript_MoveEnd
#endif

BattleScript_MirrorArmorReflect::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	jumpifvolatile BS_ATTACKER, VOLATILE_SUBSTITUTE, BattleScript_MirrorArmorDoesntAffect
BattleScript_MirrorArmorReflectStatLoss:
	statbuffchange BS_ATTACKER, STAT_CHANGE_MIRROR_ARMOR | STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_MirrorArmorReflectEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_MirrorArmorReflectPrintString
	goto BattleScript_MirrorArmorReflectWontFall
BattleScript_MirrorArmorReflectPrintString:
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MirrorArmorReflectEnd:
	return

BattleScript_MirrorArmorDoesntAffect:
	swapattackerwithtarget
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	swapattackerwithtarget
	return

BattleScript_MirrorArmorReflectWontFall:
	copybyte gBattlerTarget, gBattlerAttacker   @ STRINGID_STATSWONTDECREASE uses target
	goto BattleScript_MirrorArmorReflectPrintString

@ gBattlerTarget is battler with Mirror Armor
BattleScript_MirrorArmorReflectStickyWeb:
	call BattleScript_AbilityPopUp
	setattackertostickywebuser
	jumpifbyteequal gBattlerAttacker, gBattlerTarget, BattleScript_StickyWebOnSwitchInEnd   @ Sticky web user not on field -> no stat loss
	call BattleScript_MirrorArmorReflectStatLoss
	goto BattleScript_StickyWebOnSwitchInEnd

BattleScript_StatDown::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectHaze::
	attackcanceler
	attackanimation
	waitanimation
	normalisebuffs
	printstring STRINGID_STATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectBide::
	attackcanceler
	attackanimation
	waitanimation
	setbide
	goto BattleScript_MoveEnd

BattleScript_EffectRoar::
	attackcanceler
	jumpifroarfails BattleScript_ButItFailed
	jumpifcommanderactive BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_GUARD_DOG, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut
	jumpifvolatile BS_TARGET, VOLATILE_ROOT, BattleScript_PrintMonIsRooted
	jumpiftargetdynamaxed BattleScript_RoarBlockedByDynamax
	accuracycheck BattleScript_MoveMissedPause
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_ButItFailed
	forcerandomswitch BattleScript_ButItFailed

BattleScript_RoarBloc…24715 tokens truncated…rintstring STRINGID_AFTERMATHDMG
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
BattleScript_AftermathDmgRet:
	return

BattleScript_DampPreventsAftermath::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	pause 40
	copybyte gBattlerAbility, sBATTLER
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSABILITYPREVENTSABILITY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveUsedIsAsleep::
	printstring STRINGID_PKMNFASTASLEEP
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_BeforeSnoreMessage::
	printstring STRINGID_PKMNFASTASLEEP
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	return

BattleScript_MoveUsedWokeUp::
	printfromtable gWokeUpStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	return

BattleScript_MonWokeUpInUproar::
	printstring STRINGID_PKMNWOKEUPINUPROAR
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_EFFECT_BATTLER
	end2

BattleScript_PoisonTurnDmg::
	printstring STRINGID_PKMNHURTBYPOISON
	waitmessage B_WAIT_TIME_LONG
BattleScript_DoStatusTurnDmg::
	statusanimation BS_ATTACKER
BattleScript_DoTurnDmg:
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	tryfaintmon BS_ATTACKER
	checkteamslost BattleScript_DoTurnDmgEnd
	tryactivateitem BS_ATTACKER, ACTIVATION_ON_HP_THRESHOLD
BattleScript_DoTurnDmgEnd:
	end2

BattleScript_PoisonHealActivates::
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_POISONHEALHPUP
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	end2

BattleScript_BurnTurnDmg::
	printstring STRINGID_PKMNHURTBYBURN
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoStatusTurnDmg

BattleScript_FrostbiteTurnDmg::
	printstring STRINGID_PKMNHURTBYFROSTBITE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoStatusTurnDmg

BattleScript_BleedTurnDmg::
	printstring STRINGID_PKMNHURTBYBLEED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoStatusTurnDmg

BattleScript_MoveUsedIsFrozen::
	printstring STRINGID_PKMNISFROZEN
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_BattlerDefrosted::
	printfromtable gGotDefrostedStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	return

BattleScript_BattlerFrostbiteHealed::
	printfromtable gFrostbiteHealedStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	return

BattleScript_MoveUsedIsParalyzed::
	printstring STRINGID_PKMNISPARALYZED
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	cancelmultiturnmoves
	goto BattleScript_MoveEnd

BattleScript_PowderMoveNoEffect::
	pause B_WAIT_TIME_SHORT
	jumpiftype BS_SCRIPTING, TYPE_GRASS, BattleScript_PowderMoveNoEffectPrint
	jumpifability BS_SCRIPTING, ABILITY_OVERCOAT, BattleScript_PowderMoveNoEffectOvercoat
	setlastuseditem BS_SCRIPTING
	printstring STRINGID_SAFETYGOGGLESPROTECTED
	goto BattleScript_PowderMoveNoEffectWaitMsg
BattleScript_PowderMoveNoEffectOvercoat:
	call BattleScript_AbilityPopUp
BattleScript_PowderMoveNoEffectPrint:
	printstring STRINGID_SCR_ITDOESNTAFFECT
BattleScript_PowderMoveNoEffectWaitMsg:
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveUsedFlinched::
	printstring STRINGID_PKMNFLINCHED
	waitmessage B_WAIT_TIME_LONG
	jumpifability BS_ATTACKER, ABILITY_STEADFAST, BattleScript_TryActivateSteadFast
BattleScript_MoveUsedFlinchedEnd:
	goto BattleScript_MoveEnd
BattleScript_TryActivateSteadFast:
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_MoveUsedFlinchedEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_MoveUsedFlinchedEnd
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_MoveUsedFlinchedEnd
	setbyte gBattleCommunication, STAT_SPEED
	stattextbuffer
	printstring STRINGID_ATTACKERABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveUsedFlinchedEnd

BattleScript_PrintUproarOverTurns::
	printfromtable gUproarOverTurnStringIds
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_ThrashConfuses::
	volatileanimation BS_ATTACKER, VOLATILE_CONFUSION
	copybyte sBATTLER, gBattlerAttacker
	printstring STRINGID_PKMNFATIGUECONFUSION
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_ThrashConfusesRet::
	volatileanimation BS_SCRIPTING, VOLATILE_CONFUSION
	printstring STRINGID_PKMNFATIGUECONFUSION
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveUsedIsConfused::
	printstring STRINGID_PKMNISCONFUSED
	waitmessage B_WAIT_TIME_LONG
	volatileanimation BS_ATTACKER, VOLATILE_CONFUSION
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, FALSE, BattleScript_MoveUsedIsConfusedRet
BattleScript_DoSelfConfusionDmg::
	cancelmultiturnmoves
	printstring STRINGID_ITHURTCONFUSION
	waitmessage B_WAIT_TIME_LONG
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	tryselfconfusiondmgformchange
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd
BattleScript_MoveUsedIsConfusedRet::
	return

BattleScript_MoveUsedPowder::
	pause B_WAIT_TIME_SHORT
	cancelmultiturnmoves
	volatileanimation BS_ATTACKER, VOLATILE_POWDER
	waitanimation
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printstring STRINGID_POWDEREXPLODES
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_MoveUsedIsConfusedNoMore::
	printstring STRINGID_PKMNHEALEDCONFUSION
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_PrintPayDayMoneyString::
	printstring STRINGID_PLAYERPICKEDUPMONEY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_WrapTurnDmg::
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_DoTurnDmgEnd
	playanimation BS_ATTACKER, B_ANIM_TURN_TRAP, sB_ANIM_ARG1
	printstring STRINGID_PKMNHURTBY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoTurnDmg

BattleScript_WrapEnds::
	printstring STRINGID_PKMNFREEDFROM
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_MoveUsedIsInLove::
	printstring STRINGID_PKMNINLOVE
	waitmessage B_WAIT_TIME_LONG
	volatileanimation BS_ATTACKER, VOLATILE_INFATUATION
	return

BattleScript_MoveUsedIsInLoveCantAttack::
	printstring STRINGID_PKMNIMMOBILIZEDBYLOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_NightmareTurnDmg::
	printstring STRINGID_PKMNLOCKEDINNIGHTMARE
	waitmessage B_WAIT_TIME_LONG
	volatileanimation BS_ATTACKER, VOLATILE_NIGHTMARE
	goto BattleScript_DoTurnDmg

BattleScript_CurseTurnDmg::
	printstring STRINGID_PKMNAFFLICTEDBYCURSE
	waitmessage B_WAIT_TIME_LONG
	volatileanimation BS_ATTACKER, VOLATILE_CURSED
	goto BattleScript_DoTurnDmg

BattleScript_TargetPRLZHeal::
	printstring STRINGID_PKMNHEALEDPARALYSIS
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_TargetWokeUp::
	printstring STRINGID_TARGETWOKEUP
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_TargetBurnHeal::
	printstring STRINGID_PKMNBURNHEALED
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_TargetPoisonHealed::
	printstring STRINGID_PASTELVEILENTERS
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_MoveEffectSleep::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gFellAsleepStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_UpdateEffectStatusIconRet::
	updatestatusicon BS_EFFECT_BATTLER
	waitstate
	trytriggerstatusform
	flushtextbox
	return

BattleScript_YawnMakesAsleepEnd2::
	statusanimation BS_EFFECT_BATTLER
	printstring STRINGID_PKMNFELLASLEEP
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_EFFECT_BATTLER
	waitstate
	tryactivateitem BS_EFFECT_BATTLER, ACTIVATION_ON_STATUS_CHANGE
	jumpfifsemiinvulnerable BS_EFFECT_BATTLER, STATE_SKY_DROP, BattleScript_YawnEnd
	makevisible BS_EFFECT_BATTLER
	skydropyawn
BattleScript_YawnEnd:
	end2

BattleScript_EmbargoEndTurn::
	printstring STRINGID_EMBARGOENDS
	waitmessage B_WAIT_TIME_LONG
	tryactivateitem BS_ATTACKER, ACTIVATION_ON_USABLE_AGAIN
	end2

BattleScript_TelekinesisEndTurn::
	printstring STRINGID_TELEKINESISENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_BufferEndTurn::
	printstring STRINGID_BUFFERENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_ToxicOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectToxic
	end2

BattleScript_FlameOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectBurn
	end2

BattleScript_MoveEffectPoison::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotPoisonedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectBurn::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotBurnedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectFrostbite::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotFrostbiteStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectBleed::
	statusanimation BS_EFFECT_BATTLER
	printstring STRINGID_PKMNGOTBLEED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectFear::
	printstring STRINGID_PKMNFEARED
	waitmessage B_WAIT_TIME_LONG
	return

// PRU: outcome narration for independent Lovely Bite / Shadow Fangs secondaries.
BattleScript_MoveEffectPRUInfatuation::
	volatileanimation BS_EFFECT_BATTLER, VOLATILE_INFATUATION
	printstring STRINGID_PKMNFELLINLOVE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectPRUCurse::
	printstring STRINGID_PKMNLAIDCURSE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectFreeze::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotFrozenStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectParalysis::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotParalyzedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectUproar::
	printstring STRINGID_PKMNCAUSEDUPROAR
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectToxic::
	statusanimation BS_EFFECT_BATTLER
	printstring STRINGID_PKMNBADLYPOISONED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectPayDay::
	printstring STRINGID_COINSSCATTERED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectWrap::
	printfromtable gWrappedStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectConfusion::
	volatileanimation BS_EFFECT_BATTLER, VOLATILE_CONFUSION
	printstring STRINGID_PKMNWASCONFUSED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectRecoil::
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printstring STRINGID_PKMNHITWITHRECOIL
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	return

BattleScript_ItemSteal::
	playanimation BS_EFFECT_BATTLER, B_ANIM_ITEM_STEAL
	printstring STRINGID_PKMNSTOLEITEM
	waitmessage B_WAIT_TIME_LONG
	tryactivateabilitywithabilityshield BS_ATTACKER, FALSE
	return

BattleScript_AbilityRaisesDefenderStat::
	pause B_WAIT_TIME_SHORT
	statbuffchange BS_TARGET, STAT_CHANGE_ONLY_CHECKING, BattleScript_AbilityCantRaiseDefenderStat
	call BattleScript_AbilityPopUp
	statbuffchange BS_TARGET, 0, BattleScript_AbilityCantRaiseDefenderStat
	printstring STRINGID_DEFENDERSSTATROSE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityCantRaiseDefenderStat::
	saveattacker
	copybyte gBattlerAttacker, gBattlerTarget
	printstring STRINGID_STATSWONTINCREASE
	waitmessage B_WAIT_TIME_LONG
	restoreattacker
	return

BattleScript_AbilityShieldProtects::
	saveattacker
	copybyte gBattlerAttacker, gBattlerAbility
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_ABILITYSHIELDPROTECTS
	waitmessage B_WAIT_TIME_LONG
	restoreattacker
	return

BattleScript_AbilityPopUpTarget::
	copybyte gBattlerAbility, gBattlerTarget
BattleScript_AbilityPopUp::
	tryactivateabilityshield BS_ABILITY_BATTLER
	showabilitypopup
	pause B_WAIT_TIME_SHORT
	recordability BS_ABILITY_BATTLER
	sethword sABILITY_OVERWRITE, 0
	return

BattleScript_AbilityPopUpScripting:
	copybyte gBattlerAbility, sBATTLER
	goto BattleScript_AbilityPopUp

BattleScript_AbilityPopUpOverwriteThenNormal:
	setbyte sFIXED_ABILITY_POPUP, TRUE
	showabilitypopup
	pause B_WAIT_TIME_SHORT
	sethword sABILITY_OVERWRITE, 0
	updateabilitypopup
	pause B_WAIT_TIME_SHORT
	recordability BS_ABILITY_BATTLER
	destroyabilitypopup
	setbyte sFIXED_ABILITY_POPUP, FALSE
	return

@ Can't compare directly to a value, have to compare to value at pointer
sZero:
.byte 0

BattleScript_MoodyActivates::
	call BattleScript_AbilityPopUp
	jumpifbyteequal sSTATCHANGER, sZero, BattleScript_MoodyLower
	statbuffchange BS_ATTACKER, STAT_CHANGE_CERTAIN | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoodyLower
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_CHANGED, BattleScript_MoodyLower
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoodyLower:
	jumpifbyteequal sSAVED_STAT_CHANGER, sZero, BattleScript_MoodyEnd
	copybyte sSTATCHANGER, sSAVED_STAT_CHANGER
	statbuffchange BS_ATTACKER, STAT_CHANGE_CERTAIN | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoodyEnd
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_CHANGED, BattleScript_MoodyEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoodyEnd:
	end2

BattleScript_EmergencyExit::
	pause 5
	call BattleScript_AbilityPopUpScripting
	pause B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_SLIDE_OFFSCREEN
	waitanimation
	jumpifbattletype BATTLE_TYPE_TRAINER, BattleScript_EmergencyExitTrainer
	setteleportoutcome BS_SCRIPTING
	finishaction
	return
BattleScript_EmergencyExitTrainer:
	openpartyscreen BS_SCRIPTING, BattleScript_EmergencyExitRet
	waitstate
	returntoball BS_SCRIPTING, FALSE
	switchoutabilities BS_SCRIPTING
	switchhandleorder BS_SCRIPTING, 2
	getswitchedmondata BS_SCRIPTING
	switchindataupdate BS_SCRIPTING
	hpthresholds BS_SCRIPTING
	printstring STRINGID_SWITCHINMON
	switchinanim BS_SCRIPTING, FALSE, TRUE
	waitstate
	switchineffects BS_SCRIPTING
	switchinevents
BattleScript_EmergencyExitRet:
	return

BattleScript_EmergencyExitEnd2::
	call BattleScript_EmergencyExit
	end2

BattleScript_TraceActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUpScripting
	printstring STRINGID_PKMNTRACED
	waitmessage B_WAIT_TIME_LONG
	settracedability BS_SCRIPTING
	switchinabilities BS_SCRIPTING
	return

BattleScript_ReceiverActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_RECEIVERABILITYTAKEOVER
	waitmessage B_WAIT_TIME_LONG
	settracedability BS_ABILITY_BATTLER
	switchinabilities BS_ABILITY_BATTLER
	return

BattleScript_AbilityHpHeal::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXRESTOREDHPALITTLE2
	waitmessage B_WAIT_TIME_LONG
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	return

BattleScript_RainDishActivates::
	call BattleScript_AbilityHpHeal
	end2

BattleScript_CheekPouchActivates::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	copybyte gBattlerAttacker, gBattlerAbility
	call BattleScript_AbilityHpHeal
	copybyte gBattlerAttacker, sSAVED_BATTLER
	return

BattleScript_PickupActivates::
	pause 5
	tryrecycleitem BattleScript_PickupActivatesEnd
	call BattleScript_AbilityPopUp
	printstring STRINGID_XFOUNDONEY
	waitmessage B_WAIT_TIME_LONG
	tryactivateitem BS_ATTACKER, ACTIVATION_ON_PICK_UP
BattleScript_PickupActivatesEnd:
	end2

BattleScript_HarvestActivates::
	pause 5
	tryrecycleitem BattleScript_HarvestActivatesEnd
	call BattleScript_AbilityPopUp
	printstring STRINGID_HARVESTBERRY
	waitmessage B_WAIT_TIME_LONG
	tryactivateitem BS_ATTACKER, ACTIVATION_ON_HARVEST
BattleScript_HarvestActivatesEnd:
	end2

BattleScript_SolarPowerActivates::
	call BattleScript_AbilityPopUp
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printstring STRINGID_SOLARPOWERHPDROP
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	end2

BattleScript_HealerActivates::
	call BattleScript_AbilityPopUp
	curestatus BS_SCRIPTING
	updatestatusicon BS_SCRIPTING
	printstring STRINGID_HEALERCURE
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_ShedSkinActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXCUREDYPROBLEM
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	end2

BattleScript_ActivateWeatherAbilities:
	saveattacker
	savetarget
	tryboosterenergy ON_WEATHER
	setbyte gBattlerAttacker, 0
	sortbattlers
BattleScript_ActivateWeatherAbilities_Loop:
	copyarraywithindex gBattlerTarget, gBattlersBySpeed, gBattlerAttacker, 1
	activateweatherchangeabilities BS_TARGET
	addbyte gBattlerAttacker, 1
	jumpifbytenotequal gBattlerAttacker, gBattlersCount, BattleScript_ActivateWeatherAbilities_Loop
	restoreattacker
	restoretarget
	return

BattleScript_TryIntimidateHoldEffects:
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_ADRENALINE_ORB, BattleScript_TryIntimidateHoldEffectsRet
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_TryIntimidateHoldEffectsRet
	setstatchanger STAT_SPEED, 1, FALSE
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	statbuffchange BS_TARGET, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_TryIntimidateHoldEffectsRet
	copybyte sBATTLER, gBattlerTarget
	setlastuseditem BS_TARGET
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_TryIntimidateHoldEffectsRet:
	return

BattleScript_IntimidateActivates::
	savetarget
	call BattleScript_AbilityPopUp
	setbyte gBattlerTarget, 0
BattleScript_IntimidateLoop:
	jumpiftargetally BattleScript_IntimidateLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_IntimidateLoopIncrement
	jumpifvolatile BS_TARGET, VOLATILE_SUBSTITUTE, BattleScript_IntimidateLoopIncrement
	jumpifintimidateabilityprevented
BattleScript_IntimidateEffect:
	copybyte sBATTLER, gBattlerAttacker
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_IntimidateLoopIncrement
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_IntimidateWontDecrease
	printstring STRINGID_PKMNCUTSATTACKWITH
BattleScript_IntimidateEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	saveattacker
	savetarget
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_TryIntimidateHoldEffects
	restoreattacker
	restoretarget
BattleScript_IntimidateLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_IntimidateLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	restoreattacker
	pause B_WAIT_TIME_MED
	return

BattleScript_IntimidatePrevented::
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSSTATLOSSWITH
	goto BattleScript_IntimidateEffect_WaitString

BattleScript_IntimidateWontDecrease:
	printstring STRINGID_STATSWONTDECREASE
	goto BattleScript_IntimidateEffect_WaitString

BattleScript_IntimidateInReverse::
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUpTarget
	pause B_WAIT_TIME_SHORT
	modifybattlerstatstage BS_TARGET, STAT_ATK, INCREASE, 1, BattleScript_IntimidateLoopIncrement, ANIM_ON
	call BattleScript_TryIntimidateHoldEffects
	goto BattleScript_IntimidateLoopIncrement

BattleScript_SupersweetSyrupActivates::
 	savetarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_SUPERSWEETAROMAWAFTS
	waitmessage B_WAIT_TIME_LONG
	setbyte gBattlerTarget, 0
BattleScript_SupersweetSyrupLoop:
	jumpiftargetally BattleScript_SupersweetSyrupLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_SupersweetSyrupLoopIncrement
	jumpifvolatile BS_TARGET, VOLATILE_SUBSTITUTE, BattleScript_SupersweetSyrupLoopIncrement
BattleScript_SupersweetSyrupEffect:
	copybyte sBATTLER, gBattlerAttacker
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_SupersweetSyrupLoopIncrement
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_SupersweetSyrupWontDecrease
	printfromtable gStatDownStringIds
BattleScript_SupersweetSyrupEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	saveattacker
	savetarget
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_TryIntimidateHoldEffects
	restoreattacker
	restoretarget
BattleScript_SupersweetSyrupLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_SupersweetSyrupLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	restoreattacker
	pause B_WAIT_TIME_MED
	return

BattleScript_SupersweetSyrupWontDecrease:
	printstring STRINGID_STATSWONTDECREASE
	goto BattleScript_SupersweetSyrupEffect_WaitString

BattleScript_PrimalWeatherBlocksMove::
	pause B_WAIT_TIME_SHORT
	printfromtable gPrimalWeatherBlocksStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_ProtosynthesisActivates::
	call BattleScript_AbilityPopUpScripting
	printstring STRINGID_SUNLIGHTACTIVATEDABILITY
	waitmessage B_WAIT_TIME_MED
	printstring STRINGID_STATWASHEIGHTENED
	waitmessage B_WAIT_TIME_MED
	return

BattleScript_QuarkDriveActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_ELECTRICTERRAINACTIVATEDABILITY
	waitmessage B_WAIT_TIME_MED
	printstring STRINGID_STATWASHEIGHTENED
	waitmessage B_WAIT_TIME_MED
	return

BattleScript_RuinAbilityActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_ABILITYWEAKENEDSURROUNDINGMONSSTAT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SupremeOverlordActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_ATTACKERGAINEDSTRENGTHFROMTHEFALLEN
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_CostarActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNCOPIEDSTATCHANGES
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ZeroToHeroActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUpScripting
	printstring STRINGID_ZEROTOHEROTRANSFORMATION
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_CommanderActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUpScripting
	printstring STRINGID_COMMANDERACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_CommanderAtkIncrease:
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_CommanderDefIncrease, BIT_DEF | BIT_SPATK | BIT_SPDEF | BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_CommanderDefIncrease
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CommanderDefIncrease:
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_CommanderSpAtkIncrease, BIT_SPATK | BIT_SPDEF | BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_CommanderSpAtkIncrease
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CommanderSpAtkIncrease:
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_CommanderSpDefIncrease, BIT_SPDEF | BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_CommanderSpDefIncrease
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CommanderSpDefIncrease:
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_CommanderSpeedIncrease, BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_CommanderSpeedIncrease
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CommanderSpeedIncrease:
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_CommanderEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_CommanderEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CommanderEnd:
	restoreattacker
	return

BattleScript_HospitalityActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_HOSPITALITYRESTORATION
	waitmessage B_WAIT_TIME_LONG
 	playanimation BS_EFFECT_BATTLER, B_ANIM_SIMPLE_HEAL
	healthbarupdate BS_EFFECT_BATTLER, PASSIVE_HP_UPDATE
	datahpupdate BS_EFFECT_BATTLER, PASSIVE_HP_UPDATE
	return

BattleScript_AncientBastionActivates::
	call BattleScript_AbilityPopUp
	pause B_WAIT_TIME_SHORT
	trysetspikes BattleScript_AncientBastionEnd
	printstring STRINGID_POINTEDSTONESFLOAT
	waitmessage B_WAIT_TIME_LONG
BattleScript_AncientBastionEnd:
	restoretarget
	restoreattacker
	return

BattleScript_AncientBloomActivates::
	call BattleScript_AbilityPopUpScripting
	playanimation BS_ATTACKER, B_ANIM_SIMPLE_HEAL
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printstring STRINGID_PKMNSXRESTOREDHPALITTLE2
	waitmessage B_WAIT_TIME_LONG
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, FALSE, BattleScript_AncientBloomEnd
	printstring STRINGID_TERRAINBECOMESGRASSY
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
BattleScript_AncientBloomEnd:
	restoreattacker
	return

BattleScript_TidalRoarActivates::
	savetarget
	call BattleScript_AbilityPopUpScripting
	setbyte gBattlerTarget, 0
BattleScript_TidalRoarLoop:
	jumpiftargetally BattleScript_TidalRoarLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_TidalRoarLoopIncrement
	jumpifvolatile BS_TARGET, VOLATILE_SUBSTITUTE, BattleScript_TidalRoarLoopIncrement
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_TidalRoarTrySpAtk, BIT_SPATK
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_TidalRoarTrySpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TidalRoarTrySpAtk:
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_TidalRoarLoopIncrement
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_TidalRoarLoopIncrement
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TidalRoarLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_TidalRoarLoop
	destroyabilitypopup
	restoretarget
	restoreattacker
	pause B_WAIT_TIME_MED
	return

BattleScript_AttackWeakenedByStrongWinds::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ATTACKWEAKENEDBSTRONGWINDS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MimicryActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_BATTLERTYPECHANGEDTO
	waitmessage B_WAIT_TIME_SHORT
	return

BattleScript_ActivateTerrainEffects:
	saveattacker
	savetarget
	tryboosterenergy ON_TERRAIN
	resetterrainabilityflags
	setbyte gBattlerAttacker, 0
	sortbattlers
BattleScript_ActivateTerrainSeed:
	copyarraywithindex gBattlerTarget, gBattlersBySpeed, gBattlerAttacker, 1
	tryterrainseed BS_TARGET, BattleScript_ActivateTerrainAbility
	removeitem BS_TARGET
BattleScript_ActivateTerrainAbility:
	activateterrainchangeabilities BS_TARGET
	addbyte gBattlerAttacker, 1
	jumpifbytenotequal gBattlerAttacker, gBattlersCount, BattleScript_ActivateTerrainSeed
	restoreattacker
	restoretarget
	return

BattleScript_ElectricSurgeActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TERRAINBECOMESELECTRIC
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	return

BattleScript_MistySurgeActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TERRAINBECOMESMISTY
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	return

BattleScript_GrassySurgeActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TERRAINBECOMESGRASSY
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	return

BattleScript_PsychicSurgeActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TERRAINBECOMESPSYCHIC
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	return

BattleScript_BadDreamsActivates::
	setbyte gBattlerTarget, 0
BattleScript_BadDreamsLoop:
	jumpiftargetally BattleScript_BadDreamsIncrement
	jumpifability BS_TARGET, ABILITY_MAGIC_GUARD, BattleScript_BadDreamsIncrement
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_BadDreams_Dmg
	jumpifstatus BS_TARGET, STATUS1_SLEEP, BattleScript_BadDreams_Dmg
	goto BattleScript_BadDreamsIncrement
BattleScript_BadDreams_Dmg:
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_BadDreams_ShowPopUp
BattleScript_BadDreams_DmgAfterPopUp:
	printstring STRINGID_BADDREAMSDMG
	waitmessage B_WAIT_TIME_LONG
	dmg_1_8_targethp
	healthbarupdate BS_TARGET, PASSIVE_HP_UPDATE
	datahpupdate BS_TARGET, PASSIVE_HP_UPDATE
	jumpifhasnohp BS_TARGET, BattleScript_BadDreams_HidePopUp
BattleScript_BadDreamsIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_BadDreamsLoop
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_BadDreamsEnd
	destroyabilitypopup
	pause 15
BattleScript_BadDreamsEnd:
	end2
BattleScript_BadDreams_ShowPopUp:
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setbyte sFIXED_ABILITY_POPUP, TRUE
	goto BattleScript_BadDreams_DmgAfterPopUp
BattleScript_BadDreams_HidePopUp:
	destroyabilitypopup
	tryfaintmon BS_TARGET
	goto BattleScript_BadDreamsIncrement

BattleScript_TookAttack::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNSXTOOKATTACK
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SturdyPreventsOHKO::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPROTECTEDBY
	pause B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_DampStopsExplosion::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUpScripting
	printstring STRINGID_PKMNPREVENTSUSAGE
	pause B_WAIT_TIME_LONG
	moveendto MOVEEND_NEXT_TARGET
	moveendcase MOVEEND_CLEAR_BITS
	end

BattleScript_MoveHPDrain::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	healthbarupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	datahpupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	printstring STRINGID_PKMNRESTOREDHPUSING
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveStatDrain::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	statbuffchange BS_SCRIPTING, STAT_CHANGE_ALLOW_PTR, BattleScript_MoveStatDrain_Cont
	printstring STRINGID_SCRIPTINGSTATROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoveStatDrain_Cont:
	clearsemiinvulnerablebit
	return

BattleScript_MonMadeMoveUseless::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXMADEYUSELESS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_FlashFireBoost::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printfromtable gFlashFireStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityPreventsPhasingOut::
	call BattleScript_AbilityPreventsPhasingOutRet
	goto BattleScript_MoveEnd

BattleScript_AbilityPreventsPhasingOutRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUpTarget
	printstring STRINGID_PKMNANCHORSITSELFWITH
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityNoStatLoss::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSSTATLOSSWITH
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ItemNoStatLoss::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_CLEARAMULETWONTLOWERSTATS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ObliviousPreventsAttraction::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSROMANCEWITH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_FlinchPrevention::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXPREVENTSFLINCHING
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_OwnTempoPrevents::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	copybyte sBATTLER, gBattlerTarget
	printstring STRINGID_PKMNPREVENTSCONFUSIONWITH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SoundproofProtected::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXBLOCKSY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_IceFaceNullsDamage::
	call BattleScript_TargetFormChangeWithString
	return

BattleScript_DazzlingProtected::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUpScripting
	printstring STRINGID_POKEMONCANNOTUSEMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MoveUsedPsychicTerrainPrevents::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PSYCHICTERRAINPREVENTS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_GrassyTerrainHeals::
	printstring STRINGID_GRASSYTERRAINHEALS
	waitmessage B_WAIT_TIME_LONG
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	end2

BattleScript_AbilityNoSpecificStatLoss::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXPREVENTSYLOSS
	waitmessage B_WAIT_TIME_LONG
	setbyte cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGE_EMPTY
	setmoveresultflags MOVE_RESULT_NO_EFFECT
	return

BattleScript_StickyHoldActivates::
	call BattleScript_StickyHoldActivatesRet
	goto BattleScript_MoveEnd

BattleScript_StickyHoldActivatesRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	copybyte sBATTLER, gBattlerAbility
	printstring STRINGID_PKMNSXMADEYINEFFECTIVE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ColorChangeActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNCHANGEDTYPEWITH
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ProteanActivates::
	pause B_WAIT_TIME_SHORTEST
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityAvoidsDamage::
	call BattleScript_AbilityPopUp
	printfromtable gMissStringIds @ waitmessage is executed next so no waitmessage here
	return

BattleScript_TeraShellDistortingTypeMatchups::
	pause B_WAIT_TIME_SHORTEST
	call BattleScript_AbilityPopUpScripting
	printstring STRINGID_PKMNMADESHELLGLEAM
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_CursedBodyActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_CURSEDBODYDISABLED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MummyActivates::
	setbyte sFIXED_ABILITY_POPUP, TRUE
	call BattleScript_AbilityPopUpTarget
	copybyte gBattlerAbility, gBattlerAttacker
	copyhword sABILITY_OVERWRITE, gLastUsedAbility
	call BattleScript_AbilityPopUpOverwriteThenNormal
	recordability BS_TARGET
	recordability BS_ATTACKER
	printstring STRINGID_ATTACKERACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	call BattleScript_TryRevertWeatherform
	flushtextbox
	tryendneutralizinggas
	return

BattleScript_WanderingSpiritActivates::
	saveattacker
	savetarget
	copybyte gBattlerAbility, gBattlerTarget
	sethword sABILITY_OVERWRITE, ABILITY_WANDERING_SPIRIT
	call BattleScript_AbilityPopUpOverwriteThenNormal
	copybyte gBattlerAbility, gBattlerAttacker
	copyhword sABILITY_OVERWRITE, gLastUsedAbility
	call BattleScript_AbilityPopUpOverwriteThenNormal
	recordability BS_TARGET
	recordability BS_ATTACKER
	printstring STRINGID_SWAPPEDABILITIES
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	jumpiffainted BS_TARGET, TRUE, BattleScript_WanderingSpiritActivatesRet
	switchinabilities BS_TARGET
BattleScript_WanderingSpiritActivatesRet:
	restoreattacker
	restoretarget
	return

BattleScript_TargetsStatWasMaxedOut::
	call BattleScript_AbilityPopUp
	statbuffchange BS_TARGET, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_CERTAIN, BattleScript_TargetsStatWasMaxedOutRet
	printstring STRINGID_TARGETSSTATWASMAXEDOUT
	waitmessage B_WAIT_TIME_LONG
BattleScript_TargetsStatWasMaxedOutRet:
	return

BattleScript_BattlerAbilityStatRaiseOnSwitchIn::
	call BattleScript_AbilityPopUpScripting
	statbuffchange BS_SCRIPTING, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_CERTAIN, BattleScript_BattlerAbilityStatRaiseOnSwitchInRet
	waitanimation
	printstring STRINGID_SCRIPTINGABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
BattleScript_BattlerAbilityStatRaiseOnSwitchInRet:
	return

BattleScript_ScriptingAbilityStatRaise::
	copybyte gBattlerAbility, sBATTLER
	call BattleScript_AbilityPopUp
	saveattacker
	copybyte gBattlerAttacker, sBATTLER
	statbuffchange BS_ATTACKER, STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_CERTAIN, BattleScript_ScriptingAbilityStatRaiseRet
	printstring STRINGID_ATTACKERABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
BattleScript_ScriptingAbilityStatRaiseRet:
	restoreattacker
	return

BattleScript_WeakArmorActivates::
	call BattleScript_AbilityPopUp
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_WeakArmorActivatesSpeed
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_WeakArmorDefPrintString
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGE_EMPTY, BattleScript_WeakArmorActivatesSpeed
	pause B_WAIT_TIME_SHORTEST
	printfromtable gStatDownStringIds
	clearmoveresultflags MOVE_RESULT_MISSED @ Set by statbuffchange when stat can't be decreased
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_WeakArmorActivatesSpeed
BattleScript_WeakArmorDefPrintString:
	printstring STRINGID_TARGETABILITYSTATLOWER
	waitmessage B_WAIT_TIME_LONG
BattleScript_WeakArmorActivatesSpeed:
	jumpifgenconfiglowerthan CONFIG_B_WEAK_ARMOR_SPEED, GEN_7, BattleScript_WeakArmorSetSpeedGen6
	setstatchanger STAT_SPEED, 2, FALSE
	goto BattleScript_WeakArmorDoSpeed
BattleScript_WeakArmorSetSpeedGen6:
	setstatchanger STAT_SPEED, 1, FALSE
BattleScript_WeakArmorDoSpeed:
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_WeakArmorActivatesEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_WeakArmorSpeedPrintString
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGE_EMPTY, BattleScript_WeakArmorActivatesEnd
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	clearmoveresultflags MOVE_RESULT_MISSED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_WeakArmorActivatesEnd
BattleScript_WeakArmorSpeedPrintString:
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
BattleScript_WeakArmorActivatesEnd:
	return

BattleScript_RaiseStatOnFaintingTarget::
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_RaiseStatOnFaintingTarget_End
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_RaiseStatOnFaintingTarget_End
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RaiseStatOnFaintingTarget_End:
	return

BattleScript_AttackerAbilityStatRaise::
	statbuffchange BS_SCRIPTING, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_AttackerAbilityStatRaise_End
	call BattleScript_AbilityPopUpScripting
	statbuffchange BS_SCRIPTING, STAT_CHANGE_ALLOW_PTR, BattleScript_AttackerAbilityStatRaise_End
	printstring STRINGID_ATTACKERABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackerAbilityStatRaise_End:
	return

BattleScript_FellStingerRaisesStat::
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_FellStingerRaisesAtkEnd
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_CHANGED, BattleScript_FellStingerRaisesAtkEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FellStingerRaisesAtkEnd:
	return

BattleScript_AttackerAbilityStatRaiseEnd3::
	call BattleScript_AttackerAbilityStatRaise
	restoreattacker
	return

BattleScript_AttackerAbilityStatRaiseEnd2::
	call BattleScript_AttackerAbilityStatRaise
	restoreattacker
	end2

BattleScript_SwitchInAbilityMsg::
	call BattleScript_AbilityPopUp
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ActivateAsOne::
	call BattleScript_AbilityPopUp
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	@ show unnerve
	sethword sABILITY_OVERWRITE, ABILITY_UNNERVE
	setbyte cMULTISTRING_CHOOSER, B_MSG_SWITCHIN_UNNERVE
	call BattleScript_AbilityPopUp
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_FriskMsgWithPopup::
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
BattleScript_FriskMsg::
	printstring STRINGID_FRISKACTIVATES
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_FriskActivates::
	saveattacker
	savetarget
	copybyte gBattlerAttacker, sBATTLER
	tryfriskmessage
	restoreattacker
	restoretarget
	return

BattleScript_ImposterActivates::
	call BattleScript_AbilityPopUp
	transformdataexecution
	playmoveanimation MOVE_TRANSFORM
	waitanimation
	printstring STRINGID_IMPOSTERTRANSFORM
	waitmessage B_WAIT_TIME_LONG
	restoreattacker
	restoretarget
	return

BattleScript_HurtAttacker:
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printstring STRINGID_PKMNHURTSWITH
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	return

BattleScript_RoughSkinActivates::
	call BattleScript_AbilityPopUp
	call BattleScript_HurtAttacker
	return

BattleScript_RockyHelmetActivates::
	@ don't play the animation for a fainted mon
	jumpifabsent BS_TARGET, BattleScript_RockyHelmetActivatesDmg
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
BattleScript_RockyHelmetActivatesDmg:
	call BattleScript_HurtAttacker
	return

BattleScript_SpikyShieldEffect::
	jumpifabsent BS_ATTACKER, BattleScript_SpikyShieldRet
	clearmoveresultflags MOVE_RESULT_NO_EFFECT
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printstring STRINGID_PKMNHURTSWITH
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	setmoveresultflags MOVE_RESULT_MISSED
BattleScript_SpikyShieldRet::
	return

BattleScript_KingsShieldEffect::
	clearmoveresultflags MOVE_RESULT_NO_EFFECT
	seteffectsecondary BS_ATTACKER, BS_TARGET, MOVE_EFFECT_NONE
	copybyte sBATTLER, gBattlerTarget
	copybyte gBattlerTarget, gBattlerAttacker
	copybyte gBattlerAttacker, sBATTLER
	setmoveresultflags MOVE_RESULT_MISSED
	return

BattleScript_BanefulBunkerEffect::
	clearmoveresultflags MOVE_RESULT_NO_EFFECT
	setnonvolatilestatus TRIGGER_ON_PROTECT
	setmoveresultflags MOVE_RESULT_MISSED
	return

BattleScript_CuteCharmActivates::
	call BattleScript_AbilityPopUp
	volatileanimation BS_ATTACKER, VOLATILE_INFATUATION
	printstring STRINGID_PKMNSXINFATUATEDY
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTarget
	return

BattleScript_GooeyActivates::
	statbuffchange BS_ATTACKER, STAT_CHANGE_ONLY_CHECKING, BattleScript_GooeyActivatesRet
	waitstate
	call BattleScript_AbilityPopUp
	swapattackerwithtarget  @ for defiant, mirror armor
	seteffectsecondary BS_ATTACKER, BS_TARGET, MOVE_EFFECT_SPD_MINUS_1
	swapattackerwithtarget
BattleScript_GooeyActivatesRet:
	return

BattleScript_AbilityStatusEffect::
	waitstate
	call BattleScript_AbilityPopUp
	setnonvolatilestatus TRIGGER_ON_ABILITY
	return

BattleScript_BattleBondActivatesOnMoveEndAttacker::
	pause 5
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_ATTACKERBECAMEFULLYCHARGED
	handleformchange BS_ATTACKER, 0
	playanimation BS_ATTACKER, B_ANIM_FORM_CHANGE
	waitanimation
	handleformchange BS_ATTACKER, 1
	printstring STRINGID_ATTACKERBECAMEASHSPECIES
	return

BattleScript_EffectBattleBondStatIncrease::
	call BattleScript_AbilityPopUp
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectBattleBondStatIncreaseTrySpAtk, BIT_SPATK | BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_EffectBattleBondStatIncreaseTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectBattleBondStatIncreaseTrySpAtk:
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectBattleBondStatIncreaseTrySpeed, BIT_SPEED
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_EffectBattleBondStatIncreaseTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectBattleBondStatIncreaseTrySpeed:
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_EffectBattleBondStatIncreaseRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_EffectBattleBondStatIncreaseRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectBattleBondStatIncreaseRet:
	return

BattleScript_DancerActivates::
	call BattleScript_AbilityPopUp
	waitmessage B_WAIT_TIME_SHORT
	jumptocalledmove TRUE

BattleScript_SynchronizeActivates::
	waitstate
	call BattleScript_AbilityPopUp
	setnonvolatilestatus TRIGGER_ON_ABILITY
	return

BattleScript_NoItemSteal::
	call BattleScript_AbilityPopUpTarget
	printstring STRINGID_PKMNSXMADEYINEFFECTIVE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityCuredStatus::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXCUREDITSYPROBLEM
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	return

BattleScript_BattlerShookOffTaunt::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSHOOKOFFTHETAUNT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BattlerGotOverItsInfatuation::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNGOTOVERITSINFATUATION
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_IgnoresWhileAsleep::
	printstring STRINGID_PKMNIGNORESASLEEP
	waitmessage B_WAIT_TIME_LONG
	moveendto MOVEEND_NEXT_TARGET
	end

BattleScript_IgnoresAndUsesRandomMove::
	printstring STRINGID_PKMNIGNOREDORDERS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveUsedLoafingAround::
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_LOAFING, BattleScript_MoveUsedLoafingAroundMsg
	@ Skip ahead if not the Battle Palace message
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_INCAPABLE_OF_POWER, BattleScript_MoveUsedLoafingAroundMsg
	setbyte gBattleCommunication, 0
	palacetryescapestatus
	setbyte cMULTISTRING_CHOOSER, B_MSG_INCAPABLE_OF_POWER
BattleScript_MoveUsedLoafingAroundMsg::
	printfromtable gInobedientStringIds
	waitmessage B_WAIT_TIME_LONG
	moveendto MOVEEND_NEXT_TARGET
	end
BattleScript_TruantLoafingAround::
	flushtextbox
	call BattleScript_AbilityPopUp
	goto BattleScript_MoveUsedLoafingAroundMsg

BattleScript_IgnoresAndFallsAsleep::
	printstring STRINGID_PKMNBEGANTONAP
	waitmessage B_WAIT_TIME_LONG
	seteffectprimary BS_ATTACKER, BS_ATTACKER, MOVE_EFFECT_SLEEP
	moveendto MOVEEND_NEXT_TARGET
	end

BattleScript_IgnoresAndHitsItself::
	printstring STRINGID_PKMNWONTOBEY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoSelfConfusionDmg

BattleScript_SubstituteFade::
	playanimation BS_TARGET, B_ANIM_SUBSTITUTE_FADE
	printstring STRINGID_PKMNSUBSTITUTEFADED
	return

BattleScript_BerryCureStatusRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printfromtable CureStatusBerryEffectStringID
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_GemActivates::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_GEMACTIVATES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

BattleScript_BerryReduceDmg::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_BERRYDMGREDUCES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureConfusionRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMSNAPPEDOUT
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_MentalHerbCureRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printfromtable gMentalHerbCureStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_MentalHerbCureFling::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printfromtable gMentalHerbCureStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	return

BattleScript_MentalHerbCureEnd2::
	call BattleScript_MentalHerbCureRet
	end2

BattleScript_WhiteHerbEnd2::
	call BattleScript_WhiteHerbRet
	end2

BattleScript_WhiteHerbRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDSTATUS
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_WhiteHerbFling::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDSTATUS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ItemHealHP_RemoveItem::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_ItemHealHP_RemoveItemRet_AbilityPopUp
	goto BattleScript_ItemHealHP_RemoveItemRet_Anim
BattleScript_ItemHealHP_RemoveItemRet_AbilityPopUp:
	call BattleScript_AbilityPopUpScripting
BattleScript_ItemHealHP_RemoveItemRet_Anim:
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	healthbarupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	datahpupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	removeitem BS_SCRIPTING
	return

BattleScript_BerryPPHeal::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_BerryPPHeal_AbilityPopup
	goto BattleScript_BerryPPHeal_Anim
BattleScript_BerryPPHeal_AbilityPopup:
	call BattleScript_AbilityPopUpScripting
BattleScript_BerryPPHeal_Anim:
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDPP
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_ItemHealHP_End2::
	call BattleScript_ItemHealHP_Ret
	end2

BattleScript_AirBalloonMsgInRet::
	printstring STRINGID_AIRBALLOONFLOAT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AirBalloonMsgPop::
	printstring STRINGID_AIRBALLOONPOP
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
	return

BattleScript_ItemHurtRet::
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	printstring STRINGID_HURTBYITEM
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	return

BattleScript_ItemHurtEnd2::
	playanimation BS_ATTACKER, B_ANIM_MON_HIT
	waitanimation
	call BattleScript_ItemHurtRet
	end2

BattleScript_ItemHealHP_Ret::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDHPALITTLE
	waitmessage B_WAIT_TIME_LONG
	healthbarupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	datahpupdate BS_ATTACKER, PASSIVE_HP_UPDATE
	return

BattleScript_SelectingNotAllowedMoveChoiceItem::
	printselectionstring STRINGID_ITEMALLOWSONLYYMOVE
	endselectionscript

BattleScript_SelectingNotAllowedMoveChoiceItemInPalace::
	printstring STRINGID_ITEMALLOWSONLYYMOVE
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedMoveGorillaTactics::
	printselectionstring STRINGID_ABILITYALLOWSONLYMOVE
	endselectionscript

BattleScript_SelectingNotAllowedMoveGorillaTacticsInPalace::
	printstring STRINGID_ABILITYALLOWSONLYMOVE
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedMoveAssaultVest::
	printselectionstring STRINGID_ASSAULTVESTDOESNTALLOW
	endselectionscript

BattleScript_SelectingNotAllowedMoveAssaultVestInPalace::
	printstring STRINGID_ASSAULTVESTDOESNTALLOW
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedPlaceholder::
	printselectionstring STRINGID_NOTDONEYET
	endselectionscript

BattleScript_SelectingNotAllowedPlaceholderInPalace::
	printstring STRINGID_NOTDONEYET
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_HangedOnMsg::
	playanimation BS_TARGET, B_ANIM_HANGED_ON
	printstring STRINGID_PKMNHUNGONWITHX
	waitmessage B_WAIT_TIME_LONG
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_FOCUS_SASH, BattleScript_HangedOnMsgRet
	removeitem BS_TARGET
BattleScript_HangedOnMsgRet:
	return

BattleScript_BerryConfuseHeal::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_BerryConfuseHealRet_AbilityPopup
	goto BattleScript_BerryConfuseHealRet_Anim
BattleScript_BerryConfuseHealRet_AbilityPopup:
	call BattleScript_AbilityPopUp
BattleScript_BerryConfuseHealRet_Anim:
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	healthbarupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	datahpupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	seteffectprimary BS_SCRIPTING, BS_SCRIPTING, MOVE_EFFECT_CONFUSION
	removeitem BS_SCRIPTING
	return

BattleScript_ConsumableStatRaiseRet::
	jumpifnotberry BS_SCRIPTING, BattleScript_ConsumableStatRaiseRet_Anim
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_ConsumableStatRaiseRet_AbilityPopup
	goto BattleScript_ConsumableStatRaiseRet_Anim
BattleScript_ConsumableStatRaiseRet_AbilityPopup:
	call BattleScript_AbilityPopUp
BattleScript_ConsumableStatRaiseRet_Anim:
	statbuffchange BS_SCRIPTING, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_ConsumableStatRaiseRet_End
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	statbuffchange BS_SCRIPTING, STAT_CHANGE_ALLOW_PTR, BattleScript_ConsumableStatRaiseRet_End
	setbyte cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGED_ITEM
	savetarget
	copybyte gBattlerTarget, sBATTLER @ BattleScript_StatUp uses target as a message arg
	call BattleScript_StatUp
	restoretarget
	removeitem BS_SCRIPTING
BattleScript_ConsumableStatRaiseRet_End:
	return

BattleScript_BerryFocusEnergy::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNUSEDXTOGETPUMPED
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_ActionSelectionItemsCantBeUsed::
	printselectionstring STRINGID_ITEMSCANTBEUSEDNOW
	endselectionscript

BattleScript_FlushMessageBox::
	flushtextbox
	return

BattleScript_PalacePrintFlavorText::
	setbyte gBattleCommunication + 1, 0
BattleScript_PalaceTryBattlerFlavorText::
	palaceflavortext
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, TRUE, BattleScript_PalaceEndFlavorText
	printfromtable gBattlePalaceFlavorTextTable
	waitmessage B_WAIT_TIME_LONG
BattleScript_PalaceEndFlavorText::
	addbyte gBattleCommunication + 1, 1
	jumpifbytenotequal gBattleCommunication + 1, gBattlersCount, BattleScript_PalaceTryBattlerFlavorText
	setbyte gBattleCommunication, 0
	setbyte gBattleCommunication + 1, 0
	end2

BattleScript_ArenaTurnBeginning::
	waitcry
	volumedown
	playse SE_ARENA_TIMEUP1
	pause 8
	playse SE_ARENA_TIMEUP1
	drawarenareftextbox
	arenajudgmentstring B_MSG_REF_COMMENCE_BATTLE
	arenawaitmessage
	pause B_WAIT_TIME_LONG
	erasearenareftextbox
	volumeup
	end2

BattleScript_ArenaDoJudgment::
	makevisible BS_PLAYER1
	waitstate
	makevisible BS_OPPONENT1
	waitstate
	volumedown
	playse SE_ARENA_TIMEUP1
	pause 8
	playse SE_ARENA_TIMEUP1
	pause B_WAIT_TIME_LONG
	drawarenareftextbox
	arenajudgmentstring B_MSG_REF_THATS_IT
	arenawaitmessage
	pause B_WAIT_TIME_LONG
	setbyte gBattleCommunication, 0  @ Reset state for arenajudgmentwindow
	arenajudgmentwindow
	pause B_WAIT_TIME_LONG
	arenajudgmentwindow
	arenajudgmentstring B_MSG_REF_JUDGE_MIND
	arenawaitmessage
	arenajudgmentwindow
	arenajudgmentstring B_MSG_REF_JUDGE_SKILL
	arenawaitmessage
	arenajudgmentwindow
	arenajudgmentstring B_MSG_REF_JUDGE_BODY
	arenawaitmessage
	arenajudgmentwindow
	jumpifbyte CMP_EQUAL, gBattleCommunication + 1, ARENA_RESULT_PLAYER_LOST, BattleScript_ArenaJudgmentPlayerLoses
	jumpifbyte CMP_EQUAL, gBattleCommunication + 1, ARENA_RESULT_TIE, BattleScript_ArenaJudgmentDraw
@ ARENA_RESULT_PLAYER_WON
	arenajudgmentstring B_MSG_REF_PLAYER_WON
	arenawaitmessage
	arenajudgmentwindow
	erasearenareftextbox
	printstring STRINGID_DEFEATEDOPPONENTBYREFEREE
	waitmessage B_WAIT_TIME_LONG
	undodynamax BS_OPPONENT1
	playfaintcry BS_OPPONENT1
	waitcry
	dofaintanimation BS_OPPONENT1
	cleareffectsonfaint BS_OPPONENT1
	waitanimation
	arenaopponentmonlost
	end2

BattleScript_ArenaJudgmentPlayerLoses:
	arenajudgmentstring B_MSG_REF_OPPONENT_WON
	arenawaitmessage
	arenajudgmentwindow
	erasearenareftextbox
	printstring STRINGID_LOSTTOOPPONENTBYREFEREE
	waitmessage B_WAIT_TIME_LONG
	undodynamax BS_PLAYER1
	playfaintcry BS_PLAYER1
	waitcry
	dofaintanimation BS_PLAYER1
	cleareffectsonfaint BS_PLAYER1
	waitanimation
	arenaplayermonlost
	end2

BattleScript_ArenaJudgmentDraw:
	arenajudgmentstring B_MSG_REF_DRAW
	arenawaitmessage
	arenajudgmentwindow
	erasearenareftextbox
	printstring STRINGID_TIEDOPPONENTBYREFEREE
	waitmessage B_WAIT_TIME_LONG
	arenabothmonslost
	undodynamax BS_PLAYER1
	playfaintcry BS_PLAYER1
	waitcry
	dofaintanimation BS_PLAYER1
	cleareffectsonfaint BS_PLAYER1
	waitanimation
	undodynamax BS_OPPONENT1
	playfaintcry BS_OPPONENT1
	waitcry
	dofaintanimation BS_OPPONENT1
	cleareffectsonfaint BS_OPPONENT1
	waitanimation
	end2

BattleScript_AskIfWantsToForfeitMatch::
	printselectionstring STRINGID_QUESTIONFORFEITMATCH
	forfeityesnobox
	endselectionscript

BattleScript_PrintPlayerForfeited::
	printstring STRINGID_FORFEITEDMATCH
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_PrintPlayerForfeitedLinkBattle::
	printstring STRINGID_FORFEITEDMATCH
	waitmessage B_WAIT_TIME_LONG
	endlinkbattle
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_TotemFlaredToLife::
	playanimation BS_ATTACKER, B_ANIM_TOTEM_FLARE, NULL
	printstring STRINGID_AURAFLAREDTOLIFE
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ApplyTotemVarBoost
	end2

BattleScript_MirrorHerbCopyStatChangeEnd2::
	call BattleScript_MirrorHerbCopyStatChange
	end2

BattleScript_MirrorHerbCopyStatChange::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, NULL
	printstring STRINGID_MIRRORHERBCOPIED
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
BattleScript_MirrorHerbStartCopyStats:
	copyfoesstatincrease BS_SCRIPTING, BattleScript_MirrorHerbStartReturn
	statbuffchange BS_SCRIPTING, STAT_CHANGE_ALLOW_PTR, BattleScript_MirrorHerbStartReturn
	setbyte sSTAT_ANIM_PLAYED, TRUE @ play stat change animation only once
	goto BattleScript_MirrorHerbStartCopyStats
BattleScript_MirrorHerbStartReturn:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	return

BattleScript_OpportunistCopyStatChange::
	call BattleScript_AbilityPopUpScripting
BattleScript_OpportunistStartCopyStats:
	copyfoesstatincrease BS_SCRIPTING, BattleScript_OpportunistCopyStatChangeEnd
	statbuffchange BS_SCRIPTING, STAT_CHANGE_ALLOW_PTR, BattleScript_OpportunistCopyStatChangeEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	setbyte sSTAT_ANIM_PLAYED, TRUE @ play stat change animation only once
	goto BattleScript_OpportunistStartCopyStats
BattleScript_OpportunistCopyStatChangeEnd:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	return

BattleScript_TotemVar::
	call BattleScript_TotemVar_Ret
	end2

BattleScript_TotemVar_Ret::
	gettotemboost BattleScript_ApplyTotemVarBoost
BattleScript_TotemVarEnd:
	return
BattleScript_ApplyTotemVarBoost:
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_TotemVarEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_TotemVar_Ret  @loop until stats bitfield is empty


BattleScript_AnnounceAirLockCloudNine::
	call BattleScript_AbilityPopUp
	printstring STRINGID_AIRLOCKACTIVATES
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ActivateWeatherAbilities
	return

BattleScript_ActivateTeraformZero::
	call BattleScript_AbilityPopUp
	waitmessage B_WAIT_TIME_LONG
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_ANY, BattleScript_ActivateTeraformZero_RemoveWeather
	jumpifhalfword CMP_COMMON_BITS, gFieldStatuses, STATUS_FIELD_TERRAIN_ANY, BattleScript_ActivateTeraformZero_RemoveTerrain
	goto BattleScript_ActivateTeraformZero_Ret
BattleScript_ActivateTeraformZero_RemoveWeather:
	removeweather
	printfromtable gWeatherEndsStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ActivateWeatherAbilities
	jumpifhalfword CMP_NO_COMMON_BITS, gFieldStatuses, STATUS_FIELD_TERRAIN_ANY, BattleScript_ActivateTeraformZeroEffects
BattleScript_ActivateTeraformZero_RemoveTerrain:
	removeterrain
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ActivateTeraformZeroEffects:
	saveattacker
	savetarget
	tryboosterenergy ON_ANY
	resetterrainabilityflags
	setbyte gBattlerAttacker, 0
	sortbattlers
BattleScript_ActivateTeraformZeroLoop:
	copyarraywithindex gBattlerTarget, gBattlersBySpeed, gBattlerAttacker, 1
	activateterrainchangeabilities BS_TARGET
	activateweatherchangeabilities BS_TARGET
	addbyte gBattlerAttacker, 1
	jumpifbytenotequal gBattlerAttacker, gBattlersCount, BattleScript_ActivateTeraformZeroLoop
	restoreattacker
	restoretarget
BattleScript_ActivateTeraformZero_Ret:
	return

BattleScript_QuickClawActivation::
	flushtextbox
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_CANACTFASTERTHANKSTO
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_QuickDrawActivation::
	flushtextbox
	call BattleScript_AbilityPopUp
	printstring STRINGID_CANACTFASTERTHANKSTO
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_CustapBerryActivation::
	flushtextbox
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_CANACTFASTERTHANKSTO
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	end2

BattleScript_MicleBerryActivate::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_MicleBerryActivateRet_Ripen
	goto BattleScript_MicleBerryActivateRet_Anim
BattleScript_MicleBerryActivateRet_Ripen:
	call BattleScript_AbilityPopUpScripting
BattleScript_MicleBerryActivateRet_Anim:
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_MICLEBERRYACTIVATES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_JabocaRowapBerryActivates::
	jumpifability BS_TARGET, ABILITY_RIPEN, BattleScript_JabocaRowapBerryActivate_Ripen
	goto BattleScript_JabocaRowapBerryActivate_Anim
BattleScript_JabocaRowapBerryActivate_Ripen:
	call BattleScript_AbilityPopUp
BattleScript_JabocaRowapBerryActivate_Anim:
	jumpifabsent BS_TARGET, BattleScript_JabocaRowapBerryActivate_Dmg   @ dont play the animation for a fainted target
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
BattleScript_JabocaRowapBerryActivate_Dmg:
	call BattleScript_HurtAttacker
	removeitem BS_TARGET
	return

@ z moves / effects
BattleScript_ZMoveActivateDamaging::
	flushtextbox
	trytrainerslidezmovemsg
	printstring STRINGID_ZPOWERSURROUNDS
	playanimation BS_ATTACKER, B_ANIM_ZMOVE_ACTIVATE, NULL
	printstring STRINGID_ZMOVEUNLEASHED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ZMoveActivateStatus::
	flushtextbox
	trytrainerslidezmovemsg
	savetarget
	printstring STRINGID_ZPOWERSURROUNDS
	playanimation BS_ATTACKER, B_ANIM_ZMOVE_ACTIVATE, NULL
	setzeffect
	restoretarget
	copybyte sSTATCHANGER, sSAVED_STAT_CHANGER
	return

BattleScript_ZEffectPrintString::
	printfromtable gZEffectStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_RecoverHPZMove::
	healthbarupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	datahpupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	printfromtable gZEffectStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_StatUpZMove::
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_StatUpZMoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_StatUpZMoveEnd
	printstring STRINGID_ZMOVESTATUP
	waitmessage B_WAIT_TIME_LONG
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StatUpZMoveEnd:
	return

BattleScript_HealReplacementZMove::
	playanimation BS_SCRIPTING, B_ANIM_WISH_HEAL, 0x0
	printfromtable gZEffectStringIds
	waitmessage B_WAIT_TIME_LONG
	healthbarupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	datahpupdate BS_SCRIPTING, PASSIVE_HP_UPDATE
	return

BattleScript_EffectExtremeEvoboost::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	goto BattleScript_ButItFailed
BattleScript_ExtremeEvoboostAnim:
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostDef, BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostDef::
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostSpeed, BIT_SPEED | BIT_SPATK | BIT_SPDEF
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostSpeed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostSpAtk, BIT_SPATK | BIT_SPDEF
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostSpAtk::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostSpDef, BIT_SPDEF
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostSpDef::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostEnd::
	goto BattleScript_MoveEnd

// PRU: Eevoboost is a separate native one-stage stat increase for all five stats.
// Do not change the existing Extreme Evoboost +2 Z-Move behaviour.
BattleScript_EffectPRUEevoboost::
	attackcanceler
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_PRUEevoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_PRUEevoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_PRUEevoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_PRUEevoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_PRUEevoboostAnim
	goto BattleScript_ButItFailed
BattleScript_PRUEevoboostAnim:
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_PRUEevoboostDef, BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PRUEevoboostDef::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_PRUEevoboostSpeed, BIT_SPEED | BIT_SPATK | BIT_SPDEF
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PRUEevoboostSpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_PRUEevoboostSpAtk, BIT_SPATK | BIT_SPDEF
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PRUEevoboostSpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_PRUEevoboostSpDef, BIT_SPDEF
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PRUEevoboostSpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange BS_ATTACKER, STAT_CHANGE_ALLOW_PTR, BattleScript_PRUEevoboostEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PRUEevoboostEnd::
	goto BattleScript_MoveEnd

BattleScript_RemoveTerrain::
	removeterrain
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_Pickpocket::
	call BattleScript_AbilityPopUp
	jumpifability BS_ATTACKER, ABILITY_STICKY_HOLD, BattleScript_PickpocketPrevented
	swapattackerwithtarget
	copybyte gEffectBattler, gBattlerTarget
	call BattleScript_ItemSteal
	swapattackerwithtarget
	activateitemeffects
	return

BattleScript_PickpocketPrevented:
	pause B_WAIT_TIME_SHORT
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_ITEMCANNOTBEREMOVED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_StickyBarbTransfer::
	playanimation BS_TARGET, B_ANIM_ITEM_STEAL
	printstring STRINGID_STICKYBARBTRANSFER
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
	return

BattleScript_RedCardActivationNoSwitch::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_REDCARDACTIVATE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	restoretarget
	restoreattacker
	return

BattleScript_RedCardActivates::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_REDCARDACTIVATE
	waitmessage B_WAIT_TIME_LONG
	swapattackerwithtarget
	jumpifvolatile BS_EFFECT_BATTLER, VOLATILE_ROOT, BattleScript_RedCardIngrain
	jumpifability BS_EFFECT_BATTLER, ABILITY_SUCTION_CUPS, BattleScript_RedCardSuctionCups
	jumpiftargetdynamaxed BattleScript_RedCardDynamaxed
	removeitem BS_SCRIPTING
	setbyte sSWITCH_CASE, B_SWITCH_RED_CARD
	forcerandomswitch BattleScript_RedCardEnd
	@ changes the current battle script. the rest happens in BattleScript_RoarSuccessSwitch_Ret, if switch is successful
BattleScript_RedCardIngrain:
	printstring STRINGID_PKMNANCHOREDITSELF
BattleScript_RedCardIngrainContinue:
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	goto BattleScript_RedCardEnd
BattleScript_RedCardSuctionCups:
	printstring STRINGID_PKMNANCHORSITSELFWITH
	goto BattleScript_RedCardIngrainContinue
BattleScript_RedCardDynamaxed:
	printstring STRINGID_MOVEBLOCKEDBYDYNAMAX
	goto BattleScript_RedCardIngrainContinue

BattleScript_RedCardEnd:
	restoretarget
	restoreattacker
	return

BattleScript_EjectButtonActivates::
	makevisible BS_ATTACKER
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_EJECTBUTTONACTIVATE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	undodynamax BS_SCRIPTING
	makeinvisible BS_SCRIPTING
	openpartyscreen BS_SCRIPTING, BattleScript_EjectButtonEnd
	waitstate
	returntoball BS_SCRIPTING, FALSE
	copybyte sSAVED_BATTLER, sBATTLER
	switchoutabilities BS_SCRIPTING
	copybyte sBATTLER, sSAVED_BATTLER
	switchhandleorder BS_SCRIPTING, 0x2
	getswitchedmondata BS_SCRIPTING
	switchindataupdate BS_SCRIPTING
	hpthresholds BS_SCRIPTING
	trytoclearprimalweather
	flushtextbox
	printstring 0x3
	switchinanim BS_SCRIPTING, FALSE, TRUE
	waitstate
	switchineffects BS_SCRIPTING
	switchinevents
BattleScript_EjectButtonEnd:
	return

BattleScript_EjectPackActivate_Ret::
	goto BattleScript_EjectButtonActivates

BattleScript_EjectPackActivate_End2::
	call BattleScript_EjectPackActivate_Ret
	end2

BattleScript_EjectPackActivates::
	jumpifcantswitch BS_SCRIPTING, BattleScript_EjectButtonEnd
	goto BattleScript_EjectPackActivate_Ret

BattleScript_DoesntAffectTargetAtkString::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	setmoveresultflags MOVE_RESULT_NO_EFFECT
	goto BattleScript_MoveEnd

BattleScript_NoEffectivenessAbility::
	call BattleScript_AbilityPopUp
BattleScript_DoesntAffectScripting::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_SCR_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_GoodAsGoldActivates::
	call BattleScript_AbilityPopUp
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_SCR_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_MED
	return

BattleScript_PastelVeilActivates::
	setbyte gBattleCommunication, 0
	setbyte gBattleCommunication + 1, 0
BattleScript_PastelVeil_TryCurePoison:
	jumpifstatus BS_TARGET, STATUS1_POISON | STATUS1_TOXIC_POISON, BattleScript_PastelVeilCurePoison
	goto BattleScript_PastelVeilLoopIncrement
BattleScript_PastelVeilCurePoison:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication + 1, 0x0, BattleScript_PastelVeilCurePoisonNoPopUp
	call BattleScript_AbilityPopUp
	setbyte gBattleCommunication + 1, 1
BattleScript_PastelVeilCurePoisonNoPopUp: @ Only show Pastel Veil pop up once if it cures two mons
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
BattleScript_PastelVeilLoopIncrement:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_PastelVeilEnd
	addbyte gBattleCommunication, 1
	jumpifnoally BS_TARGET, BattleScript_PastelVeilEnd
	setallytonexttarget BattleScript_PastelVeil_TryCurePoison
	goto BattleScript_PastelVeilEnd
BattleScript_PastelVeilEnd:
	restoretarget
	return

BattleScript_NeutralizingGasExits::
	saveattacker
	savetarget
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NEUTRALIZINGGASOVER
	waitmessage B_WAIT_TIME_LONG
	setbyte gBattlerAttacker, 0
	sortbattlers
BattleScript_NeutralizingGasExitsLoop:
	copyarraywithindex gBattlerTarget, gBattlersBySpeed, gBattlerAttacker, 1
	jumpifabilitycantbereactivated BS_TARGET, BattleScript_NeutralizingGasExitsLoopIncrement
	saveattacker
	switchinabilities BS_TARGET
	restoreattacker
BattleScript_NeutralizingGasExitsLoopIncrement:
	addbyte gBattlerAttacker, 1
	jumpifbytenotequal gBattlerAttacker, gBattlersCount, BattleScript_NeutralizingGasExitsLoop
	restoreattacker
	restoretarget
	return

BattleScript_MagicianActivates::
	call BattleScript_AbilityPopUp
	call BattleScript_ItemSteal
	return

BattleScript_SymbiosisActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_SYMBIOSISITEMPASS
	waitmessage B_WAIT_TIME_LONG
	tryactivateabilitywithabilityshield BS_EFFECT_BATTLER, FALSE
	return

BattleScript_TargetAbilityStatRaiseRet::
	saveattacker
	copybyte gBattlerAttacker, gEffectBattler
	call BattleScript_AbilityPopUp
	statbuffchange BS_ATTACKER, STAT_CHANGE_CERTAIN, BattleScript_TargetAbilityStatRaiseRet_End
	call BattleScript_StatUp
BattleScript_TargetAbilityStatRaiseRet_End:
	restoreattacker
	return

BattleScript_EffectRaiseStatAllies::
	savetarget
	copybyte gBattlerTarget, gBattlerAttacker
	copybyte sSAVED_STAT_CHANGER, sSTATCHANGER
BattleScript_RaiseSideStatsLoop:
	jumpifabsent BS_TARGET, BattleScript_RaiseSideStatsIncrement
	copybyte sSTATCHANGER, sSAVED_STAT_CHANGER
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_RaiseSideStatsIncrement
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_RaiseSideStatsIncrement
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RaiseSideStatsIncrement:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_RaiseSideStatsEnd
	setallytonexttarget BattleScript_RaiseSideStatsLoop
BattleScript_RaiseSideStatsEnd:
	restoretarget
	return

BattleScript_EffectLowerStatFoes::
	savetarget
	copybyte sBATTLER, gBattlerTarget
	copybyte sSAVED_STAT_CHANGER, sSTATCHANGER
BattleScript_LowerSideStatsLoop:
	jumpifabsent BS_TARGET, BattleScript_LowerSideStatsIncrement
	copybyte sSTATCHANGER, sSAVED_STAT_CHANGER
	statbuffchange BS_TARGET, STAT_CHANGE_ALLOW_PTR, BattleScript_LowerSideStatsIncrement
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_CHANGE, BattleScript_LowerSideStatsIncrement
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_LowerSideStatsIncrement:
	jumpifbytenotequal gBattlerTarget, sBATTLER, BattleScript_LowerSideStatsEnd
	setallytonexttarget BattleScript_LowerSideStatsLoop
BattleScript_LowerSideStatsEnd:
	restoretarget
	return

BattleScript_EffectSetWeather::
	playanimation 0, B_ANIM_MAX_SET_WEATHER
	printfromtable gMoveWeatherChangeStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ActivateWeatherAbilities
	return

BattleScript_EffectSetTerrain::
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	return

BattleScript_DamageNonTypesStarts::
	printfromtable gDamageNonTypesStartStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_DamageNonTypesContinues::
	printfromtable gDamageNonTypesDmgStringIds
	waitmessage B_WAIT_TIME_LONG
	effectivenesssound
	hitanimation BS_ATTACKER
	goto BattleScript_DoTurnDmg

BattleScript_EffectTryReducePP::
	tryspiteppreduce BattleScript_MoveEnd
	printstring STRINGID_PKMNREDUCEDPP
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectParalyzeSide::
	savetarget
	copybyte sBATTLER, gBattlerTarget
BattleScript_ParalyzeSideLoop:
	jumpifabsent BS_TARGET, BattleScript_ParalyzeSideIncrement
	trysetparalysis BattleScript_ParalyzeSideIncrement
BattleScript_ParalyzeSideIncrement:
	jumpifbytenotequal gBattlerTarget, sBATTLER, BattleScript_ParalyzeSideEnd
	setallytonexttarget BattleScript_ParalyzeSideLoop
BattleScript_ParalyzeSideEnd:
	restoretarget
	return

BattleScript_EffectPoisonSide::
	savetarget
	copybyte sBATTLER, gBattlerTarget
BattleScript_PoisonSideLoop:
	jumpifabsent BS_TARGET, BattleScript_PoisonSideIncrement
	trysetpoison BattleScript_PoisonSideIncrement
BattleScript_PoisonSideIncrement:
	jumpifbytenotequal gBattlerTarget, sBATTLER, BattleScript_PoisonSideEnd
	setallytonexttarget BattleScript_PoisonSideLoop
BattleScript_PoisonSideEnd:
	restoretarget
	return

BattleScript_EffectPoisonParalyzeSide::
	savetarget
	copybyte sBATTLER, gBattlerTarget
BattleScript_PoisonParalyzeSideLoop:
	jumpifabsent BS_TARGET, BattleScript_PoisonParalyzeSideIncrement
	trysetpoisonparalysis BattleScript_PoisonParalyzeSideIncrement
BattleScript_PoisonParalyzeSideIncrement:
	jumpifbytenotequal gBattlerTarget, sBATTLER, BattleScript_PoisonParalyzeSideEnd
	setallytonexttarget BattleScript_PoisonParalyzeSideLoop
BattleScript_PoisonParalyzeSideEnd:
	restoretarget
	return

BattleScript_EffectEffectSporeSide::
	savetarget
	copybyte sBATTLER, gBattlerTarget
BattleScript_EffectSporeSideLoop:
	jumpifabsent BS_TARGET, BattleScript_EffectSporeSideIncrement
	tryseteffectspore BattleScript_EffectSporeSideIncrement
BattleScript_EffectSporeSideIncrement:
	jumpifbytenotequal gBattlerTarget, sBATTLER, BattleScript_EffectSporeSideEnd
	setallytonexttarget BattleScript_EffectSporeSideLoop
BattleScript_EffectSporeSideEnd:
	restoretarget
	return

BattleScript_EffectConfuseSide::
	savetarget
	copybyte sBATTLER, gBattlerTarget
BattleScript_ConfuseSideLoop:
	jumpifabsent BS_TARGET, BattleScript_ConfuseSideIncrement
	trysetconfusion BattleScript_ConfuseSideIncrement
	volatileanimation BS_EFFECT_BATTLER, VOLATILE_CONFUSION
BattleScript_ConfuseSidePrintMessage:
	printstring STRINGID_PKMNWASCONFUSED
	waitmessage B_WAIT_TIME_LONG
BattleScript_ConfuseSideIncrement:
	jumpifbytenotequal gBattlerTarget, sBATTLER, BattleScript_ConfuseSideEnd
	setallytonexttarget BattleScript_ConfuseSideLoop
BattleScript_ConfuseSideEnd:
	restoretarget
	jumpifbyte CMP_EQUAL, gBattleCommunication + 1, 1, BattleScript_PrintCoinsScattered @ Gold Rush
	return

BattleScript_PrintCoinsScattered:
	printstring STRINGID_COINSSCATTERED
	return

BattleScript_EffectInfatuateSide::
	savetarget
	copybyte sBATTLER, gBattlerTarget
BattleScript_InfatuateSideLoop:
	jumpifabsent BS_TARGET, BattleScript_InfatuateSideIncrement
	trysetinfatuation BattleScript_InfatuateSideIncrement
	volatileanimation BS_EFFECT_BATTLER, VOLATILE_INFATUATION
BattleScript_InfatuateSidePrintMessage:
	printstring STRINGID_PKMNFELLINLOVE
	waitmessage B_WAIT_TIME_LONG
BattleScript_InfatuateSideIncrement:
	jumpifbytenotequal gBattlerTarget, sBATTLER, BattleScript_InfatuateSideEnd
	setallytonexttarget BattleScript_InfatuateSideLoop
BattleScript_InfatuateSideEnd:
	restoretarget
	return

BattleScript_EffectTormentSide::
	savetarget
	copybyte sBATTLER, gBattlerTarget
BattleScript_TormentSideLoop:
	jumpifabsent BS_TARGET, BattleScript_TormentSideIncrement
	trysettorment BattleScript_TormentSideIncrement
BattleScript_TormentSidePrintMessage:
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
BattleScript_TormentSideIncrement:
	jumpifbytenotequal gBattlerTarget, sBATTLER, BattleScript_TormentSideEnd
	setallytonexttarget BattleScript_TormentSideLoop
BattleScript_TormentSideEnd:
	restoretarget
	return

BattleScript_TormentEnds::
	printstring STRINGID_TORMENTEDNOMORE
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_EffectMeanLookSide::
	savetarget
	copybyte sBATTLER, gBattlerTarget
BattleScript_MeanLookSideLoop:
	jumpifabsent BS_TARGET, BattleScript_MeanLookSideIncrement
	trysetescapeprevention BattleScript_MeanLookSideIncrement
BattleScript_MeanLookSidePrintMessage:
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
BattleScript_MeanLookSideIncrement:
	jumpifbytenotequal gBattlerTarget, sBATTLER, BattleScript_MeanLookSideEnd
	setallytonexttarget BattleScript_MeanLookSideLoop
BattleScript_MeanLookSideEnd:
	restoretarget
	return

BattleScript_EffectRaiseCritAlliesAnim::
	savetarget
	copybyte gBattlerTarget, gBattlerAttacker
BattleScript_RaiseCritAlliesLoop:
	jumpifabsent BS_TARGET, BattleScript_RaiseCritAlliesIncrement
	setstatchanger STAT_ATK, 0, FALSE @ for animation
	statbuffchange BS_TARGET, 0, BattleScript_RaiseCritAlliesIncrement @ for animation
	printstring STRINGID_PKMNGETTINGPUMPED
	waitmessage B_WAIT_TIME_LONG
BattleScript_RaiseCritAlliesIncrement:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_RaiseCritAlliesEnd
	setallytonexttarget BattleScript_RaiseCritAlliesLoop
BattleScript_RaiseCritAlliesEnd:
	restoretarget
	return

BattleScript_EffectHealOneSixthAllies::
	jumpifteamhealthy BattleScript_MoveEnd
	savetarget
	copybyte gBattlerTarget, gBattlerAttacker
BattleScript_HealOneSixthAlliesLoop:
	jumpifabsent BS_TARGET, BattleScript_HealOneSixthAlliesIncrement
	tryhealsixthhealth BattleScript_HealOneSixthAlliesIncrement
	healthbarupdate BS_TARGET, PASSIVE_HP_UPDATE
	datahpupdate BS_TARGET, PASSIVE_HP_UPDATE
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_HealOneSixthAlliesIncrement:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_HealOneSixthAlliesEnd
	setallytonexttarget BattleScript_HealOneSixthAlliesLoop
BattleScript_HealOneSixthAlliesEnd:
	restoretarget
	return

BattleScript_EffectRecycleBerriesAllies::
	savetarget
	copybyte gBattlerTarget, gBattlerAttacker
BattleScript_RecycleBerriesAlliesLoop:
	jumpifabsent BS_TARGET, BattleScript_RecycleBerriesAlliesIncrement
	tryrecycleberry BattleScript_RecycleBerriesAlliesIncrement
	swapattackerwithtarget
	printstring STRINGID_XFOUNDONEY
	waitmessage B_WAIT_TIME_LONG
	swapattackerwithtarget
BattleScript_RecycleBerriesAlliesIncrement:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_RecycleBerriesAlliesEnd
	setallytonexttarget BattleScript_RecycleBerriesAlliesLoop
BattleScript_RecycleBerriesAlliesEnd:
	restoretarget
	return

BattleScript_EffectSteelsurge::
	setsteelsurge BattleScript_MoveEnd
	printfromtable gDmgHazardsStringIds
	waitmessage B_WAIT_TIME_LONG
	return

@@@ END MAX MOVES @@@

BattleScript_DynamaxBegins::
	flushtextbox
	trytrainerslidedynamaxmsg
	jumpifcangigantamax BS_ATTACKER, BattleScript_DynamaxBegins_GigantamaxString_01
	printstring STRINGID_TIMETODYNAMAX
	waitmessage B_WAIT_TIME_MED
	goto BattleScript_DynamaxBegins_SwitchIn
BattleScript_DynamaxBegins_GigantamaxString_01:
	printstring STRINGID_TIMETOGIGANTAMAX
	waitmessage B_WAIT_TIME_MED
BattleScript_DynamaxBegins_SwitchIn:
	returnatktoball
	pause B_WAIT_TIME_SHORT
	returntoball BS_SCRIPTING, TRUE
	switchinanim BS_SCRIPTING, TRUE, TRUE
	updatedynamax
	playanimation BS_SCRIPTING, B_ANIM_DYNAMAX_GROWTH
	waitanimation
	jumpifbyteequal B_SHOW_DYNAMAX_MESSAGE, FALSE, BattleScript_DynamaxBegins_End3
	jumpifcangigantamax BS_ATTACKER, BattleScript_DynamaxBegins_GigantamaxString_02
	printstring STRINGID_PKMNDYNAMAXED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DynamaxBegins_End3
BattleScript_DynamaxBegins_GigantamaxString_02:
	printstring STRINGID_PKMNGIGANTAMAXED
	waitmessage B_WAIT_TIME_LONG
BattleScript_DynamaxBegins_End3:
	end3

BattleScript_DynamaxEnds::
	flushtextbox
	updatedynamax
	playanimation BS_SCRIPTING, B_ANIM_FORM_CHANGE
	waitanimation
	end2

BattleScript_DynamaxEnds_Ret::
	flushtextbox
	updatedynamax
	playanimation BS_SCRIPTING, B_ANIM_FORM_CHANGE
	waitanimation
	pause B_WAIT_TIME_SHORT
	return

BattleScript_MoveBlockedByDynamax::
	accuracycheck BattleScript_MoveMissedPause
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MOVEBLOCKEDBYDYNAMAX
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_PokemonCantUseTheMove::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_BUTPOKEMONCANTUSETHEMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_TargetAvoidsAttack::
	pause B_WAIT_TIME_SHORT
	printfromtable gMissStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_CouldntFullyProtect::
	printstring STRINGID_COULDNTFULLYPROTECT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BerserkGeneRet::
	statbuffchange BS_SCRIPTING, STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_ONLY_CHECKING, BattleScript_BerserkGeneRet_TryConfuse
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	statbuffchange BS_SCRIPTING, STAT_CHANGE_ALLOW_PTR, BattleScript_BerserkGeneRet_TryConfuse
	setbyte cMULTISTRING_CHOOSER, B_MSG_STAT_CHANGED_ITEM
	call BattleScript_StatUp
BattleScript_BerserkGeneRet_TryConfuse:
	jumpifability BS_SCRIPTING, ABILITY_OWN_TEMPO, BattleScript_BerserkGeneRet_OwnTempoPrevents
	jumpifsafeguard BattleScript_BerserkGeneRet_SafeguardProtected
	seteffectprimary BS_SCRIPTING, BS_SCRIPTING, MOVE_EFFECT_CONFUSION
	goto BattleScript_BerserkGeneRet_End
BattleScript_BerserkGeneRet_SafeguardProtected::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNUSEDSAFEGUARD
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_BerserkGeneRet_End
BattleScript_BerserkGeneRet_OwnTempoPrevents:
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUpScripting
	printstring STRINGID_PKMNPREVENTSCONFUSIONWITH
	waitmessage B_WAIT_TIME_LONG
BattleScript_BerserkGeneRet_End:
	removeitem BS_SCRIPTING
	return

BattleScript_BoosterEnergyRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	call BattleScript_AbilityPopUpScripting
	printstring STRINGID_BOOSTERENERGYACTIVATES
	waitmessage B_WAIT_TIME_MED
	printstring STRINGID_STATWASHEIGHTENED
	waitmessage B_WAIT_TIME_MED
	removeitem BS_SCRIPTING
	return

BattleScript_SleepClauseBlocked::
	pause B_WAIT_TIME_SHORT
	setmoveresultflags MOVE_RESULT_FAILED
	printstring STRINGID_BLOCKEDBYSLEEPCLAUSE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SleepClausePreventsEnd2::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_BLOCKEDBYSLEEPCLAUSE
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_QuestionForfeitBattle::
	printselectionstring STRINGID_QUESTIONFORFEITBATTLE
	forfeityesnobox
	endselectionscript

BattleScript_ForfeitBattleGaveMoney::
	getmoneyreward
.if B_WHITEOUT_MONEY >= GEN_4
	printstring STRINGID_PLAYERWHITEOUT2_TRAINER
.else
	printstring STRINGID_PLAYERWHITEOUT3
.endif
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_Attackstring::
	printattackstring
	return

BattleScript_SubmoveAttackstring::
	printattackstring
	pause B_WAIT_TIME_LONG
	attackanimation
	waitanimation
	setcalledmove
	return

BattleScript_SleepTalkAttackstring::
	printattackstring
	pause B_WAIT_TIME_LONG
	printstring STRINGID_PKMNFASTASLEEP
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	attackanimation
	waitanimation
	setcalledmove
	return

BattleScript_MetronomeAttackstring::
	printattackstring
	pause B_WAIT_TIME_LONG
	attackanimation
	waitanimation
	setcalledmove
	printstring STRINGID_WAGGLINGAFINGER
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_NaturePowerAttackstring::
	printattackstring
	pause B_WAIT_TIME_SHORT
	setcalledmove
	printstring STRINGID_NATUREPOWERTURNEDINTO
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SwapFromSubstitute::
	jumpifvolatile BS_SCRIPTING, VOLATILE_SUBSTITUTE, BattleScript_SwapFromSubstituteContinue
	goto BattleScript_SwapFromSubstituteReturn
BattleScript_SwapFromSubstituteContinue:
	playanimation BS_SCRIPTING, B_ANIM_SWAP_FROM_SUBSTITUTE
	waitanimation
BattleScript_SwapFromSubstituteReturn:
	return

BattleScript_SwapToSubstitute::
	jumpifvolatile BS_SCRIPTING, VOLATILE_SUBSTITUTE, BattleScript_SwapToSubstituteContinue
	goto BattleScript_SwapToSubstituteReturn
BattleScript_SwapToSubstituteContinue:
	playanimation BS_SCRIPTING, B_ANIM_SWAP_TO_SUBSTITUTE
	waitanimation
BattleScript_SwapToSubstituteReturn:
	return

BattleScript_TooScaredToMove::
	printstring STRINGID_MONTOOSCAREDTOMOVE
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_MON_SCARED
	goto BattleScript_MoveEnd

BattleScript_GhostGetOutGetOut::
	printstring STRINGID_GHOSTGETOUTGETOUT
	playanimation BS_ATTACKER, B_ANIM_GHOST_GET_OUT
	goto BattleScript_MoveEnd

BattleScript_SilphScopeUnveiled::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_SILPHSCOPEUNVEILED
	waitstate
	playanimation BS_OPPONENT1, B_ANIM_SILPH_SCOPED
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_GHOSTWASMAROWAK
	waitmessage B_WAIT_TIME_LONG
	end2
