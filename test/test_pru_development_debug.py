"""PRU alpha debug policy: no overworld debug shortcut in any build."""
import re
from pathlib import Path

config = Path("include/config/debug.h").read_text(encoding="utf-8")
global_config = Path("include/constants/global.h").read_text(encoding="utf-8")
start_menu = Path("src/start_menu.c").read_text(encoding="utf-8")
workflow = Path(".github/workflows/pru-clean-build.yml").read_text(encoding="utf-8")

def setting(name):
    match = re.search(r"^#define\s+" + name + r"\s+(\S+)", config, re.MULTILINE)
    assert match, f"Missing debug setting: {name}"
    return match.group(1)

assert setting("DEBUG_OVERWORLD_MENU") == "FALSE", "Public alpha must disable R+START debug"
assert setting("DEBUG_OVERWORLD_IN_MENU") == "FALSE", "Keep the normal Start menu intact"
assert setting("DEBUG_OVERWORLD_HELD_KEYS") == "(R_BUTTON)", "Expected R+START shortcut"
assert setting("DEBUG_OVERWORLD_TRIGGER_EVENT") == "pressedStartButton"
assert "#define DISABLED_ON_RELEASE FALSE" in global_config
assert "#define DISABLED_ON_RELEASE TRUE" in global_config
assert "if (DEBUG_OVERWORLD_MENU == TRUE && DEBUG_OVERWORLD_IN_MENU == TRUE)" in start_menu
assert "make hns -j2 -O" in workflow, "Development ROM must use normal (non-release) HNS build"
assert "python3 test/test_pru_development_debug.py" in workflow
print("PRU_ALPHA_DEBUG_POLICY_PASS: R+START disabled in all builds; start menu unchanged")
