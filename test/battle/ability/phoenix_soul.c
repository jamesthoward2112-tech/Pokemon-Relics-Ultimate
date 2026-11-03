#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Phoenix Soul survives a lethal damaging hit and heals one quarter HP")
{
    GIVEN {
        PLAYER(SPECIES_HO_OH) { Ability(ABILITY_PHOENIX_SOUL); MaxHP(100); HP(30); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SEISMIC_TOSS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SEISMIC_TOSS, opponent);
        HP_BAR(player, hp: 1);
        ABILITY_POPUP(player, ABILITY_PHOENIX_SOUL);
        MESSAGE("Ho-Oh endured the hit using Phoenix Soul!");
    } THEN {
        EXPECT_EQ(player->hp, 26);
    }
}

SINGLE_BATTLE_TEST("Phoenix Soul remains spent after switching out")
{
    GIVEN {
        PLAYER(SPECIES_HO_OH) { Ability(ABILITY_PHOENIX_SOUL); MaxHP(100); HP(30); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SEISMIC_TOSS); }
        TURN { SWITCH(player, 1); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { SWITCH(player, 0); MOVE(opponent, MOVE_DRAGON_RAGE); }
    } THEN {
        EXPECT_EQ(player->hp, 0);
        EXPECT_EQ(gBattleStruct->pjrPhoenixSoulUsed[B_POSITION_PLAYER_LEFT], TRUE);
    }
}

SINGLE_BATTLE_TEST("Phoenix Soul activates at 1 HP only once during a multi-hit attack")
{
    GIVEN {
        PLAYER(SPECIES_RELIC_HO_OH) { MaxHP(100); HP(1); }
        OPPONENT(SPECIES_MELMETAL);
    } WHEN {
        TURN { MOVE(opponent, MOVE_DOUBLE_IRON_BASH); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_PHOENIX_SOUL);
    } THEN {
        EXPECT_EQ(player->hp, 0);
    }
}

