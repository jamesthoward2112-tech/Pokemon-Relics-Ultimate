from pathlib import Path
import zipfile
root=Path.home()/"PRU-Job13-Fortotoise"
out=root/"docs/RelicDex/PRU_Job15_Source_Trainer_Encounters_Art.zip"
files=[]
patterns=[
"src/data/wild_encounters.json",
"src/data/trainers_hns.party",
"src/data/trainers_frlg.party",
"src/data/trainers.party",
"src/data/pokemon/pru_dex_order.h",
"src/data/pokemon/species_info/*.h",
"src/data/pokemon/level_up_learnsets/*.h",
"src/data/graphics/pokemon.h",
"src/data/graphics/pjr.h",
"src/data/graphics/pru_pokemon.h",
"graphics/trainers/front_pics/*.png",
"graphics/trainers/palettes/*.pal",
"graphics/pokemon/charizard/gmax/*",
"graphics/pokemon/prl_authoritative/*/front.png",
"graphics/pokemon/prl_authoritative/*/normal.pal",
"graphics/pokemon/ho_oh_relic/*.png",
"graphics/pokemon/ho_oh_relic/*.pal",
"graphics/pokemon/articuno/*/*.png",
"graphics/pokemon/zapdos/*/*.png",
"graphics/pokemon/moltres/*/*.png",
"graphics/pokemon/kyogre/primal/*",
"graphics/pokemon/groudon/primal/*",
"graphics/pokemon/rayquaza/mega/*",
"graphics/pokemon/deoxys/*",
"graphics/pokemon/mewtwo/*",
"graphics/pokemon/mew/*",
"graphics/pokemon/celebi/*",
"graphics/pokemon/regirock/*",
"graphics/pokemon/regice/*",
"graphics/pokemon/registeel/*",
"graphics/pokemon/latias/*",
"graphics/pokemon/latios/*",
"graphics/pokemon/jirachi/*",
"graphics/pokemon/ho_oh/*",
"graphics/pokemon/unown_eye/*",
"graphics/pokemon/p_birds/*",
"graphics/pokemon/p_bird/*",
]
for pat in patterns:
    files.extend(p for p in root.glob(pat) if p.is_file())
unique=sorted(set(files))
with zipfile.ZipFile(out,"w",zipfile.ZIP_DEFLATED,compresslevel=8) as z:
    for p in unique:z.write(p,arcname=str(p.relative_to(root)).replace("\\","/"))
print("SOURCE_SNAPSHOT",out,len(unique),out.stat().st_size)
