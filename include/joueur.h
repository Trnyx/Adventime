/*
 * \file 
 *
 * \brief
 *
 * \author
 */



#ifndef _JEU_JOUEUR_
#define _JEU_JOUEUR_



#include <statistiques.h>
#include <inventaire.h>





/*
 * \struct t_joueur
 * \brief Structure modélisant un joueur
 */
typedef struct s_joueur {
    #include <attributs_entite.h>

    char *name;                     /**< Le nom du joueur */
    t_statistiques statistiques;    /**< Les statistiques du joueur */
    t_inventaire inventaire;        /**< L'inventaire du joueur */
    
} t_joueur;





t_joueur creerJoueur();
void detruireJoueur(t_joueur *joueur);





#endif