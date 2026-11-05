#!/usr/bin/env python3
"""Export canonical 450 PRU Job15 front battle sprites, using active GBA style."""
from pathlib import Path
from PIL import Image
import csv,hashlib,json,re,zipfile
ROOT=Path(__file__).resolve().parents[2]
txt=(ROOT/"src/data/pokemon/pru_dex_order.h").read_text(encoding="utf8")
order=re.findall(r"^\s*(SPECIES_[A-Z0-9_]+),\s*//\s*(\d{3})\s+([^\r\n]+)",txt,re.M)
assert len(order)==450
def key(s):return re.sub(r"[^A-Z0-9]","",s.upper())
graph={}
pat=r'const\s+u32\s+gMonFrontPic_([A-Za-z0-9_]+)\s*\[\s*\]\s*=\s*INCBIN_U32\s*\(\s*"([^"]+?)\.4bpp\.smol"\s*\)'
for fp in (ROOT/"src/data/graphics").glob("*.h"):
    for name,path in re.findall(pat,fp.read_text(encoding="utf8"),re.S):
        actual=ROOT/(path+".png")
        if actual.is_file():graph.setdefault(key(name),[]).append((name,path,actual))
out=ROOT/"docs/RelicDex/Final 450 Front Sprites"
out.mkdir(parents=True,exist_ok=True)
for fp in out.glob("*.png"):fp.unlink()
rows=[];errors=[]
for symbol,n,name in order:
    n=int(n)
    stem=symbol.removeprefix("SPECIES_")
    stem={"UNOWN":"UNOWNA","CASTFORM":"CASTFORMNORMAL","DEOXYS":"DEOXYSNORMAL"}.get(stem,stem)
    candidates=graph.get(key(stem),[])
    fixed=[v for v in candidates if "/prl_authoritative/" in v[1] or "/pru_" in v[1]]
    gba=[v for v in candidates if v[1].rsplit("/",1)[-1].endswith("_gba")]
    chosen=(fixed or gba or candidates)
    if not chosen:errors.append((n,name,symbol,"no graphics symbol"));continue
    label,p,fp=chosen[-1]
    im=Image.open(fp)
    if im.width<64 or im.height<64:errors.append((n,name,symbol,"small "+str(im.size)));continue
    if im.mode not in ("P","RGB","RGBA"):errors.append((n,name,symbol,"mode "+im.mode));continue
    frame=im.crop((0,0,64,64))
    if frame.mode=="P":
        if max(frame.getdata())>=16:errors.append((n,name,symbol,"over 16 colors"));continue
        frame.info["transparency"]=0
    elif frame.mode=="RGB":
        rgba=frame.convert("RGBA");bg=rgba.getpixel((0,0))
        rgba.putdata([(*c[:3],0) if c[:3]==bg[:3] else c for c in rgba.getdata()])
        frame=rgba
    clean=re.sub(r"[^A-Za-z0-9._-]+","_",name).strip("_")
    filename=f"{n:03d}_{clean}.png"
    dest=out/filename
    frame.save(dest,optimize=True)
    rows.append(dict(dex=n,name=name,species=symbol,filename=filename,source_png=str(fp.relative_to(ROOT)).replace("\\","/"),front_pic_symbol=label,sha256=hashlib.sha256(dest.read_bytes()).hexdigest(),colour_mode=frame.mode,original_frame=f"{im.width}x{im.height}"))
if errors:
    print("FRONT_RESOLUTION_ERRORS",len(errors))
    for problem in errors:print(problem)
    raise SystemExit(1)
assert len(rows)==450 and [r["dex"] for r in rows]==list(range(1,451))
for s in ("Fortotoise","Gemlin","Scarabub"):
    r=next((x for x in rows if x["name"]==s),None)
    assert r and "/prl_authoritative/" in r["source_png"],r
with (out/"FRONT_SPRITES_MANIFEST.csv").open("w",encoding="utf8",newline="") as f:
    w=csv.DictWriter(f,fieldnames=list(rows[0]));w.writeheader();w.writerows(rows)
(out/"FRONT_SPRITES_MANIFEST.json").write_text(json.dumps(rows,ensure_ascii=False,indent=2),encoding="utf8")
(out/"README.md").write_text("# Final 450 Front Sprites (PRU Job 15)\n\nExact GBA-style Job 15 battle front first frames in PRU Dex order. All exported as 64x64 PNGs. See manifest for source path and SHA-256. No icon images or historical placeholder sprites are used. This export does not imply PC icon QA completion.\n",encoding="utf8")
zpath=ROOT/"docs/RelicDex/PRU_Job15_Final_450_Front_Sprites.zip"
with zipfile.ZipFile(zpath,"w",zipfile.ZIP_DEFLATED,compresslevel=9) as z:
    for f in sorted(out.iterdir()):
        if f.is_file():z.write(f,arcname="Final 450 Front Sprites/"+f.name)
print("JOB15_FINAL_450_EXPORTED",len(rows),"ZIP",zpath.stat().st_size)
print("EXAMPLES",[(r["dex"],r["name"],r["source_png"]) for r in rows if r["name"] in ("Bulbasaur","Fortotoise","Gemlin","Scarabub","Sylveon","Coelossus","Deoxys")])
