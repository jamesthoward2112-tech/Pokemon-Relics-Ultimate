"""Static regression checks for the Rocket badge-heist finale."""

from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
VIP = (ROOT / "data/maps/SaffronCity_FightingDojoVIP_hns/scripts.inc").read_text()
TEAMS = (ROOT / "src/data/trainers_hns.party").read_text()
GIOVANNI = (ROOT / "data/maps/ViridianCity_Gym_hns/scripts.inc").read_text()
INDIGO = (ROOT / "data/maps/IndigoPlateau_hns/scripts.inc").read_text()
ROCKET = (ROOT / "data/maps/Route22_hns/scripts.inc").read_text()
STAT_CODE = (ROOT / "src/battle_main.c").read_text()

LEADERS = {
    "BROCK": ["Golem", "Omastar", "Kabutops", "Aerodactyl", "Obsideon", "Pinsirex"],
    "MISTY": ["Politoed", "Cloyster", "Vaporeon", "Kingdra", "Starmie", "Blastoise"],
    "SURGE": ["Electrode", "Magneton", "Electivire", "Jolteon", "Porygon2", "Raichu"],
    "ERIKA": ["Vileplume", "Bellossom", "Exeggutor", "Leafeon", "Victreebel", "Venusaur"],
    "JANINE": ["Muk", "Venomoth", "Crobat", "Tentacruel", "Adnokana", "Frytning"],
    "SABRINA": ["Mr. Mime", "Hypno", "Slowbro", "Espeon", "Mystynx", "Alakazam"],
    "BLAINE": ["Ninetales", "Rapidash", "Magmortar", "Flareon", "Arcanine", "Charizard"],
}
FLAGS = list(LEADERS)


def trainer(name):
    section = f"=== TRAINER_{name}_HNS ===\n"
    assert section in TEAMS, f"missing {section}"
    return TEAMS.split(section, 1)[1].split("===", 1)[0]


def members(name):
    block = trainer(name)
    pairs = re.findall(r"^([^\n:]+?)(?:\s+@\s+[^\n]+)?\n(?:Ability: [^\n]+\n)?Level:\s*(\d+)", block, re.M)
    assert len(pairs) == 6, f"{name}: expected 6, found {pairs}"
    return [(species.strip(), int(level)) for species, level in pairs]


def check():
    assert "all EIGHT KANTO" in ROCKET, "Rocket must demand all 8 leaders"
    assert "FIGHTING DOJO" in ROCKET, "Rocket must point to Saffron Dojo"
    assert "GIOVANNI!" not in ROCKET.split("Route22_Text_PRURocketBalloon:", 1)[1].split("Route22_Movement_", 1)[0], "Rocket must preserve the 8th-leader twist"
    assert "MAP_SCRIPT_ON_TRANSITION" in VIP, "Dojo lacks map-entry sync"
    assert "SaffronCity_FightingDojoVIP_EventScript_PRUHeistSync::" in VIP
    for idx, (leader, species) in enumerate(LEADERS.items()):
        name = f"PRU_HEIST_{leader}"
        mons = members(name)
        assert [s for s, _ in mons] == species, (name, mons)
        assert all(76 <= level <= 80 for _, level in mons), (name, mons)
        assert f"TRAINER_{name}_HNS" in VIP, f"{leader} fight is outside VIP"
        assert f"setflag FLAG_PRU_HEIST_{leader}" in VIP, f"{leader} victory not saved in VIP"
        if idx:
            assert f"goto_if_unset FLAG_PRU_HEIST_{FLAGS[idx-1]}" in VIP
    assert "FLAG_HIDE_DOJO_BLUE" in VIP, "Blue must remain absent during the heist"
    assert "SaffronCity_FightingDojoVIP_EventScript_Nurse::" in VIP

    g = members("PRU_HEIST_GIOVANNI")
    assert g == [
        ("Omastar", 81), ("Kabutops", 82), ("Aerodactyl", 83),
        ("Coelossus", 83), ("Rhyperior", 84), ("Mewtwo", 85),
    ], g
    assert "Armour" in GIOVANNI and "Cerulean" in GIOVANNI
    assert "PruIsMewtwoCaught" in GIOVANNI and "clearflag FLAG_HIDE_MEWTWO" in GIOVANNI
    assert "TRAINER_PRU_HEIST_GIOVANNI_HNS" in STAT_CODE
    assert "2 * 120" in STAT_CODE, "Trainer-only 120 base Def and SpDef missing"
    assert "FLAG_PRU_HEIST_GIOVANNI" in INDIGO
    assert "goto_if_set FLAG_PRU_HEIST_GIOVANNI, IndigoPlateau_EventScript_PRUDoorUnlocked" in INDIGO

    for location, label in [
        ("PewterCity_Gym_hns", "Brock"),
        ("VermilionCity_Gym_hns", "Surge"),
        ("CeladonCity_Gym_hns", "Erika"),
        ("FuchsiaCity_Gym_hns", "Janine"),
        ("SaffronCity_Gym_hns", "Sabrina"),
    ]:
        src = (ROOT / f"data/maps/{location}/map.json").read_text()
        script = f"{location.removesuffix('_hns')}_EventScript_{label}"
        assert f'"script": "{script}",\n      "flag": "FLAG_DEFEATED_VIRIDIAN_GYM"' in src
    assert "FLAG_DEFEATED_VIRIDIAN_GYM" in (ROOT / "data/maps/CeruleanCity_Gym_hns/scripts.inc").read_text()
    assert "FLAG_DEFEATED_VIRIDIAN_GYM" in (ROOT / "data/maps/SeafoamIslands_Gym_hns/scripts.inc").read_text()

    for name, low, high in [
        ("WILL_POSTOBC", 82, 85), ("KOGA_POSTOBC", 83, 86),
        ("BRUNO_POSTOBC", 84, 87), ("KAREN_POSTOBC", 85, 88),
        ("LANCE_POSTOBC", 86, 89),
    ]:
        party = members(name)
        assert all(low <= lvl <= high for _, lvl in party), (name, party)
        assert max(level for _, level in party) == high, (name, party)
    print("PASS: seven Dojo leaders, Giovanni roster and E4 rematch progression")


if __name__ == "__main__":
    check()
