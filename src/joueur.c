/**
 * @file joueur.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/joueur.h"





/**
 * @brief 
 * 
 * @param flags 
 * @return boolean 
 */
boolean doitSeDeplacer(t_action_flags *flags) {
    return flags->up || flags->down || flags->left || flags->right;
}



/**
 * @brief Get the Direction Joueur object
 * 
 * @param joueur 
 */
void getDirectionJoueur(t_joueur *joueur) {
    t_vecteur2 orientation = { 0, 0 };


    if (joueur->actionFlags->right == joueur->actionFlags->left)
        orientation.x = 0;
    else if (joueur->actionFlags->left)
        orientation.x = -1;
    else if (joueur->actionFlags->right)
        orientation.x = 1;
    

    if (joueur->actionFlags->up == -joueur->actionFlags->down)
        orientation.y = 0;
    else if (joueur->actionFlags->up)
        orientation.y = -1;
    else if (joueur->actionFlags->down)
        orientation.y = 1;
    

    joueur->orientation = orientation;
}



/**
 * @brief 
 * 
 * @param moteur 
 * @param joueur 
 * @return int 
 */
int updateJoueur(t_moteur *moteur, t_joueur *joueur) {
    printf("Update Joueur => ");

    if (doitSeDeplacer(joueur->actionFlags)) {
        printf("Deplacement du joueur (N : %i / S : %i / O : %i / E : %i) => ", joueur->actionFlags->up, joueur->actionFlags->down, joueur->actionFlags->left, joueur->actionFlags->right);

        getDirectionJoueur(joueur);
        deplacerEntite(moteur, (t_entite*) joueur, joueur->statistiques.vitesse);
    }

    printf("Fin Update Joueur\n");
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param flags 
 */
void detruireActionFlags(t_action_flags **flags) {
    if (flags != NULL && *flags != NULL) {
        free(*flags);
        *flags = NULL;
    }
}



/**
 * @brief 
 * 
 * @param joueur 
 */
void detruireJoueur(t_joueur **joueur) {
    if (joueur != NULL && *joueur != NULL) {
        detruireActionFlags(&(*joueur)->actionFlags);
        detruireEntite((t_entite**) joueur);
    }
};





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @return t_action_flags* 
 */
t_action_flags* initialiserActionFlags() {
    t_action_flags *flags = malloc(sizeof(t_action_flags));

    flags->up = 0;
    flags->down = 0;
    flags->left = 0;
    flags->right = 0;
    flags->interaction = 0;
    flags->miniMap = 0;

    return flags;
}





/**
 * @brief 
 * 
 * @param position 
 * @return t_joueur* 
 */
t_joueur* creerJoueur(const t_vecteur2 position) {
    printf("Creation du joueur (%1.0f:%1.0f) => ", position.x, position.y);
    t_entite *entite = creerEntite(position);
    t_joueur *joueur = realloc(entite, sizeof(t_joueur));


    joueur->entiteType = ENTITE_JOUEUR;

    joueur->statistiques.vitesse = JOUEUR_VITESSE_DEFAUT;
    joueur->statistiques.attaque = JOUEUR_ATTAQUE_DEFAUT;
    joueur->statistiques.defense = JOUEUR_DEFENSE_DEFAUT;
    joueur->statistiques.pv = JOUEUR_PV_DEFAUT;
    joueur->statistiques.pvMax = JOUEUR_PV_DEFAUT;

    joueur->statistiques.experience = 0;
    joueur->statistiques.niveau = 0;

    joueur->actionFlags = initialiserActionFlags();

    joueur->update = (int    (*)(t_moteur*, t_entite*, const float)) updateJoueur;
    joueur->detruire = (void (*)(t_entite**)) detruireJoueur;


    printf("Succes\n");
    entite = NULL;
    return joueur;
};
