# PRU custom back-sprite grounding implementation plan

> For agentic workers: use the existing PRU canonical build; no replacement ROM baseline.

**Goal:** Move Khang and every other original zero-offset custom back sprite down, leaving already tuned offsets unchanged.

**Architecture:** The GBA engine reads back-sprite Y placement from species-info records. Update only the 44 zero-valued PRU/PJR custom species entries across the two live species-info headers. Preserve the 12 pre-existing nonzero settings, the underlying PNG assets, trainer-only E4 visual forms, and all front sprites.

**Tech stack:** C species-info headers, Python 3 source-data regression, GitHub Actions canonical ROM compiler.

**Spec:** James Howard's 24 October 2026 request in PRU: "Khang needs his back sprite moved down... ALL custom evolutions need the same treatment ... except the ones we've already altered."

## Task 1 — Failing source regression
- [x] Inspect PJR macro definitions, PRU custom records, historical tuned offsets.
- [x] Reproduce 44 failures against the current main source (Khang backY=0).
- [ ] Add `tools/pru/check_custom_back_sprite_offsets.py`: expect +6 for the 44 formerly-zero entries, exact values for the 12 preserved entries, unchanged E4 trainer-only forms.

## Task 2 — Small source fix and canonical build
- [ ] Change the zero back-sprite Y values in `src/data/pokemon/species_info/pjr_families.h` and `pru_custom.h` to 6; leave nonzero values untouched.
- [ ] Run regression in `.github/workflows/pru-clean-build.yml`.
- [ ] Commit atomically on current main head, verify SHA and GitHub Action.
- [ ] Verify successful source tests, 32 MiB ROM and direct GBA release; playtest sprite positioning in-game.
