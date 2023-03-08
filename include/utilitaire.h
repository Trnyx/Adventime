/**
 * @file utilitaire.h
 *
 * @brief
 *
 * @author Clément Hibon, Julien Houget
 * @date 21 janvier
 * @version 1.3
 */



#ifndef _JEU_UTILS_
#define _JEU_UTILS_





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 */
typedef enum {
    FAUX,
    VRAI
} boolean;



/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct
 * @brief
 */
typedef struct s_vecteur2 {
    float x;
    float y;
} t_vecteur2;



/**
 * @struct
 * @brief
 */
typedef struct s_vecteur3 {
    float x;
    float y;
    float z;
} t_vecteur3;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


int getNombreAleatoire(const int min, const int max);
// int getNombreAvecProbabilite();

float calculDistanceEntrePoints(const t_vecteur2 source, const t_vecteur2 cible);
float calculAngleEntrePoints(const t_vecteur2 source, const t_vecteur2 cible);
float revolution(const float angle);
t_vecteur2 choisirPointDansRayon(const int rayon);





#endif