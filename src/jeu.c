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
#include "../include/physique.h"
#include "../include/initialiseur.h"
#include "../include/textures.h"
#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/main.h"
#include "../include/monde.h"
#include "../include/joueur.h"
#include "../include/input_manager.h"







static int nouveauMonde() {
    int seed = -1;
    t_monde *monde = creerMonde(seed);
    moteur->monde = monde;

    const t_vecteur2 positionJoueur = getPointApparitionJoueur(monde->map);
    monde->joueur = creerJoueur(positionJoueur);

    updateCamera(monde->joueur->position);


    int continuer = 1;
    while (continuer != -1) {
        continuer = inputManager(moteur->monde->joueur);
        update();
    }

    return continuer;
}





/**
 * @brief 
 * 
 * @param action 
 * @return state_main 
 */
state_main jouer(e_actionMonde action) {
    switch (action) {
        default:
            nouveauMonde();
            break;
    }


    return JEU_QUITTER;
}