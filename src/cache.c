/**
 * @file cache.c
 *
 * @brief Module de gestion du cache
 * 
 * Le cache permet d'avoir un accès plus simple et plus rapide à des variables importantes
 *
 * @author Clément Hibon
 * @date 9 mars
 */



#include <stdlib.h>
#include <stdio.h>

#include "../include/cache.h"





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit le cache est libère la mémoire allouée pour ce dernier
 * 
 * @param cache L'adresse du pointeur du cache à détruire
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
 * @brief Alloue l'espace nécessaire pour le cache et l'initialise
 * 
 * @return Un pointeur sur le cache, NULL si echec
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