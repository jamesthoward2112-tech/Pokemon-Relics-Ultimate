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
static const struct PruRhythmBattleBg sPruRhythmBattleBgs[55] = {
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 0: Route 29 wild grass
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 1: Mt Silver rocky redraw
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 2: Ice Path
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 3: Mt Silver rocky redraw
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 4: Ice Path
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 5: Ice Path
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 6: Mt Silver rocky redraw
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 7: Mt Silver rocky redraw
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 8: Alph Outside
    {gPruBatch1IlexTiles, gPruBatch1IlexMap, gPruBatch1IlexPal}, // 9: Ilex Forest
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 10: Alph Outside
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 11: Alph Outside
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 12: Alph Outside
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 13: Ice Path
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 14: Ice Path
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 15: Mt Silver rocky redraw
    {gPruBatch1EnteiMortarTiles, gPruBatch1EnteiMortarMap, gPruBatch1EnteiMortarPal}, // 16: Mt Mortar volcanic relic
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 17: Alph Outside
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 18: Alph Outside
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 19: Alph Outside
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 20: Ice Path
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 21: Route 29 wild grass
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 22: Alph Outside
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 23: Ice Path
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 24: Ice Path
    {gPruBatch1EnteiMortarTiles, gPruBatch1EnteiMortarMap, gPruBatch1EnteiMortarPal}, // 25: Mt Mortar volcanic relic
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 26: Alph Outside
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 27: Alph Outside
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 28: Alph Outside
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 29: Alph Outside
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 30: Ice Path
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 31: Alph Outside
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 32: Route 29 wild grass
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 33: Route 29 wild grass
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 34: Route 29 wild grass
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 35: Mt Silver rocky redraw
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 36: Mt Silver rocky redraw
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 37: Route 29 wild grass
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 38: Alph Outside
    {gPruBatch1IlexTiles, gPruBatch1IlexMap, gPruBatch1IlexPal}, // 39: Ilex Forest
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 40: Ice Path
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 41: Mt Silver rocky redraw
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal}, // 42: Route 29 wild grass
    {gPruBatch1IlexTiles, gPruBatch1IlexMap, gPruBatch1IlexPal}, // 43: Ilex Forest
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 44: Alph Outside
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 45: Mt Silver rocky redraw
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 46: Alph Outside
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 47: Mt Silver rocky redraw
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 48: Ice Path
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 49: Alph Outside
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 50: Mt Silver rocky redraw
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal}, // 51: Alph Outside
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal}, // 52: Mt Silver rocky redraw
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal}, // 53: Ice Path
    {gPruBatch1EnteiMortarTiles, gPruBatch1EnteiMortarMap, gPruBatch1EnteiMortarPal}, // 54: Mt Mortar volcanic relic
};
