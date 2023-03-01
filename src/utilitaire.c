/**
 * @file utilitaire.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 21 janvier
 * @version 1.3
 */




#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/utilitaire.h"





/**
 * @brief Get the Nombre Aleatoire object
 * 
 * @param min 
 * @param max 
 * @return int 
 */
int getNombreAleatoire(const int min, const int max) {
    return min + rand() % ((max + 1) - min);
}



int getNombreAvecProbabilite() {
    return 0;
}





/**
 * @brief 
 * 
 * @param source 
 * @param cible 
 * @return float 
 */
float calculDistanceEntrePoints(const t_vecteur2 source, const t_vecteur2 cible) {
    return sqrt( pow(cible.x - source.x, 2) + pow(cible.y - source.y, 2) );
}





/**
 * @brief 
 * 
 * @param source 
 * @param cible 
 * @return float 
 */
float calculAngleEntrePoints(const t_vecteur2 source, const t_vecteur2 cible) {
    float angle = atan2(source.y / 2 - cible.y, source.x / 2 - cible.x) * (180 / M_PI);

    if (angle < 0) 
        angle = 360 - (-angle);

    return angle;
}





/**
 * @brief 
 * 
 * @param rayon 
 * @return t_vecteur2 
 */
t_vecteur2 choisirPointDansRayon(const int rayon) {
    t_vecteur2 point = {
        getNombreAleatoire(-rayon, rayon),
        getNombreAleatoire(-rayon, rayon),
    };

    return point;
}