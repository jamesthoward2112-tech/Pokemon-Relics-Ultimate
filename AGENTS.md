# AGENTS.md — Pokémon Relics Ultimate
Updated 2026-11-03. Supersedes outdated Johto Relics / pjr-rebuild guidance.

Repository: jamesthoward2112-tech/Pokemon-Relics-Ultimate.
Read PRU_HANDOFF.md and docs/PRU_RELEASE_LEDGER.md at the beginning of every task.
Current game is standalone PRU, not a PJR donor fork release.

## Spec Kit workflow for PRU changes
- Read `.specify/memory/constitution.md` and `docs/PRU_SPEC_KIT.md` alongside the handoff and release ledger before new work. These add to, not replace, existing PRU instructions.
- For substantial features or risky fixes, record user-visible acceptance criteria, unaffected behaviours and save compatibility in `specs/<feature>/spec.md`; add `plan.md` and `tasks.md` only when scope warrants them. For tiny fixes, prefer a concise regression checklist.
- Compare the current HEAD, known-good commit, failing logs and changed files before patching. Distinguish a broken game feature from a broken test harness. Prefer the smallest verified correction; never alter working game maps just to satisfy a mistaken test.
- Keep actual source tests, compilation, mGBA interaction evidence, GitHub release and player testing as separate statuses. Never bypass a required real gameplay test or add unrelated screenshot gates.
- Check CI and release evidence before declaring completion. Preserve the previous confirmed ROM; do not force push or overwrite concurrent work.
- The tracked Spec Kit templates can be used without the official CLI. Only claim CLI commands or agent integrations were installed or run when they actually were.

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
