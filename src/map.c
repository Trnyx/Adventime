/**
 * @file camera.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 5 février
 * @version 1.1
 */



#include <stdlib.h>
#include <stdio.h>

#include "../include/moteur.h"
#include "../include/map.h"
#include "../include/vegetations.h"
#include "../include/camera.h"





/* -------------------------------------------------------------------------- */
/*                                    Rendu                                   */
/* -------------------------------------------------------------------------- */


/* ----------------------------------- Sol ---------------------------------- */


int dessinerBlockSol(t_moteur *moteur, const int tag, SDL_Rect *rendu) {
    SDL_Rect source;


    switch (tag) {
        case SOL_EAU_PROFONDE:
        case SOL_EAU:
        case SOL_SABLE:
        case SOL_HERBE_1:
        case SOL_HERBE_2:
        case SOL_HERBE_3:
        case SOL_MONTAGNE_1:
        case SOL_MONTAGNE_2:
            splitTexture(&source, (8 + 2 * TAILLE_TILE * tag),8, TAILLE_TILE,TAILLE_TILE);
            break;
        default:
            return SDL_RenderCopy(moteur->renderer, moteur->textures->null, NULL, rendu);
    }


    return SDL_RenderCopy(moteur->renderer, moteur->textures->sol, &source, rendu);
}



/**
 * @brief 
 * 
 * @param moteur 
 * @param origine 
 * @param offset 
 * @param rendu 
 */
void dessinerSol(t_moteur *moteur, SDL_Rect *rendu) {
    t_camera *camera = moteur->camera;

    for (float x = camera->origine.x - 1; x <= camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 1; x++) {
        for (float y = camera->origine.y - 1; y <= camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 1; y++) {
            rendu->x = positionRelativeEnPositionSurEcran(x, camera->offset.x, camera->origine.x, rendu->w) + rendu->w;
            rendu->y = positionRelativeEnPositionSurEcran(y, camera->offset.y, camera->origine.y, rendu->h) + rendu->h;


            t_block *block = getBlockDansMap(x, y, COUCHE_SOL, moteur->monde->map);
            if (block == NULL) {
                SDL_RenderCopy(moteur->renderer, moteur->textures->null, NULL, rendu);
                continue;
            }


            // SDL_Texture *texture = getTexture(block->tag, moteur->textures);
            // if (texture == NULL) continue;

            // SDL_Rect source = dessinerSol(moteur, block->tag, rendu);
            dessinerBlockSol(moteur, block->tag, rendu);


            // SDL_RenderCopy(moteur->renderer, moteur->textures->sol, &source, &rendu);
        }
    }
}





/* ------------------------------- Vegetations ------------------------------ */


int dessinerVegetal(t_moteur *moteur, const int tag, SDL_Rect *rendu) {
    SDL_Rect source;
    SDL_Rect renduVegetaux;


    switch (tag) {
        case HERBE:
            splitTexture(&source, 0,0, TAILLE_TILE,TAILLE_TILE);
            break;
        case CHAINE:
            splitTexture(&source, (2 * TAILLE_TILE * (tag % HERBE)),0, 3*TAILLE_TILE,2*TAILLE_TILE);
            break;


        default:
            break;
    }


    renduVegetaux.x = rendu->x - rendu->w;
    renduVegetaux.y = rendu->y - rendu->h;
    renduVegetaux.w = 3 * rendu->w;
    renduVegetaux.h = 2 * rendu->h;
    
    return SDL_RenderCopy(moteur->renderer, moteur->textures->vegetaux, &source, &renduVegetaux);
}



/**
 * @brief 
 * 
 * @param moteur 
 * @param origine 
 * @param offset 
 * @param rendu 
 */
void dessinerVegetation(t_moteur *moteur, SDL_Rect *rendu) {
    t_camera *camera = moteur->camera;

    for (float x = camera->origine.x - 1; x <= camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 1; x++) {
        for (float y = camera->origine.y - 1; y <= camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 1; y++) {
            rendu->x = positionRelativeEnPositionSurEcran(x, camera->offset.x, camera->origine.x, rendu->w) + rendu->w;
            rendu->y = positionRelativeEnPositionSurEcran(y, camera->offset.y, camera->origine.y, rendu->h) + rendu->h;


            t_block *block = getBlockDansMap(x, y, COUCHE_VEGETATION, moteur->monde->map);
            if (block == NULL) continue;
            if (block->tag == VIDE) continue;


            dessinerVegetal(moteur, block->tag, rendu);
        }
    }
}
