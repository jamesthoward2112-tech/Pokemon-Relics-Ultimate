"""Guard the E20 reward, professor summit and separate Ho-Oh catch routes."""
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
def source(path): return (ROOT / path).read_text()

class E20FinaleStoryTests(unittest.TestCase):
    def test_relic_oak_requires_e20_and_completed_six_clues(self):
        s=source("data/maps/MtSilver_SummitDay_hns/scripts.inc")
        block=s.split("MtSilver_SummitDay_EventScript_SyncRelicOak::",1)[1].split("MtSilver_SummitDay_EventScript_SyncOakDone::",1)[0]
        for flag in ("FLAG_PRU_ELITE18_CLEARED","FLAG_PJR_RELIC_RAIKOU","FLAG_PJR_RELIC_ENTEI","FLAG_PJR_RELIC_LUGIA","FLAG_PJR_RELIC_UNOWN_I","FLAG_PJR_RELIC_CELEBI","FLAG_PJR_RELIC_SUICUNE","FLAG_PJR_RELIC_ALPHORACLE","FLAG_PJR_GOT_RAINBOW_CREST"):
            with self.subTest(flag=flag): self.assertIn("goto_if_unset "+flag,block)
    def test_oak_battle_and_single_relic_capture(self):
        s=source("data/maps/MtSilver_SummitDay_hns/scripts.inc")
        self.assertIn("TRAINER_PRU_E18_18_A_MASTER_HNS",s)
        self.assertIn("seteventmon SPECIES_RELIC_HO_OH, 85",s)
        self.assertIn("goto_if_set FLAG_PJR_RELIC_HO_OH, MtSilver_SummitDay_EventScript_OakEpilogue",s)
        self.assertIn("setflag FLAG_PJR_RELIC_HO_OH",s)
        self.assertIn("setflag FLAG_PRU_RELIC_OAK_EPILOGUE_COMPLETE",s)
        self.assertNotIn("special GameClear",s)
    def test_oak_overworld_and_original_tin_tower_stay_intact(self):
        import json
        o=json.loads(source("data/maps/MtSilver_SummitDay_hns/map.json"))
        oak=[x for x in o["object_events"] if x["script"]=="MtSilver_SummitDay_EventScript_RelicOak"]
        self.assertEqual(len(oak),1)
        self.assertEqual(oak[0]["graphics_id"],"OBJ_EVENT_GFX_PROF_OAK_HNS")
        self.assertIn("goto_if_set FLAG_PJR_RELIC_HO_OH",source("data/maps/TinTower_RoofDay_hns/scripts.inc"))
    def test_existing_rewards_and_old_saves(self):
        s=source("data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc")
        self.assertIn("giveitem ITEM_MASTER_BALL, 6",s)
        self.assertIn("giveitem ITEM_ANCIENT_STONE, 5",s)
        self.assertIn("call PRU_Elite20_StartFinale",s)
        self.assertIn("goto_if_set FLAG_PRU_E20_CREDITS_SHOWN",s)
if __name__=="__main__": unittest.main()
