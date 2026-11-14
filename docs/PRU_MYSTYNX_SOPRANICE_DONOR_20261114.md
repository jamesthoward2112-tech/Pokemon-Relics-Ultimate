# Mystynx: Elite Redux Sopranice complete sprite donor

Source: https://github.com/Elite-Redux/eliteredux-source/tree/upcoming/graphics/pokemon/sopranice

This is a **visuals-only** change to existing `SPECIES_MYSTYNX`.
Keep Mystynx's Ice/Fairy typing, name, stats, moves, abilities, evolution,
Pokédex order, story, and save-file compatibility as they are in Alpha 5.

The original Elite Redux files are copied byte-for-byte into
`graphics/pokemon/prl_authoritative/mystynx/`:

| File | Original Git SHA | Format |
| --- | --- | --- |
| `front.png` | `83e035b442ecb41e6ff4fba46acbb163846df95e` | 64×64 indexed 4bpp |
| `back.png` | `be41ae2ce7704ef2b6f7584da95d90cba026c3a9` | 64×64 indexed 4bpp |
| `icon.png` | `566b40c99e5e0c17183d88be9ac780e9f98d20d4` | 32×64 two-frame icon |
| `normal.pal` | `40af179c158809110c034b8a552aaa5a5428cbc8` | Original normal palette |
| `shiny.pal` | `4ec6f0ca00932cb1a5db01976a018247f19842c7` | Original shiny palette |

The original icon PNG is indexed *exactly* to PRU's existing shared
`graphics/pokemon/icon_palettes/pal3.pal`, so Mystynx's
`.iconPalIndex` must change from `2` to `3`.

The pre-build sprite-repair routine must validate, not repaint, these donor
files. The pinned PRL art importer must keep Mystynx on its exception list.
Do not apply this fix to old `main`: the new branch is based on the
confirmed Alpha 5 sequence, including later Eeveelution moveset corrections.

**Remaining verification:** Build the ROM and test normal/shiny front and
back in battles; both icon frames and colours on party, PC and summary screens;
check back-sprite placement and ensure no other Pokémon sprites regress.
