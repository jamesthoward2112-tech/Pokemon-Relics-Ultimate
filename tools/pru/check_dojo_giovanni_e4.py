"""Static regression checks for the Rocket badge-heist finale."""

from pathlib import Path
import json
import re

ROOT = Path(__file__).resolve().parents[2]
VIP = (ROOT / "data/maps/SaffronCity_FightingDojoVIP_hns/scripts.inc").read_text()
VIP_MAP = json.loads((ROOT / "data/maps/SaffronCity_FightingDojoVIP_hns/map.json").read_text())
TEAMS = (ROOT / "src/data/trainers_hns.party").read_text()
GIOVANNI = (ROOT / "data/maps/ViridianCity_Gym_hns/scripts.inc").read_text()
GIOVANNI_MAP = json.loads((ROOT / "data/maps/ViridianCity_Gym_hns/map.json").read_text())
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
STAGE_POSITIONS = {
    "BROCK": (21, 20),
    "MISTY": (21, 20),
    "SURGE": (21, 20),
    "ERIKA": (21, 20),
    "JANINE": (21, 20),
    "SABRINA": (21, 20),
    "BLAINE": (21, 20),
}
COMPANION_POSITIONS = {
    "ONIX": (23, 20),
    "STARMIE": (23, 20),
    "RAICHU": (23, 20),
    "VICTREEBEL": (23, 20),
    "MUK": (23, 20),
    "KADABRA": (23, 20),
    "MAGMAR": (23, 20),
}
HEIST_PARTNER_IDS = {
    "BROCK": 28,      # Onix
    "MISTY": 23,      # Starmie
    "SURGE": 19,      # Raichu
    "ERIKA": 24,      # Victreebel
    "JANINE": 30,     # Muk
    "SABRINA": 27,    # Kadabra
    "BLAINE": 34,     # Magmar
}


def trainer(name):
    section = f"=== TRAINER_{name}_HNS ===\n"
    assert section in TEAMS, f"missing {section}"
    return TEAMS.split(section, 1)[1].split("===", 1)[0]


def members(name):
    block = trainer(name)
    pairs = re.findall(r"^([^\n:]+?)(?:\s+@\s+[^\n]+)?\n(?:Ability: [^\n]+\n)?Level:\s*(\d+)", block, re.M)
    assert len(pairs) == 6, f"{name}: expected 6, found {pairs}"
    return [(species.strip(), int(level)) for species, level in pairs]


def check_heist_abilities_legal():
    # Every explicitly requested trainer ability must appear in that
    # species' three allowed ability slots. Violations crash battle_main.c.
    allowed = {}
    for path in (ROOT / "src/data/pokemon/species_info").glob("*.h"):
        content = path.read_text()
        records = list(re.finditer(r"\[SPECIES_([A-Z0-9_]+)\]\s*=\s*\{", content))
        for i, record in enumerate(records):
            block = content[record.end():records[i + 1].start() if i + 1 < len(records) else len(content)]
            abilities = re.search(r"\.abilities\s*=\s*\{([^}]+)\}", block)
            if abilities:
                allowed[record.group(1)] = {
                    value.strip().removeprefix("ABILITY_")
                    for value in abilities.group(1).split(",")
                }
    for leader in [*LEADERS, "GIOVANNI"]:
        for species, ability in re.findall(
            r"^(.+?)\s+@[^\n]+\nAbility:\s+([^\n]+)\nLevel:",
            trainer(f"PRU_HEIST_{leader}"), re.M,
        ):
            key = re.sub(r"[^A-Z0-9]+", "_", species.upper()).strip("_")
            requested = re.sub(r"[^A-Z0-9]+", "_", ability.upper()).strip("_")
            assert key in allowed, f"{leader}: no species ability data for {species}"
            assert requested in allowed[key], (
                f"{leader}: illegal ability {ability} for {species}; legal: {sorted(allowed[key])}"
            )


def check_dojo_layout():
    events = VIP_MAP["object_events"]
    for leader, xy in STAGE_POSITIONS.items():
        matches = [e for e in events if e["graphics_id"] == f"OBJ_EVENT_GFX_{leader}_HNS"]
        assert len(matches) == 1, f"{leader}: expected one stage leader"
        assert (matches[0]["x"], matches[0]["y"]) == xy, f"{leader}: not on the large Dojo stage"

    for species, xy in COMPANION_POSITIONS.items():
        matches = [e for e in events if e["graphics_id"] == f"OBJ_EVENT_GFX_MON_BASE+SPECIES_{species}"]
        assert len(matches) == 1, f"{species}: expected one stage partner"
        assert (matches[0]["x"], matches[0]["y"]) == xy, f"{species}: partner misplaced"
        assert "WALK_SEQUENCE" not in matches[0]["movement_type"], (
            f"{species}: partner must stay beside their leader during the heist"
        )

    desk_mons = [
        e for e in events if e["graphics_id"].startswith("OBJ_EVENT_GFX_MON_BASE+")
        and e["y"] == 5 and e["x"] >= 36
    ]
    assert [e["graphics_id"] for e in desk_mons] == [
        "OBJ_EVENT_GFX_MON_BASE+SPECIES_CHANSEY"
    ], "the BP counter must not contain roaming Kanto/Johto leader Pokémon"

    desk = [e for e in events if e["script"] == "PRU_ChanseyTrainer_Lv100"]
    assert len(desk) == 1, "right-hand desk needs the repeatable double Lv100 Chansey trainer"
    assert (desk[0]["x"], desk[0]["y"]) == (39, 5)
    assert desk[0]["graphics_id"] == "OBJ_EVENT_GFX_MON_BASE+SPECIES_CHANSEY"
    assert desk[0]["flag"] == "0"

    sync = VIP.split("SaffronCity_FightingDojoVIP_EventScript_PRUHeistSync::", 1)[1].split(
        "@ The seven leader battles", 1
    )[0]
    for leader in LEADERS:
        assert f"goto_if_unset FLAG_PRU_HEIST_{leader}, SaffronCity_FightingDojoVIP_EventScript_PRUShow{leader.title()}" in sync, (
            f"{leader} must wait its turn"
        )
        assert f"setflag FLAG_HIDE_DOJO_{leader}" in sync
        assert f"clearflag FLAG_HIDE_DOJO_{leader}" in sync
    assert "setflag FLAG_HIDE_DOJO_BLUE" in sync
    # Blaine's real post-battle farewell, shown before the white flash, must
    # reveal the final badge objective without naming the eighth Gym's city.
    blaine_farewell = VIP.split("SaffronCity_FightingDojoVIP_Text_PRUHeistNextBlaine:", 1)[1].split(
        "SaffronCity_FightingDojoVIP_Text_PRUHeistChallenge:", 1
    )[0]
    assert "EIGHTH BADGE remains" in blaine_farewell
    assert "north of PALLET TOWN" in blaine_farewell
    assert "Find its GYM" in blaine_farewell
    assert "VIRIDIAN" not in blaine_farewell
    blaine_battle = VIP.split("SaffronCity_FightingDojoVIP_EventScript_PRUHeistBlaine::", 1)[1].split(
        "SaffronCity_FightingDojoVIP_EventScript_PRUNotReady::", 1
    )[0]
    assert "msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNextBlaine" in blaine_battle
    assert blaine_battle.index("Text_PRUHeistNextBlaine") < blaine_battle.index("fadescreenswapbuffers FADE_TO_WHITE")

    for name in LEADERS:
        leader = next(e for e in events if e["graphics_id"] == f"OBJ_EVENT_GFX_{name}_HNS")
        assert leader["movement_type"] == "MOVEMENT_TYPE_FACE_DOWN", f"{name}: must be static"
    for species in COMPANION_POSITIONS:
        partner = next(e for e in events if e["graphics_id"] == f"OBJ_EVENT_GFX_MON_BASE+SPECIES_{species}")
        assert partner["movement_type"] == "MOVEMENT_TYPE_FACE_DOWN", f"{species}: must be static"

    for i, (leader, companion) in enumerate(HEIST_PARTNER_IDS.items()):
        block = VIP.split(f"SaffronCity_FightingDojoVIP_EventScript_PRUHeist{leader.title()}::", 1)[1].split(
            "\nSaffronCity_FightingDojoVIP_EventScript_PRUHeist", 1
        )[0]
        assert f"removeobject {companion} " in block, f"{leader}: companion not removed"
        assert "call SaffronCity_FightingDojoVIP_EventScript_PRUHeistSync" in block
        if i < len(HEIST_PARTNER_IDS) - 1:
            assert f"addobject {[1,3,4,5,6,7][i]}" in block, f"{leader}: next leader not spawned"


def check():
    check_heist_abilities_legal()
    check_dojo_layout()
    for leader in LEADERS:
        name = leader.title()
        block_start = VIP.split(f"SaffronCity_FightingDojoVIP_EventScript_PRUHeist{name}::", 1)[1]
        block = block_start.split("\nSaffronCity_FightingDojoVIP_EventScript_PRU", 1)[0]
        farewell = f"msgbox SaffronCity_FightingDojoVIP_Text_PRUHeistNext{name}"
        assert farewell in block, f"{leader}: farewell text missing"
        assert block.index(farewell) < block.index("fadescreenswapbuffers FADE_TO_WHITE")
        assert block.index("fadescreenswapbuffers FADE_TO_WHITE") < block.index(f"setflag FLAG_PRU_HEIST_{leader}")
        assert block.index(f"setflag FLAG_PRU_HEIST_{leader}") < block.index("fadescreenswapbuffers FADE_FROM_WHITE")
    assert "Earn them ALL at" in ROCKET, "Rocket must demand every badge be earned at the Dojo"
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
    assert "AI: Smart Trainer / Prediction / Ace Pokemon" in trainer("PRU_HEIST_GIOVANNI"), (
        "Giovanni's last-slot Mewtwo must be reserved until every other party member falls"
    )
    assert not any(
        "MEWTWO" in event["graphics_id"]
        for event in GIOVANNI_MAP["object_events"]
    ), "Armoured Mewtwo must not appear in the gym before Giovanni's surprise send-out"
    assert "Armour" in GIOVANNI and "Cerulean" in GIOVANNI
    assert "PruIsMewtwoCaught" in GIOVANNI and "clearflag FLAG_HIDE_MEWTWO" in GIOVANNI
    assert "TRAINER_PRU_HEIST_GIOVANNI_HNS" in STAT_CODE
    assert "2 * 120" in STAT_CODE, "Trainer-only 120 base Def and SpDef missing"
    assert "FLAG_PRU_HEIST_GIOVANNI" in INDIGO
    assert "goto_if_set FLAG_PRU_HEIST_GIOVANNI, IndigoPlateau_EventScript_PRUMeowthAlert" in INDIGO, (
        "Giovanni's defeat must unlock the final Rocket showdown, not bypass Jessie and James"
    )

    for location, label in [
        ("PewterCity_Gym_hns", "Brock"),
        ("VermilionCity_Gym_hns", "Surge"),
        ("CeladonCity_Gym_hns", "Erika"),
        ("FuchsiaCity_Gym_hns", "Janine"),
        ("SaffronCity_Gym_hns", "Sabrina"),
    ]:
        src = (ROOT / f"data/maps/{location}/map.json").read_text()
        script = f"{location.removesuffix('_hns')}_EventScript_{label}"
        assert f'"script": "{script}",\n      "flag": "FLAG_PRU_HIDE_GYM_{label.upper()}"' in src
    assert "FLAG_PRU_HEIST_MISTY" in (ROOT / "data/maps/CeruleanCity_Gym_hns/scripts.inc").read_text()
    assert "FLAG_PRU_HEIST_BLAINE" in (ROOT / "data/maps/SeafoamIslands_Gym_hns/scripts.inc").read_text()

    for name, low, high in [
        ("WILL_POSTOBC", 82, 85), ("KOGA_POSTOBC", 83, 86),
        ("BRUNO_POSTOBC", 84, 87), ("KAREN_POSTOBC", 85, 88),
        ("LANCE_POSTOBC", 86, 89),
    ]:
        party = members(name)
        assert all(low <= lvl <= high for _, lvl in party), (name, party)
        assert max(level for _, level in party) == high, (name, party)
    assert "LEVEL_UP_MOVE(80, MOVE_WATER_SPOUT)" in (ROOT / "src/data/pokemon/level_up_learnsets/pru.h").read_text()
    assert "sPRUKyogreLevelUpLearnset" in (ROOT / "src/pokemon.c").read_text()
    assert "sPRUKyogreGen3LevelUpLearnset" in (ROOT / "src/data/pokemon/level_up_learnsets_gen3.c").read_text()
    for leader, city in [
        ("BROCK", "PewterCity"), ("SURGE", "VermilionCity"), ("ERIKA", "CeladonCity"),
        ("JANINE", "FuchsiaCity"), ("SABRINA", "SaffronCity"),
    ]:
        gym_script = (ROOT / f"data/maps/{city}_Gym_hns/scripts.inc").read_text()
        assert f"FLAG_PRU_HIDE_GYM_{leader}" in gym_script
        assert f"goto_if_set FLAG_PRU_HEIST_{leader}" in gym_script
    assert r'\p' in INDIGO.split("IndigoPlateau_Text_PRUGuard:", 1)[1]
    print("PASS: seven Dojo leaders, Giovanni roster and E4 rematch progression")


if __name__ == "__main__":
    check()
