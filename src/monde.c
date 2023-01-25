/*
 * \file 
 *
 * \brief
 *
 * \author
 */



#include <monde.h>





void setGenerationSeed(unsigned int seed) {
    srand(seed);
}





t_vecteur2 getPointApparitionJoueur(t_map *map) {
    float x, y;

    t_vecteur2 position = { x, y };
    return position;
}





t_monde creerMonde(int seed) {
    if (seed == -1) 
        setGenerationSeed(rand());
    else
        setGenerationSeed(seed);


    
    t_map *map = genererMap();


    t_vecteur2 position = getPointApparitionJoueur(map);
    t_joueur *joueur = creerJoueur(position.x, position.y);
}
