/**
 * @file generation_bases.c
 *
 * @brief 
 * 
 *
 * @author Clément Hibon
 * @date 8 février
 * @version 1.1
 */



#include "../include/vegetations.h"
#include "../include/monstre.h"
#include "../include/map.h"





/* -------------------------------------------------------------------------- */
/*                                     Map                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tableau initialisant toutes les informations de bases d'un biome 
 * 
 * Les différents informations définis :
 *      - Le biome
 *      - L'altitude du biome
 *      - Les types de sol que peut avoir le biome
 *      - Les probabilites (cumulative) d'apparition des sols
 *      - Les tag des végétaux pouvant apparaitre dans le biome
 *      - Les probabilites d'apparition des tags des végétaux
 *      - La densite de la végétation
 *      - Les types des monstres qui peuvent apparaitre dans le biome
 *      - Les probabilites d'apparition des types des monstres
 */
const t_baseBiome basesBiomes[] = {
    { 
        BIOME_PROFONDEUR, -1, 
        // Sol
        { SOL_EAU_PROFONDE, SOL_EAU }, { 100, 0 },
        // Vegetations
        { 0 }, { 0 }, 0.0,
        // Monstres
        { 0 }, { 0 },
    },


    { 
        BIOME_LAC, 0, 
        // Sol
        { SOL_EAU, SOL_SABLE }, { 70, 30 },
        // Vegetations
        { PALMIER }, { 100 }, 0.0,
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_EAU }, { 15, 85 },
    },
  
  
    { 
        BIOME_PLAINE, 1, 
        // Sol
        { SOL_HERBE_1, SOL_HERBE_2 }, { 55, 45 }, 
        // Vegetations
        { CHAINE }, { 30 }, 1.0,
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_PLANTE }, { 90, 10 },
    },
  
  
    { 
        BIOME_FORET, 1, 
        // Sol
        { SOL_HERBE_1, SOL_HERBE_2, SOL_HERBE_3 }, { 30, 40, 20 }, 
        // Vegetations
        { CHAINE }, { 100 }, 3.0,
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_PLANTE }, { 30, 70 },
    },
  
  
    { 
        BIOME_MONTAGNE, 2, 
        // Sol
        { SOL_MONTAGNE_1, SOL_MONTAGNE_2 }, { 50, 50 }, 
        // Vegetations
        { CHAINE, SAPIN }, { 50, 50 }, 0.7,
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_MONTAGNARD }, { 15, 85 },
    },
};





/* -------------------------------------------------------------------------- */
/*                                  Vegetaux                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tableau regroupant les informations de base des végétaux
 */
const t_baseVegetal basesVegetaux[] = {
    { HERBE, 1.0 },
    // { ROSE, 3.0 },
    // { TULIPE, 3.0 },
    { CHAINE, 3.0 },
    { PALMIER, 6.0 },
    { SAPIN, 5.0 },
};





/* -------------------------------------------------------------------------- */
/*                                  Monstres                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tableau regroupant les intervales des statistiques de bases en fonction du type du monstre
 * 
 */
const t_baseStatistiquesIntervales statistiquesDeBasesIntervales[NB_MONSTRE_TYPES] = {
    { { 60, 70 }, { 60, 70 }, { 10, 10 }, 80, { 0 } }, // NORMAL
    { { 65, 75 }, { 55, 65 }, { 15, 15 }, 80, { 0 } }, // PLANTE
    { { 55, 65 }, { 60, 70 }, { 10, 10 }, 90, { 0 } }, // EAU
    { { 55, 65 }, { 75, 85 }, { 15, 15 }, 80, { 0 } }, // MONTAGNARD
};