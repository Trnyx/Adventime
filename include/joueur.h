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
#include "entite.h"





#define JOUEUR_VITESSE_DEFAUT 6
#define JOUEUR_ATTAQUE_DEFAUT 10
#define JOUEUR_DEFENSE_DEFAUT 10
#define JOUEUR_PV_DEFAUT 20





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_joueur
 * @brief Structure modélisant un joueur
 */
typedef struct s_joueur {
    #include "attributs_entite.h"

    t_statistiques statistiques;    /**< Les statistiques du joueur */
    // t_inventaire *inventaire;        /**< L'inventaire du joueur */

    
} t_joueur;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_joueur* creerJoueur(t_vecteur2 position);
void detruireJoueur(t_joueur **joueur);





#endif