/**
 * @file 
 *
 * @brief
 *
 * @author
 */



#ifndef _JEU_JOUEUR_
#define _JEU_JOUEUR_



#include "statistiques.h"
#include "inventaire.h"
#include "entite.h"





/**
 * @struct t_joueur
 * @brief Structure modélisant un joueur
 */
typedef struct s_joueur {
    struct s_entite;

    char *name;                     /**< Le nom du joueur */
    t_statistiques statistiques;    /**< Les statistiques du joueur */
    t_inventaire inventaire;        /**< L'inventaire du joueur */
    
} t_joueur;





t_joueur* creerJoueur(const int x, const int y);
void detruireJoueur(t_joueur *joueur);





#endif