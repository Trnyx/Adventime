/**
 * @file generation_animaux.c
 *
 * @brief Module gérant la génération des animaux
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
 * @brief Génère les informations et statistiques d'un animal en fonction de sont tag
 * 
 * @param animal Un pointeur sur l'animal à générer
 * @param tag Le tag de l'animal à générer
 * @return Le pointeur sur l'animal donné en paramètre 
 */
t_animal* genererAnimal(t_animal *animal, const e_entiteTag tag) {
    animal->tag = tag;
    
    const int niveau = getNombreAleatoire(1, 3);

    animal->baseStatistiques = genererStatistiquesDeBaseAnimal(animal->tag);
    animal->statistiques = genererStatistiques(animal->baseStatistiques, niveau);

    
    return animal;
}



/**
 * @brief Génère un troupeau d'animaux
 * 
 * @param map Un pointeur sur la map dans laquelle les animaux sont générés
 */
void genererAnimaux(t_map *map) {
    apparitionTroupeau(map->entites, map);
}