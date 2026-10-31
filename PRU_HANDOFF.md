# PRU_HANDOFF.md — authoritative session handover
Last audited: 2026-10-30. All statuses below are scoped to evidence; no newer gameplay is implied.

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
