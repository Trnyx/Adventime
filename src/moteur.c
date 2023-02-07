/**
 * @file moteur.c
 *
 * @brief
 *
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>
#include "../include/moteur.h"
#include "../include/window.h"





void regulerFPS(t_moteur *moteur) {

}





void initControles(t_controles *controles) {
    // Deplacements
    controles->key_up = SDL_SCANCODE_W;
    controles->key_down = SDL_SCANCODE_S;
    controles->key_left = SDL_SCANCODE_A;
    controles->key_right = SDL_SCANCODE_E;

    // Interactions
    controles->interaction = SDL_SCANCODE_F;
    controles->attack = SDL_BUTTON_LEFT;

    // Autres
    controles->escape = SDL_SCANCODE_ESCAPE;
    controles->miniMap = SDL_SCANCODE_TAB;
}





t_moteur* initMoteur() {
    t_moteur *moteur = malloc(sizeof(t_moteur));


    initSDL(moteur);
    initControles(moteur->controles);


    return moteur;
}





void detruireMoteur(t_moteur **moteur) {
    if (moteur != NULL && *moteur != NULL) {

        free((*moteur));
        *moteur = NULL;
        
    }
}





void updateEchelle(t_moteur *moteur) {}





