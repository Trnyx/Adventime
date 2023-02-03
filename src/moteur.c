/**
 * @file moteur.c
 *
 * @brief
 *
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>
#include "../include/moteur.h"
#include "../include/window.h"





void regulerFPS(t_moteur *moteur) {

}





t_moteur* initMoteur() {
    t_moteur *moteur = malloc(sizeof(t_moteur));


    initSDL(moteur);


    return moteur;
}





void detruireMoteur(t_moteur **moteur) {
    if (moteur != NULL && *moteur != NULL) {

        free((*moteur));
        *moteur = NULL;
        
    }
}





void updateEchelle(t_moteur *moteur) {}





