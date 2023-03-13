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


void detruireCache(t_cache **cache) {
    if (cache != NULL && *cache != NULL) {

        detruireMonde(&(*cache)->monde);

        free(*cache);
        *cache = NULL;
    }
}





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


t_cache *initCache() {
    t_cache *cache = malloc(sizeof(t_cache));

    if (cache == NULL) {
        free(cache);
        
        return NULL;
    }


    cache->monde = NULL;
    cache->map = NULL;

    cache->entites = malloc(sizeof(t_liste));
    init_liste(cache->entites);


    return cache;
}