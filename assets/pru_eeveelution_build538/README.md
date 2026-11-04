# Build 538 Eeveelution source art

This folder pins the ten Eeveelutions' approved battle art, palettes and party
icons for sprite scaling. The source baseline is build 538 commit
`3d6a0460d5c151de5bf3c7f1fe49cb6a94d38086` after its normal sprite import
pipeline: seven Infinity species use the exact installed Infinity artwork and
palettes; Eeveeon, Nimbeon and Drakeon use the pinned PRL artwork and palettes.
All ten use the build-538 party icon files and icon palette assignments.

`manifest.json` records SHA-256 hashes for every pinned input. The build
restores these files after its donor synchronization stages, then applies only
an 80% nearest-neighbour reduction. This prevents later donor imports from
silently changing the approved artwork before resizing.
