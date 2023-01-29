/**
 * @file monstre.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @version 1.1
 */





#ifndef _JEU_MONSTRE_
#define _JEU_MONSTRE_



#include <statistiques.h>
#include <entite.h>





typedef enum s_monstreTag {
    OISEAU
} e_monstreTag;


typedef enum s_monstreType {
    NORMAL,
    PLANTE,
    MONTAGNE,
} e_typeMonstre;




/**
 * @struct t_monstre
 * @brief Structure modélisant un monstre
 */
typedef struct s_monstre {
    struct entite_s;
    
    char* name;                             /**< Le nom d'un Monstre */

    e_monstreTag tag;                       /**< Le tag du Monstre */
    e_typeMonstre type;                     /**< Le type du Monstre */
    
    t_statistiques statistiques;            /**< Les statistiques du Monstre */
    t_baseStatistiques baseStatistiques;    /**< Les statistiques de base du Monster */
} t_monstre;





t_monstre creerMonstre();





#endif