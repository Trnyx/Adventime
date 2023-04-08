/**
 * @file animation.h
 * 
 * @brief Module de manipulation du monde
 * 
 * @author Clément Hibon
 * @date 
 * @version 1.1
 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/moteur.h"
#include "../include/monde.h"
#include "../include/seed.h"





/**
 * srand(unsigned int seed) permet de définir le "seed" utilisé par la fonction rand()
 * grâce au "seed", la fonction rand() donnera toujours les mêmes valeurs
 * 
 * Prenons par exemple les 5 premières génération du seed 123 :
 *  seed        : 123
 *  résultats   : 128959393 / 1692901013 / 436085873 / 748533630 / 776550279
 * 
 *  => Pour le seed "123", les 5 premières au début de l'execution du code 
 *     suivra toujours cet ordre
 */

/**
 * @brief Applique le seed pour l'initialisation des valeurs aléatoires
 * 
 * @param seed Le seed utilisé
 * @return Le seed donné
 */
int setGenerationSeed(long long int seed) {
    srand(seed);
    return seed;
}




/**
 * @brief Converti la chaine de caractère en seed
 * 
 * @param seedString La chaine de caractère utilisé pour le seed
 * 
 * @return Le seed
 */
long long int convertionSeed(char *seedString) {
    return convertirEnSeed(seedString);
}





/**
 * @brief Obtient le point d'apparition par défaut du joueur
 * 
 * @param map La map dans laquelle le joueur apparait
 * 
 * @return La position d'apparition par défaut du joueur 
 */
t_vecteur2 getPointApparitionJoueur(t_map *map) {
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
            // block = NULL;
            continue;
        }


        chunk = getChunk(chunk->position.x, chunk->position.y, COUCHE_OBJETS, map);
        block = getBlockDansChunk(blockPosition.x, blockPosition.y, chunk);

        if (block->tag != VIDE) {
            // block = NULL;
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
 * @brief Alloue l'espace nécessaire pour un monde et le créer
 * 
 * @param seed Le seed du monde
 * 
 * @return Un pointeur sur le monde créé, NULL si echec
 */
t_monde* creerMonde(long long int seed) {
    t_monde *monde = malloc(sizeof(t_monde));
    const time_t timestamp = time(NULL);


    if (monde == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour le monde\n");
        return NULL;
    }


    monde->id = genererId();


    if (seed == -1) {
        seed = setGenerationSeed(timestamp);
    }
    else {
        seed = setGenerationSeed(seed);
    }


    // Seed
    monde->seed = seed;
    printf("SEED : %lli\n", seed);

    // Maps
    monde->overworld = genererMap(MAP_OVERWORLD);
    monde->caverne = NULL; // genererMap(MAP_CAVE);

    // Boss
    monde->positionApparitionBoss = getPointApparitionBoss(monde->overworld);
    monde->boss = NULL;


    // Timestamp
    monde->timestampRenouvellement = timestamp;


    // Joueur
    t_vecteur2 position = getPointApparitionJoueur(monde->overworld);
    monde->pointApparitionDefaut = position;
    monde->pointApparition = position;

    monde->bossFlags = initialiserBossFlags();

    return monde;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit un monde est libère la mémoire allouée pour ce dernier
 * 
 * @param monde L'adresse du pointeur du monde à détruire
 */
void detruireMonde(t_monde **monde) {
    if (monde != NULL && *monde != NULL) {
        if ((*monde)->id != NULL) {
            free((*monde)->id);
            (*monde)->id = NULL;
        }

        if ((*monde)->overworld != NULL)
            detruireMap(&(*monde)->overworld);
        if ((*monde)->caverne != NULL)
            detruireMap(&(*monde)->caverne);

    
        free(*monde);
        *monde = NULL;  
    }
}