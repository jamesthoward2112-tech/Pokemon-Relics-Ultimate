#!/usr/bin/env python3
"""Sync existing SpriteCook images into PRU without modifying ROM artwork.

Requires SPRITECOOK_API_KEY with read_assets scope. This script only performs
GET requests to SpriteCook; it does not generate assets or spend credits.
"""
from __future__ import annotations

import io
import json
import os
import re
from pathlib import Path
from urllib.parse import quote, urlparse

import requests
from PIL import Image, UnidentifiedImageError

API = "https://api.spritecook.ai"
DEST = Path("assets/spritecook/incoming")
ID_PATTERN = re.compile(r"^[a-zA-Z0-9_-]{8,100}$")
MAX_BYTES = 24 * 1024 * 1024
TIMEOUT = 40


def get_json(url: str, key: str):
    response = requests.get(
        url, headers={"Authorization": f"Bearer {key}"}, timeout=TIMEOUT
    )
    response.raise_for_status()
    return response.json()


def as_assets(value):
    if isinstance(value, list):
        return value
    if isinstance(value, dict):
        for field in ("assets", "items", "results", "recent_assets", "data"):
            if field in value:
                try:
                    return as_assets(value[field])
                except ValueError:
                    pass
        if "id" in value or "asset_id" in value:
            return [value]
    raise ValueError("Unexpected SpriteCook recent-assets response")


def find_url(value):
    """Prefer cleaned pixel art over unprocessed/raw versions when available."""
    if not isinstance(value, dict):
        return None
    for field in ("pixel_url", "sprite_url", "image_url", "content_url", "url", "raw_url"):
        candidate = value.get(field)
        if isinstance(candidate, str) and candidate.startswith("https://"):
            return candidate
    for field in ("asset", "data", "metadata", "urls"):
        nested = find_url(value.get(field))
        if nested:
            return nested
    return None


def download(url: str, key: str):
    parsed = urlparse(url)
    if parsed.scheme != "https":
        raise ValueError("Refusing non-HTTPS image URL")
    # Never send our API key to a third-party host.
    use_auth = parsed.hostname == "api.spritecook.ai"
    headers = {"Authorization": f"Bearer {key}"} if use_auth else {}
    response = requests.get(url, headers=headers, timeout=TIMEOUT)
    response.raise_for_status()
    if len(response.content) > MAX_BYTES:
        raise ValueError("Artwork exceeds maximum allowed size")
    return response.content


def save_original(payload: bytes, target: Path):
    """Write only if content changed; preserve original PNG bytes exactly."""
    try:
        with Image.open(io.BytesIO(payload)) as image:
            image.load()
            if image.format == "PNG":
                actual_bytes = payload
            else:
                temp = io.BytesIO()
                image.convert("RGBA").save(temp, "PNG")
                actual_bytes = temp.getvalue()
    except (UnidentifiedImageError, OSError, ValueError) as exc:
        raise ValueError("Asset is not a supported image") from exc
    if target.exists() and target.read_bytes() == actual_bytes:
        return False
    target.write_bytes(actual_bytes)
    return True

def write_manifest():
    entries = []
    for path in sorted(DEST.glob("*.png")):
        with Image.open(path) as im:
            im.load()
            rgba = im.convert("RGBA")
            alpha_min, alpha_max = rgba.getchannel("A").getextrema()
            entries.append({
                "file": path.name,
                "width": im.width,
                "height": im.height,
                "fits_64x64": im.width <= 64 and im.height <= 64,
                "transparent_pixels": alpha_min < 255,
                "opaque_pixels": alpha_max == 255,
                "unique_colors": len(rgba.getcolors(maxcolors=65536) or []),
            })
    (DEST / "manifest.json").write_text(
        json.dumps({"count": len(entries), "assets": entries}, indent=2) + "\n",
        encoding="utf-8"
    )
    print(f"Manifest updated: {len(entries)} imported images")



def main():
    key = os.environ.get("SPRITECOOK_API_KEY", "").strip()
    if not key:
        raise SystemExit("Missing SPRITECOOK_API_KEY repository Actions secret")
    DEST.mkdir(parents=True, exist_ok=True)

    limit = int(os.environ.get("SPRITECOOK_SYNC_LIMIT", "50"))
    recent = get_json(f"{API}/v1/api/assets/recent?limit={limit}", key)
    assets = as_assets(recent)
    saved, skipped, failed = 0, 0, 0

    for item in assets:
        item = {"id": item} if isinstance(item, str) else item
        if not isinstance(item, dict):
            skipped += 1
            continue
        asset_id = str(item.get("id") or item.get("asset_id") or "")
        if not ID_PATTERN.fullmatch(asset_id):
            skipped += 1
            continue
        target = DEST / f"{asset_id}.png"
        try:
            detail = get_json(
                f"{API}/v1/api/assets/{quote(asset_id, safe='')}", key
            )
            image_url = find_url(detail) or find_url(item)
            if not image_url:
                image_url = f"{API}/v1/assets/{quote(asset_id, safe='')}/content/pixel"
            blob = download(image_url, key)
            changed = save_original(blob, target)
            if changed:
                saved += 1
                print(f"Saved/updated {target}")
            else:
                skipped += 1
        except (requests.RequestException, ValueError) as exc:
            failed += 1
            print(f"Could not sync asset {asset_id}: {type(exc).__name__}: {exc}")

    write_manifest()
    print(f"SpriteCook sync: {saved} saved/updated, {skipped} unchanged, {failed} failed")
    if failed:
        raise SystemExit("Some assets could not be synced; check API output format")


if __name__ == "__main__":
    main()
