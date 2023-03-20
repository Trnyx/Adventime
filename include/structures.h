/**
 * @file structures.h
 *
 * @brief 
 *
 * @author Clément Hibon
 * @date 10 mars
 * @version 1.1
 */





#ifndef _JEU_STRUCTURES_
#define _JEU_STRUCTURES_




#include <SDL2/SDL.h>

#include "utilitaire.h"
#include "blocks_tag.h"
#include "map.h"






/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


typedef enum {
    STRUCTURE_PUIT,
    STRUCTURE_MAISON_1,
    STRUCTURE_MAISON_2,
    STRUCTURE_MAISON_3,
    STRUCTURE_TEMPLE,
} e_structureTag;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_structure
 * @brief 
 * 
 */
typedef struct s_structure {
    e_structureTag tag;         /**< */

    unsigned int hauteur;       /**< */
    unsigned int largeur;       /**< */

    e_blockTag blocks[7][6];    /**< */
} t_structure;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void genererVillage(t_map *map);





#endif