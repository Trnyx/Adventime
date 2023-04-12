/**
 * @file mob.h
 * 
 * @brief Module de manipulation des mobs
 * 
 * @author Clément Hibon
 * @date 3 mars
 */





#ifndef _JEU_MOB_
#define _JEU_MOB_


#include "entite.h"
#include "item.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @enum e_deplacementType
 * @brief Les différents types de déplacement
 * 
 */
typedef enum {
    /**<  */
    DEPLACEMENT_JOUEUR = -1,
    /**< Indique aucun déplacement */
    DEPLACEMENT_STATIQUE,
    /**< Indique que le mode de déplacement est normal */
    DEPLACEMENT_NORMAL,
    /**< Indique que le mode de déplacement est combat */
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
 * @struct t_mob
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



/**
 * @struct t_baseMob
 * @brief Modélise la base d'un mob
 * 
 */
typedef struct s_baseMob {
    e_entiteTag tag;                        /**< Le tag du mob */

    e_itemTag loots[2];                     /**< Les items que peut loot le mob */
    unsigned int lootProbabilite[2];        /**< Les probabilités de loot des items */
} t_baseMob;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseMob basesMobs[];





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_mob* creerMob(const t_vecteur2 position);
void detruireMob(t_mob **mob);

void updateMob(t_mob *mob, float distance);





#endif