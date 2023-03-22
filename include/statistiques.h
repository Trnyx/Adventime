/**
 * @file statisitques.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.3
 */





#ifndef _JEU_STATISTIQUES_
#define _JEU_STATISTIQUES_





#include "temps.h"





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_statistiques
 * @brief 
 */
typedef struct s_statistiques {
    #include "attributs_statistiques.h"

    unsigned int pvMax;
    unsigned int experience;
    unsigned int niveau;
} t_statistiques;



/**
 * @struct t_baseStatistiques
 * @brief 
 */
typedef struct s_baseStatistiques {
    #include "attributs_statistiques.h"
    
    unsigned int experience_courbe;
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





#endif