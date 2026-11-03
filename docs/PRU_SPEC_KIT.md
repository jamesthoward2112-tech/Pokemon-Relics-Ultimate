# Spec Kit adoption for Pokémon Relics Ultimate (PRU)

**Status:** Adopted in the active PRU branch via PR #69. The constitution and templates are tracked, and AGENTS.md now requires a regression-first Spec Kit workflow for relevant changes. The official Spec Kit CLI and agent commands have not been installed; no game code is modified by this adoption.

## Why this exists

PRU is an established, playable C/GBA ROM hack with high-risk save IDs, event flags, map warps, palette-dependent sprites, trainer events and complicated CI donor-art imports. We use short specifications and explicit regression contracts to avoid losing approved features during AI-assisted changes.

## Read before each task

1. `AGENTS.md` — existing PRU rules and build policy.
2. `PRU_HANDOFF.md` — authoritative active work, issues and next steps.
3. `docs/PRU_RELEASE_LEDGER.md` — build, asset, test and SHA provenance.
4. `.specify/memory/constitution.md` — policy and acceptance gates.
5. The relevant `specs/<feature>/` documents — scope for this change only.

The current development branch is not guaranteed to remain `feat/pru-relic-hunt-20261101`. Confirm its HEAD and the newest approved source before starting; never hardcode an old checkpoint as the latest release.

## Ready-to-use process

For a larger feature or risky bug: write `spec.md` (player scenarios, current behaviour, acceptance, preserve), `plan.md` (real files, compatibility and testing), `tasks.md` (small independent changes), then implement. After implementation compare actual code and tests with every acceptance criterion. Leave no unresolved checklist item labelled complete.

For a small narrowly scoped fix, use a concise spec and one regression checklist rather than generating unnecessary research documents.

Recommended statuses: **requested / specified / planned / coded / source-tested / compiled / emulator-tested / released / player-tested**. Never collapse these into a single “done”.

## Install the official CLI and agent commands when working in a local checkout

The official GitHub Spec Kit CLI is not bundled into this documentation-only branch. From a clean, backed-up local checkout, and preferably on a dedicated integration branch:

```sh
uv tool install specify-cli
specify init --here --force --integration none --script py
```

`--integration none` provides shared scaffolding without assuming a coding-agent platform. To add supported commands for a specific installed coding agent, use `specify integration install <key>` (for example, `codex`, `claude` or `copilot`). Review the generated diff before committing; `--force` may overwrite managed paths. Do not re-run initialization blindly on a dirty PRU checkout.

Official guidance: https://github.github.io/spec-kit/guides/existing-projects.html
CLI and integrations: https://github.github.io/spec-kit/installation.html and https://github.github.io/spec-kit/integrations/index.html

## PRU review gate

- Confirm no unrequested `src/`, `data/`, `graphics/`, `sound/`, `assets/`, map, build workflow, species, moves or save-layout file changes.
- Check preservation of 450 species and approved art/abilities/forms (unless specifically amended).
- Audit changed tutor menus, map events/warps, item flags, Pokédex IDs and egg/hatch behaviour when applicable.
- State exactly which source regressions and emulator interactions passed; do not invent gameplay testing.
- For executable changes, use the existing canonical build and verify the 32 MiB binary, direct .gba asset and SHA-256.
- Keep working checkpoints in PRU_HANDOFF.md and docs/PRU_RELEASE_LEDGER.md.
- Keep the last verified binary available as a fallback.

## Adoption and future CLI setup

PR #69 merged the constitution, templates and initial release-safety specification onto the existing PRU work branch. A follow-up documentation commit wired them into AGENTS.md. Those changes do not modify gameplay, run an emulator or create a ROM release. For local native Spec Kit commands, use the official CLI installation instructions above in a safe checkout; review generated differences rather than overwriting existing PRU instructions.
