/**
 * @file joueur.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */



#ifndef _JEU_JOUEUR_
#define _JEU_JOUEUR_





#include "statistiques.h"
#include "inventaire.h"
#include "monstre.h"
#include "entite.h"
#include "map.h"





#define JOUEUR_VITESSE_DEFAUT 6
#define JOUEUR_ATTAQUE_DEFAUT 10
#define JOUEUR_DEFENSE_DEFAUT 10
#define JOUEUR_PV_DEFAUT 20

#define JOUEUR_COOLDOWN_ATTAQUE 1





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 */
typedef struct s_action_flags {
    // Déplacements
    int up;
    int down;
    int left;
    int right;

    // Intéractions
    int interaction;

    // Attaque
    int attack;

    // Autres
    int miniMap;
} t_action_flags;



/**
 * @struct t_joueur
 * @brief Structure modélisant un joueur
 */
typedef struct s_joueur {
    // #include "attributs_entite.h"
    struct s_entiteVivante;

    t_action_flags *actionFlags;    /**< */
    e_mapType map;                  /**< */

    t_boss_flags bossFlags;         /**< */

    int cooldownAttaque;            /**< */
    
} t_joueur;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_joueur* creerJoueur(const t_vecteur2 position);
void detruireJoueur(t_joueur **joueur);





#endif