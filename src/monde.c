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
    const int centre = (TAILLE_MAP * TAILLE_CHUNK) / 2;
    
    
    const float x = centre, y = centre;


    t_vecteur2 position = { x, y };
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
    monde->map = genererMap(MAP_OVERWORLD);

    // t_vecteur2 position = getPointApparitionJoueur(map);
    // t_joueur *joueur = creerJoueur(position.x, position.y);


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
        detruireMap(&(*monde)->map);

    
        free(*monde);
        *monde = NULL;  
    }
    printf("Succes\n");
}