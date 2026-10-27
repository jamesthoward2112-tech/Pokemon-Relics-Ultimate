#include "global.h"
#include "chooseboxmon.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "fieldmap.h"
#include "overworld.h"
#include "script.h"
#include "test/test.h"
#include "constants/event_objects.h"
#include "constants/vars.h"

TEST("PRU tutor compatibility reaches move teaching without broad unlocks")
{
    struct Pokemon mon;
    u16 none = MOVE_NONE;

    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_SHUCKLE, MOVE_STICKY_WEB));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_SHUCKOLOSSE, MOVE_STICKY_WEB));
    EXPECT(!CanSpeciesLearnPruTutorMove(SPECIES_PIKACHU, MOVE_STICKY_WEB));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_MAROWAK, MOVE_FAULTLINE));
    EXPECT(!CanSpeciesLearnPruTutorMove(SPECIES_PIKACHU, MOVE_FAULTLINE));
    EXPECT(CanSpeciesLearnPruTutorMove(SPECIES_SCYTHER, MOVE_U_TURN));

    CreateMon(&mon, SPECIES_SHUCKLE, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_MOVE1, &none);
    SetMonData(&mon, MON_DATA_MOVE2, &none);
    SetMonData(&mon, MON_DATA_MOVE3, &none);
    SetMonData(&mon, MON_DATA_MOVE4, &none);
    EXPECT_NE(GiveMoveToMon(&mon, MOVE_STICKY_WEB), MON_HAS_MAX_MOVES);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE1), MOVE_STICKY_WEB);
}

static u8 CheckLeagueRoomTrainer(u16 mapId, u16 expectedGfx, bool32 kantoActive)
{
    const struct MapHeader *source = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(mapId), MAP_NUM(mapId));
    struct MapHeader savedHeader = gMapHeader;
    struct WarpData savedLocation = gSaveBlock1Ptr->location;
    struct ObjectEvent savedObjectEvents[OBJECT_EVENTS_COUNT];
    struct ObjectEventTemplate savedTemplates[OBJECT_EVENT_TEMPLATES_COUNT];
    u16 savedMapLayoutId = gSaveBlock1Ptr->mapLayoutId;
    u16 savedLeagueState = VarGet(VAR_LEAGUE_STATE);
    u16 savedGfx = VarGet(VAR_OBJ_GFX_ID_0);
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
    u8 result = 0;

    memcpy(savedObjectEvents, gObjectEvents, sizeof(savedObjectEvents));
    memcpy(savedTemplates, gSaveBlock1Ptr->objectEventTemplates, sizeof(savedTemplates));
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
    RunOnTransitionMapScript();
    template = &gSaveBlock1Ptr->objectEventTemplates[0];
    objectEventId = TrySpawnObjectEventTemplate(template, MAP_NUM(mapId), MAP_GROUP(mapId), 0, 0);
    if (template->flagId == 0)
        result |= 1;
    if (template->script != NULL)
        result |= 2;
    if (template->graphicsId == OBJ_EVENT_GFX_VAR_0)
        result |= 128;
    if (GetObjectEventGraphicsInfo(template->graphicsId) == GetObjectEventGraphicsInfo(expectedGfx))
        result |= 256;
    if (VarGet(VAR_OBJ_GFX_ID_0) == expectedGfx)
        result |= 16;
    if (VarGet(VAR_RESULT) == (kantoActive ? TRUE : FALSE))
        result |= 32;
    if (gMapHeader.mapScripts != NULL)
        result |= 64;
    if (objectEventId != OBJECT_EVENTS_COUNT && gObjectEvents[objectEventId].active)
    {
        result |= 4;
        if (gObjectEvents[objectEventId].graphicsId == expectedGfx)
            result |= 8;
    }

    if (objectEventId != OBJECT_EVENTS_COUNT)
        RemoveObjectEvent(&gObjectEvents[objectEventId]);
    memcpy(gObjectEvents, savedObjectEvents, sizeof(savedObjectEvents));
    memcpy(gSaveBlock1Ptr->objectEventTemplates, savedTemplates, sizeof(savedTemplates));
    gMapHeader = savedHeader;
    gSaveBlock1Ptr->location = savedLocation;
    gSaveBlock1Ptr->mapLayoutId = savedMapLayoutId;
    VarSet(VAR_LEAGUE_STATE, savedLeagueState);
    VarSet(VAR_OBJ_GFX_ID_0, savedGfx);
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
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_WILLS_ROOM_HNS, OBJ_EVENT_GFX_LORELEI, TRUE), 511);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_KOGAS_ROOM_HNS, OBJ_EVENT_GFX_BRUNO_HNS, TRUE), 511);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_BRUNOS_ROOM_HNS, OBJ_EVENT_GFX_AGATHA, TRUE), 511);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_KARENS_ROOM_HNS, OBJ_EVENT_GFX_LANCE_HNS, TRUE), 511);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM_HNS, OBJ_EVENT_GFX_RED_NORMAL_HNS, TRUE), 511);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_WILLS_ROOM_HNS, OBJ_EVENT_GFX_WILL_HNS, FALSE), 511);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_KOGAS_ROOM_HNS, OBJ_EVENT_GFX_KOGA_HNS, FALSE), 511);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_BRUNOS_ROOM_HNS, OBJ_EVENT_GFX_BRUNO_HNS, FALSE), 511);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_KARENS_ROOM_HNS, OBJ_EVENT_GFX_KAREN_HNS, FALSE), 511);
    EXPECT_EQ(CheckLeagueRoomTrainer(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM_HNS, OBJ_EVENT_GFX_LANCE_HNS, FALSE), 511);
}
