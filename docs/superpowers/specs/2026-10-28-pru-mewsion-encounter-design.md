# PRU Mewsion encounter design

## Intent

Make the existing AlteRed-derived Mewsion species (#425 in PRU) obtainable as a Level 90 one-time capture in Cerulean Cave B2F, with its own distinctive overworld appearance. James has already caught Mewtwo and has Mew in the PC, so the encounter must use Pokédex caught records, not party composition.

## Behaviour and constraints

- Unlock only after both Mew and Mewtwo are registered caught **and the player exits Cerulean Cave and returns**.
- On qualifying B2F entries, show once: “A strange presence fills the air... Dark matter has been detected nearby!”
- Place Mewsion at the exact original Mewtwo tile (8,14). Keep the original Level 80 Mewtwo encounter available to players who haven't caught it.
- On KO, flight, or whiteout the Mewsion encounter may be retried; only a successful capture removes it permanently.
- Mewsion shares Mewtwo's National Dex identity in current code, so use a **separate append-only capture flag**. Never change existing species IDs, Mewtwo flags, or player saves.
- Keep all original Mewsion front, back, shiny, icon, moves and stats.
- Dedicated Mewsion overworld art must visually match its existing white/black/red battle artwork and differ from both vanilla and Insurgence Shadow Mewtwo. Never swap in the near-vanilla AlteRed Mewtwo overworld graphic.

## Approach

Chosen: gate one new object via map-entry state and separate capture flags, following the existing Astrachi-style legendary pattern. Alternatives ruled out: a second battle on Mewtwo's event script (would not spawn after Mewtwo capture), and checking the shared National Dex caught bit (would mark Mewsion caught when Mewtwo is caught). An ordinary party/PC presence check is also insufficient for historical captures.

The event logic can be implemented independently of artwork. The image-generation service rejected the dedicated sprite request, so battle-accurate OW art is a known acceptance blocker; do not ship a visually incorrect substitute as final.

## Acceptance

Old saves remain compatible. Correct prerequisite, full cave re-entry, one warning per entry, Level 90 tile, capture-only permanent removal, and battle-art-matching overworld artwork are all verified.
