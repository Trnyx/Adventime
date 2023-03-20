/**
 * @file structures.c
 *
 * @brief 
 *
 * @author Clément Hibon
 * @date 10 mars
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/structures.h"
#include "../include/disc_sampling.h"





/* -------------------------------------------------------------------------- */
/*                                 Validation                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie que le chunk donné est conforme pour la génération d'un village
 * 
 * @param chunk Le chunk qui doit être vérifié
 * @return 1 si valide, 0 sinon / Cas particulier : -1 => cas bannis
 */
int biomeValidationPourVillage(t_chunk *chunk) {
    if (chunk->biome <= BIOME_LAC) return -1;
    else return chunk->biome == BIOME_PLAINE || chunk->biome == BIOME_FORET;
}



/**
 * @brief Vérifie que le chunk donné est conforme pour la génération de l'entré du temple
 * 
 * @param chunk Le chunk qui doit être vérifié
 * @return 1 si valide, 0 sinon
 */
int biomeValidationPourEntreeTemple(t_chunk *chunk) {
    return chunk->biome == BIOME_MONTAGNE;
}





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Get the Chunk Central Biome object
 * 
 * @param biome 
 * @param map 
 * @param validation 
 * @return t_chunk* 
 */
t_chunk* getChunkCentralBiome(const e_biome biome, t_map *map, int (*validation)(t_chunk*)) {
    t_chunk *chunkFinal = NULL;
    int max = 0;
    int compteur = 0;


    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            t_chunk *chunk = getChunk(x, y, COUCHE_SOL, map);


            if (chunk == NULL) continue;

            if (chunk->biome == biome) {
                for (int xChunk = chunk->position.x - 1; xChunk <= chunk->position.x + 1; xChunk++) {
                    for (int yChunk = chunk->position.y - 1; yChunk <= chunk->position.y + 1; yChunk++) {
                        if (xChunk == chunk->position.x && yChunk == chunk->position.y) continue;
                        t_chunk *chunkTempo = getChunk(xChunk, yChunk, COUCHE_SOL, map);

                        int valide = validation(chunkTempo);

                        // Si le biome trouvé est un biome interdisant l'apparition
                        // on met le compteur avec un nombre négatif pour être sûr
                        // que le chunk ne soit pas sélectionné
                        if (valide == -1)
                            compteur = -8;
                        else if (valide)
                            ++compteur;
                    }
                }


                if (compteur >= max) {
                    max = compteur;
                    chunkFinal = chunk;
                }

                compteur = 0;
            }
        }
    }
    

    printf("CHUNK FINAL : %.2f:%.2f (%i)\n", chunkFinal->position.x, chunkFinal->position.y, chunkFinal->biome);
    return chunkFinal;
}





/* -------------------------------------------------------------------------- */
/*                                   Village                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @return e_structureTag 
 */
e_structureTag selectionMaisonTag() {
    return getNombreAleatoire(STRUCTURE_PETITE_MAISON_1, STRUCTURE_PETITE_MAISON_3);
}





/**
 * @brief 
 * 
 * @param map 
 */
void genererVillage(t_map *map) {
    printf("GENERATION VILLAGE => ");
    t_chunk *plusGrandePlaine = getChunkCentralBiome(BIOME_PLAINE, map, biomeValidationPourVillage);


    if (plusGrandePlaine != NULL) {
        const t_vecteur2 centre = {
            (plusGrandePlaine->position.x * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
            (plusGrandePlaine->position.y * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
        };
        
        const t_vecteur2 min = { centre.x - (TAILLE_CHUNK), centre.y - (TAILLE_CHUNK) };
        const t_vecteur2 max = { centre.x + (TAILLE_CHUNK), centre.y + (TAILLE_CHUNK) };

        const int nombreBatiment = getNombreAleatoire(6, 8);
        

        printf("GENERATION GRILLE => ");
        const t_discSampling grille = genererGrilleDiscSampling(min, max, nombreBatiment, 18, DISC_ALEATOIRE);
        grille.elementPositions[0] = centre;


        printf("%i => ", grille.nbElements);
        for (int i = 0; i < grille.nbElements; i++) {
            t_vecteur2 position = grille.elementPositions[i];
            e_structureTag tag = selectionMaisonTag();

            if (!i && grille.nbElements > 1) {
                printf("GENERATION PUIT %1.2f:%1.2f => ", position.x, position.y);
                genererStructure(position, STRUCTURE_PUIT, map);
            }
            else {
                printf("GENERATION BATIMENT %i (%1.2f:%1.2f) => ", i, position.x, position.y);
                genererStructure(position, tag, map);
            }

        }


        free(grille.elementPositions);

    }

    printf("\n\n");
}





/* -------------------------------------------------------------------------- */
/*                                   Temple                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param map 
 */
void genererEntreeTemple(t_map *map) {
    printf("GENERATION ENTREE TEMPLE => ");
    t_chunk *plusGrandeMontagne = getChunkCentralBiome(BIOME_MONTAGNE, map, biomeValidationPourEntreeTemple);


    if (plusGrandeMontagne != NULL) {
        const t_vecteur2 centre = {
            (plusGrandeMontagne->position.x * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
            (plusGrandeMontagne->position.y * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
        };

        printf("%1.2f:%1.2f => ", centre.x, centre.y);
        genererStructure(centre, STRUCTURE_ENTREE_TEMPLE, map);
    }
    printf("\n");
}





/* -------------------------------------------------------------------------- */
/*                                   Caverne                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param map 
 */
void genererEntreeCaverne(t_map *map) {
    printf("GENERATION ENTREE Caverne => ");

    
    printf("\n");
}

