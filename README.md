# Pokémon Relics Ultimate (PRU)

**Canonical source repository for Pokémon Relics Ultimate.**

This project unifies the Johto/Kanto world and HNS engine from Pokémon Johto Relics, updated Pokémon/moves/abilities and custom content from Pokémon Relic Legacy, and approved components from Kanto and Hoenn Relics.

## Status
**Source consolidation in progress; no verified playable ROM from this repository yet.**

The first import will use the existing working PRU development source. A clean compilation and assets audit must pass before any PRU release is considered ready. Missing custom graphics will **not** be silently replaced with placeholders.

## Development contract
- `main` is the PRU integration branch (not PJR main).
- Source changes land through reviewed changes, with a green build check.
- Each released build is a direct `.gba` file; no ZIP-only deliveries.
- Approved original sprites and effects take precedence over inferred substitutes.
- All Gen 1–3 plus PRU-approved custom species only; target Pokédex 444.
- Preserve legacy reference repositories; the PRU build itself must not require their checkouts.

## Source inventory
- [Pokémon Johto Relics](https://github.com/jamesthoward2112-tech/Pokemon-Johto-Relics) — current engine, Johto/Kanto map and event baseline, PRU in-progress branches.
- [Pokémon Relic Legacy](https://github.com/jamesthoward2112-tech/Pokemon-Relic-Legacy) — later sprites/moves/abilities and reference implementations.
- [Pokémon Hoenn Relics](https://github.com/jamesthoward2112-tech/Pokemon-Hoenn-Relics) — Hoenn Relics and reference content.
- Pokémon Kanto Relics and additional donor repositories — to identify and audit; do not treat as build dependencies.

See `docs/PRU_MIGRATION.md` for the provenance and missing-asset ledger after bootstrap.
