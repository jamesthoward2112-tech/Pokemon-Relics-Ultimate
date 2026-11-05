# Video review sprite inputs

These are pinned visual reference assets captured for the user's PC-storage review video.

- `icons/` contains the reviewed 37 selected icon references from the approved #548 tree. During CI the size adjustment is applied to the live icon assets after all normal installers have run, so newer pipeline outputs are never replaced by these reference copies.
- `gemlin/`, `jollibird/`, `kablowfish/`, and `grimfowl/` are the approved indexed PRL front/back donor art and normal palette captured at the #548 starting point. The installer only changes framing and nearest-neighbour size. Gemlin's separate authentic back sprite is flipped horizontally for the player-side direction; the front is never used as its back.
- No AI-generated pixel art or invented palette colours are used.
- The video-selected custom icons above 25 pixels are reduced by 20% with nearest-neighbour sampling. Canonical shared Alakazam and Hitmonlee icons stay unchanged. Nolax is intentionally excluded.

Adnokana and Cheauking had mismatched RGBA orb icons; their replacement icons are built from the approved front art and quantized to shared GBA palette #2. Their species records use that palette. The icon snapshots are visual references, not byte-for-byte constraints on post-install assets. Technical checks validate frame dimensions, indexed colour range, transparency, and output framing; a human must review the generated contact sheet and compiled ROM.
