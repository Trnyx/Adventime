/**
 * @file statisitques.h
 *
 * @brief Module de manipulation des statistiques
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.3
 */





#ifndef _JEU_STATISTIQUES_
#define _JEU_STATISTIQUES_





#include "temps.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @enum e_courbeExperience
 * @brief Enumération regroupant les différentes type de courbe d'expérience
 */
typedef enum {
    /*! Indique que la vitesse de progression des niveaux est lente */
    EXPERIENCE_LENT,
    /*! Indique que la vitesse de progression des niveaux est moyenne */
    EXPERIENCE_MOYEN,
    /*! Indique que la vitesse de progression des niveaux est rapide */
    EXPERIENCE_RAPIDE,
} e_courbeExperience;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_statistiques
 * @brief Structure regroupant les différentes statistiques
 */
typedef struct s_statistiques {
    #include "attributs_statistiques.h"

    unsigned int pvMax;         /**< Le nombre de point de vie maximum */
    unsigned int experience;    /**< Le nombre de point d'expèrience */
    unsigned int niveau;        /**< Le nombre de niveau */
} t_statistiques;



/**
 * @struct t_baseStatistiques
 * @brief Structure regroupant les différentes statistiques de base
 */
typedef struct s_baseStatistiques {
    #include "attributs_statistiques.h"
    
    e_courbeExperience experience_courbe;   /**< Le type de courbe d'expèrience */
} t_baseStatistiques;





/**
 * @struct t_baseStatistiquesIntervales
 * @brief Modélise les intervales des statistiques de base
 */
typedef struct s_baseStatistiquesIntervales {
    int attaque[2];         /**< L'intervale pour les statistiques d'attaque */
    int defense[2];         /**< L'intervale pour les statistiques de défense */
    int vitesse[2];         /**< L'intervale pour les statistiques de vitesse */
    int pv;                 /**< L'intervale pour les statistiques des pv */
    int courbeExp[2];       /**< L'intervale pour la courbe de gain de niveau */
} t_baseStatistiquesIntervales;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


int calculStatistique(const int base, const int niveau);
int calculPv(const int attaque, const int defense, const int basePv);

t_statistiques genererStatistiques(const t_baseStatistiques baseStatistiques, const int niveau);
t_baseStatistiques genererStatistiquesDeBaseBoss(const e_jour jour);
t_baseStatistiques genererStatistiquesDeBaseJoueur();





#endif