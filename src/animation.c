/**
 * @file animation.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 10 mars
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>
#include "../include/animation.h"





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param animation 
 * @param timestamp 
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


void detruireAnimation(t_animation **animation) {
    if (animation != NULL && *animation != NULL) {
        free(*animation);
        *animation = NULL;
    }
}





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


t_animation* creerAnimation(const unsigned int vitesse, const unsigned int nombreFrame) {
    t_animation *animation = malloc(sizeof(t_animation));

    if (animation == NULL) {
        printf("Erreur mémoire : \n");
        return NULL;
    }


    animation->vitesse = vitesse;
    animation->nombreFrame = nombreFrame;

    animation->frameCourante = 0;
    animation->timestampUpdate = 0;


    return animation;
}