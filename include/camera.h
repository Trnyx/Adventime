/**
 * @file camera.h
 *
 * @brief Module de manipulation de la caméra
 *
 * @author Clément Hibon
 * @date 5 février
 * @version 1.1
 */




#ifndef _JEU_CAMERA_
#define _JEU_CAMERA_





#include "utilitaire.h"
#include "textures.h"
#include "map.h"
#include "temps.h"





#define TAILLE_CAMERA_LARGEUR 31
#define TAILLE_CAMERA_HAUTEUR 17

// #define TAILLE_CAMERA_LARGEUR 64
// #define TAILLE_CAMERA_HAUTEUR 32

// #define TAILLE_CAMERA_LARGEUR (TAILLE_MAP * TAILLE_CHUNK)
// #define TAILLE_CAMERA_HAUTEUR (TAILLE_MAP * TAILLE_CHUNK)

#define TAILLE_CAMERA_DEMI_LARGEUR TAILLE_CAMERA_LARGEUR / 2
#define TAILLE_CAMERA_DEMI_HAUTEUR TAILLE_CAMERA_HAUTEUR / 2





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


// Nous avons besoin de définir cette structure "temporaire"
// afin que le compilateur connaisse son existence
// typedef struct s_moteur t_moteur;


/**
 * @struct t_camera
 * @brief Structure modélisant une caméra
 * 
 */
typedef struct s_camera {
    t_vecteur2 position;            /**< La position actuelle de la caméra */
    t_vecteur2 futurePosition;      /**< La future position de la caméra */

    t_vecteur2 origine;             /**< Les coordonnées de l'origine de l'écran */
    t_vecteur2 offset;              /**< Les coordonnées de décalage de bloc */

    t_vecteur2 tailleRendu;         /**< Les dimensions (en pixel) de la taille des rendus */
} t_camera;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_camera* creerCamera(const t_vecteur2 position);
void detruireCamera(t_camera **camera);

void updateCamera(const t_vecteur2 position);
void afficherCamera(t_map *map);

void dessinerCalqueAmbiance(t_temps *temps);

int positionRelativeEnPositionSurEcran(const float coordonnee, const float offset, const float origine, const float tailleRendu);










#endif