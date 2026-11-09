#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_bg.h"
#include "battle_main.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_environment.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "link.h"
#include "load_save.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "test_runner.h"
#include "text_window.h"
#include "trig.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "constants/battle_anim.h"
#include "rtc.h"
#include "constants/battle_partner.h"
#include "rtc.h"
#include "data/battle_environment.h"
#include "data/pru_rhythm_bg_table.h"

// Dedicated original art for the two November 2026 location-based beta tests.
extern const u32 gPruTestMtSilverTiles[];
extern const u32 gPruTestMtSilverMap[];
extern const u16 gPruTestMtSilverPal[];
extern const u32 gPruTestRoute29Tiles[];
extern const u32 gPruTestRoute29Map[];
extern const u16 gPruTestRoute29Pal[];
// Original PRU art; retain the two proven scenes and introduce Batch 01.
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
static const struct PruRhythmBattleBg sPruOriginalTestBattleBgs[12] = {
    {gPruTestMtSilverTiles, gPruTestMtSilverMap, gPruTestMtSilverPal},
    {gPruTestRoute29Tiles, gPruTestRoute29Map, gPruTestRoute29Pal},
    {gPruBatch1IlexTiles, gPruBatch1IlexMap, gPruBatch1IlexPal},
    {gPruBatch1RuinsTiles, gPruBatch1RuinsMap, gPruBatch1RuinsPal},
    {gPruBatch1IcePathTiles, gPruBatch1IcePathMap, gPruBatch1IcePathPal},
    {gPruBatch1EnteiMortarTiles, gPruBatch1EnteiMortarMap, gPruBatch1EnteiMortarPal},
    {gPruCleanSilverTiles, gPruCleanSilverMap, gPruCleanSilverPal},
    {gPruCleanHoOhTiles, gPruCleanHoOhMap, gPruCleanHoOhPal},
    {gPru50CaveTiles, gPru50CaveMap, gPru50CavePal}, // Limestone cave / Union Cave / Dark Cave / Kanto underground
    {gPru50RainTiles, gPru50RainMap, gPru50RainPal}, // Lake of Rage / heavy rain / wetlands
    {gPru50RiverTiles, gPru50RiverMap, gPru50RiverPal}, // Wooded rivers and Johto 30-32 paths
    {gPru50CoastTiles, gPru50CoastMap, gPru50CoastPal}, // Olivine / coastal routes / Cianwood
};


// .rodata

static const struct OamData sVsLetter_V_OamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct OamData sVsLetter_S_OamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 64,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AffineAnimCmd sVsLetterAffineAnimCmds0[] =
{
    AFFINEANIMCMD_FRAME(0x0080, 0x0080, 0x00, 0x00),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sVsLetterAffineAnimCmds1[] =
{
    AFFINEANIMCMD_FRAME(0x0080, 0x0080, 0x00, 0x00),
    AFFINEANIMCMD_FRAME(0x0018, 0x0018, 0x00, 0x80),
    AFFINEANIMCMD_FRAME(0x0018, 0x0018, 0x00, 0x80),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const sVsLetterAffineAnimTable[] =
{
    sVsLetterAffineAnimCmds0,
    sVsLetterAffineAnimCmds1,
};

#define TAG_VS_LETTERS 10000

static const struct SpriteTemplate sVsLetter_V_SpriteTemplate =
{
    .tileTag = TAG_VS_LETTERS,
    .paletteTag = TAG_VS_LETTERS,
    .oam = &sVsLetter_V_OamData,
    .affineAnims = sVsLetterAffineAnimTable,
    .callback = SpriteCB_VsLetterDummy
};

static const struct SpriteTemplate sVsLetter_S_SpriteTemplate =
{
    .tileTag = TAG_VS_LETTERS,
    .paletteTag = TAG_VS_LETTERS,
    .oam = &sVsLetter_S_OamData,
    .affineAnims = sVsLetterAffineAnimTable,
    .callback = SpriteCB_VsLetterDummy
};

static const struct CompressedSpriteSheet sVsLettersSpriteSheet =
{
    gVsLettersGfx, 0x1000, TAG_VS_LETTERS
};

const struct BgTemplate gBattleBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 24,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 28,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 1,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
   {
        .bg = 3,
        .charBaseIndex = 2,
        .mapBaseIndex = 26,
        .screenSize = 1,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    },
};

static const struct WindowTemplate sStandardBattleWindowTemplates[] =
{
    [B_WIN_MSG] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 0x0090,
    },
    [B_WIN_ACTION_PROMPT] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 35,
        .width = 14,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 0x01c0,
    },
    [B_WIN_ACTION_MENU] = {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 35,
        .width = 12,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x0190,
    },
    [B_WIN_MOVE_NAME_1] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 55,
        .width = 16,    //for z move names
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0300,
    },
    [B_WIN_MOVE_NAME_2] = {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 55,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0318,
    },
    [B_WIN_MOVE_NAME_3] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 57,
        .width = 16,    //for z effect descriptions
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0328,
    },
    [B_WIN_MOVE_NAME_4] = {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 57,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0340,
    },
    [B_WIN_PP] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 55,
        .width = 4,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0290,
    },
    [B_WIN_DUMMY] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 57,
        .width = 0,
        .height = 0,
        .paletteNum = 5,
        .baseBlock = 0x0298,
    },
    [B_WIN_PP_REMAINING] = {
        .bg = 0,
        .tilemapLeft = 25,
        .tilemapTop = 55,
        .width = 4,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0298,
    },
    [B_WIN_MOVE_TYPE] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 57,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x02a0,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 55,
        .width = 8,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x02b0,
    },
    [B_WIN_YESNO] = {
        .bg = 0,
        .tilemapLeft = 26,
        .tilemapTop = 9,
        .width = 3,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x0100,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .bg = 1,
        .tilemapLeft = 19,
        .tilemapTop = 8,
        .width = 10,
        .height = 11,
        .paletteNum = 5,
        .baseBlock = 0x0100,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .bg = 2,
        .tilemapLeft = 18,
        .tilemapTop = 0,
        .width = 12,
        .height = 3,
        .paletteNum = 6,
        .baseBlock = 0x016e,
    },
    [B_WIN_VS_PLAYER] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0020,
    },
    [B_WIN_VS_OPPONENT] = {
        .bg = 2,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0040,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 2,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0020,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .bg = 2,
        .tilemapLeft = 2,
        .tilemapTop = 2,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0040,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 6,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0060,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .bg = 2,
        .tilemapLeft = 2,
        .tilemapTop = 6,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0080,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .bg = 0,
        .tilemapLeft = 12,
        .tilemapTop = 2,
        .width = 6,
        .height = 2,
        .paletteNum = 0,
        .baseBlock = 0x00a0,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .bg = 0,
        .tilemapLeft = 4,
        .tilemapTop = 2,
        .width = 7,
        .height = 2,
        .paletteNum = 0,
        .baseBlock = 0x00a0,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .bg = 0,
        .tilemapLeft = 19,
        .tilemapTop = 2,
        .width = 7,
        .height = 2,
        .paletteNum = 0,
        .baseBlock = 0x00b0,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 47,
        .width = 18,
        .height = 6,
        .paletteNum = 5,
        .baseBlock = 0x0350,
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sKantoTutorialBattleWindowTemplates[] =
{
    [B_WIN_MSG] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 0x0090,
    },
    [B_WIN_ACTION_PROMPT] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 35,
        .width = 14,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 0x01c0,
    },
    [B_WIN_ACTION_MENU] = {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 35,
        .width = 12,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x0190,
    },
    [B_WIN_MOVE_NAME_1] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 55,
        .width = 16,    //for z move names
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0300,
    },
    [B_WIN_MOVE_NAME_2] = {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 55,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0318,
    },
    [B_WIN_MOVE_NAME_3] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 57,
        .width = 16,    //for z effect descriptions
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0328,
    },
    [B_WIN_MOVE_NAME_4] = {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 57,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0340,
    },
    [B_WIN_PP] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 55,
        .width = 4,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0290,
    },
    [B_WIN_DUMMY] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 57,
        .width = 0,
        .height = 0,
        .paletteNum = 5,
        .baseBlock = 0x0298,
    },
    [B_WIN_PP_REMAINING] = {
        .bg = 0,
        .tilemapLeft = 25,
        .tilemapTop = 55,
        .width = 4,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0298,
    },
    [B_WIN_MOVE_TYPE] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 57,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x02a0,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 55,
        .width = 8,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x02b0,
    },
    [B_WIN_YESNO] = {
        .bg = 0,
        .tilemapLeft = 26,
        .tilemapTop = 9,
        .width = 3,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x0100,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .bg = 1,
        .tilemapLeft = 19,
        .tilemapTop = 8,
        .width = 10,
        .height = 11,
        .paletteNum = 5,
        .baseBlock = 0x0100,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .bg = 2,
        .tilemapLeft = 18,
        .tilemapTop = 0,
        .width = 12,
        .height = 3,
        .paletteNum = 6,
        .baseBlock = 0x016e,
    },
    [B_WIN_VS_PLAYER] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0020,
    },
    [B_WIN_VS_OPPONENT] = {
        .bg = 2,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0040,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 2,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0020,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .bg = 2,
        .tilemapLeft = 2,
        .tilemapTop = 2,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0040,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 6,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0060,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .bg = 2,
        .tilemapLeft = 2,
        .tilemapTop = 6,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0080,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .bg = 0,
        .tilemapLeft = 12,
        .tilemapTop = 2,
        .width = 6,
        .height = 2,
        .paletteNum = 0,
        .baseBlock = 0x00a0,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .bg = 0,
        .tilemapLeft = 4,
        .tilemapTop = 2,
        .width = 7,
        .height = 2,
        .paletteNum = 0,
        .baseBlock = 0x00a0,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .bg = 0,
        .tilemapLeft = 19,
        .tilemapTop = 2,
        .width = 7,
        .height = 2,
        .paletteNum = 0,
        .baseBlock = 0x00b0,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 47,
        .width = 18,
        .height = 6,
        .paletteNum = 5,
        .baseBlock = 0x0350,
    },
    [B_WIN_OAK_OLD_MAN] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 7,
        .baseBlock = 0x090
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sBattleArenaWindowTemplates[] =
{
    [B_WIN_MSG] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 0x0090,
    },
    [B_WIN_ACTION_PROMPT] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 35,
        .width = 14,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 0x01c0,
    },
    [B_WIN_ACTION_MENU] = {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 35,
        .width = 12,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x0190,
    },
    [B_WIN_MOVE_NAME_1] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 55,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0300,
    },
    [B_WIN_MOVE_NAME_2] = {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 55,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0310,
    },
    [B_WIN_MOVE_NAME_3] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 57,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0320,
    },
    [B_WIN_MOVE_NAME_4] = {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 57,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0330,
    },
    [B_WIN_PP] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 55,
        .width = 4,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0290,
    },
    [B_WIN_DUMMY] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 57,
        .width = 0,
        .height = 0,
        .paletteNum = 5,
        .baseBlock = 0x0298,
    },
    [B_WIN_PP_REMAINING] = {
        .bg = 0,
        .tilemapLeft = 25,
        .tilemapTop = 55,
        .width = 4,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0298,
    },
    [B_WIN_MOVE_TYPE] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 57,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x02a0,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 55,
        .width = 8,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x02b0,
    },
    [B_WIN_YESNO] = {
        .bg = 0,
        .tilemapLeft = 26,
        .tilemapTop = 9,
        .width = 3,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x0100,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .bg = 1,
        .tilemapLeft = 19,
        .tilemapTop = 8,
        .width = 10,
        .height = 11,
        .paletteNum = 5,
        .baseBlock = 0x0100,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .bg = 2,
        .tilemapLeft = 18,
        .tilemapTop = 0,
        .width = 12,
        .height = 3,
        .paletteNum = 6,
        .baseBlock = 0x016e,
    },
    [ARENA_WIN_PLAYER_NAME] = {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 1,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0100,
    },
    [ARENA_WIN_VS] = {
        .bg = 0,
        .tilemapLeft = 14,
        .tilemapTop = 1,
        .width = 2,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0110,
    },
    [ARENA_WIN_OPPONENT_NAME] = {
        .bg = 0,
        .tilemapLeft = 16,
        .tilemapTop = 1,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0114,
    },
    [ARENA_WIN_MIND] = {
        .bg = 0,
        .tilemapLeft = 12,
        .tilemapTop = 4,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0124,
    },
    [ARENA_WIN_SKILL] = {
        .bg = 0,
        .tilemapLeft = 12,
        .tilemapTop = 6,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0130,
    },
    [ARENA_WIN_BODY] = {
        .bg = 0,
        .tilemapLeft = 12,
        .tilemapTop = 8,
        .width = 6,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x013c,
    },
    [ARENA_WIN_JUDGMENT_TITLE] = {
        .bg = 0,
        .tilemapLeft = 8,
        .tilemapTop = 11,
        .width = 14,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x0148,
    },
    [ARENA_WIN_JUDGMENT_TEXT] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 7,
        .baseBlock = 0x0090,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 47,
        .width = 18,
        .height = 6,
        .paletteNum = 5,
        .baseBlock = 0x0350,
    },
    DUMMY_WIN_TEMPLATE
};

const struct WindowTemplate *const gBattleWindowTemplates[] =
{
    [B_WIN_TYPE_NORMAL] = sStandardBattleWindowTemplates,
    [B_WIN_TYPE_ARENA]  = sBattleArenaWindowTemplates,
    [B_WIN_TYPE_KANTO_TUTORIAL] = sKantoTutorialBattleWindowTemplates,
};

// If current map scene equals any of the values in sMapBattleSceneMapping,
// use its battle environment value. Otherwise, use the default.
static u8 GetBattleEnvironmentByMapScene(u8 mapBattleScene)
{
    int i;
    for (i = 0; i < NELEMS(sMapBattleSceneMapping); i++)
    {
        if (mapBattleScene == sMapBattleSceneMapping[i].mapScene)
            return sMapBattleSceneMapping[i].battleEnvironment;
    }
    return BATTLE_ENVIRONMENT_PLAIN;
}

static bool32 UseModernBattleEnvironment(void)
{
    return gSaveblock3.challengeSettings.newBackgrounds;
}

enum
{
    BATTLE_TERRAIN_TIME_DAY,
    BATTLE_TERRAIN_TIME_TWILIGHT,
    BATTLE_TERRAIN_TIME_NIGHT,
};

static u32 GetBattleTerrainTimeOfDay(void)
{
    switch (GetTimeOfDay())
    {
    case TIME_DAY:
        return BATTLE_TERRAIN_TIME_DAY;
    case TIME_MORNING:
    case TIME_EVENING:
        return BATTLE_TERRAIN_TIME_TWILIGHT;
    default:
        // The first hour of night is still fading down from evening in the
        // overworld, so keep the sunset backgrounds through it.
        if (IsBetweenHours(GetTimeOfDayHours(), NIGHT_HOUR_BEGIN, NIGHT_HOUR_BEGIN + 1))
            return BATTLE_TERRAIN_TIME_TWILIGHT;
        return BATTLE_TERRAIN_TIME_NIGHT;
    }
}

// Pokémon Rhythm backdrops occupy BG3 as complete stationary scenes.
// Match surroundings while keeping all 55 original Rhythm indices reachable.
static const u8 sPruRhythmGrass[] = {0, 9, 21, 32, 33, 34, 37, 39, 42, 43};
static const u8 sPruRhythmWater[] = {2, 4, 5, 20, 30, 40, 48, 53};
static const u8 sPruRhythmCave[] = {3, 7, 16, 19, 36, 41, 47, 54};
static const u8 sPruRhythmRock[] = {1, 6, 15, 35, 36, 45, 50, 52};
static const u8 sPruRhythmIce[] = {3, 13, 14, 23, 24};
static const u8 sPruRhythmUrban[] = {8, 10, 11, 12, 17, 22, 26, 28, 31, 41, 44, 46, 49, 51};
static const u8 sPruRhythmVolcano[] = {16, 25, 54};
static const u8 sPruRhythmBurial[] = {18, 19, 27, 29, 38, 44};
static const u8 sPruElite20RhythmScenes[20] = {35, 48, 46, 34, 39, 19, 16, 45, 14, 8, 18, 38, 30, 42, 49, 54, 41, 36, 13, 0};

static u8 GetPruElite20RhythmBgIndex(void)
{
    u32 trainerA;
    u32 trainerB;

    // The Dojo reuses many trainers seen elsewhere. Match both opponents so
    // these arenas never leak into their unrelated solo battles.
    if (!(gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS))
        return 0xFF;

    trainerA = TRAINER_BATTLE_PARAM.opponentA;
    trainerB = TRAINER_BATTLE_PARAM.opponentB;
#define MATCH_ELITE20_PAIR(round, normalA, normalB, masterA, masterB) \
    if (((trainerA == normalA) && (trainerB == normalB)) \
     || ((trainerA == masterA) && (trainerB == masterB))) \
        return sPruElite20RhythmScenes[(round) - 1]

    MATCH_ELITE20_PAIR(1, TRAINER_PRU_E18_01_A_HNS, TRAINER_PRU_E18_01_B_HNS, TRAINER_PRU_E18_01_A_MASTER_HNS, TRAINER_PRU_E18_01_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(2, TRAINER_PRU_E18_02_A_HNS, TRAINER_PRU_E18_02_B_HNS, TRAINER_PRU_E18_02_A_MASTER_HNS, TRAINER_PRU_E18_02_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(3, TRAINER_PRU_E18_03_A_HNS, TRAINER_PRU_E18_03_B_HNS, TRAINER_PRU_E18_03_A_MASTER_HNS, TRAINER_PRU_E18_03_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(4, TRAINER_PRU_E18_04_A_HNS, TRAINER_PRU_E18_04_B_HNS, TRAINER_PRU_E18_04_A_MASTER_HNS, TRAINER_PRU_E18_04_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(5, TRAINER_PRU_E18_05_A_HNS, TRAINER_PRU_E18_05_B_HNS, TRAINER_PRU_E18_05_A_MASTER_HNS, TRAINER_PRU_E18_05_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(6, TRAINER_PRU_E18_06_A_HNS, TRAINER_PRU_E18_06_B_HNS, TRAINER_PRU_E18_06_A_MASTER_HNS, TRAINER_PRU_E18_06_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(7, TRAINER_PRU_E18_07_A_HNS, TRAINER_PRU_E18_07_B_HNS, TRAINER_PRU_E18_07_A_MASTER_HNS, TRAINER_PRU_E18_07_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(8, TRAINER_PRU_E20_JASMINE_HNS, TRAINER_PRU_E20_CLAIR_HNS, TRAINER_PRU_E20_JASMINE_MASTER_HNS, TRAINER_PRU_E20_CLAIR_MASTER_HNS);
    MATCH_ELITE20_PAIR(9, TRAINER_PRU_E18_09_A_HNS, TRAINER_PRU_E18_09_B_HNS, TRAINER_PRU_E18_09_A_MASTER_HNS, TRAINER_PRU_E18_09_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(10, TRAINER_PRU_E18_10_A_HNS, TRAINER_PRU_E18_10_B_HNS, TRAINER_PRU_E18_10_A_MASTER_HNS, TRAINER_PRU_E18_10_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(11, TRAINER_PRU_E18_11_A_HNS, TRAINER_PRU_E18_11_B_HNS, TRAINER_PRU_E18_11_A_MASTER_HNS, TRAINER_PRU_E18_11_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(12, TRAINER_PRU_E18_12_A_HNS, TRAINER_PRU_E18_12_B_HNS, TRAINER_PRU_E18_12_A_MASTER_HNS, TRAINER_PRU_E18_12_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(13, TRAINER_PRU_E18_13_A_HNS, TRAINER_PRU_E18_13_B_HNS, TRAINER_PRU_E18_13_A_MASTER_HNS, TRAINER_PRU_E18_13_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(14, TRAINER_PRU_E18_14_A_HNS, TRAINER_PRU_E18_14_B_HNS, TRAINER_PRU_E18_14_A_MASTER_HNS, TRAINER_PRU_E18_14_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(15, TRAINER_PRU_E18_15_A_HNS, TRAINER_PRU_E18_15_B_HNS, TRAINER_PRU_E18_15_A_MASTER_HNS, TRAINER_PRU_E18_15_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(16, TRAINER_PRU_E18_08_A_HNS, TRAINER_PRU_E18_08_B_HNS, TRAINER_PRU_E18_08_A_MASTER_HNS, TRAINER_PRU_E18_08_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(17, TRAINER_PRU_E20_STEVEN_HNS, TRAINER_PRU_E20_MAY_HNS, TRAINER_PRU_E20_STEVEN_MASTER_HNS, TRAINER_PRU_E20_MAY_MASTER_HNS);
    MATCH_ELITE20_PAIR(18, TRAINER_PRU_E20_RIVAL_HNS, TRAINER_PRU_E20_GIOVANNI_HNS, TRAINER_PRU_E20_RIVAL_MASTER_HNS, TRAINER_PRU_E20_GIOVANNI_MASTER_HNS);
    MATCH_ELITE20_PAIR(19, TRAINER_PRU_E18_17_A_HNS, TRAINER_PRU_E18_17_B_HNS, TRAINER_PRU_E18_17_A_MASTER_HNS, TRAINER_PRU_E18_17_B_MASTER_HNS);
    MATCH_ELITE20_PAIR(20, TRAINER_PRU_E18_18_A_HNS, TRAINER_PRU_E18_18_B_HNS, TRAINER_PRU_E18_18_A_MASTER_HNS, TRAINER_PRU_E18_18_B_MASTER_HNS);
#undef MATCH_ELITE20_PAIR
    return 0xFF;
}

// Area selection derived from PRU map.json: location, weather and cave families.
// One coherent background per multi-floor cave system; never shift/stretch bottom tiles.
static u8 GetPruNewAreaBackgroundIndex(void)
{
    switch ((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum)
    {
    case MAP_AKALA_CAVE_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_AKALA_FOREST_HNS: return 56; // general outdoor grass
    case MAP_AKALA_ISLE_HNS: return 56; // general outdoor grass
    case MAP_ALOLA_WATER_HNS: return 56; // general outdoor grass
    case MAP_AZALEA_TOWN_HNS: return 57; // town/city MAPSEC_AZALEA_TOWN
    case MAP_BATTLE_FRONTIER_OUTSIDE_EAST_HNS: return 56; // general outdoor grass
    case MAP_BATTLE_FRONTIER_OUTSIDE_WEST_HNS: return 56; // general outdoor grass
    case MAP_BELLCHIME_TRAIL_HNS: return 56; // general outdoor grass
    case MAP_BIRTH_ISLAND_EXTERIOR_HNS: return 56; // general outdoor grass
    case MAP_BLACKTHORN_CITY_HNS: return 61; // town/city MAPSEC_BLACKTHORN_CITY
    case MAP_BURNED_TOWER_1F_HNS: return 58; // cave/interior system MAPSEC_BURNED_TOWER
    case MAP_BURNED_TOWER_B1F_HNS: return 58; // cave/interior system MAPSEC_BURNED_TOWER
    case MAP_CELADON_CITY_APARTMENTS_ROOF_DAY_HNS: return 57; // town/city MAPSEC_CELADON_CITY
    case MAP_CELADON_CITY_APARTMENTS_ROOF_NIGHT_HNS: return 57; // town/city MAPSEC_CELADON_CITY
    case MAP_CELADON_CITY_DEPARTMENT_STORE_ROOF_DAY_HNS: return 56; // general outdoor grass
    case MAP_CELADON_CITY_DEPARTMENT_STORE_ROOF_NIGHT_HNS: return 56; // general outdoor grass
    case MAP_CELADON_CITY_HNS: return 57; // town/city MAPSEC_CELADON_CITY
    case MAP_CERULEAN_CAVE_1F_HNS: return 63; // cave/interior system MAPSEC_CERULEAN_CAVE
    case MAP_CERULEAN_CAVE_B1F_HNS: return 63; // cave/interior system MAPSEC_CERULEAN_CAVE
    case MAP_CERULEAN_CAVE_B2F_HNS: return 63; // cave/interior system MAPSEC_CERULEAN_CAVE
    case MAP_CERULEAN_CITY_HNS: return 56; // town/city MAPSEC_CERULEAN_CITY
    case MAP_CHERRYGROVE_CITY_HNS: return 56; // town/city MAPSEC_CHERRYGROVE_CITY
    case MAP_CIANWOOD_CITY_HNS: return 64; // town/city MAPSEC_CIANWOOD_CITY / local WEATHER_RAIN
    case MAP_CLIFF_EDGE_CAVE_HNS: return 63; // cave/interior system MAPSEC_CLIFF_CAVE
    case MAP_CLIFF_EDGE_GATE_HNS: return 63; // cave/interior system MAPSEC_CLIFF_CAVE
    case MAP_DARK_CAVE_NORTH_SIDE_HNS: return 63; // cave/interior system MAPSEC_DARK_CAVE
    case MAP_DARK_CAVE_SOUTH_SIDE_HNS: return 63; // cave/interior system MAPSEC_DARK_CAVE
    case MAP_DIGLETTS_CAVE_ENTRANCE_NORTH_HNS: return 63; // cave/interior system MAPSEC_DIGLETTS_CAVE
    case MAP_DIGLETTS_CAVE_ENTRANCE_SOUTH_HNS: return 63; // cave/interior system MAPSEC_DIGLETTS_CAVE
    case MAP_DIGLETTS_CAVE_TUNNEL_HNS: return 63; // cave/interior system MAPSEC_DIGLETTS_CAVE
    case MAP_DRAGONS_DEN_CAVERN_HNS: return 59; // cave/interior system MAPSEC_DRAGONS_DEN
    case MAP_DRAGONS_DEN_ENTRANCE_HNS: return 59; // cave/interior system MAPSEC_DRAGONS_DEN
    case MAP_DRAGONS_DEN_SHRINE_HNS: return 59; // cave/interior system MAPSEC_DRAGONS_DEN
    case MAP_DRAGONS_DEN_STORM_SHRINE_HNS: return 59; // cave/interior system MAPSEC_DRAGONS_DEN
    case MAP_ECRUTEAK_CITY_HNS: return 58; // town/city MAPSEC_ECRUTEAK_CITY
    case MAP_EMBEDDED_TOWER_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_FUCHSIA_CITY_HNS: return 57; // town/city MAPSEC_FUCHSIA_CITY
    case MAP_FUCHSIA_CITY_SAFARI_ZONE_BRUSH_HNS: return 56; // general outdoor grass
    case MAP_FUCHSIA_CITY_SAFARI_ZONE_CAVE_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_FUCHSIA_CITY_SAFARI_ZONE_MOUNTAIN_HNS: return 56; // general outdoor grass
    case MAP_GOLDENROD_CITY_DEPARTMENT_STORE_7FNIGHT_HNS: return 58; // town/city MAPSEC_GOLDENROD_CITY
    case MAP_GOLDENROD_CITY_DEPARTMENT_STORE_7F_HNS: return 58; // town/city MAPSEC_GOLDENROD_CITY
    case MAP_GOLDENROD_CITY_HNS: return 58; // town/city MAPSEC_GOLDENROD_CITY
    case MAP_ICE_PATH_1F_HNS: return 59; // cave/interior system MAPSEC_ICE_PATH
    case MAP_ICE_PATH_B1F_HNS: return 59; // cave/interior system MAPSEC_ICE_PATH
    case MAP_ICE_PATH_B2F_HNS: return 59; // cave/interior system MAPSEC_ICE_PATH
    case MAP_ICE_PATH_B3F_HNS: return 59; // cave/interior system MAPSEC_ICE_PATH
    case MAP_ICE_PATH_B4F_HNS: return 59; // cave/interior system MAPSEC_ICE_PATH
    case MAP_ILEX_FOREST_HNS: return 56; // general outdoor grass
    case MAP_INDIGO_PLATEAU_HNS: return 56; // town/city MAPSEC_INDIGO_PLATEAU
    case MAP_LAKE_OF_RAGE_HNS: return 64; // lake of rage / storm / local WEATHER_RAIN_THUNDERSTORM
    case MAP_LAKE_OF_RAGE_LOW_TIDE_HNS: return 64; // lake of rage / storm
    case MAP_LAVENDER_TOWN_HNS: return 58; // town/city MAPSEC_LAVENDER_TOWN
    case MAP_MAHOGANYTOWN_HNS: return 56; // town/city MAPSEC_MAHOGANY_TOWN
    case MAP_MELEMELE_ISLE_HNS: return 56; // general outdoor grass
    case MAP_MT_MOON_CAVE_HNS: return 63; // cave/interior system MAPSEC_MT_MOON
    case MAP_MT_MOON_OUTSIDE_HNS: return 56; // general outdoor grass
    case MAP_MT_MORTAR_1F_NORTH_HNS: return 60; // cave/interior system MAPSEC_MT_MORTAR
    case MAP_MT_MORTAR_1F_SOUTH_HNS: return 60; // cave/interior system MAPSEC_MT_MORTAR
    case MAP_MT_MORTAR_2F_HNS: return 60; // cave/interior system MAPSEC_MT_MORTAR
    case MAP_MT_MORTAR_B1F_HNS: return 60; // cave/interior system MAPSEC_MT_MORTAR
    case MAP_MT_SILVER_1F_ITEM_ROOM_HNS: return 61; // cave/interior system MAPSEC_MT_SILVER
    case MAP_MT_SILVER_1F_MOLTRES_ROOM_HNS: return 61; // cave/interior system MAPSEC_MT_SILVER
    case MAP_MT_SILVER_1F_WATERFALL_ROOM_HNS: return 61; // cave/interior system MAPSEC_MT_SILVER
    case MAP_MT_SILVER_2F_HNS: return 61; // cave/interior system MAPSEC_MT_SILVER
    case MAP_MT_SILVER_3F_HNS: return 61; // cave/interior system MAPSEC_MT_SILVER
    case MAP_MT_SILVER_MOUNTAIN_SIDE_HNS: return 61; // cave/interior system MAPSEC_MT_SILVER
    case MAP_MT_SILVER_OUTSIDE_HNS: return 61; // cave/interior system MAPSEC_MT_SILVER
    case MAP_MT_SILVER_POKEMON_CENTER_HNS: return 61; // cave/interior system MAPSEC_MT_SILVER
    case MAP_MT_SILVER_SNOW_HNS: return 61; // cave/interior system MAPSEC_MT_SILVER
    case MAP_NATIONAL_PARK_BUG_CONTEST_HNS: return 56; // general outdoor grass
    case MAP_NATIONAL_PARK_NORMAL_HNS: return 56; // general outdoor grass
    case MAP_NEWSINJOH_HOTSPRINGS_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_NEW_BARK_TOWN_HNS: return 56; // town/city MAPSEC_NEW_BARK_TOWN
    case MAP_NEW_SINJOH_HNS: return 56; // town/city MAPSEC_NEW_SINJOH
    case MAP_OLIVINE_CITY_HNS: return 64; // town/city MAPSEC_OLIVINE_CITY / local WEATHER_RAIN
    case MAP_PALLET_TOWN_HNS: return 56; // town/city MAPSEC_PALLET_TOWN
    case MAP_PEWTER_CITY_HNS: return 61; // town/city MAPSEC_PEWTER_CITY
    case MAP_PONI_CAVE_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_PONI_ISLE_HNS: return 56; // general outdoor grass
    case MAP_ROCK_TUNNEL_1F_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_ROCK_TUNNEL_B1F_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_ROUTE10_HNS: return 61; // route 10 terrain
    case MAP_ROUTE11_HNS: return 66; // route 11 terrain
    case MAP_ROUTE12_HNS: return 66; // route 12 terrain
    case MAP_ROUTE13_HNS: return 66; // route 13 terrain
    case MAP_ROUTE14_HNS: return 66; // route 14 terrain
    case MAP_ROUTE15_HNS: return 56; // route 15 terrain
    case MAP_ROUTE16_HNS: return 56; // route 16 terrain
    case MAP_ROUTE17_HNS: return 64; // route 17 terrain / local WEATHER_RAIN
    case MAP_ROUTE18_HNS: return 66; // route 18 terrain
    case MAP_ROUTE19_CAVE_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_ROUTE19_HNS: return 66; // route 19 terrain
    case MAP_ROUTE1_HNS: return 56; // route 1 terrain
    case MAP_ROUTE20_HNS: return 66; // route 20 terrain
    case MAP_ROUTE21_HNS: return 66; // route 21 terrain
    case MAP_ROUTE22_HNS: return 56; // route 22 terrain
    case MAP_ROUTE23_HNS: return 56; // general outdoor grass
    case MAP_ROUTE24_HNS: return 65; // route 24 terrain
    case MAP_ROUTE25_HNS: return 65; // route 25 terrain
    case MAP_ROUTE26NORTH_HNS: return 56; // route 26 terrain
    case MAP_ROUTE26_HNS: return 56; // route 26 terrain
    case MAP_ROUTE27_HNS: return 56; // route 27 terrain
    case MAP_ROUTE28_HNS: return 56; // route 28 terrain
    case MAP_ROUTE29_HNS: return 56; // route 29 terrain
    case MAP_ROUTE2_HNS: return 57; // route 2 terrain
    case MAP_ROUTE30_HNS: return 65; // route 30 terrain
    case MAP_ROUTE31_HNS: return 65; // route 31 terrain
    case MAP_ROUTE32_HNS: return 65; // route 32 terrain
    case MAP_ROUTE33_HNS: return 56; // route 33 terrain
    case MAP_ROUTE34_HNS: return 56; // route 34 terrain
    case MAP_ROUTE35_HNS: return 56; // route 35 terrain
    case MAP_ROUTE36_HNS: return 58; // route 36 terrain
    case MAP_ROUTE37_HNS: return 57; // route 37 terrain
    case MAP_ROUTE38_HNS: return 56; // route 38 terrain
    case MAP_ROUTE39_HNS: return 56; // route 39 terrain
    case MAP_ROUTE3_HNS: return 56; // route 3 terrain
    case MAP_ROUTE40_HNS: return 64; // route 40 terrain / local WEATHER_RAIN
    case MAP_ROUTE41_HNS: return 64; // route 41 terrain / local WEATHER_RAIN_THUNDERSTORM
    case MAP_ROUTE42_HNS: return 61; // route 42 terrain
    case MAP_ROUTE43_HNS: return 64; // route 43 terrain
    case MAP_ROUTE44_HNS: return 59; // route 44 terrain
    case MAP_ROUTE45_GROUDON_CAVE_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_ROUTE45_HNS: return 61; // route 45 terrain
    case MAP_ROUTE46_HNS: return 61; // route 46 terrain
    case MAP_ROUTE47_HNS: return 61; // route 47 terrain
    case MAP_ROUTE48_HNS: return 61; // route 48 terrain
    case MAP_ROUTE49_HNS: return 56; // route 49 terrain
    case MAP_ROUTE4_HNS: return 56; // route 4 terrain
    case MAP_ROUTE50_HNS: return 56; // route 50 terrain
    case MAP_ROUTE5_HNS: return 56; // route 5 terrain
    case MAP_ROUTE6_HNS: return 56; // route 6 terrain
    case MAP_ROUTE7_HNS: return 56; // route 7 terrain
    case MAP_ROUTE8_HNS: return 56; // route 8 terrain
    case MAP_ROUTE9_HNS: return 65; // route 9 terrain
    case MAP_RUINS_OF_ALPH_B1F_HNS: return 58; // cave/interior system MAPSEC_RUINS_OF_ALPH
    case MAP_RUINS_OF_ALPH_LAB_HNS: return 58; // cave/interior system MAPSEC_RUINS_OF_ALPH
    case MAP_RUINS_OF_ALPH_OUTSIDE_HNS: return 58; // cave/interior system MAPSEC_RUINS_OF_ALPH
    case MAP_RUINS_OF_ALPH_PUZZLE_AND_REWARD_CHAMBERS_HNS: return 58; // cave/interior system MAPSEC_RUINS_OF_ALPH
    case MAP_RUINS_OF_ALPH_WORDS_ROOM1_HNS: return 58; // cave/interior system MAPSEC_RUINS_OF_ALPH
    case MAP_RUINS_OF_ALPH_WORDS_ROOM2_HNS: return 58; // cave/interior system MAPSEC_RUINS_OF_ALPH
    case MAP_RUINS_OF_ALPH_WORDS_ROOM3_HNS: return 58; // cave/interior system MAPSEC_RUINS_OF_ALPH
    case MAP_RUINS_OF_ALPH_WORDS_ROOM4_HNS: return 58; // cave/interior system MAPSEC_RUINS_OF_ALPH
    case MAP_SAFARI_ZONE1_HNS: return 56; // general outdoor grass
    case MAP_SAFARI_ZONE2_HNS: return 56; // general outdoor grass
    case MAP_SAFARI_ZONE3_HNS: return 56; // general outdoor grass
    case MAP_SAFARI_ZONE_ENTERANCE_HNS: return 56; // general outdoor grass
    case MAP_SAFARI_ZONE_GATE_HNS: return 56; // town/city MAPSEC_SAFARI_ZONE_GATE
    case MAP_SAFARI_ZONE_LOW_LEFT_HNS: return 56; // general outdoor grass
    case MAP_SAFARI_ZONE_LOW_MID_HNS: return 56; // general outdoor grass
    case MAP_SAFARI_ZONE_TOP_LEFT_HNS: return 56; // general outdoor grass
    case MAP_SAFARI_ZONE_TOP_MID_HNS: return 56; // general outdoor grass
    case MAP_SAFFRON_CITY_HNS: return 58; // town/city MAPSEC_SAFFRON_CITY
    case MAP_SEAFOAM_ISLANDS_1F_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_SEAFOAM_ISLANDS_B1F_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_SEAFOAM_ISLANDS_GYM_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_SEAFOAM_ISLANDS_SECRET_CAVE_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_SINJOH_RUINS_HNS: return 56; // town/city MAPSEC_SINJOH_RUINS
    case MAP_SLOWPOKE_WELL_B1F_HNS: return 63; // cave/interior system MAPSEC_SLOWPOKE_WELL
    case MAP_SLOWPOKE_WELL_B2F_HNS: return 63; // cave/interior system MAPSEC_SLOWPOKE_WELL
    case MAP_SNOWSWEPT_CAVERN_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_SOUTHERN_ISLAND_EXTERIOR_HNS: return 56; // general outdoor grass
    case MAP_SOUTHERN_ISLAND_INTERIOR_HNS: return 56; // general outdoor grass
    case MAP_TIN_TOWER_1F_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_2F_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_3F_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_4F_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_5F_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_6F_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_7F_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_8F_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_9F_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_ROOF_DAY_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TIN_TOWER_ROOF_NIGHT_HNS: return 58; // cave/interior system MAPSEC_TIN_TOWER
    case MAP_TOHJO_FALLS_CAVERN_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_TOHJO_FALLS_GIOVANNI_ROOM_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_TRAINER_HILL_COURTYARD_HNS: return 56; // general outdoor grass
    case MAP_ULAULA_ISLE_HNS: return 56; // general outdoor grass
    case MAP_ULA_ULA_CAVE_2_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_ULA_ULA_CAVE_HNS: return 63; // unclassified underground; general limestone cave
    case MAP_ULA_ULA_FOREST_HNS: return 56; // general outdoor grass
    case MAP_UNION_CAVE_1F_HNS: return 63; // cave/interior system MAPSEC_UNION_CAVE
    case MAP_UNION_CAVE_B1F_HNS: return 63; // cave/interior system MAPSEC_UNION_CAVE
    case MAP_UNION_CAVE_B2F_HNS: return 63; // cave/interior system MAPSEC_UNION_CAVE
    case MAP_VERMILION_CITY_HNS: return 66; // town/city MAPSEC_VERMILION_CITY
    case MAP_VICTORY_ROAD_KANTO_1F_HNS: return 63; // cave/interior system MAPSEC_VICTORY_ROAD_HNS
    case MAP_VICTORY_ROAD_KANTO_B1F_HNS: return 63; // cave/interior system MAPSEC_VICTORY_ROAD_HNS
    case MAP_VICTORY_ROAD_KANTO_B2F_HNS: return 63; // cave/interior system MAPSEC_VICTORY_ROAD_HNS
    case MAP_VIOLET_CITY_HNS: return 56; // town/city MAPSEC_VIOLET_CITY
    case MAP_VIRIDIAN_CITY_HNS: return 56; // town/city MAPSEC_VIRIDIAN_CITY
    case MAP_VIRIDIAN_FOREST_HNS: return 57; // forest
    case MAP_WHIRL_ISLANDS_1F_HNS: return 59; // cave/interior system MAPSEC_WHIRL_ISLANDS
    case MAP_WHIRL_ISLANDS_B1F_HNS: return 59; // cave/interior system MAPSEC_WHIRL_ISLANDS
    case MAP_WHIRL_ISLANDS_B1F_INNER_HNS: return 59; // cave/interior system MAPSEC_WHIRL_ISLANDS
    case MAP_WHIRL_ISLANDS_B2F_HNS: return 59; // cave/interior system MAPSEC_WHIRL_ISLANDS
    case MAP_WHIRL_ISLANDS_B3F_HNS: return 59; // cave/interior system MAPSEC_WHIRL_ISLANDS
    case MAP_WHIRL_ISLANDS_DESCENT_HNS: return 59; // cave/interior system MAPSEC_WHIRL_ISLANDS
    case MAP_WHIRL_ISLANDS_LUGIA_CHAMBER_HNS: return 59; // cave/interior system MAPSEC_WHIRL_ISLANDS
    default: return 0xFF;
    }
}

static u8 GetPruRhythmBattleBgIndex(u16 environment)
{
#if IS_HNS
    const u8 *choices = sPruRhythmGrass;
    u32 count = NELEMS(sPruRhythmGrass);
    u32 mapSeed;

    // Do not affect link battles, battle facilities or forced test environments.
    if (TestRunner_Battle_GetForcedEnvironment()
     || (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_FRONTIER | BATTLE_TYPE_RECORDED_LINK | BATTLE_TYPE_EREADER_TRAINER)))
        return 0xFF;

    // Golden Ho-Oh is the only non-trainer Mt Silver summit encounter.
    // Trainer battles (including Red) retain the separate rocky Mt Silver scene.
    if (((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum)
          == MAP_MT_SILVER_SUMMIT_DAY_HNS
     || ((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum)
          == MAP_MT_SILVER_SUMMIT_NIGHT_HNS)
        return (gBattleTypeFlags & BATTLE_TYPE_TRAINER) ? 61 : 62;

    // Approved location-specific PRU scenes, then a shared natural biomes fallback.

    switch ((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum)
    {
    case MAP_MT_SILVER_OUTSIDE_HNS:
    case MAP_MT_SILVER_1F_WATERFALL_ROOM_HNS:
    case MAP_MT_SILVER_2F_HNS:
    case MAP_MT_SILVER_3F_HNS:
    case MAP_MT_SILVER_SNOW_HNS:
        return 61; // User-approved redrawn rocky Mt Silver stage.
    case MAP_ROUTE29_HNS:
        return 56; // Original grassy Route 29 scene.
    case MAP_ILEX_FOREST_HNS:
        return 57; // Original misty forest and shrine clearing.
    case MAP_RUINS_OF_ALPH_OUTSIDE_HNS:
        return 58; // Original ruins meadow with stone archway.
    case MAP_ICE_PATH_1F_HNS:
    case MAP_ICE_PATH_B1F_HNS:
    case MAP_ICE_PATH_B2F_HNS:
    case MAP_ICE_PATH_B3F_HNS:
    case MAP_ICE_PATH_B4F_HNS:
        return 59; // Original blue crystal ice chamber.
    case MAP_MT_MORTAR_B1F_HNS:
        return 60; // Original volcanic relic chamber (Entei region).
    case MAP_SEAFOAM_ISLANDS_SECRET_CAVE_HNS:
        return 48; // PRU shared icy-water environment, for Archie and Kyogre.
    case MAP_MT_SILVER_1F_MOLTRES_ROOM_HNS:
        return 16; // PRU original volcanic environment, for Groudon.
    case MAP_LAVENDER_SPIRIT_TOWER_1F_HNS:
    case MAP_LAVENDER_SPIRIT_TOWER_2F_HNS:
    case MAP_LAVENDER_SPIRIT_TOWER_3F_HNS:
    case MAP_LAVENDER_SPIRIT_TOWER_4F_HNS:
    case MAP_LAVENDER_SPIRIT_TOWER_5F_HNS:
    case MAP_LAVENDER_SPIRIT_TOWER_6F_HNS:
    case MAP_LAVENDER_SPIRIT_TOWER_7F_HNS:
        return 44; // PRU original ancient ruins environment.
    }

    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        u8 elite20Bg = GetPruElite20RhythmBgIndex();
        if (elite20Bg != 0xFF)
            return elite20Bg;

        // Distinct Gym Leader arenas; rematches and postgame challenges use
        // the same leader's background, independent of their map location.
        switch (TRAINER_BATTLE_PARAM.opponentA)
        {
        // The reused League rooms select trainer IDs from the championship
        // progression scripts, so route by the actual battle rather than room.
        case TRAINER_WILL_1_HNS:
        case TRAINER_WILL_2_HNS:
        case TRAINER_WILL_POSTOBC_HNS: return 19; // Psychic Arena.
        case TRAINER_KOGA_1_HNS:
        case TRAINER_KOGA_2_HNS:
        case TRAINER_KOGA_POSTOBC_HNS: return 39; // Shadowy Jungle.
        case TRAINER_BRUNO_1_HNS:
        case TRAINER_BRUNO_2_HNS:
        case TRAINER_BRUNO_POSTOBC_HNS:
        case TRAINER_PRU_KANTO_E4_BRUNO_HNS: return 8; // Fighting Stadium.
        case TRAINER_KAREN_1_HNS:
        case TRAINER_KAREN_2_HNS:
        case TRAINER_KAREN_POSTOBC_HNS: return 38; // Dark Arena.
        case TRAINER_LANCE_1_HNS:
        case TRAINER_LANCE_2_HNS:
        case TRAINER_LANCE_3_HNS:
        case TRAINER_LANCE_POSTOBC_HNS:
        case TRAINER_PRU_KANTO_E4_LANCE_HNS: return 30; // Mountain Bridge.
        case TRAINER_PRU_KANTO_E4_LORELEI_HNS: return 14; // Snow Pass.
        case TRAINER_PRU_KANTO_E4_AGATHA_HNS: return 18; // Graveyard.
        case TRAINER_PRU_KANTO_E4_RED_HNS:
        case TRAINER_RED_POSTOBC_HNS: return 13; // Mt. Silver Snowy Forest.
        case TRAINER_FALKNER_1_HNS:
        case TRAINER_FALKNER_2_HNS:
        case TRAINER_FALKNER_POSTOBC_HNS: return 0;
        case TRAINER_BUGSY_1_HNS:
        case TRAINER_BUGSY_2_HNS:
        case TRAINER_BUGSY_POSTOBC_HNS: return 43;
        case TRAINER_WHITNEY_1_HNS:
        case TRAINER_WHITNEY_2_HNS:
        case TRAINER_WHITNEY_POSTOBC_HNS: return 8;
        case TRAINER_MORTY_1_HNS:
        case TRAINER_MORTY_2_HNS:
        case TRAINER_MORTY_POSTOBC_HNS: return 44;
        case TRAINER_CHUCK_1_HNS:
        case TRAINER_CHUCK_2_HNS:
        case TRAINER_CHUCK_1_2_HNS:
        case TRAINER_CHUCK_1_3_HNS:
        case TRAINER_CHUCK_POSTOBC_HNS: return 45;
        case TRAINER_JASMINE_1_HNS:
        case TRAINER_JASMINE_2_HNS:
        case TRAINER_JASMINE_1_2_HNS:
        case TRAINER_JASMINE_1_3_HNS:
        case TRAINER_JASMINE_POSTOBC_HNS: return 30;
        case TRAINER_PRYCE_1_HNS:
        case TRAINER_PRYCE_2_HNS:
        case TRAINER_PRYCE_1_2_HNS:
        case TRAINER_PRYCE_1_3_HNS:
        case TRAINER_PRYCE_POSTOBC_HNS: return 14;
        case TRAINER_CLAIR_1_HNS:
        case TRAINER_CLAIR_2_HNS:
        case TRAINER_CLAIR_3_HNS:
        case TRAINER_CLAIR_POSTOBC_HNS: return 41;
        case TRAINER_BROCK_HNS:
        case TRAINER_BROCK_POSTOBC_HNS: return 35;
        case TRAINER_MISTY_HNS:
        case TRAINER_MISTY_POSTOBC_HNS: return 48;
        case TRAINER_LTSURGE_HNS:
        case TRAINER_LTSURGE_POSTOBC_HNS: return 46;
        case TRAINER_ERIKA_HNS:
        case TRAINER_ERIKA_POSTOBC_HNS: return 9;
        case TRAINER_JANINE_HNS:
        case TRAINER_JANINE_POSTOBC_HNS: return 31;
        case TRAINER_SABRINA_HNS:
        case TRAINER_SABRINA_POSTOBC_HNS: return 19;
        case TRAINER_BLAINE_HNS:
        case TRAINER_BLAINE_POSTOBC_HNS: return 16;
        case TRAINER_BLUE_HNS:
        case TRAINER_BLUE_2_HNS:
        case TRAINER_BLUE_POSTOBC_HNS: return 51;
        default: break;
        }
    }


    // Actual PRU terrain and map weather take priority over random donor-slot choices.
    // E20 and Gym trainer-specific selections above remain authoritative.
    {
        u8 mapped = GetPruNewAreaBackgroundIndex();
        if (mapped != 0xFF)
            return mapped;
    }

    // Wild and regular trainer fights use scenery appropriate to the map.
    // Stable map-based variety through 55 shared slots of original PRU art.
    switch (environment)
    {
    case BATTLE_ENVIRONMENT_WATER:
    case BATTLE_ENVIRONMENT_POND:
    case BATTLE_ENVIRONMENT_UNDERWATER:
    case BATTLE_ENVIRONMENT_CAVE_WATER:
    case BATTLE_ENVIRONMENT_GRAY_CAVE_WATER:
        choices = sPruRhythmWater;
        count = NELEMS(sPruRhythmWater);
        break;
    case BATTLE_ENVIRONMENT_CAVE:
    case BATTLE_ENVIRONMENT_GRAY_CAVE:
        choices = sPruRhythmCave;
        count = NELEMS(sPruRhythmCave);
        break;
    case BATTLE_ENVIRONMENT_MOUNTAIN:
    case BATTLE_ENVIRONMENT_SAND:
        choices = sPruRhythmRock;
        count = NELEMS(sPruRhythmRock);
        break;
    case BATTLE_ENVIRONMENT_ROCK_SNOW:
    case BATTLE_ENVIRONMENT_MOUNTAIN_SNOW:
    case BATTLE_ENVIRONMENT_SNOW_CAVE:
    case BATTLE_ENVIRONMENT_ICE:
    case BATTLE_ENVIRONMENT_SNOW:
        choices = sPruRhythmIce;
        count = NELEMS(sPruRhythmIce);
        break;
    case BATTLE_ENVIRONMENT_VOLCANO:
    case BATTLE_ENVIRONMENT_VOLCANO_CAVE:
        choices = sPruRhythmVolcano;
        count = NELEMS(sPruRhythmVolcano);
        break;
    case BATTLE_ENVIRONMENT_BURIAL_GROUND:
        choices = sPruRhythmBurial;
        count = NELEMS(sPruRhythmBurial);
        break;
    case BATTLE_ENVIRONMENT_BUILDING:
    case BATTLE_ENVIRONMENT_GYM:
    case BATTLE_ENVIRONMENT_LEADER:
    case BATTLE_ENVIRONMENT_BLUE_BUILDING:
        choices = sPruRhythmUrban;
        count = NELEMS(sPruRhythmUrban);
        break;
    default:
        break;
    }

    mapSeed = (u32)gSaveBlock1Ptr->location.mapGroup * 131
            + (u32)gSaveBlock1Ptr->location.mapNum * 17
            + environment * 7;
    return choices[mapSeed % count];
#else
    return 0xFF;
#endif
}

static void LoadBattleEnvironmentGfx(u16 environment)
{
    const void *tileset, *tilemap, *palette;

    u8 pruRhythmBg = GetPruRhythmBattleBgIndex(environment);
    if (pruRhythmBg >= 55 && pruRhythmBg < 67)
    {
        // Eight original PRU scenes selected independently of the 55 legacy slots.
        const struct PruRhythmBattleBg *bg = &sPruOriginalTestBattleBgs[pruRhythmBg - 55];
        DecompressDataWithHeaderVram(bg->tiles, (void *)BG_CHAR_ADDR(2));
        DecompressDataWithHeaderVram(bg->tilemap, (void *)BG_SCREEN_ADDR(26));
        LoadPalette(bg->palette, BG_PLTT_ID(12), 3 * PLTT_SIZE_4BPP);
        return;
    }
    if (pruRhythmBg != 0xFF)
    {
        // Transfer one complete image; never mix separate donor entry panels.
        const struct PruRhythmBattleBg *bg = &sPruRhythmBattleBgs[pruRhythmBg];
        DecompressDataWithHeaderVram(bg->tiles, (void *)BG_CHAR_ADDR(2));
        DecompressDataWithHeaderVram(bg->tilemap, (void *)BG_SCREEN_ADDR(26));
        LoadPalette(bg->palette, BG_PLTT_ID(12), 3 * PLTT_SIZE_4BPP);
        return;
    }

    if (environment >= NELEMS(gBattleEnvironmentInfo))
        environment = BATTLE_ENVIRONMENT_PLAIN;

    tileset = gBattleEnvironmentInfo[environment].background.tileset;
    tilemap = gBattleEnvironmentInfo[environment].background.tilemap;
    palette = gBattleEnvironmentInfo[environment].palette;

    if (UseModernBattleEnvironment())
    {
        const struct ModernBattleGfx *modern = &sModernBattleGfx[environment];
        if (modern->background.tileset)
            tileset = modern->background.tileset;
        if (modern->background.tilemap)
            tilemap = modern->background.tilemap;
        if (modern->palette)
        {
            u32 terrainTime = GetBattleTerrainTimeOfDay();
            palette = modern->palette;
            if (terrainTime == BATTLE_TERRAIN_TIME_NIGHT && modern->paletteNight)
                palette = modern->paletteNight;
            else if (terrainTime == BATTLE_TERRAIN_TIME_TWILIGHT && modern->paletteTwilight)
                palette = modern->paletteTwilight;
        }
    }

    DecompressDataWithHeaderVram(tileset, (void *)(BG_CHAR_ADDR(2)));
    DecompressDataWithHeaderVram(tilemap, (void *)(BG_SCREEN_ADDR(26)));
    LoadPalette(palette, BG_PLTT_ID(2), 3 * PLTT_SIZE_4BPP);
}

static void LoadBattleEnvironmentEntryGfx(u16 environment)
{
    const void *tileset, *tilemap;

    if (environment >= NELEMS(gBattleEnvironmentInfo))
        environment = BATTLE_ENVIRONMENT_PLAIN;

    tileset = gBattleEnvironmentInfo[environment].entry.tileset;
    tilemap = gBattleEnvironmentInfo[environment].entry.tilemap;

    if (UseModernBattleEnvironment())
    {
        const struct ModernBattleGfx *modern = &sModernBattleGfx[environment];
        if (modern->entry.tileset)
            tileset = modern->entry.tileset;
        if (modern->entry.tilemap)
            tilemap = modern->entry.tilemap;
    }

    DecompressDataWithHeaderVram(tileset, (void *)BG_CHAR_ADDR(1));
    DecompressDataWithHeaderVram(tilemap, (void *)BG_SCREEN_ADDR(28));
}

static u8 GetBattleEnvironmentOverride(void)
{
    u8 battleScene = GetCurrentMapBattleScene();

    if (TestRunner_Battle_GetForcedEnvironment()
     && gBattleEnvironmentInfo[gBattleEnvironment].background.tilemap
     && gBattleEnvironmentInfo[gBattleEnvironment].background.tileset)
    {
        return gBattleEnvironment;
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_FRONTIER | BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK | BATTLE_TYPE_EREADER_TRAINER))
        return BATTLE_ENVIRONMENT_FRONTIER;
    else if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
    {
        switch (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES))
        {
    #if !IS_HNS
        case SPECIES_GROUDON:
            return BATTLE_ENVIRONMENT_GROUDON;
        case SPECIES_KYOGRE:
            return BATTLE_ENVIRONMENT_KYOGRE;
        case SPECIES_RAYQUAZA:
            return BATTLE_ENVIRONMENT_RAYQUAZA;
    #endif
        default:
            return gBattleEnvironment;
        }
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        u32 trainerClass = GetTrainerClassFromId(TRAINER_BATTLE_PARAM.opponentA);
    #if IS_HNS
        // Clair's first battle and Blaine use the volcano cave background instead of the usual stadium.
        if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_CLAIR_1_HNS
         || TRAINER_BATTLE_PARAM.opponentA == TRAINER_BLAINE_HNS)
            return BATTLE_ENVIRONMENT_VOLCANO_CAVE;
    #endif
        if (trainerClass == TRAINER_CLASS_LEADER || trainerClass == TRAINER_CLASS_LEADER_FRLG || trainerClass == TRAINER_CLASS_LEADER_HNS || trainerClass == TRAINER_CLASS_LEADER_KANTO_HNS)
            return BATTLE_ENVIRONMENT_LEADER;
        else if (trainerClass == TRAINER_CLASS_CHAMPION || trainerClass == TRAINER_CLASS_CHAMPION_FRLG || trainerClass == TRAINER_CLASS_CHAMPION_HNS)
            return BATTLE_ENVIRONMENT_CHAMPION;
    }

    if (battleScene == MAP_BATTLE_SCENE_NORMAL)
        return gBattleEnvironment;

    return GetBattleEnvironmentByMapScene(battleScene);
}

// Used only to disable the panorama-splitting entrance on standard PRU
// battles. Preserve the original link, facility and partner transitions.
bool8 IsPruCrystalBattleBgActive(void)
{
    if (gBattleTypeFlags & (BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_MULTI))
        return FALSE;

    return GetPruRhythmBattleBgIndex(GetBattleEnvironmentOverride()) != 0xFF;
}

void BattleInitBgsAndWindows(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, gBattleBgTemplates, ARRAY_COUNT(gBattleBgTemplates));

    if (gBattleTypeFlags & BATTLE_TYPE_ARENA)
    {
        gBattleScripting.windowsType = B_WIN_TYPE_ARENA;
        SetBgTilemapBuffer(1, gBattleAnimBgTilemapBuffer);
        SetBgTilemapBuffer(2, gBattleAnimBgTilemapBuffer);
    }
    else if (IS_FRLG && (gBattleTypeFlags & (BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_CATCH_TUTORIAL)))
    {
        gBattleScripting.windowsType = B_WIN_TYPE_KANTO_TUTORIAL;
    }
    else
    {
        gBattleScripting.windowsType = B_WIN_TYPE_NORMAL;
    }

    InitWindows(gBattleWindowTemplates[gBattleScripting.windowsType]);
    DeactivateAllTextPrinters();
}

void InitBattleBgsVideo(void)
{
    DisableInterrupts(INTR_FLAG_HBLANK);
    EnableInterrupts(INTR_FLAG_VBLANK | INTR_FLAG_VCOUNT | INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
    BattleInitBgsAndWindows();
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON | DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
}

void LoadBattleMenuWindowGfx(void)
{
    LoadUserWindowBorderGfx(2, 0x12, BG_PLTT_ID(1));
    LoadUserWindowBorderGfx(2, 0x22, BG_PLTT_ID(1));
    LoadPalette(gBattleWindowTextPalette, BG_PLTT_ID(5), PLTT_SIZE_4BPP);

    if ((gBattleTypeFlags & (BATTLE_TYPE_ARENA | BATTLE_TYPE_POKEDUDE))
    || (IS_FRLG && (gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE)))
    {
        // Load graphics for the Battle Arena referee's mid-battle messages.
        Menu_LoadStdPalAt(BG_PLTT_ID(7));
        LoadMessageBoxGfx(0, 0x30, BG_PLTT_ID(7));
        gPlttBufferUnfaded[BG_PLTT_ID(7) + 6] = 0;
        CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(7) + 6], &gPlttBufferFaded[BG_PLTT_ID(7) + 6], PLTT_SIZEOF(1));
    }
}

void DrawMainBattleBackground(void)
{
    LoadBattleEnvironmentGfx(GetBattleEnvironmentOverride());
}

void LoadBattleTextboxAndBackground(void)
{
    DecompressDataWithHeaderVram(gBattleTextboxTiles, (void *)(BG_CHAR_ADDR(0)));
    CopyToBgTilemapBuffer(0, gBattleTextboxTilemap, 0, 0);
    CopyBgTilemapBufferToVram(0);
    LoadPalette(gBattleTextboxPalette, BG_PLTT_ID(0), 2 * PLTT_SIZE_4BPP);
    LoadBattleMenuWindowGfx();
    if (B_TERRAIN_BG_CHANGE == TRUE)
        DrawTerrainTypeBattleBackground();
    else
        DrawMainBattleBackground();
}

static void DrawLinkBattleParticipantPokeballs(u8 taskId, u8 multiplayerId, u8 bgId, u8 destX, u8 destY)
{
    s32 i;
    u16 pokeballStatuses = 0;
    u16 tiles[6];

    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if (gTasks[taskId].data[5] != 0)
        {
            switch (multiplayerId)
            {
            case 0:
                pokeballStatuses = 0x3F & gTasks[taskId].data[3];
                break;
            case 1:
                pokeballStatuses = (0xFC0 & gTasks[taskId].data[4]) >> 6;
                break;
            case 2:
                pokeballStatuses = (0xFC0 & gTasks[taskId].data[3]) >> 6;
                break;
            case 3:
                pokeballStatuses = 0x3F & gTasks[taskId].data[4];
                break;
            }
        }
        else
        {
            switch (multiplayerId)
            {
            case 0:
                pokeballStatuses = 0x3F & gTasks[taskId].data[3];
                break;
            case 1:
                pokeballStatuses = 0x3F & gTasks[taskId].data[4];
                break;
            case 2:
                pokeballStatuses = (0xFC0 & gTasks[taskId].data[3]) >> 6;
                break;
            case 3:
                pokeballStatuses = (0xFC0 & gTasks[taskId].data[4]) >> 6;
                break;
            }
        }

        for (i = 0; i < 3; i++)
            tiles[i] = ((pokeballStatuses & (3 << (i * 2))) >> (i * 2)) + 0x6001;

        CopyToBgTilemapBufferRect_ChangePalette(bgId, tiles, destX, destY, 3, 1, 0x11);
        CopyBgTilemapBufferToVram(bgId);
    }
    else
    {
        if (multiplayerId == gBattleScripting.multiplayerId)
            pokeballStatuses = gTasks[taskId].data[3];
        else
            pokeballStatuses = gTasks[taskId].data[4];

        for (i = 0; i < 6; i++)
            tiles[i] = ((pokeballStatuses & (3 << (i * 2))) >> (i * 2)) + 0x6001;

        CopyToBgTilemapBufferRect_ChangePalette(bgId, tiles, destX, destY, 6, 1, 0x11);
        CopyBgTilemapBufferToVram(bgId);
    }
}

static void DrawLinkBattleVsScreenOutcomeText(void)
{
    if (gBattleOutcome == B_OUTCOME_DREW)
    {
        BattlePutTextOnWindow(gText_Draw, B_WIN_VS_OUTCOME_DRAW);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if (gBattleOutcome == B_OUTCOME_WON)
        {
            switch (gLinkPlayers[gBattleScripting.multiplayerId].id)
            {
            case 0:
                BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_LEFT);
                BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_RIGHT);
                break;
            case 1:
                BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_RIGHT);
                BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_LEFT);
                break;
            case 2:
                BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_LEFT);
                BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_RIGHT);
                break;
            case 3:
                BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_RIGHT);
                BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_LEFT);
                break;
            }
        }
        else
        {
            switch (gLinkPlayers[gBattleScripting.multiplayerId].id)
            {
            case 0:
                BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_RIGHT);
                BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_LEFT);
                break;
            case 1:
                BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_LEFT);
                BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_RIGHT);
                break;
            case 2:
                BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_RIGHT);
                BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_LEFT);
                break;
            case 3:
                BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_LEFT);
                BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_RIGHT);
                break;
            }
        }
    }
    else if (gBattleOutcome == B_OUTCOME_WON)
    {
        if (gLinkPlayers[gBattleScripting.multiplayerId].id != 0)
        {
            BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_RIGHT);
            BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_LEFT);
        }
        else
        {
            BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_LEFT);
            BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_RIGHT);
        }
    }
    else
    {
        if (gLinkPlayers[gBattleScripting.multiplayerId].id != 0)
        {
            BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_LEFT);
            BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_RIGHT);
        }
        else
        {
            BattlePutTextOnWindow(gText_Win, B_WIN_VS_OUTCOME_RIGHT);
            BattlePutTextOnWindow(gText_Loss, B_WIN_VS_OUTCOME_LEFT);
        }
    }
}

void InitLinkBattleVsScreen(u8 taskId)
{
    struct LinkPlayer *linkPlayer;
    u8 *name;
    s32 i, palId;

    switch (gTasks[taskId].data[0])
    {
    case 0:
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        {
            for (i = 0; i < MAX_LINK_PLAYERS; i++)
            {
                name = gLinkPlayers[i].name;
                linkPlayer = &gLinkPlayers[i];

                switch (linkPlayer->id)
                {
                case 0:
                    BattlePutTextOnWindow(name, B_WIN_VS_MULTI_PLAYER_1);
                    DrawLinkBattleParticipantPokeballs(taskId, linkPlayer->id, 1, 2, 4);
                    break;
                case 1:
                    BattlePutTextOnWindow(name, B_WIN_VS_MULTI_PLAYER_2);
                    DrawLinkBattleParticipantPokeballs(taskId, linkPlayer->id, 2, 2, 4);
                    break;
                case 2:
                    BattlePutTextOnWindow(name, B_WIN_VS_MULTI_PLAYER_3);
                    DrawLinkBattleParticipantPokeballs(taskId, linkPlayer->id, 1, 2, 8);
                    break;
                case 3:
                    BattlePutTextOnWindow(name, B_WIN_VS_MULTI_PLAYER_4);
                    DrawLinkBattleParticipantPokeballs(taskId, linkPlayer->id, 2, 2, 8);
                    break;
                }
            }
        }
        else
        {
            u8 playerId = gBattleScripting.multiplayerId;
            u8 opponentId = playerId ^ BIT_SIDE;
            u8 opponentId_copy = opponentId;

            if (gLinkPlayers[playerId].id != 0)
                opponentId = playerId, playerId = opponentId_copy;

            name = gLinkPlayers[playerId].name;
            BattlePutTextOnWindow(name, B_WIN_VS_PLAYER);

            name = gLinkPlayers[opponentId].name;
            BattlePutTextOnWindow(name, B_WIN_VS_OPPONENT);

            DrawLinkBattleParticipantPokeballs(taskId, playerId, 1, 2, 7);
            DrawLinkBattleParticipantPokeballs(taskId, opponentId, 2, 2, 7);
        }
        gTasks[taskId].data[0]++;
        break;
    case 1:
        palId = AllocSpritePalette(TAG_VS_LETTERS);
        gPlttBufferUnfaded[OBJ_PLTT_ID(palId) + 15] = gPlttBufferFaded[OBJ_PLTT_ID(palId) + 15] = RGB_WHITE;
        gBattleStruct->linkBattleVsSpriteId_V = CreateSprite(&sVsLetter_V_SpriteTemplate, 111, 80, 0);
        gBattleStruct->linkBattleVsSpriteId_S = CreateSprite(&sVsLetter_S_SpriteTemplate, 129, 80, 0);
        gSprites[gBattleStruct->linkBattleVsSpriteId_V].invisible = TRUE;
        gSprites[gBattleStruct->linkBattleVsSpriteId_S].invisible = TRUE;
        gTasks[taskId].data[0]++;
        break;
    case 2:
        if (gTasks[taskId].data[5] != 0)
        {
            gBattle_BG1_X = -(20) - (Sin2(gTasks[taskId].data[1]) / 32);
            gBattle_BG2_X = -(140) - (Sin2(gTasks[taskId].data[2]) / 32);
            gBattle_BG1_Y = -36;
            gBattle_BG2_Y = -36;
        }
        else
        {
            gBattle_BG1_X = -(20) - (Sin2(gTasks[taskId].data[1]) / 32);
            gBattle_BG1_Y = (Cos2(gTasks[taskId].data[1]) / 32) - 164;
            gBattle_BG2_X = -(140) - (Sin2(gTasks[taskId].data[2]) / 32);
            gBattle_BG2_Y = (Cos2(gTasks[taskId].data[2]) / 32) - 164;
        }

        if (gTasks[taskId].data[2] != 0)
        {
            gTasks[taskId].data[2] -= 2;
            gTasks[taskId].data[1] += 2;
        }
        else
        {
            if (gTasks[taskId].data[5] != 0)
                DrawLinkBattleVsScreenOutcomeText();

            PlaySE(SE_M_HARDEN);
            DestroyTask(taskId);
            gSprites[gBattleStruct->linkBattleVsSpriteId_V].invisible = FALSE;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].invisible = FALSE;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].oam.tileNum += 0x40;
            gSprites[gBattleStruct->linkBattleVsSpriteId_V].data[0] = 0;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].data[0] = 1;
            gSprites[gBattleStruct->linkBattleVsSpriteId_V].data[1] = gSprites[gBattleStruct->linkBattleVsSpriteId_V].x;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].data[1] = gSprites[gBattleStruct->linkBattleVsSpriteId_S].x;
            gSprites[gBattleStruct->linkBattleVsSpriteId_V].data[2] = 0;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].data[2] = 0;
        }
        break;
    }
}

void DrawBattleEntryBackground(void)
{
    // The complete Rhythm BG3 scene is already visible. Do not load
    // any extra entry tiles, grass, water, rocks or other foreground overlay.
    if (IsPruCrystalBattleBgActive())
        return;

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        DecompressDataWithHeaderVram(gBattleVSFrame_Gfx, (void *)(BG_CHAR_ADDR(1)));
        DecompressDataWithHeaderVram(gVsLettersGfx, (void *)OBJ_VRAM0);
        LoadPalette(gBattleVSFrame_Pal, BG_PLTT_ID(6), PLTT_SIZE_4BPP);
        SetBgAttribute(1, BG_ATTR_SCREENSIZE, 1);
        SetGpuReg(REG_OFFSET_BG1CNT, 0x5C04);
        CopyToBgTilemapBuffer(1, gBattleVSFrame_Tilemap, 0, 0);
        CopyToBgTilemapBuffer(2, gBattleVSFrame_Tilemap, 0, 0);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG1 | WININ_WIN0_BG2 | WININ_WIN0_OBJ | WININ_WIN0_CLR);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        gBattle_BG1_Y = 0xFF5C;
        gBattle_BG2_Y = 0xFF5C;
        LoadCompressedSpriteSheetUsingHeap(&sVsLettersSpriteSheet);
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_FRONTIER | BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK | BATTLE_TYPE_EREADER_TRAINER))
    {
        if (TestRunner_Battle_GetForcedEnvironment()
         && gBattleEnvironmentInfo[gBattleEnvironment].background.tilemap
         && gBattleEnvironmentInfo[gBattleEnvironment].background.tileset)
        {
            LoadBattleEnvironmentEntryGfx(gBattleEnvironment);
        }
        else if (!(gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER) || gPartnerTrainerId > TRAINER_PARTNER(PARTNER_NONE))
        {
            LoadBattleEnvironmentEntryGfx(BATTLE_ENVIRONMENT_BUILDING);
        }
        else
        {
            // Set up bg for the multi battle intro where both teams slide in facing the screen.
            // Note Steven's multi battle (which has a dedicated back pic) is excluded above.
            SetBgAttribute(1, BG_ATTR_CHARBASEINDEX, 2);
            SetBgAttribute(2, BG_ATTR_CHARBASEINDEX, 2);
            CopyToBgTilemapBuffer(1, gMultiBattleIntroBg_Opponent_Tilemap, 0, 0);
            CopyToBgTilemapBuffer(2, gMultiBattleIntroBg_Player_Tilemap, 0, 0);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(2);
        }
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
    {
        LoadBattleEnvironmentEntryGfx(GetBattleEnvironmentOverride());
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            enum TrainerClassID trainerClass = GetTrainerClassFromId(TRAINER_BATTLE_PARAM.opponentA);
            if (trainerClass == TRAINER_CLASS_LEADER || trainerClass == TRAINER_CLASS_CHAMPION)
            {
                LoadBattleEnvironmentEntryGfx(GetBattleEnvironmentOverride());
                return;
            }
        }

        LoadBattleEnvironmentEntryGfx(gBattleEnvironment);
    }
}

bool8 LoadChosenBattleElement(u8 caseId)
{
    bool8 ret = FALSE;

    switch (caseId)
    {
    case 0:
        DecompressDataWithHeaderVram(gBattleTextboxTiles, (void *)(BG_CHAR_ADDR(0)));
        break;
    case 1:
        CopyToBgTilemapBuffer(0, gBattleTextboxTilemap, 0, 0);
        CopyBgTilemapBufferToVram(0);
        break;
    case 2:
        LoadPalette(gBattleTextboxPalette, BG_PLTT_ID(0), 2 * PLTT_SIZE_4BPP);
        break;
    case 3:
        {
            u8 pruBg = GetPruRhythmBattleBgIndex(GetBattleEnvironmentOverride());
            if (pruBg >= 55 && pruBg < 67)
                DecompressDataWithHeaderVram(sPruOriginalTestBattleBgs[pruBg - 55].tiles, (void *)BG_CHAR_ADDR(2));
            else if (pruBg != 0xFF && pruBg < 55)
                DecompressDataWithHeaderVram(sPruRhythmBattleBgs[pruBg].tiles, (void *)BG_CHAR_ADDR(2));
            else
                DecompressDataWithHeaderVram(gBattleEnvironmentInfo[GetBattleEnvironmentOverride()].background.tileset, (void *)(BG_CHAR_ADDR(2)));
        }
        break;
    case 4:
        {
            u8 pruBg = GetPruRhythmBattleBgIndex(GetBattleEnvironmentOverride());
            if (pruBg >= 55 && pruBg < 67)
                DecompressDataWithHeaderVram(sPruOriginalTestBattleBgs[pruBg - 55].tilemap, (void *)BG_SCREEN_ADDR(26));
            else if (pruBg != 0xFF && pruBg < 55)
                DecompressDataWithHeaderVram(sPruRhythmBattleBgs[pruBg].tilemap, (void *)BG_SCREEN_ADDR(26));
            else
                DecompressDataWithHeaderVram(gBattleEnvironmentInfo[GetBattleEnvironmentOverride()].background.tilemap, (void *)(BG_SCREEN_ADDR(26)));
        }
        break;
    case 5:
        {
            u8 pruBg = GetPruRhythmBattleBgIndex(GetBattleEnvironmentOverride());
            if (pruBg >= 55 && pruBg < 67)
                LoadPalette(sPruOriginalTestBattleBgs[pruBg - 55].palette, BG_PLTT_ID(12), 3 * PLTT_SIZE_4BPP);
            else if (pruBg != 0xFF && pruBg < 55)
                LoadPalette(sPruRhythmBattleBgs[pruBg].palette, BG_PLTT_ID(12), 3 * PLTT_SIZE_4BPP);
            else
                LoadPalette(gBattleEnvironmentInfo[GetBattleEnvironmentOverride()].palette, BG_PLTT_ID(2), 3 * PLTT_SIZE_4BPP);
        }
        break;
    case 6:
        LoadBattleMenuWindowGfx();
        break;
    default:
        ret = TRUE;
        break;
    }

    return ret;
}

void DrawTerrainTypeBattleBackground(void)
{
    switch (gFieldStatuses & STATUS_FIELD_TERRAIN_ANY)
    {
    case STATUS_FIELD_GRASSY_TERRAIN:
        LoadMoveBg(BG_GRASSY_TERRAIN);
        break;
    case STATUS_FIELD_MISTY_TERRAIN:
        LoadMoveBg(BG_MISTY_TERRAIN);
        break;
    case STATUS_FIELD_ELECTRIC_TERRAIN:
        LoadMoveBg(BG_ELECTRIC_TERRAIN);
        break;
    case STATUS_FIELD_PSYCHIC_TERRAIN:
        LoadMoveBg(BG_PSYCHIC_TERRAIN);
        break;
    default:
        DrawMainBattleBackground();
        break;
    }
}

