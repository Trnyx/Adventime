/**
 * @file structures.h
 *
 * @brief Module de manipulation des structures 
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


/**
 * @enum e_structureTag
 * @brief Enumerateur contenant les tags des structures 
 * 
 */
typedef enum {
    STRUCTURE_PUIT,
    STRUCTURE_PETITE_MAISON_1,
    STRUCTURE_PETITE_MAISON_2,
    STRUCTURE_PETITE_MAISON_3,
    STRUCTURE_GRANDE_MAISON_1,
    STRUCTURE_GRANDE_MAISON_2,
    STRUCTURE_GRANDE_MAISON_3,
    STRUCTURE_ENTREE_TEMPLE,
} e_structureTag;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_structure
 * @brief Structures modélisant les données d'une structure
 * 
 */
typedef struct s_structure {
    e_structureTag tag;         /**< Le tag de la structure */

    unsigned int hauteur;       /**< Le nombre de blocs en hauteur que prend la structure */
    unsigned int largeur;       /**< Le nombre de blocs en largeur que prend la structure */

    e_blockTag blocks[7][6];    /**< Le tableau regroupant les blocs de la structure */
} t_structure;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void genererStructure(const t_vecteur2 position, const e_structureTag tag, t_map *map);
void genererEntreeTemple(t_map *map);
void genererVillage(t_map *map);
void genererEntreeCaverne(t_map *map);





#endif
