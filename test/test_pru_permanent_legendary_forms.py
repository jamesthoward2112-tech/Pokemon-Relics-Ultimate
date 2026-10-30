import csv
import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def species_record(species):
    source = (ROOT / "src/data/pokemon/species_info/gen_3_families.h").read_text()
    match = re.search(r"\[" + re.escape(species) + r"\]\s*=\s*\{(.*?)\n    },", source, re.S)
    if not match:
        raise AssertionError(f"missing SpeciesInfo record for {species}")
    return match.group(1)


def function_body(path, name):
    source = (ROOT / path).read_text()
    match = re.search(r"^\s*(?:bool32|bool8|void)\s+" + re.escape(name) + r"\s*\([^;]*?\)\s*\{(.*?)\n}", source, re.S | re.M)
    if not match:
        raise AssertionError(f"missing function {name} in {path}")
    return match.group(1)


class PermanentLegendaryFormTests(unittest.TestCase):
    def assert_species_fields(self, species, fields):
        record = species_record(species)
        compact = re.sub(r"\s+", " ", record)
        for field in fields:
            with self.subTest(species=species, field=field):
                self.assertIn(re.sub(r"\s+", " ", field), compact)

    def test_groudon_base_species_is_permanent_black_primal(self):
        self.assert_species_fields("SPECIES_GROUDON", (
            ".baseHP        = 100", ".baseAttack    = 180", ".baseDefense   = 160",
            ".baseSpAttack  = 150", ".baseSpDefense = 90", ".baseSpeed     = 90",
            "MON_TYPES(TYPE_GROUND, TYPE_FIRE)",
            ".abilities = { ABILITY_DESOLATE_LAND, ABILITY_DESOLATE_LAND, ABILITY_DESOLATE_LAND }",
            ".frontPic = gMonFrontPic_GroudonPrimal", ".backPic = gMonBackPic_GroudonPrimal",
            ".palette = gMonShinyPalette_GroudonPrimal", ".shinyPalette = gMonShinyPalette_GroudonPrimal",
            ".iconSprite = gMonIcon_GroudonPrimal", "sPicTable_GroudonPrimal",
            "gShinyOverworldPalette_GroudonPrimal, gShinyOverworldPalette_GroudonPrimal",
        ))

    def test_kyogre_base_species_is_permanent_black_primal(self):
        self.assert_species_fields("SPECIES_KYOGRE", (
            ".baseHP        = 100", ".baseAttack    = 150", ".baseDefense   = 90",
            ".baseSpAttack  = 180", ".baseSpDefense = 160", ".baseSpeed     = 90",
            "MON_TYPES(TYPE_WATER)",
            ".abilities = { ABILITY_PRIMORDIAL_SEA, ABILITY_PRIMORDIAL_SEA, ABILITY_PRIMORDIAL_SEA }",
            ".frontPic = gMonFrontPic_KyogrePrimal", ".backPic = gMonBackPic_KyogrePrimal",
            ".palette = gMonShinyPalette_KyogrePrimal", ".shinyPalette = gMonShinyPalette_KyogrePrimal",
            ".iconSprite = gMonIcon_KyogrePrimal", "sPicTable_KyogrePrimal",
            "gShinyOverworldPalette_KyogrePrimal, gShinyOverworldPalette_KyogrePrimal",
        ))

    def test_rayquaza_base_species_is_permanent_black_shiny_mega(self):
        self.assert_species_fields("SPECIES_RAYQUAZA", (
            ".baseHP        = 105", ".baseAttack    = 180", ".baseDefense   = 100",
            ".baseSpAttack  = 180", ".baseSpDefense = 100", ".baseSpeed     = 115",
            "MON_TYPES(TYPE_DRAGON, TYPE_FLYING)",
            ".abilities = { ABILITY_DELTA_STREAM, ABILITY_DELTA_STREAM, ABILITY_DELTA_STREAM }",
            ".frontPic = gMonFrontPic_RayquazaMega", ".backPic = gMonBackPic_RayquazaMega",
            ".palette = gMonShinyPalette_RayquazaMega", ".shinyPalette = gMonShinyPalette_RayquazaMega",
            ".iconSprite = gMonIcon_RayquazaMega", "sPicTable_RayquazaMega",
            "gShinyOverworldPalette_RayquazaMega, gShinyOverworldPalette_RayquazaMega",
        ))
        form_table = (ROOT / "src/data/pokemon/form_change_tables.h").read_text()
        rayquaza = re.search(r"static const struct FormChange sRayquazaFormChangeTable\[\]\s*=\s*\{(.*?)\n};", form_table, re.S).group(1)
        self.assertNotIn("MOVE_DRAGON_ASCENT", rayquaza)

    def test_dynamic_form_change_apis_and_gimmick_controls_are_disabled(self):
        self.assertIn("#define P_PRU_DYNAMIC_FORM_CHANGES      FALSE", (ROOT / "include/config/species_enabled.h").read_text())
        for path, name in (("src/pokemon.c", "TryFormChange"), ("src/pokemon.c", "TryBoxMonFormChange"),
                           ("src/battle_util.c", "TryBattleFormChange"), ("src/battle_util.c", "CanMegaEvolve")):
            self.assertIn("#if !P_PRU_DYNAMIC_FORM_CHANGES", function_body(path, name), f"{name} must be disabled centrally")

    def test_mewduo_uses_parental_bond_in_every_ability_slot(self):
        source = (ROOT / "src/data/pokemon/species_info/pru_custom.h").read_text()
        block = re.search(r"\[SPECIES_MEWSION\]\s*=\s*\{(.*?)\n},", source, re.S).group(1)
        self.assertIn(".abilities = { ABILITY_PARENTAL_BOND, ABILITY_PARENTAL_BOND, ABILITY_PARENTAL_BOND }", block)
        self.assertIn("#define B_PARENTAL_BOND_DMG         GEN_LATEST", (ROOT / "include/config/battle.h").read_text())

    def test_storm_shrine_has_a_gated_retryable_shiny_rayquaza_encounter(self):
        folder = ROOT / "data/maps/DragonsDen_StormShrine_hns"
        self.assertTrue((folder / "map.json").is_file())
        script = (folder / "scripts.inc").read_text()
        for expected in ("FLAG_IS_CHAMPION", "setwildbattleshiny SPECIES_RAYQUAZA, 85",
                         "FLAG_PRU_RAYQUAZA_CAUGHT", "CRY_MODE_ENCOUNTER"):
            self.assertIn(expected, script)
        util = (ROOT / "src/script_pokemon_util.c").read_text()
        for move in ("MOVE_DRAGON_ASCENT", "MOVE_DRAGON_PULSE", "MOVE_EXTREME_SPEED", "MOVE_EARTHQUAKE"):
            self.assertIn(move, util)

    def test_canonical_pokedex_has_exactly_450_species_without_adding_rayquaza(self):
        path = ROOT / "data/pru/PRU_National_Pokedex_2026-10-16.csv"
        with path.open(encoding="utf-8-sig", newline="") as handle:
            rows = list(csv.DictReader(handle))
        self.assertEqual(len(rows), 450)
        self.assertEqual([r["Name"] for r in rows[-3:]], ["Rhyperior", "Magmortar", "Electivire"])
        self.assertEqual(rows[-1]["PRU_No"], "450")
        self.assertEqual((ROOT / "include/constants/species.h").read_text().count("SPECIES_RAYQUAZA "), 1)
        shrine_map = (ROOT / "data/maps/DragonsDen_Shrine_hns/map.json").read_text()
        self.assertIn("VAR_BLACKTHORN_CITY_STATE", shrine_map)


if __name__ == "__main__":
    unittest.main()
