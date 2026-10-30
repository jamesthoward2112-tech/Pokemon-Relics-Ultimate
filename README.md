# Pokémon Relics Ultimate (PRU)

Canonical C/GBA project for the standalone Johto + Kanto game, built from the
HnS / Johto Relics engine with selectively imported Relic Legacy artwork and features.

## Current state (2026-10-30)
PRU has actual compiled and downloadable .gba prereleases; it is not an empty bootstrap.
The approved roster is **exactly 450 species**, final three Rhyperior, Magmortar and Electivire.
Main is not necessarily the latest feature source: PR #66 stacks on #65 and the
permanent-form work, while other open branches contain newer E20/tutor/Mewduo work.

Start with [PRU_HANDOFF.md](PRU_HANDOFF.md), [AGENTS.md](AGENTS.md) and
[docs/PRU_RELEASE_LEDGER.md](docs/PRU_RELEASE_LEDGER.md).
See [GitHub Releases](https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/releases)
for actual release assets; a passing source check is not proof of player-tested gameplay.

Canonical build: `make hns -j2 -O` generates `pokehns.gba`.
Existing CI donor-art imports still mutate the checkout; migration to immutable
hash-pinned approved art is planned but must not break working source.
