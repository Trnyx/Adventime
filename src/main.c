#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include "../include/initialiseur.h"
#include "../include/moteur.h"
#include "../include/main.h"
#include "../include/monde.h"




SDL_Texture* getTexture(int block, t_textures *textures) {    
    switch (block) {
        case SOL_EAU_PROFONDE: return textures->sol_profondeur;
        case SOL_EAU: return textures->sol_eau;
        case SOL_SABLE: return textures->sol_sable;
        case SOL_HERBE_1: return textures->sol_herbe_1;
        case SOL_HERBE_2: return textures->sol_herbe_2;
        case SOL_HERBE_3: return textures->sol_herbe_3;
        case SOL_MONTAGNE_1: return textures->sol_montagne_1;
        case SOL_MONTAGNE_2: return textures->sol_montagne_2;
        case SOL_NEIGE: return textures->sol_neige;
        
        default:
            break;
    }
}




int main() {

    t_moteur *moteur;

    initAll(&moteur);



    SDL_Event evt;
    while (1) {
        while (SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT) {
                goto cleanup;
            }
            SDL_RenderClear(moteur->renderer);
            SDL_RenderPresent(moteur->renderer);
            SDL_RenderClear(moteur->renderer);
        }
    }

    cleanup:
    SDL_DestroyRenderer(moteur->renderer);
    SDL_DestroyWindow(moteur->window);
    SDL_Quit();

    return 0;
}
