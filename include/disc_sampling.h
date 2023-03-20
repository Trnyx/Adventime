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
/*                                Enumerateurs                                */
/* -------------------------------------------------------------------------- */


typedef enum {
    DISC_CENTRE,
    DISC_ALEATOIRE,
} e_disc_methode_gen;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_discSampling
 * @brief Structure représentant une grille généré avec l'algorithme Poisson Disc Sampling
 * 
 */
typedef struct s_discSampling {
    t_vecteur2 minGrille;           /**< Les coordonnées "minimum" (angle haut gauche) de la grille */
    t_vecteur2 maxGrille;           /**< Les coordonnées "maximum" (angle bas droit) de la grille */
    
    int nbElements;                 /**< Le nombre d'éléments contenus dans la grille */
    t_vecteur2 *elementPositions;   /**< Les positions des éléments dans la grille */
} t_discSampling;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_discSampling genererGrilleDiscSampling(const t_vecteur2 minGrille, const t_vecteur2 maxGrille, int nbElementsObjectif, float rayon, const e_disc_methode_gen methode);





#endif