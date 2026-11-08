# PRU Pikachu Ancient Stone evolution (8 November 2026)

The protagonist Pikachu now evolves to Noxichu using the existing **Ancient Stone**, at any level. The old Moon Stone route to Noxichu has been retired. Pikachu's Thunder Stone route to Raichu is unchanged.

This uses the existing item ID, consumption behavior, shop stock, evolution engine and species constants: no saved data, sprites, story flags or Pokédex order are changed.

Regression checks: `tools/pru/check_pikachu_ancient_stone.py`, `tools/pru/check_relic_stone_services.py`, `tools/pru/check_evo_dex_discovery.py`, `tools/pru/check_canonical_eeveelutions.py`, and `tools/pru/audit_all_custom_evolutions.py`. Compiled and gameplay-test status must be reported separately.
