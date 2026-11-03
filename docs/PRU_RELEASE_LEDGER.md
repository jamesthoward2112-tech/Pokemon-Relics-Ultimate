## 3 November 2026 — Job 4 False Swipe and Escape Rope (Coded; source-tested; build pending)

- **Branch / source HEAD:** `feat/pru-relic-hunt-20261101`; source commit `0d51e263260c4a28e6de77e8389bb5563a231b7d`. The implementation was selectively reconciled from `prep/pru-rockshop-no-build-20261101`; no unrelated staged features were merged.
- **Last successful ROM:** Job 3C `pru-build-7cb61e567f`, source `7cb61e567f6ff33dd767836b76eedaf1ae1d3f56`, 33,554,432 bytes, SHA-256 `fc12476b1190a18d368358f13d1cb973e7d1e71ef83abdd8512d445f3de9182b`. This remains the fallback until Job 4 clean build succeeds.
- **Coded:** TM54 False Swipe (existing item 635 / ¥3,000) added to both Cherrygrove stock phases and Goldenrod 5F/Celadon 3F. Escape Rope remains reusable Key Item 120; Elm grants it after the initial Poké Ball progression and recovers it for saves that passed the event without it. Visible and hidden former Rope pickups now award one badge-tier TM. Mt Mortar, Whirl Islands, Sprout Tower and Tin Tower static Rope rewards were replaced; Goldenrod 2F and all 18 badge/PC stock entries no longer sell Rope. Existing pickup coordinates, graphics and flags are retained.
- **Source tests PASS:** focused Job 4 regression; Job 1 Dark Void; Job 2 Mystery Egg; Job 3 Rock Shop; Job 3A Expert; Job 3B Sylveon/450 Dex; Job 3C Ruins donor-parity; `git diff --check`. CI workflow now runs the focused regression and retains the blocking Alph ladder traversal test.
- **Build / emulator:** no Job 4 ROM build yet. GitHub Actions was triggered by source commit `0d51e263`; check its clean compile, 32 MiB verification and blocking Alph ladder mGBA traversal. Feature-specific shopping, teaching, Rope use and converted pickup interactions are not emulator-tested. No player test.
- **Exact next action:** check Actions for source commit `0d51e263260c4a28e6de77e8389bb5563a231b7d`; resolve any real failure; on success verify ROM asset/size/SHA, then update this checkpoint, release ledger, handoff and Notion with the release.
- **Notion:** source milestone comment added to the PRU Development Journal (comment `40d4939d-4316-8177-bccd-001d4862be24`).

# PRU release ledger — 2026-10-30 snapshot
Every new release requires full source SHA, parent lineage, PRs included,
ROM SHA256 and size, confirmed checks, untested gameplay and verified URL.

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
