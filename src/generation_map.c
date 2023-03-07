/**
 * @file generation_map.c
 *
 * @brief Génération d'une map 
 * 
 * Voici l'algorithme de création d'une map :
 *  1. Pour chacuns des chunks de la map, un biome est sélectionné aléatoirement
 *  2. Une fois tous les biomes choisis, on normalise la map NOMBRE_DE_NORMALISATION_MAP fois
 *  3. Pour chacuns des blocks d'un chunk, un tag est sélectionné aléatoirement, celui ci dépendant du biome du chunk dans lequel il se situe
 *  4. Une fois tous les tags des blocks choisis, on normalise les blocks entre eux NOMBRE_DE_NORMALISATION_CHUNK fois
 *  5. A chaque normalisation d'un chunk on le lisse afin de supprimer (le plus possible) les éventuels blocks qui seraient rester seul lors de l'étape de la normalisation
 *  6. Une fois tous les blocks normalisé, on place la végétation
 * 
 * Ce que nous appelons la "normalisation" est le fait "d'applatire" les chunks / les blocks entre eux 
 * chacun s'élève, s'abaisse ou ne bouge pas en fonction de ce qui l'entoure
 * 
 * @author Clément Hibon
 * @date 21 janvier
 * @version 1.4
 */



#include <stdio.h>
#include <stdlib.h>

#include "../include/map.h"
#include "../include/physique.h"





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tableau regroupant les probabilités d'apparition d'un biome
 * 
 * Principalement utilisé pour récupérer la probabilité en fonction de l'index du biome souhaité
 */
const int probabilitesBiomes[NB_BIOMES] = { 
    PROBA_BIOME_PROFONDEUR,
    PROBA_BIOME_LAC, 
    PROBA_BIOME_PLAINE, 
    PROBA_BIOME_FORET, 
    PROBA_BIOME_MONTAGNE,
    PROBA_BIOME_DESERT,
};





/* -------------------------------------------------------------------------- */
/*                               Test Existence                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie si un block se situe bien à l'intérieur d'un chunk
 * 
 * @param x La coordonnée x du block (coordonnée relative au chunk)
 * @param y La coordonnée y du block (coordonnée relative au chunk)
 * @return Vrai si le block se situe bien dans un chunk, faux sinon
 * 
 * @version 1.1
 */
int blockEstDansLeChunk(const int x, const int y) {
    return x >= 0 && y >= 0 && x < TAILLE_CHUNK && y < TAILLE_CHUNK;
}


/**
 * @brief Vérifie si un block se situe bien à l'intérieur de la map
 * 
 * @param x La coordonnée x du block (cordonnée relative à la map)
 * @param y La coordonnée y du block (cordonnée relative à la map)
 * @return Vrai si le block se situe bien dans la map, faux sinon
 * 
 * @version 1.1
 */
int blockEstDansLaMap(const int x, const int y) {
    return x >= 0 && y >= 0 && x < (TAILLE_MAP * TAILLE_CHUNK) && y < (TAILLE_MAP * TAILLE_CHUNK);
}


/**
 * @brief Vérifie que un chunk est bien à l'intérieur de la map
 * 
 * @param x La coordonnée x du chunk
 * @param y La coordonnée y du chunk
 * @param z La coordonnée z du chunk (correspond à la couche du chunk)
 * @return Vrai si le chunk se situe bien dans la map, faux sinon
 * 
 * @version 1.1
 */ 
int chunkEstDansLaMap(const int x, const int y, const int z) {
    return x >= 0 && y >= 0 && z >= 0 && x < TAILLE_MAP && y < TAILLE_MAP && z < NB_COUCHE;
}



/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Récupère l'objet prédominant dans les alentours 
 * 
 * @param alentours Un tableau regroupant la quantité des éléments se situant autour de l'objet initialement observé
 * @param nbElementsAlentours Le nombre d'éléments contenue dans le tableau alentours
 * @return Une structure composé du tag de l'objet prédominant ainsi que le nombre de fois où il est apparue
 * 
 * @version 1.2
 */
t_predominance getPredominance(int alentours[], const int nbElementsAlentours) {
    t_predominance predominance = { 0, 0 };  

  
    for (int i = 0; i < nbElementsAlentours; i++) {
        if (alentours[i] >= predominance.occurence && i != predominance.tag) {
            predominance.occurence = alentours[i];
            predominance.tag = i;
        }
      
        alentours[i] = 0;
    }


    return predominance;
}





/* -------------------------------------------------------------------------- */
/*                                  Selection                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Selectionne un biome 
 * 
 * @param xChunk La coordonnée x du chunk
 * @param yChunk La coordonnée y du chunk
 * @return Le tag du biome sélectionné
 * 
 * @version 1.1
 */
e_biome selectionBiome(const int xChunk, const int yChunk) {
    // Si le chunk se situe en bordure de map Dans ce cas on force le biome à PROFONDEUR
    if (xChunk == 0 || yChunk == 0 || xChunk == TAILLE_MAP - 1 || yChunk == TAILLE_MAP - 1) return BIOME_PROFONDEUR;


    const int probabilite = getNombreAleatoire(1, 100); 

    for (int i = 0; i < NB_BIOMES; i++) {
        if (probabilitesBiomes[i] >= probabilite) return i;
    }
    
  
    return -1;
}



/**
 * @brief Selectionne le tag d'un block (sol)
 * 
 * @param biome Le biome dans lequel le block se situe
 * @return Le tag du block sélectionné
 * 
 * @version 1.1
 */
e_solTag selectionBlock(const e_biome biome) {
    e_solTag solTag = VIDE;
    const t_baseBiome baseBiome = basesBiomes[biome];
    const int nombreBlockPossible = sizeof(baseBiome.typesDeSol) / sizeof(baseBiome.typesDeSol[0]);


    while (solTag == VIDE) {
        const int index =  getNombreAleatoire(0, nombreBlockPossible - 1);
        const int probabilite =  getNombreAleatoire(1, 100);
    
        const int probabiliteBlock = baseBiome.probabiliteDesBlocks[index];
        if (probabiliteBlock >= probabilite) {
            return baseBiome.typesDeSol[index];
        }
    }
  
  
    return solTag;
}





/* -------------------------------------------------------------------------- */
/*                                 Changement                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Change le biome d'un chunk
 * 
 * @param biomePredominant Le biome prédominant autour du chunk
 * @param biomeActuel Le biome du chunk à modifier
 * @return Le nouveau biome
 * 
 * @version 1.2
 */
e_biome changerBiome(t_predominance biomePredominant, e_biome biomeActuel) { 
    // Si le biome prédominant est le même que le biome central
    // on renvoie ce dernier car aucune modification de sera apporté
    if (biomePredominant.tag == biomeActuel) return biomeActuel;

    int modificateurAltitude = 0;
    int changement = 0;
  
  
    switch (biomePredominant.tag) {
        case BIOME_DESERT: 
            if (biomePredominant.occurence >= 1 && biomePredominant.occurence <= 2) changement = 1;
            break;
        case BIOME_MONTAGNE: 
            if (biomePredominant.occurence >= 1 && biomePredominant.occurence <= 3) changement = 1;
            break;
        case BIOME_PLAINE: 
            if (biomePredominant.occurence >= 3 && biomePredominant.occurence <= 6) changement = 1;
            break;
        case BIOME_FORET: 
            if (biomePredominant.occurence >= 2 && biomePredominant.occurence <= 4) changement = 1;
            break;
        case BIOME_LAC: 
            if (biomePredominant.occurence >= 3) changement = 1;
            break;
        case BIOME_PROFONDEUR: 
            if (biomePredominant.occurence >= 3 && biomePredominant.occurence <= 5) changement = 1;
            break;
    }


    // En cas de changement d'altitude du biome
    // On surélève le biome central si le biome prédominant et plus haut que ce dernier
    // A l'inverse, si le biome prédominant est plus bas, alors on rabaisse le biome central
    if (changement) {
        if (biomePredominant.tag > biomeActuel) 
            modificateurAltitude = 1;
        else if (biomePredominant.tag < biomeActuel)
            modificateurAltitude = -1;
    }


    return biomeActuel + modificateurAltitude;
}





/**
 * @brief Change le tag du block
 * 
 * @param blockPredominant Le tag du block prédominant autour du block
 * @param blockActuel Le tag du block à modifier
 * @return Le nouveau tag du block
 * 
 * @version 1.2
 */
e_solTag changerBlock(t_predominance blockPredominant, e_solTag blockActuel) {
    // Si le block prédominant est le même que le block central alors on renvoie ce dernier
    // Sinon on ajoute à la hauteur du block principale la différence entre 
    // la hauteur du block principal et celle du block prédominant
    if (blockPredominant.tag == blockActuel) return blockActuel;
    return blockActuel + (blockPredominant.tag - blockActuel);
}





/* -------------------------------------------------------------------------- */
/*                                  Alentours                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Récupère les biomes aux alentours d'un chunk
 * 
 * @param chunk Le chunk central
 * @param map La map dans laquelle se situent les différents chunks
 * @return Un tableau contenant le nombre d'occurence des biomes alentours
 * 
 * @version 1.2
 */
int* getBiomesAlentours(t_chunk *chunk, t_map *map) {
    static int biomesAlentours[NB_BIOMES] = { 0 };
    t_chunk *chunkCourrant = NULL;
  

    for (int y = chunk->position.y - 1; y <= chunk->position.y + 1; y++) {
        for (int x = chunk->position.x - 1; x <= chunk->position.x + 1; x++) {
            if (x == chunk->position.x && y == chunk->position.y) continue;
            if (!chunkEstDansLaMap(x, y, COUCHE_SOL)) continue;

          
            chunkCourrant = getChunk(x, y, COUCHE_SOL, map);
            if (chunkCourrant != NULL) {
                biomesAlentours[chunkCourrant->biome]++;
            }
        }
    }


    return biomesAlentours;
}



/**
 * @brief Récupère les tags des blocks alentours
 * 
 * @param xBlock La coordonnée x (relative à la map) du block central
 * @param yBlock La coordonnée y (relative à la map) du block central
 * @param map La map dans laquelle se situent les différents blocks
 * @return Un tableau contenant le nombre d'occurence des tags des blocks alentours
 * 
 * @version 1.1
 */
int* getBlocksAlentours(const int xBlock, const int yBlock, t_map *map) {
    static int blocksAlentours[NB_TYPES_SOL] = { 0 };
    t_chunk *chunk = NULL;
    t_block *block = NULL;

  
    for (int y = yBlock - 1; y <= yBlock + 1; y++) {
        for (int x = xBlock - 1; x <= xBlock + 1; x++) {
            if (x == xBlock && y == yBlock) continue;
            if (!blockEstDansLaMap(x, y)) continue;

            chunk = getChunkGraceABlock(x, y, COUCHE_SOL, map);
            if (chunk == NULL) continue;


            block = getBlockDansChunk(x % TAILLE_CHUNK, y % TAILLE_CHUNK, chunk);
            if (block == NULL) continue;
          
          
            blocksAlentours[block->tag]++;
        }
    }


    return blocksAlentours;
}





/* -------------------------------------------------------------------------- */
/*                                Normalisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief "Normalise" les blocks d'un chunk
 * 
 * @param chunk Le chunk qui doit être normalisé
 * @param map La map dans laquelle le tout se situe
 * 
 * @version 1.3
 */
void normalisationDuChunk(t_chunk* chunk, t_map *map) {
    e_solTag blockVoisins[TAILLE_CHUNK][TAILLE_CHUNK] = { SOL_EAU_PROFONDE };
    t_block *block = NULL;


    for (int y = 0; y < TAILLE_CHUNK; y++) {
        for (int x = 0; x < TAILLE_CHUNK; x++) {
            block = getBlockDansChunk(x, y, chunk);

            int *blocksAlentours = getBlocksAlentours(block->position.x, block->position.y, map);
            t_predominance blockPredominant = getPredominance(blocksAlentours, NB_TYPES_SOL);

            if (blockPredominant.occurence >= 2) {
                blockVoisins[x][y] = changerBlock(blockPredominant, block->tag);
            }
            else {
                blockVoisins[x][y] = block->tag;
            }
        }
    }


    for (int x = 0; x < TAILLE_CHUNK; x++) {
        for (int y = 0; y < TAILLE_CHUNK; y++) {
            block = getBlockDansChunk(x, y, chunk);
            block->tag = blockVoisins[x][y];
        }
    }
}



/**
 * @brief Lisse les blocks d'un chunk en fonction d'un ceuil
 * 
 * @param chunk Le chunk qui doit être lissé
 * @param map La map dans laquelle le tout se situe
 * @param ceuil Le ceuil à partir du quelle un block est concidéré comme étant à être modifié
 * 
 * @version 1.2
 */
void lissageDuChunk(t_chunk* chunk, t_map *map, const int ceuil) {
    e_solTag hauteurVoisins[TAILLE_CHUNK][TAILLE_CHUNK] = { 0 };
    t_block *block = NULL;


    for (int x = 0; x < TAILLE_CHUNK; x++) {
        for (int y = 0; y < TAILLE_CHUNK; y++) {
            block = getBlockDansChunk(x, y, chunk);
            int *blocksAlentours = getBlocksAlentours(block->position.x, block->position.y, map);

            for (int i = 0; i < NB_TYPES_SOL; i++) {
                if (i > block->tag)
                    hauteurVoisins[x][y] += blocksAlentours[i];
                else if (i < block->tag)
                    hauteurVoisins[x][y] -= blocksAlentours[i];

                blocksAlentours[i] = 0;
            }

        }
    }


    for (int x = 0; x < TAILLE_CHUNK; x++) {
        for (int y = 0; y < TAILLE_CHUNK; y++) {
            block = getBlockDansChunk(x, y, chunk);

            if (hauteurVoisins[x][y] >= ceuil) 
                block->tag++;
            else if (hauteurVoisins[x][y] <= -ceuil)
                block->tag--;
        }
    }
}





/**
 * @brief "Normalise" les chunks d'une map
 * 
 * @param map La map à normaliser
 * 
 * @version 1.1
 */
void normalisationDeLaMap(t_map* map) {  
    e_biome nouveauxBiomes[TAILLE_MAP][TAILLE_MAP] = { BIOME_PROFONDEUR };
    t_chunk *chunk = NULL;


    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            chunk = getChunk(x, y, COUCHE_SOL, map);
            if (chunk == NULL) continue;
            if (!chunkEstDansLaMap(x, y, COUCHE_SOL)) continue;
          
            int *biomesAlentours = getBiomesAlentours(chunk, map);
            t_predominance biomePredominant = getPredominance(biomesAlentours, NB_BIOMES);

          
            nouveauxBiomes[x][y] = changerBiome(biomePredominant, chunk->biome);
        }
    }


    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            chunk = getChunk(x, y, COUCHE_SOL, map);
            chunk->biome = nouveauxBiomes[x][y];
        }
    }
}





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief Initialise un chunk
 * 
 * Positionne le chunk aux coordonnées données, sélectionne son biome 
 * et alloue la mémoire nécessaire pour stocker les blocks qui seront stockés dans le chunk
 * 
 * @param x La coordonnée x du chunk
 * @param y La coordonnée y du chunk
 * @param z La coordonnée z du chunk
 * @return Le chunk initialisé 
 * 
 * @version 1.2
 */
t_chunk initialisationChunk(const int x, const int y, const int z) {
    t_chunk chunk;


    chunk.blocks = calloc(TAILLE_CHUNK * TAILLE_CHUNK, sizeof(t_block));
    chunk.biome = selectionBiome(x, y);

    t_vecteur3 position = { x, y, z };
    chunk.position = position;


    return chunk;
}





/* -------------------------------------------------------------------------- */
/*                                 Generation                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Génère un block
 * 
 * Positionne le block au sein du chunk aux coordonnées données ainsi que dans la map et sélectionne 
 * 
 * @param x La coordonnée x du block (relative au chunk)
 * @param y La coordonnée y du block (relative au chunk)
 * @param chunk Le chunk dans lequel le block se situe
 * @param estVide Si le bloc à initialisé doit être vide
 * @return Le block généré
 * 
 * @version 1.2
 */
t_block generationBlock(const int x, const int y, const t_chunk *chunk, const boolean estVide) {
    t_block block;


    block.tag = estVide == VRAI ? VIDE : selectionBlock(chunk->biome);

    t_vecteur2 position = { (TAILLE_CHUNK * chunk->position.x) + x, (TAILLE_CHUNK * chunk->position.y) + y };
    t_vecteur2 positionDansChunk = { x, y };
  
    block.position = position;
    block.positionDansChunk = positionDansChunk;


    return block;
}



/**
 * @brief Génère un chunk
 * 
 * @param chunk Un pointeur sur le chunk qui a été préalablement initialisé
 * @param map Un pointeur sur la map dans laquelle le chunk se situe
 * @param estVide Si le chunk à générer doit être vide
 * @return Un pointeur sur le chunk généré
 * 
 * @version 1.3
 */
t_chunk* generationChunk(t_chunk *chunk, t_map *map, const boolean estVide) {
    for (int x = 0, i = 0; x < TAILLE_CHUNK; x++) {
        for (int y = 0; y < TAILLE_CHUNK; y++) {
            chunk->blocks[i++] = generationBlock(x, y, chunk, estVide);
        }
    }


    // Si le chunk est vide, tous les blocks sont identiques (VIDE)
    // il n'y a donc nul besoin de normaliser le chunk 
    if (estVide == VRAI) return chunk;


    for (int i = 0; i < NOMBRE_DE_NORMALISATION_CHUNK; i++) {
        normalisationDuChunk(chunk, map);
        lissageDuChunk(chunk, map, 7 - i);
    }

    lissageDuChunk(chunk, map, 5);


    return chunk;
}




/**
 * @brief 
 * 
 * @param map 
 * @return t_map* 
 */
t_map* genererOverworld(t_map *map) {
    t_chunk* chunkTempo = NULL;


    map->chunks = calloc(TAILLE_MAP * TAILLE_MAP * NB_COUCHE, sizeof(t_chunk));


    for (int i = 0, x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            for (int z = 0; z < NB_COUCHE; z++) {
                map->chunks[i++] = initialisationChunk(x, y, z);
            }
        }
    }


    for (int i = 0; i < NOMBRE_DE_NORMALISATION_MAP; i++) {
        normalisationDeLaMap(map);
    }


    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            for (int z = 0; z < NB_COUCHE; z++) {
                chunkTempo = getChunk(x, y, z, map);

                if (z == COUCHE_SOL) 
                    generationChunk(chunkTempo, map, FAUX);
                else
                    generationChunk(chunkTempo, map, VRAI);
            }
        }
    }


    genererVegetations(map);

    genererAnimaux(map);


    return map;
}





/**
 * @brief Génère une map compplète
 * 
 * @return Un pointeur sur la map générée
 * 
 * @version 1.2
 */
t_map* genererMap(e_mapType type) {
    printf("Generation map => ");

    t_map* map = malloc(sizeof(t_map));

    if (map == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour la map\n");
        free(map);
        return NULL;
    }

    map->entites = malloc(sizeof(t_liste));
    init_liste(map->entites);

    map->type = type;
    

    switch (type) {
        case MAP_OVERWORLD: genererOverworld(map); break;
        // case MAP_CAVE: genererCave(map); break;
        default:
            break;
    }
    

    printf("Succes\n");
    return map;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param block 
 * @return int 
 * 
 * @version 1.1
 */
int detruireBlock(t_block **block) {
    if (block == NULL || *block == NULL) return 0;

    free(*block);
    *block = NULL;

    return 0;
}


/**
 * @brief 
 * 
 * @param chunk 
 * @return int 
 * 
 * @version 1.2
 */
int detruireChunk(t_chunk **chunk) {
    if (chunk == NULL || *chunk == NULL) return 0;


    free((*chunk)->blocks);
    (*chunk)->blocks = NULL;

  
    return 0;
}


/**
 * @brief 
 * 
 * @param map 
 * @return int 
 * 
 * @version 1.2
 */
int detruireMap(t_map **map) {
    printf("Destruction Map => ");
    if (map == NULL || *map == NULL) return 0;
    t_chunk *chunk = NULL;
  

    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            for (int z = 0; z < NB_COUCHE; z++) {
                chunk = getChunk(x, y, z, *map);
                detruireChunk(&chunk);
            }
        }
    }


    free((*map)->chunks);
    (*map)->chunks = NULL;
  
    free(*map);
    *map = NULL;

  
    return 0;
}






/**
 * Generation map
 *      Initialisationn Chunk
 *      Normalisation Chunk
 *      Génération Chunk
 *          Initialisation Block
 *          Normalisation Block
 *          Génération Block
 */