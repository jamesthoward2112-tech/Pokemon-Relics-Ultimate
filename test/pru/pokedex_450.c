#include "global.h"
#include "pokemon.h"
#include "pokedex.h"
#include "test/battle.h"
#include "data/pokemon/pru_dex_order.h"

TEST("PRU all 450 Pokédex entries have unique persisted Seen/Caught slots")
{
    u16 i, j;

    if (!IS_HNS)
        return;

    for (i = 0; i < PRU_DEX_COUNT; i++)
    {
        u16 species = sPruDexSpecies[i];
        u16 slot = SpeciesToNationalPokedexNum(species);

        EXPECT(slot != NATIONAL_DEX_NONE);
        EXPECT(slot <= NATIONAL_DEX_COUNT);
        EXPECT_EQ(SpeciesToPokedexNum(species), i + 1);
        EXPECT_EQ(NationalPokedexNumToSpecies(slot), species);
        for (j = 0; j < i; j++)
            EXPECT(slot != SpeciesToNationalPokedexNum(sPruDexSpecies[j]));
    }
}

TEST("PRU existing Nat Dex bits remain intact and custom evolutions do not alias base")
{
    if (!IS_HNS)
        return;

    EXPECT_EQ(SpeciesToNationalPokedexNum(SPECIES_BULBASAUR), NATIONAL_DEX_BULBASAUR);
    EXPECT_EQ(SpeciesToNationalPokedexNum(SPECIES_CHARIZARD), NATIONAL_DEX_CHARIZARD);
    EXPECT_EQ(SpeciesToNationalPokedexNum(SPECIES_BLASTOISE), NATIONAL_DEX_BLASTOISE);

    EXPECT(SpeciesToNationalPokedexNum(SPECIES_EDENSAUR) != SpeciesToNationalPokedexNum(SPECIES_VENUSAUR));
    EXPECT(SpeciesToNationalPokedexNum(SPECIES_CHARAXIS) != SpeciesToNationalPokedexNum(SPECIES_CHARIZARD));
    EXPECT(SpeciesToNationalPokedexNum(SPECIES_FORTOTOISE) != SpeciesToNationalPokedexNum(SPECIES_BLASTOISE));
    EXPECT(SpeciesToNationalPokedexNum(SPECIES_NOXICHU) != SpeciesToNationalPokedexNum(SPECIES_RAICHU));
    EXPECT(SpeciesToNationalPokedexNum(SPECIES_HERACURION) != SpeciesToNationalPokedexNum(SPECIES_HERACROSS));
    EXPECT(SpeciesToNationalPokedexNum(SPECIES_NOLAX) != SpeciesToNationalPokedexNum(SPECIES_SNORLAX));

    EXPECT_EQ(SpeciesToPokedexNum(SPECIES_CHARAXIS), 8);
    EXPECT_EQ(SpeciesToPokedexNum(SPECIES_FORTOTOISE), 12);
    EXPECT_EQ(SpeciesToPokedexNum(SPECIES_SYLVEON), 185);
}
