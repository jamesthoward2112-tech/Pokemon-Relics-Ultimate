#include "global.h"
#include "chooseboxmon.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "fieldmap.h"
#include "field_camera.h"
#include "overworld.h"
#include "party_menu.h"
#include "script.h"
#include "sprite.h"
#include "test/test.h"
#include "constants/event_objects.h"
#include "constants/vars.h"

TEST("PRU tutor compatibility reaches move teaching without broad unlocks")
{
    struct Pokemon mon;
    u16 none = MOVE_NONE;

    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_SHUCKLE, MOVE_STICKY_WEB));
    // Player-facing compatibility: Grass gets Sticky Web too, even when
    // it has no Bug secondary typing.
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_BULBASAUR, MOVE_STICKY_WEB));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_SHUCKOLOSSE, MOVE_STICKY_WEB));
    EXPECT(!CanSpeciesLearnPruTutorMove(SPECIES_PIKACHU, MOVE_STICKY_WEB));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_MAROWAK, MOVE_FAULTLINE));
    EXPECT(!CanSpeciesLearnPruTutorMove(SPECIES_PIKACHU, MOVE_FAULTLINE));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_SCYTHER, MOVE_U_TURN));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_VALKYVOIR, MOVE_MINDWAVE));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_VALKYVOIR, MOVE_PSYCHIC_FANGS));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_ALAKAZAM, MOVE_AGILITY));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_MACHAMP, MOVE_SHOCKWAVE_FIST));
    // Fighting-type Shockwave Fist inherits Brick Break's exact tutor
    // compatibility. Electric typing alone no longer grants access.
    EXPECT_EQ(CanSpeciesLearnPruTutorMove(SPECIES_PIKACHU, MOVE_SHOCKWAVE_FIST),
              CanSpeciesLearnPruTutorMove(SPECIES_PIKACHU, MOVE_BRICK_BREAK));
    EXPECT_EQ(CanSpeciesLearnPruTutorMove(SPECIES_ELECTABUZZ, MOVE_SHOCKWAVE_FIST),
              CanSpeciesLearnPruTutorMove(SPECIES_ELECTABUZZ, MOVE_BRICK_BREAK));
    EXPECT_EQ(CanSpeciesLearnPruTutorMove(SPECIES_MAROWAK, MOVE_SHOCKWAVE_FIST),
              CanSpeciesLearnPruTutorMove(SPECIES_MAROWAK, MOVE_BRICK_BREAK));
    EXPECT_EQ(CanSpeciesLearnPruTutorMove(SPECIES_SKARMORY, MOVE_SHOCKWAVE_FIST),
              CanSpeciesLearnPruTutorMove(SPECIES_SKARMORY, MOVE_BRICK_BREAK));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_STEELIX, MOVE_METAL_BARRAGE));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_SKARMORY, MOVE_METAL_BARRAGE));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_GEODUDE, MOVE_METAL_BARRAGE));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_MAROWAK, MOVE_METAL_BARRAGE));
    EXPECT(!CanSpeciesLearnPruTutorMove(SPECIES_PIKACHU, MOVE_MINDWAVE));

    // The party menu is a distinct path from the PC selection callback.
    // A matching species must be accepted during a tutor session but never
    // gain the same move through an ordinary TM/item action.
    EXPECT(CanSpeciesLearnPruTutorMoveForParty(SPECIES_SHUCKLE, MOVE_STICKY_WEB, TRUE));
    EXPECT(CanSpeciesLearnPruTutorMoveForParty(SPECIES_BULBASAUR, MOVE_STICKY_WEB, TRUE));
    EXPECT(CanSpeciesLearnPruTutorMoveForParty(SPECIES_VALKYVOIR, MOVE_MINDWAVE, TRUE));
    EXPECT(CanSpeciesLearnPruTutorMoveForParty(SPECIES_MACHAMP, MOVE_SHOCKWAVE_FIST, TRUE));
    EXPECT_EQ(CanSpeciesLearnPruTutorMoveForParty(SPECIES_PIKACHU, MOVE_SHOCKWAVE_FIST, TRUE),
              CanSpeciesLearnPruTutorMove(SPECIES_PIKACHU, MOVE_BRICK_BREAK));
    EXPECT(CanSpeciesLearnPruTutorMoveForParty(SPECIES_STEELIX, MOVE_METAL_BARRAGE, TRUE));
    EXPECT(!CanSpeciesLearnPruTutorMoveForParty(SPECIES_SHUCKLE, MOVE_STICKY_WEB, FALSE));
    EXPECT(!CanSpeciesLearnPruTutorMoveForParty(SPECIES_PIKACHU, MOVE_STICKY_WEB, TRUE));

    CreateMon(&mon, SPECIES_SHUCKLE, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_MOVE1, &none);
    SetMonData(&mon, MON_DATA_MOVE2, &none);
    SetMonData(&mon, MON_DATA_MOVE3, &none);
    SetMonData(&mon, MON_DATA_MOVE4, &none);
    EXPECT_NE(GiveMoveToMon(&mon, MOVE_STICKY_WEB), MON_HAS_MAX_MOVES);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE1), MOVE_STICKY_WEB);
}

static EWRAM_DATA struct ObjectEvent sSavedLeagueObjectEvents[OBJECT_EVENTS_COUNT];
static EWRAM_DATA struct ObjectEventTemplate sSavedLeagueTemplates[OBJECT_EVENT_TEMPLATES_COUNT];

static u16 CheckLeagueRoomTrainer(u16 mapId, u16 expectedGfx, bool32 kantoActive)
{
    const struct MapHeader *source = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(mapId), MAP_NUM(mapId));
    struct MapHeader savedHeader = gMapHeader;
    struct WarpData savedLocation = gSaveBlock1Ptr->location;
    u16 savedMapLayoutId = gSaveBlock1Ptr->mapLayoutId;
    s16 savedPosX = gSaveBlock1Ptr->pos.x;
    s16 savedPosY = gSaveBlock1Ptr->pos.y;
    u16 savedCameraOffsetX = gTotalCameraPixelOffsetX;
    u16 savedCameraOffsetY = gTotalCameraPixelOffsetY;
    u16 savedLeagueState = VarGet(VAR_LEAGUE_STATE);
    u16 savedResult = VarGet(VAR_RESULT);
    bool32 savedFlags[] = {
        FlagGet(FLAG_IS_CHAMPION),
        FlagGet(FLAG_BADGE16_GET),
        FlagGet(FLAG_PRU_HEIST_COMPLETED),
        FlagGet(FLAG_PRU_HEIST_GIOVANNI),
        FlagGet(FLAG_PRU_KANTO_LEAGUE_CLEARED),
        FlagGet(FLAG_PRU_HIDE_JOHTO_E4),
        FlagGet(FLAG_PRU_HIDE_KANTO_E4),
    };
    struct ObjectEventTemplate *template;
    u8 objectEventId;
    u16 result = 0;

    memcpy(sSavedLeagueObjectEvents, gObjectEvents, sizeof(sSavedLeagueObjectEvents));
    memcpy(sSavedLeagueTemplates, gSaveBlock1Ptr->objectEventTemplates, sizeof(sSavedLeagueTemplates));
    gMapHeader = *source;
    gMapHeader.mapLayout = GetMapLayout(gMapHeader.mapLayoutId);
    gSaveBlock1Ptr->mapLayoutId = gMapHeader.mapLayoutId;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(mapId);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(mapId);
    VarSet(VAR_LEAGUE_STATE, 1);
    if (kantoActive)
    {
        FlagSet(FLAG_IS_CHAMPION);
        FlagSet(FLAG_BADGE16_GET);
        FlagSet(FLAG_PRU_HEIST_COMPLETED);
        FlagSet(FLAG_PRU_HEIST_GIOVANNI);
    }
    else
    {
        FlagClear(FLAG_IS_CHAMPION);
        FlagClear(FLAG_BADGE16_GET);
        FlagClear(FLAG_PRU_HEIST_COMPLETED);
        FlagClear(FLAG_PRU_HEIST_GIOVANNI);
    }
    FlagClear(FLAG_PRU_KANTO_LEAGUE_CLEARED);
    // Old saves may retain both legacy hide flags. The replacement event must
    // remain visible because it is not governed by either stale flag.
    FlagSet(FLAG_PRU_HIDE_JOHTO_E4);
    FlagSet(FLAG_PRU_HIDE_KANTO_E4);

    LoadObjEventTemplatesFromHeader();
    // Match the real map-entry sequence: ResumeMap resets sprite VRAM and
    // palettes before InitObjectEventsLocal spawns map actors.
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetObjectEvents();
    template = &gSaveBlock1Ptr->objectEventTemplates[0];
    // Model the doorway viewport: the trainer is six tiles ahead of the player.
    gSaveBlock1Ptr->pos.x = template->x + MAP_OFFSET - 7;
    gSaveBlock1Ptr->pos.y = template->y + MAP_OFFSET - 3;
    gTotalCameraPixelOffsetX = 0;
    gTotalCameraPixelOffsetY = 0;
    if (CountFreeSpriteTiles() >= 16)
        result |= 256;
    if (gReservedSpriteTileCount == 0)
        result |= 512;
    if (!gObjectEvents[0].active)
        result |= 1024;
    if (template->kind == OBJ_KIND_NORMAL)
        result |= 2048;
    objectEventId = TrySpawnObjectEventTemplate(template, MAP_NUM(mapId), MAP_GROUP(mapId), 0, 0);
    if (template->flagId == 0)
        result |= 1;
    if (template->script != NULL)
        result |= 2;
    if (template->graphicsId == expectedGfx)
        result |= 16;
    if (kantoActive == (FlagGet(FLAG_IS_CHAMPION) && FlagGet(FLAG_BADGE16_GET) && FlagGet(FLAG_PRU_HEIST_COMPLETED) && FlagGet(FLAG_PRU_HEIST_GIOVANNI)))
        result |= 32;
    if (gMapHeader.mapScripts != NULL)
        result |= 64;
    if (objectEventId != OBJECT_EVENTS_COUNT && gObjectEvents[objectEventId].active)
    {
        result |= 4;
        if (gObjectEvents[objectEventId].graphicsId == expectedGfx)
            result |= 8;
        if (!gSprites[gObjectEvents[objectEventId].spriteId].invisible)
            result |= 128;
    }
    if (objectEventId != OBJECT_EVENTS_COUNT)
        RemoveObjectEvent(&gObjectEvents[objectEventId]);
    memcpy(gObjectEvents, sSavedLeagueObjectEvents, sizeof(sSavedLeagueObjectEvents));
    memcpy(gSaveBlock1Ptr->objectEventTemplates, sSavedLeagueTemplates, sizeof(sSavedLeagueTemplates));
    gMapHeader = savedHeader;
    gSaveBlock1Ptr->location = savedLocation;
    gSaveBlock1Ptr->mapLayoutId = savedMapLayoutId;
    gSaveBlock1Ptr->pos.x = savedPosX;
    gSaveBlock1Ptr->pos.y = savedPosY;
    gTotalCameraPixelOffsetX = savedCameraOffsetX;
    gTotalCameraPixelOffsetY = savedCameraOffsetY;
    VarSet(VAR_LEAGUE_STATE, savedLeagueState);
    VarSet(VAR_RESULT, savedResult);
    if (savedFlags[0]) FlagSet(FLAG_IS_CHAMPION); else FlagClear(FLAG_IS_CHAMPION);
    if (savedFlags[1]) FlagSet(FLAG_BADGE16_GET); else FlagClear(FLAG_BADGE16_GET);
    if (savedFlags[2]) FlagSet(FLAG_PRU_HEIST_COMPLETED); else FlagClear(FLAG_PRU_HEIST_COMPLETED);
    if (savedFlags[3]) FlagSet(FLAG_PRU_HEIST_GIOVANNI); else FlagClear(FLAG_PRU_HEIST_GIOVANNI);
    if (savedFlags[4]) FlagSet(FLAG_PRU_KANTO_LEAGUE_CLEARED); else FlagClear(FLAG_PRU_KANTO_LEAGUE_CLEARED);
    if (savedFlags[5]) FlagSet(FLAG_PRU_HIDE_JOHTO_E4); else FlagClear(FLAG_PRU_HIDE_JOHTO_E4);
    if (savedFlags[6]) FlagSet(FLAG_PRU_HIDE_KANTO_E4); else FlagClear(FLAG_PRU_HIDE_KANTO_E4);
    return result;
}

TEST("Kanto Elite Four actors spawn visibly in the five existing rooms")
{
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_WILLS_ROOM_HNS, OBJ_EVENT_GFX_WILL_HNS, TRUE), 4095);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_KOGAS_ROOM_HNS, OBJ_EVENT_GFX_KOGA_HNS, TRUE), 4095);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_BRUNOS_ROOM_HNS, OBJ_EVENT_GFX_BRUNO_HNS, TRUE), 4095);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_KARENS_ROOM_HNS, OBJ_EVENT_GFX_KAREN_HNS, TRUE), 4095);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM_HNS, OBJ_EVENT_GFX_LANCE_HNS, TRUE), 4095);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_WILLS_ROOM_HNS, OBJ_EVENT_GFX_WILL_HNS, FALSE), 4095);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_KOGAS_ROOM_HNS, OBJ_EVENT_GFX_KOGA_HNS, FALSE), 4095);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_BRUNOS_ROOM_HNS, OBJ_EVENT_GFX_BRUNO_HNS, FALSE), 4095);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_KARENS_ROOM_HNS, OBJ_EVENT_GFX_KAREN_HNS, FALSE), 4095);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM_HNS, OBJ_EVENT_GFX_LANCE_HNS, FALSE), 4095);
}
