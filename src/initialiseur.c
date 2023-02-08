/**
 * @file initialiseur.c
 * 
 * @brief 
 * 
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>

#include "../include/initialiseur.h"
// #include image.h
// #include ttf.h





/**
 * @brief 
 */
void initAll(t_moteur **moteur, t_textures **textures) {
    // Moteur
    *moteur = initMoteur();

    // Audio
    
    // SDL Image
    *textures = initTextures((*moteur)->renderer);
    

    // SDL TTF
}
