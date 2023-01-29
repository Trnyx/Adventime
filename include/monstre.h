/**
 * @file monstre.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @version 1.1
 */





#ifndef _JEU_MONSTRE_
#define _JEU_MONSTRE_



#include <statistiques.h>
#include <entite.h>





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 */
typedef enum s_montreTag {
    MONSTRE_OISEAU,
    NB_MONSTRE_TAGS
} e_monstreTag;


/**
 * @brief 
 * 
 */
typedef enum s_monstreType {
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
 * @brief 
 * 
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
 * @brief 
 * 
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