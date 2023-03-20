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




#include "blocks_tag.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


typedef enum {
    MAISON_1,
    MAISON_2,
    MAISON_3,
    PUIT,
    TEMPLE,
} e_structureTag;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


typedef struct s_structure {
    e_structureTag tag;
    e_blockTag *blocks;
} t_structure;




/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */





#endif