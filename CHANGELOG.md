# Pokeemerald-Expansion Changelogs

## 1.10.x
- **[Version 1.10.2](docs/changelogs/1.10.x/1.10.2.md) - 🧹 Bugfix Release**
- **[Version 1.10.1](docs/changelogs/1.10.x/1.10.1.md) - 🧹 Bugfix Release**
- **[Version 1.10.0](docs/changelogs/1.10.x/1.10.0.md) - ✨ Feature Release**

## 1.9.x
- **[Version 1.9.4](docs/changelogs/1.9.x/1.9.4.md) - 🧹 Bugfix Release**
- **[Version 1.9.3](docs/changelogs/1.9.x/1.9.3.md) - 🧹 Bugfix Release**
- **[Version 1.9.2](docs/changelogs/1.9.x/1.9.2.md) - 🧹 Bugfix Release**
- **[Version 1.9.1](docs/changelogs/1.9.x/1.9.1.md) - 🧹 Bugfix Release**
- **[Version 1.9.0](docs/changelogs/1.9.x/1.9.0.md) - ✨ Feature Release**

## 1.8.x
- **[Version 1.8.6](docs/changelogs/1.8.x/1.8.6.md) - 🧹 Bugfix Release**
- **[Version 1.8.5](docs/changelogs/1.8.x/1.8.5.md) - 🧹 Bugfix Release**
- **[Version 1.8.4](docs/changelogs/1.8.x/1.8.4.md) - 🧹 Bugfix Release**
- **[Version 1.8.3](docs/changelogs/1.8.x/1.8.3.md) - 🧹 Bugfix Release**
- **[Version 1.8.2](docs/changelogs/1.8.x/1.8.2.md) - 🧹 Bugfix Release**
- **[Version 1.8.1](docs/changelogs/1.8.x/1.8.1.md) - 🔥 HOTFIX Release**
- **[Version 1.8.0](docs/changelogs/1.8.x/1.8.0.md) - ✨ Feature Release**

## 1.7.x
- **[Version 1.7.4](docs/changelogs/1.7.x/1.7.4.md) - 🧹 Bugfix Release**
- **[Version 1.7.3](docs/changelogs/1.7.x/1.7.3.md) - 🧹 Bugfix Release**
- **[Version 1.7.2](docs/changelogs/1.7.x/1.7.2.md) - 🧹 Bugfix Release**
- **[Version 1.7.1](docs/changelogs/1.7.x/1.7.1.md) - 🧹 Bugfix Release**
- **[Version 1.7.0](docs/changelogs/1.7.x/1.7.0.md) - ✨ Feature Release**

## 1.6.x
- **[Version 1.6.2](docs/changelogs/1.6.x/1.6.2.md) - 🧹 Bugfix Release**
- **[Version 1.6.1](docs/changelogs/1.6.x/1.6.1.md) - 🔥 HOTFIX Release**
- **[Version 1.6.0](docs/changelogs/1.6.x/1.6.0.md) - ✨ Feature Release**

## 1.5.x
- **[Version 1.5.3](docs/changelogs/1.5.x/1.5.3.md) - 🔥 HOTFIX Release**
- **[Version 1.5.2](docs/changelogs/1.5.x/1.5.2.md) - 🧹 Bugfix Release**
- **[Version 1.5.1](docs/changelogs/1.5.x/1.5.1.md) - 🧹 Bugfix Release**
- **[Version 1.5.0](docs/changelogs/1.5.x/1.5.0.md) - ✨ Feature Release**

## 1.4.x
- **[Version 1.4.3](docs/changelogs/1.4.x/1.4.3.md) - 🧹 Bugfix Release**
- **[Version 1.4.2](docs/changelogs/1.4.x/1.4.2.md) - 🧹 Bugfix Release**
- **[Version 1.4.1](docs/changelogs/1.4.x/1.4.1.md) - 🔥 HOTFIX Release**
- **[Version 1.4.0](docs/changelogs/1.4.x/1.4.0.md) - ✨ Feature Release**

## 1.3.x
- **[Version 1.3.0](docs/changelogs/1.3.x/1.3.0.md) - ✨ Feature Release**

## 1.2.x
- **[Version 1.2.0](docs/changelogs/1.2.x/1.2.0.md) - ✨ Feature Release**

## 1.1.x
- **[Version 1.1.1](docs/changelogs/1.1.x/1.1.1.md) - 🧹 Bugfix Release**
- **[Version 1.1.0](docs/changelogs/1.1.x/1.1.0.md) - ✨ Feature Release**

## 1.0.x
- **[Version 1.0.0](docs/changelogs/1.0.x/1.0.0.md) - ✨ Feature Release**

## Pre-1.0.x:
- **[Version 0.9.0](docs/changelogs/0.9.x/0.9.0.md) - 🦕 Retroactive Version**
# Job 18 — final story, Golden Ho-Oh and Ancient Guardian Dragonite

- Oak's Elite 20 victory now reveals the Ultimate Ancient Relic without disclosing its location. The Ruins of Alph scientist directs the player to Mt Silver only after the final Elite 20 victory and all seven RELICS.
- Replaced the Tin Tower Kimono Girls' former Ho-Oh event with a retryable, non-catchable Level 60 Ancient Guardian Dragonite fight. Imported the approved Elite Redux Mega Dragonite front/back/icon assets as a trainer-only visual form, with the requested Multiscale / Weakness Policy battle build.
- Removed the Mt Silver Oak trainer battle. Oak's original dialogue now describes his obsession and failed attempt; he summons the only catchable Level 100 Golden Ho-Oh after the two story requirements. Defeat or escape permits retry; capture starts the existing Job 16 cinematic and Job 17 credits once.
- Updated the Mt Silver shortcut sign to `Shortcut to Top`. Kept the six one-time E20 Master Balls, existing Golden Reign / Phoenix Soul implementation, Red and save flags.
- Updated source regressions and the hosted clean-build workflow to include Job 18 checks and publish a clearly labelled Job 18 test release.

**Known limitation:** no pre-Dragonite playthrough save was present in the accepted source or attached files. This change does not fabricate a `.sav`; a genuine mGBA-created pre-battle save remains outstanding. The hosted build and emulator results are recorded in the Job 18 ledger once the workflow completes.
