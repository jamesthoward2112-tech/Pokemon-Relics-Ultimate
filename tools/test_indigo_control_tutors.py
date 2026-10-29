"""Regression checks for PJR Indigo Plateau battlefield-control move tutors."""
from pathlib import Path
import json
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
SCRIPT = ROOT / "data" / "maps" / "IndigoPlateau_PokemonCenter_hns" / "scripts.inc"
MAP = ROOT / "data" / "maps" / "IndigoPlateau_PokemonCenter_hns" / "map.json"
CHOOSEBOX = ROOT / "src" / "chooseboxmon.c"
PARTY_CONSTANTS = ROOT / "include" / "constants" / "party_menu.h"
PJR_FAMILIES = ROOT / "src" / "data" / "pokemon" / "species_info" / "pjr_families.h"
MOVES_INFO = ROOT / "src" / "data" / "moves_info.h"

HAZARD_MOVES = [
    "MOVE_STEALTH_ROCK", "MOVE_SPIKES", "MOVE_TOXIC_SPIKES", "MOVE_STICKY_WEB",
    "MOVE_STONE_AXE", "MOVE_CEASELESS_EDGE", "MOVE_SALT_CURE", "MOVE_LEECH_SEED",
    "MOVE_TOXIC", "MOVE_WILL_O_WISP", "MOVE_THUNDER_WAVE", "MOVE_TAUNT",
    "MOVE_ENCORE", "MOVE_KNOCK_OFF", "MOVE_ROAR", "MOVE_WHIRLWIND",
    "MOVE_DRAGON_TAIL", "MOVE_INFESTATION", "MOVE_ACHILLES_HEEL",
    "MOVE_PERMAFROST", "MOVE_WILDFIRE", "MOVE_DARK_MATTER",
]

CLEANUP_MOVES = [
    "MOVE_RAPID_SPIN", "MOVE_DEFOG", "MOVE_MORTAL_SPIN", "MOVE_TIDY_UP",
    "MOVE_COURT_CHANGE", "MOVE_HAZE", "MOVE_CLEAR_SMOG", "MOVE_BRICK_BREAK",
    "MOVE_PSYCHIC_FANGS", "MOVE_ICE_SPINNER", "MOVE_HEAL_BELL",
    "MOVE_AROMATHERAPY", "MOVE_U_TURN", "MOVE_VOLT_SWITCH", "MOVE_FLIP_TURN",
    "MOVE_PARTING_SHOT", "MOVE_SNARL", "MOVE_ICY_WIND", "MOVE_BREAKING_SWIPE",
    "MOVE_CHILLING_WATER", "MOVE_ACID_SPRAY", "MOVE_NUZZLE",
]

def text() -> str:
    return SCRIPT.read_text(encoding="utf-8")

def block(label: str, next_label: str | None = None) -> str:
    source = text()
    start = source.index(label + "::")
    if next_label:
        end = source.index(next_label + "::", start)
        return source[start:end]
    return source[start:]

class TestIndigoControlTutors(unittest.TestCase):
    def test_existing_indigo_npcs_are_reused(self):
        source = text()
        self.assertRegex(
            source,
            r"IndigoPlateau_EventScript_Cooltrainer::\s+goto IndigoPlateau_EventScript_HazardTutor",
        )
        self.assertRegex(
            source,
            r"IndigoPlateau_EventScript_ShigyNinja::\s+goto IndigoPlateau_EventScript_CleanupTutor",
        )

    def test_hazard_tutor_has_locked_move_set(self):
        section = block(
            "IndigoPlateau_EventScript_HazardTutor",
            "IndigoPlateau_EventScript_CleanupTutor",
        )
        self.assertEqual(section.count("case "), len(HAZARD_MOVES) + 2)
        source = text()
        for move in HAZARD_MOVES:
            self.assertRegex(source, rf"setvar VAR_0x8005, {move}\b")

    def test_cleanup_tutor_has_locked_move_set(self):
        section = block(
            "IndigoPlateau_EventScript_CleanupTutor",
            "IndigoPlateau_EventScript_TutorTeach_StealthRock",
        )
        self.assertEqual(section.count("case "), len(CLEANUP_MOVES) + 2)
        source = text()
        for move in CLEANUP_MOVES:
            self.assertRegex(source, rf"setvar VAR_0x8005, {move}\b")

    def test_tutors_are_free_repeatable_and_use_logical_compatibility(self):
        source = text()
        common = block(
            "IndigoPlateau_EventScript_TutorTeachMove",
            "IndigoPlateau_EventScript_TutorCancelled",
        )
        self.assertIn("chooseboxmon SELECT_PC_MON_PJR_CONTROL_TUTOR", common)
        self.assertNotRegex(common, r"removeitem|removemoney|setflag")
        self.assertNotRegex(
            block(
                "IndigoPlateau_EventScript_HazardTutor",
                "IndigoPlateau_EventScript_TutorTeach_StealthRock",
            ),
            r"checkitem|checkmoney|goto_if_set|setflag",
        )

        choosebox = CHOOSEBOX.read_text(encoding="utf-8")
        constants = PARTY_CONSTANTS.read_text(encoding="utf-8")
        self.assertIn("SELECT_PC_MON_PJR_CONTROL_TUTOR", constants)
        self.assertIn(
            "[SELECT_PC_MON_PJR_CONTROL_TUTOR] = {ChooseMonForMoveTutor, "
            "CanMonLearnPjrControlMove, MoveTutor_AfterChooseBoxMon, FALSE}",
            choosebox,
        )

        # Both tutors now cover the approved 444 Pokémon (including the
        # appended PRU species), but never automatically unlock all moves.
        self.assertIn("if (CanLearnTeachableMove(species, move))", choosebox)
        self.assertIn("SpeciesToPokedexNum(species) == 0xFFFF", choosebox)
        self.assertIn("!IS_HNS", choosebox)
        self.assertNotIn(
            "if (species < SPECIES_SCARABUB || species > SPECIES_DRAGONITE_RELIC)",
            choosebox,
        )
        self.assertIn("CanSpeciesLearnPjrControlTutorMove(species, gSpecialVar_0x8005)", choosebox)
        self.assertNotIn("if (IsPjrControlTutorMove(gSpecialVar_0x8005))", choosebox)
        compatibility = choosebox.split("static bool32 CanSpeciesLearnPjrControlTutorMove", 1)[1].split("static u32 CanMonLearnPjrControlMove", 1)[0]
        for move in HAZARD_MOVES + CLEANUP_MOVES:
            self.assertIn(f"case {move}:", compatibility)

        # Move rules reflect species type and anatomy, not only the old
        # custom-ID range. New additions must stay eligible too.
        for species in ("SPECIES_SCEPTITAN", "SPECIES_DONPHALANX",
                        "SPECIES_SKULBERUS", "SPECIES_NOXICHU",
                        "SPECIES_EEVEEON"):
            self.assertIn(species, compatibility)
        self.assertIn("case MOVE_CEASELESS_EDGE:", compatibility)
        self.assertIn("case MOVE_RAPID_SPIN:", compatibility)
        self.assertIn("case MOVE_TIDY_UP:", compatibility)
        self.assertIn("case MOVE_PSYCHIC_FANGS:", compatibility)
        self.assertIn("case MOVE_COURT_CHANGE:", compatibility)
        self.assertIn("return species == SPECIES_EEVEEON;", compatibility)
        self.assertIn("moveType = GetMoveType(move);", compatibility)
        self.assertIn("if (moveType != TYPE_NORMAL && IsSpeciesOfType(species, moveType))", compatibility)
        self.assertRegex(compatibility, r"(?s)case MOVE_WILL_O_WISP:.*?TYPE_FIRE.*?TYPE_GHOST")
        self.assertRegex(compatibility, r"(?s)case MOVE_WHIRLWIND:.*?TYPE_FLYING")

        # Shuckoloose is Bug/Rock and the Rock control moves are genuinely Rock type.
        pjr_families = PJR_FAMILIES.read_text(encoding="utf-8")
        moves_info = MOVES_INFO.read_text(encoding="utf-8")
        self.assertRegex(
            pjr_families,
            r"SPECIES_SHUCKOLOSSE.*?TYPE_BUG, TYPE_ROCK",
        )
        for move in ("MOVE_STEALTH_ROCK", "MOVE_STONE_AXE", "MOVE_SALT_CURE"):
            self.assertRegex(
                moves_info,
                rf"(?s)\[{move}\]\s*=\s*\{{.*?\.type\s*=\s*TYPE_ROCK",
            )

        # Normal tutor/TM compatibility remains intact outside these two NPCs.
        self.assertIn(
            "CanLearnTeachableMove(GetBoxMonData(boxmon, MON_DATA_SPECIES), "
            "gSpecialVar_0x8005)",
            choosebox,
        )

    def test_pru_restores_equipped_berries_as_well_as_other_consumables(self):
        source = (ROOT / "src" / "battle_util.c").read_text(encoding="utf-8")
        self.assertIn("void TryRestoreHeldItems(void)", source)
        self.assertIn("if (!IS_HNS && GetItemPocket(lostItem) == POCKET_BERRIES", source)
        self.assertIn("(IS_HNS || GetItemPocket(lostItem) != POCKET_BERRIES)", source)
        self.assertIn("SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &lostItem);", source)
        cfg = (ROOT / "include" / "config" / "battle.h").read_text(encoding="utf-8")
        self.assertIn("#define B_RESTORE_HELD_BATTLE_ITEMS GEN_LATEST", cfg)

    def test_cleanup_tutor_npc_is_static(self):
        data = json.loads(MAP.read_text(encoding="utf-8"))
        npc = next(
            obj for obj in data["object_events"]
            if obj.get("script") == "IndigoPlateau_EventScript_ShigyNinja"
        )
        self.assertEqual(npc["movement_type"], "MOVEMENT_TYPE_NONE")
        self.assertEqual(npc["movement_range_x"], 0)
        self.assertEqual(npc["movement_range_y"], 0)

    def test_transport_npcs_are_not_repurposed(self):
        source = text()
        self.assertIn("IndigoPlateau_EventScript_Psychic::", source)
        self.assertIn("IndigoPlateau_EventScript_Abra::", source)
        self.assertIn("warpteleport MAP_NEW_BARK_TOWN_HNS, 20, 12", source)

if __name__ == "__main__":
    unittest.main()
