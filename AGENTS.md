# AGENTS.md — Pokémon Relics Ultimate (PRU)

This repository is **Pokémon Relics Ultimate (PRU)**. It is not the older Pokémon Johto Relics (PJR) repository.

## Repository and safe starting point

- Repository: `jamesthoward2112-tech/Pokemon-Relics-Ultimate`
- Default branch: `main`; current development often lives on unmerged feature/repair/Work Mode branches.
- At the start of each task, inspect the requested branch, its live GitHub HEAD, current PRs and local working-tree status. Do not assume `main` is the most playable or complete build.
- Preserve the latest *verified* working PRU base and all user-approved fixes. Verify its SHA and contents before rebasing, merging or copying source.
- Never switch to `Pokemon-Johto-Relics`, `pjr-rebuild`, or an older ROM to satisfy a PRU request.
- Multiple worktrees/sessions may be active. Do not reset, clean, delete, amend, force-push, or move another session's branch or worktree. Do not interrupt an ongoing build.
- In particular, do not remove a branch just because a newer PR exists: check ancestry, divergent commits, unique files, open PRs, uncommitted work and live build dependencies first.

## Crash-resistant work

Keep useful work recoverable if a Work Mode session stops.

1. Inspect only enough context to identify the correct branch and affected files.
2. Implement small, coherent changes on an isolated task branch/worktree.
3. Run relevant source checks, then commit and push to **that task's approved PRU branch** regularly.
4. Verify the pushed SHA; inspect GitHub Actions for that SHA.
5. Fix any reproducible test/build failures and repeat the check; do not describe an unverified ROM as playable.
6. Preserve unrelated staged, unstaged and untracked work.
7. When time or Work Mode credits are limited, save progress before starting the next large change.

Do not automatically merge into `main`, close PRs, delete branches or publish a release as a side effect of a routine code change.

## Current PRU project decisions

The following are approved gameplay directions; check the active task and tests to learn which are already implemented.

- Keep the Pokémon Relics Ultimate **PRU** title screen and branding. PJR title artwork is not a replacement.
- Pokémon Rhythm backgrounds are the approved active battle-background style. Retain provenance and source artwork; do not silently revert to Crystal Redux art.
- The Johto Elite Four and later Kanto Elite Four rematch use the original five functional League-room actors, with championship progression selecting the battle.
- After the Kanto championship, the Elite Four entrance is permanently sealed while Indigo Plateau's Pokémon Center, healing, mart and tutors remain accessible.
- Elite challenge rounds and leader rematches belong in the Saffron VIP Dojo, not Indigo Plateau's Pokémon Center. The current expansion target is 20 Elite challenges.
- Approved Indigo Plateau tutor organization is a neat line on the lower-left floor facing upward toward the mart. Do not remove tutors without preserving every move service.
- Preserve the Rocket badge-heist progression, Jessie/James/Meowth interception, RELICS encounters, custom Pokémon, moves, abilities, sprites and all working quality-of-life changes.
- Preserve intentionally chosen Johto starters: Scarabub → Heracross → Heracurion, Skarmet → Skarmory → Skarmadon, and Mootiny → Miltank → Miltitan. Silver receives the mapped unchosen baby starter.
- Red's established team is Edensaur, Charaxis, Fortotoise, Khang, Nolax and Noxichu. Jessie and James keep Pikachu where scripted; Noxichu is reserved for Red.
- Avoid frustrating puzzle redesigns; the project favors streamlined progression.

## Assets and external searches

- Reuse approved assets already in PRU before searching archives, ROM donors or the ChatGPT Library again.
- Record reusable donor attribution and exact asset paths in project documentation.
- Do not overwrite existing approved Pokémon graphics globally for one trainer-specific encounter.
- Keep source assets needed by clean GitHub Actions builds; do not rely on ignored local/generated files.

## Build, QA and handoff

- The HNS build command is `make hns` and its ROM is `pokehns.gba`.
- Run the relevant source regression tests and a clean build. Use mGBA runtime checks for scripted events, trainers and actors where required.
- A successful source test is not proof that a full story progression or new ROM was tested.
- The requested playable release is a **directly downloadable `.gba`**, not a ZIP-only handoff.
- Report separately: local-only edits; committed/pushed changes; GitHub Actions state; tests run; build result; and an actual available ROM/download link.
- Do not describe work as continuing in the background without evidence from the active session, GitHub or automation.
