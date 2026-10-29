#ifndef GUARD_PRU_MEWSION_GATE_H
#define GUARD_PRU_MEWSION_GATE_H

#include <stdbool.h>

// Mewduo shares Mewtwo's National Dex number. Only its dedicated capture
// marker can reliably indicate that Mewduo itself was caught; old flags may
// be set in pre-existing saves even when Mewduo was never encountered.
static inline bool PruMewsionAllowed(bool mewCaught, bool mewtwoCaught,
                                     bool mewduoCaptured)
{
    return mewCaught && mewtwoCaught && !mewduoCaptured;
}

#endif // GUARD_PRU_MEWSION_GATE_H
