"""Guard the exact TRE Mewtwo-Arm sprite and Giovanni-only battle override."""

from hashlib import sha256
from pathlib import Path
from struct import unpack_from


ROOT = Path(__file__).resolve().parents[2]
SPRITES = ROOT / "graphics/pokemon/mewtwo/armoured"

SOURCES = {
    "source_front.png": (64, 64, "0ca6986cecae61fe10156ae6c9e29b181d444ad623845366a5d813c3ff8d8918"),
    "source_back.png": (64, 64, "cd387c829f645cf39f7ae3f5485a034848ba005f66469090b2bd83f4b118e1ec"),
    "source_icon.png": (32, 64, "40cc05cdf21d381237d1aba185524cfdd81808fe0a3438061ae0efeab0d4f727"),
}


def dimensions(png: Path) -> tuple[int, int]:
    data = png.read_bytes()
    assert data[:8] == b"\x89PNG\r\n\x1a\n", f"not PNG: {png}"
    return unpack_from(">II", data, 16)


def check() -> None:
    for name, (width, height, expected_sha) in SOURCES.items():
        path = SPRITES / name
        assert path.is_file(), f"missing authentic TRE donor sprite: {name}"
        assert dimensions(path) == (width, height), f"wrong TRE sprite size: {name}"
        assert sha256(path.read_bytes()).hexdigest() == expected_sha, f"TRE donor modified: {name}"

    for name, size in (("front.png", (64, 64)), ("back.png", (64, 64)), ("icon.png", (32, 64))):
        path = SPRITES / name
        assert path.is_file() and dimensions(path) == size, f"missing GBA-ready {name}"
    assert (SPRITES / "normal.pal").is_file(), "battle-only palette missing"

    gfx = (ROOT / "src/graphics.c").read_text()
    battle = (ROOT / "src/battle_gfx_sfx_util.c").read_text()
    species = (ROOT / "src/data/pokemon/species_info/gen_1_families.h").read_text()

    assert "gPruArmouredMewtwoFrontGfx" in gfx and "gPruArmouredMewtwoPalette" in gfx
    assert "IsPruGiovanniArmouredMewtwo" in battle
    assert "TRAINER_PRU_HEIST_GIOVANNI_HNS" in battle
    assert "DecompressDataWithHeaderWram(gPruArmouredMewtwoFrontGfx" in battle
    assert "paletteData = gPruArmouredMewtwoPalette" in battle
    assert ".frontPic = gMonFrontPic_Mewtwo," in species, "ordinary cave Mewtwo art changed"
    assert ".palette = gMonPalette_Mewtwo," in species, "ordinary cave Mewtwo palette changed"
    print("PASS: exact TRE slot 0922 art, Giovanni-only Armoured Mewtwo visual, ordinary Mewtwo unchanged")


if __name__ == "__main__":
    check()
