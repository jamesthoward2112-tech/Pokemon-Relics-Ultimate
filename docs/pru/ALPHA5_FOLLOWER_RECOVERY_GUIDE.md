# PRU Alpha 5 — emergency follower-source recovery

This branch was created **16 November 2026** from `release/pru-alpha5-source-20261112`. It deliberately does **not** overwrite Alpha 5, PRR or PRU2.

## Status

The newer test source on NucBoxG2 is at:
`/home/james/pru-patchbuild/alpha5-noxichu-one-tile-static-idle-20261116`

The original Alpha 5 GitHub branch does not yet include the recent follower integration. **This backup branch initially contains only the recovery script. The finished source is not backed up until the script reports SOURCE BACKUP COMPLETE.**

The newest source was compiled locally, but the final binary-patch verification and upload were interrupted by the Remote Desktop Commander usage limit. Do not describe that ROM as fully verified or published.

## One-time backup from the NucBox

Open **Windows Terminal / PowerShell** on NucBoxG2. Paste:

```powershell
wsl -d Ubuntu -- bash -lc 'curl -fsSL https://raw.githubusercontent.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/backup/pru-alpha5-follower-recovery-20261116/tools/pru/recover_nucbox_follower_to_github.sh | bash'
```

This uses the installed Ubuntu WSL and the existing Git checkout. It verifies the final one-tile/static-idle source, creates a *separate* temporary Git worktree, copies only the scoped follower/Mootiny source and graphics, and pushes a commit to this recovery branch. The original working directory and ROM are left intact.

If you are prompted to sign in to GitHub, authenticate with the account that owns this repository. If the command prints an error, do not delete or reset any folders; report the exact error.

## Source validation and outstanding work

- Only Pikachu and Noxichu in slot 1 may follow.
- Noxichu uses the approved smaller front/back and side views.
- One-tile distance restored; standing direction animation at idle, normal steps while moving.
- Mootiny front/back and party icon retained.
- Tor excluded from PRU; Kablowfish original graphics restored.
- **Still required:** GitHub Actions compilation of the recovered source, preserve/reapply the three previously published Alpha 5 binary learnset changes, and emulator testing of idle, walking, doors, warps, party order and Noxichu evolution.

**Do not merge into Alpha 5 master until all tests pass.**
