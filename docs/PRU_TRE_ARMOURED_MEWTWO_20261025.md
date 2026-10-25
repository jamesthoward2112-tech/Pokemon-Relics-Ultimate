# PRU: TRE Armoured Mewtwo asset lock (25 October 2026)

- Original source: the user's `TRE_Johto_Extended_Custom_Sprite_Bank.zip` (from TRE Dragonsden 2026 donor ROM).
- Exact named form: `0922_Mewtwo.Arm`.
- Extracted source: 64×64 front/back battle sprites and 32×64 two-frame party icon.
- Original author credited by TRE `Créditos.rtf`: [DestvoL](https://www.deviantart.com/destvol/art/Armor-Mewtwo-sprite-GBA-ver-799287791).
- The source shiny front/back PNGs were byte-identical to the normal front/back in this archive.
- Reproducible import: `python3 tools/pru/import_tre_armoured_mewtwo.py <extracted-0922-folder>`.
- GBA-ready indexed versions and a shared 16-colour battle palette retain all source pixels.

Only **Giovanni's final enemy Mewtwo** uses the front art and palette; the
party's ordinary Mewtwo, Cerulean Cave encounter, base species graphics,
Dex species count, and Mega Mewtwo forms remain unchanged. The source back
and icon images are archived for completeness but are deliberately not wired
globally, as Giovanni's Mewtwo is a trainer Pokémon that cannot be caught.

Giovanni's Mewtwo already has the approved separate trainer-only Defence and
Special Defence bonus equivalent to base 120 (ordinary Mewtwo stays at 90).
This artwork pass does **not** import TRE's much higher base stats, typing or
ability; it only uses the sprite source requested by James.
