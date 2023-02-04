/**
 * @file textures.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 3 février
 * @version 1.0
 */



#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

#include "../include/textures.h"





t_textures* initTextures(SDL_Renderer *renderer) {
    t_textures *textures = malloc(sizeof(t_textures));
    SDL_Surface *surface = NULL;


    /* ----------------------------------- Map ---------------------------------- */
    // assets/images/.png

    surface = IMG_Load("assets/images/sol_profondeur.png");
    textures->sol_profondeur = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("assets/images/sol_eau.png");
    textures->sol_eau = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("assets/images/sol_sable.png");
    textures->sol_sable = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("assets/images/sol_herbe_1.png");
    textures->sol_herbe_1 = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("assets/images/sol_herbe_2.png");
    textures->sol_herbe_2 = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("assets/images/sol_herbe_3.png");
    textures->sol_herbe_3 = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("assets/images/sol_montagne_1.png");
    textures->sol_montagne_1 = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("assets/images/sol_montagne_2.png");
    textures->sol_montagne_2 = SDL_CreateTextureFromSurface(renderer, surface);

    // surface = IMG_Load("assets/images/sol_neige.png");
    // textures->sol_neige = SDL_CreateTextureFromSurface(renderer, surface);

    

    /* -------------------------------- Végétaux -------------------------------- */


    /* --------------------------------- Joueur --------------------------------- */


    /* -------------------------------- Monstres -------------------------------- */


    /* --------------------------------- Animaux -------------------------------- */


    /* --------------------------------- Autres --------------------------------- */


    return textures;
}





void detruireTextures(t_textures **textures) {
    if (textures != NULL && *textures != NULL) {

        // Map
        if ((*textures)->sol_profondeur != NULL) 
            SDL_DestroyTexture((*textures)->sol_profondeur);
        if ((*textures)->sol_eau != NULL) 
            SDL_DestroyTexture((*textures)->sol_eau);
        if ((*textures)->sol_sable != NULL) 
            SDL_DestroyTexture((*textures)->sol_sable);
        if ((*textures)->sol_herbe_1 != NULL) 
            SDL_DestroyTexture((*textures)->sol_herbe_1);
        if ((*textures)->sol_herbe_2 != NULL) 
            SDL_DestroyTexture((*textures)->sol_herbe_2);
        if ((*textures)->sol_herbe_3 != NULL) 
            SDL_DestroyTexture((*textures)->sol_herbe_3);
        if ((*textures)->sol_montagne_1 != NULL) 
            SDL_DestroyTexture((*textures)->sol_montagne_1);
        if ((*textures)->sol_montagne_2 != NULL) 
            SDL_DestroyTexture((*textures)->sol_montagne_2);
        if ((*textures)->sol_neige != NULL) 
            SDL_DestroyTexture((*textures)->sol_neige);

        // Végétaux
        if ((*textures)->vegetaux_herbe != NULL) 
            SDL_DestroyTexture((*textures)->vegetaux_herbe);
        if ((*textures)->vegetaux_chene != NULL) 
            SDL_DestroyTexture((*textures)->vegetaux_chene);
        
        // Joueur
        if ((*textures)->joueur != NULL) 
            SDL_DestroyTexture((*textures)->joueur);

        // Monstres
        if ((*textures)->monstres != NULL) 
            SDL_DestroyTexture((*textures)->monstres);


        free(*textures);
        *textures = NULL;

    }
}