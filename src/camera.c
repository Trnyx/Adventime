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

#include "../include/camera.h"





t_camera* creerCamera(t_vecteur2 position) {
    t_camera *camera = malloc(sizeof(t_camera));


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