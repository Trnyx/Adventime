/**
 * @file experience.h
 *
 * @brief Module de manipulation pour l'expérience 
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.3
 */






#ifndef _JEU_EXPERIENCE_
#define _JEU_EXPERIENCE_





#include "entite.h"
#include "statistiques.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


int (*getExperienceCourbe(const e_courbeExperience courbe))(const unsigned int);

int calculExperience(t_entiteVivante *cible);
void donnerExperience(t_entiteVivante *entite, const int experience);





#endif