#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveType(MOVE_GOLDEN_REIGN) == TYPE_FIRE);
    ASSUME(GetMoveCategory(MOVE_GOLDEN_REIGN) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_GOLDEN_REIGN, MOVE_EFFECT_BURN, 20));
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_GOLDEN_REIGN, MOVE_EFFECT_SUN, 100));
}

DOUBLE_BATTLE_TEST("Golden Reign damages both foes, sets sun, and uses Make It Rain animation")
{
    GIVEN {
        PLAYER(SPECIES_RELIC_HO_OH);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_GOLDEN_REIGN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GOLDEN_REIGN, playerLeft);
        HP_BAR(opponentLeft);
        HP_BAR(opponentRight);
    } THEN {
        EXPECT(gBattleWeather & B_WEATHER_SUN);
        EXPECT_LT(opponentLeft->hp, opponentLeft->maxHP);
        EXPECT_LT(opponentRight->hp, opponentRight->maxHP);
    }
}

SINGLE_BATTLE_TEST("Golden Reign works against one target and does not inherit Make It Rain penalties")
{
    GIVEN {
        PLAYER(SPECIES_RELIC_HO_OH);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_GOLDEN_REIGN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GOLDEN_REIGN, player);
        HP_BAR(opponent);
        NONE_OF {
            MESSAGE("Coins were scattered everywhere!");
            MESSAGE("Relic Ho-Oh's Sp. Atk fell!");
        }
    }
}

