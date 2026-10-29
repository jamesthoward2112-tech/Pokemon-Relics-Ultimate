#!/usr/bin/env python3
"""Apply the curated Elite 20 Relic species assignments to both difficulties.

Preserves the original trainer IDs, roster size, items, levels and remaining
Pokémon. Changes are limited to the specified species slot and its four moves.
"""

import argparse
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
MANIFEST = ROOT / "assets/pru_e20/custom_team_assignments.json"
VISUAL_FORMS = ROOT / "assets/pru_e20/visual_form_assignments.json"
PARTIES = ROOT / "src/data/trainers_hns.party"


def build_updates(source: str, assignments: list[dict]) -> tuple[str, list[str]]:
    updates = []
    for assignment in assignments:
        for difficulty in ("", "_MASTER"):
            trainer_id = f'TRAINER_{assignment["trainer"]}{difficulty}_HNS'
            start_marker = f"=== {trainer_id} ==="
            start = source.find(start_marker)
            if start < 0:
                raise ValueError(f"Missing trainer: {trainer_id}")
            end = source.find("\n=== ", start + len(start_marker))
            if end < 0:
                end = len(source)
            block = source[start:end]
            old = assignment["replace"]
            new = assignment["species"]
            pattern = re.compile(rf"(?m)^{re.escape(old)} @([^\n]*)\n(.*?)(?=\n\n|\Z)", re.DOTALL)
            matches = list(pattern.finditer(block))
            if not matches:
                if re.search(rf"(?m)^{re.escape(new)} @", block):
                    continue  # Already applied in a previous run.
                raise ValueError(f"Expected exactly one {old} in {trainer_id}")
            if len(matches) != 1:
                raise ValueError(f"Ambiguous slot for {old} in {trainer_id}")
            match = matches[0]
            moves = assignment.get("moves")
            body = match.group(2)
            if len(re.findall(r"(?m)^- .+$", body)) != 4:
                raise ValueError(f"Four original moves required: {trainer_id}")
            if moves is not None:
                if len(moves) != 4:
                    raise ValueError(f"Four replacement moves required: {trainer_id}")
                move_iterator = iter(moves)
                body = re.sub(r"(?m)^- .+$", lambda _: "- " + next(move_iterator), body)
            replacement = f'{new} @{match.group(1)}\n{body}'
            new_block = block[:match.start()] + replacement + block[match.end():]
            source = source[:start] + new_block + source[end:]
            updates.append(f"{trainer_id}: {old} -> {new}")
    return source, updates


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", action="store_true", help="Write the reviewed modifications (default: preview)")
    parser.add_argument("--visual-forms", action="store_true", help="Apply existing trainer-only custom sprites, preserving moves unless specified")
    args = parser.parse_args()
    if args.visual_forms:
        assignments = [dict(entry, species=entry["form"]) for entry in json.loads(VISUAL_FORMS.read_text(encoding="utf-8"))["forms"]]
    else:
        assignments = json.loads(MANIFEST.read_text(encoding="utf-8"))["assignments"]
    original = PARTIES.read_text(encoding="utf-8")
    updated, changes = build_updates(original, assignments)
    for line in changes:
        print(line)
    if args.apply and updated != original:
        PARTIES.write_text(updated, encoding="utf-8")
        print(f"Applied {len(changes)} targeted Elite 20 trainer slots")
    else:
        print(f"{'Already applied' if not changes else 'Preview'}: {len(changes)} planned slots")


if __name__ == "__main__":
    main()
