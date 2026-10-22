#!/usr/bin/env python3
"""Install owner-approved TRE Articuno-P #955, Zapdos-P #956, Moltres-P #957
on the exact existing Gen-1 species, without assigning new Pokédex entries.
Embedded pristine native 64x64/32x32 donor PNGs avoid a runtime network fetch.
Generated sprites use palette index zero as transparency and ≤16 GBA colours.
"""
from io import BytesIO
from pathlib import Path
from zipfile import ZipFile
from PIL import Image
import base64
import zlib

ROOT = Path(__file__).resolve().parents[2]
BIRDS = ("articuno", "zapdos", "moltres")
DATA = (
    'c-ri|bx>SQxA41>!QCOayF+jtG-'
    '#0E?ydoX4Hn!JG&l(a2@u>pKyV1IL4(8K{!Nb5IrrXrtM2>nR}WQPRQ2rLvaEk=P1k6=LO>({{{EHe>l%N>w!@f01AxB`57uYy;bm{>?c&O1<KgP!#p&i^8?'
    'B+HfQd#1`y9YjQUt$-'
    '{g?XNP>}u(Veh^Q0BD&?U}<gNPcw$%+8ZNeK^qGjE~Mr4o=3EVdZcXiy;!0JsWJ0#GsuL?Xn!yWz08njJ|0gy$bQy#X;Bw#OgXB{Hth4sP+^p;Zt_3z#EO)9'
    'Z<Tu;yozCPVh-^x)b}Bwm?Qg=X0<%s6ua6>?RBWIF)hM1TOoS*s|+P?NreH?Z&`H_%%fu#EQ9jmplyD-'
    '2_0y1CkMK|>YUjdfXMDks&(N2bQyOUSg%)tk44p7CP|!$V=gO1pjGO`JfBc2q96QX|K_!0Mu&UtJ84n`5&STH8~GcIr)-'
    'Z|<Ji^;IbgJ<ckn?8WvLl&hY$JP;)PL>IrPj+0+n)&^6b*o6b@iDe<-64S^zQUlU9n7REkoLC{k-'
    'qOxtYTdd$wqzkQMDn)o1BJ%Yi`hmhA_2{FZkkc`%nQUFajJwbGik|Phj)aZo|*OJU%(42InD-PjlZ<AMc)`C|hkpZV&<z%viX^EB1^Cw~0SQd+jI5_YCftKj'
    '2lGn~3WfU3Ji{ZK|k7+m%B{h5dwL>Cuv{q!>jt}ana6-{?Hgi6+JJ`c{F(T1<s>|e#JlZdB@4~iWG4bJq2F=$)a(68_949RX&cZ-'
    'h`RP{~^H8j`R$HVI!#DUCbfq7RL{bEPq_nqVX9=&*5%FYdkE?~C1lTFmUvco7A&MO<HSk+X_u!<^*Cc*L-X(3=&1oo;AlN>an$-'
    '`{_#>HpqDJAtPiIFw`F>f|v7qiFBUHLp3WqCmuujJExUfCf34#=oVEzaOt8W@kE(NVIbzFd8kwOa2(Dbg(5EYrH+S7diB}pox=5Z1;5=?_KfgPT0VMj*Mj;2'
    '2<O!P9_E=^dC$n9<<@-'
    '}B@+}+n%pfEX^lstmx5b{60z@dTIte7vv9kU5ReDMmeqT8%(@KQ~Qlq%O@d#$9Ng%=qREs$nIqxBm`G@a;^o(*#F#7|#)I1kFXN}rODwg&yACP_=^sZ-qHx|'
    'dl0SkZ7kW2<CA1>uz^p)@f8*hfq;Y+zC+#og0;Zwq>YG|dJ9A$98TbWrfJx<zC%PS42gtTD<eWthHjMH^yTCG|Rd;Z<r@a0?G4SJ026iv&G`d3)2#67WB)+}'
    '<+|w|k=H#Hxd^RUkMzM{9O;E?n|aL$62<AD9!*i^L9j<||C3K3r|r5x;MeVs81gTzHO3?SzX5D)NrhZ-'
    '?BftSoEmSime!h?iI<rgg4tk!fSQ^BMI>l9hwnNhbAPSdxiyxJh!k=c`V)=jcUpqsPSEOIZowA0&AhhAZcpouz?XIPj0zG~nkGaSZ;(7Gh!BnFl$xb$AWApd'
    'xSNmXN63tmuoIzL&@L%l$CN)MY`oyk^UFWc>C;67cO%t2!?VSbyi@jg8I4r3^*P3?SLUkj<0hEUbptH}jB;G+aT4nJP}@@OK|>v2J!BOh9PqIn--0yyl+pO)'
    't%qJ^q_%o@Y$llDN}TXis#?`_#KOG}v$p86Q|TV9L$9lvn~b=GI|daXe2Ro&NM=P`^C0xD~k?t)qnI+tj_`y;C~s`_{=8Ed#i2Vg#$BX*1ZuRj2dqb3wX?xW'
    'qldoWpMA{zCip_2s{lOkZII=wfBvaMRZ}qnZ^w3XSYXfH!+^bo=bvBjHXu+tuzn-'
    'bXm#P7AL}mw!MvisBE_s;Dk9G2APMDV}FX?!0)1lSrBvnQST^E)fLl)9juRUOm(Kc#-+AQh9uPM*s^Q4wzb-M5iK0MXwv&Z{vSMUueyaf`bG-xwC~!-'
    'x5o#vTkdr5Xua7K8`Ta<}EJwRhFNpW0cWso%FsoUZ!<IICZ#HUPvHUES;yr$gwq24PJM8Mz^84HSJp(7mJNKWfl6!@uW6jdvA*ONTi1XR!hv;q%c**Ek#(QV'
    '7n-^VCOdQ$=LqZKG%vfh}O48PZNBw-;uGd-Qbose(rNN|JBKzZGP;di~u`+i5WAoc1<kJ8PY;rLdE)<aQ$O4l051hK?E70r7DQiR@K1?+y+E%4+H{trzNRn='
    'gL_<j!qVTERR!%#Y$~!o6k=Evq`8DkDA_Zt!YY6Pg0FDj%=SYTSUE{4c`nD@C?jcAW!WLT>H4P2PzDtABioVq%oxshvj}6wYY~nN{CQi_)+lNIGj20uz^dyZ'
    'Vd$PEXZyG-jAUGNiQ33ZoC%zoOaxxyzaPGgoOTx>jX2$^Gp*CK8N?lA9h&ECw)Kq541p3Opx?r^sKf<IieQUzv!92nWkz=i5d>Yk#x*L`ax1=j7jLf<&RCrW'
    '+D0py7Pr(=~yq|c?t<2C-'
    'eMvDQlTvyfWS6T}8_6)8${yqFnpB;Y{S{oSJ2`bZ)kknA*Wr^i9w9%lEMem@w7DVgVkp{Kh$|@^7n+3t`l>W8|cKn9k{FqIzJGcWVgc>7oq7tT^mx7a{uQuL'
    '?-N5#rxjMl<;Q>BQKjIoe7IceslQa$thb)K3Puu_d`O%Mi#^nmd@k48G5_y{=zp#nIEtBguC$rckp!SOF37NPR=FQq{u1?<^WPrS~PRA>yw7o-'
    'ZJ#>SAW?C!p(?L3WFeD!ojm;0@73s1r?_st3cAu%)Vw0>Es}t=74t>_hZV9Msr>!e@jodDv9N-d(9As%aHwq!UP`7G+&v=+{xzPXvxaEVHy!6-'
    'bOuITnJR`K&d)b!B%QX6gYyX#?QJrapvOAMWS=K)*_QWvWwzunxl6Ui&MPlik9sa<BGZJ72g^-eD3Zwk@k9?=E(d-'
    'm!1Y&P;X|2uGIuoZ!C+l(^RK>iW4+Y!{J5Q8@xsS$tX^fAcP1CY6c3$Zw_@riV~*)FVb`AohKKW%(v742Fus;Z&@!JPv^(n%F;2WhV4GT*3~7ss~uyRBX)0p'
    'v9+`=HRCQ6ZmmLn3Hh+*nFpo-'
    'm(rCP%|wFWH2xC9w3&3YEet6ns}Rt5zi?Ym0{t`ZEQqXLp3QjxuITaNcO>R<~~Yi)=_N}X|BUpdrW|*u^bhna2|7U<iuhE2%?&t;#s3yl8a*xYXMfLu|%lY_'
    '3%sdgFzq&3X4iE-s1{JjGZ}bzc;!LI5Zw7{7LLs&)+1UtYOGf4bsa|qyHlNGFxF-@w%be?<@Ukg{aXz@7a;j&|F@uK~415o+zzrV)wD*tp-'
    '#V%fPci<Hz?!WSJ>yR5;*H$}apPjUeTwly36q9}?A~f#ZD<VtD;8AH!f&6gLHB-3o~kk@^)SPRUDcfHR!LWW^^U|5g-'
    'QC7_+C;ebWQgl3Z|OutAaMa&=#STO`5bu|j8g}0Tc8+9<Q>=4Nrsb{m{GqKl8ThK)H%b)-'
    ';n=aJMWrA9q*`N)@$Di`3J<9h8Y3)2Z;TNZJzk*Vp2?Ob8zf02&bxOjf@kpG^>sfr}|16V|CU8XfggJd??wnl=PJsmyt?~`@P;+Tlj}z}OW<mag!0lj6Ni;`'
    'Xz#5U3r#a7)rjI6jlBXNGeb!Pfh>kP8vHN(gQ5#I=!xOqjTN-@IR6S*Cvmw<{v8bzV{mmiH2=5syAPPVM^B$k@cs;ZZAyBbHo{=BY_-'
    '{Jnp5c9$`K4UHz7PG&yGn9u;BPW!p&I{^fN}pf0b7_`I{pK|{{Zkm0Q?UC{{z7P0PsHm{0{*C1Hk_P@c(T9+?R$zOAQYIf7|~9fbA_^UH%0CQ~z!M0l=Q`-'
    'dz9y-0pt@@R2T?PZ&2z`^wjD^W<C9%D4&&2aib|@utN`ge_LK%xudB-n2ZNOeGcU6x6%Pq|-x6l?yT<CYtM=ATFZab5hR@bKR>}NGs%-+U%B?-'
    'kc=uBKON)kI}t1at}9q^J$kJz}fbm1kjt0j}n|$c4e?-2LME|NENi*<<E~HQSDTOc&Fq*{%7obw^>6^DawGT8&-!HlxYjjwk#u-'
    'm3NuCZ~^Hr!!H<;Rh<mfw&2DKv|HE5STz=OP$D9toNx&aV)!G|p8BE6is_G13V2!Jj46+oI9iC-ElSEsO1}?ZPA(xwY4lO11Zqkic@*lgedZcJAeFt{L{Xgf'
    'GH)?UDX&=U)ddWV6>HsJ9);q=!>=S&Fc?Nh^<`?18aTFN=j0?|@eI{p&{$M8EF*1q5ya(!4DQxj+d4i6`umm63b!e#R`4N)+eFu=F3CX3!das4!!fYve!w$-'
    'F8GX{Ng$M?hLwrhG5q2&tfq@pst5$0Y%uEF@ij#Ux)h)bdT*3pz6(S3J3Xk5n$HOh?<V&R@+(_g<43rlgOn*G)jN;I8j;AjV!>V$qr`U-'
    'd|_KzNrB*EpJiSsZyhAcit3v4K9D14jGW+<!mB?p1)(#3;W_36-iG)Tq-4N61y4uu_^-'
    '_=Lm2^tj1B;Q8_EARCr>+j7eCW~>wAT<|4FNs2FcntihcEU3ej?U1s#nRilrw2!%WsMy&B2R>}6&;iP}TuPFgfCqt(&4b8>d1KSnUtWP?iJJ`ZIjXg5J=a!h'
    'DC&g}T_YAjO%ugR%i&D!x_-_J4W?_J-MFui{9MRtk!o`GSksoaL}F-'
    'X$wFmR(=i0PGc##ou=#o=%`b%LnUfrie^EvZZf$*$F#QC48Rcm^J*Ad^e{Vx3<jiEc><a8na7gs1AFf85?1yv@~?6ulrle+?J60J?kZC@kAIE8xN|-'
    'sHS`mFu2Ed@x0FT70*_bAizqJT`V)e!8T$Y|Rd@=$wI-DTzvx%$7fAFa7G^o8w{nysro)@`|gm*wdUP08t@XV~aW=0zh?}&8mP|H#?RRM`a}CbNOjDEs}~RN'
    'm*IIo70DHBwbvb*^>Y;G({@rLM=t0l5~q)a9<gF+{n4K_H^!ATDBi<%!ff|2&i|Me_S}hK4FJV8tx#ZeD4(>>6vY(XML&*bTJ_Ube~^ae~?k6|C?Y5+9vOWQ'
    'dODj=;Y*Ees?@QUu|%dpc&NA&!zlX_@1aMb>B8}L>$YH_qyEXBgKKY!Ft#iUrdv(fnD*d`#=<PX5#$1Uyrl#szEc%h2O=F=<?We;7+qENiO8!`Xhv7q9_n=K'
    'e49}<I3eCgGPV7-vcL?_~IbbhnKq77(tj!zmZ5livwvDrCFlH>`f7yiLh5e7~%-!-'
    'jqv(c9`aAID7EsHtOgNJk%M3gcH?2U*|Dx@D}ot=UtQ7%Z_(Vz)>ThC)ps87B16h1JYYXD5qQY!P?N+Axa?q!MX}r>O3x*&ol$aq95`T>XkqKCaolSkTBy)&'
    'da1CQDwD>jj&;d(CF%&P`!ZDXe&A8nDa)1ajXCpu(t@ofh!hNValEq10i#Nf~8mmwic;WL;-Oqy=9sokopzTOWD<tkt(@Qw=e@WdKIL91vz-'
    '&`BSwYbU4qwhvir{peYiZ4+)`vbF4dw^|T7zgPMVq8wtQVj@oE>86e4!JQ*k}6B$bKVh^o=<XIkK;+o|L;*lg*v8&hCfvHSLq;~=wun{|}?~hx_=n4sM5W5^'
    'DzulIYQcAr#s33A9AFwS1i#<Xi$w|q-'
    'NAm_|+crES+|4S8q;8+Aehfnfxehx#1=FGPMn5ghuXCpTYQ~JDz68EJlA~kAf$B0g{1JmkX+cGm{qFUCEY|x%1cr+hcn3iT7D`koEc*sU4tY_o&$m8i&zcT!'
    '(&!=*CpDH24N>R)EHF1QI{8BhrOK7mabWUp5E^iw?{V^+wR~#3T9HEerM7=_`oNN1wRXbRApD}mX5r3{%?v(C?#XHo!wZgbPE=%SlyLm7bHY4NIf6WeFVVfd'
    'XtVl}5OQ#Ev0(J`ey4U+A0{QmA$%}Y8ix<#=-kNH{B~;n%n!Rk_y9eqjau1%=~zAxl(UQrm^mNgPT5loWex~c%q6QG2syo65C(tZ?dc!Iq*EqKI5_8>-'
    '(mlb%kpucw^<dYR$KU}4&=sBeW8S2iL1}AEI9J6Q5c2!nBR^#q-'
    'IKHO5|akpci&By|R7HM(t|>DGen1#GWIqNx&TA7$R5R9e%pj?hG5zr1QCueD=VJljk(h_euLV)%#*bCOC{bs)(`JOTEod9PK`q$Dq8+HJ2p;^<J5`_*(k8@?'
    'VqARl#J>o7bi}b0?jOfjT-'
    'm1MbUqlyl3sw04dr(s$c%u^^aTXuIj8m5A#w9Hn+H?NpSg!wlE0#`JXtXt}|W*~M`F{*T#75nW|=bU?|pOv!YpKE;ji*QBtrvXHH{pgRVl+h1GsYR>V2U=2)'
    '~C&~}|g)TjeKw}!0i(vr*s$6-<y92Vwqbj{@|8O;_r`@xwX)ZOr@bm(mPZn!+?Sj|Lv&~&n)E4h5*wy_V&`c>bzLA8aLTjk?MP!+Lwt|ksrF6UU@FO3-'
    'R{B}UlnX`F2jm8xFI8?3)P{n;;gp&u3xQ;7@?)H$&xi+Y_^pIHX}vrYq&z`;b;tNUi_3IL@elWZrWDB6*~B{`%=36t_AB*K6^+7VjUI$&)b-{f-'
    '+61BoSSEp&Lkg`z2C~w44&qFB>l7P*r2{b(em`Q(wt|Z*ZiJsYVUZZQ8X>6=&0R;a$9tGbLd=JeZ(gD5#rG=<-'
    'XK%&<h7{HvcHjQy9QREfUFTfl%5=20+>*`hS#6i-_b9(Q)DJO6zLYkpa5qy4jQ=Su<aD+qg%ybc@b-'
    'uM@oBlG{+e6Lbs?9%!xCc2jje?~^xlZfH<*qJ^%#Apj+8c2%%48(@z6;OJ9E8+99JTRAmbR9~kv0%kl5mIkIOSKLL-'
    '214)7f7%{H?#)uuZQPf7oLhf{7DvI<&-@F0y*_=Au=;wkd$ujK(ho%Z@?{M=-'
    'P0}NXE$E=#l*0JdpP>i*vAwZne~Wd_M8HN?L;{A){{>NbfRumF(E}StAHD0m@F)HHCVUA)+~nOnO?<^AW;&-rbJ^Ke>>r<modo?i*X(3(587Vmamw-'
    'q)z^MfACg=?)rt-hF(omqlRN^lr+58bw^9!!+~G7A;=be^NYWqoAQDrh-V?SMYb43PNF{{F2-@(HTd1((4w<ANz(W*{ln7R(eohc891?9kN%_<BJB2n__kv-'
    'H~=QqL#NCY9iqlc4L+vsn58yYF4or{q@?fH(2HbepTm)6(aoJtoUg6p?F;=nq*Nic)cvzIX9Bsr1N5T&kC#Ex$N7h*(zUrt%f#;}*g!h}wizy8R{5EC`B*Vm'
    '`6OI5d=&KLufSR@%|~^zxCDgvP(xj0`x&?dwfgF3)%Gc4VKM!en%!vkS6*&RldE@>=tA7z_560OdEi$v;avKC16E(`g`jcda>wmh4-'
    'ln_R~Qb2tQ4b~O;rCq4LG-JTqqDu=Z-%-^@WCZa=;R@hA@Xq@VBnxhlZVx8h;ZqJbGzN{v!nvKSl^QEFrTfq&nM@LljVRT@qmVZM7G-'
    'LJ+MU0tovpxIgJ>Q@NLlKst$cnTUoWz2m|Lr+ILTA4yeHk*ueJG7Q5*P}h6UOVC^wr7=+{+t%=Vq9T*A5pansHIY_1HoTI>iKJ#$c3$Uh2c20+Q;>GOS{1Z4'
    '&#tB1puGiugH-x8HcDN}cCNj#+To%z75$1Vkra(?N|e9<t;w0^JVi;Y-'
    'kkR+whzBKv_z8l?ZA)JlC`LZo?}sU5KGGQ>BHBQMLQmAjPgKgYD_4D3nofjHSNt0OM*ex@1&UVZ*TNihvB$~y@s-}K5uIdBG7mPRml-'
    '6EePT079`McCwbXk*2t&&_xrfYqtaWx-59m+^|+L$is@0z+|CiY&K=0H&vGQ5t^|%9UCjIH>m+#Hdo)~Qun>8gaN&V^{Y#MC!tjS)n-'
    'J#LMJYQxQ}=MaCK;?U?{0b=CC8p)j`1!1q-n=GCCPM!FDQ!gBK-Xn6v3a;1lrji5Yjfg=b!ldQ%7w0VW*Nh4hGsg7@g32fQVj%J~{fDlEeaiZ%NvF$e5;V`N'
    '$G@0{p}{<3{0c>TcXz_$CgkvUK>@>rwWp9x&oA(leP)L)T$qtr+<jkNawaD#RZb2;uqwS??T}xJqQiUake6s7__4)+I@w5dw{M*SZ!TaR2|oGx7fyp8uV%B>'
    'rLNf7tmScK(N*|6%8U*!drJ{)e6aVdsC?`TuHmChAklYld<2--ZM0duQ%u<?8uwU1Udx{3kTG8*+I4h321rQdNUCD}|%HONxmsF#C&(G2%n5xA0?UD#a|%q@'
    'b?>Gh^|4Y0&A?EL9lRak0z4;1lP5l3$CHe~Nv1O`g~HT_DSUH~Yla#z`*K@etvdeGrb?89Zx37Qpb}Xo~qceh_*vI9-'
    'z7C};7ymCLn;4Ef$A$tQ^TCh9Z8<MdXT?n_AkqKV_OvX?)@v35>S<VSEsADSq1eK4qbZE8)X`HU?uozbY?;JSXDrPV^z+o*_0<=*iXM`DBAn+o6#L}@q~!4m'
    'Rz1k$v+PCg7d!KV`TomTG20<?8l$Ltz|uDo~h2TSnM<!s2tH;@+7ETn9)J}Z#a@1}-'
    'KtSY%&sW8r*e0#DAC}!u*!cVMZmMXmN9FSk_Z+P`H`5Y{Rm1X94csq)^_dH|P9*(cjKf>Qo*fQDbS%a1e7u?<ijSVTJI>wq_OJ2{dvaQjZuZqQNEzx4kKBf?'
    '26n$s@m9ZNAv!se-r4CnrTAy|8jXoNadYZ!Ad8aOuhje-NZtC@hD&EfWT270A0QRXU7J(LTlnmx%XXg%SP?c~D$}xKqtGeyp&*l}UrYZ7l%trc9mn-'
    '@<nGWSG`VU(tQ^H2JnjT}H!HUGv!NL2pU|FS%X}cs8kz4O|+%Ci%v1`$Qtxb9akw6_Q=Q=p&EDkw7o6w*EX)hCe*ZrUcUZ81A=Ev*(<+;t(9}-'
    '|(hXqm>4sdQPx#~9#dh?+}1<OkJ_y?~v)`Y}Oh!3RqL?{Zmz_%B?uC+0|Ak(}%CnkH)D`P)S04lz&qJF+?VjA+qO$xV;EV*9chT7Ytf2tt1vQr2=fKa-'
    'GuDO3ezM(+=Rx6dY0A1W_xRDg8q7kY3xX3r^EJ1cR_?%_S0G;%!RGcqWSLfLP<G_JSr-ufV8h9r~0S%n8tVH#ijnWGwrSM5TmH1iY8D8JkpMM-'
    'Dij<-QR=DoI6NHQe6NKM#v*H`4Z&TJ4bqJ7I2J#jLt~xa-@)>qCF{rpW>z%ZGW~BG){exWTqDIsg_-ba5O>tz4@U+|ddiWBu$1ZnnSNo8|O@`20kdb;utu6B'
    '<t{p?fZy}j}M0j!?N(qr)g$NBzNGx=u72HF%37TH*_LsaM;(;iB5K|XYe)gn#+U?k&5>no(A%7fszvfPlTFx+-'
    '*CK$J?x|Ple>=rPcA`5N|0Bu#9Kadsmm6OdV%lA&RiT1Uro$1mOT>>##VGlf0pDv*b!$2Y)ww*3*D!wqh7pdZ{C>ALR>Mn$%i@JlFTINy^=zcQz@j_b$TK`?'
    '`N2|;?)wYK0ATW)3YaTca68*}3W+sw56)WHIlUvWyu(>H=QcD3W&&X%@MlOYY5KrVm}zF)YgY|#6u$0}&^utTCpv!3H!>hV9_XUoU|E06a7LVJJ3Ep?C9M>3'
    '%MV*vt5hRm!tOok(~1xXl46-X_PS3AsoXnpsFF<g8g%@C5(BjG@%yc^CJC2hRu&Iphmk@;A9_!*2Hqt8xDOk?m6Rcu`fQyZL-Rd!Qtu|h84OcQJUsB}3pKV>'
    '%D89p>5;R`i*?X~!8tMpJQ(I#uk|}Osq@;_>_qyMz9i)>FAjd`-'
    '(4X1W4+;dQtCo4*<AmTzokrmfo$vHB8Bvehi`LKmu1D8I}Ve+b)*+mEbF1wJ?3~6UJYN!)9JLq+kB2A))_6Z?s8&)21EifKc?f<(L(IpTraf6axUU=o2=b-'
    '<VP}~A`*gz_qIOSZK~cxnKWo9CjRIdKXvq=ut1$YZ_8h#-'
    'K5vz1Izx|WY&!+>evR6ZWR0O!AwDsuk{z4vPs7$j;+{JvDV(~Q`|Ml_I_iLHzJ<tV+`haJtsmx`RxRaSbADm3iLL<TYL~>)s6qiB4yL#>6s7!rR?5r`_8u<?'
    'kDH7KkF878TF^_{Z+JZOVah6Buv~aGPS?IdHw9(Hrhkb?{#C|CrCvp!{)B|^2eS>xJu_-VASc8uwbsO&!1KH2?<SA!$i)O^Ix(w(a!b9pQBm`4J!RlK^nY|z'
    'pJ@q^OeG70JU7ja}df^zPFsBn{ebbc#;&M^lEqO5(kX{tNzlwAZl=l0lLiEPR-'
    '^J!+<@G{_06eoT^J<srn9&X+gIpyC=URPJYhI=;Cln#M0gM_8zd>K_Srndd)+LvhhWcnqBH;pzKV8i*tNeG^MHd&#~q)8NW&d^%7%+IEh=TP-'
    '3g^k2+W>Wh&ES>EHRZ?>dhWyiJo#zx~Lfw5mVe{zM)ha+0@77F`k6u~8Ar-CR$I+f?tABAWr$^9TPpm)TPs#K-'
    '?qOHhf8zU7y&+wFQ9is7?IK1a1in~ip|Cc#o6L**Bg^R&C?bq^j1q|{_=lsX7A;5%im!P<71*t+$G#<A<Tn<ObggP(3~_f}!brnKSpZ~0MzNoBqmaQpTgp*N'
    'Cg@5c9M8>ZhhW1<+98LfKornH_=hS<P(o}~MuJ82^adho*;GVnX|`8alRuD#Q~CPF^DQ*9-'
    'Se(tWi>(miBGBWZsVV@Vx=)&n!i$G>3)XJXF4}b2b?Cah^>3guR8resf?$fM)pPu3Xr#{b>M!lO6<7YEP77gGr0#ubAH(Z!feJLLpYX@U<<A2X#y~kF6O>Y*'
    'DZI+CoaV@F?muu07z_VdOElB?HXq$n3SmxR$#EBJ+JmF;lb@0x-M^SkGfSHF!T_eoIUmaO%)sONGAgLk2RyFlgH|_9C@~)q%m&vf-'
    'u5ZP!#{8k7z~>9yw1#(){tGfDo90P_4eHvOobMVg2#ee&O}Gr1$2aESc=`p$lvHBdhDEx|L|A?for5i4@fWt;@mkUTLvOeXd#N6zN|$dXEk@*czi;+6@9<Xz'
    'lbPIb<C<e=vOlg-h1<YIi3!WB-sVXLZ@{)b9=3MMNbt%~>==QW!|!aGUWazVD1mW~=m_^|h4^S+MpQN5zn0q|gti9_N-'
    'y;pzi!ogGT|;QS0Y6r2w#FW%gAtYYq2nyhS}er%<oB9nDg${+RRBo%LZ)nnERt0WVID&3I)e%pHf4LSa$|Wrif}aJ38zghg!!T`iNAItS(X~px)y+CtTPkTr'
    '7M$_4+iF+f||G%ma653S}i5^ga(eR)V7(-2WgN$fnjqjuM-'
    '*tqLmbVKr9_cYS_@Lsn>N%?gVJGrhj`Ao0#%Umsq8uhf0{{ItiBfb^W2o12GTXzQooU5}7b{Z3Wv6$)HF{f}7n*le|^$qS$_%{Ob|Gv4BdKr|Y()F+tn-'
    'P};!=H4S)W;*L#{HpTg0kjoDR15O93liXg6mFlK2=d>mTDoYB5Ji8kcW+t5vX2d|3v_%Z-Ti`M%Dtl8^)20c#10HUwqVgIxWo#)aQPZjWP7-'
    'ov||#?m7nyy%;l`&R=f5^1?lH!C;sM!KjgTmHN(OiIiOOJ-jcknm{bgtBo=$O8TnWjLX-SsIgH4_B9yM<*=l0+B-'
    '<NmUg2?cIl^1SSaKYnP#rdzFM*LT)ZqyjM(0(b3azJgas-'
    'K@ca0x=?8*+|`xtl_n>Du}MkU#PN0bn_iBT8bH?*hwei25}HOy|#1gB`7(}r3kb%`9nn(@}DiF@?Dp+OI?bqR#EM^Lvq6(G23z!c3TPD}rVxxH@}SI<&`y3F'
    'GeQwhpX{nVP|ny0-5Pp0p;^9Mxh<Ny-Y?^4?;>X7q;i$2|Uq8X?2H;Ll1m7D5Q&wEUL^mk`$!h8_%=-'
    '?;pB|bp!?f68wEE6}dejV5T?Dic`DdQaaivZ5zhDcJQ`M8ApzUu%LC^eiNPIguZjQxTF@u2A38PMSBFGr<Ts69>}F+g?9>8L+Itv5bxAp!^_d-NjI))xQx`*'
    ')S2;b8ZS<}9*Bp9bGI1l~L^y}$g|n6GX1<CXv!0RA@Y|H1r!qco1R^q-W!ZNTBSq(~CDk7yTTl}5S$QC~jPLlYBWrI24m<_%A;Q8E*E1xHGT;|D(ei-Pj}B<'
    'ESSR&Ml_j6KLh<=Z#ql7@SOo{4=m#qq26tJg(3{K4YA&!pqI4(7<xP;JM?=-38gG2)HzSr7mL60QgiBtYQ=LXCgw;iMs2bi34wV=Q-'
    '&LX_Nn_>#z4k4X?PZ}^huUJ!Erb4~CxZqT*CTy)E)TfZ6dS!(`ToiRA!*c`rY5e|z}DDqq3?Lnpng5VNPmwkd+pFb8rJzr2e=8IHp6)l8n?z&P`H1OJ-'
    '82ED)K=TV=?3suZzF5MA1Kz3G%Hiz5I%qt0CdOBMEomd`nJHS3wx_ANdXy#)nC&Tr;Yx3YXf;F--ReX_y=I`i89+b>IxVxt%t`E^k0wC@N*UPfa(#lLY@J$h'
    '!t?cgY8bHIf3NG(<h&JQ_B+#v?1Owp)NubvURC9?+Y%1qI>kgC2yF|Fo7jsV8g7Iu_T`#w2%j0+nx8t3_LCrgQg6(^*0ubo%E5==R#wC-'
    'S<G!K*NlPG1D;DpK~o5sS(AIdI+Ef^h^wbLu174KR4OLFObt=gE)>U>8w8&MyqbH(eNEELi)$q$PT!+8!3hW!jWtNh1ZiC?%8=}#&{04v$PR^@HwL3lLfN4g'
    '=hQ}TV)LoHK0Yh?AIQ6X<B&#SlvzM{ohd6~geWjGJo)*6A^3*qUOYnq0G1X@CU@Vy`$U;SF75eoG4I=n-'
    '9<<!t)d$BX#&blGRb7jpSPJ}8dD%e#2ASrRNN6d#Ju)HtB#F4rAsC|%OxC-'
    '+n>+$V5hxzLo>__Tyz;Fm!a|9;HQ3nGrs+Ri;!M=p`617;@``!(#j9R_pA~VuSFot<#5PJFFs*Maw&!<G)horb>^DG2B3}OX~2}m0Fa@OfKS90wV38ufs-'
    'J~f=7-'
    'OC!6FPLt+_XH{_R2($BMl&)s2sXmT1(S#=zM`nxL$%(2nA$31u)zhLp{eH6_%;iH01+x0JSnWn;bSLq%u5C2?#grDf<rSZjus6@HuHIfAVsXbBmn=XzK{M~$'
    'wavPK=T>!`g#q-{qTA!<`AyQY8;=hXIiRtciiG71~Ty(L_+nSb)v`D9hgGjO@|1PZPAv(Y|-_yx4PZC$Ejn^!*Yb~7zSf5h}qlgtWlPTq{@zS$-'
    'x^IX^VA(~#%l|HvxMyYRZ%gvXPsmQvESrWpG7?}Ft0BKku}oir*7G)exwUQ-mkd|e?4}^mjIz5uHsa*@(JR_cE9mHeEAh}1_pH#;TUwg9p^wP?6Q{^E9$63y'
    '>+l=YEh9s>lP5%gUMXuaD{bZ6wA1+e_y?j`ZX^wrZ<tUq5C72OI3wgVHnZlR6{0zZ=xgL~nL?IJU9@op_GBsa-Pb2;XZtg3^0`s!>=ad<9~$|6+)~^4*&m{c'
    '3bh=%Ve30UrZDeA&ELNkvy!%x`5<i^(wC_QEZfooID_gHUOBu_0&iMVraPU>Zt^=6I`s-'
    'TZz&n$_$kL(>}^nd_{I?yKi%_`B30jh%C6y82l1y|t{Zb?=5g^=2Jb<HOgf3x62V>1KnvprwGIrJx&LT@tIZQ%KoiKvgw~~_M9J|HS|si<d-u-'
    '^q79v=xuV6KZWuq!(~hk9Y{w?ELd}a`?WLx0dLoNk%rUIdpUh#4j1(l+9DPl6H+&}*0hGa^0!Sw}Z!?0@<Q&i>2+Ie{4GMm)KHSE&h0DOj48HM>wbV!#%So?'
    'TlX~&MQc;6qNq_LNnWLE(Dis1;ME<1Jrw`xH;+~3lC*>`}*(JB7-'
    '{*?iATXd_>0zDT$@OCX1H3jSoepP`W1k0TUiYe1nV!&((492&viVOrnn}X2@$%u38wFG>>H%it5kaLCw@lKR5A%YM<~O9`kXnhzMptq9j{Unucy{9|+*_EFW'
    'FNpayV<NOEY&!#Uu(M8p=LWrl_!5|c;eJJ*5y$YC`<$D1Wbqt?4M_uE9u1iU`}x)LL4&1yo+<ppgJRx?aB!ugE<7N#Y27(ym|}PZB34ZuZ~>K%8ejm{;tzFR'
    'TW!d=am5Fpo#r(AR+VGZ8CAi(z72_^_pTIPdl`>^J*CL;Zg;koZ2;3fX*b4^S1)Iz<04kEkSz}tKfWU&{n(}VFHbsP+EW?^*usNdXdgnFSE1lKwK-'
    '#xbCEFw}u6^4UlbvpH|PG>2)-'
    '=)EJJ}Vyb4C)0Gf!ceO$qB>@z<B&qg#C380T1>^VZ@XxiJ4yFTgk~fENa|`~cp8;pcqG68AUG1Q2M>9#=68g%qq(F^P?6>Lo^M8GSMwCA5&BFu0-'
    '}b)_(0}8$FMQsA-}dG3*^nY=-'
    '|I%K_h2V#)ajSV=J|}*ICxZ6uXu;;piivN9Zi8A<E_Vfj%;S78~!pUa|ChGMP2nom>eZ_r2XVTEv5H2WV~;t<a;pc4c;j({M}<vyZ+E!CtA|?cJn`-'
    'qsp@e*rp8o6#$F1c=mf#E@>5lB4Szu$Zg^6jw6vKfgE0JPzO+rlcAdJ2#~~=tA#|Lgf~Rt=#c;fa>=KBfJPeOca;p+C)aj@re^2k%Sl!^*Pr>(XlR<s(#ra;'
    'SPs5dn8n)QrsogfhQB^ZU7B3d;{w?g=3nB}+NWM!zRsxEyMXAxOJ1sc^Kigro2kG}Zr+i9HJ#&^Aa}1{Z?3FCAlCyv2SIqT<tsn%I?A)-'
    'PI*Q0uSg%z)KOaSe;X5|HdBRrnIfyV^QFP27T*uQMykTRwnG2>#mxA7K9J1^p~bb)<19+xlf$DknkqJIdil+tI5oackB=vaK87!~3SN`Ib!aV&4o>oYrP%%)'
    'b=ggb<I_A4;z(cQ4tfaT+kEh2`^0kkQQ|q}a=isU2)OqT>GqDe*u?@{DUMr*@Y$`|de(iKh{T1X_Q%sumfqePc{fOPIK|@&jvkEqBNkU2K(powqD1DV`w^9y'
    'ip_|eHRb-J2)_7(fO>Zjn_DMx*$=~NlNepuJG)y2H4WjAs81djI6&&bF0$-ciJ5Q%iW-yY8>0D7P1quVkfGt$^sIaAYU|q0b92P-'
    '7b(u!m5ao`QOux+Ul&S;d!2a#aQeaX$l0^93gB|Yg3{LYyo{?>U~{KIQCp3v%6)Du!5riD&qejBK=y&1)q&R47#%e%;g^<K$K*bT@A3jXkw^mGyJ@-'
    'Te*Y5PbLQJt8h1j3gFkagbnzSBBrI56yvbbBk7(y#JHd*~D*6LD0Q_x4|KkMz{vBoX-v2Hci@T92kp&jDnCT)SZ-'
    'X82hBB$MhLc{_{EXI7Q!DDzOL#xXI4!5k0yUUSK~+$(LT3n7H4<_!*kb>lgEHvEu&A|x_aY7~NQ_~6?yZi^oiS5h7;ckavUX6_nRoo-'
    'G>|H`tG~n_4ycg0bzv{=7VVKFnwi*7J^2AO?L>ZwZWr5E{FZpaiam{Jh5F<{Os~V2m3{AoF;Dq(C<EYoCY0SY{Z*UwF2|9$IeyWImfchgGwu0KT<S-'
    '2sy+D8^xc`z3nynrS2F=;xo;~KLHvs0+p#6x6*7MxOmYW+_Vd@!v5}A?8L}=rG@*XxO#S@Y(CnE+`I9z8T7FF8ykn&;ThhSFO9m;{k9c8}caS*zOr%;duq~)'
    '--kl*6%jZAJ$)ECF$W)-'
    '1#0ahyk%J$YqTSB+Op*+_fVpFp9JSA{L)0!(d!5`ogccIrIajo_^h$BMSPVRcdxh8(W0v2UZv?8XUI&Jm`j}9tK61883XdQ)$7eOY#0n#2vH-'
    ';!XcIW79Dxs~nc|LNvXQS^!+jq3ucC68q-0+Mm&9}+A~pT^<H}naj$Jsl$xth0GR;z&$-'
    'R)snL38Q%gNPfo;y+bwA6eV%000Bj)peW;flTuEFr&@+FL=rc8H--{T_FhTq#@|_t$eHx;;S!jT%-hTs%^Aeo7t^C7hSWkY{JF!fK_z@73LFJbemhsZ1NX$-'
    '2yZtvZb*^~h(dPo>rXvz{#OtFNB7hg^L3I7+3OwoUaoew^P=?tcuK3tC)NHY_(Ncg&qACL~%$`#^eG4BX1MPpKH;^YC1+-t&G9iF_E-'
    'a8M@(g<mJq<c&Yk4tnCkR-qYLa$)=uN--WMq~E&r`*HV`Wi;itFs-'
    '^`WFa|pkYiMWZH(i}^x6Gl5Lx}BSF!lY@=j4f!b5*oY*N)x$pGq$%e}=2L+oh4yi{wb)!Wsguo2Nrh1o^Iq&21J^$U7jgCjSGEg!4l^&{n?DyeuzTqvpSa(X'
    'g~)e{$`ZJ0cVvX?<x>&4Ug=Sc_4cf5tm<CVk{XDVkKX%pfC=F4mG{4|4(@{%8wK~~bsjeYTA149M5ZHN+0hxZoZ`Ew`KjXZ`=YIgM@@^qh4UFz8*RL~^JS^f'
    '40VNzKKzj7T1n70Jn4k#N0Q|EXu!~yPrH3im>Xe}j-+Errchbc^8K!yfwRzqDk)1v(xPb8NGmm5lR3$xnMF{!&Y)-'
    'q!#xAzw6;X;EkQII7nN@{FaOlFi&fo84Ql6l>qob(>6Fm74@Pi=<R)y60#Qbq3J>*LrPgx80eIF?UcgYdvZ65+)i1-'
    'bT!qTVkN(fyJ77iz6a0$qP<e>@r=eaIqJ0U8a`QW%p_X0E1R`@RZYeg_BBm{4h4=h~S{pl|!zNl~ufZHsxzt4*Evn_C}k%au}b))x*)i@FiraFtz=^;(q`Bs'
    '~3R2l8`%{3ySie;fCZN&VEjb^C{JS0U;3ZyQ@``O!-M4CFEfx8>Z+v*|lQ2<}jFFG7#~)~q<mEuWYAc6AGL-D1=)j1-'
    '`ZZ;Rp+67OyT(|zc<165bXgI`f}<jJ?XHLiAw2aZ0tK7+T#B(!XH^|GBw;P3?7pPB&VBl-'
    '{m&Q=(;$_<fVqd@hmRqb<Re)yXXR}Iz!0uIC#1wK{eMwq|1mN2%h-'
    'gL|%u$uU;tq$4^`KYV1#3z(%;#qDz{Kq>JwD5^FFfTK_wh%2&*`3@fxpY3H#5UiChz}#W8WO%;{61fyp^#0i!Ws_zwIEo~Np^@?C*UC0z9^`iLBeAF;#<Ec6'
    '=WNQDeC1*m7A@{X<D#>$uL#<_K)q2Kn)g8=&|2hmQ~u7mPp+fuOIW@OJLD--'
    'H)fgH-@gy4sa2UjsY-t@XFV$oha4!t$j(r)#Kb5y$vPoXfu+o<x3KoKEyyY$LnD+nBpI-Bo0TJ{t|8#T@;h-'
    '+gC~UN((a5$6~MuPxnVcX77l);Xi86jmC<bzgyXUT}{s~{!$=@KJAPDB-'
    '%TnFEM&2nsg^MJ7GuO?dM%gD2*r8m{mx`z17AzI+tK;G0yA0<Z5y48&#>gP&f0ZP()pTAZ1?uNhPY(pdeWi!4zPacI8h1qx_1dMob#Sx9<SDDfuf=SlTJNew'
    'r_nV*af?&)}fNQ8)zIGDrVs?OE>gAd!YsEBP5R^cIj<%$gx?JZ6YlAwZh3=5P5T^F|}S^TneWkSq*uS+0HmM^|>EMX?&uP9@J)HSU2O9sARtUY|FGo*+l&_A'
    'enN(;znTK&T{Q>sIs?ldximo&8Hcz}l7>DzOQWGSN#K#LtKi4(3G*FE}8WntZd1Rtam_sEC0%Hv?`{{YZ-'
    'JA8^Jy@Q;S!p5)R?|Ee`<nBu5W+zcN{-ww&v@^wY-vYoywxL#W%H;fR0K8UpM?p@5<2wnSu_j2KHDVlB8H7&?!XYyyy%eP4N%Qj#hJs5m{#Q|N3dHI3z3*Y}'
    '#o{w&@`NygvHaA&3@t`fLl<pEz3b{`$Gtl{NM7WNi#~AE!1@|TH)Aeoypuo067)`<S@~Neth|KwEk+T@o{4j<SZyKv-Xc*R>jH|hxZ(-'
    '4zM3l**p2nCw=N>OkKU1ndzlb5u6t6rHh}g?r-'
    'OzvpGzlBvI{LPq`rRBW^BU5Y#3G8AH=#5>GP;yY#<D~6Eeg*ZapTV&Y4EuFk*gJv2Jdse19P0q4niAmS(e?lmWKb1<S!OJhmKC3u<fB3G|t;Ek18GCy|rcM`'
    'a9o3e)0UBN49?&s*|p{t5x_%RrUpMy7BX@#UPROoXwioE1`@`*W24M%+51dZ`ul)e)Li&uPlC$6E4l@c~iHzdBwV_@s6kyD_qNI=M%VbQ=kk#t|_(flbAZai'
    'P#ttY{N}QFBxjzfHX?rP+ygglmD$e!%X?Ny6+M=w@Yqfhc(MdH=x5{7F}v<2p2jQ{CG#`=;+u~`4qS9(Nx#JDFGQwA(m9dV}c*GUc1Izq-'
    'zsKThfVW@aQ@|({Kc(px_Ut0ySzAO`WmVd0dzRf%J)OMjfFi_wP^ck>W8z65Et>*O&(6g7<3oeM-Oi!Xz1WzjQ`5&k0UHv^)Dz>5o5zUk8uFvm)NheF{5Ayg'
    'C<1QO=7$<{in1$ZTzKzc^Kii>%JSSG2N+@yt3cXL=QV`Jy;wj3OeKSO?;EJ6!4in=}&j)nknWHR_-hi@m<RGYWda_(Zfeulh>BXRCwZVL~VEXC^UmNn&swL&'
    'zZ2#2#+T_}ud^I!P<S8VNH>s1XDin=(qxG@ymJ^hJKE+17YCu+|aS8=U*hhL`EJ7F(-'
    'Fxc{z8263H9*w+?z@P^E@Alaztvn<1#FZyfn5VOJ$V58=X_V*8|i+tnte3F3A+0)Fc#Fs!Ny7PyNekd;*{DDYJuat=aex(nSqlf}HjC)*oqZt$>+FO#l<#9j'
    '>GyTuq?k_kTq%G68+N0z*71`jqpOaT2^njO-x}p`-'
    '&aH9T!B0!nt|N1}o4Vm%_gLlX9WP#%Q(?Al75JEBvC6z=%UD95C{R?B!0Ms0B6kl*lG^gcsANsnYq4wqo2X7S$-'
    'U)z7OmyV7=~Be)*tNjWxq#|AoLOybiMk~s?dBXV}<%EJqP|f1AR?sGa~g#_OFA*x56#O-'
    '&o!lI;*Ifd#@+B>(UcJ)I7#ygB<x7A6Tr`4l#RW4w1nbGiZ4C5N%dMdYbWF_DA}JIanMHKi@}bF#eI<UQqW#L4wA`)(7`d#R*PH!6d8pu!#fbo$oR7FOZr+%'
    'B#fz`bVQ1Y^F^&j|@y-'
    'zp`PFi>@Tu17y1{uZJDphY<kmhqItze{C$tL#uML<dI}w!QB=<YH~y<xrlXn<ZD7F+j1oc*rYO7>8hPe|G}PTh)8sGaHgM6sg)CMTg8QW?J5`y+(@oVv=g?G'
    '0G$6iU$~AQE=NWNfWM9K|D7-'
    'VJGJNkx|Y4I|KGJ|Uv>>^<te_QkNt9?YMSDV=`3HhJXGV!y)gM&jWoZQo6pg{s83HZQ5NCY+nUhPU>1y1I*}1^58<^Dp$;xznK@Se{xL!9I?DO6;=29hsB!J'
    'sKpJQLIqt>WjGOlZb=$Xw*goY+Oipxnncwh0*UX*&fyiPz7K*IdLg5?43ffdN*i%Md{vgEAH<hB7t*vr=jMW9q9?o?2*6aYiZ)b*xE;zTp2ie{~Y@2;G>U!U'
    'Gr*2Bj*co?h4o@J0Fk)1VQ5!>u7?OnWo({XqBEhWhO)CH?&&Gar5cfg~oEDXevzgeqlR)_bEgb>a{>Bwf-UXgNEb3U`l1Bvej?#1y3$V;+M`+)y9WsgJW)D_'
    'ykYQPec?b-~R%=`+D`zRl0Lnq%QTWNf&8`{hBeIllTXVzRoN-'
    '3wODzUe(V5C?hSQhgg=~i{945Wrzmblbaj^>azyX$5S&Dn*=#mlZ)jfK<NX%(DnL2}?nPGjhI1nGHRTd3uY)Er{aWWHq%DR|mXNp(|ZLl!&wt@6KUXfT=`VX'
    '=F7noAk!82Yy{!Fxz_@CppLWHjowT6=L2cH6X*-7iXA$VCm?>XMy+_#|&zeYR9aR69C%f#Hh&kGn(Y7lj(sZl5FXL?>n3doPqhsNzU`V>^-'
    'dkF*YN2k<+!^06;5{-R>K)I%H`K3s2TB8f2a68HSl1s)@n53m4Z}K|ymRcoX&q$*%hT4Z%c_>Dw=0lD0r^_OOuZ*w!-'
    '3}1|vSa=jiN<NI$16@1oQgd8tGt4WNo0Pdq)$@o6g)y#{ZU`QjU!tjA5sg{%86VA=-_;l=z^XuV?S5GyPj|(e=vr8R4ZqU+x|P-'
    '!}XsIt|+NB<j8sr9EGgApK6pDI-$tzEUl+I)kHx;@l-'
    ';8RL>4e;kyz&yD(M;IFSY<TGVZc?TDCfe+~4ag#tOc9AamTb}z}LF#tX&Bp{F2LI|p{b{IRo?vwH4dkq~MMW8{RZx|&zJQ0nK93nNqB|tAN1g$G|u11HRZzb'
    '++z~kIfqg1fVSP_~FLD7WY(rtjVG*()ra1cEks|X-'
    '2S>fw)fCY_2CyDv_9#U(^pi(O9V)*_lXzOVVp%Qq=a}}_>ckRDal|iKbNh;n5Um^?_yeuf}?Y5;bo^|Lzi%FpHi5g|XMF;?=AO_jw+rngcOAQ(NiqMGlsY(?'
    '9Bu#`4b0rb+Wg>D7Lk!hTxUz(B+#5ovA<jz$KR3j%-c65)_Db;+XoI0W;N^xRH(Y5%H~>NpY%x{ztj`Y|pGUhL?OzMr$e#OOo0wFeh-'
    '|d@>q|=$Bj(F*TcBtdO2kUdu5<!`Imu&$b${T~eY(I^&inr8m*$TX-'
    'pgK+Y<2L!4jF`+Ns^R)?CRUNVuX3r`MKwEvu9*7(}s9ss6W@JR+jV9@0Lvqu`}X?r-dcEuT`UP_DLX`(r~}G+U9=?&)3V$)7gVs5NOiNZRDkf-qXA}lD7F+p'
    'NQ?6G6dB6nYdM9|Ljj?z8Wl}OB90&K`YTjM*2g;=wi*{9ph}@A5|%S8>d8w;fQW5Xj*v&Ra`IE_Y7tKwdc3J(t&g)-'
    '3CB7V(EdR?%xvhp99385bK{%Fy$a8Aa`?IWWV9pqR?v4gTpOgM|*NhXnzAPRz1#VxbjY}a=n^#IsAI^xAy#VD2Y>eHLy=X@QyR~1M!1~3SCten$Fcup6wQc9'
    'cUtXT-'
    '4A?S{Hg@<oh;nhBzGGHT3i_$l}dUFy#b_RIpV{u^P&ZXs#(P6mA<;817(j+Ve3m(s|%ar~K2x_Q97>RTe1&o|GMUVTAx85Shz^Awx<`TTBy1_npy&dfSD*!}'
    'Trw+Me5LX!Ky7FFtub?=ZzsrZnT4i;%CU-'
    'm7@ZF8#dTt1C*nysID^IFU*NPN>Hv6XO_(_6l5bWw7IZkt#`on3DjT!+|N*hgKbo*9n94Kn}JQNUo*xgybAWy`%Gl{%wwTzWE0?6d%RZ*|F1eP6!4(j-'
    'RqcKtU0_x(NF1+uo4<Q@N$HWaRvmYVlyn@+j%knJL{+ZT0N8L0d?*W6xr@ZTDFEsI1)!Yj?j<L#e9~kq4J7Zlg*hUy-Ok7^Usj{9(kzS)!W22&t==;HGl#Y1'
    '@j0U!Y1Nl7%$CFG=5J@rI*UOC$R3X~KMn&73gctu%IC<QG5*J$fJZ)R85Y^I|Y>4z&6Nu|PR37w1{Lt;FhkODxiz{3g&wZs)q`&-'
    'oQHfowkW#6=oIau64^cf2(^F!UMl4^CQg*wjG#*C*%ZL99v&?DLfW`h7KLS0^tI>woWFCYt_#o|-'
    'F$99|oXL{Geq;Hp>4v2jkuHrk|@v~<6}VmWka&IuXF9h9<Rk%txGMf+>7NUy}kjd*vjw1~NXSHBV#MwN_cTz$7@z^)9bzV^9#7Owvhta8>FK6XyeXPmd}UE%'
    'q#x~sLy?zCnbySJ$(ogJ%mMMi`sK&-OoRvzSQ9;|p<9msX!oN{CbFOt3M<l*;*MURklw4dHn5a^L{XL9S$KKpXB-h-'
    'r35ny}HPB<An7t|zRfC)5pU;~P?HD{05`T!FRZ2WI0GX~P0JVWHJu}Z$S0>r5*tYZZ%YMlrtcu_B7pvAuBRJ!QG%1ITLoBIe<-'
    'f$;)IlD?<vP&P`vYR_hX?qudQx95??P+Uxz&9_N&_HEohLEQlDap*EgmrB{vWxj^n(GHZocPZVy^dy50C6rFB-J623yHwIxO(>8^-'
    'D<(_S`n@O^}=ATl)q_5Y(C>VPN%t+B@%{rnYa79|D0;1OkSD^rH0MyYwQUC{h$cks?K^K{}y{(h(ve2oXf22vUU5k=`UoM>+!1n^FaQIP>1~UhciWdB69^n|'
    'U*2=42*w&Ua<bE@yw%*?X^5*#hf=aZnMD6+c-'
    'c$+RaE46O0HZ40;#5pT$uFkP*m)q@n6c8!o1__Mec`P@oM<b0MmNsiFAes(@7FMU#jrwif+g15`G+|4~WHsid82y6pmT_YDWZ4}3B-'
    '@3iYf28HzL@z~8zcYGoJ|>J#(u%&PZCHcQ%)3&Z*F5ZNJJkoI)eEt6?k{_7g0-2=hA-pPNR_9o85_65;@7UH71jo)v0@zVBG85YCk<2{TDD%YI@SDKkv}3*?'
    '(I#B<5HBY^P@Tn<9#z%e~OwiJHJ>%W+@fc(k&L9G5p@)ht$r^CFS7i&IW@o=X!^qayv24Z4VTZ1^`nr^iM*09!MpFf#7X*r#lL~0esQ-Sf4%MMwlz}tb5%C8'
    'c4{^_U|Xxk3g~(S&8X#aHih12Y|(kVmM@UH(AyhGF^S|Wwn4;ffUeXR|G-'
    '5(L_pX*W!ZH++F68iQt*?tm+mtk)9JCugmS_UDJKBvMf?;tx;Yz^dUyWnseD$D`)}<tjlouGf5SJfqm_9ua2bzdzqj-'
    'O4S1Q{PiU5#p)IDeOVh+NhJW6!tP|5F9lzJJ>0sk+u>n__WkM{f8VG%E0rt_Bu&hT#B1=}u=;2P{r=R&QECzqB&aBC8qvK{7&yj|C5I{SxjB{jJcDOz5(ye1'
    'O$|e-JxDwfb+QnHDlqLSJZxmmu&6P*XK_+%XfTDP0amHk?6GILQ4>&5jQ|D)@v5OC+&OrWYh3i-)si?gjV+I7@HWZb6zJd?l$P^-'
    'zA`z9fdumnY^Gj~ujAQ+=5I3JP_uVXe}arcm%kOe=?^JltTuji*w_aF-kC-|yz~O`v{o^_xuXUR<IHN$*Ig8FMT=COD53oXbRjH8&l6B-q*<jlcSma3jF%-'
    '^Fq4htfk;xNa}moNZR;sr<8jM){F9;?Z;<n<O)koo{!A7esL4<SeF~ZGyTN;WM!pP)HZ=N@|Be3H#yvtnRc?wT`Lzm6vocRvAz<7B{4sAU*P~6WO$(C}4_gW'
    'TwhCLUOWAs#Hjk|;o#zJ5D?zsjXeT?r)yO(?<+vCfbJ8vYJa>?FAeO54HQ=rf<Kb<Za4j0Oc;)(nA6ypA<m)>b6R*y1=&TkB6Y@=tIY}+iek7q(HJ!EX3X^N'
    'P|2S%|GL|a>z^Ddqrj>r~x|nB}GIV$_OC(ekoR6>GXUxdBYifU7u+BXImnYvGHB?m1V`d{6q$LjrP+Sq#ZUzlp@q?Op&kKyU53KP{x{X^xVPp1ON(!Av*3;l'
    '8Yufhmx&bD6n$16Ch}TQ72Z-~r4l`6Yy=91R25nGZ+tY3*asQA-JQ$7PW?W3Se5$(c#v9khtNLI}$l2<oUH0$6+~b&Jh><2!qCdBm)49O#%qNH9#$kp@!VVM'
    'EO3+6_d4~e~{%EJyD5At~wd7gwsi&0NmuPiO5CdqUP^8e1kP`Fl<T$@g0%GszsU60VzP|Og^e&s3xdJWkiH-hgYL>&0A6E{`67jNzcDm*#J#G#OJ*#8llBS!'
    'qV_zgJSl6O@l5Ozh#3<U==M_inp=pwT$dsKk8;-'
    'ij(TXJEqEcm%^u6NZ{%v`S%<km}HWWj<adOSBKVq<E&O5JbnYcW?AXPeu@EOqexq0+~ih<Wcfj(Q<`%DsPm<h{gJ|PD3xvvR=JTDbjA)BLA?ShtTHv{yFnRD'
    'gd-Qk<4=8>d9uV!(pFVJ4}GH<PaIJa}9{s_jtKcm%)g&mf%`=yi3i3+;zh<}q=8G~b1-'
    'cjGuAjI_d^62W+#&YEYdkBx^^s+Y$DUmd3!h&Y$I4h?@^Bv0KC~eTA@hZJ*V&`3Km9f3rxiig)X$s#W1WZ~Vy#q?UGFpT8`P7$NR7jN<#mbrsq*cqMar6Z$y'
    'YMI#eIB+2m&)#s>)Tfi)+*b&;xqfLN|wa}ry{=Xj@PoIhm=xy+i&DjA|b>r$t)C?&YOPkE%pY}Q6e`06Y-'
    'qsYzdk^4ad2AHphwt?Khs^j?_$lOJBIt78R4ZLx^O9R9S(I^wOoBi3A4^rzIS>J^Bh4bgo8+yl$`tBMm=Q2kV%<9w@xwB<oeQ_bjT%ta?2$`t}D_DK9=ml4A'
    '}i(>VSx;v%=cO9te&jM<YrCzlyc7#`I1O<)vh>+K_LAE$jSF&?=iN5eb;?~xU_A*i>$DXNHMp@Qh2pWbYxC`}WLJ3cDsz^m7H3;Du9&;H75xE9y2Q_~x1^ga'
    'V=c=<;p>KR}81uG8tUhSdpiTz$bqhw8tjw?j3R@5MSSm9BvCwg6G^;|(pbG`V+N9tDzuRq*Ty0mt{^e|J;etWyUM9=X1`;=`W{4Oe_B5MR2-;krUPvGGu{-'
    '+`5oeQ3!u-'
    'S0I*>8AKof9n6&*nKI*esWDaDW63X_e<?*v+5wiJrJ?a6AL;z_;VTbi=NP<d+^~rVSgV78;5SN2kEIJf^XB(sf4<r`PYyVfmvwZyjwMhV|6;Xq}8ni#7^ylu'
    's&{GH=pBEYTvVMPjer9Z;XMw>2&gw`?#m11PooLb7>f+O=TQ8@oknuWL;UZQk{vhb%u|l5HZ<(*tnZi#D480o{6jZ&lBQRM)YDjtfVJWKvb&Hg=~dNI;9mzT'
    'IPnG2HGEV}+3yOSd+vL?4X=!Qqm*FsUF%vZqyvf#+lmD|KcSKt{)L9^qf5*&4@C2>>Ll;@zUizU$`w{H^+Ay~j|mX_ZgujrZT_GskU|NuNNAobxli^cU7_rG'
    'iTY;C@}*G*D3S7J+|8msSOKGm3p%C1!k4s*=2?^K)(yjiR@^TZM1i%WN_Cla7gb@Pk=D)m02{%zzt5?UkjGXZqgfhs6-'
    '(+?$knsrJAqS2j&=`z0Y}$G5qJ%TrEGM==+BL;KQc3W<GWa%V2XxYF{g`GXw;?a){Xy)-'
    'a6>og^3>3DaYUCLXu2}k#&9TW@+xSI<dZ8@RRL9u79Wis^!!wbA`(ytnj+l!<+ZU>3Nm4DRVmq;eMIrTFYCFA#fYDZy@!pV`7?8gPB3;#2KrThcH{yUrT&-'
    'nF>U(fjUj9<_A^^9N7`1Oom&-nF>U;nT8_2w=8ND~kM{5t-~um8@1UzYz|@cWcMG3E04FhO}3y#|N-'
    'Y=@e9i%5i29Gb<52CdBzkDd~7c!$<xGm25AN$8W|krJgl9`X2WtCq$#E4=IbV1iz#V2F2(E`2Tc81Mq*00llEtF(gt<V$)qfM~`A(AQ2WLS8DLigW2#@yEOm'
    'uG|>e(fFpY%e?jFT(KP?z|y2#J<cvGQlAW;Nu@uKC*}{!9;8K1EuPz8gL_^-Ig|J@hvAbNSJp??NitM-'
    'S?o$1#>n3@0Lh}kIF(A@3!Z;3;1y5G;dHIY^l<7`NLUFwJ>sg=-'
    'S6hDRF`8XaplV*VwRl9Y@YGtT6Uia9+dPW5izLCZf>!N7^^BcnO6WcH?C@<^Y|)A69Q~}iKZgL0EocjdVx1YI9N7~gWi1@io7?OuvEygd3%*E<d$57^w)=!H'
    '?xaYUa7l@5LIk?PD(4zszz;xMX3>4!$OU7_d9w*-{&bIKKpYD-b2)xY_Ea<R-'
    'T*v4nPg7&A?#6+N^<^Zy>ziRTSQJheTa38eRdQRFZ3%QIuC!E3m+1?d;ycxKjLtj64oMl=X(U^So!-'
    'Ia=n{5hhHcgf|n5)>zpGfrUq)w=YsX8r}3LGn5ZLALHZ*1>HBl56*kXlPc$bxMJ@~_D$|uU1J<FU$A$vF)J{pt3ueDQp>GXIvOPKu_7R*EpBbWQ3sR{yA_f3'
    '-Y|N)E-H3kcMsT0-z1`=w)hzy8Xxk{&5(n#54w8N$bKF0KQzPtMOfg{|MI5fb?9$jkf&B75j@BAY2}fFHs-lOP)|OZP&KTam{=EeDIiDW#d}z6w}D9?0S~9%'
    'oB`B6j(6}?L|%SpPLC7y$oY*Y4rSPH<NIqbWWW3zaEP@IYTenB{TdLs+d8<q%72`+v9WDvT^X>uQz9O@Uh<l|{^NnRSm3@t=4G8;Sq4!dm2#aPRd3m-'
    '(WD>Z*`vdc2NBif?PWi{Ozcf3Z7(=~5$Su!Cmis?NzD_ERZ$)jkeO-5q*QNK11xm=;pT%Ep+~-'
    'TD*_j42m$RhA^;*Aw7FdbX31=Oma>g*+cXW8Mr<rw^A?XQtRc*9o%|)6R;miS-'
    'X#75Vn`*4Hya|?$(G)P6zU23vVc!b0z4q5Fn3X_j0_kti_%U@qH0_Nx!z&5+Nv>x0DB{p>|%jAF$HbJV1RXPB6s!*S{FlOJ8DE4RE)nuB(=9E4njS^G2I4cz'
    'ioo01cABf$>Wpz5B;csYMS$XOG$z7FKhFCenc)2*R*;#_aM@ANGe!Zi7LKco_EY8b4LM1uc){;905#yL_k~Z-'
    'fn`izPw~aDDO(zJTud6R7S{7JWEqMb=2(g5Vx>S)7(PqZhUAmi{~e$Vd87Pg)PS^H5prn6Ic+7L=0JK-'
    'J!F1Z1;3(0r$FayhcyhI81fn$WaNelD2UelaTEwwq+uv;5a>A(mH4@&C>b?!K-'
    'Q;l?F!@hfsxnu;fI2A?9RMO^dA!E@pk{FpSVMPie!Kavn6wh(35fASZKGV5|5k-kNx3)FF#hTI3e#(B6e;1tEJ_k84RS)rT-wH~0b=Je=acIkbwuc6}yS30{'
    'L?xiTy?yZs4w<;3esEzp7%H&{9_0g!>AV9@jE*-jrNCE9s`$6v3+&E_mSGQEhE`&IN+yqbL~B-'
    'd~Jbl>v(9z<8#(7pIvsC$)j7TIW0HR?oQOiBWXXq!bDtdzXU9!pVUycsl=d$G`Mt3FX4v%2H)B`skc45kCce4T$H*%0?#^Muy8F7}x5H<<Cio}kbf!AE($@-'
    '(&i-'
    'Y&kHkqJ?KDdN16eQOcBD&8!66P5fBki=q_+OhrTvb2SD#!}imEYZHLme95Ggeyg~)dcR)*B3yczX}DS+UsbBv{2k9kUKy*T<PjMK1zB~)P}$G#_poR5_hr4&'
    'yxyDCGAp0jb~rYtaC1S>3PYjdcpgRVctgMi<dqjf>n|Fwv8%pE?QEql{eonPn`wy5H2Y9AAkas?rsiV)zx(MaG3BFDz?&3hvB3I=UA#l!EwShHY13Z0Js*Fb'
    'ym!fU&o<Id#uIy#01Z)x$0W#lM)a$yJ;Re{KovY>hZdUIB+?y5BjjqT-(2P1d`~>%dYpT{jKg?!2;JkPs1&C*1J^JI>D)8a6B6#ZO6`QJYEr&S(Eq-'
    'h8<p8<ws4|@ZHP^_PrCT=pE!S1HPBe>%OR<{D5Z3FC?M`Pf5P~+M@N))_8IEa?H-'
    '+d@6&<Vy~>$Rm3?@;PNcKUR$Y5VvuXyi{aKn`f3YbY566FVlsE=g6%9g<fPa_Clt%)JZic&UAe`5fjADeSyBr>{({|;`o4ZZI1m_IM1heojO7J#q>nG--'
    '`Ut;71q<!W1HNC;Sr8&;5mBkIpGA;v#8SS4;;Jjh?wit2R^5LdJC{NnXa^qwdtECH9-t{H~g7_>uj{^TA3e}MI1}LafOA4!2Gp1|I4fX7y-'
    's4#>L~9uRP;$dG*Jm*KMe?IxZbr5e+!NfT<s~PBGWtg!R&MEA?&XS15SbSJ}n#uWfl_A8c$oTIZv05tHnWcJ%k1PpVKAK@6$wjX;Xm)%LkK1@)7%BjeDJbv&'
    '*7SJf;Mrj-'
    '^GRAOlMBl)g`1@Sd7m0S2iY5|?3Fau84=a5YHQMiCI0*1vY9xj?|UWBu29W&&sbmq}Y7e0Ok*}H2U@N`C@Q{qMgelOBIyqClS8l3kuDrbvSQkUskr#|7scGx'
    'sK{J8w`qbZ3g1E)}pd}hnZJW1&_hfkWvCl41QySI1afL#E}EQh$irM@dD>u{HL%$yT9w2>z1AVS7~gR$)?G_Zf-l!DO*?DKhCjn&-'
    'h!c~x^5UhKIk#{#0Jm%(pO*TT&Ws~qeE9NW63|SKpr*ZNa*x*9lC~97{Dwq7Y9Aq6HE_AmE$<=3hu(4Bopw{ozKS8w7X}9$=k;_RY_fdjA_;5`+cOcg<a8DE'
    'VUFCy@>wxl}Zm6|kYQk#f6Cy&sNEgABJKc~QF+KXEn<dnMnc-'
    '*>@bxxoBc5073u5Et)R%peo5yqKy5Bjcg$MlrCDIZpr^MrF>e{2VbgE;yssXPwk7Ww*Cu!&OB-be0C7%)~fGY?W5{cHq(;S!d)p{ylD?-'
    '|!#hVo&dBbNvO1APHb$zQeW{z4OE=G^1Ei0f+`N~&GY2~>}mqf~DsAK<8SR$~VCST^Yk7?4h0&*cI;|D{3ecLCy36a44agq^Xnj2OZw;0?fKdiFLExj~&yi4'
    '-{o~f@YR6x9Ct=z8W!e5@mN}WNT#!^BslPxhXSa<tgx!_Wu-iRox+*0!dTZf%}>qmK!%scrtN@kD-'
    'jOmB=MaLNWZO6QdDq1v8(Xw5aPIh#>VOTrqR<)HcUGe>7b;a0W^`p--'
    'oz|g8-_r5#eL)D3s3T}_dGGs!^a~($;Opn>{9e;`#umCc^%uS^8->>>H9tJci0qhVU4dH_s|Kb-v-rPqCex`F#Ne<x9&SF-'
    '>HF>Yk1wC}mcVMi$Gw{jK7q&FYJia8#MHBn76`P?#QgEeXpmUpHE1A)BfT34rR43*5*Hrf@ku)j%nZ1<J!57=6{J1S_3WVg8dH(wJM24*-'
    '(bL}<|WVKsaxN>cr~ldpJB;jNZs99J@ntMW~rN-dk;3>GBtk06CQpybSWTs{l{ITjQiqIY?5FR_8q0X*S3k5lHZ>4F(aPn2t7xXsPv}4Ird<a0mVVE1cw_Q%'
    '``Y5Ww?eM7Aazsn4Y}^ykGW+4r^zc^G5nN+g9->j4$q_`k9|xRvh@_+>l}bSL?l;QNEiJ8V;ehOL!b0c?O)C3pWBT^yqQ{`Q=Mhh--kN33<IH!bFq-PZS1Fv'
    'h{={{c_M4r?+F7X)1j3`r_O5I13v~btNL;I%WW3+4o92KBd*6^^1vAi4QsErkceqQt5cMYj|4_dg|cx&1uD_EE`hHJHCYc-L{smLBnR~e6#yP<(WP~X7{7o-'
    '6{8p3KeeG7;^1GrS|o^8M|lW&SM7swEZsiAOa_1FBDrGd}@9ZE?{>F5Hcp{`=Bm^Q5wQ>NiOq3ar6mKh%TLH!CkvN-amVhQZs>bfw#jnv4U}EK`WD?s!w>wa'
    '<M-sBFct8V9VOseuFI>(Yx?KGv=#u`s!8XRG~7!k3V)vE=W>ZtivQzl8lf)BMR9^OU;<XS^ia-'
    '(tGijkM=&2+(#%}iDsn$JBd|(E_Bp4qhcMPY{=9GnoB4f)o>f2AHGN)l4BI4uS%<ia_g8CdUoLQkV{f3jn|BZQh7t=hNBWIY&1u{`6tNsGh}h-'
    'JG39i$rCO{XDfbCA4UJt(n2Ps>jz}&rzuKK$H&!|_K?U^Q;Z^fWf<~5BV?Mt5c0n>-EaoTXMlVL$Y+3j2FPcCd<Mv8fP4nXXMp_w6p-;i=kfnOSvM8%`-'
    '8#*{+KP}zuzYRD?Rj2dJyT~r2alFKb<P^w;Z45ZxSb-mY+_I_gj9Q_Ma2w{VOZ*KUs-o|Hq6Wr;VHrmi*gDr@&uBC!bcIj=}a@T`cpLh-'
    '|0Dr{mB37JpOvOEj9(;?r?Eev9{1|0#;cX&a~a^8L2KrT-'
    '5*`%arUy{X~12`l5j+2Zi8<bN)G_B(%FV0K!4dP48F`pdn)PVb#opPq;Lt#)wz$61+wW#rG*5as(%j_b86;9oB4Nu5&wUHAa-_TjHz{{f0Mc25'
)


def source_images():
    raw = zlib.decompress(base64.b85decode("".join(DATA)))
    with ZipFile(BytesIO(raw)) as bank:
        return {slug: {
            kind: Image.open(BytesIO(bank.read(f"{slug}/{kind}.png"))).convert("RGBA")
            for kind in ("front", "back", "icon", "shiny_front", "shiny_back")
        } for slug in BIRDS}


def rgb_palette(cols):
    # Indices 0-15, with index 0 transparent and unused slots black.
    return list(cols) + [(0, 0, 0)] * (16 - len(cols))


def png_indexed(img, indices, colors):
    pal = rgb_palette(colors)
    dest = Image.new("P", img.size)
    dest.putpalette([component for c in pal for component in c] + [0] * (768 - 48))
    dest.putdata([0 if rgba[3] < 128 else indices[rgba[:3]]
                  for rgba in img.getdata()])
    assert len(dest.getcolors()) <= 16 and max(dest.getdata()) <= 15
    return dest


def save_sheet(img, destination, frames=1):
    sheet = Image.new("P", (img.width, img.height * frames), 0)
    sheet.putpalette(img.getpalette())
    for frame in range(frames):
        sheet.paste(img, (0, frame * img.height))
    sheet.save(destination, format="PNG", transparency=0, optimize=False)
    with Image.open(destination) as check:
        assert check.mode == "P" and check.size == sheet.size
        assert max(check.getdata()) <= 15


def save_jasc(colors, destination):
    pal = rgb_palette(colors)
    assert len(pal) == 16
    destination.write_text("JASC-PAL\\n0100\\n16\\n" +
                           "".join(f"{r} {g} {b}\\n" for r, g, b in pal))


def install(slug, donor):
    assert donor["front"].size == donor["back"].size == (64, 64)
    assert donor["icon"].size == (32, 32)
    for part in ("front", "back"):
        n, s = donor[part], donor["shiny_" + part]
        assert n.size == s.size
        assert all((p[3] >= 128) == (q[3] >= 128)
                   for p, q in zip(n.getdata(), s.getdata()))

    normal_colors = [(0, 0, 0)]
    matching_shiny = {}
    for part in ("front", "back"):
        for n, s in zip(donor[part].getdata(), donor["shiny_" + part].getdata()):
            if n[3] < 128:
                continue
            rgb = n[:3]
            if rgb not in matching_shiny:
                normal_colors.append(rgb)
                matching_shiny[rgb] = s[:3]
            else:
                assert matching_shiny[rgb] == s[:3], "Shiny palette mismatch"
    assert len(normal_colors) <= 16, f"{slug}: palette overflow"
    shiny_colors = [(0, 0, 0)] + [matching_shiny[c] for c in normal_colors[1:]]
    index = {c: i for i, c in enumerate(normal_colors)}

    icon_colors = [(0, 0, 0)]
    icon_seen = set()
    for pix in donor["icon"].getdata():
        if pix[3] >= 128 and pix[:3] not in icon_seen:
            icon_seen.add(pix[:3])
            icon_colors.append(pix[:3])
    assert len(icon_colors) <= 16, f"{slug}: icon palette overflow"
    icon_index = {c: i for i, c in enumerate(icon_colors)}

    output = ROOT / "graphics/pokemon" / slug
    output.mkdir(parents=True, exist_ok=True)
    front = png_indexed(donor["front"], index, normal_colors)
    back = png_indexed(donor["back"], index, normal_colors)
    icon = png_indexed(donor["icon"], icon_index, icon_colors)

    for name in ("anim_front.png", "anim_front_gba.png"):
        save_sheet(front, output / name, 2)
    for name in ("back.png", "back_gba.png"):
        save_sheet(back, output / name)
    for name in ("icon.png", "icon_gba.png"):
        save_sheet(icon, output / name, 2)
    for name in ("normal.pal", "normal_gba.pal"):
        save_jasc(normal_colors, output / name)
    for name in ("shiny.pal", "shiny_gba.pal"):
        save_jasc(shiny_colors, output / name)
    print(f"PASS {slug}-P: 64x128 two-frame front, 64x64 back, "
          f"32x64 party icon, {len(normal_colors)} palette entries; shiny mapped")


if __name__ == "__main__":
    for slug, donor in source_images().items():
        install(slug, donor)