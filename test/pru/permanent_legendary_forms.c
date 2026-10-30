#include "global.h"
#include "battle_util.h"
#include "battle_dynamax.h"
#include "battle_terastal.h"
#include "overworld.h"
#include "pokemon.h"
#include "test/battle.h"
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

    CreateMon(&mon, SPECIES_GROUDON, 50, 0, OTID_STRUCT_PLAYER_ID);
    personality = GetMonData(&mon, MON_DATA_PERSONALITY);
    for (u32 i = 0; i < NUM_STATS; i++)
        ivs[i] = GetMonData(&mon, MON_DATA_HP_IV + i);

    // Simulate an older save's calculated stat block, retaining a fixed HP loss.
    mon.attack = 1;
    mon.hp = mon.maxHP - 50;
    RecalculatePermanentLegendaryStats(&mon);

    EXPECT(mon.attack != 1);
    EXPECT(mon.maxHP != 1);
    EXPECT_EQ(mon.maxHP - mon.hp, 50);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PERSONALITY), personality);
    for (u32 i = 0; i < NUM_STATS; i++)
        EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV + i), ivs[i]);
}

TEST("PRU Storm Shrine is registered in Dragon's Den")
{
    const struct MapHeader *map = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_DRAGONS_DEN_STORM_SHRINE_HNS),
        MAP_NUM(MAP_DRAGONS_DEN_STORM_SHRINE_HNS));

    EXPECT(map != NULL);
    EXPECT_EQ(map->mapLayoutId, LAYOUT_DRAGONS_DEN_SHRINE_HNS);
}

SINGLE_BATTLE_TEST("PRU Mewduo Parental Bond strikes twice at reduced damage")
{
    enum Move move;
    s16 damage[2];
    PARAMETRIZE { move = MOVE_FACADE; }   // Physical
    PARAMETRIZE { move = MOVE_PSYSTRIKE; } // Special

    GIVEN {
        ASSUME(GetMoveCategory(move) != DAMAGE_CATEGORY_STATUS);
        ASSUME(GetMoveStrikeCount(move) < 2);
        PLAYER(SPECIES_MEWSION);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, captureDamage: &damage[0]);
        HP_BAR(opponent, captureDamage: &damage[1]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    } THEN {
        EXPECT_EQ(player->ability, ABILITY_PARENTAL_BOND);
        EXPECT_MUL_EQ(damage[0], Q_4_12(0.25), damage[1]);
    }
}

SINGLE_BATTLE_TEST("PRU Mewduo Parental Bond does not add a strike to multi-hit attacks")
{
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_TRIPLE_KICK) != DAMAGE_CATEGORY_STATUS);
        ASSUME(GetMoveStrikeCount(MOVE_TRIPLE_KICK) == 3);
        PLAYER(SPECIES_MEWSION);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TRIPLE_KICK); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TRIPLE_KICK, player);
        HP_BAR(opponent);
        HP_BAR(opponent);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    } THEN {
        EXPECT_EQ(player->ability, ABILITY_PARENTAL_BOND);
    }
}

DOUBLE_BATTLE_TEST("PRU Mewduo Parental Bond does not duplicate spread attacks")
{
    GIVEN {
        ASSUME(GetMoveStrikeCount(MOVE_EARTHQUAKE) < 2);
        ASSUME(GetMoveTarget(MOVE_EARTHQUAKE) == TARGET_FOES_AND_ALLY);
        ASSUME(GetSpeciesType(SPECIES_PIDGEY, 1) == TYPE_FLYING);
        PLAYER(SPECIES_MEWSION);
        PLAYER(SPECIES_PIDGEY);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_EARTHQUAKE); MOVE(playerRight, MOVE_CELEBRATE); MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, playerLeft);
        HP_BAR(opponentLeft);
        MESSAGE("It doesn't affect Pidgey…");
        MESSAGE("It doesn't affect the opposing Pidgey…");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponentLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponentRight);
    } THEN {
        EXPECT_EQ(playerLeft->ability, ABILITY_PARENTAL_BOND);
    }
}
