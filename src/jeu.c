/**
 * @file jeu.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 2 mars
 * @version 1.1
 */




#include <stdlib.h>
#include <stdio.h>

#include "../include/main.h"
#include "../include/jeu.h"
#include "../include/monde.h"







static int nouveauMonde(t_moteur *moteur, t_audio *audio) {
    int seed = -1;
    t_monde *monde = creerMonde(seed);
    moteur->monde = monde;

    const t_vecteur2 positionJoueur = getPointApparitionJoueur(monde->map);
    monde->joueur = creerJoueur(positionJoueur);

    moteur->camera->position = monde->joueur->position;


    int continuer = 1;
    while (continuer != -1) {
        continuer = inputManager(moteur->monde->joueur, moteur);
        update(moteur, audio);
    }

    return continuer;
}





/**
 * @brief 
 * 
 * @param action 
 * @param moteur 
 * @param audio 
 * @return state_main 
 */
state_main jouer(e_actionMonde action, t_moteur *moteur, t_audio *audio) {
    switch (action) {
        default:
            nouveauMonde(moteur, audio);
            break;
    }


    return JEU_QUITTER;
}