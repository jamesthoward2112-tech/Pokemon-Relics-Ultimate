# PRU combined 22 backgrounds + ten Eeveelution artwork — 10 November 2026

Base is approved 22-background feature commit `fce587ac` (GitHub PR #85). The ten latest Eeveelution sprite sets come **from the successfully compiled 09:20 10 November Eeveelution test ROM source**, not older screenshots. All ten front/back sprites (64×64), party icons (32×64), and in-game palettes were restored byte-identically. Source species ID slots, names, mechanics and saves were not renumbered.

## Backgrounds
- Twelve PRU-original battleback scenes remain approved.
- Ten Nidhoggn CC0 scenes remain accepted and credited in `docs/PRU_Expanded_22_Backgrounds_Credits.md`.
- Context-specific Johto/Kanto Gym assignments, caves, Lavender ghost floors, rainy Lake of Rage, Mt Silver rock and special Golden Ho-Oh summit are preserved from PR #85.

## Additional build-source repairs
The 22-background Git branch omitted the otherwise working Team Rocket balloon object-event source PNG and palette. These were restored from the previous successfully compiled sprite-test tree. Four unrelated donor species art folders (Adnokana, Mewsion, Frytning, Cheauking) contained PNGs that the GBA converter cannot compile; their **existing working, indexed sprites and matching palettes** were restored from that same previously compiled source to avoid introducing speculative art changes.

## Verification
- `make hns -j4 -O`: **PASS** (exit 0)
- ROM file size: **33,554,432 bytes** (32 MiB)
- ROM SHA-256: `3f0ebf750017e2f2c40beb506c362271de65e3f26b3b0e8fda418f2cee7a7165`
- GBA header checksum: **PASS**
- Ten sprites/palettes compared byte-for-byte with original approved test source: **PASS**
- Twenty-two battleback source tile sets and mapping assertions: **PASS**
- **Pending:** in-game emulator inspection of all platforms, palettes and battle transitions. This is a test build, not a verified public Alpha release.

The SpriteCook archive contains 52 images; 23 source images are exactly 64×64. Their numbered review sheet is a **separate review-only artifact**. None of those additional unapproved candidates has been installed into this ROM.
