# PRU Alpha ending audit — before flying Golden Ho-Oh artwork

**Scope:** preparation from PR75 source head `ee552f0d` on 7 November 2026. This is development source only; the already-published v0.1.0 alpha ROM is **not automatically updated** by source commits.

## Findings in the current alpha

1. The post-Golden Ho-Oh introduction in `src/credits_hns.c` still showed "THE SIX RELICS STIR", named six of the seven RELICS, and said "ALPHORACLE AWAITS". These are stale because this credits sequence follows the Golden Ho-Oh catch at Mt. Silver, after the seven RELICS are complete.
2. The final attribution page in `src/data/credits_pru.h` said "THE SIX RELICS AWAKEN" and "GOLDEN HO-OH AWAITS". It is the ending, not a teaser.
3. The `SPECIES_HO_OH` national Pokédex entry displayed the inherited generic Rainbow biography, even though PRU uses the Golden Ho-Oh artwork. `SPECIES_RELIC_HO_OH` had a separate shorter ancient-Relic bio. Keep both descriptions consistent with the sole Oak/Mt Silver encounter.
4. The credits flight uses `gMonFrontPic_HoOhRelic` as a **single frame** through `gSpriteSheet_CreditsRelicHoOh` (size `0x800`) and `sAnim_CreditsRelicHoOh`, while `SpriteCB_CreditsRelicHoOh` moves the static sprite left with slight sine bobbing. This is why it appears to be a sliding front-battle sprite, not a bird flying.

## Source text changes prepared on this branch

- Keep four intro pages, 19 PRU-specific attribution pages and the original Johto/Kanto League credits.
- Replace future-tense RELICS/Alphoracle captions with a completed-story tribute to Oak, Mt Silver and Golden Ho-Oh.
- Update the final acknowledgements page to "THE GOLDEN FLAME ENDURES", "MT SILVER REMEMBERS" and "YOUR LEGEND LIVES ON".
- The National Ho-Oh and distinct Relic Ho-Oh forms now share the Pokédex category **Relic** and the same new four-line biography:

  > At Mt. Silver, Professor Oak  
  > summoned this ancient golden Ho-Oh.  
  > Its radiant wings carry a sacred  
  > flame that promises rebirth.

- Preserve all E20 reward logic, encounter flags, existing captures, Pokémon IDs, abilities, base stats, sprites, saves and all other story scripts.
- Run `python3 test/test_pru_alpha_ending_text.py` and existing Job16/17 checks; a clean native ROM compile and emulator visual QA are still **required** before declaring the replacement ROM ready.

## Dedicated flying Golden Ho-Oh — three-frame artwork integrated

**Art direction supplied and approved by user on 7 November 2026.** Three flying poses were converted into the shared GBA indexed graphic `graphics/intro/scene_2/relic_ho_oh_flight.png` (64×192, 3 × 64×64, 16 colours with transparency).

Candidate asset specification, subject to resource selection:

- Dedicated airborne Golden Ho-Oh, **not** an existing front battle sprite and **not** a replacement for its battle sprite or Pokédex art.
- A small GBA-ready animated sheet: ideally 3–4 frames of wing movement, sprite frames no larger than 64×64, shared GBA 4bpp palette (16 total colours including transparent entry), clean transparent edges.
- Preserve Golden Ho-Oh's approved colours, head, wing details and flame accents. Decide flight orientation from the final supplied reference and existing leftward on-screen movement.
- Implemented separate credits-only `gSpriteSheet_CreditsRelicHoOh` with an uncompressed target size of `0x1800` bytes and dedicated palette. Its animation runs `ANIMCMD_FRAME(0, 10)` → `(64, 10)` → `(128, 12)` → `(64, 10)` and jumps to the beginning.
- Preserve existing credit sequencing, base scenery, flyby lifetime, audio, save flags and one-only Ho-Oh encounter.
- QA in mGBA/Pizza Boy A for scale, frame pacing, flying direction, VRAM/tile allocation, palettes, no clipping, and progress into the following credits pages.

## Outstanding release gates (not fixed by text work)

- Native GitHub compile currently blocked by expired Hoenn's Last Wish scene-0 archive. The current alpha is an integrity-verified binary-patched ROM, not a fresh build from these changes.
- Story full playthrough, RELICS/Guardian/Ho-Oh event-flag QA, sprite acceptance, challenge mode, stable saves.
- Public RelicDex still contains an older 444-entry list and must be synced to the in-game 450 before beta.
- Sprite/artwork donor rights and detailed attribution should be reviewed before public distribution.

**Status (7 Nov 2026):** revised text and both Golden Ho-Oh bios committed, and all three selected flying designs converted and integrated into credits-only graphics source. `test/test_pru_alpha_ending_text.py`, `test/test_pru_job16_cinematic.py`, and `test/test_pru_job17_custom_credits.py` passed. A separate integrity-verified 32 MiB flight-animation test ROM was also made by patching only the credits palette, sprite sheet and animation pointers of the existing alpha and published as a GitHub prerelease. Because the expired Hoenn's Last Wish donor archive still blocks the native source build, that test ROM does **not** yet contain the newer credits text or Dex bios; full in-emulator visual acceptance remains pending. Tracked as GitHub Issue #79.


### Flight-only playable test (binary-patched, not a full source compilation)

- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-v0.1.0-alpha-hooh-flight-test-20261107
- File: `Pru_Flight_Test.gba`; SHA-256 `00ca2fa93c1f804c47a0e43d0109134ec0dc2f6da3a697ab38072d34d27fb3d6`; 33,554,432 bytes.
- Base: published PRU v0.1.0 Alpha, SHA-256 `c171c0e49d4f3edc084a9c7cee6d9d765a98fc645af304fd7741044a69cc8bfa`.
- Exactly 6,966 bytes differ, all confined to the three-frame sprite resources in unused ROM padding, animation pointers, the credits graphics descriptor and palette descriptor. Original battle/Pokédex art and save data unchanged.
- New graphics resource: 6,144 bytes GBA 4bpp packed; 6,916 bytes valid literal LZ77 stream; 32-byte 16-colour GBA palette; 20-byte 0→64→128→64 frame-command loop. ROM header unchanged and independently verified.
- **Must still** verify in an emulator that wing cycling, VRAM, colours, sprite direction and timing look right. Do not treat checksums alone as emulator approval.
