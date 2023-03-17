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





#define JOUEUR_VITESSE_DEFAUT 5
#define JOUEUR_ATTAQUE_DEFAUT 20
#define JOUEUR_DEFENSE_DEFAUT 20
#define JOUEUR_PV_DEFAUT 40

#define JOUEUR_COOLDOWN_ATTAQUE 10





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

    int timestampAttaque;           /**< */
    unsigned int cooldownAttaque;   /**< */
    
} t_joueur;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_joueur* creerJoueur(const t_vecteur2 position);
int updateJoueur(t_joueur *joueur);
void detruireJoueur(t_joueur **joueur);

void mortJoueur(t_joueur *joueur);
void reapparitionJoueur(t_joueur *joueur, const t_vecteur2 position);





#endif