#ifndef GUARD_ITEM_BALL_H
#define GUARD_ITEM_BALL_H

#include "constants/items.h"

void GetItemBallIdAndAmountFromTemplate(void);

// Shared PRU conversion for both visible and hidden former Rope pickups.
#if IS_HNS
enum Item GetPruEscapeRopePickupTm(void);
#endif

#endif //GUARD_ITEM_BALL_H
