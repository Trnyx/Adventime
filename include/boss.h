/**
 * @file boss.h
 * 
 * @brief Module de gestion des boss
 * 
 * @author Clément Hibon
 * @date 18 mars
 */



#ifndef _JEU_BOSS_
#define _JEU_BOSS_





#include "temps.h"
#include "monstre.h"
#include "statistiques.h"





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_boss_flags
 * @brief Les flags indiquant si le boss du jour correspondant a été vaincu
 * 
 */
typedef struct s_boss_flags {
    unsigned int lundi;         /**< Flag pour le boss du lundi */
    unsigned int mercredi;      /**< Flag pour le boss du mercredi */
    unsigned int vendredi;      /**< Flag pour le boss du vendredi */
} t_boss_flags;





/**
 * @struct t_boss
 * @brief Structure modélisant un boss
 * 
 */
typedef struct s_boss {
    struct s_mob;                   /**< "Etend" la structure mob */

    boolean peutAttaquerJoueur;     /**< Vérifie que le boss peut attaquer le joueur */
    e_jour jour;                    /**< Le jour du boss */
} t_boss;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseStatistiques statistiquesDeBasesBoss[];





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_boss_flags initialiserBossFlags();

t_vecteur2 getPointApparitionBoss(t_map *map);
t_boss* chargerBoss();
t_boss* creerBoss(const t_vecteur2 position, const e_jour jour);






#endif