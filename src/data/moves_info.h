#include "battle_dynamax.h"
#include "battle_anim_scripts.h"
#include "constants/battle.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_string_ids.h"
#include "constants/hold_effects.h"
#include "constants/moves.h"
#include "constants/contest.h"

// The Gen. 4+ contest data comes from urpg's contest movedex.

#if B_BINDING_TURNS >= GEN_5
#define BINDING_TURNS "4 or 5"
#else
#define BINDING_TURNS "2 to 5"
#endif

// Shared Move Description entries

const u8 gNotDoneYetDescription[] = _(
    "This move can't be used. Its\n"
    "effect is in development.");

static const u8 sNullDescription[] = _("");

static const u8 sMegaDrainDescription[] = _(
    "Attack that absorbs\n"
    "half the damage inflicted.");

#if B_SKIP_RECHARGE != GEN_1
static const u8 sHyperBeamDescription[] = _(
    "Powerful, but leaves the\n"
    "user immobile the next turn.");
#else
static const u8 sHyperBeamDescription[] = _(
    "Leaves the user immobile\n"
    "if target is not KO'd.");
#endif

static const u8 sRevengeDescription[] = _(
    "Attack that moves last\n"
    "and gains power if hit.");

static const u8 sPluckDescription[] = _(
    "Eats the foe's held Berry\n"
    "gaining its effect.");

static const u8 sHealingWishDescription[] = _(
    "The user faints to heal up\n"
    "the recipient.");

static const u8 sWringOutDescription[] = _(
    "The higher the foe's HP\n"
    "the more damage caused.");

static const u8 sUTurnDescription[] = _(
    "Does damage then switches\n"
    "out the user.");

static const u8 sStormThrowDescription[] = _(
    "This attack always results\n"
    "in a critical hit.");

static const u8 sCircleThrowDescription[] = _(
    "Knocks foe away to switch\n"
    "it out or end wild battle.");

static const u8 sChipAwayDescription[] = _(
    "Strikes through the foe's\n"
    "stat changes.");

static const u8 sHeavySlamDescription[] = _(
    "Does more damage if the\n"
    "user outweighs the foe.");

static const u8 sPsyshockDescription[] = _(
    "Attacks with a psychic wave\n"
    "that does physical damage.");

static const u8 sLavaPlumeDescription[] = _(
    "Scarlet flames torch\n"
    "everything around the user.");

static const u8 sShadowForceDescription[] = _(
    "Vanishes on the first turn\n"
    "then strikes the next turn.");

static const u8 sFalseSwipeDescription[] = _(
    "Attack that leaves the\n"
    "foe with at least 1 HP.");

static const u8 sDrainingKissDescription[] = _(
    "Attack that absorbs over\n"
    "half the damage inflicted.");

static const u8 sCloseCombatDescription[] = _(
    "A strong attack but lowers\n"
    "the defensive stats.");

static const u8 sHyperspaceHoleDescription[] = _(
    "Uses a warp hole to attack.\n"
    "Can't be evaded.");

static const u8 sSuckerPunchDescription[] = _(
    "Strikes first if the foe\n"
    "is preparing Attack.");

static const u8 sFeintDescription[] = _(
    "Attack that hits foes\n"
    "using moves like Protect.");

static const u8 sProtectDescription[] = _(
    "Evades attack, but may fail\n"
    "if used in succession.");

static const u8 sGMaxOneBlowDescription[] = _(
    "G-max Urshifu attack.\n"
    "Ignores Max Guard.");

const struct MoveInfo gMovesInfo[MOVES_COUNT_ALL] =
{
    [MOVE_NONE] =
    {
        .name = COMPOUND_STRING("-"),
        .description = COMPOUND_STRING(""),
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 0,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .metronomeBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .sketchBanned = TRUE,
        .assistBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_None,
    },

    [MOVE_POUND] =
    {
        .name = COMPOUND_STRING("POUND"),
        .description = COMPOUND_STRING(
            "Pounds the foe with\n"
            "forelegs or tail."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS == GEN_4,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_POUND,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Pound,
    },

    [MOVE_KARATE_CHOP] =
    {
        .name = COMPOUND_STRING("KARATE CHOP"),
        .description = COMPOUND_STRING(
            "A chopping attack with a\n"
            "high critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = B_UPDATED_MOVE_TYPES >= GEN_2 ? TYPE_FIGHTING : TYPE_NORMAL,
        .accuracy = 100,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_KarateChop,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOUBLE_SLAP] =
    {
        .name = COMPOUND_STRING("DOUBLE SLAP"),
        .description = COMPOUND_STRING(
            "Repeatedly slaps the foe\n"
            "2 to 5 times."),
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_POUND},
        .battleAnimScript = gBattleAnimMove_DoubleSlap,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COMET_PUNCH] =
    {
        .name = COMPOUND_STRING("COMET PUNCH"),
        .description = COMPOUND_STRING(
            "Repeatedly punches the foe\n"
            "2 to 5 times."),
        .effect = EFFECT_HIT,
        .power = 18,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CometPunch,
    },

    [MOVE_MEGA_PUNCH] =
    {
        .name = COMPOUND_STRING("MEGA PUNCH"),
        .description = COMPOUND_STRING(
            "A strong punch thrown with\n"
            "incredible power."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_MegaPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PAY_DAY] =
    {
        .name = COMPOUND_STRING("PAY DAY"),
        .description = COMPOUND_STRING(
            "Throws coins at the foe.\n"
            "Money is recovered after."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PAYDAY,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST : CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PayDay,
    },

    [MOVE_FIRE_PUNCH] =
    {
        .name = COMPOUND_STRING("FIRE PUNCH"),
        .description = COMPOUND_STRING(
            "A fiery punch that may burn\n"
            "the foe."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_FIRE_PUNCH,
        .contestComboMoves = {COMBO_STARTER_ICE_PUNCH, COMBO_STARTER_SUNNY_DAY, COMBO_STARTER_THUNDER_PUNCH},
        .battleAnimScript = gBattleAnimMove_FirePunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICE_PUNCH] =
    {
        .name = COMPOUND_STRING("ICE PUNCH"),
        .description = COMPOUND_STRING(
            "An icy punch that may\n"
        #if B_USE_FROSTBITE == TRUE
            "leave the foe with frostbite."),
        #else
            "freeze the foe."),
        #endif
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_ICE_PUNCH,
        .contestComboMoves = {COMBO_STARTER_FIRE_PUNCH, COMBO_STARTER_THUNDER_PUNCH},
        .battleAnimScript = gBattleAnimMove_IcePunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THUNDER_PUNCH] =
    {
        .name = COMPOUND_STRING("THUNDER PUNCH"),
        .description = COMPOUND_STRING(
            "An electrified punch that\n"
            "may paralyze the foe."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_THUNDER_PUNCH,
        .contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_FIRE_PUNCH, COMBO_STARTER_ICE_PUNCH},
        .battleAnimScript = gBattleAnimMove_ThunderPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SCRATCH] =
    {
        .name = COMPOUND_STRING("SCRATCH"),
        .description = COMPOUND_STRING(
            "Scratches the foe with\n"
            "sharp claws."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SCRATCH,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_Scratch,
    },

    [MOVE_VISE_GRIP] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 5, }),
        .name = COMPOUND_STRING("VISE GRIP"),
        .description = COMPOUND_STRING(
            "Grips the foe with large and\n"
            "powerful pincers."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_VICE_GRIP,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ViseGrip,
    },

    [MOVE_GUILLOTINE] =
    {
        .name = COMPOUND_STRING("GUILLOTINE"),
        .description = COMPOUND_STRING(
            "A powerful pincer attack\n"
            "that KOs if it hits."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 30,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_VICE_GRIP},
        .battleAnimScript = gBattleAnimMove_Guillotine,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RAZOR_WIND] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("RAZOR WIND"),
        #if B_UPDATED_MOVE_DATA == GEN_3 || B_UPDATED_MOVE_DATA == GEN_1
            .description = COMPOUND_STRING(
                "A 2-turn move that strikes\n"
                "the foe on the 2nd turn."),
        #else
            .description = COMPOUND_STRING(
                "A 2-turn move with a high\n"
                "critical-hit ratio."),
        #endif
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_3 ? 100 : 75,
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .criticalHitStage = 1,
        #elif B_UPDATED_MOVE_DATA == GEN_2
            .criticalHitStage = 2,
        #else
            .criticalHitStage = 0,
        #endif
        .pp = 10,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .windMove = B_EXTRAPOLATED_MOVE_FLAGS,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNWHIPPEDWHIRLWIND },
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RazorWind,
    },

    [MOVE_SWORDS_DANCE] =
    {
        .name = COMPOUND_STRING("SWORDS DANCE"),
        .description = COMPOUND_STRING(
            "A fighting dance that\n"
            "sharply raises Attack."),
        .effect = EFFECT_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SWORDS_DANCE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SwordsDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CUT] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 5, }),
        .name = COMPOUND_STRING("CUT"),
        .description = COMPOUND_STRING(
            "Cuts the foe with sharp\n"
            "scythes, claws, etc."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_Cut,
    },

    [MOVE_GUST] =
    {
        .name = COMPOUND_STRING("GUST"),
        .description = COMPOUND_STRING(
            "Strikes the foe with a gust\n"
            "of wind whipped up by wings."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = B_UPDATED_MOVE_TYPES >= GEN_2 ? TYPE_FLYING : TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_4) || (B_UPDATED_MOVE_FLAGS < GEN_3),
        .damagesAirborneDoubleDamage = B_UPDATED_MOVE_FLAGS >= GEN_2,
        .windMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Gust,
    },

    [MOVE_WING_ATTACK] =
    {
        .name = COMPOUND_STRING("WING ATTACK"),
        .description = COMPOUND_STRING(
            "Strikes the foe with wings\n"
            "spread wide."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_2 ? 60 : 35,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WingAttack,
    },

    [MOVE_WHIRLWIND] =
    {
        .name = COMPOUND_STRING("WHIRLWIND"),
        .description = COMPOUND_STRING(
            "Blows away the foe, switches\n"
            "it out or ends wild battle."),
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .accuracy = 0,
            .priority = -6,
        #elif B_UPDATED_MOVE_DATA >= GEN_3
            .accuracy = 100,
            .priority = -6,
        #elif B_UPDATED_MOVE_DATA == GEN_2
            .accuracy = 100,
            .priority = -1,
        #else
            .accuracy = 85,
            .priority = 0,
        #endif
        .pp = 20,
        .target = TARGET_SELECTED,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .windMove = TRUE,
        .ignoresProtect = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .copycatBanned = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .assistBanned = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_NEXT_APPEAL_LATER : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STEALTH_ROCK, COMBO_STARTER_SPIKES, COMBO_STARTER_TOXIC_SPIKES},
        .battleAnimScript = gBattleAnimMove_Whirlwind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLY] =
    {
        .name = COMPOUND_STRING("FLY"),
        .description = COMPOUND_STRING(
            "Flies up on the first turn,\n"
            "then strikes the next turn."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 90 : 70,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNFLEWHIGH, .status = STATE_ON_AIR },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Fly,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BIND] =
    {
        .name = COMPOUND_STRING("BIND"),
        .description = COMPOUND_STRING(
            "Binds and squeezes the foe\n"
            "for "BINDING_TURNS" turns."),
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 75,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_BIND,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_VICE_GRIP},
        .battleAnimScript = gBattleAnimMove_Bind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLAM] =
    {
        .name = COMPOUND_STRING("SLAM"),
        .description = COMPOUND_STRING(
            "Slams the foe with a long\n"
            "tail, vine, etc."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_POUND},
        .battleAnimScript = gBattleAnimMove_Slam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_VINE_WHIP] =
    {
        .name = COMPOUND_STRING("VINE WHIP"),
        .description = COMPOUND_STRING(
            "Strikes the foe with\n"
            "slender, whiplike vines."),
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 25,
        #elif B_UPDATED_MOVE_DATA >= GEN_4
            .pp = 15,
        #else
            .pp = 10,
        #endif
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 45 : 35,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_VineWhip,
    },

    [MOVE_STOMP] =
    {
        .name = COMPOUND_STRING("STOMP"),
        .description = COMPOUND_STRING(
            "Stomps the enemy with a big\n"
            "foot. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS >= GEN_2,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_Stomp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOUBLE_KICK] =
    {
        .name = COMPOUND_STRING("DOUBLE KICK"),
        .description = COMPOUND_STRING(
            "A double-kicking attack\n"
            "that strikes the foe twice."),
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DoubleKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEGA_KICK] =
    {
        .name = COMPOUND_STRING("MEGA KICK"),
        .description = COMPOUND_STRING(
            "An extremely powerful kick\n"
            "with intense force."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_MegaKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_JUMP_KICK] =
    {
        .name = COMPOUND_STRING("JUMP KICK"),
        .description = COMPOUND_STRING(
            "A strong jumping kick. May\n"
            "miss and hurt the kicker."),
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 100,
        #elif B_UPDATED_MOVE_DATA == GEN_4
            .power = 85,
        #else
            .power = 70,
        #endif
        .effect = EFFECT_RECOIL_IF_MISS,
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_JumpKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROLLING_KICK] =
    {
        .name = COMPOUND_STRING("ROLLING KICK"),
        .description = COMPOUND_STRING(
            "A fast kick delivered from\n"
            "a rapid spin. May flinch."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 85,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RollingKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SAND_ATTACK] =
    {
        .name = COMPOUND_STRING("SAND ATTACK"),
        .description = COMPOUND_STRING(
            "Reduces the foe's accuracy\n"
            "by hurling sand in its face."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = B_UPDATED_MOVE_TYPES >= GEN_2 ? TYPE_GROUND : TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_SAND_ATTACK,
        .contestComboMoves = {COMBO_STARTER_MUD_SLAP, COMBO_STARTER_SANDSTORM},
        .battleAnimScript = gBattleAnimMove_SandAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HEADBUTT] =
    {
        .name = COMPOUND_STRING("HEADBUTT"),
        .description = COMPOUND_STRING(
            "A ramming attack that may\n"
            "cause flinching."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_Headbutt,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HORN_ATTACK] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 5, }),
        .name = COMPOUND_STRING("HORN ATTACK"),
        .description = COMPOUND_STRING(
            "Jabs the foe with sharp\n"
            "horns."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_HORN_ATTACK,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_HornAttack,
    },

    [MOVE_FURY_ATTACK] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("FURY ATTACK"),
        .description = COMPOUND_STRING(
            "Jabs the foe 2 to 5 times\n"
            "with sharp horns, etc."),
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HORN_ATTACK, COMBO_STARTER_PECK},
        .battleAnimScript = gBattleAnimMove_FuryAttack,
    },

    [MOVE_HORN_DRILL] =
    {
        .name = COMPOUND_STRING("HORN DRILL"),
        .description = COMPOUND_STRING(
            "A one-hit KO attack that\n"
            "uses a horn like a drill."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 30,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HORN_ATTACK},
        .battleAnimScript = gBattleAnimMove_HornDrill,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TACKLE] =
    {
        .name = COMPOUND_STRING("TACKLE"),
        .description = COMPOUND_STRING(
            "Charges the foe with a full-\n"
            "body tackle."),
        #if B_UPDATED_MOVE_DATA >= GEN_7
            .power = 40,
        #elif B_UPDATED_MOVE_DATA >= GEN_5
            .power = 50,
        #else
            .power = 35,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 100 : 95,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DEFENSE_CURL, COMBO_STARTER_HARDEN, COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_Tackle,
    },

    [MOVE_BODY_SLAM] =
    {
        .name = COMPOUND_STRING("BODY SLAM"),
        .description = COMPOUND_STRING(
            "A full-body slam that may\n"
            "cause paralysis."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BodySlam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WRAP] =
    {
        .name = COMPOUND_STRING("WRAP"),
        .description = COMPOUND_STRING(
            "Wraps and squeezes the foe\n"
            BINDING_TURNS" times with vines, etc."),
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 85,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Wrap,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TAKE_DOWN] =
    {
        .name = COMPOUND_STRING("TAKE DOWN"),
        .description = COMPOUND_STRING(
            "A reckless charge attack\n"
            "that also hurts the user."),
        .effect = EFFECT_RECOIL,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .recoilPercentage = 25 },
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_HARDEN},
        .battleAnimScript = gBattleAnimMove_TakeDown,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THRASH] =
    {
        .name = COMPOUND_STRING("THRASH"),
        .description = COMPOUND_STRING(
            "A rampage of 2 to 3 turns\n"
            "that confuses the user."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 120 : 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 20,
        .target = TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .instructBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_USER_MORE_EASILY_STARTLED : CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAGE},
        .battleAnimScript = gBattleAnimMove_Thrash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOUBLE_EDGE] =
    {
        .name = COMPOUND_STRING("DOUBLE-EDGE"),
        .description = COMPOUND_STRING(
            "A life-risking tackle that\n"
            "also hurts the user."),
        .effect = EFFECT_RECOIL,
        .power = B_UPDATED_MOVE_DATA >= GEN_2 ? 120 : 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .recoilPercentage = B_UPDATED_MOVE_DATA >= GEN_3 ? 33 : 25 },
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_HARDEN},
        .battleAnimScript = gBattleAnimMove_DoubleEdge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TAIL_WHIP] =
    {
        .name = COMPOUND_STRING("TAIL WHIP"),
        .description = COMPOUND_STRING(
            "Wags the tail to lower the\n"
            "foe's Defense."),
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_TailWhip,
    },

    [MOVE_POISON_STING] =
    {
        .name = COMPOUND_STRING("POISON STING"),
        .description = COMPOUND_STRING(
            "A toxic attack with barbs,\n"
            "etc., that may poison."),
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 30 : 20,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonSting,
    },

    [MOVE_TWINEEDLE] =
    {
        .name = COMPOUND_STRING("TWINEEDLE"),
        .description = COMPOUND_STRING(
            "Foreleg stingers jab foe\n"
            "twice. May poison."),
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .strikeCount = 2,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 20,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_SAME_TYPE : CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Twineedle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PIN_MISSILE] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("PIN MISSILE"),
        .description = COMPOUND_STRING(
            "Sharp pins are fired to\n"
            "strike 2 to 5 times."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 25 : 14,
        .type = TYPE_BUG,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 95 : 85,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PinMissile,
    },

    [MOVE_LEER] =
    {
        .name = COMPOUND_STRING("LEER"),
        .description = COMPOUND_STRING(
            "Frightens the foes with a\n"
            "leer to lower Defense."),
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION : CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_LEER,
        .contestComboMoves = {COMBO_STARTER_RAGE, COMBO_STARTER_SCARY_FACE},
        .battleAnimScript = gBattleAnimMove_Leer,
    },

    [MOVE_BITE] =
    {
        .name = COMPOUND_STRING("BITE"),
        .description = COMPOUND_STRING(
            "Bites with vicious fangs.\n"
            "May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = B_UPDATED_MOVE_TYPES >= GEN_2 ? TYPE_DARK : TYPE_NORMAL,
        .accuracy = 100,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 30 : 10,
        },
            { .moveEffect = MOVE_EFFECT_BLEED, .chance = 5, }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LEER, COMBO_STARTER_SCARY_FACE},
        .battleAnimScript = gBattleAnimMove_Bite,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GROWL] =
    {
        .name = COMPOUND_STRING("GROWL"),
        .description = COMPOUND_STRING(
            "Growls cutely to reduce the\n"
            "foe's Attack."),
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_Growl,
    },

    [MOVE_ROAR] =
    {
        .name = COMPOUND_STRING("ROAR"),
        .description = COMPOUND_STRING(
            "Switches the foe out\n"
            "or ends wild battle."),
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 0 : 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        #if B_UPDATED_MOVE_DATA >= GEN_3
            .priority = -6,
        #elif B_UPDATED_MOVE_DATA == GEN_2
            .priority = -1,
        #else
            .priority = 0,
        #endif
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .soundMove = TRUE,
        .copycatBanned = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .assistBanned = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_NEXT_APPEAL_LATER : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STEALTH_ROCK, COMBO_STARTER_ENTRAINMENT, COMBO_STARTER_PLAY_NICE, COMBO_STARTER_SPIKES, COMBO_STARTER_TOXIC_SPIKES},
        .battleAnimScript = gBattleAnimMove_Roar,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SING] =
    {
        .name = COMPOUND_STRING("SING"),
        .description = COMPOUND_STRING(
            "A soothing song lulls the\n"
            "foe into a deep slumber."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_SING,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Sing,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUPERSONIC] =
    {
        .name = COMPOUND_STRING("SUPERSONIC"),
        .description = COMPOUND_STRING(
            "Emits bizarre sound waves\n"
            "that may confuse the foe."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Supersonic,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SONIC_BOOM] =
    {
        .name = COMPOUND_STRING("SONIC BOOM"),
        .description = COMPOUND_STRING(
            "Launches shock waves that\n"
            "always inflict 20 HP damage."),
        .effect = EFFECT_FIXED_HP_DAMAGE,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .fixedDamage = 20 },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SonicBoom,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DISABLE] =
    {
        .name = COMPOUND_STRING("DISABLE"),
        .description = COMPOUND_STRING(
        #if B_DISABLE_TURNS >= GEN_5
            "For 4 turns, prevents foe\n"
        #elif B_DISABLE_TURNS == GEN_4
            "For 4-7 turns, prevents foe\n"
        #else
            "For 2-5 turns, prevents foe\n"
        #endif
            "from using last used move."),
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .accuracy = 100,
        #elif B_UPDATED_MOVE_DATA == GEN_4
            .accuracy = 80,
        #else
            .accuracy = 55,
        #endif
        .effect = EFFECT_DISABLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Disable,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ACID] =
    {
        .name = COMPOUND_STRING("ACID"),
        .description = COMPOUND_STRING(
            "Sprays a hide-melting acid.\n"
        #if B_UPDATED_MOVE_DATA >= GEN_4
            "May lower Sp. Def."),
        #else
            "May lower Defense."),
        #endif
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
            .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = B_UPDATED_MOVE_DATA >= GEN_4 ? MOVE_EFFECT_SP_DEF_MINUS_1 : MOVE_EFFECT_DEF_MINUS_1,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 10 : 33,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Acid,
    },

    [MOVE_EMBER] =
    {
        .name = COMPOUND_STRING("EMBER"),
        .description = COMPOUND_STRING(
            "A weak fire attack that may\n"
            "inflict a burn."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Ember,
    },

    [MOVE_FLAMETHROWER] =
    {
        .name = COMPOUND_STRING("FLAMETHROWER"),
        .description = COMPOUND_STRING(
            "A powerful fire attack that\n"
            "may inflict a burn."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Flamethrower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIST] =
    {
        .name = COMPOUND_STRING("MIST"),
        .description = COMPOUND_STRING(
            "Creates a mist that stops\n"
            "reduction of stats."),
        .effect = EFFECT_MIST,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Mist,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATER_GUN] =
    {
        .name = COMPOUND_STRING("WATER GUN"),
        .description = COMPOUND_STRING(
            "Squirts water to attack\n"
            "the foe."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MUD_SPORT, COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_WATER_SPORT},
        .battleAnimScript = gBattleAnimMove_WaterGun,
    },

    [MOVE_HYDRO_PUMP] =
    {
        .name = COMPOUND_STRING("HYDRO PUMP"),
        .description = COMPOUND_STRING(
            "Blasts water at high power\n"
            "to strike the foe."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 110 : 120,
        .type = TYPE_WATER,
        .accuracy = 80,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_HydroPump,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SURF] =
    {
        .name = COMPOUND_STRING("SURF"),
        .description = COMPOUND_STRING(
            "Creates a huge wave, then\n"
        #if B_UPDATED_MOVE_DATA >= GEN_4
            "crashes it down on the field."),
        #else
            "crashes it down on the foes."),
        #endif
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = B_UPDATED_MOVE_DATA >= GEN_4 ? TARGET_FOES_AND_ALLY : TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .damagesUnderwater = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MONS : CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SURF,
        .contestComboMoves = {COMBO_STARTER_DIVE, COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Surf,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICE_BEAM] =
    {
        .name = COMPOUND_STRING("ICE BEAM"),
        .description = COMPOUND_STRING(
            "Blasts the foe with an icy\n"
        #if B_USE_FROSTBITE == TRUE
            "beam. May cause frostbite."),
        #else
            "beam that may freeze it."),
        #endif
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            // The following effect is also relevant in battle_Pike.c
            // If you cherry-pick this to use something other than the config, make sure to update it there too
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_IceBeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BLIZZARD] =
    {
        .name = COMPOUND_STRING("BLIZZARD"),
        .description = COMPOUND_STRING(
            "Hits the foes with an icy\n"
        #if B_USE_FROSTBITE == TRUE
            "storm. May cause frostbite."),
        #else
            "storm that may freeze it."),
        #endif
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 110 : 120,
        .type = TYPE_ICE,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_2 ? 70 : 90,
        .pp = 5,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .alwaysHitsInHailSnow = B_BLIZZARD_HAIL >= GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_POWDER_SNOW},
        .battleAnimScript = gBattleAnimMove_Blizzard,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PSYBEAM] =
    {
        .name = COMPOUND_STRING("PSYBEAM"),
        .description = COMPOUND_STRING(
            "Fires a peculiar ray that\n"
            "may confuse the foe."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_Psybeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BUBBLE_BEAM] =
    {
        .name = COMPOUND_STRING("BUBBLE BEAM"),
        .description = COMPOUND_STRING(
            "Forcefully sprays bubbles\n"
            "that may lower Speed."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 10 : 33,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_BubbleBeam,
    },

    [MOVE_AURORA_BEAM] =
    {
        .name = COMPOUND_STRING("AURORA BEAM"),
        .description = COMPOUND_STRING(
            "Fires a rainbow-colored\n"
            "beam that may lower Attack."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 10 : 33,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_AuroraBeam,
    },

    [MOVE_HYPER_BEAM] =
    {
        .name = COMPOUND_STRING("HYPER BEAM"),
        .description = sHyperBeamDescription,
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HyperBeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PECK] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("PECK"),
        .description = COMPOUND_STRING(
            "Attacks the foe with a\n"
            "jabbing beak, etc."),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_PECK,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Peck,
    },

    [MOVE_DRILL_PECK] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 10, }),
        .name = COMPOUND_STRING("DRILL PECK"),
        .description = COMPOUND_STRING(
            "A corkscrewing attack with\n"
            "the beak acting as a drill."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_PECK},
        .battleAnimScript = gBattleAnimMove_DrillPeck,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUBMISSION] =
    {
        .name = COMPOUND_STRING("SUBMISSION"),
        .description = COMPOUND_STRING(
            "A reckless body slam that\n"
            "also hurts the user."),
        .effect = EFFECT_RECOIL,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .argument = { .recoilPercentage = 25 },
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_Submission,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LOW_KICK] =
    {
        .name = COMPOUND_STRING("LOW KICK"),
        #if B_UPDATED_MOVE_DATA >= GEN_3
            .description = COMPOUND_STRING(
                "A kick that inflicts more\n"
                "damage on heavier foes."),
            .effect = EFFECT_LOW_KICK,
        #else
            .description = COMPOUND_STRING(
                "A low, tripping kick that\n"
                "may cause flinching."),
            .effect = EFFECT_HIT,
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_FLINCH,
                .chance = 30,
            }),
        #endif
        .power = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 50,
        .type = TYPE_FIGHTING,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_3 ? 100 : 90,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WHEN_LATER : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LowKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COUNTER] =
    {
        .name = COMPOUND_STRING("COUNTER"),
        .description = COMPOUND_STRING(
            "Retaliates any physical hit\n"
            "with double the power."),
        .effect = EFFECT_REFLECT_DAMAGE,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_DEPENDS,
        .priority = -5,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .argument = {
            .reflectDamage.damagePercent = 200,
            .reflectDamage.damageCategories = 1u << DAMAGE_CATEGORY_PHYSICAL,
        },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS < GEN_5,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .meFirstBanned = TRUE,
        .metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_2,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_LAST : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TAUNT, COMBO_STARTER_ENCORE, COMBO_STARTER_TORMENT},
        .battleAnimScript = gBattleAnimMove_Counter,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SEISMIC_TOSS] =
    {
        .name = COMPOUND_STRING("SEISMIC TOSS"),
        .description = COMPOUND_STRING(
            "Inflicts damage identical\n"
            "to the user's level."),
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT, COMBO_STARTER_ENTRAINMENT, COMBO_STARTER_PLAY_NICE},
        .battleAnimScript = gBattleAnimMove_SeismicToss,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STRENGTH] =
    {
        .name = COMPOUND_STRING("STRENGTH"),
        .description = COMPOUND_STRING(
            "Builds enormous power,\n"
            "then slams the foe."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Strength,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ABSORB] =
    {
        .name = COMPOUND_STRING("ABSORB"),
        .description = COMPOUND_STRING(
            "Attack that absorbs\n"
            "half the damage inflicted."),
        .effect = EFFECT_ABSORB,
        .power = 20,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_4 ? 25 : 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_Absorb,
    },

    [MOVE_MEGA_DRAIN] =
    {
        .name = COMPOUND_STRING("MEGA DRAIN"),
        .description = sMegaDrainDescription,
        .effect = EFFECT_ABSORB,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .zMove = { .powerOverride = 120 },
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_MegaDrain,
    },

    [MOVE_LEECH_SEED] =
    {
        .name = COMPOUND_STRING("LEECH SEED"),
        .description = COMPOUND_STRING(
            "Plants a seed on the foe to\n"
            "steal HP on every turn."),
        .effect = EFFECT_LEECH_SEED,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS : CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_LEECH_SEED,
        .contestComboMoves = {COMBO_STARTER_GROWTH, COMBO_STARTER_WORRY_SEED, COMBO_STARTER_ROTOTILLER},
        .battleAnimScript = gBattleAnimMove_LeechSeed,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GROWTH] =
    {
        .name = COMPOUND_STRING("GROWTH"),
        .description = COMPOUND_STRING(
        #if B_GROWTH_STAT_RAISE >= GEN_5
            "Forces the body to grow,\n"
            "raising Attack and Sp. Atk."),
        #else
            "Forces the body to grow\n"
            "and heightens Sp. Atk."),
        #endif
        .effect = B_GROWTH_STAT_RAISE >= GEN_5 ? EFFECT_GROWTH : EFFECT_SPECIAL_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 40,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_GROWTH,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Growth,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RAZOR_LEAF] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 5, }),
        .name = COMPOUND_STRING("RAZOR LEAF"),
        .description = COMPOUND_STRING(
            "Cuts enemies with leaves.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GRASS,
        .accuracy = 95,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 25,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .slicingMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_RazorLeaf,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SOLAR_BEAM] =
    {
        .name = COMPOUND_STRING("SOLAR BEAM"),
        .description = COMPOUND_STRING(
            "Absorbs light in one turn,\n"
            "then attacks next turn."),
        .effect = EFFECT_SOLAR_BEAM,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNTOOKSUNLIGHT, .weather = B_WEATHER_SUN },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH, COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_SolarBeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_POISON_POWDER] =
    {
        .name = COMPOUND_STRING("POISON POWDER"),
        .description = COMPOUND_STRING(
            "Scatters a toxic powder\n"
            "that may poison the foe."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 75,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_POISON },
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_POISON_POWDER,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .battleAnimScript = gBattleAnimMove_PoisonPowder,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STUN_SPORE] =
    {
        .name = COMPOUND_STRING("STUN SPORE"),
        .description = COMPOUND_STRING(
            "Scatters a powder that may\n"
            "paralyze the foe."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_PARALYSIS },
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .battleAnimScript = gBattleAnimMove_StunSpore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLEEP_POWDER] =
    {
        .name = COMPOUND_STRING("SLEEP POWDER"),
        .description = COMPOUND_STRING(
            "Scatters a powder that may\n"
            "cause the foe to sleep."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_SLEEP_POWDER,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .battleAnimScript = gBattleAnimMove_SleepPowder,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PETAL_DANCE] =
    {
        .name = COMPOUND_STRING("PETAL DANCE"),
        .description = COMPOUND_STRING(
            "A rampage of 2 to 3 turns\n"
            "that confuses the user."),
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 120,
        #elif B_UPDATED_MOVE_DATA == GEN_4
            .power = 90,
        #else
            .power = 70,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 20,
        .target = TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .danceMove = TRUE,
        .instructBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_USER_MORE_EASILY_STARTLED : CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_PetalDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STRING_SHOT] =
    {
        .name = COMPOUND_STRING("STRING SHOT"),
        .description = COMPOUND_STRING(
            "Binds the foe with string\n"
            "to reduce its Speed."),
        .effect = B_UPDATED_MOVE_DATA >= GEN_6 ? EFFECT_SPEED_DOWN_2 : EFFECT_SPEED_DOWN,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 40,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_STRING_SHOT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StringShot,
    },

    [MOVE_DRAGON_RAGE] =
    {
        .name = COMPOUND_STRING("DRAGON RAGE"),
        .description = COMPOUND_STRING(
            "Launches shock waves that\n"
            "always inflict 40 HP damage."),
        .effect = EFFECT_FIXED_HP_DAMAGE,
        .power = 1,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_4) || (B_UPDATED_MOVE_FLAGS < GEN_3),
        .argument = { .fixedDamage = 40 },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_RAGE,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RUSH, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_DragonRage,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FIRE_SPIN] =
    {
        .name = COMPOUND_STRING("FIRE SPIN"),
        .description = COMPOUND_STRING(
            "Traps the foe in a ring of\n"
            "fire for "BINDING_TURNS" turns."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 35 : 15,
        .type = TYPE_FIRE,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 70,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_FIRE_SPIN,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FireSpin,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THUNDER_SHOCK] =
    {
        .name = COMPOUND_STRING("THUNDER SHOCK"),
        .description = COMPOUND_STRING(
            "An electrical attack that\n"
            "may paralyze the foe."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_ThunderShock,
    },

    [MOVE_THUNDERBOLT] =
    {
        .name = COMPOUND_STRING("THUNDERBOLT"),
        .description = COMPOUND_STRING(
            "A strong electrical attack\n"
            "that may paralyze the foe."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_Thunderbolt,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THUNDER_WAVE] =
    {
        .name = COMPOUND_STRING("THUNDER WAVE"),
        .description = COMPOUND_STRING(
            "A weak jolt of electricity\n"
            "that paralyzes the foe."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_7 ? 90 : 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_PARALYSIS },
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS : CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_THUNDER_WAVE,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_ThunderWave,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THUNDER] =
    {
        .name = COMPOUND_STRING("THUNDER"),
        .description = COMPOUND_STRING(
            "A lightning attack that may\n"
            "cause paralysis."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 110 : 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 70,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .damagesAirborne = B_UPDATED_MOVE_FLAGS >= GEN_2,
        .alwaysHitsInRain = TRUE,
        .accuracy50InSun = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 30 : 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED : CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_LOCK_ON, COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Thunder,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_THROW] =
    {
        .name = COMPOUND_STRING("ROCK THROW"),
        .description = COMPOUND_STRING(
            "Throws small rocks to\n"
            "strike the foe."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ROCK,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_2 ? 90 : 65,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_ROCK_THROW,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockThrow,
    },

    [MOVE_EARTHQUAKE] =
    {
        .name = COMPOUND_STRING("EARTHQUAKE"),
        .description = COMPOUND_STRING(
            "A powerful quake that\n"
            "hits all other POKÃ©MON."),
        .effect = EFFECT_EARTHQUAKE,
        .power = 100,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .damagesUnderground = B_UPDATED_MOVE_FLAGS >= GEN_2,
        .skyBattleBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_EARTHQUAKE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Earthquake,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FISSURE] =
    {
        .name = COMPOUND_STRING("FISSURE"),
        .description = COMPOUND_STRING(
            "A one-hit KO move that\n"
            "drops the foe in a fissure."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 30,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .damagesUnderground = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_EARTHQUAKE},
        .battleAnimScript = gBattleAnimMove_Fissure,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DIG] =
    {
        .name = COMPOUND_STRING("DIG"),
        .description = COMPOUND_STRING(
            "Digs underground the first\n"
            "turn and strikes next turn."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .power = 80,
        #elif B_UPDATED_MOVE_DATA >= GEN_2
            .power = 60,
        #else
            .power = 100,
        #endif
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .skyBattleBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKMNDUGHOLE, .status = STATE_UNDERGROUND },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Dig,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TOXIC] =
    {
        .name = COMPOUND_STRING("TOXIC"),
        .description = COMPOUND_STRING(
            "Poisons the foe with an\n"
            "intensifying toxin."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 85,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_TOXIC },
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .alwaysHitsOnSameType = B_TOXIC_NEVER_MISS >= GEN_6,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_TOXIC,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Toxic,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CONFUSION] =
    {
        .name = COMPOUND_STRING("CONFUSION"),
        .description = COMPOUND_STRING(
            "A psychic attack that may\n"
            "cause confusion."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_CONFUSION,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_KINESIS, COMBO_STARTER_PSYCHIC},
        .battleAnimScript = gBattleAnimMove_Confusion,
    },

    [MOVE_PSYCHIC] =
    {
        .name = COMPOUND_STRING("PSYCHIC"),
        .description = COMPOUND_STRING(
            "A powerful psychic attack\n"
            "that may lower Sp. Def."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 10 : 33,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_PSYCHIC,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_CONFUSION, COMBO_STARTER_KINESIS},
        .battleAnimScript = gBattleAnimMove_Psychic,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HYPNOSIS] =
    {
        .name = COMPOUND_STRING("HYPNOSIS"),
        .description = COMPOUND_STRING(
            "A hypnotizing move that\n"
            "may induce sleep."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 60,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_HYPNOSIS,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Hypnosis,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEDITATE] =
    {
        .name = COMPOUND_STRING("MEDITATE"),
        .description = COMPOUND_STRING(
            "Meditates in a peaceful\n"
            "fashion to raise Attack."),
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_Meditate,
        .validApprenticeMove = TRUE,
    },

    [MOVE_AGILITY] =
    {
        .name = COMPOUND_STRING("AGILITY"),
        .description = COMPOUND_STRING(
            "Relaxes the body to sharply\n"
            "boost Speed."),
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_AGILITY,
        .contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM},
        .battleAnimScript = gBattleAnimMove_Agility,
        .validApprenticeMove = TRUE,
    },

    [MOVE_QUICK_ATTACK] =
    {
        .name = COMPOUND_STRING("QUICK ATTACK"),
        .description = COMPOUND_STRING(
            "An extremely fast attack\n"
            "that always strikes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM},
        .battleAnimScript = gBattleAnimMove_QuickAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RAGE] =
    {
        .name = COMPOUND_STRING("RAGE"),
        .description = COMPOUND_STRING(
            "Raises the user's Attack\n"
            "every time it is hit."),
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RAGE,
        }),
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS : CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_RAGE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Rage,
    },

    [MOVE_TELEPORT] =
    {
        .name = COMPOUND_STRING("TELEPORT"),
        #if B_TELEPORT_BEHAVIOR >= GEN_8
        .description = COMPOUND_STRING(
            "Switches the user out last.\n"
            "Flees when used by wild {PKMN}."),
        #else
        .description = COMPOUND_STRING(
            "A psychic move for fleeing\n"
            "from battle instantly."),
        #endif
        .effect = EFFECT_TELEPORT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = B_UPDATED_MOVE_DATA >= GEN_8 ? -6 : 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CONFUSION, COMBO_STARTER_DOUBLE_TEAM, COMBO_STARTER_KINESIS, COMBO_STARTER_PSYCHIC},
        .battleAnimScript = gBattleAnimMove_Teleport,
    },

    [MOVE_NIGHT_SHADE] =
    {
        .name = COMPOUND_STRING("NIGHT SHADE"),
        .description = COMPOUND_STRING(
            "Inflicts damage identical\n"
            "to the user's level."),
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 1,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NightShade,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIMIC] =
    {
        .name = COMPOUND_STRING("MIMIC"),
        .description = COMPOUND_STRING(
            "Copies last move used by the\n"
            "foe during one battle."),
        .effect = EFFECT_MIMIC,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_3 ? 0 : 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .ignoresSubstitute = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_2,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Mimic,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SCREECH] =
    {
        .name = COMPOUND_STRING("SCREECH"),
        .description = COMPOUND_STRING(
            "Emits a screech to sharply\n"
            "reduce the foe's Defense."),
        .effect = EFFECT_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 40,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Screech,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOUBLE_TEAM] =
    {
        .name = COMPOUND_STRING("DOUBLE TEAM"),
        .description = COMPOUND_STRING(
            "Creates illusory copies to\n"
            "raise evasiveness."),
        .effect = EFFECT_EVASION_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DOUBLE_TEAM,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DoubleTeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RECOVER] =
    {
        .name = COMPOUND_STRING("RECOVER"),
        .description = COMPOUND_STRING(
            "Recovers up to half the\n"
            "user's maximum HP."),
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .pp = 5,
        #elif B_UPDATED_MOVE_DATA >= GEN_4
            .pp = 10,
        #else
            .pp = 20,
        #endif
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_SAME_TYPE : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Recover,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HARDEN] =
    {
        .name = COMPOUND_STRING("HARDEN"),
        .description = COMPOUND_STRING(
            "Stiffens the body's \n"
            "muscles to raise Defense."),
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_HARDEN,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Harden,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MINIMIZE] =
    {
        .name = COMPOUND_STRING("MINIMIZE"),
        .description = COMPOUND_STRING(
            "Minimizes the user's size to\n"
        #if B_MINIMIZE_EVASION >= GEN_5
            "sharply raise evasiveness."),
        #else
            "raise evasiveness."),
        #endif
        .effect = EFFECT_MINIMIZE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 10 : 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Minimize,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SMOKESCREEN] =
    {
        .name = COMPOUND_STRING("SMOKESCREEN"),
        .description = COMPOUND_STRING(
            "Lowers the foe's accuracy\n"
            "using smoke, ink, etc."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SMOG},
        .battleAnimScript = gBattleAnimMove_Smokescreen,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CONFUSE_RAY] =
    {
        .name = COMPOUND_STRING("CONFUSE RAY"),
        .description = COMPOUND_STRING(
            "A sinister ray that\n"
            "confuses the foe."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ConfuseRay,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WITHDRAW] =
    {
        .name = COMPOUND_STRING("WITHDRAW"),
        .description = COMPOUND_STRING(
            "Withdraws the body into its\n"
            "hard shell to raise Defense."),
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 40,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Withdraw,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DEFENSE_CURL] =
    {
        .name = COMPOUND_STRING("DEFENSE CURL"),
        .description = COMPOUND_STRING(
            "Curls up to conceal weak\n"
            "spots and raise Defense."),
        .effect = EFFECT_DEFENSE_CURL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_DEFENSE_CURL,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DefenseCurl,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BARRIER] =
    {
        .name = COMPOUND_STRING("BARRIER"),
        .description = COMPOUND_STRING(
            "Creates a barrier that\n"
            "sharply raises Defense."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Barrier,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LIGHT_SCREEN] =
    {
        .name = COMPOUND_STRING("LIGHT SCREEN"),
        .description = COMPOUND_STRING(
            "Wall of light cuts special\n"
            "damage for 5 turns."),
        .effect = EFFECT_LIGHT_SCREEN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_LightScreen,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HAZE] =
    {
        .name = COMPOUND_STRING("HAZE"),
        .description = COMPOUND_STRING(
            "Creates a black haze that\n"
            "eliminates all stat changes."),
        .effect = EFFECT_HAZE,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_Haze,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REFLECT] =
    {
        .name = COMPOUND_STRING("REFLECT"),
        .description = COMPOUND_STRING(
            "Wall of light cuts physical\n"
            "damage for 5 turns."),
        .effect = EFFECT_REFLECT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_Reflect,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FOCUS_ENERGY] =
    {
        .name = COMPOUND_STRING("FOCUS ENERGY"),
        .description = COMPOUND_STRING(
            "Focuses power to raise the\n"
            "critical-hit ratio."),
        .effect = EFFECT_FOCUS_ENERGY,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .argument = { .status = VOLATILE_FOCUS_ENERGY },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_FOCUS_ENERGY,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FocusEnergy,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BIDE] =
    {
        .name = COMPOUND_STRING("BIDE"),
        .description = COMPOUND_STRING(
            "Endures attack for 2\n"
            "turns to retaliate double."),
        .effect = EFFECT_BIDE,
        .power = 1,
        .type = TYPE_NORMAL,
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .accuracy = 0,
            .priority = 1,
        #elif B_UPDATED_MOVE_DATA >= GEN_2
            .accuracy = 100,
            .priority = 0,
        #else
            .accuracy = 0,
            .priority = 0,
        #endif
        .pp = 10,
        .target = TARGET_USER,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_NEXT_APPEAL_LATER : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Bide,
    },

    [MOVE_METRONOME] =
    {
        .name = COMPOUND_STRING("METRONOME"),
        .description = COMPOUND_STRING(
            "Waggles a finger to use any\n"
            "PokÃ©mon move at random."),
        .effect = EFFECT_METRONOME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = B_UPDATED_MOVE_FLAGS >= GEN_3,
        .instructBanned = TRUE,
        .encoreBanned = (B_UPDATED_MOVE_FLAGS >= GEN_7 || B_UPDATED_MOVE_FLAGS < GEN_3),
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Metronome,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIRROR_MOVE] =
    {
        .name = COMPOUND_STRING("MIRROR MOVE"),
        .description = COMPOUND_STRING(
            "Counters the foe's attack\n"
            "with the same move."),
        .effect = EFFECT_MIRROR_MOVE,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_2 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .copycatBanned = TRUE,
        .sleepTalkBanned = B_UPDATED_MOVE_FLAGS >= GEN_3,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MirrorMove,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SELF_DESTRUCT] =
    {
        .name = COMPOUND_STRING("SELF-DESTRUCT"),
        .description = COMPOUND_STRING(
            "Inflicts severe damage but\n"
            "makes the user faint."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_2 ? 200 : 130,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .explosion = TRUE,
        .parentalBondBanned = TRUE,
        .dampBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MEAN_LOOK, COMBO_STARTER_BLOCK},
        .battleAnimScript = gBattleAnimMove_SelfDestruct,
        .validApprenticeMove = TRUE,
    },

    [MOVE_EGG_BOMB] =
    {
        .name = COMPOUND_STRING("EGG BOMB"),
        .description = COMPOUND_STRING(
            "An egg is forcibly hurled at\n"
            "the foe."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SOFT_BOILED},
        .battleAnimScript = gBattleAnimMove_EggBomb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LICK] =
    {
        .name = COMPOUND_STRING("LICK"),
        .description = COMPOUND_STRING(
            "Licks with a long tongue to\n"
            "injure. May also paralyze."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 30 : 20,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Lick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SMOG] =
    {
        .name = COMPOUND_STRING("SMOG"),
        .description = COMPOUND_STRING(
            "An exhaust-gas attack\n"
            "that may also poison."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 30 : 20,
        .type = TYPE_POISON,
        .accuracy = 70,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 40,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SMOG,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Smog,
    },

    [MOVE_SLUDGE] =
    {
        .name = COMPOUND_STRING("SLUDGE"),
        .description = COMPOUND_STRING(
            "Sludge is hurled to inflict\n"
            "damage. May also poison."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 30 : 40,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SLUDGE,
        .contestComboMoves = {COMBO_STARTER_SLUDGE_BOMB},
        .battleAnimScript = gBattleAnimMove_Sludge,
    },

    [MOVE_BONE_CLUB] =
    {
        .name = COMPOUND_STRING("BONE CLUB"),
        .description = COMPOUND_STRING(
            "Clubs the foe with a bone.\n"
            "May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_BONE_CLUB,
        .contestComboMoves = {COMBO_STARTER_BONEMERANG, COMBO_STARTER_BONE_RUSH, COMBO_STARTER_SHADOW_BONE},
        .battleAnimScript = gBattleAnimMove_BoneClub,
    },

    [MOVE_FIRE_BLAST] =
    {
        .name = COMPOUND_STRING("FIRE BLAST"),
        .description = COMPOUND_STRING(
            "Incinerates everything it\n"
            "strikes. May cause a burn."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 110 : 120,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 10 : 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FireBlast,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATERFALL] =
    {
        .name = COMPOUND_STRING("WATERFALL"),
        .description = COMPOUND_STRING(
            "Charges with speed to climb\n"
            "waterfalls. May flinch."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_FLINCH,
                .chance = 20,
            }),
        #endif
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Waterfall,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CLAMP] =
    {
        .name = COMPOUND_STRING("CLAMP"),
        .description = COMPOUND_STRING(
            "Traps and squeezes the\n"
            "foe for "BINDING_TURNS" turns."),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_WATER,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 75,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 15 : 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_CLAMP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Clamp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWIFT] =
    {
        .name = COMPOUND_STRING("SWIFT"),
        .description = COMPOUND_STRING(
            "Sprays star-shaped rays\n"
            "that never miss."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Swift,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SKULL_BASH] =
    {
        .name = COMPOUND_STRING("SKULL BASH"),
        .description = COMPOUND_STRING(
            "Tucks in the head, then\n"
            "attacks on the next turn."),
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 130 : 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 10 : 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKMNLOWEREDHEAD },
        #if B_UPDATED_MOVE_DATA >= GEN_2
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
                .self = TRUE,
                .onChargeTurnOnly = TRUE,
            }),
        #endif
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SkullBash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPIKE_CANNON] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("SPIKE CANNON"),
        .description = COMPOUND_STRING(
            "Launches sharp spikes that\n"
            "strike 2 to 5 times."),
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SpikeCannon,
    },

    [MOVE_CONSTRICT] =
    {
        .name = COMPOUND_STRING("CONSTRICT"),
        .description = COMPOUND_STRING(
            "Constricts to inflict pain.\n"
            "May lower Speed."),
        .effect = EFFECT_HIT,
        .power = 10,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 10 : 33,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS : CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Constrict,
    },

    [MOVE_AMNESIA] =
    {
        .name = COMPOUND_STRING("AMNESIA"),
        .description = COMPOUND_STRING(
            "Forgets about something\n"
            "and sharply raises Sp. Def."),
        .effect = EFFECT_SPECIAL_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE : CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_AMNESIA,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Amnesia,
        .validApprenticeMove = TRUE,
    },

    [MOVE_KINESIS] =
    {
        .name = COMPOUND_STRING("KINESIS"),
        .description = COMPOUND_STRING(
            "Distracts the foe.\n"
            "May lower accuracy."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 80,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_KINESIS,
        .contestComboMoves = {COMBO_STARTER_CONFUSION, COMBO_STARTER_PSYCHIC},
        .battleAnimScript = gBattleAnimMove_Kinesis,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SOFT_BOILED] =
    {
        .name = COMPOUND_STRING("SOFT-BOILED"),
        .description = COMPOUND_STRING(
            "Recovers up to half the\n"
            "user's maximum HP."),
        .effect = EFFECT_SOFTBOILED,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 5 : 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_FIRST : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SOFT_BOILED,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SoftBoiled,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HIGH_JUMP_KICK] =
    {
        .name = COMPOUND_STRING("HIGH JUMP KICK"),
        .description = COMPOUND_STRING(
            "A jumping knee kick. If it\n"
            "misses, the user is hurt."),
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 130,
        #elif B_UPDATED_MOVE_DATA == GEN_4
            .power = 100,
        #else
            .power = 85,
        #endif
        .effect = EFFECT_RECOIL_IF_MISS,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_HighJumpKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GLARE] =
    {
        .name = COMPOUND_STRING("GLARE"),
        .description = COMPOUND_STRING(
            "Intimidates and frightens\n"
            "the foe into paralysis."),
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .accuracy = 100,
        #elif B_UPDATED_MOVE_DATA == GEN_5
            .accuracy = 90,
        #else
            .accuracy = 75,
        #endif
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_NORMAL,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_PARALYSIS },
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_SAME_TYPE : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_GLARE,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_Glare,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DREAM_EATER] =
    {
        .name = COMPOUND_STRING("DREAM EATER"),
        .description = COMPOUND_STRING(
            "Takes one half the damage\n"
            "inflicted on a sleeping foe."),
        .effect = EFFECT_DREAM_EATER,
        .power = 100,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_HYPNOSIS, COMBO_STARTER_LOVELY_KISS, COMBO_STARTER_SPORE, COMBO_STARTER_SING, COMBO_STARTER_YAWN, COMBO_STARTER_DARK_VOID, COMBO_STARTER_GRASS_WHISTLE, COMBO_STARTER_SLEEP_POWDER},
        .battleAnimScript = gBattleAnimMove_DreamEater,
        .validApprenticeMove = TRUE,
    },

    [MOVE_POISON_GAS] =
    {
        .name = COMPOUND_STRING("POISON GAS"),
        .description = COMPOUND_STRING(
        #if B_UPDATED_MOVE_DATA >= GEN_5
            "Envelops the foes in a toxic\n"
        #else
            "Envelops the foe in a toxic\n"
        #endif
            "gas that may poison."),
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .accuracy = 90,
        #elif B_UPDATED_MOVE_DATA == GEN_5
            .accuracy = 80,
        #else
            .accuracy = 55,
        #endif
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_POISON,
        .pp = 40,
        .target = B_UPDATED_MOVE_DATA >= GEN_5 ? TARGET_BOTH : TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_POISON },
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_POISON_GAS,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonGas,
    },

    [MOVE_BARRAGE] =
    {
        .name = COMPOUND_STRING("BARRAGE"),
        .description = COMPOUND_STRING(
            "Hurls round objects at the\n"
            "foe 2 to 5 times."),
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .ballisticMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Barrage,
    },

    [MOVE_LEECH_LIFE] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("LEECH LIFE"),
        .description = COMPOUND_STRING(
            "Attack that steals half\n"
            "the damage inflicted."),
        .effect = EFFECT_ABSORB,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .absorbPercentage = 50 },
        .makesContact = TRUE,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE : CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LeechLife,
    },

    [MOVE_LOVELY_KISS] =
    {
        .name = COMPOUND_STRING("LOVELY KISS"),
        .description = COMPOUND_STRING(
            "Demands a kiss with a scary\n"
            "face that induces sleep."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUICKLY_GROW_BORED :
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_LOVELY_KISS,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LovelyKiss,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SKY_ATTACK] =
    {
        .name = COMPOUND_STRING("SKY ATTACK"),
        .description = COMPOUND_STRING(
            "2-turn attack. High critical\n"
            "hit ratio, and may flinch."),
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = 140,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = B_UPDATED_MOVE_DATA >= GEN_4 ? STRINGID_CLOAKEDINAHARSHLIGHT : STRINGID_PKMNISGLOWING },
    #if B_UPDATED_MOVE_DATA >= GEN_3
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    #endif
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SkyAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TRANSFORM] =
    {
        .name = COMPOUND_STRING("TRANSFORM"),
        .description = COMPOUND_STRING(
            "Alters the user's cells to\n"
            "become a copy of the foe."),
        .effect = EFFECT_TRANSFORM,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS < GEN_5,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .copycatBanned = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Transform,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BUBBLE] =
    {
        .name = COMPOUND_STRING("BUBBLE"),
        .description = COMPOUND_STRING(
            "Attack using bubbles.\n"
            "May lower the foe's Speed."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 40 : 20,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = B_UPDATED_MOVE_DATA >= GEN_2 ? 10 : 33,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Bubble,
    },

    [MOVE_DIZZY_PUNCH] =
    {
        .name = COMPOUND_STRING("DIZZY PUNCH"),
        #if B_UPDATED_MOVE_DATA >= GEN_2
            .description = COMPOUND_STRING(
                "A rhythmic punch that may\n"
                "confuse the target."),
        #else
            .description = COMPOUND_STRING(
                "The target is hit with\n"
                "rhythmic punches."),
        #endif
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        #if B_UPDATED_MOVE_DATA >= GEN_2
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_CONFUSION,
                .chance = 20,
            }),
        #endif
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DizzyPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPORE] =
    {
        .name = COMPOUND_STRING("SPORE"),
        .description = COMPOUND_STRING(
            "Scatters a cloud of spores\n"
            "that always induce sleep."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SPORE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Spore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLASH] =
    {
        .name = COMPOUND_STRING("FLASH"),
        .description = COMPOUND_STRING(
            "Looses a powerful blast of\n"
            "light that cuts accuracy."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 100 : 70,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Flash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PSYWAVE] =
    {
        .name = COMPOUND_STRING("PSYWAVE"),
        .description = COMPOUND_STRING(
            "Attacks with a psychic\n"
            "wave of varying intensity."),
        .effect = EFFECT_PSYWAVE,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 100 : 80,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_Psywave,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPLASH] =
    {
        .name = COMPOUND_STRING("SPLASH"),
        .description = COMPOUND_STRING(
            "It's just a splash...\n"
            "Has no effect whatsoever."),
        .effect = EFFECT_DO_NOTHING,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_3 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .gravityBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUICKLY_GROW_BORED :
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Splash,
    },

    [MOVE_ACID_ARMOR] =
    {
        .name = COMPOUND_STRING("ACID ARMOR"),
        .description = COMPOUND_STRING(
            "Liquifies the user's body\n"
            "to sharply raise Defense."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 40,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE : CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AcidArmor,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CRABHAMMER] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 10, }),
        .name = COMPOUND_STRING("CRABHAMMER"),
        .description = COMPOUND_STRING(
            "Hammers with a pincer. Has a\n"
            "high critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 100 : 90,
        .type = TYPE_WATER,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 85,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_Crabhammer,
        .validApprenticeMove = TRUE,
    },

    [MOVE_EXPLOSION] =
    {
        .name = COMPOUND_STRING("EXPLOSION"),
        .description = COMPOUND_STRING(
            "Inflicts severe damage but\n"
            "makes the user faint."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_2 ? 250 : 170,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .explosion = TRUE,
        .parentalBondBanned = TRUE,
        .dampBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MEAN_LOOK, COMBO_STARTER_BLOCK},
        .battleAnimScript = gBattleAnimMove_Explosion,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FURY_SWIPES] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("FURY SWIPES"),
        .description = COMPOUND_STRING(
            "Rakes the foe with sharp\n"
            "claws, etc., 2 to 5 times."),
        .effect = EFFECT_HIT,
        .power = 18,
        .type = TYPE_NORMAL,
        .accuracy = 80,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCRATCH},
        .battleAnimScript = gBattleAnimMove_FurySwipes,
    },

    [MOVE_BONEMERANG] =
    {
        .name = COMPOUND_STRING("BONEMERANG"),
        .description = COMPOUND_STRING(
            "Throws a bone boomerang\n"
            "that strikes twice."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_GROUND,
        .accuracy = 90,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .strikeCount = 2,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_BONEMERANG,
        .contestComboMoves = {COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONE_RUSH, COMBO_STARTER_SHADOW_BONE},
        .battleAnimScript = gBattleAnimMove_Bonemerang,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REST] =
    {
        .name = COMPOUND_STRING("REST"),
        .description = COMPOUND_STRING(
            "The user sleeps for 2 turns,\n"
            "restoring HP and status."),
        .effect = EFFECT_REST,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 5 : 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_REST,
        .contestComboMoves = {COMBO_STARTER_BELLY_DRUM, COMBO_STARTER_CHARM, COMBO_STARTER_YAWN},
        .battleAnimScript = gBattleAnimMove_Rest,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_SLIDE] =
    {
        .name = COMPOUND_STRING("ROCK SLIDE"),
        #if B_UPDATED_MOVE_DATA >= GEN_2
            .description = COMPOUND_STRING(
                "Large boulders are hurled.\n"
                "May cause flinching."),
        #else
            .description = COMPOUND_STRING(
                "Hits the foe with an\n"
                "avalanche of rocks."),
        #endif
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        #if B_UPDATED_MOVE_DATA >= GEN_2
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_FLINCH,
                .chance = 30,
            }),
        #endif
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MONS : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ROCK_THROW},
        .battleAnimScript = gBattleAnimMove_RockSlide,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HYPER_FANG] =
    {
        .name = COMPOUND_STRING("HYPER FANG"),
        .description = COMPOUND_STRING(
            "Attacks with sharp fangs.\n"
            "May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        },
            { .moveEffect = MOVE_EFFECT_BLEED, .chance = 10, }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HyperFang,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SHARPEN] =
    {
        .name = COMPOUND_STRING("SHARPEN"),
        .description = COMPOUND_STRING(
            "Reduces the polygon count\n"
            "and raises Attack."),
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Sharpen,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CONVERSION] =
    {
        .name = COMPOUND_STRING("CONVERSION"),
        .description = COMPOUND_STRING(
            "Changes the user's type\n"
        #if B_UPDATED_CONVERSION >= GEN_6
            "into first known move's type."),
        #else
            "into a known move's type."),
        #endif
        .effect = EFFECT_CONVERSION,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Conversion,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TRI_ATTACK] =
    {
        .name = COMPOUND_STRING("TRI ATTACK"),
        #if B_UPDATED_MOVE_DATA >= GEN_2
            .description = COMPOUND_STRING(
                "Fires three types of beams.\n"
                #if B_USE_FROSTBITE == TRUE
                    "May burn/para/frostbite."),
                #else
                    "May burn/paralyze/freeze."),
                #endif
        #else
            .description = COMPOUND_STRING(
                "A triangular field of energy\n"
                "is created and launched."),
        #endif
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        #if B_UPDATED_MOVE_DATA >= GEN_2
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_TRI_ATTACK,
                .chance = 20,
            }),
        #endif
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOCK_ON},
        .battleAnimScript = gBattleAnimMove_TriAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUPER_FANG] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("SUPER FANG"),
        .description = COMPOUND_STRING(
            "Attacks with sharp fangs\n"
            "and cuts half the foe's HP."),
        .effect = EFFECT_FIXED_PERCENT_DAMAGE,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .damagePercentage = 50 },
        .makesContact = TRUE,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCARY_FACE},
        .battleAnimScript = gBattleAnimMove_SuperFang,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLASH] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 10, }),
        .name = COMPOUND_STRING("SLASH"),
        .description = COMPOUND_STRING(
            "Slashes with claws, etc. Has\n"
            "a high critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCRATCH, COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_Slash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUBSTITUTE] =
    {
        .name = COMPOUND_STRING("SUBSTITUTE"),
        .description = COMPOUND_STRING(
            "Creates a decoy using 1/4\n"
            "of the user's maximum HP."),
        .effect = EFFECT_SUBSTITUTE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Substitute,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STRUGGLE] =
    {
        .name = COMPOUND_STRING("STRUGGLE"),
        .description = COMPOUND_STRING(
            "Used only if all PP are gone.\n"
            "Also hurts the user a little."),
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .effect = EFFECT_STRUGGLE,
            .accuracy = 0,
            .pp = 1,
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_RECOIL_HP_25,
                .self = TRUE,
            }),
        #elif B_UPDATED_MOVE_DATA >= GEN_2
            .effect = EFFECT_RECOIL,
            .accuracy = 100,
            .pp = 1,
            .argument = { .recoilPercentage = 25 },
        #else
            .effect = EFFECT_RECOIL,
            .accuracy = 100,
            .pp = 10,
            .argument = { .recoilPercentage = 50 },
        #endif
        .power = 50,
        .type = TYPE_NORMAL,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .copycatBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .battleAnimScript = gBattleAnimMove_Struggle,
        .validApprenticeMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_TOUGH,
    },

    [MOVE_SKETCH] =
    {
        .name = COMPOUND_STRING("SKETCH"),
        .description = COMPOUND_STRING(
            "Copies the foe's last move\n"
            "permanently."),
        .effect = EFFECT_SKETCH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Sketch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TRIPLE_KICK] =
    {
        .name = COMPOUND_STRING("TRIPLE KICK"),
        .description = COMPOUND_STRING(
            "Kicks the foe 3 times in a\n"
            "row with rising intensity."),
        .effect = EFFECT_TRIPLE_KICK,
        .power = 10,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 3,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_TripleKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THIEF] =
    {
        .name = COMPOUND_STRING("THIEF"),
        .description = COMPOUND_STRING(
            "While attacking, it may\n"
            "steal the foe's held item."),
        .effect = EFFECT_STEAL_ITEM,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 40,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 25 : 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE : CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Thief,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPIDER_WEB] =
    {
        .name = COMPOUND_STRING("SPIDER WEB"),
        .description = COMPOUND_STRING(
            "Ensnares the foe to stop it\n"
            "from fleeing or switching."),
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS < GEN_3,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STRING_SHOT},
        .battleAnimScript = gBattleAnimMove_SpiderWeb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIND_READER] =
    {
        .name = COMPOUND_STRING("MIND READER"),
        .description = COMPOUND_STRING(
            "Senses the foe's action to\n"
            "ensure the next move's hit."),
        .effect = EFFECT_LOCK_ON,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 0 : 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_NEXT_APPEAL_EARLIER : CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_MIND_READER,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MindReader,
        .validApprenticeMove = TRUE,
    },

    [MOVE_NIGHTMARE] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_FEAR, .chance = 10, }),
        .name = COMPOUND_STRING("NIGHTMARE"),
        .description = COMPOUND_STRING(
            "Inflicts 1/4 damage on a\n"
            "sleeping foe every turn."),
        .effect = EFFECT_NIGHTMARE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 100 : 0,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS < GEN_3,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOVELY_KISS, COMBO_STARTER_SPORE, COMBO_STARTER_SING, COMBO_STARTER_YAWN, COMBO_STARTER_HYPNOSIS, COMBO_STARTER_DARK_VOID, COMBO_STARTER_GRASS_WHISTLE, COMBO_STARTER_SLEEP_POWDER},
        .battleAnimScript = gBattleAnimMove_Nightmare,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLAME_WHEEL] =
    {
        .name = COMPOUND_STRING("FLAME WHEEL"),
        .description = COMPOUND_STRING(
            "A fiery charge attack that\n"
            "may inflict a burn."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .thawsUser = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FlameWheel,
    },

    [MOVE_SNORE] =
    {
        .name = COMPOUND_STRING("SNORE"),
        .description = COMPOUND_STRING(
            "A loud attack that can only\n"
            "be used asleep. May flinch."),
        .effect = EFFECT_SNORE,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 50 : 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUICKLY_GROW_BORED :
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_REST},
        .battleAnimScript = gBattleAnimMove_Snore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CURSE] =
    {
        .name = COMPOUND_STRING("CURSE"),
        .description = COMPOUND_STRING(
            "A move that functions\n"
            "differently for GHOSTS."),
        .effect = EFFECT_CURSE,
        .power = 0,
        .type = B_UPDATED_MOVE_TYPES >= GEN_5 ? TYPE_GHOST : TYPE_MYSTERY,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_CURSE },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_CURSE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Curse,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLAIL] =
    {
        .name = COMPOUND_STRING("FLAIL"),
        .description = COMPOUND_STRING(
            "Inflicts more damage when\n"
            "the user's HP is down."),
        .effect = EFFECT_FLAIL,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .battleAnimScript = gBattleAnimMove_Flail,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CONVERSION_2] =
    {
        .name = COMPOUND_STRING("CONVERSION 2"),
        .description = COMPOUND_STRING(
            "Makes the user resistant\n"
            "to the last attack's type."),
        .effect = EFFECT_CONVERSION_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = B_UPDATED_MOVE_DATA >= GEN_5 ? TARGET_SELECTED : TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Conversion2,
        .validApprenticeMove = TRUE,
    },

    [MOVE_AEROBLAST] =
    {
        .name = COMPOUND_STRING("AEROBLAST"),
        .description = COMPOUND_STRING(
            "Launches a vacuumed blast.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_EXCITES_AUDIENCE_MORE_IF_LAST :
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Aeroblast,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COTTON_SPORE] =
    {
        .name = COMPOUND_STRING("COTTON SPORE"),
        .description = COMPOUND_STRING(
        #if B_UPDATED_MOVE_DATA >= GEN_6
            "Spores cling to the foes,\n"
        #else
            "Spores cling to the foe,\n"
        #endif
            "sharply reducing Speed."),
        .effect = EFFECT_SPEED_DOWN_2,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 100 : 85,
        .pp = 40,
        .target = B_UPDATED_MOVE_DATA >= GEN_6 ? TARGET_BOTH : TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CottonSpore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REVERSAL] =
    {
        .name = COMPOUND_STRING("REVERSAL"),
        .description = COMPOUND_STRING(
            "Inflicts more damage when\n"
            "the user's HP is down."),
        .effect = EFFECT_FLAIL,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WHEN_LATER : CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .battleAnimScript = gBattleAnimMove_Reversal,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPITE] =
    {
        .name = COMPOUND_STRING("SPITE"),
        .description = COMPOUND_STRING(
            "Spitefully cuts the PP\n"
        #if B_PP_REDUCED_BY_SPITE >= GEN_4
            "of the foe's last move by 4."),
        #else
            "of foe's last move by 2-5."),
        #endif
        .effect = EFFECT_SPITE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresSubstitute = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS : CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CURSE, COMBO_STARTER_ENCORE, COMBO_STARTER_TAUNT, COMBO_STARTER_TORMENT},
        .battleAnimScript = gBattleAnimMove_Spite,
        .validApprenticeMove = TRUE,
    },

    [MOVE_POWDER_SNOW] =
    {
        .name = COMPOUND_STRING("POWDER SNOW"),
        .description = COMPOUND_STRING(
            "Blasts the foes with a snowy\n"
        #if B_USE_FROSTBITE == TRUE
            "gust. May cause frostbite."),
        #else
            "gust. May cause freezing."),
        #endif
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 25,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_POWDER_SNOW,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_PowderSnow,
    },

    [MOVE_PROTECT] =
    {
        .name = COMPOUND_STRING("PROTECT"),
        .description = sProtectDescription,
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .priority = 4,
        #elif B_UPDATED_MOVE_DATA >= GEN_3
            .priority = 3,
        #else
            .priority = 2,
        #endif
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .protectMethod = PROTECT_NORMAL },
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HARDEN},
        .battleAnimScript = gBattleAnimMove_Protect,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MACH_PUNCH] =
    {
        .name = COMPOUND_STRING("MACH PUNCH"),
        .description = COMPOUND_STRING(
            "A punch is thrown at wicked\n"
            "speed to strike first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MachPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SCARY_FACE] =
    {
        .name = COMPOUND_STRING("SCARY FACE"),
        .description = COMPOUND_STRING("Sharply lowers Speed;\ninflicts Fear on the target."),
        .effect = EFFECT_SPEED_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 100 : 90,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SCARY_FACE,
        .contestComboMoves = {COMBO_STARTER_LEER, COMBO_STARTER_RAGE},
        .battleAnimScript = gBattleAnimMove_ScaryFace,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FEINT_ATTACK] =
    {
        .name = COMPOUND_STRING("FEINT ATTACK"),
        .description = COMPOUND_STRING(
            "Draws the foe close, then\n"
            "strikes without fail."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = B_UPDATED_MOVE_DATA >= GEN_4,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT, COMBO_STARTER_LEER, COMBO_STARTER_POUND},
        .battleAnimScript = gBattleAnimMove_FeintAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWEET_KISS] =
    {
        .name = COMPOUND_STRING("SWEET KISS"),
        .description = COMPOUND_STRING(
            "Demands a kiss with a cute\n"
            "look. May cause confusion."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = B_UPDATED_MOVE_TYPES >= GEN_6 ? TYPE_FAIRY : TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_SweetKiss,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BELLY_DRUM] =
    {
        .name = COMPOUND_STRING("BELLY DRUM"),
        .description = COMPOUND_STRING(
            "Maximizes Attack while\n"
            "sacrificing half of max HP."),
        .effect = EFFECT_BELLY_DRUM,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_USER_MORE_EASILY_STARTLED : CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_BELLY_DRUM,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BellyDrum,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLUDGE_BOMB] =
    {
        .name = COMPOUND_STRING("SLUDGE BOMB"),
        .description = COMPOUND_STRING(
            "Sludge is hurled to inflict\n"
            "damage. May also poison."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SLUDGE_BOMB,
        .contestComboMoves = {COMBO_STARTER_SLUDGE},
        .battleAnimScript = gBattleAnimMove_SludgeBomb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MUD_SLAP] =
    {
        .name = COMPOUND_STRING("MUD-SLAP"),
        .description = COMPOUND_STRING(
            "Hurls mud in the foe's face\n"
            "to reduce its accuracy."),
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_MUD_SLAP,
        .contestComboMoves = {COMBO_STARTER_MUD_SPORT, COMBO_STARTER_SAND_ATTACK, COMBO_STARTER_SANDSTORM},
        .battleAnimScript = gBattleAnimMove_MudSlap,
        .validApprenticeMove = TRUE,
    },

    [MOVE_OCTAZOOKA] =
    {
        .name = COMPOUND_STRING("OCTAZOOKA"),
        .description = COMPOUND_STRING(
            "Fires a lump of ink to\n"
            "damage and cut accuracy."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOCK_ON, COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Octazooka,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPIKES] =
    {
        .name = COMPOUND_STRING("SPIKES"),
        .description = COMPOUND_STRING(
            "Sets spikes that hurt a \n"
            "foe switching in."),
        .effect = EFFECT_SPIKES,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .forcePressure = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_SPIKES,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Spikes,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ZAP_CANNON] =
    {
        .name = COMPOUND_STRING("ZAP CANNON"),
        .description = COMPOUND_STRING(
            "Powerful and sure to cause\n"
            "paralysis, but inaccurate."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 120 : 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 50,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_LOCK_ON},
        .battleAnimScript = gBattleAnimMove_ZapCannon,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FORESIGHT] =
    {
        .name = COMPOUND_STRING("FORESIGHT"),
        .description = COMPOUND_STRING(
            "Negates the foe's efforts\n"
            "to heighten evasiveness."),
        .effect = EFFECT_FORESIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 0 : 100,
        .pp = 40,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresSubstitute = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL : CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Foresight,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DESTINY_BOND] =
    {
        .name = COMPOUND_STRING("DESTINY BOND"),
        .description = COMPOUND_STRING(
            "If the user faints, the foe\n"
            "is also made to faint."),
        .effect = EFFECT_DESTINY_BOND,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_FOLLOW_ME },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUICKLY_GROW_BORED :
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CURSE, COMBO_STARTER_ENDURE, COMBO_STARTER_MEAN_LOOK, COMBO_STARTER_ENCORE, COMBO_STARTER_TAUNT, COMBO_STARTER_TORMENT},
        .battleAnimScript = gBattleAnimMove_DestinyBond,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PERISH_SONG] =
    {
        .name = COMPOUND_STRING("PERISH SONG"),
        .description = COMPOUND_STRING(
            "Any PokÃ©mon hearing this\n"
            "song faints in 3 turns."),
        .effect = EFFECT_PERISH_SONG,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUICKLY_GROW_BORED :
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MEAN_LOOK, COMBO_STARTER_SING, COMBO_STARTER_BLOCK},
        .battleAnimScript = gBattleAnimMove_PerishSong,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICY_WIND] =
    {
        .name = COMPOUND_STRING("ICY WIND"),
        .description = COMPOUND_STRING(
            "A chilling attack that\n"
            "lowers the foe's Speed."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 15,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_IcyWind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DETECT] =
    {
        .name = COMPOUND_STRING("DETECT"),
        .description = sProtectDescription,
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_USER,
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .priority = 4,
        #elif B_UPDATED_MOVE_DATA >= GEN_3
            .priority = 3,
        #else
            .priority = 2,
        #endif
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .protectMethod = PROTECT_NORMAL },
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TAUNT},
        .battleAnimScript = gBattleAnimMove_Detect,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BONE_RUSH] =
    {
        .name = COMPOUND_STRING("BONE RUSH"),
        .description = COMPOUND_STRING(
            "Strikes the foe with a bone\n"
            "in hand 2 to 5 times."),
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_GROUND,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 80,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_BONE_RUSH,
        .contestComboMoves = {COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONEMERANG, COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_SHADOW_BONE},
        .battleAnimScript = gBattleAnimMove_BoneRush,
    },

    [MOVE_LOCK_ON] =
    {
        .name = COMPOUND_STRING("LOCK-ON"),
        .description = COMPOUND_STRING(
            "Locks on to the foe to\n"
            "ensure the next move hits."),
        .effect = EFFECT_LOCK_ON,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 0 : 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_NEXT_APPEAL_EARLIER : CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_LOCK_ON,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LockOn,
        .validApprenticeMove = TRUE,
    },

    [MOVE_OUTRAGE] =
    {
        .name = COMPOUND_STRING("OUTRAGE"),
        .description = COMPOUND_STRING(
            "A rampage of 2 to 3 turns\n"
            "that confuses the user."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 120 : 90,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 15,
        .target = TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .instructBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_USER_MORE_EASILY_STARTLED : CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Outrage,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SANDSTORM] =
    {
        .name = COMPOUND_STRING("SANDSTORM"),
        .description = COMPOUND_STRING(
            "Causes a sandstorm that\n"
            "rages for several turns."),
        .effect = EFFECT_WEATHER,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .windMove = TRUE,
        .argument = { .weatherType = BATTLE_WEATHER_SANDSTORM },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SANDSTORM,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Sandstorm,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GIGA_DRAIN] =
    {
        .name = COMPOUND_STRING("GIGA DRAIN"),
        .description = COMPOUND_STRING(
            "Attack that steals half\n"
            "the damage inflicted."),
        .effect = EFFECT_ABSORB,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 75 : 60,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_GigaDrain,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ENDURE] =
    {
        .name = COMPOUND_STRING("ENDURE"),
        .description = COMPOUND_STRING(
            "Endures any attack for\n"
            "1 turn, leaving at least 1HP."),
        .effect = EFFECT_ENDURE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .priority = 4,
        #elif B_UPDATED_MOVE_DATA >= GEN_3
            .priority = 3,
        #else
            .priority = 2,
        #endif
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .protectMethod = PROTECT_NONE },
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_NEXT_APPEAL_LATER : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_ENDURE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Endure,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CHARM] =
    {
        .name = COMPOUND_STRING("CHARM"),
        .description = COMPOUND_STRING(
            "Charms the foe and sharply\n"
            "reduces its Attack."),
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = B_UPDATED_MOVE_TYPES >= GEN_6 ? TYPE_FAIRY : TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_CHARM,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Charm,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROLLOUT] =
    {
        .name = COMPOUND_STRING("ROLLOUT"),
        .description = COMPOUND_STRING(
            "Attack lasting 5 turns\n"
            "with rising intensity."),
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .instructBanned = TRUE,
        .parentalBondBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DEFENSE_CURL, COMBO_STARTER_HARDEN},
        .battleAnimScript = gBattleAnimMove_Rollout,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FALSE_SWIPE] =
    {
        .name = COMPOUND_STRING("FALSE SWIPE"),
        .description = sFalseSwipeDescription,
        .effect = EFFECT_FALSE_SWIPE,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUICKLY_GROW_BORED :
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_FalseSwipe,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWAGGER] =
    {
        .name = COMPOUND_STRING("SWAGGER"),
        .description = COMPOUND_STRING(
            "Confuses the foe, but also\n"
            "sharply raises its Attack."),
        .effect = EFFECT_SWAGGER,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_7 ? 85 : 90,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        //.ignoresSubstitute = TRUE, In Gen4+, the attack raise will no longer bypass Substitute. However, this is tricky to code
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS : CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Swagger,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MILK_DRINK] =
    {
        .name = COMPOUND_STRING("MILK DRINK"),
        .description = COMPOUND_STRING(
            "Recovers up to half the\n"
            "user's maximum HP."),
        .effect = EFFECT_SOFTBOILED,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 5 : 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_FIRST : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MilkDrink,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPARK] =
    {
        .name = COMPOUND_STRING("SPARK"),
        .description = COMPOUND_STRING(
            "An electrified tackle that\n"
            "may paralyze the foe."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_Spark,
    },

    [MOVE_FURY_CUTTER] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("FURY CUTTER"),
        .description = COMPOUND_STRING(
            "Attack that intensifies\n"
            "on each successive hit."),
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 40,
        #elif B_UPDATED_MOVE_DATA == GEN_5
            .power = 20,
        #else
            .power = 10,
        #endif
        .effect = EFFECT_FURY_CUTTER,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_FuryCutter,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STEEL_WING] =
    {
        .name = COMPOUND_STRING("STEEL WING"),
        .description = COMPOUND_STRING(
            "Strikes the foe with hard\n"
            "wings spread wide."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_STEEL,
        .accuracy = 90,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SteelWing,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEAN_LOOK] =
    {
        .name = COMPOUND_STRING("MEAN LOOK"),
        .description = COMPOUND_STRING(
            "Fixes the foe with a mean\n"
            "look that prevents escape."),
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = (B_UPDATED_MOVE_FLAGS >= GEN_6) || (B_UPDATED_MOVE_FLAGS < GEN_3),
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_MEAN_LOOK,
        .contestComboMoves = {COMBO_STARTER_CURSE},
        .battleAnimScript = gBattleAnimMove_MeanLook,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ATTRACT] =
    {
        .name = COMPOUND_STRING("ATTRACT"),
        .description = COMPOUND_STRING(
            "Makes the opposite gender\n"
            "less likely to attack."),
        .effect = EFFECT_ATTRACT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Attract,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLEEP_TALK] =
    {
        .name = COMPOUND_STRING("SLEEP TALK"),
        .description = COMPOUND_STRING(
            "Uses an available move\n"
            "randomly while asleep."),
        .effect = EFFECT_SLEEP_TALK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .mimicBanned = TRUE,
        .encoreBanned = (B_UPDATED_MOVE_FLAGS >= GEN_7 || B_UPDATED_MOVE_FLAGS < GEN_3),
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_REST},
        .battleAnimScript = gBattleAnimMove_SleepTalk,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HEAL_BELL] =
    {
        .name = COMPOUND_STRING("HEAL BELL"),
        .description = COMPOUND_STRING(
            "Chimes soothingly to heal\n"
            "all status abnormalities."),
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE : CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_HEAL_BELL,
        .contestComboMoves = {COMBO_STARTER_LUCKY_CHANT},
        .battleAnimScript = gBattleAnimMove_HealBell,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RETURN] =
    {
        .name = COMPOUND_STRING("RETURN"),
        .description = COMPOUND_STRING(
            "Attack that increases\n"
            "in power with friendship."),
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Return,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PRESENT] =
    {
        .name = COMPOUND_STRING("PRESENT"),
        .description = COMPOUND_STRING(
            "A gift in the form of a\n"
            "bomb. May restore HP."),
        .effect = EFFECT_PRESENT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CELEBRATE, COMBO_STARTER_COVET, COMBO_STARTER_HAPPY_HOUR, COMBO_STARTER_WISH},
        .battleAnimScript = gBattleAnimMove_Present,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FRUSTRATION] =
    {
        .name = COMPOUND_STRING("FRUSTRATION"),
        .description = COMPOUND_STRING(
            "Attack that is stronger\n"
            "if the Trainer is disliked."),
        .effect = EFFECT_FRUSTRATION,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Frustration,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SAFEGUARD] =
    {
        .name = COMPOUND_STRING("SAFEGUARD"),
        .description = COMPOUND_STRING(
            "Protects allies from status\n"
            "problems for 5 turns."),
        .effect = EFFECT_SAFEGUARD,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 25,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Safeguard,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PAIN_SPLIT] =
    {
        .name = COMPOUND_STRING("PAIN SPLIT"),
        .description = COMPOUND_STRING(
            "Adds the user and foe's HP,\n"
            "then shares them equally."),
        .effect = EFFECT_PAIN_SPLIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_3 ? 0 : 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .battleAnimScript = gBattleAnimMove_PainSplit,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SACRED_FIRE] =
    {
        .name = COMPOUND_STRING("SACRED FIRE"),
        .description = COMPOUND_STRING(
            "A mystical fire attack that\n"
            "may inflict a burn."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .thawsUser = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 50,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_LAST : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_SacredFire,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MAGNITUDE] =
    {
        .name = COMPOUND_STRING("MAGNITUDE"),
        .description = COMPOUND_STRING(
            "A ground-shaking attack\n"
            "of random intensity."),
        .effect = EFFECT_MAGNITUDE,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .damagesUnderground = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Magnitude,
    },

    [MOVE_DYNAMIC_PUNCH] =
    {
        .name = COMPOUND_STRING("DYNAMIC PUNCH"),
        .description = COMPOUND_STRING(
            "Powerful and sure to cause\n"
            "confusion, but inaccurate."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 50,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_DynamicPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEGAHORN] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 15, }),
        .name = COMPOUND_STRING("MEGAHORN"),
        .description = COMPOUND_STRING(
            "A brutal ramming attack\n"
            "using out-thrust horns."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_BUG,
        .accuracy = 85,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Megahorn,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DRAGON_BREATH] =
    {
        .name = COMPOUND_STRING("DRAGON BREATH"),
        .description = COMPOUND_STRING(
            "Strikes the foe with a blast\n"
            "of breath. May paralyze."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_BREATH,
        .contestComboMoves = {COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_RUSH, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_DragonBreath,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BATON_PASS] =
    {
        .name = COMPOUND_STRING("BATON PASS"),
        .description = COMPOUND_STRING(
            "Switches out the user while\n"
            "keeping effects in play."),
        .effect = EFFECT_BATON_PASS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION : CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_AGILITY, COMBO_STARTER_AMNESIA, COMBO_STARTER_HONE_CLAWS, COMBO_STARTER_CALM_MIND, COMBO_STARTER_NASTY_PLOT, COMBO_STARTER_ROCK_POLISH},
        .battleAnimScript = gBattleAnimMove_BatonPass,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ENCORE] =
    {
        .name = COMPOUND_STRING("ENCORE"),
        .description = COMPOUND_STRING(
            "Makes the foe repeat its\n"
            "last move over 3 turns."),
        .effect = EFFECT_ENCORE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .encoreBanned = TRUE,
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_ENCORE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Encore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PURSUIT] =
    {
        .name = COMPOUND_STRING("PURSUIT"),
        .description = COMPOUND_STRING(
            "Inflicts bad damage if used\n"
            "on a foe switching out."),
        .effect = EFFECT_PURSUIT,
        .power = 40,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL : CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Pursuit,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RAPID_SPIN] =
    {
        .name = COMPOUND_STRING("RAPID SPIN"),
        .description = COMPOUND_STRING(
            "User spins and removes some\n"
        #if B_SPEED_BUFFING_RAPID_SPIN >= GEN_8
            "effects, while upping speed."),
        #else
            "effects."),
        #endif
        .effect = EFFECT_RAPID_SPIN,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 50 : 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        #if B_SPEED_BUFFING_RAPID_SPIN >= GEN_8
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        #endif
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RapidSpin,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWEET_SCENT] =
    {
        .name = COMPOUND_STRING("SWEET SCENT"),
        .description = COMPOUND_STRING(
        #if B_UPDATED_MOVE_DATA >= GEN_6
            "Allures the foes to harshly\n"
            "reduce evasiveness."),
        #else
            "Allures the foes to reduce\n"
            "evasiveness."),
        #endif
        .effect = B_UPDATED_MOVE_DATA >= GEN_6 ? EFFECT_EVASION_DOWN_2 : EFFECT_EVASION_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_SWEET_SCENT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SweetScent,
        .validApprenticeMove = TRUE,
    },

    [MOVE_IRON_TAIL] =
    {
        .name = COMPOUND_STRING("IRON TAIL"),
        .description = COMPOUND_STRING(
            "Attacks with a rock-hard\n"
            "tail. May lower Defense."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 75,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IronTail,
        .validApprenticeMove = TRUE,
    },

    [MOVE_METAL_CLAW] =
    {
        .name = COMPOUND_STRING("METAL CLAW"),
        .description = COMPOUND_STRING(
            "A claw attack that may\n"
            "raise the user's Attack."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 35,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 10,
        },
            { .moveEffect = MOVE_EFFECT_BLEED, .chance = 5, }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_METAL_SOUND},
        .battleAnimScript = gBattleAnimMove_MetalClaw,
        .validApprenticeMove = TRUE,
    },

    [MOVE_VITAL_THROW] =
    {
        .name = COMPOUND_STRING("VITAL THROW"),
        .description = COMPOUND_STRING(
            "Makes the user's move last,\n"
            "but it never misses."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = -1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_LAST : CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT, COMBO_STARTER_ENTRAINMENT, COMBO_STARTER_PLAY_NICE},
        .battleAnimScript = gBattleAnimMove_VitalThrow,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MORNING_SUN] =
    {
        .name = COMPOUND_STRING("MORNING SUN"),
        .description = COMPOUND_STRING(
            "Restores HP. The amount\n"
            "varies with the weather."),
        .effect = EFFECT_MORNING_SUN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_MorningSun,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SYNTHESIS] =
    {
        .name = COMPOUND_STRING("SYNTHESIS"),
        .description = COMPOUND_STRING(
            "Restores HP. The amount\n"
            "varies with the weather."),
        .effect = EFFECT_SYNTHESIS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Synthesis,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MOONLIGHT] =
    {
        .name = COMPOUND_STRING("MOONLIGHT"),
        .description = COMPOUND_STRING(
            "Restores HP. The amount\n"
            "varies with the weather."),
        .effect = EFFECT_MOONLIGHT,
        .power = 0,
        .type = B_UPDATED_MOVE_TYPES >= GEN_6 ? TYPE_FAIRY : TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Moonlight,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HIDDEN_POWER] =
    {
        .name = COMPOUND_STRING("HIDDEN POWER"),
        .description = COMPOUND_STRING(
        #if B_HIDDEN_POWER_DMG >= GEN_6
            "The type varies\n"
            "with the user."),
        #else
            "The type and effectiveness\n"
            "vary with the user."),
        #endif
        .power = B_HIDDEN_POWER_DMG >= GEN_6 ? 60 : 1,
        .effect = EFFECT_HIDDEN_POWER,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HiddenPower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CROSS_CHOP] =
    {
        .name = COMPOUND_STRING("CROSS CHOP"),
        .description = COMPOUND_STRING(
            "A double-chopping attack.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_CrossChop,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TWISTER] =
    {
        .name = COMPOUND_STRING("TWISTER"),
        .description = COMPOUND_STRING(
            "Whips up a vicious twister\n"
            "to tear at foes. May flinch."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .damagesAirborneDoubleDamage = TRUE,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Twister,
    },

    [MOVE_RAIN_DANCE] =
    {
        .name = COMPOUND_STRING("RAIN DANCE"),
        .description = COMPOUND_STRING(
            "Boosts the power of Water-\n"
            "type moves for 5 turns."),
        .effect = EFFECT_WEATHER,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .argument = { .weatherType =  BATTLE_WEATHER_RAIN },
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_BEAUTY : CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_RAIN_DANCE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RainDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUNNY_DAY] =
    {
        .name = COMPOUND_STRING("SUNNY DAY"),
        .description = COMPOUND_STRING(
            "Boosts the power of Fire-\n"
            "type moves for 5 turns."),
        .effect = EFFECT_WEATHER,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .argument = { .weatherType = BATTLE_WEATHER_SUN },
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SUNNY_DAY,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SunnyDay,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CRUNCH] =
    {
        .name = COMPOUND_STRING("CRUNCH"),
        .description = COMPOUND_STRING(
            "Crunches with sharp fangs.\n"
        #if B_UPDATED_MOVE_DATA >= GEN_4
            "May lower Defense."),
        #else
            "May lower Sp. Def."),
        #endif
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
            .additionalEffects = ADDITIONAL_EFFECTS({
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
        #else
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
        #endif
            .chance = 20,
        },
            { .moveEffect = MOVE_EFFECT_BLEED, .chance = 10, }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCARY_FACE},
        .battleAnimScript = gBattleAnimMove_Crunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIRROR_COAT] =
    {
        .name = COMPOUND_STRING("MIRROR COAT"),
        .description = COMPOUND_STRING(
            "Counters the foe's special\n"
            "attack at double the power."),
        .effect = EFFECT_REFLECT_DAMAGE,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_DEPENDS,
        .priority = -5,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = {
            .reflectDamage.damagePercent = 200,
            .reflectDamage.damageCategories = 1u << DAMAGE_CATEGORY_SPECIAL,
        },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS < GEN_5,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = B_UPDATED_MOVE_FLAGS <= GEN_8,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_LAST : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TAUNT, COMBO_STARTER_ENCORE, COMBO_STARTER_TORMENT},
        .battleAnimScript = gBattleAnimMove_MirrorCoat,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PSYCH_UP] =
    {
        .name = COMPOUND_STRING("PSYCH UP"),
        .description = COMPOUND_STRING(
            "Copies foe's stat changes\n"
            "and gives to the user."),
        .effect = EFFECT_PSYCH_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = B_UPDATED_MOVE_FLAGS < GEN_5,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PsychUp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_EXTREME_SPEED] =
    {
        .name = COMPOUND_STRING("EXTREME SPEED"),
        .description = COMPOUND_STRING(
            "An extremely fast and\n"
            "powerful attack."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = B_UPDATED_MOVE_DATA >= GEN_5 ? 2 : 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ExtremeSpeed,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ANCIENT_POWER] =
    {
        .name = COMPOUND_STRING("ANCIENT POWER"),
        .description = COMPOUND_STRING(
            "Attack that may raise\n"
            "all stats."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = B_UPDATED_MOVE_DATA < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AncientPower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SHADOW_BALL] =
    {
        .name = COMPOUND_STRING("SHADOW BALL"),
        .description = COMPOUND_STRING(
            "Hurls a black blob that may\n"
            "lower the foe's Sp. Def."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 20,
        },
            { .moveEffect = MOVE_EFFECT_FEAR, .chance = 5, }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShadowBall,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FUTURE_SIGHT] =
    {
        .name = COMPOUND_STRING("FUTURE SIGHT"),
        .description = COMPOUND_STRING(
            "Heightens inner power to\n"
            "strike 2 turns later."),
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 120,
        #elif B_UPDATED_MOVE_DATA == GEN_5
            .power = 100,
        #else
            .power = 80,
        #endif
        .effect = EFFECT_FUTURE_SIGHT,
        .type = TYPE_PSYCHIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 100 : 90,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_SAME_TYPE : CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_CONFUSION, COMBO_STARTER_KINESIS, COMBO_STARTER_PSYCHIC},
        .battleAnimScript = gBattleAnimMove_FutureSight,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_SMASH] =
    {
        .name = COMPOUND_STRING("ROCK SMASH"),
        .description = COMPOUND_STRING(
            "A rock-crushing attack\n"
            "that may lower Defense."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 40 : 20,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockSmash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WHIRLPOOL] =
    {
        .name = COMPOUND_STRING("WHIRLPOOL"),
        .description = COMPOUND_STRING(
            "Traps and hurts the foe in\n"
            "a whirlpool for "BINDING_TURNS" turns."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 35 : 15,
        .type = TYPE_WATER,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 70,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .damagesUnderwater = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_WHIRLPOOL,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Whirlpool,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BEAT_UP] =
    {
        .name = COMPOUND_STRING("BEAT UP"),
        .description = COMPOUND_STRING(
            "Summons party PokÃ©mon to\n"
            "join in the attack."),
        .effect = EFFECT_BEAT_UP,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 1 : 10,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BEAT_UP_MESSAGE,
            .preAttackEffect = TRUE,
            .self = TRUE,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION : CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BeatUp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FAKE_OUT] =
    {
        .name = COMPOUND_STRING("FAKE OUT"),
        .description = COMPOUND_STRING(
            "Moves 1st and flinches. Only\n"
            "works on user's 1st turn."),
        .priority = B_UPDATED_MOVE_DATA >= GEN_5 ? 3 : 1,
        .makesContact = B_UPDATED_MOVE_DATA >= GEN_4,
        .effect = EFFECT_FIRST_TURN_ONLY,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 100,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_FAKE_OUT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FakeOut,
        .validApprenticeMove = TRUE,
    },

    [MOVE_UPROAR] =
    {
        .name = COMPOUND_STRING("UPROAR"),
        .description = COMPOUND_STRING(
        #if B_UPROAR_TURNS >= GEN_5
            "Causes an uproar for 3\n"
        #else
            "Causes an uproar for 2 to 5\n"
        #endif
            "turns and prevents sleep."),
        .effect = EFFECT_UPROAR,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .parentalBondBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_UPROAR,
            .self = TRUE,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Uproar,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STOCKPILE] =
    {
        .name = COMPOUND_STRING("STOCKPILE"),
        .description = COMPOUND_STRING(
            "Charges up power for up to\n"
            "3 turns."),
        .effect = EFFECT_STOCKPILE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_4 ? 20 : 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_STOCKPILE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Stockpile,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPIT_UP] =
    {
        .name = COMPOUND_STRING("SPIT UP"),
        .description = COMPOUND_STRING(
            "Releases stockpiled power\n"
            "(the more the better)."),
        .effect = EFFECT_SPIT_UP,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STOCKPILE},
        .battleAnimScript = gBattleAnimMove_SpitUp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWALLOW] =
    {
        .name = COMPOUND_STRING("SWALLOW"),
        .description = COMPOUND_STRING(
            "Absorbs stockpiled power\n"
            "and restores HP."),
        .effect = EFFECT_SWALLOW,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STOCKPILE},
        .battleAnimScript = gBattleAnimMove_Swallow,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HEAT_WAVE] =
    {
        .name = COMPOUND_STRING("HEAT WAVE"),
        .description = COMPOUND_STRING(
            "Exhales a hot breath on the\n"
            "foes. May inflict a burn."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 95 : 100,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 10,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MONS : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_HeatWave,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HAIL] =
    {
        .name = COMPOUND_STRING("HAIL"),
        #if B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW
            .description = COMPOUND_STRING(
                "Summons a snowstorm that\n"
                "lasts for five turns."),
        #else
            .description = COMPOUND_STRING(
                "Summons a hailstorm that\n"
                "strikes every turn."),
        #endif
        .effect = EFFECT_WEATHER,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .argument = { .weatherType = (B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW) ? BATTLE_WEATHER_SNOW : BATTLE_WEATHER_HAIL },
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_HAIL,
        .contestComboMoves = {0},
        .battleAnimScript = (B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW) ? gBattleAnimMove_Snowscape : gBattleAnimMove_Hail,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TORMENT] =
    {
        .name = COMPOUND_STRING("TORMENT"),
        .description = COMPOUND_STRING(
            "Torments the foe and stops\n"
            "successive use of a move."),
        .effect = EFFECT_TORMENT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_TORMENT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Torment,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLATTER] =
    {
        .name = COMPOUND_STRING("FLATTER"),
        .description = COMPOUND_STRING(
            "Confuses the foe, but\n"
            "raises its Sp. Atk."),
        .effect = EFFECT_FLATTER,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_Flatter,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WILL_O_WISP] =
    {
        .name = COMPOUND_STRING("WILL-O-WISP"),
        .description = COMPOUND_STRING(
            "Inflicts a burn on the foe\n"
            "with intense fire."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 85 : 75,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_BURN },
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_WILL_O_WISP,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_WillOWisp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEMENTO] =
    {
        .name = COMPOUND_STRING("MEMENTO"),
        .description = COMPOUND_STRING(
            "The user faints and harshly\n"
            "lowers foes Atk and Sp.Atk."),
        .effect = EFFECT_MEMENTO,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 100 : 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESTORE_REPLACEMENT_HP },
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MEAN_LOOK, COMBO_STARTER_BLOCK},
        .battleAnimScript = gBattleAnimMove_Memento,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FACADE] =
    {
        .name = COMPOUND_STRING("FACADE"),
        .description = COMPOUND_STRING(
            "Boosts power when burned,\n"
            "paralyzed, or poisoned."),
        .effect = EFFECT_FACADE,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Facade,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FOCUS_PUNCH] =
    {
        .name = COMPOUND_STRING("FOCUS PUNCH"),
        .description = COMPOUND_STRING(
            "Powerful attack, moves last.\n"
            "The user flinches if hit."),
        .effect = EFFECT_FOCUS_PUNCH,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = -3,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        .punchingMove = TRUE,
        .meFirstBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_LAST : CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_FocusPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SMELLING_SALTS] =
    {
        .name = COMPOUND_STRING("SMELLING SALTS"),
        .description = COMPOUND_STRING(
            "Powerful against paralyzed\n"
            "foes, but also heals them."),
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 70 : 60,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .status = STATUS1_PARALYSIS },
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_STATUS,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL : CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FORCE_PALM, COMBO_STARTER_THUNDER_WAVE, COMBO_STARTER_GLARE},
        .battleAnimScript = gBattleAnimMove_SmellingSalts,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FOLLOW_ME] =
    {
        .name = COMPOUND_STRING("FOLLOW ME"),
        .description = COMPOUND_STRING(
            "Draws attention to make\n"
            "foes attack only the user."),
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = B_UPDATED_MOVE_DATA >= GEN_6 ? 2 : 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FollowMe,
        .validApprenticeMove = TRUE,
    },

    [MOVE_NATURE_POWER] =
    {
        .name = COMPOUND_STRING("NATURE POWER"),
        .description = COMPOUND_STRING(
            "The type of attack varies\n"
            "depending on the location."),
        .effect = EFFECT_NATURE_POWER,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = B_UPDATED_MOVE_FLAGS >= GEN_6 ? TARGET_SELECTED : TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = (B_UPDATED_MOVE_FLAGS >= GEN_7 || B_UPDATED_MOVE_FLAGS < GEN_3),
        .assistBanned = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .mimicBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NaturePower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CHARGE] =
    {
        .name = COMPOUND_STRING("CHARGE"),
        .description = COMPOUND_STRING(
            "Charges power to boost the\n"
            "Electric move used next."),
        .effect = EFFECT_CHARGE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_CHARGE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Charge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TAUNT] =
    {
        .name = COMPOUND_STRING("TAUNT"),
        .description = COMPOUND_STRING(
            "Taunts the foe into only\n"
            "using attack moves."),
        .effect = EFFECT_TAUNT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_4,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION : CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_TAUNT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Taunt,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HELPING_HAND] =
    {
        .name = COMPOUND_STRING("HELPING HAND"),
        .description = COMPOUND_STRING(
            "Boosts the power of ally\n"
            "recipient's moves."),
        .effect = EFFECT_HELPING_HAND,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = B_UPDATED_MOVE_DATA >= GEN_4 ? TARGET_ALLY : TARGET_USER,
        .priority = 5,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HelpingHand,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TRICK] =
    {
        .name = COMPOUND_STRING("TRICK"),
        .description = COMPOUND_STRING(
            "Tricks the foe into trading\n"
            "held items."),
        .effect = EFFECT_TRICK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Trick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROLE_PLAY] =
    {
        .name = COMPOUND_STRING("ROLE PLAY"),
        .description = COMPOUND_STRING(
            "Mimics the target and\n"
            "copies its Ability."),
        .effect = EFFECT_ROLE_PLAY,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RolePlay,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WISH] =
    {
        .name = COMPOUND_STRING("WISH"),
        .description = COMPOUND_STRING(
            "A wish that restores HP.\n"
            "It takes time to work."),
        .effect = EFFECT_WISH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .healingMove = TRUE,
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_LAST : CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_WISH,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Wish,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ASSIST] =
    {
        .name = COMPOUND_STRING("ASSIST"),
        .description = COMPOUND_STRING(
            "Attacks randomly with one\n"
            "of the partner's moves."),
        .effect = EFFECT_ASSIST,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = (B_UPDATED_MOVE_FLAGS >= GEN_7 || B_UPDATED_MOVE_FLAGS < GEN_3),
        .metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Assist,
        .validApprenticeMove = TRUE,
    },

    [MOVE_INGRAIN] =
    {
        .name = COMPOUND_STRING("INGRAIN"),
        .description = COMPOUND_STRING(
            "Lays roots that restore HP.\n"
            "The user can't switch out."),
        .effect = EFFECT_INGRAIN,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Ingrain,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUPERPOWER] =
    {
        .name = COMPOUND_STRING("SUPERPOWER"),
        .description = COMPOUND_STRING(
            "Boosts strength sharply,\n"
            "but lowers abilities."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_DEF_DOWN,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOCK_ON, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_Superpower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MAGIC_COAT] =
    {
        .name = COMPOUND_STRING("MAGIC COAT"),
        .description = COMPOUND_STRING(
            "Reflects special effects\n"
            "back to the attacker."),
        .effect = EFFECT_MAGIC_COAT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = TARGET_DEPENDS,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_2 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_LAST : CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MagicCoat,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RECYCLE] =
    {
        .name = COMPOUND_STRING("RECYCLE"),
        .description = COMPOUND_STRING(
            "Recycles a used item for\n"
            "one more use."),
        .effect = EFFECT_RECYCLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE : CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Recycle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REVENGE] =
    {
        .name = COMPOUND_STRING("REVENGE"),
        .description = sRevengeDescription,
        .effect = EFFECT_REVENGE,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = -4,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_LAST : CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_REVENGE,
        .contestComboMoves = {COMBO_STARTER_PAYBACK},
        .battleAnimScript = gBattleAnimMove_Revenge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BRICK_BREAK] =
    {
        .name = COMPOUND_STRING("BRICK BREAK"),
        .description = COMPOUND_STRING(
            "Destroys barriers such as\n"
            "REFLECT and causes damage."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BREAK_SCREEN,
            .preAttackEffect = TRUE,
        }),
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_BrickBreak,
        .validApprenticeMove = TRUE,
    },

    [MOVE_YAWN] =
    {
        .name = COMPOUND_STRING("YAWN"),
        .description = COMPOUND_STRING(
            "Lulls the foe into yawning,\n"
            "then sleeping next turn."),
        .effect = EFFECT_YAWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_YAWN,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Yawn,
        .validApprenticeMove = TRUE,
    },

    [MOVE_KNOCK_OFF] =
    {
        .name = COMPOUND_STRING("KNOCK OFF"),
        .description = COMPOUND_STRING(
            "Knocks down the foe's held\n"
            "item to prevent its use."),
        .effect = EFFECT_KNOCK_OFF,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 65 : 20,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MON : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        .battleAnimScript = gBattleAnimMove_KnockOff,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ENDEAVOR] =
    {
        .name = COMPOUND_STRING("ENDEAVOR"),
        .description = COMPOUND_STRING(
            "Cuts foe's HP to equal\n"
            "user's HP."),
        .effect = EFFECT_ENDEAVOR,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .battleAnimScript = gBattleAnimMove_Endeavor,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ERUPTION] =
    {
        .name = COMPOUND_STRING("ERUPTION"),
        .description = COMPOUND_STRING(
            "The higher the user's HP,\n"
            "the more damage caused."),
        .effect = EFFECT_POWER_BASED_ON_USER_HP,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_USER_MORE_EASILY_STARTLED : CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_EARTHQUAKE, COMBO_STARTER_ENDURE, COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Eruption,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SKILL_SWAP] =
    {
        .name = COMPOUND_STRING("SKILL SWAP"),
        .description = COMPOUND_STRING(
            "The user swaps special\n"
            "abilities with the target."),
        .effect = EFFECT_SKILL_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SkillSwap,
        .validApprenticeMove = TRUE,
    },

    [MOVE_IMPRISON] =
    {
        .name = COMPOUND_STRING("IMPRISON"),
        .description = COMPOUND_STRING(
            "Prevents foes from using\n"
            "moves known by the user."),
        .effect = EFFECT_IMPRISON,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_2 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .forcePressure = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_DONT_EXCITE_AUDIENCE : CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Imprison,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REFRESH] =
    {
        .name = COMPOUND_STRING("REFRESH"),
        .description = COMPOUND_STRING(
            "Heals poisoning, paralysis,\n"
            "or a burn."),
        .effect = EFFECT_REFRESH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SING, COMBO_STARTER_WATER_SPORT},
        .battleAnimScript = gBattleAnimMove_Refresh,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GRUDGE] =
    {
        .name = COMPOUND_STRING("GRUDGE"),
        .description = COMPOUND_STRING(
            "If the user faints, deletes\n"
            "all PP of foe's last move."),
        .effect = EFFECT_GRUDGE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_FOLLOW_ME },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN : CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CURSE, COMBO_STARTER_ENCORE, COMBO_STARTER_TAUNT, COMBO_STARTER_TORMENT},
        .battleAnimScript = gBattleAnimMove_Grudge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SNATCH] =
    {
        .name = COMPOUND_STRING("SNATCH"),
        .description = COMPOUND_STRING(
            "Steals the effects of the\n"
            "move the target uses next."),
        .effect = EFFECT_SNATCH,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_DEPENDS,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresSubstitute = TRUE,
        .forcePressure = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE : CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Snatch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SECRET_POWER] =
    {
        .name = COMPOUND_STRING("SECRET POWER"),
        .description = COMPOUND_STRING(
            "Attack with effects\n"
            "that vary by location."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SECRET_POWER,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SecretPower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DIVE] =
    {
        .name = COMPOUND_STRING("DIVE"),
        .description = COMPOUND_STRING(
            "Dives underwater the first\n"
            "turn and strikes next turn."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 80 : 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .skyBattleBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNHIDUNDERWATER, .status = STATE_UNDERWATER },
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_DIVE,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SURF},
        .battleAnimScript = gBattleAnimMove_Dive,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ARM_THRUST] =
    {
        .name = COMPOUND_STRING("ARM THRUST"),
        .description = COMPOUND_STRING(
            "Straight-arm punches that\n"
            "strike the foe 2 to 5 times."),
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT, COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_ArmThrust,
    },

    [MOVE_CAMOUFLAGE] =
    {
        .name = COMPOUND_STRING("CAMOUFLAGE"),
        .description = COMPOUND_STRING(
            "Alters the PokÃ©mon's type\n"
            "depending on the location."),
        .effect = EFFECT_CAMOUFLAGE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES : CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Camouflage,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TAIL_GLOW] =
    {
        .name = COMPOUND_STRING("TAIL GLOW"),
        .description = COMPOUND_STRING(
        #if B_UPDATED_MOVE_DATA >= GEN_5
            "Flash light that drastically\n"
        #else
            "Flashes a light that sharply\n"
        #endif
            "raises Sp. Atk."),
        .effect = B_UPDATED_MOVE_DATA >= GEN_5 ? EFFECT_SPECIAL_ATTACK_UP_3 : EFFECT_SPECIAL_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TailGlow,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LUSTER_PURGE] =
    {
        .name = COMPOUND_STRING("LUSTER PURGE"),
        .description = COMPOUND_STRING(
            "Attacks with a burst of\n"
            "light. May lower Sp. Def."),
        .effect = EFFECT_HIT,
        .power = (B_UPDATED_MOVE_DATA >= GEN_9) ? 95 : 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL : CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_LusterPurge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIST_BALL] =
    {
        .name = COMPOUND_STRING("MIST BALL"),
        .description = COMPOUND_STRING(
            "Attacks with a flurry of\n"
            "down. May lower Sp. Atk."),
        .effect = EFFECT_HIT,
        .power = (B_UPDATED_MOVE_DATA >= GEN_9) ? 95 : 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_MistBall,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FEATHER_DANCE] =
    {
        .name = COMPOUND_STRING("FEATHER DANCE"),
        .description = COMPOUND_STRING(
            "Envelops the foe with down\n"
            "to sharply reduce Attack."),
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .danceMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FeatherDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TEETER_DANCE] =
    {
        .name = COMPOUND_STRING("TEETER DANCE"),
        .description = COMPOUND_STRING(
            "Confuses all PokÃ©mon on\n"
            "the scene."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .danceMove = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_4,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TeeterDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BLAZE_KICK] =
    {
        .name = COMPOUND_STRING("BLAZE KICK"),
        .description = COMPOUND_STRING(
            "A kick with a high critical-\n"
            "hit ratio. May cause a burn."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY, COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_BlazeKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MUD_SPORT] =
    {
        .name = COMPOUND_STRING("MUD SPORT"),
        .description = COMPOUND_STRING(
            "Covers the user in mud to\n"
            "weaken all Electric moves."),
        // in theory this should mention 5 turns (gen 6+)
        .effect = EFFECT_MUD_SPORT,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 15,
        .target = TARGET_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_MUD_SPORT,
        .contestComboMoves = {COMBO_STARTER_MUD_SLAP, COMBO_STARTER_SANDSTORM, COMBO_STARTER_WATER_SPORT},
        .battleAnimScript = gBattleAnimMove_MudSport,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICE_BALL] =
    {
        .name = COMPOUND_STRING("ICE BALL"),
        .description = COMPOUND_STRING(
            "A 5-turn attack that gains\n"
            "power on successive hits."),
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ballisticMove = TRUE,
        .instructBanned = TRUE,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_DEFENSE_CURL},
        .battleAnimScript = gBattleAnimMove_IceBall,
    },

    [MOVE_NEEDLE_ARM] =
    {
        .name = COMPOUND_STRING("NEEDLE ARM"),
        .description = COMPOUND_STRING(
            "Attacks with thorny arms.\n"
            "May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NeedleArm,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLACK_OFF] =
    {
        .name = COMPOUND_STRING("SLACK OFF"),
        .description = COMPOUND_STRING(
            "Slacks off and restores\n"
            "half the maximum HP."),
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 5 : 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUICKLY_GROW_BORED :
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SlackOff,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HYPER_VOICE] =
    {
        .name = COMPOUND_STRING("HYPER VOICE"),
        .description = COMPOUND_STRING(
            "A loud attack that uses\n"
            "sound waves to injure."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MONS : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HyperVoice,
        .validApprenticeMove = TRUE,
    },

    [MOVE_POISON_FANG] =
    {
        .name = COMPOUND_STRING("POISON FANG"),
        .description = COMPOUND_STRING(
            "A sharp-fanged attack.\n"
            "May badly poison the foe."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TOXIC,
            .chance = B_UPDATED_MOVE_DATA >= GEN_6 ? 50 : 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonFang,
    },

    [MOVE_CRUSH_CLAW] =
    {
        .name = COMPOUND_STRING("CRUSH CLAW"),
        .description = COMPOUND_STRING(
            "Tears at the foe with sharp\n"
            "claws. May lower Defense."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_CrushClaw,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BLAST_BURN] =
    {
        .name = COMPOUND_STRING("BLAST BURN"),
        .description = COMPOUND_STRING(
            "Powerful, but leaves the\n"
            "user immobile the next turn."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_BlastBurn,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HYDRO_CANNON] =
    {
        .name = COMPOUND_STRING("HYDRO CANNON"),
        .description = COMPOUND_STRING(
            "Powerful, but leaves the\n"
            "user immobile the next turn."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_HydroCannon,
        .validApprenticeMove = TRUE,
    },

    [MOVE_METEOR_MASH] =
    {
        .name = COMPOUND_STRING("METEOR MASH"),
        .description = COMPOUND_STRING(
            "Fires a meteor-like punch.\n"
            "May raise Attack."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 100,
        .type = TYPE_STEEL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 85,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 20,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MeteorMash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ASTONISH] =
    {
        .name = COMPOUND_STRING("ASTONISH"),
        .description = COMPOUND_STRING(
            "Attack that may shock\n"
            "the foe into flinching."),
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        },
            { .moveEffect = MOVE_EFFECT_FEAR, .chance = 3, }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Astonish,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WEATHER_BALL] =
    {
        .name = COMPOUND_STRING("WEATHER BALL"),
        .description = COMPOUND_STRING(
            "The move's type and power\n"
            "change with the weather."),
        .effect = EFFECT_WEATHER_BALL,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .zMove = { .powerOverride = 160 },
        .ballisticMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_BEAUTY : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SANDSTORM, COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_WeatherBall,
        .validApprenticeMove = TRUE,
    },

    [MOVE_AROMATHERAPY] =
    {
        .name = COMPOUND_STRING("AROMATHERAPY"),
        .description = COMPOUND_STRING(
            "Heals all status problems\n"
            "with a soothing scent."),
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS < GEN_6,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE : CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Aromatherapy,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FAKE_TEARS] =
    {
        .name = COMPOUND_STRING("FAKE TEARS"),
        .description = COMPOUND_STRING(
            "Feigns crying to sharply\n"
            "lower the foe's Sp. Def."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUICKLY_GROW_BORED :
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FakeTears,
        .validApprenticeMove = TRUE,
    },

    [MOVE_AIR_CUTTER] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .name = COMPOUND_STRING("AIR CUTTER"),
        .description = COMPOUND_STRING(
            "Hacks with razorlike wind.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 55,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 25,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .slicingMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AirCutter,
        .validApprenticeMove = TRUE,
    },

    [MOVE_OVERHEAT] =
    {
        .name = COMPOUND_STRING("OVERHEAT"),
        .description = COMPOUND_STRING(
            "Allows a full-power attack,\n"
            "but sharply lowers Sp. Atk."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 130 : 140,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = B_UPDATED_MOVE_DATA < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Overheat,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ODOR_SLEUTH] =
    {
        .name = COMPOUND_STRING("ODOR SLEUTH"),
        .description = COMPOUND_STRING(
            "Negate evasiveness and\n"
            "Ghost type's immunities."),
        .effect = EFFECT_FORESIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 0 : 100,
        .pp = 40,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_OdorSleuth,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_TOMB] =
    {
        .name = COMPOUND_STRING("ROCK TOMB"),
        .description = COMPOUND_STRING(
            "Stops the foe from moving\n"
            "with rocks and cuts Speed."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 50,
        .type = TYPE_ROCK,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 95 : 80,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 15 : 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ROCK_THROW},
        .battleAnimScript = gBattleAnimMove_RockTomb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SILVER_WIND] =
    {
        .name = COMPOUND_STRING("SILVER WIND"),
        .description = COMPOUND_STRING(
            "A powdery attack that may\n"
            "raise abilities."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = B_EXTRAPOLATED_MOVE_FLAGS,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SilverWind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_METAL_SOUND] =
    {
        .name = COMPOUND_STRING("METAL SOUND"),
        .description = COMPOUND_STRING(
            "Emits a horrible screech\n"
            "that sharply lowers Sp. Def."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 40,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_METAL_SOUND,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MetalSound,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GRASS_WHISTLE] =
    {
        .name = COMPOUND_STRING("GRASS WHISTLE"),
        .description = COMPOUND_STRING(
            "Lulls the foe into sleep\n"
            "with a pleasant melody."),
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 55,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_AVOID_STARTLE_ONCE : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_GRASS_WHISTLE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GrassWhistle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TICKLE] =
    {
        .name = COMPOUND_STRING("TICKLE"),
        .description = COMPOUND_STRING(
            "Makes the foe laugh to\n"
            "lower Attack and Defense."),
        .effect = EFFECT_TICKLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS < GEN_4,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Tickle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COSMIC_POWER] =
    {
        .name = COMPOUND_STRING("COSMIC POWER"),
        .description = COMPOUND_STRING(
            "Raises Defense and Sp. Def\n"
            "with a mystic power."),
        .effect = EFFECT_COSMIC_POWER,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_BEAUTY : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CosmicPower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATER_SPOUT] =
    {
        .name = COMPOUND_STRING("WATER SPOUT"),
        .description = COMPOUND_STRING(
            "Inflicts more damage if the\n"
            "user's HP is high."),
        .effect = EFFECT_POWER_BASED_ON_USER_HP,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_USER_MORE_EASILY_STARTLED : CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_WaterSpout,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SIGNAL_BEAM] =
    {
        .name = COMPOUND_STRING("SIGNAL BEAM"),
        .description = COMPOUND_STRING(
            "A strange beam attack that\n"
            "may confuse the foe."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SignalBeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SHADOW_PUNCH] =
    {
        .name = COMPOUND_STRING("SHADOW PUNCH"),
        .description = COMPOUND_STRING(
            "An unavoidable punch that\n"
            "is thrown from shadows."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShadowPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_EXTRASENSORY] =
    {
        .name = COMPOUND_STRING("EXTRASENSORY"),
        .description = COMPOUND_STRING(
            "Attacks with a peculiar\n"
            "power. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL : CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Extrasensory,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SKY_UPPERCUT] =
    {
        .name = COMPOUND_STRING("SKY UPPERCUT"),
        .description = COMPOUND_STRING(
            "An uppercut thrown as if\n"
            "leaping into the sky."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .damagesAirborne = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_SkyUppercut,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SAND_TOMB] =
    {
        .name = COMPOUND_STRING("SAND TOMB"),
        .description = COMPOUND_STRING(
            "Traps and hurts the foe in\n"
            "quicksand for "BINDING_TURNS" turns."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 35 : 15,
        .type = TYPE_GROUND,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 70,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_SAND_TOMB,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SANDSTORM},
        .battleAnimScript = gBattleAnimMove_SandTomb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SHEER_COLD] =
    {
        .name = COMPOUND_STRING("SHEER COLD"),
        .description = COMPOUND_STRING(
            "A chilling attack that\n"
            "causes fainting if it hits."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_ICE,
        .accuracy = 30,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .noAffectOnSameTypeTarget = B_SHEER_COLD_IMMUNITY >= GEN_7,
        .accIncreaseByTenOnSameType = B_SHEER_COLD_ACC >= GEN_7,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_SheerCold,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MUDDY_WATER] =
    {
        .name = COMPOUND_STRING("MUDDY WATER"),
        .description = COMPOUND_STRING(
            "Attacks with muddy water.\n"
            "May lower accuracy."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_STARTLE_PREV_MONS : CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_MuddyWater,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BULLET_SEED] =
    {
        .name = COMPOUND_STRING("BULLET SEED"),
        .description = COMPOUND_STRING(
            "Shoots 2 to 5 seeds in a row\n"
            "to strike the foe."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 25 : 10,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .ballisticMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH, COMBO_STARTER_ROTOTILLER},
        .battleAnimScript = gBattleAnimMove_BulletSeed,
    },

    [MOVE_AERIAL_ACE] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 5, }),
        .name = COMPOUND_STRING("AERIAL ACE"),
        .description = COMPOUND_STRING(
            "An extremely speedy and\n"
            "unavoidable attack."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AerialAce,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICICLE_SPEAR] =
    {
        .name = COMPOUND_STRING("ICICLE SPEAR"),
        .description = COMPOUND_STRING(
            "Attacks the foe by firing\n"
            "2 to 5 icicles in a row."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 25 : 10,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IcicleSpear,
    },

    [MOVE_IRON_DEFENSE] =
    {
        .name = COMPOUND_STRING("IRON DEFENSE"),
        .description = COMPOUND_STRING(
            "Hardens the body's surface\n"
            "to sharply raise Defense."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 15,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IronDefense,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BLOCK] =
    {
        .name = COMPOUND_STRING("BLOCK"),
        .description = COMPOUND_STRING(
            "Blocks the foe's way and\n"
            "prevents escape."),
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_BLOCK,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Block,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HOWL] =
    {
        .name = COMPOUND_STRING("HOWL"),
        .description = COMPOUND_STRING(
            "Howls to raise the spirit\n"
            "and boosts Attack."),
        .power = 0,
        .effect = EFFECT_ATTACK_UP,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = B_UPDATED_MOVE_DATA >= GEN_8 ? TARGET_USER_AND_ALLY: TARGET_USER ,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = B_UPDATED_MOVE_FLAGS >= GEN_8,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_BETTER_IF_LAST : CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Howl,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DRAGON_CLAW] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 10, }),
        .name = COMPOUND_STRING("DRAGON CLAW"),
        .description = COMPOUND_STRING(
            "Slashes the foe with sharp\n"
            "claws."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_RUSH, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_DragonClaw,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FRENZY_PLANT] =
    {
        .name = COMPOUND_STRING("FRENZY PLANT"),
        .description = COMPOUND_STRING(
            "Powerful, but leaves the\n"
            "user immobile the next turn."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_FrenzyPlant,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BULK_UP] =
    {
        .name = COMPOUND_STRING("BULK UP"),
        .description = COMPOUND_STRING(
            "Bulks up the body to boost\n"
            "both Attack and Defense."),
        .effect = EFFECT_BULK_UP,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BulkUp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BOUNCE] =
    {
        .name = COMPOUND_STRING("BOUNCE"),
        .description = COMPOUND_STRING(
            "Bounces up, then down the\n"
            "next turn. May paralyze."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 85,
        .type = TYPE_FLYING,
        .accuracy = 85,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNSPRANGUP, .status = STATE_ON_AIR },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Bounce,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MUD_SHOT] =
    {
        .name = COMPOUND_STRING("MUD SHOT"),
        .description = COMPOUND_STRING(
            "Hurls mud at the foe and\n"
            "reduces Speed."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_HIGHLY_APPEALING : CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SANDSTORM},
        .battleAnimScript = gBattleAnimMove_MudShot,
    },

    [MOVE_POISON_TAIL] =
    {
        .name = COMPOUND_STRING("POISON TAIL"),
        .description = COMPOUND_STRING(
            "Has a high critical-hit\n"
            "ratio. May also poison."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 25,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_PoisonTail,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COVET] =
    {
        .name = COMPOUND_STRING("COVET"),
        .description = COMPOUND_STRING(
            "Cutely begs to obtain an\n"
            "item held by the foe."),
        .effect = EFFECT_STEAL_ITEM,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 60 : 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 25 : 40,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = B_UPDATED_MOVE_DATA >= GEN_4,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_COVET,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Covet,
        .validApprenticeMove = TRUE,
    },

    [MOVE_VOLT_TACKLE] =
    {
        .name = COMPOUND_STRING("VOLT TACKLE"),
        #if B_UPDATED_MOVE_DATA >= GEN_4
        .description = COMPOUND_STRING(
            "A life-risking tackle that\n"
            "hurts the user. May paralyze."),
        #else
        .description = COMPOUND_STRING(
            "A life-risking tackle that\n"
            "slightly hurts the user."),
        #endif
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .recoilPercentage = 33 },
        .makesContact = TRUE,
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_PARALYSIS,
                .chance = 10,
            }),
        #endif
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_VoltTackle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MAGICAL_LEAF] =
    {
        .name = COMPOUND_STRING("MAGICAL LEAF"),
        .description = COMPOUND_STRING(
            "Attacks with a strange leaf\n"
            "that cannot be evaded."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_MagicalLeaf,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATER_SPORT] =
    {
        .name = COMPOUND_STRING("WATER SPORT"),
        .description = COMPOUND_STRING(
            "The user becomes soaked to\n"
            "weaken all Fire moves."),
        // in theory this should mention 5 turns (gen6+)
        .effect = EFFECT_WATER_SPORT,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 15,
        .target = TARGET_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST : CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_WATER_SPORT,
        .contestComboMoves = {COMBO_STARTER_MUD_SPORT, COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_WaterSport,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CALM_MIND] =
    {
        .name = COMPOUND_STRING("CALM MIND"),
        .description = COMPOUND_STRING(
            "Raises Sp. Atk and Sp. Def\n"
            "by focusing the mind."),
        .effect = EFFECT_CALM_MIND,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS : CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_CALM_MIND,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CalmMind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LEAF_BLADE] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 10, }),
        .name = COMPOUND_STRING("LEAF BLADE"),
        .description = COMPOUND_STRING(
            "Slashes with a sharp leaf.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 90 : 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_REPETITION_NOT_BORING : CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LeafBlade,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DRAGON_DANCE] =
    {
        .name = COMPOUND_STRING("DRAGON DANCE"),
        .description = COMPOUND_STRING(
            "A mystical dance that ups\n"
            "Attack and Speed."),
        .effect = EFFECT_DRAGON_DANCE,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_DANCE,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_RUSH, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_DragonDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_BLAST] =
    {
        .name = COMPOUND_STRING("ROCK BLAST"),
        .description = COMPOUND_STRING(
            "Hurls boulders at the foe\n"
            "2 to 5 times in a row."),
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_ROCK,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 80,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .multiHit = TRUE,
        .ballisticMove = B_UPDATED_MOVE_FLAGS >= GEN_7,
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING : CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockBlast,
    },

    [MOVE_SHOCK_WAVE] =
    {
        .name = COMPOUND_STRING("SHOCK WAVE"),
        .description = COMPOUND_STRING(
            "A fast and unavoidable\n"
            "electric attack."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_ShockWave,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATER_PULSE] =
    {
        .name = COMPOUND_STRING("WATER PULSE"),
        .description = COMPOUND_STRING(
            "Attacks with ultrasonic\n"
            "waves. May confuse the foe."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .pulseMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
        .contestEffect = C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION : CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_WaterPulse,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOOM_DESIRE] =
    {
        .name = COMPOUND_STRING("DOOM DESIRE"),
        .description = COMPOUND_STRING(
            "Summons strong light to\n"
            "attack 2 turns later."),
        .effect = EFFECT_FUTURE_SIGHT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 140 : 120,
        .type = TYPE_STEEL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 100 : 85,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE, //C_UPDATED_MOVE_EFFECTS >= GEN_6 ? CONTEST_EFFECT_EXCITES_AUDIENCE_MORE_IF_LAST :
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_BEAUTY : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DoomDesire,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PSYCHO_BOOST] =
    {
        .name = COMPOUND_STRING("PSYCHO BOOST"),
        .description = COMPOUND_STRING(
            "Allows a full-power attack,\n"
            "but sharply lowers Sp. Atk."),
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_PsychoBoost,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROOST] =
    {
        .name = COMPOUND_STRING("ROOST"),
        .description = COMPOUND_STRING(
            "Restores the user's HP by\n"
            "half of its max HP."),
        .effect = EFFECT_ROOST,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 5 : 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING, //CONTEST_EFFECT_QUICKLY_GROW_BORED
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_BRAVE_BIRD},
        .battleAnimScript = gBattleAnimMove_Roost,
    },

    [MOVE_GRAVITY] =
    {
        .name = COMPOUND_STRING("GRAVITY"),
        .description = COMPOUND_STRING(
            "Gravity is intensified\n"
            "negating levitation."),
        .effect = EFFECT_GRAVITY,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Gravity,
    },

    [MOVE_MIRACLE_EYE] =
    {
        .name = COMPOUND_STRING("MIRACLE EYE"),
        .description = COMPOUND_STRING(
            "Negate evasiveness and\n"
            "Dark type's immunities."),
        .effect = EFFECT_MIRACLE_EYE,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MiracleEye,
    },

    [MOVE_WAKE_UP_SLAP] =
    {
        .name = COMPOUND_STRING("WAKE-UP SLAP"),
        .description = COMPOUND_STRING(
            "Powerful against sleeping\n"
            "foes, but also wakes them."),
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 70 : 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .status = STATUS1_SLEEP },
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_STATUS,
        }),
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOVELY_KISS, COMBO_STARTER_SPORE, COMBO_STARTER_ENTRAINMENT, COMBO_STARTER_PLAY_NICE, COMBO_STARTER_SING, COMBO_STARTER_YAWN, COMBO_STARTER_HYPNOSIS, COMBO_STARTER_DARK_VOID, COMBO_STARTER_GRASS_WHISTLE, COMBO_STARTER_SLEEP_POWDER},
        .battleAnimScript = gBattleAnimMove_WakeUpSlap,
    },

    [MOVE_HAMMER_ARM] =
    {
        .name = COMPOUND_STRING("HAMMER ARM"),
        .description = COMPOUND_STRING(
            "A swinging fist attack\n"
            "that also lowers Speed."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_HammerArm,
    },

    [MOVE_GYRO_BALL] =
    {
        .name = COMPOUND_STRING("GYRO BALL"),
        .description = COMPOUND_STRING(
            "A high-speed spin that does\n"
            "more damage to faster foes."),
        .effect = EFFECT_GYRO_BALL,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GyroBall,
    },

    [MOVE_HEALING_WISH] =
    {
        .name = COMPOUND_STRING("HEALING WISH"),
        .description = sHealingWishDescription,
        .effect = EFFECT_HEALING_WISH,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .healingMove = TRUE,
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_BEAUTY : CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HealingWish,
    },

    [MOVE_BRINE] =
    {
        .name = COMPOUND_STRING("BRINE"),
        .description = COMPOUND_STRING(
            "Does double damage to foes\n"
            "with half HP or less."),
        .effect = EFFECT_BRINE,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Brine,
    },

    [MOVE_NATURAL_GIFT] =
    {
        .name = COMPOUND_STRING("NATURAL GIFT"),
        .description = COMPOUND_STRING(
            "The effectiveness varies\n"
            "with the held Berry."),
        .effect = EFFECT_NATURAL_GIFT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NaturalGift,
    },

    [MOVE_FEINT] =
    {
        .name = COMPOUND_STRING("FEINT"),
        .description = sFeintDescription,
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 30 : 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 2,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_6,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FEINT,
        }),
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Feint,
    },

    [MOVE_PLUCK] =
    {
        .name = COMPOUND_STRING("PLUCK"),
        .description = sPluckDescription,
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BUG_BITE,
        }),
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Pluck,
    },

    [MOVE_TAILWIND] =
    {
        .name = COMPOUND_STRING("TAILWIND"),
        .description = COMPOUND_STRING(
            "Whips up a breeze, doubling\n"
        #if B_TAILWIND_TURNS >= GEN_5
            "ally Speed for 4 turns."),
        #else
            "ally Speed for 3 turns."),
        #endif
        .effect = EFFECT_TAILWIND,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 15 : 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .snatchAffected = TRUE,
        .windMove = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Tailwind,
    },

    [MOVE_ACUPRESSURE] =
    {
        .name = COMPOUND_STRING("ACUPRESSURE"),
        .description = COMPOUND_STRING(
            "The user sharply raises\n"
            "one of its stats."),
        .effect = EFFECT_ACUPRESSURE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_USER_OR_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = B_UPDATED_MOVE_FLAGS < GEN_5,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Acupressure,
    },

    [MOVE_METAL_BURST] =
    {
        .name = COMPOUND_STRING("METAL BURST"),
        .description = COMPOUND_STRING(
            "Retaliates any hit with\n"
            "greater power."),
        .effect = EFFECT_REFLECT_DAMAGE,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = {
            .reflectDamage.damagePercent = 150,
            .reflectDamage.damageCategories = 1u << DAMAGE_CATEGORY_PHYSICAL | 1u << DAMAGE_CATEGORY_SPECIAL,
        },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS < GEN_5,
        .meFirstBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_METAL_SOUND, COMBO_STARTER_ENCORE, COMBO_STARTER_TAUNT, COMBO_STARTER_TORMENT},
        .battleAnimScript = gBattleAnimMove_MetalBurst,
    },

    [MOVE_U_TURN] =
    {
        .name = COMPOUND_STRING("U-TURN"),
        .description = sUTurnDescription,
        .effect = EFFECT_HIT_ESCAPE,
        .power = 70,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE, //CONTEST_EFFECT_QUICKLY_GROW_BORED
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_UTurn,
    },

    [MOVE_CLOSE_COMBAT] =
    {
        .name = COMPOUND_STRING("CLOSE COMBAT"),
        .description = sCloseCombatDescription,
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_SPDEF_DOWN,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_CloseCombat,
    },

    [MOVE_PAYBACK] =
    {
        .name = COMPOUND_STRING("PAYBACK"),
        .description = COMPOUND_STRING(
            "Attack that gains power\n"
            "if the user moves last."),
        .effect = EFFECT_PAYBACK,
        .power = 50,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_PAYBACK,
        .contestComboMoves = {COMBO_STARTER_REVENGE},
        .battleAnimScript = gBattleAnimMove_Payback,
    },

    [MOVE_ASSURANCE] =
    {
        .name = COMPOUND_STRING("ASSURANCE"),
        .description = COMPOUND_STRING(
            "Attack that gains power\n"
            "if the foe has been hurt."),
        .effect = EFFECT_ASSURANCE,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 50,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_PAYBACK, COMBO_STARTER_REVENGE},
        .battleAnimScript = gBattleAnimMove_Assurance,
    },

    [MOVE_EMBARGO] =
    {
        .name = COMPOUND_STRING("EMBARGO"),
        .description = COMPOUND_STRING(
            "Prevents the foe from\n"
            "using any items."),
        .effect = EFFECT_EMBARGO,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Embargo,
    },

    [MOVE_FLING] =
    {
        .name = COMPOUND_STRING("FLING"),
        .description = COMPOUND_STRING(
            "The effectiveness varies\n"
            "with the held item."),
        .effect = EFFECT_FLING,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CELEBRATE, COMBO_STARTER_COVET, COMBO_STARTER_HAPPY_HOUR, COMBO_STARTER_WISH},
        .battleAnimScript = gBattleAnimMove_Fling,
    },

    [MOVE_PSYCHO_SHIFT] =
    {
        .name = COMPOUND_STRING("PSYCHO SHIFT"),
        .description = COMPOUND_STRING(
            "Transfers status problems\n"
            "to the foe."),
        .effect = EFFECT_PSYCHO_SHIFT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 100 : 90,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_2 },
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PsychoShift,
    },

    [MOVE_TRUMP_CARD] =
    {
        .name = COMPOUND_STRING("TRUMP CARD"),
        .description = COMPOUND_STRING(
            "The less PP the move has\n"
            "the more damage it does."),
        .effect = EFFECT_TRUMP_CARD,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TrumpCard,
    },

    [MOVE_HEAL_BLOCK] =
    {
        .name = COMPOUND_STRING("HEAL BLOCK"),
        .description = COMPOUND_STRING(
            "Prevents the foes from\n"
            "recovering HP for 5 turns."),
        .effect = EFFECT_HEAL_BLOCK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_2 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HealBlock,
    },

    [MOVE_WRING_OUT] =
    {
        .name = COMPOUND_STRING("WRING OUT"),
        .description = sWringOutDescription,
        .effect = EFFECT_POWER_BASED_ON_TARGET_HP,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WringOut,
    },

    [MOVE_POWER_TRICK] =
    {
        .name = COMPOUND_STRING("POWER TRICK"),
        .description = COMPOUND_STRING(
            "The user swaps its Attack\n"
            "and Defense stats."),
        .effect = EFFECT_POWER_TRICK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PowerTrick,
    },

    [MOVE_GASTRO_ACID] =
    {
        .name = COMPOUND_STRING("GASTRO ACID"),
        .description = COMPOUND_STRING(
            "Stomach acid suppresses\n"
            "the foe's Ability."),
        .effect = EFFECT_GASTRO_ACID,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GastroAcid,
    },

    [MOVE_LUCKY_CHANT] =
    {
        .name = COMPOUND_STRING("LUCKY CHANT"),
        .description = COMPOUND_STRING(
            "Prevents the foe from\n"
            "landing critical hits."),
        .effect = EFFECT_LUCKY_CHANT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_LUCKY_CHANT,
        .contestComboMoves = {COMBO_STARTER_HEAL_BELL},
        .battleAnimScript = gBattleAnimMove_LuckyChant,
    },

    [MOVE_ME_FIRST] =
    {
        .name = COMPOUND_STRING("ME FIRST"),
        .description = COMPOUND_STRING(
            "Executes the foe's attack\n"
            "with greater power."),
        .effect = EFFECT_ME_FIRST,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_OPPONENT,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .ignoresSubstitute = TRUE,
        .metronomeBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = (B_UPDATED_MOVE_FLAGS >= GEN_7 || B_UPDATED_MOVE_FLAGS < GEN_3),
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MeFirst,
    },

    [MOVE_COPYCAT] =
    {
        .name = COMPOUND_STRING("COPYCAT"),
        .description = COMPOUND_STRING(
            "The user mimics the last\n"
            "move used by a foe."),
        .effect = EFFECT_COPYCAT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = (B_UPDATED_MOVE_FLAGS >= GEN_7 || B_UPDATED_MOVE_FLAGS < GEN_3),
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_CUTE : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Copycat,
    },

    [MOVE_POWER_SWAP] =
    {
        .name = COMPOUND_STRING("POWER SWAP"),
        .description = COMPOUND_STRING(
            "Swaps changes to Attack\n"
            "and Sp. Atk with the foe."),
        .effect = EFFECT_POWER_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PowerSwap,
    },

    [MOVE_GUARD_SWAP] =
    {
        .name = COMPOUND_STRING("GUARD SWAP"),
        .description = COMPOUND_STRING(
            "Swaps changes to Defense\n"
            "and Sp. Def with the foe."),
        .effect = EFFECT_GUARD_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GuardSwap,
    },

    [MOVE_PUNISHMENT] =
    {
        .name = COMPOUND_STRING("PUNISHMENT"),
        .description = COMPOUND_STRING(
            "Does more damage the more\n"
            "the foe has powered up."),
        .effect = EFFECT_PUNISHMENT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Punishment,
    },

    [MOVE_LAST_RESORT] =
    {
        .name = COMPOUND_STRING("LAST RESORT"),
        .description = COMPOUND_STRING(
            "Can only be used if every\n"
            "other move has been used."),
        .effect = EFFECT_LAST_RESORT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 140 : 130,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LastResort,
    },

    [MOVE_WORRY_SEED] =
    {
        .name = COMPOUND_STRING("WORRY SEED"),
        .description = COMPOUND_STRING(
            "Plants a seed on the foe\n"
            "giving it Insomnia."),
        .effect = EFFECT_OVERWRITE_ABILITY,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .overwriteAbility = ABILITY_INSOMNIA },
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_WORRY_SEED,
        .contestComboMoves = {COMBO_STARTER_LEECH_SEED, COMBO_STARTER_ROTOTILLER},
        .battleAnimScript = gBattleAnimMove_WorrySeed,
    },

    [MOVE_SUCKER_PUNCH] =
    {
        .name = COMPOUND_STRING("SUCKER PUNCH"),
        .description = sSuckerPunchDescription,
        .effect = EFFECT_SUCKER_PUNCH,
        .power = B_UPDATED_MOVE_DATA >= GEN_7 ? 70 : 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SuckerPunch,
    },

    [MOVE_TOXIC_SPIKES] =
    {
        .name = COMPOUND_STRING("TOXIC SPIKES"),
        .description = COMPOUND_STRING(
            "Sets spikes that poison a\n"
            "foe switching in."),
        .effect = EFFECT_TOXIC_SPIKES,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .forcePressure = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_TOXIC_SPIKES,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ToxicSpikes,
    },

    [MOVE_HEART_SWAP] =
    {
        .name = COMPOUND_STRING("HEART SWAP"),
        .description = COMPOUND_STRING(
            "Swaps any stat changes\n"
            "with the foe."),
        .effect = EFFECT_HEART_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HeartSwap,
    },

    [MOVE_AQUA_RING] =
    {
        .name = COMPOUND_STRING("AQUA RING"),
        .description = COMPOUND_STRING(
            "Forms a veil of water\n"
            "that restores HP."),
        .effect = EFFECT_AQUA_RING,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AquaRing,
    },

    [MOVE_MAGNET_RISE] =
    {
        .name = COMPOUND_STRING("MAGNET RISE"),
        .description = COMPOUND_STRING(
            "The user levitates with\n"
            "electromagnetism."),
        .effect = EFFECT_MAGNET_RISE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .gravityBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_SMART : CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MagnetRise,
    },

    [MOVE_FLARE_BLITZ] =
    {
        .name = COMPOUND_STRING("FLARE BLITZ"),
        .description = COMPOUND_STRING(
            "A charge that may burn the\n"
            "foe. Also hurts the user."),
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .recoilPercentage = 33 },
        .makesContact = TRUE,
        .thawsUser = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FlareBlitz,
    },

    [MOVE_FORCE_PALM] =
    {
        .name = COMPOUND_STRING("FORCE PALM"),
        .description = COMPOUND_STRING(
            "A shock wave attack that\n"
            "may paralyze the foe."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_FORCE_PALM,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ForcePalm,
    },

    [MOVE_AURA_SPHERE] =
    {
        .name = COMPOUND_STRING("AURA SPHERE"),
        .description = COMPOUND_STRING(
            "Attacks with an aura blast\n"
            "that cannot be evaded."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 80 : 90,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .pulseMove = TRUE,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AuraSphere,
    },

    [MOVE_ROCK_POLISH] =
    {
        .name = COMPOUND_STRING("ROCK POLISH"),
        .description = COMPOUND_STRING(
            "Polishes the body to\n"
            "sharply raise Speed."),
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 20,
        .target = TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_ROCK_POLISH,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockPolish,
    },

    [MOVE_POISON_JAB] =
    {
        .name = COMPOUND_STRING("POISON JAB"),
        .description = COMPOUND_STRING(
            "A stabbing attack that\n"
            "may poison the foe."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonJab,
    },

    [MOVE_DARK_PULSE] =
    {
        .name = COMPOUND_STRING("DARK PULSE"),
        .description = COMPOUND_STRING(
            "Attacks with a horrible\n"
            "aura. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .pulseMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        },
            { .moveEffect = MOVE_EFFECT_FEAR, .chance = 5, }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DarkPulse,
    },

    [MOVE_NIGHT_SLASH] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 10, }),
        .name = COMPOUND_STRING("NIGHT SLASH"),
        .description = COMPOUND_STRING(
            "Hits as soon as possible.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_DARK,
        .accuracy = 100,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3 ? 1 : 2,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_NightSlash,
    },

    [MOVE_AQUA_TAIL] =
    {
        .name = COMPOUND_STRING("AQUA TAIL"),
        .description = COMPOUND_STRING(
            "The user swings its tail\n"
            "like a wave to attack."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 10,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_BEAUTY : CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_AquaTail,
    },

    [MOVE_SEED_BOMB] =
    {
        .name = COMPOUND_STRING("SEED BOMB"),
        .description = COMPOUND_STRING(
            "A barrage of hard seeds\n"
            "is fired at the foe."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_TOUGH : CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ROTOTILLER},
        .battleAnimScript = gBattleAnimMove_SeedBomb,
    },

    [MOVE_AIR_SLASH] =
    {
        .name = COMPOUND_STRING("AIR SLASH"),
        .description = COMPOUND_STRING(
            "Attacks with a blade of\n"
            "air. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 15 : 20,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .slicingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        },
            { .moveEffect = MOVE_EFFECT_BLEED, .chance = 3, }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AirSlash,
    },

    [MOVE_X_SCISSOR] =
    {
        // PRL-pinned authentic status secondary effect.
        .additionalEffects = ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_BLEED, .chance = 10, }),
        .name = COMPOUND_STRING("X-SCISSOR"),
        .description = COMPOUND_STRING(
            "Slashes the foe with crossed\n"
            "scythes, claws, etc."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = C_UPDATED_MOVE_CATEGORIES >= GEN_6 ? CONTEST_CATEGORY_COOL : CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_XScissor,
    },

 ï}Ù¼­zÊ&ŠÛ^u½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!½¹•±…ÝÌ°(€€€ô°((€€€m5=Y}]%}UIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]%UIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ù…‘•ÌÝ¥‘”µÉ…¹¥¹œ…ÑÑ…­Íq¸ˆ(€€€€€€€€€€€€‰™½È½¹”ÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ì°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}]%}UIô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]¥‘•Õ…É°(€€€ô°((€€€m5=Y}UI}MA1%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰UIMA1%Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ù•É…•Ì¡…¹•ÌÑ¼•™•¹Í•q¸ˆ(€€€€€€€€€€€€‰…¹MÀ¸•˜Ý¥Ñ Ñ¡”™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}UI}MA1%P°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Õ…É‘MÁ±¥Ð°(€€€ô°((€€€m5=Y}A=]I}MA1%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=]HMA1%Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ù•É…•Ì¡…¹•ÌÑ¼ÑÑ…­q¸ˆ(€€€€€€€€€€€€‰…¹MÀ¸Ñ¬Ý¥Ñ Ñ¡”™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A=]I}MA1%P°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½Ý•ÉMÁ±¥Ð°(€€€ô°((€€€m5=Y}]=9I}I==5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]=9HI==4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰•™•¹Í”…¹MÀ¸•˜ÍÑ…ÑÍq¸ˆ(€€€€€€€€€€€€‰…É”ÍÝ…ÁÁ•™½È€ÔÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}]=9I}I==4°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô	}UAQ}5=Y}Q€øô9|Ø€ü€À€è€´Ü°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MI5	1}9aQ}QUI9}=IH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]½¹‘•ÉI½½´°(€€€ô°((€€€m5=Y}AMeM!=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AMeM!=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍAÍåÍ¡½­•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}AMeM!=,°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}I=9Q}5=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍåÍ¡½¬°(€€€ô°((€€€m5=Y}Y9=M!=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Y9=M!=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½•Ì‘½Õ‰±”‘…µ…”¥˜Ñ¡•q¸ˆ(€€€€€€€€€€€€‰™½”¥ÌÁ½¥Í½¹•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=U	1}A=]I}=9}I}MQQUL°(€€€€€€€€¹Á½Ý•È€ô€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÍÑ…ÑÕÌ€ôMQQULÅ}AM9}9dô°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}M5}QeA°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}Q=a%°=5	=}MQIQI}A=%M=9}L°=5	=}MQIQI}A=%M=9}A=]H°=5	=}MQIQI}Q=a%}MA%-Mô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Y•¹½Í¡½¬°(€€€ô°((€€€m5=Y}UQ=Q=5%it€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰UQ=Q=5%iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡•‘Ì…‘‘¥Ñ¥½¹…°Ý•¥¡ÐÑ½q¸ˆ(€€€€€€€€€€€€‰Í¡…ÉÁ±ä‰½½ÍÐMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}UQ=Q=5%i°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÕÑ½Ñ½µ¥é”°(€€€ô°((€€€m5=Y}I}A=]It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IA=]Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M…ÑÑ•ÉÌÁ½Ý‘•ÈÑ¼µ…­•q¸ˆ(€€€€€€€€€€€€‰™½•Ì…ÑÑ…¬½¹±äÑ¡”ÕÍ•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=11=]}5°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô	}UAQ}5=Y}Q€øô9|Ø€ü€È€è€Ì°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹Á½Ý‘•É5½Ù”€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I…•A½Ý‘•È°(€€€ô°((€€€m5=Y}Q1-%9M%Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q1-%9M%Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…­•ÌÑ¡”™½”™±½…Ð¸%Ð¥Íq¸ˆ(€€€€€€€€€€€€‰•…Í¥•ÈÑ¼¡¥Ð™½È€ÌÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q1-%9M%L°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MAQ-}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹É…Ù¥Ñå	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}5-}=11=]%9}5=9M}9IY=UL°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q•±•­¥¹•Í¥Ì°(€€€ô°((€€€m5=Y}5%}I==5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5%I==4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!½±¥Ñ•µÌ±½Í”Ñ¡•¥Éq¸ˆ(€€€€€€€€€€€€‰•™™•ÑÌ™½È€ÔÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5%}I==4°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô	}UAQ}5=Y}Q€øô9|Ø€ü€À€è€´Ü°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…¥I½½´°(€€€ô°((€€€m5=Y}M5-}=]9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M5,=]8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡É½ÝÌ„É½¬Ñ¼­¹½¬Ñ¡•q¸ˆ(€€€€€€€€€€€€‰™½”‘½Ý¸Ñ¼Ñ¡”É½Õ¹¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M5-}=]8°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‘…µ…•Í¥É‰½É¹”€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9}]%Q!})UM}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}9QI%959P°=5	=}MQIQI}A1e}9%ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Mµ…­½Ý¸°(€€€ô°((€€€m5=Y}MQ=I5}Q!I=]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ=I4Q!I=\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍMÑ½ÉµQ¡É½Ý•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ØÀ€è€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…±Ý…åÍÉ¥Ñ¥…±!¥Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}9QI%959P°=5	=}MQIQI}A1e}9%ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ½ÉµQ¡É½Ü°(€€€ô°((€€€m5=Y}15}	UIMQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰15	UIMPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰‰ÕÉÍÑ¥¹œ™±…µ”Ñ¡…Ð‘½•Íq¸ˆ(€€€€€€€€€€€€‰‘…µ…”Ñ¼…±°™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}15}	UIMP°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}M!%Q})U}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…µ•	ÕÉÍÐ°(€€€ô°((€€€m5=Y}M1U}]Yt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M1U]Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÝ…µÁÌ…±°½Ñ¡•ÉÌÝ¥Ñ „Ý…Ù•q¸ˆ(€€€€€€€€€€€€‰½˜Í±Õ‘”¸5…ä…±Í¼Á½¥Í½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}A=%M=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M±Õ‘•]…Ù”°(€€€ô°((€€€m5=Y}EU%YI}9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰EU%YH9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…¹•ÌÑ¼É…¥Í”MÀ¸Ñ­q¸ˆ(€€€€€€€€€€€€‰MÀ¸•˜…¹MÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}EU%YI}9°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹‘…¹•5½Ù”€ôQIU°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}EÕ¥Ù•É…¹”°(€€€ô°((€€€m5=Y}!Ye}M15t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!YdM14ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ!•…ÙåM±…µ•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!Q}IM °(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥¹¥µ¥é•½Õ‰±•…µ…”€ô	}UAQ}5=Y}1L€øô9|Ü°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!•…ÙåM±…´°(€€€ô°((€€€m5=Y}Me9!I=9=%Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Me9!I=9=%Mˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¸½‘Í¡½¬Ý…Ù”Ñ¡…Ð½¹±åq¸ˆ(€€€€€€€€€€€€‰‘…µ…•ÌÍ…µ”µÑåÁ”íA-59ô¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Me9!I=9=%M°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ÄÈÀ€è€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ÄÀ€è€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}M5}QeA°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Må¹¡É½¹½¥Í”°(€€€ô°((€€€m5=Y}1QI=}	11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1QI<	10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!ÕÉ±Ì…¸½ÉˆÑ¡…Ð‘½•Ìµ½É•q¸ˆ(€€€€€€€€€€€€‰‘…µ…”Ñ¼Í±½Ý•È™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}1QI=}	10°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…±±¥ÍÑ¥5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}I=9Q}5=8°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}%IMP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}%1%Qd°=5	=}MQIQI}!I°=5	=}MQIQI}I=-}A=1%M!ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±•ÑÉ½	…±°°(€€€ô°((€€€m5=Y}M=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÁÉ…åÌÝ…Ñ•È…ÐÑ¡”™½”±q¸ˆ(€€€€€€€€€€€€‰¡…¹¥¹œ¥ÐÑ¼]…Ñ•ÈÑåÁ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M=,°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÑåÁ”€ôQeA}]QHô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MAQ-}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9}]%Q!})UM}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}I%9}9ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M½…¬°(€€€ô°((€€€m5=Y}15}!It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰15!Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­Ì¥¸„±½…¬½™q¸ˆ(€€€€€€€€€€€€‰™±…µ•Ì¸I…¥Í•ÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]%Q!}==}=9%Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…µ•¡…É”°(€€€ô°((€€€m5=Y}=%1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=%0ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½¥±ÌÕÀÑ¼É…¥Í”ÑÑ…¬±q¸ˆ(€€€€€€€€€€€€‰•™•¹Í”…¹ÕÉ…ä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=%0°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½¥°°(€€€ô°((€€€m5=Y}1=]}M]At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1=\M]@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÑ¡”™½”Ì±•Íq¸ˆ(€€€€€€€€€€€€‰±½Ý•É¥¹œ¥ÑÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ØÔ€è€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1½ÝMÝ••À°(€€€ô°((€€€m5=Y}%}MAIet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%MAIdˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÁÉ…åÌ„¡¥‘”µµ•±Ñ¥¹œ…¥¹q¸ˆ(€€€€€€€€€€€€‰M¡…ÉÁ±äÉ•‘Õ•ÌMÀ¸•˜¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…±±¥ÍÑ¥5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}}5%9UM|È°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥‘MÁÉ…ä°(€€€ô°((€€€m5=Y}=U1}A1et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=U0A1dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”¡¥¡•ÈÑ¡”™½”ÌÑÑ…­q¸ˆ(€€€€€€€€€€€€‰Ñ¡”µ½É”‘…µ…”…ÕÍ•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=U1}A1d°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½Õ±A±…ä°(€€€ô°((€€€m5=Y}M%5A1}	5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M%5A1	4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰‰•…´Ñ¡…Ð¡…¹•ÌÑ¡•q¸ˆ(€€€€€€€€€€€€‰™½”Ì‰¥±¥ÑäÑ¼M¥µÁ±”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=YI]I%Q}	%1%Qd°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹½Ù•ÉÝÉ¥Ñ•‰¥±¥Ñä€ô	%1%Qe}M%5A1ô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MAQ-}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¥µÁ±•	•…´°(€€€ô°((€€€m5=Y}9QI%959Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9QI%959Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…­•ÌÑ¡”™½”µ¥µ¥ŒÑ¡•q¸ˆ(€€€€€€€€€€€€‰ÕÍ•È°…¥¹¥¹œ¥ÑÌ‰¥±¥Ñä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}9QI%959P°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}9QI%959P°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¹ÑÉ…¥¹µ•¹Ð°(€€€ô°((€€€m5=Y}QI}e=Ut€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QHe=Tˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!•±ÁÌ½ÕÐÑ¡”Ñ…É•Ð°±•ÑÑ¥¹q¸ˆ(€€€€€€€€€€€€‰¥Ðµ½Ù”¹•áÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QI}e=T°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}1QH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}™Ñ•Ée½Ô°(€€€ô°((€€€m5=Y}I=U9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=U9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Í½¹œÑ¡…Ð¥¹™±¥ÑÌ‘…µ…”¹q¸ˆ(€€€€€€€€€€€€‰=Ñ¡•ÉÌ…¸©½¥¸¥¸Ñ½¼¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=U9°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I=U9°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}M5}QeA°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I½Õ¹°(€€€ô°((€€€m5=Y}!=}Y=%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!=Y=%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½•Ìµ½É”‘…µ…”•Ù•ÉäÑÕÉ¹q¸ˆ(€€€€€€€€€€€€‰¥Ð¥ÌÕÍ•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!=}Y=%°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¡½•‘Y½¥”°(€€€ô°((€€€m5=Y}!%A}]et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!%@]dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ¡¥ÁÝ…å•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ•™•¹Í•Ù…Í¥½¹MÑ…•Ì€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¡¥ÁÝ…ä°(€€€ô°((€€€m5=Y}1I}M5=t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1HM5=ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ Ý¡¥Ñ”¡…é”Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰•±¥µ¥¹…Ñ•Ì…±°ÍÑ…Ð¡…¹•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1I}M5=°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±•…ÉMµ½œ°(€€€ô°((€€€m5=Y}MQ=I}A=]It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ=IA=]Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”¡¥¡•ÈÑ¡”ÕÍ•ÈÌÍÑ…ÑÍq¸ˆ(€€€€€€€€€€€€‰Ñ¡”µ½É”‘…µ…”…ÕÍ•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQ=I}A=]H°(€€€€€€€€¹Á½Ý•È€ô€ÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]%Q!}==}=9%Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}59M%°=5	=}MQIQI}!=9}1]L°=5	=}MQIQI}15}5%9°=5	=}MQIQI}9MQe}A1=Qô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ½É•‘A½Ý•È°(€€€ô°((€€€m5=Y}EU%-}UIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰EU%,UIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ù…‘•ÌÁÉ¥½É¥Ñä…ÑÑ…­Íq¸ˆ(€€€€€€€€€€€€‰™½È½¹”ÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ì°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}EU%-}UI°ô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}EÕ¥­Õ…É°(€€€ô°((€€€m5=Y}11e}M]%Q!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰11dM]%Q ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÍÝ¥Ñ¡•ÌÁ±…•Íq¸ˆ(€€€€€€€€€€€€‰Ý¥Ñ ¥ÑÌÁ…ÉÑ¹•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}11e}M]%Q °(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô	}UAQ}5=Y}Q€øô9|Ü€ü€È€è€Ä°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Èô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MI5	1}9aQ}QUI9}=IH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±±åMÝ¥Ñ °(€€€ô°((€€€m5=Y}M1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡½½ÑÌ‰½¥±¥¹œÝ…Ñ•È…ÐÑ¡•q¸ˆ(€€€€€€€€€€€€‰™½”¸5…ä¥¹™±¥Ð„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ñ¡…ÝÍUÍ•È€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}5-}=11=]%9}5=9M}9IY=UL°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}M1°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M…±°(€€€ô°((€€€m5=Y}M!11}M5M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!10M5M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡…ÉÁ±äÉ…¥Í•ÌÑ¬½MÀ¹Ñ¬½q¸ˆ(€€€€€€€€€€€€‰MÁ••°‰ÕÐ‘É½ÁÌ•˜½MÀ¹•˜¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M!11}M5M °(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡•±±Mµ…Í °(€€€ô°((€€€m5=Y}!1}AU1Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!0AU1Mˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I•½Ù•ÉÌÕÀÑ¼¡…±˜Ñ¡•q¸ˆ(€€€€€€€€€€€€‰Ñ…É•ÐÌµ…á¥µÕ´!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!1}AU1M°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹ÁÕ±Í•5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!•…±AÕ±Í”°(€€€ô°((€€€m5=Y}!at€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}H°€¹¡…¹”€ô€Ô°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!`ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½•Ì‘½Õ‰±”‘…µ…”¥˜Ñ¡•q¸ˆ(€€€€€€€€€€€€‰™½”¡…Ì„ÍÑ…ÑÕÌÁÉ½‰±•´¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=U	1}A=]I}=9}I}MQQUL°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ØÔ€è€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹é5½Ù”€ôì€¹Á½Ý•É=Ù•ÉÉ¥‘”€ô€ÄØÀô°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÍÑ…ÑÕÌ€ôMQQULÅ}9dô°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}Q=a%°=5	=}MQIQI}=I}A14°=5	=}MQIQI}Q!U9I}]Y°=5	=}MQIQI}%9I9<°=5	=}MQIQI}]%11}=}]%M@°=5	=}MQIQI}1=Y1e}-%ML°=5	=}MQIQI}MA=I°=5	=}MQIQI}M%9°=5	=}MQIQI}e]8°=5	=}MQIQI}!eA9=M%L°=5	=}MQIQI}I-}Y=%°=5	=}MQIQI}IMM}]!%MQ1°=5	=}MQIQI}M1A}A=]H°=5	=}MQIQI}A=%M=9}L°=5	=}MQIQI}A=%M=9}A=]H°=5	=}MQIQI}Q=a%}MA%-L°=5	=}MQIQI}1Iô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!•à°(€€€ô°((€€€m5=Y}M-e}I=At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M-dI=@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q…­•ÌÑ¡”™½”¥¹Ñ¼Ñ¡”Í­åq¸ˆ(€€€€€€€€€€€€‰Ñ¡•¸‘É½ÁÌ¥ÐÑ¡”¹•áÐÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M-e}I=@°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹É…Ù¥Ñå	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹…ÉÕµ•¹Ð¹ÑÝ½QÕÉ¹ÑÑ…¬€ôì€¹ÍÑÉ¥¹%€ôMQI%9%}A-59Q==-QIQ!% °€¹ÍÑ…ÑÕÌ€ôMQQ}=9}%Hô°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}9QI%959P°=5	=}MQIQI}A1e}9%ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M­åÉ½À°(€€€ô°((€€€m5=Y}M!%Q}It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!%PHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I½Ñ…Ñ•Ì¥ÑÌ•…ÉÌÑ¼É…¥Í•q¸ˆ(€€€€€€€€€€€€‰ÑÑ…¬…¹MÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M!%Q}H°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}M!%Q}H°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡¥™Ñ•…È°(€€€ô°((€€€m5=Y}%I1}Q!I=]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%I1Q!I=\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ¥É±•Q¡É½Ý•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%Q}M]%Q!}QIP°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€´Ø°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}1QH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}9QI%959P°=5	=}MQIQI}A1e}9%ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥É±•Q¡É½Ü°(€€€ô°((€€€m5=Y}%9%9IQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%9%9IQˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	ÕÉ¹ÌÕÀ	•ÉÉ¥•Ì…¹•µÍq¸ˆ(€€€€€€€€€€€€‰ÁÉ•Ù•¹Ñ¥¹œÑ¡•¥ÈÕÍ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ØÀ€è€ÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%9%9IQ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}M!%Q})U}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%¹¥¹•É…Ñ”°(€€€ô°((€€€m5=Y}EUM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰EUM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÕÁÁÉ•ÍÍ•ÌÑ¡”™½”°µ…­¥¹q¸ˆ(€€€€€€€€€€€€‰¥Ðµ½Ù”±…ÍÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}EUM °(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}I1%H°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}EÕ…Í °(€€€ô°((€€€m5=Y}I=	Q%Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=	Q%Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½•Ì‘½Õ‰±”‘…µ…”¥˜Ñ¡•q¸ˆ(€€€€€€€€€€€€‰ÕÍ•È¡…Ì¹¼¥Ñ•´¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=	Q%L°(€€€€€€€€¹Á½Ý•È€ô€ÔÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]%Q!}==}=9%Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É½‰…Ñ¥Ì°(€€€ô°((€€€m5=Y}I1Q}QeAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I1PQeAˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÉ•™±•ÑÌÑ¡”™½”Íq¸ˆ(€€€€€€€€€€€€‰ÑåÁ”°½Áå¥¹œ¥Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I1Q}QeA°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MAQ-}UA|Äô°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}M5}QeA°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I•™±•ÑQåÁ”°(€€€ô°((€€€m5=Y}IQ1%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IQ1%Qˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…¬Ñ¡…Ð‘½•Ìµ½É•q¸ˆ(€€€€€€€€€€€€‰‘…µ…”¥˜…¸…±±ä™…¥¹Ñ•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IQ1%Q°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Q}	e}AIY}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I•Ñ…±¥…Ñ”°(€€€ô°((€€€m5=Y}%91}5	%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%905	%Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È™…¥¹ÑÌÑ¼‘…µ…•q¸ˆ(€€€€€€€€€€€€‰Ñ¡”™½”•ÅÕ…°Ñ¼¥ÑÌ!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%91}5	%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹•áÁ±½Í¥½¸€ô	}UAQ}5=Y}1L€ðô9|Ô°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹Á…É•¹Ñ…±	½¹‘	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IQ}AA1}	UQ}9=}5=I}5=YL°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥¹…±…µ‰¥Ð°(€€€ô°((€€€m5=Y}	MQ=]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	MQ=\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È¥Ù•Ì¥ÑÌ¡•±‘q¸ˆ(€€€€€€€€€€€€‰¥Ñ•´Ñ¼Ñ¡”™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	MQ=\°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Èô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}U%9}a%Q°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}1	IQ°=5	=}MQIQI}=YP°=5	=}MQIQI}!AAe}!=UH°=5	=}MQIQI}]%M!ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	•ÍÑ½Ü°(€€€ô°((€€€m5=Y}%9I9=t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%9I9<ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰A½Ý•É™Õ°…¹ÍÕÉ”Ñ¼¥¹™±¥Ñq¸ˆ(€€€€€€€€€€€€‰„‰ÕÉ¸°‰ÕÐ¥¹…ÕÉ…Ñ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÔÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}I=9Q}5=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}%9I9<°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%¹™•É¹¼°(€€€ô°((€€€m5=Y}]QI}A1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]QHA1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ „½±Õµ¸½™q¸ˆ(€€€€€€€€€€€€‰Ý…Ñ•È¸5…äµ…­”„É…¥¹‰½Ü¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A1°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€àÀ€è€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]…Ñ•ÉA±•‘”°(€€€ô°((€€€m5=Y}%I}A1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%IA1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ „½±Õµ¸½™q¸ˆ(€€€€€€€€€€€€‰™¥É”¸5…ä‰ÕÉ¸Ñ¡”É…ÍÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A1°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€àÀ€è€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥É•A±•‘”°(€€€ô°((€€€m5=Y}IMM}A1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IMLA1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ „½±Õµ¸½™q¸ˆ(€€€€€€€€€€€€‰É…ÍÌ¸5…äÉ•…Ñ”„ÍÝ…µÀ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A1°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€àÀ€è€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…ÍÍA±•‘”°(€€€ô°((€€€m5=Y}Y=1Q}M]%Q!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Y=1PM]%Q ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍUQÕÉ¹•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%Q}MA°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°€¼½=9QMQ}Q}EU%-1e}I=]}	=I(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!Iô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Y½±ÑMÝ¥Ñ °(€€€ô°((€€€m5=Y}MQIU1}	Ut€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQIU1	Uˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I•Í¥ÍÑ¥¹œ°Ñ¡”ÕÍ•È…ÑÑ…­Íq¸ˆ(€€€€€€€€€€€€‰Ñ¡”™½•Ì¸1½Ý•ÉÌMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ÔÀ€è€ÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑÉÕ±•	Õœ°(€€€ô°((€€€m5=Y}	U11=it€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	U11=iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑ½µÁÌ‘½Ý¸½¸Ñ¡”É½Õ¹¹q¸ˆ(€€€€€€€€€€€€‰!¥ÑÌ…±°…¹±½Ý•ÉÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IQ!EU-°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	Õ±±‘½é”°(€€€ô°((€€€m5=Y}I=MQ}	IQ!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=MP	IQ ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍMÑ½ÉµQ¡É½Ý•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ØÀ€è€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…±Ý…åÍÉ¥Ñ¥…±!¥Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Q}	e}AIY}AA0°€¼½=9QMQ}Q}EU%-1e}I=]}	=I(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É½ÍÑ	É•…Ñ °(€€€ô°((€€€m5=Y}I=9}Q%1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=8Q%0ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ¥É±•Q¡É½Ý•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%Q}M]%Q!}QIP°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€´Ø°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}1QH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}I=9}Q%0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}I=9}	IQ °=5	=}MQIQI}I=9}9°=5	=}MQIQI}I=9}I°=5	=}MQIQI}I=9}IUM °=5	=}MQIQI}MQ1Q!}I=,°=5	=}MQIQI}MA%-L°=5	=}MQIQI}Q=a%}MA%-Mô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…½¹Q…¥°°(€€€ô°((€€€m5=Y}]=I-}UAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]=I,U@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È¥ÌÉ½ÕÍ•¹q¸ˆ(€€€€€€€€€€€€‰UÁÌÑÑ…¬…¹MÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QQ-}MAQ-}U@°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÌÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}Q-}UA|Äô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}%IMP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]½É­UÀ°(€€€ô°((€€€m5=Y}1QI=]	t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1QI=]ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¹…É•ÌÑ¡”™½•ÌÝ¥Ñ …¹q¸ˆ(€€€€€€€€€€€€‰•±•ÑÉ¥Œ¹•Ð¸1½Ý•ÉÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9}]%Q!})UM}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}MQI%9}M!=Qô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±•ÑÉ½Ý•ˆ°(€€€ô°((€€€m5=Y}]%1}!It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]%1!Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¸•±•ÑÉ¥…°Ñ…­±”Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰…±Í¼¡ÕÉÑÌÑ¡”ÕÍ•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=%0°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹É•½¥±A•É•¹Ñ…”€ô€ÈÔô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]¥±‘¡…É”°(€€€ô°((€€€m5=Y}I%11}IU9t€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%10IU8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÁ¥¹Ì¥ÑÌ‰½‘ä±¥­”„‘É¥±°¹q¸ˆ(€€€€€€€€€€€€‰!¥ É¥Ñ¥…°µ¡¥ÐÉ…Ñ¥¼¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹É¥Ñ¥…±!¥ÑMÑ…”€ô	}UAQ}5=Y}Q€øô9|Ì€ü€Ä€è€È°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Q}	e}AIY}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}=UM}9Ieô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É¥±±IÕ¸°(€€€ô°((€€€m5=Y}U1}!=At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰U0!=@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ ‰ÉÕÑ…°¡¥ÑÍq¸ˆ(€€€€€€€€€€€€‰Ñ¡…ÐÍÑÉ¥­”ÑÝ¥”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€È°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Õ…±¡½À°(€€€ô°((€€€m5=Y}!IQ}MQ5At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!IPMQ5@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÍÕ‘‘•¸‰±½Ü…™Ñ•È„ÕÑ•q¸ˆ(€€€€€€€€€€€€‰…Ð¸5…ä…ÕÍ”™±¥¹¡¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!•…ÉÑMÑ…µÀ°(€€€ô°((€€€m5=Y}!=I9}1!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!=I81 ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ5•…É…¥¹•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ô	}!1}	1=-%9€øô9|Ø°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!½É¹1•• °(€€€ô°((€€€m5=Y}MI}M]=It€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MIM]=Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ¡¥ÁÝ…å•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ÄÔ€è€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ•™•¹Í•Ù…Í¥½¹MÑ…•Ì€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M…É•‘MÝ½É°(€€€ô°((€€€m5=Y}Ii=I}M!11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Ii=HM!10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q•…ÉÌ…ÐÑ¡”™½”Ý¥Ñ Í¡…ÉÁq¸ˆ(€€€€€€€€€€€€‰Í¡•±±Ì¸5…ä±½Ý•È•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÔÀ°(€€€€€€€ô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€Ô°ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I…é½ÉM¡•±°°(€€€ô°((€€€m5=Y}!Q}IM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!PIM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ!•…ÙåM±…µ•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!Q}IM °(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥¹¥µ¥é•½Õ‰±•…µ…”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!•…ÑÉ…Í °(€€€ô°((€€€m5=Y}1}Q=I9=t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1Q=I9<ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¥É±•ÌÑ¡”™½”Ý¥Ñ ±•…Ù•Íq¸ˆ(€€€€€€€€€€€€‰Ñ¼‘…µ…”…¹ÕÐ…ÕÉ…ä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÔÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1•…™Q½É¹…‘¼°(€€€ô°((€€€m5=Y}MQ5I=11It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ5I=11Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÉÕÍ¡•ÌÑ¡”™½”Ý¥Ñ ¥ÑÍq¸ˆ(€€€€€€€€€€€€‰‰½‘ä¸5…ä…ÕÍ”™±¥¹¡¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥¹¥µ¥é•½Õ‰±•…µ…”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ•…µÉ½±±•È°(€€€ô°((€€€m5=Y}=QQ=9}UIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=QQ=8UIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]É…ÁÌ¥ÑÌ‰½‘ä¥¸½ÑÑ½¸¹q¸ˆ(€€€€€€€€€€€€‰É…ÍÑ¥…±±äÉ…¥Í•Ì•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}9M}UA|Ì°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½ÑÑ½¹Õ…É°(€€€ô°((€€€m5=Y}9%!Q}it€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9%!Piˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1½½Í•Ì„Á¥Ñ µ‰±…¬Í¡½­q¸ˆ(€€€€€€€€€€€€‰Ý…Ù”¸5…ä±½Ý•È…ÕÉ…ä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÐÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}9¥¡Ñ…é”°(€€€ô°((€€€m5=Y}AMeMQI%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AMeMQI%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍAÍåÍ¡½­•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}AMeM!=,°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍåÍÑÉ¥­”°(€€€ô°((€€€m5=Y}Q%1}M1At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q%0M1@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑÉ¥­•ÌÑ¡”™½”Ý¥Ñ ¥ÑÍq¸ˆ(€€€€€€€€€€€€‰Ñ…¥°€ÈÑ¼€ÔÑ¥µ•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µÕ±Ñ¥!¥Ð€ôQIU°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}EU1%Qe}A9M}=9}Q%5%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q…¥±M±…À°(€€€ô°((€€€m5=Y}!UII%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!UII%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰QÉ…ÁÌÑ¡”™½”¥¸„™¥•É•q¸ˆ(€€€€€€€€€€€€‰Ý¥¹¸5…ä…ÕÍ”½¹™ÕÍ¥½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ÄÄÀ€è€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÜÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ý¥¹‘5½Ù”€ôQIU°(€€€€€€€€¹‘…µ…•Í¥É‰½É¹”€ôQIU°(€€€€€€€€¹…±Ý…åÍ!¥ÑÍ%¹I…¥¸€ôQIU°(€€€€€€€€¹…ÕÉ…äÔÁ%¹MÕ¸€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=9UM%=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}5=9M}]%Q!}==}AA1L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}I%9}9ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!ÕÉÉ¥…¹”°(€€€ô°((€€€m5=Y}!}!It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!!Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡…É”ÕÍ¥¹œÕ…É¡…¥È¹q¸ˆ(€€€€€€€€€€€€‰%Ð¡ÕÉÑÌÑ¡”ÕÍ•È„±¥ÑÑ±”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=%0°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹É•½¥±A•É•¹Ñ…”€ô€ÈÔô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!•…‘¡…É”°(€€€ô°((€€€m5=Y}I}I%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰HI%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡É½ÝÌÑÝ¼ÍÑ••°•…ÉÍq¸ˆ(€€€€€€€€€€€€‰Ñ¡…ÐÍÑÉ¥­”ÑÝ¥”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹é5½Ù”€ôì€¹Á½Ý•É=Ù•ÉÉ¥‘”€ô€ÄàÀô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€È°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}M!%Q}Iô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•…ÉÉ¥¹°(€€€ô°((€€€m5=Y}MI%9}M!=Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MI%9M!=Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ1…Ù…A±Õµ••ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…±±¥ÍÑ¥5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M•…É¥¹M¡½Ð°(€€€ô°((€€€m5=Y}Q!9=}	1MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q!9<	1MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÑåÁ”Ù…É¥•ÌÝ¥Ñ Ñ¡•q¸ˆ(€€€€€€€€€€€€‰­¥¹½˜É¥Ù”¡•±¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!9}QeA}=9}%Q4°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ø€ü€ÄÈÀ€è€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹¡½±‘™™•Ð€ô!=1}Q}I%Yô°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]%Q!}==}=9%Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q•¡¹½	±…ÍÐ°(€€€ô°((€€€m5=Y}I1%}M=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I1%M=9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ …¸…¹¥•¹Ñq¸ˆ(€€€€€€€€€€€€‰Í½¹œ¸5…ä¥¹‘Õ”Í±••À¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÍÑ…ÑÕÌ€ôMQQULÅ}M1@ô°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}M1@°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}5-}=11=]%9}5=9M}9IY=UL°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQ%U0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I•±¥M½¹œ°(€€€ô°((€€€m5=Y}MIQ}M]=It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MIPM]=Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÕÑÌÝ¥Ñ „±½¹œ¡½É¸Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰‘½•ÌÁ¡åÍ¥…°‘…µ…”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AMeM!=,°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQ%U0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M•É•ÑMÝ½É°(€€€ô°((€€€m5=Y}1%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%Qˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	±½ÝÌÙ•Éä½±…¥È…ÐÑ¡•q¸ˆ(€€€€€€€€€€€€‰™½•Ì¸%Ð±½Ý•ÉÌÑ¡•¥ÈMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!%1ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…¥…Ñ”°(€€€ô°((€€€m5=Y}	=1Q}MQI%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	=1PMQI%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑÉ¥­•ÌÝ¥Ñ „É•…Ð…µ½Õ¹Ñq¸ˆ(€€€€€€€€€€€€‰½˜±¥¡Ñ¹¥¹œ¸5…äÁ…É…±åé”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1eM%L°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	½±ÑMÑÉ¥­”°(€€€ô°((€€€m5=Y}	1U}1It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	1U1Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¹Õ±™ÌÑ¡”™½”¥¸„‰±Õ•q¸ˆ(€€€€€€€€€€€€‰™±…µ”¸5…ä¥¹™±¥Ð„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	±Õ•±…É”°(€€€ô°((€€€m5=Y}%Ie}9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%Id9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…¹•Ì±½…­•¥¸™±…µ•Ì¹q¸ˆ(€€€€€€€€€€€€‰5…äÉ…¥Í”MÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‘…¹•5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÔÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]%Q!}==}=9%Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥•Éå…¹”°(€€€ô°((€€€m5=Y}Ii}M!=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IiM!=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Á½Ý•É™Õ°€ÈµÑÕÉ¸µ½Ù”Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰µ…äÁ…É…±åé”Ñ¡”™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q]=}QUI9M}QQ,°(€€€€€€€€¹Á½Ý•È€ô€ÄÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð¹ÑÝ½QÕÉ¹ÑÑ…¬€ôì€¹ÍÑÉ¥¹%€ôMQI%9%}1=-%9Ii%91%!Pô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1eM%L°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Q}	e}AIY}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É••é•M¡½¬°(€€€ô°((€€€m5=Y}%}	UI9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%	UI8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Á½Ý•É™Õ°€ÈµÑÕÉ¸µ½Ù”Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰µ…ä¥¹™±¥Ð„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q]=}QUI9M}QQ,°(€€€€€€€€¹Á½Ý•È€ô€ÄÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð¹ÑÝ½QÕÉ¹ÑÑ…¬€ôì€¹ÍÑÉ¥¹%€ôMQI%9%}1=-%9Ii%91%!Pô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Q}	e}AIY}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%•	ÕÉ¸°(€€€ô°((€€€m5=Y}M9I1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M9I0ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰e•±±Ì…¹É…¹ÑÌ…ÐÑ¡”™½•q¸ˆ(€€€€€€€€€€€€‰±½Ý•É¥¹œ¥ÑÌMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}H°€¹¡…¹”€ô€Ô°ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°€¼½=9QMQ}Q}EU%-1e}I=]}	=I(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¹…É°°(€€€ô°((€€€m5=Y}%%1}IM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%%1IM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É½ÁÌ±…É”¥¥±•Ì½¸Ñ¡•q¸ˆ(€€€€€€€€€€€€‰™½”¸5…ä…ÕÍ”™±¥¹¡¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!%1ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%¥±•É…Í °(€€€ô°((€€€m5=Y}Y}IQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰XµIQˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Y•ÉäÁ½Ý•É™Õ°°‰ÕÐ±½Ý•ÉÍq¸ˆ(€€€€€€€€€€€€‰•™•¹Í”°MÀ¸•˜…¹MÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄàÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹é5½Ù”€ôì€¹Á½Ý•É=Ù•ÉÉ¥‘”€ô€ÈÈÀô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Y}IQ°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}YÉ•…Ñ”°(€€€ô°((€€€m5=Y}UM%=9}1It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰UM%=81Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÕµµ½¹Ì„™¥É•‰…±°¸]½É­Íq¸ˆ(€€€€€€€€€€€€‰Ý•±°Ý¥Ñ „Ñ¡Õ¹‘•É‰½±Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}UM%=9}=5	<°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ñ¡…ÝÍUÍ•È€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}1QH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÕÍ¥½¹±…É”°(€€€ô°((€€€m5=Y}UM%=9}	=1Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰UM%=8	=1Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÕµµ½¹Ì„Ñ¡Õ¹‘•É‰½±Ð¹q¸ˆ(€€€€€€€€€€€€‰]½É­ÌÝ•±°Ý¥Ñ „™¥É•‰…±°¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}UM%=9}=5	<°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}1QH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÕÍ¥½¹	½±Ð°(€€€ô°((€€€m5=Y}1e%9}AIMMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1e%9AIMLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡¥Ì…ÑÑ…¬‘½•Ì¥¡Ñ¥¹q¸ˆ(€€€€€€€€€€€€‰…¹±å¥¹œµÑåÁ”‘…µ…”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q]=}QeA}5=Y°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ü€ü€ÄÀÀ€è€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹é5½Ù”€ôì€¹Á½Ý•É=Ù•ÉÉ¥‘”€ô€ÄÜÀô°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÑåÁ”€ôQeA}1e%9ô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥¹¥µ¥é•½Õ‰±•…µ…”€ôQIU°(€€€€€€€€¹É…Ù¥Ñå	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±å¥¹AÉ•ÍÌ°(€€€ô°((€€€m5=Y}5Q}	1=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5P	1=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ù…‘•Ì‘…µ…¥¹œµ½Ù•Ì¹q¸ˆ(€€€€€€€€€€€€‰=¹±äÝ½É­Ì½¸€ÅÍÐÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5Q}	1=,°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}5Q}	1=,°ô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…Ñ	±½¬°(€€€ô°((€€€m5=Y}	1!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	1 ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1•ÑÌ½ÕÐ„±½Õ‰•± ¹q¸ˆ(€€€€€€€€€€€€‰5ÕÍÐ•…Ð„	•ÉÉäÑ¼ÕÍ”¥Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	1 °(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•¥ÉÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]%Q!}==}=9%Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	•± °(€€€ô°((€€€m5=Y}I=Q=Q%11It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=Q=Q%11Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÁÌÑ¡”ÑÑ…¬…¹MÀ¸Ñ­q¸ˆ(€€€€€€€€€€€€‰½˜É…ÍÌµÑåÁ”A½¯¥µ½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=Q=Q%11H°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}11}	QQ1IL°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}Q-}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}I=Q=Q%11H°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I½Ñ½Ñ¥±±•È°(€€€ô°((€€€m5=Y}MQ%-e}]	t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ%-d]ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]•…Ù•Ì„ÍÑ¥­ä¹•ÐÑ¡…Ñq¸ˆ(€€€€€€€€€€€€‰Í±½ÝÌ™½•ÌÍÝ¥Ñ¡¥¹œ¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQ%-e}]°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=AA=99QM}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9}]%Q!})UM}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}MQI%9}M!=Qô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ¥­å]•ˆ°(€€€ô°((€€€m5=Y}11}MQ%9It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰10MQ%9Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%˜¥Ð­¹½­Ì½ÕÐ„™½•q¸ˆ(€€€€€€€€€€€€‰Ñ¡”ÑÑ…¬ÍÑ…Ð¥ÌÉ…¥Í•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}11}MQ%9H°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ü€ü€ÔÀ€è€ÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}U%9}a%Q°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•±±MÑ¥¹•È°(€€€ô°((€€€m5=Y}A!9Q=5}=It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A!9Q=4=Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍM¡…‘½Ý½É••ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}M5%}%9YU19I	1°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥¹¥µ¥é•½Õ‰±•…µ…”€ô	}UAQ}5=Y}1L€ð9|Ü°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð¹ÑÝ½QÕÉ¹ÑÑ…¬€ôì€¹ÍÑÉ¥¹%€ôMQI%9%}Y9%M!%9MQ9Q1d°€¹ÍÑ…ÑÕÌ€ôMQQ}A!9Q=5}=Iô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%9P°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A¡…¹Ñ½µ½É”°(€€€ô°((€€€m5=Y}QI%-}=I}QIQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QI%,µ=HµQIPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½•ÌÑÉ¥¬µ½ÈµÑÉ•…Ñ¥¹œ±q¸ˆ(€€€€€€€€€€€€‰…‘‘¥¹œ¡½ÍÐÑåÁ”Ñ¼™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q!%I}QeA°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÑåÁ”€ôQeA}!=MPô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}11}MQQM}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}QÉ¥­=ÉQÉ•…Ð°(€€€ô°((€€€m5=Y}9=	1}I=It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9=	1I=Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%¹Ñ¥µ¥‘…Ñ•ÌÑ¡”™½”°Ñ¼ÕÑq¸ˆ(€€€€€€€€€€€€‰ÑÑ…¬…¹MÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}9=	1}I=H°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÌÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}9½‰±•I½…È°(€€€ô°((€€€m5=Y}%=9}1Ut€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%=81Uˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±•ÑÉ¥™¥•Ì9½Éµ…°µÑåÁ•q¸ˆ(€€€€€€€€€€€€‰µ½Ù•ÌÝ¥Ñ ¡…É•…Ñ½µÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%=9}1U°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ä°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MAQ-}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%½¹•±Õ”°(€€€ô°((€€€m5=Y}AI	=1%}!It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AI	=1%!Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…µ…•Ì…‘©…•¹ÐA½¯¥µ½¹q¸ˆ(€€€€€€€€€€€€‰…¹¡•…±ÌÕÀ‰ä¡…±˜½˜¥Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ü€ü€ØÔ€è€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹¡•…±¥¹5½Ù”€ô	}!1}	1=-%9€øô9|Ø°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}AI	=1%}!I°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!Iô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A…É…‰½±¥¡…É”°(€€€ô°((€€€m5=Y}=IMQM}UIMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=IMPLUIMˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÕÑÌ„ÕÉÍ”½¸Ñ¡”™½”±q¸ˆ(€€€€€€€€€€€€‰…‘‘¥¹œÑ¡”É…ÍÌÑåÁ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q!%I}QeA°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÑåÁ”€ôQeA}IMLô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}11}MQQM}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}5=9M}]%Q!}==}AA1L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½É•ÍÑÍÕÉÍ”°(€€€ô°((€€€m5=Y}AQ1}	1%iiIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AQ0	1%iiIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑ¥ÉÌÕÀ„Ù¥½±•¹ÐÍÑ½Éµq¸ˆ(€€€€€€€€€€€€‰½˜Á•Ñ…±ÌÑ¼…ÑÑ…¬…±°¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹Ý¥¹‘5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A•Ñ…±	±¥éé…É°(€€€ô°((€€€m5=Y}Ii}Iet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IiµIdˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÕÁ•È•™™•Ñ¥Ù”½¸]…Ñ•Èµq¸ˆ(€€€€€€€€¥˜	}UM}I=MQ	%Q€ôôQIU(€€€€€€€€€€€€‰ÑåÁ•Ì¸5…ä…ÕÍ”™É½ÍÑ‰¥Ñ”¸ˆ¤°(€€€€€€€€•±Í”(€€€€€€€€€€€€‰ÑåÁ•Ì¸5…ä…ÕÍ”™É••é¥¹œ¸ˆ¤°(€€€€€€€€•¹‘¥˜(€€€€€€€€¹•™™•Ð€ôQ}MUAI}Q%Y}=9}I°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÑåÁ”€ôQeA}]QHô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Ii}=I}I=MQ	%Q°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É••é•Éä°(€€€ô°((€€€m5=Y}%MI5%9}Y=%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%MI5%9Y=%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1•ÑÌ½ÕÐ„¡…Éµ¥¹œÉåq¸ˆ(€€€€€€€€€€€€‰Ñ¡…Ð…¹¹½Ð‰”•Ù…‘•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥Í…Éµ¥¹Y½¥”°(€€€ô°((€€€m5=Y}AIQ%9}M!=Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AIQ%9M!=Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”™½”ÌÑÑ…¬…¹‘q¸ˆ(€€€€€€€€€€€€‰MÀ¸Ñ¬°Ñ¡•¸ÍÝ¥Ñ¡•Ì½ÕÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AIQ%9}M!=P°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ=I}IA159Q}!@ô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}1MP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A…ÉÑ¥¹M¡½Ð°(€€€ô°((€€€m5=Y}Q=AMe}QUIYet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q=AMdµQUIYdˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÝ…ÁÌ…±°ÍÑ…Ð¡…¹•ÌÑ¡…Ñq¸ˆ(€€€€€€€€€€€€‰…™™•ÐÑ¡”Ñ…É•Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q=AMe}QUIYd°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô	}UAQ}5=Y}Q€øô9|Ü€ü€À€è€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}Q-}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MI5	1}9aQ}QUI9}=IH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q½ÁÍåQÕÉÙä°(€€€ô°((€€€m5=Y}I%9%9}-%MMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%9%9-%MLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍÉ…¥¹¥¹-¥ÍÍ•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÜÔô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ô	}!1}	1=-%9€øô9|Ø°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…¥¹¥¹-¥ÍÌ°(€€€ô°((€€€m5=Y}IQe}M!%1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IQdM!%1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ù…‘•ÌÍÑ…ÑÕÌµ½Ù•Ì™½Éq¸ˆ(€€€€€€€€€€€€‰½¹”ÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ì°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}IQe}M!%1ô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…™ÑåM¡¥•±°(€€€ô°((€€€m5=Y}1=]I}M!%1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1=]HM!%1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I…¥Í•ÌÑ¡”•™•¹Í”½™q¸ˆ(€€€€€€€€€€€€‰É…ÍÌµÑåÁ”A½¯¥µ½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}1=]I}M!%1°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}11}	QQ1IL°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±½Ý•ÉM¡¥•±°(€€€ô°((€€€m5=Y}IMMe}QII%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IMMdQII%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”É½Õ¹ÑÕÉ¹ÌÑ¼É…ÍÍq¸ˆ(€€€€€€€€€€€€‰™½È€ÔÑÕÉ¹Ì¸I•ÍÑ½É•Ì!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IMMe}QII%8°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}U%9}a%Q°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}%IMP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}IMMe}QII%8°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…ÍÍåQ•ÉÉ…¥¸°(€€€ô°((€€€m5=Y}5%MQe}QII%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5%MQdQII%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½Ù•ÉÌÑ¡”É½Õ¹Ý¥Ñ µ¥ÍÑq¸ˆ(€€€€€€€€€€€€‰™½È€ÔÑÕÉ¹Ì¸	±½­ÌÍÑ…ÑÕÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5%MQe}QII%8°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}U%9}a%Q°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}%IMP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}5%MQe}QII%8°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5¥ÍÑåQ•ÉÉ…¥¸°(€€€ô°((€€€m5=Y}1QI%et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1QI%dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±•ÑÉ¥™¥•ÌÑ¡”™½”°µ…­¥¹q¸ˆ(€€€€€€€€€€€€‰¥ÑÌ¹•áÐµ½Ù”±•ÑÉ¥ŒµÑåÁ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}1QI%d°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MAQ-}UA|Äô°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}AI	=1%}!Iô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±•ÑÉ¥™ä°(€€€ô°((€€€m5=Y}A1e}I=U!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A1dI=U ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰A±…åÌÉ½Õ Ý¥Ñ Ñ¡”™½”¹q¸ˆ(€€€€€€€€€€€€‰5…ä±½Ý•ÈÑÑ…¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A±…åI½Õ °(€€€ô°((€€€m5=Y}%Ie}]%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%Id]%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑ¥ÉÌÕÀ„™…¥ÉäÝ¥¹Ñ½q¸ˆ(€€€€€€€€€€€€‰ÍÑÉ¥­”Ñ¡”™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÌÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ý¥¹‘5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}…¥Éå]¥¹°(€€€ô°((€€€m5=Y}5==9	1MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5==9	1MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ Ñ¡”Á½Ý•È½™q¸ˆ(€€€€€€€€€€€€‰Ñ¡”µ½½¸¸5…ä±½Ý•ÈMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}I=9Q}5=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5½½¹‰±…ÍÐ°(€€€ô°((€€€m5=Y}	==5	UIMQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	==5	UIMPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	±…ÍÑÌ‰½Ñ ½ÁÁ½Í¥¹œ™½•Íq¹Ý¥Ñ „‘•ÍÑÉÕÑ¥Ù”Í½Õ¹¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °€¼¼AITèÍÁÉ•…Ñ¼‰½Ñ •¹•µ¥•Ì°¹•Ù•ÈÑ¡”…±±ä(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q})5M}=Q!IM}	UQ}5%MM}=9}QUI8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	½½µ‰ÕÉÍÐ°(€€€ô°((€€€m5=Y}%Ie}1=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%Id1=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1½­Ì‘½Ý¸Ñ¡”‰…ÑÑ±•™¥•±‘q¸ˆ(€€€€€€€€€€€€‰ÁÉ•Ù•¹Ñ¥¹œ•Í…Á”¹•áÐÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%Ie}1=,°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}…¥Éå1½¬°(€€€ô°((€€€m5=Y}-%9M}M!%1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰-%9LM!%1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ù…‘•Ì‘…µ…”°…¹Í¡…ÉÁ±åq¸ˆ(€€€€€€€€€€€€‰É•‘Õ•ÌÑÑ…¬¥˜ÍÑÉÕ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ð°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}-%9M}M!%1ô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}-¥¹ÍM¡¥•±°(€€€ô°((€€€m5=Y}A1e}9%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A1d9%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	•™É¥•¹Ñ¡”™½”°±½Ý•É¥¹q¸ˆ(€€€€€€€€€€€€‰¥ÑÌÑÑ…¬Ý¥Ñ¡½ÕÐ™…¥°¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QQ-}=]8°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}U%9}a%Q°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}A1e}9%°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A±…å9¥”°(€€€ô°((€€€m5=Y}=9%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=9%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡…É•Ì„Í•É•ÐÝ¥Ñ Ñ¡•q¸ˆ(€€€€€€€€€€€€‰™½”°±½Ý•É¥¹œMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MA%1}QQ-}=]8°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½¹™¥‘”°(€€€ô°((€€€m5=Y}%5=9}MQ=I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%5=9MQ=I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]¡¥ÁÌÕÀ„ÍÑ½É´½™q¸ˆ(€€€€€€€€€€€€‰‘¥…µ½¹‘Ì¸5…äÕÀ•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô	}UAQ}5=Y}Q€øô9|Ü€ü5=Y}Q}}A1UM|Èè€5=Y}Q}}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÔÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}1MP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥…µ½¹‘MÑ½É´°(€€€ô°((€€€m5=Y}MQ5}IUAQ%=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ4IUAQ%=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%µµ•ÉÍ•ÌÑ¡”™½”¥¸¡•…Ñ•‘q¸ˆ(€€€€€€€€€€€€‰ÍÑ•…´¸5…ä¥¹™±¥Ð„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ñ¡…ÝÍUÍ•È€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}1MP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}M1ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ•…µÉÕÁÑ¥½¸°(€€€ô°((€€€m5=Y}!eAIMA}!=1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!eAIMA!=1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ!åÁ•ÉÍÁ…•!½±••ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%9P°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}%IMP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}!eAIMA}!=1°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!eAIMA}UIeô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!åÁ•ÉÍÁ…•!½±”°(€€€ô°((€€€m5=Y}]QI}M!UI%-9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]QHM!UI%-8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡É½ÝÌ€ÈÑ¼€ÔÍÑ…ÉÌÑ¡…Ñq¸ˆ(€€€€€€€€€€€€‰…É”ÍÕÉ”Ñ¼ÍÑÉ¥­”™¥ÉÍÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MA%M}A=]I}=YII%°(€€€€€€€€¹Á½Ý•È€ô€ÄÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ä°(€€€€€€€€¹…Ñ•½Éä€ô	}UAQ}5=Y}Q€øô9|Ü€ü5}Q=Ie}MA%0€è5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì(€€€€€€€€€€€€¹ÍÁ•¥•ÍA½Ý•É=Ù•ÉÉ¥‘”¹ÍÁ•¥•Ì€ôMA%M}I9%9)}M °(€€€€€€€€€€€€¹ÍÁ•¥•ÍA½Ý•É=Ù•ÉÉ¥‘”¹Á½Ý•È€ô€ÈÀ°(€€€€€€€€€€€€¹ÍÁ•¥•ÍA½Ý•É=Ù•ÉÉ¥‘”¹¹Õµ=™!¥ÑÌ€ô€Ì(€€€€€€€ô°(€€€€€€€€¹µÕ±Ñ¥!¥Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}I1%H°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]…Ñ•ÉM¡ÕÉ¥­•¸°(€€€ô°((€€€m5=Y}5eMQ%1}%It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5eMQ%0%Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	É•…Ñ¡•Ì„ÍÁ•¥…°°¡½Ñq¸ˆ(€€€€€€€€€€€€‰™¥É”¸1½Ý•ÉÌMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|Ü€ü€ÜÔ€è€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5åÍÑ¥…±¥É”°(€€€ô°((€€€m5=Y}MA%-e}M!%1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MA%-dM!%1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ù…‘•Ì…ÑÑ…¬°…¹‘…µ…•Íq¸ˆ(€€€€€€€€€€€€‰Ñ¡”™½”¥˜ÍÑÉÕ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ð°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}MA%-e}M!%1ô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ¥­åM¡¥•±°(€€€ô°((€€€m5=Y}I=5Q%}5%MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=5Q%5%MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I…¥Í•ÌÑ¡”MÀ¸•˜½˜…q¸ˆ(€€€€€€€€€€€€‰Á…ÉÑ¹•ÈA½¯¥µ½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=5Q%}5%MP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Èô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQ%U0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É½µ…Ñ¥5¥ÍÐ°(€€€ô°((€€€m5=Y}I%}%5AU1Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%%5AU1Mˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰áÁ½Í•ÌÑ¡”™½”Ñ¼„ÁÕ±Í•q¸ˆ(€€€€€€€€€€€€‰Ñ¡…ÐÍ¡…ÉÁ±äÕÑÌMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MA%1}QQ-}=]9|È°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}I=9Q}5=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•É¥•%µÁÕ±Í”°(€€€ô°((€€€m5=Y}Y9=5}I9!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Y9=4I9 ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”ÑÑ…¬°MÀ¸Ñ­q¸ˆ(€€€€€€€€€€€€‰…¹MÁ••½˜Á½¥Í½¹•™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Y9=5}I9 °(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}Q=a%°=5	=}MQIQI}A=%M=9}L°=5	=}MQIQI}A=%M=9}A=]H°=5	=}MQIQI}Q=a%}MA%-Mô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Y•¹½µÉ•¹ °(€€€ô°((€€€m5=Y}A=]It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=]Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…µ…•ÌÑ¡”™½”¥˜¥ÐÕÍ•Íq¸ˆ(€€€€€€€€€€€€‰„¥É”µÑåÁ”µ½Ù”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A=]H°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ä°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Èô°(€€€€€€€€¹Á½Ý‘•É5½Ù”€ôQIU°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°€¼½=9QMQ}Q}EU%-1e}I=]}	=I(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½Ý‘•È°(€€€ô°((€€€m5=Y}=59et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=59dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I…¥Í•ÌMÀ¸Ñ¬°MÀ¸•˜…¹‘q¸ˆ(€€€€€€€€€€€€‰MÁ••½¸Ñ¡”€É¹ÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=59d°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}11}MQQM}UA|Äô°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð¹ÑÝ½QÕÉ¹ÑÑ…¬€ôì€¹ÍÑÉ¥¹%€ôMQI%9%}A-95	M=I	%9A=]Hô°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQ%U0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•½µ…¹ä°(€€€ô°((€€€m5=Y}59Q%}1Uat€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰59Q%1U`ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	½½ÍÑÌÑ¡”‘•™•¹Í•Ì½™q¸ˆ(€€€€€€€€€€€€‰Ñ¡½Í”Ý¥Ñ A±ÕÌ½È5¥¹ÕÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}59Q%}1U`°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…¹•Ñ¥±Õà°(€€€ô°((€€€m5=Y}!AAe}!=UIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!AAd!=UHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½Õ‰±•ÌÑ¡”…µ½Õ¹Ð½™q¸ˆ(€€€€€€€€€€€€‰AÉ¥é”5½¹•äÉ••¥Ù•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!AAe}!=UH°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÌÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}11}MQQM}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}!AAe}!=UH°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!…ÁÁå!½ÕÈ°(€€€ô°((€€€m5=Y}1QI%}QII%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1QI%QII%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±•ÑÉ¥™¥•ÌÑ¡”É½Õ¹™½Éq¸ˆ(€€€€€€€€€€€€ˆÔÑÕÉ¹Ì¸AÉ•Ù•¹ÑÌÍ±••À¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}1QI%}QII%8°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}U%9}a%Q°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}%IMP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}1QI%}QII%8°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±•ÑÉ¥Q•ÉÉ…¥¸°(€€€ô°((€€€m5=Y}ii1%9}15t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰ii1%914ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…µ…•Ì™½•Ì‰ä•µ¥ÑÑ¥¹q¸ˆ(€€€€€€€€€€€€‰„‰É¥¡Ð™±…Í ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}…éé±¥¹±•…´°(€€€ô°((€€€m5=Y}1	IQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1	IQˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½¹É…ÑÕ±…Ñ•Ìå½Ô½¸å½ÕÉq¸ˆ(€€€€€€€€€€€€‰ÍÁ•¥…°‘…ä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}1	IQ°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÐÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}11}MQQM}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}1	IQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•±•‰É…Ñ”°(€€€ô°((€€€m5=Y}!=1}!9Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!=1!9Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È…¹…±±ä¡½±¡…¹‘Íq¸ˆ(€€€€€€€€€€€€‰µ…­¥¹œÑ¡•´¡…ÁÁä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!=1}!9L°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÐÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}11}MQQM}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!½±‘!…¹‘Ì°(€€€ô°((€€€m5=Y}		e}=11}eMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰		dµ=10eLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”™½”ÌÑÑ…­q¸ˆ(€€€€€€€€€€€€‰‰•™½É”¥Ð…¸µ½Ù”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QQ-}=]8°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÌÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ä°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}I1%H°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	…‰å½±±å•Ì°(€€€ô°((€€€m5=Y}9Uii1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9Uii1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰IÕ‰Ì¥ÑÌ¡••­Ì……¥¹ÍÑq¸ˆ(€€€€€€€€€€€€‰Ñ¡”™½”°Á…É…±åé¥¹œ¥Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1eM%L°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!Iô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}9Õéé±”°(€€€ô°((€€€m5=Y}!=1}	-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!=1	,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ…±Í•MÝ¥Á••ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}1M}M]%A°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÐÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°€¼½=9QMQ}Q}EU%-1e}I=]}	=I(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!½±‘	…¬°(€€€ô°((€€€m5=Y}%9MQQ%=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%9MQQ%=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”™½”¥Ì¥¹™•ÍÑ•…¹‘q¸ˆ(€€€€€€€€€€€€‰…ÑÑ…­•™½È€‰	%9%9}QUI9LˆÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}]I@°(€€€€€€€€€€€€¹µÕ±Ñ¥ÍÑÉ¥¹œ¹ÝÉ…ÁÁ•€ô	}5M}]IAA}%9MQQ%=8°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%¹™•ÍÑ…Ñ¥½¸°(€€€ô°((€€€m5=Y}A=]I}UA}AU9!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=]HµU@AU9 ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡…ÉÁÕ¹ Ñ¡…ÐÉ…¥Í•Íq¸ˆ(€€€€€€€€€€€€‰Ñ¡”ÕÍ•ÈÌÑÑ…¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q-}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]%Q!}==}=9%Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½Ý•ÉUÁAÕ¹ °(€€€ô°((€€€m5=Y}=	1%Y%=9}]%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=	1%Y%=8]%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍÉ…¥¹¥¹-¥ÍÍ•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÜÔô°(€€€€€€€€¹¡•…±¥¹5½Ù”€ô	}!1}	1=-%9€øô9|Ø°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}=‰±¥Ù¥½¹]¥¹œ°(€€€ô°((€€€m5=Y}Q!=UM9}II=]Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q!=UM9II=]Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…¸¡¥Ð±å¥¹œ™½•Ì°Ñ¡•¹q¸ˆ(€€€€€€€€€€€€‰­¹½­ÌÑ¡•´Ñ¼Ñ¡”É½Õ¹¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M5-}=]8°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‘…µ…•Í¥É‰½É¹”€ôQIU°(€€€€€€€€¹¥¹½É•QåÁ•%™±å¥¹¹‘U¹É½Õ¹‘•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQ%U0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}Q!=UM9}II=]L°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}Q!=UM9}]YMô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q¡½ÕÍ…¹‘ÉÉ½ÝÌ°(€€€ô°((€€€m5=Y}Q!=UM9}]YMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q!=UM9]YLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡½Í”¡¥Ð‰äÑ¡”Ý…Ù”…¹q¸ˆ(€€€€€€€€€€€€‰¹¼±½¹•È•Í…Á”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AIY9Q}MA°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}Q!=UM9}]YL°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}Q!=UM9}II=]Mô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q¡½ÕÍ…¹‘]…Ù•Ì°(€€€ô°((€€€m5=Y}19M}]IQ!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰19L]IQ ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…Ñ¡•ÉÌÑ¡”•¹•Éä½˜Ñ¡•q¸ˆ(€€€€€€€€€€€€‰±…¹Ñ¼…ÑÑ…¬•Ù•Éä™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1…¹‘Í]É…Ñ °(€€€ô°((€€€m5=Y}1%!Q}=}IU%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%!P=IU%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¥É•Ì„É•…Ð‰•…´½˜±¥¡Ñq¸ˆ(€€€€€€€€€€€€‰Ñ¡…Ð…±Í¼¡ÕÉÑÌÑ¡”ÕÍ•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=%0°(€€€€€€€€¹Á½Ý•È€ô€ÄÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹É•½¥±A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1¥¡Ñ=™IÕ¥¸°(€€€ô°((€€€m5=Y}=I%%9}AU1Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=I%%8AU1Mˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	•…µÌ½˜±½Ý¥¹œ‰±Õ”±¥¡Ñq¸ˆ(€€€€€€€€€€€€‰‰±…ÍÐ‰½Ñ ™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹ÁÕ±Í•5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}%IMP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}=É¥¥¹AÕ±Í”°(€€€ô°((€€€m5=Y}AI%A%}	1Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AI%A%	1Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰•…ÉÍ½µ”‰±…‘•Ì½˜ÍÑ½¹•q¸ˆ(€€€€€€€€€€€€‰…ÑÑ…¬‰½Ñ ™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}1MP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÉ•¥Á¥•	±…‘•Ì°(€€€ô°((€€€m5=Y}I=9}M9Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=8M9Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ±½Í•½µ‰…Ñ•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}MA}=]8°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…½¹Í•¹Ð°(€€€ô°((€€€m5=Y}!eAIMA}UIet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!eAIMAUIdˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ!åÁ•ÉÍÁ…•!½±••ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!eAIMA}UId°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹Í­•Ñ¡	…¹¹•€ô€¡	}M-Q!}	9L€øô9|ä¤°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%9P°€¼¼Q=<è%ÌÑ¡¥ÌÍÕÁÁ½Í•Ñ¼¡…ÁÁ•¸‰•™½É”Ñ¡”…ÑÑ…¬…¹¥µ…Ñ¥½¸ü(€€€€€€€ô°(€€€€€€€ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°€¼½=9QMQ}Q}a%QM}U%9}5=I}%}%IMP(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}!eAIMA}UId°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!eAIMA}!=1ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!åÁ•ÉÍÁ…•ÕÉä°(€€€ô°((€€€m5=Y}M!=I}UAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!=IU@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I•ÍÑ½É•ÌÑ¡”ÕÍ•ÈÌ!@¹q¸ˆ(€€€€€€€€€€€€‰5½É”!@¥¸„Í…¹‘ÍÑ½É´¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M!=I}U@°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|ä€ü€Ô€è€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}EU1%Qe}A9M}=9}Q%5%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}M9MQ=I5ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡½É•UÀ°(€€€ô°((€€€m5=Y}%IMQ}%5AIMM%=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%IMP%5AIMM%=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌ¡…É…¹™¥ÉÍÐ¹q¸ˆ(€€€€€€€€€€€€‰=¹±äÝ½É­Ì™¥ÉÍÐÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%IMQ}QUI9}=91d°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€È°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹µ½Ù•AÉ½Á•ÉÑä€ô5=Y}%IMQ}%5AIMM%=8ô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥ÉÍÑ%µÁÉ•ÍÍ¥½¸°(€€€ô°((€€€m5=Y}	9U1}	U9-It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	9U0	U9-Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÉ½Ñ•ÑÌÕÍ•È…¹Á½¥Í½¹Íq¸ˆ(€€€€€€€€€€€€‰™½•Ì½¸½¹Ñ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ð°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}	9U1}	U9-Hô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	…¹•™Õ±	Õ¹­•È°(€€€ô°((€€€m5=Y}MA%I%Q}M!-1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MA%I%PM!-1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰™Ñ•È‰•¥¹œ¡¥Ð°™½•Ì…¹q¸ˆ(€€€€€€€€€€€€‰¹¼±½¹•È•Í…Á”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AIY9Q}MA°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}5=9M}]%Q!}==}AA1L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ¥É¥ÑM¡…­±”°(€€€ô°((€€€m5=Y}I-MQ}1I%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I-MP1I%Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÝ¥¹ÌÑ¡”…ÉµÌÑ¼ÍÑÉ¥­•q¸ˆ(€€€€€€€€€€€€‰%Ð¥¹½É•ÌÍÑ…Ð¡…¹•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ•™•¹Í•Ù…Í¥½¹MÑ…•Ì€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}5=9M}]%Q!}==}AA1L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}…É­•ÍÑ1…É¥…Ð°(€€€ô°((€€€m5=Y}MAI-1%9}I%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MAI-1%9I%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¥¹ÌÝ¥Ñ ‰Õ‰‰±•Ì¸ÕÉ•Íq¸ˆ(€€€€€€€€€€€€‰‰ÕÉ¹Ì½¸½¹Ñ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÍÑ…ÑÕÌ€ôMQQULÅ}	UI8ô°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I5=Y}MQQUL°(€€€€€€€€€€€€¹Í¡••É½É•=Ù•ÉÉ¥‘”€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}M1ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ…É­±¥¹É¥„°(€€€ô°((€€€m5=Y}%}!55It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%!55Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÝ¥¹ÌÑ¡”™¥ÍÐÑ¼ÍÑÉ¥­”¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”ÕÍ•ÈÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!%1ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%•!…µµ•È°(€€€ô°((€€€m5=Y}1=I1}!1%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1=I0!1%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I•ÍÑ½É•Ì…¸…±±äÌ!@¹q¸ˆ(€€€€€€€€€€€€‰!•…±Ìµ½É”½¸É…ÍÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!1}AU1M°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹µ½Ù•AÉ½Á•ÉÑä€ô5=Y}Q}1=I1}!1%9ô°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}a%Q}U%9}%9}9e}=9QMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±½É…±!•…±¥¹œ°(€€€ô°((€€€m5=Y}!%!}!=IMA=]It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!% !=IMA=]Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M±…µÌ¡…É¥¹Ñ¼Ñ¡”™½”Ý¥Ñ¡q¸ˆ(€€€€€€€€€€€€‰¥ÑÌ•¹Ñ¥É”‰½‘ä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!¥¡!½ÉÍ•Á½Ý•È°(€€€ô°((€€€m5=Y}MQI9Q!}MAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQI9Q M@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M…ÁÌÑ¡”™½”ÌÑÑ…¬Ñ½q¸ˆ(€€€€€€€€€€€€‰¡•…°!@°Ñ¡•¸‘É½ÁÌÑÑ…¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQI9Q!}M@°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ô	}!1}	1=-%9€øô9|Ø°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑÉ•¹Ñ¡M…À°(€€€ô°((€€€m5=Y}M=1I}	1t€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M=1H	1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡…É•Ì™¥ÉÍÐÑÕÉ¸°Ñ¡•¹q¸ˆ(€€€€€€€€€€€€‰¡½ÁÌÝ¥Ñ „‰±…‘”½˜±¥¡Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M=1I}	4°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð¹ÑÝ½QÕÉ¹ÑÑ…¬€ôì€¹ÍÑÉ¥¹%€ôMQI%9%}A-59Q==-MU91%!P°€¹Ý•…Ñ¡•È€ô	}]Q!I}MU8ô°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}MU99e}eô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M½±…É	±…‘”°(€€€ô°((€€€m5=Y}1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ „™±ÕÉÉä½™q¸ˆ(€€€€€€€€€€€€‰Íµ…±°±•…Ù•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÐÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}I=]Q!ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1•…™…”°(€€€ô°((€€€m5=Y}MA=Q1%!Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MA=Q1%!Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…­•ÌÑ¡”™½”…ÑÑ…¬Ñ¡•q¸ˆ(€€€€€€€€€€€€‰ÍÁ½Ñ±¥¡Ñ•A½¯¥µ½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=11=]}5°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ì°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ½Ñ±¥¡Ð°(€€€ô°((€€€m5=Y}Q=a%}Q!It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q=a%Q!Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ „Ñ¡É•…Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰Á½¥Í½¹Ì…¹‘É½ÁÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q=a%}Q!I°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}M!%Q})U}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}Q=a%ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q½á¥Q¡É•…°(€€€ô°((€€€m5=Y}1MI}=UMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1MH=ULˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Õ…É…¹Ñ••ÌÑ¡”¹•áÐµ½Ù•q¸ˆ(€€€€€€€€€€€€‰Ý¥±°‰”„É¥Ñ¥…°¡¥Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}1MI}=UL°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÌÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}Q-}UA|Äô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1…Í•É½ÕÌ°(€€€ô°((€€€m5=Y}I}UAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰HU@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	½½ÍÑÌÑ¡”…ÑÑ…­Ì½™q¸ˆ(€€€€€€€€€€€€‰Ñ¡½Í”Ý¥Ñ A±ÕÌ½È5¥¹ÕÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I}U@°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MAQ-}UA|Äô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•…ÉUÀ°(€€€ô°((€€€m5=Y}Q!I=Q}!=At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q!I=P!=@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡½ÁÌÑ¡”Ñ¡É½…ÐÑ¼‘¥Í…‰±•q¸ˆ(€€€€€€€€€€€€‰Í½Õ¹µ½Ù•Ì™½È€ÈÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q!I=Q}!=@°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}H°€¹¡…¹”€ô€Ô°ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}5-}=11=]%9}5=9M}9IY=UL°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q¡É½…Ñ¡½À°(€€€ô°((€€€m5=Y}A=119}AUt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=118AUˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰áÁ±½‘•Ì½¸™½•Ì°‰ÕÑq¸ˆ(€€€€€€€€€€€€‰É•ÍÑ½É•Ì…±±äÌ!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%Q}95e}!1}11d°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…±±¥ÍÑ¥5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½±±•¹AÕ™˜°(€€€ô°((€€€m5=Y}9!=I}M!=Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9!=HM!=Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑÉ…¹±•ÌÑ¡”™½”Ý¥Ñ …q¸ˆ(€€€€€€€€€€€€‰¡…¥¸¸Q¡”™½”…¸Ð•Í…Á”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AIY9Q}MA°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}5=9M}]%Q!}==}AA1L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¹¡½ÉM¡½Ð°(€€€ô°((€€€m5=Y}AMe!%}QII%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AMe!%QII%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”É½Õ¹ÑÕÉ¹ÌÝ•¥É™½Éq¸ˆ(€€€€€€€€€€€€ˆÔÑÕÉ¹Ì¸	±½­ÌÁÉ¥½É¥Ñä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AMe!%}QII%8°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MAQ-}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}U%9}a%Q°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}AMe!%}QII%8°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍå¡¥Q•ÉÉ…¥¸°(€€€ô°((€€€m5=Y}1U9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1U9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1Õ¹•Ì…ÐÑ¡”™½”Ñ¼±½Ý•Éq¸ˆ(€€€€€€€€€€€€‰¥ÑÌÑÑ…¬ÍÑ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1Õ¹”°(€€€ô°((€€€m5=Y}%I}1M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%I1M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]¡¥ÁÌÑ¡”™½”Ý¥Ñ ™¥É•q¸ˆ(€€€€€€€€€€€€‰±½Ý•É¥¹œ¥ÑÌ•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}MU99e}eô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥É•1…Í °(€€€ô°((€€€m5=Y}A=]I}QI%At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=]HQI%@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%Ð¡¥ÑÌ¡…É‘•ÈÑ¡”µ½É•q¸ˆ(€€€€€€€€€€€€‰ÍÑ…Ð‰½½ÍÑÌÑ¡”ÕÍ•È¡…Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQ=I}A=]H°(€€€€€€€€¹Á½Ý•È€ô€ÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]%Q!}==}=9%Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½Ý•ÉQÉ¥À°(€€€ô°((€€€m5=Y}	UI9}UAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	UI8U@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	ÕÉ¹Ì½ÕÐÑ¡”ÕÍ•È™Õ±±åq¸ˆ(€€€€€€€€€€€€‰É•µ½Ù¥¹œÑ¡”¥É”ÑåÁ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%1}%}9=Q}I}QeA°(€€€€€€€€¹Á½Ý•È€ô€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ñ¡…ÝÍUÍ•È€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÑåÁ”€ôQeA}%Iô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I5=Y}I}QeA°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}MU99e}eô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	ÕÉ¹UÀ°(€€€ô°((€€€m5=Y}MA}M]At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MAM]@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÝ…ÁÌÕÍ•ÈÌMÁ••Ý¥Ñ¡q¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•ÐÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MA}M]@°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ••‘MÝ…À°(€€€ô°((€€€m5=Y}M5IQ}MQI%-t€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M5IPMQI%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÝ¥Ñ …¸…ÕÉ…Ñ•q¸ˆ(€€€€€€€€€€€€‰¡½É¸Ñ¡…Ð¹•Ù•Èµ¥ÍÍ•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Mµ…ÉÑMÑÉ¥­”°(€€€ô°((€€€m5=Y}AUI%et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AUI%dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÕÉ•ÌÑ¡”™½”ÌÍÑ…ÑÕÍq¸ˆ(€€€€€€€€€€€€‰Ñ¼É•ÍÑ½É”!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AUI%d°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}11}MQQM}UA|Äô°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÕÉ¥™ä°(€€€ô°((€€€m5=Y}IY1Q%=9}9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IY1Q%=89ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…¹•ÌÝ¥Ñ µåÍÑ¥…°Á½Ý•È¹q¸ˆ(€€€€€€€€€€€€‰5…Ñ¡•ÌÕÍ•ÈÌ™¥ÉÍÐÑåÁ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IY1Q%=9}9°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‘…¹•5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I•Ù•±…Ñ¥½¹…¹”°(€€€ô°((€€€m5=Y}=I}9=IIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=I9=IHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÝ¥Ñ „É…äÑ¡…Ñq¸ˆ(€€€€€€€€€€€€‰¹Õ±±¥™¥•ÌÑ¡”™½”Ì‰¥±¥Ñä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹é5½Ù”€ôì€¹Á½Ý•É=Ù•ÉÉ¥‘”€ô€ÄÐÀô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=I}9=IH°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}M!%Q})U}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½É•¹™½É•È°(€€€ô°((€€€m5=Y}QI=A}-%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QI=@-%,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¸¥¹Ñ•¹Í”­¥¬™É½´Ñ¡•q¸ˆ(€€€€€€€€€€€€‰ÑÉ½Á¥Ì¸1½Ý•ÉÌÑÑ…¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}QÉ½Á-¥¬°(€€€ô°((€€€m5=Y}%9MQIUQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%9MQIUPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰=É‘•ÉÌÑ¡”Ñ…É•ÐÑ¼ÕÍ•q¸ˆ(€€€€€€€€€€€€‰¥ÑÌ±…ÍÐµ½Ù”……¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%9MQIUP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MAQ-}UA|Äô°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%¹ÍÑÉÕÐ°(€€€ô°((€€€m5=Y}	-}	1MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	,	1MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!•…ÑÌ‰•…¬Ñ¼…ÑÑ…¬±…ÍÐ¹q¸ˆ(€€€€€€€€€€€€‰	ÕÉ¹Ì™½”½¸½¹Ñ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	-}	1MP°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€´Ì°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹‰…±±¥ÍÑ¥5½Ù”€ôQIU°(€€€€€€€€¹µ•¥ÉÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Q}	e}AIY}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	•…­	±…ÍÐ°(€€€ô°((€€€m5=Y}19%9}M1Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰19%9M1Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…­•Ì„‰¥œ¹½¥Í”Ý¥Ñ¡q¸ˆ(€€€€€€€€€€€€‰¥ÑÌÍ…±•Ì¸É½ÁÌ•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}I=9Q}5=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…¹¥¹M…±•Ì°(€€€ô°((€€€m5=Y}I=9}!55It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=8!55Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÝ¥¹Ì¥ÑÌÝ¡½±”‰½‘åq¸ˆ(€€€€€€€€€€€€‰±¥­”„¡…µµ•ÈÑ¼‘…µ…”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}I=9}	IQ °=5	=}MQIQI}I=9}9°=5	=}MQIQI}I=9}I°=5	=}MQIQI}I=9}IUM °=5	=}MQIQI}I=9}Q%1ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…½¹!…µµ•È°(€€€ô°((€€€m5=Y}	IUQ1}M]%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	IUQ0M]%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Y¥½±•¹Ñ±äÍÝ¥¹Ì…É½Õ¹‘q¸ˆ(€€€€€€€€€€€€‰Ñ¼¡ÕÉÐ•Ù•Éå½¹”¹•…É‰ä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	ÉÕÑ…±MÝ¥¹œ°(€€€ô°((€€€m5=Y}UI=I}Y%1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰UI=IY%0ˆ¤°(€€€€€€€€¥˜	}AIII}%}]Q!H€ôô	}%}]Q!I}M9=\(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]•…­•¹Ì…±°…ÑÑ…­Ì°‰ÕÑq¸ˆ(€€€€€€€€€€€€‰½¹±äÕÍ…‰±”Ý¥Ñ Í¹½Ü¸ˆ¤°(€€€€€€€€•±¥˜	}AIII}%}]Q!H€ôô	}%}]Q!I}	=Q (€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]•…­•¹Ì…±°…ÑÑ…­Ì¥™q¸ˆ(€€€€€€€€€€€€‰ÕÍ•¥¸¡…¥°½ÈÍ¹½Ü¸ˆ¤°(€€€€€€€€•±Í”(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]•…­•¹Ì…±°…ÑÑ…­Ì°‰ÕÑq¸ˆ(€€€€€€€€€€€€‰½¹±äÕÍ…‰±”Ý¥Ñ ¡…¥°¸ˆ¤°(€€€€€€€€•¹‘¥˜(€€€€€€€€¹•™™•Ð€ôQ}UI=I}Y%0°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!%1ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÕÉ½É…Y•¥°°(€€€ô°((€€€m5=Y}M!11}QIAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!10QI@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M•ÑÌ„Í¡•±°ÑÉ…ÀÑ¡…Ñq¸ˆ(€€€€€€€€€€€€‰‘…µ…•Ì½¸½¹Ñ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M!11}QI@°(€€€€€€€€¹Á½Ý•È€ô€ÄÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€´Ì°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•¥ÉÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡•±±QÉ…À°(€€€ô°((€€€m5=Y}1UI}99=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1UH99=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÍÑÉ½¹œÉ…äÑ¡…Ð¡…ÉÍ¡±åq¸ˆ(€€€€€€€€€€€€‰±½Ý•ÉÌMÀ¸ÑÑ…¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}5%9UM|È°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±•ÕÉ…¹¹½¸°(€€€ô°((€€€m5=Y}AMe!%}9Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AMe!%9Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡½µÁÌÝ¥Ñ ÁÍå¡¥Œ™…¹Ì¹q¸ˆ(€€€€€€€€€€€€‰•ÍÑÉ½åÌ…¹ä‰…ÉÉ¥•ÉÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	I-}MI8°(€€€€€€€€€€€€¹ÁÉ•ÑÑ…­™™•Ð€ôQIU°(€€€€€€€ô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰¥Ñ¥¹5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍå¡¥…¹Ì°(€€€ô°((€€€m5=Y}MQ=5A%9}Q9QIU5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ=5A%9Q9QIU4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑ½µÁÌ…É½Õ¹…¹É¥±ä¹q¸ˆ(€€€€€€€€€€€€‰MÑÉ½¹•È…™Ñ•È„™…¥±ÕÉ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQ=5A%9}Q9QIU4°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ½µÁ¥¹Q…¹ÑÉÕ´°(€€€ô°((€€€m5=Y}M!=]}	=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!=\	=9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑÉ¥­•ÌÝ¥Ñ „¡…Õ¹Ñ•‘q¸ˆ(€€€€€€€€€€€€‰‰½¹”¸5¥¡Ð‘É½À•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}M!%Q})U}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô=5	=}MQIQI}M!=]}	=9°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}	=9}1U°=5	=}MQIQI}	=95I9°=5	=}MQIQI}	=9}IUM!ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡…‘½Ý	½¹”°(€€€ô°((€€€m5=Y}1I=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1I=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÝ¥Ñ „¡¥ µÍÁ••‘q¸ˆ(€€€€€€€€€€€€‰É½¬Ñ¡…Ð…±Ý…åÌ½•Ì™¥ÉÍÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ä°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}I1%H°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•±•É½¬°(€€€ô°((€€€m5=Y}1%EU%Q%=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%EU%Q%=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M±…µÌÑ¡”™½”Ý¥Ñ Ý…Ñ•È¹q¸ˆ(€€€€€€€€€€€€‰…¸±½Ý•È•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}M!%Q})U}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}I%9}9ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1¥ÅÕ¥‘…Ñ¥½¸°(€€€ô°((€€€m5=Y}AI%M5Q%}1MIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AI%M5Q%1MHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡¥ Á½Ý•È±…Í•ÈÑ¡…Ñq¸ˆ(€€€€€€€€€€€€‰™½É•ÌÉ•¡…É”¹•áÐÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I!I°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q})5M}=Q!IM}	UQ}5%MM}=9}QUI8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÉ¥Íµ…Ñ¥1…Í•È°(€€€ô°((€€€m5=Y}MAQI1}Q!%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MAQI0Q!%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑ•…±ÌÑ¡”Ñ…É•ÐÌÍÑ…Ñq¸ˆ(€€€€€€€€€€€€‰‰½½ÍÑÌ°Ñ¡•¸…ÑÑ…­Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MQ1}MQQL°(€€€€€€€€€€€€¹ÁÉ•ÑÑ…­™™•Ð€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}AA1}M}==}M}AIY}=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ•ÑÉ…±Q¡¥•˜°(€€€ô°((€€€m5=Y}MU9MQ1}MQI%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MU9MQ0MQI%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÍÕ¸µ™Õ•±•ÍÑÉ¥­”Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰¥¹½É•Ì…‰¥±¥Ñ¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ‰¥±¥Ñä€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ô	}UAQ}5=Y}1L€øô9|à°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÕ¹ÍÑ••±MÑÉ¥­”°(€€€ô°((€€€m5=Y}5==9%MQ}	5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5==9%MP	4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µ½½¸µÁ½Ý•É•‰•…´Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰¥¹½É•Ì…‰¥±¥Ñ¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ‰¥±¥Ñä€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ô	}UAQ}5=Y}1L€øô9|à°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5½½¹•¥ÍÑ	•…´°(€€€ô°((€€€m5=Y}QIU1}1==-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QIU01==,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÑ•…ÉÌÕÀ°‘É½ÁÁ¥¹q¸ˆ(€€€€€€€€€€€€‰ÑÑ…¬…¹MÀ¸ÑÑ…¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}9=	1}I=H°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q•…É™Õ±1½½¬°(€€€ô°((€€€m5=Y}i%9}iAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰i%9i@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¸•±•ÑÉ¥™¥•¥µÁ…ÐÑ¡…Ñq¸ˆ(€€€€€€€€€€€€‰…¸…ÕÍ”™±¥¹¡¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}!Iô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}i¥¹i…À°(€€€ô°((€€€m5=Y}9QUIM}59MMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9QUIL59MLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!…±Ù•ÌÑ¡”™½”Ì!@Ý¥Ñ¡q¸ˆ(€€€€€€€€€€€€‰Ñ¡”Á½Ý•È½˜¹…ÑÕÉ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%a}AI9Q}5°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹‘…µ…•A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ô	}UAQ}5=Y}1L€øô9|à°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}5=9M}]%Q!}==}AA1L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}9…ÑÕÉ•Í5…‘¹•ÍÌ°(€€€ô°((€€€m5=Y}5U1Q%}QQ-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5U1Q$µQQ,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…¬Ñ¡…Ð¡…¹•Íq¸ˆ(€€€€€€€€€€€€‰Ý¥Ñ 5•µ½É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!9}QeA}=9}%Q4°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€ÄÈÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹¡½±‘™™•Ð€ô!=1}Q}55=Idô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MI5	1}9aQ}QUI9}=IH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5Õ±Ñ¥ÑÑ…¬°(€€€ô°((€€€m5=Y}5%9}	1=]9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5%9	1=]8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%Ð•áÁ±½‘•ÌÑ¡”ÕÍ•ÈÌ¡•…‘q¸ˆ(€€€€€€€€€€€€‰Ñ¼‘…µ…”•Ù•ÉåÑ¡¥¹œ…É½Õ¹¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}!A|ÔÁ}I=%0°(€€€€€€€€¹Á½Ý•È€ô€ÄÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‘…µÁ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5¥¹‘	±½Ý¸°(€€€ô°((€€€m5=Y}A1M5}%MQMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A1M5%MQLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÝ¥Ñ •±•ÑÉ¥…°™¥ÍÑÌ¹q¸ˆ(€€€€€€€€€€€€‰9½Éµ…°µ½Ù•ÌÑÕÉ¸±•ÑÉ¥Œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%=9}1U°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A±…Íµ…¥ÍÑÌ°(€€€ô°((€€€m5=Y}A!=Q=9}eMIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A!=Q=8eMHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÍ•ÈÌ¡¥¡•ÍÐ…ÑÑ…¬ÍÑ…Ñq¸ˆ(€€€€€€€€€€€€‰‘•Ñ•Éµ¥¹•Ì¥ÑÌ…Ñ•½Éä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A!=Q=9}eMH°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ‰¥±¥Ñä€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}M5}QeA°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A¡½Ñ½¹•åÍ•È°(€€€ô°((€€€m5=Y}i%AAe}iAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰i%AAdi@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±•ÑÉ¥Œ‰ÕÉÍÑÌ…±Ý…åÌ½q¸ˆ(€€€€€€€€€€€€‰™¥ÉÍÐ…¹±…¹„É¥Ñ¥…°¡¥Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€àÀ€è€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|à€ü€ÄÀ€è€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€È°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹…±Ý…åÍÉ¥Ñ¥…±!¥Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¥˜	}UAQ}5=Y}Q€øô9|à(€€€€€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}YM}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€•¹‘¥˜(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}i¥ÁÁåi…À°(€€€ô°((€€€m5=Y}MA1%M!e}MA1M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MA1%M!dMA1M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡Õ”•±•ÑÉ¥™¥•Ý…Ù”Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰µ…äÁ…É…±åé”Ñ¡”™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1eM%L°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ±¥Í¡åMÁ±…Í °(€€€ô°((€€€m5=Y}1=Qe}11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1=Qd10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±½…ÑÌ¥¸…¥È…¹‘¥Ù•Ì…Ñq¸ˆ(€€€€€€€€€€€€‰…¹±”¸5…ä…ÕÍ”™±¥¹¡¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹É…Ù¥Ñå	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€€€€€€¹Í¡••É½É•=Ù•ÉÉ¥‘”€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±½…Ñå…±°°(€€€ô°((€€€m5=Y}A%-}AA=]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A%-AA=\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰A¥­…¡ÔÌ±½Ù”¥¹É•…Í•Ì¥ÑÍq¸ˆ(€€€€€€€€€€€€‰Á½Ý•È¸%Ð¹•Ù•Èµ¥ÍÍ•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IQUI8°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A¥­…A…Á½Ü°(€€€ô°((€€€m5=Y}	=U9e}	U		1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	=U9d	U		1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…¬Ñ¡…Ð…‰Í½É‰Íq¸ˆ(€€€€€€€€¥˜	}UAQ}5=Y}Q€øô9|à(€€€€€€€€€€€€‰…±°Ñ¡”‘…µ…”¥¹™±¥Ñ•¸ˆ¤°(€€€€€€€€•±Í”(€€€€€€€€€€€€‰¡…±˜Ñ¡”‘…µ…”¥¹™±¥Ñ•¸ˆ¤°(€€€€€€€€•¹‘¥˜(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€ØÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|à€ü€ÈÀ€è€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô	}UAQ}5=Y}Q€øô9|à€ü€ÄÀÀ€è€ÔÀô°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ô	}!1}	1=-%9€øô9|Ø°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	½Õ¹å	Õ‰‰±”°(€€€ô°((€€€m5=Y}	Uiie}	Uiit€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	Uiid	Uihˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡½½ÑÌ„©½±Ð½˜•±•ÑÉ¥¥Ñåq¸ˆ(€€€€€€€€€€€€‰Ñ¡…Ð…±Ý…åÌÁ…É…±åé•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€ØÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|à€ü€ÈÀ€è€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1eM%L°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	Õééå	Õéè°(€€€ô°((€€€m5=Y}M%ii1e}M1%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M%ii1dM1%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÍ•È±½…­•¥¸™¥É”¡…É•Ì¹q¸ˆ(€€€€€€€€€€€€‰1•…Ù•ÌÑ¡”™½”Ý¥Ñ „‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€ØÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|à€ü€ÈÀ€è€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹Ñ¡…ÝÍUÍ•È€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¥éé±åM±¥‘”°(€€€ô°((€€€m5=Y}1%Qie}1=]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%Qid1=\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q•±•­¥¹•Ñ¥Œ™½É”Ñ¡…ÐÍ•ÑÍq¸ˆ(€€€€€€€€€€€€‰Ý…±°°±½Ý•É¥¹œMÀ¸Ñ¬‘…µ…”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€àÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô	}UAQ}5=Y}Q€øô9|à€ü€äÔ€è€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%!Q}MI8°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±¥Ñéå±½Ü°(€€€ô°((€€€m5=Y}	e}	t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	d	ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ñ¥¹œ‰…‘±ä°…ÑÑ…­Ì¸M•ÑÍq¸ˆ(€€€€€€€€€€€€‰Ý…±°°±½Ý•É¥¹œÑÑ…¬‘…µ…”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€àÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô	}UAQ}5=Y}Q€øô9|à€ü€äÔ€è€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I1P°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	…‘‘å	…°(€€€ô°((€€€m5=Y}MAAe}Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MAAdMˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¥…¹ÐÍÑ…±¬Í…ÑÑ•ÉÌÍ••‘Íq¸ˆ(€€€€€€€€€€€€‰Ñ¡…Ð‘É…¥¸!@•Ù•ÉäÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€ÄÀÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô	}UAQ}5=Y}Q€øô9|à€ü€äÀ€è€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|à€ü€ÄÀ€è€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1!}M°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M…ÁÁåM••°(€€€ô°((€€€m5=Y}Iie}I=MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IidI=MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÉåÍÑ…°™É½´½±¡…é”¡¥ÑÌ¹q¸ˆ(€€€€€€€€€€€€‰±¥µ¥¹…Ñ•Ì…±°ÍÑ…Ð¡…¹•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€ÄÀÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô	}UAQ}5=Y}Q€øô9|à€ü€äÀ€è€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|à€ü€ÄÀ€è€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}!i°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É••éåÉ½ÍÐ°(€€€ô°((€€€m5=Y}MAI-1e}M]%I1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MAI-1dM]%I0ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]É…À™½”Ý¥Ñ Ý¡¥É±Ý¥¹½™q¸ˆ(€€€€€€€€€€€€‰Í•¹Ð¸!•…±ÌÁ…ÉÑäÌÍÑ…ÑÕÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|à€ü€ÄÈÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô	}UAQ}5=Y}Q€øô9|à€ü€àÔ€è€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|à€ü€Ô€è€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I=5Q!IAd°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ…É­±åMÝ¥É°°(€€€ô°((€€€m5=Y}YY}Y=11et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰YYY=11dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰•Ù•”Ì±½Ù”¥¹É•…Í•Ì¥ÑÍq¸ˆ(€€€€€€€€€€€€‰Á½Ý•È¸%Ð¹•Ù•Èµ¥ÍÍ•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IQUI8°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Y••Ù••Y½±±•ä°(€€€ô°((€€€m5=Y}=U	1}%I=9}	M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=U	1%I=8	M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÍÁ¥¹Ì…¹¡¥ÑÌÝ¥Ñ¡q¸ˆ(€€€€€€€€€€€€‰¥ÑÌ…ÉµÌ¸5…ä…ÕÍ”™±¥¹ ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€È°(€€€€€€€€¹µ¥¹¥µ¥é•½Õ‰±•…µ…”€ô	}UAQ}5=Y}1L€ð9|à°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½Õ‰±•%É½¹	…Í °(€€€ô°((€€€m5=Y}e95a}99=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰e95`99=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰U¹±•…Í¡•Ì½É”•¹•Éä¹q¸ˆ(€€€€€€€€€€€€ˆÉà……¥¹ÍÐå¹…µ…á•™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}e95a}=U	1}5°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹•¹½É•	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹Á…É•¹Ñ…±	½¹‘	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}å¹…µ…á…¹¹½¸°(€€€ô°((€€€m5=Y}M9%A}M!=Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M9%AM!=Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È¥¹½É•Ì•™™•ÑÍq¸ˆ(€€€€€€€€€€€€‰Ñ¡…Ð‘É…Ü¥¸µ½Ù•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M9%A}M!=P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹É¥Ñ¥…±!¥ÑMÑ…”€ô	}UAQ}5=Y}Q€øô9|Ì€ü€Ä€è€È°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¹¥Á•M¡½Ð°(€€€ô°((€€€m5=Y})]}1=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰)\1=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÉ•Ù•¹ÑÌÑ¡”ÕÍ•È…¹‘q¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð™É½´•Í…Á¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰¥Ñ¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}QIA}	=Q °(€€€€€€€ô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€Ô°ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•})…Ý1½¬°(€€€ô°((€€€m5=Y}MQU}!-Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQU!-Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½¹ÍÕµ•ÌÑ¡”ÕÍ•ÈÌ	•ÉÉä±q¸ˆ(€€€€€€€€€€€€‰Ñ¡•¸Í¡…ÉÁ±äÉ…¥Í•Ì•˜¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQU}!-L°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑÕ™™¡••­Ì°(€€€ô°((€€€m5=Y}9=}IQIQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9<IQIPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I…¥Í•Ì…±°½˜Ñ¡”ÕÍ•ÈÍq¸ˆ(€€€€€€€€€€€€‰ÍÑ…ÑÌ‰ÕÐÁÉ•Ù•¹ÑÌ•Í…Á”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}9=}IQIP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}9½I•ÑÉ•…Ð°(€€€ô°((€€€m5=Y}QI}M!=Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QHM!=Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”™½”ÌMÁ••…¹‘q¸ˆ(€€€€€€€€€€€€‰µ…­•Ì¥ÐÝ•…¬Ñ¼¥É”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QI}M!=P°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q…ÉM¡½Ð°(€€€ô°((€€€m5=Y}5%}A=]It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5%A=]Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…¥ŒÁ½Ý‘•È¡…¹•ÌÑ¡•q¸ˆ(€€€€€€€€€€€€‰Ñ…É•Ð¥¹Ñ¼„AÍå¡¥ŒÑåÁ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M=,°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÑåÁ”€ôQeA}AMe!%ô°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹Á½Ý‘•É5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9}]%Q!})UM}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…¥A½Ý‘•È°(€€€ô°((€€€m5=Y}I=9}IQMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=8IQLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È…ÑÑ…­ÌÑÝ¥”¸QÝ½q¸ˆ(€€€€€€€€€€€€‰Ñ…É•ÑÌ…É”¡¥Ð½¹”•… ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M5IP°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€È°(€€€€€€€€¹Á…É•¹Ñ…±	½¹‘	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…½¹…ÉÑÌ°(€€€ô°((€€€m5=Y}QQ%5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QQ%5ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±°A½¯¥µ½¸¡…Ù”Ñ•…Ñ¥µ•q¸ˆ(€€€€€€€€€€€€‰…¹•…ÐÑ¡•¥È	•ÉÉ¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QQ%5°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}11}	QQ1IL°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}5-}=11=]%9}5=9M}9IY=UL°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q•…Ñ¥µ”°(€€€ô°((€€€m5=Y}=Q=1=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=Q=1=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰QÉ…ÁÌÑ¡”™½”Ñ¼±½Ý•È•™q¸ˆ(€€€€€€€€€€€€‰…¹MÀ¸•˜•… ÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=Q=1=,°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}=Ñ½±½¬°(€€€ô°((€€€m5=Y}	=1Q}	-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	=1P	,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½Õ‰±”Á½Ý•È¥˜Ñ¡”ÕÍ•Éq¸ˆ(€€€€€€€€€€€€‰µ½Ù•Ì‰•™½É”Ñ¡”Ñ…É•Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	=1Q}	,°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	½±Ñ	•…¬°(€€€ô°((€€€m5=Y}%M!%=UM}I9t€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€Ô°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%M!%=ULI9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½Õ‰±”Á½Ý•È¥˜Ñ¡”ÕÍ•Éq¸ˆ(€€€€€€€€€€€€‰µ½Ù•Ì‰•™½É”Ñ¡”Ñ…É•Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	=1Q}	,°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰¥Ñ¥¹5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥Í¡¥½ÕÍI•¹°(€€€ô°((€€€m5=Y}=UIQ}!9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=UIP!9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÍÝ…ÁÌ•™™•ÑÌ½¹q¸ˆ(€€€€€€€€€€€€‰•¥Ñ¡•ÈÍ¥‘”½˜Ñ¡”™¥•±¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=UIQ}!9°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}5-}=11=]%9}5=9M}9IY=UL°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½ÕÉÑ¡…¹”°(€€€ô°((€€€m5=Y}19=I=UM}M=U1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰19=I=ULM=U0ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÕÍ•ÌÍ½µ”½˜¥ÑÍq¸ˆ(€€€€€€€€€€€€‰!@Ñ¼É…¥Í”…±°¥ÑÌÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}19=I=UM}M=U0°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹‘…¹•5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…¹½É½ÕÍM½Õ°°(€€€ô°((€€€m5=Y}	=e}AIMMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	=dAIMLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½•Ìµ½É”‘…µ…”Ñ¡•q¸ˆ(€€€€€€€€€€€€‰¡¥¡•ÈÑ¡”ÕÍ•ÈÌ•˜¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	=e}AIML°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}M5}QeA°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	½‘åAÉ•ÍÌ°(€€€ô°((€€€m5=Y}=IQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=IQˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÍ¡…ÉÁ±äÉ…¥Í•Íq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•ÐÌÑ¬…¹MÀ¹Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=IQ°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•½É…Ñ”°(€€€ô°((€€€m5=Y}IU5}	Q%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IU4	Q%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰A±…åÌ„‘ÉÕ´Ñ¼…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰Q¡”™½”ÌMÁ••¥Ì±½Ý•É•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÉÕµ	•…Ñ¥¹œ°(€€€ô°((€€€m5=Y}M9A}QIAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M9@QI@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¹…É•ÌÑ¡”Ñ…É•Ð¥¸„Í¹…Áq¸ˆ(€€€€€€€€€€€€‰ÑÉ…À™½È™½ÕÈÑ¼™¥Ù”ÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÌÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}]I@°(€€€€€€€€€€€€¹µÕ±Ñ¥ÍÑÉ¥¹œ¹ÝÉ…ÁÁ•€ô	}5M}]IAA}M9A}QI@°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¹…ÁQÉ…À°(€€€ô°((€€€m5=Y}AeI=}	11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AeI<	10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1…Õ¹¡•Ì„™¥•Éä‰…±°…ÐÑ¡•q¸ˆ(€€€€€€€€€€€€‰Ñ…É•Ð¸%Ðµ…ä…ÕÍ”„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹Ñ¡…ÝÍUÍ•È€ôQIU°(€€€€€€€€¹‰…±±¥ÍÑ¥5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AåÉ½	…±°°(€€€ô°((€€€m5=Y}	!5=Q!}	1t€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	!5=Q 	1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑÉ¥­•Ì…Ì„ÍÝ½É¸•…±Ì€Éáq¸ˆ(€€€€€€€€€€€€‰‘…µ…”Ñ¼å¹…µ…á•™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}e95a}=U	1}5°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	•¡•µ½Ñ¡	±…‘”°(€€€ô°((€€€m5=Y}	!5=Q!}	M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	!5=Q 	M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­Ì…Ì„Í¡¥•±¸•…±Ì€Éáq¸ˆ(€€€€€€€€€€€€‰‘…µ…”Ñ¼å¹…µ…á•™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}e95a}=U	1}5°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	•¡•µ½Ñ¡	…Í °(€€€ô°((€€€m5=Y}UI}]!1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰UI]!0ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I…¥Í•ÌMÁ••Ñ¼…ÑÑ…¬¸Q¡•q¸ˆ(€€€€€€€€€€€€‰QåÁ”¥Ì‰…Í•½¸¥ÑÌ™½É´¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}UI}]!0°(€€€€€€€€¹Á½Ý•È€ô€ÄÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÕÉ…]¡••°°(€€€ô°((€€€m5=Y}	I-%9}M]%At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	I-%9M]%Aˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÝ¥¹Ì¥ÑÌÑ…¥°Ñ¼…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”Ñ¬½˜Ñ¡½Í”¡¥Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	É•…­¥¹MÝ¥Á”°(€€€ô°((€€€m5=Y}	I9!}A=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	I9 A=-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÁ½­•ÌÑ¡”Ñ…É•Ñq¸ˆ(€€€€€€€€€€€€‰Ý¥Ñ „Á½¥¹Ñ•‰É…¹ ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÐÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	É…¹¡A½­”°(€€€ô°((€€€m5=Y}=YII%Yt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=YII%Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÑÝ…¹Ì¥ÑÌÕ¥Ñ…È±q¸ˆ(€€€€€€€€€€€€‰…ÕÍ¥¹œÍÑÉ½¹œÙ¥‰É…Ñ¥½¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}=Ù•É‘É¥Ù”°(€€€ô°((€€€m5=Y}AA1}%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AA1%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ Ñ…ÉÐ…ÁÁ±”…¥‘q¸ˆ(€€€€€€€€€€€€‰Ñ¼±½Ý•ÈÑ¡”™½”ÌMÀ¸•˜¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÁÁ±•¥°(€€€ô°((€€€m5=Y}IY}AA1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IXAA1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É½ÁÌ…¸…ÁÁ±”™É½´…‰½Ù”¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”™½”Ì•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IY}AA1°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…ÙÁÁ±”°(€€€ô°((€€€m5=Y}MA%I%Q}	I-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MA%I%P	I,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ ÍÁ¥É¥Ðµ‰É•…­¥¹q¸ˆ(€€€€€€€€€€€€‰™½É”¸1½Ý•ÉÌMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ¥É¥Ñ	É•…¬°(€€€ô°((€€€m5=Y}MQI9}MQ5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQI9MQ4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µ¥ÑÌ„ÍÑÉ…¹”ÍÑ•…´Ñ½q¸ˆ(€€€€€€€€€€€€‰Á½Ñ•¹Ñ¥…±±ä½¹™ÕÍ”Ñ¡”™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=9UM%=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}I=9Q}5=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑÉ…¹•MÑ•…´°(€€€ô°((€€€m5=Y}1%}]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M…ÑÑ•ÉÌÝ…Ñ•ÈÑ¼É•ÍÑ½É•q¸ˆ(€€€€€€€€€€€€‰Ñ¡”!@½˜¥ÑÍ•±˜…¹…±±¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}1%}\°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}EU1%Qe}A9M}=9}Q%5%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1¥™••Ü°(€€€ô°((€€€m5=Y}=	MQIUQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=	MQIUPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÉ½Ñ•ÑÌ¥ÑÍ•±˜°¡…ÉÍ¡±åq¸ˆ(€€€€€€€€€€€€‰±½Ý•É¥¹œ•˜½¸½¹Ñ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ð°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}=	MQIUPô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}=‰ÍÑÉÕÐ°(€€€ô°((€€€m5=Y}1M}MUII9It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1MMUII9Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	½ÝÌÑ¼ÍÑ…ˆÑ¡”™½•q¸ˆ(€€€€€€€€€€€€‰Ý¥Ñ ¡…¥È¸%Ð¹•Ù•Èµ¥ÍÍ•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}…±Í•MÕÉÉ•¹‘•È°(€€€ô°((€€€m5=Y}5Q=I}MMU1Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5Q=HMMU1Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ „Ñ¡¥¬±••¬¹q¸ˆ(€€€€€€€€€€€€‰Q¡”ÕÍ•ÈµÕÍÐÑ¡•¸É•ÍÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I!I°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q})5M}=Q!IM}	UQ}5%MM}=9}QUI8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5•Ñ•½ÉÍÍ…Õ±Ð°(€€€ô°((€€€m5=Y}QI9	5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QI9	4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ñ•É¹…ÑÕÌœÍÑÉ½¹•ÍÐµ½Ù”¹q¸ˆ(€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÉ•ÍÑÌ¹•áÐÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I!I°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q})5M}=Q!IM}	UQ}5%MM}=9}QUI8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Ñ•É¹…‰•…´°(€€€ô°((€€€m5=Y}MQ1}	5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ0	4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¥É•Ì„‰•…´½˜ÍÑ••°™É½µq¸ˆ(€€€€€€€€€€€€‰¥ÑÌ‰½‘ä¸%Ð¡ÕÉÑÌÑ¡”ÕÍ•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}!A|ÔÁ}I=%0°(€€€€€€€€¹Á½Ý•È€ô€ÄÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ••±	•…´°(€€€ô°((€€€m5=Y}aA9%9}=It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰aA9%9=Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰A½Ý•È½•ÌÕÀ…¹‘…µ…•Íq¸ˆ(€€€€€€€€€€€€‰…±°™½•Ì½¸AÍå¡¥ŒQ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QII%9}	==MP°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð¹Ñ•ÉÉ…¥¹	½½ÍÐ€ôì(€€€€€€€€€€€€¹Ñ•ÉÉ…¥¸€ôMQQUM}%1}AMe!%}QII%8°(€€€€€€€€€€€€¹Á•É•¹Ð€ô€ÔÀ°(€€€€€€€€€€€€¹É½Õ¹‘¡•¬€ôI=U9}!-}UMH°(€€€€€€€€€€€€¹¡¥ÑÍ	½Ñ¡½•Ì€ôQIU°(€€€€€€€ô°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}AMe!%}QII%9ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}áÁ…¹‘¥¹½É”°(€€€ô°((€€€m5=Y}MQ1}I=11It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ0I=11Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰•ÍÑÉ½åÌÑ•ÉÉ…¥¸¸…¥±Ì¥™q¸ˆ(€€€€€€€€€€€€‰É½Õ¹¥Í¸ÐÑ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQ1}I=11H°(€€€€€€€€¹Á½Ý•È€ô€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ••±I½±±•È°(€€€ô°((€€€m5=Y}M1}M!=Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M1M!=Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡½½ÑÌÍ…±•Ì€ÈÑ¼€ÔÑ¥µ•Ì¹q¸ˆ(€€€€€€€€€€€€‰UÁÌMÁ••°±½Ý•ÉÌ‘•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µÕ±Ñ¥!¥Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}I1%H°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}M1}M!=P°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M…±•M¡½Ð°(€€€ô°((€€€m5=Y}5Q=I}	5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5Q=H	4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰€ÈµÑÕÉ¸µ½Ù”Ñ¡…ÐÉ…¥Í•Íq¸ˆ(€€€€€€€€€€€€‰MÀ¸ÑÑ…¬‰•™½É”…ÑÑ…­¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q]=}QUI9M}QQ,°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð¹ÑÝ½QÕÉ¹ÑÑ…¬€ôì€¹ÍÑÉ¥¹%€ôMQI%9%}5Q=I	5!I%9ô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹½¹¡…É•QÕÉ¹=¹±ä€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5•Ñ•½É	•…´°(€€€ô°((€€€m5=Y}M!11}M%}I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!10M%I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰•…±Ì‰•ÑÑ•È½˜Á¡åÍ¥…°…¹‘q¸ˆ(€€€€€€€€€€€€‰ÍÁ•¥…°‘…µ…”¸5…äÁ½¥Í½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M!11}M%}I4°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}A=%M=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}M5}QeA°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡•±±M¥‘•É´°(€€€ô°((€€€m5=Y}5%MQe}aA1=M%=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5%MQdaA1=M%=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥Ð•Ù•ÉåÑ¡¥¹œ…¹™…¥¹Ð¹q¸ˆ(€€€€€€€€€€€€‰A½Ý•ÉÌÕÀ½¸5¥ÍÑäQ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QII%9}	==MP°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹•áÁ±½Í¥½¸€ôQIU°(€€€€€€€€¹‘…µÁ	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð¹Ñ•ÉÉ…¥¹	½½ÍÐ€ôì(€€€€€€€€€€€€¹Ñ•ÉÉ…¥¸€ô€MQQUM}%1}5%MQe}QII%8°(€€€€€€€€€€€€¹Á•É•¹Ð€ô€ÔÀ°(€€€€€€€€€€€€¹É½Õ¹‘¡•¬€ôI=U9}!-}UMH°(€€€€€€€ô°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IQ}AA1}	UQ}9=}5=I}5=YL°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}5%MQe}QII%9ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5¥ÍÑåáÁ±½Í¥½¸°(€€€ô°((€€€m5=Y}IMMe}1%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IMMd1%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±¥‘¥¹œ½¸É½Õ¹°¡¥ÑÌ¸½•Íq¸ˆ(€€€€€€€€€€€€‰™¥ÉÍÐ½¸É…ÍÍäQ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IMMe}1%°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÔÔ€è€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}I1%H°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}IMMe}QII%9ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…ÍÍå±¥‘”°(€€€ô°((€€€m5=Y}I%M%9}Y=1Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%M%9Y=1Qˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡¥Ìµ½Ù”ÌÁ½Ý•È‘½Õ‰±•Íq¸ˆ(€€€€€€€€€€€€‰Ý¡•¸½¸±•ÑÉ¥ŒQ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QII%9}	==MP°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð¹Ñ•ÉÉ…¥¹	½½ÍÐ€ôì(€€€€€€€€€€€€¹Ñ•ÉÉ…¥¸€ôMQQUM}%1}1QI%}QII%8°(€€€€€€€€€€€€¹Á•É•¹Ð€ô€ÄÀÀ°(€€€€€€€€€€€€¹É½Õ¹‘¡•¬€ôI=U9}!-}QIP°(€€€€€€€ô°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}1QI%}QII%9ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I¥Í¥¹Y½±Ñ…”°(€€€ô°((€€€m5=Y}QII%9}AU1Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QII%8AU1Mˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰QåÁ”…¹Á½Ý•È¡…¹•Íq¸ˆ(€€€€€€€€€€€€‰‘•Á•¹‘¥¹œ½¸Ñ¡”Ñ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QII%9}AU1M°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹ÁÕ±Í•5½Ù”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô}UAQ}5=Y}QL€øô9|Ø€ü=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9€è=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôí=5	=}MQIQI}1QI%}QII%8°=5	=}MQIQI}5%MQe}QII%8°=5	=}MQIQI}IMMe}QII%8°=5	=}MQIQI}AMe!%}QII%9ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q•ÉÉ…¥¹AÕ±Í”°(€€€ô°((€€€m5=Y}M-%QQI}M5-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M-%QQHM5,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÍ•ÈÍ­¥ÑÑ•ÉÌ‰•¡¥¹™½”Ñ½q¸ˆ(€€€€€€€€€€€€‰…ÑÑ…¬¸1½Ý•ÉÌ™½”ÌMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M­¥ÑÑ•ÉMµ…¬°(€€€ô°((€€€m5=Y}	UI9%9})1=UMet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	UI9%9)1=UMdˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½•ÌÑ¡…Ð¡…Ù”ÍÑ…ÑÌÕÁÁ•‘q¸ˆ(€€€€€€€€€€€€‰‘ÕÉ¥¹œÑ¡”ÑÕÉ¸•Ð‰ÕÉ¹•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹½¹±å%™Q…É•ÑI…¥Í•‘MÑ…ÑÌ€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9}]%Q!})UM}QQ9Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	ÕÉ¹¥¹)•…±½ÕÍä°(€€€ô°((€€€m5=Y}1M!}=UQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1M =UPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%˜ÕÍ•ÈÌÍÑ…ÑÌÝ•É”±½Ý•É•‘q¸ˆ(€€€€€€€€€€€€‰Ñ¡¥ÌÑÕÉ¸°Á½Ý•È¥Ì‘½Õ‰±•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}1M!}=UP°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}AIY}5=8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1…Í¡=ÕÐ°(€€€ô°((€€€m5=Y}A=1QI%MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=1QI%MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½¹ÑÉ½°™½”Ì¥Ñ•´Ñ¼…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰…¥±Ì¥˜™½”¡…Ì¹¼¥Ñ•´¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A=1QI%MP°(€€€€€€€€¹Á½Ý•È€ô€ÄÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½±Ñ•É•¥ÍÐ°(€€€ô°((€€€m5=Y}=II=M%Y}Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=II=M%YLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥¡±ä…¥‘¥Œ…Ìµ•±ÑÌ¥Ñ•µÍq¸ˆ(€€€€€€€€€€€€‰¡•±‰äÍÕÉÉ½Õ¹‘¥¹œA½¯¥µ½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=II=M%Y}L°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÐÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}]=IM9}=9%Q%=9}=}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½ÉÉ½Í¥Ù•…Ì°(€€€ô°((€€€m5=Y}=!%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=!%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÉ½Á•É±ä½…¡•Ì…±±¥•ÌÑ½q¸ˆ(€€€€€€€€€€€€‰ÕÀÑ¡•¥ÈÑÑ…¬…¹•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=!%9°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½…¡¥¹œ°(€€€ô°((€€€m5=Y}1%A}QUI9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%@QUI8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­Ì…¹ÉÕÍ¡•Ì‰…¬Ñ½q¸ˆ(€€€€€€€€€€€€‰ÍÝ¥Ñ Ý¥Ñ „Á…ÉÑäA½¯¥µ½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%Q}MA°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}Y=%}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±¥ÁQÕÉ¸°(€€€ô°((€€€m5=Y}QI%A1}a1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QI%A1a0ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰€Ìµ­¥¬…ÑÑ…¬Ñ¡…Ð•ÑÍq¸ˆ(€€€€€€€€€€€€‰µ½É”Á½Ý•É™Õ°Ý¥Ñ •… ¡¥Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QI%A1}-%,°(€€€€€€€€¹Á½Ý•È€ô€ÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€Ì°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}M5}QeA°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}QÉ¥Á±•á•°°(€€€ô°((€€€m5=Y}U1}]%9	Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰U0]%9	Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÍ•ÈÍ±…µÌÑ¡”Ñ…É•ÐÝ¥Ñ¡q¸ˆ(€€€€€€€€€€€€‰Ý¥¹Ì…¹¡¥ÑÌÑÝ¥”¥¸„É½Ü¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€È°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}IAQ%Q%=9}9=Q}	=I%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Õ…±]¥¹‰•…Ð°(€€€ô°((€€€m5=Y}M=I!%9}M9Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M=I!%9M9Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡É½ÝÌÍ½É¡¥¹œÍ…¹…Ñq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸5…ä±•…Ù”„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ñ¡…ÝÍUÍ•È€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M½É¡¥¹M…¹‘Ì°(€€€ô°((€€€m5=Y})U91}!1%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰)U91!1%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!•…±Ì!@…¹ÍÑ…ÑÕÌ½™q¸ˆ(€€€€€€€€€€€€‰¥ÑÍ•±˜…¹…±±¥•Ì¥¸‰…ÑÑ±”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ})U91}!1%9°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}EU1%Qe}A9M}=9}Q%5%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•})Õ¹±•!•…±¥¹œ°(€€€ô°((€€€m5=Y}]%-}	1=]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]%-	1=\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…ÍÑ•É¥¹œÑ¡”…É¬ÍÑå±”±q¸ˆ(€€€€€€€€€€€€‰ÍÑÉ¥­•ÌÝ¥Ñ „É¥Ñ¥…°¡¥Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÜÔ€è€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…±Ý…åÍÉ¥Ñ¥…±!¥Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q})5M}=Q!IM}	UQ}5%MM}=9}QUI8°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]¥­•‘	±½Ü°(€€€ô°((€€€m5=Y}MUI%9}MQI%-Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MUI%9MQI%-Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…ÍÑ•É¥¹œÑ¡”]…Ñ•ÈÍÑå±”±q¸ˆ(€€€€€€€€€€€€‰ÍÑÉ¥­•ÌÝ¥Ñ €ÌÉ¥Ñ¥…°¡¥ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…±Ý…åÍÉ¥Ñ¥…±!¥Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€Ì°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}MQIQ1}5=9M}M5}QeA}AA0°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÕÉ¥¹MÑÉ¥­•Ì°(€€€ô°((€€€m5=Y}Q!U9I}t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q!U9Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰QÉ…ÁÌÑ¡”™½”¥¸„…”½™q¸ˆ(€€€€€€€€€€€€‰•±•ÑÉ¥¥Ñä™½È€‰	%9%9}QUI9LˆÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}]I@°(€€€€€€€€€€€€¹µÕ±Ñ¥ÍÑÉ¥¹œ¹ÝÉ…ÁÁ•€ô	}5M}]IAA}Q!U9I}°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}=9Q}a%Q}U%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q¡Õ¹‘•É…”°(€€€ô°((€€€m5=Y}I=9}9Iet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=89Idˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”¡¥¡•ÈÑ¡”ÕÍ•ÈÌ!Aq¸ˆ(€€€€€€€€€€€€‰Ñ¡”µ½É”‘…µ…”…ÕÍ•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A=]I}	M}=9}UMI}!@°(€€€€€€€€¹Á½Ý•È€ô€ÄÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô}UAQ}5=Y}QL€øô9|Ø€ü=9QMQ}Q}UMI}5=I}M%1e}MQIQ1€è=9QMQ}Q}	QQI}]!9}1QH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}==0°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…½¹¹•Éä°(€€€ô°((€€€m5=Y}Ii%9}1It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Ii%91Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡½½ÑÌÁÍå¡¥ŒÁ½Ý•È™É½µq¸ˆ(€€€€€€€€¥˜	}UM}I=MQ	%Q€ôôQIU(€€€€€€€€€€€€‰Ñ¡”•å•Ì¸5…ä™É½ÍÑ‰¥Ñ”¸ˆ¤°(€€€€€€€€•±Í”(€€€€€€€€€€€€‰Ñ¡”•å•Ì¸5…ä™É••é”Ñ¡”™½”¸ˆ¤°(€€€€€€€€•¹‘¥˜(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Ii}=I}I=MQ	%Q°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}UQ°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É••é¥¹±…É”°(€€€ô°((€€€m5=Y}%Ie}]IQ!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%Id]IQ ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…¬™Õ•±•‰äå½ÕÉq¸ˆ(€€€€€€€€€€€€‰ÝÉ…Ñ ¸5…ä…ÕÍ”™±¥¹¡¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥•Éå]É…Ñ °(€€€ô°((€€€m5=Y}Q!U9I=UM}-%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q!U9I=UL-%,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÍ•Ì„±¥¡Ñ¹¥¹œµ±¥­”­¥­q¸ˆ(€€€€€€€€€€€€‰Ñ¼¡¥Ð¸1½Ý•ÉÌ™½”Ì•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}!%!1e}AA1%9°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}Q=U °(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q¡Õ¹‘•É½ÕÍ-¥¬°(€€€ô°((€€€m5=Y}1%1}19t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%019ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!ÕÉ±Ì„‰±¥éé…Éµ±½…­•‘q¸ˆ(€€€€€€€€€€€€‰¥¥±”±…¹”…Ð™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÈÀ€è€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…¥…±1…¹”°(€€€ô°((€€€m5=Y}MQI1}	IIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQI0	IIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M•¹‘Ì„™É¥¡Ñ™Õ°…µ½Õ¹Ñq¸ˆ(€€€€€€€€€€€€‰½˜Íµ…±°¡½ÍÑÌ…Ð™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÍÑÉ…±	…ÉÉ…”°(€€€ô°((€€€m5=Y}I%}MA11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%MA10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…­ÌÝ¥Ñ ÁÍå¡¥ŒÁ½Ý•È¹q¸ˆ(€€€€€€€€€€€€‰½”Ì±…ÍÐµ½Ù”¡…Ì€ÌA@ÕÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]!9}1QH°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}M5IP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I%}MA10°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•É¥•MÁ•±°°(€€€ô°((€€€m5=Y}%I}1]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%I1\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ É¥Ñ¥…°¡¥Ð¡…¹”¸5…åq¸ˆ(€€€€€€€€€€€€‰Á…É…±åé”°Á½¥Í½¸½È‘É½ÝÍ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€àÀ€è€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%I}1\°(€€€€€€€€€€€€¹¡…¹”€ô€ÔÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥É•±…Ü°(€€€ô°((€€€m5=Y}AMeM!%1}	M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AMeM!%1	M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌ„™½”Ý¥Ñ ÁÍå¡¥q¸ˆ(€€€€€€€€€€€€‰•¹•Éä¸5…äÉ…¥Í”•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍåÍ¡¥•±‘	…Í °(€€€ô°((€€€m5=Y}A=]I}M!%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=]HM!%Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÍÝ…ÁÌ¥ÑÌÑÑ…­q¸ˆ(€€€€€€€€€€€€‰…¹•™•¹Í”ÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A=]I}QI%,°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½Ý•ÉM¡¥™Ð°)ô°((€€€m5=Y}MQ=9}at€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ=9aˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M•ÑÌÍ¡…ÉÀÉ½­ÌÑ¡…Ð¡ÕÉÑq¸ˆ(€€€€€€€€€€€€‰Ñ¡”™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQ=9}a°(€€€€€€€€¹Á½Ý•È€ô€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹Í¡••É½É•=Ù•ÉÉ¥‘”€ôQIU°(€€€€€€€ô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€Ô°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ½¹•á”°(€€€ô°((€€€m5=Y}MAI%9Q%}MQ=I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MAI%9Q%MQ=I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]É…ÁÌ„™½”¥¸™¥•É”Ý¥¹‘Ì¹q¸ˆ(€€€€€€€€€€€€‰Y…É¥•ÌÝ¥Ñ Ñ¡”ÕÍ•ÈÌ™½É´¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀÀ€è€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€àÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ý¥¹‘5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁÉ¥¹Ñ¥‘•MÑ½É´°(€€€ô°((€€€m5=Y}5eMQ%1}A=]It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5eMQ%0A=]Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µåÍÑ•É¥½ÕÌÁ½Ý•ÈÍÑÉ¥­•Ì±q¸ˆ(€€€€€€€€€€€€‰É…¥Í¥¹œÑ¡”ÕÍ•ÈÌMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5åÍÑ¥…±A½Ý•È°(€€€ô°((€€€m5=Y}I%9}UIet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%9UIdˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É…µÁ…”½˜€ÈÑ¼€ÌÑÕÉ¹Íq¸ˆ(€€€€€€€€€€€€‰Ñ¡…Ð½¹™ÕÍ•ÌÑ¡”ÕÍ•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÈÀ€è€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}I9=4°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q!IM °(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô}UAQ}5=Y}QL€øô9|Ø€ü=9QMQ}Q}UMI}5=I}M%1e}MQIQ1€è=9QMQ}Q})5M}=Q!IM}	UQ}5%MM}=9}QUI8°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I…¥¹ÕÉä°(€€€ô°((€€€m5=Y}]Y}IM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]YIM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Í±…´Í¡É½Õ‘•¥¸Ý…Ñ•È¹q¸ˆ(€€€€€€€€€€€€‰%Ð…±Í¼¡ÕÉÑÌÑ¡”ÕÍ•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=%0°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÈÀ€è€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹É•½¥±A•É•¹Ñ…”€ô€ÌÌô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]…Ù•É…Í °(€€€ô°((€€€m5=Y}!1=I=	1MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!1=I=	1MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÕÍ•Èµ¡ÕÉÑ¥¹œ‰±…ÍÐ½™q¸ˆ(€€€€€€€€€€€€‰…µ…ÍÍ•¡±½É½Á¡å±°¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!1=I=	1MP°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÔÀ€è€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¡±½É½‰±…ÍÐ°(€€€ô°((€€€m5=Y}5=U9Q%9}1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5=U9Q%81ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¥…¹Ð¡Õ¹­Ì½˜¥”‘…µ…•q¸ˆ(€€€€€€€€€€€€‰Ñ¡”™½”¸%Ðµ…ä™±¥¹ ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀ€è€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5½Õ¹Ñ…¥¹…±”°(€€€ô°((€€€m5=Y}Y%Q=Ie}9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Y%Q=Id9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…¹•ÌÑ¼É…¥Í”ÑÑ…¬±q¸ˆ(€€€€€€€€€€€€‰•™•¹Í”…¹MÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Y%Q=Ie}9°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹‘…¹•5½Ù”€ôQIU°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}%5AI=Y}=9%Q%=9}AIY9Q}9IY=UM9ML°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Y¥Ñ½Éå…¹”°(€€€ô°((€€€m5=Y}!1=9}IUM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!1=9IUM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÝ¥Ñ „™Õ±°µ‰½‘äÑ…­±”¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”ÕÍ•ÉÌÌ‘•™•¹Í•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÈÀ€è€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}MA}=]8°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!•…‘±½¹IÕÍ °(€€€ô°((€€€m5=Y}	I	}	IIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	I	IIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…¸Á½¥Í½¸½¸¥µÁ…Ð¸A½Ý•ÉÍq¸ˆ(€€€€€€€€€€€€‰ÕÀ……¥¹ÍÐÁ½¥Í½¹•™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=U	1}A=]I}=9}I}MQQUL°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀ€è€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÍÑ…ÑÕÌ€ôMQQULÅ}AM9}9dô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}A=%M=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÔÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	…É‰	…ÉÉ…”°(€€€ô°((€€€m5=Y}MAI}]%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MAH]%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ É¥Ñ¥…°¡¥ÐÉ…Ñ¥¼¹q¸ˆ(€€€€€€€€€€€€‰UÁÌÑ¡”ÕÍ•ÈÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€àÀ€è€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀÀ€è€äÀ°(€€€€€€€€¹É¥Ñ¥…±!¥ÑMÑ…”€ô	}UAQ}5=Y}Q€øô9|Ì€ü€Ä€è€È°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÍÁ•É]¥¹œ°(€€€ô°((€€€m5=Y}	%QQI}51%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	%QQH51%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÍÁ¥¹”µ¡¥±±¥¹œÉ•Í•¹Ñµ•¹Ð¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”™½”ÌÑÑ…¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÜÔ€è€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	¥ÑÑ•É5…±¥”°(€€€ô°((€€€m5=Y}M!1QIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!1QHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È¡…É‘•¹ÌÑ¡•¥ÈÍ­¥¸±q¸ˆ(€€€€€€€€€€€€‰Í¡…ÉÁ±äÉ…¥Í¥¹œ¥ÑÌ•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}9M}UA|È°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡•±Ñ•È°(€€€ô°((€€€m5=Y}QI%A1}II=]Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QI%A1II=]Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ É¥Ñ¥…°¡¥ÐÉ…Ñ¥¼¹q¸ˆ(€€€€€€€€€€€€‰5…ä±½Ý•È•™•¹Í”½È™±¥¹ ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€äÀ€è€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀ€è€ÄÔ°(€€€€€€€€¹É¥Ñ¥…±!¥ÑMÑ…”€ô	}UAQ}5=Y}Q€øô9|Ì€ü€Ä€è€È°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÔÀ°(€€€€€€€ô°(€€€€€€€ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}QÉ¥Á±•ÉÉ½ÝÌ°(€€€ô°((€€€m5=Y}%9I91}AIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%9I90AIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!ÕÉÑÌ„™½”¡…É‘•È¥˜¥Ð¡…Íq¸ˆ(€€€€€€€€€€€€‰…¸…¥±µ•¹Ð¸5…ä±•…Ù”„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=U	1}A=]I}=9}I}MQQUL°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÍÑ…ÑÕÌ€ôMQQULÅ}9dô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%¹™•É¹…±A…É…‘”°(€€€ô°((€€€m5=Y}M1MM}t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M1MLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M•ÑÌMÁ¥­•ÌÑ¡…Ð¡ÕÉÐÑ¡•q¸ˆ(€€€€€€€€€€€€‰™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M1MM}°(€€€€€€€€¹Á½Ý•È€ô€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹Í¡••É½É•=Ù•ÉÉ¥‘”€ôQIU°(€€€€€€€ô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€Ô°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•…Í•±•ÍÍ‘”°(€€€ô°((€€€m5=Y}	1-]%9}MQ=I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	1-]%9MQ=I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÝ¥Ñ ‰ÉÕÑ…°°½±Ý¥¹‘Ì¹q¸ˆ(€€€€€€€€€€€€‰5…ä±½Ý•ÈÑ¡”™½”ÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀÀ€è€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€àÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀ€è€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ý¥¹‘5½Ù”€ôQIU°(€€€€€€€€¹…±Ý…åÍ!¥ÑÍ%¹I…¥¸€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	±•…­Ý¥¹‘MÑ½É´°(€€€ô°((€€€m5=Y}]%1	=1Q}MQ=I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]%1	=1PMQ=I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÝ¥Ñ „‰ÉÕÑ…°Ñ•µÁ•ÍÐ¹q¸ˆ(€€€€€€€€€€€€‰5…ä¥¹™±¥ÐÁ…É…±åÍ¥Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀÀ€è€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€àÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀ€è€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ý¥¹‘5½Ù”€ôQIU°(€€€€€€€€¹…±Ý…åÍ!¥ÑÍ%¹I…¥¸€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1eM%L°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]¥±‘‰½±ÑMÑ½É´°(€€€ô°((€€€m5=Y}M9MI}MQ=I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M9MHMQ=I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÝ¥Ñ ‰ÉÕÑ…±±ä¡½ÐÍ…¹¹q¸ˆ(€€€€€€€€€€€€‰5…ä¥¹™±¥Ð„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀÀ€è€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€àÀ°(€€€€€€€€¹ÁÀ€ô	}UAQ}5=Y}Q€øô9|ä€ü€ÄÀ€è€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ý¥¹‘5½Ù”€ôQIU°(€€€€€€€€¹…±Ý…åÍ!¥ÑÍ%¹I…¥¸€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M…¹‘Í•…ÉMÑ½É´°(€€€ô°((€€€m5=Y}1U9I}	1MM%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1U9H	1MM%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È¡•…±Ì…¹ÕÉ•Íq¸ˆ(€€€€€€€€€€€€‰¥ÑÍ•±˜…¹¥ÑÌ…±±ä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ})U91}!1%9°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1Õ¹…É	±•ÍÍ¥¹œ°(€€€ô°((€€€m5=Y}Q-}!IQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q-!IPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È±¥™ÑÌ¥ÑÌÍÁ¥É¥ÑÌÑ½q¸ˆ(€€€€€€€€€€€€‰¡•…°…¹ÍÑÉ•¹Ñ¡•¸¥ÑÍ•±˜¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q-}!IP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q…­•!•…ÉÐ°(€€€ô°((€€€m5=Y}QI}	1MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QI	1MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%˜Ñ¡”ÕÍ•ÈÌQ•É…ÍÑ…±±¥é•±q¸ˆ(€€€€€€€€€€€€‰¥Ð¡¥ÑÌÝ¥Ñ ¥ÑÌQ•É„ÑåÁ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QI}	1MP°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹™½É•AÉ•ÍÍÕÉ”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}QI}	1MP°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q•É…	±…ÍÐ°(€€€ô°((€€€m5=Y}M%1-}QIAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M%1,QI@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÉ½Ñ•ÑÌ¥ÑÍ•±˜°±½Ý•É¥¹q¸ˆ(€€€€€€€€€€€€‰MÁ••½¸½¹Ñ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ð°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}M%1-}QI@ô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¥±­QÉ…À°(€€€ô°((€€€m5=Y}a}-%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰a-%,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…äµ¥ÍÌ…¹¡ÕÉÐÑ¡”­¥­•È¹q¸ˆ(€€€€€€€€€€€€‰5…ä…ÕÍ”½¹™ÕÍ¥½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=%1}%}5%ML°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=9UM%=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}á•-¥¬°(€€€ô°((€€€m5=Y}1MQ}IMAQMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1MPIMAQLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡¥Ìµ½Ù”‘•…±Ìµ½É”‘…µ…•q¸ˆ(€€€€€€€€€€€€‰™½È•… ‘•™•…Ñ•…±±ä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}1MQ}IMAQL°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1…ÍÑI•ÍÁ•ÑÌ°(€€€ô°((€€€m5=Y}1U5%9}IM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1U5%9IM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µ¥¹µ…™™•Ñ¥¹œ±¥¡Ñq¸ˆ(€€€€€€€€€€€€‰¡…ÉÍ¡±ä±½Ý•ÉÌMÀ¸•˜¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}}5%9UM|È°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1Õµ¥¹…É…Í °(€€€ô°((€€€m5=Y}=II}UAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=IHU@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	½½ÍÑÌ„ÕÍ•ÈÌÍÑ…ÑÍq¸ˆ(€€€€€€€€€€€€‰‘•Á•¹‘¥¹œ½¸Q…ÑÍÕ¥É¤¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=II}U@°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}=É‘•ÉUÀ°(€€€ô°((€€€m5=Y})Q}AU9!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰)PAU9 ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÁÕ¹ ¥ÌÑ¡É½Ý¸…Ð‰±¥¹‘¥¹q¸ˆ(€€€€€€€€€€€€‰ÍÁ••Ñ¼ÍÑÉ¥­”™¥ÉÍÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ä°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}9aQ}AA1}I1%H°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•})•ÑAÕ¹ °(€€€ô°((€€€m5=Y}MA%e}aQIQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MA%daQIPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡…ÉÁ±äÕÁÌÑ…É•ÐÌÑÑ…¬±q¸ˆ(€€€€€€€€€€€€‰¡…ÉÍ¡±ä±½Ý•ÉÌ¥ÑÌ•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MA%e}aQIP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹µ…¥½…Ñ™™•Ñ•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ¥åáÑÉ…Ð°(€€€ô°((€€€m5=Y}MA%9}=UQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MA%8=UPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÕÉ¥½ÕÍ±äÍÑÉ…¥¹Ì¥ÑÌ±•Ì¹q¸ˆ(€€€€€€€€€€€€‰!…ÉÍ¡±ä±½Ý•ÉÌÕÍ•ÈÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|È°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ¥¹=ÕÐ°(€€€ô°((€€€m5=Y}A=AU1Q%=9}	=5	t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=AU1Q%=8	=5ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÌ™•±±½ÝÌ¡¥Ð½¹•q¸ˆ(€€€€€€€€€€€€‰Ñ¼Ñ•¸Ñ¥µ•Ì¥¸„É½Ü¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A=AU1Q%=9}	=5°(€€€€€€€€¹Á½Ý•È€ô€ÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€ÄÀ°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½ÁÕ±…Ñ¥½¹	½µˆ°(€€€ô°((€€€m5=Y}%}MA%99It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%MA%99Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%”µ½Ù•É•™••Ð¡¥Ð„™½•q¸ˆ(€€€€€€€€€€€€‰…¹‘•ÍÑÉ½äÑ¡”Ñ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%}MA%99H°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%•MÁ¥¹¹•È°(€€€ô°((€€€m5=Y}1%Y}IUM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%YIUM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½”…ÑÑ…­Ì¹•áÐÑÕÉ¸…¸Ñq¸ˆ(€€€€€€€€€€€€‰µ¥ÍÌ…¹‘¼‘½Õ‰±”‘…µ…”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%Y}IUM °(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…¥Ù•IÕÍ °(€€€ô°((€€€m5=Y}IY%Y1}	1MM%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IY%Y0	1MM%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I•Ù¥Ù•Ì„™…¥¹Ñ•Á…ÉÑäíA-59õq¸ˆ(€€€€€€€€€€€€‰…¹É•ÍÑ½É•Ì¡…±˜½˜¥ÑÌ!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IY%Y1}	1MM%9°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹Í­•Ñ¡	…¹¹•€ô€¡	}M-Q!}	9L€øô9|ä¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I•Ù¥Ù…±	±•ÍÍ¥¹œ°(€€€ô°((€€€m5=Y}M1Q}UIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M1PUIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!ÕÉÑÌ™½”•Ù•ÉäÑÕÉ¸¸½Õ‰±•q¸ˆ(€€€€€€€€€€€€‰‘…µ…”Ñ¼MÑ••°…¹]…Ñ•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}M1Q}UI°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M…±ÑÕÉ”°(€€€ô°((€€€m5=Y}QI%A1}%Yt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QI%A1%Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÑ…É•ÐÝ¥Ñ ÍÁ±…Í¡•Íq¸ˆ(€€€€€€€€€€€€‰½˜Ý…Ñ•È€ÌÑ¥µ•Ì¥¸„É½Ü¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€Ì°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}QÉ¥Á±•¥Ù”°(€€€ô°((€€€m5=Y}5=IQ1}MA%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5=IQ0MA%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É…Í•ÌÑÉ…Àµ½Ù•Ì…¹1••¡q¸ˆ(€€€€€€€€€€€€‰M••¸A½¥Í½¹Ì…‘©…•¹Ð™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}IA%}MA%8°(€€€€€€€€¹Á½Ý•È€ô€ÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}A=%M=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5½ÉÑ…±MÁ¥¸°(€€€ô°((€€€m5=Y}==1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰==1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡…¹•ÌÕÍ•ÈÌ…¹…±±äÍq¸ˆ(€€€€€€€€€€€€‰‰¥±¥Ñä¥¹Ñ¼Ñ¡”Ñ…É•ÐÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}==1°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½½‘±”°(€€€ô°((€€€m5=Y}%11Q}]et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%11P]dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡…ÉÁ±ä‰½½ÍÑÌ½™™•¹Í•Ì…¹‘q¸ˆ(€€€€€€€€€€€€‰MÁ••‰äÕÍ¥¹œ¥ÑÌ½Ý¸!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%11Q}]d°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}I=YI}!@ô°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥±±•ÑÝ…ä°(€€€ô°((€€€m5=Y}-=]Q=]}1Yt€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰-=]Q=\1Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÍ•ÈÍ±…Í¡•ÌÑ¡”™½”…™Ñ•Éq¸ˆ(€€€€€€€€€€€€‰­½ÝÑ½Ý¥¹œ¸%Ð¹•Ù•Èµ¥ÍÍ•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}-½ÝÑ½Ý±•…Ù”°(€€€ô°((€€€m5=Y}1=]I}QI%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1=]HQI%,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I¥•‰½ÕÅÕ•Ð¸±Ý…åÌ•ÑÍq¸ˆ(€€€€€€€€€€€€‰„É¥Ñ¥…°¡¥Ð°¹•Ù•Èµ¥ÍÍ¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…±Ý…åÍÉ¥Ñ¥…±!¥Ð€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±½Ý•ÉQÉ¥¬°(€€€ô°((€€€m5=Y}Q=I!}M=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q=I M=9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±…µ•ÌÍ½É Ñ¡”Ñ…É•Ð¹q¸ˆ(€€€€€€€€€€€€‰	½½ÍÑÌÑ¡”ÕÍ•ÈÌMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q½É¡M½¹œ°(€€€ô°((€€€m5=Y}EU}MQAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰EUMQ@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÝ¥Ñ ±¥¡Ð°™±Õ¥‘…¹•q¸ˆ(€€€€€€€€€€€€‰ÍÑ•ÁÌ¸UÁÌÑ¡”ÕÍ•ÈÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‘…¹•5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÅÕ…MÑ•À°(€€€ô°((€€€m5=Y}I%9}	U11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%9	U10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q…­±”Ñ¡…Ð‰É•…­Ì‰…ÉÉ¥•ÉÌ¹q¸ˆ(€€€€€€€€€€€€‰UÍ•ÈÌ™½É´‘•Ñ•Éµ¥¹•ÌÑåÁ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I%9}	U10°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	I-}MI8°(€€€€€€€€€€€€¹ÁÉ•ÑÑ…­™™•Ð€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I…¥¹	Õ±°°(€€€ô°((€€€m5=Y}5-}%Q}I%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5-%PI%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”ÕÍ•ÈÌMÀ¸Ñ¬¹q¸ˆ(€€€€€€€€€€€€‰5½¹•ä¥ÌÉ•½Ù•É•…™Ñ•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Aed°(€€€€€€€ô°(€€€€€€€ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…­•%ÑI…¥¸°(€€€ô°((€€€m5=Y}IU%9Q%=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰IU%9Q%=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÕµµ½¹Ì„ÉÕ¥¹½ÕÌ‘¥Í…ÍÑ•Éq¸ˆ(€€€€€€€€€€€€‰…¹ÕÑÌ¡…±˜Ñ¡”™½”Ì!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%a}AI9Q}5°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹‘…µ…•A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	1e}MQIQ1}5=9M}]%Q!}==}AA1L°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}IÕ¥¹…Ñ¥½¸°(€€€ô°((€€€m5=Y}=11%M%=9}=UIMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=11%M%=8=UIMˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÉ•¡¥ÍÑ½É¥Œ•áÁ±½Í¥½¸Ñ¡…ÐÍq¸ˆ(€€€€€€€€€€€€‰ÍÑÉ½¹•È¥˜ÍÕÁ•È•™™•Ñ¥Ù”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=11%M%=9}=UIM°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½±±¥Í¥½¹½ÕÉÍ”°(€€€ô°((€€€m5=Y}1QI=}I%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1QI<I%Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÕÑÕÉ¥ÍÑ¥Œ•±•ÑÉ¥¥Ñä¸%ÐÍq¸ˆ(€€€€€€€€€€€€‰ÍÑÉ½¹•È¥˜ÍÕÁ•È•™™•Ñ¥Ù”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}=11%M%=9}=UIM°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±•ÑÉ½É¥™Ð°(€€€ô°((€€€m5=Y}M!}Q%1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!Q%0ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É•…Ñ•Ì„MÕ‰ÍÑ¥ÑÕÑ”™½Éq¸ˆ(€€€€€€€€€€€€‰¥ÑÍ•±˜‰•™½É”ÍÝ¥Ñ¡¥¹œ½ÕÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M!}Q%0°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡•‘Q…¥°°(€€€ô°((€€€m5=Y}!%11e}IAQ%=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!%11dIAQ%=8ˆ¤°(€€€€€€€€¥˜	}AIII}%}]Q!H€ôô	}%}]Q!I}!%0(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	…©½­”ÍÕµµ½¹Ì¡…¥±ÍÑ½É´¹q¸ˆ(€€€€€€€€€€€€‰Q¡”ÕÍ•È…±Í¼ÍÝ¥Ñ¡•Ì½ÕÐ¸ˆ¤°(€€€€€€€€•±Í”(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	…©½­”ÍÕµµ½¹ÌÍ¹½ÝÍÑ½É´¹q¸ˆ(€€€€€€€€€€€€‰Q¡”ÕÍ•È…±Í¼ÍÝ¥Ñ¡•Ì½ÕÐ¸ˆ¤°(€€€€€€€€•¹‘¥˜(€€€€€€€€¹•™™•Ð€ôQ}]Q!I}9}M]%Q °(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹Ý•…Ñ¡•ÉQåÁ”€ô€¡	}AIII}%}]Q!H€ôô	}%}]Q!I}!%0¤€ü	QQ1}]Q!I}!%0€è	QQ1}]Q!I}M9=\ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¡¥±±åI••ÁÑ¥½¸°(€€€ô°((€€€m5=Y}Q%e}UAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q%dU@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÍ•ÈÑ¥‘¥•ÌÕÀ¡…é…É‘Ì…¹‘q¸ˆ(€€€€€€€€€€€€‰É…¥Í•Ì¥ÑÌÑÑ…¬…¹MÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q%e}U@°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q¥‘åUÀ°(€€€ô°((€€€m5=Y}M9=]MAt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M9=]MAˆ¤°(€€€€€€€€¥˜	}AIII}%}]Q!H€ôô	}%}]Q!I}!%0(€€€€€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€€€€€‰MÕµµ½¹Ì„¡…¥±ÍÑ½É´Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€€€€€‰ÍÑÉ¥­•Ì•Ù•ÉäÑÕÉ¸¸ˆ¤°(€€€€€€€€•±Í”(€€€€€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€€€€€‰MÕµµ½¹Ì„Í¹½ÝÍÑ½É´Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€€€€€‰±…ÍÑÌ™½È™¥Ù”ÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€•¹‘¥˜(€€€€€€€€¹•™™•Ð€ôQ}]Q!H°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹Ý•…Ñ¡•ÉQåÁ”€ô€¡	}AIII}%}]Q!H€ôô	}%}]Q!I}!%0¤€ü	QQ1}]Q!I}!%0€è	QQ1}]Q!I}M9=\ô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}MA}UA|Äô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô}UAQ}5=Y}QL€øô9|Ø€ü=9QMQ}Q}	1e}MQIQ1}5=9M}]%Q!}==}AA1L€è=9QMQ}Q}	1e}MQIQ1}AIY}5=9L°(€€€€€€€€¹½¹Ñ•ÍÑ…Ñ•½Éä€ô=9QMQ}Q=Ie}	UQd°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô€¡	}AIII}%}]Q!H€ôô	}%}]Q!I}!%0¤€ü	…ÑÑ±•¹¥µ5½Ù•}!…¥°€è	…ÑÑ±•¹¥µ5½Ù•}M¹½ÝÍ…Á”°(€€€ô°((€€€m5=Y}A=U9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=U9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•ÈÁ½Õ¹•Ì½¸Ñ¡”™½”±q¸ˆ(€€€€€€€€€€€€‰±½Ý•É¥¹œ¥ÑÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½Õ¹”°(€€€ô°((€€€m5=Y}QI%1	1it€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QI%1	1iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”ÕÍ•È…ÑÑ…­ÌÍÕ‘‘•¹±ä±q¸ˆ(€€€€€€€€€€€€‰É…¥Í¥¹œ¥ÑÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}]%Q!}==}=9%Q%=8°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}QÉ…¥±‰±…é”°(€€€ô°((€€€m5=Y}!%11%9}]QIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!%11%9]QHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Í¡½Ý•ÈÝ¥Ñ ¥”µ½±Ý…Ñ•Éq¸ˆ(€€€€€€€€€€€€‰±½Ý•ÉÌÑ¡”Ñ…É•ÐÌÑÑ…¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q-}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¡¥±±¥¹]…Ñ•È°(€€€ô°((€€€m5=Y}!eAI}I%11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!eAHI%10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÍÁ¥¹¹¥¹œÁ½¥¹Ñ•Á…ÉÑq¸ˆ(€€€€€€€€€€€€‰‰åÁ…ÍÍ•Ì„™½”ÌAÉ½Ñ•Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!åÁ•ÉÉ¥±°°(€€€ô°((€€€m5=Y}Q]%9}	5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q]%8	4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5åÍÑ¥…°•å”µ‰•…µÌÑ¡…Ð¡¥Ñq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•ÐÑÝ¥”¥¸„É½Ü¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€È°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}QÝ¥¹	•…´°(€€€ô°((€€€m5=Y}I}%MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”µ½É”Ñ¡”ÕÍ•È¡…Ì‰••¹q¸ˆ(€€€€€€€€€€€€‰¡¥Ð°Ñ¡”ÍÑÉ½¹•ÈÑ¡”µ½Ù”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I}%MP°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I…•¥ÍÐ°(€€€ô°((€€€m5=Y}I5=I}99=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I5=H99=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÍÑÉ½¹œ…ÑÑ…¬‰ÕÐ±½Ý•ÉÍq¸ˆ(€€€€€€€€€€€€‰Ñ¡”‘•™•¹Í¥Ù”ÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}MA}=]8°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Éµ½É…¹¹½¸°(€€€ô°((€€€m5=Y}	%QQI}	1t€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€Ì°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	%QQH	1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÑÑ…¬Ñ¡…Ð…‰Í½É‰Íq¸ˆ(€€€€€€€€€€€€‰¡…±˜Ñ¡”‘…µ…”¥¹™±¥Ñ•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	¥ÑÑ•É	±…‘”°(€€€ô°((€€€m5=Y}=U	1}M!=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=U	1M!=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¥Í¡…É•Ì…±°•±•ÑÉ¥¥Ñä±q¸ˆ(€€€€€€€€€€€€‰±½Í¥¹œÑ¡”±•ÑÉ¥ŒÑåÁ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%1}%}9=Q}I}QeA°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÑåÁ”€ôQeA}1QI%ô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I5=Y}I}QeA°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½Õ‰±•M¡½¬°(€€€ô°((€€€m5=Y}%Q=9}!55It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%Q=8!55Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÝ¥¹Ì„¡Õ”¡…µµ•È¸…¸Ñq¸ˆ(€€€€€€€€€€€€‰‰”ÕÍ•ÑÝ¥”¥¸„É½Ü¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…¹ÑUÍ•QÝ¥”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥…Ñ½¹!…µµ•È°(€€€ô°((€€€m5=Y}=5UAA9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=5UAA9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I•Ñ…±¥…Ñ•ÌÍÑÉ½¹±ä……¥¹ÍÑq¸ˆ(€€€€€€€€€€€€‰Ý¡¼±…ÍÐ¡ÕÉÐÑ¡”ÕÍ•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I1Q}5°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}A9L°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì(€€€€€€€€€€€€¹É•™±•Ñ…µ…”¹‘…µ…•A•É•¹Ð€ô€ÄÔÀ°(€€€€€€€€€€€€¹É•™±•Ñ…µ…”¹‘…µ…•…Ñ•½É¥•Ì€ô€ÅÔ€ðð5}Q=Ie}A!eM%0ð€ÅÔ€ðð5}Q=Ie}MA%0°(€€€€€€€ô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ•¥ÉÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}1MP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½µ•ÕÁÁ…¹”°(€€€ô°((€€€m5=Y}EU}UQQIt€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰EUUQQHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÉ•ÍÍÕÉ¥é•Ý…Ñ•ÈÕÐÝ¥Ñ …q¸ˆ(€€€€€€€€€€€€‰¡¥ É¥Ñ¥…°µ¡¥ÐÉ…Ñ¥¼¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹É¥Ñ¥…±!¥ÑMÑ…”€ô	}UAQ}5=Y}Q€øô9|Ì€ü€Ä€è€È°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÅÕ…ÕÑÑ•È°(€€€ô°((€€€m5=Y}	1i%9}Q=IEUt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	1i%9Q=IEUˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ˆ´´´ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•¥ÉÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹•¹½É•	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹Í­•Ñ¡	…¹¹•€ô€¡	}M-Q!}	9L€øô9|ä¤°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	±…é¥¹Q½ÉÅÕ”°(€€€€€€€€¹É…¹‘½µ¥é•É%¹Ù…±¥€ôQIU°(€€€ô°((€€€m5=Y}]%-}Q=IEUt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]%-Q=IEUˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ˆ´´´ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•¥ÉÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹•¹½É•	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹Í­•Ñ¡	…¹¹•€ô€¡	}M-Q!}	9L€øô9|ä¤°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}M1@°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]¥­•‘Q½ÉÅÕ”°(€€€€€€€€¹É…¹‘½µ¥é•É%¹Ù…±¥€ôQIU°(€€€ô°((€€€m5=Y}9=a%=UM}Q=IEUt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9=a%=ULQ=IEUˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ˆ´´´ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•¥ÉÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹•¹½É•	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹Í­•Ñ¡	…¹¹•€ô€¡	}M-Q!}	9L€øô9|ä¤°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}A=%M=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}9½á¥½ÕÍQ½ÉÅÕ”°(€€€€€€€€¹É…¹‘½µ¥é•É%¹Ù…±¥€ôQIU°(€€€ô°((€€€m5=Y}=5	Q}Q=IEUt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=5	PQ=IEUˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ˆ´´´ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•¥ÉÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹•¹½É•	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹Í­•Ñ¡	…¹¹•€ô€¡	}M-Q!}	9L€øô9|ä¤°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1eM%L°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½µ‰…ÑQ½ÉÅÕ”°(€€€€€€€€¹É…¹‘½µ¥é•É%¹Ù…±¥€ôQIU°(€€€ô°((€€€m5=Y}5%1}Q=IEUt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5%0Q=IEUˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ˆ´´´ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹µ•¥ÉÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹µ•ÑÉ½¹½µ•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹•¹½É•	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹Í­•Ñ¡	…¹¹•€ô€¡	}M-Q!}	9L€øô9|ä¤°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=9UM%=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…¥…±Q½ÉÅÕ”°(€€€€€€€€¹É…¹‘½µ¥é•É%¹Ù…±¥€ôQIU°(€€€ô°((€€€m5=Y}AMe	1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AMe	1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡¥Ìµ½Ù”ÌÁ½Ý•È¥¹É•…Í•Íq¸ˆ(€€€€€€€€€€€€‰Ý¡•¸½¸±•ÑÉ¥ŒQ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QII%9}	==MP°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…ÉÕµ•¹Ð¹Ñ•ÉÉ…¥¹	½½ÍÐ€ôì(€€€€€€€€€€€€¹Ñ•ÉÉ…¥¸€ôMQQUM}%1}1QI%}QII%8°(€€€€€€€€€€€€¹Á•É•¹Ð€ô€ÔÀ°(€€€€€€€€€€€€¹É½Õ¹‘¡•¬€ôI=U9}!-}9=9°(€€€€€€€ô°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍå‰±…‘”°(€€€ô°((€€€m5=Y}!eI=}MQ5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!eI<MQ4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡¥Ìµ½Ù”ÌÁ½Ý•È¥¹É•…Í•Íq¸ˆ(€€€€€€€€€€€€‰Õ¹‘•È¡…ÉÍ ÍÕ¹±¥¡Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!eI=}MQ4°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ñ¡…ÝÍUÍ•È€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!å‘É½MÑ•…´°(€€€ô°((€€€m5=Y}	1==}5==9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	1==5==8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰U¹±•…Í¡•ÌÑ¡”‰±½½µ½½¸¹q¸ˆ(€€€€€€€€€€€€‰…¸Ð‰”ÕÍ•ÑÝ¥”¥¸„É½Ü¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÐÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…¹ÑUÍ•QÝ¥”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	±½½‘5½½¸°(€€€ô°((€€€m5=Y}5Q!}=Q!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5Q!=Q!ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰‰Í½É‰Ì¡…±˜Ñ¡”‘…µ…•q¸ˆ(€€€€€€€€€€€€‰¥¹™±¥Ñ•¸5…ä…ÕÍ”„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹Ñ¡…ÝÍUÍ•È€ôQIU°(€€€€€€€€¹¡•…±¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…Ñ¡…½Ñ¡„°(€€€ô°((€€€m5=Y}MeIUA}	=5	t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MeIU@	=5ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1½Ý•ÉÌÑ¡”™½”ÌÍÁ••‘q¸ˆ(€€€€€€€€€€€€‰•… ÑÕÉ¸™½È€ÌÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…±±¥ÍÑ¥5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MeIUA}	=5°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MåÉÕÁ	½µˆ°(€€€ô°((€€€m5=Y}%Ye}U1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%YdU0ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰QåÁ”¡…¹•ÌÝ¥Ñ ¡•±µ…Í¬¹q¸ˆ(€€€€€€€€€€€€‰!¥ É¥Ñ¥…°µ¡¥ÐÉ…Ñ¥¼¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%Ye}U0°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹É¥Ñ¥…±!¥ÑMÑ…”€ô	}UAQ}5=Y}Q€øô9|Ì€ü€Ä€è€È°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%ÙåÕ‘•°°(€€€ô°((€€€m5=Y}1QI=}M!=Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1QI<M!=Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…Ñ¡•ÉÌ•±•ÑÉ¥¥Ñä°Ñ¡•¹q¸ˆ(€€€€€€€€€€€€‰™¥É•Ì„¡¥ µÙ½±Ñ…”Í¡½Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}Q]=}QUI9M}QQ,°(€€€€€€€€¹Á½Ý•È€ô€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í±••ÁQ…±­	…¹¹•€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð¹ÑÝ½QÕÉ¹ÑÑ…¬€ôì€¹ÍÑÉ¥¹%€ôMQI%9%}1QI=M!=Q!I%9°€¹Ý•…Ñ¡•È€ô	}]Q!I}I%8ô°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹½¹¡…É•QÕÉ¹=¹±ä€ôQIU°(€€€€€€€€€€€€¹Í¡••É½É•=Ù•ÉÉ¥‘”€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±•ÑÉ½M¡½Ð°(€€€ô°((€€€m5=Y}QI}MQIMQ=I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QIMQIMQ=I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%¸Q•É…Á…½ÌÌMÑ•±±…Éq¸ˆ(€€€€€€€€€€€€‰½É´°¥Ð¡¥ÑÌ…±°™½•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}QI}MQIMQ=I4°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹µ¥µ¥	…¹¹•€ôQIU°(€€€€€€€€¹Í­•Ñ¡	…¹¹•€ô€¡	}M-Q!}	9L€øô9|ä¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q•É…MÑ…ÉÍÑ½É´°(€€€ô°((€€€m5=Y}%-1}	5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%-1	4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¡½½ÑÌ„‰•…´½˜±¥¡Ð¹q¸ˆ(€€€€€€€€€€€€‰M½µ•Ñ¥µ•ÌÑÝ¥”…ÌÍÑÉ½¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%-1}	4°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥­±•	•…´°(€€€ô°((€€€m5=Y}	UI9%9}	U1]I-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	UI9%9	U1]I,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Ù…‘•Ì…ÑÑ…¬°…¹‰ÕÉ¹Íq¸ˆ(€€€€€€€€€€€€‰Ñ¡”™½”¥˜ÍÑÉÕ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ð°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}	UI9%9}	U1]I,ô°(€€€€€€€€¹é5½Ù”€ôì€¹•™™•Ð€ôi}Q}IMQ}MQQLô°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹½Áå…Ñ	…¹¹•€ôQIU°(€€€€€€€€¹…ÍÍ¥ÍÑ	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	ÕÉ¹¥¹	Õ±Ý…É¬°(€€€ô°((€€€m5=Y}Q!U9I1At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q!U9I1@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍMÕ­•ÉAÕ¹¡•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}MU-I}AU9 °(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ä°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}	QQI}%}%IMP°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q¡Õ¹‘•É±…À°(€€€ô°((€€€m5=Y}5%!Qe}1Yt€ô(€€€ì(€€€€€€€€¼¼AI0µÁ¥¹¹•…ÕÑ¡•¹Ñ¥ŒÍÑ…ÑÕÌÍ•½¹‘…Éä•™™•Ð¸(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5%!Qd1Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ•¥¹Ñ•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5¥¡Ñå±•…Ù”°(€€€ô°((€€€m5=Y}Q!e=9}UQQIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q!e=8UQQHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1…Õ¹¡•ÌÁ…ÉÑ¥±”‰±…‘•Ì…Ñq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸MÑÉ¥­•ÌÑÝ¥”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹ÍÑÉ¥­•½Õ¹Ð€ô€È°(€€€€€€€€¹Í±¥¥¹5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q…¡å½¹ÕÑÑ•È°(€€€ô°((€€€m5=Y}!I}AIMMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!IAIMLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ]É¥¹=ÕÑ•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}A=]I}	M}=9}QIQ}!@°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!…É‘AÉ•ÍÌ°(€€€ô°((€€€m5=Y}I=9}!It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I=8!Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%¹É•…Í•Ì…±±¥•ÌœÉ¥Ñ¥…°¡¥Ñq¸ˆ(€€€€€€€€€€€€‰É…Ñ¥¼°•ÍÁ•¥…±±ä¥˜É…½¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=9}!H°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…½¹¡••È°(€€€ô°((€€€m5=Y}11UI%9}Y=%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰11UI%9Y=%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½¹™ÕÍ•Ì™½”¥˜¥ÑÌÍÑ…ÑÍq¸ˆ(€€€€€€€€€€€€‰Ý•É”‰½½ÍÑ•Ñ¡¥ÌÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=9UM%=8°(€€€€€€€€€€€€¹½¹±å%™Q…É•ÑI…¥Í•‘MÑ…ÑÌ€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±±ÕÉ¥¹Y½¥”°(€€€ô°((€€€m5=Y}Q5AI}1It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q5AH1Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰‘•ÍÁ•É…Ñ¥½¸…ÑÑ…¬¸A½Ý•Éq¸ˆ(€€€€€€€€€€€€‰‘½Õ‰±•Ì¥˜±…ÍÐµ½Ù”™…¥±•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQ=5A%9}Q9QIU4°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q•µÁ•É±…É”°(€€€ô°((€€€m5=Y}MUAI11}M15t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MUAI10M14ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¸•±•ÑÉ¥™¥•Í±…´¸%˜¥Ñq¸ˆ(€€€€€€€€€€€€‰µ¥ÍÍ•Ì°Ñ¡”ÕÍ•È¥Ì¡ÕÉÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=%1}%}5%ML°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µ¥¹¥µ¥é•½Õ‰±•…µ…”€ôQIU°(€€€€€€€€¹½¹Ñ•ÍÑ™™•Ð€ô=9QMQ}Q}UMI}5=I}M%1e}MQIQ1°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½MÑ…ÉÑ•É%€ô€À°(€€€€€€€€¹½¹Ñ•ÍÑ½µ‰½5½Ù•Ì€ôìÁô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÕÁ•É•±±M±…´°(€€€ô°((€€€m5=Y}AMe!%}9=%Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AMe!%9=%Mˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M½Õ¹Ý…Ù•ÌÑ¡…Ð‘…µ…”…¹‘q¸ˆ(€€€€€€€€€€€€‰ÁÉ•Ù•¹Ð¡•…±¥¹œ™½È€ÈÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AMe!%}9=%M°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍå¡¥9½¥Í”°(€€€ô°((€€€m5=Y}UAAI}!9t€ô(€€€ì(€€€€€€€€¹•™™•Ð€ôQ}UAAI}!9°(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰UAAH!9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…­•ÌÑ¡”Ñ…É•Ð™±¥¹ ¥™q¸ˆ(€€€€€€€€€€€€‰É•…‘å¥¹œ„ÁÉ¥½É¥Ñäµ½Ù”¸ˆ¤°(€€€€€€€€¹Á½Ý•È€ô€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ì°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}UÁÁ•É!…¹°(€€€ô°((€€€m5=Y}51%99Q}!%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰51%99P!%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½ÉÉ½Í¥Ù”¡…¥¸…ÑÑ…­q¸ˆ(€€€€€€€€€€€€‰Ñ¡…Ðµ…ä‰…‘±äÁ½¥Í½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q=a%°(€€€€€€€€€€€€¹¡…¹”€ô€ÔÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…±¥¹…¹Ñ¡…¥¸°(€€€ô°((€€€€¼¼hµ5½Ù•Ì(€€€m5=Y}	I-9-}	1%Qit€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	I-9,	1%Qhˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	Õ¥±‘Ìµ½µ•¹ÑÕ´…¹É…Í¡•Íq¸ˆ(€€€€€€€€€€€€‰¥¹Ñ¼Ñ¡”™½”¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°€€€€¼½‘•Ñ•Éµ¥¹•™É½´µ½Ù”ÑåÁ”(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	É•…­¹•­	±¥Ñè°(€€€ô°(€€€m5=Y}11}=UQ}AU551%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰10µ=UPAU551%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I…µÌ…¸•¹•Éä½Éˆ¥¹Ñ½q¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±±=ÕÑAÕµµ•±¥¹œ°(€€€ô°(€€€m5=Y}MUAIM=9%}M-eMQI%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MUAIM=9%M-eMQI%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M½…ÉÌÕÀ…¹Á±Õµµ•ÑÌÑ½Ý…É‘q¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÕÁ•ÉÍ½¹¥M­åÍÑÉ¥­”°(€€€ô°(€€€m5=Y}%}=]9A=UIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%=]9A=UHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¥¹­ÌÑ¡”Ñ…É•Ð¥¸„Á½¥Í½¹q¸ˆ(€€€€€€€€€€€€‰ÍÝ…µÀ¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥‘½Ý¹Á½ÕÈ°(€€€ô°(€€€m5=Y}QQ=9%}It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QQ=9%Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	ÕÉÉ½ÝÌ‘••À…¹Í±…µÌ¥¹Ñ½q¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q•Ñ½¹¥I…”°(€€€ô°(€€€m5=Y}=9Q%99Q1}IUM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=9Q%99Q0IUM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É½ÁÌ„¡Õ”É½¬µ½Õ¹Ñ…¥¹q¸ˆ(€€€€€€€€€€€€‰½¸Ñ¡”™½”¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½¹Ñ¥¹•¹Ñ…±ÉÕÍ °(€€€ô°(€€€m5=Y}MY}MA%9}=UQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MYMA%8µ=UPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÁ¥ÑÌÑ¡É•…‘Ì½˜Í¥±¬Ñ½q¸ˆ(€€€€€€€€€€€€‰‰¥¹Ñ¡”™½”¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M…Ù…•MÁ¥¹=ÕÐ°(€€€ô°(€€€m5=Y}9YI}9%9}9%!Q5It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9YHµ9%99%!Q5Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰••ÀµÍ•…Ñ•ÉÕ‘•ÌÑÉ…Áq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}9•Ù•É¹‘¥¹9¥¡Ñµ…É”°(€€€ô°(€€€m5=Y}=I-MI]}IM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=I-MI\IM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÁ¥¹ÌÙ•Éä™…ÍÐ…¹É…µÍq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½É­ÍÉ•ÝÉ…Í °(€€€ô°(€€€m5=Y}%9I9=}=YII%Yt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%9I9<=YII%Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	É•…Ñ¡•Ì¥¹Ñ•¹Í”™¥É”…Ñq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%¹™•É¹½=Ù•É‘É¥Ù”°(€€€ô°(€€€m5=Y}!eI=}Y=IQat€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!eI<Y=IQ`ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡Õ”Ý¡¥É±Á½½°ÍÝ…±±½ÝÍq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}!å‘É½Y½ÉÑ•à°(€€€ô°(€€€m5=Y}	1==5}==5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	1==4==4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÍ•ÌÁ±…¹Ð•¹•ÉäÑ¼…ÑÑ…­q¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	±½½µ½½´°(€€€ô°(€€€m5=Y}%Y=1Q}!Y=t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%Y=1P!Y=ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰!¥ÑÌÑ¡”™½”Ý¥Ñ Á½Ý•É™Õ±q¸ˆ(€€€€€€€€€€€€‰•±•ÑÉ¥¥Ñä¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥…Ù½±Ñ!…Ù½Œ°(€€€ô°(€€€m5=Y}M!QQI}AMe!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!QQIAMe!ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½¹ÑÉ½±ÌÑ¡”Ñ…É•ÐÑ½q¸ˆ(€€€€€€€€€€€€‰¡ÕÉÐ¥Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡…ÑÑ•É•‘AÍå¡”°(€€€ô°(€€€m5=Y}MU	iI=}M155It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MU	iI<M155Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É½ÁÌÑ¡”Ñ•µÀ…¹™É••é•Íq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÕ‰é•É½M±…µµ•È°(€€€ô°(€€€m5=Y}YMQQ%9}I-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰YMQQ%9I-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰•Ù•±½ÁÌ…ÕÉ„…¹…ÑÑ…­Íq¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•Ð¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•Ù…ÍÑ…Ñ¥¹É…­”°(€€€ô°(€€€m5=Y}	1-}!=1}1%AMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	1,!=11%AMˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÕ­ÌÑ¡”Ñ…É•Ð¥¹Ñ¼‘…É­q¸ˆ(€€€€€€€€€€€€‰•¹•Éä¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	±…­!½±•±¥ÁÍ”°(€€€ô°(€€€m5=Y}Q]%9-1}Q-1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q]%9-1Q-1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q½åÌÝ¥Ñ Ñ¡”Ñ…É•Ð¥¸…q¸ˆ(€€€€€€€€€€€€‰¡…Éµ¥¹œÍÁ…”¸A½Ý•ÈÙ…É¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}QÝ¥¹­±•Q…­±”°(€€€ô°(€€€m5=Y}QMQI=A%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QMQI=A%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰A¥­…¡ÔÕÍ•ÌÑ¡”µ…à…µ½Õ¹Ñq¸ˆ(€€€€€€€€€€€€‰½˜•±•ÑÉ¥¥Ñä…¹Á½Õ¹•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}…Ñ…ÍÑÉ½Á¥­„°(€€€ô°(€€€m5=Y|ÄÀÀÀÀÀÀÁ}Y=1Q}Q!U9I	=1Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ˆÄÀ°ÀÀÀ°ÀÀÀY=1PQ!U9I	=1Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…ÀA¥­…¡ÔÕ¹±•…Í¡•Ì©½±Ð¹q¸ˆ(€€€€€€€€€€€€‰!¥ É¥Ñ¥…°µ¡¥ÐÉ…Ñ¥¼¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄäÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹É¥Ñ¥…±!¥ÑMÑ…”€ô€È°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•|ÄÀÀÀÀÀÀÁY½±ÑQ¡Õ¹‘•É‰½±Ð°(€€€ô°(€€€m5=Y}MQ=-}MAI-MUIIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ=-MAI-MUIHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±½±…¸I…¥¡Ô…ÑÑ…­ÌÝ¥Ñ¡q¸ˆ(€€€€€€€€€€€€‰™Õ±°™½É”¸…ÕÍ•ÌÁ…É…±åÍ¥Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1eM%L°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ½­•‘MÁ…É­ÍÕÉ™•È°(€€€ô°(€€€m5=Y}aQI5}Y=	==MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰aQI5Y=	==MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰•Ù•”•ÑÌ•¹•Éä™É½µq¸ˆ(€€€€€€€€€€€€‰¥ÑÌ™É¥•¹‘Ì¸	½½ÍÑÌÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}aQI5}Y=	==MP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}áÑÉ•µ•Ù½‰½½ÍÐ°(€€€ô°(€€€m5=Y}AU1YI%i%9}A9-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AU1YI%i%9A9-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M¹½É±…à•¹•É•Ñ¥…±±äµ½Ù•Íq¸ˆ(€€€€€€€€€€€€‰…¹…ÑÑ…­ÌÝ¥Ñ ™Õ±°™½É”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÕ±Ù•É¥é¥¹A…¹…­”°(€€€ô°(€€€m5=Y}9M%M}MUAI9=Yt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9M%LMUAI9=Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5•Ü…ÑÑ…­ÌÝ¥Ñ ™Õ±°™½É”¹q¸ˆ(€€€€€€€€€€€€‰AÍå¡¥…±±ä¡…É•ÌÑ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄàÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}•¹•Í¥ÍMÕÁ•É¹½Ù„°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AMe!%}QII%8°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€ô°(€€€m5=Y}M%9%MQI}II=]}I%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M%9%MQHII=\I%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰•¥‘Õ•å”Í¡½½ÑÌ½Õ¹Ñ±•ÍÍq¸ˆ(€€€€€€€€€€€€‰…ÉÉ½ÝÌÝ¥Ñ ™Õ±°™½É”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄàÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¥¹¥ÍÑ•ÉÉÉ½ÝI…¥°(€€€ô°(€€€m5=Y}51%%=UM}5==9MU1Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰51%%=UL5==9MU1Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%¹¥¹•É½…ÈÉ…Í¡•Ì¥¹Ñ½q¸ˆ(€€€€€€€€€€€€‰Ñ¡”Ñ…É•ÐÝ¥Ñ ™Õ±°™½É”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄàÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ¥¹¥µ¥é•½Õ‰±•…µ…”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…±¥¥½ÕÍ5½½¹Í…Õ±Ð°(€€€ô°(€€€m5=Y}=9%}=AIQQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=9%=AIQQˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÉ¥µ…É¥¹„ÍÕµµ½¹Ì„µ…ÍÍ¥Ù•q¸ˆ(€€€€€€€€€€€€‰…µ½Õ¹Ð½˜Ý…Ñ•È…ÐÑ¡”™½”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄäÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}=•…¹¥=Á•É•ÑÑ„°(€€€ô°(€€€m5=Y}MA1%9QI}MQ=I5M!IMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MA1%9QIMQ=I5M!ILˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1å…¹É½Œ…ÑÑ…­ÌÝ¥Ñ ™Õ±±q¸ˆ(€€€€€€€€€€€€‰™½É”¸I•µ½Ù•Ì…±°Ñ•ÉÉ…¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%}MA%99H°(€€€€€€€€¹Á½Ý•È€ô€ÄäÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÁ±¥¹Ñ•É•‘MÑ½ÉµÍ¡…É‘Ì°(€€€ô°(€€€m5=Y}1QM}M9U1}=IYIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1PLM9U1=IYHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5¥µ¥­åÔÁÕ¹¡•ÌÑ¡”Ñ…É•Ñq¸ˆ(€€€€€€€€€€€€‰Ý¥Ñ ™Õ±°™½É”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄäÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1•ÑÍM¹Õ±•½É•Ù•È°(€€€ô°(€€€m5=Y}19=I=UM}M=U1	1it€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰19=I=ULM=U1	1iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰-½µµ¼µ¼…ÑÑ…­ÌÝ¥Ñ ™Õ±±q¸ˆ(€€€€€€€€€€€€‰™½É”¸	½½ÍÑÌ…±°ÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄàÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹¥¹½É•ÍMÕ‰ÍÑ¥ÑÕÑ”€ô	}UAQ}5=Y}1L€øô9|Ø°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}11}MQQM}U@°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…¹½É½ÕÍM½Õ±‰±…é”°(€€€ô°(€€€m5=Y}UI%9}=}1=1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰UI%8=1=1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Q¡”1…¹MÁ¥É¥ÐA½¯¥µ½¹q¸ˆ(€€€€€€€€€€€€‰É•…Ñ±äÉ•‘Õ•ÌÑ¡”™½”Ì!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}%a}AI9Q}5°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹‘…µ…•A•É•¹Ñ…”€ô€ÜÔô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Õ…É‘¥…¹=™±½±„°(€€€ô°(€€€m5=Y}MI%9}MU9Ii}M5M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MI%9MU9IiM5M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M½±…±•¼…ÑÑ…­ÌÝ¥Ñ ™Õ±±q¸ˆ(€€€€€€€€€€€€‰™½É”¸%¹½É•Ì…‰¥±¥Ñ¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ‰¥±¥Ñä€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M•…É¥¹MÕ¹É…é•Mµ…Í °(€€€ô°(€€€m5=Y}59%9}5==9Ii}51MQI=5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰59%95==9Ii51MQI=4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰1Õ¹…±„…ÑÑ…­ÌÝ¥Ñ ™Õ±±q¸ˆ(€€€€€€€€€€€€‰™½É”¸%¹½É•Ì…‰¥±¥Ñ¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ‰¥±¥Ñä€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5•¹…¥¹5½½¹É…é•5…•±ÍÑÉ½´°(€€€ô°(€€€m5=Y}1%!Q}Q!Q}	UI9M}Q!}M-et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%!PQ!P	UI9LQ!M-dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰UÍ•Ì9•É½éµ„Ì¡¥¡•ÍÑq¸ˆ(€€€€€€€€€€€€‰…ÑÑ…¬¸%¹½É•Ì…‰¥±¥Ñ¥•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}A!=Q=9}eMH°(€€€€€€€€¹Á½Ý•È€ô€ÈÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ‰¥±¥Ñä€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1¥¡ÑQ¡…Ñ	ÕÉ¹ÍQ¡•M­ä°(€€€ô°(€€€m5=Y}M=U1}MQ1%9|Ý}MQI}MQI%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M=U0µMQ1%9€ÜµMQHMQI%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰5…ÉÍ¡…‘½ÜÁÕ¹¡•Ì…¹‘q¸ˆ(€€€€€€€€€€€€‰­¥­ÌÝ¥Ñ ™Õ±°™½É”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄäÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M½Õ±MÑ•…±¥¹œÝMÑ…ÉMÑÉ¥­”°(€€€ô°((€€€m5=Y}5a}UIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`UIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍAÉ½Ñ•Ñ•ÍÉ¥ÁÑ¥½¸°(€€€€€€€€¹•™™•Ð€ôQ}AI=QP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€Ð°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹ÁÉ½Ñ•Ñ5•Ñ¡½€ôAI=QQ}5a}UIô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áÕ…É°(€€€ô°((€€€m5=Y}5a}1It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`1Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¥É”å¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰%¹Ñ•¹Í¥™¥•ÌÍÕ¸™½È€ÔÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á±…É”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MU8°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}1UQQI	et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`1UQQI	dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	Õœå¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌ™½”ÌMÀ¸Ñ¬ÍÑ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á±ÕÑÑ•É‰ä°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1=]I}MA}Q-}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}1%!Q9%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`1%!Q9%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±•ÑÉ¥Œå¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰QÕÉ¹ÌÑ¡”Ñ•ÉÉ…¥¸•±•ÑÉ¥Œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á1¥¡Ñ¹¥¹œ°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1QI%}QII%8°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}MQI%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`MQI%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰9½Éµ…°å¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌ™½”ÌMÁ••ÍÑ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áMÑÉ¥­”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1=]I}MA}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}-9U-1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`-9U-1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¥¡Ñ¥¹œå¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰	½½ÍÑÌ…±±äÑÑ…¬ÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á-¹Õ­±”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I%M}Q5}QQ,°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}A!9QM5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`A!9QM4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰¡½ÍÐå¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌ™½”Ì•™•¹Í”ÍÑ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áA¡…¹Ñ…Í´°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1=]I}9M}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}!%1MQ=I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`!%1MQ=I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰%”å¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰MÕµµ½¹Ì¡…¥°™½È€ÔÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á!…¥±ÍÑ½É´°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}!%0°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}==it€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`==iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰A½¥Í½¸å¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰	½½ÍÑÌ…±±äMÀ¸Ñ¬ÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á=½é”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I%M}Q5}MA}Q,°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}eMIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`eMHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰]…Ñ•Èå¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰MÕµµ½¹ÌÉ…¥¸™½È€ÔÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á•åÍ•È°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I%8°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}%IMQI5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`%IMQI4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰±å¥¹œå¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰	½½ÍÑÌ…±±äMÁ••ÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á¥ÉÍÑÉ•…´°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I%M}Q5}MA°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}MQI11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`MQI10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…¥Éäå¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰QÕÉ¹ÌÑ¡”Ñ•ÉÉ…¥¸µ¥ÍÑä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áMÑ…É™…±°°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}5%MQe}QII%8°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}]eI5]%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`]eI5]%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É…½¸å¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌ™½”ÌÑÑ…¬ÍÑ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á]åÉµÝ¥¹°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1=]I}QQ-}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}5%9MQ=I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`5%9MQ=I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰AÍå¡¥Œå¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰QÕÉ¹ÌÑ¡”Ñ•ÉÉ…¥¸ÁÍå¡¥Œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á5¥¹‘ÍÑ½É´°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AMe!%}QII%8°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}I=-11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`I=-10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I½¬å¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰MÕµµ½¹Ì„Í…¹‘ÍÑ½É´¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áI½­™…±°°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}M9MQ=I4°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}EU-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`EU-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É½Õ¹å¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰	½½ÍÑÌ…±±äMÀ¸•˜ÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹Í­å	…ÑÑ±•	…¹¹•€ô	}aQIA=1Q}5=Y}1L°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áEÕ…­”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I%M}Q5}MA}°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}I-9MMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`I-9MLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…É¬å¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌ™½”ÌMÀ¸•˜ÍÑ…Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€Ä°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á…É­¹•ÍÌ°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1=]I}MA}}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}=YII=]Q!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`=YII=]Q ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É…ÍÌå¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰QÕÉ¹ÌÑ¡”Ñ•ÉÉ…¥¸É…ÍÍä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á=Ù•ÉÉ½ÝÑ °(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}IMMe}QII%8°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}5a}MQ1MA%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5`MQ1MA%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÑ••°å¹…µ…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰	½½ÍÑÌ…±±ä•™•¹Í”ÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áMÑ••±ÍÁ¥­”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I%M}Q5}9M°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}Y%9}1M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`Y%91M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àY•¹ÕÍ…ÕÈ…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰…µ…•Ì™½È€ÐÑÕÉ¹Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áY¥¹•1…Í °(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Y%9}1M °(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}]%1%It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`]%1%Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à¡…É¥é…É…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰…µ…•Ì™½È€ÐÑÕÉ¹Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á]¥±‘™¥É”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}]%1%I°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}99=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`99=9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à	±…ÍÑ½¥Í”…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰…µ…•Ì™½È€ÐÑÕÉ¹Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á…¹¹½¹…‘”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}99=9°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}	U1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`	U1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à	ÕÑÑ•É™É•”…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰A½¥Í½¸°Á…É…±åÍ¥Ì°½ÈÍ±••À¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á	•™Õ‘‘±”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q}MA=I}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}Y=1Q}IM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`Y=1PIM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àA¥­…¡Ô…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰A…É…±åé•Ì½ÁÁ½¹•¹ÑÌ¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áY½±ÑÉ…Í °(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1ei}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}=1}IUM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`=1IUM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à5•½ÝÑ …ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰½¹™ÕÍ•Ì…¹•…É¹Ìµ½¹•ä¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á½±‘IÕÍ °(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=9UM}Ae}e}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}!%}MQI%-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`!$MQI%-ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à5…¡…µÀ…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰	½½ÍÑÌÉ¥Ñ¥…°µ¡¥ÐÉ…Ñ¥¼¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á¡¥MÑÉ¥­”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I%Q}A1UM}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}QII=It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`QII=Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à•¹…È…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰AÉ•Ù•¹ÑÌ™½•Ì™É½´•Í…Á¥¹œ¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áQ•ÉÉ½È°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AIY9Q}MA}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}=5}	UIMQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`=4	UIMPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à-¥¹±•È…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰!…ÉÍ¡±ä±½Ý•ÉÌ™½”ÌMÁ••¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á½…µ	ÕÉÍÐ°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1=]I}MA|É}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}IM=99t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`IM=99ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à1…ÁÉ…Ì…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰I•‘Õ•Ì‘…µ…”™½È€ÔÑÕÉ¹Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áI•Í½¹…¹”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}UI=I}Y%0°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}U1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`U1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à•Ù•”…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰%¹™…ÑÕ…Ñ•Ì½ÁÁ½¹•¹ÑÌ¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áÕ‘‘±”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%9QUQ}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}IA19%M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`IA19%M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àM¹½É±…à…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰I•ÍÑ½É•Ì•…Ñ•¸	•ÉÉ¥•Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áI•Á±•¹¥Í °(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Ie1}	II%L°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}51==It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`51==Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à…É‰½‘½È…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰A½¥Í½¹Ì½ÁÁ½¹•¹ÑÌ¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á5…±½‘½È°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}A=%M=9}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}51Q=]9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`51Q=]8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à5•±µ•Ñ…°…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰AÉ•Ù•¹ÑÌÉ•Á•…Ðµ½Ù”ÕÍ”¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á5•±Ñ‘½Ý¸°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Q=I59Q}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}IU5}M=1=t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`IU4M=1<ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àI¥±±…‰½½´…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰%¹½É•ÌÑ…É•ÐÌ…‰¥±¥Ñ¥•Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ‰¥±¥Ñä€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áÉÕµM½±¼°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%a}A=]H°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}%I	11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`%I	10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à¥¹‘•É…”…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰%¹½É•ÌÑ…É•ÐÌ…‰¥±¥Ñ¥•Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ‰¥±¥Ñä€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á¥É•‰…±°°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%a}A=]H°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}!eI=M9%At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`!eI=M9%Aˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à%¹Ñ•±•½¸…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰%¹½É•ÌÑ…É•ÐÌ…‰¥±¥Ñ¥•Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹¥¹½É•ÍQ…É•Ñ‰¥±¥Ñä€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á!å‘É½Í¹¥Á”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%a}A=]H°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}]%9}It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`]%9Iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à½ÉÙ¥­¹¥¡Ð…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰I•µ½Ù•Ì½ÁÁ½¹•¹ÐÍÉ••¹Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á]¥¹‘I…”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}IY%QMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`IY%QLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à=É‰••Ñ±”…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰¡…¹•ÌÉ…Ù¥Ñä™½È€ÔÑÕÉ¹Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áÉ…Ù¥Ñ…Ì°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}IY%Qd°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}MQ=9MUIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`MQ=9MUIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àÉ•‘¹…Ü…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰M…ÑÑ•ÉÌÍ¡…ÉÀÉ½­Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áMÑ½¹•ÍÕÉ”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MQ1Q!}I=,°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}Y=11%Q!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`Y=11%Q ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à½…±½ÍÍ…°…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰…µ…•Ì™½È€ÐÑÕÉ¹Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áY½±…±¥Ñ °(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Y=11%Q °(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}QIQ9MMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`QIQ9MLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à±…ÁÁ±”…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰1½Ý•ÉÌ™½”Ì•Ù…Í¥Ù•¹•ÍÌ¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áQ…ÉÑ¹•ÍÌ°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1=]I}YM%Y9MM}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}M]Q9MMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`M]Q9MLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àÁÁ±•ÑÕ¸…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰!•…±Ì…±±äÍÑ…ÑÕÌ½¹‘¥Ñ¥½¹Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áMÝ••Ñ¹•ÍÌ°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}I=5Q!IAd°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}M9	1MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`M9	1MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àM…¹‘…½¹‘„…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰QÉ…ÁÌ™½•Ì¥¸„Í…¹‘ÍÑ½É´¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áM…¹‘‰±…ÍÐ°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}M9	1MQ}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}MQU9}M!=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`MQU8M!=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àQ½áÑÉ¥¥Ñä…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰A½¥Í½¹Ì½ÈÁ…É…±åé•Ì™½•Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áMÑÕ¹M¡½¬°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}A=%M=9}AI1ei}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}9Q%I9=t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`9Q%I9<ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à•¹Ñ¥Í­½É …ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰QÉ…ÁÌ™½•Ì¥¸™±…µ•Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á•¹Ñ¥™•É¹¼°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}%I}MA%9}M%°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}M5%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`M5%Qˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à!…ÑÑ•É•¹”…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰½¹™ÕÍ•Ì½ÁÁ½¹•¹ÑÌ¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áMµ¥Ñ”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}=9UM}M%°(€€€€€€€ô¤°(€€€ô°(((€€€m5=Y}}5a}M9==it€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`M9==iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àÉ¥µµÍ¹…É°…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰1Õ±±Ì™½•Ì¥¹Ñ¼Í±••À¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áM¹½½é”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}e]9}=°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}%91t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`%91ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à±É•µ¥”…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰!•…±Ì…±±ä!@¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á¥¹…±”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}!1}Q4°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}MQ1MUIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`MQ1MUIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…à½ÁÁ•É…©… …ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰M…ÑÑ•ÉÌÍ¡…ÉÀÍÁ¥­•Ì¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áMÑ••±ÍÕÉ”°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MQ1MUI°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}A1Q%=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`A1Q%=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰µµ…àÕÉ…±Õ‘½¸…ÑÑ…¬¹q¸ˆ(€€€€€€€€€€€€‰I•‘Õ•ÌÑ…É•ÐÌA@¸ˆ¤°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á•Á±•Ñ¥½¸°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA%Q°(€€€€€€€ô¤°(€€€ô°((€€€m5=Y}}5a}=9}	1=]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`=9	1=\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ5…á=¹•	±½Ý•ÍÉ¥ÁÑ¥½¸°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…á=¹•	±½Ü°(€€€ô°((€€€m5=Y}}5a}IA%}1=]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰µ5`IA%1=\ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ôÍ5…á=¹•	±½Ý•ÍÉ¥ÁÑ¥½¸°€€€€¼½9%4Q=<(€€€€€€€€¹•™™•Ð€ôQ}5a}5=Y°(€€€€€€€€¹Á½Ý•È€ô€ÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…áI…Á¥‘±½Ü°(€€€ô°(€€€€¼¼A½¯¥µ½¸%¹™¥¹¥Ñäµ½Ù•ÌÁ½ÉÑ•™½ÈA½¯¥µ½¸)½¡Ñ¼I•±¥Ì¸(€€€m5=Y}AIMMUI%it€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰AIMMUI%iˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½µÁÉ•ÍÍ•Ì¥ÑÌÉ½­ä‰½‘äÑ½q¸ˆ(€€€€€€€€€€€€‰Í¡…ÉÁ±äÉ…¥Í”MÀ¸•˜¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MA%1}9M}UA|È°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}µ¹•Í¥„°(€€€ô°((€€€m5=Y}Y9=5}M]%At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Y9=4M]%Aˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰M±…Í¡•ÌÑ¡”Ñ…É•ÐÝ¥Ñ …q¸ˆ(€€€€€€€€€€€€‰Ù•¹½´µ½…Ñ•ÍÑÉ¥­”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}A=%M=8°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½¥Í½¹)…ˆ°(€€€ô°((€€€m5=Y}Y9%M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Y9%M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰	•½µ•Ì¹•…É±ä¥¹Ù¥Í¥‰±”Ñ½q¸ˆ(€€€€€€€€€€€€‰Í¡…ÉÁ±äÉ…¥Í”•Ù…Í¥Ù•¹•ÍÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}YM%=9}UA|È°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½Õ‰±•Q•…´°(€€€ô°((€€€m5=Y}	=9}M]At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	=9M]@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰MÝ••ÁÌ„¡Õ”‰½¹”…É½ÍÍq¸ˆ(€€€€€€€€€€€€‰‰½Ñ ½ÁÁ½Í¥¹œA½¯¥µ½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	½¹•µ•É…¹œ°(€€€ô°((€€€m5=Y}	I%9}Iit€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	I%8Iiˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Éå½­¥¹•Í¥ÌÍÑÉ¥­•ÌÑ¡”™½”¹q¸ˆ(€€€€€€€€€€€€‰%Ðµ…ä™É••é”Ñ¡”Ñ…É•Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}Ii°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍå‰•…´°(€€€ô°((€€€m5=Y}-	1=]t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰-	1=\„ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰áÁ±½‘•Ìì±•…Ù•ÌMÁ¥­•Íq¸ˆ(€€€€€€€€€€€€‰…¹Q½á¥ŒMÁ¥­•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M1MM}°(€€€€€€€€¹Á½Ý•È€ô€ÄÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹•áÁ±½Í¥½¸€ôQIU°(€€€€€€€€¹Á…É•¹Ñ…±	½¹‘	…¹¹•€ôQIU°(€€€€€€€€¹‘…µÁ	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}áÁ±½Í¥½¸°(€€€ô°((€€€€¼¼U¹¥ÅÕ”±•ÑÉ¥ŒµÑåÁ”•áÁ±½Í¥½¸™½ÈÑ¡”A½Ý•ÈA±…¹ÐÌÍ¡¥¹ä±•ÑÉ½‘”¸(€€€€¼¼-…‰±½Ý™¥Í É•Ñ…¥¹Ì¥ÑÌ½É¥¥¹…°MÑ••°µÑåÁ”-…‰±½Ü„Õ¹¡…¹•¸(€€€m5=Y}-	==5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰-	==4„ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰…¥¹ÑÌìÍ•ÑÌMÁ¥­•Ì½É½­Ì¹q¸ˆ(€€€€€€€€€€€€‰A…É…±åé•ÌÍÕÉÙ¥Ù½ÉÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M1MM}°(€€€€€€€€¹Á½Ý•È€ô€ÈÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1QI%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}=M}9}11d°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹•áÁ±½Í¥½¸€ôQIU°(€€€€€€€€¹Á…É•¹Ñ…±	½¹‘	…¹¹•€ôQIU°(€€€€€€€€¹‘…µÁ	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}AI1eM%L°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}áÁ±½Í¥½¸°(€€€ô°((€€€m5=Y}=M5%}Iet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=M5%Idˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰½¹•¹ÑÉ…Ñ•…ÍÑÉ…°‰•…´¹q¸ˆ(€€€€€€€€€€€€‰%Ðµ…äµ…­”Ñ¡”™½”™±¥¹ ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹ÁÕ±Í•5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÄÔ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5½½¹‰±…ÍÐ°(€€€ô°((€€€m5=Y})}YUt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%+ µYTˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÁÍå¡¥Œ•¡¼ÍÑÉ¥­•ÌÝ¥Ñ¡q¸ˆ(€€€€€€€€€€€€‰…¸…ÑÑ…¬Ñ¡…Ð¹•Ù•Èµ¥ÍÍ•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÕÑÕÉ•M¥¡Ð°(€€€ô°((€€€m5=Y}MQ}MQ	t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQMQˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰‰ÉÕÑ…°¡½É¸Ñ¡ÉÕÍÐÑ¡…Ðµ…åq¹µ…­”Ñ¡”Ñ…É•Ð™±¥¹ ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °€¹¡…¹”€ô€ÈÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5•…¡½É¸°(€€€ô°((€€€m5=Y}%I=9}Q5AMQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%I=8Q5AMPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰5•Ñ…°Ý¥¹Ì…ÉÙ”Ñ¡”™½”¸%Ñq¹µ…ä±½Ý•ÈÑ¡”Ñ…É•ÐÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°€¹¡…¹”€ô€ÈÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ••±]¥¹œ°(€€€ô°((€€€m5=Y}Q%1MA%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q%1MA%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰ÍÁ¥¹¹¥¹œÑ…¥°ÍÑÉ¥­”Ñ¡…Ñq¹•ÑÌÍÑÉ½¹•È…¹É…¥Í•ÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=11=UP°(€€€€€€€€¹Á½Ý•È€ô€ÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹¥¹ÍÑÉÕÑ	…¹¹•€ôQIU°(€€€€€€€€¹Á…É•¹Ñ…±	½¹‘	…¹¹•€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}A1UM|Ä°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€€€€€€¹¡…¹”€ô€ÄÀÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}I½±±½ÕÐ°(€€€ô°((€€€m5=Y}1eA!%}!=IUMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1eA!%!=IULˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¸…¹¥•¹Ð¡½ÉÕÌ±•…ÉÍq¹Ý•…­¹•ÍÌ‰•™½É”ÍÑÉ¥­¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍå¡¥Œ°(€€€ô°((€€€m5=Y}A!=9%a}!e59t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A!=9%`!e58ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰Í…É•™±…µ”µÍ½¹œÑ¡…Ñq¹É•ÍÑ½É•Ì½¹”ÅÕ…ÉÑ•Èµ…à!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Í½Õ¹‘5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M…É•‘¥É”°(€€€ô°(((€€€m5=Y}=IQIMM}IUM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=IQIMLIUM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÉÕÍ¡•ÌÝ¥Ñ ¡…É‘•¹•…Éµ½È¹q¸ˆ(€€€€€€€€€€€€‰UÍ•ÌÑ¡”ÕÍ•ÈÌ•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	=e}AIML°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	½‘åAÉ•ÍÌ°(€€€ô°((€€€m5=Y}M%}QUM-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M%QUM,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰ÉÕÍ¡¥¹œÑÕÍ¬¡…É”Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰Í…ÑÑ•ÉÌÁ½¥¹Ñ•ÍÑ½¹•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQ=9}a°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹Í¡••É½É•=Ù•ÉÉ¥‘”€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ½¹•á”°(€€€ô°((€€€m5=Y}QI91}	1==5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QI90	1==4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰É…¥¹Ì±¥™”Ý¥Ñ …¹¥•¹Ð±¥¡Ð¹q¸ˆ(€€€€€€€€€€€€‰!•…±Ì¡…±˜Ñ¡”‘…µ…”‘•…±Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹¡•…±¥¹5½Ù”€ô	}!1}	1=-%9€øô9|Ø°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5½½¹‰±…ÍÐ°(€€€ô°((€€€m5=Y}55}I%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰55I%Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰I¥ÁÌ½Á•¸„‰ÕÉ¹¥¹œ™¥ÍÍÕÉ”¹q¸ˆ(€€€€€€€€€€€€‰%Ðµ…ä‰ÕÉ¸Ñ¡”Ñ…É•Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}…ÉÑ¡A½Ý•È°(€€€ô°((€€€m5=Y}Q!}I=11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q I=10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 (€€€€€€€€€€€€‰Í…Ù…”É½±±¥¹œ‰¥Ñ”Ñ¡…Ñq¸ˆ(€€€€€€€€€€€€‰µ…äµ…­”Ñ¡”Ñ…É•Ð™±¥¹ ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰¥Ñ¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °(€€€€€€€€€€€€¹¡…¹”€ô€ÈÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÅÕ…Q…¥°°(€€€ô°((€€€€¼¼ÕÑ¡•¹Ñ¥ŒAI0µ½Ù”•™™•ÑÌì…‘…ÁÑ•½¹±äÝ¡•É”Ñ¡”AIT•¹¥¹”É•ÅÕ¥É•Ì¥Ð¸(€€€m5=Y}5	I}	1t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5	H	1ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¡¥ µÉ¥Ð±•…˜Í±…Í ¹q¹5…ä±½Ý•È™½”Ì•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹É¥Ñ¥…±!¥ÑMÑ…”€ô€Ä°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°€¹¡…¹”€ô€ÈÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}1•…™	±…‘”°(€€€ô°((€€€m5=Y}MU9}I%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MU8I%Qˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰‰±…é¥¹œ•É•µ½¹¥…°‰±½Ü¹q¹5…äÉ…¥Í”ÕÍ•ÈÌMÁ••¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}A1UM|Ä°€¹Í•±˜€ôQIU°€¹¡…¹”€ô€ÌÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	±…é•-¥¬°(€€€ô°((€€€m5=Y}QQ=9%}Q%t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QQ=9%Q%ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰É…Í¡¥¹œÑ¥‘…°ÍÑÉ¥­”¹q¹5…ä±½Ý•ÈÑ…É•ÐÌ•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}]QH°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°€¹¡…¹”€ô€ÌÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÅÕ…Q…¥°°(€€€ô°((€€€m5=Y}A=!}IM!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A= IM ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰‘•Ù…ÍÑ…Ñ¥¹œ…¹¥•¹Ð¡¥Ð¹q¹5…ä±½Ý•ÈÑ…É•ÐÌ•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°€¹¡…¹”€ô€ÈÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}MÑ½¹•‘”°(€€€ô°((€€€m5=Y}I1%}]%M!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I1%]%M ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰I•±•…Í•Ì„Á½Ý•É™Õ°‰ÕÉÍÑq¹½˜…¹¥•¹Ð™…¥Éä•¹•Éä¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5½½¹‰±…ÍÐ°(€€€ô°((€€€m5=Y}9}	1==5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰8	1==4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰Í…É•‰±½½´ÍÑÉ¥­•ÌÑ¡•q¹™½”¸5…ä…ÕÍ”Á½¥Í½¹¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}A=%M=8°€¹¡…¹”€ô€ÌÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¹•Éå	…±°°(€€€ô°((€€€m5=Y}M=I!]%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M=I ]%9Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰M½É¡¥¹œÝ¥¹ÌÍÑÉ¥­”Ñ¡•q¹™½”¸5…ä…ÕÍ”„‰ÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	UI8°€¹¡…¹”€ô€ÈÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	É…Ù•	¥É°(€€€ô°((€€€m5=Y}	MQ%=9}99=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	MQ%=899=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰µ¥¡ÑäÍÑ••°‰±…ÍÐÑ¡…Ñq¹µ…ä‰½½ÍÐÕÍ•ÈÌ•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}}A1UM|Ä°€¹Í•±˜€ôQIU°€¹¡…¹”€ô€ÌÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…Í¡…¹¹½¸°(€€€ô°((€€€m5=Y}I%}=t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%=ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰M¡É½Õ‘ÌÑ¡”™¥•±¥¸™½q¹™½È•¥¡ÐÑÕÉ¹Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}]Q!H°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}%1°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹Ý•…Ñ¡•ÉQåÁ”€ô	QQ1}]Q!I}=ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5¥ÍÐ°(€€€ô°(((€€€€¼¼AITè•á…ÐAI0Í¥¹…ÑÕÉ•Ì°…‘…ÁÑ•Ñ¼¹…Ñ¥Ù”A)H•™™•ÐÍÑÉÕÑÌ¸(€€€m5=Y}M%M5%}M15t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M%M5%M14ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰M¡…ÑÑ•ÉÌÑ¡”•…ÉÑ ¹q¹Q¡”ÕÍ•ÈÑ…­•ÌÉ•½¥°¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}I=%0°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹É•½¥±A•É•¹Ñ…”€ô€ÌÌô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½Õ‰±•‘”°(€€€ô°((€€€m5=Y}M=%1}I%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M=%0I%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰É…¥¹ÌÁ½Ý•ÈÑ¡É½Õ Í½¥°¹q¹!•…±Ì¡…±˜‘…µ…”‘•…±Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥…É…¥¸°(€€€ô°((€€€m5=Y}	IY=t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	IY<ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰	½½ÍÑ•¥˜‰ÕÉ¹•±q¹Á½¥Í½¹•½ÈÁ…É…±åé•¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}……‘”°(€€€ô°((€€€m5=Y}I%9}M=U1Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%9M=U1Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¡½ÍÑ±äÍÕÉ”Ñ¡…Ñq¹Í¡…ÉÁ±ä‘É½ÁÌMÀ¸Ñ¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}Q-}5%9UM|È°(€€€€€€€€€€€€¹Í•±˜€ôQIU°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}]¥±±=]¥ÍÀ°(€€€ô°((€€€m5=Y}	Q=]9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰	Q=]8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰‘…É¬™±ÕÉÉäÑ¡…Ñq¹¡¥ÑÌÑÝ¼Ñ¼™¥Ù”Ñ¥µ•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹µÕ±Ñ¥!¥Ð€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	•…ÑUÀ°(€€€ô°((€€€m5=Y}Q-}1%!Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Q-1%!Pˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰MÑÉ¥­•ÌÝ¥Ñ Ý¥¹±q¹Ñ¡•¸ÍÝ¥Ñ¡•ÌÕÍ•È½ÕÐ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%Q}MA°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}1e%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹Ý¥¹‘5½Ù”€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}UQÕÉ¸°(€€€ô°((€€€m5=Y}%9MQ}%5AQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%9MP%5APˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¡…É‰ÕœÁÕ¹ Ñ¡…Ñq¹µ…ä±½Ý•È•™•¹Í”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹ÁÕ¹¡¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}}5%9UM|Ä°(€€€€€€€€€€€€¹¡…¹”€ô€ÌÀ°(€€€€€€€ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}½Õ‰±•‘”°(€€€ô°((€€€€¼¼AIT	±••‘¥¹œµ•¹…‰±•½É¥¥¹…°AI0µ½Ù”•™™•ÑÌ¸(€€€m5=Y}I%A}9}QIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%@9QHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰I¥ÁÌÑ¡”Ñ…É•Ð°±½Ý•É¥¹œ¥ÑÌMÁ••…¹Á½ÍÍ¥‰±ä…ÕÍ¥¹œ‰±••‘¥¹œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°€¹Á½Ý•È€ô€ÄÄÀ°€¹ÑåÁ”€ôQeA}I,°€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€Ô°€¹Ñ…É•Ð€ôQIQ}M1Q°€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°€¹µ…­•Í½¹Ñ…Ð€ôQIU°€¹‰¥Ñ¥¹5½Ù”€ôQIU°(€€€€€€€€¹…¹ÑUÍ•QÝ¥”€ôQIU°€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL (€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}5%9UM|Ä°€¹¡…¹”€ô€ÄÀÀô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÔÀô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÉÕ¹ °(€€€ô°((€€€m5=Y}%I=9}9Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%I=89Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰MÑ••°™…¹ÌÍµ…Í¡q¹Ñ¡É½Õ ‰…ÉÉ¥•ÉÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰¥Ñ¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì(€€€€€€€€€€€€¹µ½Ù•™™•Ð€ô5=Y}Q}	I-}MI8°(€€€€€€€€€€€€¹ÁÉ•ÑÑ…­™™•Ð€ôQIU°(€€€€€€€ô°(€€€€€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	É¥­	É•…¬°(€€€ô°(((€€€€¼¼AIT¥µÁ½ÉÑ•µ½Ù•Ìè¥¹‘•á•½É¥¥¹…°‘½¹½Èµ•Ñ…‘…Ñ„¸Q¡”…É¡¥Ù•¥¹Ñ•É…Ñ¥½¸(€€€€¼¼¡•­±¥ÍÐ‘¥ÍÑ¥¹Õ¥Í¡•Ì•á…Ð½É”µ•¡…¹¥Ì™É½´ÁÉ½Ù¥Í¥½¹…°Í•½¹‘…Éä•™™•ÑÌ¸(€€€€¼¼…ÕÑ¡•¹Ñ¥Œè•Ù½‰½½ÍÐ¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}Y=	==MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Y=	==MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰	½½ÍÑÌ…±°™¥Ù”ÍÑ…ÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}AIU}Y=	==MP°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}9=I50°(€€€€€€€€¹…ÕÉ…ä€ô€À°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}UMH°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€´È°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹¥¹½É•ÍAÉ½Ñ•Ð€ôQIU°(€€€€€€€€¹Í¹…Ñ¡™™•Ñ•€ôQIU°(€€€€€€€€¹µ¥ÉÉ½É5½Ù•	…¹¹•€ôQIU°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}áÑÉ•µ•Ù½‰½½ÍÐ°(€€€ô°((€€€€¼¼Á…ÉÑ¥…°è1½Ù•±ä	¥Ñ”¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}1=Y1e}	%Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1=Y1d	%Qˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰‰¥Ñ”Ñ¡…Ðµ…ä¡…É´¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}%Id°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰¥Ñ¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL (€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}AIU}%9QUQ%=8°€¹¡…¹”€ô€ÄÀ°ô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	¥Ñ”°(€€€ô°((€€€€¼¼Á…ÉÑ¥…°èM¡…‘½Ü…¹Ì¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}M!=]}9Mt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!=\9Lˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰…¹ÌÝ¥Ñ „ÕÉÍ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹‰¥Ñ¥¹5½Ù”€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL (€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}AIU}UIM°€¹¡…¹”€ô€ÄÀ°ô°(€€€€€€€€€€€ì€¹µ½Ù•™™•Ð€ô5=Y}Q}	1°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	¥Ñ”°(€€€ô°((€€€€¼¼¹Õµ•É¥Œè¹ÉäMÝ…É´¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}9Ie}M]I5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9IdM]I4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¸…¹Éä‰ÕœÍÝ…É´¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}	U°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}	Õ	Õéè°(€€€ô°((€€€€¼¼¹Õµ•É¥Œè¡É½µ”	…±°¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}!I=5}	11t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰!I=5	10ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰!ÕÉ±Ì„¡É½µ”‰…±°¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}±…Í¡…¹¹½¸°(€€€ô°((€€€€¼¼¹Õµ•É¥Œè½É¹•È¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}=I9It€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰=I9Hˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰½É¹•ÉÌÑ¡”Ñ…É•Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€àÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}ÉÕ¹ °(€€€ô°((€€€€¼¼¹Õµ•É¥Œè…É¬I•Í½±Ù”¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}I-}IM=1Yt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I,IM=1Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰…É¬•¹•Éä•ÉÕÁÑÌ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}…É­AÕ±Í”°(€€€ô°((€€€€¼¼¹Õµ•É¥Œè•…‘±äQ½á¥¸¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}1e}Q=a%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1dQ=a%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰½¹•¹ÑÉ…Ñ•Ñ½á¥¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÜÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M±Õ‘•	½µˆ°(€€€ô°((€€€€¼¼¹Õµ•É¥ŒèÉ¥µ•‰ÕÍÑ•È¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}I%5	UMQIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰I%5	UMQHˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰A½Ý•É™Õ°É¥µ”ÍÑÉ¥­•Ì¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÌÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Õ¹­M¡½Ð°(€€€ô°((€€€€¼¼ÍÑ…ÑÕÍ}½µÁ…Ðè%¹™•Ñ¥½¸¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}%9Q%=9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰%9Q%=8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰MÁÉ•…‘Ì¥¹™•Ñ¥½¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}9=9}Y=1Q%1}MQQUL°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹¹½¹Y½±…Ñ¥±•MÑ…ÑÕÌ€ô5=Y}Q}A=%M=8ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½¥Í½¹…Ì°(€€€ô°((€€€€¼¼ÍÑ…ÑÕÍ}½µÁ…Ðè1¥™”É…¥¸¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}1%}I%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰1%I%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰É…¥¹ÌÑ…É•Ð!@¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÐÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥…É…¥¸°(€€€ô°((€€€€¼¼¹Õµ•É¥Œè5•Ñ…°	±…ÍÐ¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}5Q1}	1MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5Q0	1MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰™¥•É”µ•Ñ…°ÍÑÉ¥­”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}%É½¹!•…°(€€€ô°((€€€€¼¼ÍÑ…ÑÕÍ}½µÁ…Ðè9•ÕÉ½Ñ½á¥¸¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}9UI=Q=a%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰9UI=Q=a%8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰Q½á¥Œ¹•ÉÙ”…•¹Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}9=9}Y=1Q%1}MQQUL°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹¹½¹Y½±…Ñ¥±•MÑ…ÑÕÌ€ô5=Y}Q}Q=a%ô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Q½á¥Œ°(€€€ô°((€€€€¼¼¹Õµ•É¥ŒèA½ÍÍ•ÍÌ¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}A=MMMMt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰A=MMMLˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¡…Õ¹Ñ¥¹œ…ÍÍ…Õ±Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÈÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÜÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡…‘½Ý	…±°°(€€€ô°((€€€€¼¼¹Õµ•É¥ŒèEÕ¥¬QÕÉ¸¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}EU%-}QUI9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰EU%,QUI8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰Í¡…ÉÀ‘É…½¸ÑÕÉ¸¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=8°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}É…½¹±…Ü°(€€€ô°((€€€€¼¼ÍÑ…ÑÕÍ}½µÁ…ÐèM¡…‘½Ü±…µÀ¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}M!=]}15At€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!=\15@ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¡½ÍÑ±ä‰¥¹‘¥¹œ…ÑÑ…¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡…‘½Ý±…Ü°(€€€ô°((€€€€¼¼¹Õµ•É¥ŒèMµ½ÍÉ••¸¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}M5=MI9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M5=MI8ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰‰±…ÍÐ½˜Ñ¡¥¬Íµ½œ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÈÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M±Õ‘”°(€€€ô°((€€€€¼¼¹Õµ•É¥ŒèM½Õ±Í¡½¬¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}M=U1M!=-t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M=U1M!=,ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¡½ÍÑ±ä‰½‘ä‰±½Ü¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡…‘½ÝAÕ¹ °(€€€ô°((€€€€¼¼ÍÑ…ÑÕÍ}½µÁ…ÐèMÑ¥¹¬MÁÉ…ä¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}MQ%9-}MAIet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MQ%9,MAIdˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰‰±¥¹‘¥¹œÍÑ•¹ ¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}UIe}=]8°(€€€€€€€€¹Á½Ý•È€ô€À°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÈÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MQQUL°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}Mµ½­•ÍÉ••¸°(€€€ô°((€€€€¼¼¹Õµ•É¥ŒèY•¹•…¹”¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}Y99t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Y99ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰I•Ñ…±¥…Ñ•ÌÝ¥Ñ ÍÁ¥Ñ”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I,°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A…å‰…¬°(€€€ô°((€€€€¼¼¹Õµ•É¥ŒèY¥±”Y•¹½´¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}Y%1}Y9=5t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰Y%1Y9=4ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰A½Ñ•¹ÐÙ•¹½´ÍÑÉ¥­”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€äÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}A=%M=8°(€€€€€€€€¹…ÕÉ…ä€ô€äÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}A½¥Í½¹)…ˆ°(€€€ô°((€€€€¼¼…ÁÁÉ½Ù•‘}™…±±‰…¬èÍÍ¥µ¥±…Ñ”¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}MM%5%1Qt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MM%5%1Qˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰‰Í½É‰ÌÑ¡”Ñ…É•Ð¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}	M=I°(€€€€€€€€¹Á½Ý•È€ô€ÜÔ°(€€€€€€€€¹ÑåÁ”€ôQeA}IML°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…ÉÕµ•¹Ð€ôì€¹…‰Í½É‰A•É•¹Ñ…”€ô€ÔÀô°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}¥…É…¥¸°(€€€ô°((€€€€¼¼…ÁÁÉ½Ù•‘}™…±±‰…¬èMÁ…É­±¥¹Í­ä¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}MAI-1%9M-et€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MAI-1%9M-dˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰áÁ±½Í¥Ù”™¥É”Á½Ý•È¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}5a}!A|ÔÁ}I=%0°(€€€€€€€€¹Á½Ý•È€ô€ÈÀÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%I°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5¥¹‘	±½Ý¸°(€€€ô°((€€€€¼¼…ÁÁÉ½Ù•‘}™…±±‰…¬èMÕÁ•È±¥Ñ ¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}MUAI}1%Q!t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰MUAH1%Q ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¸Õ¹ÍÑ…‰±”ÍÑÉ¥­”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÈÔÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€Ä°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍåÍÑÉ¥­”°(€€€ô°((€€€€¼¼…ÁÁÉ½Ù•‘}™…±±‰…¬èQ•ÉÉ½È]…Ù”¸M•”‘½Ì½AIU}UMQ=5}5=Y}%9QIQ%=9}	-1=¹µ(€€€m5=Y}QII=I}]Yt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰QII=H]Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰Ñ•ÉÉ¥™å¥¹œÝ…Ù”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ÄÄÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€àÔ°(€€€€€€€€¹ÁÀ€ô€Ô°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}M1Q°(€€€€€€€€¹ÁÉ¥½É¥Ñä€ô€À°(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¡…‘½Ý	…±°°(€€€ô°((€€€€¼¼AIT™É•”‘½Õ‰±•ÌÑÕÑ½Èµ½Ù•Ì¸Ù•Éäµ½Ù”‘…µ…•Ì	=Q ½ÁÁ½Í¥¹œÍ±½ÑÌ¸(€€€m5=Y}M!=-]Y}%MQt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰M!=-]Y%MPˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰MÑÉ¥­•Ì‰½Ñ ™½•Ì¸!…Ì…q¸ÄÀ”™±¥¹ ¡…¹”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}%!Q%9°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹µ…­•Í½¹Ñ…Ð€ôQIU°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}1%9 °€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5…¡AÕ¹ °(€€€ô°(€€€m5=Y}U1Q1%9t€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰U1Q1%9ˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰!¥ÑÌ‰½Ñ ™½•Ì…¹Í•ÑÍq¹MÑ•…±Ñ I½¬¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}MQ=9}a°(€€€€€€€€¹Á½Ý•È€ô€ÜÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}I=U9°(€€€€€€€€¹…ÕÉ…ä€ô€äÔ°(€€€€€€€€¹ÁÀ€ô€ÄÀ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}…ÉÑ¡ÅÕ…­”°(€€€ô°(€€€m5=Y}]I%Q!}Iet€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰]I%Q Idˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰¡½ÍÑ±äÉä¡¥ÑÌ‰½Ñ ¹q¹5…ä¥¹™±¥ÐH¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}!=MP°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}H°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}M¹…É°°(€€€ô°(€€€m5=Y}5Q1}	IIt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5Q0	IIˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰!¥ÑÌ‰½Ñ ™½•Ì…¹Í…ÑÑ•ÉÍq¹MÁ¥­•Ì½¸Ñ¡•¥ÈÍ¥‘”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}M1MM}°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}MQ0°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}A!eM%0°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}5•Ñ…±±…Ü°(€€€ô°(€€€m5=Y}5%9]Yt€ô(€€€ì(€€€€€€€€¹¹…µ”€ô=5A=U9}MQI%9 ‰5%9]Yˆ¤°(€€€€€€€€¹‘•ÍÉ¥ÁÑ¥½¸€ô=5A=U9}MQI%9 ‰!¥ÑÌ‰½Ñ ™½•Ì¸5…ä±½Ý•Éq¹MÀ¸•˜‰ä½¹”ÍÑ…”¸ˆ¤°(€€€€€€€€¹•™™•Ð€ôQ}!%P°(€€€€€€€€¹Á½Ý•È€ô€ØÀ°(€€€€€€€€¹ÑåÁ”€ôQeA}AMe!%°(€€€€€€€€¹…ÕÉ…ä€ô€ÄÀÀ°(€€€€€€€€¹ÁÀ€ô€ÄÔ°(€€€€€€€€¹Ñ…É•Ð€ôQIQ}	=Q °(€€€€€€€€¹…Ñ•½Éä€ô5}Q=Ie}MA%0°(€€€€€€€€¹…‘‘¥Ñ¥½¹…±™™•ÑÌ€ô%Q%=91}QL¡ì€¹µ½Ù•™™•Ð€ô5=Y}Q}MA}}5%9UM|Ä°€¹¡…¹”€ô€ÄÀ°ô¤°(€€€€€€€€¹‰…ÑÑ±•¹¥µMÉ¥ÁÐ€ô	…ÑÑ±•¹¥µ5½Ù•}AÍå¡¥Œ°(€€€ô°()ôì(