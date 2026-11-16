# All Pokémon project work — 16 November 2026

## Backup status: VERIFIED / REMAINING

**Verified safely stored**
- PRR: [full source branch / PR inventory](https://github.com/jamesthoward2112-tech/Pokemon-Radical-Relics/blob/backup/prr-all-work-20261116/docs/backups/2026-11-16_ALL_PRR_WORK.md), covering 22 PRs and 40 date-stamped GitHub branches. Protected backup branch rooted in `integration/prr-protected-branch-reconciliation-20261116`.
- PRU: Original Alpha 5 source branch `release/pru-alpha5-source-20261112` untouched.
- Noxichu follower and Mootiny conversation assets: verified ZIP of 55 files saved to ChatGPT Library at `/Pokemon Project Backups/2026-11-16/Conversation_Assets_16Nov2026.zip` (ZIP SHA256 `ed68f1b94476bc6a94a7b541b61639e68903abd482ad679ac075d7e2ed1cf210`).
- A **no-login** NucBox backup script: [backup_all_pokemon_work_20261116.sh](../../tools/pru/backup_all_pokemon_work_20261116.sh).

**Still requiring transfer from NucBox**
- Full PRU Alpha 5 follower/Mootiny development source, latest locally compiled ROM and all intermediate test builds.
- Any NucBox-only source or graphics changed today for PRR or PRU2.
- This protected branch contains a recovery tool, but is **not** proof that the latest local source was pushed.

**Other services requiring their own export**
- ChatGPT Sites: RelicDex and RadicalRelicDex website source/builds.
- Notion: PRU/PRR development plans and the latest Evolution Master Plan.
- Local-only image files not already in ChatGPT Library, if any.

## Final PRU test configuration

- Only the leading Pikachu/Noxichu may follow; option available in the party menu.
- Noxichu has 32×32 overworld canvases with approved small 19×17 front/back graphics, 25×19 side views, one-tile following, and direction-correct static idle.
- Mootiny front/back, lowered battle view and matching party icon retained.
- **Tor excluded from PRU** (belongs to PRR); Kablowfish's original graphics restored.
- No changes to PRU master, PRR or PRU2 from the follower tests.
- The local compiled one-tile/static-idle ROM was not finally verified for the three published Alpha 5 binary learnset patches before access was interrupted.

## Auth-free NucBox archive instructions

On the NucBox, run this single PowerShell command:

```powershell
wsl -d Ubuntu -- bash -lc 'curl -fsSL https://raw.githubusercontent.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/backup/pru-alpha5-follower-recovery-20261116/tools/pru/backup_all_pokemon_work_20261116.sh | bash'
```

It creates five .tar.gz archives, a local compiled .gba, and SHA256SUMS.txt under `C:\Users\HowardGMKtec\Downloads\Pokemon_ALL_Work_20261116\`. It does not require logging into GitHub, and does not overwrite any working project directories.

**The local archive is not an off-device backup until the generated files are uploaded to ChatGPT or a remote destination and verified.** Upload them to the chat so this backup branch can be populated and a GitHub Actions ROM build can be set up.

## PRR scope preserved

254 Kanto-family species; forms/ecology and acquisition; evolution rule audit, sprites, abilities, custom moves and learnsets; Oak starter/fossil displays, Set/nickname defaults, gyms/Great Badge Heist rosters and rewards, global NPC starter exclusion, rival Arcaflare progression, Mewduo fusion design, trainers/dialogue audit, and RadicalRelicDex numbering/mapping. PRR workstreams remain protected and unmerged.
