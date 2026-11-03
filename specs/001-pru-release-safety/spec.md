# Feature Specification: PRU release and regression evidence

**Feature Branch**: `chore/pru-spec-kit-20261103`  
**Created**: 2026-11-03  
**Status**: Draft — process definition only; implementation not started  
**Input**: Reduce recurring regressions and incomplete ROM deliveries without rewriting the existing game.

## User Scenarios & Testing

### User Story 1 — Preserve working features (Priority P1)

As the player, I want a change to fix its target behaviour without undoing previously working tutors, encounters, artwork, items or save progress.

**Independent test**: Review one bounded PR against its named existing regression checks and protected subsystems.

1. **Given** a known-good source lineage and a proposed change, **When** the plan is written, **Then** it names preserved behaviours and their concrete checks.
2. **Given** a modified map, encounter or tutor, **When** source tests run, **Then** adjacent affected flags, lists and scripts are checked.

### User Story 2 — Tell source status from playable status (Priority P1)

As the player, I want a direct released ROM with verified provenance rather than an unverified “done” statement.

1. **Given** a completed source change, **When** a release is claimed, **Then** the exact commit, CI run, 33,554,432-byte .gba asset, SHA-256 and direct link are supplied.
2. **Given** a build or upload failure, **When** a status is reported, **Then** the last verified ROM and precise blocker are explicit.

### User Story 3 — Resume with fewer wasted credits (Priority P2)

As a returning AI agent, I want a concise handoff that identifies the exact next action, without repeating completed source work.

1. **Given** a halted task, **When** work resumes, **Then** the agent checks the current branch/head and the ledger before starting.
2. **Given** an already successful build, **When** only documents change, **Then** no redundant production build is required.

## Functional Requirements

- **FR-001**: Each risky code change MUST describe unchanged behaviour and regression tests before implementation.
- **FR-002**: Release evidence MUST distinguish coded, source-tested, compiled, emulator-tested, released and player-tested states.
- **FR-003**: The existing canonical build command and active CI workflow MUST remain authoritative.
- **FR-004**: Specs MUST reference current source files and active branch, not copy stale branch guidance blindly.
- **FR-005**: No permanent change to Pokémon IDs, event flags or save layout may be assumed compatible without evidence.

## Success Criteria

- **SC-001**: All changed gameplay behaviours in the next bounded feature have at least one explicit acceptance scenario and at least one preservation check.
- **SC-002**: Claimed ROM releases include an exact source commit, direct .gba URL, byte size and digest.
- **SC-003**: A new agent can identify the precise continuation from existing handoff and ledger without guessing a previous successful release.

## Out of scope

No current game-code modifications, build-workflow edits, emulator test runs or ROM releases are part of this setup specification.

## Assumptions

The existing PRU handoff, ledger and AGENTS.md remain operative; adoption is incremental. This draft is meant to be refined for the next actual PRU feature, not treated as evidence that a new gate has already been implemented.
