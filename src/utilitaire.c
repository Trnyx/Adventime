/**
 * @file utilitaire.c
 *
 * @brief Module regroupant les fonctions dites utiles
 *
 * @author Clément Hibon
 * @date 21 janvier
 * @version 1.3
 */





#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/NanoId/nanoid.h"

#include "../include/utilitaire.h"





/**
 * @brief Génère un ID
 * 
 * @return Un pointeur sur l'ID
 */
char* genererId() {
    // return generate(LONGUEUR_ID);
    return custom("0123456789ABCDEF", LONGUEUR_ID);
}





/**
 * @brief Génère un nombre aléatoire entre un minimum et un maximum
 * 
 * @param min Le nombre minimum
 * @param max Le nombre maximum
 * 
 * @return Le nombre généré
 */
int getNombreAleatoire(const int min, const int max) {
    return min + rand() % ((max + 1) - min);
}



int getNombreAvecProbabilite() {
    return 0;
}





/**
 * @brief Rapporte les angles > 360° et < 0° à un angle dans l'interval [0; 360[
 * 
 * @param angle L'angle que l'on vérifie
 * 
 * @return Le nouvel angle
 */
float revolution(const float angle) {
    return angle - floor(angle / 360.0) * 360.0;
}





/**
 * @brief Calcul la distance entre deux points
 * 
 * @param source La position source
 * @param cible La position cible
 * 
 * @return La distance entre les deux points
 */
float calculDistanceEntrePoints(const t_vecteur2 source, const t_vecteur2 cible) {
    return sqrt( pow(cible.x - source.x, 2) + pow(cible.y - source.y, 2) );
}





/**
 * @brief Calcul l'angle entre deux points
 * 
 * @param source La position source
 * @param cible La position cible
 * 
 * @return L'angle entre les deux points
 */
float calculAngleEntrePoints(const t_vecteur2 source, const t_vecteur2 cible) {
    float angle = atan2(source.y - cible.y, source.x - cible.x) * (180 / M_PI);

    if (angle < 0) 
        angle = revolution(angle);

    return angle;
}





/**
 * @brief Génère un point aléatoirement dans le rayon donné
 * 
 * @param rayon Le rayon dans lequel le point sera généré
 * 
 * @return Le point généré
 */
t_vecteur2 choisirPointDansRayon(const int rayon) {
    t_vecteur2 point = {
        getNombreAleatoire(-rayon, rayon),
        getNombreAleatoire(-rayon, rayon),
    };

    return point;
}