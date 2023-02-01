/**
 * @file vegetations.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 27 janvier
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
 * @brief Tag permettant de reconnaitre les végétaux
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
 * @brief Modélise un végétal
 */
typedef struct s_vegetation {
    t_vecteur2 position;
    e_vegetalTag tag;
} t_vegetation;



/**
 * @brief Modélise la base d'un végétal
 */
typedef struct s_baseVegetation {
    e_vegetalTag tag;
    float radius;
} t_baseVegetal;





/**
 * @brief Modélise un "Disk Sampling"
 */
typedef struct s_diskSampling {
    int nbVegetaux;
    t_vecteur2 *vegetauxPositions;
    e_vegetalTag *vegetauxTags;
} t_diskSampling;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseVegetal basesVegetaux[];










#endif