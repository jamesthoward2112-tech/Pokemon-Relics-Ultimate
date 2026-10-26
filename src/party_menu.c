Warning: truncated output (original token count: 70220)
Total output lines: 8541

#include "global.h"
#include "malloc.h"
#include "battle.h"
#include "challenge_menu.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_gfx_sfx_util.h"
#include "battle_interface.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "battle_pyramid_bag.h"
#include "bg.h"
#include "contest.h"
#include "data.h"
#include "decompress.h"
#include "easy_chat.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "evolution_scene.h"
#include "field_control_avatar.h"
#include "field_effect.h"
#include "field_move.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_specials.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff.h"
#include "fldeff_misc.h"
#include "follower_npc.h"
#include "frontier_util.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "item_menu.h"
#include "item_use.h"
#include "caps.h"
#include "link.h"
#include "link_rfu.h"
#include "mail.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "menu_specialized.h"
#include "metatile_behavior.h"
#include "move_relearner.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "player_pc.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_jump.h"
#include "pokemon_storage_system.h"
#include "pokemon_summary_screen.h"
#include "pokerus.h"
#include "region_map.h"
#include "reshow_battle_screen.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "start_menu.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "trade.h"
#include "union_room.h"
#include "window.h"
#include "constants/battle.h"
#include "constants/battle_frontier.h"
#include "constants/field_effects.h"
#include "constants/field_move.h"
#include "constants/form_change_types.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/party_menu.h"
#include "constants/rgb.h"
#include "constants/songs.h"

enum {
    MENU_SUMMARY,
    MENU_SWITCH,
    MENU_CANCEL1,
    MENU_ITEM,
    MENU_GIVE,
    MENU_TAKE_ITEM,
    MENU_MOVE_ITEM,
    MENU_MAIL,
    MENU_TAKE_MAIL,
    MENU_READ,
    MENU_CANCEL2,
    MENU_SHIFT,
    MENU_SEND_OUT,
    MENU_ENTER,
    MENU_NO_ENTRY,
    MENU_STORE,
    MENU_REGISTER,
    MENU_TRADE1,
    MENU_TRADE2,
    MENU_LEVEL_UP_MOVES,
    MENU_EGG_MOVES,
    MENU_TM_MOVES,
    MENU_TUTOR_MOVES,
    MENU_SUB_MOVES,
    MENU_TOSS,
    MENU_CATALOG_BULB,
    MENU_CATALOG_OVEN,
    MENU_CATALOG_WASHING,
    MENU_CATALOG_FRIDGE,
    MENU_CATALOG_FAN,
    MENU_CATALOG_MOWER,
    MENU_CHANGE_FORM,
    MENU_CHANGE_ABILITY,
    MENU_PKMN_FOLLOWER,
    MENU_FIELD_MOVES
};

// IDs for the action lists that appear when a party mon is selected
enum {
    ACTIONS_NONE,
    ACTIONS_SWITCH,
    ACTIONS_SHIFT,
    ACTIONS_SEND_OUT,
    ACTIONS_ENTER,
    ACTIONS_NO_ENTRY,
    ACTIONS_STORE,
    ACTIONS_SUMMARY_ONLY,
    ACTIONS_ITEM,
    ACTIONS_MAIL,
    ACTIONS_REGISTER,
    ACTIONS_TRADE,
    ACTIONS_SPIN_TRADE,
    ACTIONS_MOVES_SUB,
    ACTIONS_TAKEITEM_TOSS,
    ACTIONS_ROTOM_CATALOG,
    ACTIONS_ZYGARDE_CUBE,
};

enum {
    PARTY_BOX_LEFT_COLUMN,
    PARTY_BOX_RIGHT_COLUMN,
};

enum {
    TAG_POKEBALL = 1200,
    TAG_POKEBALL_SMALL,
    TAG_STATUS_ICONS,
};

#define TAG_HELD_ITEM 55120

#define PARTY_PAL_SELECTED     (1 << 0)
#define PARTY_PAL_FAINTED      (1 << 1)
#define PARTY_PAL_TO_SWITCH    (1 << 2)
#define PARTY_PAL_MULTI_ALT    (1 << 3)
#define PARTY_PAL_SWITCHING    (1 << 4)
#define PARTY_PAL_TO_SOFTBOIL  (1 << 5)
#define PARTY_PAL_NO_MON       (1 << 6)
#define PARTY_PAL_UNUSED       (1 << 7)

#define MENU_DIR_DOWN     1
#define MENU_DIR_UP      -1
#define MENU_DIR_RIGHT    2
#define MENU_DIR_LEFT    -2

enum {
    // Window ids 0-5 are implicitly assigned to each party Pokémon in InitPartyMenuBoxes
    WIN_MSG = PARTY_SIZE,
};

struct PartyMenuBoxInfoRects
{
    void (*blitFunc)(u8, u8, u8, u8, u8, bool8);
    u8 dimensions[24];
    u8 descTextLeft;
    u8 descTextTop;
    u8 descTextWidth;
    u8 descTextHeight;
};

struct PartyMenuInternal
{
    TaskFunc task;
    MainCallback exitCallback;
    u32 chooseHalf:1;
    u32 lastSelectedSlot:3;  // Used to return to same slot when going left/right bewtween columns
    u32 spriteIdConfirmPokeball:7;
    u32 spriteIdCancelPokeball:7;
    u32 messageId:14;
    u8 windowId[3];
    u8 actions[8];
    u8 numActions;
    // In vanilla Emerald, only the first 0xB0 hwords (0x160 bytes) are actually used.
    // However, a full 0x100 hwords (0x200 bytes) are allocated.
    // It is likely that the 0x160 value used below is a constant defined by
    // bin2c, the utility used to encode the compressed palette data.
    u16 palBuffer[BG_PLTT_SIZE / sizeof(u16)];
    s16 data[16];
};

struct PartyMenuBox
{
    const struct PartyMenuBoxInfoRects *infoRects;
    const u8 *spriteCoords;
    u8 windowId;
    u8 monSpriteId;
    u8 itemSpriteId;
    u8 pokeballSpriteId;
    u8 statusSpriteId;
};

// EWRAM vars
static EWRAM_DATA struct PartyMenuInternal *sPartyMenuInternal = NULL;
EWRAM_DATA struct PartyMenu gPartyMenu = {0};
static EWRAM_DATA struct PartyMenuBox *sPartyMenuBoxes = NULL;
static EWRAM_DATA u8 *sPartyBgGfxTilemap = NULL;
static EWRAM_DATA u8 *sPartyBgTilemapBuffer = NULL;
EWRAM_DATA bool8 gPartyMenuUseExitCallback = 0;
EWRAM_DATA u8 gSelectedMonPartyId = 0;
EWRAM_DATA MainCallback gPostMenuFieldCallback = NULL;
static EWRAM_DATA u16 *sSlot1TilemapBuffer = 0; // for switching party slots
static EWRAM_DATA u16 *sSlot2TilemapBuffer = 0; //
EWRAM_DATA u8 gSelectedOrderFromParty[MAX_FRONTIER_PARTY_SIZE] = {0};
static EWRAM_DATA u16 sPartyMenuItemId = 0;
EWRAM_DATA u8 gBattlePartyCurrentOrder[PARTY_SIZE / 2] = {0}; // bits 0-3 are the current pos of Slot 1, 4-7 are Slot 2, and so on
static EWRAM_DATA u8 sInitialLevel = 0;
static EWRAM_DATA u8 sFinalLevel = 0;

// IWRAM common
COMMON_DATA void (*gItemUseCB)(u8, TaskFunc) = NULL;

static void ResetPartyMenu(void);
static void CB2_InitPartyMenu(void);
static void CB2_ReloadPartyMenu(void);
static bool8 ShowPartyMenu(void);
static bool8 ReloadPartyMenu(void);
static void SetPartyMonsAllowedInMinigame(void);
static void ExitPartyMenu(void);
static bool8 AllocPartyMenuBg(void);
static bool8 AllocPartyMenuBgGfx(void);
static void InitPartyMenuWindows(u8);
static void LoadPartyMenuWindows(void);
static void InitPartyMenuBoxes(u8);
static void LoadPartyMenuBoxes(u8);
static void LoadPartyMenuPokeballGfx(void);
static bool8 CreatePartyMonSpritesLoop(void);
static bool8 RenderPartyMenuBoxes(void);
static void CreateCancelConfirmPokeballSprites(void);
static void CreateCancelConfirmWindows(u8);
static void Task_ExitPartyMenu(u8);
static void FreePartyPointers(void);
static void PartyPaletteBufferCopy(u8);
static void DisplayPartyPokemonDataForMultiBattle(u8);
static void LoadPartyBoxPalette(struct PartyMenuBox *, u8);
static void DrawEmptySlot(u8 windowId);
static void DisplayPartyPokemonDataForRelearner(u8);
static void DisplayPartyPokemonDataForContest(u8);
static void DisplayPartyPokemonDataForChooseHalf(u8);
static void DisplayPartyPokemonDataForWirelessMinigame(u8);
static void DisplayPartyPokemonDataForBattlePyramidHeldItem(u8);
static bool8 DisplayPartyPokemonDataForMoveTutorOrEvolutionItem(u8);
static void DisplayPartyPokemonData(u8);
static void DisplayPartyPokemonNickname(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonLevelCheck(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonGenderNidoranCheck(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonHPCheck(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonMaxHPCheck(struct Pokemon *, struct PartyMenuBox *, u8);
static void DisplayPartyPokemonHPBarCheck(struct Pokemon *, struct PartyMenuBox *);
static void DisplayPartyPokemonDescriptionText(u8, struct PartyMenuBox *, u8);
static bool8 IsMonAllowedInMinigame(u8);
static void DisplayPartyPokemonDataToTeachMove(u8, enum Move);
static enum CanMoveBeLearned CanTeachMove(struct Pokemon *, enum Move);
static void DisplayPartyPokemonBarDetail(u8, const u8 *, u8, const u8 *);
static void DisplayPartyPokemonBarDetailToFit(u8 windowId, const u8 *str, u8 color, const u8 *align, u32 width);
static void DisplayPartyPokemonLevel(u8, struct PartyMenuBox *);
static void DisplayPartyPokemonGender(u8, u16, u8 *, struct PartyMenuBox *);
static void DisplayPartyPokemonHP(u16 hp, u16 maxHp, struct PartyMenuBox *menuBox);
static void DisplayPartyPokemonMaxHP(u16, struct PartyMenuBox *);
static void DisplayPartyPokemonHPBar(u16, u16, struct PartyMenuBox *);
static void CreatePartyMonIconSpriteParameterized(u16 species, u32 pid, bool32 isEgg, struct PartyMenuBox *menuBox, u8 priority);
static void CreatePartyMonHeldItemSpriteParameterized(u16, enum Item, struct PartyMenuBox *);
static void CreatePartyMonPokeballSpriteParameterized(u16, struct PartyMenuBox *);
static void CreatePartyMonStatusSpriteParameterized(u16, u8, struct PartyMenuBox *);
// These next 4 functions are essentially redundant with the above 4
// The only difference is that rather than receive the data directly they retrieve it from the mon struct
static void CreatePartyMonHeldItemSprite(struct Pokemon *, struct PartyMenuBox *);
static void CreatePartyMonPokeballSprite(struct Pokemon *, struct PartyMenuBox *);
static void CreatePartyMonIconSprite(struct Pokemon *, struct PartyMenuBox *, u32);
static void CreatePartyMonStatusSprite(struct Pokemon *, struct PartyMenuBox *);
static u8 CreateSmallPokeballButtonSprite(u8, u8);
static void DrawCancelConfirmButtons(void);
static u8 CreatePokeballButtonSprite(u8, u8);
static void AnimateSelectedPartyIcon(u8, u8);
static void PartyMenuStartSpriteAnim(u8, u8);
static u8 GetPartyBoxPaletteFlags(u8, u8);
static bool8 PartyBoxPal_ParnterOrDisqualifiedInArena(u8);
static u8 GetPartyIdFromBattleSlot(u8);
static void Task_ClosePartyMenuAndSetCB2(u8);
static void UpdatePartyToFieldOrder(void);
static void MoveCursorToConfirm(void);
static void HandleChooseMonCancel(u8, s8 *);
static void HandleChooseMonSelection(u8, s8 *);
static u16 PartyMenuButtonHandler(s8 *);
static s8 *GetCurrentPartySlotPtr(void);
static bool8 IsSelectedMonNotEgg(u8 *);
static bool8 DoesSelectedMonKnowHM(u8 *);
static void PartyMenuRemoveWindow(u8 *);
static void CB2_SetUpExitToBattleScreen(void);
static void Task_ClosePartyMenuAfterText(u8);
static void TryTutorSelectedMon(u8);
static void TryGiveMailToSelectedMon(u8);
static void TryGiveItemOrMailToSelectedMon(u8);
static void SwitchSelectedMons(u8);
static void TryEnterMonForMinigame(u8, u8);
static void Task_TryCreateSelectionWindow(u8);
static void FinishTwoMonAction(u8);
static void CancelParticipationPrompt(u8);
static bool8 DisplayCancelChooseMonYesNo(u8);
static const u8 *GetFacilityCancelString(void);
static void Task_CancelChooseMonYesNo(u8);
static void PartyMenuDisplayYesNoMenu(void);
static void Task_HandleCancelChooseMonYesNoInput(u8);
static void Task_ReturnToChooseMonAfterText(u8);
static void UpdateCurrentPartySelection(s8 *, s8);
static void UpdatePartySelectionSingleLayout(s8 *, s8);
static void UpdatePartySelectionDoubleLayout(s8 *, s8);
static s8 GetNewSlotDoubleLayout(s8, s8);
static void PrintMessage(const u8 *);
static void Task_PrintAndWaitForText(u8);
static bool16 IsMonAllowedInPokemonJump(struct Pokemon *);
static bool16 IsMonAllowedInDodrioBerryPicking(struct Pokemon *);
static void Task_CancelParticipationYesNo(u8);
static void Task_HandleCancelParticipationYesNoInput(u8);
static bool8 ShouldUseChooseMonText(void);
static void SetPartyMonFieldSelectionActions(struct Pokemon *, u8);
static void SetPartyMonLearnMoveSelectionActions(struct Pokemon*, u8);
static u8 GetPartyMenuActionsTypeInBattle(struct Pokemon *);
static u8 GetPartySlotEntryStatus(s8);
static void Task_UpdateHeldItemSprite(u8);
static void Task_HandleSelectionMenuInput(u8);
static void CB2_ShowPokemonSummaryScreen(void);
static void UpdatePartyToBattleOrder(void);
static void SlidePartyMenuBoxOneStep(u8);
static void Task_SlideSelectedSlotsOffscreen(u8);
static void SwitchPartyMon(void);
static void Task_SlideSelectedSlotsOnscreen(u8);
static void CB2_SelectBagItemToGive(void);
static void CB2_GiveHoldItem(void);
static void CB2_WriteMailToGiveMon(void);
static void Task_SwitchHoldItemsPrompt(u8);
static void Task_GiveHoldItem(u8);
static void Task_SwitchItemsYesNo(u8);
static void Task_HandleSwitchItemsYesNoInput(u8);
static void Task_WriteMailToGiveMonAfterText(u8);
static void CB2_ReturnToPartyMenuFromWritingMail(void);
static void Task_DisplayGaveMailFromPartyMessage(u8);
static void UpdatePartyMonHeldItemSprite(struct Pokemon *, struct PartyMenuBox *);
static void Task_TossHeldItemYesNo(u8 taskId);
static void Task_HandleTossHeldItemYesNoInput(u8);
static void Task_TossHeldItem(u8);
static void CB2_ReadHeldMail(void);
static void CB2_ReturnToPartyMenuFromReadingMail(void);
static void Task_SendMailToPCYesNo(u8);
static void Task_HandleSendMailToPCYesNoInput(u8);
static void Task_LoseMailMessageYesNo(u8);
static void Task_HandleLoseMailMessageYesNoInput(u8);
static bool8 TrySwitchInPokemon(void);
static void Task_SpinTradeYesNo(u8);
static void Task_HandleSpinTradeYesNoInput(u8);
static void Task_CancelAfterAorBPress(u8);
static void DisplayFieldMoveExitAreaMessage(u8);
static void DisplayCantUseFlashMessage(void);
static void DisplayCantUseSurfMessage(void);
static void Task_FieldMoveExitAreaYesNo(u8);
static void Task_HandleFieldMoveExitAreaYesNoInput(u8);
static void Task_FieldMoveWaitForFade(u8);
static u16 GetFieldMoveMonSpecies(void);
static void UpdatePartyMonHPBar(u8, struct Pokemon *);
static void SpriteCB_UpdatePartyMonIcon(struct Sprite *);
static void SpriteCB_BouncePartyMonIcon(struct Sprite *);
static void ShowOrHideHeldItemSprite(enum Item, struct PartyMenuBox *);
static void CreateHeldItemSpriteForTrade(u8, bool8);
static void SpriteCB_HeldItem(struct Sprite *);
static void SetPartyMonAilmentGfx(struct Pokemon *, struct PartyMenuBox *);
static void UpdatePartyMonAilmentGfx(u8, struct PartyMenuBox *);
static u8 GetPartyLayoutFromBattleType(void);
static void Task_SetSacredAshCB(u8);
static void CB2_ReturnToBagMenu(void);
static void Task_DisplayHPRestoredMessage(u8);
static u16 ItemEffectToMonEv(struct Pokemon *, u8);
static void ItemEffectToStatString(u8, u8 *);
static void ReturnToUseOnWhichMon(u8);
static void SetSelectedMoveForItem(u8);
static void TryUseItemOnMove(u8);
static void Task_LearnedMove(u8);
static void Task_ReplaceMoveYesNo(u8);
static void Task_DoLearnedMoveFanfareAfterText(u8);
static void Task_LearnNextMoveOrClosePartyMenu(u8);
static void Task_TryLearningNextMove(u8);
static void Task_HandleReplaceMoveYesNoInput(u8);
static void Task_ShowSummaryScreenToForgetMove(u8);
static void StopLearningMovePrompt(u8);
static void CB2_ShowSummaryScreenToForgetMove(void);
static void CB2_ReturnToPartyMenuWhileLearningMove(void);
static void Task_ReturnToPartyMenuWhileLearningMove(u8);
static void DisplayPartyMenuForgotMoveMessage(u8);
static void Task_PartyMenuReplaceMove(u8);
static void Task_HandleStopLearningMove(u8 taskId);
static void Task_StopLearningMoveYesNo(u8);
static void Task_HandleStopLearningMoveYesNoInput(u8);
static void Task_TryLearningNextMoveAfterText(u8);
static void BufferMonStatsToTaskData(struct Pokemon *, s16 *);
static void UpdateMonDisplayInfoAfterRareCandy(u8, struct Pokemon *);
static void Task_DisplayLevelUpStatsPg1(u8);
static void DisplayLevelUpStatsPg1(u8);
static void Task_DisplayLevelUpStatsPg2(u8);
static void DisplayLevelUpStatsPg2(u8);
static void Task_TryLearnNewMoves(u8);
static void PartyMenuTryEvolution(u8);
static void DisplayMonNeedsToReplaceMove(u8);
static void DisplayMonLearnedMove(u8, u16);
static void UseSacredAsh(u8);
static void Task_SacredAshLoop(u8);
static void Task_SacredAshDisplayHPRestored(u8);
static void GiveItemOrMailToSelectedMon(u8);
static void DisplayItemMustBeRemovedFirstMessage(u8);
static void Task_SwitchItemsFromBagYesNo(u8);
static void CB2_WriteMailToGiveMonFromBag(void);
static void GiveItemToSelectedMon(u8);
static void Task_UpdateHeldItemSpriteAndClosePartyMenu(u8);
static void CB2_ReturnToPartyOrBagMenuFromWritingMail(void);
static bool8 ReturnGiveItemToBagOrPC(enum Item);
static void Task_DisplayGaveMailFromBagMessage(u8);
static void Task_HandleSwitchItemsFromBagYesNoInput(u8);
static void Task_ValidateChosenHalfParty(u8);
static bool8 GetBattleEntryEligibility(struct Pokemon *);
static bool8 HasPartySlotAlreadyBeenSelected(u8);
static u8 GetBattleEntryLevelCap(void);
static u8 GetMaxBattleEntries(void);
static u8 GetMinBattleEntries(void);
static void Task_ContinueChoosingHalfParty(u8);
static void BufferBattlePartyOrder(u8 *, bool8);
static void BufferBattlePartyOrderBySide(u8 *, u8, enum BattlerId);
static void Task_InitMultiPartnerPartySlideIn(u8);
static void Task_MultiPartnerPartySlideIn(u8);
static void SlideMultiPartyMenuBoxSpritesOneStep(u8);
static void Task_WaitAfterMultiPartnerPartySlideIn(u8);
static void BufferMonSelection(void);
static void Task_PartyMenuWaitForFade(u8 taskId);
static void Task_ChooseContestMon(u8 taskId);
static void CB2_ChooseContestMon(void);
static void Task_ChoosePartyMon(u8 taskId);
static void Task_ChooseMonForMoveRelearner(u8);
static void CB2_ChooseMonForMoveRelearner(void);
static void Task_BattlePyramidChooseMonHeldItems(u8);
static void ShiftMoveSlot(struct BoxPokemon *, u8, u8);
static void BlitBitmapToPartyWindow_LeftColumn(u8, u8, u8, u8, u8, bool8);
static void BlitBitmapToPartyWindow_RightColumn(u8, u8, u8, u8, u8, bool8);
static void CursorCb_Summary(u8);
static void CursorCb_Switch(u8);
static void CursorCb_Cancel1(u8);
static void CursorCb_Item(u8);
static void CursorCb_Give(u8);
static void CursorCb_TakeItem(u8);
static void CursorCb_MoveItem(u8);
static void CursorCb_Mail(u8);
static void CursorCb_Read(u8);
static void CursorCb_TakeMail(u8);
static void CursorCb_Cancel2(u8);
static void CursorCb_SendMon(u8);
static void CursorCb_Enter(u8);
static void CursorCb_NoEntry(u8);
static void CursorCb_Store(u8);
static void CursorCb_Register(u8);
static void CursorCb_Trade1(u8);
static void CursorCb_Trade2(u8);
static void CursorCb_Toss(u8);
static void CursorCb_FieldMove(u8);
static void CursorCb_ChangeLevelUpMoves(u8);
static void CursorCb_ChangeEggMoves(u8);
static void CursorCb_ChangeTMMoves(u8);
static void CursorCb_ChangeTutorMoves(u8);
static void CursorCb_LearnMovesSubMenu(u8);
static void CursorCb_CatalogBulb(u8);
static void CursorCb_CatalogOven(u8);
static void CursorCb_CatalogWashing(u8);
static void CursorCb_CatalogFridge(u8);
static void CursorCb_CatalogFan(u8);
static void CursorCb_CatalogMower(u8);
static void CursorCb_ChangeForm(u8);
static void CursorCb_ChangeAbility(u8);
static void CursorCb_PkmnFollower(u8);
void TryItemHoldFormChange(struct Pokemon *mon, s8 slotId);
static void ShowMoveSelectWindow(u8 slot);
static void Task_HandleWhichMoveInput(u8 taskId);
static void Task_HideFollowerNPCForTeleport(u8);
static void FieldCallback_RockClimb(void);
static void Task_FirstBattleEnterParty_WaitFadeIn(u8 taskId);
static void Task_FirstBattleEnterParty_DarkenScreen(u8 taskId);
static void Task_FirstBattleEnterParty_WaitDarken(u8 taskId);
static void Task_FirstBattleEnterParty_CreatePrinter(u8 taskId);
static void Task_FirstBattleEnterParty_RunPrinterMsg1(u8 taskId);
static void Task_FirstBattleEnterParty_LightenFirstMonIcon(u8 taskId);
static void Task_FirstBattleEnterParty_WaitLightenFirstMonIcon(u8 taskId);
static void Task_FirstBattleEnterParty_StartPrintMsg2(u8 taskId);
static void Task_FirstBattleEnterParty_RunPrinterMsg2(u8 taskId);
static void Task_FirstBattleEnterParty_FadeNormal(u8 taskId);
static void Task_FirstBattleEnterParty_WaitFadeNormal(u8 taskId);

static const u8 sText_askText[] = _("Would you like to change {STR_VAR_1}'s\nability to {STR_VAR_2}?");
static const u8 sText_doneText[] = _("{STR_VAR_1}'s ability became\n{STR_VAR_2}!{PAUSE_UNTIL_PRESS}");
static const u8 sText_BasePointsResetToZero[] = _("{STR_VAR_1}'s base points\nwere all reset to zero!{PAUSE_UNTIL_PRESS}");
static const u8 sText_CannotSendMonToBoxHM[] = _("Cannot send that mon to the box,\nbecause it knows a HM move.{PAUSE_UNTIL_PRESS}");
static const u8 sText_CannotSendMonToBoxPartner[] = _("Cannot send a mon that doesn't\nbelong to you to the box.{PAUSE_UNTIL_PRESS}");

// static const data
#include "data/party_menu.h"

// code
static void InitPartyMenu(u8 menuType, u8 layout, u8 partyAction, bool8 keepCursorPos, u8 messageId, TaskFunc task, MainCallback callback)
{
    u16 i;

    ResetPartyMenu();
    sPartyMenuInternal = Alloc(sizeof(struct PartyMenuInternal));
    if (sPartyMenuInternal == NULL)
    {
        SetMainCallback2(callback);
    }
    else
    {
        gPartyMenu.menuType = menuType;
        gPartyMenu.exitCallback = callback;
        gPartyMenu.action = partyAction;
        sPartyMenuInternal->messageId = messageId;
        sPartyMenuInternal->task = task;
        sPartyMenuInternal->exitCallback = NULL;
        sPartyMenuInternal->lastSelectedSlot = 0;
        sPartyMenuInternal->spriteIdConfirmPokeball = 0x7F;
        sPartyMenuInternal->spriteIdCancelPokeball = 0x7F;

        if (menuType == PARTY_MENU_TYPE_CHOOSE_HALF)
            sPartyMenuInternal->chooseHalf = TRUE;
        else
            sPartyMenuInternal->chooseHalf = FALSE;

        if (layout != KEEP_PARTY_LAYOUT)
            gPartyMenu.layout = layout;

        for (i = 0; i < ARRAY_COUNT(sPartyMenuInternal->data); i++)
            sPartyMenuInternal->data[i] = 0;
        for (i = 0; i < ARRAY_COUNT(sPartyMenuInternal->windowId); i++)
            sPartyMenuInternal->windowId[i] = WINDOW_NONE;

        if (!keepCursorPos)
            gPartyMenu.slotId = 0;
        else if (gPartyMenu.slotId > PARTY_SIZE - 1 || GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES) == SPECIES_NONE)
            gPartyMenu.slotId = 0;

        if (gPlayerPartyCount == 0)
            gPartyMenu.slotId = PARTY_SIZE + 1; // Cancel

        gTextFlags.autoScroll = 0;
        CalculatePlayerPartyCount();
        SetMainCallback2(CB2_InitPartyMenu);
    }
}

static void RefreshPartyMenu(void) //Refreshes the party menu without restarting tasks
{
    u16 i;
    for (i = 0; i < ARRAY_COUNT(sPartyMenuInternal->data); i++)
        sPartyMenuInternal->data[i] = 0;
    for (i = 0; i < ARRAY_COUNT(sPartyMenuInternal->windowId); i++)
        sPartyMenuInternal->windowId[i] = WINDOW_NONE;
    gTextFlags.autoScroll = 0;
    CalculatePlayerPartyCount();
    SetMainCallback2(CB2_ReloadPartyMenu);
}

static void CB2_UpdatePartyMenu(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_PartyMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_InitPartyMenu(void)
{
    while (TRUE)
    {
        if (MenuHelpers_ShouldWaitForLinkRecv() == TRUE || ShowPartyMenu() == TRUE || MenuHelpers_IsLinkActive() == TRUE)
            break;
    }
}

static void CB2_ReloadPartyMenu(void)
{
    while (TRUE)
    {
        if (MenuHelpers_ShouldWaitForLinkRecv() == TRUE || ReloadPartyMenu() == TRUE || MenuHelpers_IsLinkActive() == TRUE)
            break;
    }
}

static bool8 ShowPartyMenu(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ResetVramOamAndBgCntRegs();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        gPaletteFade.bufferTransferDisabled = TRUE;
        gMain.state++;
        break…58220 tokens truncated… partyIndexes[j] = i;
                j++;
            }
        }
    }
    else
    {
        enum BattlerId rightBattler;
        if (IsOnPlayerSide(battler))
            rightBattler = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        else
            rightBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);

        j = 2;
        partyIndexes[0] = gBattlerPartyIndexes[leftBattler];
        partyIndexes[1] = gBattlerPartyIndexes[rightBattler];
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (i != partyIndexes[0] && i != partyIndexes[1])
            {
                partyIndexes[j] = i;
                j++;
            }
        }
    }

    for (i = 0; i < 3; i++)
        partyBattleOrder[i] = (partyIndexes[0 + (i * 2)] << 4) | partyIndexes[1 + (i * 2)];
}

void SwitchPartyOrderLinkMulti(enum BattlerId battler, u8 slot, u8 slot2)
{
    u8 partyIds[PARTY_SIZE];
    u8 tempSlot = 0;
    int i, j;
    u8 *partyBattleOrder;
    u8 partyIdBuffer;

    if (IsMultiBattle())
    {
        partyBattleOrder = gBattleStruct->battlerPartyOrders[battler];
        for (i = j = 0; i < PARTY_SIZE / 2; j++, i++)
        {
            partyIds[j] = partyBattleOrder[i] >> 4;
            j++;
            partyIds[j] = partyBattleOrder[i] & 0xF;
        }
        partyIdBuffer = partyIds[slot2];
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (partyIds[i] == slot)
            {
                tempSlot = partyIds[i];
                partyIds[i] = partyIdBuffer;
                break;
            }
        }
        if (i != PARTY_SIZE)
        {
            partyIds[slot2] = tempSlot;
            partyBattleOrder[0] = (partyIds[0] << 4) | partyIds[1];
            partyBattleOrder[1] = (partyIds[2] << 4) | partyIds[3];
            partyBattleOrder[2] = (partyIds[4] << 4) | partyIds[5];
        }
    }
}

static u8 GetPartyIdFromBattleSlot(u8 slot)
{
    u8 modResult = slot & 1;
    u8 retVal;

    slot /= 2;
    if (modResult != 0)
        retVal = gBattlePartyCurrentOrder[slot] & 0xF;
    else
        retVal = gBattlePartyCurrentOrder[slot] >> 4;
    return retVal;
}

static void SetPartyIdAtBattleSlot(u8 slot, u8 setVal)
{
    bool32 modResult = slot & 1;

    slot /= 2;
    if (modResult != 0)
        gBattlePartyCurrentOrder[slot] = (gBattlePartyCurrentOrder[slot] & 0xF0) | setVal;
    else
        gBattlePartyCurrentOrder[slot] = (gBattlePartyCurrentOrder[slot] & 0xF) | (setVal << 4);
}

void SwitchPartyMonSlots(u8 slot, u8 slot2)
{
    u8 partyId = GetPartyIdFromBattleSlot(slot);
    SetPartyIdAtBattleSlot(slot, GetPartyIdFromBattleSlot(slot2));
    SetPartyIdAtBattleSlot(slot2, partyId);
}

u8 GetPartyIdFromBattlePartyId(u8 battlePartyId)
{
    u8 i, j;

    for (j = i = 0; i < (int)ARRAY_COUNT(gBattlePartyCurrentOrder); j++, i++)
    {
        if ((gBattlePartyCurrentOrder[i] >> 4) != battlePartyId)
        {
            j++;
            if ((gBattlePartyCurrentOrder[i] & 0xF) == battlePartyId)
                return j;
        }
        else
        {
            return j;
        }
    }
    return 0;
}

static void UpdatePartyToBattleOrder(void)
{
    struct Pokemon *partyBuffer = Alloc(sizeof(gPlayerParty));
    u8 i;

    memcpy(partyBuffer, gPlayerParty, sizeof(gPlayerParty));
    for (i = 0; i < PARTY_SIZE; i++)
        memcpy(&gPlayerParty[GetPartyIdFromBattlePartyId(i)], &partyBuffer[i], sizeof(struct Pokemon));
    Free(partyBuffer);
}

static void UpdatePartyToFieldOrder(void)
{
    struct Pokemon *partyBuffer = Alloc(sizeof(gPlayerParty));
    u8 i;

    memcpy(partyBuffer, gPlayerParty, sizeof(gPlayerParty));
    for (i = 0; i < PARTY_SIZE; i++)
        memcpy(&gPlayerParty[GetPartyIdFromBattleSlot(i)], &partyBuffer[i], sizeof(struct Pokemon));
    Free(partyBuffer);
}

static void UNUSED SwitchAliveMonIntoLeadSlot(void)
{
    u8 i;
    struct Pokemon *mon;
    u8 partyId;

    for (i = 1; i < PARTY_SIZE; i++)
    {
        mon = &gPlayerParty[GetPartyIdFromBattleSlot(i)];
        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE && GetMonData(mon, MON_DATA_HP) != 0)
        {
            partyId = GetPartyIdFromBattleSlot(0);
            SwitchPartyMonSlots(0, i);
            SwapPartyPokemon(&gPlayerParty[partyId], mon);
            break;
        }
    }
}

static void CB2_SetUpExitToBattleScreen(void)
{
    SetMainCallback2(CB2_SetUpReshowBattleScreenAfterMenu);
}

void ShowPartyMenuToShowcaseMultiBattleParty(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_MULTI_SHOWCASE, PARTY_LAYOUT_MULTI_SHOWCASE, PARTY_ACTION_CHOOSE_MON, FALSE, PARTY_MSG_NONE, Task_InitMultiPartnerPartySlideIn, gMain.savedCallback);
}

#define tXPos  data[0]

static void Task_InitMultiPartnerPartySlideIn(u8 taskId)
{
    // The first slide step also sets the sprites offscreen
    gTasks[taskId].tXPos = 256;
    SlideMultiPartyMenuBoxSpritesOneStep(taskId);
    ChangeBgX(2, 0x10000, BG_COORD_SET);
    gTasks[taskId].func = Task_MultiPartnerPartySlideIn;
}

static void Task_MultiPartnerPartySlideIn(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u8 i;

    if (!gPaletteFade.active)
    {
        tXPos -= 8;
        SlideMultiPartyMenuBoxSpritesOneStep(taskId);
        if (tXPos == 0)
        {
            for (i = MULTI_PARTY_SIZE; i < PARTY_SIZE; i++)
            {
                if (gMultiPartnerParty[i - MULTI_PARTY_SIZE].species != SPECIES_NONE)
                    AnimateSelectedPartyIcon(sPartyMenuBoxes[i].monSpriteId, 0);
            }
            PlaySE(SE_M_HARDEN); // The Harden SE plays once the partners party mons have slid on screen
            gTasks[taskId].func = Task_WaitAfterMultiPartnerPartySlideIn;
        }
    }
}

static void Task_WaitAfterMultiPartnerPartySlideIn(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    // data[0] used as a timer afterwards rather than the x pos
    if (FollowerNPCIsBattlePartner()) {
        if (++data[0] == 128)
            Task_ClosePartyMenu(taskId);
    }
    else if (++data[0] == 256)
        Task_ClosePartyMenu(taskId);
}

static void MoveMultiPartyMenuBoxSprite(u8 spriteId, s16 x)
{
    if (x >= 0)
        gSprites[spriteId].x2 = x;
}

static void SlideMultiPartyMenuBoxSpritesOneStep(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u8 i;

    for (i = MULTI_PARTY_SIZE; i < PARTY_SIZE; i++)
    {
        if (gMultiPartnerParty[i - MULTI_PARTY_SIZE].species != SPECIES_NONE)
        {
            MoveMultiPartyMenuBoxSprite(sPartyMenuBoxes[i].monSpriteId, tXPos - 8);
            MoveMultiPartyMenuBoxSprite(sPartyMenuBoxes[i].itemSpriteId, tXPos - 8);
            MoveMultiPartyMenuBoxSprite(sPartyMenuBoxes[i].pokeballSpriteId, tXPos - 8);
            MoveMultiPartyMenuBoxSprite(sPartyMenuBoxes[i].statusSpriteId, tXPos - 8);
        }
    }
    ChangeBgX(2, 0x800, BG_COORD_ADD);
}

#undef tXpos

void ChooseMonForDaycare(void)
{
    InitPartyMenu(PARTY_MENU_TYPE_DAYCARE, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_MON, FALSE, PARTY_MSG_CHOOSE_MON_2, Task_HandleChooseMonInput, BufferMonSelection);
}

static void UNUSED ChoosePartyMonByMenuType(u8 menuType)
{
    gFieldCallback2 = CB2_FadeFromPartyMenu;
    InitPartyMenu(menuType, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_AND_CLOSE, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, CB2_ReturnToField);
}

static void BufferMonSelection(void)
{
    gSpecialVar_0x8004 = GetCursorSelectionMonId();
    if (gSpecialVar_0x8004 >= PARTY_SIZE)
        gSpecialVar_0x8004 = PARTY_NOTHING_CHOSEN;
    gFieldCallback2 = CB2_FadeFromPartyMenu;
    SetMainCallback2(CB2_ReturnToField);
}

bool8 CB2_FadeFromPartyMenu(void)
{
    FadeInFromBlack();
    CreateTask(Task_PartyMenuWaitForFade, 10);
    return TRUE;
}

static void Task_PartyMenuWaitForFade(u8 taskId)
{
    if (IsWeatherNotFadingIn())
    {
        DestroyTask(taskId);
        UnlockPlayerFieldControls();
        ScriptContext_Enable();
    }
}

void ChooseContestMon(void)
{
    LockPlayerFieldControls();
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_ChooseContestMon, 10);
}

static void Task_ChooseContestMon(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitPartyMenu(PARTY_MENU_TYPE_CONTEST, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_AND_CLOSE, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, CB2_ChooseContestMon);
        DestroyTask(taskId);
    }
}

static void CB2_ChooseContestMon(void)
{
    gContestMonPartyIndex = GetCursorSelectionMonId();
    if (gContestMonPartyIndex >= PARTY_SIZE)
        gContestMonPartyIndex = PARTY_NOTHING_CHOSEN;
    gSpecialVar_0x8004 = gContestMonPartyIndex;
    gFieldCallback2 = CB2_FadeFromPartyMenu;
    SetMainCallback2(CB2_ReturnToField);
}

// Used as a script special for showing a party mon to various npcs (e.g. in-game trades, move deleter)
void ChoosePartyMon(void)
{
    LockPlayerFieldControls();
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_ChoosePartyMon, 10);
}

static void Task_ChoosePartyMon(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitPartyMenu(PARTY_MENU_TYPE_CHOOSE_MON, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_AND_CLOSE, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, BufferMonSelection);
        DestroyTask(taskId);
    }
}

void ChooseMonForMoveRelearner(void)
{
    gRelearnMode = RELEARN_MODE_SCRIPT;
    LockPlayerFieldControls();
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_ChooseMonForMoveRelearner, 10);
}

static void Task_ChooseMonForMoveRelearner(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitPartyMenu(PARTY_MENU_TYPE_MOVE_RELEARNER, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_AND_CLOSE, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, CB2_ChooseMonForMoveRelearner);
        DestroyTask(taskId);
    }
}

static void CB2_ChooseMonForMoveRelearner(void)
{
    gSpecialVar_0x8004 = GetCursorSelectionMonId();
    if (gSpecialVar_0x8004 >= PARTY_SIZE)
    {
        gSpecialVar_0x8004 = PARTY_NOTHING_CHOSEN;
    }
    gFieldCallback2 = CB2_FadeFromPartyMenu;
    SetMainCallback2(CB2_ReturnToField);
}

void DoBattlePyramidMonsHaveHeldItem(void)
{
    u8 i;

    gSpecialVar_Result = FALSE;
    for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM) != ITEM_NONE)
        {
            gSpecialVar_Result = TRUE;
            break;
        }
    }
}

// Can be called if the Battle Pyramid Bag is full on exiting and at least one party mon still has held items
// The player can then select to toss items from the bag or take/toss held items from the party
void BattlePyramidChooseMonHeldItems(void)
{
    LockPlayerFieldControls();
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_BattlePyramidChooseMonHeldItems, 10);
}

static void Task_BattlePyramidChooseMonHeldItems(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitPartyMenu(PARTY_MENU_TYPE_STORE_PYRAMID_HELD_ITEMS, PARTY_LAYOUT_SINGLE, PARTY_ACTION_CHOOSE_MON, FALSE, PARTY_MSG_CHOOSE_MON, Task_HandleChooseMonInput, BufferMonSelection);
        DestroyTask(taskId);
    }
}

void MoveDeleterChooseMoveToForget(void)
{
    ShowPokemonSummaryScreen(SUMMARY_MODE_SELECT_MOVE, gPlayerParty, gSpecialVar_0x8004, gPlayerPartyCount - 1, CB2_ReturnToField);
    gFieldCallback = FieldCB_ContinueScriptHandleMusic;
}

void GetNumMovesSelectedMonHas(void)
{
    u32 i;
    struct BoxPokemon *boxmon = GetSelectedBoxMonFromPcOrParty();

    gSpecialVar_Result = 0;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetBoxMonData(boxmon , MON_DATA_MOVE1 + i) != MOVE_NONE)
            gSpecialVar_Result++;
    }
}

void BufferMoveDeleterNicknameAndMove(void)
{
    enum Move move = 0;
    struct BoxPokemon *boxmon = GetSelectedBoxMonFromPcOrParty();
    move = GetBoxMonData(boxmon, MON_DATA_MOVE1 + gSpecialVar_0x8005);
    GetBoxMonData(boxmon, MON_DATA_NICKNAME, gStringVar1);
    StringCopy(gStringVar2, GetMoveName(move));
}

void MoveDeleterForgetMove(void)
{
    enum Move move = MOVE_NONE;
    struct BoxPokemon *boxmon = GetSelectedBoxMonFromPcOrParty();
    SetBoxMonData(boxmon, MON_DATA_MOVE1 + gSpecialVar_0x8005, &move);
    SetBoxMonData(boxmon, MON_DATA_PP1 + gSpecialVar_0x8005, &gMovesInfo[MOVE_NONE].pp);
    u8 ppBonuses = GetBoxMonData(boxmon, MON_DATA_PP_BONUSES);
    ppBonuses &= gPPUpClearMask[gSpecialVar_0x8005];
    SetBoxMonData(boxmon, MON_DATA_PP_BONUSES, &ppBonuses);
    for (u32 i = gSpecialVar_0x8005; i < MAX_MON_MOVES - 1; i++)
        ShiftMoveSlot(boxmon, i, i + 1);
}

static void ShiftMoveSlot(struct BoxPokemon *mon, u8 slotTo, u8 slotFrom)
{
    enum Move move1 = GetBoxMonData(mon, MON_DATA_MOVE1 + slotTo);
    enum Move move0 = GetBoxMonData(mon, MON_DATA_MOVE1 + slotFrom);
    u8 pp1 = GetBoxMonData(mon, MON_DATA_PP1 + slotTo);
    u8 pp0 = GetBoxMonData(mon, MON_DATA_PP1 + slotFrom);
    u8 ppBonuses = GetBoxMonData(mon, MON_DATA_PP_BONUSES);
    u8 ppBonusMask1 = gPPUpGetMask[slotTo];
    u8 ppBonusMove1 = (ppBonuses & ppBonusMask1) >> (slotTo * 2);
    u8 ppBonusMask2 = gPPUpGetMask[slotFrom];
    u8 ppBonusMove2 = (ppBonuses & ppBonusMask2) >> (slotFrom * 2);
    ppBonuses &= ~ppBonusMask1;
    ppBonuses &= ~ppBonusMask2;
    ppBonuses |= (ppBonusMove1 << (slotFrom * 2)) + (ppBonusMove2 << (slotTo * 2));
    SetBoxMonData(mon, MON_DATA_MOVE1 + slotTo, &move0);
    SetBoxMonData(mon, MON_DATA_MOVE1 + slotFrom, &move1);
    SetBoxMonData(mon, MON_DATA_PP1 + slotTo, &pp0);
    SetBoxMonData(mon, MON_DATA_PP1 + slotFrom, &pp1);
    SetBoxMonData(mon, MON_DATA_PP_BONUSES, &ppBonuses);
}

void IsSelectedMonEgg(void)
{
    struct BoxPokemon *boxmon = GetSelectedBoxMonFromPcOrParty();
    if (GetBoxMonData(boxmon, MON_DATA_IS_EGG))
        gSpecialVar_Result = TRUE;
    else
        gSpecialVar_Result = FALSE;
}

void IsLastMonThatKnowsSurf(void)
{
    enum Move move;
    u32 i, j;

    gSpecialVar_Result = FALSE;
    if (gSpecialVar_0x8004 == PC_MON_CHOSEN)
        return;

    move = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_MOVE1 + gSpecialVar_0x8005);
    if (move == MOVE_SURF)
    {
        for (i = 0; i < CalculatePlayerPartyCount(); i++)
        {
            if (i != gSpecialVar_0x8004)
            {
                for (j = 0; j < MAX_MON_MOVES; j++)
                {
                    if (GetMonData(&gPlayerParty[i], MON_DATA_MOVE1 + j) == MOVE_SURF)
                        return;
                }
            }
        }
        if (AnyStorageMonWithMove(move) != TRUE)
            gSpecialVar_Result = !P_CAN_FORGET_HIDDEN_MOVE;
    }
}

static void CursorCb_ChangeLevelUpMoves(u8 taskId)
{
    PlaySE(SE_SELECT);
    gMoveRelearnerState = MOVE_RELEARNER_LEVEL_UP_MOVES;
    gRelearnMode = RELEARN_MODE_PARTY_MENU;
    gLastViewedMonIndex = gPartyMenu.slotId;
    gSpecialVar_0x8004 = gLastViewedMonIndex;
    TeachMoveRelearnerMove();
    Task_ClosePartyMenu(taskId);
}

static void CursorCb_ChangeEggMoves(u8 taskId)
{
    PlaySE(SE_SELECT);
    gMoveRelearnerState = MOVE_RELEARNER_EGG_MOVES;
    gRelearnMode = RELEARN_MODE_PARTY_MENU;
    gLastViewedMonIndex = gPartyMenu.slotId;
    gSpecialVar_0x8004 = gLastViewedMonIndex;
    TeachMoveRelearnerMove();
    Task_ClosePartyMenu(taskId);
}

static void CursorCb_ChangeTMMoves(u8 taskId)
{
    PlaySE(SE_SELECT);
    gMoveRelearnerState = MOVE_RELEARNER_TM_MOVES;
    gRelearnMode = RELEARN_MODE_PARTY_MENU;
    gLastViewedMonIndex = gPartyMenu.slotId;
    gSpecialVar_0x8004 = gLastViewedMonIndex;
    TeachMoveRelearnerMove();
    Task_ClosePartyMenu(taskId);
}

static void CursorCb_ChangeTutorMoves(u8 taskId)
{
    PlaySE(SE_SELECT);
    gMoveRelearnerState = MOVE_RELEARNER_TUTOR_MOVES;
    gRelearnMode = RELEARN_MODE_PARTY_MENU;
    gLastViewedMonIndex = gPartyMenu.slotId;
    gSpecialVar_0x8004 = gLastViewedMonIndex;
    TeachMoveRelearnerMove();
    Task_ClosePartyMenu(taskId);
}

static void CursorCb_LearnMovesSubMenu(u8 taskId)
{
    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    SetPartyMonSelectionActions(gPlayerParty, gPartyMenu.slotId, ACTIONS_MOVES_SUB);
    DisplaySelectionWindow(SELECTWINDOW_ACTIONS);
    DisplayPartyMenuStdMessage(PARTY_MSG_DO_WHAT_WITH_MON);
    gTasks[taskId].data[0] = 0xFF;
    gTasks[taskId].func = Task_HandleSelectionMenuInput;
}

void CursorCb_MoveItemCallback(u8 taskId)
{
    enum Item item1, item2;
    u8 buffer[100];

    if (gPaletteFade.active || MenuHelpers_ShouldWaitForLinkRecv())
        return;

    switch (PartyMenuButtonHandler(&gPartyMenu.slotId2))
    {
    case 2:     // User hit B or A while on Cancel
        HandleChooseMonCancel(taskId, &gPartyMenu.slotId2);
        break;
    case 1:     // User hit A on a Pokemon
        // Pokemon can't give away items to eggs or themselves
        if (GetMonData(&gPlayerParty[gPartyMenu.slotId2], MON_DATA_IS_EGG)
            || gPartyMenu.slotId == gPartyMenu.slotId2)
        {
            PlaySE(SE_FAILURE);
            return;
        }

        PlaySE(SE_SELECT);
        gPartyMenu.action = PARTY_ACTION_CHOOSE_MON;

        // look up held items
        item1 = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM);
        item2 = GetMonData(&gPlayerParty[gPartyMenu.slotId2], MON_DATA_HELD_ITEM);

        // swap the held items
        SetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_HELD_ITEM, &item2);
        SetMonData(&gPlayerParty[gPartyMenu.slotId2], MON_DATA_HELD_ITEM, &item1);

        TryItemHoldFormChange(&gPlayerParty[gPartyMenu.slotId], gPartyMenu.slotId);
        TryItemHoldFormChange(&gPlayerParty[gPartyMenu.slotId2], gPartyMenu.slotId2);

        // update the held item icons
        UpdatePartyMonHeldItemSprite(&gPlayerParty[gPartyMenu.slotId], &sPartyMenuBoxes[gPartyMenu.slotId]);
        UpdatePartyMonHeldItemSprite(&gPlayerParty[gPartyMenu.slotId2], &sPartyMenuBoxes[gPartyMenu.slotId2]);

        // create the string describing the move
        if (item2 == ITEM_NONE)
        {
            GetMonNickname(&gPlayerParty[gPartyMenu.slotId2], gStringVar1);
            CopyItemName(item1, gStringVar2);
            StringExpandPlaceholders(gStringVar4, gText_PkmnWasGivenItem);
        }
        else
        {
            GetMonNickname(&gPlayerParty[gPartyMenu.slotId], gStringVar1);
            CopyItemName(item1, gStringVar2);
            StringExpandPlaceholders(buffer, gText_XsYAnd);

            StringAppend(buffer, gText_XsYWereSwapped);
            GetMonNickname(&gPlayerParty[gPartyMenu.slotId2], gStringVar1);
            CopyItemName(item2, gStringVar2);
            StringExpandPlaceholders(gStringVar4, buffer);
        }

        // display the string
        DisplayPartyMenuMessage(gStringVar4, TRUE);

        // update colors of selected boxes
        AnimatePartySlot(gPartyMenu.slotId2, 0);
        AnimatePartySlot(gPartyMenu.slotId, 1);

        // return to the main party menu
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_UpdateHeldItemSprite;
        break;
    }
}

void CursorCb_MoveItem(u8 taskId)
{
    struct Pokemon *mon = &gPlayerParty[gPartyMenu.slotId];

    PlaySE(SE_SELECT);

    // delete old windows
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);

    if (GetMonData(mon, MON_DATA_HELD_ITEM) != ITEM_NONE)
    {
        gPartyMenu.action = PARTY_ACTION_SWITCH;

        // show "Move item to where" in bottom left
        DisplayPartyMenuStdMessage(PARTY_MSG_MOVE_ITEM_WHERE);
        // update color of first selected box
        AnimatePartySlot(gPartyMenu.slotId, 1);

        // set up callback
        gPartyMenu.slotId2 = gPartyMenu.slotId;
        gTasks[taskId].func = CursorCb_MoveItemCallback;
    }
    else
    {
        // create and display string about lack of hold item
        GetMonNickname(mon, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_PkmnNotHolding);
        DisplayPartyMenuMessage(gStringVar4, TRUE);

        // return to the main party menu
        ScheduleBgCopyTilemapToVram(2);
        gTasks[taskId].func = Task_UpdateHeldItemSprite;
    }
}

static void FieldCallback_RockClimb(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    FieldEffectStart(FLDEFF_USE_ROCK_CLIMB);
}

static void PartyMenu_Oak_PrintText(u8 windowId, const u8 *str)
{
    StringExpandPlaceholders(gStringVar4, str);
    gTextFlags.canABSpeedUpPrint = TRUE;
    AddTextPrinterParameterized2(windowId, FONT_NORMAL, gStringVar4, GetPlayerTextSpeedDelay(), NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
}

static bool8 FirstBattleEnterParty_CreateWindowAndMsg1Printer(void)
{
    u8 windowId = AddWindow(&sWindowTemplate_FirstBattleOakVoiceover);

    LoadMessageBoxGfx(windowId, 0x4F, BG_PLTT_ID(14));
    DrawDialogFrameWithCustomTileAndPalette(windowId, 1, 0x4F, 0xE);
    PartyMenu_Oak_PrintText(windowId, gText_OakImportantToGetToKnowPokemonThroughly);
    return windowId;
}

static void FirstBattleEnterParty_DestroyVoiceoverWindow(u8 windowId)
{
    ClearWindowTilemap(windowId);
    ClearDialogWindowAndFrameToTransparent(windowId, FALSE);
    RemoveWindow(windowId);
    ScheduleBgCopyTilemapToVram(2);
}

static void Task_FirstBattleEnterParty_WaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_FirstBattleEnterParty_DarkenScreen;
}

static void Task_FirstBattleEnterParty_DarkenScreen(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFF1FFF, 4, 0, 6, RGB_BLACK);
    gTasks[taskId].func = Task_FirstBattleEnterParty_WaitDarken;
}

static void Task_FirstBattleEnterParty_WaitDarken(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_FirstBattleEnterParty_CreatePrinter;
}

static void Task_FirstBattleEnterParty_CreatePrinter(u8 taskId)
{
    gTasks[taskId].data[0] = FirstBattleEnterParty_CreateWindowAndMsg1Printer();
    gTasks[taskId].func = Task_FirstBattleEnterParty_RunPrinterMsg1;
}

static void Task_FirstBattleEnterParty_RunPrinterMsg1(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (RunTextPrintersRetIsActive((u8)data[0]) != TRUE)
        gTasks[taskId].func = Task_FirstBattleEnterParty_LightenFirstMonIcon;
}

static void Task_FirstBattleEnterParty_LightenFirstMonIcon(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFF0008, 4, 6, 0, RGB_BLACK);
    gTasks[taskId].func = Task_FirstBattleEnterParty_WaitLightenFirstMonIcon;
}

static void Task_FirstBattleEnterParty_WaitLightenFirstMonIcon(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_FirstBattleEnterParty_StartPrintMsg2;
}

static void Task_FirstBattleEnterParty_StartPrintMsg2(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    PartyMenu_Oak_PrintText(data[0], gText_OakThisIsListOfPokemon);
    gTasks[taskId].func = Task_FirstBattleEnterParty_RunPrinterMsg2;
}

static void Task_FirstBattleEnterParty_RunPrinterMsg2(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (RunTextPrintersRetIsActive((u8)data[0]) != TRUE)
    {
        FirstBattleEnterParty_DestroyVoiceoverWindow((u8)data[0]);
        gTasks[taskId].func = Task_FirstBattleEnterParty_FadeNormal;
    }
}

static void Task_FirstBattleEnterParty_FadeNormal(u8 taskId)
{
    BeginNormalPaletteFade(0x0000FFF7, 4, 6, 0, RGB_BLACK);
    gTasks[taskId].func = Task_FirstBattleEnterParty_WaitFadeNormal;
}

static void Task_FirstBattleEnterParty_WaitFadeNormal(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        LoadUserWindowBorderGfx(0, 0x4F, BG_PLTT_ID(13));
        LoadUserWindowBorderGfx_(0, 0x58, BG_PLTT_ID(13));
        if (gPartyMenu.action == PARTY_ACTION_USE_ITEM)
            DisplayPartyMenuStdMessage(PARTY_MSG_USE_ON_WHICH_MON);
        else
            DisplayPartyMenuStdMessage(PARTY_MSG_CHOOSE_MON);
        gTasks[taskId].func = Task_HandleChooseMonInput;
    }
}
