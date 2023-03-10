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



#include "utilitaire.h"
#include "map.h"
#include "joueur.h"
#include "temps.h"





/**
 * @struct t_monde
 * @brief
 */
typedef struct s_monde {
    unsigned int seed;      /**< */

    t_map *map;             /**< */
    t_joueur *joueur;       /**< */

    t_temps *temps;         /**< Le temps dans le jeu */
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
unsigned int setGenerationSeed(unsigned int seed);


t_monde* creerMonde(int seed);
void detruireMonde(t_monde **monde);
void afficherMonde(t_monde *monde);


t_vecteur2 getPointApparitionJoueur(t_map *map);










#endif



