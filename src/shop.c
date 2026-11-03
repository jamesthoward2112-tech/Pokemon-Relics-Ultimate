#include "global.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "decoration.h"
#include "decoration_inventory.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "item_icon.h"
#include "item_menu.h"
#include "list_menu.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "money.h"
#include "move.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "scanline_effect.h"
#include "script.h"
#include "shop.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "text_window.h"
#include "tv.h"
#include "constants/decorations.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/metatile_behaviors.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "data/battle_frontier/battle_frontier_exchange_corner.h"
#if IS_HNS
#include "constants/flags.h"
#include "constants/maps.h"
#include "event_data.h"
#endif

#define TAG_SCROLL_ARROW   2100
#define TAG_ITEM_ICON_BASE 9110 // immune to time blending
#define TAG_BERRY_ICON     9150
#define TAG_QUANTITY_BERRY 9151

#define MAX_ITEMS_SHOWN 8
#define SHOP_MENU_PALETTE_ID (gMapHeader.mapLayout->layoutVersion == LAYOUT_VERSION_HNS ? 6 : gMapHeader.mapLayout->layoutVersion == LAYOUT_VERSION_FRLG ? 11 : 12)

enum {
    WIN_BUY_SELL_QUIT,
    WIN_BUY_QUIT,
};

enum {
    WIN_MONEY,
    WIN_ITEM_LIST,
    WIN_ITEM_DESCRIPTION,
    WIN_QUANTITY_IN_BAG,
    WIN_QUANTITY_PRICE,
    WIN_MESSAGE,
    WIN_BERRIES,
};

enum {
    COLORID_NORMAL,      // Item descriptions, quantity in bag, and quantity/price
    COLORID_ITEM_LIST,   // The text in the item list, and the cursor normally
    COLORID_GRAY_CURSOR, // When the cursor has selected an item to purchase
};

enum {
    MART_TYPE_NORMAL,
    MART_TYPE_DECOR,
    MART_TYPE_DECOR2,
    MART_TYPE_KURT,
    MART_TYPE_BP,
    MART_TYPE_BP_ITEM,
    MART_TYPE_BP_DECOR,
};

// shop view window NPC info enum
enum
{
    OBJ_EVENT_ID,
    X_COORD,
    Y_COORD,
    ANIM_NUM,
    LAYER_TYPE
};

struct MartInfo
{
    void (*callback)(void);
    const struct MenuAction *menuActions;
    const u16 *itemList;
    u16 itemCount;
    u8 windowId;
    u8 martType;
};

struct ShopData
{
    u16 tilemapBuffers[4][0x400];
    u32 totalCost;
    u16 itemsShowed;
    u16 selectedRow;
    u16 scrollOffset;
    u16 maxQuantity;
    u8 scrollIndicatorsTaskId;
    u8 iconSlot;
    u8 itemSpriteIds[2];
    s16 viewportObjects[OBJECT_EVENTS_COUNT][5];
};

struct KurtBallMapping
{
    u16 berry;
    u16 ball;
};

static const struct KurtBallMapping sKurtBallMappings[] =
{
    {ITEM_PECHA_BERRY,  ITEM_LOVE_BALL},
    {ITEM_RAWST_BERRY,  ITEM_LURE_BALL},
    {ITEM_CHERI_BERRY,  ITEM_FRIEND_BALL},
    {ITEM_ORAN_BERRY,   ITEM_HEAVY_BALL},
    {ITEM_CHESTO_BERRY, ITEM_MOON_BALL},
    {ITEM_ASPEAR_BERRY, ITEM_FAST_BALL},
    {ITEM_PERSIM_BERRY, ITEM_LEVEL_BALL},
};

static EWRAM_DATA struct MartInfo sMartInfo = {0};
static EWRAM_DATA struct ShopData *sShopData = NULL;
static EWRAM_DATA struct ListMenuItem *sListMenuItems = NULL;
static EWRAM_DATA u8 (*sItemNames)[ITEM_NAME_LENGTH + 2] = {0};
static EWRAM_DATA u8 sPurchaseHistoryId = 0;
static EWRAM_DATA u16 sKurtCurrentBerry = ITEM_NONE;
static EWRAM_DATA u8 sBerryIconSpriteId = 0;
static EWRAM_DATA u8 sQuantityBerryIconSpriteId = 0;
static EWRAM_DATA const struct BPShopEntry *sBPShopEntries = NULL;
EWRAM_DATA struct ItemSlot gMartPurchaseHistory[SMARTSHOPPER_NUM_ITEMS] = {0};

static void Task_ShopMenu(u8 taskId);
static void Task_HandleShopMenuQuit(u8 taskId);
static void CB2_InitBuyMenu(void);
static void Task_GoToBuyOrSellMenu(u8 taskId);
static void MapPostLoadHook_ReturnToShopMenu(void);
static void Task_ReturnToShopMenu(u8 taskId);
static void ShowShopMenuAfterExitingBuyOrSellMenu(u8 taskId);
static void BuyMenuDrawGraphics(void);
static void BuyMenuAddScrollIndicatorArrows(void);
static void Task_BuyMenu(u8 taskId);
static void BuyMenuBuildListMenuTemplate(void);
static void BuyMenuInitBgs(void);
static void BuyMenuInitWindows(void);
static void BuyMenuDecompressBgGraphics(void);
static void BuyMenuSetListEntry(struct ListMenuItem *, enum Item, u8 *);
static void BuyMenuAddItemIcon(enum Item, u8);
static void BuyMenuRemoveItemIcon(enum Item, u8);
static void BuyMenuPrint(u8 windowId, const u8 *text, u8 x, u8 y, s8 speed, u8 colorSet);
static void BuyMenuDrawMapGraphics(void);
static void BuyMenuCopyMenuBgToBg1TilemapBuffer(void);
static void BuyMenuCollectObjectEventData(void);
static void BuyMenuDrawObjectEvents(void);
static void BuyMenuDrawMapBg(void);
static bool8 BuyMenuCheckForOverlapWithMenuBg(int, int);
static void BuyMenuDrawMapMetatile(s16, s16, const u16 *, u8);
static void BuyMenuDrawMapMetatileLayer(u16 *dest, s16 offset1, s16 offset2, const u16 *src);
static bool8 BuyMenuCheckIfObjectEventOverlapsMenuBg(s16 *);
static void ExitBuyMenu(u8 taskId);
static void Task_ExitBuyMenu(u8 taskId);
static void BuyMenuTryMakePurchase(u8 taskId);
static void BuyMenuReturnToItemList(u8 taskId);
static void Task_BuyHowManyDialogueInit(u8 taskId);
static void BuyMenuConfirmPurchase(u8 taskId);
static void BuyMenuPrintItemQuantityAndPrice(u8 taskId);
static void Task_BuyHowManyDialogueHandleInput(u8 taskId);
static void BuyMenuSubtractMoney(u8 taskId);
static void RecordItemPurchase(u8 taskId);
static void Task_ReturnToItemListAfterItemPurchase(u8 taskId);
static void Task_ReturnToItemListAfterDecorationPurchase(u8 taskId);
static void Task_ExitKurtShopAfterPurchase(u8 taskId);
static void Task_HandleShopMenuBuy(u8 taskId);
static void Task_HandleShopMenuSell(u8 taskId);
static void BuyMenuPrintItemDescriptionAndShowItemIcon(s32 item, bool8 onInit, struct ListMenu *list);
static void BuyMenuPrintPriceInList(u8 windowId, u32 itemId, u8 y);

static u16 GetBerryFromBall(u16 ballItem)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sKurtBallMappings); i++)
    {
        if (sKurtBallMappings[i].ball == ballItem)
            return sKurtBallMappings[i].berry;
    }
    return ITEM_NONE;
}

static const struct OamData sOamData_QuantityBerryIcon =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 2,
    .affineParam = 0
};

static const union AnimCmd sSpriteAnim_QuantityBerryIcon[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_QuantityBerryIcon[] =
{
    sSpriteAnim_QuantityBerryIcon
};

static const struct SpriteTemplate sSpriteTemplate_QuantityBerryIcon =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &sOamData_QuantityBerryIcon,
    .anims = sSpriteAnimTable_QuantityBerryIcon,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static void AddBerryIcon(u16 berryItem)
{
    u8 spriteId;

    if (sBerryIconSpriteId != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_BERRY_ICON);
        FreeSpritePaletteByTag(TAG_BERRY_ICON);
        DestroySprite(&gSprites[sBerryIconSpriteId]);
        sBerryIconSpriteId = SPRITE_NONE;
    }

    if (berryItem == ITEM_NONE)
        return;

    spriteId = AddItemIconSprite(TAG_BERRY_ICON, TAG_BERRY_ICON, berryItem);
    if (spriteId != MAX_SPRITES)
    {
        sBerryIconSpriteId = spriteId;
        gSprites[spriteId].x = 22;
        gSprites[spriteId].y = 24;
        gSprites[spriteId].oam.priority = 0;
    }
}

static void RemoveBerryIcon(void)
{
    if (sBerryIconSpriteId != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_BERRY_ICON);
        FreeSpritePaletteByTag(TAG_BERRY_ICON);
        DestroySprite(&gSprites[sBerryIconSpriteId]);
        sBerryIconSpriteId = SPRITE_NONE;
    }
}

static void AddQuantityBerryIcon(u16 berryItem)
{
    u8 spriteId;

    if (sQuantityBerryIconSpriteId != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_QUANTITY_BERRY);
        FreeSpritePaletteByTag(TAG_QUANTITY_BERRY);
        DestroySprite(&gSprites[sQuantityBerryIconSpriteId]);
        sQuantityBerryIconSpriteId = SPRITE_NONE;
    }

    if (berryItem == ITEM_NONE)
        return;

    spriteId = AddCustomItemIconSprite(&sSpriteTemplate_QuantityBerryIcon, TAG_QUANTITY_BERRY, TAG_QUANTITY_BERRY, berryItem);
    if (spriteId != MAX_SPRITES)
    {
        sQuantityBerryIconSpriteId = spriteId;
        gSprites[spriteId].x = 219;
        gSprites[spriteId].y = 99;
        gSprites[spriteId].oam.priority = 0;
        SetOamMatrixRotationScaling(gSprites[spriteId].oam.matrixNum, 192, 192, 0);
    }
}

static void RemoveQuantityBerryIcon(void)
{
    if (sQuantityBerryIconSpriteId != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_QUANTITY_BERRY);
        FreeSpritePaletteByTag(TAG_QUANTITY_BERRY);
        DestroySprite(&gSprites[sQuantityBerryIconSpriteId]);
        sQuantityBerryIconSpriteId = SPRITE_NONE;
    }
}

static void PrintBerryCount(u8 windowId, u16 berryItem)
{
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));

    if (berryItem == ITEM_NONE)
    {
        RemoveBerryIcon();
        return;
    }

    AddBerryIcon(berryItem);
    ConvertIntToDecimalStringN(gStringVar1, CountTotalItemQuantityInBag(berryItem), STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, gText_InBagVar1);
    AddTextPrinterParameterized(windowId, FONT_NORMAL, gStringVar4, 23, 5, 0, NULL);
}

static u16 GetBPCostForItem(u16 itemId)
{
    u16 i = 0;
    if (sBPShopEntries == NULL)
        return 0;
    while (sBPShopEntries[i].item != ITEM_NONE)
    {
        if (sBPShopEntries[i].item == itemId)
            return sBPShopEntries[i].bpCost;
        i++;
    }
    return 0;
}

static void PrintBPAmountInMoneyBox(u8 windowId, u32 bp, u8 speed)
{
    u8 *ptr = ConvertIntToDecimalStringN(gStringVar1, bp, STR_CONV_MODE_RIGHT_ALIGN, 4);
    u8 x;
    StringCopy(ptr, gText_BP);
    x = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar1, 80);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    AddTextPrinterParameterized(windowId, FONT_NORMAL, gStringVar1, x, 1, speed, NULL);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

#if IS_HNS
static u8 GetNumberOfBadges(void);

static const u16 sShopInventory_ZeroBadges[] = {
    ITEM_POKE_BALL,
    ITEM_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_OneBadge[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_TwoBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_ThreeBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_FourBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_FiveBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_SixBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_SevenBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_EightBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_FULL_RESTORE,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 *const sShopInventories[] =
{
    sShopInventory_ZeroBadges,
    sShopInventory_OneBadge,
    sShopInventory_TwoBadges,
    sShopInventory_ThreeBadges,
    sShopInventory_FourBadges,
    sShopInventory_FiveBadges,
    sShopInventory_SixBadges,
    sShopInventory_SevenBadges,
    sShopInventory_EightBadges
};

static const u16 sShopInventory_ZeroBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_POTION,
    ITEM_ETHER,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_OneBadge_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ETHER,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_TwoBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ETHER,
    ITEM_ELIXIR,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_ThreeBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ETHER,
    ITEM_ELIXIR,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_FourBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ETHER,
    ITEM_ELIXIR,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_FiveBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_ETHER,
    ITEM_MAX_ETHER,
    ITEM_ELIXIR,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_SixBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_ETHER,
    ITEM_MAX_ETHER,
    ITEM_ELIXIR,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_SevenBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_ETHER,
    ITEM_MAX_ETHER,
    ITEM_ELIXIR,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_EightBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_FULL_RESTORE,
    ITEM_ETHER,
    ITEM_MAX_ETHER,
    ITEM_ELIXIR,
    ITEM_MAX_ELIXIR,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_FLUFFY_TAIL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 *const sShopInventories_PC[] =
{
    sShopInventory_ZeroBadges_PC,
    sShopInventory_OneBadge_PC,
    sShopInventory_TwoBadges_PC,
    sShopInventory_ThreeBadges_PC,
    sShopInventory_FourBadges_PC,
    sShopInventory_FiveBadges_PC,
    sShopInventory_SixBadges_PC,
    sShopInventory_SevenBadges_PC,
    sShopInventory_EightBadges_PC
};
#endif // IS_HNS

static const struct YesNoFuncTable sShopPurchaseYesNoFuncs =
{
    BuyMenuTryMakePurchase,
    BuyMenuReturnToItemList
};

static const struct MenuAction sShopMenuActions_BuySellQuit[] =
{
    { gText_ShopBuy, {.void_u8=Task_HandleShopMenuBuy} },
    { gText_ShopSell, {.void_u8=Task_HandleShopMenuSell} },
    { gText_ShopQuit, {.void_u8=Task_HandleShopMenuQuit} }
};

static const struct MenuAction sShopMenuActions_BuyQuit[] =
{
    { gText_ShopBuy, {.void_u8=Task_HandleShopMenuBuy} },
    { gText_ShopQuit, {.void_u8=Task_HandleShopMenuQuit} }
};

static const struct WindowTemplate sShopMenuWindowTemplates[] =
{
    [WIN_BUY_SELL_QUIT] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 9,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x0008,
    },
    // Separate shop menu window for decorations, which can't be sold
    [WIN_BUY_QUIT] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 9,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x0008,
    }
};

static const struct ListMenuTemplate sShopBuyMenuListTemplate =
{
    .items = NULL,
    .moveCursorFunc = BuyMenuPrintItemDescriptionAndShowItemIcon,
    .itemPrintFunc = BuyMenuPrintPriceInList,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = WIN_ITEM_LIST,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NARROW,
    .cursorKind = CURSOR_BLACK_ARROW,
    .textNarrowWidth = 84,
};

static const struct BgTemplate sShopBuyMenuBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    }
};

static const struct WindowTemplate sShopBuyMenuWindowTemplates[] =
{
    [WIN_MONEY] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x001E,
    },
    [WIN_ITEM_LIST] = {
        .bg = 0,
        .tilemapLeft = 14,
        .tilemapTop = 2,
        .width = 15,
        .height = 16,
        .paletteNum = 15,
        .baseBlock = 0x0032,
    },
    [WIN_ITEM_DESCRIPTION] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 13,
        .width = 14,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x0122,
    },
    [WIN_QUANTITY_IN_BAG] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 11,
        .width = 12,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x0176,
    },
    [WIN_QUANTITY_PRICE] = {
        .bg = 0,
        .tilemapLeft = 18,
        .tilemapTop = 11,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x018E,
    },
    [WIN_MESSAGE] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x01A2,
    },
    [WIN_BERRIES] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 3,
        .paletteNum = 15,
        .baseBlock = 0x0222,
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sShopBuyMenuYesNoWindowTemplates =
{
    .bg = 0,
    .tilemapLeft = 21,
    .tilemapTop = 9,
    .width = 5,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 0x020E,
};

static const u8 sShopBuyMenuTextColors[][3] =
{
    [COLORID_NORMAL]      = {1, 2, 3},
    [COLORID_ITEM_LIST]   = {0, 2, 3},
    [COLORID_GRAY_CURSOR] = {0, 3, 2},
};

static u8 CreateShopMenu(u8 martType)
{
    int numMenuItems;

    LockPlayerFieldControls();
    sMartInfo.martType = martType;

    if (martType == MART_TYPE_NORMAL)
    {
        struct WindowTemplate winTemplate = sShopMenuWindowTemplates[WIN_BUY_SELL_QUIT];
        winTemplate.width = GetMaxWidthInMenuTable(sShopMenuActions_BuySellQuit, ARRAY_COUNT(sShopMenuActions_BuySellQuit));
        sMartInfo.windowId = AddWindow(&winTemplate);
        sMartInfo.menuActions = sShopMenuActions_BuySellQuit;
        numMenuItems = ARRAY_COUNT(sShopMenuActions_BuySellQuit);
    }
    else
    {
        struct WindowTemplate winTemplate = sShopMenuWindowTemplates[WIN_BUY_QUIT];
        winTemplate.width = GetMaxWidthInMenuTable(sShopMenuActions_BuyQuit, ARRAY_COUNT(sShopMenuActions_BuyQuit));
        sMartInfo.windowId = AddWindow(&winTemplate);
        sMartInfo.menuActions = sShopMenuActions_BuyQuit;
        numMenuItems = ARRAY_COUNT(sShopMenuActions_BuyQuit);
    }

    SetStandardWindowBorderStyle(sMartInfo.windowId, FALSE);
    PrintMenuTable(sMartInfo.windowId, numMenuItems, sMartInfo.menuActions);
    InitMenuInUpperLeftCornerNormal(sMartInfo.windowId, numMenuItems, 0);
    PutWindowTilemap(sMartInfo.windowId);
    CopyWindowToVram(sMartInfo.windowId, COPYWIN_MAP);

    return CreateTask(Task_ShopMenu, 8);
}

static void SetShopMenuCallback(void (*callback)(void))
{
    sMartInfo.callback = callback;
}

#if IS_HNS
static u8 GetNumberOfBadges(void)
{
    u16 badgeFlag;
    u8 count = 0;

    for (badgeFlag = FLAG_BADGE01_GET; badgeFlag < FLAG_BADGE01_GET + NUM_BADGES; badgeFlag++)
    {
        if (FlagGet(badgeFlag))
            count++;
    }

    return count;
}
#endif

static void SetShopItemsForSale(const u16 *items)
{
    u16 i = 0;

#if IS_HNS
    if (items == NULL)
    {
        u8 badgeCount = GetNumberOfBadges();
        if (badgeCount >= ARRAY_COUNT(sShopInventories))
            badgeCount = ARRAY_COUNT(sShopInventories) - 1;
        if (!gSaveBlock3Ptr->challengeSettings.tx_Challenges_PkmnCenter)
            sMartInfo.itemList = sShopInventories[badgeCount];
        else
            sMartInfo.itemList = sShopInventories_PC[badgeCount];
    }
    else
#endif
    {
        sMartInfo.itemList = items;
    }

    sMartInfo.itemCount = 0;

    while (sMartInfo.itemList[i])
    {
        sMartInfo.itemCount++;
        i++;
    }
}

static void Task_ShopMenu(u8 taskId)
{
    s8 inputCode = Menu_ProcessInputNoWrap();
    switch (inputCode)
    {
    case MENU_NOTHING_CHOSEN:
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        Task_HandleShopMenuQuit(taskId);
        break;
    default:
        sMartInfo.menuActions[inputCode].func.void_u8(taskId);
        break;
    }
}

#defmzÛÛh‘éì¶»§q«^wF÷FÄ—FV×2âÔ…ô•DTÕ5õ4„õtâ¢t×VÇF—W6TÆ—7DÖVçUFV×ÆFRæÖ…6†÷vVBÒÔ…ô•DTÕ5õ4„õtã°¢VÇ6P¢t×VÇF—W6TÆ—7DÖVçUFV×ÆFRæÖ…6†÷vVBÒt×VÇF—W6TÆ—7DÖVçUFV×ÆFRçF÷FÄ—FV×3° ¢56†÷FFÓæ—FV×56†÷vVBÒt×VÇF—W6TÆ—7DÖVçUFV×ÆFRæÖ…6†÷vVC°§Ð §7FF–2fö–B'W”ÖVçU6WDÆ—7DVçG'’‡7G'V7BÆ—7DÖVçT—FVÒ¦ÖVçT—FVÒÂVçVÒ—FVÒ—FVÒÂS‚¦æÖR§°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uôäõ$ÔÀ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%@¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô% ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÒ¢6÷”—FVÔæÖR†—FVÒÂæÖR“°¢VÇ6P¢7G&–æt6÷’†æÖRÂtFV6÷&F–öç5¶—FVÕÒææÖR“° ¢ÖVçT—FVÒÓææÖRÒæÖS°¢ÖVçT—FVÒÓæ–BÒ—FVÓ°§Ð §7FF–2fö–B'W”ÖVçU&–çD—FVÔFW67&—F–öäæE6†÷t—FVÔ–6öâ‡33"—FVÒÂ&ööÃ‚öä–æ—BÂ7G'V7BÆ—7DÖVçR¦Æ—7B§°¢6öç7BS‚¦FW67&—F–öã°¢–b†öä–æ—BÒE%TR¢Æ•4T7W'6÷$Ö÷fR…4Uõ4TÄT5B“° ¢–b†—FVÒÒÄ•5Eô4ä4TÂ¢'W”ÖVçTFD—FVÔ–6öâ†—FVÒÂ56†÷FFÓæ–6öå6Æ÷B“°¢VÇ6P¢'W”ÖVçTFD—FVÔ–6öâ„•DTÕôÄ•5EôTäBÂ56†÷FFÓæ–6öå6Æ÷B“° ¢'W”ÖVçU&VÖ÷fT—FVÔ–6öâ†—FVÒÂ56†÷FFÓæ–6öå6Æ÷Bâ“°¢56†÷FFÓæ–6öå6Æ÷BãÒ°¢–b†—FVÒÒÄ•5Eô4ä4TÂ¢°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uôäõ$ÔÀ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô% ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÒ¢FW67&—F–öâÒvWD—FVÔFW67&—F–öâ†—FVÒ“°¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢FW67&—F–öâÒvWD—FVÔFW67&—F–öâ†—FVÒ“°¢4·W'D7W'&VçD&W''’ÒvWD&W''”g&öÔ&ÆÂ†—FVÒ“°¢&–çD&W''”6÷VçB…t”åô$U%$”U2Â4·W'D7W'&VçD&W''’“°¢6÷•v–æF÷uFõg&Ò…t”åô$U%$”U2Â4õ•t”åôeTÄÂ“°¢Ð¢VÇ6P¢FW67&—F–öâÒtFV6÷&F–öç5¶—FVÕÒæFW67&—F–öã°¢Ð¢VÇ6P¢°¢FW67&—F–öâÒuFW‡EõV—E6†÷–æs°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢f–ÆÅv–æF÷u—†VÄ'VffW"…t”åô$U%$”U2Â•„TÅôd”ÄÂƒ’“°¢FD&W''”–6öâ„•DTÕôÄ•5EôTäB“°¢FEFW‡E&–çFW%&ÖWFW&—¦VB…t”åô$U%$”U2ÂdôåEôäõ$ÔÂÂuFW‡EôW†—DÖVçRÂ#‚ÂRÂÂåTÄÂ“°¢6÷•v–æF÷uFõg&Ò…t”åô$U%$”U2Â4õ•t”åôeTÄÂ“°¢Ð¢Ð ¢f–ÆÅv–æF÷u—†VÄ'VffW"…t”åô•DTÕôDU45$•D”ôâÂ•„TÅôd”ÄÂƒ’“°¢'W”ÖVçU&–çB…t”åô•DTÕôDU45$•D”ôâÂFW67&—F–öâÂ2ÂÂÂ4ôÄõ$”Eôäõ$ÔÂ“°§Ð ¢òò¶VWF†R&ö6²6†÷F—66÷VçBÆö6ÂFòW&6†6W2g&öÒF†—26†÷à§7FF–2S3"vWE6†÷W&6†6U&–6R‡S3"—FVÔ–B§°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uôäõ$ÔÀ¢bbu6fT&Æö6³G"ÓæÆö6F–öâæÖw&÷WÓÒÔôu$õU„ÔôT5%UDTµô4•E•õ$ô4µõ4„õô„å2¢bbu6fT&Æö6³G"ÓæÆö6F–öâæÖçVÒÓÒÔôåTÒ„ÔôT5%UDTµô4•E•õ$ô4µõ4„õô„å2’¢°¢S3"&–6RÒvWD—FVÕ&–6R†—FVÔ–B“° ¢òò&÷VæBWv&B6òâöFB&–6RæWfW"&V6öÖW2g&VRà¢&WGW&â&–6Râò‡&–6R²’ò"¢&–6S°¢Ð ¢&WGW&âvWD—FVÕ&–6R†—FVÔ–B’ãâ—5ö¶TæWw47F—fR…ô´TäUu5õ4ÄDUõ%B“°§Ð §7FF–2fö–B'W”ÖVçU&–çE&–6T–äÆ—7B‡S‚v–æF÷t–BÂS3"—FVÔ–BÂS‚’§°¢S‚ƒ° ¢–b†—FVÔ–BÒÄ•5Eô4ä4TÂ¢°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô% ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÐ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ôDT4õ"¢°¢S‚§G"Ò6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#BÂvWD%6÷7Df÷$—FVÒ‚‡Sb–—FVÔ–B’Â5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂB“°¢7G&–æt6÷’‡G"ÂuFW‡Eô%“°¢‚ÒvWE7G&–æu&–v‡DÆ–vå„öfg6WB„dôåEôä%$õrÂu7G&–æuf#BÂ#“°¢FEFW‡E&–çFW%&ÖWFW&—¦VCB‡v–æF÷t–BÂdôåEôä%$õrÂ‚Â’ÂÂÂ56†÷'W”ÖVçUFW‡D6öÆ÷'5´4ôÄõ$”Eô•DTÕôÄ•5EÒÂDU…Eõ4´•ôE$rÂu7G&–æuf#B“°¢&WGW&ã°¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢Sb&W''”–BÒvWD&W''”g&öÔ&ÆÂ†—FVÔ–B“°¢–b†&W''”–BÒ•DTÕôäôäR¢°¢6÷”—FVÔæÖR†&W''”–BÂu7G&–æuf#B“°¢u7G&–æuf#Eµ7G&–ætÆVæwF‚†u7G&–æuf#B’ÒeÒÒTõ3°¢7G&–ætVæB†u7G&–æuf#BÂuFW‡Eõ76R“°¢7G&–ætVæB†u7G&–æuf#BÂuFW‡E÷„öæR“°¢‚ÒvWE7G&–æu&–v‡DÆ–vå„öfg6WB„dôåEôä%$õrÂu7G&–æuf#BÂ#“°¢FEFW‡E&–çFW%&ÖWFW&—¦VCB‡v–æF÷t–BÂdôåEôä%$õrÂ‚Â’ÂÂÂ56†÷'W”ÖVçUFW‡D6öÆ÷'5´4ôÄõ$”Eô•DTÕôÄ•5EÒÂDU…Eõ4´•ôE$rÂu7G&–æuf#B“°¢Ð¢&WGW&ã°¢Ð ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uôäõ$ÔÂ¢°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ€¢u7G&–æuf#À¢vWE6†÷W&6†6U&–6R†—FVÔ–B’À¢5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÀ¢b“°¢Ð¢VÇ6P¢°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ€¢u7G&–æuf#À¢tFV6÷&F–öç5¶—FVÔ–EÒç&–6RÀ¢5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÀ¢b“°¢Ð ¢–b„vWD—FVÔ–×÷'Fæ6R†—FVÔ–B’bb„6†V6´&t†4—FVÒ†—FVÔ–BÂ’ÇÂ6†V6µ4†4—FVÒ†—FVÔ–BÂ’’¢7G&–æt6÷’†u7G&–æuf#BÂuFW‡Eõ6öÆD÷WB“°¢VÇ6P¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡Eõö¶VFöÆÆ%f#“°¢‚ÒvWE7G&–æu&–v‡DÆ–vå„öfg6WB„dôåEôä%$õrÂu7G&–æuf#BÂ#“°¢FEFW‡E&–çFW%&ÖWFW&—¦VCB‡v–æF÷t–BÂdôåEôä%$õrÂ‚Â’ÂÂÂ56†÷'W”ÖVçUFW‡D6öÆ÷'5´4ôÄõ$”Eô•DTÕôÄ•5EÒÂDU…Eõ4´•ôE$rÂu7G&–æuf#B“°¢Ð§Ð §7FF–2fö–B'W”ÖVçTFE67&öÆÄ–æF–6F÷$'&÷w2‡fö–B§°¢–b‡56†÷FFÓç67&öÆÄ–æF–6F÷'5F6´–BÓÒD4µôäôäRbb4Ö'D–æfòæ—FVÔ6÷VçB²âÔ…ô•DTÕ5õ4„õtâ¢°¢56†÷FFÓç67&öÆÄ–æF–6F÷'5F6´–BÒFE67&öÆÄ–æF–6F÷$'&÷u—%&ÖWFW&—¦VB€¢45$ôÄÅô%$õuõUÀ¢s"À¢"À¢C‚À¢4Ö'D–æfòæ—FVÔ6÷VçBÒ„Ô…ô•DTÕ5õ4„õtâÒ’À¢Duõ45$ôÄÅô%$õrÀ¢Duõ45$ôÄÅô%$õrÀ¢g56†÷FFÓç67&öÆÄöfg6WB“°¢Ð§Ð §7FF–2fö–B'W”ÖVçU&VÖ÷fU67&öÆÄ–æF–6F÷$'&÷w2‡fö–B§°¢–b‡56†÷FFÓç67&öÆÄ–æF–6F÷'5F6´–BÒD4µôäôäR¢°¢&VÖ÷fU67&öÆÄ–æF–6F÷$'&÷u—"‡56†÷FFÓç67&öÆÄ–æF–6F÷'5F6´–B“°¢56†÷FFÓç67&öÆÄ–æF–6F÷'5F6´–BÒD4µôäôäS°¢Ð§Ð §7FF–2fö–B'W”ÖVçU&–çD7W'6÷"‡S‚67&öÆÄ–æF–6F÷'5F6´–BÂS‚6öÆ÷%6WB§°¢S‚’ÒÆ—7DÖVçTvWE”6ö÷&Df÷%&–çF–æt'&÷t7W'6÷"‡67&öÆÄ–æF–6F÷'5F6´–B“°¢'W”ÖVçU&–çB…t”åô•DTÕôÄ•5BÂuFW‡Eõ6VÆV7F÷$'&÷s"ÂÂ’ÂÂ6öÆ÷%6WB“°§Ð §7FF–2fö–B'W”ÖVçTFD—FVÔ–6öâ†VçVÒ—FVÒ—FVÒÂS‚–6öå6Æ÷B§°¢S‚7&—FT–C°¢S‚§7&—FT–EG"Òg56†÷FFÓæ—FVÕ7&—FT–G5¶–6öå6Æ÷EÓ°¢–b‚§7&—FT–EG"Ò5$•DUôäôäR¢&WGW&ã° ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uôäõ$ÔÀ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%@¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô% ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÐ¢ÇÂ—FVÒÓÒ•DTÕôÄ•5EôTäB¢°¢7&—FT–BÒFD—FVÔ–6öå7&—FR†–6öå6Æ÷B²Duô•DTÕô”4ôåô$4RÂ–6öå6Æ÷B²Duô•DTÕô”4ôåô$4RÂ—FVÒ“°¢–b‡7&—FT–BÒÔ…õ5$•DU2¢°¢§7&—FT–EG"Ò7&—FT–C°¢u7&—FW5·7&—FT–EÒçƒ"Ò#C°¢u7&—FW5·7&—FT–EÒç“"Òƒƒ°¢Ð¢Ð¢VÇ6P¢°¢7&—FT–BÒFDFV6÷&F–öä–6öäö&¦V7B†—FVÒÂ#ÂƒBÂÂ–6öå6Æ÷B²Duô•DTÕô”4ôåô$4RÂ–6öå6Æ÷B²Duô•DTÕô”4ôåô$4R“°¢–b‡7&—FT–BÒÔ…õ5$•DU2¢§7&—FT–EG"Ò7&—FT–C°¢Ð§Ð §7FF–2fö–B'W”ÖVçU&VÖ÷fT—FVÔ–6öâ†VçVÒ—FVÒ—FVÒÂS‚–6öå6Æ÷B§°¢S‚§7&—FT–EG"Òg56†÷FFÓæ—FVÕ7&—FT–G5¶–6öå6Æ÷EÓ°¢–b‚§7&—FT–EG"ÓÒ5$•DUôäôäR¢&WGW&ã° ¢g&VU7&—FUF–ÆW4'•Fr†–6öå6Æ÷B²Duô•DTÕô”4ôåô$4R“°¢g&VU7&—FUÆWGFT'•Fr†–6öå6Æ÷B²Duô•DTÕô”4ôåô$4R“°¢FW7G&÷•7&—FR‚fu7&—FW5²§7&—FT–EG%Ò“°¢§7&—FT–EG"Ò5$•DUôäôäS°§Ð §7FF–2fö–B'W”ÖVçT–æ—D&w2‡fö–B§°¢&W6WD&w4æD6ÆV$FÖ4'W7”fÆw2ƒ“°¢–æ—D&w4g&öÕFV×ÆFW2ƒÂ56†÷'W”ÖVçT&uFV×ÆFW2Â%$•ô4õTåB‡56†÷'W”ÖVçT&uFV×ÆFW2’“°¢6WD&uF–ÆVÖ'VffW"ƒÂ56†÷FFÓçF–ÆVÖ'VffW'5³Ò“°¢6WD&uF–ÆVÖ'VffW"ƒ"Â56†÷FFÓçF–ÆVÖ'VffW'5³5Ò“°¢6WD&uF–ÆVÖ'VffW"ƒ2Â56†÷FFÓçF–ÆVÖ'VffW'5³%Ò“°¢6WDwU&Vr…$Tuôôde4UEô$s„ôe2Â“°¢6WDwU&Vr…$Tuôôde4UEô$sdôe2Â“°¢6WDwU&Vr…$Tuôôde4UEô$s„ôe2Â“°¢6WDwU&Vr…$Tuôôde4UEô$sdôe2Â“°¢6WDwU&Vr…$Tuôôde4UEô$s$„ôe2Â“°¢6WDwU&Vr…$Tuôôde4UEô$s%dôe2Â“°¢6WDwU&Vr…$Tuôôde4UEô$s4„ôe2Â“°¢6WDwU&Vr…$Tuôôde4UEô$s5dôe2Â“°¢6WDwU&Vr…$Tuôôde4UEô$ÄD4åBÂ“°¢6WDwU&Vr…$Tuôôde4UEôD•54åBÂD•54åEôÔôDUóÂD•54åEôô$¥ôôâÂD•54åEôô$¥óEôÔ“°¢6†÷t&rƒ“°¢6†÷t&rƒ“°¢6†÷t&rƒ"“°¢6†÷t&rƒ2“°§Ð §7FF–2fö–B'W”ÖVçTFV6ö×&W74&tw&†–72‡fö–B§°¢FV6ö×&W74æD6÷•F–ÆTFFFõg&ÒƒÂu6†÷ÖVçUôvg‚Âƒ4Âƒ4S2Â“°¢FV6ö×&W74FFv—F„†VFW%w&Ò†u6†÷ÖVçUõF–ÆVÖÂ56†÷FFÓçF–ÆVÖ'VffW'5³Ò“°¢ÆöEÆWGFR†u6†÷ÖVçUõÂÂ$uõÅEEô”B…4„õôÔTåUõÄUEDUô”B’ÂÅEEõ4•¤UóD%“°§Ð §7FF–2fö–B'W”ÖVçT–æ—Ev–æF÷w2‡fö–B§°¢S‚ÖöæW•v–æF÷t–C° ¢–æ—Ev–æF÷w2‡56†÷'W”ÖVçUv–æF÷uFV×ÆFW2“°¢FV7F—fFTÆÅFW‡E&–çFW'2‚“° ¢ÖöæW•v–æF÷t–BÒ‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B’òt”åô$U%$”U2¢t”åôÔôäU“° ¢ÆöEW6W%v–æF÷t&÷&FW$vg‚†ÖöæW•v–æF÷t–BÂÂ$uõÅEEô”Bƒ2’“°¢ÆöDÖW76vT&÷„vg‚†ÖöæW•v–æF÷t–BÂ„Â$uõÅEEô”BƒB’“°¢WEv–æF÷uF–ÆVÖ†ÖöæW•v–æF÷t–B“°¢WEv–æF÷uF–ÆVÖ…t”åô•DTÕôÄ•5B“°¢WEv–æF÷uF–ÆVÖ…t”åô•DTÕôDU45$•D”ôâ“°§Ð §7FF–2fö–B'W”ÖVçU&–çB‡S‚v–æF÷t–BÂ6öç7BS‚§FW‡BÂS‚‚ÂS‚’Â3‚7VVBÂS‚6öÆ÷%6WB§°¢FEFW‡E&–çFW%&ÖWFW&—¦VCB‡v–æF÷t–BÂdôåEôäõ$ÔÂÂ‚Â’ÂÂÂ56†÷'W”ÖVçUFW‡D6öÆ÷'5¶6öÆ÷%6WEÒÂ7VVBÂFW‡B“°§Ð §7FF–2fö–B'W”ÖVçTF—7Æ”ÖW76vR‡S‚F6´–BÂ6öç7BS‚§FW‡BÂF6´gVæ26ÆÆ&6²§°¢F—7Æ”ÖW76vTæD6öçF–çVUF6²‡F6´–BÂt”åôÔU54tRÂÂBÂdôåEôäõ$ÔÂÂvWEÆ–W%FW‡E7VVDFVÆ’‚’ÂFW‡BÂ6ÆÆ&6²“°¢66†VGVÆT&t6÷•F–ÆVÖFõg&Òƒ“°§Ð §7FF–2fö–B'W”ÖVçTG&tw&†–72‡fö–B§°¢'W”ÖVçTG&tÖw&†–72‚“°¢'W”ÖVçT6÷”ÖVçT&uFô&sF–ÆVÖ'VffW"‚“°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢G&u7FDg&ÖUv—F„7W7FöÕF–ÆTæEÆWGFR…t”åô$U%$”U2ÂdÅ4RÂÂ2“°¢–b‡4Ö'D–æfòæ—FVÔ6÷VçBâ¢°¢Sbf—'7D&ÆÂÒ4Ö'D–æfòæ—FVÔÆ—7E³Ó°¢4·W'D7W'&VçD&W''’ÒvWD&W''”g&öÔ&ÆÂ†f—'7D&ÆÂ“°¢&–çD&W''”6÷VçB…t”åô$U%$”U2Â4·W'D7W'&VçD&W''’“°¢Ð¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô% ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÐ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ôDT4õ"¢°¢G&u7FDg&ÖUv—F„7W7FöÕF–ÆTæEÆWGFR…t”åôÔôäU’ÂdÅ4RÂÂ2“°¢&–çD%Ö÷VçD–äÖöæW”&÷‚…t”åôÔôäU’Âu6fT&Æö6³%G"Óæg&öçF–W"æ&GFÆUö–çG2Â“°¢FD%Æ&VÄö&¦V7Bƒ’Â“°¢Ð¢VÇ6P¢°¢FDÖöæW”Æ&VÄö&¦V7Bƒ’Â“°¢&–çDÖöæW”Ö÷VçD–äÖöæW”&÷…v—F„&÷&FW"…t”åôÔôäU’ÂÂ2ÂvWDÖöæW’‚fu6fT&Æö6³G"ÓæÖöæW’’“°¢Ð¢66†VGVÆT&t6÷•F–ÆVÖFõg&Òƒ“°¢66†VGVÆT&t6÷•F–ÆVÖFõg&Òƒ“°¢66†VGVÆT&t6÷•F–ÆVÖFõg&Òƒ"“°¢66†VGVÆT&t6÷•F–ÆVÖFõg&Òƒ2“°§Ð §7FF–2fö–B'W”ÖVçTG&tÖw&†–72‡fö–B§°¢'W”ÖVçT6öÆÆV7Dö&¦V7DWfVçDFF‚“°¢'W”ÖVçTG&tö&¦V7DWfVçG2‚“°¢'W”ÖVçTG&tÖ&r‚“°§Ð §7FF–2fö–B'W”ÖVçTG&tÖ&r‡fö–B§°¢3b’Â£°¢3b‚Â“°¢6öç7B7G'V7BÖÆ–÷WB¦ÖÆ–÷WC°¢SbÖWFF–ÆS°¢SbçVÔÖWFF–ÆW4–å&–Ö'“°¢S‚ÖWFF–ÆTÆ–W%G—S° ¢ÖÆ–÷WBÒtÖ†VFW"æÖÆ–÷WC°¢çVÔÖWFF–ÆW4–å&–Ö'’ÒvWDçVÔÖWFF–ÆW4–å&–Ö'’†ÖÆ–÷WB“°¢vWE…”6ö÷&G4öæU7FW–äg&öçDöeÆ–W"‚g‚Âg’“°¢‚ÓÒC°¢’ÓÒC° ¢f÷"†¢Ò²¢Â²¢²²¢°¢f÷"†’Ò²’ÂS²’²²¢°¢ÖWFF–ÆRÒÖw&–DvWDÖWFF–ÆT–DB‡‚²’Â’²¢“°¢–b„'W”ÖVçT6†V6´f÷$÷fW&Æv—F„ÖVçT&r†’Â¢’ÓÒE%TR¢ÖWFF–ÆTÆ–W%G—RÒÖw&–DvWDÖWFF–ÆTÆ–W%G—TB‡‚²’Â’²¢“°¢VÇ6P¢ÖWFF–ÆTÆ–W%G—RÒÔUDD”ÄUôÄ”U%õE•Uô4õdU$TC° ¢–b†ÖWFF–ÆRÂçVÔÖWFF–ÆW4–å&–Ö'’¢'W”ÖVçTG&tÖÖWFF–ÆR†’Â¢ÂÖÆ–÷WBÓç&–Ö'•F–ÆW6WBÓæÖWFF–ÆW2²ÖWFF–ÆR¢åTÕõD”ÄU5õU%ôÔUDD”ÄRÂÖWFF–ÆTÆ–W%G—R“°¢VÇ6P¢'W”ÖVçTG&tÖÖWFF–ÆR†’Â¢ÂÖÆ–÷WBÓç6V6öæF'•F–ÆW6WBÓæÖWFF–ÆW2²‚†ÖWFF–ÆRÒçVÔÖWFF–ÆW4–å&–Ö'’’¢åTÕõD”ÄU5õU%ôÔUDD”ÄR’ÂÖWFF–ÆTÆ–W%G—R“°¢Ð¢Ð§Ð §7FF–2fö–B'W”ÖVçTG&tÖÖWFF–ÆR‡3b‚Â3b’Â6öç7BSb§7&2ÂS‚ÖWFF–ÆTÆ–W%G—R§°¢Sböfg6WCÒ‚¢#°¢Sböfg6WC"Ò’¢cC° ¢7v—F6‚†ÖWFF–ÆTÆ–W%G—R¢°¢66RÔUDD”ÄUôÄ”U%õE•Uôäõ$ÔÃ ¢'W”ÖVçTG&tÖÖWFF–ÆTÆ–W"‡56†÷FFÓçF–ÆVÖ'VffW'5³5ÒÂöfg6WCÂöfg6WC"Â7&2“°¢'W”ÖVçTG&tÖÖWFF–ÆTÆ–W"‡56†÷FFÓçF–ÆVÖ'VffW'5³ÒÂöfg6WCÂöfg6WC"Â7&2²B“°¢'&V³°¢66RÔUDD”ÄUôÄ”U%õE•Uô4õdU$TC ¢'W”ÖVçTG&tÖÖWFF–ÆTÆ–W"‡56†÷FFÓçF–ÆVÖ'VffW'5³%ÒÂöfg6WCÂöfg6WC"Â7&2“°¢'W”ÖVçTG&tÖÖWFF–ÆTÆ–W"‡56†÷FFÓçF–ÆVÖ'VffW'5³5ÒÂöfg6WCÂöfg6WC"Â7&2²B“°¢'&V³°¢66RÔUDD”ÄUôÄ”U%õE•Uõ5Ä•C ¢'W”ÖVçTG&tÖÖWFF–ÆTÆ–W"‡56†÷FFÓçF–ÆVÖ'VffW'5³%ÒÂöfg6WCÂöfg6WC"Â7&2“°¢'W”ÖVçTG&tÖÖWFF–ÆTÆ–W"‡56†÷FFÓçF–ÆVÖ'VffW'5³ÒÂöfg6WCÂöfg6WC"Â7&2²B“°¢'&V³°¢Ð§Ð §7FF–2fö–B'W”ÖVçTG&tÖÖWFF–ÆTÆ–W"‡Sb¦FW7BÂ3böfg6WCÂ3böfg6WC"Â6öç7BSb§7&2§°¢òòF†—2gVæ7F–öâG&w2v†öÆR'ƒ"ÖWFF–ÆRà¢FW7E¶öfg6WC²öfg6WC%ÒÒ7&5³Ó²òòF÷ÆVg@¢FW7E¶öfg6WC²öfg6WC"²ÒÒ7&5³Ó²òòF÷&–v‡@¢FW7E¶öfg6WC²öfg6WC"²3%ÒÒ7&5³%Ó²òò&÷GFöÒÆVg@¢FW7E¶öfg6WC²öfg6WC"²35ÒÒ7&5³5Ó²òò&÷GFöÒ&–v‡@§Ð §7FF–2fö–B'W”ÖVçT6öÆÆV7Dö&¦V7DWfVçDFF‡fö–B§°¢3bf6–æuƒ°¢3bf6–æu“°¢S‚“°¢S‚ƒ°¢S‚çVÔö&¦V7G2Ò° ¢vWE…”6ö÷&G4öæU7FW–äg&öçDöeÆ–W"‚ff6–æu‚Âff6–æu’“° ¢f÷"‡’Ò²’Âô$¤T5EôUdTåE5ô4õTåC²’²²¢56†÷FFÓçf–Ww÷'Dö&¦V7G5·•Õ´ô$¥ôUdTåEô”EÒÒô$¤T5EôUdTåE5ô4õTåC° ¢f÷"‡’Ò²’ÂS²’²²¢°¢f÷"‡‚Ò²‚Âs²‚²²¢°¢S‚ö&¤WfVçD–BÒvWDö&¦V7DWfVçD–D'•…’†f6–æu‚ÒB²‚Âf6–æu’Ò"²’“° ¢òò6¶—–b–çfÆ–B÷"â÷fW'v÷&ÆBö¶VÖöâF†B—2æ÷BföÆÆ÷v–ærF†RÆ–W ¢–b†ö&¤WfVçD–BÒô$¤T5EôUdTåE5ô4õTåBbb†tö&¦V7DWfVçG5¶ö&¤WfVçD–EÒæ7F—fRbbtö&¦V7DWfVçG5¶ö&¤WfVçD–EÒæw&†–74–Bbô$¥ôUdTåEôÔôâbbtö&¦V7DWfVçG5¶ö&¤WfVçD–EÒæÆö6Ä–BÒô$¥ôUdTåEô”EôdôÄÄõtU"’¢°¢56†÷FFÓçf–Ww÷'Dö&¦V7G5¶çVÔö&¦V7G5Õ´ô$¥ôUdTåEô”EÒÒö&¤WfVçD–C°¢56†÷FFÓçf–Ww÷'Dö&¦V7G5¶çVÔö&¦V7G5Õµ…ô4ôõ$EÒÒƒ°¢56†÷FFÓçf–Ww÷'Dö&¦V7G5¶çVÔö&¦V7G5Õµ•ô4ôõ$EÒÒ“°¢56†÷FFÓçf–Ww÷'Dö&¦V7G5¶çVÔö&¦V7G5Õ´Ä”U%õE•UÒÒÖw&–DvWDÖWFF–ÆTÆ–W%G—TB†f6–æu‚ÒB²‚Âf6–æu’Ò"²’“° ¢7v—F6‚†tö&¦V7DWfVçG5¶ö&¤WfVçD–EÒæf6–ætF—&V7F–öâ¢°¢66RD•%õ4õUDƒ ¢56†÷FFÓçf–Ww÷'Dö&¦V7G5¶çVÔö&¦V7G5Õ´ä”ÕôåTÕÒÒä”Õõ5DEôd4Uõ4õUDƒ°¢'&V³°¢66RD•%ôäõ%Dƒ ¢56†÷FFÓçf–Ww÷'Dö&¦V7G5¶çVÔö&¦V7G5Õ´ä”ÕôåTÕÒÒä”Õõ5DEôd4Uôäõ%Dƒ°¢'&V³°¢66RD•%õtU5C ¢56†÷FFÓçf–Ww÷'Dö&¦V7G5¶çVÔö&¦V7G5Õ´ä”ÕôåTÕÒÒä”Õõ5DEôd4UõtU5C°¢'&V³°¢66RD•%ôT5C ¢FVfVÇC ¢56†÷FFÓçf–Ww÷'Dö&¦V7G5¶çVÔö&¦V7G5Õ´ä”ÕôåTÕÒÒä”Õõ5DEôd4UôT5C°¢'&V³°¢Ð¢çVÔö&¦V7G2²³°¢Ð¢Ð¢Ð§Ð §7FF–2fö–B'W”ÖVçTG&tö&¦V7DWfVçG2‡fö–B§°¢S‚“°¢S‚7&—FT–C°¢6öç7B7G'V7Bö&¦V7DWfVçDw&†–74–æfò¦w&†–74–æfó°¢S‚vVF†W%FV×ÒuvVF†W%G"ÓçÅ&ö6W76–æu7FFS° ¢òòF†—2gVæ7F–öâ'Vç2GW&–ærfFV÷WBÂ6òF†RvVF†W"ÆWGFR&ö6W76–ær7FFR×W7B&RFV×÷&&–Ç’6†ævVBÀ¢òò6òF†BF–ÖRÖ&ÆVæF–ærv–ÆÂv÷&²&÷W&Ç¢–b‡vVF†W%FV×ÓÒtTD„U%õÅõ5DDUõ45$TTåôdD”äuôõUB¢uvVF†W%G"ÓçÅ&ö6W76–æu7FFRÒtTD„U%õÅõ5DDUô”DÄS°¢f÷"†’Ò²’Âô$¤T5EôUdTåE5ô4õTåC²’²²¢°¢–b‡56†÷FFÓçf–Ww÷'Dö&¦V7G5¶•Õ´ô$¥ôUdTåEô”EÒÓÒô$¤T5EôUdTåE5ô4õTåB¢6öçF–çVS° ¢w&†–74–æfòÒvWDö&¦V7DWfVçDw&†–74–æfò†tö&¦V7DWfVçG5·56†÷FFÓçf–Ww÷'Dö&¦V7G5¶•Õ´ô$¥ôUdTåEô”EÕÒæw&†–74–B“° ¢7&—FT–BÒ7&VFTö&¦V7Dw&†–757&—FR€¢tö&¦V7DWfVçG5·56†÷FFÓçf–Ww÷'Dö&¦V7G5¶•Õ´ô$¥ôUdTåEô”EÕÒæw&†–74–BÀ¢7&—FT6ÆÆ&6´GVÖ×’À¢‡Sb—56†÷FFÓçf–Ww÷'Dö&¦V7G5¶•Õµ…ô4ôõ$EÒ¢b²‚À¢‡Sb—56†÷FFÓçf–Ww÷'Dö&¦V7G5¶•Õµ•ô4ôõ$EÒ¢b²C‚Òw&†–74–æfòÓæ†V–v‡Bò"À¢"“° ¢–b„'W”ÖVçT6†V6´–dö&¦V7DWfVçD÷fW&Æ4ÖVçT&r‡56†÷FFÓçf–Ww÷'Dö&¦V7G5¶•Ò’ÓÒE%TR¢°¢u7&—FW5·7&—FT–EÒç7V'7&—FUF&ÆTçVÒÒC°¢u7&—FW5·7&—FT–EÒç7V'7&—FTÖöFRÒ5T%5$•DU5ôôã°¢Ð ¢7F'E7&—FTæ–Ò‚fu7&—FW5·7&—FT–EÒÂ56†÷FFÓçf–Ww÷'Dö&¦V7G5¶•Õ´ä”ÕôåTÕÒ“°¢Ð ¢uvVF†W%G"ÓçÅ&ö6W76–æu7FFRÒvVF†W%FV×²òò&W7F÷&RvVF†W"7FFP¢7Tf7D6÷’†uÇGD'VffW$fFVB²b£bÂuÇGD'VffW%VæfFVB²b£bÂÅEEô%TddU%õ4•¤R“°§Ð §7FF–2&ööÃ‚'W”ÖVçT6†V6´–dö&¦V7DWfVçD÷fW&Æ4ÖVçT&r‡3b¦ö&¦V7B§°¢–b‚'W”ÖVçT6†V6´f÷$÷fW&Æv—F„ÖVçT&r†ö&¦V7Eµ…ô4ôõ$EÒÂö&¦V7Eµ•ô4ôõ$EÒ²"’bbö&¦V7E´Ä”U%õE•UÒÒÔUDD”ÄUôÄ”U%õE•Uô4õdU$TB¢&WGW&âE%TS°¢VÇ6P¢&WGW&âdÅ4S°§Ð §7FF–2fö–B'W”ÖVçT6÷”ÖVçT&uFô&sF–ÆVÖ'VffW"‡fö–B§°¢3b“°¢Sb¦FW7BÒ56†÷FFÓçF–ÆVÖ'VffW'5³Ó°¢6öç7BSb§7&2Ò56†÷FFÓçF–ÆVÖ'VffW'5³Ó° ¢f÷"†’Ò²’Â#C²’²²¢°¢–b‡7&5¶•ÒÒ¢FW7E¶•ÒÒ7&5¶•Ò²‚…4„õôÔTåUõÄUEDUô”BÃÂ"’Âƒ4S2“°¢Ð§Ð §7FF–2&ööÃ‚'W”ÖVçT6†V6´f÷$÷fW&Æv—F„ÖVçT&r†–çB‚Â–çB’§°¢6öç7BSb¦ÖWFF–ÆRÒ56†÷FFÓçF–ÆVÖ'VffW'5³Ó°¢–çBöfg6WCÒ‚¢#°¢–çBöfg6WC"Ò’¢cC° ¢–b†ÖWFF–ÆU¶öfg6WC"²öfg6WCÒÓÒb`¢ÖWFF–ÆU¶öfg6WC"²öfg6WC²3%ÒÓÒb`¢ÖWFF–ÆU¶öfg6WC"²öfg6WC²ÒÓÒb`¢ÖWFF–ÆU¶öfg6WC"²öfg6WC²35ÒÓÒ¢&WGW&âE%TS° ¢&WGW&âdÅ4S°§Ð §7FF–2fö–BF6µô'W”ÖVçR‡S‚F6´–B§°¢3b¦FFÒuF6·5·F6´–EÒæFF° ¢–b‚uÆWGFTfFRæ7F—fR¢°¢33"—FVÔ–BÒÆ—7DÖVçUõ&ö6W74–çWB‡DÆ—7EF6´–B“°¢Æ—7DÖVçTvWE67&öÆÄæE&÷r‡DÆ—7EF6´–BÂg56†÷FFÓç67&öÆÄöfg6WBÂg56†÷FFÓç6VÆV7FVE&÷r“° ¢7v—F6‚†—FVÔ–B¢°¢66RÄ•5EôäõD„”äuô4„õ4Tã ¢'&V³°¢66RÄ•5Eô4ä4TÃ ¢Æ•4R…4Uõ4TÄT5B“°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢u7V6–Åf%õ&W7VÇBÒdÅ4S°¢W†—D'W”ÖVçR‡F6´–B“°¢'&V³°¢FVfVÇC ¢Æ•4R…4Uõ4TÄT5B“°¢D—FVÔ–BÒ—FVÔ–C°¢6ÆV%v–æF÷uF–ÆVÖ…t”åô•DTÕôDU45$•D”ôâ“°¢'W”ÖVçU&VÖ÷fU67&öÆÄ–æF–6F÷$'&÷w2‚“°¢'W”ÖVçU&–çD7W'6÷"‡DÆ—7EF6´–BÂ4ôÄõ$”Eôu$•ô5U%4õ"“° ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uôäõ$ÔÂ¢56†÷FFÓçF÷FÄ6÷7BÒvWE6†÷W&6†6U&–6R†—FVÔ–B“°¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢56†÷FFÓçF÷FÄ6÷7BÒ°¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô% ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÐ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ôDT4õ"¢56†÷FFÓçF÷FÄ6÷7BÒvWD%6÷7Df÷$—FVÒ†—FVÔ–B“°¢VÇ6P¢56†÷FFÓçF÷FÄ6÷7BÒtFV6÷&F–öç5¶—FVÔ–EÒç&–6S° ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢Sb&W''”—FVÒÒvWD&W''”g&öÔ&ÆÂ†—FVÔ–B“°¢Sb&W''”6÷VçBÒ6÷VçEF÷FÄ—FVÕVçF—G”–ä&r†&W''”—FVÒ“° ¢–b†&W''”6÷VçBÂ¢°¢6÷”—FVÔæÖR†&W''”—FVÒÂu7G&–æuf#“°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡EôFöçD†fTVæ÷Vv…f#Â'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢VÇ6P¢°¢6÷”—FVÔæÖR†—FVÔ–BÂu7G&–æuf#“°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõf#7W&T†÷tÖç’ÂF6µô'W”†÷tÖç”F–ÆöwVT–æ—B“°¢Ð¢Ð¢VÇ6R–b„vWD—FVÔ–×÷'Fæ6R†—FVÔ–B’bb„6†V6´&t†4—FVÒ†—FVÔ–BÂ’ÇÂ6†V6µ4†4—FVÒ†—FVÔ–BÂ’’¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡EõF†D—FVÔ—56öÆD÷WBÂ'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%¢°¢–b†u6fT&Æö6³%G"Óæg&öçF–W"æ&GFÆUö–çG2Â56†÷FFÓçF÷FÄ6÷7B¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõ–÷TFöçD†fTVæ÷Vv„%Â'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢VÇ6P¢°¢6÷”—FVÔæÖR†—FVÔ–BÂu7G&–æuf#“°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõf#6W'F–æÇ”†÷tÖç’ÂF6µô'W”†÷tÖç”F–ÆöwVT–æ—B“°¢Ð¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÒ¢°¢–b†u6fT&Æö6³%G"Óæg&öçF–W"æ&GFÆUö–çG2Â56†÷FFÓçF÷FÄ6÷7B¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõ–÷TFöçD†fTVæ÷Vv„%Â'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢VÇ6P¢°¢D—FVÔ6÷VçBÒ°¢6÷”—FVÔæÖR†—FVÔ–BÂu7G&–æuf#“°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#"Â56†÷FFÓçF÷FÄ6÷7BÂ5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂB“°¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡Eõ–÷UvçFVEf#F†FÆÄ&Uf#$%“°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂu7G&–æuf#BÂ'W”ÖVçT6öæf—&ÕW&6†6R“°¢Ð¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ôDT4õ"¢°¢–b†u6fT&Æö6³%G"Óæg&öçF–W"æ&GFÆUö–çG2Â56†÷FFÓçF÷FÄ6÷7B¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõ–÷TFöçD†fTVæ÷Vv„%Â'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢VÇ6P¢°¢D—FVÔ6÷VçBÒ°¢7G&–æt6÷’†u7G&–æuf#ÂtFV6÷&F–öç5¶—FVÔ–EÒææÖR“°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#"Â56†÷FFÓçF÷FÄ6÷7BÂ5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂB“°¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡Eõ–÷UvçFVEf#F†FÆÄ&Uf#$%“°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂu7G&–æuf#BÂ'W”ÖVçT6öæf—&ÕW&6†6R“°¢Ð¢Ð¢VÇ6R–b‚—4Væ÷Vv„ÖöæW’‚fu6fT&Æö6³G"ÓæÖöæW’Â56†÷FFÓçF÷FÄ6÷7B’¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõ–÷TFöçD†fTÖöæW’Â'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢VÇ6P¢°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uôäõ$ÔÂ¢°¢6÷”—FVÔæÖR†—FVÔ–BÂu7G&–æuf#“°¢–b„vWD—FVÔ–×÷'Fæ6R†—FVÔ–B’¢°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#"Â56†÷FFÓçF÷FÄ6÷7BÂ5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂb“°¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡Eõ–÷UvçFVEf#F†FÆÄ&Uf#"“°¢D—FVÔ6÷VçBÒ°¢56†÷FFÓçF÷FÄ6÷7BÒvWE6†÷W&6†6U&–6R‡D—FVÔ–B’¢D—FVÔ6÷VçC°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂu7G&–æuf#BÂ'W”ÖVçT6öæf—&ÕW&6†6R“°¢Ð¢VÇ6R–b„vWD—FVÕö6¶WB†—FVÔ–B’ÓÒô4´UEõDÕô„Ò¢°¢7G&–æt6÷’†u7G&–æuf#"ÂvWDÖ÷fTæÖR„—FVÔ–EFô&GFÆTÖ÷fT–B†—FVÔ–B’’“°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõf#6W'F–æÇ”†÷tÖç“"ÂF6µô'W”†÷tÖç”F–ÆöwVT–æ—B“°¢Ð¢VÇ6P¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõf#6W'F–æÇ”†÷tÖç’ÂF6µô'W”†÷tÖç”F–ÆöwVT–æ—B“°¢Ð¢Ð¢VÇ6P¢°¢7G&–æt6÷’†u7G&–æuf#ÂtFV6÷&F–öç5¶—FVÔ–EÒææÖR“°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#"Â56†÷FFÓçF÷FÄ6÷7BÂ5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂÔ…ôÔôäU•ôD”t•E2“° ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôDT4õ"¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡Eõf#—4—EF†FÆÄ&Uf#"“°¢VÇ6RòòÔ%EõE•UôDT4õ# ¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡Eõ–÷UvçFVEf#F†FÆÄ&Uf#"“° ¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂu7G&–æuf#BÂ'W”ÖVçT6öæf—&ÕW&6†6R“°¢Ð¢Ð¢'&V³°¢Ð¢Ð§Ð §7FF–2fö–BF6µô'W”†÷tÖç”F–ÆöwVT–æ—B‡S‚F6´–B§°¢3b¦FFÒuF6·5·F6´–EÒæFF° ¢SbVçF—G”–ä&rÒ6÷VçEF÷FÄ—FVÕVçF—G”–ä&r‡D—FVÔ–B“°¢SbÖ…VçF—G“° ¢G&u7FDg&ÖUv—F„7W7FöÕF–ÆTæEÆWGFR…t”åõTåD•E•ô”åô$rÂdÅ4RÂÂ2“°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#ÂVçF—G”–ä&rÂ5E%ô4ôåeôÔôDUõ$”t…EôÄ”tâÂÔ…ô•DTÕôD”t•E2²“°¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡Eô–ä&uf#“°¢'W”ÖVçU&–çB…t”åõTåD•E•ô”åô$rÂu7G&–æuf#BÂÂÂÂ4ôÄõ$”Eôäõ$ÔÂ“°¢D—FVÔ6÷VçBÒ°¢G&u7FDg&ÖUv—F„7W7FöÕF–ÆTæEÆWGFR…t”åõTåD•E•õ$”4RÂdÅ4RÂÂ2“°¢'W”ÖVçU&–çD—FVÕVçF—G”æE&–6R‡F6´–B“°¢66†VGVÆT&t6÷•F–ÆVÖFõg&Òƒ“° ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢Sb&W''”—FVÒÒvWD&W''”g&öÔ&ÆÂ‡D—FVÔ–B“°¢Ö…VçF—G’Ò6÷VçEF÷FÄ—FVÕVçF—G”–ä&r†&W''”—FVÒ“°¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%¢°¢Ö…VçF—G’Òu6fT&Æö6³%G"Óæg&öçF–W"æ&GFÆUö–çG2ò56†÷FFÓçF÷FÄ6÷7C°¢Ð¢VÇ6R–b‡56†÷FFÓçF÷FÄ6÷7BÓÒ¢Ö…VçF—G’ÒÔ…ô$uô•DTÕô44•E“°¢VÇ6P¢Ö…VçF—G’ÒvWDÖöæW’‚fu6fT&Æö6³G"ÓæÖöæW’’ò56†÷FFÓçF÷FÄ6÷7C° ¢–b†Ö…VçF—G’âÔ…ô$uô•DTÕô44•E’¢56†÷FFÓæÖ…VçF—G’ÒÔ…ô$uô•DTÕô44•E“°¢VÇ6P¢56†÷FFÓæÖ…VçF—G’ÒÖ…VçF—G“° ¢uF6·5·F6´–EÒægVæ2ÒF6µô'W”†÷tÖç”F–ÆöwVT†æFÆT–çWC°§Ð §7FF–2fö–BF6µô'W”†÷tÖç”F–ÆöwVT†æFÆT–çWB‡S‚F6´–B§°¢3b¦FFÒuF6·5·F6´–EÒæFF° ¢–b„F§W7EVçF—G”66÷&F–æuFôED–çWB‚gD—FVÔ6÷VçBÂ56†÷FFÓæÖ…VçF—G’’ÓÒE%TR¢°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢56†÷FFÓçF÷FÄ6÷7BÒD—FVÔ6÷VçC°¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%¢56†÷FFÓçF÷FÄ6÷7BÒvWD%6÷7Df÷$—FVÒ‡D—FVÔ–B’¢D—FVÔ6÷VçC°¢VÇ6P¢56†÷FFÓçF÷FÄ6÷7BÒvWE6†÷W&6†6U&–6R‡D—FVÔ–B’¢D—FVÔ6÷VçC°¢'W”ÖVçU&–çD—FVÕVçF—G”æE&–6R‡F6´–B“°¢Ð¢VÇ6P¢°¢–b„¤õ•ôäUr„ô%UEDôâ’¢°¢Æ•4R…4Uõ4TÄT5B“°¢&VÖ÷fUVçF—G”&W''”–6öâ‚“°¢6ÆV%7FEv–æF÷tæDg&ÖUFõG&ç7&VçB…t”åõTåD•E•õ$”4RÂdÅ4R“°¢6ÆV%7FEv–æF÷tæDg&ÖUFõG&ç7&VçB…t”åõTåD•E•ô”åô$rÂdÅ4R“°¢6ÆV%v–æF÷uF–ÆVÖ…t”åõTåD•E•õ$”4R“°¢6ÆV%v–æF÷uF–ÆVÖ…t”åõTåD•E•ô”åô$r“°¢WEv–æF÷uF–ÆVÖ…t”åô•DTÕôÄ•5B“°¢6÷”—FVÔæÖR‡D—FVÔ–BÂu7G&–æuf#“°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#"ÂD—FVÔ6÷VçBÂ5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂÔ…ô•DTÕôD”t•E2“°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#2Â56†÷FFÓçF÷FÄ6÷7BÂ5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂÔ…ôÔôäU•ôD”t•E2“°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢Sb&W''”–BÒvWD&W''”g&öÔ&ÆÂ‡D—FVÔ–B“°¢6÷”—FVÔæÖR†&W''”–BÂu7G&–æuf#B“°¢u7G&–æuf#Eµ7G&–ætÆVæwF‚†u7G&–æuf#B’ÒeÒÒTõ3°¢7G&–ætVæB†u7G&–æuf#2ÂuFW‡Eõ76R“°¢7G&–ætVæB†u7G&–æuf#2Âu7G&–æuf#B“° ¢–b‡D—FVÔ6÷VçBÓÒ¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eô·W'Ef#æE–÷UvçFVEf#%6–æwVÆ"Â'W”ÖVçT6öæf—&ÕW&6†6R“°¢VÇ6P¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eô·W'Ef#æE–÷UvçFVEf#%ÇW&ÂÂ'W”ÖVçT6öæf—&ÕW&6†6R“°¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõf#æE–÷UvçFVEf#$%Â'W”ÖVçT6öæf—&ÕW&6†6R“°¢VÇ6P¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõf#æE–÷UvçFVEf#"Â'W”ÖVçT6öæf—&ÕW&6†6R“°¢Ð¢VÇ6R–b„¤õ•ôäUr„%ô%UEDôâ’¢°¢Æ•4R…4Uõ4TÄT5B“°¢&VÖ÷fUVçF—G”&W''”–6öâ‚“°¢6ÆV%7FEv–æF÷tæDg&ÖUFõG&ç7&VçB…t”åõTåD•E•õ$”4RÂdÅ4R“°¢6ÆV%7FEv–æF÷tæDg&ÖUFõG&ç7&VçB…t”åõTåD•E•ô”åô$rÂdÅ4R“°¢6ÆV%v–æF÷uF–ÆVÖ…t”åõTåD•E•õ$”4R“°¢6ÆV%v–æF÷uF–ÆVÖ…t”åõTåD•E•ô”åô$r“°¢'W”ÖVçU&WGW&åFô—FVÔÆ—7B‡F6´–B“°¢Ð¢Ð§Ð §7FF–2fö–B'W”ÖVçT6öæf—&ÕW&6†6R‡S‚F6´–B§°¢7&VFU–W4æôÖVçUv—F„6ÆÆ&6·2‡F6´–BÂg56†÷'W”ÖVçU–W4æõv–æF÷uFV×ÆFW2ÂÂÂÂÂ2Âg56†÷W&6†6U–W4æôgVæ72“°§Ð §7FF–2fö–B'W”ÖVçUG'”Ö¶UW&6†6R‡S‚F6´–B§°¢3b¦FFÒuF6·5·F6´–EÒæFF° ¢WEv–æF÷uF–ÆVÖ…t”åô•DTÕôÄ•5B“° ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢SbF÷FÄ&ÆÇ2ÒD—FVÔ6÷VçC°¢–b„6†V6´&t†576R‡D—FVÔ–BÂF÷FÄ&ÆÇ2’ÓÒE%TR¢°¢u7V6–Åf%óƒƒBÒD—FVÔ–C°¢u7V6–Åf%óƒƒRÒF÷FÄ&ÆÇ3°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eô·W'DvWGF–æu7F'FVBÂ'W”ÖVçU7V'G&7DÖöæW’“°¢&V6÷&D—FVÕW&6†6R‡F6´–B“°¢Ð¢VÇ6P¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡EôæôÖ÷&U&ööÔf÷%F†—2Â'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uôäõ$ÔÂ¢°¢–b„FD&t—FVÒ‡D—FVÔ–BÂD—FVÔ6÷VçB’ÓÒE%TR¢°¢vWE6WD—FVÔö'F–æVB‡D—FVÔ–BÂdÄuõ4UEô•DTÕôô%D”äTB“°¢&V6÷&D—FVÕW&6†6R‡F6´–B“°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eô†W&U–÷TvõF†æµ–÷RÂ'W”ÖVçU7V'G&7DÖöæW’“°¢Ð¢VÇ6P¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡EôæôÖ÷&U&ööÔf÷%F†—2Â'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÒ¢°¢–b„FD&t—FVÒ‡D—FVÔ–BÂD—FVÔ6÷VçB’ÓÒE%TR¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eô†W&U–÷TvõF†æµ–÷RÂ'W”ÖVçU7V'G&7DÖöæW’“°¢Ð¢VÇ6P¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡EôæôÖ÷&U&ööÔf÷%F†—2Â'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ôDT4õ"¢°¢–b„FV6÷&F–öäFB‡D—FVÔ–B’¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡EõF†æµ–÷T–ÆÅ6VæD—D†öÖRÂ'W”ÖVçU7V'G&7DÖöæW’“°¢Ð¢VÇ6P¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõ76Tf÷%f#gVÆÂÂ'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢Ð¢VÇ6P¢°¢–b„FV6÷&F–öäFB‡D—FVÔ–B’¢°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôDT4õ"¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡EõF†æµ–÷T–ÆÅ6VæD—D†öÖRÂ'W”ÖVçU7V'G&7DÖöæW’“°¢VÇ6RòòÔ%EõE•UôDT4õ# ¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡EõF†æ·4–ÆÅ6VæD—D†öÖRÂ'W”ÖVçU7V'G&7DÖöæW’“°¢Ð¢VÇ6P¢°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂuFW‡Eõ76Tf÷%f#gVÆÂÂ'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢Ð§Ð §7FF–2fö–B'W”ÖVçU7V'G&7DÖöæW’‡S‚F6´–B§°¢3b¦FFÒuF6·5·F6´–EÒæFF° ¢–æ7&VÖVçDvÖU7FB„tÔUõ5DEõ4„õTB“°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢Sb&W''”—FVÒÒvWD&W''”g&öÔ&ÆÂ‡D—FVÔ–B“°¢&VÖ÷fT&t—FVÒ†&W''”—FVÒÂD—FVÔ6÷VçB“°¢Æ•4R…4Uô$är“°¢u7V6–Åf%õ&W7VÇBÒE%TS°¢uF6·5·F6´–EÒægVæ2ÒF6µôW†—D·W'E6†÷gFW%W&6†6S°¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô% ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÐ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ôDT4õ"¢°¢u6fT&Æö6³%G"Óæg&öçF–W"æ&GFÆUö–çG2ÓÒ‡Sb—56†÷FFÓçF÷FÄ6÷7C°¢Æ•4R…4Uõ4„õ“°¢&–çD%Ö÷VçD–äÖöæW”&÷‚…t”åôÔôäU’Âu6fT&Æö6³%G"Óæg&öçF–W"æ&GFÆUö–çG2Â“° ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ôDT4õ"¢uF6·5·F6´–EÒægVæ2ÒF6µõ&WGW&åFô—FVÔÆ—7DgFW$FV6÷&F–öåW&6†6S°¢VÇ6P¢uF6·5·F6´–EÒægVæ2ÒF6µõ&WGW&åFô—FVÔÆ—7DgFW$—FVÕW&6†6S°¢Ð¢VÇ6P¢°¢&VÖ÷fTÖöæW’‚fu6fT&Æö6³G"ÓæÖöæW’Â56†÷FFÓçF÷FÄ6÷7B“°¢Æ•4R…4Uõ4„õ“°¢&–çDÖöæW”Ö÷VçD–äÖöæW”&÷‚…t”åôÔôäU’ÂvWDÖöæW’‚fu6fT&Æö6³G"ÓæÖöæW’’Â“° ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uôäõ$ÔÂ¢uF6·5·F6´–EÒægVæ2ÒF6µõ&WGW&åFô—FVÔÆ—7DgFW$—FVÕW&6†6S°¢VÇ6P¢uF6·5·F6´–EÒægVæ2ÒF6µõ&WGW&åFô—FVÔÆ—7DgFW$FV6÷&F–öåW&6†6S°¢Ð§Ð §7FF–2fö–BF6µõ&WGW&åFô—FVÔÆ—7DgFW$—FVÕW&6†6R‡S‚F6´–B§°¢3b¦FFÒuF6·5·F6´–EÒæFF° ¢–b„¤õ•ôäUr„ô%UEDôâÂ%ô%UEDôâ’¢°¢Sb&VÖ–W$&ÆÇ5FôFBÒD—FVÔ6÷VçBò°¢–b‡&VÖ–W$&ÆÇ5FôFBãÒ¢bb‚„•õ$TÔ”U%ô$ÄÅô$ôåU2ÃÒtTåórbbD—FVÔ–BÓÒ•DTÕõô´Uô$ÄÂ¢ÇÂ„•õ$TÔ”U%ô$ÄÅô$ôåU2ãÒtTåó‚bb„vWD—FVÕö6¶WB‡D—FVÔ–B’ÓÒô4´UEõô´Uô$ÄÅ2’’’¢°¢S3"76Tf–Æ&ÆRÒvWDg&VU76Tf÷$—FVÔ–ä&r„•DTÕõ$TÔ”U%ô$ÄÂ“°¢–b‡76Tf–Æ&ÆRÂ&VÖ–W$&ÆÇ5FôFB¢&VÖ–W$&ÆÇ5FôFBÒ76Tf–Æ&ÆS°¢Ð¢VÇ6P¢°¢&VÖ–W$&ÆÇ5FôFBÒ°¢Ð ¢Æ•4R…4Uõ4TÄT5B“°¢FD&t—FVÒ„•DTÕõ$TÔ”U%ô$ÄÂÂ&VÖ–W$&ÆÇ5FôFB“°¢–b‡&VÖ–W$&ÆÇ5FôFBâ¢°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#Â&VÖ–W$&ÆÇ5FôFBÂ5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂÔ…ô•DTÕôD”t•E2“°¢'W”ÖVçTF—7Æ”ÖW76vR‡F6´–BÂ‡&VÖ–W$&ÆÇ5FôFBãÒ"òuFW‡EõF‡&÷t–å&VÖ–W$&ÆÇ2¢uFW‡EõF‡&÷t–å&VÖ–W$&ÆÂ’Â'W”ÖVçU&WGW&åFô—FVÔÆ—7B“°¢Ð¢VÇ6P¢°¢'W”ÖVçU&WGW&åFô—FVÔÆ—7B‡F6´–B“°¢Ð¢Ð§Ð §7FF–2fö–BF6µõ&WGW&åFô—FVÔÆ—7DgFW$FV6÷&F–öåW&6†6R‡S‚F6´–B§°¢–b„¤õ•ôäUr„ô%UEDôâÂ%ô%UEDôâ’¢°¢Æ•4R…4Uõ4TÄT5B“°¢'W”ÖVçU&WGW&åFô—FVÔÆ—7B‡F6´–B“°¢Ð§Ð §7FF–2fö–BF6µôW†—D·W'E6†÷gFW%W&6†6R‡S‚F6´–B§°¢–b„¤õ•ôäUr„ô%UEDôâÂ%ô%UEDôâ’¢°¢Æ•4R…4Uõ4TÄT5B“°¢6ÆV$F–Æöuv–æF÷tæDg&ÖUFõG&ç7&VçB…t”åôÔU54tRÂdÅ4R“°¢6ÆV%v–æF÷uF–ÆVÖ…t”åôÔU54tR“°¢66†VGVÆT&t6÷•F–ÆVÖFõg&Òƒ“°¢&Vv–äæ÷&ÖÅÆWGFTfFR…ÄUEDU5ôÄÂÂÂÂbÂ$t%ô$Ä4²“°¢uF6·5·F6´–EÒægVæ2ÒF6µôW†—D'W”ÖVçS°¢Ð§Ð §7FF–2fö–B'W”ÖVçU&WGW&åFô—FVÔÆ—7B‡S‚F6´–B§°¢3b¦FFÒuF6·5·F6´–EÒæFF° ¢6ÆV$F–Æöuv–æF÷tæDg&ÖUFõG&ç7&VçB…t”åôÔU54tRÂdÅ4R“°¢&VG&tÆ—7DÖVçR‡DÆ—7EF6´–B“°¢'W”ÖVçU&–çD7W'6÷"‡DÆ—7EF6´–BÂ4ôÄõ$”Eô•DTÕôÄ•5B“°¢WEv–æF÷uF–ÆVÖ…t”åô•DTÕôÄ•5B“°¢WEv–æF÷uF–ÆVÖ…t”åô•DTÕôDU45$•D”ôâ“°¢66†VGVÆT&t6÷•F–ÆVÖFõg&Òƒ“°¢'W”ÖVçTFE67&öÆÄ–æF–6F÷$'&÷w2‚“°¢uF6·5·F6´–EÒægVæ2ÒF6µô'W”ÖVçS°§Ð §7FF–2fö–B'W”ÖVçU&–çD—FVÕVçF—G”æE&–6R‡S‚F6´–B§°¢3b¦FFÒuF6·5·F6´–EÒæFF° ¢f–ÆÅv–æF÷u—†VÄ'VffW"…t”åõTåD•E•õ$”4RÂ•„TÅôd”ÄÂƒ’“°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢Sb&W''”—FVÓ°¢S‚ƒ° ¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#ÂD—FVÔ6÷VçBÂ5E%ô4ôåeôÔôDUôÄTD”äuõ¤U$õ2ÂÔ…ô•DTÕôD”t•E2“°¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡E÷…f#“°¢'W”ÖVçU&–çB…t”åõTåD•E•õ$”4RÂu7G&–æuf#BÂÂÂÂ4ôÄõ$”Eôäõ$ÔÂ“° ¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#ÂD—FVÔ6÷VçBÂ5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂÔ…ô•DTÕôD”t•E2“°¢‚ÒvWE7G&–æu&–v‡DÆ–vå„öfg6WB„dôåEôäõ$ÔÂÂu7G&–æuf#Âc"“°¢'W”ÖVçU&–çB…t”åõTåD•E•õ$”4RÂu7G&–æuf#Â‚ÂÂÂ4ôÄõ$”Eôäõ$ÔÂ“° ¢&W''”—FVÒÒvWD&W''”g&öÔ&ÆÂ‡D—FVÔ–B“°¢FEVçF—G”&W''”–6öâ†&W''”—FVÒ“°¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%¢°¢S‚ƒ°¢S‚'÷FW‡E³eÓ°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#ÂD—FVÔ6÷VçBÂ5E%ô4ôåeôÔôDUôÄTD”äuõ¤U$õ2ÂÔ…ô•DTÕôD”t•E2“°¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡E÷…f#“°¢'W”ÖVçU&–çB…t”åõTåD•E•õ$”4RÂu7G&–æuf#BÂÂÂÂ4ôÄõ$”Eôäõ$ÔÂ“°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†'÷FW‡BÂ56†÷FFÓçF÷FÄ6÷7BÂ5E%ô4ôåeôÔôDUôÄTeEôÄ”tâÂB“°¢7G&–ætVæB†'÷FW‡BÂuFW‡Eô%“°¢‚ÒvWE7G&–æu&–v‡DÆ–vå„öfg6WB„dôåEôäõ$ÔÂÂ'÷FW‡BÂƒ“°¢'W”ÖVçU&–çB…t”åõTåD•E•õ$”4RÂ'÷FW‡BÂ‚ÂÂÂ4ôÄõ$”Eôäõ$ÔÂ“°¢Ð¢VÇ6P¢°¢&–çDÖöæW”Ö÷VçB…t”åõTåD•E•õ$”4RÂ6Æ7VÆFTÖöæW•FW‡D†÷&—¦öçFÅ÷6—F–öâ‡56†÷FFÓçF÷FÄ6÷7B’ÂÂ56†÷FFÓçF÷FÄ6÷7BÂDU…Eõ4´•ôE$r“°¢6öçfW'D–çEFôFV6–ÖÅ7G&–ætâ†u7G&–æuf#ÂD—FVÔ6÷VçBÂ5E%ô4ôåeôÔôDUôÄTD”äuõ¤U$õ2ÂÔ…ô•DTÕôD”t•E2“°¢7G&–ætW‡æEÆ6V†öÆFW'2†u7G&–æuf#BÂuFW‡E÷…f#“°¢'W”ÖVçU&–çB…t”åõTåD•E•õ$”4RÂu7G&–æuf#BÂÂÂÂ4ôÄõ$”Eôäõ$ÔÂ“°¢Ð§Ð §7FF–2fö–BW†—D'W”ÖVçR‡S‚F6´–B§°¢–b‡4Ö'D–æfòæÖ'EG—RÒÔ%EõE•UôµU%@¢bb4Ö'D–æfòæÖ'EG—RÒÔ%EõE•Uô% ¢bb4Ö'D–æfòæÖ'EG—RÒÔ%EõE•Uô%ô•DTÐ¢bb4Ö'D–æfòæÖ'EG—RÒÔ%EõE•Uô%ôDT4õ"¢tf–VÆD6ÆÆ&6²ÒÖ÷7DÆöD†ööµõ&WGW&åFõ6†÷ÖVçS° ¢&Vv–äæ÷&ÖÅÆWGFTfFR…ÄUEDU5ôÄÂÂÂÂbÂ$t%ô$Ä4²“°¢uF6·5·F6´–EÒægVæ2ÒF6µôW†—D'W”ÖVçS°§Ð §7FF–2fö–BF6µôW†—D'W”ÖVçR‡S‚F6´–B§°¢–b‚uÆWGFTfFRæ7F—fR¢°¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%B¢°¢òò·W'B6†÷†2æòÖöæW’ô%Æ&VÂFò&VÖ÷fP¢Ð¢VÇ6R–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô% ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÐ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ôDT4õ"¢&VÖ÷fT%Æ&VÄö&¦V7B‚“°¢VÇ6P¢&VÖ÷fTÖöæW”Æ&VÄö&¦V7B‚“°¢'W”ÖVçTg&VTÖVÖ÷'’‚“°¢6WDÖ–ä6ÆÆ&6³"„4#%õ&WGW&åFôf–VÆB“° ¢–b‡4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•UôµU%@¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô% ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ô•DTÐ¢ÇÂ4Ö'D–æfòæÖ'EG—RÓÒÔ%EõE•Uô%ôDT4õ"¢°¢VæÆö6µÆ–W$f–VÆD6öçG&öÇ2‚“°¢–b‡4Ö'D–æfòæ6ÆÆ&6²¢4Ö'D–æfòæ6ÆÆ&6²‚“°¢Ð ¢FW7G&÷•F6²‡F6´–B“°¢Ð§Ð §7FF–2fö–B6ÆV$—FVÕW&6†6W2‡fö–B§°¢5W&6†6T†—7F÷'”–BÒ°¢ÖV×6WB†tÖ'EW&6†6T†—7F÷'’ÂÂ6—¦Vöb†tÖ'EW&6†6T†—7F÷'’’“°§Ð §7FF–2fö–B&V6÷&D—FVÕW&6†6R‡S‚F6´–B§°¢3b¦FFÒuF6·5·F6´–EÒæFF° ¢Sb“° ¢f÷"†’Ò²’Â%$•ô4õTåB†tÖ'EW&6†6T†—7F÷'’“²’²²¢°¢–b†tÖ'EW&6†6T†—7F÷'•¶•Òæ—FVÔ–BÓÒD—FVÔ–BbbtÖ'EW&6†6T†—7F÷'•¶•ÒçVçF—G’Ò¢°¢–b†tÖ'EW&6†6T†—7F÷'•¶•ÒçVçF—G’²D—FVÔ6÷VçBâ#SR¢tÖ'EW&6†6T†—7F÷'•¶•ÒçVçF—G’Ò#SS°¢VÇ6P¢tÖ'EW&6†6T†—7F÷'•¶•ÒçVçF—G’³ÒD—FVÔ6÷VçC°¢&WGW&ã°¢Ð¢Ð ¢–b‡5W&6†6T†—7F÷'”–BÂ%$•ô4õTåB†tÖ'EW&6†6T†—7F÷'’’¢°¢tÖ'EW&6†6T†—7F÷'•·5W&6†6T†—7F÷'”–EÒæ—FVÔ–BÒD—FVÔ–C°¢tÖ'EW&6†6T†—7F÷'•·5W&6†6T†—7F÷'”–EÒçVçF—G’ÒD—FVÔ6÷VçC°¢5W&6†6T†—7F÷'”–B²³°¢Ð§Ð ¢7VæFVbD—FVÔ6÷Vç@¢7VæFVbD—FVÔ–@¢7VæFVbDÆ—7EF6´–@¢7VæFVbD6ÆÆ&6´†¢7VæFVbD6ÆÆ&6´Æð §fö–B7&VFUö¶VÖ'DÖVçR†6öç7BSb¦—FV×4f÷%6ÆR§°¢7&VFU6†÷ÖVçR„Ô%EõE•Uôäõ$ÔÂ“°¢6WE6†÷—FV×4f÷%6ÆR†—FV×4f÷%6ÆR“°¢6ÆV$—FVÕW&6†6W2‚“°¢6WE6†÷ÖVçT6ÆÆ&6²…67&—D6öçFW‡EôVæ&ÆR“°§Ð §fö–B7&VFTFV6÷&F–öå6†÷ÖVçR†6öç7BSb¦—FV×4f÷%6ÆR§°¢7&VFU6†÷ÖVçR„Ô%EõE•UôDT4õ"“°¢6WE6†÷—FV×4f÷%6ÆR†—FV×4f÷%6ÆR“°¢6WE6†÷ÖVçT6ÆÆ&6²…67&—D6öçFW‡EôVæ&ÆR“°§Ð §fö–B7&VFTFV6÷&F–öå6†÷$ÖVçR†6öç7BSb¦—FV×4f÷%6ÆR§°¢7&VFU6†÷ÖVçR„Ô%EõE•UôDT4õ#"“°¢6WE6†÷—FV×4f÷%6ÆR†—FV×4f÷%6ÆR“°¢6WE6†÷ÖVçT6ÆÆ&6²…67&—D6öçFW‡EôVæ&ÆR“°§Ð §7FF–2Uu$ÕôDDSb4%—FVÔÆ—7E³3%ÒÒ³Ó° §7FF–2fö–B6WD%6†÷—FV×2†6öç7B7G'V7B%6†÷VçG'’¦VçG&–W2§°¢Sb’Ò°¢4%6†÷VçG&–W2ÒVçG&–W3°¢v†–ÆR†VçG&–W5¶•Òæ—FVÒÒ•DTÕôäôäRbb’Â%$•ô4õTåB‡4%—FVÔÆ—7B’Ò¢°¢4%—FVÔÆ—7E¶•ÒÒVçG&–W5¶•Òæ—FVÓ°¢’²³°¢Ð¢4%—FVÔÆ—7E¶•ÒÒ•DTÕôäôäS°¢6WE6†÷—FV×4f÷%6ÆR‡4%—FVÔÆ—7B“°§Ð §7FF–2fö–B7&VFT%6†÷6öÖÖöâ‡S‚Ö'EG—RÂ6öç7B7G'V7B%6†÷VçG'’¦VçG&–W2§°¢S‚F6´–C°¢3b¦FF° ¢Æö6µÆ–W$f–VÆD6öçG&öÇ2‚“°¢4Ö'D–æfòæÖ'EG—RÒÖ'EG—S°¢6WD%6†÷—FV×2†VçG&–W2“°¢6WE6†÷ÖVçT6ÆÆ&6²…67&—D6öçFW‡EôVæ&ÆR“° ¢F6´–BÒ7&VFUF6²…F6µõ6†÷ÖVçRÂ‚“°¢FFÒuF6·5·F6´–EÒæFF°¢FF³…ÒÒ‡S3"”4#%ô–æ—D'W”ÖVçRãâc°¢FF³•ÒÒ‡S3"”4#%ô–æ—D'W”ÖVçS°¢uF6·5·F6´–EÒægVæ2ÒF6µôvõFô'W”÷%6VÆÄÖVçS°¢fFU67&VVâ„dDUõDõô$Ä4²Â“°§Ð §fö–B7&VFT%f—FÖ–å6†÷‡fö–B’²7&VFT%6†÷6öÖÖöâ„Ô%EõE•Uô%Â4%f—FÖ–å6†÷VçG&–W2“²Ð§fö–B7&VFT%†öÆD—FVÕ6†÷‡fö–B’²7&VFT%6†÷6öÖÖöâ„Ô%EõE•Uô%ô•DTÒÂ4%†öÆD—FVÕ6†÷VçG&–W2“²Ð§fö–B7&VFT%FV6÷%6†÷‡fö–B’²7&VFT%6†÷6öÖÖöâ„Ô%EõE•Uô%ôDT4õ"Â4%FV6÷#6†÷VçG&–W2“²Ð§fö–B7&VFT%FV6÷%6†÷"‡fö–B’²7&VFT%6†÷6öÖÖöâ„Ô%EõE•Uô%ôDT4õ"Â4%FV6÷#%6†÷VçG&–W2“²Ð§fö–B7&VFT%ö¶T&ÆÅ6†÷‡fö–B’²7&VFT%6†÷6öÖÖöâ„Ô%EõE•Uô%Â4%ö¶T&ÆÅ6†÷VçG&–W2“²Ð§fö–B7&VFT%†öÆD—FVÕ6†÷"‡fö–B’²7&VFT%6†÷6öÖÖöâ„Ô%EõE•Uô%ô•DTÒÂ4%†öÆD—FVÕ6†÷VçG&–W3"“²Ð§fö–B7&VFT%÷vW%6†÷‡fö–B’²7&VFT%6†÷6öÖÖöâ„Ô%EõE•Uô%ô•DTÒÂ4%÷vW%6†÷VçG&–W2“²Ð §7FF–26öç7BSb4·W'D&ÆÅ6†÷—FV×5µÒÐ§°¢•DTÕôÄõdUô$ÄÂÀ¢•DTÕôÅU$Uô$ÄÂÀ¢•DTÕôe$”TäEô$ÄÂÀ¢•DTÕô„Te•ô$ÄÂÀ¢•DTÕôÔôôåô$ÄÂÀ¢•DTÕôd5Eô$ÄÂÀ¢•DTÕôÄUdTÅô$ÄÂÀ¢•DTÕôäôäRÀ§Ó° §fö–B7&VFT·W'D&ÆÅ6†÷‡fö–B§°¢S‚F6´–C°¢3b¦FF° ¢Æö6µÆ–W$f–VÆD6öçG&öÇ2‚“°¢4Ö'D–æfòæÖ'EG—RÒÔ%EõE•UôµU%C°¢6WE6†÷—FV×4f÷%6ÆR‡4·W'D&ÆÅ6†÷—FV×2“°¢6ÆV$—FVÕW&6†6W2‚“°¢6WE6†÷ÖVçT6ÆÆ&6²…67&—D6öçFW‡EôVæ&ÆR“° ¢F6´–BÒ7&VFUF6²…F6µõ6†÷ÖVçRÂ‚“°¢FFÒuF6·5·F6´–EÒæFF°¢FF³…ÒÒ‡S3"”4#%ô–æ—D'W”ÖVçRãâc°¢FF³•ÒÒ‡S3"”4#%ô–æ—D'W”ÖVçS°¢uF6·5·F6´–EÒægVæ2ÒF6µôvõFô'W”÷%6VÆÄÖVçS°¢fFU67&VVâ„dDUõDõô$Ä4²Â“°§Ð