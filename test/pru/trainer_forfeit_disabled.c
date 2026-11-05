#include "global.h"
#include "battle.h"
#include "battle_main.h"
#include "test/battle.h"
#include "constants/battle.h"

// Do not set the battle outcome or manipulate a live player save: this test
// checks the actual PRU forfeit decision for each encounter category.
TEST("PRU normal trainer battles cannot be forfeited")
{
    u32 oldFlags = gBattleTypeFlags;

    if (IS_HNS)
    {
        gBattleTypeFlags = BATTLE_TYPE_TRAINER;
        EXPECT(!CanPlayerForfeitNormalTrainerBattle());
        EXPECT(!DidPlayerForfeitNormalTrainerBattle());

        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE;
        EXPECT(!CanPlayerForfeitNormalTrainerBattle());
    }

    gBattleTypeFlags = oldFlags;
}

TEST("PRU Frontier and Trainer Hill trainer battles cannot be forfeited")
{
    u32 oldFlags = gBattleTypeFlags;

    if (IS_HNS)
    {
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_FRONTIER;
        EXPECT(!CanPlayerForfeitNormalTrainerBattle());

        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_TRAINER_HILL;
        EXPECT(!CanPlayerForfeitNormalTrainerBattle());
    }

    gBattleTypeFlags = oldFlags;
}

TEST("PRU wild battles are not classified as forfeit-enabled trainer battles")
{
    u32 oldFlags = gBattleTypeFlags;

    gBattleTypeFlags = 0;
    EXPECT(!CanPlayerForfeitNormalTrainerBattle());

    gBattleTypeFlags = oldFlags;
}
