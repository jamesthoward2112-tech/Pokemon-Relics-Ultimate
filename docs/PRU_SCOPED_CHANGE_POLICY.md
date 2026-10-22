# PRU scoped-change and regression protection policy

Status: **effective immediately for every new change** (2026-10-22).  
Scope: Pokémon Relics Ultimate (PRU), GitHub source, CI builds, and published GBA ROMs.

## One request = one narrow source change

The last **verified playable ROM** is the baseline. Record its release URL, complete commit SHA and ROM SHA-256, then branch from **that exact source** (or document why a newer verified commit is required). Never substitute an older donor repo or an untested mixture of branches.

Example: "ROM X is fine; give Misty a Squirtle; change nothing else."

For that request:
- Touch only the file(s) defining Misty's intended team plus a relevant targeted test when needed.
- Do not change trainers elsewhere, Rocket or Steevee/Neevee art, sprite positions, party icons, title graphics, encounters, balance, evolutions, maps or battle effects.
- Inspect the full source diff before merging. If any unrelated file changes, remove it or explain an essential dependency and get explicit approval first.
- Use read-only tests for the changed feature and essential global invariants (notably the approved **444 species**). Tests may inspect unrelated features, but must **not reimport or rewrite** their assets.
- Compile and verify a complete GBA ROM. Preserve the previous verified release for instant rollback.
- Never claim a ROM is done from a source commit or green test alone: confirm ROM artifact, SHA-256, and relevant gameplay validation. Report emulator-only checks as unverified if not performed.

## Approved content is locked

Treat working Jessie & James; Steevee & Neevee; Chansey Twins; custom species art; all icon palettes and sprite coordinates; Jirachi/Astrachi; and every accepted feature as **immutable by default**. Do not replace an asset from PJR, PRL, TRE or Insurgence merely because an installation script exists. Only deliberately modify it in a separately scoped change.

If a feature needs alteration to implement another, explain the required dependency and test both features; do not silently expand scope.

## Build process: required migration

The current `.github/workflows/pru-clean-build.yml` still performs historical source-changing asset restorations and overlays. **They are legacy build prerequisites, not permission to change established content.** Do not just delete them until all generated assets, needed binary inputs and source overlays have been migrated and a clean-source compile has passed.

Migration plan:
1. Identify the build-time mutations from each install/restore script by auditing generated checkout changes and ignored files.
2. Check in or reproducibly pin the *approved, currently verified* assets and source patches (never blindly use older donors). Record per-asset origin/hash and approved positional/palette details.
3. Separate the optional, explicit **asset-import/migration** operation from the default **compile/test/release** job. Normal ROM builds must use committed canonical inputs and never re-fetch or overwrite working sprites or unrelated source.
4. Fail default builds on unexpected source changes during preparation. Keep cacheable toolchain installation and unrelated **read-only** regression checks; only changed artifacts need generation.
5. Verify the new clean build against a known playable baseline (including sprite alignment, white/transparency, party icons, boss encounters and 444-species constraints) before retiring the old steps.

Until migration is completed, review and disclose the **effective build-time mutations** as well as the committed PR diff. A narrow Git diff alone is not sufficient if CI alters the checkout.

## Release acceptance checklist

- [ ] Exact baseline source and playable ROM identified; last working version remains downloadable.
- [ ] Scope and touched paths described; unrelated game systems unchanged.
- [ ] All changed files reviewed; expected generated/CI mutations reviewed.
- [ ] Relevant read-only tests and full clean compile passed.
- [ ] Direct `.gba` artifact and checksum published; emulator/gameplay testing status stated.
- [ ] No release replaces the previously approved ROM before it is verified.

Avoid frequent full-build runs for documentation-only edits; CI may skip changes limited to Markdown/docs while `workflow_dispatch` remains available.
