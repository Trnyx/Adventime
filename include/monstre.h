/**
 * @file monstre.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.3
 */





#ifndef _JEU_MONSTRE_
#define _JEU_MONSTRE_





#include "mob.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */



/**
 * @brief Enumérateur regroupant les différents types des monstres
 * 
 * Un compteur du nombre de types est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    MONSTRE_TYPE_NORMAL,
    MONSTRE_TYPE_PLANTE,
    MONSTRE_TYPE_MONTAGNARD,
    // MONSTRE_TYPE_DESERTIQUE,
    NB_MONSTRE_TYPES,
} e_monstreType;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Modélise un monstre
 */
typedef struct s_monstre {
    // #include "attributs_entite.h"
    struct s_mob;
    
    char* name;                             /**< Le nom d'un Monstre */
    int rayonDetection;                     /**< Le rayon dans lequel le joueur sera détecté ù*/
    e_monstreType type;                     /**< Le type du Monstre */
    boolean estNocturne;
} t_monstre;



/**
 * @brief Modélise les intervales des statistiques de base d'un monstre
 */
typedef struct s_baseStatistiquesIntervales {
    int attaque[2];         /**< */
    int defense[2];         /**< */
    int vitesse[2];         /**< */
    int pv;                 /**< */
    int courbeExp[2];       /**< */
} t_baseStatistiquesIntervales;





/**
 * @brief 
 * 
 */
typedef struct s_boss_flags {
    unsigned int lundi;
    unsigned int mercredi;
    unsigned int vendredi;
} t_boss_flags;




/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseStatistiquesIntervales statistiquesDeBasesIntervalesMonstres[NB_MONSTRE_TYPES];





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */
#include "map.h"
typedef struct s_map t_map;


t_baseStatistiques genererStatistiquesDeBaseMonstre(const e_monstreType type);

t_monstre* genererMonstre(t_monstre *monstre, const e_biome biome, const int niveauJoueur);
t_monstre* creerMonstre(const t_vecteur2 position, const e_biome biome, const int niveauJoueur);
void apparitionMonstre(t_liste *entites, t_map *map, const t_vecteur2 positionJoueur, const int niveauJoueur);

void detruireMonstre(t_monstre **monstre);





#endif