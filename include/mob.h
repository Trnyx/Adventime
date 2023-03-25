/**
 * @file mob.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 mars
 * @version 1.1
 */





#ifndef _JEU_MOB_
#define _JEU_MOB_


#include "entite.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @enum e_deplacementType
 * @brief Les différents types de déplacement
 * 
 */
typedef enum {
    DEPLACEMENT_JOUEUR = -1,
    DEPLACEMENT_STATIQUE,
    DEPLACEMENT_NORMAL,
    DEPLACEMENT_COMBAT,
} e_deplacementType;


/**
 * @enum e_rotation
 * @brief Les sens de rotations
 * 
 * Principalement utilisé par les mobs pendant les phases de combat  
 * 
 */
typedef enum {
    /*! Aucune rotation */
    ROTATION_AUCUNE,
    /*! Rotation dans le sens horaire */
    ROTATION_HORAIRE,
    /*! Rotation dans le sens anti horaire */
    ROTATION_ANTI_HORAIRE
} e_rotation;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Structure représentant un mob
 * 
 * Un mob est une entité mobile (mob correspond à l'abreviation)
 */
typedef struct s_mob {
    struct s_entiteVivante;                 /**< On "étend" la structure "entiteVivante" */

    // 
    boolean aggressif;                      /**< Si le mob est aggressif */
    t_entiteVivante *cible;                 /**< La cible du mob */


    // Deplacement 
    unsigned int rayonDeplacement;          /**< Le rayon dans lequel le mob peut se déplacer */
    t_vecteur2 positionDeplacement;         /**< La position à laquelle le mob veut se déplacer */
    e_deplacementType deplacementType;      /**< Le type de déplacement du mob */

    double gamma;
    e_rotation rotation;

    // Cooldown
    unsigned int timerDeplacement;          /**< Timer à partir duquel on calcul le temps de déplacement (en ticks) */
    unsigned int cooldownDeplacement;       /**< Cooldown entre deux déplacements (en ticks) */
    unsigned int cooldownBruitage;          /**< Cooldown entre deux bruits (en seconde) */
    

} t_mob;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_mob* creerMob(const t_vecteur2 position);
void detruireMob(t_mob **mob);

void updateMob(t_mob *mob, float distance);





#endif