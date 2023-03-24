/**
 * @file generation_caverne.c
 *
 * @brief Génération d'une caverne 
 * 
 * Voici l'algorithme de création d'une caverne :
 *  1. Pour chacuns des chunks de la caverne, un biome est sélectionné aléatoirement
 * 
 * Ce que nous appelons la "normalisation" est le fait "d'applatire" les chunks / les blocks entre eux 
 * chacun s'élève, s'abaisse ou ne bouge pas en fonction de ce qui l'entoure
 * 
 * @author Clément Hibon
 * @date 23 mars
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/map.h"





void genererCave(t_map *map) {
    t_chunk* chunkTempo = NULL;

    map->chunks = calloc(TAILLE_MAP * TAILLE_MAP * NB_COUCHE, sizeof(t_chunk));


}