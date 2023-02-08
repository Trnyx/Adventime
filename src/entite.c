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





/**
 * @brief 
 * 
 * @param map 
 * @param entite 
 * @param positionSuivante 
 * @return boolean 
 */
boolean peutDeplacerEntite(const t_map *map, const t_entite *entite, const t_vecteur2 positionSuivante) {
    t_block *block = getBlockDansMap(positionSuivante.x, positionSuivante.y, map);
    if (block == NULL) return FAUX;

    if (block->tag == VIDE) return VRAI;

    return VRAI;
}



/**
 * @brief 
 * 
 * @param moteur 
 * @param entite 
 * @param vitesse 
 * @return boolean 
 */
boolean deplacerEntite(const t_moteur *moteur, t_entite *entite, const float vitesse) {
    const float distance = vitesse * TPS;

    // Justification calcul normale
    const float normale = sqrt(pow(entite->orientation.x, 2) + pow(entite->orientation.y, 2));

    // Justification calcul
    t_vecteur2 positionSuivante;
    positionSuivante.x = entite->position.x + (distance * (entite->orientation.x / normale));
    positionSuivante.y = entite->position.y + (distance * (entite->orientation.y / normale));
    
    boolean peutSeDeplacer = peutDeplacerEntite(moteur->monde->map, entite, positionSuivante);


    if (peutSeDeplacer == VRAI) {
        entite->position = positionSuivante;
    }


    return peutSeDeplacer;
}





void detruireEntite(t_entite **entite) {
    if (entite != NULL && *entite != NULL) {

        free(*entite);
        *entite = NULL;

    }
}