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





/* -------------------------------------------------------------------------- */
/*                                    Rendu                                   */
/* -------------------------------------------------------------------------- */





int dessinerBlock(t_moteur *moteur, const int tag, SDL_Rect *rendu) {
    SDL_Rect source;


    switch (tag) {
        /* ----------------------------------- Sol ---------------------------------- */

        case SOL_EAU_PROFONDE:
        case SOL_EAU:
        case SOL_SABLE:
        case SOL_HERBE_1:
        case SOL_HERBE_2:
        case SOL_HERBE_3:
        case SOL_MONTAGNE_1:
        case SOL_MONTAGNE_2:
            splitTexture(&source, tag,0, TAILLE_TEXTURE,TAILLE_TEXTURE, TAILLE_TEXTURE,TAILLE_TEXTURE);
            break;


        /* -------------------------------- Vegetaion ------------------------------- */

        case CHAINE:
            splitTexture(&source);
            break;


        default:
            break;
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
void dessinerMap(t_moteur *moteur, const t_vecteur2 origine, const t_vecteur2 offset, SDL_Rect *rendu) {
    for (float x = origine.x - 1; x <= moteur->camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 1; x++) {
        for (float y = origine.y - 1; y <= moteur->camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 1; y++) {

            rendu->x = positionRelativeEnPositionSurEcran(x, offset.x, origine.x, rendu->w) + rendu->w;
            rendu->y = positionRelativeEnPositionSurEcran(y, offset.y, origine.y, rendu->h) + rendu->h;


            t_block *block = getBlockDansMap(x, y, COUCHE_SOL, moteur->monde->map);
            if (block == NULL) {
                SDL_RenderCopy(moteur->renderer, moteur->textures->sol_profondeur, NULL, &rendu);
                continue;
            }


            // SDL_Texture *texture = getTexture(block->tag, moteur->textures);
            // if (texture == NULL) continue;

            // SDL_Rect source = dessinerBlock(moteur, block->tag, rendu);
            dessinerBlock(moteur, block->tag, rendu);


            // SDL_RenderCopy(moteur->renderer, moteur->textures->sol, &source, &rendu);

        }
    }
}





/**
 * @brief 
 * 
 * @param moteur 
 */
void afficherCamera(t_moteur *moteur) {
    const float TAILLE_BLOCK_RENDU_H = moteur->window_height / TAILLE_CAMERA_HAUTEUR;
    const float TAILLE_BLOCK_RENDU_L = moteur->window_width / TAILLE_CAMERA_LARGEUR;

    // const float origineX = (moteur->camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR);
    // const float origineY = (moteur->camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR);
    const t_vecteur2 origine = {
        (moteur->camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR),
        (moteur->camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR)
    };

    const t_vecteur2 offset = {
        (moteur->camera->position.x - (int)moteur->camera->position.x), // * TAILLE_BLOCK_RENDU_H;
        (moteur->camera->position.y - (int)moteur->camera->position.y), // * TAILLE_BLOCK_RENDU_L;
    };


    SDL_Rect rendu;
    rendu.h = TAILLE_BLOCK_RENDU_H;
    rendu.w = TAILLE_BLOCK_RENDU_L;



    // for (float x = origineX - 1; x <= moteur->camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 1; x++) {
    //     for (float y = origineY - 1; y <= moteur->camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 1; y++) {

    //         rendu.x = positionRelativeEnPositionSurEcran(x, offset.x, origineX, TAILLE_BLOCK_RENDU_L) + TAILLE_BLOCK_RENDU_L; // positionnementEnPixel.x - offset.x;
    //         rendu.y = positionRelativeEnPositionSurEcran(y, offset.y, origineY, TAILLE_BLOCK_RENDU_H) + TAILLE_BLOCK_RENDU_H; // positionnementEnPixel.y - offset.y;


    //         t_block *block = getBlockDansMap(x, y, COUCHE_SOL, moteur->monde->map);
    //         if (block == NULL) {
    //             SDL_RenderCopy(moteur->renderer, moteur->textures->sol_profondeur, NULL, &rendu);
    //             continue;
    //         }


    //         // SDL_Texture *texture = getTexture(block->tag, moteur->textures);
    //         // if (texture == NULL) continue;

    //         // SDL_Rect source = dessinerBlock(moteur, block->tag, rendu);
    //         dessinerBlock(moteur, block->tag, rendu);


    //         // SDL_RenderCopy(moteur->renderer, moteur->textures->sol, &source, &rendu);

    //     }
    // }
    dessinerMap(moteur, origine, offset, &rendu);



    
    // rendu.x = positionRelativeEnPositionSurEcran(moteur->monde->joueur->position.x, 0.0, origineX, TAILLE_BLOCK_RENDU_L); // positionnementEnPixel.x - offset.x;
    // rendu.y = positionRelativeEnPositionSurEcran(moteur->monde->joueur->position.y, 0.0, origineY, TAILLE_BLOCK_RENDU_H); // positionnementEnPixel.y - offset.y;
    rendu.x = positionRelativeEnPositionSurEcran(moteur->monde->joueur->position.x, 0.0, origine.x, TAILLE_BLOCK_RENDU_L); // positionnementEnPixel.x - offset.x;
    rendu.y = positionRelativeEnPositionSurEcran(moteur->monde->joueur->position.y, 0.0, origine.y, TAILLE_BLOCK_RENDU_H); // positionnementEnPixel.y - offset.y;
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





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


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





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


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