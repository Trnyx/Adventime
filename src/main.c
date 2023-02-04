#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "../include/initialiseur.h"
#include "../include/moteur.h"
#include "../include/textures.h"
#include "../include/main.h"









int main(int argc, char* argv[]) {

    t_moteur *moteur = NULL;
    t_textures *textures = NULL;

    initAll(&moteur, &textures);



    SDL_Surface *surface = IMG_Load("assets/images/sol_herbe_1.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);

    SDL_Rect taille_texture = { 0, 0, 16, 16 };
    SDL_Rect taille_rendu = { 0, 0, 64, 64 };



    SDL_Event evt;
    while (1) {
        while (SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT) {
                goto cleanup;
            }
            SDL_RenderClear(moteur->renderer);

        

            // On pose les textures
            SDL_RenderCopy(moteur->renderer, texture, &taille_texture, &taille_rendu);


            // On fait le rendu
            SDL_RenderPresent(moteur->renderer);
        }
    }

    cleanup:
    SDL_DestroyRenderer(moteur->renderer);
    SDL_DestroyWindow(moteur->window);
    SDL_Quit();

    return 0;
}