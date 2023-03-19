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
 * @enum e_monstreType
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
 * @struct t_monstre
 * @brief Modélise un monstre
 */
typedef struct s_monstre {
    struct s_mob;                   /**< On "étend" la structure "mob" */
    
    char* name;                     /**< Le nom du Monstre */
    int rayonDetection;             /**< Le rayon dans lequel le joueur sera détecté ù*/
    e_monstreType type;             /**< Le type du Monstre */
    boolean estNocturne;            /**< Si le monstre est de type nocturne */
} t_monstre;



/**
 * @struct t_baseStatistiquesIntervales
 * @brief Modélise les intervales des statistiques de base d'un monstre
 */
typedef struct s_baseStatistiquesIntervales {
    int attaque[2];         /**< L'intervale pour les statistiques d'attaque */
    int defense[2];         /**< L'intervale pour les statistiques de défense */
    int vitesse[2];         /**< L'intervale pour les statistiques de vitesse */
    int pv;                 /**< L'intervale pour les statistiques des pv */
    int courbeExp[2];       /**< L'intervale pour la courbe de gain de niveau */
} t_baseStatistiquesIntervales;





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