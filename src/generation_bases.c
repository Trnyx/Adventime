/**
 * @file generation_bases.c
 *
 * @brief Toutes les informations de bases utiles aux générations et autres
 * 
 * - Les informations de bases des biomes
 * - Les informations de bases des végétaux
 * - Les informations de bases concernant les monstres
 * - Les informations de bases concernant les animaux
 * 
 *
 * @author Clément Hibon
 * @date 8 février
 * @version 1.2
 */



#include "../include/vegetations.h"
#include "../include/monstre.h"
#include "../include/animal.h"
#include "../include/boss.h"
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
        { SOL_EAU, SOL_SABLE }, { 70, 100 },
        // Vegetations
        { PALMIER }, { 100 }, 0.0,
        // Monstres
        { MONSTRE_TYPE_NORMAL }, { 100 },
    },
  
  
    { 
        BIOME_PLAINE, 1, 
        // Sol
        { SOL_HERBE_1, SOL_HERBE_2 }, { 55, 100 }, 
        // Vegetations
        { CHAINE }, { 100 }, 1.0,
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_PLANTE }, { 90, 100 },
    },
  
  
    { 
        BIOME_FORET, 1, 
        // Sol
        { SOL_HERBE_1, SOL_HERBE_2, SOL_HERBE_3 }, { 20, 65, 100 }, 
        // Vegetations
        { CHAINE, SAPIN }, { 80, 100 }, 3.0,
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_PLANTE }, { 10, 100 },
    },
  
  
    { 
        BIOME_MONTAGNE, 2, 
        // Sol
        { SOL_MONTAGNE_1, SOL_MONTAGNE_2 }, { 50, 100 }, 
        // Vegetations
        { SAPIN }, { 100 }, 0.7,
        // Monstres
        { MONSTRE_TYPE_MONTAGNARD }, { 100 },
    },
  
  
    // { 
    //     BIOME_DESERT, 1, 
    //     // Sol
    //     { SOL_SABLE, SOL_HERBE_1 }, { 90, 10 }, 
    //     // Vegetations
    //     { PALMIER }, { 100 }, 0.7,
    //     // Monstres
    //     { MONSTRE_TYPE_DESERTIQUE }, { 100 },
    // },
};





/* -------------------------------------------------------------------------- */
/*                                  Vegetaux                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tableau regroupant les informations de base des végétaux
 */
const t_baseVegetal basesVegetaux[] = {
    { HERBE, 1.0 },
    { CHAINE, 3.0 },
    { PALMIER, 6.0 },
    { SAPIN, 5.0 },
};





/* -------------------------------------------------------------------------- */
/*                                    Mobs                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 */
const t_baseMob basesMobs[] = {
    // Animal
    { TAG_ANIMAL_VACHE, { ITEM_STEAK }, { 100 } },
    { TAG_ANIMAL_COCHON, { ITEM_STEAK }, { 100 } },
    
    // 
    { TAG_MONSTRE_BASIC, { ITEM_MATERIEL_BATON }, { 100 } },
};





/* -------------------------------------------------------------------------- */
/*                                  Monstres                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tableau regroupant les intervales des statistiques de bases en fonction du type du monstre
 * 
 * - attaque
 * - defense
 * - vitesse
 * - pv
 * - courbeExp
 */
const t_baseStatistiquesIntervales statistiquesDeBasesIntervalesMonstres[NB_MONSTRE_TYPES] = {
    { { 20, 30 }, { 20, 30 }, { 4, 4 }, 40, { EXPERIENCE_MOYEN, EXPERIENCE_MOYEN } }, // NORMAL
    { { 25, 35 }, { 15, 25 }, { 4, 4 }, 40, { EXPERIENCE_MOYEN, EXPERIENCE_RAPIDE } }, // PLANTE
    { { 15, 25 }, { 35, 45 }, { 4, 4 }, 40, { EXPERIENCE_LENT, EXPERIENCE_RAPIDE } }, // MONTAGNARD
    // { { 55, 65 }, { 60, 70 }, { 10, 10 }, 90, { 0 } }, // EAU
    // { { 70, 75 }, { 70, 75 }, { 10, 10 }, 90, { 0 } }, // DESERTIQUE
};




/* -------------------------------------------------------------------------- */
/*                                   Animaux                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tableau regroupant les statistiques de bases en fonction de l'animal
 * 
 * - attaque
 * - defense
 * - vitesse
 * - pv
 * - courbeExp
 */
const t_baseStatistiquesIntervales statistiquesDeBasesIntervalesAnimaux[] = {
    { { 15, 20 }, { 15, 20 }, { 4, 4 }, 30, { 0 } }, // VACHE
    { { 10, 15 }, { 10, 15 }, { 4, 4 }, 30, { 0 } }, // COCHON
};





/* -------------------------------------------------------------------------- */
/*                                    Boss                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tableau regroupant les statistiques de bases en fonction de l'animal
 * 
 * - attaque
 * - defense
 * - vitesse
 * - pv
 * - courbeExp
 */
const t_baseStatistiques statistiquesDeBasesBoss[] = {
    { 0, 0, 0, 0, 0 },          // DIMANCHE
    { 50, 50, 8, 60, 0 },       // LUNDI
    { 0, 0, 0, 0, 0 },          // MARDI
    { 50, 50, 9, 50, 0 },       // MERCREDI
    { 0, 0, 0, 0, 0 },          // JEUDI
    { 50, 50, 9, 50, 0 },       // VENDREDI
    { 0, 0, 0, 0, 0 },          // SAMEDI
};