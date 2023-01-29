/**
 * @file monde.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @version 1.1
 */





#ifndef _JEU_MONDE_
#define _JEU_MONDE_



#include <utils.h>
#include <map.h>
#include <joueur.h>
#include <entite.h>





/**
 * @struct t_monde
 * @brief
 */
typedef struct s_monde {
    unsigned int seed;
    t_map map;
    t_joueur joueur;
} t_monde;





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
void setGenerationSeed(unsigned int seed);


t_monde creerMonde(int seed);





#endif



