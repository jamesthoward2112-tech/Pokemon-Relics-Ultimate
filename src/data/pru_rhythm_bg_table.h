// Shared original PRU Battle Backgrounds: approved eight-scene pack.
// Historic 55 indices remain ABI-compatible but reference only PRU-original art.
struct PruRhythmBattleBg
{
    const u32 *tiles;
    const u32 *tilemap;
    const u16 *palette;
};
extern const u32 gPruTestMtSilverTiles[];
extern const u32 gPruTestMtSilverMap[];
extern const u16 gPruTestMtSilverPal[];
extern const u32 gPruTestRoute29Tiles[];
extern const u32 gPruTestRoute29Map[];
extern const u16 gPruTestRoute29Pal[];
extern const u32 gPruBatch1IlexTiles[];
extern const u32 gPruBatch1IlexMap[];
extern const u16 gPruBatch1IlexPal[];
extern const u32 gPruBatch1RuinsTiles[];
extern const u32 gPruBatch1RuinsMap[];
extern const u16 gPruBatch1RuinsPal[];
extern const u32 gPruBatch1IcePathTiles[];
extern const u32 gPruBatch1IcePathMap[];
extern const u16 gPruBatch1IcePathPal[];
extern const u32 gPruBatch1EnteiMortarTiles[];
extern const u32 gPruBatch1EnteiMortarMap[];
extern const u16 gPruBatch1EnteiMortarPal[];
extern const u32 gPruCleanSilverTiles[];
extern const u32 gPruCleanSilverMap[];
extern const u16 gPruCleanSilverPal[];
extern const u32 gPruCleanHoOhTiles[];
extern const u32 gPruCleanHoOhMap[];
extern const u16 gPruCleanHoOhPal[];
extern const u32 gPru50CaveTiles[];
extern const u32 gPru50CaveMap[];
extern const u16 gPru50CavePal[];
extern const u32 gPru50RainTiles[];
extern const u32 gPru50RainMap[];
extern const u16 gPru50RainPal[];
extern const u32 gPru50RiverTiles[];
extern const u32 gPru50RiverMap[];
extern const u16 gPru50RiverPal[];
extern const u32 gPru50CoastTiles[];
extern const u32 gPru50CoastMap[];
extern const u16 gPru50CoastPal[];
static const struct PruRhythmBattleBg sPruRhythmBattleBgs[55] = {
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 0: PRU original shared scenery
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 1: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 2: PRU original shared scenery
    {gPru50CaveTiles, gPru50CaveMap, gPru50CavePal}, // 3: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 4: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 5: PRU original shared scenery
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 6: PRU original shared scenery
    {gPru50CaveTiles, gPru50CaveMap, gPru50CavePal}, // 7: PRU original shared scenery
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 8: PRU original shared scenery
    {gPruBatch1IlexTiles, gPruBatch1IlexMap, gPruBatch1IlexPal}, // 9: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 10: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 11: PRU original shared scenery
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 12: PRU original shared scenery
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 13: PRU original shared scenery
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 14: PRU original shared scenery
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 15: PRU original shared scenery
    {gPruBatch1EnteiMortarTiles, gPruBatch1EnteiMortarMap, gPruBatch1EnteiMortarPal}, // 16: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 17: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 18: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 19: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 20: PRU original shared scenery
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 21: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 22: PRU original shared scenery
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 23: PRU original shared scenery
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 24: PRU original shared scenery
    {gPruBatch1EnteiMortarTiles, gPruBatch1EnteiMortarMap, gPruBatch1EnteiMortarPal}, // 25: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 26: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 27: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 28: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 29: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 30: PRU original shared scenery
    {gPru50RiverTiles, gPru50RiverMap, gPru50RiverPal}, // 31: PRU original shared scenery
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 32: PRU original shared scenery
    {gPru50RainTiles, gPru50RainMap, gPru50RainPal}, // 33: PRU original shared scenery
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 34: PRU original shared scenery
    {gPru50CaveTiles, gPru50CaveMap, gPru50CavePal}, // 35: PRU original shared scenery
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 36: PRU original shared scenery
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 37: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 38: PRU original shared scenery
    {gPruBatch1IlexTiles, gPruBatch1IlexMap, gPruBatch1IlexPal}, // 39: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 40: PRU original shared scenery
    {gPru50CaveTiles, gPru50CaveMap, gPru50CavePal}, // 41: PRU original shared scenery
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 42: PRU original shared scenery
    {gPruBatch1IlexTiles, gPruBatch1IlexMap, gPruBatch1IlexPal}, // 43: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 44: PRU original shared scenery
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 45: PRU original shared scenery
    {gPru50RainTiles, gPru50RainMap, gPru50RainPal}, // 46: PRU original shared scenery
    {gPru50CaveTiles, gPru50CaveMap, gPru50CavePal}, // 47: PRU original shared scenery
    {gPru50RainTiles, gPru50RainMap, gPru50RainPal}, // 48: PRU original shared scenery
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 49: PRU original shared scenery
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 50: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 51: PRU original shared scenery
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 52: PRU original shared scenery
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // 53: PRU original shared scenery
    {gPruBatch1EnteiMortarTiles, gPruBatch1EnteiMortarMap, gPruBatch1EnteiMortarPal}, // 54: PRU original shared scenery
};
