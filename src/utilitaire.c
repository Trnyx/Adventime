/**
 * @file 
 *
 * @brief
 *
 * @author
 */




#include "stdio.h"
#include "stdlib.h"
#include "../include/utilitaire.h"




int getNombreAleatoire(const int min, const int max) {
    return min + rand() % ((max + 1) - min);
}



int getNombreAvecProbabilite() {
    return 0;
}
