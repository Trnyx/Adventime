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
    const int TAILLE_BLOCK_RENDU_H = moteur->window_height / TAILLE_CAMERA_HAUTEUR;
    const int TAILLE_BLOCK_RENDU_L = moteur->window_width / TAILLE_CAMERA_LARGEUR;
    // SDL_Log("TAILLE BLOCK RENDU : %i", TAILLE_BLOCK_RENDU);

    SDL_Rect rendu;

    rendu.h = TAILLE_BLOCK_RENDU_H;
    rendu.w = TAILLE_BLOCK_RENDU_L;

    const int centrageLargeur = ((int)moteur->camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR);
    const int centrageHauteur = ((int)moteur->camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR);

    for (int x = moteur->camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR; x <= moteur->camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR; x++) {
        for (int y = moteur->camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR; y <= moteur->camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR; y++) {
            // SDL_Log("CAMERA BLOCK RENDU : %i:%i", x, y);
            t_block *block = getBlockDansMap(x, y, COUCHE_SOL, moteur->monde->map);
            if (block == NULL) continue;

            SDL_Texture *texture = getTexture(block->tag, moteur->textures);
            if (texture == NULL) continue;

            // rendu; // = { block->position.x, block->position.y, TAILLE_BLOCK_RENDU, TAILLE_BLOCK_RENDU };
            // rendu.x = block->position.x * TAILLE_BLOCK_RENDU;
            rendu.x = (x % centrageLargeur) * TAILLE_BLOCK_RENDU_L;
            rendu.y = (y % centrageHauteur) * TAILLE_BLOCK_RENDU_H;
            // SDL_Log("BLOCK POSITION : %i:%i", x % (int)moteur->camera->position.x, y % (int)moteur->camera->position.y);

            // printf("BLOCK => %i\n", block->tag);
            SDL_RenderCopy(moteur->renderer, texture, NULL, &rendu);

        }
    }


    rendu.x = ((int)moteur->monde->joueur->position.x % centrageLargeur) * TAILLE_BLOCK_RENDU_L;
    rendu.y = ((int)moteur->monde->joueur->position.y % centrageHauteur) * TAILLE_BLOCK_RENDU_H;
    SDL_RenderCopy(moteur->renderer, moteur->textures->joueur, NULL, &rendu);

    // SDL_Log("JOUEUR : %1.0f:%1.0f", moteur->monde->joueur->position.x, moteur->monde->joueur->position.y);
}



void updateCamera(t_moteur *moteur, const t_vecteur2 position) {
    moteur->camera->position = position;
}





t_camera* creerCamera(t_vecteur2 position) {
    printf("Creation camera => ");
    t_camera *camera = malloc(sizeof(t_camera));

    if (camera == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour la caméra");
        free(camera);
        return NULL;
    }


    camera->position = position;

    t_vecteur2 futurePosition = { 0, 0 };
    camera->futurePosition = futurePosition;


    printf("Succes\n");
    return camera;
}





void detruireCamera(t_camera **camera) {
    if (camera != NULL && *camera != NULL) {
        free(*camera);
        *camera = NULL;
    }
}