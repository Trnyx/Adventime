/**
 * @file generation_vegetations.c
 *
 * @brief Génération de la végétation 
 * 
 * La génération de la végétation suit le principe du "Poisson Disk Sampling"
 * 
 * Poisson Disk Sampling est une technique permettant de sélectionner de manière aléatoire des points serrés de façon à ce qu'ils respectent une distance minimale 
 * Comme les points sont choisis de façon aléatoire, le résultat a un aspect plus organique
 * 
 * L'algorithme suit donc les étapes suivantes
 * 
 * 
 *
 * @author Clément Hibon
 * @date 27 janvier
 * @version 1.3
 */



#include <stdlib.h>
#include <math.h>

#include "../include/vegetations.h"
#include "../include/map.h"





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                                 Selections                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Sélectionne le tag du végétal
 * 
 * @param baseBiome La base du biome dans lequel le végétal est placé
 * @return Le tag du végétal
 * 
 * @version 1.1
 */
// e_vegetalTag selectionVegetation(t_baseBiome baseBiome) {
e_vegetalTag selectionVegetation(e_solTag sol) {
    // const int probabilite = getNombreAleatoire(1, 100); // rand() % 100;
    // const int nbVegetauxPossibles = sizeof(baseBiome.tagVegetations) / sizeof(baseBiome.tagVegetations[0]);

    // for (int i = 0; i < nbVegetauxPossibles; i++) {
    //     if (baseBiome.probabilitesVegetations[i] <= probabilite) return baseBiome.tagVegetations[i];
    // }
    
  
    // return HERBE;

    switch (sol) {
        case SOL_SABLE:
            return PALMIER;

        case SOL_HERBE_1:
        case SOL_HERBE_2:
        case SOL_HERBE_3:
            return CHAINE;

        case SOL_MONTAGNE_1:
        case SOL_MONTAGNE_2:
            return SAPIN;

        default:
            return -1;
    }
}





/* -------------------------------------------------------------------------- */
/*                                    Tests                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie que le végétal peut être placé
 * 
 * @param positionVegetal La position du végétal  à placer
 * @param grid Le tableau regroupant les positions des végétaux déjà placés
 * @param rayon Le rayon minimum pour 
 * @return Vrai si le végétal peut être placé aux coordonnées données, faux sinon
 * 
 * @version 1.2
 */
boolean peutPlacerVegetal(const t_vecteur2 positionVegetal, const t_diskSampling grid, const float rayon) {
    int peutEtrePlace = 0;
    int i = 0;


    while (!peutEtrePlace && i < grid.nbVegetaux) {
        const t_vecteur2 vegetalDejaPlace = grid.vegetauxPositions[i];      
        const float norme = calculDistanceEntrePoints(positionVegetal, vegetalDejaPlace);

        if (norme >= rayon && norme <= rayon * 2.0) 
            peutEtrePlace = VRAI;
        
        i++;
    }

  
    return FAUX;
}





/* -------------------------------------------------------------------------- */
/*                                 Generations                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Génère une grille en se basant sur la technique du "Poisson Disk Sampling"
 * 
 * @param chunk Un pointeur sur le chunk de la couche du sol
 * @param baseBiome Les informations de base du biome
 * @return La grille de placement des végétaux
 * 
 * @version 1.3
 */
t_diskSampling genererDiskSampling(t_chunk *chunk) {
    t_diskSampling vegetation;
    const int nbVegetaux = getNombreAleatoire((TAILLE_CHUNK) / 2, (2 * TAILLE_CHUNK) / 3);

    vegetation.nbVegetaux = 0;
    vegetation.vegetauxPositions = calloc(nbVegetaux, sizeof(t_vecteur2));
    vegetation.vegetauxTags = calloc(nbVegetaux, sizeof(e_vegetalTag));

    const t_baseBiome baseBiome = basesBiomes[chunk->biome];
    // const e_vegetalTag vegetalTag = selectionVegetation(baseBiome);
    // printf("VEGETAL TAG : %i => ", vegetalTag);
    // printf("DENSITE : %1.2f => ", baseBiome.vegetationDensite);

  
    if (baseBiome.vegetationDensite > 0) {
        const float rayon = (TAILLE_CHUNK / 4) / baseBiome.vegetationDensite;
        // const float rayon = baseVegetal.radius / baseBiome.vegetationDensite;
      
      
        for (int n = 0; n < nbVegetaux; n++) {
            t_vecteur2 nouveauPoint = {
                getNombreAleatoire(0, (TAILLE_CHUNK) - 1),
                getNombreAleatoire(0, (TAILLE_CHUNK) - 1),
            };
    
    
            if (!n || peutPlacerVegetal(nouveauPoint, vegetation, rayon)) {
                vegetation.vegetauxPositions[n] = nouveauPoint;
                // vegetation.vegetauxTags[n] = vegetalTag;
                vegetation.nbVegetaux++;
            }
        }
    }

  
    vegetation.vegetauxPositions = realloc(vegetation.vegetauxPositions, sizeof(t_vecteur2) * vegetation.nbVegetaux);
    vegetation.vegetauxTags = realloc(vegetation.vegetauxTags, sizeof(e_vegetalTag) * vegetation.nbVegetaux);
    return vegetation;
}





/**
 * @brief Génère les végétaux
 * 
 * @param map Un pointeur sur la map dans laquelle sera généré les végétaux
 * 
 * @version 1.2
 */
void genererVegetations(t_map *map) {
    t_chunk *chunk = NULL;
    t_block *block = NULL;


    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
        
            chunk = getChunk(x, y, COUCHE_SOL, map);
            if (chunk == NULL) continue;
            if (chunk->biome == BIOME_PROFONDEUR) continue;

            // const t_baseBiome baseBiome = basesBiomes[chunk->biome];
            t_diskSampling vegetaux = genererDiskSampling(chunk);
          
            for (int i = 0; i < vegetaux.nbVegetaux; i++) {
                const t_vecteur2 positionVegetal = vegetaux.vegetauxPositions[i];
                
                block = getBlockDansChunk((int)positionVegetal.x % TAILLE_CHUNK, (int)positionVegetal.y % TAILLE_CHUNK, chunk);
                if (block == NULL) continue;
                if (block->tag <= SOL_EAU) continue;

                const e_vegetalTag vegetalTag = selectionVegetation(block->tag);
                // const e_vegetalTag vegetalTag = selectionVegetation(baseBiome);
        
                chunk = getChunk(x, y, COUCHE_OBJETS, map);
                block = getBlockDansChunk((int)positionVegetal.x % TAILLE_CHUNK, (int)positionVegetal.y % TAILLE_CHUNK, chunk);
                block->tag = vegetalTag;
            }

            free(vegetaux.vegetauxPositions);
            free(vegetaux.vegetauxTags);
        }
    }
}