/**
 * @file logique_physique.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 10 février
 * @version 1.1
 */



#include <stdlib.h>
#include <stdio.h>

#include "../include/physique.h"



/* -------------------------------------------------------------------------- */
/*                                    Algo                                    */
/* -------------------------------------------------------------------------- */

/* --------------------------------- Entités -------------------------------- */

// Entitées Actuelles 
//  Pour chacune des entités, on calcul la distance entre celle ci et le joueur
//  Si l'entité se situe dans le rayon au dela du rayon inactif
//      Si monstre aggressif
//          Suppression du monstre
//      Sinon
//          Ignore l'entité
//  Si l'entité se situe dans le rayon actif
//      Gestion de la logique 
//          - déplacement
//          - joueur détection
//          - combat
//  Sinon Si l'entité se situe dans le rayon semi actif 
//      Gestion de la durée de vie 
//  Pour toutes les entités non ignorées, ajout du temps
//  
//  
//
// Spawn
//  Si mob cap non atteint
//      Si le nombre de monstres aggressifs max n'est pas atteint
//          Calcul la probabilité d'apparition d'un monstre
//          Si apparition possible
//              Apparition du monste dans le rayon semi actif
//      Si le nombre de monstres passif max n'est pas atteint
//          Calcul la probabilité d'apparition d'un monstre
//          Si apparition possible
//              Apparition du monste dans le rayon semi actif
//      Si le nombre d'animaux max n'est pas atteint
//          Calcul la probabilité d'apparition d'un animal
//          Si apparition possible
//              Apparition de l'animal dans le rayon actif ou semi actif




// Fonction à executer à chaque frame
void logique() {
    
}
