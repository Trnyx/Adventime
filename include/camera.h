/**
 * @file camera.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 5 février
 * @version 1.1
 */




#ifndef _JEU_CAMERA_
#define _JEU_CAMERA_





#include "utilitaire.h"





#define TAILLE_CAMERA_LARGEUR 24
#define TAILLE_CAMERA_HAUTEUR 12

#define TAILLE_CAMERA_DEMI_LARGEUR TAILLE_CAMERA_LARGEUR / 2
#define TAILLE_CAMERA_DEMI_HAUTEUR TAILLE_CAMERA_HAUTEUR / 2





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


// Nous avons besoin de définir cette structure "temporaire"
// afin que le compilateur connaisse son existence
typedef struct s_moteur t_moteur;


/**
 * @brief 
 * 
 */
typedef struct s_camera {
    t_vecteur2 position;
    t_vecteur2 futurePosition;
} t_camera;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_camera* creerCamera(t_vecteur2 position);
void detruireCamera(t_camera **camera);

void updateCamera(t_moteur *moteur, const t_vecteur2 position);
void afficherCamera(t_moteur *moteur);










#endif