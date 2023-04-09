/**
 * @file monde.h
 *
 * @brief Module de manipulation d'un monde
 *
 * @author Clément Hibon
 * @date 25 janvier
 */





#ifndef _JEU_MONDE_
#define _JEU_MONDE_



#include "utilitaire.h"
#include "map.h"
#include "joueur.h"
#include "temps.h"
#include "boss.h"





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_monde
 * @brief Modélise un monde
 */
typedef struct s_monde {
    char *id;                               /**< L'ID du monde */
    long long int seed;                     /**< La seed de génération du monde */

    // Maps
    t_map *overworld;                       /**< La map overworld */
    t_map *caverne;                         /**< La map caverne */

    t_vecteur2 positionApparitionBoss;      /**< La point d'apparition du boss */
    t_boss *boss;                           /**< Le boss qui est actuellement présent dans le monde */


    // Joueur
    t_joueur *joueur;                       /**< Les informations du joueur dans le monde */
    t_vecteur2 pointApparitionDefaut;       /**< Le point d'apparition par défaut pour le joueur */
    t_vecteur2 pointApparition;             /**< Le point d'apparition du joueur si il le modifie */

    // Progression
    t_boss_flags bossFlags;                 /**< Les différent boss battue par le joueur */

    // Information
    time_t timestampRenouvellement;         /**< Le timestamp lors du dernier renouvellement du monde */
} t_monde;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


int setGenerationSeed(long long int seed);


t_monde* creerMonde(long long int seed);
void detruireMonde(t_monde **monde);
void afficherMonde(t_monde *monde);


t_vecteur2 getPointApparitionJoueur(t_map *map);










#endif



