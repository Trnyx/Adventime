/**
 * @file joueur.h
 * 
 * @brief Module de manipulation du joueur 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */



#ifndef _JEU_JOUEUR_
#define _JEU_JOUEUR_





#include "inventaire.h"
#include "entite.h"
#include "map.h"





// La statistique "attaque" de base du joueur
#define JOUEUR_BASE_ATTAQUE 25
// La statistique "defense" de base du joueur
#define JOUEUR_BASE_DEFENSE 25
// La statistique "vitesse" de base du joueur
#define JOUEUR_BASE_VITESSE 5
// La statistique "pv" de base du joueur
#define JOUEUR_BASE_PV 45

// Cooldown entre chaque attaque du joueur [en ticks]
#define JOUEUR_COOLDOWN_ATTAQUE 10





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_action_flags
 * @brief Structure de stockage des inputs du joueur 
 */
typedef struct s_action_flags {
    // Déplacements
    int up;       				/**< Le joueur se déplace vers le NORD */
    int down;       			/**< Le joueur se déplace vers le SUD */
    int left;       			/**< Le joueur se déplace vers l'OUEST */
    int right;        			/**< Le joueur se déplace vers l'EST */

    // Inventaire
    int inventory;				/**< Le joueur ouvre/ferme son inventaire */
    int bool_inventory;			/**< L'inventaire est actuellement ouvert */

    // Intéractions
    int interaction;			/**< Le joueur interargit */

    // Attaque
    int attack;					/**< Le joueur attaque */

    // Autres
    int miniMap;				/**< Le joueur affiche la mini map*/
} t_action_flags;



/**
 * @struct t_joueur
 * @brief Structure modélisant un joueur
 */
typedef struct s_joueur {
    struct s_entiteVivante;         /**< On "étend" la structure "entiteVivante" */

    // Localisation
    e_mapType map;                  /**< La map dans laquelle le joueur se situe */

    // Inventaire
    t_inventaire *inventaire;       /**< L'inventaire du joueur */
    int slotSelectionne;            /**< Le slot selectionne par le joueur */

    // Input
    t_action_flags *actionFlags;    /**< Les inputs du joueur */    
} t_joueur;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_joueur* creerJoueur(const t_vecteur2 position);
void updateJoueur(t_joueur *joueur);
void detruireJoueur(t_joueur **joueur);

t_action_flags* initialiserActionFlags();

void mortJoueur(t_joueur *joueur);
void reapparitionJoueur(t_joueur *joueur, const t_vecteur2 position);





#endif
