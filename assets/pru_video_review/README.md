# Video review sprite inputs

These are pinned inputs for the repair stage based on the user's PC-storage review video.

- `icons/` contains all 37 selected icon images after the complete approved sprite-install pipeline, before the one-time 20% size adjustment. It preserves existing palette mappings, including corrected Ho-Oh, Mewsion, Tropisaur, Torkaldera, Coelossus, Heracurion, Fortotoise, and Charaxis icons.
- `gemlin/`, `jollibird/`, `kablowfish/`, and `grimfowl/` are the approved indexed PRL front/back donor art and normal palette captured at the #548 starting point. The installer only changes framing and nearest-neighbour size. Gemlin's separate authentic back sprite is flipped horizontally for the player-side direction; the front is never used as its back.
- No AI-generated pixel art or invented palette colours are used.
- The video-selected custom icons above 25 pixels are reduced by 20% with nearest-neighbour sampling. Canonical shared Alakazam and Hitmonlee icons stay unchanged. Nolax is intentionally excluded.

The source snapshots are regression pins. If an upstream installer changes one, update and review the pin explicitly before the video repair step can pass.
