#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"

static u8 GetCurrentBadgeCount(void)
{
    u16 i;
    u8 badgeCount = 0;
    for (i = FLAG_BADGE01_GET; i < FLAG_BADGE01_GET + NUM_BADGES; i++)
    {
        if (FlagGet(i))
            badgeCount++;
    }
    return badgeCount;
}

// Challenge level caps are indexed by completed Johto badges and protect the
// next leader's ace. Hard mode stays four levels below that ace.
static const u8 sLevelCapTable_Normal[] =
{
    [0] = 16, // Falkner
    [1] = 22, // Bugsy
    [2] = 27, // Whitney
    [3] = 33, // Morty
    [4] = 39, // Chuck
    [5] = 43, // Jasmine
    [6] = 38, // Pryce
    [7] = 52, // Clair
    [8] = 56, // Eight badges; preserved pre-League cap
};

static const u8 sLevelCapTable_Hard[] =
{
    [0] = 12, // Falkner
    [1] = 18, // Bugsy
    [2] = 23, // Whitney
    [3] = 29, // Morty
    [4] = 35, // Chuck
    [5] = 39, // Jasmine
    [6] = 34, // Pryce
    [7] = 48, // Clair
    [8] = 54, // Eight badges; preserved pre-League cap
};

// Post-league caps, matching HnS: beating the Johto Elite Four raises the cap to
// 70 for the Kanto half, and only beating the Kanto league removes it entirely.
#define KANTO_MAX_LEVEL 70

u32 GetCurrentLevelCap(void)
{
    static const u32 sLevelCapFlagMap[][2] =
    {
        {FLAG_BADGE01_GET, 15},
        {FLAG_BADGE02_GET, 19},
        {FLAG_BADGE03_GET, 24},
        {FLAG_BADGE04_GET, 29},
        {FLAG_BADGE05_GET, 31},
        {FLAG_BADGE06_GET, 33},
        {FLAG_BADGE07_GET, 42},
        {FLAG_BADGE08_GET, 46},
        {FLAG_IS_CHAMPION, 58},
    };

    u8 challengeLevelCap = gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap;

    if (challengeLevelCap != 0)
    {
        u8 badgeCount = GetCurrentBadgeCount();
        if (badgeCount > 8)
            badgeCount = 8;

#if IS_HNS
        if (FlagGet(FLAG_IS_KANTO_CHAMPION))
            return MAX_LEVEL;

        if (FlagGet(FLAG_IS_CHAMPION))
            return KANTO_MAX_LEVEL;
#else
        if (FlagGet(FLAG_IS_CHAMPION))
            return MAX_LEVEL;
#endif

        if (challengeLevelCap == 1)
            return sLevelCapTable_Normal[badgeCount];
        else
            return sLevelCapTable_Hard[badgeCount];
    }

    u32 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{
    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, MAX_TOTAL_EVS *  1 / 17},
        {FLAG_BADGE02_GET, MAX_TOTAL_EVS *  3 / 17},
        {FLAG_BADGE03_GET, MAX_TOTAL_EVS *  5 / 17},
        {FLAG_BADGE04_GET, MAX_TOTAL_EVS *  7 / 17},
        {FLAG_BADGE05_GET, MAX_TOTAL_EVS *  9 / 17},
        {FLAG_BADGE06_GET, MAX_TOTAL_EVS * 11 / 17},
        {FLAG_BADGE07_GET, MAX_TOTAL_EVS * 13 / 17},
        {FLAG_BADGE08_GET, MAX_TOTAL_EVS * 15 / 17},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}
