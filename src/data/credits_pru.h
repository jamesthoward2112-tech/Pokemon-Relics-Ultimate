// PRU-original on-screen credits, displayed in every HNS ending.
// The full inherited Heart & Soul credits remain in credits_hns.h
// and existing repository CREDITS.md; provenance notes in docs/PRU_CREDITS.md.
// Keep GBA lines short and five slots per page for the existing renderer.

enum
{
    PAGE_PRU_01,
    PAGE_PRU_02,
    PAGE_PRU_03,
    PAGE_PRU_04,
    PAGE_PRU_05,
    PAGE_PRU_06,
    PAGE_PRU_07,
    PAGE_PRU_08,
    PAGE_PRU_09,
    PAGE_PRU_10,
    PAGE_PRU_11,
    PAGE_PRU_12,
    PAGE_PRU_13,
    PAGE_PRU_14,
    PAGE_PRU_15,
    PAGE_PRU_16,
    PAGE_PRU_17,
    PAGE_PRU_18,
    PAGE_PRU_19,
    PAGE_PRU_20,
    PAGE_PRU_21,
    PAGE_PRU_22,
    PAGE_PRU_23,
    PAGE_PRU_24,
    PAGE_PRU_25,
    PAGE_PRU_26,
    PAGE_PRU_27,
    PAGE_PRU_28,
    PAGE_PRU_29,
    PAGE_COUNT
};

#define ENTRIES_PER_PAGE 5

static const u8 sCreditsText_EmptyString[] = _("");
static const struct CreditsEntry sCreditsEntry_EmptyString = {0, FALSE, sCreditsText_EmptyString};

static const u8 sPRUCreditsText_0_0[] = _("POKéMON RELICS ULTIMATE");
static const struct CreditsEntry sPRUCreditsEntry_0_0 = {0, TRUE, sPRUCreditsText_0_0};
static const u8 sPRUCreditsText_0_1[] = _("A JOHTO & KANTO ADVENTURE");
static const struct CreditsEntry sPRUCreditsEntry_0_1 = {0, FALSE, sPRUCreditsText_0_1};
static const u8 sPRUCreditsText_0_2[] = _("450 POKéMON. ONE LEGACY.");
static const struct CreditsEntry sPRUCreditsEntry_0_2 = {0, FALSE, sPRUCreditsText_0_2};
static const u8 sPRUCreditsText_1_0[] = _("PROJECT LEAD");
static const struct CreditsEntry sPRUCreditsEntry_1_0 = {0, TRUE, sPRUCreditsText_1_0};
static const u8 sPRUCreditsText_1_1[] = _("JAMES HOWARD");
static const struct CreditsEntry sPRUCreditsEntry_1_1 = {0, FALSE, sPRUCreditsText_1_1};
static const u8 sPRUCreditsText_1_2[] = _("STORY & CREATIVE DIRECTION");
static const struct CreditsEntry sPRUCreditsEntry_1_2 = {0, FALSE, sPRUCreditsText_1_2};
static const u8 sPRUCreditsText_2_0[] = _("THE WORLD OF PRU");
static const struct CreditsEntry sPRUCreditsEntry_2_0 = {0, TRUE, sPRUCreditsText_2_0};
static const u8 sPRUCreditsText_2_1[] = _("RELICS HUNT & ELITE 20");
static const struct CreditsEntry sPRUCreditsEntry_2_1 = {0, FALSE, sPRUCreditsText_2_1};
static const u8 sPRUCreditsText_2_2[] = _("JOHTO, KANTO AND BEYOND");
static const struct CreditsEntry sPRUCreditsEntry_2_2 = {0, FALSE, sPRUCreditsText_2_2};
static const u8 sPRUCreditsText_3_0[] = _("GAMEPLAY & DESIGN");
static const struct CreditsEntry sPRUCreditsEntry_3_0 = {0, TRUE, sPRUCreditsText_3_0};
static const u8 sPRUCreditsText_3_1[] = _("RELIC EVOLUTIONS & MOVES");
static const struct CreditsEntry sPRUCreditsEntry_3_1 = {0, FALSE, sPRUCreditsText_3_1};
static const u8 sPRUCreditsText_3_2[] = _("BATTLES, QUESTS & EVENTS");
static const struct CreditsEntry sPRUCreditsEntry_3_2 = {0, FALSE, sPRUCreditsText_3_2};
static const u8 sPRUCreditsText_4_0[] = _("ENGINE FOUNDATIONS");
static const struct CreditsEntry sPRUCreditsEntry_4_0 = {0, TRUE, sPRUCreditsText_4_0};
static const u8 sPRUCreditsText_4_1[] = _("PRET / POKEEMERALD");
static const struct CreditsEntry sPRUCreditsEntry_4_1 = {0, FALSE, sPRUCreditsText_4_1};
static const u8 sPRUCreditsText_4_2[] = _("RH-HIDEOUT EXPANSION");
static const struct CreditsEntry sPRUCreditsEntry_4_2 = {0, FALSE, sPRUCreditsText_4_2};
static const u8 sPRUCreditsText_5_0[] = _("ENGINE CONTRIBUTORS");
static const struct CreditsEntry sPRUCreditsEntry_5_0 = {0, TRUE, sPRUCreditsText_5_0};
static const u8 sPRUCreditsText_5_1[] = _("POKEEMERALD-EXPANSION TEAM");
static const struct CreditsEntry sPRUCreditsEntry_5_1 = {0, FALSE, sPRUCreditsText_5_1};
static const u8 sPRUCreditsText_5_2[] = _("THANK YOU FOR THE ENGINE");
static const struct CreditsEntry sPRUCreditsEntry_5_2 = {0, FALSE, sPRUCreditsText_5_2};
static const u8 sPRUCreditsText_6_0[] = _("JOHTO & KANTO FOUNDATION");
static const struct CreditsEntry sPRUCreditsEntry_6_0 = {0, TRUE, sPRUCreditsText_6_0};
static const u8 sPRUCreditsText_6_1[] = _("POKéMON HEART & SOUL");
static const struct CreditsEntry sPRUCreditsEntry_6_1 = {0, FALSE, sPRUCreditsText_6_1};
static const u8 sPRUCreditsText_6_2[] = _("LIL DILL AND CONTRIBUTORS");
static const struct CreditsEntry sPRUCreditsEntry_6_2 = {0, FALSE, sPRUCreditsText_6_2};
static const u8 sPRUCreditsText_7_0[] = _("HEART & SOUL CONTRIBUTORS");
static const struct CreditsEntry sPRUCreditsEntry_7_0 = {0, TRUE, sPRUCreditsText_7_0};
static const u8 sPRUCreditsText_7_1[] = _("INFINITEBACON42");
static const struct CreditsEntry sPRUCreditsEntry_7_1 = {0, FALSE, sPRUCreditsText_7_1};
static const u8 sPRUCreditsText_7_2[] = _("EXCLSIOR / TIXOREBEL");
static const struct CreditsEntry sPRUCreditsEntry_7_2 = {0, FALSE, sPRUCreditsText_7_2};
static const u8 sPRUCreditsText_8_0[] = _("HEART & SOUL ART & MAPS");
static const struct CreditsEntry sPRUCreditsEntry_8_0 = {0, TRUE, sPRUCreditsText_8_0};
static const u8 sPRUCreditsText_8_1[] = _("KERTRA / CRYSTAL ADVANCE");
static const struct CreditsEntry sPRUCreditsEntry_8_1 = {0, FALSE, sPRUCreditsText_8_1};
static const u8 sPRUCreditsText_8_2[] = _("JOHTO REDRAWN TEAM");
static const struct CreditsEntry sPRUCreditsEntry_8_2 = {0, FALSE, sPRUCreditsText_8_2};
static const u8 sPRUCreditsText_9_0[] = _("GAMEPLAY INSPIRATION");
static const struct CreditsEntry sPRUCreditsEntry_9_0 = {0, TRUE, sPRUCreditsText_9_0};
static const u8 sPRUCreditsText_9_1[] = _("CRYSTAL LEGACY");
static const struct CreditsEntry sPRUCreditsEntry_9_1 = {0, FALSE, sPRUCreditsText_9_1};
static const u8 sPRUCreditsText_9_2[] = _("THE SMITH PLAYS");
static const struct CreditsEntry sPRUCreditsEntry_9_2 = {0, FALSE, sPRUCreditsText_9_2};
static const u8 sPRUCreditsText_10_0[] = _("RELIC SPRITE SOURCES");
static const struct CreditsEntry sPRUCreditsEntry_10_0 = {0, TRUE, sPRUCreditsText_10_0};
static const u8 sPRUCreditsText_10_1[] = _("POKéMON INFINITY");
static const struct CreditsEntry sPRUCreditsEntry_10_1 = {0, FALSE, sPRUCreditsText_10_1};
static const u8 sPRUCreditsText_10_2[] = _("COMMUNITY SPRITE ARTISTS");
static const struct CreditsEntry sPRUCreditsEntry_10_2 = {0, FALSE, sPRUCreditsText_10_2};
static const u8 sPRUCreditsText_11_0[] = _("ADDITIONAL SPRITE SOURCES");
static const struct CreditsEntry sPRUCreditsEntry_11_0 = {0, TRUE, sPRUCreditsText_11_0};
static const u8 sPRUCreditsText_11_1[] = _("POKéMON INSURGENCE");
static const struct CreditsEntry sPRUCreditsEntry_11_1 = {0, FALSE, sPRUCreditsText_11_1};
static const u8 sPRUCreditsText_11_2[] = _("DONOR ASSET CONTRIBUTORS");
static const struct CreditsEntry sPRUCreditsEntry_11_2 = {0, FALSE, sPRUCreditsText_11_2};
static const u8 sPRUCreditsText_12_0[] = _("SKARMET ARTWORK");
static const struct CreditsEntry sPRUCreditsEntry_12_0 = {0, TRUE, sPRUCreditsText_12_0};
static const u8 sPRUCreditsText_12_1[] = _("POKéMON TOURMALINE");
static const struct CreditsEntry sPRUCreditsEntry_12_1 = {0, FALSE, sPRUCreditsText_12_1};
static const u8 sPRUCreditsText_12_2[] = _("TDILOS & CONTRIBUTING ARTISTS");
static const struct CreditsEntry sPRUCreditsEntry_12_2 = {0, FALSE, sPRUCreditsText_12_2};
static const u8 sPRUCreditsText_13_0[] = _("BATTLE SCENERY");
static const struct CreditsEntry sPRUCreditsEntry_13_0 = {0, TRUE, sPRUCreditsText_13_0};
static const u8 sPRUCreditsText_13_1[] = _("POKéMON RHYTHM");
static const struct CreditsEntry sPRUCreditsEntry_13_1 = {0, FALSE, sPRUCreditsText_13_1};
static const u8 sPRUCreditsText_13_2[] = _("RHYTHM ART CONTRIBUTORS");
static const struct CreditsEntry sPRUCreditsEntry_13_2 = {0, FALSE, sPRUCreditsText_13_2};
static const u8 sPRUCreditsText_14_0[] = _("ROCK SHOP ART");
static const struct CreditsEntry sPRUCreditsEntry_14_0 = {0, TRUE, sPRUCreditsText_14_0};
static const u8 sPRUCreditsText_14_1[] = _("AZUL AGUA");
static const struct CreditsEntry sPRUCreditsEntry_14_1 = {0, FALSE, sPRUCreditsText_14_1};
static const u8 sPRUCreditsText_14_2[] = _("ORIGINAL DONOR ASSETS");
static const struct CreditsEntry sPRUCreditsEntry_14_2 = {0, FALSE, sPRUCreditsText_14_2};
static const u8 sPRUCreditsText_15_0[] = _("TRAINER ART SOURCES");
static const struct CreditsEntry sPRUCreditsEntry_15_0 = {0, TRUE, sPRUCreditsText_15_0};
static const u8 sPRUCreditsText_15_1[] = _("TEAM ROCKET JESSIE & JAMES");
static const struct CreditsEntry sPRUCreditsEntry_15_1 = {0, FALSE, sPRUCreditsText_15_1};
static const u8 sPRUCreditsText_15_2[] = _("MRNIGHTOLOGY DONOR ROM");
static const struct CreditsEntry sPRUCreditsEntry_15_2 = {0, FALSE, sPRUCreditsText_15_2};
static const u8 sPRUCreditsText_16_0[] = _("CUSTOM BATTLE INTROS");
static const struct CreditsEntry sPRUCreditsEntry_16_0 = {0, TRUE, sPRUCreditsText_16_0};
static const u8 sPRUCreditsText_16_1[] = _("JESSIE & JAMES");
static const struct CreditsEntry sPRUCreditsEntry_16_1 = {0, FALSE, sPRUCreditsText_16_1};
static const u8 sPRUCreditsText_16_2[] = _("STEEVEE & NEEVEE");
static const struct CreditsEntry sPRUCreditsEntry_16_2 = {0, FALSE, sPRUCreditsText_16_2};
static const u8 sPRUCreditsText_17_0[] = _("TILESETS & ENVIRONMENTS");
static const struct CreditsEntry sPRUCreditsEntry_17_0 = {0, TRUE, sPRUCreditsText_17_0};
static const u8 sPRUCreditsText_17_1[] = _("EKAT99 / WESLEYFG");
static const struct CreditsEntry sPRUCreditsEntry_17_1 = {0, FALSE, sPRUCreditsText_17_1};
static const u8 sPRUCreditsText_17_2[] = _("KALARIE & CONTRIBUTORS");
static const struct CreditsEntry sPRUCreditsEntry_17_2 = {0, FALSE, sPRUCreditsText_17_2};
static const u8 sPRUCreditsText_18_0[] = _("SURFING OVERWORLDS");
static const struct CreditsEntry sPRUCreditsEntry_18_0 = {0, TRUE, sPRUCreditsText_18_0};
static const u8 sPRUCreditsText_18_1[] = _("SLAWTER666");
static const struct CreditsEntry sPRUCreditsEntry_18_1 = {0, FALSE, sPRUCreditsText_18_1};
static const u8 sPRUCreditsText_18_2[] = _("WALLY-217");
static const struct CreditsEntry sPRUCreditsEntry_18_2 = {0, FALSE, sPRUCreditsText_18_2};
static const u8 sPRUCreditsText_19_0[] = _("ART & SPRITE TOOLING");
static const struct CreditsEntry sPRUCreditsEntry_19_0 = {0, TRUE, sPRUCreditsText_19_0};
static const u8 sPRUCreditsText_19_1[] = _("POKéSPRITE");
static const struct CreditsEntry sPRUCreditsEntry_19_1 = {0, FALSE, sPRUCreditsText_19_1};
static const u8 sPRUCreditsText_19_2[] = _("PORYPAL");
static const struct CreditsEntry sPRUCreditsEntry_19_2 = {0, FALSE, sPRUCreditsText_19_2};
static const u8 sPRUCreditsText_20_0[] = _("DEVELOPMENT WORKFLOW");
static const struct CreditsEntry sPRUCreditsEntry_20_0 = {0, TRUE, sPRUCreditsText_20_0};
static const u8 sPRUCreditsText_20_1[] = _("GITHUB");
static const struct CreditsEntry sPRUCreditsEntry_20_1 = {0, FALSE, sPRUCreditsText_20_1};
static const u8 sPRUCreditsText_20_2[] = _("SOURCE CONTROL & REVIEW");
static const struct CreditsEntry sPRUCreditsEntry_20_2 = {0, FALSE, sPRUCreditsText_20_2};
static const u8 sPRUCreditsText_21_0[] = _("AI DEVELOPMENT TOOLS");
static const struct CreditsEntry sPRUCreditsEntry_21_0 = {0, TRUE, sPRUCreditsText_21_0};
static const u8 sPRUCreditsText_21_1[] = _("OPENAI / CHATGPT");
static const struct CreditsEntry sPRUCreditsEntry_21_1 = {0, FALSE, sPRUCreditsText_21_1};
static const u8 sPRUCreditsText_21_2[] = _("ANTHROPIC / CLAUDE");
static const struct CreditsEntry sPRUCreditsEntry_21_2 = {0, FALSE, sPRUCreditsText_21_2};
static const u8 sPRUCreditsText_22_0[] = _("AI DEVELOPMENT TOOLS");
static const struct CreditsEntry sPRUCreditsEntry_22_0 = {0, TRUE, sPRUCreditsText_22_0};
static const u8 sPRUCreditsText_22_1[] = _("GOOGLE / GEMINI");
static const struct CreditsEntry sPRUCreditsEntry_22_1 = {0, FALSE, sPRUCreditsText_22_1};
static const u8 sPRUCreditsText_22_2[] = _("CODE & DOCUMENTATION SUPPORT");
static const struct CreditsEntry sPRUCreditsEntry_22_2 = {0, FALSE, sPRUCreditsText_22_2};
static const u8 sPRUCreditsText_23_0[] = _("ORIGINAL CONTRIBUTORS");
static const struct CreditsEntry sPRUCreditsEntry_23_0 = {0, TRUE, sPRUCreditsText_23_0};
static const u8 sPRUCreditsText_23_1[] = _("HEART & SOUL TEAM");
static const struct CreditsEntry sPRUCreditsEntry_23_1 = {0, FALSE, sPRUCreditsText_23_1};
static const u8 sPRUCreditsText_23_2[] = _("POKEEMERALD EXPANSION TEAM");
static const struct CreditsEntry sPRUCreditsEntry_23_2 = {0, FALSE, sPRUCreditsText_23_2};
static const u8 sPRUCreditsText_24_0[] = _("ARTIST ATTRIBUTION");
static const struct CreditsEntry sPRUCreditsEntry_24_0 = {0, TRUE, sPRUCreditsText_24_0};
static const u8 sPRUCreditsText_24_1[] = _("SEE DOCS/PRU_CREDITS");
static const struct CreditsEntry sPRUCreditsEntry_24_1 = {0, FALSE, sPRUCreditsText_24_1};
static const u8 sPRUCreditsText_24_2[] = _("AND EXISTING SOURCE CREDITS");
static const struct CreditsEntry sPRUCreditsEntry_24_2 = {0, FALSE, sPRUCreditsText_24_2};
static const u8 sPRUCreditsText_25_0[] = _("POKéMON RIGHTS");
static const struct CreditsEntry sPRUCreditsEntry_25_0 = {0, TRUE, sPRUCreditsText_25_0};
static const u8 sPRUCreditsText_25_1[] = _("NINTENDO / CREATURES");
static const struct CreditsEntry sPRUCreditsEntry_25_1 = {0, FALSE, sPRUCreditsText_25_1};
static const u8 sPRUCreditsText_25_2[] = _("GAME FREAK");
static const struct CreditsEntry sPRUCreditsEntry_25_2 = {0, FALSE, sPRUCreditsText_25_2};
static const u8 sPRUCreditsText_26_0[] = _("TO OUR COMMUNITY");
static const struct CreditsEntry sPRUCreditsEntry_26_0 = {0, TRUE, sPRUCreditsText_26_0};
static const u8 sPRUCreditsText_26_1[] = _("FAN ARTISTS & TESTERS");
static const struct CreditsEntry sPRUCreditsEntry_26_1 = {0, FALSE, sPRUCreditsText_26_1};
static const u8 sPRUCreditsText_26_2[] = _("THANK YOU FOR YOUR SUPPORT");
static const struct CreditsEntry sPRUCreditsEntry_26_2 = {0, FALSE, sPRUCreditsText_26_2};
static const u8 sPRUCreditsText_27_0[] = _("TO OUR PLAYERS");
static const struct CreditsEntry sPRUCreditsEntry_27_0 = {0, TRUE, sPRUCreditsText_27_0};
static const u8 sPRUCreditsText_27_1[] = _("THANK YOU FOR EXPLORING");
static const struct CreditsEntry sPRUCreditsEntry_27_1 = {0, FALSE, sPRUCreditsText_27_1};
static const u8 sPRUCreditsText_27_2[] = _("THE WORLD OF RELICS");
static const struct CreditsEntry sPRUCreditsEntry_27_2 = {0, FALSE, sPRUCreditsText_27_2};
static const u8 sPRUCreditsText_28_0[] = _("YOUR JOURNEY CONTINUES");
static const struct CreditsEntry sPRUCreditsEntry_28_0 = {0, TRUE, sPRUCreditsText_28_0};
static const u8 sPRUCreditsText_28_1[] = _("THE RELICS ENDURE");
static const struct CreditsEntry sPRUCreditsEntry_28_1 = {0, FALSE, sPRUCreditsText_28_1};
static const u8 sPRUCreditsText_28_2[] = _("POKéMON RELICS ULTIMATE");
static const struct CreditsEntry sPRUCreditsEntry_28_2 = {0, FALSE, sPRUCreditsText_28_2};

static const struct CreditsEntry *const sCreditsEntryPointerTable[PAGE_COUNT][ENTRIES_PER_PAGE] =
{
    [PAGE_PRU_01] = { &sPRUCreditsEntry_0_0, &sPRUCreditsEntry_0_1, &sPRUCreditsEntry_0_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_02] = { &sPRUCreditsEntry_1_0, &sPRUCreditsEntry_1_1, &sPRUCreditsEntry_1_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_03] = { &sPRUCreditsEntry_2_0, &sPRUCreditsEntry_2_1, &sPRUCreditsEntry_2_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_04] = { &sPRUCreditsEntry_3_0, &sPRUCreditsEntry_3_1, &sPRUCreditsEntry_3_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_05] = { &sPRUCreditsEntry_4_0, &sPRUCreditsEntry_4_1, &sPRUCreditsEntry_4_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_06] = { &sPRUCreditsEntry_5_0, &sPRUCreditsEntry_5_1, &sPRUCreditsEntry_5_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_07] = { &sPRUCreditsEntry_6_0, &sPRUCreditsEntry_6_1, &sPRUCreditsEntry_6_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_08] = { &sPRUCreditsEntry_7_0, &sPRUCreditsEntry_7_1, &sPRUCreditsEntry_7_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_09] = { &sPRUCreditsEntry_8_0, &sPRUCreditsEntry_8_1, &sPRUCreditsEntry_8_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_10] = { &sPRUCreditsEntry_9_0, &sPRUCreditsEntry_9_1, &sPRUCreditsEntry_9_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_11] = { &sPRUCreditsEntry_10_0, &sPRUCreditsEntry_10_1, &sPRUCreditsEntry_10_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_12] = { &sPRUCreditsEntry_11_0, &sPRUCreditsEntry_11_1, &sPRUCreditsEntry_11_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_13] = { &sPRUCreditsEntry_12_0, &sPRUCreditsEntry_12_1, &sPRUCreditsEntry_12_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_14] = { &sPRUCreditsEntry_13_0, &sPRUCreditsEntry_13_1, &sPRUCreditsEntry_13_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_15] = { &sPRUCreditsEntry_14_0, &sPRUCreditsEntry_14_1, &sPRUCreditsEntry_14_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_16] = { &sPRUCreditsEntry_15_0, &sPRUCreditsEntry_15_1, &sPRUCreditsEntry_15_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_17] = { &sPRUCreditsEntry_16_0, &sPRUCreditsEntry_16_1, &sPRUCreditsEntry_16_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_18] = { &sPRUCreditsEntry_17_0, &sPRUCreditsEntry_17_1, &sPRUCreditsEntry_17_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_19] = { &sPRUCreditsEntry_18_0, &sPRUCreditsEntry_18_1, &sPRUCreditsEntry_18_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_20] = { &sPRUCreditsEntry_19_0, &sPRUCreditsEntry_19_1, &sPRUCreditsEntry_19_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_21] = { &sPRUCreditsEntry_20_0, &sPRUCreditsEntry_20_1, &sPRUCreditsEntry_20_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_22] = { &sPRUCreditsEntry_21_0, &sPRUCreditsEntry_21_1, &sPRUCreditsEntry_21_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_23] = { &sPRUCreditsEntry_22_0, &sPRUCreditsEntry_22_1, &sPRUCreditsEntry_22_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_24] = { &sPRUCreditsEntry_23_0, &sPRUCreditsEntry_23_1, &sPRUCreditsEntry_23_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_25] = { &sPRUCreditsEntry_24_0, &sPRUCreditsEntry_24_1, &sPRUCreditsEntry_24_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_26] = { &sPRUCreditsEntry_25_0, &sPRUCreditsEntry_25_1, &sPRUCreditsEntry_25_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_27] = { &sPRUCreditsEntry_26_0, &sPRUCreditsEntry_26_1, &sPRUCreditsEntry_26_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_28] = { &sPRUCreditsEntry_27_0, &sPRUCreditsEntry_27_1, &sPRUCreditsEntry_27_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
    [PAGE_PRU_29] = { &sPRUCreditsEntry_28_0, &sPRUCreditsEntry_28_1, &sPRUCreditsEntry_28_2, &sCreditsEntry_EmptyString, &sCreditsEntry_EmptyString },
};
