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





#define TAILLE_CAMERA_LARGEUR 13
#define TAILLE_CAMERA_HAUTEUR 7





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










#endif