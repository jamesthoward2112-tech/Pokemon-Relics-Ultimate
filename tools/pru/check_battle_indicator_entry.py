#!/usr/bin/env python3
"""Guard against black 8x8 gimmick indicators flashing during battle entry."""

from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
gimmick = (ROOT / "src/battle_gimmick.c").read_text(encoding="utf-8")
interface = (ROOT / "src/battle_interface.c").read_text(encoding="utf-8")

creation = gimmick.split("void CreateIndicatorSprite(enum BattlerId battler)", 1)[1].split("\n}\n", 1)[0]
visibility = gimmick.split("void UpdateIndicatorVisibilityAndType(u32 healthboxId, bool32 invisible)", 1)[1].split("\n}\n", 1)[0]

assert "gSprites[spriteId].invisible = TRUE;" in creation, "Indicator must begin hidden, before tile graphics are valid"
assert "gSprites[spriteId].invisible = FALSE;" not in creation, "Premature indicator visibility causes black squares"
assert "sprite->invisible = invisible;" in visibility, "Actual gimmick indicators still need to be shown when activated"
assert "sprite->invisible = TRUE;" in visibility, "Battlers without an active gimmick must remain hidden"
assert "CreateIndicatorSprite(battler);" in interface, "Healthbox initialization must still allocate the indicator"
assert "UpdateIndicatorVisibilityAndType(healthboxSpriteId, FALSE);" in interface, "Battle UI must still reveal valid indicators"

print("PASS: encounter indicator sprites start hidden and valid gimmick icons can still appear")
