/**
 * @file generation_animaux.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 28 février
 * @version 1.1
 */



#include <stdio.h>
#include <stdlib.h>

#include "../include/utilitaire.h"
#include "../include/animal.h"
#include "../include/map.h"





/* -------------------------------------------------------------------------- */
/*                                 Generation                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param animal 
 * @param tag 
 * @return t_animal* 
 */
t_animal* genererAnimal(t_animal *animal, const e_entiteTag tag) {
    animal->tag = tag;
    
    const int niveau = getNombreAleatoire(1, 3);

    animal->baseStatistiques = genererStatistiquesDeBaseAnimal(animal->tag);
    animal->statistiques = genererStatistiques(animal->baseStatistiques, niveau);

    
    return animal;
}



/**
 * @brief 
 * 
 * @param map 
 */
void genererAnimaux(t_map *map) {
    printf("GENERATION ANIMAUX => ");
    apparitionTroupeau(map->entites, map);
}