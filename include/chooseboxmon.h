#ifndef GUARD_CHOOSEBOXMON_H
#define GUARD_CHOOSEBOXMON_H

struct MoveLearnUI {
    void (*askConfirmation)(void);
    s32 (*waitConfirmation)(void);
    void (*printMessage)(const u8 *message);
    void (*playFanfare)(u32 songId);
    void (*showMoveList)(u8 taskId);
    void (*endTask)(u8 taskId);
};

u32 IsBoxMonExcluded(struct BoxPokemon *boxmon);
bool32 CanBoxMonBeSelected(struct BoxPokemon *boxmon);
s32 LearnMove(const struct MoveLearnUI *ui, u8 taskId);
s32 GetLearnMoveStartState(void);
s32 GetLearnMoveResumeAfterSummaryScreenState(void);
// Used by both the free Indigo tutor and Move Expert's tutor-move list.
bool32 CanSpeciesLearnPjrControlTutorMoveForRelearner(u16 species, u16 move);
// Shared compatibility gate for the free PRU Control and doubles tutors.
bool32 CanSpeciesLearnPruTutorMove(u16 species, u16 move);
// Stable move selection shared by Indigo's party, PC and learning screens.
u16 GetSelectedBoxTutorMove(void);

#endif // GUARD_CHOOSEBOXMON_H
