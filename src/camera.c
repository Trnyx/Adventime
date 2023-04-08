/**
 * @file camera.c
 *
 * @brief Module de gestion de la caméra
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
 * @brief Actualise toutes les informations de la caméra
 * 
 * @param position La position à laquelle la caméra doit être placé
 */
void updateCamera(const t_vecteur2 position) {
    t_camera *camera = moteur->camera;
    
    camera->position = position;
    camera->origine.x = (camera->position.x - TAILLE_CAMERA_DEMI_LARGEUR);
    camera->origine.y = (camera->position.y - TAILLE_CAMERA_DEMI_HAUTEUR);
    camera->offset.x = (camera->position.x - (int)camera->position.x);
    camera->offset.y = (camera->position.y - (int)camera->position.y);
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
    t_camera *camera = malloc(sizeof(t_camera));

    if (camera == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour la caméra\n");
        return NULL;
    }


    camera->position = position;

    t_vecteur2 futurePosition = { 0, 0 };
    camera->futurePosition = futurePosition;


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
    if (camera != NULL && *camera != NULL) {
        free(*camera);
        *camera = NULL;
    }
}
