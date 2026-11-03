#include "global.h"
#include "item_ball.h"
#include "event_data.h"
#include "constants/event_objects.h"
#include "constants/items.h"

#if IS_HNS
#include "constants/flags.h"

// Former Rope loot keeps its map object and pickup flag, but awards one TM
// chosen from the current 16-badge Johto/Kanto progression.
enum Item GetPruEscapeRopePickupTm(void)
{
    u16 badgeFlag;
    u8 badges = 0;

    for (badgeFlag = FLAG_BADGE01_GET; badgeFlag < FLAG_BADGE01_GET + NUM_BADGES; badgeFlag++)
    {
        if (FlagGet(badgeFlag))
            badges++;
    }

    if (badges <= 1)
        return ITEM_TM_BULLET_SEED;
    if (badges <= 3)
        return ITEM_TM_ROCK_TOMB;
    if (badges <= 5)
        return ITEM_TM_BRICK_BREAK;
    if (badges <= 7)
        return ITEM_TM_SHADOW_BALL;
    if (badges <= 11)
        return ITEM_TM_ROOST;
    if (badges <= 14)
        return ITEM_TM_ROCK_SLIDE;
    return ITEM_TM_EARTHQUAKE;
}
#endif

static u32 GetItemBallAmountFromTemplate(u32);
static u32 GetItemBallIdFromTemplate(u32);

static u32 GetItemBallAmountFromTemplate(u32 itemBallId)
{
    u32 amount = gMapHeader.events->objectEvents[itemBallId].movementRangeX;

    if (amount > MAX_BAG_ITEM_CAPACITY)
        return MAX_BAG_ITEM_CAPACITY;

    return (amount == 0) ? 1 : amount;
}

static u32 GetItemBallIdFromTemplate(u32 itemBallId)
{
    enum Item itemId = gMapHeader.events->objectEvents[itemBallId].trainerRange_berryTreeId;

#if IS_HNS
    if (itemId == ITEM_ESCAPE_ROPE)
        return GetPruEscapeRopePickupTm();
#endif
    return (itemId >= ITEMS_COUNT) ? (ITEM_NONE + 1) : itemId;
}

void GetItemBallIdAndAmountFromTemplate(void)
{
    u32 itemBallId = (gSpecialVar_LastTalked - 1);
    gSpecialVar_Result = GetItemBallIdFromTemplate(itemBallId);
    gSpecialVar_0x8009 = GetItemBallAmountFromTemplate(itemBallId);
#if IS_HNS
    if (gMapHeader.events->objectEvents[itemBallId].trainerRange_berryTreeId == ITEM_ESCAPE_ROPE)
        gSpecialVar_0x8009 = 1;
#endif
}
