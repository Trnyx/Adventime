/**
 * @file logique_deplacements.c
 * 
 * @brief Gestion des déplacement du jeu
 * 
 * @author Clément Hibon
 * @date 10 février
 */





#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../include/utilitaire.h"
#include "../include/physique.h"
#include "../include/moteur.h"
#include "../include/mob.h"
#include "../include/deplacement.h"





/* -------------------------------------------------------------------------- */
/*                                   Logique                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Termine les déplacement du mob
 * 
 * @param mob Un pointeur sur le mob qui se déplace
 */
void finDeplacement(t_mob *mob) {
    mob->positionDeplacement = mob->position;
    mob->cooldownDeplacement = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
}





/**
 * @brief Oriente le mob vers une position
 * 
 * @param mob Un pointeur sur le mob qui doit être orienté
 */
static void orienterVersPosition(t_mob *mob) {
    const float angle = calculAngleEntrePoints(mob->position, mob->positionDeplacement);
    orienterEntite(angle, (t_entite*)mob);
}



/**
 * @brief Oriente le mob vers sa cible
 * 
 * @param mob Un pointeur sur le mob qui doit être orienté
 */
static void orienterVersCible(t_mob *mob) {
    const float angle = calculAngleEntrePoints(mob->position, mob->cible->position);
    orienterEntite(angle, (t_entite*)mob);
}





/**
 * @brief Déplace un mob vers une position cible
 * 
 * @param mob Un pointeur sur le mob qui doit se déplacer
 * @param vitesse La vitesse de déplacement du mob
 * @param cible La position cible que doit rejoindre le mob
 */
void deplacerVers(t_mob *mob, const float vitesse, const t_vecteur2 cible) {
    mob->direction.x = (cible.x - mob->position.x);
    mob->direction.y = (cible.y - mob->position.y);

    deplacerEntite((t_entite*)mob, vitesse);
    orienterVersPosition(mob);
}



/**
 * @brief Deplace un mob autour d'une position cible
 * 
 * @param mob Un pointeur sur le mob qui doit se déplacer
 * @param vitesse La vitesse de déplacement
 * @param cible La position cible autour de laquelle se déplace le mob
 */
void deplacerAutour(t_mob *mob, const float vitesse, const t_vecteur2 cible) {
    const float distance = calculDistanceEntrePoints(mob->position, cible);

    
    switch (mob->rotation) {
        case ROTATION_HORAIRE:
            mob->gamma += 0.02;
            break;
        
        case ROTATION_ANTI_HORAIRE:
            mob->gamma -= 0.02;
            break;
        
        default:
            break;
    }


    const t_vecteur2 position = {
        cos(mob->gamma) * distance,
        sin(mob->gamma) * distance,
    };


    mob->positionDeplacement.x = position.x + cible.x;
    mob->positionDeplacement.y = position.y + cible.y;


    mob->direction.x = (mob->positionDeplacement.x - mob->position.x);
    mob->direction.y = (mob->positionDeplacement.y - mob->position.y);
    

    deplacerEntite((t_entite*)mob, vitesse);
    orienterVersCible(mob);
}



/**
 * @brief Deplace le mob en direction opposé à la cible
 * 
 * @param mob Un pointeur sur le mob qui doit se déplacer
 * @param vitesse La vitesse de déplacement
 * @param cible La position de la cible de laquelle le mob s'éloigne
 */
void seloigneDe(t_mob *mob, const float vitesse, const t_vecteur2 cible) {
    mob->direction.x = (mob->position.x - cible.x);
    mob->direction.y = (mob->position.y - cible.y);

    deplacerEntite((t_entite*)mob, vitesse);
    orienterVersPosition(mob);
}


