#ifndef GUARD_PRU_MEWDUO_CAUGHT_ICON_H
#define GUARD_PRU_MEWDUO_CAUGHT_ICON_H

#include <stdbool.h>

// Mewduo uses Mewtwo's National Dex number, which is already caught before
// this encounter unlocks. Its ball indicator must use its own capture marker.
static inline bool PruHasCaughtSpeciesForBattleIcon(bool isMewduo,
                                                     bool nationalDexCaught,
                                                     bool mewduoCaught)
{
    return isMewduo ? mewduoCaught : nationalDexCaught;
}

#endif // GUARD_PRU_MEWDUO_CAUGHT_ICON_H
