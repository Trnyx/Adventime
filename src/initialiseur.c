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
void initAll(t_moteur **moteur) {
    // Moteur
    *moteur = initMoteur();
    t_vecteur2 positionCamera = { 0, 0 };
    (*moteur)->camera = creerCamera(positionCamera);
    (*moteur)->textures = initTextures((*moteur)->renderer);


    // Audio
    
    
    // SDL Image
    

    // SDL TTF
}
