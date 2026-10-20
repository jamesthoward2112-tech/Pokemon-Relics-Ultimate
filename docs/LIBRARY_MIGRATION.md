# PRU migration: ChatGPT Library → GitHub

**Status: In progress, 20 October 2026.** The source snapshot has been imported to this repo, but the hundreds of Pokémon Library files have **not** all been uploaded. This is a provenance and migration ledger, not a claim of full completion.

## Canonical sources of truth

- **Approved design / decisions:** [Notion — PRU Development and Sprite Decisions (17–20 Oct)](https://app.notion.com/p/3ff4939d4316814e9b74c8508d790925).
- **Species roster:** [Notion — PRU National Pokédex (444)](https://app.notion.com/p/3fb4939d431681e58608e3f1acf41296).
- **Moves / sprites / evolution details:** [Notion — PRU Canonical Pokémon Data](https://app.notion.com/p/3fb4939d431681afa46fdeb97cf8c79b).
- **Battle transitions:** [Notion — PRL Duo Battle Transitions](https://app.notion.com/p/3f64939d4316812bb512cfb8d391f898).
- **Tested implementation:** commits, action logs, source audits, compiled GBA and user save QA. A design decision is not proof that code is present or working.

## Source migration

Completed: source snapshot of the PRU Bell Tower integration branch in `main`, excluding old actions, binary ROMs, saves, and original README.

Reference upstream: `jamesthoward2112-tech/Pokemon-Johto-Relics`, branch `pru/bell-tower-final-rocket-lv58-20261020`, SHA `6f26a381a13821fd63688cd53dd59de682148bab`. This branch descends from eight-badge polish through Kimono art. **Full clean ROM build in this new repo is still unverified.**

## Library inventory (initial scan)

| Library folder | Files seen | Migration status |
|---|---:|---|
| /Pokémon Relics Ultimate | 42 | Pending review / import |
| /PRU | 10 | Pending review / import |
| /Pokémon Relic Legacy | 82 | Pending review / import |
| /Pokémon Johto Relics | 127 | Pending review / import |
| /PJR | 9 | Pending review / import |
| /Project Hoenn Relics | 161 | Pending review / import |
| /Project Kanto Relics | At least 176 | Initial listing paginated; not yet exhaustive |
| /Relics Shared Assets | 29 | Pending review / import |
| /Pokemon Sprite Libraries | 21 | Pending review / import |
| /_PHR_TEMP | 2 | Pending review; likely working scratch |
| Root-level Pokémon uploads | Not counted | Needs title/type classification; mixed with unrelated files |
| Library Archive and other subfolders | Not counted | Inspect for Pokémon assets and duplicate files |

Inventory counts are **preliminary file counts**, not unique files and not proof that files are ready for use. Check duplicates by SHA-256 and prefer newest explicitly approved source.

## High-priority original missing graphics

The original approved PRL transition package **exists in the ChatGPT Library**:

`/Pokémon Relic Legacy/Generated Assets/Battle Transitions/PRL_Duo_Animated_Trainer_Transitions_GBA_Assets_20261011.zip`

Also available:
- `PRL_Battle_Transitions_Integration.md`
- `Jessie_James_GBA_240x160.png`
- `Steevee_Neevee_GBA_240x160.png`
- PRL animated GIF/MP4 previews

The ZIP contains original palette, 4bpp tile atlas and BG tilemap data for **both** approved trainer introductions. Original archive subfolder names `jessie_james` and `steevee_neevee` must be carefully matched to current source paths `jessie_james` and `eevee_twins`. **Do not redraw or replace with placeholder art.** These binary assets still need to be imported, then built and tested.

## Migration policy

1. `graphics/`, `data/`, `src/`, `sound/`, `tools/`, `assets/`: current approved, appropriately attributed source assets used by PRU.
2. `docs/`: design specs, sprite/manifests, migration ledgers and source provenance, linked to current Notion pages.
3. `reference/` or a separately scoped archive repository: legacy materials needed for provenance, not duplicated executable engine trees in the PRU build root.
4. **Never publicly commit private player `.sav` files, personal test data, or original commercial `.gba` base ROMs**. Keep user save backups outside the public repository. Preserve playable directly downloadable PRU build artifacts only after confirming publication rights and build/tests.
5. Third-party donor sprites, source or patches must retain attribution and have redistribution permission reviewed. A file in ChatGPT Library is not automatically safe for public GitHub publication.
6. Keep unused WIP graphics or superseded variants in an archive, not active sprite lookup paths. The newest *approved* graphics supersede older versions; Notion provides decisions, Git commits verify implementation.
7. New builds must work from fresh checkout of this one repository, have green CI, produce a raw `.gba`, and state user-save QA separately.

## Migration acceptance gate

- [x] Master PRU GitHub repository exists
- [x] One canonical PRU source snapshot imported into `main`
- [x] Found exact original approved PRL duo-intro Library asset package
- [ ] Import the approved original missing battle transition assets (binary)
- [ ] Check source against current Notion decisions and import any newer missing branches / approved art
- [ ] Exhaustively inventory Library assets, classify provenance and deduplicate
- [ ] Restore original credits, attribution and licenses; resolve permission concerns
- [ ] Full clean `make hns` + source tests + mGBA boot from master repo
- [ ] Release direct `.gba` from master repo after build validation
- [ ] User-save playthrough verifies Rocket Bell Tower, Kimono battles, artwork and other current fixes

**Do not delete original Library items** until their SHA-256-matched replacements are safely stored, reviewed and backed up on GitHub.
