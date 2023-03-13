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
#include "mob.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */





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
} t_animal;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseStatistiques baseStatistiquesAnimaux[];





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */
// #include "map.h"
typedef struct s_map t_map;


t_baseStatistiques genererStatistiquesDeBaseAnimal(const e_entiteTag tag);

t_animal* genererAnimal(t_animal *animal, const e_entiteTag tag);
t_animal* creerAnimal(const t_vecteur2 position, const e_entiteTag tag);
void apparitionAnimal(const t_vecteur2 positionTroupeau, t_liste *entites, t_map *map);
void apparitionTroupeau(t_liste *entites, t_map *map);

void detruireAnimal(t_animal **animal);





#endif