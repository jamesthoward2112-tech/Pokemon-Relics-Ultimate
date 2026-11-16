#!/usr/bin/env bash
# Full local backup for PRU, PRR and PRU2 (16 November 2026).
# Read-only to existing projects; no GitHub authentication needed.
set -Eeuo pipefail
export LC_ALL=C
DAY='2026-11-16 00:00:00'
WIN='/mnt/c/Users/HowardGMKtec'
OUT="$WIN/Downloads/Pokemon_ALL_Work_20261116"
ROOT='/home/james/pru-patchbuild'
LATEST="$ROOT/alpha5-noxichu-one-tile-static-idle-20261116"
mkdir -p "$OUT"
exec > >(tee -a "$OUT/BACKUP_LOG.txt") 2>&1
echo "BACKUP START $(date -u +%FT%TZ)"
test -f "$LATEST/src/event_object_movement.c" || { echo "ERROR: latest PRU source not found"; exit 2; }
grep -Fq 'if (OW_SPECIES(objectEvent) == SPECIES_NOXICHU)' "$LATEST/src/event_object_movement.c" || { echo "ERROR: latest idle fix missing"; exit 2; }
if grep -Fq 'if (dx + dy <= 2)' "$LATEST/src/event_object_movement.c"; then echo "ERROR: outdated two-tile source"; exit 2; fi
echo "Verified latest PRU source and one-tile follower code."

echo "1/5 Complete latest PRU source"
tar -czf "$OUT/01_PRU_LATEST_ALPHA5_SOURCE.tar.gz" -C "$ROOT" \
  --exclude='*/.git' --exclude='*/.git/*' --exclude='*/build/*' --exclude='*/obj/*' \
  --exclude='*/node_modules/*' --exclude='*/__pycache__/*' \
  --exclude='*.o' --exclude='*.d' --exclude='*.elf' --exclude='*.map' \
  --exclude='*.gba' --exclude='*.sav' alpha5-noxichu-one-tile-static-idle-20261116

echo "2/5 Other PRU source edits today"
(
 cd "$ROOT"
 find . -type f -newermt "$DAY" \
  ! -path './alpha5-noxichu-one-tile-static-idle-20261116/*' \
  ! -path '*/.git/*' ! -path '*/build/*' ! -path '*/obj/*' \
  ! -name '*.o' ! -name '*.d' ! -name '*.elf' ! -name '*.gba' \
  \( -path '*/src/*' -o -path '*/graphics/*' -o -path '*/include/*' -o -name '*.py' -o -name '*.sh' -o -name '*.json' -o -name '*.md' \) -print0 |
  tar -czf "$OUT/02_PRU_OTHER_SOURCE_CHANGES.tar.gz" --null -T -
)
echo "3/5 Today's ROMs, sprites, scripts and reports from Windows Downloads"
(
 cd "$WIN/Downloads"
 find . -maxdepth 1 -type f -newermt "$DAY" \
  -regextype posix-extended \
  -iregex '.*/(pru|prr|pokemon|relic|noxi|mooti|tor_|gemlin|sprite|alpha5|elite|radical).*' -print0 |
  tar -czf "$OUT/03_WINDOWS_DOWNLOADS_PROJECT_OUTPUTS.tar.gz" --null -T -
)
echo "4/5 Documents/RelicDev/PRR/PRU2 edited files"
(
 cd "$WIN/Documents"
 {
  if test -d RelicDev; then
   find RelicDev -type f -newermt "$DAY" ! -path '*/.git/*' ! -path '*/build/*' ! -name '*.o' -print0
  fi
  find . -maxdepth 2 -type d \
   \( -iname 'PRR*' -o -iname 'PRU*' -o -iname '*Pokemon*' -o -iname '*Relic*' \) \
   ! -path './RelicDev*' -print0 |
   while IFS= read -r -d '' d; do
    find "$d" -type f -newermt "$DAY" ! -path '*/.git/*' ! -path '*/build/*' ! -name '*.o' -print0
   done
 } | sort -zu | tar -czf "$OUT/04_DOCUMENTS_POKEMON_PROJECT_CHANGES.tar.gz" --null -T -
)
echo "5/5 Other WSL Pokémon project edits today"
(
 cd /home/james
 find . -maxdepth 3 -type d \
  \( -iname '*prr*' -o -iname '*pru2*' -o -iname '*pokemon*' -o -iname '*relic*' \) \
  ! -path './pru-patchbuild*' -print0 |
  while IFS= read -r -d '' d; do
   find "$d" -type f -newermt "$DAY" ! -path '*/.git/*' ! -path '*/build/*' ! -name '*.o' -print0
  done | sort -zu | tar -czf "$OUT/05_WSL_OTHER_POKEMON_PROJECT_CHANGES.tar.gz" --null -T -
)
if test -f "$LATEST/pokehns.gba"; then
 cp -p "$LATEST/pokehns.gba" "$OUT/PRU_ALPHA5_LATEST_LOCAL_COMPILED_UNVERIFIED.gba"
fi
{
 echo "Backup created $(date -u +%FT%TZ)"
 echo "Latest source $LATEST"
 git -C "$LATEST" rev-parse HEAD 2>/dev/null || true
 git -C "$LATEST" status --short 2>/dev/null | head -120 || true
 find /home/james -maxdepth 3 -type d \
  \( -iname '*prr*' -o -iname '*pru*' -o -iname '*pokemon*' -o -iname '*relic*' \) 2>/dev/null | head -180
} > "$OUT/WORKSPACE_GIT_INVENTORY.txt"
(
 cd "$OUT"
 sha256sum -- *.tar.gz *.gba > SHA256SUMS.txt
 ls -lh -- *.tar.gz *.gba SHA256SUMS.txt > FILE_INDEX.txt
)
echo "LOCAL_BACKUP_PACKAGE_COMPLETE"
echo "Folder: $OUT"
echo "Upload all .tar.gz files, the .gba and SHA256SUMS.txt to ChatGPT."
echo "These archives are LOCAL only until uploaded and checked remotely."
