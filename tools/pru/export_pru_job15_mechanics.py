#!/usr/bin/env python3
"""Extract current Job15 PRU species stats/types/abilities/evolution/level moves for RelicDex."""
from pathlib import Path
import json,re,collections
ROOT=Path(__file__).resolve().parents[2]
ORDER=re.findall(r"^\s*(SPECIES_[A-Z0-9_]+),\s*//\s*(\d{3})\s+([^\r\n]+)",(ROOT/"src/data/pokemon/pru_dex_order.h").read_text(),re.M)
source={}
where={}
def find_entries(text):
    # Most species definitions are explicit bracket-indexed C structures.
    pat=r"\[(SPECIES_[A-Z0-9_]+)\]\s*=\s*\{"
    for m in re.finditer(pat,text):
        level=1;i=m.end();start=i
        while i<len(text) and level:
            c=text[i]
            if c=="{":level+=1
            elif c=="}":level-=1
            i+=1
        if level==0:yield m.group(1),text[start:i-1]
for path in (ROOT/"src/data/pokemon/species_info").glob("*.h"):
    text=path.read_text(encoding="utf8")
    for name,block in find_entries(text):
        source[name]=block
        where[name]=str(path.relative_to(ROOT)).replace("\\","/")
learnsets={}
for path in (ROOT/"src/data/pokemon/level_up_learnsets").glob("*.h"):
    text=path.read_text(encoding="utf8")
    for m in re.finditer(r"static\s+const\s+struct\s+LevelUpMove\s+(s[A-Za-z0-9_]+)\[\]\s*=\s*\{(.*?)LEVEL_UP_END",text,re.S):
        moves=[{"level":int(level),"name":" ".join(x.title() for x in move.split("_")),"code":move} for level,move in re.findall(r"LEVEL_UP_MOVE\(\s*(\d+)\s*,\s*MOVE_([A-Z0-9_]+)\s*\)",m.group(2))]
        learnsets[m.group(1)]=moves
def first(body,pattern):
    r=re.search(pattern,body,re.S)
    return r.group(1) if r else None
def friendly(token):
    return " ".join(x.title() for x in token.split("_"))
def evolve(body):
    raw=first(body,r"\.evolutions\s*=\s*(EVOLUTION\s*\(.*?\))\s*[,;]")
    if not raw:return [],""
    evos=[]
    for m in re.finditer(r"\{\s*(EVO_[A-Z0-9_]+)\s*,\s*([A-Z0-9_]+)\s*,\s*(SPECIES_[A-Z0-9_]+)([^}]*?)\}",raw):
        method,param,target,extra=m.groups()
        targ=friendly(target.removeprefix("SPECIES_"))
        if method=="EVO_LEVEL":
            desc=f"Level {param} to {targ}"
        elif method=="EVO_ITEM":
            desc=f"Use {friendly(param.removeprefix('ITEM_'))} to evolve into {targ}"
        elif method=="EVO_TRADE":
            desc=f"Trade to evolve into {targ}"
        elif method in ("EVO_FRIENDSHIP","EVO_FRIENDSHIP_DAY","EVO_FRIENDSHIP_NIGHT"):
            desc=f"High friendship to {targ}"
        elif method=="EVO_LEVEL_MOVE":
            desc=f"Level up knowing {friendly(param.removeprefix('MOVE_'))} to {targ}"
        else:
            desc=f"{friendly(method.removeprefix('EVO_'))} ({param}) to {targ}"
        conditions=re.findall(r"\{\s*(IF_[A-Z0-9_]+)\s*,\s*([A-Z0-9_]+)\s*\}",extra)
        if conditions:desc+="; "+", ".join(f"{friendly(k.removeprefix('IF_'))}: {friendly(v.removeprefix('TIME_'))}" for k,v in conditions)
        evos.append({"method":method,"param":param,"target":target,"conditions":conditions,"description":desc})
    # Nested conditions can occur after the target brace in EVOLUTION(...).
    # Retain source code verbatim and annotate the common single evolution.
    all_cond=re.findall(r"\{\s*(IF_[A-Z0-9_]+)\s*,\s*([A-Z0-9_]+)\s*\}",raw)
    if len(evos)==1 and all_cond:
        evos[0]["conditions"]=all_cond
        evos[0]["description"]+="; "+", ".join(f"{friendly(k.removeprefix('IF_'))}: {friendly(v.removeprefix('TIME_'))}" for k,v in all_cond)
    return evos,raw
# Expand the native PJR macro-written species definitions; these are real PRU
# species-info declarations rather than stale RelicDex historical defaults.
pjr_text=(ROOT/"src/data/pokemon/species_info/pjr_families.h").read_text(encoding="utf8")
for macro in re.finditer(r"\b(PJR_FINAL_SPECIES|PJR_RED_SPECIES)\s*\(\s*(SPECIES_[A-Z0-9_]+)\s*,",pjr_text):
    typ,sp=macro.group(1),macro.group(2)
    i=pjr_text.index("(",macro.start())+1
    depth=1;quoted=False;escape=False;args=[];part=[]
    while i<len(pjr_text) and depth>0:
        c=pjr_text[i]
        if quoted:
            part.append(c)
            if escape:escape=False
            elif c=="\\":escape=True
            elif c=='"':quoted=False
        elif c=='"':
            quoted=True;part.append(c)
        elif c=="(":
            depth+=1;part.append(c)
        elif c==")":
            depth-=1
            if depth:part.append(c)
        elif c=="," and depth==1:
            args.append("".join(part).strip());part=[]
        else:part.append(c)
        i+=1
    if part:args.append("".join(part).strip())
    if len(args)<21:continue
    name=args[12] if typ=="PJR_FINAL_SPECIES" else args[10]
    ability_tokens=args[9:12] if typ=="PJR_FINAL_SPECIES" else [args[9]]
    moves_ptr=args[23] if typ=="PJR_FINAL_SPECIES" else args[19]
    fields=[f".{key} = {value}," for key,value in zip(["baseHP","baseAttack","baseDefense","baseSpAttack","baseSpDefense","baseSpeed"],args[1:7])]
    fields+=[".types = MON_TYPES("+", ".join(args[7:9])+"),",".abilities = {"+", ".join(ability_tokens)+"},",
             ".speciesName = _("+name+"),",".levelUpLearnset = "+moves_ptr+","]
    source[sp]="\n".join(fields)
    where[sp]="src/data/pokemon/species_info/pjr_families.h ("+typ+")"

rows=[]
for species,n,order_name in ORDER:
    block=source.get(species,"")
    disp=first(block,r'\.speciesName\s*=\s*_\("([^"]+)"\)') or order_name
    types=re.findall(r"TYPE_([A-Z0-9_]+)",first(block,r"\.types\s*=\s*MON_TYPES\((.*?)\)") or "")
    abilities=re.findall(r"ABILITY_([A-Z0-9_]+)",first(block,r"\.abilities\s*=\s*\{(.*?)\}") or "")
    abilities=[friendly(x) for x in dict.fromkeys(abilities) if x!="NONE"]
    stats={}
    for field,output in [("baseHP","hp"),("baseAttack","atk"),("baseDefense","def"),("baseSpAttack","spa"),("baseSpDefense","spd"),("baseSpeed","spe")]:
        v=first(block,r"\."+field+r"\s*=\s*(\d+)")
        if v:stats[output]=int(v)
    mp=first(block,r"\.levelUpLearnset\s*=\s*(s[A-Za-z0-9_]+)")
    moves=learnsets.get(mp,[]) if mp else []
    evos,raw=evolve(block)
    rows.append({
        "dex":int(n),"species":species,"name":disp,"order_name":order_name,
        "types":[friendly(x) for x in types],"abilities":abilities,"stats":stats,
        "moves":moves,"move_pointer":mp,"evos":evos,"evolution_raw":raw,
        "source":where.get(species),"parsed":bool(block),
    })
out=ROOT/"docs/RelicDex/PRU_Job15_450_Mechanics.json"
out.write_text(json.dumps(rows,ensure_ascii=False,indent=2),encoding="utf8")
c=collections.Counter()
for x in rows:
    for key in ("parsed","abilities","types","stats","moves","evolution_raw"):
        if x[key]:c[key]+=1
print("MECHANICS_EXTRACTION_450",dict(c))
print("UNPARSED",[ (x["dex"],x["name"]) for x in rows if not x["parsed"]][:90])
print("NO_MOVES",[ (x["dex"],x["name"],x["move_pointer"]) for x in rows if not x["moves"]][:75])
print("SAMPLE",[x for x in rows if x["name"] in ("Sylveon","Gemlin","Mewduo","Scarabub","Fortotoise")][:5])
