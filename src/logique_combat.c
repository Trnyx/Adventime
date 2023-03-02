/**
 * @file logique_combat.c
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




//   Check distance et ouverture
//   Si assez proche et dans l'ouverture 
//     Calcul de dégât (attaque / défense)
//     Application des dégâts
//     Check mort
//     Si mort
//       Gestion des drops (inventaire / items)
//       Calcul de l'expérience gagné / perdu
//       Donne l'expérience au gagnant
//       Retire l'expérience au perdant
