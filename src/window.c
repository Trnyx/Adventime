/**
 * @file window.c
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







/**
 * @brief 
 * 
 * @return int 
 */
void initSDL(t_moteur *moteur) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }



    SDL_Window *window;
    window = SDL_CreateWindow("Adventime", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);


    int flags = 0;
    flags |= SDL_RENDERER_ACCELERATED;
    flags |= SDL_RENDERER_PRESENTVSYNC;


    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, flags);



    moteur->window = window;
    moteur->renderer = renderer;
    moteur->window_height = WINDOW_HEIGHT;
    moteur->window_width = WINDOW_WIDTH;
}
