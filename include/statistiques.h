/**
 * @file statisitques.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.3
 */





#ifndef _JEU_STATISTIQUES_
#define _JEU_STATISTIQUES_





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_statistiques
 * @brief 
 */
typedef struct s_statistiques {
    #include "attributs_statistiques.h"

    unsigned int pvMax;
    unsigned int experience;
    unsigned int niveau;
} t_statistiques;



/**
 * @struct t_baseStatistiques
 * @brief 
 */
typedef struct s_baseStatistiques {
    #include "attributs_statistiques.h"
    
    unsigned int experience_courbe;
} t_baseStatistiques;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


int calculStatistique(const int base, const int niveau);
int calculPv(const int attaque, const int defense, const int basePv);
t_statistiques genererStatistiques(const t_baseStatistiques baseStatistiques, const int niveau);





#endif