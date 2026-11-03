# Pokémon Relics Ultimate Constitution

This constitution describes non-negotiable safety and delivery principles for AI-assisted work on the existing PRU C/GBA game. It supplements, rather than replaces, AGENTS.md, PRU_HANDOFF.md and docs/PRU_RELEASE_LEDGER.md.

## Core Principles

### I. Preserve the playable game first

PRU is a working standalone Johto + Kanto ROM hack, not a new app or a rewrite. Begin every task by inspecting the current branch HEAD, the latest successful ROM/source lineage, AGENTS.md, PRU_HANDOFF.md and docs/PRU_RELEASE_LEDGER.md. Preserve existing progress, event flags, species/move/item IDs, save compatibility, gameplay, maps, art, graphics registrations, quests, trainers, tutors and rewards unless an explicit request changes them. Never silently revert approved sprites or palettes.

### II. One bounded change and clear acceptance criteria

Before implementation, document the requested behaviour, the exact affected subsystems, what must remain unchanged, acceptance scenarios, failure scenarios and whether old saves are at risk. Distinguish player-approved requests from proposals, assumptions and unverified reports. Prefer localised edits over broad refactors; never merge unrelated feature branches blindly. The currently approved 450-species roster and established permanent-form rules are protected baseline constraints unless explicitly superseded.

### III. Regression prevention is part of completion

For every game-code change, identify the relevant source-level regressions and run the established appropriate checks. For changes to encounters, maps, warps, sprites, tutors, items or battle effects, check adjacent behaviours and preserved flags/IDs. Document what was tested in source, compiled, tested in mGBA, or verified by the player; those are distinct claims. Run targeted mGBA interaction tests when explicitly requested or genuinely required to validate the risky behaviour, but do not add unrelated optional emulator screenshot gates.

### IV. Builds must have verifiable provenance

The canonical build is `make hns -j2 -O`, producing `pokehns.gba` of exactly 33,554,432 bytes (32 MiB). Before claiming a playable ROM delivery, verify the compiled binary and its checksum and provide the exact source commit, relevant CI run, direct .gba release asset and SHA-256. A successful source check is not a successful ROM build; a successful build is not release publication; neither is proof of player-tested gameplay. Never substitute a ZIP archive, image or development plan for a requested playable .gba.

### V. Protect source lineage and approved artwork

Use one integration writer for each overlapping area. Do not force-push or overwrite active concurrent work. Reconcile newer commits before integration. Record which branch and exact commit were used, and keep a known-good fallback. The existing CI artwork import stages are part of the current production build; do not remove or reorder them casually. Player-approved pixel art and palettes are controlled assets, not prompts for generative replacement.

### VI. Minimise wasted work and preserve resumability

Keep each task small enough to finish, verify and resume independently. Use existing scripts, conventions and tests before introducing dependencies. Record DONE / CURRENT / NEXT / COMMIT, blocked checks, source vs binary status and exact next action in the established handoff/release ledger as appropriate. Avoid speculative full-repository rewrites, duplicate builds, gratuitous branches and unnecessary API/AI calls.

## Practical PRU constraints

- Maintain the approved species count and identities unless explicitly revised.
- Treat old-save compatibility, Pokédex ordering, event flags, tutor compatibility, and overworld encounters as high-risk.
- Preserve the ongoing RELICS hunt, E4/E20 and Indigo services while changing other features.
- Update only the subsystems and test files within the requested scope.
- Existing repository instructions and latest evidence take precedence over obsolete documents in other branches.

## Development and review

1. Read the active project handoff and confirm the latest source and last successful binary.
2. Create a bounded specification with user scenarios and explicit preservation checks.
3. Make an implementation plan referencing real repo paths, dependencies and save implications.
4. Turn the plan into atomic tasks with focused test evidence.
5. Implement, run relevant regressions, inspect the diff for unintended deletions, and build only as necessary.
6. Record verification and release provenance before announcing completion.

## Governance

Explicit current user instructions take precedence; if they materially change a prior invariant, document that change. Read AGENTS.md alongside this constitution. The latest active-branch handoff and ledger provide operational facts and build status, not permanent policy. Amend this constitution through a reviewable diff, with rationale and any affected specs updated. Do not use constitution updates as a route to silently alter game features.

**Version**: 1.0.0 | **Ratified**: 2026-11-03 | **Last Amended**: 2026-11-03
