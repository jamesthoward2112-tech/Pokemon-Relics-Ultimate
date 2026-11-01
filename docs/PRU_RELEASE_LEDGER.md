# PRU release ledger — 2026-10-30 snapshot
Every new release requires full source SHA, parent lineage, PRs included,
ROM SHA256 and size, confirmed checks, untested gameplay and verified URL.

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
