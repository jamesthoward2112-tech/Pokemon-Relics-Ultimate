## 3 November 2026 — Job 5 Indigo tutors and Scary Face Fear (ROM built; Alph ladder mGBA-tested)

- **Branch / source commit:** `feat/pru-relic-hunt-20261101`; `6325f44fca3b1d9db9119878c7d907fd17433b83`. Feature implementation `afbf21db8c1f98ab6bd884b9ac1180ef64ec7ba9`; tutor regression correction `dadaef823eba6778d23f5301ac3ddfad05273bf2`; final assembly correction `6325f44fca3b1d9db9119878c7d907fd17433b83`.
- **ROM built and released:** [Pokemon-Relics-Ultimate-6325f44fca.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-6325f44fca/Pokemon-Relics-Ultimate-6325f44fca.gba) — 33,554,432 bytes (32 MiB), SHA-256 `42384cddfce34153452505eed6e3d963a71929b880d930079f56219984b98ea0`. Release: [pru-build-6325f44fca](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-6325f44fca).
- **Implemented:** Existing Indigo tutors retain all prior choices; added Eerie Fog and Scary Face to the Hazard tutor, Electroweb to Doubles, and Follow Me, Reflect, Double Hit and Baton Pass to Setup, using selective compatibility and existing move IDs. Scary Face retains its original properties and -2 Speed effect, then applies the existing Fear volatile only when the move result permits.
- **Source regression status: PASS.** New Job 5 regression, updated seven-test Indigo tutor regression, Jobs 1–4A source regressions, Job 3C donor-parity check and `git diff --check` all passed locally; Actions run [41635418000](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41635418000) passed the source tests and clean build.
- **Build / mGBA status: PASS.** Run 41635418000 verified the 32 MiB ROM and passed the blocking map-ID/coordinate Alph B1F entry, ladder exit and re-entry traversal. This confirms the existing ladder remains functional.
- **Gameplay untested:** Indigo tutor interaction/menu navigation and teaching, Eerie Fog in battle, and Scary Face Fear/Speed/status/ability/substitute/protection behavior were not exercised in gameplay. Alph puzzle-room return routes remain source-checked, not individually traversed.
- **Earlier failed runs retained:** 41633842320 exposed a stale menu-size assertion (corrected); 41634244020 exposed an invalid assembly symbol (replaced with native `jumpifmoveresultflags`). The corrected run 41635418000 passed.
- **Exact next action:** player-test Indigo tutor menus and teach both moves; verify Scary Face against eligible and immune/statused targets in singles and doubles. Use this released ROM as the next job's baseline.
- **Relevant source:** Indigo Plateau HNS scripts; `src/chooseboxmon.c`; `data/battle_scripts_1.s`; `tools/test_indigo_control_tutors.py`; `test/test_pru_indigo_tutors_scary_face.py`; `.github/workflows/pru-clean-build.yml`.
- **Notion:** final build, mGBA ladder result and untested feature gameplay recorded in the PRU Development Journal.

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

## 2026-11-03 Ruins of Alph original B1F ladder restoration

- Branch: `feat/pru-relic-hunt-20261101`; source commit `7cb61e567f6ff33dd767836b76eedaf1ae1d3f56`.
- Restored the original five B1F warp events/indices, ladder metatile attributes and (15,16) tile `0x42E5`; removed the (15,15) extra warp and interaction; build-time statue installer now preserves ladder data.
- Focused source regressions and full clean build passed in Actions run [41612553467](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41612553467). Blocking mGBA test asserted actual entrance, ladder exit and re-entry map IDs/coordinates. All four puzzle-room return connections passed source checks but were not individually traversed in mGBA.
- ROM size: 33,554,432 bytes. SHA-256: `fc12476b1190a18d368358f13d1cb973e7d1e71ef83abdd8512d445f3de9182b`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-7cb61e567f/Pokemon-Relics-Ultimate-7cb61e567f.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-7cb61e567f
- No player gameplay test was run. Next action if required: manually/emulator traverse each of the four puzzle-room return routes.

## 2026-11-03 Rock Shop Eeveelution Expert

- Branch: `feat/pru-relic-hunt-20261101`; source commit `868400903a8a76ab81c3b573404807bbd80a12a6`, based on Job 3 source `b4967a4948fcef832dc7ef95686fc707275b0054`.
- Actions run [41603367214](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41603367214) passed source regressions, clean HNS compilation, 32 MiB ROM verification, artifact upload and release publication.
- ROM: 33,554,432 bytes; GitHub asset SHA-256 `a31878022fd48141b0af3a2fcebbcd27257129401f067adee764427b5a564448`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-868400903a/Pokemon-Relics-Ultimate-868400903a.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-868400903a
- Existing mGBA Alph-ladder assertion failed with `No textured exterior frame after warp`; the workflow retained the failure while allowing packaging on this branch. Prior Job 3 `brown fraction 0.1881` failure remains recorded. Neither tests this job's NPC. Expert/menu/evolution gameplay and old-save loading remain untested.

## 2026-11-03 Ecruteak Rock Shop

- Branch: `feat/pru-relic-hunt-20261101`; source commit: `b4967a4948fcef832dc7ef95686fc707275b0054`, based on the Job 2 lineage `f43559e7682a6cfb9f9c316919e25c77aaf98632`.
- Actions run [41600095191](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41600095191) passed source regressions, full HNS compilation, 32 MiB binary verification, artifact upload and release publication. Its existing Alph-ladder mGBA visual assertion failed (`brown fraction 0.1881`) and is non-blocking on this branch; this is not an Ecruteak gameplay test.
- ROM size: 33,554,432 bytes. SHA-256: `bb28df95e916747a9617b0b530ce92c2bd0de7275f0dc3bbc328abbc79513661` (GitHub release asset digest).
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-b4967a4948/Pokemon-Relics-Ultimate-b4967a4948.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-b4967a4948
- Ecruteak purchases, Fog Badge tier behavior, save compatibility and player testing remain unverified.

## 2026-11-02 Route 34 Day-Care Mystery Egg seller

- Branch: `feat/pru-relic-hunt-20261101`; source commit: `f43559e7682a6cfb9f9c316919e25c77aaf98632`; parent Job 1 source: `aa850e57cf1c808f9a40314f8f5e54ecdce16b8f`.
- GitHub Actions run [41547688057](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41547688057) passed source regression, full compilation, 32 MiB ROM verification, existing mGBA Alph ladder traversal, artifact upload and release publication.
- ROM size: 33,554,432 bytes. SHA-256: `e839ac84ca532c359286b4cf6dbf0806b3da43436d93b31e076a29b96d2ec250`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-f43559e768/Pokemon-Relics-Ultimate-f43559e768.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-f43559e768
- mGBA tested the existing Alph ladder only. Mystery Egg purchase interactions, hatching, challenge party cases and pre-existing save loading remain gameplay-unverified.

## 2026-11-01 Correct B1F ladder exit trigger

- Branch: `feat/pru-relic-hunt-20261101`; source commit: `6e28dde2a5ba48420db1091c3fcc03c704e6ccd9`; parent: `8459d665559c9fc3acad96f5ae6a1d1b691f9162`.
- Corrected the prior ladder warp's location after player video showed the avatar arriving directly below the visible B1F ladder. The ladder tile is now at (15,15), with an A-button sign interaction that warps to the existing outside entrance (21,21); the original entry/exit warp at (15,16) remains.
- Actions run [41341671168](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41341671168) passed regression checks, full compilation, 32 MiB ROM verification, artifact upload and release publication.
- ROM size: 33,554,432 bytes. SHA256: `c3c63384493e60b896c8ad60c5e4e0d9307257d0590fc14ef950548bfa96b26c`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-6e28dde2a5/Pokemon-Relics-Ultimate-6e28dde2a5.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-6e28dde2a5
- Gameplay was not emulator-tested; player confirmation remains outstanding.

## 2026-11-01 B1F ladder exit and I-Unown Eye pedestal

- Branch: `feat/pru-relic-hunt-20261101`; source commit: `bcbde6cf9b03aa7e8cea3d14dc1c6a4683150c99`; parent: `aa3cb1b6e73dfb26d53203004f718f35124af5f5`.
- Scope: make the visible B1F ladder at (12,10) return to the existing outside entrance, retain the original south exit, and resize the Eye statue's lower inscribed pedestal to 16x12 within its existing 32x32 frame.
- GitHub Actions run [41331042623](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41331042623) passed source regression checks, full compilation, 32 MiB binary verification, artifact upload and release publication.
- ROM size: 33,554,432 bytes. SHA256: `c9bf30a313f9d20e4999cefd701388da5ecea9cd0c0b99b9a5ee1c8c4de8d2b9`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-bcbde6cf9b/Pokemon-Relics-Ultimate-bcbde6cf9b.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-bcbde6cf9b
- Gameplay was not emulator-tested; player testing remains outstanding.

## 2026-11-01 Alphoracle pedestal scale correction

- Branch: `feat/pru-relic-hunt-20261101`; source commit: `8ceb68cb4cfe3120cc85b5adb09875db3921688f`.
- Scope: enlarge the Alphoracle figure and retain a 16x12 lower pedestal at the same scale as nearby statues. Eye statue and icon palettes remain unchanged.
- GitHub Actions run [41328773459](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41328773459) passed regression checks, clean build, ROM/header/checksum verification, artifact upload and GitHub release publication.
- ROM size: 33,554,432 bytes. SHA256: `3e30c2ed5dde1fc775b3832039f029ffc5ace274dbf3625fd533ce2116a344d3`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-8ceb68cb4c/Pokemon-Relics-Ultimate-8ceb68cb4c.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-8ceb68cb4c
- No emulator or gameplay test; awaiting player validation.

## 2026-11-01 statue scale and icon palette correction

- Branch: `feat/pru-relic-hunt-20261101`; source commit: `a3f50c389e8cbff4b114be41025d0adb297f49fd`.
- Scope: resize both custom Ruins of Alph statues to standard statue scale; keep the Alphoracle shrine visible after capture; restore Khang's normal species icon palette and retain Alphoracle's dedicated PC/party palette.
- GitHub Actions run [41327318504](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41327318504) passed source regressions, clean build, ROM/header/checksum verification, artifact upload and GitHub release publication.
- ROM size: 33,554,432 bytes. SHA256: `4b103ca090aa57f7626de230ee2b53de6e37a54ad192edd7b2975c38a31c5258`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-a3f50c389e/Pokemon-Relics-Ultimate-a3f50c389e.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-a3f50c389e
- No emulator or gameplay test; awaiting player validation.

| Source commit | Status | Evidence |
| --- | --- | --- |
| a4d393129ec3683f0443a80272df71653a3874af | Player-confirmed tutor-stable reference | GitHub release tag pru-build-a4d393129e |
| d46842dd2459b7723bfc1a5e446e9f005ebc7f3a | Later stable Mewduo-lineage reference; not proof of all features | GitHub release tag pru-build-d46842dd24 |
| 401214913d3809a5e82f565bce9553f9a438a1fd | Direct 32 MiB GitHub .gba published; player validation incomplete | GitHub release tag pru-build-401214913d |
| 027d713b9a2744df3c2e243a1ac1e19ccc5af60c | Compiled/validated 32 MiB, NOT published as GitHub release; player saw inaccessible Dark Cave entrance | Actions run 41056382028, artifact 12976679332 |

027d713b9a original ROM SHA256:
81109f5d4c0fdd2d3da9a09df3580a07167d86e071906766ced44b5e907ab7c0

027d713b9a binary-only door-tile hotfix (local user attachment, untested, not a GitHub release):
966c35a00488fe4d2568054a00c80a449d823d76a7f4b2d0d4274721e5032f86

Actions 41048069339: compile/verify/publish succeeded.
Actions 41051288000 and 41053595222: compile/verify passed, optional mGBA frame step failed.
Actions 41056382028: compile/verify/artifact passed, GitHub prerelease publication failed 403.
The failed run was a PUSH event and setup log recorded Contents: write. The 403
cannot be corrected by merely repeating that already-present YAML permission.

Fallback preference: a4d393129e for specifically confirmed tutors; use d46842dd24
only for features the player actually tested. Never call 401214913d player-confirmed.

## 2026-11-01 Ruins of Alph / I-Unown patch

- Branch: `feat/pru-relic-hunt-20261101`; source parent: `924f5de512037d6052f94b29025d92cc263df20a`.
- Source patch commit: `80ddf582abb63dbbc0f172befdbc68b38e13b3af` (intermediate `66c046d64231022ad46aae48398a4ae3c561ffe6` was superseded to preserve the exact Champion/Suicune encounter gates).
- Scope: remove oversized Alphoracle object while preserving the eye statue and encounter; move the gated ladder to B1F (26,28); correct I-Unown icon palette without changing front/back sprites.
- GitHub Actions run [41314187422](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41314187422): clean build, binary verification, artifact upload and release publication all passed. No emulator screenshot/gameplay testing.
- ROM size: 33,554,432 bytes. SHA256: `8ee47fdc15ef6388991c81c17217371329649af1a8d892d0484a7a610ecc3ceb`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-80ddf582ab/Pokemon-Relics-Ultimate-80ddf582ab.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-80ddf582ab

## 2026-11-01 I-Unown statue foreground fix

- Branch: `feat/pru-relic-hunt-20261101`; fix commit: `bc28e144f1e81cfe0a7925fcfd806f8a8836d7f0`; parent: `e555670b40a6022d2f4c88c0cc424d2d19eac910`.
- Root cause: B1F foreground tiles at (16,9) and (16,10) drew the original grey statue over the eye object. Local metatile copies 200/201 clear only these tiles and preserve collision attributes. Surrounding statues and the encounter script remain unchanged.
- Actions run [41316844492](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41316844492): full build, ROM verification, artifact upload and publication all passed.
- ROM size: 33,554,432 bytes. SHA256: `a0bf30b49fbcc39f95cb89b8296a968c74c6567454131ba58315c7197233e1f7`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-bc28e144f1/Pokemon-Relics-Ultimate-bc28e144f1.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-bc28e144f1
- Gameplay was not emulator-tested.

## 2026-11-01 Ruins of Alph statue restoration

- Branch: `feat/pru-relic-hunt-20261101`; source commit: `f76b6880f620735eae98d232843bfa23b10aec96`; parent: `203f05a0cbb90d9219f3aefce8585b31d24233c9`.
- Scope: restore the Eye statue's cool-grey stone palette, install the supplied Alphoracle statue as a separate indexed overworld object/palette, and remove only the old statue foreground tiles beneath the two encounters.
- GitHub Actions run [41325268343](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41325268343) passed focused statue checks, full source regression, compilation, 32 MiB binary verification, artifact upload and release publication.
- ROM size: 33,554,432 bytes. SHA256: `f545fadd6b73812c0e46bf97ff8bc24358b460cf10958bb2ec2593aa31a1c83b`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-f76b6880f6/Pokemon-Relics-Ultimate-f76b6880f6.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-f76b6880f6
- No emulator screenshot/gameplay testing; player testing remains outstanding.
# 2026-11-02 Radical Red move audit and I-Unown Dark Void

- Branch: `feat/pru-relic-hunt-20261101`; source commit: `aa850e57cf1c808f9a40314f8f5e54ecdce16b8f`; checkpoint commit: `f8484c84c9f26d7b44d1a558f3d673e666892300`.
- GitHub Actions run [41542334072](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41542334072) passed source regression, full compilation, 32 MiB binary verification, existing mGBA Alph ladder traversal, artifact upload and release publication.
- ROM size: 33,554,432 bytes. SHA-256: `3a01c7c611c2cc1cd30d95e0c87e3ced046236dd9a2c6b54120c36c6f13e8816`.
- Direct ROM: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-aa850e57cf/Pokemon-Relics-Ultimate-aa850e57cf.gba
- Release: https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-aa850e57cf
- The workflow's mGBA test only validates the existing Alph ladder traversal. Dark Void singles/doubles, Omen Eye battle behavior and pre-existing save compatibility remain untested; player validation is outstanding.

## Job 6 Golden Ho-Oh / Golden Reign / Phoenix Soul — source pushed, build pending

- Source commit: `8abc9fc54fa8d361f33d4c50939bcb4116ba99a7` on `feat/pru-relic-hunt-20261101`; based on Job 5 checkpoint `2e9de621ec13460152663112145ac20e09c11dd6`.
- Source scope: exclusive Golden Reign and Phoenix Soul for `SPECIES_RELIC_HO_OH`; sole level-100 Oak/Mt. Silver encounter with all RELIC, Crest and Oak gates; Tin Tower and Navel Rock remain story flybys and are no longer catchable. Legacy saves and existing Ho-Oh are retained.
- Focused source checks for Jobs 1–6 passed locally. Added battle-engine checks are queued in Actions run [41649939179](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41649939179). Production build, 32 MiB binary verification and blocking mGBA Alph ladder test are pending.
- Fallback remains Job 5 ROM `Pokemon-Relics-Ultimate-6325f44fca.gba`, SHA-256 `42384cddfce34153452505eed6e3d963a71929b880d930079f56219984b98ea0`. No Job 6 release URL or ROM checksum is recorded until Actions succeeds.


## 4 November 2026 — Eeveelution sizing and user calf redraws (ROM built; player visual check pending)

- Branch `feat/pru-relic-hunt-20261101`; source commit `91998b7daa577a822d4dbeba2cb9df64c2eb43ef`. GitHub Actions run [41817527904](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41817527904) passed sprite import/scale checks, Box 3 save validation, source regressions, battle-engine tests, clean compile, 32 MiB binary verification and release publication.
- Applied 80% nearest-neighbor centered sizing to all ten custom Eeveelution fronts/backs/icons, rebuilt Nimbeon's party icon from the approved front and corrected icon palette assignments. Imported user-provided Miltitan/Mootiny fronts and normal palettes; preserved the back art and remapped it to the new palette; icons were derived from the supplied fronts. No shiny redraws were supplied.
- Release [pru-build-91998b7daa](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-91998b7daa): [Pru.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-91998b7daa/Pru.gba), 33,554,432 bytes, SHA-256 `32c0f2a1f51258a3f6920335bccbf0410960c3e5666604fac08132a22562bb80`; [Pru.sav](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-91998b7daa/Pru.sav), 131,072 bytes, SHA-256 `d71a68d383115012231c2b77e7260019bfa81a75ee5c416960109fbc479446bc`.
- Box 3 save checks passed: 24 intended Pokémon, valid records/checksums/shiny flags, level 50, no held items. Other boxes and original save were not modified.
- Gameplay visual testing was not run in Pizza Boy; player inspection is still required for front/back sprites and party/PC icons. Do not report visual QA as complete based on source/build checks alone.


## 4 November 2026 — Restore build-538 Eeveelutions and reduce size (ROM built; player visual check pending)

- **Branch/source:** `feat/pru-relic-hunt-20261101`; source head `b24b5544195b5cac44e4c2aacc2e27b1ea8603bf` (sprite implementation `b48d82aeb0b7c2cc83634133d92eab20d09988f2`, palette-check line-ending correction `b24b5544195b5cac44e4c2aacc2e27b1ea8603bf`).
- **What changed:** pinned the exact build-538 post-import sprites, palettes and party icons for ten custom Eeveelutions; restored these after current donor synchronization and applied only a centered 80% nearest-neighbour reduction. Nimbeon's build-538 party icon and icon palette assignment were restored. Kept user-approved Miltitan/Mootiny art in the same ROM.
- **Checks:** Actions run [41822264299](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/actions/runs/41822264299) passed exact pixel/palette/icon baseline checks, calf sprite checks, Box 3 save validation, full source regressions, battle-engine tests, clean compilation, compiled-sprite check, 32 MiB ROM verification and publication. Earlier run #540 stopped at a CRLF-sensitive palette checksum check; the check was corrected and run #541 passed.
- **Release:** [pru-build-b24b554419](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/tag/pru-build-b24b554419). [Pru.gba](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-b24b554419/Pru.gba), 33,554,432 bytes, SHA-256 `c88b78c23f5f3b0cd647f6e2038f51cd1c95c56a2804d0de9c80f6ab19d624cd`. [Pru.sav](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases/download/pru-build-b24b554419/Pru.sav), 131,072 bytes, SHA-256 `d71a68d383115012231c2b77e7260019bfa81a75ee5c416960109fbc479446bc`.
- **Gameplay appearance:** no post-build Pizza Boy screenshot or hands-on PC/party check was available in this run; the player should confirm the reduced sprites in-game. The prior build-538 appearance is used as the pixel baseline, and automated checks confirm the output is exactly its 80% resampling with palettes intact.
- **Save safety:** Box 3 contains the intended 24 valid Pokémon, checksums and shiny values; other boxes and the original save were not modified.
