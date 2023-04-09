/**
 * @file deplacement.h
 * 
 * @brief Module de manipulation pour les déplacements
 * 
 * @author Clément Hibon
 * @date 3 mars
 */





#ifndef _JEU_DEPLACEMENT_
#define _JEU_DEPLACEMENT_



#include "mob.h"





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void deplacerVers(t_mob *mob, const float vitesse, const t_vecteur2 cible);
void deplacerAutour(t_mob *mob, const float vitesse, const t_vecteur2 cible);
void seloigneDe(t_mob *mob, const float vitesse, const t_vecteur2 cible);
void finDeplacement(t_mob *mob);

void attaquer(t_mob *mob, const float distanceFinale);





#endif