/**
 * @file statisitques.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.1
 */





#ifndef _JEU_STATISTIQUES_
#define _JEU_STATISTIQUES_





/**
 * @struct t_statistiques
 * @brief 
/**
 * @struct t_statistiques
 * @brief 
 */
typedef struct s_statistiques {
    #include "attributs_statistiques.h"
    #include "attributs_statistiques.h"

    unsigned int pvMax;
    unsigned int experience;
    unsigned int niveau;
} t_statistiques;



/**
 * @struct t_baseStatistiques
 * @brief 
/**
 * @struct t_baseStatistiques
 * @brief 
 */
typedef struct s_baseStatistiques {
    #include "attributs_statistiques.h"
    #include "attributs_statistiques.h"
    
    unsigned int experience_courbe;
} t_baseStatistiques;





#endif