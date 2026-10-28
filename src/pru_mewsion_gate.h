#ifndef GUARD_PRU_MEWSION_GATE_H
#define GUARD_PRU_MEWSION_GATE_H

#include <stdbool.h>

// The approved encounter checks four independent save states. In particular,
// "caught Mewsion" cannot use its inherited Mewtwo National Dex number.
static inline bool PruMewsionAllowed(bool mewCaught, bool mewtwoCaught,
                                     bool returnedToCave, bool mewsionCaught)
{
    return mewCaught && mewtwoCaught && returnedToCave && !mewsionCaught;
}

#endif // GUARD_PRU_MEWSION_GATE_H
