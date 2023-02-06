/**
 * @file joueur.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#include "../include/joueur.h"





void detruireJoueur(t_joueur **joueur) {
    if (joueur != NULL && *joueur != NULL) {
        free(*joueur);
        *joueur = NULL;
    }
};





t_joueur* creerJoueur(t_vecteur2 position) {
    t_joueur *joueur = malloc(sizeof(t_joueur));
    t_entite *entite = creerEntite(position);


    joueur->position = entite->position;
    joueur->orientation = entite->orientation;
    joueur->entiteType = ENTITE_JOUEUR;

    joueur->statistiques.vitesse = JOUEUR_VITESSE_DEFAUT;
    joueur->statistiques.attaque = JOUEUR_ATTAQUE_DEFAUT;
    joueur->statistiques.defense = JOUEUR_DEFENSE_DEFAUT;

    joueur->statistiques.pv = JOUEUR_PV_DEFAUT;
    joueur->statistiques.pvMax = JOUEUR_PV_DEFAUT;

    joueur->statistiques.experience = 0;
    joueur->statistiques.niveau = 0;


    joueur->detruire = (void (*)(t_entite**)) detruireJoueur;


    entite = NULL;
    return joueur;
};
