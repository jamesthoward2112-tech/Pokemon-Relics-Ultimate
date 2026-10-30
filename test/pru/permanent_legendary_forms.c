#include "global.h"
#include "battle_util.h"
#include "battle_dynamax.h"
#include "battle_terastal.h"
#include "overworld.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/layouts.h"
#include "constants/maps.h"

TEST("PRU permanent Groudon Kyogre and Rayquaza use approved battle data")
{
    const struct SpeciesInfo *groudon = &gSpeciesInfo[SPECIES_GROUDON];
    const struct SpeciesInfo *kyogre = &gSpeciesInfo[SPECIES_KYOGRE];
    const struct SpeciesInfo *rayquaza = &gSpeciesInfo[SPECIES_RAYQUAZA];

    EXPECT_EQ(groudon->baseHP, 100);
    EXPECT_EQ(groudon->baseAttack, 180);
    EXPECT_EQ(groudon->baseDefense, 160);
    EXPECT_EQ(groudon->baseSpAttack, 150);
    EXPECT_EQ(groudon->baseSpDefense, 90);
    EXPECT_EQ(groudon->baseSpeed, 90);
    EXPECT_EQ(groudon->types[0], TYPE_GROUND);
    EXPECT_EQ(groudon->types[1], TYPE_FIRE);
    EXPECT_EQ(groudon->abilities[0], ABILITY_DESOLATE_LAND);
    EXPECT_EQ(groudon->abilities[1], ABILITY_DESOLATE_LAND);
    EXPECT_EQ(groudon->abilities[2], ABILITY_DESOLATE_LAND);
    EXPECT_EQ(groudon->palette, groudon->shinyPalette);

    EXPECT_EQ(kyogre->baseHP, 100);
    EXPECT_EQ(kyogre->baseAttack, 150);
    EXPECT_EQ(kyogre->baseDefense, 90);
    EXPECT_EQ(kyogre->baseSpAttack, 180);
    EXPECT_EQ(kyogre->baseSpDefense, 160);
    EXPECT_EQ(kyogre->baseSpeed, 90);
    EXPECT_EQ(kyogre->types[0], TYPE_WATER);
    EXPECT_EQ(kyogre->abilities[0], ABILITY_PRIMORDIAL_SEA);
    EXPECT_EQ(kyogre->abilities[1], ABILITY_PRIMORDIAL_SEA);
    EXPECT_EQ(kyogre->abilities[2], ABILITY_PRIMORDIAL_SEA);
    EXPECT_EQ(kyogre->palette, kyogre->shinyPalette);

    EXPECT_EQ(rayquaza->baseHP, 105);
    EXPECT_EQ(rayquaza->baseAttack, 180);
    EXPECT_EQ(rayquaza->baseDefense, 100);
    EXPECT_EQ(rayquaza->baseSpAttack, 180);
    EXPECT_EQ(rayquaza->baseSpDefense, 100);
    EXPECT_EQ(rayquaza->baseSpeed, 115);
    EXPECT_EQ(rayquaza->types[0], TYPE_DRAGON);
    EXPECT_EQ(rayquaza->types[1], TYPE_FLYING);
    EXPECT_EQ(rayquaza->abilities[0], ABILITY_DELTA_STREAM);
    EXPECT_EQ(rayquaza->abilities[1], ABILITY_DELTA_STREAM);
    EXPECT_EQ(rayquaza->abilities[2], ABILITY_DELTA_STREAM);
    EXPECT(rayquaza->perfectIVCount == 3);
    EXPECT_EQ(rayquaza->palette, rayquaza->shinyPalette);

    EXPECT_EQ(gSpeciesInfo[SPECIES_MEWSION].abilities[0], ABILITY_PARENTAL_BOND);
    EXPECT_EQ(gSpeciesInfo[SPECIES_MEWSION].abilities[1], ABILITY_PARENTAL_BOND);
    EXPECT_EQ(gSpeciesInfo[SPECIES_MEWSION].abilities[2], ABILITY_PARENTAL_BOND);
}

TEST("PRU globally disables form changes and legendary gimmick controls")
{
    struct Pokemon mon = {0};
    struct BoxPokemon boxMon = {0};

    EXPECT(!TryFormChange(&mon, FORM_CHANGE_ITEM_USE));
    EXPECT(!TryBoxMonFormChange(&boxMon, FORM_CHANGE_ITEM_USE));
    EXPECT(!TryBattleFormChange(0, FORM_CHANGE_BATTLE_WEATHER, ABILITY_NONE));
    EXPECT(!TryPrimalReversion(0));
    EXPECT(!CanMegaEvolve(0));
    EXPECT(!CanUltraBurst(0));
    EXPECT(!CanDynamax(0));
    EXPECT(!CanTerastallize(0));
}

TEST("PRU old legendary party stats migrate without changing identity or IVs")
{
    struct Pokemon mon;
    u32 personality;
    u32 ivs[NUM_STATS];
    s32 oldAttack;
    s32 oldMaxHp;

    CreateMon(&mon, SPECIES_GROUDON, 50, 0, OTID_STRUCT_PLAYER_ID);
    personality = GetMonData(&mon, MON_DATA_PERSONALITY);
    for (u32 i = 0; i < NUM_STATS; i++)
        ivs[i] = GetMonData(&mon, MON_DATA_HP_IV + i);
    oldAttack = mon.attack;
    oldMaxHp = mon.maxHP;

    // Simulate an older save's calculated stat block, retaining a fixed HP loss.
    mon.attack = 1;
    mon.maxHP = oldMaxHp;
    mon.hp = oldMaxHp - 50;
    RecalculatePermanentLegendaryStats(&mon);

    EXPECT(mon.attack != 1);
    EXPECT(mon.maxHP != 1);
    EXPECT_EQ(mon.maxHP - mon.hp, 50);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PERSONALITY), personality);
    for (u32 i = 0; i < NUM_STATS; i++)
        EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV + i), ivs[i]);
    EXPECT_EQ(oldAttack, mon.attack);
    EXPECT_EQ(oldMaxHp, mon.maxHP);
}

TEST("PRU Storm Shrine is registered in Dragon's Den")
{
    const struct MapHeader *map = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_DRAGONS_DEN_STORM_SHRINE_HNS),
        MAP_NUM(MAP_DRAGONS_DEN_STORM_SHRINE_HNS));

    EXPECT(map != NULL);
    EXPECT_EQ(map->mapLayoutId, LAYOUT_DRAGONS_DEN_SHRINE_HNS);
}
