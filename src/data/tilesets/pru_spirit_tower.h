#if IS_HNS
// PRU Lavender memory tower: original FRLG Pokemon Tower art, available in HNS
// without enabling unrelated FRLG map and tileset data.
const u32 gPruSpiritTowerPrimaryTiles[] = INCBIN_U32("data/tilesets/primary/building_frlg/tiles.4bpp.smol");
const u16 gPruSpiritTowerPrimaryPalettes[][16] =
{
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/00.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/01.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/02.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/03.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/04.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/05.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/06.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/07.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/08.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/09.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/10.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/11.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/12.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/13.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/14.gbapal"),
    INCBIN_U16("data/tilesets/primary/building_frlg/palettes/15.gbapal"),
};
const u32 gPruSpiritTowerSecondaryTiles[] = INCBIN_U32("data/tilesets/secondary/pokemon_tower_frlg/tiles.4bpp.fastSmol");
const u16 gPruSpiritTowerSecondaryPalettes[][16] =
{
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/00.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/01.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/02.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/03.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/04.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/05.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/06.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/07.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/08.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/09.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/10.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/11.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/12.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/13.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/14.gbapal"),
    INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/15.gbapal"),
};
const u16 gPruSpiritTowerPrimaryMetatiles[] = INCBIN_U16("data/tilesets/primary/building_frlg/metatiles.bin");
const u16 gPruSpiritTowerPrimaryAttrs[] = INCBIN_U16("data/tilesets/primary/building_frlg/metatile_attributes.bin");
const u16 gPruSpiritTowerSecondaryMetatiles[] = INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/metatiles.bin");
const u16 gPruSpiritTowerSecondaryAttrs[] = INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/metatile_attributes.bin");

const struct Tileset gTileset_PruSpiritTowerPrimary =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gPruSpiritTowerPrimaryTiles,
    .palettes = gPruSpiritTowerPrimaryPalettes,
    .metatiles = gPruSpiritTowerPrimaryMetatiles,
    .metatileAttributes = gPruSpiritTowerPrimaryAttrs,
    .callback = NULL,
};

const struct Tileset gTileset_PruSpiritTowerSecondary =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gPruSpiritTowerSecondaryTiles,
    .palettes = gPruSpiritTowerSecondaryPalettes,
    .metatiles = gPruSpiritTowerSecondaryMetatiles,
    .metatileAttributes = gPruSpiritTowerSecondaryAttrs,
    .callback = NULL,
};
#endif // IS_HNS
