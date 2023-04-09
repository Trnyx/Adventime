/**
 * @file animation.c
 * 
 * @brief Module de manipulation des animations
 * 
 * @author Clément Hibon
 * @date 10 mars
 */





#include <stdlib.h>
#include <stdio.h>
#include "../include/animation.h"





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Actualise l'animation
 * 
 * @param animation Pointeur sur l'animation à actualiser
 * @param timestamp Le temps actuel du jeu
 */
void updateAnimation(t_animation *animation, const unsigned int timestamp) {
    if (animation != NULL) {
        if (animation->timestampUpdate + animation->vitesse <= timestamp) {
            animation->timestampUpdate = timestamp;
            (animation->frameCourante)++;

            if (animation->frameCourante >= animation->nombreFrame)
                animation->frameCourante = 0;
        }
    }
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit une animation est libère la mémoire allouée pour cette dernière
 * 
 * @param animation L'adresse du pointeur de l'animation à détruire
 */
void detruireAnimation(t_animation **animation) {
    if (animation != NULL && *animation != NULL) {
        free(*animation);
        *animation = NULL;
    }
}





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour une animation et la créer
 * 
 * @param vitesse La vitesse de défilement soit le temps (en milisecondes) entre chaque changement d'image
 * @param nombreFrame Le nombre d'image constituant l'animation
 * 
 * @return Un pointeur sur l'animation créée, NULL si echec
 */
t_animation* creerAnimation(const unsigned int vitesse, const unsigned int nombreFrame) {
    t_animation *animation = malloc(sizeof(t_animation));

    if (animation == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la mémoire nécessaire pour une animation\n");
        return NULL;
    }


    animation->vitesse = vitesse;
    animation->nombreFrame = nombreFrame;

    animation->frameCourante = 0;
    animation->timestampUpdate = 0;


    return animation;
}