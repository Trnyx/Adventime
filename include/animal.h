/**
 * @file animal.h
 *
 * @brief Module de manipulation des animaux
 *
 * @author Clément Hibon
 * @date 28 février
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
 * @struct t_animal
 * @brief Modélise un animal
 */
typedef struct s_animal {
    struct s_mob;           /**< On "étend" la structure "mob" */
    
    char* name;             /**< Le nom de l'animal */
} t_animal;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const t_baseStatistiquesIntervales statistiquesDeBasesIntervalesAnimaux[];





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */

typedef struct s_map t_map;


t_baseStatistiques genererStatistiquesDeBaseAnimal(const e_entiteTag tag);

t_animal* genererAnimal(t_animal *animal, const e_entiteTag tag);
t_animal* creerAnimal(const t_vecteur2 position, const e_entiteTag tag);
void apparitionAnimal(const t_vecteur2 positionTroupeau, t_liste *entites, t_map *map, const e_entiteTag tag);
void apparitionTroupeau(t_liste *entites, t_map *map);

void detruireAnimal(t_animal **animal);





#endif
