/**
 * @file generation_vegetations.c
 *
 * @brief Génération de la végétation 
 * 
 * La génération de la végétation suit le principe du "Poisson Disc Sampling"
 * Cf. disc_sampling.c pour plus d'informations
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
#include "../include/disc_sampling.h"





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
e_vegetalTag selectionVegetation(e_solTag sol) {
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
            return HERBE;
    }
}





/* -------------------------------------------------------------------------- */
/*                                 Generation                                 */
/* -------------------------------------------------------------------------- */


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


            const t_baseBiome baseBiome = basesBiomes[chunk->biome];
            if (baseBiome.vegetationDensite <= 0) continue;


            const t_vecteur2 min = { 0, 0 };
            const t_vecteur2 max = { TAILLE_CHUNK, TAILLE_CHUNK };

            const int nbVegetaux = TAILLE_CHUNK;
            float rayon = (TAILLE_CHUNK * 0.5) / baseBiome.vegetationDensite;
            if (rayon < 1.0)
                rayon = 1.0;


            t_discSampling grille = genererGrilleDiscSampling(min, max, nbVegetaux, rayon, NULL);
            if (grille.nbElements == 0) continue;


            for (int i = 0; i < grille.nbElements; i++) {
                const t_vecteur2 point = grille.elementPositions[i];
                
                block = getBlockDansChunk((int)point.x % TAILLE_CHUNK, (int)point.y % TAILLE_CHUNK, chunk);
                if (block == NULL) continue;
                if (block->tag <= SOL_EAU || block->tag >= NB_TYPES_SOL) continue;

                const e_vegetalTag vegetalTag = selectionVegetation(block->tag);
        
                t_chunk *chunkObjets = getChunk(x, y, COUCHE_OBJETS, map);
                block = getBlockDansChunk((int)point.x % TAILLE_CHUNK, (int)point.y % TAILLE_CHUNK, chunkObjets);
                if (block->tag != VIDE) continue;

                block->tag = vegetalTag;
            }


            free(grille.elementPositions);
        }
    }
}
