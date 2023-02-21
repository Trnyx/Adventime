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
 * @version 1.2
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
 * @brief Vérifie que le végétal peut être placé
 * 
 * @param positionVegetal La position du végétal  à placer
 * @param grid Le tableau regroupant les positions des végétaux déjà placés
 * @param rayon Le rayon minimum pour 
 * @return Vrai si le végétal peut être placé aux coordonnées données, faux sinon
 * 
 * @version 1.2
 */
int peutPlacerVegetatal(const t_vecteur2 positionVegetal, const t_diskSampling grid, const float rayon) {
    int peutEtrePlace = 0;
    int i = 0;


    while (!peutEtrePlace && i < grid.nbVegetaux) {
        const t_vecteur2 vegetalDejaPlace = grid.vegetauxPositions[i++];      
        const float norme = calculDistanceEntrePoints(positionVegetal, vegetalDejaPlace);

        if (norme >= rayon && norme <= rayon * 2.0) 
            peutEtrePlace = 1;
    }

  
    return peutEtrePlace;
}





/* -------------------------------------------------------------------------- */
/*                                 Generations                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Génère une grille en se basant sur la technique du "Poisson Disk Sampling"
 * 
 * @param chunk Un pointeur sur le chunk de la couche du sol
 * @return La grille de placement des végétaux
 * 
 * @version 1.2
 */
t_diskSampling genererDiskSampling(t_chunk *chunk) {
    t_diskSampling vegetals;
    const int nbVegetaux = getNombreAleatoire((TAILLE_CHUNK) / 2, (2 * TAILLE_CHUNK) / 3);

    vegetals.nbVegetaux = 0;
    vegetals.vegetauxPositions = calloc(nbVegetaux, sizeof(t_vecteur2));
    vegetals.vegetauxTags = calloc(nbVegetaux, sizeof(t_vecteur2));

    const t_baseBiome baseBiome = basesBiomes[chunk->biome];
    const e_vegetalTag vegetalTag = selectionVegetation(baseBiome) % HERBE;

  
    if (baseBiome.vegetationDensite > 0) {
        const float rayon = (TAILLE_CHUNK / 2) / baseBiome.vegetationDensite;
      
      
        for (int n = 0; n < nbVegetaux; n++) {
            t_vecteur2 nouveauPoint = {
                getNombreAleatoire(0, (TAILLE_CHUNK) - 1),
                getNombreAleatoire(0, (TAILLE_CHUNK) - 1),
            };
    
    
            if (!n || peutPlacerVegetatal(nouveauPoint, vegetals, rayon)) {
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
 * @brief Génère les végétaux
 * 
 * @param map Un pointeur sur la map dans laquelle sera généré les végétaux
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

            t_diskSampling vegetaux = genererDiskSampling(chunk);
          
            for (int i = 0; i < vegetaux.nbVegetaux; i++) {
                t_vecteur2 positionVegetal = vegetaux.vegetauxPositions[i];
                
                block = getBlockDansChunk((int)positionVegetal.x % TAILLE_CHUNK, (int)positionVegetal.y % TAILLE_CHUNK, chunk);
                if (block == NULL) continue;
                if (block->tag <= SOL_EAU) continue;
        
                chunk = getChunk(x, y, COUCHE_VEGETATION, map);
                block = getBlockDansChunk((int)positionVegetal.x % TAILLE_CHUNK, (int)positionVegetal.y % TAILLE_CHUNK, chunk);
                block->tag = CHAINE;
            }

            free(vegetaux.vegetauxPositions);
            free(vegetaux.vegetauxTags);
        }
    }
}