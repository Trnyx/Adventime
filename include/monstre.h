/*
 * \file 
 *
 * \brief
 *
 * \author
 */



#ifndef _JEU_MONSTRE_
#define _JEU_MONSTRE_



#include "entite.h"
#include "statistiques.h"





typedef enum s_monstreTag {
    OISEAU
} t_monstreTag;


typedef enum s_monstreType {
    MONTAGNARD,
    PLANTE
} t_monstreType;




/*
 * \struct t_monstre
 * \brief Structure modélisant un monstre
 */
typedef struct s_monstre {
    struct s_entite;
    
    char* name;                             /**< Le nom d'un Monstre */

    t_monstreTag tag;                       /**< Le tag du Monstre */
    t_monstreType type;                     /**< Le type du Monstre */
    
    t_statistiques statistiques;            /**< Les statistiques du Monstre */
    t_baseStatistiques baseStatistiques;    /**< Les statistiques de base du Monster */
} t_monstre;





t_monstre creerMonstre();





#endif