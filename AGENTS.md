# AGENTS.md — Pokémon Relics Ultimate
Updated 2026-10-30. Supersedes outdated Johto Relics / pjr-rebuild guidance.

Repository: jamesthoward2112-tech/Pokemon-Relics-Ultimate.
Read PRU_HANDOFF.md and docs/PRU_RELEASE_LEDGER.md at the beginning of every task.
Current game is standalone PRU, not a PJR donor fork release.

## Player instructions
- Deliver a real raw .gba quickly. The player handles gameplay testing in Pizza Boy.
- Never add optional mGBA screenshot/boot tests as delivery gates.
- Do not claim 'done' until a genuine file exists, with exact SHA and build provenance.
- Report DONE / CURRENT / NEXT / COMMIT, distinguishing source, compiled, released and player-tested.
- Never substitute generated pictures or Work prompts for changes to the ROM.
- Protect existing saves, items, flags, species IDs, moves, approved artwork, E4/E20 and quests.
- Exactly 450 species. Final three: Rhyperior, Magmortar, Electivire.
- Preserve all Indigo tutor/specialist functions and broad compatibility.
- Groudon/Kyogre are permanently black Primal appearances; Rayquaza has permanent black Mega appearance;
  no form changing, Mega Stones or Orb-triggered transformations.
- Mewduo ability is DUEL SOUL including eligible two-foe moves.
- Dragon Ascent has 10 PP; Achilles Heel needs actual learners.
- Challenge menu should reuse H&S options. No player sprite selector without a separate request.

## Branch policy
- Do not blindly merge parallel PRs #55/#58/#60/#61/#62/#65/#66.
- Start from last player-confirmed good source lineage; reconcile later changes and feature owners.
- One integration writer. No force pushes. Never overwrite separate active branches.
- Before integrating, inspect all deletions/reversions from protected tables:
  species, move tutor compatibility, item 910, map warps/flags, graphics/icon registrations and save IDs.
- Source success is not binary success; compilation is not a release; release is not player-testing.

## Build/artwork/release
- make hns -j2 -O produces pokehns.gba (33,554,432 bytes).
- Minimum essential checks: roster, important tutor interfaces, item IDs, map/warp references,
  compiled size/header, and exact ROM SHA256. No unrelated emulator gates.
- Approved artwork must not silently revert. Existing CI mutates sources by restoring/importing
  donor art; migrate carefully by committing approved outputs and hash-pinning a sprite manifest.
  Do not remove required CI restorations before migration is complete.
- GitHub Actions ZIP does not count as direct .gba release. Verify actual asset URLs.
- If GitHub Release upload fails, preserve/recover the EXACT successful compiled ROM and record SHA.
- 'Add a door' requires artwork, walkable collision, correct warp in both directions and
  compatibility with previous saves; text-only source checks cannot prove gameplay.
- Keep a release ledger with source SHA, parent, included PRs, binary checksum, status and URL.
