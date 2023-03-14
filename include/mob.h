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
 * @brief 
 * 
 */
typedef enum {
    DEPLACEMENT_JOUEUR = -1,
    DEPLACEMENT_STATIQUE,
    DEPLACEMENT_NORMAL,
    DEPLACEMENT_COMBAT,
} e_deplacementType;


/**
 * @brief 
 * 
 */
typedef enum {
    ROTATION_AUCUNE,
    ROTATION_HORAIRE,
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
    struct s_entiteVivante;                 /**< inclue les bases d'une entité */

    // 
    boolean aggressif;                      /**< Si le mob est aggressif */
    t_entiteVivante *cible;                 /**< La cible du mob */


    // Deplacement 
    unsigned int rayonDeplacement;          /**< Le rayon dans lequel le mob peut se déplacer */
    t_vecteur2 positionDeplacement;               /**< La position à laquelle le mob veut se déplacer */
    e_deplacementType deplacementType;      /**< Le type de déplacement du mob */

    

    unsigned int timerDeplacement;          /**< Timer à partir duquel on calcul le temps de déplacement (en ticks) */
    unsigned int cooldownDeplacement;       /**< Cooldown entre deux déplacements (en ticks) */
    

    // Attaque
    unsigned int cooldownAttaque;       /**< Cooldown entre deux attaque (en seconde) */
} t_mob;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_mob* creerMob(const t_vecteur2 position);
void detruireMob(t_mob **mob);

void updateMob(t_mob *mob, float distance);





#endif