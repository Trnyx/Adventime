/**
 * @file vegetations.h
 *
 * @brief Module de manipulations de la végétation
 *
 * @author Clément Hibon
 * @date 27 janvier
 * @version 1.1
 */





#ifndef _JEU_VEGETATIONS_
#define _JEU_VEGETATIONS_



#include "utilitaire.h"





// Le nombre de type de végétations
#define NB_VEGETATIONS 6





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @enum e_vegetalTag
 * @brief Tag permettant de reconnaitre les végétaux
 */
typedef enum {
    DEBUT_VEGETAL = 99,
    HERBE,
    CHAINE,
    PALMIER,
    SAPIN,
    FIN_VEGETAL,
} e_vegetalTag;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_vegetation
 * @brief Modélise un végétal
 */
typedef struct s_vegetation {
    e_vegetalTag tag;           /**< Le tag du végétal */
    t_vecteur2 position;        /**< La position du végétal */
} t_vegetation;



/**
 * @struct t_baseVegetal
 * @brief Modélise la base d'un végétal
 */
typedef struct s_baseVegetation {
    e_vegetalTag tag;           /**< Le tag du végétal */
    float radius;               /**< Le rayon autour dans lequel il ne peut y avoir de végétal */
} t_baseVegetal;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseVegetal basesVegetaux[];





#endif