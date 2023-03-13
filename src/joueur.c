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

#include "../include/moteur.h"
#include "../include/joueur.h"
#include "../include/camera.h"
#include "../include/combat.h"





/* -------------------------------------------------------------------------- */
/*                                Verifications                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param joueur 
 * @return boolean 
 */
boolean peutAttaquer(t_joueur *joueur) {
    return !(joueur->cooldownAttaque);
}



/**
 * @brief 
 * 
 * @param flags 
 * @return boolean 
 */
boolean doitAttaquer(t_action_flags *flags) {
    return flags->attack == 1;
}



/**
 * @brief 
 * 
 * @param flags 
 * @return boolean 
 */
boolean doitSeDeplacer(t_action_flags *flags) {
    return flags->up || flags->down || flags->left || flags->right;
}





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


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




float getOrientationJoueur(t_joueur *joueur) {
    const t_vecteur2 centreEcran = {
        moteur->window_width / 2,
        moteur->window_height / 2,
    };

    return calculAngleEntrePoints(centreEcran, moteur->positionSouris);
}





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


void joueurAttaque(t_joueur *joueur, const float angleAttaque) {
    printf("JOUEUR ATTAQUE (angle : %1.2f)\n", angleAttaque);
    joueur->cooldownAttaque = JOUEUR_COOLDOWN_ATTAQUE;
    t_liste mobsAlentour = getEntitesAlentour((t_entite*)joueur, ENTITE_MOB, 2.0);

    if (!liste_vide(&mobsAlentour)) {
        printf("ENTITE PROCHE\n");
        en_tete(&mobsAlentour);
        t_mob *mob = NULL;

        while (!hors_liste(&mobsAlentour)) {
            valeur_elt(&mobsAlentour, (t_entite**)&mob);
            metUnCoup((t_entiteVivante*)joueur, (t_entiteVivante*)mob, angleAttaque, 2.0);

            suivant(&mobsAlentour);
        }
    }
    else {
        printf("AUCUNE ENTITE PROCHE\n");
    }
}





/**
 * @brief 
 * 
 * @param joueur 
 * @return int 
 */
int updateJoueur(t_joueur *joueur) {
    if (joueur->cooldownAttaque > 0) {
        (joueur->cooldownAttaque)--;
    }


    if (doitSeDeplacer(joueur->actionFlags)) {
        joueur->operation = SE_DEPLACE_VERS;
        getDirectionJoueur(joueur);
        deplacerEntite((t_entite*)joueur, joueur->statistiques.vitesse);
    } else {
        joueur->operation = ATTENTE;
    }

    const float angle = getOrientationJoueur(joueur);
    orienterEntite(angle, (t_entite*)joueur);


    if (doitAttaquer(joueur->actionFlags) && peutAttaquer(joueur)) {
        joueur->operation = ATTAQUE;
        joueurAttaque(joueur, angle);
    } else if (joueur->operation != SE_DEPLACE_VERS) {
        joueur->operation = ATTENTE;
    }


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
    else {
        printf("PAS DE JOUEUR => ");
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
    flags->attack = 0;
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

    // Statistiques
    joueur->statistiques.vitesse = JOUEUR_VITESSE_DEFAUT;
    joueur->statistiques.attaque = JOUEUR_ATTAQUE_DEFAUT;
    joueur->statistiques.defense = JOUEUR_DEFENSE_DEFAUT;
    joueur->statistiques.pv = JOUEUR_PV_DEFAUT;
    joueur->statistiques.pvMax = JOUEUR_PV_DEFAUT;

    joueur->statistiques.experience = 0;
    joueur->statistiques.niveau = 1;

    // Actions
    joueur->actionFlags = initialiserActionFlags();

    // Animation
    joueur->animation = creerAnimation(100, 4);

    // Fonctions
    joueur->update = (int(*)(t_entite*, const float, t_entite*)) updateJoueur;
    joueur->detruire = (void (*)(t_entite**)) detruireJoueur;

    // Timer
    joueur->cooldownAttaque = 0;
    joueur->destructionInactif = FAUX;


    printf("Succes\n");
    entite = NULL;
    return joueur;
};
