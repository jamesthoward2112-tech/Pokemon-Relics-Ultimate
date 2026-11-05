# Video review sprite inputs

These are pinned visual reference assets captured for the user's PC-storage review video.

- `icons/` contains the reviewed 37 selected icon references from the approved #548 tree. During CI the size adjustment is applied to the live icon assets after all normal installers have run, so newer pipeline outputs are never replaced by these reference copies.
- `gemlin/` retains its approved indexed donor art. Its separate authentic back sprite is flipped horizontally for the player-side direction; the front is never used as its back.
- `gemigoyle/`, `jollibird/`, `kablowfish/`, and `grimfowl/` contain the player's approved alternate front/back poses. They are fixed 64x64 indexed PNGs with transparent index 0 and use each species' existing 16-entry normal palette. Back sprites leave rows 51–63 transparent. The installer copies these bytes and restores the matching normal palette after pinned donor imports, so older sprite installers cannot replace them.
- No new palette colours or unrelated Pokémon artwork are introduced by these replacements.
- The video-selected custom icons above 25 pixels are reduced by 20% with nearest-neighbour sampling. Canonical shared Alakazam and Hitmonlee icons stay unchanged. Nolax is intentionally excluded.

Adnokana and Cheauking had mismatched RGBA orb icons; their replacement icons are built from the approved front art and quantized to shared GBA palette #2. Their species records use that palette. The icon snapshots are visual references, not byte-for-byte constraints on post-install assets. Technical checks validate frame dimensions, indexed colour range, transparency, palette selection, and the exact approved battle-art bytes; a human must review the generated contact sheet and compiled ROM.
