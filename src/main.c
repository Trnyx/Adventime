#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "../include/initialiseur.h"
#include "../include/textures.h"
#include "../include/moteur.h"
#include "../include/main.h"
#include "../include/monde.h"
#include "../include/joueur.h"





#define TAILLE_BLOCK 4





int main(int argc, char* argv[]) {

    t_moteur *moteur = NULL;

    initAll(&moteur);



    int seed = -1;

    t_monde *monde = creerMonde(seed);
    t_map *map = monde->map;

    t_vecteur2 positionJoueur = getPointApparitionJoueur(map);
    t_joueur *joueur = creerJoueur(positionJoueur);


    // SDL_Surface *surface = IMG_Load("assets/images/sol_herbe_1.png");
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);

    SDL_Rect taille_texture = { 0, 0, 16, 16 };
    SDL_Rect rendu;

    rendu.h = TAILLE_BLOCK;
    rendu.w = TAILLE_BLOCK;
    // SDL_Rect taille_rendu = { 0, 0, 64, 64 };



    SDL_Event evt;
    while (1) {
        while (SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT) {
                goto cleanup;
            }
            SDL_RenderClear(moteur->renderer);

        

            // On pose les textures
            for (int xChunk = 0; xChunk < TAILLE_MAP; xChunk++) {
                for (int yChunk = 0; yChunk < TAILLE_MAP; yChunk++) {

                    t_chunk *chunk = getChunk(xChunk, yChunk, COUCHE_SOL, map);
                    if (chunk == NULL) continue;


                    for (int xBlock = 0; xBlock < TAILLE_CHUNK; xBlock++) {
                        for (int yBlock = 0; yBlock < TAILLE_CHUNK; yBlock++) {

                            t_block *block = getBlockDansChunk(xBlock, yBlock, chunk);
                            if (block == NULL) continue;


                            SDL_Texture *texture = getTexture(block->tag, moteur->textures);
                            if (texture == NULL) continue;

                            // rendu; // = { block->position.x, block->position.y, TAILLE_BLOCK, TAILLE_BLOCK };
                            // rendu.x = block->position.x * TAILLE_BLOCK;
                            rendu.x = (TAILLE_CHUNK * xChunk + xBlock) * TAILLE_BLOCK;
                            rendu.y = (TAILLE_CHUNK * yChunk + yBlock) * TAILLE_BLOCK;

                            // printf("BLOCK => %i\n", block->tag);
                            SDL_RenderCopy(moteur->renderer, texture, NULL, &rendu);
                        }   
                    }
                    
                }
            }
            

            rendu.x = joueur->position.x * TAILLE_BLOCK;
            rendu.y = joueur->position.y * TAILLE_BLOCK;
            SDL_RenderCopy(moteur->renderer, moteur->textures->joueur, NULL, &rendu);


            // On fait le rendu
            SDL_RenderPresent(moteur->renderer);
            SDL_RenderClear(moteur->renderer);
        }
    }

    cleanup:
    detruireMonde(&monde);
    detruireJoueur(&joueur);
    SDL_DestroyRenderer(moteur->renderer);
    SDL_DestroyWindow(moteur->window);
    SDL_Quit();

    return 0;
}
