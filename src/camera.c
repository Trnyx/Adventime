/**
 * @file camera.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 5 février
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>

#include "../include/moteur.h"
#include "../include/camera.h"




#define TAILLE_TEXTURE 16
void afficherCamera(t_moteur *moteur) {
    const int TAILLE_BLOCK_RENDU = moteur->window_height / TAILLE_CAMERA_HAUTEUR;
    // SDL_Log("TAILLE BLOCK RENDU : %i", TAILLE_BLOCK_RENDU);

    SDL_Rect rendu;

    rendu.h = TAILLE_BLOCK_RENDU;
    rendu.w = TAILLE_BLOCK_RENDU;


    for (int x = moteur->camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR; x <= moteur->camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR; x++) {
        for (int y = moteur->camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR; y <= moteur->camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR; y++) {
            // SDL_Log("CAMERA BLOCK RENDU : %i:%i", x, y);
            t_block *block = getBlockDansMap(x, y, COUCHE_SOL, moteur->monde->map);
            if (block == NULL) continue;

            SDL_Texture *texture = getTexture(block->tag, moteur->textures);
            if (texture == NULL) continue;

            // rendu; // = { block->position.x, block->position.y, TAILLE_BLOCK_RENDU, TAILLE_BLOCK_RENDU };
            // rendu.x = block->position.x * TAILLE_BLOCK_RENDU;
            rendu.x = (x % ((int)moteur->camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR)) * TAILLE_BLOCK_RENDU;
            rendu.y = (y % ((int)moteur->camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR)) * TAILLE_BLOCK_RENDU;
            SDL_Log("BLOCK POSITION : %i:%i", x % (int)moteur->camera->position.x, y % (int)moteur->camera->position.y);

            // printf("BLOCK => %i\n", block->tag);
            SDL_RenderCopy(moteur->renderer, texture, NULL, &rendu);

        }
    }


    rendu.x = moteur->monde->joueur->position.x * TAILLE_BLOCK_RENDU;
    rendu.y = moteur->monde->joueur->position.y * TAILLE_BLOCK_RENDU;
    SDL_RenderCopy(moteur->renderer, moteur->textures->joueur, NULL, &rendu);

    SDL_Log("JOUEUR : %1.0f:%1.0f", moteur->monde->joueur->position.x, moteur->monde->joueur->position.y);
}



void updateCamera(t_moteur *moteur, const t_vecteur2 position) {
    moteur->camera->position = position;
    afficherCamera(moteur);
}





t_camera* creerCamera(t_vecteur2 position) {
    t_camera *camera = malloc(sizeof(t_camera));

    if (camera == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour la caméra");
        free(camera);
        return NULL;
    }


    camera->position = position;

    t_vecteur2 futurePosition = { 0, 0 };
    camera->futurePosition = futurePosition;


    return camera;
}





void detruireCamera(t_camera **camera) {
    if (camera != NULL && *camera != NULL) {
        free(*camera);
        *camera = NULL;
    }
}