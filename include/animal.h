/**
 * @file animal.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 28 février
 * @version 1.1
 */





#ifndef _JEU_ANIMAUX_
#define _JEU_ANIMAUX_





#include "statistiques.h"
#include "entite.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Enumérateur regroupant les différents tags des animaux
 * 
 * Un compteur du nombre de tags est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    ANIMAUX_VACHE,
    ANIMAUX_COCHON,
    ANIMAUX_POULET,
    NB_ANIMAUX_TAGS
} e_animalTag;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Modélise un animal
 */
typedef struct s_animal {
    // #include "attributs_entite.h"
    struct s_mob;
    
    char* name;                             /**< Le nom de l'animal */

    int rayonDetection;                     /**< Le rayon dans lequel le joueur sera détecté */

    e_animalTag tag;                        /**< Le tag de l'animal */

    t_statistiques statistiques;            /**< Les statistiques de l'animal */
} t_animal;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */
#include "map.h"
typedef struct s_map t_map;

t_animal* genererAnimal(t_animal *animal, const e_biome biome);
t_animal* creerAnimal(const t_vecteur2 position, const e_biome biome);
void apparitionAnimal(t_liste *entites, t_map *map, const t_vecteur2 positionJoueur);

void detruireAnimal(t_animal **animal);





#endif