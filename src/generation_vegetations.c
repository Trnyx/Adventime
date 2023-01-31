/**
 * @file generation_vegetations.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @version 1.1
 */



#include <stdlib.h>
#include <math.h>
#include <vegetations.h>
#include <map.h>





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


const t_baseVegetal basesVegetaux[] = {
    { HERBE, 1.0 },
    // { ROSE, 3.0 },
    // { TULIPE, 3.0 },
    { CHAINE, 3.0 },
    { PALMIER, 6.0 },
    { SAPIN, 5.0 },
};





/* -------------------------------------------------------------------------- */
/*                                 Selections                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param baseBiome 
 * @return e_vegetalTag 
 * 
 * @version 1.1
 */
e_vegetalTag selectionVegetation(t_baseBiome baseBiome) {
    const int probabilite = getNombreAleatoire(1, 100); // rand() % 100;
    const int nbVegetauxPossibles = sizeof(baseBiome.tagVegetations) / sizeof(baseBiome.tagVegetations[0]);

    for (int i = 0; i < nbVegetauxPossibles; i++) {
        if (baseBiome.probabilitesVegetations[i] >= probabilite) return baseBiome.tagVegetations[i];
    }
    
  
    return -1;
}





/* -------------------------------------------------------------------------- */
/*                                    Tests                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param grid 
 * @param rayon 
 * @return int 
 * 
 * @version 1.1
 */
int peutPlacerVegetatal(const int x, const int y, const t_discSampling grid, const float rayon) {
    int peutEtrePlace = 0;
    int i = 0;


    while (!peutEtrePlace && i < grid.nbVegetaux) {
        const t_vecteur2 vegetalDejaPlace = grid.vegetauxPositions[i++];      
        const float norme = sqrt(pow(vegetalDejaPlace.x - x, 2) + pow(vegetalDejaPlace.y - y, 2));

        if (norme >= rayon && norme <= rayon * 2.0) 
            peutEtrePlace = 1;
    }

  
    return peutEtrePlace;
}





/* -------------------------------------------------------------------------- */
/*                                 Generations                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param chunk 
 * @return t_discSampling 
 * 
 * @version 1.1
 */
t_discSampling genererDiscSampling(t_chunk *chunk) {
    t_discSampling vegetals;
    const int nbVegetaux = getNombreAleatoire((TAILLE_CHUNK) / 2, (2 * TAILLE_CHUNK) / 3);

    vegetals.nbVegetaux = 0;
    vegetals.vegetauxPositions = calloc(nbVegetaux, sizeof(t_vecteur2));
    vegetals.vegetauxTags = calloc(nbVegetaux, sizeof(t_vecteur2));

    const t_baseBiome baseBiome = basesBiomes[chunk->biome];
    const e_vegetalTag vegetalTag = selectionVegetation(baseBiome) % HERBE;

  
    if (baseBiome.vegetationDensite[0]) {
        const float rayon = 10.0 / baseBiome.vegetationDensite[0];
      
      
        for (int n = 0; n < nbVegetaux; n++) {
            t_vecteur2 nouveauPoint = {
                getNombreAleatoire(0, (TAILLE_CHUNK) - 1),
                getNombreAleatoire(0, (TAILLE_CHUNK) - 1),
            };
    
    
            if (!n || peutPlacerVegetatal(nouveauPoint.x, nouveauPoint.y, vegetals, rayon)) {
                vegetals.vegetauxPositions[n] = nouveauPoint;
                vegetals.vegetauxTags[n] = HERBE;
                vegetals.nbVegetaux++;
            }
        }
    }

  
    vegetals.vegetauxPositions = realloc(vegetals.vegetauxPositions, sizeof(t_vecteur2) * vegetals.nbVegetaux);
    vegetals.vegetauxTags = realloc(vegetals.vegetauxTags, sizeof(t_vecteur2) * vegetals.nbVegetaux);
    return vegetals;
}





/**
 * @brief 
 * 
 * @param map 
 * 
 * @version 1.1
 */
void genererVegetations(t_map *map) {
    t_chunk *chunk = NULL;
    t_block *block = NULL;


    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
        
            chunk = getChunk(x, y, COUCHE_SOL, map);
            if (chunk == NULL) continue;
            if (chunk->biome == BIOME_PROFONDEUR) continue;

            t_discSampling vegetaux = genererDiscSampling(chunk);
          
            for (int i = 0; i < vegetaux.nbVegetaux; i++) {
                t_vecteur2 positionVegetal = vegetaux.vegetauxPositions[i];
                
                block = getBlockDansChunk((int)positionVegetal.x % TAILLE_CHUNK, (int)positionVegetal.y % TAILLE_CHUNK, chunk);
                if (block == NULL) continue;
                if (block->tag <= SOL_EAU) continue;
        
                block = getBlockDansChunk((int)positionVegetal.x % TAILLE_CHUNK, (int)positionVegetal.y % TAILLE_CHUNK, chunk);
                block->tag = HERBE;
            }

            free(vegetaux.vegetauxPositions);
            free(vegetaux.vegetauxTags);
        }
    }
}