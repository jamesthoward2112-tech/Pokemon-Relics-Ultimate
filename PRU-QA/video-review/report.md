# Video sprite review repairs

Reviewed 37 icon references from the attached clip. Nolax was excluded.
Custom icons were reduced by 20% with nearest-neighbour pixels when their frame exceeded 25 pixels in either dimension. Shared vanilla icons were left untouched.

## Icons reduced

- Nimbeon: reduced (`graphics/pokemon/nimbeon/icon.png`).
- Drakeon: reduced (`graphics/pokemon/drakeon/icon.png`).
- Champeon: already compact (`graphics/pokemon/champeon/icon.png`).
- Guardeon: reduced (`graphics/pokemon/guardeon/icon.png`).
- Toxeon: reduced (`graphics/pokemon/toxeon/icon.png`).
- Sphynxeon: already compact (`graphics/pokemon/sphynxeon/icon.png`).
- Skarmet: already compact (`graphics/pokemon/skarmet/icon.png`).
- Kablowfish: reduced (`graphics/pokemon/prl_authoritative/kablowfish/icon.png`).
- Grimfowl: already compact (`graphics/pokemon/prl_authoritative/grimfowl/icon.png`).
- Heracurion: reduced (`graphics/pokemon/prl_authoritative/heracurion/icon.png`).
- Scarabub: reduced (`graphics/pokemon/prl_authoritative/scarabub/icon.png`).
- Skarmadon: reduced (`graphics/pokemon/prl_authoritative/skarmadon/icon.png`).
- Jollibird: reduced (`graphics/pokemon/prl_authoritative/jollibird/icon.png`).
- Osteodian: already compact (`graphics/pokemon/prl_authoritative/osteodian/icon.png`).
- Sunflorid: already compact (`graphics/pokemon/prl_authoritative/sunflorid/icon.png`).
- Sudowarden: reduced (`graphics/pokemon/pjr_locked/sudowarden/icon.png`).
- Mystynx: reduced (`graphics/pokemon/prl_authoritative/mystynx/icon.png`).
- Ghoulbat: reduced (`graphics/pokemon/prl_authoritative/ghoulbat/icon.png`).
- Khang: reduced (`graphics/pokemon/prl_authoritative/khang/icon.png`).
- Fortotoise: reduced (`graphics/pokemon/prl_authoritative/fortotoise/icon.png`).
- Charaxis: reduced (`graphics/pokemon/prl_authoritative/charaxis/icon.png`).
- HoOhRelic: reduced (`graphics/pokemon/ho_oh_relic/icon.png`).
- Gemlin: already compact (`graphics/pokemon/prl_authoritative/gemlin/icon.png`).
- Gemigoyle: reduced (`graphics/pokemon/prl_authoritative/gemigoyle/icon.png`).
- Astrachi: reduced (`graphics/pokemon/astrachi/icon.png`).
- Adnokana: already compact (`graphics/pokemon/adnokana/icon.png`).
- Cheauking: already compact (`graphics/pokemon/cheauking/icon.png`).
- Frytning: reduced (`graphics/pokemon/frytning/icon.png`).
- Mewsion: reduced (`graphics/pokemon/mewsion/icon.png`).
- Tropisaur: reduced (`graphics/pokemon/prl_authoritative/tropisaur/icon.png`).
- Coelossus: reduced (`graphics/pokemon/prl_authoritative/coelossus/icon.png`).
- Cactomb: reduced (`graphics/pokemon/prl_authoritative/cactomb/icon.png`).
- Torkaldera: reduced (`graphics/pokemon/prl_authoritative/torkaldera/icon.png`).
- Sceptitan: reduced (`graphics/pokemon/prl_authoritative/sceptitan/icon.png`).
- Solaziken: reduced (`graphics/pokemon/prl_authoritative/solaziken/icon.png`).

## Battle image framing

- gemlin front: [34, 36] → [42, 44] px; nearest-neighbour and original palette indexes retained.
- gemlin back: [33, 36] → [33, 36] px; nearest-neighbour and original palette indexes retained; genuine Gemlin back donor oriented for player side.
- jollibird front: [55, 52] → [44, 42] px; nearest-neighbour and original palette indexes retained.
- jollibird back: [63, 50] → [50, 40] px; nearest-neighbour and original palette indexes retained.
- kablowfish front: [61, 47] → [49, 38] px; nearest-neighbour and original palette indexes retained.
- kablowfish back: [58, 45] → [47, 36] px; nearest-neighbour and original palette indexes retained.
- grimfowl front: [52, 64] → [42, 52] px; nearest-neighbour and original palette indexes retained.
- grimfowl back: [63, 64] → [49, 50] px; nearest-neighbour and original palette indexes retained.

Visual acceptance still requires checking the finished ROM in mGBA.
