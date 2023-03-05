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
    ATTENTE,
    SE_DEPLACE_VERS,
    SE_DEPLACE_AUTOUR,
    S_ELOIGNE_DE,
} e_operation;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Structure représentant un mob
 * 
 * Un mob est une entité mobile (mob correspond à l'abreviation)
 */
typedef struct s_mob {
    struct s_entite;                        /**< inclue les bases d'une entité */

    // 
    boolean aggressif;                      /**< Si le mob est aggressif */

    // Deplacement 
    e_operation operation;                  /**< Ce que fait le mob */
    unsigned int rayonDeplacement;          /**< Le rayon dans lequel le mob peut se déplacer */
    t_vecteur2 positionDeplacement;               /**< La position à laquelle le mob veut se déplacer */

    unsigned int timestampDebutDeplacement; /**< Timestamp de départ de déplacement */
    unsigned int timestampFinDeplacement;   /**< Timestamp de fin de déplacement */
    unsigned int delaiAttenteDeplacement;   /**< Temps d'attente entre deux déplacements (en seconde) */
    
    e_deplacementType deplacementType;      /**< Le type de déplacement du mob */

    // Attaque
    unsigned int timestampAttaque;          /**< Timestamp de la dernière attaque */
    unsigned int delaiAttenteAttaque;       /**< Temps d'attente entre deux attaque (en seconde) */
} t_mob;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_mob* creerMob(const t_vecteur2 position);
void detruireMob(t_mob **mob);

void updateMob(t_mob *mob, const float distance);





#endif