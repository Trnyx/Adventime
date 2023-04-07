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
#include "../include/physique.h"




#define TAILLE_TEXTURE 16





/**
 * @brief Convertie la position relative en position pixel par rapport à l'écran
 * 
 * @param coordonnee La cooronnée originale en jeu
 * @param offset Le décalage de bloc [0; 1[ 
 * @param origine L'origine à laquelle sera rapporté les coordonnée relative en jeu
 * @param tailleRendu La taille (en pixel) du rendu
 * 
 * @return La position relative en jeu converti en pixel sur écran
 */
int positionRelativeEnPositionSurEcran(const float coordonnee, const float offset, const float origine, const float tailleRendu) {
    return (((coordonnee * tailleRendu) - (origine * tailleRendu)) - (offset * tailleRendu));
}





/* -------------------------------------------------------------------------- */
/*                                   Dessin                                   */
/* -------------------------------------------------------------------------- */





// int dessinerEntite(SDL_Texture *texture, t_entite *entite, const t_vecteur2 origine, const t_vecteur2 offset, SDL_Rect *rendu) {
//     rendu.x = positionRelativeEnPositionSurEcran(entite->position.x, offset.x, origine.x, rendu->w); // positionnementEnPixel.x - offset.x;
//     rendu.y = positionRelativeEnPositionSurEcran(entite->position.y, offset.y, origine.y, rendu->h); // positionnementEnPixel.y - offset.y;

//     SDL_RenderCopy(moteur->renderer, texture, &source, rendu);
// }




/**
 * @brief Dessine le calque dit ambiance
 * 
 * Le calque d'ambiance permet d'indiquer au joueur la période de la journée dans laquelle il se trouve
 * 
 * @param temps Un pointeur sur le temps en jeu
 */
void dessinerCalqueAmbiance(t_temps *temps) {
    SDL_Rect calque;
    calque.x = calque.y = 0;
    calque.h = moteur->window_height;
    calque.w = moteur->window_width;
    

    Uint8 r, g, b;
    unsigned int a;


    if (temps->heures >= HEURE_JEU_LEVE_SOLEIL && temps->heures < HEURE_JEU_MATIN) {
        r = 0xff; g = 0xa7; b = 0x00; a = 30;
    }
    else if (temps->heures >= HEURE_JEU_MATIN && temps->heures < HEURE_JEU_APRES_MIDI) {
        r = 0x00; g = 0x00; b = 0x00; a = 0;
    }
    else if (temps->heures >= HEURE_JEU_APRES_MIDI && temps->heures < HEURE_JEU_COUCHE_SOLEIL) {
        r = 0x00; g = 0x00; b = 0x00; a = 0;
    }
    else if (temps->heures >= HEURE_JEU_COUCHE_SOLEIL && temps->heures < HEURE_JEU_NUIT) {
        r = 0xfb; g = 0x90; b = 0x62; a = 40;
    }
    else {
        r = 0x19; g = 0x19; b = 0x70; a = 34;
    }
    


    SDL_SetRenderDrawColor(moteur->renderer, r, g, b, a);
    SDL_RenderFillRect(moteur->renderer, &calque);
}


/* -------------------------------------------------------------------------- */
/*                                    Rendu                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param map 
 */
void afficherCamera(t_map *map) {
    // t_camera *camera = moteur->camera;
    // camera->tailleRendu.x = moteur->window_width / TAILLE_CAMERA_LARGEUR;
    // camera->tailleRendu.y = moteur->window_height / TAILLE_CAMERA_HAUTEUR;

    // const float origineX = (camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR);
    // const float origineY = (camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR);
    // camera->origine.x = (camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR);
    // camera->origine.y = (camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR);
    // camera->offset.x = (camera->position.x - (int)camera->position.x);
    // camera->offset.y = (camera->position.y - (int)camera->position.y);


    // SDL_Rect rendu;
    // rendu.w = camera->tailleRendu.x;
    // rendu.h = camera->tailleRendu.y;


    /* ----------------------------------- Map ---------------------------------- */

    // for (float x = origineX - 1; x <= camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 1; x++) {
    //     for (float y = origineY - 1; y <= camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 1; y++) {

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
    // dessinerSol(moteur, map, &rendu);

    // SDL_Log("JOUEUR : %1.0f:%1.0f", moteur->monde->joueur->position.x, moteur->monde->joueur->position.y);


    /* --------------------------------- Entites -------------------------------- */
    // SDL_Rect sprite;
    // sprite.x = 0;
    // sprite.y = 0;
    // sprite.w = TAILLE_TILE;
    // sprite.h = TAILLE_TILE;
    // Animaux
    // Monstres


    // if (!liste_vide(map->entites)) {
    //     t_monstre *monstre;
    //     en_tete(map->entites);

    //     while (!hors_liste(map->entites)) {
    //         valeur_elt(map->entites, (t_entite**)&monstre);

    //         rendu.x = positionRelativeEnPositionSurEcran(monstre->position.x, 0.0, camera->origine.x, rendu.w); // positionnementEnPixel.x - offset.x;
    //         rendu.y = positionRelativeEnPositionSurEcran(monstre->position.y, 0.0, camera->origine.y, rendu.h); // positionnementEnPixel.y - offset.y;
    //         SDL_RenderCopy(moteur->renderer, moteur->textures->monstres, &sprite, &rendu);

    //         suivant(map->entites);
    //     }
        
    // }


    /* --------------------------------- Joueur --------------------------------- */

    // dessinerEntite(moteur, (t_entite*) joueur);


    /* -------------------------------- Vegetaux -------------------------------- */

    // if (map->type == MAP_OVERWORLD) {
    //     dessinerVegetation(moteur, map, &rendu);
    // }

}



/**
 * @brief Actualise toutes les informations de la caméra
 * 
 * @param position La position à laquelle la caméra doit être placé
 */
void updateCamera(const t_vecteur2 position) {
    // printf("Update Camera => ");
    t_camera *camera = moteur->camera;
    
    camera->position = position;
    camera->origine.x = (camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR);
    camera->origine.y = (camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR);
    camera->offset.x = (camera->position.x - (int)camera->position.x);
    camera->offset.y = (camera->position.y - (int)camera->position.y);

    // printf("%1.2f:%1.2f => ", position.x, position.y);
    // printf("Fin Update Camera\n");
}





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour une caméra et la créer
 * 
 * @param position La position à laquelle la caméra doit être créée
 * 
 * @return Un pointeur sur la caméra créée, NULL si echec
 */
t_camera* creerCamera(const t_vecteur2 position) {
    printf("Creation camera => ");
    t_camera *camera = malloc(sizeof(t_camera));

    if (camera == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour la caméra\n");
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
 * @brief Detruit une camera est libère la mémoire allouée pour cette dernière
 * 
 * @param camera L'adresse du pointeur de la camera à détruire
 */
void detruireCamera(t_camera **camera) {
    printf("Destruction Camera => ");
    if (camera != NULL && *camera != NULL) {
        free(*camera);
        *camera = NULL;
    }
    printf("Succes\n");
}
