# PRU release ledger — 2026-10-30 snapshot
Every new release requires full source SHA, parent lineage, PRs included,
ROM SHA256 and size, confirmed checks, untested gameplay and verified URL.

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
