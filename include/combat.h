/**
 * @file combat.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 10 février
 * @version 1.1
 */





#ifndef _JEU_COMBAT_
#define _JEU_COMBAT_



#include "utilitaire.h"
#include "entite.h"




/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


boolean toucheLaCible(const t_vecteur2 mob, const t_vecteur2 cible, const float angleAttaque, const float range);
float calculDegat(const int niveauAttaquant, int pointAttaque, int pointDefense, const boolean attaquantEstNocture, const boolean defenseurEstNocturne);
boolean appliquerDegat(t_entiteVivante *entite, const float degat);
void metUnCoup(t_entiteVivante *entie, t_entiteVivante *cible, const float angleAttaque, const float range);
void mort(t_entiteVivante *entite);





#endif