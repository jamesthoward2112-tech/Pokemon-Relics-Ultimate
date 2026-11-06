"""Job 18 acceptance contracts for the revised endings and Dragonite boss."""
from hashlib import sha256
from pathlib import Path
import json
import re
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]

def read(path):
    return (ROOT / path).read_text(encoding="utf-8")


def assert_dialogue_fits(path, labels):
    source = read(path)
    for label in labels:
        match = re.search(
            rf"(?m)^{re.escape(label)}::?\s*\n((?:\s*\.string\s+\"[^\"]*\"\s*\n)+)",
            source,
        )
        assert match, f"missing dialogue label {label}"
        text = "".join(re.findall(r'\.string\s+"([^"]*)"', match.group(1)))
        assert text.endswith("$"), f"{label} has no terminator"
        for page_number, page in enumerate(text.rstrip("$").split(r"\p"), 1):
            rows = re.split(r"\\[nl]", page)
            assert 1 <= len(rows) <= 2, (label, page_number, rows)
            for row in rows:
                assert row.strip() and len(row) <= 34, (label, page_number, row)


def test_e20_oak_and_alph_lab_gates():
    e20 = read("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
    oak = e20.split("PRU_Elite20_Text_GoldenSky:\n", 1)[1].split("PRU_Elite20_Text_FinalCelebration:", 1)[0]
    assert "ULTIMATE ANCIENT RELIC" in oak
    assert "MT. SILVER" not in oak and "TIN TOWER" not in oak
    assert "msgbox PRU_Elite20_Text_GoldenSky" in e20.split("PRU_Elite18_Gauntlet::", 1)[1].split("PRU_Elite20_StartFinale::", 1)[0]
    finale = e20.split("PRU_Elite20_StartFinale::", 1)[1].split("PRU_Elite20_ClaimRewards::", 1)[0]
    assert "special GameClear" not in finale
    assert "giveitem ITEM_MASTER_BALL, 6" in e20

    lab = read("data/maps/RuinsOfAlph_Lab_hns/scripts.inc")
    gate = lab.split("RuinsOfAlph_Lab_EventScript_Scientist1::", 1)[1].split("RuinsOfAlph_Lab_EventScript_RelicNeedsElite20::", 1)[0]
    for flag in (
        "FLAG_PJR_RELIC_RAIKOU", "FLAG_PJR_RELIC_ENTEI", "FLAG_PJR_RELIC_LUGIA",
        "FLAG_PJR_RELIC_UNOWN_I", "FLAG_PJR_RELIC_CELEBI", "FLAG_PJR_RELIC_SUICUNE",
        "FLAG_PJR_RELIC_ALPHORACLE",
    ):
        assert f"goto_if_unset {flag}" in gate
    assert "goto_if_unset FLAG_PRU_ELITE18_CLEARED" in gate
    assert "ULTIMATE ANCIENT RELIC" in lab
    assert "MT. SILVER's summit" in lab
    assert "TIN TOWER" not in lab


def test_mtsilver_has_only_summoning_and_final_capture_credit_trigger():
    summit = read("data/maps/MtSilver_SummitDay_hns/scripts.inc")
    oak = summit.split("MtSilver_SummitDay_EventScript_RelicOak::", 1)[1].split("MtSilver_SummitDay_EventScript_OakSummon::", 1)[0]
    for flag in (
        "FLAG_PRU_ELITE18_CLEARED", "FLAG_PJR_RELIC_RAIKOU", "FLAG_PJR_RELIC_ENTEI",
        "FLAG_PJR_RELIC_LUGIA", "FLAG_PJR_RELIC_UNOWN_I", "FLAG_PJR_RELIC_CELEBI",
        "FLAG_PJR_RELIC_SUICUNE", "FLAG_PJR_RELIC_ALPHORACLE",
    ):
        assert f"goto_if_unset {flag}" in oak
    assert "trainerbattle" not in oak
    assert "checkitem ITEM_ANCIENT_RAINBOW_CREST" not in summit
    assert "FLAG_PJR_GOT_RAINBOW_CREST, MtSilver_SummitDay_EventScript_Oak" not in summit
    assert "seteventmon SPECIES_RELIC_HO_OH, 100" in summit
    caught = summit.split("MtSilver_SummitDay_EventScript_OakRelicCaught::", 1)[1].split("MtSilver_SummitDay_EventScript_OakEpilogue::", 1)[0]
    assert "setflag FLAG_PJR_RELIC_HO_OH" in caught
    assert "setflag FLAG_PRU_GOLDEN_FINALE_SHOWN" in caught
    assert "setflag FLAG_PRU_E20_CREDITS_PENDING" in caught
    assert "special GameClear" in caught and "waitstate" in caught
    assert summit.count("seteventmon SPECIES_RELIC_HO_OH,") == 1
    oak_text = summit.split("MtSilver_SummitDay_Text_OakObsession:", 1)[1].split("MtSilver_SummitDay_Text_OakSummon:", 1)[0]
    assert "tried to summon it myself" in oak_text
    assert "choose me" in oak_text

    sign = read("data/maps/MtSilver_Outside_hns/scripts.inc")
    assert '"Shortcut to Top$"' in sign


def test_tin_tower_uses_noncatchable_trainer_only_guardian():
    script = read("data/maps/TinTower_RoofDay_hns/scripts.inc")
    events = json.loads(read("data/maps/TinTower_RoofDay_hns/map.json"))
    gfx = [obj["graphics_id"] for obj in events["object_events"] if obj.get("local_id") == "LOCALID_HO_OH"]
    assert gfx == ["OBJ_EVENT_GFX_MON_BASE+SPECIES_DRAGONITE"]
    assert "seteventmon SPECIES_DRAGONITE_GUARDIAN, 60, ITEM_WEAKNESS_POLICY" in script
    assert "setflag FLAG_NO_WILD_CATCHING" in script
    assert "clearflag FLAG_NO_WILD_CATCHING" in script
    assert "B_OUTCOME_WON, TinTower_RoofDay_EventScript_GuardianDefeated" in script
    assert "FLAG_PRU_GUARDIAN_DRAGONITE_COMPLETE" in script
    assert "setflag FLAG_CAUGHT_HO_OH" not in script
    for text in ("Ancient Guardian", "blue", "crystals", "has acknowledged your courage"):
        assert text in script
    assert "SPECIES_HO_OH, CRY_MODE_ENCOUNTER" not in script

    pokemon = read("src/pokemon.c")
    eventmon = pokemon.split("void CreateEnemyEventMon(void)", 1)[1].split("static u16 CalculateBoxMonChecksum", 1)[0]
    guardian = eventmon.split("if (species == SPECIES_DRAGONITE_GUARDIAN && level == 60)", 1)[1].split("if (itemId)", 1)[0]
    for text in (
        "NATURE_ADAMANT", "u8 abilityNum = 2", "MAX_PER_STAT_IVS", "MON_DATA_HP_EV",
        "MON_DATA_ATK_EV", "MON_DATA_SPEED_EV", "MOVE_DRAGON_DANCE", "MOVE_DUAL_WINGBEAT",
        "MOVE_DRAGON_CLAW", "MOVE_ROOST", "CalculateMonStats",
    ):
        assert text in pokemon
    for move in ("MOVE_DRAGON_DANCE", "MOVE_DUAL_WINGBEAT", "MOVE_DRAGON_CLAW", "MOVE_ROOST"):
        assert move in guardian
    assert "MOVE_EARTHQUAKE" not in guardian


def test_exact_guardian_assets_and_exclusive_visual_identity():
    paths = {
        "front.png": "b35cd8dcb12cae133beb608144902172262fda90110e28b45008fbe2bbf84589",
        "back.png": "8b68818cd56def13e61beb9703db428151ad52fd4734098ca34a5ce35c560cd0",
        "icon.png": "332ab7c028bb6b51c84e282ebc39d16ccd82cad367e1156a83a1fd16253656c8",
    }
    for name, digest in paths.items():
        asset = ROOT / "assets/pru_ancient_guardian_dragonite" / name
        assert sha256(asset.read_bytes()).hexdigest() == digest
        image = Image.open(asset)
        assert image.mode == "P"
        assert image.size == ((32, 64) if name == "icon.png" else (64, 64))
        art = ROOT / "graphics/pokemon/ancient_guardian_dragonite" / name
        assert art.read_bytes() == asset.read_bytes()

    species = read("src/data/pokemon/species_info/pjr_families.h")
    block = species.split("PJR_E4_VISUAL_FORM(SPECIES_DRAGONITE_GUARDIAN", 1)[1].split(");", 1)[0]
    assert "gMonFrontPic_DragoniteGuardian" in block
    assert "gMonBackPic_DragoniteGuardian" in block
    assert "gMonIcon_DragoniteGuardian" in block
    assert "NATIONAL_DEX_DRAGONITE" in block
    relic = species.split("PJR_E4_VISUAL_FORM(SPECIES_DRAGONITE_RELIC", 1)[1].split(");", 1)[0]
    assert "gMonFrontPic_Dragonite," in relic and "gMonBackPic_Dragonite," in relic
    assert "SPECIES_DRAGONITE_GUARDIAN" not in read("src/data/pokemon/pru_dex_order.h")
    assert "SPECIES_DRAGONITE_RELIC" not in "\n".join(
        p.read_text(errors="ignore") for p in (ROOT / "data/trainers").glob("*.inc")
    ) if (ROOT / "data/trainers").exists() else True


def test_new_dialogue_pages_fit_gba_text_windows():
    assert_dialogue_fits(
        "data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc",
        ["PRU_Elite20_Text_OakRelics", "PRU_Elite20_Text_GoldenSky",
         "PRU_Elite20_Text_RelicsAlreadyFound", "PRU_Elite20_Text_RepeatReveal"],
    )
    assert_dialogue_fits(
        "data/maps/RuinsOfAlph_Lab_hns/scripts.inc",
        ["RuinsOfAlph_Lab_Text_RelicsComplete", "RuinsOfAlph_Lab_Text_RelicNeedsElite20"],
    )
    assert_dialogue_fits(
        "data/maps/MtSilver_SummitDay_hns/scripts.inc",
        ["MtSilver_SummitDay_Text_OakObsession", "MtSilver_SummitDay_Text_OakSummon",
         "MtSilver_SummitDay_Text_OakNeedRequirements", "MtSilver_SummitDay_Text_OakRetry",
         "MtSilver_SummitDay_Text_OakEpilogue"],
    )
    assert_dialogue_fits(
        "data/maps/TinTower_RoofDay_hns/scripts.inc",
        ["TinTower_RoofDay_Text_Kimono_Opening", "TinTower_RoofDay_Text_Kimono_Closing1",
         "TinTower_RoofDay_Text_GuardianChallenge", "TinTower_RoofDay_Text_GuardianRetry",
         "TinTower_RoofDay_Text_GuardianFarewell", "TinTower_RoofDay_Text_GuardianAlreadyResolved"],
    )
    assert_dialogue_fits(
        "data/maps/EcruteakCity_Theater_hns/scripts.inc",
        ["EcruteakCity_Theater_Text_GirlHooh", "EcruteakCity_Theater_Text_ZukiHooh"],
    )


if __name__ == "__main__":
    test_e20_oak_and_alph_lab_gates()
    test_mtsilver_has_only_summoning_and_final_capture_credit_trigger()
    test_tin_tower_uses_noncatchable_trainer_only_guardian()
    test_exact_guardian_assets_and_exclusive_visual_identity()
    test_new_dialogue_pages_fit_gba_text_windows()
    print("PASS: Job 18 storyline, gated summit, exclusive Dragonite assets and fixed battle data")
