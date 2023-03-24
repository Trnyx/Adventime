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



#include "utilitaire.h"





#define NB_VEGETATIONS 6





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
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





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseVegetal basesVegetaux[];





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */





#endif