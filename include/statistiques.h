/*
 * \file 
 *
 * \brief
 *
 * \author
 */



#ifndef _JEU_STATISTIQUES_
#define _JEU_STATISTIQUES_





/*
 * \struct t_statistiques
 * \brief 
 */
typedef struct s_statistiques {
    #include <attributs_statistiques.h>

    int pvMax;
    int experience;
    int niveau;
} t_statistiques;



/*
 * \struct t_baseStatistiques
 * \brief 
 */
typedef struct s_baseStatistiques {
    #include <attributs_statistiques.h>
    
    int experience_courbe;
} t_baseStatistiques;





#endif