## 3 November 2026 — Job 4A Escape Rope pickups corrected to Max Revives (ROM built; Alph ladder mGBA-tested)

- **Branch / source commit:** `feat/pru-relic-hunt-20261101`; `0f1023351de364c8f6e37330ed1d5888289f27bd`.
- **ROM:** [Pokemon-Relics-Ultimate-0f1023351d.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-0f1023351d/Pokemon-Relics-Ultimate-0f1023351d.gba), 33,554,432 bytes (32 MiB), SHA-256 `5ab52fe8ae7452a2f57b5674bfd22c376a388bfad61978740b89f166cde0dbc7`.
- **Coded:** All former visible, hidden, and four scripted HNS Escape Rope field pickups now yield exactly one `ITEM_MAX_REVIVE`; removed the badge-tier helper and declaration. Preserved the reusable Escape Rope Key Item, Elm grant/recovery, False Swipe shops, original item event labels/flags/locations/graphics and TM settings. Sprout Tower rival dialogue is unchanged. No non-HNS changes.
- **Source regressions PASS:** focused Job 4A test; Jobs 1, 2, 3, 3A, 3B and 3C regressions; donor-parity test; `git diff --check`.
- **Build and emulator PASS:** GitHub Actions run [41622893273](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41622893273) clean production build, ROM verification, and blocking mGBA Alph B1F exit traversal. The ladder test verifies the existing ladder, not the new pickup reward.
- **Gameplay not tested:** collecting a converted Max Revive pickup in mGBA was not exercised. False Swipe / Key Item behavior is preserved and covered by source regressions, not new gameplay interactions.
- **Exact next action:** in-game, collect one former Escape Rope pickup and confirm the Bag receives exactly one Max Revive; retain this ROM as the latest tested fallback.
- **Notion:** Job 4A final release/testing entry required; source milestone comment `40d4939d-4316-813a-87e2-001d3bc0730b` exists.

## 3 November 2026 — Job 4 False Swipe and Escape Rope (ROM built; ladder mGBA-tested; feature gameplay pending)

- **Branch / source commit:** `feat/pru-relic-hunt-20261101`; `0d51e263260c4a28e6de77e8389bb5563a231b7d`. Final documentation checkpoint follows this source commit.
- **ROM:** [Pokemon-Relics-Ultimate-0d51e26326.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-0d51e26326/Pokemon-Relics-Ultimate-0d51e26326.gba), 33,554,432 bytes (32 MiB), SHA-256 `389de16f35499cdcd4cbd73efba03e762981eb53f8340ebc3c4eb4dc6faeb7a7`. Release: [pru-build-0d51e26326](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-0d51e26326). Includes Jobs 1–3C; prior Job 3C release remains available.
- **Coded:** TM54 False Swipe remains item 635 at ¥3,000 and is in both Cherrygrove stock phases, Goldenrod 5F and Celadon 3F. Escape Rope remains reusable Key Item 120; Elm grants it after the first Poké Ball progression and recovers it for eligible older saves. Visible and hidden former Rope pickups award exactly one badge-tier TM. Mt Mortar, Whirl Islands, Sprout Tower and Tin Tower static rewards were converted. Goldenrod 2F and all 18 HNS badge/PC stock tables no longer sell Escape Rope. Original pickup flags, locations and graphics are retained.
- **Source tests:** PASS: focused Job 4 regression, Job 1 Dark Void, Job 2 Mystery Egg, Job 3 Rock Shop, Job 3A Expert, Job 3B Sylveon/450 Dex, Job 3C Ruins donor parity, and `git diff --check`. Actions run [41618331917](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41618331917) passed all source regressions and clean build.
- **Binary / emulator:** PASS: exact 33,554,432-byte build and ROM verification. The blocking mGBA probe passed outside → B1F → outside → B1F ladder traversal on this build. Alph puzzle-room exits remain source-checked but not individually traversed. False Swipe purchases/teaching and Escape Rope grant/use/converted pickups were **not gameplay-tested** in mGBA or by the player.
- **Exact next action:** player-test TM54 purchase/teaching, Elm grant and older-save recovery, cave escape/reuse, and a visible plus hidden converted pickup in Pizza Boy; report any issue against source commit `0d51e263`.
- **Notion:** source and final build checkpoints recorded in the PRU Development Journal.

## 2026-11-03 Job 3C original H&S Alph B1F ladder (ROM built; ladder emulator tested)
Source: `7cb61e567f6ff33dd767836b76eedaf1ae1d3f56`; branch `feat/pru-relic-hunt-20261101`. Restored the five original B1F warps and ladder tile/attributes; removed the extra warp/script and installer mutations. Focused regressions and full CI build passed in Actions run [41612553467](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41612553467). Blocking mGBA EWRAM probe verified real outside (21,22) → B1F (15,16) → outside (21,21) → B1F (15,16) key-driven transitions. ROM: [Pokemon-Relics-Ultimate-7cb61e567f.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-7cb61e567f/Pokemon-Relics-Ultimate-7cb61e567f.gba), 33,554,432 bytes, SHA256 `fc12476b1190a18d368358f13d1cb973e7d1e71ef83abdd8512d445f3de9182b`. Puzzle-room reciprocal warp source checks passed, but the four puzzle routes were not each walked in mGBA. Keep Job 3B ROM as older fallback; no player gameplay test claimed. Next action if needed: mGBA-play the four puzzle return routes.

# PRU_HANDOFF.md — authoritative session handover
Last audited: 2026-11-01. All statuses below are scoped to evidence; no newer gameplay is implied.

## 2026-11-01 Correct B1F ladder exit trigger (compiled and released)
Branch: `feat/pru-relic-hunt-20261101`; source commit: `6e28dde2a5ba48420db1091c3fcc03c704e6ccd9`.
Player video showed the avatar at the visible ladder while the earlier extra warp was several tiles away. Moved the additional exit to the ladder tile (15,15) and added an A-button facing interaction that warps to the established Ruins of Alph Outside entrance (21,21). The standard B1F entrance/exit at (15,16) remains. Eye statue and pedestal are unchanged.
Actions run [41341671168](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41341671168) passed regression checks, full clean build and 32 MiB ROM verification. SHA256: `c3c63384493e60b896c8ad60c5e4e0d9307257d0590fc14ef950548bfa96b26c`.
Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-6e28dde2a5/Pokemon-Relics-Ultimate-6e28dde2a5.gba
Gameplay was not emulator-tested; player confirmation remains outstanding.

## 2026-11-01 B1F ladder exit and I-Unown Eye pedestal (compiled and released)
Branch: `feat/pru-relic-hunt-20261101`; source commit: `bcbde6cf9b03aa7e8cea3d14dc1c6a4683150c99`.
Added an exit warp on the visible B1F ladder at (12,10), leading to the established outside entrance; the original south exit remains. Rebuilt the Eye statue from its approved source artwork so its 16x12 inscribed base matches the Alphoracle stand while keeping the existing 32x32 object frame and independent cool-grey palette. Alphoracle artwork, encounter gating, Magic Bounce and the rest of the approved PRU state are unchanged.
Actions run [41331042623](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41331042623) passed source regression checks, full clean compilation, 32 MiB ROM verification, artifact upload and release publication. ROM SHA256: `c9bf30a313f9d20e4999cefd701388da5ecea9cd0c0b99b9a5ee1c8c4de8d2b9`.
Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-bcbde6cf9b/Pokemon-Relics-Ultimate-bcbde6cf9b.gba
Gameplay was not emulator-tested; player testing remains outstanding.

## 2026-11-01 Alphoracle pedestal scale correction (compiled and released)
Branch: `feat/pru-relic-hunt-20261101`; source commit: `8ceb68cb4cfe3120cc85b5adb09875db3921688f`.
Enlarged the Alphoracle shrine figure while keeping its lower pedestal at 16x12 sprite pixels, matching the neighboring statue stands. The approved source artwork and its independent overworld palette remain in use; the I-Unown Eye statue is unchanged. Alphoracle's map interaction, unlock conditions and persistent visibility are unchanged.
Focused statue regression tests, the Khang/Alphoracle icon palette check, clean compilation, full ROM/header/checksum verification and GitHub prerelease publication passed in Actions run [41328773459](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41328773459). ROM: [Pokemon-Relics-Ultimate-8ceb68cb4c.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-8ceb68cb4c/Pokemon-Relics-Ultimate-8ceb68cb4c.gba), 33,554,432 bytes, SHA256 `3e30c2ed5dde1fc775b3832039f029ffc5ace274dbf3625fd533ce2116a344d3`.
No emulator screenshot or gameplay test was run; the player will test independently.

## 2026-11-01 statue scale and icon palette correction (compiled and released)
Branch: `feat/pru-relic-hunt-20261101`; source commit: `a3f50c389e8cbff4b114be41025d0adb297f49fd`.
Corrected the custom Eye and Alphoracle objects to 32x32 sprite frames, matching the ordinary statue's visible 16x32 artwork bounds. The Alphoracle object no longer uses its caught flag as an object-hide flag, so the shrine remains visible after capture and the existing script can report completion. Removed Khang's erroneous forced Articuno-P icon palette; Khang now uses its normal species palette, while Alphoracle retains its dedicated palette 14 and approved icon art.
The original encounter scripts, unlock conditions, collision, and cleared original statue foregrounds remain intact. Focused statue tests and the Khang/Alphoracle palette check passed. GitHub Actions run [41327318504](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41327318504) passed the full source regression suite, clean compilation, 32 MiB ROM/header/checksum verification, artifact upload and release publication. ROM: [Pokemon-Relics-Ultimate-a3f50c389e.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-a3f50c389e/Pokemon-Relics-Ultimate-a3f50c389e.gba), 33,554,432 bytes, SHA256 `4b103ca090aa57f7626de230ee2b53de6e37a54ad192edd7b2975c38a31c5258`.
No emulator screenshot or gameplay test was run; the player will test independently. Commit `5c98d131` is an incomplete upload and is superseded by the restored full-source commit above.

## 2026-11-01 Ruins of Alph statue restoration (compiled and released)
Branch: `feat/pru-relic-hunt-20261101`; source commit: `f76b6880f620735eae98d232843bfa23b10aec96`; parent: `203f05a0cbb90d9219f3aefce8585b31d24233c9`.
Restored the I-Unown eye monolith's cool-grey palette from its own object palette, installed the supplied Alphoracle statue as a separate tall indexed object graphic/palette, and cleared the original foreground statue tiles beneath both encounters using local metatile copies. Both encounter objects, map coordinates, interaction scripts and existing unlock gates remain in place. The two custom objects keep independent palette tags.
Focused Ruins of Alph checks and the full PRU source regression suite passed. GitHub Actions run [41325268343](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41325268343) passed compilation, Team Rocket sprite checks, 32 MiB ROM verification, artifact upload and release publication. ROM: [Pokemon-Relics-Ultimate-f76b6880f6.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-f76b6880f6/Pokemon-Relics-Ultimate-f76b6880f6.gba), 33,554,432 bytes, SHA256 `f545fadd6b73812c0e46bf97ff8bc24358b460cf10958bb2ec2593aa31a1c83b`.
No emulator screenshot or gameplay test was run; the player will test independently.

## 2026-11-01 I-Unown statue foreground fix (complete)
Branch: `feat/pru-relic-hunt-20261101`; source fix commit: `bc28e144f1e81cfe0a7925fcfd806f8a8836d7f0`; parent: `e555670b40a6022d2f4c88c0cc424d2d19eac910`.
Root cause was the B1F foreground layer at (16,9) and (16,10), which drew the original grey statue over the eye object. Two local metatile copies clear only those foreground tiles while retaining floor and collision data; adjacent statues are unchanged. The I-Unown encounter object/script remains unchanged.
Focused regression checks pass. GitHub Actions run [41316844492](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41316844492) passed full compilation, 32 MiB binary verification, artifact upload, and release publication. ROM: [Pokemon-Relics-Ultimate-bc28e144f1.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-bc28e144f1/Pokemon-Relics-Ultimate-bc28e144f1.gba), 33,554,432 bytes, SHA256 `a0bf30b49fbcc39f95cb89b8296a968c74c6567454131ba58315c7197233e1f7`.
No emulator screenshot test was run; player will test.

## 2026-11-01 Ruins of Alph / I-Unown patch checkpoint
Branch: `feat/pru-relic-hunt-20261101`; source patch commit: `80ddf582abb63dbbc0f172befdbc68b38e13b3af` (parent `66c046d64231022ad46aae48398a4ae3c561ffe6`; original confirmed base `924f5de512037d6052f94b29025d92cc263df20a`).
Completed: removed the oversized Alphoracle object; preserved the eye statue at B1F (16,10); moved the gated ladder to B1F (26,28); routed the rightmost final statue to the Alphoracle encounter with its original Champion/Suicune unlock gates; remapped only I-Unown's party/PC icon pixels onto palette slot 15.
Checks: focused map/icon regression checks passed; GitHub Actions run [41314187422](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41314187422) passed clean build, full binary verification and release upload. ROM: [Pokemon-Relics-Ultimate-80ddf582ab.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-80ddf582ab/Pokemon-Relics-Ultimate-80ddf582ab.gba), 33,554,432 bytes, SHA256 `8ee47fdc15ef6388991c81c17217371329649af1a8d892d0484a7a610ecc3ceb`.
The immediately preceding commit `66c046d64231022ad46aae48398a4ae3c561ffe6` is superseded; use the `80ddf582ab` release. Gameplay was not emulator-tested; the player will test.

## Where development is
Repo: jamesthoward2112-tech/Pokemon-Relics-Ultimate
PR #66 head before this patch: d68ac49fa10eb07ee60be54684cd0c78dda6bde2
PR #66 is stacked on #65 (Storm Shrine door), which builds on permanent-forms work.
Other PRs requiring careful selective integration: #55/#58 tutor/E4, #60/#61 Mewduo/item 910,
#62 Elite 20 finale. Do not assume main includes these.

## User-tested / compiled / released
a4d393129ec3683f0443a80272df71653a3874af = user-confirmed tutor-stable reference.
d46842dd2459b7723bfc1a5e446e9f005ebc7f3a = later Mewduo stable-lineage reference,
not proof that all nine tutors/art/icons remained good.
401214913d3809a5e82f565bce9553f9a438a1fd = published direct 32 MiB .gba, not confirmed.
027d713b9a2744df3c2e243a1ac1e19ccc5af60c = actual compiled ROM recovered from
Actions run 41056382028 / artifact 12976679332; ROM size/header and source tests passed.
Github release publishing failed HTTP 403 despite push event and Contents: write.
Original ROM SHA256: 81109f5d4c0fdd2d3da9a09df3580a07167d86e071906766ced44b5e907ab7c0.
Binary-only cave-door hotfix (delivered via ChatGPT attachment, NOT released on GitHub):
at ROM offset 0x1550E8, replace little-endian constant 0x32ED with 0x3287.
Hotfix SHA256: 966c35a00488fe4d2568054a00c80a449d823d76a7f4b2d0d4274721e5032f86.
Hotfix has NOT been player-tested; do not claim it works until the player confirms.

## Current player bug: Groudon access
The user filmed Dark Cave top-right rock wall with no usable cave door.
Map: data/maps/DarkCave_NorthSide_hns/map.json
Entrance warp (46,4) -> Route45_GroudonCave, with reciprocal return; guard (46,5)
hides when FLAG_IS_CHAMPION is set.
OnLoad native function PruOpenDarkCaveGroudonDoor in src/fieldmap.c replaced
the wall with tile 0x2ED and floor 0x281. The map's actual existing exit at
(45,9) uses known-walkable 0x287 (full metatile 0x3287), so this patch
uses that tile for (46,4); the player needs to test appearance/entry.
Cave warp elevation zero is a wildcard; do NOT claim elevation 3 itself is the bug.

## Standing priorities
- User tests the game in Pizza Boy; don't waste time/credits on optional mGBA checks.
- 450 species, no save-ID shifts, Indigo tutors broad learnability, relic custom sprites.
- Permanent black Primal Groudon/Kyogre and black Mega-look Rayquaza; no form changing.
- Mewduo DUEL SOUL, double-hits eligible spread moves; Dragon Ascent 10PP.
- Achilles Heel learners; old item 910; intact E4/E20, credits, Rocket/Relics quests.
- Preserve approved sprites, palettes, icon slots and BLD black/red badge.
- Avoid introducing player character selection not in current PR #66 scope.
- DONE / CURRENT / NEXT / COMMIT status, no promises or false release links.

## Engineering next steps after player-confirmed ROM
1. Consolidate feature-owned work onto one integration branch, protected deletion audit.
2. Smaller compiled-data invariant suite, 32 MiB ROM and checksum; no screenshot gating.
3. Migrate donor import outputs to approved checked-in sprite assets with hash manifest.
4. Fix 403 publication/release-only upload; preserve last player-tested rollback.
5. Keep PRU_HANDOFF.md and release ledger current for every AI session.
