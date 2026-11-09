# SpriteCook → PRU original artwork sync

GitHub Actions runs `.github/workflows/spritecook-sync.yml` every 15 minutes
(and on manual **Run workflow**). It reads recent SpriteCook assets and saves
the original pixel-art PNGs to `assets/spritecook/incoming/<asset-id>.png`.
Files already saved are never overwritten. This does not replace ROM graphics.

## One-time activation

1. At [SpriteCook API Keys](https://app.spritecook.ai/api-keys), create a key
   with only `read_assets` scope.
2. In GitHub, open repository **Settings → Secrets and variables → Actions**.
3. Create a **repository secret** named exactly `SPRITECOOK_API_KEY`.
   Paste the SpriteCook key as the secret value.
4. Open **Actions → Sync SpriteCook originals → Run workflow**, or let the
   next scheduled run execute.

The Actions secret is never committed or printed. If the secret is absent, the
workflow skips importing and prints activation instructions.

The importer checks up to the latest 50 assets per run; create a separate
backfill process for older assets beyond that window. Image downloads do
not use SpriteCook generation credits. Sync frequency is subject to GitHub
Actions scheduling delays. The images may need further manual work to
make GBA back sprites or enforce 16-colour palettes.

For security, never store API keys in repository files or commit history.
