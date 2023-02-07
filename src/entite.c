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

#include "../include/moteur.h"
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

    entite->entiteType = ENTITE_RIEN;

    entite->hitbox.x = 0;
    entite->hitbox.y = 0;
    entite->hitbox.h = 0;
    entite->hitbox.w = 0;
    

    return entite;
}





boolean peutDeplacerEntite() {
    int collision = FAUX;


    return collision;
}



/**
 * @brief 
 * 
 * @param entite 
 * @return int 
 */
boolean deplacerEntite(t_entite *entite, const float vitesse) {
    const float distance = vitesse * TPS;

    // const float normale = sqrt(pow( , 2) + pow( , 2));
    t_vecteur2 positionSuivante = { entite->position.x, entite->position.y };

    boolean peutSeDeplacer = peutDeplacerEntite();

    if (peutSeDeplacer == VRAI) {

    }
    else {

    }


    return peutSeDeplacer;
}





void detruireEntite(t_entite **entite) {
    if (entite != NULL && *entite != NULL) {

        free(*entite);
        *entite = NULL;

    }
}