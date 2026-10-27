# Pokémon Rhythm Battle Backgrounds Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace PRU's active 38 Crystal Redux backgrounds with all 55 Rhythm entries while preserving static GBA-safe rendering.

**Architecture:** Introduce a 55-entry Rhythm image table and deterministic per-map/leader selection. Import 4bpp LZ77 assets from the verified donor extraction and trim unused offscreen tiles to fit VRAM; preserve the old assets only as a backup.

**Tech Stack:** C, Python 3, GBA LZ77, PRU/PJR decompilation, GitHub Actions.

**Spec:** `docs/superpowers/specs/2026-10-25-rhythm-battle-backgrounds-design.md`

## Global Constraints

- Exactly 55 source entries and 44 distinct visual sets; all 55 selectable.
- Palette 96 bytes; decompressed map 4096 bytes; tiles no more than 20480 bytes; visible scene 240×160 unchanged.
- Full static BG3 only; no extra entry overlays, HBlank split or black-square transition.
- Retain fallback behavior for link, Frontier and forced environments.

## Review Focus

- Highest-detail scenes (Rhythm 43, 49, 52) must not corrupt BG3 map memory.
- Duplicate donor entries must not waste binary space or disappear from the reachable index set.
- Gym rematch battles must choose the same unique scene as first encounters.
- Kyogre cave and Lavender Tower must not fall back to unrelated sunny backgrounds.
- Link/Frontier/forced test battles must retain the vanilla fallback.

---

### Task 1: Import and validate 55 GBA backgrounds

**Files:**
- Create: `tools/pru/import_rhythm_battle_backgrounds.py`
- Create: `graphics/battle_environment/rhythm/{00..54}/tiles.4bpp.lz`, `tilemap.bin.lz`, `palette_48colors.gbapal`
- Create: `tools/pru/check_rhythm_battle_backgrounds.py`
- Create: `docs/PRU_RHYTHM_BG_ASSET_PROVENANCE.md`

**Interfaces:**
- Consumes: verified extracted Rhythm assets from this task's local `background_comparison/rhythm/raw` extraction.
- Produces: GBA-ready matching image tiles, 4096-byte tilemaps, 96-byte palettes for indices 00–54.

- [ ] Write a failing test validating 55 backgrounds, GBA sizes and pixel-exact viewport compatibility.
- [ ] Run it and confirm RED due to absent assets.
- [ ] Implement the deterministic importer/repacker; import and verify all 55 assets.
- [ ] Re-run the test; require green with index and pixel checks, then commit.

### Task 2: Switch runtime selection and CI to Rhythm

**Files:**
- Create: `src/data/pru_rhythm_gfx.h`, `src/data/pru_rhythm_bg_table.h`
- Modify: `src/graphics.c`, `src/battle_bg.c`, `tools/pru/check_crystal_battle_backgrounds.py`, `tools/pru/check_static_battle_backgrounds.py`, `.github/workflows/pru-clean-build.yml`
- Modify: `docs/pru_crystal_redux_38_battle_backgrounds.md` (mark historical)

**Interfaces:**
- Consumes: the 55 assets produced by Task 1.
- Produces: `sPruRhythmBattleBgs[55]` and deterministic battle/Gym selection in `src/battle_bg.c`.

- [ ] Extend the failing test to require a linked 55-entry table, all 55 reachable and 16 distinct Gym mappings; run RED.
- [ ] Introduce Rhythm data pointers and replace the active Crystal selections with themed Rhythm pools and scripted exceptions.
- [ ] Keep static intro, link/Frontier and forced fallback unchanged; adapt historic archive checks and add the new test to CI.
- [ ] Run focused tests plus affected regression tests and require green, then commit.
- [ ] Push feature branch and verify GitHub Actions' actual ROM build/artifact; if it fails, fix, recommit and rebuild before declaring completion.
