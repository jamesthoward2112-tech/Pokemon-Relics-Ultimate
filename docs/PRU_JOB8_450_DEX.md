# PRU Job 8 — 450-species in-game Pokédex

Source baseline: Job 7 / `013f29cfc8`. No species IDs, save block sizes, story variables, or progression scripts are changed.

## In-game behavior

- The HGSS-style Pokédex opens in PRU National mode, regardless of the old National unlock. Numeric ordering follows `src/data/pokemon/pru_dex_order.h`, exactly 450 unique species grouped by families.
- List numbers and information-screen numbers use the PRU index. Internal list references remain National-style persisted bit slots so sprites, cries, forms, evolutions, area pages and search work without a new display ID encoding.
- Alphabetical, size, and weight searches sort/filter the actual PRU roster. Unseen entries stay hidden until the usual Seen flag; caught-only sorts respect Caught flags.
- Official species retain their existing National seen/caught slots. The 55 standalone custom species get reserved slots in previously unused Gen-5 National IDs 495–549. This does not resize the 128 KiB save file or renumber species.
- On opening the Pokédex, the game scans an existing party and PC boxes and credits custom species physically owned in an older save to their new independent Seen/Caught slots. The scanner does not guess whether custom Pokémon that were previously released had been seen/caught; their legacy flag was shared with a base species, so that data cannot be safely disambiguated.

## QA

- `python3 tools/pru/check_job8_pokedex.py`: static roster and save-layout audit.
- `make -j2 check BUILD=hns TESTS=test/pru/pokedex_450.c`: compiled all-450 uniqueness and roundtrip test.
- Full `make hns` release and mGBA boot via the standard CI workflow.

Existing saves should be kept backed up. No save-file conversion or new-save requirement is introduced.
