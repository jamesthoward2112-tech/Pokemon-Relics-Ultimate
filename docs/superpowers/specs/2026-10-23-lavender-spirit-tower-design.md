# Lavender Spirit Tower restoration — approved design

## Intent

Restore the optional, seven-floor Lavender memory tower so it behaves like a complete Pokémon Tower dungeon, with a believable spirit-travel premise, sparse human encounters, wild ghosts, escalating fog and a safe retreat to Mr Fuji. The player reported black voids and an apparently broken tower in `1000043054.mp4`; the present PRU instance borrows FireRed floor binaries and stairs but omits the donor's encounters and nearly all objects.

## Scope

- Keep the separate HNS tower map IDs, original FireRed/LeafGreen seven-floor binaries, graphics, geometry and staircase links. Do not replace modern Lavender Radio Tower or reorder existing map IDs, flags or species.
- Validate every layout dimension, warp tile and reciprocal stair destination against the original donor, with a test that catches invalid destination coordinates and collision/layout regressions. Fix concrete defects found.
- Make Mr Fuji describe a **strange Pikachu** rumoured to be in the old tower, without mentioning a costume or Mimikyu. He offers to send the player there **in spirit** after they close their eyes; an Escape Rope returns to the tile directly before him. The normal tower ground-floor exit also returns to Soul House.
- Moderate overworld fog on floors 2–7, increasing sense of eeriness; unchanged Eerie Fog battle encounter rules for Maroghost, Osteodian and Mimikyu. Original tower music remains.
- Add wild ghost encounters to floors 2–7, using approved Gen 1–3 and existing PRU species only, scaled from the high 40s to mid 60s. Keep first floor quiet. Do not create new Pokédex entries.
- Use at most a few optional Channeler NPCs. Avoid compulsory generic trainer battles on each floor.
- Preserve Maroghost Lv66 (5F), Osteodian Lv68 (6F), Mimikyu Lv70 (7F), catch-or-defeat guardian progression, respawn-after-defeat Mimikyu, catch flags, and Thick Club reward.

## Alternatives considered

1. **Restore existing FRLG donor (selected):** full original layout files and tilesets are already in PRU, so repair missing integration and test the navigation with the fewest moving parts.
2. Import a new third-party tower ROM: would introduce uncertain incompatible assets and still require event, encounter and warp integration; no improvement without a known better donor.

## Verification

Source-level tests validate the map and wild-data contracts, no new species, return-script and boss flags. A fresh GitHub Actions compile and playable emulator pass must be reported separately; do not claim gameplay verification from a source test alone.
