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




/**
 * @brief 
 * 
 * @param coordonnee 
 * @param offset 
 * @param origine 
 * @param tailleRendu 
 * @return int 
 */
int positionRelativeEnPositionSurEcran(const float coordonnee, const float offset, const float origine, const float tailleRendu) {
    return (((coordonnee * tailleRendu) - (origine * tailleRendu)) - (offset * tailleRendu));
}



/**
 * @brief 
 * 
 * @param moteur 
 */
void afficherCamera(t_moteur *moteur) {
    const float TAILLE_BLOCK_RENDU_H = moteur->window_height / TAILLE_CAMERA_HAUTEUR;
    const float TAILLE_BLOCK_RENDU_L = moteur->window_width / TAILLE_CAMERA_LARGEUR;
    // SDL_Log("TAILLE BLOCK RENDU : %i", TAILLE_BLOCK_RENDU);
    const float origineX = (moteur->camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR);
    const float origineY = (moteur->camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR);


    t_vecteur2 positionnementEnPixel;
    t_vecteur2 offset;
    offset.x = (moteur->camera->position.x - (int)moteur->camera->position.x); // * TAILLE_BLOCK_RENDU_H;
    offset.y = (moteur->camera->position.y - (int)moteur->camera->position.y); // * TAILLE_BLOCK_RENDU_L;


    SDL_Rect rendu;
    rendu.h = TAILLE_BLOCK_RENDU_H;
    rendu.w = TAILLE_BLOCK_RENDU_L;


    // printf("AFFICHAGE => Offset : %1.2f:%1.2f\n", offset.x, offset.y);



    for (float x = origineX - 1; x <= moteur->camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 1; x++) {
        for (float y = origineY - 1; y <= moteur->camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 1; y++) {
            // positionnementEnPixel.x = positionRelativeEnPositionSurEcran(x, origineX, TAILLE_BLOCK_RENDU_L); // (x * TAILLE_BLOCK_RENDU_L) - (origineX * TAILLE_BLOCK_RENDU_L);
            // positionnementEnPixel.y = positionRelativeEnPositionSurEcran(y, origineY, TAILLE_BLOCK_RENDU_H); // (y * TAILLE_BLOCK_RENDU_H) - (origineY * TAILLE_BLOCK_RENDU_H);

            rendu.x = positionRelativeEnPositionSurEcran(x, offset.x, origineX, TAILLE_BLOCK_RENDU_L) + TAILLE_BLOCK_RENDU_L; // positionnementEnPixel.x - offset.x;
            rendu.y = positionRelativeEnPositionSurEcran(y, offset.y, origineY, TAILLE_BLOCK_RENDU_H) + TAILLE_BLOCK_RENDU_H; // positionnementEnPixel.y - offset.y;


            // SDL_Log("CAMERA BLOCK RENDU : %i:%i", x, y);
            t_block *block = getBlockDansMap(x, y, COUCHE_SOL, moteur->monde->map);
            if (block == NULL) {
                SDL_RenderCopy(moteur->renderer, moteur->textures->sol_profondeur, NULL, &rendu);
                continue;
            }

            SDL_Texture *texture = getTexture(block->tag, moteur->textures);
            if (texture == NULL) continue;

            // rendu; // = { block->position.x, block->position.y, TAILLE_BLOCK_RENDU, TAILLE_BLOCK_RENDU };
            // rendu.x = block->position.x * TAILLE_BLOCK_RENDU;
            // SDL_Log("BLOCK POSITION : %i:%i", x % (int)moteur->camera->position.x, y % (int)moteur->camera->position.y);

            // printf("BLOCK => %i\n", block->tag);
            SDL_RenderCopy(moteur->renderer, texture, NULL, &rendu);

        }
    }



    // positionnementEnPixel.x = positionRelativeEnPositionSurEcran(moteur->monde->joueur->position.x, origineX, TAILLE_BLOCK_RENDU_L); // (moteur->monde->joueur->position.x * TAILLE_BLOCK_RENDU_L) - (origineX * TAILLE_BLOCK_RENDU_L);
    // positionnementEnPixel.y = positionRelativeEnPositionSurEcran(moteur->monde->joueur->position.y, origineY, TAILLE_BLOCK_RENDU_H); // (moteur->monde->joueur->position.y * TAILLE_BLOCK_RENDU_H) - (origineY * TAILLE_BLOCK_RENDU_H);
    // SDL_Log("Position Joueur (Pixel) : %1.2f:%1.2f", positionnementEnPixel.x, positionnementEnPixel.y);
    
    rendu.x = positionRelativeEnPositionSurEcran(moteur->monde->joueur->position.x, 0.0, origineX, TAILLE_BLOCK_RENDU_L); // positionnementEnPixel.x - offset.x;
    rendu.y = positionRelativeEnPositionSurEcran(moteur->monde->joueur->position.y, 0.0, origineY, TAILLE_BLOCK_RENDU_H); // positionnementEnPixel.y - offset.y;
    // rendu.x = moteur->window_width / 2;
    // rendu.y = moteur->window_height / 2;
    SDL_RenderCopy(moteur->renderer, moteur->textures->joueur, NULL, &rendu);


    // SDL_Log("JOUEUR : %1.0f:%1.0f", moteur->monde->joueur->position.x, moteur->monde->joueur->position.y);
}



/**
 * @brief 
 * 
 * @param moteur 
 * @param position 
 */
void updateCamera(t_moteur *moteur, const t_vecteur2 position) {
    printf("Update Camera => ");
    t_camera *camera = moteur->camera;
    camera->position = position;
    printf("%1.2f:%1.2f => ", position.x, position.y);
    printf("Fin Update Camera\n");
}





/**
 * @brief 
 * 
 * @param position 
 * @return t_camera* 
 */
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





/**
 * @brief 
 * 
 * @param camera 
 */
void detruireCamera(t_camera **camera) {
    if (camera != NULL && *camera != NULL) {
        free(*camera);
        *camera = NULL;
    }
}