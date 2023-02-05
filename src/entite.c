/**
 * @file entite.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */




#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/entite.h"
#include "../include/utilitaire.h"





/**
 * @brief 
 * 
 * @param position 
 * @return t_entite* 
 */
t_entite* creerEntite(const t_vecteur2 position) {
    t_entite *entite = malloc(sizeof(t_entite));


    entite->position = position;
    entite->orientation.x = 1;
    entite->orientation.y = 0;
    entite->vitesse = 0;

    // entite->type = ENTITE_RIEN;

    entite->hitbox.x = 0;
    entite->hitbox.y = 0;
    entite->hitbox.h = 0;
    entite->hitbox.w = 0;
    

    return entite;
}





int peutDeplacerEntite() {

}



/**
 * @brief 
 * 
 * @param entite 
 * @return int 
 */
int deplacerEntite(t_entite *entite) {

}





void detruireEntite(t_entite **entite) {
    if (entite != NULL && *entite != NULL) {

        free(*entite);
        *entite = NULL;

    }
}