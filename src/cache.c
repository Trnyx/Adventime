/**
 * @file cache.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 9 mars
 * @version 1.1
 */



#include <stdlib.h>
#include <stdio.h>

#include "../include/cache.h"





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param cache 
 */
void detruireCache(t_cache **cache) {
    if (cache != NULL && *cache != NULL) {
        if ((*cache)->monde != NULL)
            detruireMonde(&(*cache)->monde);

        free(*cache);
        *cache = NULL;
    }
}





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @return t_cache* 
 */
t_cache *initCache() {
    t_cache *cache = malloc(sizeof(t_cache));

    if (cache == NULL) {
        printf("Erreur mémoire ; Impossible d'allouer la mémoire nécessaire pour le cache\n");
        return NULL;
    }


    cache->monde = NULL;
    cache->map = NULL;
    cache->entites = NULL;

    t_compteur compteur = { 0, 0, 0, 0 };
    cache->compteurEntites = compteur;


    return cache;
}