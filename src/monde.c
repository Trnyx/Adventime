/**
 * @file 
 *
 * @brief
 *
 * @author
 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/monde.h"





/**
 * @brief Set the Generation Seed object
 * 
 * @param seed 
 * @return unsigned int 
 */
unsigned int setGenerationSeed(unsigned int seed) {
    srand(seed);
    return seed;
}





/**
 * @brief Get the Point Apparition Joueur object
 * 
 * @param map 
 * @return t_vecteur2 
 */
t_vecteur2 getPointApparitionJoueur(t_map *map) {
    const int centre = (TAILLE_CHUNK) / 2;

    t_chunk *chunk = NULL;
    t_block *block = NULL;

    while (chunk == NULL) {
        t_vecteur2 chunkPosition = {
            getNombreAleatoire(1, TAILLE_MAP - 2),
            getNombreAleatoire(1, TAILLE_MAP - 2),
        };


        chunk = getChunk(chunkPosition.x, chunkPosition.y, COUCHE_SOL, map);


        if (chunk == NULL)
            continue;

        if (chunk->biome == BIOME_PROFONDEUR || chunk->biome == BIOME_LAC) {
            chunk = NULL;
        }
    }


    while (block == NULL) {
        t_vecteur2 blockPosition = {
            getNombreAleatoire(0, TAILLE_CHUNK - 1),
            getNombreAleatoire(0, TAILLE_CHUNK - 1),
        };


        block = getBlockDansChunk(blockPosition.x, blockPosition.y, chunk);


        if (block == NULL)
            continue;

        if (block->tag == SOL_EAU_PROFONDE || block->tag == SOL_EAU) {
            block = NULL;
            continue;
        }


        chunk = getChunk(chunk->position.x, chunk->position.y, COUCHE_OBJETS, map);
        block = getBlockDansChunk(blockPosition.x, blockPosition.y, chunk);

        if (block->tag != VIDE) {
            block = NULL;
            continue;
        }
    }
    

    t_vecteur2 position = { block->position.x, block->position.y };
    return position;
}





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param seed 
 * @return t_monde* 
 */
t_monde* creerMonde(int seed) {
    t_monde *monde = malloc(sizeof(t_monde));


    if (monde == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour le monde\n");
        free(monde);
        return NULL;
    }


    if (seed == -1) {
        seed = setGenerationSeed(time(NULL));
    }
    else {
        seed = setGenerationSeed(seed);
    }


    monde->seed = seed;
    monde->overworld = genererMap(MAP_OVERWORLD);
    monde->timestampRenouvellement = time(NULL);

    // monde->bossFlags = initialiserBossFlags();
    t_vecteur2 position = getPointApparitionJoueur(monde->overworld);
    monde->pointApparitionDefaut = position;
    monde->pointApparition.x = -1.0;
    monde->pointApparition.y = -1.0;


    return monde;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param monde 
 */
void detruireMonde(t_monde **monde) {
    printf("Destruction Monde => ");
    if (monde != NULL && *monde != NULL) {
        detruireMap(&(*monde)->overworld);

    
        free(*monde);
        *monde = NULL;  
    }
    printf("Succes\n");
}