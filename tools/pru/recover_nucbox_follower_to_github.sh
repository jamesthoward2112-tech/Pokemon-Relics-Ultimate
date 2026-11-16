#!/usr/bin/env bash
# One-time PRU Alpha 5 follower source backup from the user's NucBoxG2.
# Safely stages a SEPARATE worktree. Does not edit original source or master.
set -euo pipefail

SOURCE="${PRU_SOURCE_PATH:-/home/james/pru-patchbuild/alpha5-noxichu-one-tile-static-idle-20261116}"
STAGING="${PRU_STAGING_PATH:-/home/james/pru-patchbuild/github-rescue-alpha5-follower-20261116}"
REPO_URL="https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate.git"
BRANCH="backup/pru-alpha5-follower-recovery-20261116"

echo "Checking the exact local PRU Alpha 5 follower test source..."
test -f "$SOURCE/src/event_object_movement.c" || { echo "MISSING SOURCE: $SOURCE"; exit 2; }
test -s "$SOURCE/graphics/pokemon/prl_authoritative/noxichu/follower.4bpp" || { echo "MISSING FOLLOWER ART"; exit 2; }
test "$(stat -c%s "$SOURCE/graphics/pokemon/prl_authoritative/noxichu/follower.4bpp")" -eq 4096
test -f "$SOURCE/pokehns.gba" || { echo "MISSING LOCAL COMPILED ROM"; exit 2; }
grep -Fq "for (i = 0; i < 1; i++)" "$SOURCE/src/event_object_movement.c" || { echo "LEAD-ONLY FIX MISSING"; exit 2; }
grep -Fq "if (OW_SPECIES(objectEvent) == SPECIES_NOXICHU)" "$SOURCE/src/event_object_movement.c" || { echo "STATIC-IDLE FIX MISSING"; exit 2; }
if grep -Fq "if (dx + dy <= 2)" "$SOURCE/src/event_object_movement.c"; then
    echo "TWO-TILE FOLLOWING STILL ACTIVE. WRONG SOURCE COPY; STOPPED."
    exit 2
fi
if ! git -C "$SOURCE" rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    echo "Local test source has no Git metadata; cannot safely stage and push."
    exit 2
fi
if test -e "$STAGING"; then
    echo "Staging folder already exists: $STAGING"
    echo "Nothing overwritten. Check for an existing completed backup."
    exit 3
fi

echo "Fetching the GitHub rescue branch..."
git -C "$SOURCE" fetch --no-tags "$REPO_URL" "refs/heads/$BRANCH"
HEAD_SHA="$(git -C "$SOURCE" rev-parse FETCH_HEAD)"
git -C "$SOURCE" worktree add --detach "$STAGING" "$HEAD_SHA"

files=(
    "src/event_object_movement.c"
    "src/option_menu.c"
    "src/new_game.c"
    "src/party_menu.c"
    "src/overworld.c"
    "src/pokemon.c"
    "src/pokemon_icon.c"
    "src/data/pokemon/species_info/pjr_families.h"
    "src/data/object_events/object_event_pic_tables_followers.h"
    "graphics/pokemon/prl_authoritative/noxichu/follower.4bpp"
    "graphics/pokemon/prl_authoritative/noxichu/follower.4bpp.smol"
    "graphics/pokemon/prl_authoritative/noxichu/follower.gbapal"
    "graphics/pokemon/prl_authoritative/mootiny/front.png"
    "graphics/pokemon/prl_authoritative/mootiny/back.png"
    "graphics/pokemon/prl_authoritative/mootiny/icon.png"
    "graphics/pokemon/prl_authoritative/mootiny/normal.pal"
    "graphics/pokemon/prl_authoritative/mootiny/shiny.pal"
)

for file in "${files[@]}"; do
    test -f "$SOURCE/$file" || { echo "STOPPED: required file missing: $file"; exit 4; }
    mkdir -p "$STAGING/$(dirname "$file")"
    cp -p "$SOURCE/$file" "$STAGING/$file"
done

mkdir -p "$STAGING/docs/pru"
{
    echo "# PRU Alpha 5 follower recovery snapshot"
    echo ""
    echo "Original local source: $SOURCE"
    echo "Only the lead Pikachu or Noxichu may follow."
    echo "Noxichu: approved 19x17 front/back, original side views, one-tile distance and static facing idle."
    echo "Mootiny approved. Tor excluded; Kablowfish originals restored."
    echo "Original Alpha 5, PRR and PRU2 unchanged."
    echo ""
    echo "Local compiled ROM SHA256 (not stored in Git source history):"
    sha256sum "$SOURCE/pokehns.gba"
    echo ""
    echo "BUILD NOTE: verify the three previously published Alpha 5 binary learnset fixes"
    echo "before shipping. A successful compile alone does not verify them."
} > "$STAGING/docs/pru/ALPHA5_FOLLOWER_NUCBOX_RECOVERY.md"

git -C "$STAGING" add -f -- "${files[@]}" docs/pru/ALPHA5_FOLLOWER_NUCBOX_RECOVERY.md
git -C "$STAGING" diff --cached --check
if git -C "$STAGING" diff --cached --quiet; then
    echo "Already identical to GitHub recovery branch."
    exit 0
fi
git -C "$STAGING" \
    -c user.name="PRU source recovery" \
    -c user.email="github-actions[bot]@users.noreply.github.com" \
    commit -m "backup(pru): recover Alpha 5 Noxichu follower and Mootiny approved assets"

echo "Pushing source changes to GitHub (may request sign-in)..."
git -C "$STAGING" push "$REPO_URL" "HEAD:refs/heads/$BRANCH"
echo "SOURCE BACKUP COMPLETE"
echo "https://github.com/jamesthoward2112-tech/Pokemon-Relics-Ultimate/tree/$BRANCH"
echo "Compiled ROM still stored locally: $SOURCE/pokehns.gba"
