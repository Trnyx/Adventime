/**
 * @file generation_map.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @version 1.1
 */



#include <stdlib.h>
#include <map.h>





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


const e_biome biomes[] = { 
    BIOME_PROFONDEUR, 
    BIOME_LAC,
    BIOME_PLAINE, 
    BIOME_FORET, 
    BIOME_MONTAGNE,
};


const int probabilitesBiomes[] = { 
    PROBA_BIOME_PROFONDEUR,
    PROBA_BIOME_LAC, 
    PROBA_BIOME_PLAINE, 
    PROBA_BIOME_FORET, 
    PROBA_BIOME_MONTAGNE 
};


const t_baseBiome basesBiomes[] = {
    { 
        BIOME_PROFONDEUR, -1, 
        // Sol
        { SOL_EAU_PROFONDE, SOL_EAU }, { 100, 0 },
        // Vegetations
        { 0 }, { 0 }, { 0.0 },
        // Monstres
        { 0 }, { 0 },
    },


    { 
        BIOME_LAC, 0, 
        // Sol
        { SOL_EAU, SOL_SABLE }, { 70, 30 },
        // Vegetations
        { PALMIER }, { 100 }, { 0.0 },
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_EAU }, { 15, 85 },
    },
  
  
    { 
        BIOME_PLAINE, 1, 
        // Sol
        { SOL_HERBE_1, SOL_HERBE_2 }, { 55, 45 }, 
        // Vegetations
        { CHAINE }, { 30 }, { 1.0 },
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_PLANTE }, { 90, 10 },
    },
  
  
    { 
        BIOME_FORET, 1, 
        // Sol
        { SOL_HERBE_1, SOL_HERBE_2, SOL_HERBE_3 }, { 30, 40, 20 }, 
        // Vegetations
        { CHAINE }, { 100 }, { 3.0 },
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_PLANTE }, { 30, 70 },
    },
  
  
    { 
        BIOME_MONTAGNE, 2, 
        // Sol
        { SOL_MONTAGNE_1, SOL_MONTAGNE_2 }, { 50, 50 }, 
        // Vegetations
        { CHAINE, SAPIN }, { 50, 50 }, { 1.0, 2.0 },
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_MONTAGNARD }, { 15, 85 },
    },
};





/* -------------------------------------------------------------------------- */
/*                               Test Existence                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @return 
 * 
 * @version 1.1
 */
int blockEstDansLeChunk(const int x, const int y) {
    return x >= 0 && y >= 0 && x < TAILLE_CHUNK - 1 && y < TAILLE_CHUNK - 1;
}


/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @return 
 * 
 * @version 1.1
 */
int blockEstDansLaMap(const int x, const int y) {
    return x >= 0 && y >= 0 && x < (TAILLE_MAP * TAILLE_CHUNK) - 1 && y < (TAILLE_MAP * TAILLE_CHUNK) - 1;
}


/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @return 
 * 
 * @version 1.1
 */ 
int chunkEstDansLaMap(const int x, const int y, const int z) {
    return x >= 0 && y >= 0 && z >= 0 && x < TAILLE_MAP - 1 && y < TAILLE_MAP - 1;
}



/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Get the Block Dans Chunk object
 * 
 * @param x 
 * @param y 
 * @param chunk 
 * @return t_block* 
 * 
 * @version 1.2
 */
t_block* getBlockDansChunk(const int x, const int y, t_chunk *chunk) {
    for (int i = 0; i < TAILLE_CHUNK * TAILLE_CHUNK; i++) {
        if (chunk->blocks[i].positionDansChunk.x == x && chunk->blocks[i].positionDansChunk.y == y) {
            return &chunk->blocks[i];
        }
    }

    return NULL;
}



/**
 * @brief Get the Chunk object
 * 
 * @param x 
 * @param y 
 * @param map 
 * @return t_chunk* 
 * 
 * @version 1.2
 */
t_chunk* getChunk(const int x, const int y, const int couche, t_map *map) {
    for (int i = 0; i < TAILLE_MAP * TAILLE_MAP * NB_COUCHE; i++) {
        if (map->chunks[i].position.x == x && map->chunks[i].position.y == y && map->chunks[i].position.z == couche) {
            return &map->chunks[i];
        }
    }

    return NULL;
}


/**
 * @brief Get the Predominance object
 * 
 * @param alentours 
 * @param nbElementsAlentours 
 * @return t_predominance 
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
 * @brief 
 * 
 * @param xChunk 
 * @param yChunk 
 * @return e_biome 
 * 
 * @version 1.1
 */
e_biome selectionBiome(const int xChunk, const int yChunk) {
    if (xChunk == 0 || yChunk == 0 || xChunk == TAILLE_MAP - 1 || yChunk == TAILLE_MAP - 1) return BIOME_PROFONDEUR;


    const int probabilite = getNombreAleatoire(1, 100); 

    for (int i = 0; i < NB_BIOMES; i++) {
        if (probabilitesBiomes[i] >= probabilite) return biomes[i];
    }
    
  
    return -1;
}



/**
 * @brief 
 * 
 * @param biome 
 * @return e_solTag 
 * 
 * @version 1.1
 */
e_solTag selectionBlock(const e_biome biome) {
    e_solTag blockTag = VIDE;
    const t_baseBiome baseBiome = basesBiomes[biome];
    const int nombreBlockPossible = sizeof(baseBiome.typesDeSol) / sizeof(baseBiome.typesDeSol[0]);


    while (blockTag == VIDE) {
        const int index =  getNombreAleatoire(0, nombreBlockPossible - 1);
        const int probabilite =  getNombreAleatoire(0, 100);
    
        const int probabiliteBlock = baseBiome.probabiliteDesBlocks[index];
        if (probabiliteBlock >= probabilite) {
            return baseBiome.typesDeSol[index];
        }
    }
  
  
    return blockTag;
}





/* -------------------------------------------------------------------------- */
/*                                 Changement                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param biomePredominant 
 * @param biomeActuel 
 * @return e_biome 
 * 
 * @version 1.2
 */
e_biome changerBiome(t_predominance biomePredominant, e_biome biomeActuel) { 
    if (biomePredominant.tag == biomeActuel) return biomeActuel;

    int modificateurAltitude = 0;
    int changement = 0;
  
  
    switch (biomePredominant.tag) {
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


    if (changement) {
        if (biomePredominant.tag > biomeActuel) 
            modificateurAltitude = 1;
        else if (biomePredominant.tag < biomeActuel)
            modificateurAltitude = -1;
    }


    return biomeActuel + modificateurAltitude;
}





/**
 * @brief 
 * 
 * @param blockPredominant 
 * @param blockActuel 
 * @return e_blockTag 
 * 
 * @version 1.2
 */
e_solTag changerBlock(t_predominance blockPredominant, e_solTag blockActuel) {
    if (blockPredominant.tag == blockActuel) return blockActuel;

    return blockActuel + (blockPredominant.tag - blockActuel);
}





/* -------------------------------------------------------------------------- */
/*                                  Alentours                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Get the Biomes Alentours object
 * 
 * @param chunk 
 * @param map 
 * @return int* 
 * 
 * @version 1.2
 */
int* getBiomesAlentours(t_chunk *chunk, t_map *map) {
    static int biomesAlentours[NB_BIOMES] = { 0 };
    t_chunk *chunkCourrant = NULL;
  

    for (int y = chunk->position.y - 1; y <= chunk->position.y + 1; y++) {
        for (int x = chunk->position.x - 1; x <= chunk->position.x + 1; x++) {
            if (!chunkEstDansLaMap(x, y, COUCHE_SOL)) continue;
            if (x == chunk->position.x && y == chunk->position.y) continue;

          
            chunkCourrant = getChunk(x, y, COUCHE_SOL, map);
            if (chunkCourrant != NULL) {
                biomesAlentours[chunkCourrant->biome]++;
            }
        }
    }


    return biomesAlentours;
}



/**
 * @brief Get the Blocks Alentours object
 * 
 * @param xBlock 
 * @param yBlock 
 * @param map 
 * @return int* 
 * 
 * @version 1.1
 */
int* getBlocksAlentours(const int xBlock, const int yBlock, t_map *map) {
    static int blocksAlentours[NB_BLOCKS] = { 0 };
    t_chunk *chunk = NULL;
    t_block *block = NULL;

  
    for (int y = yBlock - 1; y <= yBlock + 1; y++) {
        for (int x = xBlock - 1; x <= xBlock + 1; x++) {
            if (x == xBlock && y == yBlock) continue;
            if (!blockEstDansLaMap(x, y)) continue;

            chunk = getChunk(x / TAILLE_CHUNK, y / TAILLE_CHUNK, COUCHE_SOL, map);
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
 * @brief 
 * 
 * @param chunk 
 * @param map 
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
            t_predominance blockPredominant = getPredominance(blocksAlentours, NB_BLOCKS);

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
 * @brief 
 * 
 * @param chunk 
 * @param map 
 * @param ceuil 
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

            for (int i = 0; i < NB_BLOCKS; i++) {
                if (i > block->tag)
                    hauteurVoisins[x][y] += blocksAlentours[i];
                else if (i < block->tag)
                    hauteurVoisins[x][y] -= blocksAlentours[i];
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
 * @brief 
 * 
 * @param map 
 * 
 * @version 1.1
 */
void normalisationDeLaMap(t_map* map) {  
    e_biome nouveauxBiomes[TAILLE_MAP][TAILLE_MAP] = { BIOME_PROFONDEUR };
    t_chunk *chunk = NULL;


    for (int y = 0; y < TAILLE_MAP; y++) {
        for (int x = 0; x < TAILLE_MAP; x++) {
            chunk = getChunk(x, y, COUCHE_SOL, map);
            if (chunk == NULL) continue;
            if (chunk->position.x == 0 || chunk->position.y == 0 || chunk->position.x == TAILLE_MAP - 1 || chunk->position.y == TAILLE_MAP - 1) continue;
          
            int *biomesAlentours = getBiomesAlentours(chunk, map);
            t_predominance biomePredominant = getPredominance(biomesAlentours, NB_BIOMES);

          
            nouveauxBiomes[y][x] = changerBiome(biomePredominant, chunk->biome);
        }
    }


    for (int y = 0; y < TAILLE_MAP; y++) {
        for (int x = 0; x < TAILLE_MAP; x++) {
            chunk = getChunk(x, y, COUCHE_SOL, map);
            chunk->biome = nouveauxBiomes[y][x];
        }
    }
}





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param z 
 * @return t_chunk 
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
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param chunk 
 * @param estVide 
 * @return t_block 
 * 
 * @version 1.2
 */
t_block generationBlock(const int x, const int y, const t_chunk *chunk, const int estVide) {
    t_block block;


    block.tag = estVide ? VIDE : selectionBlock(chunk->biome);

    t_vecteur2 position = { (TAILLE_CHUNK * chunk->position.x) + x, (TAILLE_CHUNK * chunk->position.y) + y };
    t_vecteur2 positionDansChunk = { x, y };
  
    block.position = position;
    block.positionDansChunk = positionDansChunk;


    return block;
}



/**
 * @brief 
 * 
 * @param chunk 
 * @param map 
 * @param estVide 
 * @return t_chunk* 
 * 
 * @version 1.3
 */
t_chunk* generationChunk(t_chunk *chunk, t_map *map, const int estVide) {
    for (int x = 0, i = 0; x < TAILLE_CHUNK; x++) {
        for (int y = 0; y < TAILLE_CHUNK; y++) {
            chunk->blocks[i++] = generationBlock(x, y, chunk, estVide);
        }
    }


    if (estVide) return chunk;


    for (int i = 0; i < 2; i++) {
        normalisationDuChunk(chunk, map);
        lissageDuChunk(chunk, map, 7 - i);
    }

    lissageDuChunk(chunk, map, 5);


    return chunk;
}



/**
 * @brief 
 * 
 * @return t_map* 
 * 
 * @version 1.1
 */
t_map* genererMap() {
    t_map* map = malloc(sizeof(t_map));
    t_chunk* chunkTempo = NULL;

    map->chunks = calloc(TAILLE_MAP * TAILLE_MAP * NB_COUCHE, sizeof(t_chunk));


    for (int i = 0, x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            for (int z = 0; z < NB_COUCHE; z++) {
                map->chunks[i++] = initialisationChunk(x, y, z);
            }
        }
    }


    for (int i = 0; i < 1; i++) {
        normalisationDeLaMap(map);
    }


    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            for (int z = 0; z < NB_COUCHE; z++) {
                chunkTempo = getChunk(x, y, z, map);

                if (z == COUCHE_SOL) 
                    generationChunk(chunkTempo, map, 0);
                else
                    generationChunk(chunkTempo, map, 1);
            }
        }
    }


    // genererVegetations(map);

    

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
    // t_block *block = NULL;
  

    // for (int x = 0; x < TAILLE_CHUNK; x++) {
    //     for (int y = 0; y < TAILLE_CHUNK; y++) {
    //         block = getBlockDansChunk(x, y, *chunk);
    //         // detruireBlock(&block);
    //     }
    // }
  
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