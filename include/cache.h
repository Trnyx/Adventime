/**
 * @file cache.h
 *
 * @brief Module de manipulation du cache
 * 
 * Le cache permet un accès rapide à certaines variables facilitant leur gestion
 *
 * @author Clément Hibon
 * @date 9 mars
 */





#ifndef _JEU_CACHE_
#define _JEU_CACHE_





#include "joueur.h"
#include "monde.h"
#include "liste.h"



/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_cache
 * @brief Structure contenant les informations que l'on stock dans le cache
 */
typedef struct s_cache {
    t_monde *monde;                 /**< Le monde chargé */
    t_map *map;                     /**< La map chargée */

    t_liste *entites;               /**< Les entités chargées */
    t_compteur compteurEntites;     /**< Le compteur d'entités */
} t_cache;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_cache* initCache();
void detruireCache(t_cache **cache);





#endif