#include "global.h"
#include "event_data.h"
#include "caps.h"
#include "nuzlocke.h"
#include "test/battle.h"

static const u8 sExpectedNormalCaps[8] = {16, 22, 27, 33, 39, 43, 38, 52};
static const u8 sExpectedHardCaps[8] = {12, 18, 23, 29, 35, 39, 34, 48};

TEST("PRU Normal and Hard level caps follow the Johto badge count")
{
    bool8 savedBadges[NUM_BADGES];
    bool8 savedChampion = FlagGet(FLAG_IS_CHAMPION);
    bool8 savedKantoChampion = FlagGet(FLAG_IS_KANTO_CHAMPION);
    u8 savedLevelCap = gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap;
    u8 i, completedBadges;

    if (!IS_HNS)
        return;

    for (i = 0; i < NUM_BADGES; i++)
    {
        savedBadges[i] = FlagGet(FLAG_BADGE01_GET + i);
        FlagClear(FLAG_BADGE01_GET + i);
    }
    FlagClear(FLAG_IS_CHAMPION);
    FlagClear(FLAG_IS_KANTO_CHAMPION);

    for (completedBadges = 0; completedBadges < ARRAY_COUNT(sExpectedNormalCaps); completedBadges++)
    {
        for (i = 0; i < completedBadges; i++)
            FlagSet(FLAG_BADGE01_GET + i);

        gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap = 1;
        EXPECT_EQ(GetCurrentLevelCap(), sExpectedNormalCaps[completedBadges]);
        gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap = 2;
        EXPECT_EQ(GetCurrentLevelCap(), sExpectedHardCaps[completedBadges]);

        for (i = 0; i < completedBadges; i++)
            FlagClear(FLAG_BADGE01_GET + i);
    }

    for (i = 0; i < NUM_BADGES; i++)
    {
        if (savedBadges[i])
            FlagSet(FLAG_BADGE01_GET + i);
        else
            FlagClear(FLAG_BADGE01_GET + i);
    }
    if (savedChampion)
        FlagSet(FLAG_IS_CHAMPION);
    else
        FlagClear(FLAG_IS_CHAMPION);
    if (savedKantoChampion)
        FlagSet(FLAG_IS_KANTO_CHAMPION);
    else
        FlagClear(FLAG_IS_KANTO_CHAMPION);
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap = savedLevelCap;
}

TEST("PRU Nuzlocke state remains independent of Normal and Hard level caps")
{
    bool8 savedPokemonGet = FlagGet(FLAG_SYS_POKEMON_GET);
    bool8 savedStartNuzlocke = FlagGet(FLAG_START_NUZLOCKE);
    bool8 savedEndNuzlocke = FlagGet(FLAG_END_NUZLOCKE);
    bool8 savedBadges[NUM_BADGES];
    bool8 savedChampion = FlagGet(FLAG_IS_CHAMPION);
    bool8 savedKantoChampion = FlagGet(FLAG_IS_KANTO_CHAMPION);
    u8 savedNuzlocke = gSaveBlock3Ptr->challengeSettings.tx_Challenges_Nuzlocke;
    u8 savedLevelCap = gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap;
    u8 i;

    if (!IS_HNS)
        return;

    for (i = 0; i < NUM_BADGES; i++)
    {
        savedBadges[i] = FlagGet(FLAG_BADGE01_GET + i);
        FlagClear(FLAG_BADGE01_GET + i);
    }
    FlagClear(FLAG_IS_CHAMPION);
    FlagClear(FLAG_IS_KANTO_CHAMPION);
    FlagSet(FLAG_SYS_POKEMON_GET);
    FlagSet(FLAG_START_NUZLOCKE);
    FlagClear(FLAG_END_NUZLOCKE);
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_Nuzlocke = 1;
    EXPECT(IsNuzlockeActive());

    gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap = 1;
    EXPECT(IsNuzlockeActive());
    EXPECT_EQ(GetCurrentLevelCap(), 16);
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap = 2;
    EXPECT(IsNuzlockeActive());
    EXPECT_EQ(GetCurrentLevelCap(), 12);

    FlagSet(FLAG_END_NUZLOCKE);
    EXPECT(!IsNuzlockeActive());
    FlagClear(FLAG_END_NUZLOCKE);
    FlagClear(FLAG_START_NUZLOCKE);
    EXPECT(!IsNuzlockeActive());

    if (savedPokemonGet)
        FlagSet(FLAG_SYS_POKEMON_GET);
    else
        FlagClear(FLAG_SYS_POKEMON_GET);
    if (savedStartNuzlocke)
        FlagSet(FLAG_START_NUZLOCKE);
    else
        FlagClear(FLAG_START_NUZLOCKE);
    if (savedEndNuzlocke)
        FlagSet(FLAG_END_NUZLOCKE);
    else
        FlagClear(FLAG_END_NUZLOCKE);
    for (i = 0; i < NUM_BADGES; i++)
    {
        if (savedBadges[i])
            FlagSet(FLAG_BADGE01_GET + i);
        else
            FlagClear(FLAG_BADGE01_GET + i);
    }
    if (savedChampion)
        FlagSet(FLAG_IS_CHAMPION);
    else
        FlagClear(FLAG_IS_CHAMPION);
    if (savedKantoChampion)
        FlagSet(FLAG_IS_KANTO_CHAMPION);
    else
        FlagClear(FLAG_IS_KANTO_CHAMPION);
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_Nuzlocke = savedNuzlocke;
    gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap = savedLevelCap;
}
