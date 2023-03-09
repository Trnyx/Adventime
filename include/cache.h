/**
 * @file cache.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 9 mars
 * @version 1.1
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
 * @brief 
 */
typedef struct s_cache {
    t_monde *monde;                 /**< Le monde chargé */
    t_map *map;                     /**< La map chargée */

    t_liste *entites;               /**< Les entités chargées */
} t_cache;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_cache* initCache();
void detruireCache(t_cache **cache);





#endif