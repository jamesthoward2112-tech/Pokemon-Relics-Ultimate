# Heracurion – approved PRU sprite replacement

User approved the new Heracurion concept on 2026-10-31.
Design: antique golden horn, teal relic armour, matched battle back and party icon.

This patch preserves all species IDs, moves, stats, evolution data and game mechanics.
Sprites use 64×64 indexed PNG for front/back, 32×64 indexed icon and 16-colour JASC palettes.
The party icon is remapped to PRU's existing shared palette index 2, preventing icon-palette table or save ABI changes.

Source build reference for the other relic species: dd1d0360ffba95ef4f3197c2add3246c86df174b.
The patch should install after PRL sprite synchronisation, while respecting the existing
feat/pru-locked-gmax-charaxis-polish-20261031 branch and existing post-sync installers.

New approved art SHA256 is locked in tools/pru/install_approved_heracurion.py.
A ROM build and user test are required before calling the patch playable.
