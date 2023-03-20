/**
 * @file boss.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 18 mars
 * @version 1.1
 */



#ifndef _JEU_BOSS_
#define _JEU_BOSS_





#include "mob.h"
#include "statistiques.h"





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_boss_flags
 * @brief 
 * 
 */
typedef struct s_boss_flags {
    unsigned int lundi;
    unsigned int mercredi;
    unsigned int vendredi;
} t_boss_flags;





/**
 * @struct t_boss
 * @brief 
 * 
 */
typedef struct s_boss {
    struct s_mob;

    
} t_boss;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_boss_flags initialiserBossFlags();





#endif