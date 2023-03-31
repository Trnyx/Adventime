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





#define LONGUEUR_ID 8





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @enum booleen
 * @brief 
 */
typedef enum {
    FAUX,
    VRAI
} boolean;


 /**
  * \enum err_sauv
  * \brief Définit les erreurs possibles durant la sauvegarde.
 */
typedef enum
{
    SUCCESS = 0,
    FOPEN_FAIL,
    LOAD_FAIL,
} err_sauv;



/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_vecteur2
 * @brief Structure modélisant un vecteur à deux dimensions
 */
typedef struct s_vecteur2 {
    float x;    /**< La coordonnée x du vecteur */
    float y;    /**< La coordonnée y du vecteur */
} t_vecteur2;



/**
 * @struct t_vecteur3
 * @brief Structure modélisant un vecteur à trois dimensions
 */
typedef struct s_vecteur3 {
    float x;    /** La coordonnée x du vecteur */
    float y;    /** La coordonnée y du vecteur */
    float z;    /** La coordonnée z du vecteur */
} t_vecteur3;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


char* genererId();

int getNombreAleatoire(const int min, const int max);
// int getNombreAvecProbabilite();

float calculDistanceEntrePoints(const t_vecteur2 source, const t_vecteur2 cible);
float calculAngleEntrePoints(const t_vecteur2 source, const t_vecteur2 cible);
float revolution(const float angle);
t_vecteur2 choisirPointDansRayon(const int rayon);





#endif