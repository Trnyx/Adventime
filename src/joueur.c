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
#include <math.h>
#include <SDL2/SDL.h>

#include "../include/joueur.h"
#include "../include/camera.h"





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
    t_vecteur2 direction = { 0, 0 };


    if (joueur->actionFlags->right == joueur->actionFlags->left)
        direction.x = 0;
    else if (joueur->actionFlags->left)
        direction.x = -1;
    else if (joueur->actionFlags->right)
        direction.x = 1;
    

    if (joueur->actionFlags->up == -joueur->actionFlags->down)
        direction.y = 0;
    else if (joueur->actionFlags->up)
        direction.y = -1;
    else if (joueur->actionFlags->down)
        direction.y = 1;
    

    joueur->direction = direction;
}




void getOrientationJoueur(t_moteur *moteur, t_joueur *joueur) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    printf("Souris : %i : %i\n", x, y);
    
    float angle = atan2(720 / 2 - y, 1280 / 2 - x) * (180 / M_PI);
    if (angle < 0)
        angle = 360 - (-angle);


    if (angle >= 45 && angle < 135)
        joueur->orientation = NORD;
    else if (angle >= 135 && angle < 225)
        joueur->orientation = EST;
    else if (angle >= 225 && angle < 315)
        joueur->orientation = SUD;
    else
        joueur->orientation = OUEST;


    
    SDL_Log("Angle : %1.0f\n", angle);
}





/**
 * @brief 
 * 
 * @param moteur 
 * @param joueur 
 * @return int 
 */
int updateJoueur(t_moteur *moteur, t_joueur *joueur) {
    // printf("Update Joueur => ");

    if (doitSeDeplacer(joueur->actionFlags)) {
        // printf("Deplacement du joueur (N : %i / S : %i / O : %i / E : %i) => ", joueur->actionFlags->up, joueur->actionFlags->down, joueur->actionFlags->left, joueur->actionFlags->right);

        getDirectionJoueur(joueur);
        deplacerEntite(moteur, (t_entite*) joueur, joueur->statistiques.vitesse);
    }

    getOrientationJoueur(moteur, joueur);

    // printf("Fin Update Joueur\n");
    return 0;
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
    joueur->map = MAP_OVERWORLD;

    joueur->statistiques.vitesse = JOUEUR_VITESSE_DEFAUT;
    joueur->statistiques.attaque = JOUEUR_ATTAQUE_DEFAUT;
    joueur->statistiques.defense = JOUEUR_DEFENSE_DEFAUT;
    joueur->statistiques.pv = JOUEUR_PV_DEFAUT;
    joueur->statistiques.pvMax = JOUEUR_PV_DEFAUT;

    joueur->statistiques.experience = 0;
    joueur->statistiques.niveau = 1;

    joueur->actionFlags = initialiserActionFlags();

    joueur->update = (int(*)(t_moteur*, t_entite*, const float)) updateJoueur;
    joueur->detruire = (void (*)(t_entite**)) detruireJoueur;


    printf("Succes\n");
    entite = NULL;
    return joueur;
};
