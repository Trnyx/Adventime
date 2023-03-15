/**
 * @file disc_sampling.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 15 mars
 * @version 1.1
 */





#ifndef _JEU_DISC_SAMPLING_
#define _JEU_DISC_SAMPLING_





#include "utilitaire.h"





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 */
typedef struct s_discSampling {
    t_vecteur2 minGrille;
    t_vecteur2 maxGrille;
    
    int nbElements;
    t_vecteur2 *elementPositions;
} t_discSampling;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_discSampling genererGrilleDiscSampling(const t_vecteur2 minGrille, const t_vecteur2 maxGrille, int nbElementsObjectif, float rayon);





#endif