#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include "../include/initialiseur.h"
#include "../include/moteur.h"
#include "../include/main.h"









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
        }
    }

    cleanup:
    SDL_DestroyRenderer(moteur->renderer);
    SDL_DestroyWindow(moteur->window);
    SDL_Quit();

    return 0;
}

    return 0;
}