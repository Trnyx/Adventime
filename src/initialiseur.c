/**
 * @file initialiseur.c
 * 
 * @brief 
 * 
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>

#include "../include/initialiseur.h"
#include "../include/menus.h"
#include "SDL2/SDL_image.h"
// #include image.h
// #include ttf.h





/**
 * @brief 
 */
void initAll(t_moteur **moteur, t_audio **audio) {
    // Moteur
    *moteur = initMoteur();
    
    t_vecteur2 positionCamera = { 0, 0 };
    (*moteur)->camera = creerCamera(positionCamera);
    (*moteur)->textures = initTextures((*moteur)->renderer);

    SDL_SetRenderDrawBlendMode((*moteur)->renderer, SDL_BLENDMODE_BLEND);

    SDL_Surface * logo = NULL;
    logo = IMG_Load("assets/images/logo.png");
    SDL_SetWindowIcon((*moteur)->window, logo);
    SDL_FreeSurface(logo);


    // Audio
    *audio = initAudio();
    
    
    // SDL Image
    

    // SDL TTF
}



void detruireAll(t_moteur *moteur, t_audio *audio) {
    nk_sdl_shutdown();

    detruireJoueur(&moteur->monde->joueur);
    detruireMonde(&moteur->monde);
    
    detruireCamera(&moteur->camera);
    detruireTextures(&moteur->textures);

    SDL_DestroyRenderer(moteur->renderer);
    SDL_DestroyWindow(moteur->window);
    detruireMoteur(&moteur);

    detruireAudio(&audio);
}
