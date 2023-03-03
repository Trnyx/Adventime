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





/* ----------------------------- Pointeur Global ---------------------------- */

t_moteur *moteur = NULL;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void regulerFPS() {
    int tempsEcoule = SDL_GetTicks() - moteur->frame;
    if (TPS > tempsEcoule) 
        SDL_Delay(TPS - tempsEcoule);
    moteur->frame = SDL_GetTicks();
}





void initControles(t_controles *controles) {
    // Deplacements
    controles->key_up = SDL_SCANCODE_W;
    controles->key_down = SDL_SCANCODE_S;
    controles->key_left = SDL_SCANCODE_A;
    controles->key_right = SDL_SCANCODE_D;

    // Interactions
    controles->interaction = SDL_SCANCODE_F;
    controles->attack = SDL_BUTTON_LEFT;

    // Autres
    controles->escape = SDL_SCANCODE_ESCAPE;
    controles->miniMap = SDL_SCANCODE_TAB;
}





t_moteur* initMoteur() {
    t_moteur *m = malloc(sizeof(t_moteur));

    if (m == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour le moteur\n");
        free(m);
        return NULL;
    }

    initSDL(m);

    m->camera = NULL;
    m->textures = NULL;
    initControles(&m->controles);
    
    m->monde = NULL;

    m->frame = SDL_GetTicks();


    return m;
}





void detruireMoteur(t_moteur **moteur) {
    printf("Destruction Moteur => ");
    if (moteur != NULL && *moteur != NULL) {

        free((*moteur));
        *moteur = NULL;
        
    }
    printf("Succes\n");
}





void updateEchelle() {

    SDL_GetWindowSize(moteur->window, &moteur->window_width, &moteur->window_height);
  
}





