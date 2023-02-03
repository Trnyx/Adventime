#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../include/audio.h"
#include "../include/main.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


int main() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("WARNING : Erreur d'initialisation de SDL MIXER : %s\n", Mix_GetError());
    }




    SDL_Window * window;
    window = SDL_CreateWindow("Adventime", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);

    int flags = 0;
    flags |= SDL_RENDERER_ACCELERATED;
    flags |= SDL_RENDERER_PRESENTVSYNC;

    SDL_Renderer * renderer;
    renderer = SDL_CreateRenderer(window, -1, flags);


    Mix_PlayMusic(Mix_LoadMUS("assets/audio/musiques/menu.mp3"), -1);

    SDL_Event evt;
    while (1) {
        while (SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT) {
                goto cleanup;
            }
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }

    cleanup:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}