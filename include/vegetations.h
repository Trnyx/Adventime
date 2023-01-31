/**
 * @file vegetations.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @version 1.1
 */





#ifndef _JEU_VEGETATIONS_
#define _JEU_VEGETATIONS_



#include <utils.h>





#define NB_VEGETATIONS 6





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 */
typedef enum {
    HERBE = 100,
    // ROSE,
    // TULIPE,
    CHAINE,
    PALMIER,
    SAPIN,
} e_vegetalTag;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 */
typedef struct s_vegetation {
    t_vecteur2 position;
    e_vegetalTag tag;
} t_vegetation;



/**
 * @brief 
 * 
 */
typedef struct s_baseVegetation {
    e_vegetalTag tag;
    float radius;
} t_baseVegetal;





/**
 * @brief 
 * 
 */
typedef struct s_discSampling {
    int nbVegetaux;
    t_vecteur2 *vegetauxPositions;
    e_vegetalTag *vegetauxTags;
} t_discSampling;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseVegetal basesVegetaux[];










#endif