/**
 * @file deplacement.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 mars
 * @version 1.1
 */





#ifndef _JEU_DEPLACEMENT_
#define _JEU_DEPLACEMENT_



#include "mob.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */



/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


int (*getDeplacement(e_deplacementType deplacement))(t_mob*, const float);

void deplacerVers(t_mob *mob, const t_vecteur2 cible);
void deplacerAutour(t_mob *mob, const t_vecteur2 cible);
void seloigneDe(t_mob *mob, const t_vecteur2 cible);
void finDeplacement(t_mob *mob);






#endif