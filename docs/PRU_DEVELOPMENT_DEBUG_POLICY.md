# PRU development debug policy — effective 6 November 2026

**Creator decision:** Keep the overworld debug menu enabled for all foreseeable development and playtest ROMs. Do **not** switch it off until the creator requests the **Master Alpha** ROM.

## Current development builds

- In `include/config/debug.h`, `DEBUG_OVERWORLD_MENU` is `DISABLED_ON_RELEASE`: this expands to `TRUE` for ordinary `make hns` development builds and `FALSE` when compiled with `RELEASE=1`.
- Open debug in the overworld by **holding R and pressing START**. The standard Start menu remains unchanged.
- Battle debug (SELECT in battle), the AI delay display and the Pokémon summary sprite visualizer remain disabled; this request enables the normal overworld debug menu, not unrelated battle/summary shortcuts.
- Do not turn off debug in subsequent job branches, CI changes, test ROM builds or source integrations. Carry this configuration and `test/test_pru_development_debug.py` forward when branching.
- Debug changes are compilation-only: existing game content and save data must stay intact.

## Master Alpha gate (not yet authorised)

When the creator explicitly asks to prepare **Master Alpha**, change `DEBUG_OVERWORLD_MENU` to `FALSE`, verify the master source and all published GBA binaries have **no functional debug access**, and run the complete regression, gameplay and emulator checks. A separate `make hns RELEASE=1` build also disables debug by design, but **do not** treat that alone as evidence that Master Alpha has been approved.

This instruction supersedes the previous request to keep debug disabled during the interim PRU development period.
