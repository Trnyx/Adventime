/**
 * @file monstre.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.1
 */





#ifndef _JEU_MONSTRE_
#define _JEU_MONSTRE_



#include "map.h"
#include "statistiques.h"
#include "entite.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Enumérateur regroupant les différents tags des monstres
 * 
 * Un compteur du nombre de tags est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    MONSTRE_OISEAU,
    NB_MONSTRE_TAGS
} e_monstreTag;


/**
 * @brief Enumérateur regroupant les différents types des monstres
 * 
 * Un compteur du nombre de types est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    MONSTRE_TYPE_NORMAL,
    MONSTRE_TYPE_PLANTE,
    MONSTRE_TYPE_EAU,
    MONSTRE_TYPE_MONTAGNARD,
    NB_MONSTRE_TYPES,
} e_monstreType;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Modélise un monstre
 */
typedef struct s_monstre {
    struct entite_s;
    
    char* name;                             /**< Le nom d'un Monstre */

    e_monstreTag tag;                       /**< Le tag du Monstre */
    e_monstreType type;                     /**< Le type du Monstre */
    
    t_statistiques statistiques;            /**< Les statistiques du Monstre */
    t_baseStatistiques baseStatistiques;    /**< Les statistiques de base du Monster */
} t_monstre;



/**
 * @brief Modélise les intervales des statistiques de base d'un monstre
 */
typedef struct s_baseStatistiquesIntervales {
    int attaque[2];
    int defense[2];
    int vitesse[2];
    int pv;
    int courbeExp[2];
} t_baseStatistiquesIntervales;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseStatistiquesIntervales statistiquesDeBasesIntervales[NB_MONSTRE_TYPES];





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_monstre creerMonstre(const int x, const int y, e_biome biome);





#endif